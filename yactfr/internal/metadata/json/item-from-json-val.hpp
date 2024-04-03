/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_ITEM_FROM_JSON_VAL_HPP
#define YACTFR_INTERNAL_METADATA_JSON_ITEM_FROM_JSON_VAL_HPP

#include <string>

#include "json-val.hpp"

namespace yactfr {
namespace internal {

/*
 * Converts the JSON value `jsonVal` to an equivalent yactfr item and
 * returns it.
 */
Item::Up itemFromJsonVal(const JsonVal& jsonVal);

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_JSON_ITEM_FROM_JSON_VAL_HPP
