/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

StaticLengthArrayType::StaticLengthArrayType(const unsigned int minAlign, DataType::UP elemType,
                                             const Size len, MapItem::UP userAttrs,
                                             const bool hasMetadataStreamUuidRole) :
    ArrayType {_KIND_SL_ARRAY, minAlign, std::move(elemType), std::move(userAttrs)},
    _len {len},
    _hasMetadataStreamUuidRole {hasMetadataStreamUuidRole}
{
}

StaticLengthArrayType::StaticLengthArrayType(DataType::UP elemType, const Size len,
                                             MapItem::UP userAttrs,
                                             const bool hasMetadataStreamUuidRole) :
    StaticLengthArrayType {1, std::move(elemType), len, std::move(userAttrs), hasMetadataStreamUuidRole}
{
}

DataType::UP StaticLengthArrayType::_clone() const
{
    return StaticLengthArrayType::create(this->minimumAlignment(), this->elementType().clone(),
                                         _len, internal::tryCloneUserAttrs(this->userAttributes()),
                                         _hasMetadataStreamUuidRole);
}

bool StaticLengthArrayType::_isEqual(const DataType& other) const noexcept
{
    auto& otherStaticLengthArrayType = other.asStaticLengthArrayType();

    return ArrayType::_isEqual(other) && _len == otherStaticLengthArrayType._len &&
           otherStaticLengthArrayType._hasMetadataStreamUuidRole == _hasMetadataStreamUuidRole;
}

} // namespace yactfr
