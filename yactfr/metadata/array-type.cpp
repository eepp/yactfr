/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <cassert>

#include <yactfr/metadata/array-type.hpp>

namespace yactfr {

ArrayType::ArrayType(const _tKind kind, const unsigned int minAlign, DataType::Up elemType,
                     MapItem::Up attrs) :
    CompoundDataType {kind, minAlign, elemType->alignment(), std::move(attrs)},
    _elemType {std::move(elemType)}
{
    assert(_elemType);
}

bool ArrayType::_isEqual(const DataType& other) const noexcept
{
    return CompoundDataType::_isEqual(other) && *_elemType == *other.asArrayType()._elemType;
}

} // namespace yactfr
