/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dyn-array-type.hpp>

namespace yactfr {

DynamicArrayType::DynamicArrayType(const unsigned int minAlign, DataType::UP elemType,
                                   DataLocation lenLoc) :
    DynamicArrayType {_KIND_DYN_ARRAY, minAlign, std::move(elemType), std::move(lenLoc)}
{
}

DynamicArrayType::DynamicArrayType(const int kind, const unsigned int minAlign,
                                   DataType::UP elemType, DataLocation lenLoc) :
    ArrayType {_KIND_DYN_ARRAY | kind, minAlign, std::move(elemType)},
    _lenLoc {std::move(lenLoc)}
{
}

DataType::UP DynamicArrayType::_clone() const
{
    return std::make_unique<DynamicArrayType>(this->alignment(), this->elementType().clone(),
                                              _lenLoc);
}

bool DynamicArrayType::_compare(const DataType& other) const noexcept
{
    auto& otherDynArrayType = static_cast<const DynamicArrayType&>(other);

    return ArrayType::_compare(other) && _lenLoc == otherDynArrayType._lenLoc;
}

} // namespace yactfr
