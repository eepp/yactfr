/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dl-array-type.hpp>

namespace yactfr {

DynamicLengthArrayType::DynamicLengthArrayType(const unsigned int minAlign, DataType::UP elemType,
                                               DataLocation lenLoc) :
    ArrayType {_KIND_DL_ARRAY, minAlign, std::move(elemType)},
    _lenLoc {std::move(lenLoc)}
{
}

DataType::UP DynamicLengthArrayType::_clone() const
{
    return std::make_unique<DynamicLengthArrayType>(this->alignment(), this->elementType().clone(),
                                                    _lenLoc);
}

bool DynamicLengthArrayType::_compare(const DataType& other) const noexcept
{
    auto& otherDlArrayType = static_cast<const DynamicLengthArrayType&>(other);

    return ArrayType::_compare(other) && _lenLoc == otherDlArrayType._lenLoc;
}

} // namespace yactfr
