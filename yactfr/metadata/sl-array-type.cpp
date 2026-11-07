/*
 * SPDX-FileCopyrightText: 2015-2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

StaticLengthArrayType::StaticLengthArrayType(const unsigned int minAlign, DataType::Up elemType,
                                             const Size len, MapItem::Up attrs,
                                             const bool hasMetadataStreamUuidRole) :
    ArrayType {_kindSlArray, minAlign, std::move(elemType), std::move(attrs)},
    _len {len},
    _hasMetadataStreamUuidRole {hasMetadataStreamUuidRole}
{
}

StaticLengthArrayType::StaticLengthArrayType(DataType::Up elemType, const Size len,
                                             MapItem::Up attrs,
                                             const bool hasMetadataStreamUuidRole) :
    StaticLengthArrayType {1, std::move(elemType), len, std::move(attrs), hasMetadataStreamUuidRole}
{
}

DataType::Up StaticLengthArrayType::_clone() const
{
    return StaticLengthArrayType::create(this->minimumAlignment(), this->elementType().clone(),
                                         _len, internal::tryCloneAttrs(this->attributes()),
                                         _hasMetadataStreamUuidRole);
}

bool StaticLengthArrayType::_isEqual(const DataType& other) const noexcept
{
    auto& otherStaticLengthArrayType = other.asStaticLengthArrayType();

    return ArrayType::_isEqual(other) && _len == otherStaticLengthArrayType._len &&
           otherStaticLengthArrayType._hasMetadataStreamUuidRole == _hasMetadataStreamUuidRole;
}

} // namespace yactfr
