/*
 * yactfr virtual machine.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_VM_HPP
#define _YACTFR_VM_HPP

#include <cassert>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits>
#include <algorithm>
#include <type_traits>
#include <cstdint>

#include <yactfr/aliases.hpp>
#include <yactfr/element.hpp>
#include <yactfr/data-source-factory.hpp>
#include <yactfr/element.hpp>
#include <yactfr/element-sequence-iterator.hpp>
#include <yactfr/decoding-errors.hpp>

#include "proc.hpp"
#include "std-int-reader.hpp"

namespace yactfr {
namespace internal {

constexpr auto SIZE_UNSET = std::numeric_limits<Size>::max();
constexpr auto SAVED_VALUE_UNSET = std::numeric_limits<std::uint64_t>::max();

// possible VM states
enum class VmState {
    BEGIN_PACKET,
    BEGIN_PACKET_CONTENT,
    END_PACKET_CONTENT,
    END_PACKET,
    BEGIN_EVENT_RECORD,
    END_EVENT_RECORD,
    EXEC_INSTR,
    EXEC_ARRAY_INSTR,
    READ_UUID_BYTE,
    READ_SUBSTRING_UNTIL_NULL,
    READ_SUBSTRING,
    END_STRING,
    SET_PACKET_UUID,
    CONTINUE_SKIP_PADDING_BITS,
    CONTINUE_SKIP_CONTENT_PADDING_BITS,
};

// VM stack frame
struct VmStackFrame final
{
    explicit VmStackFrame(const Proc& proc, const VmState parentState) :
        proc {&proc.rawProc()},
        it {std::begin(proc.rawProc())},
        parentState {parentState}
    {
    }

    // base procedure (container of `it` below)
    const Proc::Raw *proc;

    // _next_ instruction to execute (part of `*proc` above)
    Proc::RawIterator it;

    // state when this frame was created
    VmState parentState;

    /*
     * Array elements left to read (`*proc` is the procedure of this
     * array read instruction in this case).
     */
    Size remElems;
};

/*
 * This contains the whole state of a yactfr VM _except_ for everything
 * related to data source/buffering.
 */
class VmPos final
{
public:
    VmPos(const PacketProc& packetProc);
    VmPos(const VmPos& other);
    VmPos& operator=(const VmPos& other);

public:
    void setState(const VmState newState)
    {
        state = newState;
    }

    void stackPush(const Proc& proc)
    {
        stack.push_back(VmStackFrame {proc, state});
    }

    VmStackFrame& stackTop() noexcept
    {
        assert(!stack.empty());
        return stack.back();
    }

    void stackPop()
    {
        assert(!stack.empty());
        stack.pop_back();
    }

    void setParentStateAndStackPop() noexcept
    {
        assert(!stack.empty());
        state = this->stackTop().parentState;
        this->stackPop();
    }

    void gotoNextInstr()
    {
        ++this->stackTop().it;
    }

    void gotoNextArrayElemInstr()
    {
        auto& stackTop = this->stackTop();

        ++stackTop.it;

        if (stackTop.it == std::end(*stackTop.proc)) {
            assert(stackTop.remElems > 0);
            --stackTop.remElems;
            stackTop.it = std::begin(*stackTop.proc);
        }
    }

    void loadNewProc(const Proc& proc)
    {
        assert(stack.empty());
        this->stackPush(proc);
    }

    const Instr& nextInstr() noexcept
    {
        return **this->stackTop().it;
    }

    void saveValue(const Index pos) noexcept
    {
        assert(pos < savedValues.size());
        savedValues[pos] = lastIntVal.u;
    }

    std::uint64_t savedValue(const Index pos) noexcept
    {
        assert(pos < savedValues.size());
        return savedValues[pos];
    }

    std::uint64_t updateClockValue(const Index index, const Size size) noexcept
    {
        assert(index < clockValues.size());

        /*
         * Special case for a 64-bit new value, which is the limit of a
         * clock value as of this version: overwrite the current value
         * directly.
         */
        if (size == 64) {
            clockValues[index] = lastIntVal.u;
            return lastIntVal.u;
        }

        auto curValue = clockValues[index];
        const auto newValueMask = (UINT64_C(1) << size) - 1;
        const auto curValueMasked = curValue & newValueMask;

        if (lastIntVal.u < curValueMasked) {
            /*
             * It looks like a wrap occured on the number of bits of the
             * new value. Assume that the clock value wrapped only one
             * time.
             */
            curValue += newValueMask + 1;
        }

        // clear the low bits of the current clock value
        curValue &= ~newValueMask;

        // set the low bits of the current clock value
        curValue |= lastIntVal.u;

        // store this result
        clockValues[index] = curValue;
        return curValue;
    }

    Size remainingContentBitsInPacket() const noexcept
    {
        return curPacketContentSizeBits - cursorOffsetInCurPacketBits;
    }

    Index cursorOffsetInElementSequenceBits() const noexcept
    {
        return curPacketOffsetInElementSequenceBits +
               cursorOffsetInCurPacketBits;
    }

    void resetForNewPacket()
    {
        cursorOffsetInCurPacketBits = 0;
        state = VmState::BEGIN_PACKET;
        lastBo = boost::none;
        curDstPacketProc = nullptr;
        curErtProc = nullptr;
        curPacketTotalSizeBits = SIZE_UNSET;
        curPacketContentSizeBits = SIZE_UNSET;
        stack.clear();
        std::fill(std::begin(clockValues), std::end(clockValues), 0);
        std::fill(std::begin(savedValues), std::end(savedValues), SAVED_VALUE_UNSET);
    }

private:
    void _initVectorsFromPacketProc();
    void _setSimpleFromOther(const VmPos& other);
    void _setFromOther(const VmPos& other);

public:
    // offset of current packet beginning within its element sequence (bits)
    Index curPacketOffsetInElementSequenceBits = 0;

    // cursor offset within current packet (bits)
    Index cursorOffsetInCurPacketBits = 0;

    // current elements
    struct {
        PacketBeginningElement packetBeginning;
        PacketEndElement packetEnd;
        ScopeBeginningElement scopeBeginning;
        ScopeEndElement scopeEnd;
        PacketContentBeginningElement packetContentBeginning;
        PacketContentEndElement packetContentEnd;
        EventRecordBeginningElement eventRecordBeginning;
        EventRecordEndElement eventRecordEnd;
        DataStreamIdElement dataStreamId;
        PacketOriginIndexElement packetOriginIndex;
        ExpectedPacketTotalSizeElement expectedPacketTotalSize;
        ExpectedPacketContentSizeElement expectedPacketContentSize;
        PacketMagicNumberElement packetMagicNumber;
        PacketUuidElement packetUuid;
        ClockValueElement clockValue;
        PacketEndClockValueElement packetEndClockValue;
        DataStreamTypeElement dataStreamType;
        EventRecordTypeElement eventRecordType;
        SignedIntElement signedInt;
        UnsignedIntElement unsignedInt;
        SignedEnumElement signedEnum;
        UnsignedEnumElement unsignedEnum;
        FloatElement flt;
        StringBeginningElement stringBeginning;
        StringEndElement stringEnd;
        SubstringElement substring;
        StaticArrayBeginningElement staticArrayBeginning;
        StaticArrayEndElement staticArrayEnd;
        StaticTextArrayBeginningElement staticTextArrayBeginning;
        StaticTextArrayEndElement staticTextArrayEnd;
        DynamicArrayBeginningElement dynamicArrayBeginning;
        DynamicArrayEndElement dynamicArrayEnd;
        DynamicTextArrayBeginningElement dynamicTextArrayBeginning;
        DynamicTextArrayEndElement dynamicTextArrayEnd;
        StructBeginningElement structBeginning;
        StructEndElement structEnd;
        VariantBeginningSignedTagElement variantBeginningSignedTag;
        VariantBeginningUnsignedTagElement variantBeginningUnsignedTag;
        VariantEndElement variantEnd;
    } elems;

    // next state to handle
    VmState state = VmState::BEGIN_PACKET;

    // state after aligning
    VmState postSkipBitsState;

    // state after reading string (until null)
    VmState postEndStringState;

    // last bit array byte order
    boost::optional<ByteOrder> lastBo;

    // remaining padding bits to skip for alignment
    Size remBitsToSkip = 0;

    // last integer value
    union {
        std::uint64_t u;
        std::int64_t i;
    } lastIntVal;

    // current ID (event record or data stream type)
    TypeId curId;

    // packet procedure
    const PacketProc *packetProc = nullptr;

    // current data stream type packet procedure
    const DataStreamTypePacketProc *curDstPacketProc = nullptr;

    // current event record type procedure
    const EventRecordTypeProc *curErtProc = nullptr;

    // packet UUID
    boost::uuids::uuid uuid;

    // current packet total size (bits)
    Size curPacketTotalSizeBits = SIZE_UNSET;

    // current packet content size (bits)
    Size curPacketContentSizeBits = SIZE_UNSET;

    // stack
    std::vector<VmStackFrame> stack;

    // vector of saved values
    std::vector<std::uint64_t> savedValues;

    // vector of clock values
    std::vector<std::uint64_t> clockValues;
};

class IterInfos
{
public:
    void setElemFromOther(const VmPos *myPos, const VmPos *otherPos,
                          const Element *otherElem)
    {
        const auto otherElemAddr = reinterpret_cast<std::uintptr_t>(otherElem);
        const auto otherPosAddr = reinterpret_cast<std::uintptr_t>(otherPos);
        const auto diff = otherElemAddr - otherPosAddr;
        const auto myPosAddr = reinterpret_cast<std::uintptr_t>(myPos);

        elem = reinterpret_cast<const Element *>(myPosAddr + diff);
    }

    bool operator==(const IterInfos& other) const noexcept
    {
        return offset == other.offset && mark == other.mark;
    }

    bool operator!=(const IterInfos& other) const noexcept
    {
        return offset != other.offset || mark != other.mark;
    }

    bool operator<(const IterInfos& other) const noexcept
    {
        return offset < other.offset || (offset == other.offset &&
                                         mark < other.mark);
    }

    bool operator<=(const IterInfos& other) const noexcept
    {
        return offset < other.offset || (offset == other.offset &&
                                         mark <= other.mark);
    }

    bool operator>(const IterInfos& other) const noexcept
    {
        return offset > other.offset || (offset == other.offset &&
                                         mark > other.mark);
    }

    bool operator>=(const IterInfos& other) const noexcept
    {
        return offset > other.offset || (offset == other.offset &&
                                         mark >= other.mark);
    }

public:
    Index mark = 0;
    Index offset = 0;

    /*
     * Points to one of the elements in the `elems` field of the
     * VmPos in the same ElementSequenceIteratorPosition.
     */
    const Element *elem = nullptr;
};

class Vm final
{
public:
    explicit Vm(DataSourceFactory *dataSrcFactory,
                const PacketProc& packetProc, ElementSequenceIterator& iter);
    Vm(const Vm& vm, ElementSequenceIterator& iter);
    Vm& operator=(const Vm& vm);
    void seekPacket(Index offset);
    void savePosition(ElementSequenceIteratorPosition& pos) const;
    void restorePosition(const ElementSequenceIteratorPosition& pos);

    const VmPos& pos() const
    {
        return _pos;
    }

    void nextElement()
    {
        while (YACTFR_UNLIKELY(!this->_handleState()));
    }

    void updateIterElementFromOtherPos(const VmPos& otherPos,
                                       const Element* otherElem)
    {
        if (!otherElem) {
            _iter->_curElement = nullptr;
        } else {
            const auto posElemAddr = reinterpret_cast<std::uintptr_t>(otherElem);
            const auto posAddr = reinterpret_cast<std::uintptr_t>(&otherPos);
            const auto diff = posElemAddr - posAddr;
            const auto myPosAddr = reinterpret_cast<std::uintptr_t>(&_pos);

            _iter->_curElement = reinterpret_cast<const Element *>(myPosAddr + diff);
        }
    }

    void iter(ElementSequenceIterator& iter)
    {
        _iter = &iter;
    }

    ElementSequenceIterator& iter()
    {
        return *_iter;
    }

private:
    // instruction handler status
    enum class _ExecReaction {
        EXEC_NEXT_INSTR,
        FETCH_NEXT_INSTR_AND_STOP,
        CHANGE_STATE,
        EXEC_CUR_INSTR,
        STOP,
    };

private:
    void _initExecFuncs();
    bool _getNewDataBlock(Index offsetInElementSequenceBytes, Size sizeBytes);

    bool _handleState()
    {
        switch (_pos.state) {
        case VmState::EXEC_INSTR:
            return this->_stateExecInstr();

        case VmState::EXEC_ARRAY_INSTR:
            return this->_stateExecArrayInstr();

        case VmState::BEGIN_EVENT_RECORD:
            return this->_stateBeginEventRecord();

        case VmState::END_EVENT_RECORD:
            return this->_stateEndEventRecord();

        case VmState::READ_SUBSTRING:
            return this->_stateReadSubstring();

        case VmState::READ_SUBSTRING_UNTIL_NULL:
            return this->_stateReadSubstringUntilNull();

        case VmState::END_STRING:
            return this->_stateEndString();

        case VmState::CONTINUE_SKIP_PADDING_BITS:
            return this->_stateContinueSkipPaddingBits();

        case VmState::CONTINUE_SKIP_CONTENT_PADDING_BITS:
            return this->_stateContinueSkipPaddingBits();

        case VmState::READ_UUID_BYTE:
            return this->_stateReadUuidByte();

        case VmState::SET_PACKET_UUID:
            return this->_stateSetPacketUuid();

        case VmState::BEGIN_PACKET:
            return this->_stateBeginPacket();

        case VmState::BEGIN_PACKET_CONTENT:
            return this->_stateBeginPacketContent();

        case VmState::END_PACKET_CONTENT:
            return this->_stateEndPacketContent();

        case VmState::END_PACKET:
            return this->_stateEndPacket();

        default:
            abort();
        }
    }

    bool _stateExecInstr()
    {
        while (true) {
            const auto status = this->_exec(_pos.nextInstr());

            if (YACTFR_LIKELY(status == _ExecReaction::FETCH_NEXT_INSTR_AND_STOP)) {
                _pos.gotoNextInstr();
                return true;
            }

            switch (status) {
            case _ExecReaction::STOP:
                return true;

            case _ExecReaction::EXEC_NEXT_INSTR:
                _pos.gotoNextInstr();
                break;

            case _ExecReaction::EXEC_CUR_INSTR:
                break;

            case _ExecReaction::CHANGE_STATE:
                // the handler changed the state: return false to continue
                return false;

            default:
                abort();
            }
        }

        return true;
    }

    bool _stateExecArrayInstr()
    {
        if (_pos.stackTop().remElems == 0) {
            _pos.setParentStateAndStackPop();
            return false;
        }

        while (true) {
            auto& stackTop = _pos.stackTop();

            if (stackTop.it == std::end(*stackTop.proc)) {
                assert(stackTop.remElems > 0);
                --stackTop.remElems;

                if (_pos.stackTop().remElems == 0) {
                    _pos.setParentStateAndStackPop();
                    return false;
                }

                stackTop.it = std::begin(*stackTop.proc);
                continue;
            }

            const auto status = this->_exec(_pos.nextInstr());

            if (YACTFR_LIKELY(status == _ExecReaction::FETCH_NEXT_INSTR_AND_STOP)) {
                _pos.gotoNextInstr();
                return true;
            }

            switch (status) {
            case _ExecReaction::STOP:
                return true;

            case _ExecReaction::EXEC_NEXT_INSTR:
                _pos.gotoNextInstr();
                break;

            default:
                abort();
            }
        }

        return true;
    }

    bool _stateContinueSkipPaddingBits()
    {
        this->_continueSkipPaddingBits(_pos.state == VmState::CONTINUE_SKIP_CONTENT_PADDING_BITS);
        _pos.setState(_pos.postSkipBitsState);

        // not done: handle next state immediately
        return false;
    }

    bool _stateBeginPacket()
    {
        this->_resetIterMark();
        _pos.resetForNewPacket();

        if (this->_remainingBitsInBuf() == 0) {
            // try getting 1 bit to see if we're at the end of the element sequence
            if (!this->_tryHaveBits(1)) {
                this->_setIterEnd();
                return true;
            }
        }

        this->_updateIterCurOffset(_pos.elems.packetBeginning);
        _pos.loadNewProc(_pos.packetProc->preambleProc());
        _pos.setState(VmState::BEGIN_PACKET_CONTENT);
        return true;
    }

    bool _stateBeginPacketContent()
    {
        this->_updateIterCurOffset(_pos.elems.packetContentBeginning);

        // the packet's preamble procedure is already loaded at this point
        _pos.setState(VmState::EXEC_INSTR);
        return true;
    }

    bool _stateEndPacketContent()
    {
        /*
         * Next time, skip the padding bits after the packet content before
         * setting the state to END_PACKET. If we have no packet size, then
         * the element sequence contains only one packet and there's no
         * padding after the packet content.
         */
        Size bitsToSkip = 0;

        if (_pos.curPacketTotalSizeBits != SIZE_UNSET) {
            bitsToSkip = _pos.curPacketTotalSizeBits -
                         _pos.cursorOffsetInCurPacketBits;
        }

        if (bitsToSkip > 0) {
            _pos.remBitsToSkip = bitsToSkip;
            _pos.postSkipBitsState = VmState::END_PACKET;
            _pos.state = VmState::CONTINUE_SKIP_PADDING_BITS;
        } else {
            // nothing to skip, go to end directly
            _pos.state = VmState::END_PACKET;
        }

        this->_updateIterCurOffset(_pos.elems.packetContentEnd);
        return true;
    }

    bool _stateEndPacket()
    {
        const auto offset = _pos.cursorOffsetInElementSequenceBits();

        // readjust buffer address and offsets
        _pos.curPacketOffsetInElementSequenceBits = _pos.cursorOffsetInElementSequenceBits();
        _pos.cursorOffsetInCurPacketBits = 0;
        assert((_pos.curPacketOffsetInElementSequenceBits & 7) == 0);

        if (_pos.curPacketTotalSizeBits == SIZE_UNSET) {
            // element sequence contains a single packet
            this->_resetBuffer();
        } else {
            const auto oldBufAddr = _bufAddr;

            _bufAddr -= (_bufOffsetInCurPacketBits / 8);
            _bufAddr += (_pos.curPacketTotalSizeBits / 8);
            _bufOffsetInCurPacketBits = 0;
            _bufSizeBits -= (_bufAddr - oldBufAddr) * 8;
        }

        this->_updateIter(_pos.elems.packetEnd, offset);
        _pos.setState(VmState::BEGIN_PACKET);
        return true;
    }

    bool _stateBeginEventRecord()
    {
        assert(_pos.curDstPacketProc);

        if (_pos.curPacketContentSizeBits == SIZE_UNSET) {
            if (this->_remainingBitsInBuf() == 0) {
                // try getting 1 bit to see if we're at the end of the packet
                if (!this->_tryHaveBits(1)) {
                    _pos.setState(VmState::END_PACKET_CONTENT);
                    return false;
                }
            }
        } else {
            if (_pos.remainingContentBitsInPacket() == 0) {
                _pos.setState(VmState::END_PACKET_CONTENT);
                return false;
            }
        }

        // align now so that the iterator's offset is after any padding
        this->_alignCursor(_pos.curDstPacketProc->eventRecordAlignment());

        this->_updateIterCurOffset(_pos.elems.eventRecordBeginning);
        _pos.loadNewProc(_pos.curDstPacketProc->eventRecordPreambleProc());
        _pos.setState(VmState::EXEC_INSTR);
        return true;
    }

    bool _stateEndEventRecord()
    {
        assert(_pos.curErtProc);
        _pos.curErtProc = nullptr;
        this->_updateIterCurOffset(_pos.elems.eventRecordEnd);
        _pos.setState(VmState::BEGIN_EVENT_RECORD);
        return true;
    }

    bool _stateReadUuidByte()
    {
        if (_pos.stackTop().remElems == 0) {
            // set completed UUID
            _pos.setState(VmState::SET_PACKET_UUID);
            return false;
        }

        auto& instr = **_pos.stackTop().it;

        this->_execReadStdInt<std::uint64_t, 8, readIntUnsigned8>(instr);
        _pos.uuid.data[16 - _pos.stackTop().remElems] = static_cast<std::uint8_t>(_pos.lastIntVal.u);
        --_pos.stackTop().remElems;
        return true;
    }

    bool _stateSetPacketUuid()
    {
        assert(_pos.packetProc->traceType().uuid());

        // _pos.elems.packetUuid._expectedUuid is already set once
        _pos.elems.packetUuid._uuid = _pos.uuid;
        this->_updateIterCurOffset(_pos.elems.packetUuid);
        _pos.setParentStateAndStackPop();
        return true;
    }

    bool _stateReadSubstring()
    {
        assert((_pos.cursorOffsetInCurPacketBits & 7) == 0);

        if (_pos.stackTop().remElems == 0) {
            _pos.setParentStateAndStackPop();
            return false;
        }

        // require at least one byte
        this->_requireContentBits(8);

        auto buf = this->_bufAtCursor();
        const auto bufSizeBytes = this->_remainingBitsInBuf() / 8;
        const auto substringSizeBytes = std::min(bufSizeBytes,
                                                 _pos.stackTop().remElems);
        const auto substringSizeBits = substringSizeBytes * 8;

        if (substringSizeBits > _pos.remainingContentBitsInPacket()) {
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.cursorOffsetInElementSequenceBits(),
                substringSizeBits, _pos.remainingContentBitsInPacket()
            };
        }

        _pos.elems.substring._begin = reinterpret_cast<const char *>(buf);
        _pos.elems.substring._end = reinterpret_cast<const char *>(buf + substringSizeBytes);
        assert(_pos.elems.substring.size() > 0);
        this->_updateIterCurOffset(_pos.elems.substring);
        this->_consumeExistingBits(substringSizeBytes * 8);
        _pos.stackTop().remElems -= substringSizeBytes;
        return true;
    }

    bool _stateReadSubstringUntilNull()
    {
        assert((_pos.cursorOffsetInCurPacketBits & 7) == 0);

        // require at least one byte
        this->_requireContentBits(8);

        auto buf = this->_bufAtCursor();
        const auto bufSizeBytes = this->_remainingBitsInBuf() / 8;

        assert(bufSizeBytes >= 1);

        auto res = reinterpret_cast<const char *>(std::memchr(buf, 0, bufSizeBytes));
        auto begin = reinterpret_cast<const char *>(buf);
        const char *end;

        if (res) {
            // _after_ the null byte to include it
            end = res + 1;
        } else {
            // no null byte yet: current end of buffer
            end = reinterpret_cast<const char *>(buf + bufSizeBytes);
        }

        const Size substringSizeBits = (end - begin) * 8;

        if (substringSizeBits > _pos.remainingContentBitsInPacket()) {
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.cursorOffsetInElementSequenceBits(),
                substringSizeBits, _pos.remainingContentBitsInPacket()
            };
        }

        _pos.elems.substring._begin = begin;
        _pos.elems.substring._end = end;

        if (res) {
            // we're done
            _pos.setState(VmState::END_STRING);
        }

        assert(_pos.elems.substring.size() > 0);
        this->_updateIterCurOffset(_pos.elems.substring);
        this->_consumeExistingBits(_pos.elems.substring.size() * 8);
        return true;
    }

    bool _stateEndString()
    {
        this->_updateIterCurOffset(_pos.elems.stringEnd);
        _pos.setState(_pos.postEndStringState);
        assert(_pos.state == VmState::EXEC_INSTR ||
               _pos.state == VmState::EXEC_ARRAY_INSTR);
        return true;
    }

    _ExecReaction _exec(const Instr& instr)
    {
        assert(instr.kind() != Instr::Kind::BEGIN_READ_VARIANT_UNKNOWN_TAG);
        return (this->*_execFuncs[static_cast<int>(instr.kind())])(instr);
    }

    void _updateIter(const Element& elem, const Index offset)
    {
        _iter->_curElement = &elem;
        _iter->_offset = offset;
        ++_iter->_mark;
    }

    void _updateIterCurOffset(const Element& elem)
    {
        _iter->_curElement = &elem;
        _iter->_offset = _pos.cursorOffsetInElementSequenceBits();
        ++_iter->_mark;
    }

    void _setIterEnd() const noexcept
    {
        _iter->_mark = 0;
        _iter->_offset = ElementSequenceIterator::_END_OFFSET;
    }

    void _resetIterMark() const noexcept
    {
        _iter->_mark = 0;
    }

    void _alignCursor(const Size alignment)
    {
        const auto newCursorOffsetBits = (_pos.cursorOffsetInCurPacketBits +
                                          alignment - 1) & -alignment;
        const auto bitsToSkip = newCursorOffsetBits -
                                _pos.cursorOffsetInCurPacketBits;

        if (YACTFR_LIKELY(bitsToSkip == 0)) {
            // already aligned! yay!
            return;
        }

        if (YACTFR_UNLIKELY(bitsToSkip > _pos.remainingContentBitsInPacket())) {
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.cursorOffsetInElementSequenceBits(),
                bitsToSkip, _pos.remainingContentBitsInPacket()
            };
        }

        _pos.remBitsToSkip = bitsToSkip;
        _pos.postSkipBitsState = _pos.state;
        _pos.state = VmState::CONTINUE_SKIP_CONTENT_PADDING_BITS;
        this->_continueSkipPaddingBits(true);
    }

    void _alignCursor(const Instr& instr)
    {
        this->_alignCursor(static_cast<const InstrReadData&>(instr).alignment());
    }

    void _continueSkipPaddingBits(const bool contentBits)
    {
        while (_pos.remBitsToSkip > 0) {
            if (contentBits) {
                this->_requireContentBits(1);
            } else {
                this->_requireBits(1);
            }

            const auto bitsToSkip = std::min(_pos.remBitsToSkip,
                                             this->_remainingBitsInBuf());

            _pos.remBitsToSkip -= bitsToSkip;
            this->_consumeExistingBits(bitsToSkip);
        }

        // we're done now!
        _pos.setState(_pos.postSkipBitsState);
    }

    bool _tryHaveBits(const Size bits)
    {
        assert(bits <= 64);

        if (YACTFR_LIKELY(bits <= this->_remainingBitsInBuf())) {
            // we still have enough
            return true;
        }

        /*
         * Align the current cursor to its current byte and compute the
         * offset, from the beginning of the element sequence, to
         * request in bytes at this point.
         */
        const auto flooredCursorOffsetInCurPacketBits = _pos.cursorOffsetInCurPacketBits & ~7ULL;
        const auto flooredCursorOffsetInCurPacketBytes = flooredCursorOffsetInCurPacketBits / 8;
        const auto curPacketOffsetInElementSequenceBytes = _pos.curPacketOffsetInElementSequenceBits / 8;
        const auto requestOffsetInElementSequenceBytes = curPacketOffsetInElementSequenceBytes +
                                                        flooredCursorOffsetInCurPacketBytes;
        const auto bitInByte = _pos.cursorOffsetInCurPacketBits & 7;
        const auto sizeBytes = (bits + 7 + bitInByte) / 8;

        return this->_getNewDataBlock(requestOffsetInElementSequenceBytes,
                                      sizeBytes);
    }

    void _requireBits(const Size bits)
    {
        if (YACTFR_UNLIKELY(!this->_tryHaveBits(bits))) {
            throw PrematureEndOfDataDecodingError {
                _pos.cursorOffsetInElementSequenceBits(), bits
            };
        }
    }

    void _requireContentBits(const Size bits)
    {
        if (YACTFR_UNLIKELY(bits > _pos.remainingContentBitsInPacket())) {
            // going past the packet's content
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.cursorOffsetInElementSequenceBits(),
                bits, _pos.remainingContentBitsInPacket()
            };
        }

        this->_requireBits(bits);
    }

    const std::uint8_t *_bufAtCursor() const noexcept
    {
        const auto offsetBytes = (_pos.cursorOffsetInCurPacketBits -
                                  _bufOffsetInCurPacketBits) / 8;

        return &_bufAddr[offsetBytes];
    }

    Size _remainingBitsInBuf() const noexcept
    {
        return (_bufOffsetInCurPacketBits + _bufSizeBits) -
               _pos.cursorOffsetInCurPacketBits;
    }

    void _consumeExistingBits(const Size bitsToConsume) noexcept
    {
        assert(bitsToConsume <= this->_remainingBitsInBuf());
        _pos.cursorOffsetInCurPacketBits += bitsToConsume;
    }

    void _resetBuffer() noexcept
    {
        _bufAddr = nullptr;
        _bufSizeBits = 0;
        _bufOffsetInCurPacketBits = _pos.cursorOffsetInCurPacketBits;
    }

    // instruction handlers
    _ExecReaction _execReadSignedIntLe(const Instr& instr);
    _ExecReaction _execReadSignedIntBe(const Instr& instr);
    _ExecReaction _execReadSignedIntA8(const Instr& instr);
    _ExecReaction _execReadSignedIntA16Le(const Instr& instr);
    _ExecReaction _execReadSignedIntA32Le(const Instr& instr);
    _ExecReaction _execReadSignedIntA64Le(const Instr& instr);
    _ExecReaction _execReadSignedIntA16Be(const Instr& instr);
    _ExecReaction _execReadSignedIntA32Be(const Instr& instr);
    _ExecReaction _execReadSignedIntA64Be(const Instr& instr);
    _ExecReaction _execReadUnsignedIntLe(const Instr& instr);
    _ExecReaction _execReadUnsignedIntBe(const Instr& instr);
    _ExecReaction _execReadUnsignedIntA8(const Instr& instr);
    _ExecReaction _execReadUnsignedIntA16Le(const Instr& instr);
    _ExecReaction _execReadUnsignedIntA32Le(const Instr& instr);
    _ExecReaction _execReadUnsignedIntA64Le(const Instr& instr);
    _ExecReaction _execReadUnsignedIntA16Be(const Instr& instr);
    _ExecReaction _execReadUnsignedIntA32Be(const Instr& instr);
    _ExecReaction _execReadUnsignedIntA64Be(const Instr& instr);
    _ExecReaction _execReadFloat32Le(const Instr& instr);
    _ExecReaction _execReadFloat32Be(const Instr& instr);
    _ExecReaction _execReadFloatA32Le(const Instr& instr);
    _ExecReaction _execReadFloatA32Be(const Instr& instr);
    _ExecReaction _execReadFloat64Le(const Instr& instr);
    _ExecReaction _execReadFloat64Be(const Instr& instr);
    _ExecReaction _execReadFloatA64Le(const Instr& instr);
    _ExecReaction _execReadFloatA64Be(const Instr& instr);
    _ExecReaction _execReadSignedEnumLe(const Instr& instr);
    _ExecReaction _execReadSignedEnumBe(const Instr& instr);
    _ExecReaction _execReadSignedEnumA8(const Instr& instr);
    _ExecReaction _execReadSignedEnumA16Le(const Instr& instr);
    _ExecReaction _execReadSignedEnumA32Le(const Instr& instr);
    _ExecReaction _execReadSignedEnumA64Le(const Instr& instr);
    _ExecReaction _execReadSignedEnumA16Be(const Instr& instr);
    _ExecReaction _execReadSignedEnumA32Be(const Instr& instr);
    _ExecReaction _execReadSignedEnumA64Be(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumLe(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumBe(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumA8(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumA16Le(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumA32Le(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumA64Le(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumA16Be(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumA32Be(const Instr& instr);
    _ExecReaction _execReadUnsignedEnumA64Be(const Instr& instr);
    _ExecReaction _execReadString(const Instr& instr);
    _ExecReaction _execBeginReadScope(const Instr& instr);
    _ExecReaction _execEndReadScope(const Instr& instr);
    _ExecReaction _execBeginReadStruct(const Instr& instr);
    _ExecReaction _execEndReadStruct(const Instr& instr);
    _ExecReaction _execBeginReadStaticArray(const Instr& instr);
    _ExecReaction _execEndReadStaticArray(const Instr& instr);
    _ExecReaction _execBeginReadStaticTextArray(const Instr& instr);
    _ExecReaction _execEndReadStaticTextArray(const Instr& instr);
    _ExecReaction _execBeginReadStaticUuidArray(const Instr& instr);
    _ExecReaction _execBeginReadDynamicArray(const Instr& instr);
    _ExecReaction _execEndReadDynamicArray(const Instr& instr);
    _ExecReaction _execBeginReadDynamicTextArray(const Instr& instr);
    _ExecReaction _execEndReadDynamicTextArray(const Instr& instr);
    _ExecReaction _execBeginReadVariantSignedTag(const Instr& instr);
    _ExecReaction _execBeginReadVariantUnsignedTag(const Instr& instr);
    _ExecReaction _execEndReadVariant(const Instr& instr);
    _ExecReaction _execSaveValue(const Instr& instr);
    _ExecReaction _execSetPacketEndClockValue(const Instr& instr);
    _ExecReaction _execUpdateClockValue(const Instr& instr);
    _ExecReaction _execSetCurrentId(const Instr& instr);
    _ExecReaction _execSetDataStreamType(const Instr& instr);
    _ExecReaction _execSetEventRecordType(const Instr& instr);
    _ExecReaction _execSetDataStreamId(const Instr& instr);
    _ExecReaction _execSetPacketOriginIndex(const Instr& instr);
    _ExecReaction _execSetPacketTotalSize(const Instr& instr);
    _ExecReaction _execSetPacketContentSize(const Instr& instr);
    _ExecReaction _execSetPacketMagicNumber(const Instr& instr);
    _ExecReaction _execEndPacketPreambleProc(const Instr& instr);
    _ExecReaction _execEndDstPacketPreambleProc(const Instr& instr);
    _ExecReaction _execEndDstErtPreambleProc(const Instr& instr);
    _ExecReaction _execEndErtProc(const Instr& instr);

    void _setNamedDataElementFromInstr(NamedDataElement& elem,
                                       const InstrReadData& instrReadData) noexcept
    {
        elem._name = instrReadData.fieldName();
        elem._dispName = instrReadData.fieldDisplayName();
    }

    template <typename ValT, typename ElemT>
    void _setIntElemBase(const ValT val, const Instr& instr,
                         ElemT& elem) noexcept
    {
        using DataTypeT = typename std::remove_const<typename std::remove_reference<decltype(elem.type())>::type>::type;

        auto& instrReadData = static_cast<const InstrReadData&>(instr);

        this->_setNamedDataElementFromInstr(elem, instrReadData);
        elem._type = static_cast<const DataTypeT *>(instrReadData.type());

        if (std::is_signed<ValT>::value) {
            _pos.lastIntVal.i = val;
        } else {
            _pos.lastIntVal.u = val;
        }

        elem._value = val;
        this->_updateIterCurOffset(elem);
    }

    template <typename ValT>
    void _setIntElem(const ValT val, const Instr& instr) noexcept
    {
        if (std::is_signed<ValT>::value) {
            this->_setIntElemBase(val, instr, _pos.elems.signedInt);
        } else {
            this->_setIntElemBase(val, instr, _pos.elems.unsignedInt);
        }
    }

    template <typename ValT>
    void _setEnumElem(const ValT val, const Instr& instr) noexcept
    {
        if (std::is_signed<ValT>::value) {
            this->_setIntElemBase(val, instr, _pos.elems.signedEnum);
        } else {
            this->_setIntElemBase(val, instr, _pos.elems.unsignedEnum);
        }
    }

    void _setFloatVal(const double val, const InstrReadData& instrReadData) noexcept
    {
        this->_setNamedDataElementFromInstr(_pos.elems.flt, instrReadData);
        _pos.elems.flt._type = static_cast<const FloatType *>(instrReadData.type());
        _pos.elems.flt._value = val;
        this->_updateIterCurOffset(_pos.elems.flt);
    }

    void _execReadBitArrayPreamble(const Instr& instr, const Size size)
    {
        auto& instrReadBitArray = static_cast<const InstrReadBitArray&>(instr);

        this->_alignCursor(instrReadBitArray);
        this->_requireContentBits(size);
    }

    template <typename RetT, Size SizeBits, RetT (*Func)(const std::uint8_t *)>
    RetT _readStdInt(const Instr& instr)
    {
        auto& instrReadBitArray = static_cast<const InstrReadBitArray&>(instr);

        this->_execReadBitArrayPreamble(instr, SizeBits);
        _pos.lastBo = instrReadBitArray.byteOrder();
        return Func(this->_bufAtCursor());
    }

    template <typename RetT, Size SizeBits, RetT (*Func)(const std::uint8_t *)>
    void _execReadStdInt(const Instr& instr)
    {
        const auto val = this->_readStdInt<RetT, SizeBits, Func>(instr);

        this->_setIntElem(val, instr);
        this->_consumeExistingBits(SizeBits);
    }

    template <typename RetT, Size SizeBits, RetT (*Func)(const std::uint8_t *)>
    void _execReadStdEnum(const Instr& instr)
    {
        const auto val = this->_readStdInt<RetT, SizeBits, Func>(instr);

        this->_setEnumElem(val, instr);
        this->_consumeExistingBits(SizeBits);
    }

    template <typename RetT, RetT (*Funcs[])(const std::uint8_t *)>
    RetT _readInt(const Instr& instr)
    {
        auto& instrReadBitArray = static_cast<const InstrReadBitArray&>(instr);

        this->_execReadBitArrayPreamble(instr, instrReadBitArray.size());

        if (YACTFR_LIKELY(static_cast<bool>(_pos.lastBo))) {
            if ((_pos.cursorOffsetInCurPacketBits & 7) != 0) {
                /*
                 * A bit array which does not start on a byte boundary
                 * must have the same byte order as the previous bit
                 * array.
                 */
                if (YACTFR_UNLIKELY(instrReadBitArray.byteOrder() != *_pos.lastBo)) {
                    throw ByteOrderChangeWithinByteDecodingError {
                        _pos.cursorOffsetInElementSequenceBits(),
                        *_pos.lastBo,
                        instrReadBitArray.byteOrder()
                    };
                }
            }
        }

        _pos.lastBo = instrReadBitArray.byteOrder();

        const auto index = (instrReadBitArray.size() - 1) * 8 +
                           (_pos.cursorOffsetInCurPacketBits & 7);

        return Funcs[index](this->_bufAtCursor());
    }

    template <typename RetT, RetT (*Funcs[])(const std::uint8_t *)>
    void _execReadInt(const Instr& instr)
    {
        const auto val = this->_readInt<RetT, Funcs>(instr);

        this->_setIntElem(val, instr);
        this->_consumeExistingBits(static_cast<const InstrReadBitArray&>(instr).size());
    }

    template <typename RetT, RetT (*Funcs[])(const std::uint8_t *)>
    void _execReadEnum(const Instr& instr)
    {
        const auto val = this->_readInt<RetT, Funcs>(instr);

        this->_setEnumElem(val, instr);
        this->_consumeExistingBits(static_cast<const InstrReadBitArray&>(instr).size());
    }

    template <typename FloatT>
    void _execReadFloatPost(const std::uint64_t val, const Instr& instr) noexcept
    {
        // is there a better way to do this?
        using IntT = std::conditional_t<sizeof(FloatT) == sizeof(std::uint32_t),
                                        std::uint32_t, std::uint64_t>;

        static_assert(sizeof(FloatT) == sizeof(IntT),
                      "Float and integer sizes match in union.");
        static_assert(std::alignment_of<FloatT>::value == std::alignment_of<IntT>::value,
                      "Float and integer alignments match in union.");

        union {
            FloatT flt;
            IntT uInt;
        } u;

        u.uInt = static_cast<IntT>(val);
        this->_setFloatVal(u.flt, static_cast<const InstrReadData&>(instr));
        this->_consumeExistingBits(sizeof(FloatT) * 8);
    }

    template <typename FloatT, std::uint64_t (*Funcs[])(const std::uint8_t *)>
    void _execReadFloat(const Instr& instr)
    {
        const auto val = this->_readInt<std::uint64_t, Funcs>(instr);

        this->_execReadFloatPost<FloatT>(val, instr);
    }

    template <typename FloatT, std::uint64_t (*Func)(const std::uint8_t *)>
    void _execReadStdFloat(const Instr& instr)
    {
        const auto val = this->_readStdInt<std::uint64_t, sizeof(FloatT) * 8, Func>(instr);

        this->_execReadFloatPost<FloatT>(val, instr);
    }

    template <typename InstrReadVariantT, typename ElemT>
    void _execBeginReadVariant(const Instr& instr, ElemT& elem)
    {
        this->_alignCursor(instr);

        auto& instrBeginReadVariant = static_cast<const InstrReadVariantT&>(instr);
        const auto uTag = _pos.savedValue(instrBeginReadVariant.tagPos());
        const auto tag = static_cast<typename InstrReadVariantT::Value>(uTag);
        auto proc = instrBeginReadVariant.findProc(tag);

        if (YACTFR_UNLIKELY(!proc)) {
            if (std::is_signed<typename InstrReadVariantT::Value>::value) {
                throw UnknownVariantSignedTagValueDecodingError {
                    _pos.cursorOffsetInElementSequenceBits(),
                    static_cast<std::int64_t>(tag)
                };
            } else {
                throw UnknownVariantUnsignedTagValueDecodingError {
                    _pos.cursorOffsetInElementSequenceBits(),
                    static_cast<std::uint64_t>(tag)
                };
            }
        }

        this->_setNamedDataElementFromInstr(elem, instrBeginReadVariant);
        elem._type = &instrBeginReadVariant.variantType();
        elem._tag = tag;
        this->_updateIterCurOffset(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(*proc);
        _pos.setState(VmState::EXEC_INSTR);
    }

    void _execBeginReadStaticArrayCommon(const Instr& instr,
                                         StaticArrayBeginningElement& elem,
                                         const VmState nextState)
    {
        auto& instrBeginReadStaticArray = static_cast<const InstrBeginReadStaticArray&>(instr);
        auto& staticArrayBeginningElem = static_cast<StaticArrayBeginningElement&>(elem);
        auto& namedDataElem = static_cast<NamedDataElement&>(staticArrayBeginningElem);

        this->_alignCursor(instr);
        this->_setNamedDataElementFromInstr(namedDataElem, instrBeginReadStaticArray);
        this->_updateIterCurOffset(staticArrayBeginningElem);
        _pos.gotoNextInstr();
        _pos.stackPush(instrBeginReadStaticArray.proc());
        _pos.stackTop().remElems = instrBeginReadStaticArray.length();
        _pos.setState(nextState);
    }

    void _execBeginReadDynamicArrayCommon(const Instr& instr,
                                          DynamicArrayBeginningElement& elem,
                                          const VmState nextState)
    {
        auto& instrBeginReadDynArray = static_cast<const InstrBeginReadDynamicArray&>(instr);
        const auto length = _pos.savedValue(instrBeginReadDynArray.lengthPos());

        if (YACTFR_UNLIKELY(length == SAVED_VALUE_UNSET)) {
            throw DynamicArrayLengthNotSetDecodingError {
                _pos.cursorOffsetInElementSequenceBits()
            };
        }

        this->_alignCursor(instr);
        this->_setNamedDataElementFromInstr(elem, instrBeginReadDynArray);
        elem._length = length;
        this->_updateIterCurOffset(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(instrBeginReadDynArray.proc());
        _pos.stackTop().remElems = length;
        _pos.setState(nextState);
    }

private:
    DataSourceFactory *_dataSrcFactory;
    DataSource::UP _dataSource;

    // current buffer
    const std::uint8_t *_bufAddr = nullptr;

    // size of current buffer (bits)
    Size _bufSizeBits = 0;

    // offset of buffer within current packet (bits)
    Index _bufOffsetInCurPacketBits = 0;

    // owning element sequence iterator
    ElementSequenceIterator *_iter;

    // array of instruction handler functions
    std::array<_ExecReaction (Vm::*)(const Instr&), 80> _execFuncs;

    // position (whole VM's state)
    VmPos _pos;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_VM_HPP
