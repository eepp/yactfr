/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_FROM_TEXT_HPP
#define YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_FROM_TEXT_HPP

#include <string>
#include <string_view>

#include "json-val.hpp"

namespace yactfr::internal {

/*
 * Parses the JSON text `str` and returns the resulting JSON value,
 * adding `baseOffset` to the text location offset of all the created
 * JSON values.
 *
 * Throws `TextParseError` on error.
 */
[[ nodiscard ]] JsonVal::Up parseJson(std::string_view str, Size baseOffset = 0);

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_FROM_TEXT_HPP
