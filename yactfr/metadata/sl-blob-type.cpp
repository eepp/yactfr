/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/sl-blob-type.hpp>

namespace yactfr {

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len,
                                           std::string mediaType) :
    BlobType {_KIND_SL_BLOB, align, std::move(mediaType)},
    _len {len}
{
}

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len) :
    BlobType {_KIND_SL_BLOB, align},
    _len {len}
{
}

DataType::UP StaticLengthBlobType::_clone() const
{
    return std::make_unique<StaticLengthBlobType>(this->alignment(), _len, this->mediaType());
}

bool StaticLengthBlobType::_compare(const DataType& other) const noexcept
{
    auto& otherSlBlobType = static_cast<const StaticLengthBlobType&>(other);

    return BlobType::_compare(other) && _len == otherSlBlobType._len;
}

} // namespace yactfr
