/*
 * yactfr virtual machine.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstdint>

#include "vm.hpp"
#include "int-reader.hpp"

namespace yactfr {
namespace internal {

VmPos::VmPos(const PacketProc& packetProc) :
    packetProc {&packetProc}
{
    if (packetProc.traceType().uuid()) {
        elems.packetUuid._expectedUuid = *packetProc.traceType().uuid();
    }

    this->_initVectorsFromPacketProc();
}

VmPos::VmPos(const VmPos& other)
{
    this->_setFromOther(other);
}

VmPos& VmPos::operator=(const VmPos& other)
{
    assert(packetProc == other.packetProc);
    this->_setFromOther(other);
    return *this;
}

void VmPos::_initVectorsFromPacketProc()
{
    savedValues.resize(packetProc->savedValuesCount(), SIZE_UNSET);
    clockValues.resize(packetProc->indexedClockTypes().size());
}

void VmPos::_setSimpleFromOther(const VmPos& other)
{
    curPacketOffsetInPacketSequenceBits = other.curPacketOffsetInPacketSequenceBits;
    cursorOffsetInCurPacketBits = other.cursorOffsetInCurPacketBits;
    elems = other.elems;
    state = other.state;
    lastBo = other.lastBo;
    remBitsToSkip = other.remBitsToSkip;
    postSkipBitsState = other.postSkipBitsState;
    postEndStringState = other.postEndStringState;
    lastIntVal = other.lastIntVal;
    curId = other.curId;
    packetProc = other.packetProc;
    curDstPacketProc = other.curDstPacketProc;
    curErtProc = other.curErtProc;
    uuid = other.uuid;
    curPacketTotalSizeBits = other.curPacketTotalSizeBits;
    curPacketContentSizeBits = other.curPacketContentSizeBits;
}

void VmPos::_setFromOther(const VmPos& other)
{
    this->_setSimpleFromOther(other);
    stack = other.stack;
    savedValues = other.savedValues;
    clockValues = other.clockValues;
}

} // namespace internal

PacketSequenceIteratorPosition::~PacketSequenceIteratorPosition()
{
}

PacketSequenceIteratorPosition::PacketSequenceIteratorPosition() :
    _vmPos {nullptr},
    _iterInfos {std::make_unique<internal::IterInfos>()}
{
}

PacketSequenceIteratorPosition::PacketSequenceIteratorPosition(const PacketSequenceIteratorPosition& other) :
    PacketSequenceIteratorPosition {}
{
    if (other._vmPos) {
        // use copy constructor
        _vmPos = std::make_unique<internal::VmPos>(*other._vmPos);
    } else {
        _vmPos = nullptr;
        return;
    }

    _iterInfos->offset = other._iterInfos->offset;
    _iterInfos->mark = other._iterInfos->mark;
    assert(other._iterInfos->elem);
    _iterInfos->setElemFromOther(_vmPos.get(), other._vmPos.get(),
                                 other._iterInfos->elem);
}

PacketSequenceIteratorPosition::PacketSequenceIteratorPosition(PacketSequenceIteratorPosition&& other) :
    _vmPos {std::move(other._vmPos)},
    _iterInfos {std::make_unique<internal::IterInfos>(*other._iterInfos)}
{
}

PacketSequenceIteratorPosition& PacketSequenceIteratorPosition::operator=(const PacketSequenceIteratorPosition& other)
{
    if (other._vmPos) {
        // use copy constructor
        _vmPos = std::make_unique<internal::VmPos>(*other._vmPos);
    } else {
        _vmPos = nullptr;
        return *this;
    }

    _iterInfos->offset = other._iterInfos->offset;
    _iterInfos->mark = other._iterInfos->mark;
    assert(other._iterInfos->elem);
    _iterInfos->setElemFromOther(_vmPos.get(), other._vmPos.get(),
                                 other._iterInfos->elem);
    return *this;
}

PacketSequenceIteratorPosition& PacketSequenceIteratorPosition::operator=(PacketSequenceIteratorPosition&& other)
{
    _vmPos = std::move(other._vmPos);
    *_iterInfos = *other._iterInfos;
    return *this;
}

PacketSequenceIteratorPosition::operator bool() const noexcept
{
    return static_cast<bool>(_vmPos);
}

bool PacketSequenceIteratorPosition::operator==(const PacketSequenceIteratorPosition& other) const noexcept
{
    return *_iterInfos == *other._iterInfos;
}

bool PacketSequenceIteratorPosition::operator!=(const PacketSequenceIteratorPosition& other) const noexcept
{
    return *_iterInfos != *other._iterInfos;
}

bool PacketSequenceIteratorPosition::operator<(const PacketSequenceIteratorPosition& other) const noexcept
{
    return *_iterInfos < *other._iterInfos;
}

bool PacketSequenceIteratorPosition::operator<=(const PacketSequenceIteratorPosition& other) const noexcept
{
    return *_iterInfos <= *other._iterInfos;
}

bool PacketSequenceIteratorPosition::operator>(const PacketSequenceIteratorPosition& other) const noexcept
{
    return *_iterInfos > *other._iterInfos;
}

bool PacketSequenceIteratorPosition::operator>=(const PacketSequenceIteratorPosition& other) const noexcept
{
    return *_iterInfos >= *other._iterInfos;
}

namespace internal {

Vm::Vm(DataSourceFactory *dataSrcFactory, const PacketProc& packetProc,
       PacketSequenceIterator& iter) :
    _dataSrcFactory {dataSrcFactory},
    _dataSource {dataSrcFactory->createDataSource()},
    _iter {&iter},
    _pos {packetProc}
{
    this->_initExecFuncs();
}

Vm::Vm(const Vm& other, PacketSequenceIterator& iter) :
    _dataSrcFactory {other._dataSrcFactory},
    _dataSource {_dataSrcFactory->createDataSource()},
    _iter {&iter},
    _pos {other._pos}
{
    this->_initExecFuncs();
    this->_resetBuffer();
}

Vm& Vm::operator=(const Vm& other)
{
    assert(_dataSrcFactory == other._dataSrcFactory);
    _iter = nullptr;
    _pos = other._pos;
    this->_resetBuffer();
    return *this;
}

void Vm::_initExecFuncs()
{
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_LE)] = &Vm::_execReadSignedIntLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_BE)] = &Vm::_execReadSignedIntBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_A8)] = &Vm::_execReadSignedIntA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_A16_LE)] = &Vm::_execReadSignedIntA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_A32_LE)] = &Vm::_execReadSignedIntA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_A64_LE)] = &Vm::_execReadSignedIntA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_A16_BE)] = &Vm::_execReadSignedIntA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_A32_BE)] = &Vm::_execReadSignedIntA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_INT_A64_BE)] = &Vm::_execReadSignedIntA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_LE)] = &Vm::_execReadUnsignedIntLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_BE)] = &Vm::_execReadUnsignedIntBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_A8)] = &Vm::_execReadUnsignedIntA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_A16_LE)] = &Vm::_execReadUnsignedIntA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_A32_LE)] = &Vm::_execReadUnsignedIntA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_A64_LE)] = &Vm::_execReadUnsignedIntA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_A16_BE)] = &Vm::_execReadUnsignedIntA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_A32_BE)] = &Vm::_execReadUnsignedIntA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_INT_A64_BE)] = &Vm::_execReadUnsignedIntA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_32_LE)] = &Vm::_execReadFloat32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_32_BE)] = &Vm::_execReadFloat32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_A32_LE)] = &Vm::_execReadFloatA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_A32_BE)] = &Vm::_execReadFloatA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_64_LE)] = &Vm::_execReadFloat64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_64_BE)] = &Vm::_execReadFloat64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_A64_LE)] = &Vm::_execReadFloatA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_FLOAT_A64_BE)] = &Vm::_execReadFloatA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_LE)] = &Vm::_execReadSignedEnumLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_BE)] = &Vm::_execReadSignedEnumBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_A8)] = &Vm::_execReadSignedEnumA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_A16_LE)] = &Vm::_execReadSignedEnumA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_A32_LE)] = &Vm::_execReadSignedEnumA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_A64_LE)] = &Vm::_execReadSignedEnumA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_A16_BE)] = &Vm::_execReadSignedEnumA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_A32_BE)] = &Vm::_execReadSignedEnumA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_SIGNED_ENUM_A64_BE)] = &Vm::_execReadSignedEnumA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_LE)] = &Vm::_execReadUnsignedEnumLe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_BE)] = &Vm::_execReadUnsignedEnumBe;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_A8)] = &Vm::_execReadUnsignedEnumA8;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_A16_LE)] = &Vm::_execReadUnsignedEnumA16Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_A32_LE)] = &Vm::_execReadUnsignedEnumA32Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_A64_LE)] = &Vm::_execReadUnsignedEnumA64Le;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_A16_BE)] = &Vm::_execReadUnsignedEnumA16Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_A32_BE)] = &Vm::_execReadUnsignedEnumA32Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_UNSIGNED_ENUM_A64_BE)] = &Vm::_execReadUnsignedEnumA64Be;
    _execFuncs[static_cast<int>(Instr::Kind::READ_STRING)] = &Vm::_execReadString;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_SCOPE)] = &Vm::_execBeginReadScope;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_SCOPE)] = &Vm::_execEndReadScope;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STRUCT)] = &Vm::_execBeginReadStruct;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_STRUCT)] = &Vm::_execEndReadStruct;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STATIC_ARRAY)] = &Vm::_execBeginReadStaticArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_STATIC_ARRAY)] = &Vm::_execEndReadStaticArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STATIC_TEXT_ARRAY)] = &Vm::_execBeginReadStaticTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_STATIC_TEXT_ARRAY)] = &Vm::_execEndReadStaticTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_STATIC_UUID_ARRAY)] = &Vm::_execBeginReadStaticUuidArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_DYNAMIC_ARRAY)] = &Vm::_execBeginReadDynamicArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_DYNAMIC_ARRAY)] = &Vm::_execEndReadDynamicArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_DYNAMIC_TEXT_ARRAY)] = &Vm::_execBeginReadDynamicTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_DYNAMIC_TEXT_ARRAY)] = &Vm::_execEndReadDynamicTextArray;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_VARIANT_SIGNED_TAG)] = &Vm::_execBeginReadVariantSignedTag;
    _execFuncs[static_cast<int>(Instr::Kind::BEGIN_READ_VARIANT_UNSIGNED_TAG)] = &Vm::_execBeginReadVariantUnsignedTag;
    _execFuncs[static_cast<int>(Instr::Kind::END_READ_VARIANT)] = &Vm::_execEndReadVariant;
    _execFuncs[static_cast<int>(Instr::Kind::SAVE_VALUE)] = &Vm::_execSaveValue;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PACKET_END_CLOCK_VALUE)] = &Vm::_execSetPacketEndClockValue;
    _execFuncs[static_cast<int>(Instr::Kind::UPDATE_CLOCK_VALUE)] = &Vm::_execUpdateClockValue;
    _execFuncs[static_cast<int>(Instr::Kind::SET_CURRENT_ID)] = &Vm::_execSetCurrentId;
    _execFuncs[static_cast<int>(Instr::Kind::SET_DATA_STREAM_TYPE)] = &Vm::_execSetDataStreamType;
    _execFuncs[static_cast<int>(Instr::Kind::SET_EVENT_RECORD_TYPE)] = &Vm::_execSetEventRecordType;
    _execFuncs[static_cast<int>(Instr::Kind::SET_DATA_STREAM_ID)] = &Vm::_execSetDataStreamId;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PACKET_ORIGIN_INDEX)] = &Vm::_execSetPacketOriginIndex;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PACKET_TOTAL_SIZE)] = &Vm::_execSetPacketTotalSize;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PACKET_CONTENT_SIZE)] = &Vm::_execSetPacketContentSize;
    _execFuncs[static_cast<int>(Instr::Kind::SET_PACKET_MAGIC_NUMBER)] = &Vm::_execSetPacketMagicNumber;
    _execFuncs[static_cast<int>(Instr::Kind::END_PACKET_PREAMBLE_PROC)] = &Vm::_execEndPacketPreambleProc;
    _execFuncs[static_cast<int>(Instr::Kind::END_DST_PACKET_PREAMBLE_PROC)] = &Vm::_execEndDstPacketPreambleProc;
    _execFuncs[static_cast<int>(Instr::Kind::END_DST_ERT_PREAMBLE_PROC)] = &Vm::_execEndDstErtPreambleProc;
    _execFuncs[static_cast<int>(Instr::Kind::END_ERT_PROC)] = &Vm::_execEndErtProc;
}

void Vm::seekPacket(const Index offsetBytes)
{
    _pos.curPacketOffsetInPacketSequenceBits = offsetBytes * 8;
    _pos.resetForNewPacket();
    this->_resetBuffer();

    // will set the packet beginning element, or end of iterator
    this->nextElement();
}

bool Vm::_getNewDataBlock(const Index offsetInPacketSequenceBytes,
                          const Size sizeBytes)
{
    assert(sizeBytes <= 9);

    const auto dataBlock = _dataSource->data(offsetInPacketSequenceBytes,
                                             sizeBytes);

    if (!dataBlock) {
        // no data
        return false;
    }

    _bufAddr = static_cast<const std::uint8_t *>(dataBlock->addr());
    _bufSizeBits = dataBlock->size() * 8;

    const auto offsetInPacketSequenceBits = offsetInPacketSequenceBytes * 8;

    _bufOffsetInCurPacketBits = offsetInPacketSequenceBits -
                                _pos.curPacketOffsetInPacketSequenceBits;
    return true;
}

void Vm::savePosition(PacketSequenceIteratorPosition& pos) const
{
    if (!pos) {
        // allocate new position
        pos._vmPos = std::make_unique<internal::VmPos>(_pos);
    } else {
        *pos._vmPos = _pos;
    }

    pos._iterInfos->offset = _iter->_offset;
    pos._iterInfos->mark = _iter->_mark;
    assert(_iter->_curElement);
    pos._iterInfos->setElemFromOther(pos._vmPos.get(), &_pos,
                                     _iter->_curElement);
}

void Vm::restorePosition(const PacketSequenceIteratorPosition& pos)
{
    assert(pos);
    _pos = *pos._vmPos;
    _iter->_offset = pos._iterInfos->offset;
    _iter->_mark = pos._iterInfos->mark;
    this->updateIterElementFromOtherPos(*pos._vmPos,
                                        pos._iterInfos->elem);

    /*
     * Reset buffer: the next call to operator++() will require more
     * data and the VM will request a new data block at this moment.
     * This is important to avoid throwing from this method so that it
     * always succeeds.
     */
    this->_resetBuffer();
}

Vm::_ExecReaction Vm::_execReadSignedIntLe(const Instr& instr)
{
    this->_execReadInt<std::int64_t, readIntLeSignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntBe(const Instr& instr)
{
    this->_execReadInt<std::int64_t, readIntBeSignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntA8(const Instr& instr)
{
    this->_execReadStdInt<std::int64_t, 8, readIntSigned8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntA16Le(const Instr& instr)
{
    this->_execReadStdInt<std::int64_t, 16, readIntSignedLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntA32Le(const Instr& instr)
{
    this->_execReadStdInt<std::int64_t, 32, readIntSignedLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntA64Le(const Instr& instr)
{
    this->_execReadStdInt<std::int64_t, 64, readIntSignedLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntA16Be(const Instr& instr)
{
    this->_execReadStdInt<std::int64_t, 16, readIntSignedBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntA32Be(const Instr& instr)
{
    this->_execReadStdInt<std::int64_t, 32, readIntSignedBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedIntA64Be(const Instr& instr)
{
    this->_execReadStdInt<std::int64_t, 64, readIntSignedBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntLe(const Instr& instr)
{
    this->_execReadInt<std::uint64_t, readIntLeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntBe(const Instr& instr)
{
    this->_execReadInt<std::uint64_t, readIntBeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntA8(const Instr& instr)
{
    this->_execReadStdInt<std::uint64_t, 8, readIntUnsigned8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntA16Le(const Instr& instr)
{
    this->_execReadStdInt<std::uint64_t, 16, readIntUnsignedLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntA32Le(const Instr& instr)
{
    this->_execReadStdInt<std::uint64_t, 32, readIntUnsignedLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntA64Le(const Instr& instr)
{
    this->_execReadStdInt<std::uint64_t, 64, readIntUnsignedLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntA16Be(const Instr& instr)
{
    this->_execReadStdInt<std::uint64_t, 16, readIntUnsignedBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntA32Be(const Instr& instr)
{
    this->_execReadStdInt<std::uint64_t, 32, readIntUnsignedBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedIntA64Be(const Instr& instr)
{
    this->_execReadStdInt<std::uint64_t, 64, readIntUnsignedBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloat32Le(const Instr& instr)
{
    this->_execReadFloat<float, readIntLeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloat32Be(const Instr& instr)
{
    this->_execReadFloat<float, readIntBeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloatA32Le(const Instr& instr)
{
    this->_execReadStdFloat<float, readIntUnsignedLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloatA32Be(const Instr& instr)
{
    this->_execReadStdFloat<float, readIntUnsignedBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloat64Le(const Instr& instr)
{
    this->_execReadFloat<double, readIntLeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloat64Be(const Instr& instr)
{
    this->_execReadFloat<double, readIntBeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloatA64Le(const Instr& instr)
{
    this->_execReadStdFloat<double, readIntUnsignedLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadFloatA64Be(const Instr& instr)
{
    this->_execReadStdFloat<double, readIntUnsignedBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumLe(const Instr& instr)
{
    this->_execReadEnum<std::int64_t, readIntLeSignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumBe(const Instr& instr)
{
    this->_execReadEnum<std::int64_t, readIntBeSignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumA8(const Instr& instr)
{
    this->_execReadStdEnum<std::int64_t, 8, readIntSigned8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumA16Le(const Instr& instr)
{
    this->_execReadStdEnum<std::int64_t, 16, readIntSignedLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumA32Le(const Instr& instr)
{
    this->_execReadStdEnum<std::int64_t, 32, readIntSignedLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumA64Le(const Instr& instr)
{
    this->_execReadStdEnum<std::int64_t, 64, readIntSignedLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumA16Be(const Instr& instr)
{
    this->_execReadStdEnum<std::int64_t, 16, readIntSignedBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumA32Be(const Instr& instr)
{
    this->_execReadStdEnum<std::int64_t, 32, readIntSignedBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadSignedEnumA64Be(const Instr& instr)
{
    this->_execReadStdEnum<std::int64_t, 64, readIntSignedBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumLe(const Instr& instr)
{
    this->_execReadEnum<std::uint64_t, readIntLeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumBe(const Instr& instr)
{
    this->_execReadEnum<std::uint64_t, readIntBeUnsignedFuncs>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumA8(const Instr& instr)
{
    this->_execReadStdEnum<std::uint64_t, 8, readIntUnsigned8>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumA16Le(const Instr& instr)
{
    this->_execReadStdEnum<std::uint64_t, 16, readIntUnsignedLe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumA32Le(const Instr& instr)
{
    this->_execReadStdEnum<std::uint64_t, 32, readIntUnsignedLe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumA64Le(const Instr& instr)
{
    this->_execReadStdEnum<std::uint64_t, 64, readIntUnsignedLe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumA16Be(const Instr& instr)
{
    this->_execReadStdEnum<std::uint64_t, 16, readIntUnsignedBe16>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumA32Be(const Instr& instr)
{
    this->_execReadStdEnum<std::uint64_t, 32, readIntUnsignedBe32>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadUnsignedEnumA64Be(const Instr& instr)
{
    this->_execReadStdEnum<std::uint64_t, 64, readIntUnsignedBe64>(instr);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execReadString(const Instr& instr)
{
    auto& instrReadString = static_cast<const InstrReadString&>(instr);

    this->_alignCursor(instr);
    this->_setNamedDataElementFromInstr(_pos.elems.stringBeginning,
                                        instrReadString);
    _pos.elems.stringBeginning._type = &instrReadString.stringType();
    this->_updateIterCurOffset(_pos.elems.stringBeginning);
    _pos.postEndStringState = _pos.state;
    _pos.setState(VmState::READ_SUBSTRING_UNTIL_NULL);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadScope(const Instr& instr)
{
    auto& instrBeginReadScope = static_cast<const InstrBeginReadScope&>(instr);

    _pos.elems.scopeBeginning._scope = instrBeginReadScope.scope();
    this->_updateIterCurOffset(_pos.elems.scopeBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(instrBeginReadScope.proc());
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadScope(const Instr& instr)
{
    auto& instrEndReadScope = static_cast<const InstrEndReadScope&>(instr);

    _pos.elems.scopeEnd._scope = instrEndReadScope.scope();
    this->_updateIterCurOffset(_pos.elems.scopeEnd);
    _pos.stackPop();
    assert(_pos.state == VmState::EXEC_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStruct(const Instr& instr)
{
    auto& instrBeginReadStruct = static_cast<const InstrBeginReadStruct&>(instr);

    this->_alignCursor(instr);
    this->_setNamedDataElementFromInstr(_pos.elems.structBeginning,
                                        instrBeginReadStruct);
    _pos.elems.structBeginning._type = &instrBeginReadStruct.structType();
    this->_updateIterCurOffset(_pos.elems.structBeginning);
    _pos.gotoNextInstr();
    _pos.stackPush(instrBeginReadStruct.proc());
    _pos.setState(VmState::EXEC_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadStruct(const Instr& instr)
{
    this->_updateIterCurOffset(_pos.elems.structEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStaticArray(const Instr& instr)
{
    auto& instrBeginReadStaticArray = static_cast<const InstrBeginReadStaticArray&>(instr);

    _pos.elems.staticArrayBeginning._type = &instrBeginReadStaticArray.staticArrayType();
    this->_execBeginReadStaticArrayCommon(instr, _pos.elems.staticArrayBeginning,
                                          VmState::EXEC_ARRAY_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadStaticArray(const Instr& instr)
{
    this->_updateIterCurOffset(_pos.elems.staticArrayEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStaticTextArray(const Instr& instr)
{
    auto& instrBeginReadStaticArray = static_cast<const InstrBeginReadStaticTextArray&>(instr);

    _pos.elems.staticTextArrayBeginning._type = &instrBeginReadStaticArray.staticTextArrayType();
    this->_execBeginReadStaticArrayCommon(instr, _pos.elems.staticTextArrayBeginning,
                                          VmState::READ_SUBSTRING);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadStaticTextArray(const Instr& instr)
{
    this->_updateIterCurOffset(_pos.elems.staticTextArrayEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadStaticUuidArray(const Instr& instr)
{
    auto& instrBeginReadStaticArray = static_cast<const InstrBeginReadStaticUuidArray&>(instr);

    _pos.elems.staticArrayBeginning._type = &instrBeginReadStaticArray.staticArrayType();
    this->_execBeginReadStaticArrayCommon(instr, _pos.elems.staticArrayBeginning,
                                          VmState::READ_UUID_BYTE);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadDynamicArray(const Instr& instr)
{
    auto& instrBeginReadDynamicArray = static_cast<const InstrBeginReadDynamicArray&>(instr);

    _pos.elems.dynamicArrayBeginning._type = &instrBeginReadDynamicArray.dynamicArrayType();
    this->_execBeginReadDynamicArrayCommon(instr, _pos.elems.dynamicArrayBeginning,
                                           VmState::EXEC_ARRAY_INSTR);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadDynamicArray(const Instr& instr)
{
    this->_updateIterCurOffset(_pos.elems.dynamicArrayEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadDynamicTextArray(const Instr& instr)
{
    auto& instrBeginReadDynamicArray = static_cast<const InstrBeginReadDynamicArray&>(instr);

    _pos.elems.dynamicTextArrayBeginning._type = &instrBeginReadDynamicArray.dynamicArrayType();
    this->_execBeginReadDynamicArrayCommon(instr, _pos.elems.dynamicTextArrayBeginning,
                                           VmState::READ_SUBSTRING);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadDynamicTextArray(const Instr& instr)
{
    this->_updateIterCurOffset(_pos.elems.dynamicTextArrayEnd);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execBeginReadVariantSignedTag(const Instr& instr)
{
    this->_execBeginReadVariant<InstrBeginReadVariantSignedTag>(instr,
                                                                _pos.elems.variantBeginningSignedTag);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execBeginReadVariantUnsignedTag(const Instr& instr)
{
    this->_execBeginReadVariant<InstrBeginReadVariantUnsignedTag>(instr,
                                                                  _pos.elems.variantBeginningUnsignedTag);
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execEndReadVariant(const Instr& instr)
{
    this->_updateIterCurOffset(_pos.elems.variantEnd);
    _pos.setParentStateAndStackPop();
    return _ExecReaction::STOP;
}

Vm::_ExecReaction Vm::_execSaveValue(const Instr& instr)
{
    auto& instrSaveValue = static_cast<const InstrSaveValue&>(instr);

    _pos.saveValue(instrSaveValue.pos());
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetPacketEndClockValue(const Instr& instr)
{
    auto& instrSetPacketEndClockValue = static_cast<const InstrSetPacketEndClockValue&>(instr);

    _pos.elems.packetEndClockValue._clockType = &instrSetPacketEndClockValue.clockType();
    _pos.elems.packetEndClockValue._cycles = _pos.lastIntVal.u;
    this->_updateIterCurOffset(_pos.elems.packetEndClockValue);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execUpdateClockValue(const Instr& instr)
{
    auto& instrUpdateClockValue = static_cast<const InstrUpdateClockValue&>(instr);

    const auto newVal = _pos.updateClockValue(instrUpdateClockValue.index(),
                                              instrUpdateClockValue.size());
    _pos.elems.clockValue._clockType = &instrUpdateClockValue.clockType();
    _pos.elems.clockValue._cycles = newVal;
    this->_updateIterCurOffset(_pos.elems.clockValue);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetCurrentId(const Instr& instr)
{
    _pos.curId = _pos.lastIntVal.u;
    return _ExecReaction::EXEC_NEXT_INSTR;
}

Vm::_ExecReaction Vm::_execSetDataStreamType(const Instr& instr)
{
    auto& instrSetDst = static_cast<const InstrSetDataStreamType&>(instr);
    TypeId id;

    if (instrSetDst.fixedId()) {
        id = *instrSetDst.fixedId();
    } else {
        id = _pos.curId;
    }

    auto dstPacketProc = (*_pos.packetProc)[id];

    if (!dstPacketProc) {
        throw UnknownDataStreamTypeDecodingError {
            _pos.cursorOffsetInPacketSequenceBits(), id
        };
    }

    _pos.curDstPacketProc = dstPacketProc;
    _pos.elems.dataStreamType._dataStreamType = &dstPacketProc->dataStreamType();
    this->_updateIterCurOffset(_pos.elems.dataStreamType);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetEventRecordType(const Instr& instr)
{
    assert(_pos.curDstPacketProc);

    auto& instrSetErt = static_cast<const InstrSetEventRecordType&>(instr);
    TypeId id;

    if (instrSetErt.fixedId()) {
        id = *instrSetErt.fixedId();
    } else {
        id = _pos.curId;
    }

    assert(_pos.curDstPacketProc);

    auto ertProc = (*_pos.curDstPacketProc)[id];

    if (!ertProc) {
        throw UnknownEventRecordTypeDecodingError {
            _pos.cursorOffsetInPacketSequenceBits(), id
        };
    }

    _pos.curErtProc = ertProc;
    _pos.elems.eventRecordType._eventRecordType = &ertProc->eventRecordType();
    this->_updateIterCurOffset(_pos.elems.eventRecordType);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetDataStreamId(const Instr& instr)
{
    _pos.elems.dataStreamId._dataStreamId = _pos.lastIntVal.u;
    this->_updateIterCurOffset(_pos.elems.dataStreamId);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPacketOriginIndex(const Instr& instr)
{
    _pos.elems.packetOriginIndex._index = _pos.lastIntVal.u;
    this->_updateIterCurOffset(_pos.elems.packetOriginIndex);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPacketTotalSize(const Instr& instr)
{
    const auto packetTotalSizeCandidateBits = _pos.lastIntVal.u;

    if ((packetTotalSizeCandidateBits & 7) != 0) {
        throw ExpectedPacketTotalSizeNotMultipleOf8DecodingError {
            _pos.cursorOffsetInPacketSequenceBits(),
            packetTotalSizeCandidateBits
        };
    }

    if (_pos.curPacketContentSizeBits != SIZE_UNSET) {
        if (packetTotalSizeCandidateBits < _pos.curPacketContentSizeBits) {
            throw ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError {
                _pos.cursorOffsetInPacketSequenceBits(),
                packetTotalSizeCandidateBits,
                _pos.curPacketContentSizeBits
            };
        }
    }

    if (packetTotalSizeCandidateBits < _pos.cursorOffsetInCurPacketBits) {
        throw ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError {
            _pos.cursorOffsetInPacketSequenceBits(),
            packetTotalSizeCandidateBits,
            _pos.cursorOffsetInCurPacketBits
        };
    }

    _pos.curPacketTotalSizeBits = packetTotalSizeCandidateBits;

    if (_pos.curPacketContentSizeBits == SIZE_UNSET) {
        _pos.curPacketContentSizeBits = _pos.curPacketTotalSizeBits;
    }

    _pos.elems.expectedPacketTotalSize._expectedSize = _pos.curPacketTotalSizeBits;
    this->_updateIterCurOffset(_pos.elems.expectedPacketTotalSize);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPacketContentSize(const Instr& instr)
{
    const auto packetContentSizeCandidateBits = _pos.lastIntVal.u;

    if (_pos.curPacketTotalSizeBits != SIZE_UNSET) {
        if (_pos.curPacketTotalSizeBits < packetContentSizeCandidateBits) {
            throw ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError {
                _pos.cursorOffsetInPacketSequenceBits(),
                _pos.curPacketTotalSizeBits,
                packetContentSizeCandidateBits
            };
        }
    }

    if (packetContentSizeCandidateBits < _pos.cursorOffsetInCurPacketBits) {
        throw ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError {
            _pos.cursorOffsetInPacketSequenceBits(),
            packetContentSizeCandidateBits,
            _pos.cursorOffsetInCurPacketBits
        };
    }

    _pos.curPacketContentSizeBits = packetContentSizeCandidateBits;
    _pos.elems.expectedPacketContentSize._expectedSize = _pos.curPacketContentSizeBits;
    this->_updateIterCurOffset(_pos.elems.expectedPacketContentSize);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execSetPacketMagicNumber(const Instr& instr)
{
    _pos.elems.packetMagicNumber._value = _pos.lastIntVal.u;
    this->_updateIterCurOffset(_pos.elems.packetMagicNumber);
    return _ExecReaction::FETCH_NEXT_INSTR_AND_STOP;
}

Vm::_ExecReaction Vm::_execEndPacketPreambleProc(const Instr& instr)
{
    // after packet header
    _pos.stackPop();
    assert(_pos.stack.empty());

    if (_pos.curDstPacketProc) {
        _pos.loadNewProc(_pos.curDstPacketProc->packetPreambleProc());
        return _ExecReaction::EXEC_CUR_INSTR;
    } else {
        _pos.setState(VmState::END_PACKET_CONTENT);
        return _ExecReaction::CHANGE_STATE;
    }
}

Vm::_ExecReaction Vm::_execEndDstPacketPreambleProc(const Instr& instr)
{
    // after packet context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curDstPacketProc);
    _pos.setState(VmState::BEGIN_EVENT_RECORD);
    return _ExecReaction::CHANGE_STATE;
}

Vm::_ExecReaction Vm::_execEndDstErtPreambleProc(const Instr& instr)
{
    // after second event record context
    _pos.stackPop();
    assert(_pos.stack.empty());
    assert(_pos.curErtProc);
    _pos.loadNewProc(_pos.curErtProc->proc());
    return _ExecReaction::EXEC_CUR_INSTR;
}

Vm::_ExecReaction Vm::_execEndErtProc(const Instr& instr)
{
    // after event record payload
    _pos.stackPop();
    assert(_pos.stack.empty());
    _pos.setState(VmState::END_EVENT_RECORD);
    return _ExecReaction::CHANGE_STATE;
}

} // namespace yactfr
} // namespace internal
