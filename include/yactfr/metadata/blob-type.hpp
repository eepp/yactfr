/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_BLOB_TYPE_HPP
#define _YACTFR_METADATA_BLOB_TYPE_HPP

#include <string>

#include "scalar-dt.hpp"
#include "dt.hpp"

namespace yactfr {

/*!
@brief
    %Base class of static-length and dynamic-length BLOB types.

@ingroup metadata_dt
*/
class BlobType :
    public ScalarDataType
{
protected:
    explicit BlobType(_Kind kind, unsigned int align, MapItem::UP userAttrs,
                      std::string mediaType = BlobType::defaultMediaType());

public:
    /// <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types">IANA media type</a>
    /// of data stream BLOBs described by this type.
    const std::string& mediaType() const
    {
        return _mediaType;
    }

    /// Default BLOB type media type.
    static constexpr const char *defaultMediaType() noexcept
    {
        return "application/octet-stream";
    }

protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    const std::string _mediaType;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_BLOB_TYPE_HPP
