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

constexpr Size sizeUnset = std::numeric_limits<Size>::max();
constexpr std::uint64_t savedValUnset = std::numeric_limits<std::uint64_t>::max();

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
    savedVals.resize(pktProc->savedValsCount(), sizeUnset);
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
    this->_initExecFunc<Instr::Kind::BeginReadDlArray>(&Vm::_execBeginReadDlArray);
    this->_initExecFunc<Instr::Kind::BeginReadDlBlob>(&Vm::_execBeginReadDlBlob);
    this->_initExecFunc<Instr::Kind::BeginReadDlStr>(&Vm::_execBeginReadDlStr);
    this->_initExecFunc<Instr::Kind::BeginReadOptBoolSel>(&Vm::_execBeginReadOptBoolSel);
    this->_initExecFunc<Instr::Kind::BeginReadOptSIntSel>(&Vm::_execBeginReadOptSIntSel);
    this->_initExecFunc<Instr::Kind::BeginReadOptUIntSel>(&Vm::_execBeginReadOptUIntSel);
    this->_initExecFunc<Instr::Kind::BeginReadScope>(&Vm::_execBeginReadScope);
    this->_initExecFunc<Instr::Kind::BeginReadSlArray>(&Vm::_execBeginReadSlArray);
    this->_initExecFunc<Instr::Kind::BeginReadSlBlob>(&Vm::_execBeginReadSlBlob);
    this->_initExecFunc<Instr::Kind::BeginReadSlStr>(&Vm::_execBeginReadSlStr);
    this->_initExecFunc<Instr::Kind::BeginReadSlUuidArray>(&Vm::_execBeginReadSlUuidArray);
    this->_initExecFunc<Instr::Kind::BeginReadSlUuidBlob>(&Vm::_execBeginReadSlUuidBlob);
    this->_initExecFunc<Instr::Kind::BeginReadStruct>(&Vm::_execBeginReadStruct);
    this->_initExecFunc<Instr::Kind::BeginReadVarSIntSel>(&Vm::_execBeginReadVarSIntSel);
    this->_initExecFunc<Instr::Kind::BeginReadVarUIntSel>(&Vm::_execBeginReadVarUIntSel);
    this->_initExecFunc<Instr::Kind::EndDsErPreambleProc>(&Vm::_execEndDsErPreambleProc);
    this->_initExecFunc<Instr::Kind::EndDsPktPreambleProc>(&Vm::_execEndDsPktPreambleProc);
    this->_initExecFunc<Instr::Kind::EndErProc>(&Vm::_execEndErProc);
    this->_initExecFunc<Instr::Kind::EndPktPreambleProc>(&Vm::_execEndPktPreambleProc);
    this->_initExecFunc<Instr::Kind::EndReadDlArray>(&Vm::_execEndReadDlArray);
    this->_initExecFunc<Instr::Kind::EndReadDlBlob>(&Vm::_execEndReadDlBlob);
    this->_initExecFunc<Instr::Kind::EndReadDlStr>(&Vm::_execEndReadDlStr);
    this->_initExecFunc<Instr::Kind::EndReadOptBoolSel>(&Vm::_execEndReadOptBoolSel);
    this->_initExecFunc<Instr::Kind::EndReadOptSIntSel>(&Vm::_execEndReadOptSIntSel);
    this->_initExecFunc<Instr::Kind::EndReadOptUIntSel>(&Vm::_execEndReadOptUIntSel);
    this->_initExecFunc<Instr::Kind::EndReadScope>(&Vm::_execEndReadScope);
    this->_initExecFunc<Instr::Kind::EndReadSlArray>(&Vm::_execEndReadSlArray);
    this->_initExecFunc<Instr::Kind::EndReadSlBlob>(&Vm::_execEndReadSlBlob);
    this->_initExecFunc<Instr::Kind::EndReadSlStr>(&Vm::_execEndReadSlStr);
    this->_initExecFunc<Instr::Kind::EndReadStruct>(&Vm::_execEndReadStruct);
    this->_initExecFunc<Instr::Kind::EndReadVarSIntSel>(&Vm::_execEndReadVarSIntSel);
    this->_initExecFunc<Instr::Kind::EndReadVarUIntSel>(&Vm::_execEndReadVarUIntSel);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA16Be>(&Vm::_execReadFlBitArrayA16Be);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA16BeRev>(&Vm::_execReadFlBitArrayA16BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA16Le>(&Vm::_execReadFlBitArrayA16Le);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA16LeRev>(&Vm::_execReadFlBitArrayA16LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA32Be>(&Vm::_execReadFlBitArrayA32Be);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA32BeRev>(&Vm::_execReadFlBitArrayA32BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA32Le>(&Vm::_execReadFlBitArrayA32Le);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA32LeRev>(&Vm::_execReadFlBitArrayA32LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA64Be>(&Vm::_execReadFlBitArrayA64Be);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA64BeRev>(&Vm::_execReadFlBitArrayA64BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA64Le>(&Vm::_execReadFlBitArrayA64Le);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA64LeRev>(&Vm::_execReadFlBitArrayA64LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA8>(&Vm::_execReadFlBitArrayA8);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayA8Rev>(&Vm::_execReadFlBitArrayA8Rev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayBe>(&Vm::_execReadFlBitArrayBe);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayBeRev>(&Vm::_execReadFlBitArrayBeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayLe>(&Vm::_execReadFlBitArrayLe);
    this->_initExecFunc<Instr::Kind::ReadFlBitArrayLeRev>(&Vm::_execReadFlBitArrayLeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA16Be>(&Vm::_execReadFlBitMapA16Be);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA16BeRev>(&Vm::_execReadFlBitMapA16BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA16Le>(&Vm::_execReadFlBitMapA16Le);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA16LeRev>(&Vm::_execReadFlBitMapA16LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA32Be>(&Vm::_execReadFlBitMapA32Be);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA32BeRev>(&Vm::_execReadFlBitMapA32BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA32Le>(&Vm::_execReadFlBitMapA32Le);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA32LeRev>(&Vm::_execReadFlBitMapA32LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA64Be>(&Vm::_execReadFlBitMapA64Be);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA64BeRev>(&Vm::_execReadFlBitMapA64BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA64Le>(&Vm::_execReadFlBitMapA64Le);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA64LeRev>(&Vm::_execReadFlBitMapA64LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA8>(&Vm::_execReadFlBitMapA8);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapA8Rev>(&Vm::_execReadFlBitMapA8Rev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapBe>(&Vm::_execReadFlBitMapBe);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapBeRev>(&Vm::_execReadFlBitMapBeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapLe>(&Vm::_execReadFlBitMapLe);
    this->_initExecFunc<Instr::Kind::ReadFlBitMapLeRev>(&Vm::_execReadFlBitMapLeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA16Be>(&Vm::_execReadFlBoolA16Be);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA16BeRev>(&Vm::_execReadFlBoolA16BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA16Le>(&Vm::_execReadFlBoolA16Le);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA16LeRev>(&Vm::_execReadFlBoolA16LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA32Be>(&Vm::_execReadFlBoolA32Be);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA32BeRev>(&Vm::_execReadFlBoolA32BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA32Le>(&Vm::_execReadFlBoolA32Le);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA32LeRev>(&Vm::_execReadFlBoolA32LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA64Be>(&Vm::_execReadFlBoolA64Be);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA64BeRev>(&Vm::_execReadFlBoolA64BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA64Le>(&Vm::_execReadFlBoolA64Le);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA64LeRev>(&Vm::_execReadFlBoolA64LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA8>(&Vm::_execReadFlBoolA8);
    this->_initExecFunc<Instr::Kind::ReadFlBoolA8Rev>(&Vm::_execReadFlBoolA8Rev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolBe>(&Vm::_execReadFlBoolBe);
    this->_initExecFunc<Instr::Kind::ReadFlBoolBeRev>(&Vm::_execReadFlBoolBeRev);
    this->_initExecFunc<Instr::Kind::ReadFlBoolLe>(&Vm::_execReadFlBoolLe);
    this->_initExecFunc<Instr::Kind::ReadFlBoolLeRev>(&Vm::_execReadFlBoolLeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloat32Be>(&Vm::_execReadFlFloat32Be);
    this->_initExecFunc<Instr::Kind::ReadFlFloat32BeRev>(&Vm::_execReadFlFloat32BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloat32Le>(&Vm::_execReadFlFloat32Le);
    this->_initExecFunc<Instr::Kind::ReadFlFloat32LeRev>(&Vm::_execReadFlFloat32LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloat64Be>(&Vm::_execReadFlFloat64Be);
    this->_initExecFunc<Instr::Kind::ReadFlFloat64BeRev>(&Vm::_execReadFlFloat64BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloat64Le>(&Vm::_execReadFlFloat64Le);
    this->_initExecFunc<Instr::Kind::ReadFlFloat64LeRev>(&Vm::_execReadFlFloat64LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA32Be>(&Vm::_execReadFlFloatA32Be);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA32BeRev>(&Vm::_execReadFlFloatA32BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA32Le>(&Vm::_execReadFlFloatA32Le);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA32LeRev>(&Vm::_execReadFlFloatA32LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA64Be>(&Vm::_execReadFlFloatA64Be);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA64BeRev>(&Vm::_execReadFlFloatA64BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA64Le>(&Vm::_execReadFlFloatA64Le);
    this->_initExecFunc<Instr::Kind::ReadFlFloatA64LeRev>(&Vm::_execReadFlFloatA64LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA16Be>(&Vm::_execReadFlSIntA16Be);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA16BeRev>(&Vm::_execReadFlSIntA16BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA16Le>(&Vm::_execReadFlSIntA16Le);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA16LeRev>(&Vm::_execReadFlSIntA16LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA32Be>(&Vm::_execReadFlSIntA32Be);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA32BeRev>(&Vm::_execReadFlSIntA32BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA32Le>(&Vm::_execReadFlSIntA32Le);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA32LeRev>(&Vm::_execReadFlSIntA32LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA64Be>(&Vm::_execReadFlSIntA64Be);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA64BeRev>(&Vm::_execReadFlSIntA64BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA64Le>(&Vm::_execReadFlSIntA64Le);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA64LeRev>(&Vm::_execReadFlSIntA64LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA8>(&Vm::_execReadFlSIntA8);
    this->_initExecFunc<Instr::Kind::ReadFlSIntA8Rev>(&Vm::_execReadFlSIntA8Rev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntBe>(&Vm::_execReadFlSIntBe);
    this->_initExecFunc<Instr::Kind::ReadFlSIntBeRev>(&Vm::_execReadFlSIntBeRev);
    this->_initExecFunc<Instr::Kind::ReadFlSIntLe>(&Vm::_execReadFlSIntLe);
    this->_initExecFunc<Instr::Kind::ReadFlSIntLeRev>(&Vm::_execReadFlSIntLeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA16Be>(&Vm::_execReadFlUIntA16Be);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA16BeRev>(&Vm::_execReadFlUIntA16BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA16Le>(&Vm::_execReadFlUIntA16Le);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA16LeRev>(&Vm::_execReadFlUIntA16LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA32Be>(&Vm::_execReadFlUIntA32Be);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA32BeRev>(&Vm::_execReadFlUIntA32BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA32Le>(&Vm::_execReadFlUIntA32Le);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA32LeRev>(&Vm::_execReadFlUIntA32LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA64Be>(&Vm::_execReadFlUIntA64Be);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA64BeRev>(&Vm::_execReadFlUIntA64BeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA64Le>(&Vm::_execReadFlUIntA64Le);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA64LeRev>(&Vm::_execReadFlUIntA64LeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA8>(&Vm::_execReadFlUIntA8);
    this->_initExecFunc<Instr::Kind::ReadFlUIntA8Rev>(&Vm::_execReadFlUIntA8Rev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntBe>(&Vm::_execReadFlUIntBe);
    this->_initExecFunc<Instr::Kind::ReadFlUIntBeRev>(&Vm::_execReadFlUIntBeRev);
    this->_initExecFunc<Instr::Kind::ReadFlUIntLe>(&Vm::_execReadFlUIntLe);
    this->_initExecFunc<Instr::Kind::ReadFlUIntLeRev>(&Vm::_execReadFlUIntLeRev);
    this->_initExecFunc<Instr::Kind::ReadNtStrUtf16>(&Vm::_execReadNtStrUtf16);
    this->_initExecFunc<Instr::Kind::ReadNtStrUtf32>(&Vm::_execReadNtStrUtf32);
    this->_initExecFunc<Instr::Kind::ReadNtStrUtf8>(&Vm::_execReadNtStrUtf8);
    this->_initExecFunc<Instr::Kind::ReadVlSInt>(&Vm::_execReadVlSInt);
    this->_initExecFunc<Instr::Kind::ReadVlUInt>(&Vm::_execReadVlUInt);
    this->_initExecFunc<Instr::Kind::SaveVal>(&Vm::_execSaveVal);
    this->_initExecFunc<Instr::Kind::SetCurId>(&Vm::_execSetCurrentId);
    this->_initExecFunc<Instr::Kind::SetDsId>(&Vm::_execSetDsId);
    this->_initExecFunc<Instr::Kind::SetDsInfo>(&Vm::_execSetDsInfo);
    this->_initExecFunc<Instr::Kind::SetDst>(&Vm::_execSetDst);
    this->_initExecFunc<Instr::Kind::SetErInfo>(&Vm::_execSetErInfo);
    this->_initExecFunc<Instr::Kind::SetErt>(&Vm::_execSetErt);
    this->_initExecFunc<Instr::Kind::SetPktContentLen>(&Vm::_execSetPktContentLen);
    this->_initExecFunc<Instr::Kind::SetPktDiscErCounterSnap>(&Vm::_execSetPktDiscErCounterSnap);
    this->_initExecFunc<Instr::Kind::SetPktEndDefClkVal>(&Vm::_execSetPktEndDefClkVal);
    this->_initExecFunc<Instr::Kind::SetPktInfo>(&Vm::_execSetPktInfo);
    this->_initExecFunc<Instr::Kind::SetPktMagicNumber>(&Vm::_execSetPktMagicNumber);
    this->_initExecFunc<Instr::Kind::SetPktSeqNum>(&Vm::_execSetPktSeqNum);
    this->_initExecFunc<Instr::Kind::SetPktTotalLen>(&Vm::_execSetPktTotalLen);
    this->_initExecFunc<Instr::Kind::UpdateDefClkVal>(&Vm::_execUpdateDefClkVal);
    this->_initExecFunc<Instr::Kind::UpdateDefClkValFl>(&Vm::_execUpdateDefClkValFl);
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
    _bufOffsetInCurPktBits = offsetInElemSeqBytes * 8 - _pos.curPktOffsetInElemSeqBits;
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

Vm::_tExecReaction Vm::_execReadFlBitArrayLe(const Instr& instr)
{
    this->_execReadFlBitArray<readFlUIntLeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayBe(const Instr& instr)
{
    this->_execReadFlBitArray<readFlUIntBeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA8(const Instr& instr)
{
    this->_execReadStdFlBitArray<8, readFlUInt8, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA16Le(const Instr& instr)
{
    this->_execReadStdFlBitArray<16, readFlUIntLe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA32Le(const Instr& instr)
{
    this->_execReadStdFlBitArray<32, readFlUIntLe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA64Le(const Instr& instr)
{
    this->_execReadStdFlBitArray<64, readFlUIntLe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA16Be(const Instr& instr)
{
    this->_execReadStdFlBitArray<16, readFlUIntBe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA32Be(const Instr& instr)
{
    this->_execReadStdFlBitArray<32, readFlUIntBe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA64Be(const Instr& instr)
{
    this->_execReadStdFlBitArray<64, readFlUIntBe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapLe(const Instr& instr)
{
    this->_execReadFlBitMap<readFlUIntLeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapBe(const Instr& instr)
{
    this->_execReadFlBitMap<readFlUIntBeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA8(const Instr& instr)
{
    this->_execReadStdFlBitMap<8, readFlUInt8, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA16Le(const Instr& instr)
{
    this->_execReadStdFlBitMap<16, readFlUIntLe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA32Le(const Instr& instr)
{
    this->_execReadStdFlBitMap<32, readFlUIntLe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA64Le(const Instr& instr)
{
    this->_execReadStdFlBitMap<64, readFlUIntLe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA16Be(const Instr& instr)
{
    this->_execReadStdFlBitMap<16, readFlUIntBe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA32Be(const Instr& instr)
{
    this->_execReadStdFlBitMap<32, readFlUIntBe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA64Be(const Instr& instr)
{
    this->_execReadStdFlBitMap<64, readFlUIntBe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolLe(const Instr& instr)
{
    this->_execReadFlBool<readFlUIntLeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolBe(const Instr& instr)
{
    this->_execReadFlBool<readFlUIntBeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA8(const Instr& instr)
{
    this->_execReadStdFlBool<8, readFlUInt8, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA16Le(const Instr& instr)
{
    this->_execReadStdFlBool<16, readFlUIntLe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA32Le(const Instr& instr)
{
    this->_execReadStdFlBool<32, readFlUIntLe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA64Le(const Instr& instr)
{
    this->_execReadStdFlBool<64, readFlUIntLe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA16Be(const Instr& instr)
{
    this->_execReadStdFlBool<16, readFlUIntBe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA32Be(const Instr& instr)
{
    this->_execReadStdFlBool<32, readFlUIntBe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA64Be(const Instr& instr)
{
    this->_execReadStdFlBool<64, readFlUIntBe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntLe(const Instr& instr)
{
    this->_execReadFlInt<std::int64_t, readFlSIntLeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntBe(const Instr& instr)
{
    this->_execReadFlInt<std::int64_t, readFlSIntBeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA8(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 8, readFlSInt8, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA16Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 16, readFlSIntLe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA32Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 32, readFlSIntLe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA64Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 64, readFlSIntLe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA16Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 16, readFlSIntBe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA32Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 32, readFlSIntBe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA64Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 64, readFlSIntBe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntLe(const Instr& instr)
{
    this->_execReadFlInt<std::uint64_t, readFlUIntLeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntBe(const Instr& instr)
{
    this->_execReadFlInt<std::uint64_t, readFlUIntBeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA8(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 8, readFlUInt8, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA16Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 16, readFlUIntLe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA32Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 32, readFlUIntLe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA64Le(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 64, readFlUIntLe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA16Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 16, readFlUIntBe16, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA32Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 32, readFlUIntBe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA64Be(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 64, readFlUIntBe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat32Le(const Instr& instr)
{
    this->_execReadFlFloat<float, readFlUIntLeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat32Be(const Instr& instr)
{
    this->_execReadFlFloat<float, readFlUIntBeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA32Le(const Instr& instr)
{
    this->_execReadStdFlFloat<float, readFlUIntLe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA32Be(const Instr& instr)
{
    this->_execReadStdFlFloat<float, readFlUIntBe32, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat64Le(const Instr& instr)
{
    this->_execReadFlFloat<double, readFlUIntLeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat64Be(const Instr& instr)
{
    this->_execReadFlFloat<double, readFlUIntBeFuncs, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA64Le(const Instr& instr)
{
    this->_execReadStdFlFloat<double, readFlUIntLe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA64Be(const Instr& instr)
{
    this->_execReadStdFlFloat<double, readFlUIntBe64, false>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayLeRev(const Instr& instr)
{
    this->_execReadFlBitArray<readFlUIntLeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayBeRev(const Instr& instr)
{
    this->_execReadFlBitArray<readFlUIntBeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA8Rev(const Instr& instr)
{
    this->_execReadStdFlBitArray<8, readFlUInt8, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA16LeRev(const Instr& instr)
{
    this->_execReadStdFlBitArray<16, readFlUIntLe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA32LeRev(const Instr& instr)
{
    this->_execReadStdFlBitArray<32, readFlUIntLe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA64LeRev(const Instr& instr)
{
    this->_execReadStdFlBitArray<64, readFlUIntLe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA16BeRev(const Instr& instr)
{
    this->_execReadStdFlBitArray<16, readFlUIntBe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA32BeRev(const Instr& instr)
{
    this->_execReadStdFlBitArray<32, readFlUIntBe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitArrayA64BeRev(const Instr& instr)
{
    this->_execReadStdFlBitArray<64, readFlUIntBe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolLeRev(const Instr& instr)
{
    this->_execReadFlBool<readFlUIntLeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolBeRev(const Instr& instr)
{
    this->_execReadFlBool<readFlUIntBeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA8Rev(const Instr& instr)
{
    this->_execReadStdFlBitMap<8, readFlUInt8, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA16LeRev(const Instr& instr)
{
    this->_execReadStdFlBitMap<16, readFlUIntLe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA32LeRev(const Instr& instr)
{
    this->_execReadStdFlBitMap<32, readFlUIntLe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA64LeRev(const Instr& instr)
{
    this->_execReadStdFlBitMap<64, readFlUIntLe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA16BeRev(const Instr& instr)
{
    this->_execReadStdFlBitMap<16, readFlUIntBe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA32BeRev(const Instr& instr)
{
    this->_execReadStdFlBitMap<32, readFlUIntBe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapA64BeRev(const Instr& instr)
{
    this->_execReadStdFlBitMap<64, readFlUIntBe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapLeRev(const Instr& instr)
{
    this->_execReadFlBitMap<readFlUIntLeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBitMapBeRev(const Instr& instr)
{
    this->_execReadFlBitMap<readFlUIntBeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA8Rev(const Instr& instr)
{
    this->_execReadStdFlBool<8, readFlUInt8, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA16LeRev(const Instr& instr)
{
    this->_execReadStdFlBool<16, readFlUIntLe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA32LeRev(const Instr& instr)
{
    this->_execReadStdFlBool<32, readFlUIntLe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA64LeRev(const Instr& instr)
{
    this->_execReadStdFlBool<64, readFlUIntLe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA16BeRev(const Instr& instr)
{
    this->_execReadStdFlBool<16, readFlUIntBe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA32BeRev(const Instr& instr)
{
    this->_execReadStdFlBool<32, readFlUIntBe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlBoolA64BeRev(const Instr& instr)
{
    this->_execReadStdFlBool<64, readFlUIntBe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntLeRev(const Instr& instr)
{
    this->_execReadFlInt<std::int64_t, readFlSIntLeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntBeRev(const Instr& instr)
{
    this->_execReadFlInt<std::int64_t, readFlSIntBeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA8Rev(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 8, readFlSInt8, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA16LeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 16, readFlSIntLe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA32LeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 32, readFlSIntLe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA64LeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 64, readFlSIntLe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA16BeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 16, readFlSIntBe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA32BeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 32, readFlSIntBe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlSIntA64BeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::int64_t, 64, readFlSIntBe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntLeRev(const Instr& instr)
{
    this->_execReadFlInt<std::uint64_t, readFlUIntLeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntBeRev(const Instr& instr)
{
    this->_execReadFlInt<std::uint64_t, readFlUIntBeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA8Rev(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 8, readFlUInt8, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA16LeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 16, readFlUIntLe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA32LeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 32, readFlUIntLe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA64LeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 64, readFlUIntLe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA16BeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 16, readFlUIntBe16, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA32BeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 32, readFlUIntBe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlUIntA64BeRev(const Instr& instr)
{
    this->_execReadStdFlInt<std::uint64_t, 64, readFlUIntBe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat32LeRev(const Instr& instr)
{
    this->_execReadFlFloat<float, readFlUIntLeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat32BeRev(const Instr& instr)
{
    this->_execReadFlFloat<float, readFlUIntBeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA32LeRev(const Instr& instr)
{
    this->_execReadStdFlFloat<float, readFlUIntLe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA32BeRev(const Instr& instr)
{
    this->_execReadStdFlFloat<float, readFlUIntBe32, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat64LeRev(const Instr& instr)
{
    this->_execReadFlFloat<double, readFlUIntLeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloat64BeRev(const Instr& instr)
{
    this->_execReadFlFloat<double, readFlUIntBeFuncs, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA64LeRev(const Instr& instr)
{
    this->_execReadStdFlFloat<double, readFlUIntLe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadFlFloatA64BeRev(const Instr& instr)
{
    this->_execReadStdFlFloat<double, readFlUIntBe64, true>(instr);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadVlUInt(const Instr& instr)
{
    return this->_execReadVlIntCommon(instr, _pos.elems.vlUInt, VmState::ContinueReadVlUInt);
}

Vm::_tExecReaction Vm::_execReadVlSInt(const Instr& instr)
{
    return this->_execReadVlIntCommon(instr, _pos.elems.vlSInt, VmState::ContinueReadVlSInt);
}

Vm::_tExecReaction Vm::_execReadNtStrCommon(const Instr& instr, const VmState state)
{
    this->_alignHead(instr);
    this->_setDataElemFromInstr(_pos.elems.ntStrBeginning, instr);
    this->_setDataElemFromInstr(_pos.elems.ntStrEnd, instr);
    this->_updateItForUser(_pos.elems.ntStrBeginning);
    _pos.nextState = _pos.state();
    _pos.state(state);
    _pos.ntStrCuBuf.index = 0;
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execReadNtStrUtf8(const Instr& instr)
{
    return this->_execReadNtStrCommon(instr, VmState::ReadUtf8DataUntilNull);
}

Vm::_tExecReaction Vm::_execReadNtStrUtf16(const Instr& instr)
{
    return this->_execReadNtStrCommon(instr, VmState::ReadUtf16DataUntilNull);
}

Vm::_tExecReaction Vm::_execReadNtStrUtf32(const Instr& instr)
{
    return this->_execReadNtStrCommon(instr, VmState::ReadUtf32DataUntilNull);
}

Vm::_tExecReaction Vm::_execBeginReadScope(const Instr& instr)
{
    const auto& beginReadScopeInstr = static_cast<const BeginReadScopeInstr&>(instr);

    // align now so that the offset of the iterator is _after_ any padding
    this->_alignHead(beginReadScopeInstr.align());

    _pos.elems.scopeBeginning._scope = beginReadScopeInstr.scope();
    this->_updateItForUser(_pos.elems.scopeBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(&beginReadScopeInstr.proc());
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadScope(const Instr& instr)
{
    _pos.elems.scopeEnd._scope = static_cast<const EndReadScopeInstr&>(instr).scope();
    this->_updateItForUser(_pos.elems.scopeEnd);
    _pos.stackPop();
    assert(_pos.state() == VmState::ExecInstr);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execBeginReadStruct(const Instr& instr)
{
    const auto& beginReadStructInstr = static_cast<const BeginReadStructInstr&>(instr);

    this->_alignHead(instr);
    this->_setDataElemFromInstr(_pos.elems.structBeginning, instr);
    this->_updateItForUser(_pos.elems.structBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(&beginReadStructInstr.proc());
    _pos.state(VmState::ExecInstr);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadStruct(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.structEnd, instr);
    this->_updateItForUser(_pos.elems.structEnd);
    _pos.setParentStateAndStackPop();
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execBeginReadSlArray(const Instr& instr)
{
    return this->_execBeginReadSlArray(instr, VmState::ExecArrayInstr);
}

Vm::_tExecReaction Vm::_execEndReadSlArray(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.slArrayEnd, instr);
    this->_updateItForUser(_pos.elems.slArrayEnd);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execBeginReadSlStr(const Instr& instr)
{
    const auto& beginReadSlStrInstr = static_cast<const BeginReadSlStrInstr&>(instr);

    _pos.elems.slStrBeginning._maxLen = beginReadSlStrInstr.maxLen();
    this->_execBeginReadStaticData(beginReadSlStrInstr, _pos.elems.slStrBeginning,
                                   beginReadSlStrInstr.maxLen(), nullptr, VmState::ReadRawData);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadSlStr(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.slStrEnd, instr);
    this->_updateItForUser(_pos.elems.slStrEnd);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execBeginReadSlUuidArray(const Instr& instr)
{
    return this->_execBeginReadSlArray(instr, VmState::ReadUuidByte);
}

Vm::_tExecReaction Vm::_execBeginReadDlArray(const Instr& instr)
{
    const auto& beginReadDlArrayInstr = static_cast<const BeginReadDlArrayInstr&>(instr);

    this->_execBeginReadDynData(beginReadDlArrayInstr, _pos.elems.dlArrayBeginning,
                                beginReadDlArrayInstr.lenPos(), _pos.elems.dlArrayBeginning._len,
                                &beginReadDlArrayInstr.proc(), VmState::ExecArrayInstr);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadDlArray(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.dlArrayEnd, instr);
    this->_updateItForUser(_pos.elems.dlArrayEnd);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execBeginReadDlStr(const Instr& instr)
{
    const auto& beginReadDlStrInstr = static_cast<const BeginReadDlStrInstr&>(instr);

    this->_execBeginReadDynData(beginReadDlStrInstr, _pos.elems.dlStrBeginning,
                                beginReadDlStrInstr.maxLenPos(), _pos.elems.dlStrBeginning._maxLen,
                                nullptr, VmState::ReadRawData);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadDlStr(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.dlStrEnd, instr);
    this->_updateItForUser(_pos.elems.dlStrEnd);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execBeginReadSlBlob(const Instr& instr)
{
    return this->_execBeginReadSlBlob(instr, VmState::ReadRawData);
}

Vm::_tExecReaction Vm::_execBeginReadSlUuidBlob(const Instr& instr)
{
    return this->_execBeginReadSlBlob(instr, VmState::ReadUuidBlobSection);
}

Vm::_tExecReaction Vm::_execEndReadSlBlob(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.slBlobEnd, instr);
    this->_updateItForUser(_pos.elems.slBlobEnd);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execBeginReadDlBlob(const Instr& instr)
{
    const auto& beginReadDlBlobInstr = static_cast<const BeginReadDlBlobInstr&>(instr);

    this->_execBeginReadDynData(beginReadDlBlobInstr, _pos.elems.dlBlobBeginning,
                                beginReadDlBlobInstr.lenPos(), _pos.elems.dlBlobBeginning._len,
                                nullptr, VmState::ReadRawData);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadDlBlob(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.dlBlobEnd, instr);
    this->_updateItForUser(_pos.elems.dlBlobEnd);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execBeginReadVarSIntSel(const Instr& instr)
{
    this->_execBeginReadVar<BeginReadVarSIntSelInstr>(instr, _pos.elems.varSIntSelBeginning);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execBeginReadVarUIntSel(const Instr& instr)
{
    this->_execBeginReadVar<BeginReadVarUIntSelInstr>(instr, _pos.elems.varUIntSelBeginning);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execBeginReadOptBoolSel(const Instr& instr)
{
    this->_execBeginReadOpt<BeginReadOptBoolSelInstr, bool>(instr, _pos.elems.optBoolSelBeginning);
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execBeginReadOptSIntSel(const Instr& instr)
{
    _pos.elems.optSIntSelBeginning._selVal = this->_execBeginReadOpt<BeginReadOptSIntSelInstr,
                                                                     long long>(instr,
                                                                                _pos.elems.optSIntSelBeginning);;
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execBeginReadOptUIntSel(const Instr& instr)
{
    _pos.elems.optUIntSelBeginning._selVal = this->_execBeginReadOpt<BeginReadOptUIntSelInstr,
                                                                     unsigned long long>(instr,
                                                                                         _pos.elems.optUIntSelBeginning);;
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadVarUIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.varUIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.varUIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadVarSIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.varSIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.varSIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadOptBoolSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.optBoolSelEnd, instr);
    this->_updateItForUser(_pos.elems.optBoolSelEnd);
    _pos.setParentStateAndStackPop();
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadOptUIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.optUIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.optUIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execEndReadOptSIntSel(const Instr& instr)
{
    this->_setDataElemFromInstr(_pos.elems.optSIntSelEnd, instr);
    this->_updateItForUser(_pos.elems.optSIntSelEnd);
    _pos.setParentStateAndStackPop();
    return _tExecReaction::Stop;
}

Vm::_tExecReaction Vm::_execSaveVal(const Instr& instr)
{
    _pos.saveVal(static_cast<const SaveValInstr&>(instr).pos());
    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execSetPktEndDefClkVal(const Instr&)
{
    _pos.elems.pktInfo._endDefClkVal = _pos.lastIntVal.u;
    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execUpdateDefClkValFl(const Instr& instr)
{
    return this->_execUpdateDefClkValCommon(static_cast<const UpdateDefClkValFlInstr&>(instr).len());
}

Vm::_tExecReaction Vm::_execUpdateDefClkVal(const Instr&)
{
    return this->_execUpdateDefClkValCommon(_pos.lastIntVal.u);
}

Vm::_tExecReaction Vm::_execSetCurrentId(const Instr&)
{
    _pos.curId = _pos.lastIntVal.u;
    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execSetDst(const Instr& instr)
{
    const auto& setDstInstr = static_cast<const SetDstInstr&>(instr);
    const auto id = setDstInstr.fixedId() ? *setDstInstr.fixedId() : _pos.curId;

    if (const auto dstPacketProc = (*_pos.pktProc)[id]) {
        _pos.curDsPktProc = dstPacketProc;
        _pos.elems.dsInfo._dst = &dstPacketProc->dst();
        return _tExecReaction::ExecNextInstr;
    } else {
        throw UnknownDataStreamTypeDecodingError {
            _pos.headOffsetInElemSeqBits(), id
        };
    }
}

Vm::_tExecReaction Vm::_execSetErt(const Instr& instr)
{
    assert(_pos.curDsPktProc);

    const auto& setErtInstr = static_cast<const SetErtInstr&>(instr);
    const auto id = setErtInstr.fixedId() ? *setErtInstr.fixedId() : _pos.curId;

    assert(_pos.curDsPktProc);

    if (const auto erProc = (*_pos.curDsPktProc)[id]) {
        _pos.curErProc = erProc;
        _pos.elems.erInfo._ert = &erProc->ert();
        return _tExecReaction::ExecNextInstr;
    } else {
        throw UnknownEventRecordTypeDecodingError {
            _pos.headOffsetInElemSeqBits(), id
        };
    }
}

Vm::_tExecReaction Vm::_execSetDsId(const Instr&)
{
    _pos.elems.dsInfo._id = _pos.lastIntVal.u;
    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execSetPktSeqNum(const Instr&)
{
    _pos.elems.pktInfo._seqNum = _pos.lastIntVal.u;
    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execSetPktDiscErCounterSnap(const Instr&)
{
    _pos.elems.pktInfo._discErCounterSnap = _pos.lastIntVal.u;
    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execSetPktTotalLen(const Instr&)
{
    const auto pktTotalSizeCandidateBits = _pos.lastIntVal.u;

    if ((pktTotalSizeCandidateBits & 7) != 0) {
        throw ExpectedPacketTotalLengthNotMultipleOf8DecodingError {
            _pos.headOffsetInElemSeqBits(),
            pktTotalSizeCandidateBits
        };
    }

    if (_pos.curExpectedPktContentLenBits != sizeUnset) {
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

    if (_pos.curExpectedPktContentLenBits == sizeUnset) {
        _pos.curExpectedPktContentLenBits = _pos.curExpectedPktTotalLenBits;
    }

    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execSetPktContentLen(const Instr&)
{
    const auto pktContentSizeCandidateBits = _pos.lastIntVal.u;

    if (_pos.curExpectedPktTotalLenBits != sizeUnset) {
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
    return _tExecReaction::ExecNextInstr;
}

Vm::_tExecReaction Vm::_execSetDsInfo(const Instr&)
{
    this->_updateItForUser(_pos.elems.dsInfo);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execSetPktInfo(const Instr&)
{
    _pos.elems.pktInfo._expectedTotalLen = boost::none;
    _pos.elems.pktInfo._expectedContentLen = boost::none;

    if (_pos.curExpectedPktTotalLenBits != std::numeric_limits<Size>::max()) {
        _pos.elems.pktInfo._expectedTotalLen = _pos.curExpectedPktTotalLenBits;
    }

    if (_pos.curExpectedPktContentLenBits != std::numeric_limits<Size>::max()) {
        _pos.elems.pktInfo._expectedContentLen = _pos.curExpectedPktContentLenBits;
    }
    this->_updateItForUser(_pos.elems.pktInfo);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execSetErInfo(const Instr&)
{
    this->_updateItForUser(_pos.elems.erInfo);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execSetPktMagicNumber(const Instr&)
{
    _pos.elems.pktMagicNumber._val = _pos.lastIntVal.u;
    this->_updateItForUser(_pos.elems.pktMagicNumber);
    return _tExecReaction::FetchNextInstrAndStop;
}

Vm::_tExecReaction Vm::_execEndPktPreambleProc(const Instr&)
{
    // after packet header
    _pos.stackPop();
    assert(_pos.stack.empty());

    if (_pos.curDsPktProc) {
        _pos.loadNewProc(_pos.curDsPktProc->pktPreambleProc());
        return _tExecReaction::ExecCurInstr;
    } else {
        _pos.state(VmState::EndPktContent);
        return _tExecReaction::ChangeState;
    }
}

Vm::_tExecReaction Vm::_execEndDsPktPreambleProc(const Instr&)
{
    // after packet context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curDsPktProc);

    if (_pos.curDsPktProc->dst().eventRecordTypes().empty()) {
        _pos.state(VmState::EndPktContent);
    } else {
        _pos.state(VmState::BeginEr);
    }

    return _tExecReaction::ChangeState;
}

Vm::_tExecReaction Vm::_execEndDsErPreambleProc(const Instr&)
{
    // after second event record context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curErProc);
    _pos.loadNewProc(_pos.curErProc->proc());
    return _tExecReaction::ExecCurInstr;
}

Vm::_tExecReaction Vm::_execEndErProc(const Instr&)
{
    // after event record payload
    _pos.stackPop();
    assert(_pos.stack.empty());
    _pos.state(VmState::EndEr);
    return _tExecReaction::ChangeState;
}

} // namespace yactfr
} // namespace internal
