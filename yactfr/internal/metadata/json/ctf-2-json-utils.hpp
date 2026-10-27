/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_UTILS_HPP
#define YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_UTILS_HPP

#include <optional>
#include <boost/uuid/uuid.hpp>

#include <yactfr/metadata/item.hpp>

#include "json-val.hpp"

namespace yactfr::internal {

/*
 * Returns the attributes of the JSON object value `jsonObjVal`, or an
 * empty map item there's no such property.
 */
MapItem::Up attrsOfObj(const JsonObjVal& jsonObjVal);

/*
 * Returns the raw integer value from the JSON unsigned or signed
 * integer value `jsonIntVal`, casted as `ValT`.
 */
template <typename ValT>
ValT rawIntValFromJsonIntVal(const JsonVal& jsonIntVal) noexcept
{
    if (jsonIntVal.isUInt()) {
        return static_cast<ValT>(*jsonIntVal.asUInt());
    } else {
        return static_cast<ValT>(*jsonIntVal.asSInt());
    }
}

/*
 * Returns the optional raw string value from the property named
 * `propName` within `jsonObjVal`.
 */
inline std::optional<std::string> optStrOfObj(const JsonObjVal& jsonObjVal,
                                                const std::string& propName)
{
    const auto jsonVal = jsonObjVal[propName];

    if (jsonVal) {
        return *jsonVal->asStr();
    }

    return std::nullopt;
}

/*
 * Returns the optional unsigned integer value from the property named
 * `propName` within `jsonObjVal`.
 */
inline std::optional<unsigned long long> optUIntOfObj(const JsonObjVal& jsonObjVal,
                                                        const std::string& propName)
{
    const auto jsonVal = jsonObjVal[propName];

    if (jsonVal) {
        return *jsonVal->asUInt();
    }

    return std::nullopt;
}

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_UTILS_HPP
