/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dl-blob-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

DynamicLengthBlobType::DynamicLengthBlobType(const unsigned int align, DataLocation lenLoc,
                                             std::string mediaType, MapItem::UP attrs) :
    BlobType {_KIND_DL_BLOB, align, std::move(attrs), std::move(mediaType)},
    _lenLoc {std::move(lenLoc)}
{
}

DynamicLengthBlobType::DynamicLengthBlobType(DataLocation lenLoc, std::string mediaType,
                                             MapItem::UP attrs) :
    DynamicLengthBlobType {8, std::move(lenLoc), std::move(mediaType), std::move(attrs)}
{
}

DynamicLengthBlobType::DynamicLengthBlobType(const unsigned int align, DataLocation lenLoc,
                                             MapItem::UP attrs) :
    BlobType {_KIND_DL_BLOB, align, std::move(attrs)},
    _lenLoc {std::move(lenLoc)}
{
}

DynamicLengthBlobType::DynamicLengthBlobType(DataLocation lenLoc, MapItem::UP attrs) :
    DynamicLengthBlobType {8, std::move(lenLoc), std::move(attrs)}
{
}

DataType::UP DynamicLengthBlobType::_clone() const
{
    return DynamicLengthBlobType::create(this->alignment(), _lenLoc, this->mediaType(),
                                         internal::tryCloneAttrs(this->attributes()));
}

bool DynamicLengthBlobType::_isEqual(const DataType& other) const noexcept
{
    return BlobType::_isEqual(other) &&
           _lenLoc == other.asDynamicLengthBlobType()._lenLoc;
}

} // namespace yactfr
