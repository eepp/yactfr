/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_SL_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_SL_ARRAY_TYPE_HPP

#include <memory>
#include <utility>

#include "../aliases.hpp"
#include "array-type.hpp"
#include "dt-visitor.hpp"
#include "dt.hpp"

namespace yactfr {

/*!
@brief
    Static-length array type.

@ingroup metadata_dt

A static-length array type describes data stream static-length arrays.
*/
class StaticLengthArrayType final :
    public ArrayType
{
public:
    /// Unique pointer to constant static-length array type.
    using UP = std::unique_ptr<const StaticLengthArrayType>;

public:
    /*!
    @brief
        Builds a static-length array data type.

    @param[in] minimumAlignment
        Minimum alignment of data stream static-length arrays described
        by this type.
    @param[in] elementType
        %Element type.
    @param[in] length
        Length of data stream static-length arrays described by this
        type (count of element).
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length arrays described by
        this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] hasMetadataStreamUuidRole
        Whether or not the static-length arrays described by this type
        have the "metadata stream UUID" role.

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        \p elementType is set.
    @pre
        @parblock
        If \p hasMetadataStreamUuidRole is true, then \p length is 16
        and all of the following are true:

        - <code>elementType->%isFixedLengthUnsignedIntegerType()</code>
        - <code>elementType->%asFixedLengthUnsignedIntegerType().%length() == 8</code>
        - <code>elementType->%asFixedLengthUnsignedIntegerType().%alignment() == 8</code>
        @endparblock
    */
    explicit StaticLengthArrayType(unsigned int minimumAlignment, DataType::UP elementType,
                                   Size length, MapItem::UP userAttributes = nullptr,
                                   bool hasMetadataStreamUuidRole = false);

    /*!
    @brief
        Builds a static-length array data type having a default minimum
        alignment property (1).

    @param[in] elementType
        %Element type.
    @param[in] length
        Length of data stream static-length arrays described by this
        type (count of element).
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length arrays described by
        this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] hasMetadataStreamUuidRole
        Whether or not the static-length arrays described by this type
        have the "metadata stream UUID" role.

    @pre
        \p elementType is set.
    @pre
        @parblock
        If \p hasMetadataStreamUuidRole is true, then \p length is 16
        and all of the following are true:

        - <code>elementType->%isFixedLengthUnsignedIntegerType()</code>
        - <code>elementType->%asFixedLengthUnsignedIntegerType().%length() == 8</code>
        - <code>elementType->%asFixedLengthUnsignedIntegerType().%alignment() == 8</code>
        @endparblock
    */
    explicit StaticLengthArrayType(DataType::UP elementType, Size length,
                                   MapItem::UP userAttributes = nullptr,
                                   bool hasMetadataStreamUuidRole = false);

    /*!
    @brief
        Creates a constant static-length array type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the static-length array type
        constructor.

    @returns
        Created constant static-length array type unique pointer.

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
        Length of data stream static-length arrays described by this
        type (count of element).
    */
    Size length() const noexcept
    {
        return _len;
    }

    /*!
    @brief
        Whether or not the static-length arrays described by this type
        have the "metadata stream UUID" role.
    */
    bool hasMetadataStreamUuidRole() const noexcept
    {
        return _hasMetadataStreamUuidRole;
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
    const bool _hasMetadataStreamUuidRole;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SL_ARRAY_TYPE_HPP
