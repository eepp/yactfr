/*
 * Copyright (C) 2015-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_SET_PSEUDO_DT_POS_IN_SCOPE_HPP
#define YACTFR_INTERNAL_METADATA_SET_PSEUDO_DT_POS_IN_SCOPE_HPP

#include "pseudo-types.hpp"

namespace yactfr {
namespace internal {

/*
 * Sets the position-in-scope of all the pseudo data types of `pseudoDt`
 * (included) in a pre-order (decoding order) fashion.
 *
 * After calling this function, the `posInScope()` method for all those
 * pseudo data types return a value.
 */
void setPseudoDtPosInScope(PseudoDt& pseudoDt);

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_SET_PSEUDO_DT_POS_IN_SCOPE_HPP
