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
                             boost::optional<std::string>&& ns,
                             boost::optional<std::string>&& name,
                             boost::optional<std::string>&& uid, TraceEnvironment&& env,
                             StructureType::Up pktHeaderType, ClockTypeSet&& clkTypes,
                             DataStreamTypeSet&& dsts, MapItem::Up attrs,
                             const TraceType& traceType) :
    _majorVersion {majorVersion},
    _minorVersion {minorVersion},
    _ns {std::move(ns)},
    _name {std::move(name)},
    _uid {std::move(uid)},
    _env {std::move(env)},
    _pktHeaderType {std::move(pktHeaderType)},
    _clkTypes {std::move(clkTypes)},
    _dsts {std::move(dsts)},
    _attrs {std::move(attrs)},
    _traceType {&traceType}
{
    this->_buildDstMap();
    this->_createParentLinks(traceType);
    this->_setDispNames();
    this->_setKeyDts();
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

class SetKeyDtsDtVisitor :
    public DataTypeVisitor
{
public:
    explicit SetKeyDtsDtVisitor(const TraceTypeImpl& traceType,
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
        this->_setKeyDts(dt.lengthLocation(), TraceTypeImpl::dlArrayTypeLenTypes(dt));
        this->_visitArrayType(dt);
    }

    void visit(const DynamicLengthStringType& dt) override
    {
        this->_setKeyDts(dt.maximumLengthLocation(), TraceTypeImpl::dlStrTypeMaxLenTypes(dt));
    }

    void visit(const DynamicLengthBlobType& dt) override
    {
        this->_setKeyDts(dt.lengthLocation(), TraceTypeImpl::dlBlobTypeLenTypes(dt));
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
        this->_setKeyDts(varType.selectorLocation(), TraceTypeImpl::varOptTypeSelTypes(varType));

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
        this->_setKeyDts(optType.selectorLocation(), TraceTypeImpl::varOptTypeSelTypes(optType));

        // currently being visited
        _current.insert({&optType, 0});

        optType.dataType().accept(*this);

        // not visited anymore
        _current.erase(&optType);
    }

    template <typename VarTypeT>
    void _setKeyDtsVar(const VarTypeT& dt, const DataLocation& loc,
                       const DataLocation::PathElements::const_iterator locIt, DataTypeSet& dts) const
    {
        const auto it = _current.find(&dt);

        if (it == _current.end()) {
            // fan out (consider all options)
            for (auto& opt : dt.options()) {
                this->_setKeyDts(opt->dataType(), loc, locIt, dts);
            }
        } else {
            // follow current option only
            this->_setKeyDts(dt[it->second].dataType(), loc, locIt, dts);
        }
    }

    void _setKeyDts(const DataType& dt, const DataLocation& loc,
                    const DataLocation::PathElements::const_iterator locIt, DataTypeSet& dts) const
    {
        if (dt.isFixedLengthBooleanType() || dt.isIntegerType()) {
            // those are the only valid length/selector data types
            assert(locIt == loc.pathElements().end());
            dts.insert(&dt);
        } else if (dt.isStructureType()) {
            const auto memberType = dt.asStructureType()[*locIt];

            assert(memberType);
            this->_setKeyDts(memberType->dataType(), loc, locIt + 1, dts);
        } else if (dt.isArrayType()) {
            assert(_current.find(&dt) != _current.end());
            this->_setKeyDts(dt.asArrayType().elementType(), loc, locIt, dts);
        } else if (dt.isVariantWithUnsignedIntegerSelectorType()) {
            this->_setKeyDtsVar(dt.asVariantWithUnsignedIntegerSelectorType(), loc, locIt, dts);
        } else if (dt.isVariantWithSignedIntegerSelectorType()) {
            this->_setKeyDtsVar(dt.asVariantWithSignedIntegerSelectorType(), loc, locIt, dts);
        } else if (dt.isOptionalType()) {
            assert(_current.find(&dt) != _current.end());
            this->_setKeyDts(dt.asOptionalType().dataType(), loc, locIt, dts);
        } else {
            std::abort();
        }
    }

    void _setKeyDts(const DataLocation& loc, DataTypeSet& dts) const
    {
        auto& dt = call([this, &loc]() -> const DataType& {
            switch (loc.scope()) {
            case Scope::PacketHeader:
                return *_traceType->pktHeaderType();

            case Scope::PacketContext:
                assert(_curDst);
                return *_curDst->packetContextType();

            case Scope::EventRecordHeader:
                assert(_curDst);
                return *_curDst->eventRecordHeaderType();

            case Scope::EventRecordCommonContext:
                assert(_curDst);
                return *_curDst->eventRecordCommonContextType();

            case Scope::EventRecordSpecificContext:
                assert(_curErt);
                return *_curErt->specificContextType();

            case Scope::EventRecordPayload:
                assert(_curErt);
                return *_curErt->payloadType();

            default:
                std::abort();
            }
        });

        this->_setKeyDts(dt, loc, loc.begin(), dts);
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

void TraceTypeImpl::_setKeyDts() const
{
    if (_pktHeaderType) {
        SetKeyDtsDtVisitor visitor {*this};

        _pktHeaderType->accept(visitor);
    }

    for (auto& dst : _dsts) {
        if (dst->packetContextType()) {
            SetKeyDtsDtVisitor visitor {*this, dst.get()};

            dst->packetContextType()->accept(visitor);
        }

        if (dst->eventRecordHeaderType()) {
            SetKeyDtsDtVisitor visitor {*this, dst.get()};

            dst->eventRecordHeaderType()->accept(visitor);
        }

        if (dst->eventRecordCommonContextType()) {
            SetKeyDtsDtVisitor visitor {*this, dst.get()};

            dst->eventRecordCommonContextType()->accept(visitor);
        }

        for (auto& ert : dst->eventRecordTypes()) {
            if (ert->specificContextType()) {
                SetKeyDtsDtVisitor visitor {*this, dst.get(), ert.get()};

                ert->specificContextType()->accept(visitor);
            }

            if (ert->payloadType()) {
                SetKeyDtsDtVisitor visitor {*this, dst.get(), ert.get()};

                ert->payloadType()->accept(visitor);
            }
        }
    }
}

class SetDispNamesDtVisitor :
    public DataTypeVisitor
{
public:
    explicit SetDispNamesDtVisitor(const bool removeUnderscore) :
        _removeUnderscore {removeUnderscore}
    {
    }

    void visit(const StructureType& structType) override
    {
        for (const auto& memberType : structType) {
            this->_setDispName(*memberType, memberType->name());
            memberType->dataType().accept(*this);
        }
    }

    void visit(const StaticLengthArrayType& dt) override
    {
        this->_visit(dt);
    }

    void visit(const DynamicLengthArrayType& dt) override
    {
        this->_visit(dt);
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
        this->_visit(dt);
    }

    void visit(const OptionalWithUnsignedIntegerSelectorType& dt) override
    {
        this->_visit(dt);
    }

    void visit(const OptionalWithSignedIntegerSelectorType& dt) override
    {
        this->_visit(dt);
    }

private:
    template <typename ObjT>
    void _setDispName(const ObjT& obj, const std::string& name) const noexcept
    {
        TraceTypeImpl::setDispName(obj, name, _removeUnderscore);
    }

    void _visit(const ArrayType& arrayType)
    {
        arrayType.elementType().accept(*this);
    }

    template <typename VarTypeT>
    void _visitVarType(const VarTypeT& varType)
    {
        for (auto& opt : varType) {
            if (opt->name()) {
                this->_setDispName(*opt, *opt->name());
            }

            opt->dataType().accept(*this);
        }
    }

    void _visit(const OptionalType& optType)
    {
        optType.dataType().accept(*this);
    }

private:
    bool _removeUnderscore;
};

void TraceTypeImpl::_setDispNames() const
{
    SetDispNamesDtVisitor visitor {_majorVersion == 1};

    if (_pktHeaderType) {
        _pktHeaderType->accept(visitor);
    }

    for (auto& dst : _dsts) {
        if (dst->packetContextType()) {
            dst->packetContextType()->accept(visitor);
        }

        if (dst->eventRecordHeaderType()) {
            dst->eventRecordHeaderType()->accept(visitor);
        }

        if (dst->eventRecordCommonContextType()) {
            dst->eventRecordCommonContextType()->accept(visitor);
        }

        for (auto& ert : dst->eventRecordTypes()) {
            if (ert->specificContextType()) {
                ert->specificContextType()->accept(visitor);
            }

            if (ert->payloadType()) {
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
