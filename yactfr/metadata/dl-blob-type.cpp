/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dl-blob-type.hpp>

namespace yactfr {

DynamicLengthBlobType::DynamicLengthBlobType(const unsigned int align, DataLocation lenLoc,
                                             std::string mediaType) :
    BlobType {_KIND_DL_BLOB, align, std::move(mediaType)},
    _lenLoc {std::move(lenLoc)}
{
}

DynamicLengthBlobType::DynamicLengthBlobType(const unsigned int align, DataLocation lenLoc) :
    BlobType {_KIND_DL_BLOB, align},
    _lenLoc {std::move(lenLoc)}
{
}

DataType::UP DynamicLengthBlobType::_clone() const
{
    return std::make_unique<DynamicLengthBlobType>(this->alignment(), _lenLoc, this->mediaType());
}

bool DynamicLengthBlobType::_isEqual(const DataType& other) const noexcept
{
    auto& otherDlBlobType = static_cast<const DynamicLengthBlobType&>(other);

    return BlobType::_isEqual(other) && _lenLoc == otherDlBlobType._lenLoc;
}

} // namespace yactfr
