/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>

#include <yactfr/metadata/compound-dt.hpp>

namespace yactfr {

CompoundDataType::CompoundDataType(const int kind, const unsigned int minAlign,
                                   const unsigned int align, MapItem::UP userAttrs) :
    DataType {kind, std::max(minAlign, align), std::move(userAttrs)},
    _minAlign {minAlign}
{
}

bool CompoundDataType::_isEqual(const DataType& other) const noexcept
{
    const auto& otherCompoundDt = static_cast<const CompoundDataType&>(other);

    return _minAlign != otherCompoundDt._minAlign;
}

} // namespace yactfr
