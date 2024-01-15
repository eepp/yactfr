/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DL_BLOB_TYPE_HPP
#define _YACTFR_METADATA_DL_BLOB_TYPE_HPP

#include <memory>
#include <utility>

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
    /// Unique pointer to constant dynamic-length BLOB type.
    using UP = std::unique_ptr<const DynamicLengthBlobType>;

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
    @param[in] attributes
        @parblock
        Attributes of data stream dynamic-length BLOBs described by
        this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit DynamicLengthBlobType(unsigned int alignment, DataLocation lengthLocation,
                                   std::string mediaType, MapItem::UP attributes = nullptr);

    /*!
    @brief
        Builds a dynamic-length BLOB type having a default alignment
        property (8).

    @param[in] lengthLocation
        Location of lengths (bytes) of data stream dynamic-length BLOBs
        described by this type.
    @param[in] mediaType
        <a href="https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types">IANA media type</a>
        of data stream dynamic-length BLOBs described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream dynamic-length BLOBs described by
        this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    */
    explicit DynamicLengthBlobType(DataLocation lengthLocation,
                                   std::string mediaType, MapItem::UP attributes = nullptr);

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
    @param[in] attributes
        Attributes of data stream dynamic-length BLOBs described
        by this type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit DynamicLengthBlobType(unsigned int alignment, DataLocation lengthLocation,
                                   MapItem::UP attributes = nullptr);

    /*!
    @brief
        Builds a dynamic-length BLOB type having a default IANA media
        type (<code>application/octet-stream</code>) and alignment
        property (8).

    @param[in] lengthLocation
        Location of lengths (bytes) of data stream dynamic-length BLOBs
        described by this type.
    @param[in] attributes
        Attributes of data stream dynamic-length BLOBs described
        by this type.
    */
    explicit DynamicLengthBlobType(DataLocation lengthLocation,
                                   MapItem::UP attributes = nullptr);

    /*!
    @brief
        Creates a constant dynamic-length BLOB type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the dynamic-length BLOB type
        constructor.

    @returns
        Created constant dynamic-length BLOB type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

    /*!
    @brief
        Location of lengths (bytes) of data stream dynamic-length BLOBs
        described by this type.
    */
    const DataLocation& lengthLocation() const noexcept
    {
        return _lenLoc;
    }

    /*!
    @brief
        Types of lengths (bytes) of data stream dynamic-length BLOBs
        described by this type, or an empty set if this type is not part
        of a trace type yet.
    */
    const DataTypeSet& lengthTypes() const noexcept
    {
        return _theLenTypes;
    }

private:
    DataType::UP _clone() const override;
    bool _isEqual(const DataType& other) const noexcept override;

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
