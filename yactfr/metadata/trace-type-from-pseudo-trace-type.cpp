/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>
#include <tuple>
#include <set>

#include <yactfr/text-loc.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/text-parse-error.hpp>

#include "trace-type-from-pseudo-trace-type.hpp"
#include "dt-from-pseudo-root-dt.hpp"
#include "utils.hpp"

namespace yactfr {
namespace internal {

TraceType::UP traceTypeFromPseudoTraceType(PseudoTraceType& pseudoTraceType)
{
    return TraceTypeFromPseudoTraceTypeConverter {pseudoTraceType}.releaseTraceType();
}

TraceTypeFromPseudoTraceTypeConverter::TraceTypeFromPseudoTraceTypeConverter(PseudoTraceType& pseudoTraceType) :
    _pseudoTraceType {&pseudoTraceType}
{
    _traceType = this->_traceTypeFromPseudoTraceType();
}

TraceType::UP TraceTypeFromPseudoTraceTypeConverter::_traceTypeFromPseudoTraceType()
{
    // validate first
    _pseudoTraceType->validate();

    DataStreamTypeSet dstSet;

    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        dstSet.insert(this->_dstFromPseudoDst(*idPseudoDstPair.second));
    }

    auto pktHeaderType = this->_scopeStructTypeFromPseudoDt(_pseudoTraceType->pseudoPktHeaderType(),
                                                            Scope::PACKET_HEADER);

    // create yactfr trace type
    return std::make_unique<const TraceType>(_pseudoTraceType->majorVersion(),
                                             _pseudoTraceType->minorVersion(),
                                             _pseudoTraceType->uuid(), std::move(pktHeaderType),
                                             std::move(_pseudoTraceType->clkTypes()),
                                             std::move(dstSet),
                                             tryCloneUserAttrs(_pseudoTraceType->userAttrs()));
}

StructureType::UP TraceTypeFromPseudoTraceTypeConverter::_scopeStructTypeFromPseudoDt(const PseudoDt * const pseudoDt,
                                                                                      const Scope scope,
                                                                                      const PseudoDst * const pseudoDst,
                                                                                      const PseudoErt * const pseudoErt) const
{
    if (!pseudoDt) {
        return nullptr;
    }

    return dtFromPseudoRootDt(*pseudoDt, scope, *_pseudoTraceType, pseudoDst, pseudoErt);
}

std::unique_ptr<const DataStreamType> TraceTypeFromPseudoTraceTypeConverter::_dstFromPseudoDst(const PseudoDst& pseudoDst)
{
    // collect pseudo child event record types
    PseudoErtSet pseudoErts;
    const auto it = _pseudoTraceType->pseudoOrphanErts().find(pseudoDst.id());

    if (it != _pseudoTraceType->pseudoOrphanErts().end()) {
        for (const auto& ertIdPseudoOrphanErtPair : it->second) {
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

    // convert pseudo scope data types
    auto pseudoPktCtxType = this->_scopeStructTypeFromPseudoDt(pseudoDst.pseudoPktCtxType(),
                                                               Scope::PACKET_CONTEXT, &pseudoDst);
    auto erHeaderType = this->_scopeStructTypeFromPseudoDt(pseudoDst.pseudoErHeaderType(),
                                                           Scope::EVENT_RECORD_HEADER, &pseudoDst);
    auto erCommonCtxType = this->_scopeStructTypeFromPseudoDt(pseudoDst.pseudoErCommonCtxType(),
                                                              Scope::EVENT_RECORD_COMMON_CONTEXT,
                                                              &pseudoDst);

    // create yactfr data stream type
    return std::make_unique<const DataStreamType>(pseudoDst.id(), pseudoDst.ns(), pseudoDst.name(),
                                                  std::move(ertSet), std::move(pseudoPktCtxType),
                                                  std::move(erHeaderType),
                                                  std::move(erCommonCtxType),
                                                  pseudoDst.defClkType(),
                                                  tryCloneUserAttrs(pseudoDst.userAttrs()));
}

std::unique_ptr<const EventRecordType> TraceTypeFromPseudoTraceTypeConverter::_ertFromPseudoErt(const PseudoErt& pseudoErt,
                                                                                                const PseudoDst& curPseudoDst)
{
    // validate pseudo event record type
    pseudoErt.validate(curPseudoDst);

    // convert pseudo scope data types
    auto specCtxType = this->_scopeStructTypeFromPseudoDt(pseudoErt.pseudoSpecCtxType(),
                                                          Scope::EVENT_RECORD_SPECIFIC_CONTEXT,
                                                          &curPseudoDst, &pseudoErt);
    auto payloadType = this->_scopeStructTypeFromPseudoDt(pseudoErt.pseudoPayloadType(),
                                                          Scope::EVENT_RECORD_PAYLOAD,
                                                          &curPseudoDst, &pseudoErt);

    // create yactfr event record type
    return std::make_unique<const EventRecordType>(pseudoErt.id(), pseudoErt.ns(), pseudoErt.name(),
                                                   pseudoErt.logLevel(), pseudoErt.emfUri(),
                                                   std::move(specCtxType), std::move(payloadType),
                                                   tryCloneUserAttrs(pseudoErt.userAttrs()));
}

} // namespace internal
} // namespace yactfr
