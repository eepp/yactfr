/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "utils.hpp"

namespace yactfr {
namespace internal {

MapItem::UP tryCloneUserAttrs(const MapItem * const userAttrs)
{
    if (!userAttrs) {
        return nullptr;
    }

    return MapItem::UP {static_cast<const MapItem *>(userAttrs->clone().release())};
}

} // namespace internal
} // namespace yactfr
