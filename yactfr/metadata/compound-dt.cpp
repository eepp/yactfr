/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <algorithm>

#include <yactfr/metadata/compound-dt.hpp>

namespace yactfr {

CompoundDataType::CompoundDataType(const _tKind kind, const unsigned int minAlign,
                                   const unsigned int align, MapItem::Up attrs) :
    DataType {kind, std::max(minAlign, align), std::move(attrs)},
    _minAlign {minAlign}
{
}

bool CompoundDataType::_isEqual(const DataType& other) const noexcept
{
    return _minAlign == static_cast<const CompoundDataType&>(other)._minAlign;
}

} // namespace yactfr
