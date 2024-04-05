/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include "ctf-2-json-utils.hpp"
#include "ctf-2-json-strs.hpp"
#include "item-from-json-val.hpp"

namespace yactfr {
namespace internal {

namespace buuids = boost::uuids;

boost::optional<buuids::uuid> uuidOfObj(const JsonObjVal& jsonObjVal)
{
    if (const auto jsonUuidVal = jsonObjVal[strs::uuid]) {
        buuids::uuid uuid;
        auto it = uuid.begin();

        for (auto i = 0U; i < uuid.static_size(); ++i, ++it) {
            *it = *jsonUuidVal->asArray()[i].asUInt();
        }

        return uuid;
    }

    return boost::none;
}

MapItem::Up attrsOfObj(const JsonObjVal& jsonObjVal)
{
    if (const auto jsonAttrsVal = jsonObjVal[strs::attrs]) {
        return MapItem::Up {static_cast<const MapItem *>(itemFromJsonVal(*jsonAttrsVal).release())};
    }

    return createItem(MapItem::Container {});
}

} // namespace internal
} // namespace yactfr
