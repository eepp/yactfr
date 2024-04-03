/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <utility>

#include <yactfr/metadata/blob-type.hpp>

namespace yactfr {

BlobType::BlobType(const _tKind kind, const unsigned int align, MapItem::Up attrs,
                   std::string&& mediaType) :
    ScalarDataType {kind, align, std::move(attrs)},
    _mediaType {std::move(mediaType)}
{
    assert(align >= 8);
}

bool BlobType::_isEqual(const DataType& other) const noexcept
{
    return _mediaType == other.asBlobType()._mediaType;
}

} // namespace yactfr
