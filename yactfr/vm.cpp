/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstdint>

#include "vm.hpp"
#include "fl-int-reader.hpp"

namespace yactfr {
namespace internal {

VmPos::VmPos(const PktProc& pktProc) :
    pktProc {&pktProc}
{
    if (pktProc.traceType().uuid()) {
        elems.traceTypeUuid._expectedUuid = *pktProc.traceType().uuid();
    }

    this->_initVectorsFromPktProc();
}

VmPos::VmPos(const VmPos& other)
{
    this->_setFromOther(other);
}

VmPos& VmPos::operator=(const VmPos& other)
{
    assert(pktProc == other.pktProc);
    this->_setFromOther(other);
    return *this;
}

void VmPos::_initVectorsFromPktProc()
{
    savedVals.resize(pktProc->savedValsCount(), SIZE_UNSET);
}

void VmPos::_setSimpleFromOther(const VmPos& other)
{
    curPktOffsetInElemSeqBits = other.curPktOffsetInElemSeqBits;
    headOffsetInCurPktBits = other.headOffsetInCurPktBits;
    elems = other.elems;
    theState = other.theState;
    lastBo = other.lastBo;
    remBitsToSkip = other.remBitsToSkip;
    postSkipBitsState = other.postSkipBitsState;
    postEndStrState = other.postEndStrState;
    lastIntVal = other.lastIntVal;
    curId = other.curId;
    pktProc = other.pktProc;
    curDsPktProc = other.curDsPktProc;
    curErProc = other.curErProc;
    uuid = other.uuid;
    curExpectedPktTotalLenBits = other.curExpectedPktTotalLenBits;
    curExpectedPktContentLenBits = other.curExpectedPktContentLenBits;
}

void VmPos::_setFromOther(const VmPos& other)
{
    this->_setSimpleFromOther(other);
    stack = other.stack;
    savedVals = other.savedVals;
    defClkVal = other.defClkVal;
}

} // namespace internal

ElementSequenceIteratorPosition::~ElementSequenceIteratorPosition()
{
}

ElementSequenceIteratorPosition::ElementSequenceIteratorPosition() :
    _vmPos {nullptr},
    _itInfos {std::make_unique<internal::ItInfos>()}
{
}

ElementSequenceIteratorPosition::ElementSequenceIteratorPosition(const ElementSequenceIteratorPosition& other) :
    ElementSequenceIteratorPosition {}
{
    if (other._vmPos) {
        // use copy constructor
        _vmPos = std::make_unique<internal::VmPos>(*other._vmPos);
    } else {
        _vmPos = nullptr;
        return;
    }

    _itInfos->offset = other._itInfos->offset;
    _itInfos->mark = other._itInfos->mark;
    assert(other._itInfos->elem);
    _itInfos->elemFromOther(*_vmPos, *other._vmPos, *other._itInfos->elem);
}

ElementSequenceIteratorPosition::ElementSequenceIteratorPosition(ElementSequenceIteratorPosition&& other) :
    _vmPos {std::move(other._vmPos)},
    _itInfos {std::make_unique<internal::ItInfos>(*other._itInfos)}
{
}

ElementSequenceIteratorPosition& ElementSequenceIteratorPosition::operator=(const ElementSequenceIteratorPosition& other)
{
    if (other._vmPos) {
        // use copy constructor
        _vmPos = std::make_unique<internal::VmPos>(*other._vmPos);
    } else {
        _vmPos = nullptr;
        return *this;
    }

    _itInfos->offset = other._itInfos->offset;
    _itInfos->mark = other._itInfos->mark;
    assert(other._itInfos->elem);
    _itInfos->elemFromOther(*_vmPos, *other._vmPos, *other._itInfos->elem);
    return *this;
}

ElementSequenceIteratorPosition& ElementSequenceIteratorPosition::operator=(ElementSequenceIteratorPosition&& other)
{
    _vmPos = std::move(other._vmPos);
    *_itInfos = *other._itInfos;
    return *this;
}

ElementSequenceIteratorPosition::operator bool() const noexcept
{
    return static_cast<bool>(_vmPos);
}

bool ElementSequenceIteratorPosition::operator==(const ElementSequenceIteratorPosition& other) const noexcept
{
    return *_itInfos == *other._itInfos;
}

bool ElementSequenceIteratorPosition::operator!=(const ElementSequenceIteratorPosition& other) const noexcept
{
    return *_itInfos != *other._itInfos;
}

bool ElementSequenceIteratorPosition::operator<(const ElementSequenceIteratorPosition& other) const noexcept
{
    return *_itInfos < *other._itInfos;
}

bool ElementSequenceIteratorPosition::operator<=(const ElementSequenceIteratorPosition& other) const noexcept
{
    return *_itInfos <= *other._itInfos;
}

bool ElementSequenceIteratorPosition::operator>(const ElementSequenceIteratorPosition& other) const noexcept
{
    return *_itInfos > *other._itInfos;
}

bool ElementSequenceIteratorPosition::operator>=(const ElementSequenceIteratorPosition& other) const noexcept
{
    return *_itInfos >= *other._itInfos;
}

namespace internal {

Vm::Vm(DataSourceFactory& dataSrcFactory, const PktProc& pktProc, ElementSequenceIterator& it) :
    _dataSrcFactory {&dataSrcFactory},
    _dataSrc {dataSrcFactory.createDataSource()},
    _it {&it},
    _pos {pktProc}
{
    this->_initExecFuncs();
}

Vm::Vm(const Vm& other, ElementSequenceIterator& it) :
    _dataSrcFactory {other._dataSrcFactory},
    _dataSrc {_dataSrcFactory->createDataSource()},
    _it {&it},
    _pos {other._pos}
{
    this->_initExecFuncs();
    this->_resetBuffer();
}

Vm& Vm::operator=(const Vm& other)
{
    assert(_dataSrcFactory == other._dataSrcFactory);
    _it = nullptr;
    _pos = other._pos;
    this->_resetBuffer();
    return *this;
}

void Vm::_initExecFuncs()
{
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_LE)] = &Vm::_execReadFlSIntLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_BE)] = &Vm::_execReadFlSIntBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_A8)] = &Vm::_execReadFlSIntA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_A16_LE)] = &Vm::_execReadFlSIntA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_A32_LE)] = &Vm::_execReadFlSIntA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_A64_LE)] = &Vm::_execReadFlSIntA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_A16_BE)] = &Vm::_execReadFlSIntA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_A32_BE)] = &Vm::_execReadFlSIntA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SINT_A64_BE)] = &Vm::_execReadFlSIntA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_LE)] = &Vm::_execReadFlUIntLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_BE)] = &Vm::_execReadFlUIntBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_A8)] = &Vm::_execReadFlUIntA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_A16_LE)] = &Vm::_execReadFlUIntA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_A32_LE)] = &Vm::_execReadFlUIntA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_A64_LE)] = &Vm::_execReadFlUIntA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_A16_BE)] = &Vm::_execReadFlUIntA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_A32_BE)] = &Vm::_execReadFlUIntA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UINT_A64_BE)] = &Vm::_execReadFlUIntA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_32_LE)] = &Vm::_execReadFlFloat32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_32_BE)] = &Vm::_execReadFlFloat32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_A32_LE)] = &Vm::_execReadFlFloatA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_A32_BE)] = &Vm::_execReadFlFloatA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_64_LE)] = &Vm::_execReadFlFloat64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_64_BE)] = &Vm::_execReadFlFloat64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_A64_LE)] = &Vm::_execReadFlFloatA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_FLOAT_A64_BE)] = &Vm::_execReadFlFloatA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_LE)] = &Vm::_execReadFlSEnumLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_BE)] = &Vm::_execReadFlSEnumBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_A8)] = &Vm::_execReadFlSEnumA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_A16_LE)] = &Vm::_execReadFlSEnumA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_A32_LE)] = &Vm::_execReadFlSEnumA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_A64_LE)] = &Vm::_execReadFlSEnumA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_A16_BE)] = &Vm::_execReadFlSEnumA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_A32_BE)] = &Vm::_execReadFlSEnumA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_SENUM_A64_BE)] = &Vm::_execReadFlSEnumA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_LE)] = &Vm::_execReadFlUEnumLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_BE)] = &Vm::_execReadFlUEnumBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_A8)] = &Vm::_execReadFlUEnumA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_A16_LE)] = &Vm::_execReadFlUEnumA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_A32_LE)] = &Vm::_execReadFlUEnumA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_A64_LE)] = &Vm::_execReadFlUEnumA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_A16_BE)] = &Vm::_execReadFlUEnumA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_A32_BE)] = &Vm::_execReadFlUEnumA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FL_UENUM_A64_BE)] = &Vm::_execReadFlUEnumA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_NT_STR)] = &Vm::_execReadNtStr;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_SCOPE)] = &Vm::_execBeginReadScope;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_SCOPE)] = &Vm::_execEndReadScope;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STRUCT)] = &Vm::_execBeginReadStruct;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_STRUCT)] = &Vm::_execEndReadStruct;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STATIC_ARRAY)] = &Vm::_execBeginReadStaticArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_STATIC_ARRAY)] = &Vm::_execEndReadStaticArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STATIC_TEXT_ARRAY)] = &Vm::_execBeginReadStaticTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_STATIC_TEXT_ARRAY)] = &Vm::_execEndReadStaticTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STATIC_UUID_ARRAY)] = &Vm::_execBeginReadStaticUuidArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_DYN_ARRAY)] = &Vm::_execBeginReadDynArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_DYN_ARRAY)] = &Vm::_execEndReadDynArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_DYN_TEXT_ARRAY)] = &Vm::_execBeginReadDynTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_DYN_TEXT_ARRAY)] = &Vm::_execEndReadDynTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_VAR_SSEL)] = &Vm::_execBeginReadVarSSel;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_VAR_USEL)] = &Vm::_execBeginReadVarUSel;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_VAR)] = &Vm::_execEndReadVar;
    _execFuncs[static_cast<int>(Instr::Kind::SAVE_VAL)] = &Vm::_execSaveVal;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PKT_END_DEF_CLK_VAL)] = &Vm::_execSetPktEndDefClkVal;
    _execFuncs[static_cast<int>(Instr::Kind::UPDATE_DEF_CLK_VAL)] = &Vm::_execUpdateDefClkVal;
    _execFuncs[static_cast<int>(Instr::Kind::SET_CUR_ID)] = &Vm::_execSetCurrentId;
    _execFuncs[static_cast<int>(Instr::Kind::SET_DST)] = &Vm::_execSetDst;
    _execFuncs[static_cast<int>(Instr::Kind::SET_ERT)] = &Vm::_execSetErt;
    _execFuncs[static_cast<int>(Instr::Kind::SET_DS_ID)] = &Vm::_execSetDsId;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PKT_ORIGIN_INDEX)] = &Vm::_execSetPktOriginIndex;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PKT_TOTAL_LEN)] = &Vm::_execSetPktTotalLen;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PKT_CONTENT_LEN)] = &Vm::_execSetPktContentLen;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PKT_MAGIC_NUMBER)] = &Vm::_execSetPktMagicNumber;
    _execFuncs[static_cast<int>(Instr::Kind::END_PKT_PREAMBLE_PROC)] = &Vm::_execEndPktPreambleProc;
    _execFuncs[static_cast<int>(Instr::Kind::END_DS_PKT_PREAMBLE_PROC)] = &Vm::_execEndDsPktPreambleProc;
    _execFuncs[static_cast<int>(Instr::Kind::END_DS_ER_PREAMBLE_PROC)] = &Vm::_execEndDsErPreambleProc;
    _execFuncs[static_cast<int>(Instr::Kind::END_ER_PROC)] = &Vm::_execEndErProc;
    _execFuncs[static_cast<int>(Instr::Kind::SET_DS_INFO)] = &Vm::_execSetDsInfo;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PKT_INFO)] = &Vm::_execSetPktInfo;
    _execFuncs[static_cast<int>(Instr::Kind::SET_ER_INFO)] = &Vm::_execSetErInfo;
}

void Vm::seekPkt(const Index offsetBytes)
{
    _pos.curPktOffsetInElemSeqBits = offsetBytes * 8;
    _pos.resetForNewPkt();
    this->_resetBuffer();

    // will set the packet beginning element, or end of iterator
    this->nextElem();
}

bool Vm::_newDataBlock(const Index offsetInElemSeqBytes, const Size sizeBytes)
{
    assert(sizeBytes <= 9);

    const auto dataBlock = _dataSrc->data(offsetInElemSeqBytes, sizeBytes);

    if (!dataBlock) {
        // no data
        return false;
    }

    _bufAddr = static_cast<const std::uint8_t *>(dataBlock->address());
    _bufLenBits = dataBlock->size() * 8;

    const auto offsetInElemSeqBits = offsetInElemSeqBytes * 8;

    _bufOffsetInCurPktBits = offsetInElemSeqBits - _pos.curPktOffsetInElemSeqBits;
    return true;
}

void Vm::savePos(ElementSequenceIteratorPosition& pos) const
{
    if (!pos) {
        // allocate new position
        pos._vmPos = std::make_unique<internal::VmPos>(_pos);
    } else {
        *pos._vmPos = _pos;
    }

    pos._itInfos->offset = _it->_offset;
    pos._itInfos->mark = _it->_mark;
    assert(_it->_curElem);
    pos._itInfos->elemFromOther(*pos._vmPos, _pos, *_it->_curElem);
}

void Vm::restorePos(const ElementSequenceIteratorPosition& pos)
{
    assert(pos);
    _pos = *pos._vmPos;
    _it->_offset = pos._itInfos->offset;
    _it->_mark = pos._itInfos->mark;
    this->updateItElemFromOtherPos(*pos._vmPos, pos._itInfos->elem);

    /*
     * Reset buffer: the next call to operator++() will require more
     * data and the VM will request a new data block at this moment.
     *
     * This is important to avoid throwing from this method so that it
     * always succeeds.
     */
    this->_resetBuffer();
}

Vm::_ExecReaction Vm::_execReadFlSIntLe(const Instr& instr)
{
    this->_execReadFlInt<std::int64_t, readFlSIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntBe(const Instr& instr)
{
    this->_execReadFlInt<std::int64_t, readFlSIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntA8(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 8, readFlSInt8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntA16Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 16, readFlSIntLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntA32Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 32, readFlSIntLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntA64Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 64, readFlSIntLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntA16Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 16, readFlSIntBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntA32Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 32, readFlSIntBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSIntA64Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 64, readFlSIntBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntLe(const Instr& instr)
{
    this->_execReadFlInt<std::uint64_t, readFlUIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntBe(const Instr& instr)
{
    this->_execReadFlInt<std::uint64_t, readFlUIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntA8(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 8, readFlUInt8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntA16Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 16, readFlUIntLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntA32Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 32, readFlUIntLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntA64Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 64, readFlUIntLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntA16Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 16, readFlUIntBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntA32Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 32, readFlUIntBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUIntA64Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 64, readFlUIntBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloat32Le(const Instr& instr)
{
    this->_execReadFlFloat<float, readFlUIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloat32Be(const Instr& instr)
{
    this->_execReadFlFloat<float, readFlUIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloatA32Le(const Instr& instr)
{
    this->_execReadStdFlFloat<float, readFlUIntLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloatA32Be(const Instr& instr)
{
    this->_execReadStdFlFloat<float, readFlUIntBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloat64Le(const Instr& instr)
{
    this->_execReadFlFloat<double, readFlUIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloat64Be(const Instr& instr)
{
    this->_execReadFlFloat<double, readFlUIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloatA64Le(const Instr& instr)
{
    this->_execReadStdFlFloat<double, readFlUIntLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlFloatA64Be(const Instr& instr)
{
    this->_execReadStdFlFloat<double, readFlUIntBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumLe(const Instr& instr)
{
    this->_execReadFlEnum<std::int64_t, readFlSIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumBe(const Instr& instr)
{
    this->_execReadFlEnum<std::int64_t, readFlSIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumA8(const Instr& instr)
{
    this->_execReadStdFlEnum<std::int64_t, 8, readFlSInt8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumA16Le(const Instr& instr)
{
    this->_execReadStdFlEnum<std::int64_t, 16, readFlSIntLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumA32Le(const Instr& instr)
{
    this->_execReadStdFlEnum<std::int64_t, 32, readFlSIntLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumA64Le(const Instr& instr)
{
    this->_execReadStdFlEnum<std::int64_t, 64, readFlSIntLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumA16Be(const Instr& instr)
{
    this->_execReadStdFlEnum<std::int64_t, 16, readFlSIntBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumA32Be(const Instr& instr)
{
    this->_execReadStdFlEnum<std::int64_t, 32, readFlSIntBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlSEnumA64Be(const Instr& instr)
{
    this->_execReadStdFlEnum<std::int64_t, 64, readFlSIntBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumLe(const Instr& instr)
{
    this->_execReadFlEnum<std::uint64_t, readFlUIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumBe(const Instr& instr)
{
    this->_execReadFlEnum<std::uint64_t, readFlUIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumA8(const Instr& instr)
{
    this->_execReadStdFlEnum<std::uint64_t, 8, readFlUInt8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumA16Le(const Instr& instr)
{
    this->_execReadStdFlEnum<std::uint64_t, 16, readFlUIntLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumA32Le(const Instr& instr)
{
    this->_execReadStdFlEnum<std::uint64_t, 32, readFlUIntLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumA64Le(const Instr& instr)
{
    this->_execReadStdFlEnum<std::uint64_t, 64, readFlUIntLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumA16Be(const Instr& instr)
{
    this->_execReadStdFlEnum<std::uint64_t, 16, readFlUIntBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumA32Be(const Instr& instr)
{
    this->_execReadStdFlEnum<std::uint64_t, 32, readFlUIntBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlUEnumA64Be(const Instr& instr)
{
    this->_execReadStdFlEnum<std::uint64_t, 64, readFlUIntBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadNtStr(const Instr& instr)
{
    const auto& readNtStrInstr = static_cast<const ReadNtStrInstr&>(instr);

    this->_alignHead(instr);
    this->_setDataElemFromInstr(_pos.elems.ntStrBeginning, readNtStrInstr);
    _pos.elems.ntStrBeginning._dt = &readNtStrInstr.strType();
    this->_updateItCurOffset(_pos.elems.ntStrBeginning);
    _pos.postEndStrState = _pos.state();
    _pos.state(VmState::READ_SUBSTR_UNTIL_NULL);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadScope(const Instr& instr)
{
    const auto& beginReadScopeInstr = static_cast<const BeginReadScopeInstr&>(instr);

    // align now so that the iterator's offset is after any padding
    this->_alignHead(beginReadScopeInstr.align());

    _pos.elems.scopeBeginning._scope = beginReadScopeInstr.scope();
    this->_updateItCurOffset(_pos.elems.scopeBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(beginReadScopeInstr.proc());
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadScope(const Instr& instr)
{
    const auto& endReadScopeInstr = static_cast<const EndReadScopeInstr&>(instr);

    this->_updateItCurOffset(_pos.elems.end);
    _pos.stackPop();
    assert(_pos.state() == VmState::EXEC_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStruct(const Instr& instr)
{
    const auto& beginReadStructInstr = static_cast<const BeginReadStructInstr&>(instr);

    this->_alignHead(instr);
    this->_setDataElemFromInstr(_pos.elems.structBeginning, beginReadStructInstr);
    _pos.elems.structBeginning._dt = &beginReadStructInstr.structType();
    this->_updateItCurOffset(_pos.elems.structBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(beginReadStructInstr.proc());
    _pos.state(VmState::EXEC_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadStruct(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.end);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStaticArray(const Instr& instr)
{
    const auto& beginReadStaticArrayInstr = static_cast<const BeginReadStaticArrayInstr&>(instr);

    _pos.elems.staticArrayBeginning._dt = &beginReadStaticArrayInstr.staticArrayType();
    this->_execBeginReadStaticArrayCommon(instr, _pos.elems.staticArrayBeginning,
                                          VmState::EXEC_ARRAY_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadStaticArray(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.end);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStaticTextArray(const Instr& instr)
{
    const auto& beginReadStaticArrayInstr = static_cast<const BeginReadStaticTextArrayInstr&>(instr);

    _pos.elems.staticTextArrayBeginning._dt = &beginReadStaticArrayInstr.staticTextArrayType();
    this->_execBeginReadStaticArrayCommon(instr, _pos.elems.staticTextArrayBeginning,
                                          VmState::READ_SUBSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadStaticTextArray(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.end);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStaticUuidArray(const Instr& instr)
{
    const auto& beginReadStaticArrayInstr = static_cast<const BeginReadStaticUuidArrayInstr&>(instr);

    _pos.elems.staticArrayBeginning._dt = &beginReadStaticArrayInstr.staticArrayType();
    this->_execBeginReadStaticArrayCommon(instr, _pos.elems.staticArrayBeginning,
                                          VmState::READ_UUID_BYTE);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadDynArray(const Instr& instr)
{
    const auto& beginReadDynArrayInstr = static_cast<const BeginReadDynArrayInstr&>(instr);

    _pos.elems.dynArrayBeginning._dt = &beginReadDynArrayInstr.dynArrayType();
    this->_execBeginReadDynArrayCommon(instr, _pos.elems.dynArrayBeginning,
                                       VmState::EXEC_ARRAY_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadDynArray(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.end);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadDynTextArray(const Instr& instr)
{
    const auto& beginReadDynArrayInstr = static_cast<const BeginReadDynArrayInstr&>(instr);

    _pos.elems.dynTextArrayBeginning._dt = &beginReadDynArrayInstr.dynArrayType();
    this->_execBeginReadDynArrayCommon(instr, _pos.elems.dynTextArrayBeginning,
                                           VmState::READ_SUBSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadDynTextArray(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.end);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadVarSSel(const Instr& instr)
{
    this->_execBeginReadVar<BeginReadVarSSelInstr>(instr, _pos.elems.varSSelBeginning);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadVarUSel(const Instr& instr)
{
    this->_execBeginReadVar<BeginReadVarUSelInstr>(instr, _pos.elems.varUSelBeginning);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadVar(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.end);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execSaveVal(const Instr& instr)
{
    const auto& saveValInstr = static_cast<const SaveValInstr&>(instr);

    _pos.saveVal(saveValInstr.pos());
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktEndDefClkVal(const Instr& instr)
{
    const auto& setPktEndDefClkValInstr = static_cast<const SetPktEndDefClkValInstr&>(instr);

    _pos.elems.pktInfo._endDefClkVal = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execUpdateDefClkVal(const Instr& instr)
{
    const auto& updateDefClkValInstr = static_cast<const UpdateDefClkValInstr&>(instr);
    const auto newVal = _pos.updateDefClkVal(updateDefClkValInstr.len());

    _pos.elems.defClkVal._cycles = newVal;
    this->_updateItCurOffset(_pos.elems.defClkVal);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetCurrentId(const Instr& instr)
{
    _pos.curId = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetDst(const Instr& instr)
{
    const auto& setDstInstr = static_cast<const SetDstInstr&>(instr);
    const auto id = setDstInstr.fixedId() ? *setDstInstr.fixedId() : _pos.curId;
    const auto dstPacketProc = (*_pos.pktProc)[id];

    if (!dstPacketProc) {
        throw UnknownDataStreamTypeDecodingError {
            _pos.headOffsetInElemSeqBits(), id
        };
    }

    _pos.curDsPktProc = dstPacketProc;
    _pos.elems.dsInfo._dst = &dstPacketProc->dst();
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetErt(const Instr& instr)
{
    assert(_pos.curDsPktProc);

    const auto& setErtInstr = static_cast<const SetErtInstr&>(instr);
    const auto id = setErtInstr.fixedId() ? *setErtInstr.fixedId() : _pos.curId;

    assert(_pos.curDsPktProc);

    const auto erProc = (*_pos.curDsPktProc)[id];

    if (!erProc) {
        throw UnknownEventRecordTypeDecodingError {
            _pos.headOffsetInElemSeqBits(), id
        };
    }

    _pos.curErProc = erProc;
    _pos.elems.erInfo._ert = &erProc->ert();
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetDsId(const Instr& instr)
{
    _pos.elems.dsInfo._id = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktOriginIndex(const Instr& instr)
{
    _pos.elems.pktInfo._originIndex = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktTotalLen(const Instr& instr)
{
    const auto pktTotalSizeCandidateBits = _pos.lastIntVal.u;

    if ((pktTotalSizeCandidateBits & 7) != 0) {
        throw ExpectedPacketTotalLengthNotMultipleOf8DecodingError {
            _pos.headOffsetInElemSeqBits(),
            pktTotalSizeCandidateBits
        };
    }

    if (_pos.curExpectedPktContentLenBits != SIZE_UNSET) {
        if (pktTotalSizeCandidateBits < _pos.curExpectedPktContentLenBits) {
            throw ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError {
                _pos.headOffsetInElemSeqBits(),
                pktTotalSizeCandidateBits,
                _pos.curExpectedPktContentLenBits
            };
        }
    }

    if (pktTotalSizeCandidateBits < _pos.headOffsetInCurPktBits) {
        throw ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError {
            _pos.headOffsetInElemSeqBits(),
            pktTotalSizeCandidateBits,
            _pos.headOffsetInCurPktBits
        };
    }

    _pos.curExpectedPktTotalLenBits = pktTotalSizeCandidateBits;

    if (_pos.curExpectedPktContentLenBits == SIZE_UNSET) {
        _pos.curExpectedPktContentLenBits = _pos.curExpectedPktTotalLenBits;
    }

    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktContentLen(const Instr& instr)
{
    const auto pktContentSizeCandidateBits = _pos.lastIntVal.u;

    if (_pos.curExpectedPktTotalLenBits != SIZE_UNSET) {
        if (_pos.curExpectedPktTotalLenBits < pktContentSizeCandidateBits) {
            throw ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError {
                _pos.headOffsetInElemSeqBits(),
                _pos.curExpectedPktTotalLenBits,
                pktContentSizeCandidateBits
            };
        }
    }

    if (pktContentSizeCandidateBits < _pos.headOffsetInCurPktBits) {
        throw ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError {
            _pos.headOffsetInElemSeqBits(),
            pktContentSizeCandidateBits,
            _pos.headOffsetInCurPktBits
        };
    }

    _pos.curExpectedPktContentLenBits = pktContentSizeCandidateBits;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetDsInfo(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.dsInfo);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPktInfo(const Instr& instr)
{
    _pos.elems.pktInfo._expectedTotalLen = boost::none;
    _pos.elems.pktInfo._expectedContentLen = boost::none;

    if (_pos.curExpectedPktTotalLenBits != SIZE_MAX) {
        _pos.elems.pktInfo._expectedTotalLen = _pos.curExpectedPktTotalLenBits;
    }

    if (_pos.curExpectedPktContentLenBits != SIZE_MAX) {
        _pos.elems.pktInfo._expectedContentLen = _pos.curExpectedPktContentLenBits;
    }
    this->_updateItCurOffset(_pos.elems.pktInfo);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetErInfo(const Instr& instr)
{
    this->_updateItCurOffset(_pos.elems.erInfo);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPktMagicNumber(const Instr& instr)
{
    _pos.elems.pktMagicNumber._val = _pos.lastIntVal.u;
    this->_updateItCurOffset(_pos.elems.pktMagicNumber);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execEndPktPreambleProc(const Instr& instr)
{
    // after packet header
    _pos.stackPop();
    assert(_pos.stack.empty());

    if (_pos.curDsPktProc) {
        _pos.loadNewProc(_pos.curDsPktProc->pktPreambleProc());
        return _ExecReaction::EXEC_CUR_INSTR;
    } else {
        _pos.state(VmState::END_PKT_CONTENT);
        return _ExecReaction::CHANGE_STATE;
    }
}

Vm::_ExecReaction Vm::_execEndDsPktPreambleProc(const Instr& instr)
{
    // after packet context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curDsPktProc);
    _pos.state(VmState::BEGIN_ER);
    return _ExecReaction::CHANGE_STATE;
}

Vm::_ExecReaction Vm::_execEndDsErPreambleProc(const Instr& instr)
{
    // after second event record context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curErProc);
    _pos.loadNewProc(_pos.curErProc->proc());
    return _ExecReaction::EXEC_CUR_INSTR;
}

Vm::_ExecReaction Vm::_execEndErProc(const Instr& instr)
{
    // after event record payload
    _pos.stackPop();
    assert(_pos.stack.empty());
    _pos.state(VmState::END_ER);
    return _ExecReaction::CHANGE_STATE;
}

} // namespace yactfr
} // namespace internal
