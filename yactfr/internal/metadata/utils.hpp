/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/item.hpp>

namespace yactfr {
namespace internal {

MapItem::UP tryCloneUserAttrs(const MapItem *userAttrs);

} // namespace internal
} // namespace yactfr
