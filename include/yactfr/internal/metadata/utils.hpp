/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_UTILS_HPP
#define _YACTFR_INTERNAL_METADATA_UTILS_HPP

#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "../../metadata/item.hpp"

namespace yactfr {
namespace internal {

static inline MapItem::UP tryCloneAttrs(const MapItem * const attrs)
{
    if (!attrs) {
        return nullptr;
    }

    return MapItem::UP {static_cast<const MapItem *>(attrs->clone().release())};
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_UTILS_HPP
