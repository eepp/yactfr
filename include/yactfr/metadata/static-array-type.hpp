/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_STATIC_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_STATIC_ARRAY_TYPE_HPP

#include "../aliases.hpp"
#include "array-type.hpp"
#include "dt-visitor.hpp"
#include "dt.hpp"

namespace yactfr {

/*!
@brief
    Static array type.

@ingroup metadata_dt

A static array type describes data stream static arrays.
*/
class StaticArrayType :
    public ArrayType
{
public:
    /*!
    @brief
        Builds a static array data type.

    @param[in] minimumAlignment
        Minimum alignment of data stream static arrays described by this
        type.
    @param[in] elementType
        Element type.
    @param[in] length
        Length of data stream static arrays described by this type
        (count of element).
    @param[in] hasTraceTypeUuidRole
        Whether or not the static arrays described by this type have the
        "trace type UUID" role.

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        @parblock
        If \p hasTraceTypeUuidRole is true, then \p length is 16 and
        all of the following are true:

        * <code>elementType->isUnsignedIntegerType()</code>
        * <code>elementType->asUnsignedIntegerType().length() == 8</code>
        @endparblock
    */
    explicit StaticArrayType(unsigned int minimumAlignment, DataType::UP elementType, Size length,
                             bool hasTraceTypeUuidRole = false);

protected:
    explicit StaticArrayType(int kind, unsigned int minAlign, DataType::UP elemType, Size len,
                             bool hasTraceTypeUuidRole = false);

public:
    /// Length of data stream static arrays described by this type
    /// (count of element).
    Size length() const noexcept
    {
        return _len;
    }

    /// Whether or not the static arrays described by this type have
    /// the "trace type UUID" role.
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

    bool _compare(const DataType& other) const noexcept override;

private:
    const Size _len;
    const bool _hasTraceTypeUuidRole;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STATIC_ARRAY_TYPE_HPP
