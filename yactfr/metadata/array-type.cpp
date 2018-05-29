/*
 * CTF array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/array-type.hpp>

namespace yactfr {

ArrayType::ArrayType(const unsigned int minAlign, DataType::UP elemType,
                     const Size length) :
    ArrayType {_KIND_ARRAY, minAlign, std::move(elemType), length}
{
}

ArrayType::ArrayType(const int kind, const unsigned int minAlign,
                     DataType::UP elemType, const Size length) :
    ArraySequenceTypeBase {_KIND_ARRAY | kind, minAlign, std::move(elemType)},
    _length {length}
{
}

DataType::UP ArrayType::_clone() const
{
    return std::make_unique<ArrayType>(this->alignment(),
                                       this->elemType().clone(),
                                       this->length());
}

bool ArrayType::_compare(const DataType& otherType) const
{
    auto& arrayType = static_cast<const ArrayType&>(otherType);

    return arrayType.alignment() == this->alignment() &&
           arrayType.elemType() == this->elemType() &&
           arrayType.length() == this->length();
}

} // namespace yactfr
