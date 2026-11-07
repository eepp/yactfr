/*
 * SPDX-FileCopyrightText: 2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len,
                                           std::string mediaType, MapItem::Up attrs,
                                           const bool hasMetadataStreamUuidRole) :
    BlobType {_kindSlBlob, align, std::move(attrs), std::move(mediaType)},
    _len {len},
    _hasMetadataStreamUuidRole {hasMetadataStreamUuidRole}
{
}

StaticLengthBlobType::StaticLengthBlobType(const Size len, std::string mediaType,
                                           MapItem::Up attrs,
                                           const bool hasMetadataStreamUuidRole) :
    StaticLengthBlobType {8, len, std::move(mediaType), std::move(attrs), hasMetadataStreamUuidRole}
{
}

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len,
                                           MapItem::Up attrs,
                                           const bool hasMetadataStreamUuidRole) :
    BlobType {_kindSlBlob, align, std::move(attrs)},
    _len {len},
    _hasMetadataStreamUuidRole {hasMetadataStreamUuidRole}
{
}

StaticLengthBlobType::StaticLengthBlobType(const Size len, MapItem::Up attrs,
                                           const bool hasMetadataStreamUuidRole) :
    StaticLengthBlobType {8, len, std::move(attrs), hasMetadataStreamUuidRole}
{
}

DataType::Up StaticLengthBlobType::_clone() const
{
    return StaticLengthBlobType::create(this->alignment(), _len, this->mediaType(),
                                        internal::tryCloneAttrs(this->attributes()),
                                        _hasMetadataStreamUuidRole);
}

bool StaticLengthBlobType::_isEqual(const DataType& other) const noexcept
{
    auto& otherSlBlobType = other.asStaticLengthBlobType();

    return BlobType::_isEqual(other) && _len == otherSlBlobType._len &&
           otherSlBlobType._hasMetadataStreamUuidRole == _hasMetadataStreamUuidRole;
}

} // namespace yactfr
