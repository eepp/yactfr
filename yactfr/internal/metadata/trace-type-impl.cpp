/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cassert>

#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/aliases.hpp>

#include "trace-type-impl.hpp"
#include "../proc.hpp"
#include "../pkt-proc-builder.hpp"
#include "../utils.hpp"

namespace yactfr {
namespace internal {

TraceTypeImpl::TraceTypeImpl(const unsigned int majorVersion, const unsigned int minorVersion,
                             boost::optional<boost::uuids::uuid> uuid,
                             StructureType::UP pktHeaderType, ClockTypeSet&& clkTypes,
                             DataStreamTypeSet&& dsts, MapItem::UP userAttrs,
                             const TraceType& traceType) :
    _majorVersion {majorVersion},
    _minorVersion {minorVersion},
    _uuid {std::move(uuid)},
    _pktHeaderType {std::move(pktHeaderType)},
    _clkTypes {std::move(clkTypes)},
    _dsts {std::move(dsts)},
    _userAttrs {std::move(userAttrs)},
    _traceType {&traceType}
{
    this->_buildDstMap();
    this->_createParentLinks(traceType);
    this->_setTypeDeps();
}

void TraceTypeImpl::_buildDstMap()
{
    for (auto& dstUp : _dsts) {
        assert(_idsToDsts.find(dstUp->id()) == _idsToDsts.end());
        _idsToDsts[dstUp->id()] = dstUp.get();
    }
}

const DataStreamType *TraceTypeImpl::findDst(const TypeId id) const noexcept
{
    auto it = _idsToDsts.find(id);

    if (it == _idsToDsts.end()) {
        return nullptr;
    }

    return it->second;
}

void TraceTypeImpl::_createParentLinks(const TraceType& traceType) const
{
    for (const auto& dst : _dsts) {
        dst->_setTraceType(traceType);

        for (const auto& ert : dst->eventRecordTypes()) {
            ert->_setDst(*dst);
        }
    }
}

class SetTypeDepsDtVisitor :
    public DataTypeVisitor
{
public:
    explicit SetTypeDepsDtVisitor(const TraceTypeImpl& traceType,
                                  const DataStreamType * const curDst = nullptr,
                                  const EventRecordType * const curErt = nullptr) :
        _traceType {&traceType},
        _curDst {curDst},
        _curErt {curErt}
    {
    }

    void visit(const StructureType& structType) override
    {
        for (const auto& memberType : structType) {
            memberType->dataType().accept(*this);
        }
    }

    void visit(const StaticLengthArrayType& dt) override
    {
        this->_visitArrayType(dt);
    }

    void visit(const DynamicLengthArrayType& dt) override
    {
        this->_setTypeDeps(dt.lengthLocation(), TraceTypeImpl::dlArrayTypeLenTypes(dt));
        this->_visitArrayType(dt);
    }

    void visit(const DynamicLengthStringType& dt) override
    {
        this->_setTypeDeps(dt.maximumLengthLocation(), TraceTypeImpl::dlStrTypeMaxLenTypes(dt));
    }

    void visit(const DynamicLengthBlobType& dt) override
    {
        this->_setTypeDeps(dt.lengthLocation(), TraceTypeImpl::dlBlobTypeLenTypes(dt));
    }

    void visit(const VariantWithUnsignedIntegerSelectorType& dt) override
    {
        this->_visitVarType(dt);
    }

    void visit(const VariantWithSignedIntegerSelectorType& dt) override
    {
        this->_visitVarType(dt);
    }

    void visit(const OptionalWithBooleanSelectorType& dt) override
    {
        this->_visitOptType(dt);
    }

    void visit(const OptionalWithUnsignedIntegerSelectorType& dt) override
    {
        this->_visitOptType(dt);
    }

    void visit(const OptionalWithSignedIntegerSelectorType& dt) override
    {
        this->_visitOptType(dt);
    }

private:
    void _visitArrayType(const ArrayType& arrayType)
    {
        // currently being visited
        _current.insert({&arrayType, 0});

        arrayType.elementType().accept(*this);

        // not visited anymore
        _current.erase(&arrayType);
    }

    template <typename VarTypeT>
    void _visitVarType(const VarTypeT& varType)
    {
        this->_setTypeDeps(varType.selectorLocation(), TraceTypeImpl::varOptTypeSelTypes(varType));

        for (auto i = 0U; i < varType.size(); ++i) {
            // currently being visited
            _current[&varType] = i;

            varType[i].dataType().accept(*this);
        }

        // not visited anymore
        _current.erase(&varType);
    }

    template <typename OptTypeT>
    void _visitOptType(const OptTypeT& optType)
    {
        this->_setTypeDeps(optType.selectorLocation(), TraceTypeImpl::varOptTypeSelTypes(optType));

        // currently being visited
        _current.insert({&optType, 0});

        optType.dataType().accept(*this);

        // not visited anymore
        _current.erase(&optType);
    }

    template <typename VarTypeT>
    void _setTypeDepsVar(const VarTypeT& dt, const DataLocation& loc,
                         const DataLocation::PathElements::const_iterator locIt, DataTypeSet& dts) const
    {
        const auto it = _current.find(&dt);

        if (it == _current.end()) {
            // fan out (consider all options)
            for (auto& opt : dt.options()) {
                this->_setTypeDeps(opt->dataType(), loc, locIt, dts);
            }
        } else {
            // follow current option only
            this->_setTypeDeps(dt[it->second].dataType(), loc, locIt, dts);
        }
    }

    void _setTypeDeps(const DataType& dt, const DataLocation& loc,
                      const DataLocation::PathElements::const_iterator locIt, DataTypeSet& dts) const
    {
        if (dt.isFixedLengthBooleanType() || dt.isIntegerType()) {
            // those are the only valid length/selector data types
            assert(locIt == loc.pathElements().end());
            dts.insert(&dt);
        } else if (dt.isStructureType()) {
            const auto memberType = dt.asStructureType()[*locIt];

            assert(memberType);
            this->_setTypeDeps(memberType->dataType(), loc, locIt + 1, dts);
        } else if (dt.isArrayType()) {
            assert(_current.find(&dt) != _current.end());
            this->_setTypeDeps(dt.asArrayType().elementType(), loc, locIt, dts);
        } else if (dt.isVariantWithUnsignedIntegerSelectorType()) {
            this->_setTypeDepsVar(dt.asVariantWithUnsignedIntegerSelectorType(), loc, locIt, dts);
        } else if (dt.isVariantWithSignedIntegerSelectorType()) {
            this->_setTypeDepsVar(dt.asVariantWithSignedIntegerSelectorType(), loc, locIt, dts);
        } else if (dt.isOptionalType()) {
            assert(_current.find(&dt) != _current.end());
            this->_setTypeDeps(dt.asOptionalType().dataType(), loc, locIt, dts);
        } else {
            std::abort();
        }
    }

    void _setTypeDeps(const DataLocation& loc, DataTypeSet& dts) const
    {
        const DataType *dt = nullptr;

        switch (loc.scope()) {
        case Scope::PACKET_HEADER:
            dt = _traceType->pktHeaderType();
            break;

        case Scope::PACKET_CONTEXT:
            assert(_curDst);
            dt = _curDst->packetContextType();
            break;

        case Scope::EVENT_RECORD_HEADER:
            assert(_curDst);
            dt = _curDst->eventRecordHeaderType();
            break;

        case Scope::EVENT_RECORD_COMMON_CONTEXT:
            assert(_curDst);
            dt = _curDst->eventRecordCommonContextType();
            break;

        case Scope::EVENT_RECORD_SPECIFIC_CONTEXT:
            assert(_curErt);
            dt = _curErt->specificContextType();
            break;

        case Scope::EVENT_RECORD_PAYLOAD:
            assert(_curErt);
            dt = _curErt->payloadType();
            break;

        default:
            std::abort();
        }

        assert(dt);
        this->_setTypeDeps(*dt, loc, loc.begin(), dts);
    }

private:
    const TraceTypeImpl * const _traceType;
    const DataStreamType * const _curDst;
    const EventRecordType * const _curErt;

    /*
     * Option/element indexes of currently visited variant/optional and
     * dynamic array/string/BLOB types (always 0 for a dynamic array or
     * optional type).
     */
    std::unordered_map<const DataType *, Index> _current;
};

void TraceTypeImpl::_setTypeDeps() const
{
    if (_pktHeaderType) {
        SetTypeDepsDtVisitor visitor {*this};

        _pktHeaderType->accept(visitor);
    }

    for (auto& dst : _dsts) {
        if (dst->packetContextType()) {
            SetTypeDepsDtVisitor visitor {*this, dst.get()};

            dst->packetContextType()->accept(visitor);
        }

        if (dst->eventRecordHeaderType()) {
            SetTypeDepsDtVisitor visitor {*this, dst.get()};

            dst->eventRecordHeaderType()->accept(visitor);
        }

        if (dst->eventRecordCommonContextType()) {
            SetTypeDepsDtVisitor visitor {*this, dst.get()};

            dst->eventRecordCommonContextType()->accept(visitor);
        }

        for (auto& ert : dst->eventRecordTypes()) {
            if (ert->specificContextType()) {
                SetTypeDepsDtVisitor visitor {*this, dst.get(), ert.get()};

                ert->specificContextType()->accept(visitor);
            }

            if (ert->payloadType()) {
                SetTypeDepsDtVisitor visitor {*this, dst.get(), ert.get()};

                ert->payloadType()->accept(visitor);
            }
        }
    }
}

const PktProc& TraceTypeImpl::pktProc() const
{
    if (!_pktProc) {
        _pktProc = internal::PktProcBuilder {*_traceType}.releasePktProc();
    }

    return *_pktProc;
}

} // namespace internal
} // namespace yactfr
