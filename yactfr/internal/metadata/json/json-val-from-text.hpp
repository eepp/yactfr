/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_FROM_TEXT_HPP
#define YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_FROM_TEXT_HPP

#include <string>

#include "json-val.hpp"

namespace yactfr {
namespace internal {

/*
 * Parses the JSON text between `begin` and `end` (excluded) and returns
 * the resulting JSON value, adding `baseOffset` to the text location
 * offset of all the created JSON values.
 *
 * Throws `TextParseError` on error.
 */
JsonVal::Up parseJson(const char *begin, const char *end, Size baseOffset = 0);

/*
 * Parses the JSON string `str` and returns the resulting JSON value,
 * adding `baseOffset` to the text location offset of all the created
 * JSON values.
 *
 * Throws `TextParseError` on error.
 */
inline JsonVal::Up parseJson(const std::string& str, const Size baseOffset = 0)
{
    return parseJson(str.data(), str.data() + str.size(), baseOffset);
}

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_FROM_TEXT_HPP
