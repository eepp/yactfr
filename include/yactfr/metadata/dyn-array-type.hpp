/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DYN_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_DYN_ARRAY_TYPE_HPP

#include "array-type.hpp"
#include "data-loc.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

class DataType;

/*!
@brief
    Dynamic array type.

@ingroup metadata_dt

A dynamic array type describes data stream dynamic arrays.
*/
class DynamicArrayType final :
    public ArrayType
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief
        Builds a dynamic array type.

    @param[in] minimumAlignment
        Minimum alignment of data stream dynamic arrays described by
        this type.
    @param[in] elementType
        Element type.
    @param[in] lengthLocation
        Location of lengths of data stream dynamic arrays described by
        this type (number of elements).

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        \p lengthLocation only locates unsigned integers.
    */
    explicit DynamicArrayType(unsigned int minimumAlignment, DataType::UP elementType,
                              DataLocation lengthLocation);

    /// Location of lengths of data stream dynamic arrays described by
    /// this type.
    const DataLocation& lengthLocation() const noexcept
    {
        return _lenLoc;
    }

    /// Types of lengths of data stream dynamic arrays described by this
    /// type, or an empty set if this type is not part of a trace type
    /// yet.
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

#endif // _YACTFR_METADATA_DYN_ARRAY_TYPE_HPP
