/*
 * Copyright (C) 2016-2025 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <boost/optional/optional.hpp>
#include <cstdlib>
#include <unordered_map>
#include <cassert>

#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/dl-blob-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/dt-visitor.hpp>
#include <yactfr/metadata/dt.hpp>
#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/fl-bit-map-type.hpp>
#include <yactfr/metadata/fl-bool-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/non-nt-str-type.hpp>
#include <yactfr/metadata/nt-str-type.hpp>
#include <yactfr/metadata/opt-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/vl-int-type.hpp>

#include "build-pkt-pgm.hpp"
#include "pgm.hpp"
#include "utils.hpp"
#include "yactfr/metadata/dst.hpp"
#include "yactfr/metadata/ert.hpp"
#include "yactfr/metadata/int-type-common.hpp"

namespace yactfr {
namespace internal {
namespace {

class CoucheTard;

/*
 * A simple data type visitor which forwards specific visiting methods
 * to CoucheTard::_analyze().
 */
class CoucheTardDtVisitor final :
    public DataTypeVisitor
{
public:
    explicit CoucheTardDtVisitor(CoucheTard& ct) noexcept :
        _ct {&ct}
    {
    }

private:
    void visit(const StaticLengthArrayType& dt) override;
    void visit(const DynamicLengthArrayType& dt) override;
    void visit(const DynamicLengthBlobType& dt) override;
    void visit(const DynamicLengthStringType& dt) override;
    void visit(const StructureType& dt) override;
    void visit(const VariantWithUnsignedIntegerSelectorType& dt) override;
    void visit(const VariantWithSignedIntegerSelectorType& dt) override;
    void visit(const OptionalWithBooleanSelectorType& dt) override;
    void visit(const OptionalWithUnsignedIntegerSelectorType& dt) override;
    void visit(const OptionalWithSignedIntegerSelectorType& dt) override;

private:
    CoucheTard *_ct;
};

/*
 * A Couche-Tard computes and then makes available, for a given
 * trace type:
 *
 * For a dynamic data type:
 *     The saved position of the value of the length/selector of
 *     an instance.
 *
 *     Use dynDtSavedValPos().
 *
 * For a key integer type:
 *     The position(s) where to save the value of an instance.
 *
 *     Use keyIntTypeSavedValPoss(), which may return `nullptr`.
 *
 * Saved value positions are reused as much as possible. For example,
 * the saved value position of the first key integer type of any packet
 * context type is always the same because there's only one current
 * packet when decoding. The same logic applies to event record types.
 * `_nextSavedValPos` is always the next saved value position to use and
 * _assignNewSavedValPos() keeps its maximum value
 * into `_savedValsCount`.
 *
 * Get the total number of saved value positions with savedValsCount().
 */
class CoucheTard final
{
    friend class CoucheTardDtVisitor;

public:
    explicit CoucheTard(const TraceType& traceType) :
        _traceType {&traceType}
    {
        this->_analyze();
    }

    Index dynDtSavedValPos(const DataType& dt) const noexcept
    {
        assert(_dynDtSavedValPosMap.count(&dt) == 1);
        return _dynDtSavedValPosMap.at(&dt);
    }

    const std::unordered_set<Index> *keyIntTypeSavedValPoss(const DataType& dt) const noexcept
    {
        const auto it = _keyIntTypeSavedValPossMap.find(&dt);

        if (it == _keyIntTypeSavedValPossMap.end()) {
            return nullptr;
        }

        return &it->second;
    }

    Size savedValsCount() const noexcept
    {
        return _savedValsCount;
    }

private:
    void _analyze(const DynamicLengthArrayType& dlArrayType)
    {
        this->_assignNewSavedValPos(dlArrayType, dlArrayType.lengthTypes());
        this->_analyze(dlArrayType.elementType());
    }

    void _analyze(const DynamicLengthStringType& dlStrType)
    {
        this->_assignNewSavedValPos(dlStrType, dlStrType.maximumLengthTypes());
    }

    void _analyze(const DynamicLengthBlobType& dlBlobType)
    {
        this->_assignNewSavedValPos(dlBlobType, dlBlobType.lengthTypes());
    }

    void _analyze(const StaticLengthArrayType& slArrayType)
    {
        this->_analyze(slArrayType.elementType());
    }

    void _analyze(const StructureType& structType)
    {
        for (auto& memberType : structType.memberTypes()) {
            this->_analyze(memberType->dataType());
        }
    }

    template <typename VarTypeT>
    void _analyzeVarType(const VarTypeT& varType)
    {
        this->_assignNewSavedValPos(varType, varType.selectorTypes());

        for (auto& opt : varType) {
            this->_analyze(opt->dataType());
        }
    }

    void _analyze(const OptionalType& optType)
    {
        this->_assignNewSavedValPos(optType, optType.selectorTypes());
        this->_analyze(optType.dataType());
    }

    void _analyze(const DataType& dt)
    {
        CoucheTardDtVisitor visitor {*this};

        dt.accept(visitor);
    }

    void _analyze(const StructureType * const dt)
    {
        if (!dt) {
            return;
        }

        this->_analyze(*dt);
    }

    void _analyze()
    {
        this->_analyze(_traceType->packetHeaderType());

        const auto baseDstNextPos = _nextSavedValPos;

        for (auto& dst : *_traceType) {
            _nextSavedValPos = baseDstNextPos;
            this->_analyze(dst->packetContextType());
            this->_analyze(dst->eventRecordHeaderType());
            this->_analyze(dst->eventRecordCommonContextType());

            const auto baseErNextPos = _nextSavedValPos;

            for (auto& ert : *dst) {
                _nextSavedValPos = baseErNextPos;
                this->_analyze(ert->specificContextType());
                this->_analyze(ert->payloadType());
            }
        }
    }

    void _assignNewSavedValPos(const DataType& dynDt, const DataTypeSet& keyDts)
    {
        _dynDtSavedValPosMap[&dynDt] = _nextSavedValPos;

        for (const auto keyDt : keyDts) {
            _keyIntTypeSavedValPossMap[keyDt].insert(_nextSavedValPos);
        }

        ++_nextSavedValPos;
        _savedValsCount = std::max(_savedValsCount, _nextSavedValPos);
    }

private:
    const TraceType *_traceType;
    Index _nextSavedValPos = 0;
    Size _savedValsCount = 0;
    std::unordered_map<const DataType *, Index> _dynDtSavedValPosMap;
    std::unordered_map<const DataType *, std::unordered_set<Index>> _keyIntTypeSavedValPossMap;
};

void CoucheTardDtVisitor::visit(const StaticLengthArrayType& dt)
{
    _ct->_analyze(dt);
}

void CoucheTardDtVisitor::visit(const DynamicLengthArrayType& dt)
{
    _ct->_analyze(dt);
}

void CoucheTardDtVisitor::visit(const DynamicLengthBlobType& dt)
{
    _ct->_analyze(dt);
}

void CoucheTardDtVisitor::visit(const DynamicLengthStringType& dt)
{
    _ct->_analyze(dt);
}

void CoucheTardDtVisitor::visit(const StructureType& dt)
{
    _ct->_analyze(dt);
}

void CoucheTardDtVisitor::visit(const VariantWithUnsignedIntegerSelectorType& dt)
{
    _ct->_analyzeVarType(dt);
}

void CoucheTardDtVisitor::visit(const VariantWithSignedIntegerSelectorType& dt)
{
    _ct->_analyzeVarType(dt);
}

void CoucheTardDtVisitor::visit(const OptionalWithBooleanSelectorType& dt)
{
    _ct->_analyze(dt);
}

void CoucheTardDtVisitor::visit(const OptionalWithUnsignedIntegerSelectorType& dt)
{
    _ct->_analyze(dt);
}

void CoucheTardDtVisitor::visit(const OptionalWithSignedIntegerSelectorType& dt)
{
    _ct->_analyze(dt);
}

class Builder;

/*
 * Companion of `Builder` to forward specific visiting methods to
 * Builder::_appendRead*InstrFromDt().
 */
class BuilderDtVisitor final :
    public DataTypeVisitor
{
public:
    explicit BuilderDtVisitor(Builder& builder, const StructureMemberType * const memberType,
                              PgmNucleos& pgm) noexcept :
        _builder {&builder},
        _memberType {memberType},
        _pgm {&pgm}
    {
    }

private:
    void visit(const FixedLengthBitArrayType& dt) override;
    void visit(const FixedLengthBitMapType& dt) override;
    void visit(const FixedLengthBooleanType& dt) override;
    void visit(const FixedLengthSignedIntegerType& dt) override;
    void visit(const FixedLengthUnsignedIntegerType& dt) override;
    void visit(const FixedLengthFloatingPointNumberType& dt) override;
    void visit(const VariableLengthSignedIntegerType& dt) override;
    void visit(const VariableLengthUnsignedIntegerType& dt) override;
    void visit(const NullTerminatedStringType& dt) override;
    void visit(const StructureType& dt) override;
    void visit(const StaticLengthArrayType& dt) override;
    void visit(const DynamicLengthArrayType& dt) override;
    void visit(const StaticLengthStringType& dt) override;
    void visit(const DynamicLengthStringType& dt) override;
    void visit(const StaticLengthBlobType& dt) override;
    void visit(const DynamicLengthBlobType& dt) override;
    void visit(const VariantWithUnsignedIntegerSelectorType& dt) override;
    void visit(const VariantWithSignedIntegerSelectorType& dt) override;
    void visit(const OptionalWithBooleanSelectorType& dt) override;
    void visit(const OptionalWithUnsignedIntegerSelectorType& dt) override;
    void visit(const OptionalWithSignedIntegerSelectorType& dt) override;

private:
    Builder *_builder;
    const StructureMemberType * const _memberType;
    PgmNucleos *_pgm;
};

class Builder final
{
    friend class BuilderDtVisitor;

public:
    explicit Builder(const TraceType& traceType) :
        _traceType {&traceType},
        _ct {traceType}
    {
        this->_build();
    }

    PktPgm pktPgm() const noexcept
    {
        return PktPgm {
            *_traceType, std::move(_pktPreamblePgm),
            std::move(_dsPktPgms), _ct.savedValsCount()
        };
    }

private:
    /*
     * The strategy here is to:
     *
     * 1. Build a Couche-Tard, which holds the saved value positions for
     *    all dynamic and key data types.
     *
     * 2. Process the data types of the trace type tree in a preorder
     *    fashion to create programs containing instructions:
     *
     *    • Translate any data type to its corresponding
     *      reading instruction.
     *
     *      For example:
     *
     *      ‣ A big-endian, byte-aligned, 32-bit fixed-length unsigned
     *        integer type translates to the
     *        `InstrBase::Opcode::ReadFlUIntA32Be` opcode.
     *
     *      ‣ A dynamic-length BLOB type translates to the
     *        `InstrBase::Opcode::ReadDlBlob` opcode.
     *
     *    • For each unsigned integer type having roles, append the
     *      corresponding instructions.
     *
     *      For example, the
     *      `UnsignedIntegerTypeRole::PacketTotalLength` role translates
     *      to the `InstrBase::Opcode::SetPktTotalLenFromCurInt` opcode.
     *
     *    • For each boolean/integer type: use
     *      CoucheTard::keyIntTypeSavedValPoss() to find the position(s)
     *      where to save the value of an instance. Any returned
     *      position becomes a single `SaveCurIntInstr` instruction.
     *
     *    • For each static-length array having the "metadata stream
     *      UUID" role, use the
     *      `InstrBase::Opcode::ReadSlUuidArray` opcode.
     *
     *    • For each static-length BLOB having the "metadata stream
     *      UUID" role, use the
     *      `InstrBase::Opcode::ReadSlUuidBlob` opcode.
     *
     *    • For each dynamic data type, use
     *      CoucheTard::dynDtSavedValPos() to find the position of the
     *      saved length/selector of an instance. This is part of the
     *      instruction data.
     */
    void _build()
    {
        // build packet preamble program
        {
            // packet header
            _hasDstIdRole = false;
            this->_tryAppendReadScopeInstrFromDt(Scope::PacketHeader, _traceType->packetHeaderType(),
                                                 _pktPreamblePgm);

            // append "set data stream type" instruction
            InstrBase::appendToPgmNucleos(_pktPreamblePgm,
                                          _hasDstIdRole ? InstrBase::Opcode::SetDstFromCurTypeId :
                                                          InstrBase::Opcode::SetDstFromUnique);

            // append "set data stream info" instruction
            InstrBase::appendToPgmNucleos(_pktPreamblePgm, InstrBase::Opcode::SetDsInfo);
        }

        // build per-DST programs
        for (auto& dst : _traceType->dataStreamTypes()) {
            _dsPktPgms.emplace(dst->id(), this->_buildDsPktPgm(*dst));
        }
    }

    DsPktPgm _buildDsPktPgm(const DataStreamType& dst)
    {
        // build packet preamble program
        auto pktPreamblePgm = call([this, &dst] {
            PgmNucleos pgm;

            // packet context
            this->_tryAppendReadScopeInstrFromDt(Scope::PacketContext, dst.packetContextType(),
                                                 pgm);

            // append "set packet info" instruction
            InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetPktInfo);

            return pgm;
        });

        // build event record preamble program
        auto erPreamblePgm = call([this, &dst] {
            PgmNucleos pgm;

            // event record header
            _hasErtIdRole = false;
            this->_tryAppendReadScopeInstrFromDt(Scope::EventRecordHeader, dst.eventRecordHeaderType(),
                                                 pgm);

            // append "set event record type" instruction
            InstrBase::appendToPgmNucleos(pgm, _hasErtIdRole ? InstrBase::Opcode::SetErtFromCurTypeId :
                                                               InstrBase::Opcode::SetErtFromUnique);

            // append "set event record info" instruction
            InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetErInfo);

            // common event record context
            this->_tryAppendReadScopeInstrFromDt(Scope::EventRecordCommonContext,
                                                 dst.eventRecordCommonContextType(), pgm);

            return pgm;
        });

        // build per-ERT programs
        auto erPgms = call([this, &dst] {
            DsPktPgm::ErPgmMap pgms;

            for (auto& ert : dst.eventRecordTypes()) {
                pgms.emplace(ert->id(), this->_buildErPgm(*ert));
            }

            return pgms;
        });

        return DsPktPgm {
            dst, std::move(pktPreamblePgm), std::move(erPreamblePgm), std::move(erPgms)
        };
    }

    ErPgm _buildErPgm(const EventRecordType& ert)
    {
        PgmNucleos pgm;

        // specific context
        this->_tryAppendReadScopeInstrFromDt(Scope::EventRecordSpecificContext,
                                             ert.specificContextType(), pgm);

        // payload
        this->_tryAppendReadScopeInstrFromDt(Scope::EventRecordPayload,
                                             ert.payloadType(), pgm);

        return ErPgm {ert, std::move(pgm)};
    }

    void _tryAppendReadScopeInstrFromDt(const Scope scope, const StructureType * const dt,
                                        PgmNucleos& pgm)
    {
        if (!dt) {
            return;
        }

        PgmNucleos scopePgm;

        this->_appendReadDataInstrFromDt(*dt, nullptr, scopePgm);
        ReadScopeInstr::appendToPgmNucleos(pgm, scope, scopePgm);
    }

    void _tryAppendSaveCurIntInstr(const DataType& dt, PgmNucleos& pgm)
    {
        const auto savedValPoss = _ct.keyIntTypeSavedValPoss(dt);

        if (savedValPoss) {
            for (const auto pos : *savedValPoss) {
                SaveCurIntInstr::appendToPgmNucleos(pgm, pos);
            }
        }
    }

    void _appendReadDataInstrFromDt(const FixedLengthBitArrayType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        const auto opcode = call([&dt] {
            if (dt.byteOrder() == ByteOrder::Little) {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitArrayA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitArrayA16Le;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitArrayA32Le;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitArrayA64Le;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitArrayLe;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitArrayA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitArrayA16LeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitArrayA32LeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitArrayA64LeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitArrayLeRev;
                }
            } else {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitArrayA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitArrayA16BeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitArrayA32BeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitArrayA64BeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitArrayBeRev;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitArrayA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitArrayA16Be;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitArrayA32Be;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitArrayA64Be;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitArrayBe;
                }
            }
        });

        switch (opcode) {
        case InstrBase::Opcode::ReadFlBitArrayLe:
        case InstrBase::Opcode::ReadFlBitArrayLeRev:
        case InstrBase::Opcode::ReadFlBitArrayBe:
        case InstrBase::Opcode::ReadFlBitArrayBeRev:
            ReadOddFlBitArrayInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;

        default:
            ReadDataInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;
        }
    }

    void _appendReadDataInstrFromDt(const FixedLengthBitMapType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        const auto opcode = call([&dt] {
            if (dt.byteOrder() == ByteOrder::Little) {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitMapA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitMapA16Le;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitMapA32Le;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitMapA64Le;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitMapLe;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitMapA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitMapA16LeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitMapA32LeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitMapA64LeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitMapLeRev;
                }
            } else {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitMapA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitMapA16BeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitMapA32BeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitMapA64BeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitMapBeRev;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBitMapA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlBitMapA16Be;

                        case 32:
                            return InstrBase::Opcode::ReadFlBitMapA32Be;

                        case 64:
                            return InstrBase::Opcode::ReadFlBitMapA64Be;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBitMapBe;
                }
            }
        });

        switch (opcode) {
        case InstrBase::Opcode::ReadFlBitMapLe:
        case InstrBase::Opcode::ReadFlBitMapLeRev:
        case InstrBase::Opcode::ReadFlBitMapBe:
        case InstrBase::Opcode::ReadFlBitMapBeRev:
            ReadOddFlBitArrayInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;

        default:
            ReadDataInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;
        }
    }

    void _appendReadDataInstrFromDt(const FixedLengthBooleanType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        const auto opcode = call([&dt] {
            if (dt.byteOrder() == ByteOrder::Little) {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBoolA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlBoolA16Le;

                        case 32:
                            return InstrBase::Opcode::ReadFlBoolA32Le;

                        case 64:
                            return InstrBase::Opcode::ReadFlBoolA64Le;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBoolLe;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBoolA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlBoolA16LeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlBoolA32LeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlBoolA64LeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBoolLeRev;
                }
            } else {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBoolA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlBoolA16BeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlBoolA32BeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlBoolA64BeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBoolBeRev;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlBoolA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlBoolA16Be;

                        case 32:
                            return InstrBase::Opcode::ReadFlBoolA32Be;

                        case 64:
                            return InstrBase::Opcode::ReadFlBoolA64Be;
                        }
                    }

                    return InstrBase::Opcode::ReadFlBoolBe;
                }
            }
        });

        // append "read data" instruction first
        switch (opcode) {
        case InstrBase::Opcode::ReadFlBoolLe:
        case InstrBase::Opcode::ReadFlBoolLeRev:
        case InstrBase::Opcode::ReadFlBoolBe:
        case InstrBase::Opcode::ReadFlBoolBeRev:
            ReadOddFlBitArrayInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;

        default:
            ReadDataInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;
        }

        // append one or more "save current integer" instructions if needed
        this->_tryAppendSaveCurIntInstr(dt, pgm);
    }

    void _appendReadDataInstrFromDt(const FixedLengthSignedIntegerType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        const auto opcode = call([&dt] {
            if (dt.byteOrder() == ByteOrder::Little) {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlSIntA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlSIntA16Le;

                        case 32:
                            return InstrBase::Opcode::ReadFlSIntA32Le;

                        case 64:
                            return InstrBase::Opcode::ReadFlSIntA64Le;
                        }
                    }

                    return InstrBase::Opcode::ReadFlSIntLe;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlSIntA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlSIntA16LeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlSIntA32LeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlSIntA64LeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlSIntLeRev;
                }
            } else {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlSIntA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlSIntA16BeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlSIntA32BeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlSIntA64BeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlSIntBeRev;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlSIntA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlSIntA16Be;

                        case 32:
                            return InstrBase::Opcode::ReadFlSIntA32Be;

                        case 64:
                            return InstrBase::Opcode::ReadFlSIntA64Be;
                        }
                    }

                    return InstrBase::Opcode::ReadFlSIntBe;
                }
            }
        });

        // append "read data" instruction first
        switch (opcode) {
        case InstrBase::Opcode::ReadFlSIntLe:
        case InstrBase::Opcode::ReadFlSIntLeRev:
        case InstrBase::Opcode::ReadFlSIntBe:
        case InstrBase::Opcode::ReadFlSIntBeRev:
            ReadOddFlBitArrayInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;

        default:
            ReadDataInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;
        }

        // append one or more "save current integer" instructions if needed
        this->_tryAppendSaveCurIntInstr(dt, pgm);
    }

    template <typename DtT>
    void _finishAppendReadUIntInstrFromDt(const DtT& dt, const boost::optional<Size>& uIntLen,
                                          PgmNucleos& pgm)
    {
        // append one or more "save current integer" instructions if needed
        this->_tryAppendSaveCurIntInstr(dt, pgm);

        // append one or more role execution instructions
        for (const auto role : dt.roles()) {
            switch (role) {
            case UnsignedIntegerTypeRole::DataStreamId:
                InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetDsIdFromCurInt);
                break;

            case UnsignedIntegerTypeRole::DataStreamTypeId:
            case UnsignedIntegerTypeRole::EventRecordTypeId:
                if (role == UnsignedIntegerTypeRole::DataStreamTypeId) {
                    _hasDstIdRole = true;
                } else {
                    _hasErtIdRole = true;
                }

                InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetCurTypeIdFromCurInt);
                break;

            case UnsignedIntegerTypeRole::DefaultClockTimestamp:
                if (uIntLen) {
                    UpdateDefClkValFlFromCurIntInstr::appendToPgmNucleos(pgm, *uIntLen);
                } else {
                    InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::UpdateDefClkValVlFromCurInt);
                }

                break;

            case UnsignedIntegerTypeRole::DiscardedEventRecordCounterSnapshot:
                InstrBase::appendToPgmNucleos(pgm,
                                              InstrBase::Opcode::SetPktDiscErCounterSnapFromCurInt);
                break;

            case UnsignedIntegerTypeRole::PacketContentLength:
                InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetPktContentLenFromCurInt);
                break;

            case UnsignedIntegerTypeRole::PacketEndDefaultClockTimestamp:
                InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetPktEndDefClkValFromCurInt);
                break;

            case UnsignedIntegerTypeRole::PacketMagicNumber:
                InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetPktMagicNumberFromCurInt);
                break;

            case UnsignedIntegerTypeRole::PacketSequenceNumber:
                InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetPktSeqNumFromCurInt);
                break;

            case UnsignedIntegerTypeRole::PacketTotalLength:
                InstrBase::appendToPgmNucleos(pgm, InstrBase::Opcode::SetPktTotalLenFromCurInt);
                break;

            default:
                std::abort();
            }
        }
    }

    void _appendReadDataInstrFromDt(const FixedLengthUnsignedIntegerType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        const auto opcode = call([&dt] {
            if (dt.byteOrder() == ByteOrder::Little) {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlUIntA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlUIntA16Le;

                        case 32:
                            return InstrBase::Opcode::ReadFlUIntA32Le;

                        case 64:
                            return InstrBase::Opcode::ReadFlUIntA64Le;
                        }
                    }

                    return InstrBase::Opcode::ReadFlUIntLe;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlUIntA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlUIntA16LeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlUIntA32LeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlUIntA64LeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlUIntLeRev;
                }
            } else {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlUIntA8Rev;

                        case 16:
                            return InstrBase::Opcode::ReadFlUIntA16BeRev;

                        case 32:
                            return InstrBase::Opcode::ReadFlUIntA32BeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlUIntA64BeRev;
                        }
                    }

                    return InstrBase::Opcode::ReadFlUIntBeRev;
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 8:
                            return InstrBase::Opcode::ReadFlUIntA8;

                        case 16:
                            return InstrBase::Opcode::ReadFlUIntA16Be;

                        case 32:
                            return InstrBase::Opcode::ReadFlUIntA32Be;

                        case 64:
                            return InstrBase::Opcode::ReadFlUIntA64Be;
                        }
                    }

                    return InstrBase::Opcode::ReadFlUIntBe;
                }
            }
        });

        // append "read data" instruction first
        switch (opcode) {
        case InstrBase::Opcode::ReadFlUIntLe:
        case InstrBase::Opcode::ReadFlUIntLeRev:
        case InstrBase::Opcode::ReadFlUIntBe:
        case InstrBase::Opcode::ReadFlUIntBeRev:
            ReadOddFlBitArrayInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;

        default:
            ReadDataInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;
        }

        /*
         * Append "save current integer" and role execution instructions
         * if needed.
         */
        this->_finishAppendReadUIntInstrFromDt(dt, dt.length(), pgm);
    }

    void _appendReadDataInstrFromDt(const FixedLengthFloatingPointNumberType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        const auto opcode = call([&dt] {
            if (dt.byteOrder() == ByteOrder::Little) {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloatA32Le;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloatA64Le;

                        default:
                            std::abort();
                        }
                    } else {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloat32Le;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloat64Le;

                        default:
                            std::abort();
                        }
                    }
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloatA32LeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloatA64LeRev;

                        default:
                            std::abort();
                        }
                    } else {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloat32LeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloat64LeRev;

                        default:
                            std::abort();
                        }
                    }
                }
            } else {
                if (dt.bitOrder() == BitOrder::FirstToLast) {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloatA32BeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloatA64BeRev;

                        default:
                            std::abort();
                        }
                    } else {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloat32BeRev;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloat64BeRev;

                        default:
                            std::abort();
                        }
                    }
                } else {
                    if (dt.alignment() % 8 == 0) {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloatA32Be;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloatA64Be;

                        default:
                            std::abort();
                        }
                    } else {
                        switch (dt.length()) {
                        case 32:
                            return InstrBase::Opcode::ReadFlFloat32Be;

                        case 64:
                            return InstrBase::Opcode::ReadFlFloat64Be;

                        default:
                            std::abort();
                        }
                    }
                }
            }
        });

        switch (opcode) {
        case InstrBase::Opcode::ReadFlFloat32Le:
        case InstrBase::Opcode::ReadFlFloat32LeRev:
        case InstrBase::Opcode::ReadFlFloat32Be:
        case InstrBase::Opcode::ReadFlFloat32BeRev:
        case InstrBase::Opcode::ReadFlFloat64Le:
        case InstrBase::Opcode::ReadFlFloat64LeRev:
        case InstrBase::Opcode::ReadFlFloat64Be:
        case InstrBase::Opcode::ReadFlFloat64BeRev:
            ReadOddFlBitArrayInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;

        default:
            ReadDataInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
            break;
        }
    }

    void _appendReadDataInstrFromDt(const VariableLengthSignedIntegerType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        // append "read data" instruction first
        ReadDataInstr::appendToPgmNucleos(pgm, InstrBase::Opcode::ReadVlSInt, memberType, dt);

        // append one or more "save current integer" instructions if needed
        this->_tryAppendSaveCurIntInstr(dt, pgm);
    }

    void _appendReadDataInstrFromDt(const VariableLengthUnsignedIntegerType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        // append "read data" instruction first
        ReadDataInstr::appendToPgmNucleos(pgm, InstrBase::Opcode::ReadVlUInt, memberType, dt);

        /*
         * Append "save current integer" and role execution instructions
         * if needed.
         */
        this->_finishAppendReadUIntInstrFromDt(dt, boost::none, pgm);
    }

    void _appendReadDataInstrFromDt(const NullTerminatedStringType& dt,
                                    const StructureMemberType * const memberType,
                                    PgmNucleos& pgm)
    {
        const auto opcode = call([&dt] {
            switch (dt.encoding()) {
            case StringEncoding::Utf8:
                return InstrBase::Opcode::ReadNtStrUtf8;

            case StringEncoding::Utf16Be:
            case StringEncoding::Utf16Le:
                return InstrBase::Opcode::ReadNtStrUtf16;

            case StringEncoding::Utf32Be:
            case StringEncoding::Utf32Le:
                return InstrBase::Opcode::ReadNtStrUtf32;
            }

            std::abort();
        });

        ReadDataInstr::appendToPgmNucleos(pgm, opcode, memberType, dt);
    }

    void _appendReadDataInstrFromDt(const StructureType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        PgmNucleos membersPgm;

        for (auto& innerMemberType : dt) {
            this->_appendReadDataInstrFromDt(innerMemberType->dataType(), innerMemberType.get(),
                                             membersPgm);
        }

        ReadStructInstr::appendToPgmNucleos(pgm, memberType, dt, membersPgm);
    }

    PgmNucleos _elemPgmFromDt(const ArrayType& dt)
    {
        PgmNucleos elemPgm;

        this->_appendReadDataInstrFromDt(dt.elementType(), nullptr, elemPgm);
        return elemPgm;
    }

    void _appendReadDataInstrFromDt(const StaticLengthArrayType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        ReadSlArrayInstr::appendToPgmNucleos(pgm,
                                             dt.hasMetadataStreamUuidRole() ? InstrBase::Opcode::ReadSlUuidArray :
                                                                              InstrBase::Opcode::ReadSlArray,
                                             memberType, dt, this->_elemPgmFromDt(dt));
    }

    void _appendReadDataInstrFromDt(const DynamicLengthArrayType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        ReadDlArrayInstr::appendToPgmNucleos(pgm, memberType, dt, _ct.dynDtSavedValPos(dt),
                                             this->_elemPgmFromDt(dt));
    }

    void _appendReadDataInstrFromDt(const StaticLengthStringType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        ReadSlDataInstr::appendToPgmNucleos(pgm, InstrBase::Opcode::ReadSlStr, memberType, dt);
    }

    void _appendReadDataInstrFromDt(const DynamicLengthStringType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        ReadDlDataInstr::appendToPgmNucleos(pgm, InstrBase::Opcode::ReadDlStr, memberType, dt,
                                            _ct.dynDtSavedValPos(dt));
    }

    void _appendReadDataInstrFromDt(const StaticLengthBlobType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        ReadSlDataInstr::appendToPgmNucleos(pgm,
                                            dt.hasMetadataStreamUuidRole() ? InstrBase::Opcode::ReadSlUuidBlob :
                                                                             InstrBase::Opcode::ReadSlBlob,
                                            memberType, dt);
    }

    void _appendReadDataInstrFromDt(const DynamicLengthBlobType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        ReadDlDataInstr::appendToPgmNucleos(pgm, InstrBase::Opcode::ReadDlBlob, memberType, dt,
                                            _ct.dynDtSavedValPos(dt));
    }

    template <typename InstrT, typename DtT>
    void _appendReadVarInstrFromDt(const DtT& dt, const StructureMemberType * const memberType,
                                   PgmNucleos& pgm)
    {
        std::vector<PgmNucleos> optPgms;

        for (auto& opt : dt) {
            PgmNucleos optPgm;

            this->_appendReadDataInstrFromDt(opt->dataType(), nullptr, optPgm);
            optPgms.emplace_back(std::move(optPgm));
        }

        InstrT::appendToPgmNucleos(pgm, memberType, dt, _ct.dynDtSavedValPos(dt), optPgms);
    }

    void _appendReadDataInstrFromDt(const VariantWithUnsignedIntegerSelectorType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        this->_appendReadVarInstrFromDt<ReadVarWithUIntSelInstr>(dt, memberType, pgm);
    }

    void _appendReadDataInstrFromDt(const VariantWithSignedIntegerSelectorType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        this->_appendReadVarInstrFromDt<ReadVarWithSIntSelInstr>(dt, memberType, pgm);
    }

    template <typename InstrT, typename DtT>
    void _appendReadOptInstrFromDt(const DtT& dt, const StructureMemberType * const memberType,
                                   PgmNucleos& pgm)
    {
        PgmNucleos optPgm;

        this->_appendReadDataInstrFromDt(dt.dataType(), nullptr, optPgm);
        InstrT::appendToPgmNucleos(pgm, memberType, dt, _ct.dynDtSavedValPos(dt), optPgm);
    }

    void _appendReadDataInstrFromDt(const OptionalWithBooleanSelectorType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        this->_appendReadOptInstrFromDt<ReadOptWithBoolSelInstr>(dt, memberType, pgm);
    }

    void _appendReadDataInstrFromDt(const OptionalWithUnsignedIntegerSelectorType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        this->_appendReadOptInstrFromDt<ReadOptWithUIntSelInstr>(dt, memberType, pgm);
    }

    void _appendReadDataInstrFromDt(const OptionalWithSignedIntegerSelectorType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        this->_appendReadOptInstrFromDt<ReadOptWithSIntSelInstr>(dt, memberType, pgm);
    }

    void _appendReadDataInstrFromDt(const DataType& dt,
                                    const StructureMemberType * const memberType, PgmNucleos& pgm)
    {
        BuilderDtVisitor visitor {*this, memberType, pgm};

        dt.accept(visitor);
    }

private:
    const TraceType *_traceType;
    CoucheTard _ct;
    PgmNucleos _pktPreamblePgm;
    PktPgm::DsPktPgms _dsPktPgms;
    bool _hasDstIdRole;
    bool _hasErtIdRole;
};

void BuilderDtVisitor::visit(const FixedLengthBitArrayType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const FixedLengthBitMapType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const FixedLengthBooleanType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const FixedLengthSignedIntegerType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const FixedLengthUnsignedIntegerType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const FixedLengthFloatingPointNumberType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const VariableLengthSignedIntegerType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const VariableLengthUnsignedIntegerType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const NullTerminatedStringType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const StructureType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const StaticLengthArrayType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const DynamicLengthArrayType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const StaticLengthStringType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const DynamicLengthStringType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const StaticLengthBlobType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const DynamicLengthBlobType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const VariantWithUnsignedIntegerSelectorType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const VariantWithSignedIntegerSelectorType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const OptionalWithBooleanSelectorType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const OptionalWithUnsignedIntegerSelectorType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

void BuilderDtVisitor::visit(const OptionalWithSignedIntegerSelectorType& dt)
{
    _builder->_appendReadDataInstrFromDt(dt, _memberType, *_pgm);
}

} // namespace

PktPgm buildPktPgm(const TraceType& traceType)
{
    Builder builder {traceType};

    return builder.pktPgm();
}

} // namespace internal
} // namespace yactfr
