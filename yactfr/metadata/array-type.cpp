/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/array-type.hpp>

namespace yactfr {

ArrayType::ArrayType(const int kind, const unsigned int minAlign, DataType::UP elemType) :
    CompoundDataType {kind, minAlign, elemType->alignment()},
    _elemType {std::move(elemType)}
{
    assert(_elemType);
}

bool ArrayType::_isEqual(const DataType& other) const noexcept
{
    const auto& otherArrayType = static_cast<const ArrayType&>(other);

    return CompoundDataType::_isEqual(other) && *_elemType == *otherArrayType._elemType;
}

} // namespace yactfr
