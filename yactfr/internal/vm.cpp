/*
 * Copyright (C) 2017-2024 Philippe Proulx <eepp.ca>
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
    nextState = other.nextState;
    lastFlBitArrayBo = other.lastFlBitArrayBo;
    remBitsToSkip = other.remBitsToSkip;
    lastIntVal = other.lastIntVal;
    curVlIntLenBits = other.curVlIntLenBits;
    curVlIntElem = &this->elemFromOther(other, *other.curVlIntElem);
    curId = other.curId;
    ntStrCuBuf = other.ntStrCuBuf;
    pktProc = other.pktProc;
    curDsPktProc = other.curDsPktProc;
    curErProc = other.curErProc;
    metadataStreamUuid = other.metadataStreamUuid;
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

void Vm::setFromOther(const Vm& other, ElementSequenceIterator& it)
{
    assert(_dataSrcFactory == other._dataSrcFactory);
    _it = &it;
    _pos = other._pos;
    this->_resetBuffer();
}

void Vm::_initExecFuncs() noexcept
{
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_LE>(&Vm::_execReadFlBitArrayLe);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_BE>(&Vm::_execReadFlBitArrayBe);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_A8>(&Vm::_execReadFlBitArrayA8);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_A16_LE>(&Vm::_execReadFlBitArrayA16Le);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_A32_LE>(&Vm::_execReadFlBitArrayA32Le);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_A64_LE>(&Vm::_execReadFlBitArrayA64Le);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_A16_BE>(&Vm::_execReadFlBitArrayA16Be);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_A32_BE>(&Vm::_execReadFlBitArrayA32Be);
    this->_initExecFunc<Instr::Kind::READ_FL_BIT_ARRAY_A64_BE>(&Vm::_execReadFlBitArrayA64Be);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_LE>(&Vm::_execReadFlBoolLe);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_BE>(&Vm::_execReadFlBoolBe);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_A8>(&Vm::_execReadFlBoolA8);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_A16_LE>(&Vm::_execReadFlBoolA16Le);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_A32_LE>(&Vm::_execReadFlBoolA32Le);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_A64_LE>(&Vm::_execReadFlBoolA64Le);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_A16_BE>(&Vm::_execReadFlBoolA16Be);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_A32_BE>(&Vm::_execReadFlBoolA32Be);
    this->_initExecFunc<Instr::Kind::READ_FL_BOOL_A64_BE>(&Vm::_execReadFlBoolA64Be);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_LE>(&Vm::_execReadFlSIntLe);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_BE>(&Vm::_execReadFlSIntBe);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_A8>(&Vm::_execReadFlSIntA8);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_A16_LE>(&Vm::_execReadFlSIntA16Le);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_A32_LE>(&Vm::_execReadFlSIntA32Le);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_A64_LE>(&Vm::_execReadFlSIntA64Le);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_A16_BE>(&Vm::_execReadFlSIntA16Be);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_A32_BE>(&Vm::_execReadFlSIntA32Be);
    this->_initExecFunc<Instr::Kind::READ_FL_SINT_A64_BE>(&Vm::_execReadFlSIntA64Be);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_LE>(&Vm::_execReadFlUIntLe);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_BE>(&Vm::_execReadFlUIntBe);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_A8>(&Vm::_execReadFlUIntA8);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_A16_LE>(&Vm::_execReadFlUIntA16Le);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_A32_LE>(&Vm::_execReadFlUIntA32Le);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_A64_LE>(&Vm::_execReadFlUIntA64Le);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_A16_BE>(&Vm::_execReadFlUIntA16Be);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_A32_BE>(&Vm::_execReadFlUIntA32Be);
    this->_initExecFunc<Instr::Kind::READ_FL_UINT_A64_BE>(&Vm::_execReadFlUIntA64Be);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_32_LE>(&Vm::_execReadFlFloat32Le);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_32_BE>(&Vm::_execReadFlFloat32Be);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_A32_LE>(&Vm::_execReadFlFloatA32Le);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_A32_BE>(&Vm::_execReadFlFloatA32Be);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_64_LE>(&Vm::_execReadFlFloat64Le);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_64_BE>(&Vm::_execReadFlFloat64Be);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_A64_LE>(&Vm::_execReadFlFloatA64Le);
    this->_initExecFunc<Instr::Kind::READ_FL_FLOAT_A64_BE>(&Vm::_execReadFlFloatA64Be);
    this->_initExecFunc<Instr::Kind::READ_VL_UINT>(&Vm::_execReadVlUInt);
    this->_initExecFunc<Instr::Kind::READ_VL_SINT>(&Vm::_execReadVlSInt);
    this->_initExecFunc<Instr::Kind::READ_NT_STR_UTF_8>(&Vm::_execReadNtStrUtf8);
    this->_initExecFunc<Instr::Kind::READ_NT_STR_UTF_16>(&Vm::_execReadNtStrUtf16);
    this->_initExecFunc<Instr::Kind::READ_NT_STR_UTF_32>(&Vm::_execReadNtStrUtf32);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_SCOPE>(&Vm::_execBeginReadScope);
    this->_initExecFunc<Instr::Kind::END_READ_SCOPE>(&Vm::_execEndReadScope);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_STRUCT>(&Vm::_execBeginReadStruct);
    this->_initExecFunc<Instr::Kind::END_READ_STRUCT>(&Vm::_execEndReadStruct);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_SL_ARRAY>(&Vm::_execBeginReadSlArray);
    this->_initExecFunc<Instr::Kind::END_READ_SL_ARRAY>(&Vm::_execEndReadSlArray);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_SL_UUID_ARRAY>(&Vm::_execBeginReadSlUuidArray);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_SL_STR>(&Vm::_execBeginReadSlStr);
    this->_initExecFunc<Instr::Kind::END_READ_SL_STR>(&Vm::_execEndReadSlStr);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_SL_BLOB>(&Vm::_execBeginReadSlBlob);
    this->_initExecFunc<Instr::Kind::END_READ_SL_BLOB>(&Vm::_execEndReadSlBlob);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_SL_UUID_BLOB>(&Vm::_execBeginReadSlUuidBlob);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_DL_ARRAY>(&Vm::_execBeginReadDlArray);
    this->_initExecFunc<Instr::Kind::END_READ_DL_ARRAY>(&Vm::_execEndReadDlArray);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_DL_STR>(&Vm::_execBeginReadDlStr);
    this->_initExecFunc<Instr::Kind::END_READ_DL_STR>(&Vm::_execEndReadDlStr);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_DL_BLOB>(&Vm::_execBeginReadDlBlob);
    this->_initExecFunc<Instr::Kind::END_READ_DL_BLOB>(&Vm::_execEndReadDlBlob);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_VAR_SINT_SEL>(&Vm::_execBeginReadVarSIntSel);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_VAR_UINT_SEL>(&Vm::_execBeginReadVarUIntSel);
    this->_initExecFunc<Instr::Kind::END_READ_VAR_UINT_SEL>(&Vm::_execEndReadVarUIntSel);
    this->_initExecFunc<Instr::Kind::END_READ_VAR_SINT_SEL>(&Vm::_execEndReadVarSIntSel);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_OPT_BOOL_SEL>(&Vm::_execBeginReadOptBoolSel);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_OPT_SINT_SEL>(&Vm::_execBeginReadOptSIntSel);
    this->_initExecFunc<Instr::Kind::BEGIN_READ_OPT_UINT_SEL>(&Vm::_execBeginReadOptUIntSel);
    this->_initExecFunc<Instr::Kind::END_READ_OPT_BOOL_SEL>(&Vm::_execEndReadOptBoolSel);
    this->_initExecFunc<Instr::Kind::END_READ_OPT_UINT_SEL>(&Vm::_execEndReadOptUIntSel);
    this->_initExecFunc<Instr::Kind::END_READ_OPT_SINT_SEL>(&Vm::_execEndReadOptSIntSel);
    this->_initExecFunc<Instr::Kind::SAVE_VAL>(&Vm::_execSaveVal);
    this->_initExecFunc<Instr::Kind::SET_PKT_END_DEF_CLK_VAL>(&Vm::_execSetPktEndDefClkVal);
    this->_initExecFunc<Instr::Kind::UPDATE_DEF_CLK_VAL_FL>(&Vm::_execUpdateDefClkValFl);
    this->_initExecFunc<Instr::Kind::UPDATE_DEF_CLK_VAL>(&Vm::_execUpdateDefClkVal);
    this->_initExecFunc<Instr::Kind::SET_CUR_ID>(&Vm::_execSetCurrentId);
    this->_initExecFunc<Instr::Kind::SET_DST>(&Vm::_execSetDst);
    this->_initExecFunc<Instr::Kind::SET_ERT>(&Vm::_execSetErt);
    this->_initExecFunc<Instr::Kind::SET_DS_ID>(&Vm::_execSetDsId);
    this->_initExecFunc<Instr::Kind::SET_PKT_SEQ_NUM>(&Vm::_execSetPktSeqNum);
    this->_initExecFunc<Instr::Kind::SET_PKT_DISC_ER_COUNTER_SNAP>(&Vm::_execSetPktDiscErCounterSnap);
    this->_initExecFunc<Instr::Kind::SET_PKT_TOTAL_LEN>(&Vm::_execSetPktTotalLen);
    this->_initExecFunc<Instr::Kind::SET_PKT_CONTENT_LEN>(&Vm::_execSetPktContentLen);
    this->_initExecFunc<Instr::Kind::SET_PKT_MAGIC_NUMBER>(&Vm::_execSetPktMagicNumber);
    this->_initExecFunc<Instr::Kind::END_PKT_PREAMBLE_PROC>(&Vm::_execEndPktPreambleProc);
    this->_initExecFunc<Instr::Kind::END_DS_PKT_PREAMBLE_PROC>(&Vm::_execEndDsPktPreambleProc);
    this->_initExecFunc<Instr::Kind::END_DS_ER_PREAMBLE_PROC>(&Vm::_execEndDsErPreambleProc);
    this->_initExecFunc<Instr::Kind::END_ER_PROC>(&Vm::_execEndErProc);
    this->_initExecFunc<Instr::Kind::SET_DS_INFO>(&Vm::_execSetDsInfo);
    this->_initExecFunc<Instr::Kind::SET_PKT_INFO>(&Vm::_execSetPktInfo);
    this->_initExecFunc<Instr::Kind::SET_ER_INFO>(&Vm::_execSetErInfo);
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

Vm::_ExecReaction Vm::_execReadFlBitArrayLe(const Instr& instr)
{
    this->_execReadFlBitArray<readFlUIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayBe(const Instr& instr)
{
    this->_execReadFlBitArray<readFlUIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayA8(const Instr& instr)
{
    this->_execReadStdFlBitArray<8, readFlUInt8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayA16Le(const Instr& instr)
{
    this->_execReadStdFlBitArray<16, readFlUIntLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayA32Le(const Instr& instr)
{
    this->_execReadStdFlBitArray<32, readFlUIntLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayA64Le(const Instr& instr)
{
    this->_execReadStdFlBitArray<64, readFlUIntLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayA16Be(const Instr& instr)
{
    this->_execReadStdFlBitArray<16, readFlUIntBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayA32Be(const Instr& instr)
{
    this->_execReadStdFlBitArray<32, readFlUIntBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBitArrayA64Be(const Instr& instr)
{
    this->_execReadStdFlBitArray<64, readFlUIntBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolLe(const Instr& instr)
{
    this->_execReadFlBool<readFlUIntLeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolBe(const Instr& instr)
{
    this->_execReadFlBool<readFlUIntBeFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolA8(const Instr& instr)
{
    this->_execReadStdFlBool<8, readFlUInt8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolA16Le(const Instr& instr)
{
    this->_execReadStdFlBool<16, readFlUIntLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolA32Le(const Instr& instr)
{
    this->_execReadStdFlBool<32, readFlUIntLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolA64Le(const Instr& instr)
{
    this->_execReadStdFlBool<64, readFlUIntLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolA16Be(const Instr& instr)
{
    this->_execReadStdFlBool<16, readFlUIntBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolA32Be(const Instr& instr)
{
    this->_execReadStdFlBool<32, readFlUIntBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFlBoolA64Be(const Instr& instr)
{
    this->_execReadStdFlBool<64, readFlUIntBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
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

Vm::_ExecReaction Vm::_execReadVlUInt(const Instr& instr)
{
    return this->_execReadVlIntCommon(instr, _pos.elems.vlUInt, VmState::CONTINUE_READ_VL_UINT);
}

Vm::_ExecReaction Vm::_execReadVlSInt(const Instr& instr)
{
    return this->_execReadVlIntCommon(instr, _pos.elems.vlSInt, VmState::CONTINUE_READ_VL_SINT);
}

Vm::_ExecReaction Vm::_execReadNtStrCommon(const Instr& instr, const VmState state)
{
    this->_alignHead(instr);
    this->_setDataElemFromInstr(_pos.elems.ntStrBeginning, instr);
    this->_setDataElemFromInstr(_pos.elems.ntStrEnd, instr);
    this->_updateItForUser(_pos.elems.ntStrBeginning);
    _pos.nextState = _pos.state();
    _pos.state(state);
    _pos.ntStrCuBuf.index = 0;
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadNtStrUtf8(const Instr& instr)
{
    return this->_execReadNtStrCommon(instr, VmState::READ_UTF_8_DATA_UNTIL_NULL);
}

Vm::_ExecReaction Vm::_execReadNtStrUtf16(const Instr& instr)
{
    return this->_execReadNtStrCommon(instr, VmState::READ_UTF_16_DATA_UNTIL_NULL);
}

Vm::_ExecReaction Vm::_execReadNtStrUtf32(const Instr& instr)
{
    return this->_execReadNtStrCommon(instr, VmState::READ_UTF_32_DATA_UNTIL_NULL);
}

Vm::_ExecReaction Vm::_execBeginReadScope(const Instr& instr)
{
    const auto& beginReadScopeInstr = static_cast<const BeginReadScopeInstr&>(instr);

    // align now so that the offset of the iterator is _after_ any padding
    this->_alignHead(beginReadScopeInstr.align());

    _pos.elems.scopeBeginning._scope = beginReadScopeInstr.scope();
    this->_updateItForUser(_pos.elems.scopeBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(&beginReadScopeInstr.proc());
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadScope(const Instr& instr)
{
    _pos.elems.scopeEnd._scope = static_cast<const EndReadScopeInstr&>(instr).scope();
    this->_updateItForUser(_pos.elems.scopeEnd);
    _pos.stackPop();
    assert(_pos.state() == VmState::EXEC_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStruct(const Instr& instr)
{
    const auto& beginReadStructInstr = static_cast<const BeginReadStructInstr&>(instr);

    this->_alignHead(instr);
    this->_setDataElemFromInstr(_pos.elems.structBeginning, instr);
    this->_updateItForUser(_pos.elems.structBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(&beginReadStructInstr.proc());
    _pos.state(VmState::EXEC_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadStruct(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.structEnd, instr);
    this->_updateItForUser(_pos.elems.structEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadSlArray(const Instr& instr)
{
    return this->_execBeginReadSlArray(instr, VmState::EXEC_ARRAY_INSTR);
}

Vm::_ExecReaction Vm::_execEndReadSlArray(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.slArrayEnd, instr);
    this->_updateItForUser(_pos.elems.slArrayEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadSlStr(const Instr& instr)
{
    const auto& beginReadSlStrInstr = static_cast<const BeginReadSlStrInstr&>(instr);

    _pos.elems.slStrBeginning._maxLen = beginReadSlStrInstr.maxLen();
    this->_execBeginReadStaticData(beginReadSlStrInstr, _pos.elems.slStrBeginning,
                                   beginReadSlStrInstr.maxLen(), nullptr, VmState::READ_RAW_DATA);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadSlStr(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.slStrEnd, instr);
    this->_updateItForUser(_pos.elems.slStrEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadSlUuidArray(const Instr& instr)
{
    return this->_execBeginReadSlArray(instr, VmState::READ_UUID_BYTE);
}

Vm::_ExecReaction Vm::_execBeginReadDlArray(const Instr& instr)
{
    const auto& beginReadDlArrayInstr = static_cast<const BeginReadDlArrayInstr&>(instr);

    this->_execBeginReadDynData(beginReadDlArrayInstr, _pos.elems.dlArrayBeginning,
                                beginReadDlArrayInstr.lenPos(), _pos.elems.dlArrayBeginning._len,
                                &beginReadDlArrayInstr.proc(), VmState::EXEC_ARRAY_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadDlArray(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.dlArrayEnd, instr);
    this->_updateItForUser(_pos.elems.dlArrayEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadDlStr(const Instr& instr)
{
    const auto& beginReadDlStrInstr = static_cast<const BeginReadDlStrInstr&>(instr);

    this->_execBeginReadDynData(beginReadDlStrInstr, _pos.elems.dlStrBeginning,
                                beginReadDlStrInstr.maxLenPos(), _pos.elems.dlStrBeginning._maxLen,
                                nullptr, VmState::READ_RAW_DATA);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadDlStr(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.dlStrEnd, instr);
    this->_updateItForUser(_pos.elems.dlStrEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadSlBlob(const Instr& instr)
{
    return this->_execBeginReadSlBlob(instr, VmState::READ_RAW_DATA);
}

Vm::_ExecReaction Vm::_execBeginReadSlUuidBlob(const Instr& instr)
{
    return this->_execBeginReadSlBlob(instr, VmState::READ_UUID_BLOB_SECTION);
}

Vm::_ExecReaction Vm::_execEndReadSlBlob(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.slBlobEnd, instr);
    this->_updateItForUser(_pos.elems.slBlobEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadDlBlob(const Instr& instr)
{
    const auto& beginReadDlBlobInstr = static_cast<const BeginReadDlBlobInstr&>(instr);

    this->_execBeginReadDynData(beginReadDlBlobInstr, _pos.elems.dlBlobBeginning,
                                beginReadDlBlobInstr.lenPos(), _pos.elems.dlBlobBeginning._len,
                                nullptr, VmState::READ_RAW_DATA);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadDlBlob(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.dlBlobEnd, instr);
    this->_updateItForUser(_pos.elems.dlBlobEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadVarSIntSel(const Instr& instr)
{
    this->_execBeginReadVar<BeginReadVarSIntSelInstr>(instr, _pos.elems.varSIntSelBeginning);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadVarUIntSel(const Instr& instr)
{
    this->_execBeginReadVar<BeginReadVarUIntSelInstr>(instr, _pos.elems.varUIntSelBeginning);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadOptBoolSel(const Instr& instr)
{
    this->_execBeginReadOpt<BeginReadOptBoolSelInstr, bool>(instr, _pos.elems.optBoolSelBeginning);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadOptSIntSel(const Instr& instr)
{
    const auto selVal = this->_execBeginReadOpt<BeginReadOptSIntSelInstr,
                                                long long>(instr, _pos.elems.optSIntSelBeginning);

    _pos.elems.optSIntSelBeginning._selVal = selVal;
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadOptUIntSel(const Instr& instr)
{
    const auto selVal = this->_execBeginReadOpt<BeginReadOptUIntSelInstr,
                                                unsigned long long>(instr,
                                                                    _pos.elems.optUIntSelBeginning);

    _pos.elems.optUIntSelBeginning._selVal = selVal;
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadVarUIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.varUIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.varUIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadVarSIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.varSIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.varSIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadOptBoolSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.optBoolSelEnd, instr);
    this->_updateItForUser(_pos.elems.optBoolSelEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadOptUIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.optUIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.optUIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadOptSIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.optSIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.optSIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execSaveVal(const Instr& instr)
{
    const auto& saveValInstr = static_cast<const SaveValInstr&>(instr);

    _pos.saveVal(saveValInstr.pos());
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktEndDefClkVal(const Instr&)
{
    _pos.elems.pktInfo._endDefClkVal = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execUpdateDefClkValFl(const Instr& instr)
{
    const auto& updateDefClkValFlInstr = static_cast<const UpdateDefClkValFlInstr&>(instr);

    return this->_execUpdateDefClkValCommon(updateDefClkValFlInstr.len());
}

Vm::_ExecReaction Vm::_execUpdateDefClkVal(const Instr&)
{
    return this->_execUpdateDefClkValCommon(_pos.lastIntVal.u);
}

Vm::_ExecReaction Vm::_execSetCurrentId(const Instr&)
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

Vm::_ExecReaction Vm::_execSetDsId(const Instr&)
{
    _pos.elems.dsInfo._id = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktSeqNum(const Instr&)
{
    _pos.elems.pktInfo._seqNum = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktDiscErCounterSnap(const Instr&)
{
    _pos.elems.pktInfo._discErCounterSnap = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPktTotalLen(const Instr&)
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

Vm::_ExecReaction Vm::_execSetPktContentLen(const Instr&)
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

Vm::_ExecReaction Vm::_execSetDsInfo(const Instr&)
{
    this->_updateItForUser(_pos.elems.dsInfo);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPktInfo(const Instr&)
{
    _pos.elems.pktInfo._expectedTotalLen = boost::none;
    _pos.elems.pktInfo._expectedContentLen = boost::none;

    if (_pos.curExpectedPktTotalLenBits != SIZE_MAX) {
        _pos.elems.pktInfo._expectedTotalLen = _pos.curExpectedPktTotalLenBits;
    }

    if (_pos.curExpectedPktContentLenBits != SIZE_MAX) {
        _pos.elems.pktInfo._expectedContentLen = _pos.curExpectedPktContentLenBits;
    }
    this->_updateItForUser(_pos.elems.pktInfo);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetErInfo(const Instr&)
{
    this->_updateItForUser(_pos.elems.erInfo);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPktMagicNumber(const Instr&)
{
    _pos.elems.pktMagicNumber._val = _pos.lastIntVal.u;
    this->_updateItForUser(_pos.elems.pktMagicNumber);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execEndPktPreambleProc(const Instr&)
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

Vm::_ExecReaction Vm::_execEndDsPktPreambleProc(const Instr&)
{
    // after packet context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curDsPktProc);

    if (_pos.curDsPktProc->dst().eventRecordTypes().empty()) {
        _pos.state(VmState::END_PKT_CONTENT);
    } else {
        _pos.state(VmState::BEGIN_ER);
    }

    return _ExecReaction::CHANGE_STATE;
}

Vm::_ExecReaction Vm::_execEndDsErPreambleProc(const Instr&)
{
    // after second event record context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curErProc);
    _pos.loadNewProc(_pos.curErProc->proc());
    return _ExecReaction::EXEC_CUR_INSTR;
}

Vm::_ExecReaction Vm::_execEndErProc(const Instr&)
{
    // after event record payload
    _pos.stackPop();
    assert(_pos.stack.empty());
    _pos.state(VmState::END_ER);
    return _ExecReaction::CHANGE_STATE;
}

} // namespace yactfr
} // namespace internal
