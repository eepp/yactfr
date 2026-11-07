/*
 * SPDX-FileCopyrightText: 2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#ifndef YACTFR_INTERNAL_METADATA_UTILS_HPP
#define YACTFR_INTERNAL_METADATA_UTILS_HPP

#include "../../metadata/item.hpp"

namespace yactfr::internal {

[[ nodiscard ]] inline MapItem::Up tryCloneAttrs(const MapItem * const attrs)
{
    if (!attrs) {
        return nullptr;
    }

    return MapItem::Up {static_cast<const MapItem *>(attrs->clone().release())};
}

/*
 * Returns whether or not the optional attributes `attrsA` and `attrsB`
 * are equal (both missing or both present and equal).
 */
[[ nodiscard ]] inline bool attrsAreEqual(const MapItem * const attrsA,
                                          const MapItem * const attrsB) noexcept
{
    if (!attrsA || !attrsB) {
        return attrsA == attrsB;
    }

    return *attrsA == *attrsB;
}

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_METADATA_UTILS_HPP
