/*
 * Copyright (C) 2022-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_JSON_PSEUDO_DT_ERECTOR_HPP
#define _YACTFR_INTERNAL_METADATA_JSON_PSEUDO_DT_ERECTOR_HPP

#include <string>
#include <unordered_map>

#include "json-val.hpp"
#include "../pseudo-types.hpp"

namespace yactfr {
namespace internal {

/*
 * Erects pseudo data types from equivalent CTF 2 JSON values,
 * maintaining a map of data type aliases.
 */
class PseudoDtErector final
{
public:
    explicit PseudoDtErector() = default;

    /*
     * Erects and returns the pseudo data type for the property named
     * `propName` of the JSON object `jsonDt`.
     *
     * The value of the property named `propName` may be a JSON object
     * (full data type) or a JSON string (data type alias name).
     */
    PseudoDt::UP pseudoDtOfJsonObj(const JsonObjVal& jsonDt, const std::string& propName);

    /*
     * Adds the data type alias `pseudoDt` named `name`.
     *
     * `nameLoc` is the location of the JSON string which is the name of
     * the alias.
     */
    void addAlias(const std::string& name, PseudoDt::UP pseudoDt, const TextLocation& nameLoc);

private:
    PseudoDt::UP _aliasedPseudoDt(const std::string& name, const TextLocation& textLoc);

    PseudoDt::UP _pseudoDtFromDlArrayType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                          unsigned int minAlign);

    PseudoDt::UP _pseudoDtFromSlArrayType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                          unsigned int minAlign);

    PseudoDt::UP _pseudoDtFromArrayType(const JsonObjVal& jsonDt, const std::string& type,
                                        MapItem::UP userAttrs);

    PseudoDt::UP _pseudoDtFromStructType(const JsonObjVal& jsonDt, MapItem::UP userAttrs);
    PseudoDt::UP _pseudoDtFromOptType(const JsonObjVal& jsonDt, MapItem::UP userAttrs);
    PseudoDt::UP _pseudoDtFromVarType(const JsonObjVal& jsonDt, MapItem::UP userAttrs);

private:
    std::unordered_map<std::string, PseudoDt::UP> _aliases;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_JSON_PSEUDO_DT_ERECTOR_HPP
