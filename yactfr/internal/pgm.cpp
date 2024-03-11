/*
 * Copyright (C) 2016-2025 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstdint>
#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/trace-type.hpp>

#include "pgm.hpp"
#include "utils.hpp"

namespace yactfr {
namespace internal {

InstrBase::InstrBase(const Opcode opcode) noexcept
{
    this->_unsafeWriteDataU<_opByteRange().upper,
                            _opByteRange().lower>(static_cast<unsigned long long>(opcode));
}

void InstrBase::appendToPgmNucleos(PgmNucleos& nucleos, const Opcode opcode)
{
    const InstrBase instr {opcode};

    nucleos.push_back(*instr.asNucleo());
}

ReadDataInstr::ReadDataInstr(const Opcode opcode, const StructureMemberType * const memberType,
                             const DataType& dt) noexcept :
    InstrBase {opcode},
    _memberTypeAddr {reinterpret_cast<std::uint64_t>(memberType)},
    _dtAddr {reinterpret_cast<std::uint64_t>(&dt)}
{
    this->_writeToBase<_alignByteRange().upper, _alignByteRange().lower>(dt.alignment());
}

void ReadDataInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Opcode opcode,
                                       const StructureMemberType * const memberType,
                                       const DataType& dt)
{
    InstrBase::_appendStaticToPgmNucleos<ReadDataInstr>(nucleos, opcode, memberType, dt);
}

ReadOddFlBitArrayInstr::ReadOddFlBitArrayInstr(const Opcode opcode,
                                               const StructureMemberType * const memberType,
                                               const DataType& dt) noexcept :
    ReadDataInstr {opcode, memberType, dt}
{
    auto& flBitArrayType = dt.asFixedLengthBitArrayType();

    this->_writeToBase<_dataLenByteRange().upper,
                       _dataLenByteRange().lower>(flBitArrayType.length());
}

void ReadOddFlBitArrayInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Opcode opcode,
                                                const StructureMemberType * const memberType,
                                                const DataType& dt)
{
    InstrBase::_appendStaticToPgmNucleos<ReadOddFlBitArrayInstr>(nucleos, opcode, memberType, dt);
}

SaveCurIntInstr::SaveCurIntInstr(const Index pos) noexcept :
    InstrBase {Opcode::SaveCurInt}
{
    this->_writeToBase<_posByteRange().upper, _posByteRange().lower>(pos);
}

void SaveCurIntInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Index pos)
{
    InstrBase::_appendStaticToPgmNucleos<SaveCurIntInstr>(nucleos, pos);
}

UpdateDefClkValFlFromCurIntInstr::UpdateDefClkValFlFromCurIntInstr(const Size curIntLen) noexcept :
    InstrBase {Opcode::UpdateDefClkValFlFromCurInt}
{
    this->_writeToBase<_curIntLenByteRange().upper, _curIntLenByteRange().lower>(curIntLen);
}

void UpdateDefClkValFlFromCurIntInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Size curIntLen)
{
    InstrBase::_appendStaticToPgmNucleos<UpdateDefClkValFlFromCurIntInstr>(nucleos, curIntLen);
}

namespace {

Size slDtLen(const DataType& dt) noexcept
{
    if (dt.isStaticLengthStringType()) {
        return dt.asStaticLengthStringType().maximumLength();
    } else if (dt.isStaticLengthBlobType()) {
        return dt.asStaticLengthBlobType().length();
    } else {
        assert(dt.isStaticLengthArrayType());
        return dt.asStaticLengthArrayType().length();
    }
}

} // namespace

ReadSlDataInstr::ReadSlDataInstr(const Opcode opcode, const StructureMemberType * const memberType,
                                 const DataType& dt) noexcept :
    ReadDataInstr {opcode, memberType, dt},
    _elemCount {static_cast<std::uint64_t>(slDtLen(dt))}
{
}

void ReadSlDataInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Opcode opcode,
                                         const StructureMemberType * const memberType,
                                         const DataType& dt)
{
    InstrBase::_appendStaticToPgmNucleos<ReadSlDataInstr>(nucleos, opcode, memberType, dt);
    InstrBase::appendToPgmNucleos(nucleos, call([opcode] {
        switch (opcode) {
        case Opcode::ReadSlStr:
            return Opcode::EndReadSlStr;

        case Opcode::ReadSlBlob:
            return Opcode::EndReadSlBlob;

        case Opcode::ReadSlUuidBlob:
            return Opcode::EndReadSlUuidBlob;

        default:
            std::abort();
        }
    }));
}

ReadSlArrayInstr::ReadSlArrayInstr(const Opcode opcode,
                                   const StructureMemberType * const memberType,
                                   const DataType& dt, const Size elemPgmLen) noexcept :
    ReadSlDataInstr {opcode, memberType, dt}
{
    this->_writeToBase<_elemPgmByteRange().upper, _elemPgmByteRange().lower>(elemPgmLen);
}

void ReadSlArrayInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Opcode opcode,
                                          const StructureMemberType * const memberType,
                                          const DataType& dt, const PgmNucleos& elemPgmNucleos)
{
    const auto isEmpty = dt.asStaticLengthArrayType().length() == 0;

    InstrBase::_appendStaticToPgmNucleos<ReadSlArrayInstr>(nucleos, opcode, memberType,
                                                           dt,
                                                           isEmpty ? 0 : elemPgmNucleos.size() + 1);

    if (!isEmpty) {
        nucleos.insert(nucleos.end(), elemPgmNucleos.begin(), elemPgmNucleos.end());
        InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadArrayElem);
    }

    InstrBase::appendToPgmNucleos(nucleos,
                                  opcode == Opcode::ReadSlArray ? Opcode::EndReadSlArray :
                                                                  Opcode::EndReadSlUuidArray);
}

ReadDlDataInstr::ReadDlDataInstr(const Opcode opcode, const StructureMemberType * const memberType,
                                 const DataType& dt, const Index savedElemCountPos) noexcept :
    ReadDataInstr {opcode, memberType, dt}
{
    this->_writeToBase<_savedElemCountPosByteRange().upper,
                       _savedElemCountPosByteRange().lower>(savedElemCountPos);
}

void ReadDlDataInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Opcode opcode,
                                         const StructureMemberType * const memberType,
                                         const DataType& dt, const Index savedElemCountPos)
{
    InstrBase::_appendStaticToPgmNucleos<ReadDlDataInstr>(nucleos, opcode, memberType,
                                                          dt, savedElemCountPos);

    if (opcode == Opcode::ReadDlStr) {
        InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadDlStr);
    } else if (opcode == Opcode::ReadDlBlob) {
        InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadDlBlob);
    }
}

ReadDlArrayInstr::ReadDlArrayInstr(const StructureMemberType * const memberType,
                                   const DataType& dt, const Index savedElemCountPos,
                                   const Size elemPgmLen) noexcept :
    ReadDlDataInstr {Opcode::ReadDlArray, memberType, dt, savedElemCountPos},
    _elemPgmLen {static_cast<std::uint64_t>(elemPgmLen)}
{
}

void ReadDlArrayInstr::appendToPgmNucleos(PgmNucleos& nucleos,
                                          const StructureMemberType * const memberType,
                                          const DataType& dt, const Index savedElemCountPos,
                                          const PgmNucleos& elemPgmNucleos)
{
    InstrBase::_appendStaticToPgmNucleos<ReadDlArrayInstr>(nucleos, memberType, dt,
                                                           savedElemCountPos,
                                                           elemPgmNucleos.size() + 1);
    nucleos.insert(nucleos.end(), elemPgmNucleos.begin(), elemPgmNucleos.end());
    InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadArrayElem);
    InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadDlArray);
}

ReadStructInstr::ReadStructInstr(const StructureMemberType * const memberType,
                                 const DataType& dt) noexcept :
    ReadDataInstr {Opcode::ReadStruct, memberType, dt}
{
}

void ReadStructInstr::appendToPgmNucleos(PgmNucleos& nucleos, const StructureMemberType * const memberType,
                                         const DataType& dt, const PgmNucleos& membersPgm)
{
    InstrBase::_appendStaticToPgmNucleos<ReadStructInstr>(nucleos, memberType, dt);
    nucleos.insert(nucleos.end(), membersPgm.begin(), membersPgm.end());
    InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadStruct);
}

ReadOptWithBoolSelInstr::ReadOptWithBoolSelInstr(const StructureMemberType * const memberType,
                                                 const DataType& dt, const Index savedSelPos,
                                                 const Size pgmLen) noexcept :
    ReadDataInstr {Opcode::ReadOptWithBoolSel, memberType, dt},
    _pgmLen {static_cast<std::uint64_t>(pgmLen)}
{
    this->_writeToBase<_savedSelPosByteRange().upper, _savedSelPosByteRange().lower>(savedSelPos);
}

void ReadOptWithBoolSelInstr::appendToPgmNucleos(PgmNucleos& nucleos,
                                                 const StructureMemberType * const memberType,
                                                 const DataType& dt, const Index savedSelPos,
                                                 const PgmNucleos& pgmNucleos)
{
    InstrBase::_appendStaticToPgmNucleos<ReadOptWithBoolSelInstr>(nucleos, memberType, dt,
                                                                  savedSelPos, pgmNucleos.size());
    nucleos.insert(nucleos.end(), pgmNucleos.begin(), pgmNucleos.end());
    InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadOptWithBoolSel);
}

ReadScopeInstr::ReadScopeInstr(const Scope scope) noexcept :
    InstrBase {Opcode::ReadScope}
{
    this->_writeToBase<_scopeByteRange().upper,
                       _scopeByteRange().lower>(static_cast<unsigned long long>(scope));
}

void ReadScopeInstr::appendToPgmNucleos(PgmNucleos& nucleos, const Scope scope,
                                        const PgmNucleos& scopePgmNucleos)
{
    InstrBase::_appendStaticToPgmNucleos<ReadScopeInstr>(nucleos, scope);
    nucleos.insert(nucleos.end(), scopePgmNucleos.begin(), scopePgmNucleos.end());
    InstrBase::appendToPgmNucleos(nucleos, Opcode::EndReadScope);
}

ErPgm::ErPgm(const EventRecordType& eventRecordType, PgmNucleos pgm) :
    _ert {&eventRecordType},
    _pgm {std::move(pgm)}
{
    InstrBase::appendToPgmNucleos(_pgm, InstrBase::Opcode::EndReadEr);
}

DsPktPgm::DsPktPgm(const DataStreamType& dst, PgmNucleos pktPreamblePgm, PgmNucleos erPreamblePgm,
                   ErPgmMap erPgms) :
    _dst {&dst},
    _pktPreamblePgm {std::move(pktPreamblePgm)},
    _erPreamblePgm {std::move(erPreamblePgm)},
    _erPgmsMap {std::move(erPgms)}
{
    InstrBase::appendToPgmNucleos(_pktPreamblePgm, InstrBase::Opcode::EndReadDsPktPreamble);
    InstrBase::appendToPgmNucleos(_erPreamblePgm, InstrBase::Opcode::EndReadDsErPreamble);

    // fill event record program vector (allow a few holes)
    _erPgmsVec.resize(dst.eventRecordTypes().size() * 2);

    for (auto& idErPgmUpPair : erPgms) {
        if (idErPgmUpPair.first < _erPgmsVec.size()) {
            _erPgmsVec[idErPgmUpPair.first] = &idErPgmUpPair.second;
        }
    }

    // set event record alignment
    if (_dst->eventRecordHeaderType()) {
        _erAlign = _dst->eventRecordHeaderType()->alignment();
    } else if (_dst->eventRecordCommonContextType()) {
        _erAlign = _dst->eventRecordCommonContextType()->alignment();
    } else {
        assert(_dst->eventRecordTypes().size() <= 1);

        if (!_dst->eventRecordTypes().empty()) {
            auto& ert = **_dst->eventRecordTypes().begin();

            if (ert.specificContextType()) {
                _erAlign = ert.specificContextType()->alignment();
            } else if (ert.payloadType()) {
                _erAlign = ert.payloadType()->alignment();
            }
        }
    }
}

const ErPgm *DsPktPgm::operator[](const TypeId id) const noexcept
{
    if (id < _erPgmsVec.size()) {
        return _erPgmsVec[id];
    }

    // fall back on map
    const auto it = _erPgmsMap.find(id);

    if (it == _erPgmsMap.end()) {
        return nullptr;
    }

    return &it->second;
}

const ErPgm& DsPktPgm::uniqueErPgm() const noexcept
{
    assert(this->erPgmsCount() == 1);
    assert(_erPgmsMap.size() == 1);
    return _erPgmsMap.begin()->second;
}

PktPgm::PktPgm(const TraceType& traceType, PgmNucleos preamblePgm, DsPktPgms dsPktPgms,
               const Size savedValsCount) :
    _traceType {&traceType},
    _preamblePgm {std::move(preamblePgm)},
    _dsPktPgms {std::move(dsPktPgms)},
    _savedValsCount {savedValsCount}
{
    InstrBase::appendToPgmNucleos(_preamblePgm, InstrBase::Opcode::EndReadPktPreamble);
}

const DsPktPgm *PktPgm::operator[](const TypeId id) const noexcept
{
    const auto it = _dsPktPgms.find(id);

    if (it == _dsPktPgms.end()) {
        return nullptr;
    }

    return &it->second;
}

const DsPktPgm& PktPgm::uniqueDsPktPgm() const noexcept
{
    assert(this->dsPktPgmsCount() == 1);
    assert(_dsPktPgms.size() == 1);
    return _dsPktPgms.begin()->second;
}

} // namespace internal
} // namespace yactfr
