/*
 * Copyright (C) 2015-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_SET_PSEUDO_DT_DATA_LOC_HPP
#define YACTFR_INTERNAL_METADATA_SET_PSEUDO_DT_DATA_LOC_HPP

#include <yactfr/metadata/scope.hpp>

#include "pseudo-types.hpp"

namespace yactfr {
namespace internal {

/*
 * Sets the yactfr data locations of all the dynamic-length, optional,
 * and variant pseudo data types within the root pseudo data type
 * `pseudoDt` having the scope `scope`.
 *
 * This is a way to have such data locations _before_ creating actual
 * yactfr data type objects.
 *
 * After calling this function, all the `lenLoc()` and `selLoc()`
 * methods for such pseudo data types return a value.
 */
void setPseudoDtDataLoc(PseudoDt& pseudoDt, Scope scope);

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_SET_PSEUDO_DT_DATA_LOC_HPP
