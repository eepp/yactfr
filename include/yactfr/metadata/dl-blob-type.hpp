/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DL_BLOB_TYPE_HPP
#define _YACTFR_METADATA_DL_BLOB_TYPE_HPP

#include "blob-type.hpp"
#include "data-loc.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

/*!
@brief
    Dynamic-length BLOB type.

@ingroup metadata_dt

A dynamic-length BLOB type describes data stream dynamic-length
BLOBs.
*/
class DynamicLengthBlobType final :
    public BlobType
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief
        Builds a dynamic-length BLOB type.

    @param[in] alignment
        Alignment of data stream dynamic-length BLOBs described by this
        type.
    @param[in] lengthLocation
        Location of lengths (bytes) of data stream dynamic-length BLOBs
        described by this type.
    @param[in] mediaType
        <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types">IANA media type</a>
        of data stream dynamic-length BLOBs described by this type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit DynamicLengthBlobType(unsigned int alignment, DataLocation lengthLocation,
                                   std::string mediaType);

    /*!
    @brief
        Builds a dynamic-length BLOB type having a default IANA media
        type (<code>application/octet-stream</code>).

    @param[in] alignment
        Alignment of data stream dynamic-length BLOBs described by this
        type.
    @param[in] lengthLocation
        Location of lengths (bytes) of data stream dynamic-length BLOBs
        described by this type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit DynamicLengthBlobType(unsigned int alignment, DataLocation lengthLocation);

    /// Location of lengths (bytes) of data stream dynamic-length BLOBs
    /// described by this type.
    const DataLocation& lengthLocation() const noexcept
    {
        return _lenLoc;
    }

    /// Types of lengths (bytes) of data stream dynamic-length BLOBs
    /// described by this type, or an empty set if this type is not part
    /// of a trace type yet.
    const DataTypeSet& lengthTypes() const noexcept
    {
        return _theLenTypes;
    }

private:
    DataType::UP _clone() const override;
    bool _compare(const DataType& other) const noexcept override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    DataTypeSet& _lenTypes() const noexcept
    {
        return _theLenTypes;
    }

private:
    const DataLocation _lenLoc;
    mutable DataTypeSet _theLenTypes;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DL_BLOB_TYPE_HPP
