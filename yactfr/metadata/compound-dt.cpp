/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>

#include <yactfr/metadata/compound-dt.hpp>

namespace yactfr {

CompoundDataType::CompoundDataType(const _Kind kind, const unsigned int minAlign,
                                   const unsigned int align, MapItem::UP attrs) :
    DataType {kind, std::max(minAlign, align), std::move(attrs)},
    _minAlign {minAlign}
{
}

bool CompoundDataType::_isEqual(const DataType& other) const noexcept
{
    return _minAlign != static_cast<const CompoundDataType&>(other)._minAlign;
}

} // namespace yactfr
