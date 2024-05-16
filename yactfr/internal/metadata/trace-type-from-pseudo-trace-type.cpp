/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/text-loc.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>
#include <yactfr/text-parse-error.hpp>

#include "trace-type-from-pseudo-trace-type.hpp"
#include "dt-from-pseudo-root-dt.hpp"

namespace yactfr {
namespace internal {

TraceType::Up traceTypeFromPseudoTraceType(PseudoTraceType& pseudoTraceType)
{
    return TraceTypeFromPseudoTraceTypeConverter {pseudoTraceType}.releaseTraceType();
}

TraceTypeFromPseudoTraceTypeConverter::TraceTypeFromPseudoTraceTypeConverter(PseudoTraceType& pseudoTraceType) :
    _pseudoTraceType {&pseudoTraceType}
{
    _traceType = this->_traceTypeFromPseudoTraceType();
}

TraceType::Up TraceTypeFromPseudoTraceTypeConverter::_traceTypeFromPseudoTraceType()
{
    // validate first
    _pseudoTraceType->validate();

    DataStreamTypeSet dstSet;

    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        dstSet.insert(this->_dstFromPseudoDst(*idPseudoDstPair.second));
    }

    // create yactfr trace type
    return TraceType::create(_pseudoTraceType->majorVersion(), _pseudoTraceType->minorVersion(),
                             _pseudoTraceType->ns(), _pseudoTraceType->name(),
                             _pseudoTraceType->uid(), _pseudoTraceType->env(),
                             this->_scopeStructTypeFromPseudoDt(_pseudoTraceType->pseudoPktHeaderType(),
                                                                Scope::PacketHeader),
                             std::move(_pseudoTraceType->clkTypes()), std::move(dstSet),
                             tryCloneAttrs(_pseudoTraceType->attrs()));
}

StructureType::Up TraceTypeFromPseudoTraceTypeConverter::_scopeStructTypeFromPseudoDt(PseudoDt * const pseudoDt,
                                                                                      const Scope scope,
                                                                                      const PseudoDst * const pseudoDst,
                                                                                      const PseudoErt * const pseudoErt) const
{
    if (!pseudoDt) {
        return nullptr;
    }

    return dtFromPseudoRootDt(*pseudoDt, scope, *_pseudoTraceType, pseudoDst, pseudoErt);
}

std::unique_ptr<const DataStreamType> TraceTypeFromPseudoTraceTypeConverter::_dstFromPseudoDst(PseudoDst& pseudoDst)
{
    // collect pseudo child event record types
    PseudoErtSet pseudoErts;
    const auto it = _pseudoTraceType->pseudoOrphanErts().find(pseudoDst.id());

    if (it != _pseudoTraceType->pseudoOrphanErts().end()) {
        for (auto& ertIdPseudoOrphanErtPair : it->second) {
            pseudoErts.insert(&ertIdPseudoOrphanErtPair.second.pseudoErt());
        }
    }

    // validate pseudo data stream type before converting
    pseudoDst.validate(pseudoErts);

    // convert pseudo event record types
    EventRecordTypeSet ertSet;

    for (auto pseudoErt : pseudoErts) {
        ertSet.insert(this->_ertFromPseudoErt(*pseudoErt, pseudoDst));
    }

    // create yactfr data stream type
    return DataStreamType::create(pseudoDst.id(), pseudoDst.ns(), pseudoDst.name(),
                                  pseudoDst.uid(), std::move(ertSet),
                                  this->_scopeStructTypeFromPseudoDt(pseudoDst.pseudoPktCtxType(),
                                                                     Scope::PacketContext,
                                                                     &pseudoDst),
                                  this->_scopeStructTypeFromPseudoDt(pseudoDst.pseudoErHeaderType(),
                                                                     Scope::EventRecordHeader,
                                                                     &pseudoDst),
                                  this->_scopeStructTypeFromPseudoDt(pseudoDst.pseudoErCommonCtxType(),
                                                                     Scope::EventRecordCommonContext,
                                                                     &pseudoDst),
                                  pseudoDst.defClkType(), tryCloneAttrs(pseudoDst.attrs()));
}

std::unique_ptr<const EventRecordType> TraceTypeFromPseudoTraceTypeConverter::_ertFromPseudoErt(PseudoErt& pseudoErt,
                                                                                                const PseudoDst& curPseudoDst)
{
    // validate pseudo event record type
    pseudoErt.validate(curPseudoDst);

    // create yactfr event record type
    return EventRecordType::create(pseudoErt.id(), pseudoErt.ns(), pseudoErt.name(),
                                   pseudoErt.uid(), pseudoErt.logLevel(), pseudoErt.emfUri(),
                                   this->_scopeStructTypeFromPseudoDt(pseudoErt.pseudoSpecCtxType(),
                                                                      Scope::EventRecordSpecificContext,
                                                                      &curPseudoDst, &pseudoErt),
                                   this->_scopeStructTypeFromPseudoDt(pseudoErt.pseudoPayloadType(),
                                                                      Scope::EventRecordPayload,
                                                                      &curPseudoDst, &pseudoErt),
                                   tryCloneAttrs(pseudoErt.attrs()));
}

} // namespace internal
} // namespace yactfr
