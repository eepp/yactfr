/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_DATA_LOC_MAP_HPP
#define _YACTFR_METADATA_INTERNAL_DATA_LOC_MAP_HPP

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
#include "../metadata-parse-error.hpp"
#include "pseudo-types.hpp"

namespace yactfr {
namespace internal {

/*
 * Map of pseudo data types to yactfr data locations.
 *
 * This is a way to have such data locations _before_ creating actual
 * yactfr data type objects.
 */
class DataLocMap :
    boost::noncopyable
{
public:
    /*
     * Builds a data location map for `pseudoDt` (pseudo dynamic array
     * or variant type) within the scope `scope`.
     */
    explicit DataLocMap(const PseudoDt& pseudoDt, Scope scope);

    /*
     * Returns the data location of the pseudo dynamic array or variant
     * type `pseudoDt`.
     */
    const DataLocation& operator[](const PseudoDt& pseudoDt) const noexcept;

private:
    /*
     * An entry of `_MemberNames`.
     */
    using _MemberNamesEntry = std::vector<const std::string *>;

    /*
     * A vector of `_MemberNamesEntry`, used temporarily by _create()
     * and _dataLocFromPseudoDataLoc() to convert pseudo data locations
     * to yactfr data locations.
     */
    using _MemberNames = std::vector<_MemberNamesEntry>;

private:
    /*
     * Creates and returns a yactfr data location from the pseudo data
     * location `pseudoDataLoc` within the root scope `scope`.
     */
    DataLocation _dataLocFromPseudoDataLoc(const PseudoDataLoc& pseudoDataLoc);

    /*
     * Fills `_map` to contain the yactfr data locations of all pseudo
     * dynamic array and variant types within `*_pseudoDt`.
     */
    void _create(const PseudoDt& pseudoDt);

private:
    Scope _scope;
    _MemberNames _memberNames;
    std::unordered_map<const PseudoDt *, DataLocation> _map;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_DATA_LOC_MAP_HPP
