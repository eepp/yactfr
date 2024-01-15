/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/array-type.hpp>

namespace yactfr {

ArrayType::ArrayType(const _Kind kind, const unsigned int minAlign, DataType::UP elemType,
                     MapItem::UP userAttrs) :
    CompoundDataType {kind, minAlign, elemType->alignment(), std::move(userAttrs)},
    _elemType {std::move(elemType)}
{
    assert(_elemType);
}

bool ArrayType::_isEqual(const DataType& other) const noexcept
{
    return CompoundDataType::_isEqual(other) && *_elemType == *other.asArrayType()._elemType;
}

} // namespace yactfr
