/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len,
                                           std::string mediaType, MapItem::UP userAttrs,
                                           const bool hasMetadataStreamUuidRole) :
    BlobType {_KIND_SL_BLOB, align, std::move(userAttrs), std::move(mediaType)},
    _len {len},
    _hasMetadataStreamUuidRole {hasMetadataStreamUuidRole}
{
}

StaticLengthBlobType::StaticLengthBlobType(const Size len, std::string mediaType,
                                           MapItem::UP userAttrs,
                                           const bool hasMetadataStreamUuidRole) :
    StaticLengthBlobType {8, len, std::move(mediaType), std::move(userAttrs), hasMetadataStreamUuidRole}
{
}

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len,
                                           MapItem::UP userAttrs,
                                           const bool hasMetadataStreamUuidRole) :
    BlobType {_KIND_SL_BLOB, align, std::move(userAttrs)},
    _len {len},
    _hasMetadataStreamUuidRole {hasMetadataStreamUuidRole}
{
}

StaticLengthBlobType::StaticLengthBlobType(const Size len, MapItem::UP userAttrs,
                                           const bool hasMetadataStreamUuidRole) :
    StaticLengthBlobType {8, len, std::move(userAttrs), hasMetadataStreamUuidRole}
{
}

DataType::UP StaticLengthBlobType::_clone() const
{
    return StaticLengthBlobType::create(this->alignment(), _len, this->mediaType(),
                                        internal::tryCloneUserAttrs(this->userAttributes()),
                                        _hasMetadataStreamUuidRole);
}

bool StaticLengthBlobType::_isEqual(const DataType& other) const noexcept
{
    auto& otherSlBlobType = other.asStaticLengthBlobType();

    return BlobType::_isEqual(other) && _len == otherSlBlobType._len &&
           otherSlBlobType._hasMetadataStreamUuidRole == _hasMetadataStreamUuidRole;
}

} // namespace yactfr
