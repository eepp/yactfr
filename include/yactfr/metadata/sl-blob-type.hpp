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

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit StaticLengthBlobType(unsigned int alignment, Size length);

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

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit StaticLengthBlobType(unsigned int alignment, Size length,
                                  std::string mediaType);

    /// Length (bytes) of data stream static-length BLOBs described by
    /// this type.
    Size length() const noexcept
    {
        return _len;
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& other) const noexcept override;

private:
    const Size _len;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SL_BLOB_TYPE_HPP
