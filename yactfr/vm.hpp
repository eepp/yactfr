/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
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
#include <array>

#include <yactfr/aliases.hpp>
#include <yactfr/elem.hpp>
#include <yactfr/data-src-factory.hpp>
#include <yactfr/elem.hpp>
#include <yactfr/elem-seq-it.hpp>
#include <yactfr/decoding-errors.hpp>

#include "proc.hpp"
#include "std-fl-int-reader.hpp"

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
    READ_SUBSTR_UNTIL_NULL,
    READ_SUBSTR,
    READ_BLOB_SECTION,
    CONTINUE_READ_VL_UINT,
    CONTINUE_READ_VL_SINT,
    END_STR,
    SET_TRACE_TYPE_UUID,
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
    Size rem;
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
         * Reset all information elements as a given element sequence
         * may contain packets from data streams having different types,
         * therefore having different packet context and event record
         * header types.
         */
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
        EndElement end;
        ScopeBeginningElement scopeBeginning;
        PacketContentBeginningElement pktContentBeginning;
        EventRecordBeginningElement erBeginning;
        PacketMagicNumberElement pktMagicNumber;
        TraceTypeUuidElement traceTypeUuid;
        DataStreamInfoElement dsInfo;
        PacketInfoElement pktInfo;
        EventRecordInfoElement erInfo;
        DefaultClockValueElement defClkVal;
        FixedLengthBitArrayElement flBitArray;
        FixedLengthBooleanElement flBool;
        FixedLengthSignedIntegerElement flSInt;
        FixedLengthUnsignedIntegerElement flUInt;
        FixedLengthSignedEnumerationElement flSEnum;
        FixedLengthUnsignedEnumerationElement flUEnum;
        FixedLengthFloatingPointNumberElement flFloat;
        VariableLengthBitArrayElement vlBitArray;
        VariableLengthSignedIntegerElement vlSInt;
        VariableLengthUnsignedIntegerElement vlUInt;
        VariableLengthSignedEnumerationElement vlSEnum;
        VariableLengthUnsignedEnumerationElement vlUEnum;
        NullTerminatedStringBeginningElement ntStrBeginning;
        SubstringElement substr;
        BlobSectionElement blobSection;
        StaticLengthArrayBeginningElement slArrayBeginning;
        DynamicLengthArrayBeginningElement dlArrayBeginning;
        StaticLengthStringBeginningElement slStrBeginning;
        DynamicLengthStringBeginningElement dlStrBeginning;
        StaticLengthBlobBeginningElement slBlobBeginning;
        DynamicLengthBlobBeginningElement dlBlobBeginning;
        StructureBeginningElement structBeginning;
        VariantWithSignedSelectorBeginningElement varSSelBeginning;
        VariantWithUnsignedSelectorBeginningElement varUSelBeginning;
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

    // current variable-length bit array length (bits)
    Size curVlBitArrayLenBits;

    // current variable-length bit array element
    VariableLengthBitArrayElement *curVlBitArrayElem;

    // current ID (event record or data stream type)
    TypeId curId;

    // packet procedure
    const PktProc *pktProc = nullptr;

    // current data stream type packet procedure
    const DsPktProc *curDsPktProc = nullptr;

    // current event record type procedure
    const ErProc *curErProc = nullptr;

    // packet UUID
    boost::uuids::uuid uuid;

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
    Vm& operator=(const Vm& vm);
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

        case VmState::READ_SUBSTR:
            return this->_stateReadSubstr();

        case VmState::READ_BLOB_SECTION:
            return this->_stateReadBlobSection();

        case VmState::CONTINUE_READ_VL_UINT:
            return this->_stateContinueReadVlInt<false>();

        case VmState::CONTINUE_READ_VL_SINT:
            return this->_stateContinueReadVlInt<true>();

        case VmState::READ_SUBSTR_UNTIL_NULL:
            return this->_stateReadSubstrUntilNull();

        case VmState::END_STR:
            return this->_stateEndStr();

        case VmState::CONTINUE_SKIP_PADDING_BITS:
            return this->_stateContinueSkipPaddingBits();

        case VmState::CONTINUE_SKIP_CONTENT_PADDING_BITS:
            return this->_stateContinueSkipPaddingBits();

        case VmState::READ_UUID_BYTE:
            return this->_stateReadUuidByte();

        case VmState::SET_TRACE_TYPE_UUID:
            return this->_stateSetTraceTypeUuid();

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

        this->_updateItCurOffset(_pos.elems.pktBeginning);
        _pos.loadNewProc(_pos.pktProc->preambleProc());
        _pos.state(VmState::BEGIN_PKT_CONTENT);
        return true;
    }

    bool _stateBeginPktContent()
    {
        this->_updateItCurOffset(_pos.elems.pktContentBeginning);

        // the packet's preamble procedure is already loaded at this point
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

        this->_updateItCurOffset(_pos.elems.end);
        return true;
    }

    bool _stateEndPkt()
    {
        const auto offset = _pos.headOffsetInElemSeqBits();

        // readjust buffer address and offsets
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

        this->_updateIt(_pos.elems.end, offset);
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

        // align now so that the iterator's offset is after any padding
        this->_alignHead(_pos.curDsPktProc->erAlign());

        this->_updateItCurOffset(_pos.elems.erBeginning);
        _pos.loadNewProc(_pos.curDsPktProc->erPreambleProc());
        _pos.state(VmState::EXEC_INSTR);
        return true;
    }

    bool _stateEndEr()
    {
        assert(_pos.curErProc);
        _pos.curErProc = nullptr;
        this->_updateItCurOffset(_pos.elems.end);
        _pos.state(VmState::BEGIN_ER);
        return true;
    }

    bool _stateReadUuidByte()
    {
        if (_pos.stackTop().rem == 0) {
            // set completed UUID
            _pos.state(VmState::SET_TRACE_TYPE_UUID);
            return false;
        }

        auto& instr = **_pos.stackTop().it;

        this->_execReadStdFlInt<std::uint64_t, 8, readFlUInt8>(instr);
        _pos.uuid.data[16 - _pos.stackTop().rem] = static_cast<std::uint8_t>(_pos.lastIntVal.u);
        --_pos.stackTop().rem;
        return true;
    }

    bool _stateSetTraceTypeUuid()
    {
        assert(_pos.pktProc->traceType().uuid());

        // `_pos.elems.traceTypeUuid._expectedUuid` is already set once
        _pos.elems.traceTypeUuid._uuid = _pos.uuid;
        this->_updateItCurOffset(_pos.elems.traceTypeUuid);
        _pos.setParentStateAndStackPop();
        return true;
    }

    template <typename ByteT, typename ElemT>
    bool _stateReadBytes(ElemT& elem)
    {
        assert((_pos.headOffsetInCurPktBits & 7) == 0);

        if (_pos.stackTop().rem == 0) {
            _pos.setParentStateAndStackPop();
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

        elem._begin = reinterpret_cast<const ByteT *>(buf);
        elem._end = reinterpret_cast<const ByteT *>(buf + sectionSizeBytes);
        assert(elem.size() > 0);
        this->_updateItCurOffset(elem);
        this->_consumeExistingBits(sectionSizeBytes * 8);
        _pos.stackTop().rem -= sectionSizeBytes;
        return true;
    }

    bool _stateReadSubstr()
    {
        return this->_stateReadBytes<char>(_pos.elems.substr);
    }

    bool _stateReadBlobSection()
    {
        return this->_stateReadBytes<std::uint8_t>(_pos.elems.blobSection);
    }

    void _signExtendVlSIntVal() noexcept
    {
        const auto mask = UINT64_C(1) << (_pos.curVlBitArrayLenBits - 1);

        _pos.lastIntVal.u = _pos.lastIntVal.u & ((UINT64_C(1) << _pos.curVlBitArrayLenBits) - 1);
        _pos.lastIntVal.u = (_pos.lastIntVal.u ^ mask) - mask;
    }

    void _appendVlIntByte(std::uint8_t byte)
    {
        // validate future variable-length bit-array length
        if ((_pos.curVlBitArrayLenBits + 7) > 64) {

            throw OversizedVariableLengthBitArrayDecodingError {_pos.headOffsetInElemSeqBits()};
        }

        // mark this byte as consumed immediately
        this->_consumeExistingBits(8);

        // update unsigned integer value, clearing continuation bit
        _pos.lastIntVal.u |= (static_cast<std::uint64_t>(byte & 0b0111'1111) <<
                              _pos.curVlBitArrayLenBits);

        // update current variable-length bit-array length
        _pos.curVlBitArrayLenBits += 7;
    }

    template <bool IsSignedV>
    bool _stateContinueReadVlInt()
    {
        /*
         * Read a single byte, and then:
         *
         * If the variable-length bit array is not ended:
         *     Keep this state.
         *
         * Otherwise:
         *     Set the variable-length bit array element and set the
         *     state to the previous value.
         *
         * See <https://en.wikipedia.org/wiki/LEB128>.
         */
        assert((_pos.headOffsetInCurPktBits & 7) == 0);

        // require at least one byte
        this->_requireContentBits(8);

        // read current byte
        const auto byte = *this->_bufAtHead();

        // mark this byte as consumed immediately
        this->_consumeExistingBits(8);

        if ((byte & 0b1000'0000) == 0) {
            // this is the last byte
            this->_appendVlIntByte(byte);

            /*
             * When calling _setBitArrayElemBase() below,
             * `**_pos.stackTop().it` is the current
             * `ReadVlBitArrayInstr` instruction.
             */
            assert(_pos.curVlBitArrayElem);
            _pos.curVlBitArrayElem->_len = _pos.curVlBitArrayLenBits;

            if (IsSignedV) {
                this->_signExtendVlSIntVal();
                this->_setBitArrayElemBase(_pos.lastIntVal.i, **_pos.stackTop().it,
                                           *_pos.curVlBitArrayElem);
            } else {
                this->_setBitArrayElemBase(_pos.lastIntVal.u, **_pos.stackTop().it,
                                           *_pos.curVlBitArrayElem);
            }

            // we're done with this instruction and this state
            _pos.gotoNextInstr();
            _pos.state(_pos.nextState);
            assert(_pos.state() == VmState::EXEC_INSTR ||
                   _pos.state() == VmState::EXEC_ARRAY_INSTR);
            return true;
        }

        // not the last byte
        this->_appendVlIntByte(byte);
        return false;
    }

    bool _stateReadSubstrUntilNull()
    {
        assert((_pos.headOffsetInCurPktBits & 7) == 0);

        // require at least one byte
        this->_requireContentBits(8);

        const auto buf = this->_bufAtHead();
        const auto bufSizeBytes = this->_remBitsInBuf() / 8;

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

        const Size substrLenBits = (end - begin) * 8;

        if (substrLenBits > _pos.remContentBitsInPkt()) {
            throw CannotDecodeDataBeyondPacketContentDecodingError {
                _pos.headOffsetInElemSeqBits(),
                substrLenBits, _pos.remContentBitsInPkt()
            };
        }

        _pos.elems.substr._begin = begin;
        _pos.elems.substr._end = end;

        if (res) {
            // we're done
            _pos.state(VmState::END_STR);
        }

        assert(_pos.elems.substr.size() > 0);
        this->_updateItCurOffset(_pos.elems.substr);
        this->_consumeExistingBits(_pos.elems.substr.size() * 8);
        return true;
    }

    bool _stateEndStr()
    {
        this->_updateItCurOffset(_pos.elems.end);
        _pos.state(_pos.nextState);
        assert(_pos.state() == VmState::EXEC_INSTR || _pos.state() == VmState::EXEC_ARRAY_INSTR);
        return true;
    }

    _ExecReaction _exec(const Instr& instr)
    {
        return (this->*_execFuncs[static_cast<Index>(instr.kind())])(instr);
    }

    void _updateIt(const Element& elem, const Index offset)
    {
        _it->_curElem = &elem;
        _it->_offset = offset;
        ++_it->_mark;
    }

    void _updateItCurOffset(const Element& elem)
    {
        _it->_curElem = &elem;
        _it->_offset = _pos.headOffsetInElemSeqBits();
        ++_it->_mark;
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
            // going past the packet's content
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
    _ExecReaction _execReadFlBitArrayLe(const Instr& instr);
    _ExecReaction _execReadFlBitArrayBe(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA8(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA16Le(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA32Le(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA64Le(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA16Be(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA32Be(const Instr& instr);
    _ExecReaction _execReadFlBitArrayA64Be(const Instr& instr);
    _ExecReaction _execReadFlBoolLe(const Instr& instr);
    _ExecReaction _execReadFlBoolBe(const Instr& instr);
    _ExecReaction _execReadFlBoolA8(const Instr& instr);
    _ExecReaction _execReadFlBoolA16Le(const Instr& instr);
    _ExecReaction _execReadFlBoolA32Le(const Instr& instr);
    _ExecReaction _execReadFlBoolA64Le(const Instr& instr);
    _ExecReaction _execReadFlBoolA16Be(const Instr& instr);
    _ExecReaction _execReadFlBoolA32Be(const Instr& instr);
    _ExecReaction _execReadFlBoolA64Be(const Instr& instr);
    _ExecReaction _execReadFlSIntLe(const Instr& instr);
    _ExecReaction _execReadFlSIntBe(const Instr& instr);
    _ExecReaction _execReadFlSIntA8(const Instr& instr);
    _ExecReaction _execReadFlSIntA16Le(const Instr& instr);
    _ExecReaction _execReadFlSIntA32Le(const Instr& instr);
    _ExecReaction _execReadFlSIntA64Le(const Instr& instr);
    _ExecReaction _execReadFlSIntA16Be(const Instr& instr);
    _ExecReaction _execReadFlSIntA32Be(const Instr& instr);
    _ExecReaction _execReadFlSIntA64Be(const Instr& instr);
    _ExecReaction _execReadFlUIntLe(const Instr& instr);
    _ExecReaction _execReadFlUIntBe(const Instr& instr);
    _ExecReaction _execReadFlUIntA8(const Instr& instr);
    _ExecReaction _execReadFlUIntA16Le(const Instr& instr);
    _ExecReaction _execReadFlUIntA32Le(const Instr& instr);
    _ExecReaction _execReadFlUIntA64Le(const Instr& instr);
    _ExecReaction _execReadFlUIntA16Be(const Instr& instr);
    _ExecReaction _execReadFlUIntA32Be(const Instr& instr);
    _ExecReaction _execReadFlUIntA64Be(const Instr& instr);
    _ExecReaction _execReadFlFloat32Le(const Instr& instr);
    _ExecReaction _execReadFlFloat32Be(const Instr& instr);
    _ExecReaction _execReadFlFloatA32Le(const Instr& instr);
    _ExecReaction _execReadFlFloatA32Be(const Instr& instr);
    _ExecReaction _execReadFlFloat64Le(const Instr& instr);
    _ExecReaction _execReadFlFloat64Be(const Instr& instr);
    _ExecReaction _execReadFlFloatA64Le(const Instr& instr);
    _ExecReaction _execReadFlFloatA64Be(const Instr& instr);
    _ExecReaction _execReadFlSEnumLe(const Instr& instr);
    _ExecReaction _execReadFlSEnumBe(const Instr& instr);
    _ExecReaction _execReadFlSEnumA8(const Instr& instr);
    _ExecReaction _execReadFlSEnumA16Le(const Instr& instr);
    _ExecReaction _execReadFlSEnumA32Le(const Instr& instr);
    _ExecReaction _execReadFlSEnumA64Le(const Instr& instr);
    _ExecReaction _execReadFlSEnumA16Be(const Instr& instr);
    _ExecReaction _execReadFlSEnumA32Be(const Instr& instr);
    _ExecReaction _execReadFlSEnumA64Be(const Instr& instr);
    _ExecReaction _execReadFlUEnumLe(const Instr& instr);
    _ExecReaction _execReadFlUEnumBe(const Instr& instr);
    _ExecReaction _execReadFlUEnumA8(const Instr& instr);
    _ExecReaction _execReadFlUEnumA16Le(const Instr& instr);
    _ExecReaction _execReadFlUEnumA32Le(const Instr& instr);
    _ExecReaction _execReadFlUEnumA64Le(const Instr& instr);
    _ExecReaction _execReadFlUEnumA16Be(const Instr& instr);
    _ExecReaction _execReadFlUEnumA32Be(const Instr& instr);
    _ExecReaction _execReadFlUEnumA64Be(const Instr& instr);
    _ExecReaction _execReadVlBitArray(const Instr& instr);
    _ExecReaction _execReadVlUInt(const Instr& instr);
    _ExecReaction _execReadVlSInt(const Instr& instr);
    _ExecReaction _execReadVlUEnum(const Instr& instr);
    _ExecReaction _execReadVlSEnum(const Instr& instr);
    _ExecReaction _execReadNtStr(const Instr& instr);
    _ExecReaction _execBeginReadScope(const Instr& instr);
    _ExecReaction _execEndReadScope(const Instr& instr);
    _ExecReaction _execBeginReadStruct(const Instr& instr);
    _ExecReaction _execEndReadStruct(const Instr& instr);
    _ExecReaction _execBeginReadSlArray(const Instr& instr);
    _ExecReaction _execEndReadSlArray(const Instr& instr);
    _ExecReaction _execBeginReadSlStr(const Instr& instr);
    _ExecReaction _execEndReadSlStr(const Instr& instr);
    _ExecReaction _execBeginReadSlUuidArray(const Instr& instr);
    _ExecReaction _execBeginReadDlArray(const Instr& instr);
    _ExecReaction _execEndReadDlArray(const Instr& instr);
    _ExecReaction _execBeginReadDlStr(const Instr& instr);
    _ExecReaction _execEndReadDlStr(const Instr& instr);
    _ExecReaction _execBeginReadSlBlob(const Instr& instr);
    _ExecReaction _execEndReadSlBlob(const Instr& instr);
    _ExecReaction _execBeginReadDlBlob(const Instr& instr);
    _ExecReaction _execEndReadDlBlob(const Instr& instr);
    _ExecReaction _execBeginReadVarSSel(const Instr& instr);
    _ExecReaction _execBeginReadVarUSel(const Instr& instr);
    _ExecReaction _execEndReadVar(const Instr& instr);
    _ExecReaction _execSaveVal(const Instr& instr);
    _ExecReaction _execSetPktEndDefClkVal(const Instr& instr);
    _ExecReaction _execUpdateDefClkValFl(const Instr& instr);
    _ExecReaction _execUpdateDefClkVal(const Instr& instr);
    _ExecReaction _execSetCurrentId(const Instr& instr);
    _ExecReaction _execSetDst(const Instr& instr);
    _ExecReaction _execSetErt(const Instr& instr);
    _ExecReaction _execSetDsId(const Instr& instr);
    _ExecReaction _execSetPktOriginIndex(const Instr& instr);
    _ExecReaction _execSetPktTotalLen(const Instr& instr);
    _ExecReaction _execSetPktContentLen(const Instr& instr);
    _ExecReaction _execSetPktMagicNumber(const Instr& instr);
    _ExecReaction _execEndPktPreambleProc(const Instr& instr);
    _ExecReaction _execEndDsPktPreambleProc(const Instr& instr);
    _ExecReaction _execEndDsErPreambleProc(const Instr& instr);
    _ExecReaction _execEndErProc(const Instr& instr);
    _ExecReaction _execSetDsInfo(const Instr& instr);
    _ExecReaction _execSetPktInfo(const Instr& instr);
    _ExecReaction _execSetErInfo(const Instr& instr);

    static void _setDataElemFromInstr(DataElement& elem, const ReadDataInstr& readDataInstr) noexcept
    {
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
    void _setBitArrayElemBase(const ValT val, const Instr& instr, ElemT& elem) noexcept
    {
        using DataTypeT = typename std::remove_const<typename std::remove_reference<decltype(elem.type())>::type>::type;

        auto& readDataInstr = static_cast<const ReadDataInstr&>(instr);

        Vm::_setDataElemFromInstr(elem, readDataInstr);
        elem._dt = static_cast<const DataTypeT *>(&readDataInstr.dt());
        this->_setLastIntVal(val);
        elem._val(val);
        this->_updateItCurOffset(elem);
    }

    void _setFlIntElem(const std::uint64_t val, const Instr& instr) noexcept
    {
        this->_setBitArrayElemBase(val, instr, _pos.elems.flUInt);
    }

    void _setFlIntElem(const std::int64_t val, const Instr& instr) noexcept
    {
        this->_setBitArrayElemBase(val, instr, _pos.elems.flSInt);
    }

    void _setFlEnumElem(const std::uint64_t val, const Instr& instr) noexcept
    {
        this->_setBitArrayElemBase(val, instr, _pos.elems.flUEnum);
    }

    void _setFlEnumElem(const std::int64_t val, const Instr& instr) noexcept
    {
        this->_setBitArrayElemBase(val, instr, _pos.elems.flSEnum);
    }

    void _setFlFloatVal(const double val, const ReadDataInstr& instr) noexcept
    {
        Vm::_setDataElemFromInstr(_pos.elems.flFloat, instr);
        _pos.elems.flFloat._dt = static_cast<const FixedLengthFloatingPointNumberType *>(&instr.dt());
        _pos.elems.flFloat._val(val);
        this->_updateItCurOffset(_pos.elems.flFloat);
    }

    void _execReadFlBitArrayPreamble(const Instr& instr, const Size len)
    {
        auto& readFlBitArrayInstr = static_cast<const ReadFlBitArrayInstr&>(instr);

        this->_alignHead(readFlBitArrayInstr);
        this->_requireContentBits(len);
    }

    template <typename RetT, Size LenBits, RetT (*Func)(const std::uint8_t *)>
    RetT _readStdFlInt(const Instr& instr)
    {
        auto& readFlBitArrayInstr = static_cast<const ReadFlBitArrayInstr&>(instr);

        this->_execReadFlBitArrayPreamble(instr, LenBits);
        _pos.lastFlBitArrayBo = readFlBitArrayInstr.bo();
        return Func(this->_bufAtHead());
    }

    template <Size LenBits, std::uint64_t (*Func)(const std::uint8_t *)>
    void _execReadStdFlBitArray(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<std::uint64_t, LenBits, Func>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBitArray);
        this->_consumeExistingBits(LenBits);
    }

    template <Size LenBits, std::uint64_t (*Func)(const std::uint8_t *)>
    void _execReadStdFlBool(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<std::uint64_t, LenBits, Func>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBool);
        this->_consumeExistingBits(LenBits);
    }

    template <typename RetT, Size LenBits, RetT (*Func)(const std::uint8_t *)>
    void _execReadStdFlInt(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<RetT, LenBits, Func>(instr);

        this->_setFlIntElem(val, instr);
        this->_consumeExistingBits(LenBits);
    }

    template <typename RetT, Size LenBits, RetT (*Func)(const std::uint8_t *)>
    void _execReadStdFlEnum(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<RetT, LenBits, Func>(instr);

        this->_setFlEnumElem(val, instr);
        this->_consumeExistingBits(LenBits);
    }

    template <typename RetT, RetT (*Funcs[])(const std::uint8_t *)>
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

        return Funcs[index](this->_bufAtHead());
    }

    template <std::uint64_t (*Funcs[])(const std::uint8_t *)>
    void _execReadFlBitArray(const Instr& instr)
    {
        const auto val = this->_readFlInt<std::uint64_t, Funcs>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBitArray);
        this->_consumeExistingBits(static_cast<const ReadFlBitArrayInstr&>(instr).len());
    }

    template <std::uint64_t (*Funcs[])(const std::uint8_t *)>
    void _execReadFlBool(const Instr& instr)
    {
        const auto val = this->_readFlInt<std::uint64_t, Funcs>(instr);

        this->_setBitArrayElemBase(val, instr, _pos.elems.flBool);
        this->_consumeExistingBits(static_cast<const ReadFlBoolInstr&>(instr).len());
    }

    template <typename RetT, RetT (*Funcs[])(const std::uint8_t *)>
    void _execReadFlInt(const Instr& instr)
    {
        const auto val = this->_readFlInt<RetT, Funcs>(instr);

        this->_setFlIntElem(val, instr);
        this->_consumeExistingBits(static_cast<const ReadFlBitArrayInstr&>(instr).len());
    }

    template <typename RetT, RetT (*Funcs[])(const std::uint8_t *)>
    void _execReadFlEnum(const Instr& instr)
    {
        const auto val = this->_readFlInt<RetT, Funcs>(instr);

        this->_setFlEnumElem(val, instr);
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

    template <typename FloatT, std::uint64_t (*Funcs[])(const std::uint8_t *)>
    void _execReadFlFloat(const Instr& instr)
    {
        const auto val = this->_readFlInt<std::uint64_t, Funcs>(instr);

        this->_execReadFlFloatPost<FloatT>(val, instr);
    }

    template <typename FloatT, std::uint64_t (*Func)(const std::uint8_t *)>
    void _execReadStdFlFloat(const Instr& instr)
    {
        const auto val = this->_readStdFlInt<std::uint64_t, sizeof(FloatT) * 8, Func>(instr);

        this->_execReadFlFloatPost<FloatT>(val, instr);
    }

    _ExecReaction _execReadVlBitArrayCommon(const Instr& instr,
                                            VariableLengthBitArrayElement& elem,
                                            const VmState nextState)
    {
        this->_alignHead(instr);
        _pos.curVlBitArrayElem = &elem;
        _pos.curVlBitArrayLenBits = 0;
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
                throw InvalidVariantSignedSelectorValueDecodingError {
                    _pos.headOffsetInElemSeqBits(),
                    static_cast<std::int64_t>(selVal)
                };
            } else {
                throw InvalidVariantUnsignedSelectorValueDecodingError {
                    _pos.headOffsetInElemSeqBits(),
                    static_cast<std::uint64_t>(selVal)
                };
            }
        }

        Vm::_setDataElemFromInstr(elem, beginReadVarInstr);
        elem._dt = &beginReadVarInstr.varType();
        elem._selVal = selVal;
        this->_updateItCurOffset(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(proc);
        _pos.state(VmState::EXEC_INSTR);
    }

    template <typename ElemT>
    void _execBeginReadStaticData(const ReadDataInstr& instr, ElemT& elem, const Size len,
                                  const Proc * const proc, const VmState nextState)
    {
        this->_alignHead(instr);
        Vm::_setDataElemFromInstr(elem, instr);
        this->_updateItCurOffset(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(proc);
        _pos.stackTop().rem = len;
        _pos.state(nextState);
    }

    _ExecReaction _execBeginReadSlArray(const Instr& instr, const VmState nextState)
    {
        const auto& beginReadStaticArrayInstr = static_cast<const BeginReadSlArrayInstr&>(instr);

        _pos.elems.slArrayBeginning._dt = &beginReadStaticArrayInstr.staticArrayType();
        _pos.elems.slArrayBeginning._len = beginReadStaticArrayInstr.len();
        this->_execBeginReadStaticData(beginReadStaticArrayInstr, _pos.elems.slArrayBeginning,
                                       beginReadStaticArrayInstr.len(),
                                       &beginReadStaticArrayInstr.proc(), nextState);
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
        this->_updateItCurOffset(elem);
        _pos.gotoNextInstr();
        _pos.stackPush(proc);
        _pos.stackTop().rem = len;
        _pos.state(nextState);
    }

    _ExecReaction _execUpdateDefClkValCommon(const Size len) noexcept
    {
        const auto newVal = _pos.updateDefClkVal(len);

        _pos.elems.defClkVal._cycles = newVal;
        this->_updateItCurOffset(_pos.elems.defClkVal);
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
    std::array<ExecFunc, 128> _execFuncs;

    // position (whole VM's state)
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

#endif // _YACTFR_VM_HPP
