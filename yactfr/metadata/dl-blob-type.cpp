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
                                             std::string mediaType, MapItem::UP userAttrs) :
    BlobType {_KIND_DL_BLOB, align, std::move(userAttrs), std::move(mediaType)},
    _lenLoc {std::move(lenLoc)}
{
}

DynamicLengthBlobType::DynamicLengthBlobType(DataLocation lenLoc, std::string mediaType,
                                             MapItem::UP userAttrs) :
    DynamicLengthBlobType {8, std::move(lenLoc), std::move(mediaType), std::move(userAttrs)}
{
}

DynamicLengthBlobType::DynamicLengthBlobType(const unsigned int align, DataLocation lenLoc,
                                             MapItem::UP userAttrs) :
    BlobType {_KIND_DL_BLOB, align, std::move(userAttrs)},
    _lenLoc {std::move(lenLoc)}
{
}

DynamicLengthBlobType::DynamicLengthBlobType(DataLocation lenLoc, MapItem::UP userAttrs) :
    DynamicLengthBlobType {8, std::move(lenLoc), std::move(userAttrs)}
{
}

DataType::UP DynamicLengthBlobType::_clone() const
{
    return DynamicLengthBlobType::create(this->alignment(), _lenLoc, this->mediaType(),
                                         internal::tryCloneUserAttrs(this->userAttributes()));
}

bool DynamicLengthBlobType::_isEqual(const DataType& other) const noexcept
{
    auto& otherDlBlobType = static_cast<const DynamicLengthBlobType&>(other);

    return BlobType::_isEqual(other) && _lenLoc == otherDlBlobType._lenLoc;
}

} // namespace yactfr
