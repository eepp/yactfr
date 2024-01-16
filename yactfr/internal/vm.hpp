/*
 * Copyright (C) 2017-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_VM_HPP
#define _YACTFR_INTERNAL_VM_HPP

#include <cassert>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits>
#include <algorithm>
#include <type_traits>
#include <cstdint>
#include <array>

#include <yactfr/aliases.hpp>
#include <yactfr/elem.hpp>
#include <yactfr/data-src-factory.hpp>
#include <yactfr/elem.hpp>
#include <yactfr/elem-seq-it.hpp>
#include <yactfr/decoding-errors.hpp>

#include "proc.hpp"
#include "std-fl-int-reader.hpp"
#include "fl-int-rev.hpp"

namespace yactfr {
namespace internal {

constexpr auto SIZE_UNSET = std::numeric_limits<Size>::max();
constexpr auto SAVED_VAL_UNSET = std::numeric_limits<std::uint64_t>::max();

// possible VM states
enum class VmState {
    BEGIN_PKT,
    BEGIN_PKT_CONTENT,
    END_PKT_CONTENT,
    END_PKT,
    BEGIN_ER,
    END_ER,
    EXEC_INSTR,
    EXEC_ARRAY_INSTR,
    READ_UUID_BYTE,
    READ_UTF_8_DATA_UNTIL_NULL,
    READ_UTF_16_DATA_UNTIL_NULL,
    READ_UTF_32_DATA_UNTIL_NULL,
    READ_RAW_DATA,
    READ_UUID_BLOB_SECTION,
    CONTINUE_READ_VL_UINT,
    CONTINUE_READ_VL_SINT,
    END_STR,
    SET_METADATA_STREAM_UUID,
    CONTINUE_SKIP_PADDING_BITS,
    CONTINUE_SKIP_CONTENT_PADDING_BITS,
};

// VM stack frame
struct VmStackFrame final
{
    explicit VmStackFrame(const Proc * const proc, const VmState parentState) :
        proc {proc ? &proc->rawProc() : nullptr},
        parentState {parentState}
    {
        if (proc) {
            it = proc->rawProc().begin();
        }
    }

    /*
     * Base procedure (container of `it` below).
     *
     * May be `nullptr`.
     */
    const Proc::Raw *proc;

    /*
     * _Next_ instruction to execute (part of `*proc` above).
     *
     * Not needed if `proc` is `nullptr`.
     */
    Proc::RawIt it;

    // state when this frame was created
    VmState parentState;

    /*
     * Either:
     *
     * * Array elements left to read (`*proc` is the procedure of this
     *   array read instruction in this case).
     *
     * * String bytes left to read.
     *
     * * BLOB bytes left to read.
     */
    Size rem = 0;
};

/*
 * This contains the whole state of a yactfr VM _except_ for everything
 * related to data source/buffering.
 */
class VmPos final
{
public:
    explicit VmPos(const PktProc& pktProc);
    VmPos(const VmPos& other);
    VmPos& operator=(const VmPos& other);

    void state(const VmState newState) noexcept
    {
        theState = newState;
    }

    VmState state() const noexcept
    {
        return theState;
    }

    void stackPush(const Proc * const proc = nullptr)
    {
        stack.push_back(VmStackFrame {proc, theState});
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
        theState = this->stackTop().parentState;
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

        if (stackTop.it == stackTop.proc->end()) {
            assert(stackTop.rem > 0);
            --stackTop.rem;
            stackTop.it = stackTop.proc->begin();
        }
    }

    void loadNewProc(const Proc& proc)
    {
        assert(stack.empty());
        this->stackPush(&proc);
    }

    const Instr& nextInstr() noexcept
    {
        return **this->stackTop().it;
    }

    void saveVal(const Index pos) noexcept
    {
        assert(pos < savedVals.size());
        savedVals[pos] = lastIntVal.u;
    }

    std::uint64_t savedVal(const Index pos) noexcept
    {
        assert(pos < savedVals.size());
        return savedVals[pos];
    }

    std::uint64_t updateDefClkVal(const Size len) noexcept
    {
        /*
         * Special case for a 64-bit new value, which is the limit of a
         * clock value as of this version: overwrite the current value
         * directly.
         */
        if (len == 64) {
            defClkVal = lastIntVal.u;
            return lastIntVal.u;
        }

        auto curVal = defClkVal;
        const auto newValMask = (UINT64_C(1) << len) - 1;
        const auto curValMasked = curVal & newValMask;

        if (lastIntVal.u < curValMasked) {
            /*
             * It looks like a wrap occured on the number of bits of the
             * new value. Assume that the clock value wrapped only one
             * time.
             */
            curVal += newValMask + 1;
        }

        // clear the low bits of the current clock value
        curVal &= ~newValMask;

        // set the low bits of the current clock value
        curVal |= lastIntVal.u;

        // store this result
        defClkVal = curVal;
        return curVal;
    }

    Size remContentBitsInPkt() const noexcept
    {
        return curExpectedPktContentLenBits - headOffsetInCurPktBits;
    }

    Index headOffsetInElemSeqBits() const noexcept
    {
        return curPktOffsetInElemSeqBits + headOffsetInCurPktBits;
    }

    void resetForNewPkt()
    {
        headOffsetInCurPktBits = 0;
        theState = VmState::BEGIN_PKT;
        lastFlBitArrayBo = boost::none;
        curDsPktProc = nullptr;
        curErProc = nullptr;
        curExpectedPktTotalLenBits = SIZE_UNSET;
        curExpectedPktContentLenBits = SIZE_UNSET;
        stack.clear();
        defClkVal = 0;
        std::fill(savedVals.begin(), savedVals.end(), SAVED_VAL_UNSET);

        /*
         * Reset all informative elements as a given element sequence
         * may contain packets from data streams having different types,
         * therefore having different packet context and event record
         * header types.
         */
        elems.dsInfo._reset();
        elems.pktInfo._reset();
        elems.erInfo._reset();
    }

    template <typename ElemT>
    ElemT& elemFromOther(const VmPos& otherPos, const ElemT& otherElem) const noexcept
    {
        const auto otherElemAddr = reinterpret_cast<std::uintptr_t>(&otherElem);
        const auto otherPosAddr = reinterpret_cast<std::uintptr_t>(&otherPos);
        const auto diff = otherElemAddr - otherPosAddr;
        const auto thisAddr = reinterpret_cast<std::uintptr_t>(this);

        return *reinterpret_cast<ElemT *>(thisAddr + diff);
    }

private:
    void _initVectorsFromPktProc();
    void _setSimpleFromOther(const VmPos& other);
    void _setFromOther(const VmPos& other);

public:
    // offset of current packet beginning within its element sequence (bits)
    Index curPktOffsetInElemSeqBits = 0;

    // head offset within current packet (bits)
    Index headOffsetInCurPktBits = 0;

    // current elements
    struct {
        PacketBeginningElement pktBeginning;
        PacketEndElement pktEnd;
        ScopeBeginningElement scopeBeginning;
        ScopeEndElement scopeEnd;
        PacketContentBeginningElement pktContentBeginning;
        PacketContentEndElement pktContentEnd;
        EventRecordBeginningElement erBeginning;
        EventRecordEndElement erEnd;
        PacketMagicNumberElement pktMagicNumber;
        MetadataStreamUuidElement metadataStreamUuid;
        DataStreamInfoElement dsInfo;
        PacketInfoElement pktInfo;
        EventRecordInfoElement erInfo;
        DefaultClockValueElement defClkVal;
        FixedLengthBitArrayElement flBitArray;
        FixedLengthBooleanElement flBool;
        FixedLengthSignedIntegerElement flSInt;
        FixedLengthUnsignedIntegerElement flUInt;
        FixedLengthFloatingPointNumberElement flFloat;
        VariableLengthSignedIntegerElement vlSInt;
        VariableLengthUnsignedIntegerElement vlUInt;
        NullTerminatedStringBeginningElement ntStrBeginning;
        NullTerminatedStringEndElement ntStrEnd;
        RawDataElement rawData;
        StaticLengthArrayBeginningElement slArrayBeginning;
        StaticLengthArrayEndElement slArrayEnd;
        DynamicLengthArrayBeginningElement dlArrayBeginning;
        DynamicLengthArrayEndElement dlArrayEnd;
        StaticLengthStringBeginningElement slStrBeginning;
        StaticLengthStringEndElement slStrEnd;
        DynamicLengthStringBeginningElement dlStrBeginning;
        DynamicLengthStringEndElement dlStrEnd;
        StaticLengthBlobBeginningElement slBlobBeginning;
        StaticLengthBlobEndElement slBlobEnd;
        DynamicLengthBlobBeginningElement dlBlobBeginning;
        DynamicLengthBlobEndElement dlBlobEnd;
        StructureBeginningElement structBeginning;
        StructureEndElement structEnd;
        VariantWithSignedIntegerSelectorBeginningElement varSIntSelBeginning;
        VariantWithSignedIntegerSelectorEndElement varSIntSelEnd;
        VariantWithUnsignedIntegerSelectorBeginningElement varUIntSelBeginning;
        VariantWithUnsignedIntegerSelectorEndElement varUIntSelEnd;
        OptionalWithBooleanSelectorBeginningElement optBoolSelBeginning;
        OptionalWithBooleanSelectorEndElement optBoolSelEnd;
        OptionalWithSignedIntegerSelectorBeginningElement optSIntSelBeginning;
        OptionalWithSignedIntegerSelectorEndElement optSIntSelEnd;
        OptionalWithUnsignedIntegerSelectorBeginningElement optUIntSelBeginning;
        OptionalWithUnsignedIntegerSelectorEndElement optUIntSelEnd;
    } elems;

    // next state to handle
    VmState theState = VmState::BEGIN_PKT;

    // next immediate state
    VmState nextState;

    // last fixed-length bit array byte order
    boost::optional<ByteOrder> lastFlBitArrayBo;

    // remaining padding bits to skip for alignment
    Size remBitsToSkip = 0;

    // last integer value
    union {
        std::uint64_t u;
        std::int64_t i;
    } lastIntVal;

    // current variable-length integer length (bits)
    Size curVlIntLenBits;

    // current variable-length integer element
    VariableLengthIntegerElement *curVlIntElem;

    /*
     * Code unit buffer for null-terminated strings.
     *
     * This makes it possible for _stateReadStrDataUntilNull() to find
     * the encoded U+0000 codepoint even if it spans multiple
     * data blocks.
     *
     * For example, assume `ntStrCuBuf.index` is 0 and what's left in
     * the current data block is
     *
     *     64 00 20 00 3c d8 3b df 00
     *
     * Also assume the encoding is UTF-16LE (code unit size is two).
     * Then there are five complete code units there, and half of one
     * (the last zero byte). Therefore, after reading that last zero
     * byte, `ntStrCuBuf.buf[0]` would be zero and `ntStrCuBuf.index`
     * one.
     *
     * Now assume the next data block starts with
     *
     *     00 1f fc cc bc 44 35 56
     *
     * _stateReadStrDataUntilNull() continues reading the current code
     * unit, making `ntStrCuBuf.buf[1]` zero and `ntStrCuBuf.index` two.
     * Since `ntStrCuBuf.index` is equal to the code unit size, the
     * method can check the current code unit value: two zeros, which
     * means U+0000, which means the end of that string.
     */
    struct {
        std::uint8_t buf[4];
        Index index = 0;
    } ntStrCuBuf;

    // current ID (event record or data stream type)
    TypeId curId;

    // packet procedure
    const PktProc *pktProc = nullptr;

    // current data stream type packet procedure
    const DsPktProc *curDsPktProc = nullptr;

    // current event record type procedure
    const ErProc *curErProc = nullptr;

    // metadata stream UUID
    boost::uuids::uuid metadataStreamUuid;

    // current packet expected total length (bits)
    Size curExpectedPktTotalLenBits;

    // current packet content length (bits)
    Size curExpectedPktContentLenBits;

    // stack
    std::vector<VmStackFrame> stack;

    // vector of saved values
    std::vector<std::uint64_t> savedVals;

    // default clock value, if any
    std::uint64_t defClkVal = 0;
};

class ItInfos final
{
public:
    void elemFromOther(const VmPos& myPos, const VmPos& otherPos, const Element& otherElem)
    {
        elem = &myPos.elemFromOther(otherPos, otherElem);
    }

    bool operator==(const ItInfos& other) const noexcept
    {
        return offset == other.offset && mark == other.mark;
    }

    bool operator!=(const ItInfos& other) const noexcept
    {
        return offset != other.offset || mark != other.mark;
    }

    bool operator<(const ItInfos& other) const noexcept
    {
        return offset < other.offset || (offset == other.offset && mark < other.mark);
    }

    bool operator<=(const ItInfos& other) const noexcept
    {
        return offset < other.offset || (offset == other.offset && mark <= other.mark);
    }

    bool operator>(const ItInfos& other) const noexcept
    {
        return offset > other.offset || (offset == other.offset && mark > other.mark);
    }

    bool operator>=(const ItInfos& other) const noexcept
    {
        return offset > other.offset || (offset == other.offset && mark >= other.mark);
    }

public:
    Index mark = 0;
    Index offset = 0;

    /*
     * Points to one of the elements in the `elems` field of the `VmPos`
     * in the same `ElementSequenceIteratorPosition`.
     */
    const Element *elem = nullptr;
};

class Vm final
{
public:
    explicit Vm(DataSourceFactory& dataSrcFactory, const PktProc& pktProc,
                ElementSequenceIterator& it);
    Vm(const Vm& vm, ElementSequenceIterator& it);
    void setFromOther(const Vm& vm, ElementSequenceIterator& it);
    void seekPkt(Index offset);
    void savePos(ElementSequenceIteratorPosition& pos) const;
    void restorePos(const ElementSequenceIteratorPosition& pos);

    const VmPos& pos() const
    {
        return _pos;
    }

    void nextElem()
    {
        while (!this->_handleState());
    }

    void updateItElemFromOtherPos(const VmPos& otherPos, const Element * const otherElem)
    {
        if (!otherElem) {
            _it->_curElem = nullptr;
        } else {
            const auto posElemAddr = reinterpret_cast<std::uintptr_t>(otherElem);
            const auto posAddr = reinterpret_cast<std::uintptr_t>(&otherPos);
            const auto diff = posElemAddr - posAddr;
            const auto myPosAddr = reinterpret_cast<std::uintptr_t>(&_pos);

            _it->_curElem = reinterpret_cast<const Element *>(myPosAddr + diff);
        }
    }

    void it(ElementSequenceIterator& it)
    {
        _it = &it;
    }

    ElementSequenceIterator& it()
    {
        return *_it;
    }

private:
    // instruction handler reaction
    enum class _ExecReaction {
        EXEC_NEXT_INSTR,
        FETCH_NEXT_INSTR_AND_STOP,
        CHANGE_STATE,
        EXEC_CUR_INSTR,
        STOP,
    };

private:
    template <Instr::Kind InstrKindV>
    void _initExecFunc(_ExecReaction (Vm::*)(const Instr&)) noexcept;

    void _initExecFuncs() noexcept;
    bool _newDataBlock(Index offsetInElemSeqBytes, Size sizeBytes);

    bool _handleState()
    {
        switch (_pos.state()) {
        case VmState::EXEC_INSTR:
            return this->_stateExecInstr();

        case VmState::EXEC_ARRAY_INSTR:
            return this->_stateExecArrayInstr();

        case VmState::BEGIN_ER:
            return this->_stateBeginEr();

        case VmState::END_ER:
            return this->_stateEndEr();

        case VmState::READ_RAW_DATA:
            return this->_stateReadRawData();

        case VmState::READ_UUID_BLOB_SECTION:
            return this->_stateReadUuidBlobSection();

        case VmState::CONTINUE_READ_VL_UINT:
            return this->_stateContinueReadVlInt<false>();

        case VmState::CONTINUE_READ_VL_SINT:
            return this->_stateContinueReadVlInt<true>();

        case VmState::READ_UTF_8_DATA_UNTIL_NULL:
            return this->_stateReadStrDataUntilNull<1>();

        case VmState::READ_UTF_16_DATA_UNTIL_NULL:
            return this->_stateReadStrDataUntilNull<2>();

        case VmState::READ_UTF_32_DATA_UNTIL_NULL:
            return this->_stateReadStrDataUntilNull<4>();

        case VmState::END_STR:
            return this->_stateEndStr();

        case VmState::CONTINUE_SKIP_PADDING_BITS:
            return this->_stateContinueSkipPaddingBits();

        case VmState::CONTINUE_SKIP_CONTENT_PADDING_BITS:
            return this->_stateContinueSkipPaddingBits();

        case VmState::READ_UUID_BYTE:
            return this->_stateReadUuidByte();

        case VmState::SET_METADATA_STREAM_UUID:
            return this->_stateSetMetadataStreamUuid();

        case VmState::BEGIN_PKT:
            return this->_stateBeginPkt();

        case VmState::BEGIN_PKT_CONTENT:
            return this->_stateBeginPktContent();

        case VmState::END_PKT_CONTENT:
            return this->_stateEndPktContent();

        case VmState::END_PKT:
            return this->_stateEndPkt();

        default:
            std::abort();
        }
    }

    bool _stateExecInstr()
    {
        while (true) {
            const auto reaction = this->_exec(_pos.nextInstr());

            switch (reaction) {
            case _ExecReaction::FETCH_NEXT_INSTR_AND_STOP:
                _pos.gotoNextInstr();
                return true;

            case _ExecReaction::STOP:
                return true;

            case _ExecReaction::EXEC_NEXT_INSTR:
                _pos.gotoNextInstr();
                break;

            case _ExecReaction::EXEC_CUR_INSTR:
                break;

            case _ExecReaction::CHANGE_STATE:
                // the handler changed the state: return `false` to continue
                return false;

            default:
                std::abort();
            }
        }

        return true;
    }

    bool _stateExecArrayInstr()
    {
        if (_pos.stackTop().rem == 0) {
            _pos.setParentStateAndStackPop();
            return false;
        }

        while (true) {
            auto& stackTop = _pos.stackTop();

            if (stackTop.it == stackTop.proc->end()) {
                assert(stackTop.rem > 0);
                --stackTop.rem;

                if (_pos.stackTop().rem == 0) {
                    _pos.setParentStateAndStackPop();
                    return false;
                }

                stackTop.it = stackTop.proc->begin();
                continue;
            }

            const auto reaction = this->_exec(_pos.nextInstr());

            switch (reaction) {
            case _ExecReaction::FETCH_NEXT_INSTR_AND_STOP:
                _pos.gotoNextInstr();
                return true;

            case _ExecReaction::STOP:
                return true;

            case _ExecReaction::EXEC_NEXT_INSTR:
                _pos.gotoNextInstr();
                break;

            case _ExecReaction::CHANGE_STATE:
                return false;

            default:
                std::abort();
            }
        }

        return true;
    }

    bool _stateContinueSkipPaddingBits()
    {
        this->_continueSkipPaddingBits(_pos.state() == VmState::CONTINUE_SKIP_CONTENT_PADDING_BITS);
        _pos.state(_pos.nextState);

        // not done: handle next state immediately
        return false;
    }

    bool _stateBeginPkt()
    {
        this->_resetItMark();
        _pos.resetForNewPkt();

        if (this->_remBitsInBuf() == 0) {
            /*
             * Try getting 1 bit to see if we're at the end of the
             * element sequence.
             */
            if (!this->_tryHaveBits(1)) {
                this->_setItEnd();
                return true;
            }
        }

        this->_updateItForUser(_pos.elems.pktBeginning);
        _pos.loadNewProc(_pos.pktProc->preambleProc());
        _pos.state(VmState::BEGIN_PKT_CONTENT);
        return true;
    }

    bool _stateBeginPktContent()
    {
        this->_updateItForUser(_pos.elems.pktContentBeginning);

        /*
         * The preamble procedure of the packet is already loaded at
         * this point.
         */
        _pos.state(VmState::EXEC_INSTR);
        return true;
    }

    bool _stateEndPktContent()
    {
        /*
         * Next time, skip the padding bits after the packet content
         * before setting the state to `END_PKT`.
         *
         * If we have no packet total length, then the element sequence
         * contains only one packet and there's no padding after the
         * packet content.
         */
        Size bitsToSkip = 0;

        if (_pos.curExpectedPktTotalLenBits != SIZE_UNSET) {
            bitsToSkip = _pos.curExpectedPktTotalLenBits - _pos.headOffsetInCurPktBits;
        }

        if (bitsToSkip > 0) {
            _pos.remBitsToSkip = bitsToSkip;
            _pos.nextState = VmState::END_PKT;
            _pos.state(VmState::CONTINUE_SKIP_PADDING_BITS);
        } else {
            // nothing to skip, go to end directly
            _pos.state(VmState::END_PKT);
        }

        this->_updateItForUser(_pos.elems.pktContentEnd);
        return true;
    }

    bool _stateEndPkt()
    {
        const auto offset = _pos.headOffsetInElemSeqBits();

        // adjust buffer address and offsets
        _pos.curPktOffsetInElemSeqBits = _pos.headOffsetInElemSeqBits();
        _pos.headOffsetInCurPktBits = 0;
        assert((_pos.curPktOffsetInElemSeqBits & 7) == 0);

        if (_pos.curExpectedPktTotalLenBits == SIZE_UNSET) {
            // element sequence contains a single packet
            this->_resetBuffer();
        } else {
            const auto oldBufAddr = _bufAddr;

            _bufAddr -= (_bufOffsetInCurPktBits / 8);
            _bufAddr += (_pos.curExpectedPktTotalLenBits / 8);
            _bufOffsetInCurPktBits = 0;
            _bufLenBits -= (_bufAddr - oldBufAddr) * 8;
        }

        this->_updateItForUser(_pos.elems.pktEnd, offset);
        _pos.state(VmState::BEGIN_PKT);
        return true;
    }

    bool _stateBeginEr()
    {
        assert(_pos.curDsPktProc);

        if (_pos.curExpectedPktContentLenBits == SIZE_UNSET) {
            if (this->_remBitsInBuf() == 0) {
                /*
                 * Try getting 1 bit to see if we're at the end of the
                 * packet.
                 */
                if (!this->_tryHaveBits(1)) {
                    _pos.state(VmState::END_PKT_CONTENT);
                    return false;
                }
            }
        } else {
            if (_pos.remContentBitsInPkt() == 0) {
                _pos.state(VmState::END_PKT_CONTENT);
                return false;
            }
        }

        /*
         * Align now so that the offset of the iterator is _after_ any
         * padding.
         */
        this->_alignHead(_pos.curDsPktProc->erAlign());

        this->_updateItForUser(_pos.elems.erBeginning);
        _pos.loadNewProc(_pos.curDsPktProc->erPreambleProc());
        _pos.state(VmState::EXEC_INSTR);
        return true;
    }

    bool _stateEndEr()
    {
        assert(_pos.curErProc);
        _pos.curErProc = nullptr;
        this->_updateItForUser(_pos.elems.erEnd);
        _pos.state(VmState::BEGIN_ER);
        return true;
    }

    bool _stateReadUuidByte()
    {
        if (_pos.stackTop().rem == 0) {
            // set completed UUID
            _pos.state(VmState::SET_METADATA_STREAM_UUID);
            return false;
        }

        auto& instr = **_pos.stackTop().it;

        this->_execReadStdFlInt<std::uint64_t, 8, readFlUInt8, false>(instr);
        _pos.metadataStreamUuid.data[16 - _pos.stackTop().rem] = static_cast<std::uint8_t>(_pos.lastIntVal.u);
        --_pos.stackTop().rem;
        return true;
    }

    bool _stateSetMetadataStreamUuid()
    {
        _pos.elems.metadataStreamUuid._uuid = _pos.metadataStreamUuid;
        this->_updateItForUser(_pos.elems.metadataStreamUuid);
        _pos.setParentStateAndStackPop();
        return true;
    }

    bool _stateReadBytes()
    {
        assert((_pos.headOffsetInCurPktBits & 7) == 0);

        if (_pos.stackTop().rem == 0) {
            return false;
        }

        // require at least one byte
        this->_requireContentBits(8);

        const auto buf = this->_bufAtHead();
        const auto bufSizeBytes = this->_remBitsInBuf() / 8;
        const auto sectionSizeBytes = std::min(bufSizeBytes, _pos.stackTop().rem);
        const auto sectionLenBits = sectionSizeBytes * 8;

        if (sectionLenBits > _pos.remContentBitsInPkt()) {
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.headOffsetInElemSeqBits(),
                sectionLenBits, _pos.remContentBitsInPkt()
            };
        }

        _pos.elems.rawData._begin = buf;
        _pos.elems.rawData._end = buf + sectionSizeBytes;
        assert(_pos.elems.rawData.size() > 0);
        this->_updateItForUser(_pos.elems.rawData);
        this->_consumeExistingBits(sectionSizeBytes * 8);
        _pos.stackTop().rem -= sectionSizeBytes;
        return true;
    }

    bool _stateReadRawData()
    {
        const auto cont = this->_stateReadBytes();

        if (!cont) {
            _pos.setParentStateAndStackPop();
        }

        return cont;
    }

    bool _stateReadUuidBlobSection()
    {
        if (this->_stateReadBytes()) {
            // new UUID bytes
            const auto blobSize = _pos.elems.rawData.size();
            const auto startIndex = 16 - _pos.stackTop().rem - blobSize;

            for (auto index = startIndex; index < startIndex + blobSize; ++index) {
                _pos.metadataStreamUuid.data[index] = static_cast<std::uint8_t>(_pos.elems.rawData.begin()[index]);
            }

            return true;
        } else {
            // done
            _pos.state(VmState::SET_METADATA_STREAM_UUID);
            return false;
        }
    }

    void _signExtendVlSIntVal() noexcept
    {
        assert(_pos.curVlIntLenBits <= 64);

        if (_pos.curVlIntLenBits == 64) {
            return;
        }

        const auto mask = static_cast<std::uint64_t>(1) << (_pos.curVlIntLenBits - 1);

        _pos.lastIntVal.u = _pos.lastIntVal.u & ((static_cast<std::uint64_t>(1) << _pos.curVlIntLenBits) - 1);
        _pos.lastIntVal.u = (_pos.lastIntVal.u ^ mask) - mask;
    }

    template <bool IsSignedV>
    void _appendVlIntByte(const std::uint8_t byte)
    {
        auto newVlIntLenBits = _pos.curVlIntLenBits + 7;
        const auto byteVal = byte & 0b0111'1111;

        // validate future variable-length integer length
        if (newVlIntLenBits > 63) {
            /*
             * Exception for some 10th byte which can contain the last
             * bit of a 64-bit integer (as 9 × 7 is 63).
             *
             * The condition to accept it is:
             *
             * * It's the last byte of the variable-length integer.
             *
             * * If `IsSignedV` is false:
             *       Its 7-bit value (`byteVal`) must be 1.
             *
             *   If `IsSignedV` is true:
             *       Its 7-bit value must be 0 (positive) or 127
             *       (negative).
             */
            if ((byte & 0b1000'0000) != 0) {
                // not the last byte
                throw OversizedVariableLengthIntegerDecodingError {_pos.headOffsetInElemSeqBits()};
            }

            if (IsSignedV && byteVal != 0 && byteVal != 0b0111'1111) {
                throw OversizedVariableLengthIntegerDecodingError {_pos.headOffsetInElemSeqBits()};
            } else if (!IsSignedV && byteVal != 1) {
                throw OversizedVariableLengthIntegerDecodingError {_pos.headOffsetInElemSeqBits()};
            }

            newVlIntLenBits = 64;
        }

        // mark this byte as consumed immediately
        this->_consumeExistingBits(8);

        // update unsigned integer value, clearing continuation bit
        _pos.lastIntVal.u |= (static_cast<std::uint64_t>(byteVal) << _pos.curVlIntLenBits);

        // update current variable-length integer length
        _pos.curVlIntLenBits = newVlIntLenBits;
    }

    template <bool IsSignedV>
    bool _stateContinueReadVlInt()
    {
        /*
         * Read a single byte, and then:
         *
         * If the variable-length integer is not ended:
         *     Keep this state.
         *
         * Otherwise:
         *     Set the variable-length integer element and set the state
         *     to the previous value.
         *
         * See <https://en.wikipedia.org/wiki/LEB128>.
         */
        assert((_pos.headOffsetInCurPktBits & 7) == 0);

        // require at least one byte
        this->_requireContentBits(8);

        // read current byte
        const auto byte = *this->_bufAtHead();

        if ((byte & 0b1000'0000) == 0) {
            // this is the last byte
            this->_appendVlIntByte<IsSignedV>(byte);

            /*
             * When calling _setBitArrayElemBase() below,
             * `**_pos.stackTop().it` is the current
             * `ReadVlIntInstr` instruction.
             */
            auto& instr = **_pos.stackTop().it;

            assert(_pos.curVlIntElem);
            _pos.curVlIntElem->_len = _pos.curVlIntLenBits;

            /*
             * `_pos.headOffsetInElemSeqBits()` now returns the offset
             * at the _end_ of the VL integer; the iterator user expects
             * its beginning offset.
             */
            const auto offset = _pos.headOffsetInElemSeqBits() - _pos.curVlIntElem->dataLength();

            if (IsSignedV) {
                this->_signExtendVlSIntVal();
                this->_setBitArrayElemBase(_pos.lastIntVal.i, instr, *_pos.curVlIntElem, offset);
            } else {
                this->_setBitArrayElemBase(_pos.lastIntVal.u, instr, *_pos.curVlIntElem, offset);
            }

            // we're done with this instruction and this state
            _pos.gotoNextInstr();
            _pos.state(_pos.nextState);
            assert(_pos.state() == VmState::EXEC_INSTR ||
                   _pos.state() == VmState::EXEC_ARRAY_INSTR);
            return true;
        }

        // not the last byte
        this->_appendVlIntByte<IsSignedV>(byte);
        return false;
    }

    template <Size CuLenV>
    bool _stateReadStrDataUntilNull()
    {
        assert((_pos.headOffsetInCurPktBits & 7) == 0);

        // require at least one byte
        this->_requireContentBits(8);

        const auto begin = this->_bufAtHead();
        const auto bufSizeBytes = this->_remBitsInBuf() / 8;

        assert(bufSizeBytes >= 1);

        auto end = begin + bufSizeBytes;
        auto gotNull = false;

        // try to find a complete or partial encoded U+0000 codepoint
        for (Index i = 0; i < bufSizeBytes; ++i) {
            _pos.ntStrCuBuf.buf[_pos.ntStrCuBuf.index] = begin[i];
            ++_pos.ntStrCuBuf.index;

            if (_pos.ntStrCuBuf.index == CuLenV) {
                // end of code unit: is it U+0000?
                if (std::all_of(_pos.ntStrCuBuf.buf,
                                _pos.ntStrCuBuf.buf + CuLenV,
                                [](const auto b) {
                                    return b == 0;
                                })) {
                    // this is the real end
                    gotNull = true;
                    end = begin + i + 1;
                    break;
                } else {
                    _pos.ntStrCuBuf.index = 0;
                }
            }
        }

        const Size rawDataLenBits = (end - begin) * 8;

        if (rawDataLenBits > _pos.remContentBitsInPkt()) {
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.headOffsetInElemSeqBits(),
                rawDataLenBits, _pos.remContentBitsInPkt()
            };
        }

        _pos.elems.rawData._begin = begin;
        _pos.elems.rawData._end = end;

        if (gotNull) {
            // we're done
            _pos.state(VmState::END_STR);
        }

        assert(_pos.elems.rawData.size() > 0);
        this->_updateItForUser(_pos.elems.rawData);
        this->_consumeExistingBits(_pos.elems.rawData.size() * 8);
        return true;
    }

    bool _stateEndStr()
    {
        /*
         * NOTE: _setDataElemFromInstr() was already called from
         * _execReadNtStr() for `_pos.elems.ntStrEnd`.
         */
        this->_updateItForUser(_pos.elems.ntStrEnd);
        _pos.state(_pos.nextState);
        assert(_pos.state() == VmState::EXEC_INSTR || _pos.state() == VmState::EXEC_ARRAY_INSTR);
        return true;
    }

    _ExecReaction _exec(const Instr& instr)
    {
        return (this->*_execFuncs[static_cast<Index>(instr.kind())])(instr);
    }

    void _updateItForUser(const Element& elem, const Index offset) noexcept
    {
        _it->_curElem = &elem;
        _it->_offset = offset;
        ++_it->_mark;
    }

    void _updateItForUser(const Element& elem) noexcept
    {
        this->_updateItForUser(elem, _pos.headOffsetInElemSeqBits());
    }

    void _setItEnd() const noexcept
    {
        _it->_mark = 0;
        _it->_offset = ElementSequenceIterator::_END_OFFSET;
    }

    void _resetItMark() const noexcept
    {
        _it->_mark = 0;
    }

    void _alignHead(const Size align)
    {
        const auto newHeadOffsetBits = (_pos.headOffsetInCurPktBits + align - 1) & -align;
        const auto bitsToSkip = newHeadOffsetBits - _pos.headOffsetInCurPktBits;

        if (bitsToSkip == 0) {
            // already aligned! yay!
            return;
        }

        if (bitsToSkip > _pos.remContentBitsInPkt()) {
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.headOffsetInElemSeqBits(),
                bitsToSkip, _pos.remContentBitsInPkt()
            };
        }

        _pos.remBitsToSkip = bitsToSkip;
        _pos.nextState = _pos.state();
        _pos.state(VmState::CONTINUE_SKIP_CONTENT_PADDING_BITS);
        this->_continueSkipPaddingBits(true);
    }

    void _alignHead(const Instr& instr)
    {
        this->_alignHead(static_cast<const ReadDataInstr&>(instr).align());
    }

    void _continueSkipPaddingBits(const bool contentBits)
    {
        while (_pos.remBitsToSkip > 0) {
            if (contentBits) {
                this->_requireContentBits(1);
            } else {
                this->_requireBits(1);
            }

            const auto bitsToSkip = std::min(_pos.remBitsToSkip, this->_remBitsInBuf());

            _pos.remBitsToSkip -= bitsToSkip;
            this->_consumeExistingBits(bitsToSkip);
        }

        // we're done now!
        _pos.state(_pos.nextState);
    }

    bool _tryHaveBits(const Size bits)
    {
        assert(bits <= 64);

        if (bits <= this->_remBitsInBuf()) {
            // we still have enough
            return true;
        }

        /*
         * Align the current head to its current byte and compute the
         * offset, from the beginning of the element sequence, to
         * request in bytes at this point.
         */
        const auto flooredHeadOffsetInCurPacketBits = _pos.headOffsetInCurPktBits & ~7ULL;
        const auto flooredHeadOffsetInCurPacketBytes = flooredHeadOffsetInCurPacketBits / 8;
        const auto curPacketOffsetInElemSeqBytes = _pos.curPktOffsetInElemSeqBits / 8;
        const auto requestOffsetInElemSeqBytes = curPacketOffsetInElemSeqBytes +
                                                 flooredHeadOffsetInCurPacketBytes;
        const auto bitInByte = _pos.headOffsetInCurPktBits & 7;
        const auto sizeBytes = (bits + 7 + bitInByte) / 8;

        return this->_newDataBlock(requestOffsetInElemSeqBytes, sizeBytes);
    }

    void _requireBits(const Size bits)
    {
        if (!this->_tryHaveBits(bits)) {
            throw PrematureEndOfDataDecodingError {
                _pos.headOffsetInElemSeqBits(), bits
            };
        }
    }

    void _requireContentBits(const Size bits)
    {
        if (bits > _pos.remContentBitsInPkt()) {
            // going past the packet content
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.headOffsetInElemSeqBits(),
                bits, _pos.remContentBitsInPkt()
            };
        }

        this->_requireBits(bits);
    }

    const std::uint8_t *_bufAtHead() const noexcept
    {
        const auto offsetBytes = (_pos.headOffsetInCurPktBits - _bufOffsetInCurPktBits) / 8;

        return &_bufAddr[offsetBytes];
    }

    Size _remBitsInBuf() const noexcept
    {
        return (_bufOffsetInCurPktBits + _bufLenBits) - _pos.headOffsetInCurPktBits;
    }

    void _consumeExistingBits(const Size bitsToConsume) noexcept
    {
        assert(bitsToConsume <= this->_remBitsInBuf());
        _pos.headOffsetInCurPktBits += bitsToConsume;
    }

    void _resetBuffer() noexcept
    {
        _bufAddr = nullptr;
        _bufLenBits = 0;
        _bufOffsetInCurPktBits = _pos.headOffsetInCurPktBits;
    }

    // instruction handlers
    _ExecReaction _execBeginReadDlArray(const Instr& instr);
    _ExecReaction _execBeginReadDlBlob(const Instr& instr);
    _ExecReaction _execBeginReadDlStr(const Instr& instr);
    _ExecReaction _execBeginReadOptBoolSel(const Instr& instr);
    _ExecReaction _execBeginReadOptSIntSel(const Instr& instr);
    _ExecReaction _execBeginReadOptUIntSel(const Instr& instr);
    _ExecReaction _execBeginReadScope(const Instr& instr);
    _ExecReaction _execBeginReadSlArray(const Instr& instr);
    _ExecReaction _execBeginReadSlBlob(const Instr& instr);
    _ExecReaction _execBeginReadSlStr(const Instr& instr);
    _ExecReaction _execBeginReadSlUuidArray(const Instr& instr);
    _ExecReaction _execBeginReadSlUuidBlob(const Instr& instr);
    _ExecReaction _execBeginReadStruct(const Instr& instr);
    _ExecReaction _execBeginReadVarSIntSel(const Instr& instr);
    _ExecReaction _execBeginReadVarUIntSel(const Instr& instr);
    _ExecReaction _execEndDsErPreambleProc(const Instr& instr);
    _ExecReaction _execEndDsPktPreambleProc(const Instr& instr);
    _ExecReaction _execEndErProc(const Instr& instr);
    _ExecReaction _execEndPktPreambleProc(const Instr& instr);
    _ExecReaction _execEndReadDlArray(const Instr& instr);
    _ExecReaction _execEndReadDlBlob(const Instr& instr);
    _ExecReaction _execEndReadDlStr(const Instr& instr);
    _ExecReaction _execEndReadOptBoolSel(const Instr& instr);
    _ExecReaction _execEndReadOptSIntSel(const Instr& instr);
    _ExecReaction _execEndReadOptUIntSel(const Instr& instr);
    _ExecReaction _execEndReadScope(const Instr& instr);
    _ExecReaction _execEndReadSlArray(const Instr& instr);
    _ExecReaction _execEndReadSlBlob(const Instr& instr);
    _ExecReaction _execEndReadSlStr(const Instr& instr);
    _ExecReaction _execEndReadStruct(const Instr& instr);
    _ExecReaction _execEndReadVarSIntSel(const Instr& instr);
    _ExecReaction _execEndReadVarUIntSel(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA16Be(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA16BeRev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA16Le(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA16LeRev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA32Be(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA32BeRev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA32Le(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA32LeRev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA64Be(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA64BeRev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA64Le(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA64LeRev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA8(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA8Rev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayBe(const Instr& instr);
    _ExecReaction _execReadFlBitArrayBeRev(const Instr& instr);
    _ExecReaction _execReadFlBitArrayLe(const Instr& instr);
    _ExecReaction _execReadFlBitArrayLeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolA16Be(const Instr& instr);
    _ExecReaction _execReadFlBoolA16BeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolA16Le(const Instr& instr);
    _ExecReaction _execReadFlBoolA16LeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolA32Be(const Instr& instr);
    _ExecReaction _execReadFlBoolA32BeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolA32Le(const Instr& instr);
    _ExecReaction _execReadFlBoolA32LeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolA64Be(const Instr& instr);
    _ExecReaction _execReadFlBoolA64BeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolA64Le(const Instr& instr);
    _ExecReaction _execReadFlBoolA64LeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolA8(const Instr& instr);
    _ExecReaction _execReadFlBoolA8Rev(const Instr& instr);
    _ExecReaction _execReadFlBoolBe(const Instr& instr);
    _ExecReaction _execReadFlBoolBeRev(const Instr& instr);
    _ExecReaction _execReadFlBoolLe(const Instr& instr);
    _ExecReaction _execReadFlBoolLeRev(const Instr& instr);
    _ExecReaction _execReadFlFloat32Be(const Instr& instr);
    _ExecReaction _execReadFlFloat32BeRev(const Instr& instr);
    _ExecReaction _execReadFlFloat32Le(const Instr& instr);
    _ExecReaction _execReadFlFloat32LeRev(const Instr& instr);
    _ExecReaction _execReadFlFloat64Be(const Instr& instr);
    _ExecReaction _execReadFlFloat64BeRev(const Instr& instr);
    _ExecReaction _execReadFlFloat64Le(const Instr& instr);
    _ExecReaction _execReadFlFloat64LeRev(const Instr& instr);
    _ExecReaction _execReadFlFloatA32Be(const Instr& instr);
    _ExecReaction _execReadFlFloatA32BeRev(const Instr& instr);
    _ExecReaction _execReadFlFloatA32Le(const Instr& instr);
    _ExecReaction _execReadFlFloatA32LeRev(const Instr& instr);
    _ExecReaction _execReadFlFloatA64Be(const Instr& instr);
    _ExecReaction _execReadFlFloatA64BeRev(const Instr& instr);
    _ExecReaction _execReadFlFloatA64Le(const Instr& instr);
    _ExecReaction _execReadFlFloatA64LeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntA16Be(const Instr& instr);
    _ExecReaction _execReadFlSIntA16BeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntA16Le(const Instr& instr);
    _ExecReaction _execReadFlSIntA16LeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntA32Be(const Instr& instr);
    _ExecReaction _execReadFlSIntA32BeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntA32Le(const Instr& instr);
    _ExecReaction _execReadFlSIntA32LeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntA64Be(const Instr& instr);
    _ExecReaction _execReadFlSIntA64BeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntA64Le(const Instr& instr);
    _ExecReaction _execReadFlSIntA64LeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntA8(const Instr& instr);
    _ExecReaction _execReadFlSIntA8Rev(const Instr& instr);
    _ExecReaction _execReadFlSIntBe(const Instr& instr);
    _ExecReaction _execReadFlSIntBeRev(const Instr& instr);
    _ExecReaction _execReadFlSIntLe(const Instr& instr);
    _ExecReaction _execReadFlSIntLeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntA16Be(const Instr& instr);
    _ExecReaction _execReadFlUIntA16BeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntA16Le(const Instr& instr);
    _ExecReaction _execReadFlUIntA16LeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntA32Be(const Instr& instr);
    _ExecReaction _execReadFlUIntA32BeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntA32Le(const Instr& instr);
    _ExecReaction _execReadFlUIntA32LeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntA64Be(const Instr& instr);
    _ExecReaction _execReadFlUIntA64BeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntA64Le(const Instr& instr);
    _ExecReaction _execReadFlUIntA64LeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntA8(const Instr& instr);
    _ExecReaction _execReadFlUIntA8Rev(const Instr& instr);
    _ExecReaction _execReadFlUIntBe(const Instr& instr);
    _ExecReaction _execReadFlUIntBeRev(const Instr& instr);
    _ExecReaction _execReadFlUIntLe(const Instr& instr);
    _ExecReaction _execReadFlUIntLeRev(const Instr& instr);
    _ExecReaction _execReadNtStrUtf16(const Instr& instr);
    _ExecReaction _execReadNtStrUtf32(const Instr& instr);
    _ExecReaction _execReadNtStrUtf8(const Instr& instr);
    _ExecReaction _execReadVlSInt(const Instr& instr);
    _ExecReaction _execReadVlUInt(const Instr& instr);
    _ExecReaction _execSaveVal(const Instr& instr);
    _ExecReaction _execSetCurrentId(const Instr& instr);
    _ExecReaction _execSetDsId(const Instr& instr);
    _ExecReaction _execSetDsInfo(const Instr& instr);
    _ExecReaction _execSetDst(const Instr& instr);
    _ExecReaction _execSetErInfo(const Instr& instr);
    _ExecReaction _execSetErt(const Instr& instr);
    _ExecReaction _execSetPktContentLen(const Instr& instr);
    _ExecReaction _execSetPktDiscErCounterSnap(const Instr& instr);
    _ExecReaction _execSetPktEndDefClkVal(const Instr& instr);
    _ExecReaction _execSetPktInfo(const Instr& instr);
    _ExecReaction _execSetPktMagicNumber(const Instr& instr);
    _ExecReaction _execSetPktSeqNum(const Instr& instr);
    _ExecReaction _execSetPktTotalLen(const Instr& instr);
    _ExecReaction _execUpdateDefClkVal(const Instr& instr);
    _ExecReaction _execUpdateDefClkValFl(const Instr& instr);

    _ExecReaction _execReadNtStrCommon(const Instr& instr, const VmState state);

    template <typename ElemT>
    static void _setDataElemFromInstr(ElemT& elem, const Instr& instr) noexcept
    {
        assert(instr.isBeginReadData() || instr.isEndReadData());

        auto& readDataInstr = static_cast<const ReadDataInstr&>(instr);

        elem._dt = &readDataInstr.dt();
        elem._structMemberType = readDataInstr.memberType();
    }

    void _setLastIntVal(const std::int64_t val) noexcept
    {
        _pos.lastIntVal.i = val;
    }

    void _setLastIntVal(const std::uint64_t val) noexcept
    {
        _pos.lastIntVal.u = val;
    }

    template <typename ValT, typename ElemT>
    void _setBitArrayElemBase(const ValT val, const Instr& instr, ElemT& elem, const Index offset) noexcept
    {
        Vm::_setDataElemFromInstr(elem, instr);
        this->_setLastIntVal(val);
        elem._val(val);
        this->_updateItForUser(elem, offset);
    }

    template <typename ValT, typename ElemT>
    void _setBitArrayElemBase(const ValT val, const Instr& instr, ElemT& elem) noexcept
    {
        this->_setBitArrayElemBase(val, instr, elem, _pos.headOffsetInElemSeqBits());
    }

    void _setFlIntElem(const std::uint64_t val, const Instr& instr) noexcept
    {
        this->_setBitArrayElemBase(val, instr, _pos.elems.flUInt);
    }

    void _setFlIntElem(const std::int64_t val, const Instr& instr) noexcept
    {
        this->_setBitArrayElemBase(val, instr, _pos.elems.flSInt);
    }

    void _setFlFloatVal(const double val, const ReadDataInstr& instr) noexcept
    {
        Vm::_setDataElemFromInstr(_pos.elems.flFloat, instr);
        _pos.elems.flFloat._val(val);
        this->_updateItForUser(_pos.elems.flFloat);
    }

    void _execReadFlBitArrayPreamble(const Instr& instr, const Size len)
    {
        auto& readFlBitArrayInstr = static_cast<const ReadFlBitArrayInstr&>(instr);

        this->_alignHead(readFlBitArrayInstr);
        this->_requireContentBits(len);
    }

    template <typename RetT, Size LenBitsV, RetT (*FuncV)(const std::uint8_t *), bool RevV>
    RetT _readStdFlInt(const Instr& instr)
    {
        auto& readFlBitArrayInstr = static_cast<const ReadFlBitArrayInstr&>(instr);

        this->_execReadFlBitArrayPreamble(instr, LenBitsV);
        _pos.lastFlBitArrayBo = readFlBitArrayInstr.bo();

        auto ret = FuncV(this->_bufAtHead());

        if (RevV) {
            ret = revFlIntBits(ret, LenBitsV);
        }

        return ret;
    }

    template <Size LenBitsV, std::uint64_t (*FuncV)(const std::uint8_t *), bool RevV>
    void _execReadStdFlBitArray(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<std::uint64_t, LenBitsV, FuncV, RevV>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBitArray);
        this->_consumeExistingBits(LenBitsV);
    }

    template <Size LenBitsV, std::uint64_t (*FuncV)(const std::uint8_t *), bool RevV>
    void _execReadStdFlBool(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<std::uint64_t, LenBitsV, FuncV, RevV>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBool);
        this->_consumeExistingBits(LenBitsV);
    }

    template <typename RetT, Size LenBitsV, RetT (*FuncV)(const std::uint8_t *), bool RevV>
    void _execReadStdFlInt(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<RetT, LenBitsV, FuncV, RevV>(instr);

        this->_setFlIntElem(val, instr);
        this->_consumeExistingBits(LenBitsV);
    }

    template <typename RetT, RetT (*FuncsV[])(const std::uint8_t *), bool RevV>
    RetT _readFlInt(const Instr& instr)
    {
        auto& readFlBitArrayInstr = static_cast<const ReadFlBitArrayInstr&>(instr);

        this->_execReadFlBitArrayPreamble(instr, readFlBitArrayInstr.len());

        if (static_cast<bool>(_pos.lastFlBitArrayBo)) {
            if ((_pos.headOffsetInCurPktBits & 7) != 0) {
                /*
                 * A fixed-length bit array which does not start on a
                 * byte boundary must have the same byte order as the
                 * previous fixed-length bit array.
                 */
                if (readFlBitArrayInstr.bo() != *_pos.lastFlBitArrayBo) {
                    throw ByteOrderChangeWithinByteDecodingError {
                        _pos.headOffsetInElemSeqBits(),
                        *_pos.lastFlBitArrayBo,
                        readFlBitArrayInstr.bo()
                    };
                }
            }
        }

        _pos.lastFlBitArrayBo = readFlBitArrayInstr.bo();

        const auto index = (readFlBitArrayInstr.len() - 1) * 8 + (_pos.headOffsetInCurPktBits & 7);
        auto ret = FuncsV[index](this->_bufAtHead());

        if (RevV) {
            ret = revFlIntBits(ret, readFlBitArrayInstr.len());
        }

        return ret;
    }

    template <std::uint64_t (*FuncsV[])(const std::uint8_t *), bool RevV>
    void _execReadFlBitArray(const Instr& instr)
    {
        const auto val = this->_readFlInt<std::uint64_t, FuncsV, RevV>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBitArray);
        this->_consumeExistingBits(static_cast<const ReadFlBitArrayInstr&>(instr).len());
    }

    template <std::uint64_t (*FuncsV[])(const std::uint8_t *), bool RevV>
    void _execReadFlBool(const Instr& instr)
    {
        const auto val = this->_readFlInt<std::uint64_t, FuncsV, RevV>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBool);
        this->_consumeExistingBits(static_cast<const ReadFlBoolInstr&>(instr).len());
    }

    template <typename RetT, RetT (*FuncsV[])(const std::uint8_t *), bool RevV>
    void _execReadFlInt(const Instr& instr)
    {
        const auto val = this->_readFlInt<RetT, FuncsV, RevV>(instr);

        this->_setFlIntElem(val, instr);
        this->_consumeExistingBits(static_cast<const ReadFlBitArrayInstr&>(instr).len());
    }

    template <typename FloatT>
    void _execReadFlFloatPost(const std::uint64_t val, const Instr& instr) noexcept
    {
        // is there a better way to do this?
        using UIntT = std::conditional_t<sizeof(FloatT) == sizeof(std::uint32_t),
                                         std::uint32_t, std::uint64_t>;

        static_assert(sizeof(FloatT) == sizeof(UIntT),
                      "Floating point number and integer sizes match in union.");
        static_assert(std::alignment_of<FloatT>::value == std::alignment_of<UIntT>::value,
                      "Floating point number and integer alignments match in union.");

        union {
            FloatT flFloat;
            UIntT flUInt;
        } u;

        u.flUInt = static_cast<UIntT>(val);
        this->_setFlFloatVal(u.flFloat, static_cast<const ReadDataInstr&>(instr));
        this->_consumeExistingBits(sizeof(FloatT) * 8);
    }

    template <typename FloatT, std::uint64_t (*FuncsV[])(const std::uint8_t *), bool RevV>
    void _execReadFlFloat(const Instr& instr)
    {
        const auto val = this->_readFlInt<std::uint64_t, FuncsV, RevV>(instr);

        this->_execReadFlFloatPost<FloatT>(val, instr);
    }

    template <typename FloatT, std::uint64_t (*FuncV)(const std::uint8_t *), bool RevV>
    void _execReadStdFlFloat(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<std::uint64_t, sizeof(FloatT) * 8, FuncV, RevV>(instr);

        this->_execReadFlFloatPost<FloatT>(val, instr);
    }

    _ExecReaction _execReadVlIntCommon(const Instr& instr, VariableLengthIntegerElement& elem,
                                       const VmState nextState)
    {
        this->_alignHead(instr);
        _pos.curVlIntElem = &elem;
        _pos.curVlIntLenBits = 0;
        _pos.lastIntVal.u = 0;
        _pos.nextState = _pos.state();
        _pos.state(nextState);
        return _ExecReaction::CHANGE_STATE;
    }

    template <typename ReadVarInstrT, typename ElemT>
    void _execBeginReadVar(const Instr& instr, ElemT& elem)
    {
        this->_alignHead(instr);

        const auto& beginReadVarInstr = static_cast<const ReadVarInstrT&>(instr);
        const auto uSelVal = _pos.savedVal(beginReadVarInstr.selPos());
        const auto selVal = static_cast<typename ReadVarInstrT::Opt::Val>(uSelVal);
        const auto proc = beginReadVarInstr.procForSelVal(selVal);

        if (!proc) {
            if (std::is_signed<typename ReadVarInstrT::Opt::Val>::value) {
                throw InvalidVariantSignedIntegerSelectorValueDecodingError {
                    _pos.headOffsetInElemSeqBits(),
                    static_cast<std::int64_t>(selVal)
                };
            } else {
                throw InvalidVariantUnsignedIntegerSelectorValueDecodingError {
                    _pos.headOffsetInElemSeqBits(),
                    static_cast<std::uint64_t>(selVal)
                };
            }
        }

        Vm::_setDataElemFromInstr(elem, instr);
        elem._selVal = selVal;
        this->_updateItForUser(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(proc);
        _pos.state(VmState::EXEC_INSTR);
    }

    static bool isEndReadOpt(const Instr& instr) noexcept
    {
        return instr.kind() == Instr::Kind::END_READ_OPT_BOOL_SEL ||
               instr.kind() == Instr::Kind::END_READ_OPT_UINT_SEL ||
               instr.kind() == Instr::Kind::END_READ_OPT_SINT_SEL;
    }

    template <typename ReadOptInstrT, typename SelValT, typename ElemT>
    SelValT _execBeginReadOpt(const Instr& instr, ElemT& elem)
    {
        this->_alignHead(instr);

        const auto& beginReadOptInstr = static_cast<const ReadOptInstrT&>(instr);
        const auto selVal = static_cast<SelValT>(_pos.savedVal(beginReadOptInstr.selPos()));
        const auto isEnabled = beginReadOptInstr.isEnabled(selVal);

        Vm::_setDataElemFromInstr(elem, instr);
        this->_updateItForUser(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(&beginReadOptInstr.proc());

        if (isEnabled) {
            elem._isEnabled = true;
        } else {
            elem._isEnabled = false;

            /*
             * Disabled: go directly to the last instruction of the
             * loaded subprocedure, which has the kind
             * `Instr::Kind::END_READ_OPT`.
             */
            assert(!_pos.stackTop().proc->empty());
            _pos.stackTop().it = _pos.stackTop().proc->end() - 1;
            assert(isEndReadOpt(_pos.nextInstr()));
        }

        _pos.state(VmState::EXEC_INSTR);
        return selVal;
    }

    template <typename ElemT>
    void _execBeginReadStaticData(const ReadDataInstr& instr, ElemT& elem, const Size len,
                                  const Proc * const proc, const VmState nextState)
    {
        this->_alignHead(instr);
        Vm::_setDataElemFromInstr(elem, instr);
        this->_updateItForUser(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(proc);
        _pos.stackTop().rem = len;
        _pos.state(nextState);
    }

    _ExecReaction _execBeginReadSlArray(const Instr& instr, const VmState nextState)
    {
        const auto& beginReadStaticArrayInstr = static_cast<const BeginReadSlArrayInstr&>(instr);

        _pos.elems.slArrayBeginning._len = beginReadStaticArrayInstr.len();
        this->_execBeginReadStaticData(beginReadStaticArrayInstr, _pos.elems.slArrayBeginning,
                                       beginReadStaticArrayInstr.len(),
                                       &beginReadStaticArrayInstr.proc(), nextState);
        return _ExecReaction::STOP;
    }

    _ExecReaction _execBeginReadSlBlob(const Instr& instr, const VmState nextState)
    {
        const auto& beginReadSlBlobInstr = static_cast<const BeginReadSlBlobInstr&>(instr);

        _pos.elems.slBlobBeginning._len = beginReadSlBlobInstr.len();
        this->_execBeginReadStaticData(beginReadSlBlobInstr, _pos.elems.slBlobBeginning,
                                       beginReadSlBlobInstr.len(), nullptr, nextState);
        return _ExecReaction::STOP;
    }

    template <typename ElemT>
    void _execBeginReadDynData(const ReadDataInstr& instr, ElemT& elem, const Index lenPos,
                               Size& len, const Proc * const proc, const VmState nextState)
    {
        len = _pos.savedVal(lenPos);
        assert(len != SAVED_VAL_UNSET);
        this->_alignHead(instr);
        Vm::_setDataElemFromInstr(elem, instr);
        this->_updateItForUser(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(proc);
        _pos.stackTop().rem = len;
        _pos.state(nextState);
    }

    _ExecReaction _execUpdateDefClkValCommon(const Size len) noexcept
    {
        const auto newVal = _pos.updateDefClkVal(len);

        _pos.elems.defClkVal._cycles = newVal;
        this->_updateItForUser(_pos.elems.defClkVal);
        return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
    }

private:
    using ExecFunc = _ExecReaction (Vm::*)(const Instr&);

private:
    DataSourceFactory *_dataSrcFactory;
    DataSource::UP _dataSrc;

    // current buffer
    const std::uint8_t *_bufAddr = nullptr;

    // length of current buffer (bits)
    Size _bufLenBits = 0;

    // offset of buffer within current packet (bits)
    Index _bufOffsetInCurPktBits = 0;

    // owning element sequence iterator
    ElementSequenceIterator *_it;

    // array of instruction handler functions
    std::array<ExecFunc, 150> _execFuncs;

    // position (whole state of the VM)
    VmPos _pos;
};

template <Instr::Kind InstrKindV>
void Vm::_initExecFunc(const ExecFunc execFunc) noexcept
{
    constexpr auto index = static_cast<unsigned int>(InstrKindV);

    static_assert(index < std::tuple_size<decltype(this->_execFuncs)>::value,
                  "Instruction handler array is large enough.");

    _execFuncs[index] = execFunc;
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_VM_HPP
