/*
 * CTF static array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/static-array-type.hpp>

namespace yactfr {

StaticArrayType::StaticArrayType(const unsigned int minAlign, DataType::UP elemType,
                                 const Size length) :
    StaticArrayType {_KIND_STATIC_ARRAY, minAlign, std::move(elemType), length}
{
}

StaticArrayType::StaticArrayType(const int kind, const unsigned int minAlign,
                                 DataType::UP elemType, const Size length) :
    ArrayType {_KIND_STATIC_ARRAY | kind, minAlign, std::move(elemType)},
    _length {length}
{
}

DataType::UP StaticArrayType::_clone() const
{
    return std::make_unique<StaticArrayType>(this->alignment(),
                                             this->elemType().clone(),
                                             this->length());
}

bool StaticArrayType::_compare(const DataType& otherType) const
{
    auto& arrayType = static_cast<const StaticArrayType&>(otherType);

    return arrayType.alignment() == this->alignment() &&
           arrayType.elemType() == this->elemType() &&
           arrayType.length() == this->length();
}

} // namespace yactfr
