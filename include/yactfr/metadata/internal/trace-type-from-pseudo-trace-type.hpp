/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_OBJ_FROM_PSEUDO_OBJ_HPP
#define _YACTFR_METADATA_INTERNAL_OBJ_FROM_PSEUDO_OBJ_HPP

#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/utility.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../../aliases.hpp"
#include "../../trace-env.hpp"
#include "../trace-type.hpp"
#include "../data-loc.hpp"
#include "../dst.hpp"
#include "../ert.hpp"
#include "../fl-enum-type.hpp"
#include "../int-range.hpp"
#include "../aliases.hpp"
#include "../../text-parse-error.hpp"
#include "pseudo-types.hpp"

namespace yactfr {
namespace internal {

TraceType::UP traceTypeFromPseudoTraceType(PseudoTraceType& pseudoTraceType);

/*
 * Converter of root pseudo data type to yactfr data type.
 */
class TraceTypeFromPseudoTraceTypeConverter :
    boost::noncopyable
{
    friend TraceType::UP traceTypeFromPseudoTraceType(PseudoTraceType&);

private:
    explicit TraceTypeFromPseudoTraceTypeConverter(PseudoTraceType& pseudoTraceType);

    /*
     * Releases and returns the resulting yactfr trace type.
     */
    TraceType::UP releaseTraceType()
    {
        return std::move(_traceType);
    }

    /*
     * Converts the pseudo trace type `*_pseudoTraceType` to a yactr
     * trace type.
     */
    TraceType::UP _traceTypeFromPseudoTraceType();

    /*
     * Converts the pseudo data stream type `pseudoDst` to a yactfr data
     * stream type.
     */
    std::unique_ptr<const DataStreamType> _dstFromPseudoDst(const PseudoDst& pseudoDst);

    /*
     * Converts the pseudo event record type `pseudoErt` to a yactfr
     * event record type.
     */
    std::unique_ptr<const EventRecordType> _ertFromPseudoErt(const PseudoErt& pseudoErt,
                                                             const PseudoDst& curPseudoDst);

    /*
     * Converts the root pseudo structure type `pseudoDt` to a yactfr
     * structure type.
     *
     * If `pseudoDt` is `nullptr`, then this method returns an empty
     * pointer immediately.
     */
    StructureType::UP _scopeStructTypeFromPseudoDt(const PseudoDt *pseudoDt, Scope scope,
                                                   const PseudoDst *curPseudoDst = nullptr,
                                                   const PseudoErt *curPseudoErt = nullptr) const;


private:
    // final yactfr trace type
    TraceType::UP _traceType;

    // pseudo trace type
    PseudoTraceType *_pseudoTraceType;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_OBJ_FROM_PSEUDO_OBJ_HPP
