/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

DynamicLengthArrayType::DynamicLengthArrayType(const unsigned int minAlign, DataType::Up elemType,
                                               DataLocation lenLoc, MapItem::Up attrs) :
    ArrayType {_kindDlArray, minAlign, std::move(elemType), std::move(attrs)},
    _lenLoc {std::move(lenLoc)}
{
}

DynamicLengthArrayType::DynamicLengthArrayType(DataType::Up elemType, DataLocation lenLoc,
                                               MapItem::Up attrs) :
    DynamicLengthArrayType {1, std::move(elemType), std::move(lenLoc), std::move(attrs)}
{
}

DataType::Up DynamicLengthArrayType::_clone() const
{
    return DynamicLengthArrayType::create(this->alignment(), this->elementType().clone(), _lenLoc,
                                          internal::tryCloneAttrs(this->attributes()));
}

bool DynamicLengthArrayType::_isEqual(const DataType& other) const noexcept
{
    return ArrayType::_isEqual(other) && _lenLoc == other.asDynamicLengthArrayType()._lenLoc;
}

} // namespace yactfr
