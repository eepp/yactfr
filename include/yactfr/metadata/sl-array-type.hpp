/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_SL_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_SL_ARRAY_TYPE_HPP

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
    @param[in] hasTraceTypeUuidRole
        Whether or not the static-length arrays described by this type
        have the "trace type UUID" role.

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        @parblock
        If \p hasTraceTypeUuidRole is true, then \p length is 16 and all
        of the following are true:

        - <code>elementType->%isFixedLengthUnsignedIntegerType()</code>
        - <code>elementType->%asFixedLengthUnsignedIntegerType().%length() == 8</code>
        - <code>elementType->%asFixedLengthUnsignedIntegerType().%alignment() == 8</code>
        @endparblock
    */
    explicit StaticLengthArrayType(unsigned int minimumAlignment, DataType::UP elementType,
                                   Size length, MapItem::UP userAttributes = nullptr,
                                   bool hasTraceTypeUuidRole = false);

    /// Length of data stream static-length arrays described by this
    /// type (count of element).
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

#endif // _YACTFR_METADATA_SL_ARRAY_TYPE_HPP
