/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_ITEM_FROM_JSON_VAL_HPP
#define _YACTFR_METADATA_INTERNAL_ITEM_FROM_JSON_VAL_HPP

#include <string>

#include "json-val.hpp"

namespace yactfr {
namespace internal {

/*
 * Converts the JSON value `jsonVal` to an equivalent yactfr item and
 * returns it.
 */
Item::UP itemFromJsonVal(const JsonVal& jsonVal);

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_ITEM_FROM_JSON_VAL_HPP
