/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

DynamicLengthArrayType::DynamicLengthArrayType(const unsigned int minAlign, DataType::UP elemType,
                                               DataLocation lenLoc, MapItem::UP userAttrs) :
    ArrayType {_KIND_DL_ARRAY, minAlign, std::move(elemType), std::move(userAttrs)},
    _lenLoc {std::move(lenLoc)}
{
}

DataType::UP DynamicLengthArrayType::_clone() const
{
    return std::make_unique<DynamicLengthArrayType>(this->alignment(), this->elementType().clone(),
                                                    _lenLoc,
                                                    internal::tryCloneUserAttrs(this->userAttributes()));
}

bool DynamicLengthArrayType::_isEqual(const DataType& other) const noexcept
{
    auto& otherDlArrayType = static_cast<const DynamicLengthArrayType&>(other);

    return ArrayType::_isEqual(other) && _lenLoc == otherDlArrayType._lenLoc;
}

} // namespace yactfr
