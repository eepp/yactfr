/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_SL_BLOB_TYPE_HPP
#define _YACTFR_METADATA_SL_BLOB_TYPE_HPP

#include "../aliases.hpp"
#include "blob-type.hpp"
#include "dt-visitor.hpp"
#include "dt.hpp"

namespace yactfr {

/*!
@brief
    Static-length BLOB type.

@ingroup metadata_dt

A static-length BLOB type describes data stream static-length BLOBs.
*/
class StaticLengthBlobType final :
    public BlobType
{
public:
    /*!
    @brief
        Builds a static-length BLOB data type having a default
        IANA media type (<code>application/octet-stream</code>).

    @param[in] alignment
        Alignment of data stream static-length BLOBs described by this
        type.
    @param[in] length
        Length (bytes) of data stream static-length BLOBs described by
        this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length BLOBs described by
        this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] hasTraceTypeUuidRole
        Whether or not the static-length BLOBs described by this type
        have the "trace type UUID" role.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    @pre
        If \p hasTraceTypeUuidRole is true, then \p length is 16.
    */
    explicit StaticLengthBlobType(unsigned int alignment, Size length,
                                  MapItem::UP userAttributes = nullptr,
                                  bool hasTraceTypeUuidRole = false);

    /*!
    @brief
        Builds a static-length BLOB data type having a default IANA
        media type (<code>application/octet-stream</code>) and a default
        alignment property (8).

    @param[in] length
        Length (bytes) of data stream static-length BLOBs described by
        this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length BLOBs described by
        this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] hasTraceTypeUuidRole
        Whether or not the static-length BLOBs described by this type
        have the "trace type UUID" role.

    @pre
        If \p hasTraceTypeUuidRole is true, then \p length is 16.
    */
    explicit StaticLengthBlobType(Size length, MapItem::UP userAttributes = nullptr,
                                  bool hasTraceTypeUuidRole = false);

    /*!
    @brief
        Builds a static-length BLOB data type.

    @param[in] alignment
        Alignment of data stream static-length BLOBs described by this
        type.
    @param[in] length
        Length (bytes) of data stream static-length BLOBs described by
        this type.
    @param[in] mediaType
        <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types">IANA media type</a>
        of data stream static-length BLOBs described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length BLOBs described by
        this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] hasTraceTypeUuidRole
        Whether or not the static-length BLOBs described by this type
        have the "trace type UUID" role.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    @pre
        If \p hasTraceTypeUuidRole is true, then \p length is 16.
    */
    explicit StaticLengthBlobType(unsigned int alignment, Size length, std::string mediaType,
                                  MapItem::UP userAttributes = nullptr,
                                  bool hasTraceTypeUuidRole = false);

    /*!
    @brief
        Builds a static-length BLOB data type having a default
        alignment property (8).

    @param[in] length
        Length (bytes) of data stream static-length BLOBs described by
        this type.
    @param[in] mediaType
        <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types">IANA media type</a>
        of data stream static-length BLOBs described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length BLOBs described by
        this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] hasTraceTypeUuidRole
        Whether or not the static-length BLOBs described by this type
        have the "trace type UUID" role.

    @pre
        If \p hasTraceTypeUuidRole is true, then \p length is 16.
    */
    explicit StaticLengthBlobType(Size length, std::string mediaType,
                                  MapItem::UP userAttributes = nullptr,
                                  bool hasTraceTypeUuidRole = false);

    /// Length (bytes) of data stream static-length BLOBs described by
    /// this type.
    Size length() const noexcept
    {
        return _len;
    }

    /// Whether or not the static-length arrays described by this type
    /// have the "trace type UUID" role.
    bool hasTraceTypeUuidRole() const noexcept
    {
        return _hasTraceTypeUuidRole;
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _isEqual(const DataType& other) const noexcept override;

private:
    const Size _len;
    const bool _hasTraceTypeUuidRole;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SL_BLOB_TYPE_HPP
