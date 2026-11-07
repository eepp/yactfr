/*
 * SPDX-FileCopyrightText: 2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#ifndef YACTFR_METADATA_BLOB_TYPE_HPP
#define YACTFR_METADATA_BLOB_TYPE_HPP

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
    explicit BlobType(_tKind kind, unsigned int align, MapItem::Up attrs,
                      std::string&& mediaType = BlobType::defaultMediaType());

public:
    /*!
    @brief
        <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types">IANA media type</a>
        of data stream BLOBs described by this type.
    */
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

#endif // YACTFR_METADATA_BLOB_TYPE_HPP
