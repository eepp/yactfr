/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_TRACE_TYPE_FROM_PSEUDO_TRACE_TYPE_HPP
#define YACTFR_INTERNAL_METADATA_TRACE_TYPE_FROM_PSEUDO_TRACE_TYPE_HPP

#include <memory>
#include <optional>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/data-loc.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/ert.hpp>
#include <yactfr/metadata/int-range.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/text-parse-error.hpp>

#include "pseudo-types.hpp"

namespace yactfr::internal {

[[ nodiscard ]] TraceType::Up traceTypeFromPseudoTraceType(PseudoTraceType& pseudoTraceType);

/*
 * Converter of root pseudo data type to yactfr data type.
 */
class TraceTypeFromPseudoTraceTypeConverter
{
    friend TraceType::Up traceTypeFromPseudoTraceType(PseudoTraceType&);

private:
    explicit TraceTypeFromPseudoTraceTypeConverter(PseudoTraceType& pseudoTraceType);

    TraceTypeFromPseudoTraceTypeConverter(const TraceTypeFromPseudoTraceTypeConverter&) = delete;
    TraceTypeFromPseudoTraceTypeConverter& operator=(const TraceTypeFromPseudoTraceTypeConverter&) = delete;

    /*
     * Releases and returns the resulting yactfr trace type.
     */
    [[ nodiscard ]] TraceType::Up releaseTraceType()
    {
        return std::move(_traceType);
    }

    /*
     * Converts the pseudo trace type `*_pseudoTraceType` to a yactr
     * trace type.
     */
    [[ nodiscard ]] TraceType::Up _traceTypeFromPseudoTraceType();

    /*
     * Converts the pseudo data stream type `pseudoDst` to a yactfr data
     * stream type.
     */
    [[ nodiscard ]] std::unique_ptr<const DataStreamType> _dstFromPseudoDst(PseudoDst& pseudoDst);

    /*
     * Converts the pseudo event record type `pseudoErt` to a yactfr
     * event record type.
     */
    [[ nodiscard ]] std::unique_ptr<const EventRecordType> _ertFromPseudoErt(PseudoErt& pseudoErt,
                                                             const PseudoDst& curPseudoDst);

    /*
     * Converts the root pseudo structure type `pseudoDt` to a yactfr
     * structure type.
     *
     * If `pseudoDt` is `nullptr`, then this method returns an empty
     * pointer immediately.
     */
    [[ nodiscard ]] StructureType::Up _scopeStructTypeFromPseudoDt(PseudoDt *pseudoDt, Scope scope,
                                                   const PseudoDst *curPseudoDst = nullptr,
                                                   const PseudoErt *curPseudoErt = nullptr) const;


private:
    // final yactfr trace type
    TraceType::Up _traceType;

    // pseudo trace type
    PseudoTraceType *_pseudoTraceType;
};

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_METADATA_TRACE_TYPE_FROM_PSEUDO_TRACE_TYPE_HPP
