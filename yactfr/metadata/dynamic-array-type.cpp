/*
 * CTF dynamic array type.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dynamic-array-type.hpp>

namespace yactfr {

DynamicArrayType::DynamicArrayType(const unsigned int minAlign,
                                   DataType::UP elemType,
                                   const FieldRef& length) :
    DynamicArrayType {_KIND_DYNAMIC_ARRAY, minAlign, std::move(elemType), length}
{
}

DynamicArrayType::DynamicArrayType(const int kind, const unsigned int minAlign,
                                   DataType::UP elemType, const FieldRef& length) :
    ArrayType {_KIND_DYNAMIC_ARRAY | kind, minAlign, std::move(elemType)},
    _length {length}
{
}

DataType::UP DynamicArrayType::_clone() const
{
    return std::make_unique<DynamicArrayType>(this->alignment(),
                                              this->elemType().clone(),
                                              this->length());
}

bool DynamicArrayType::_compare(const DataType& otherType) const
{
    auto& seqType = static_cast<const DynamicArrayType&>(otherType);

    return seqType.alignment() == this->alignment() &&
           seqType.elemType() == this->elemType() &&
           seqType.length() == this->length();
}

} // namespace yactfr
