/*
 * CTF dynamic array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Dynamic array type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_DYNAMIC_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_DYNAMIC_ARRAY_TYPE_HPP

// for ArrayType
#include "array-type.hpp"

// for FieldRef
#include "field-ref.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

class DataType;

/*!
@brief  Dynamic array type.

@ingroup metadata_dt

A dynamic array type describes data stream dynamic arrays.
*/
class DynamicArrayType :
    public ArrayType
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief  Builds a dynamic array type.

    @param minAlign Minimal alignment of data stream dynamic arrays
                    described by this dynamic array type (power of two,
                    greater than 0).
    @param elemType Element's type.
    @param length   Field reference of the length of data stream
                    dynamic arrays described by this dynamic array type
                    (number of elements).

    @throws InvalidMetadata The dynamic array type is invalid.
    */
    explicit DynamicArrayType(unsigned int minAlign, DataType::UP elemType,
                              const FieldRef& length);

protected:
    explicit DynamicArrayType(int kind, unsigned int minAlign,
                              DataType::UP elemType, const FieldRef& length);

public:
    /*!
    @brief  Field reference of the length of data stream dynamic arrays
            described by this dynamic array type (number of elements).
    */
    const FieldRef& length() const noexcept
    {
        return _length;
    }

    /*!
    @brief  Length's field type.

    \c nullptr if this dynamic array type is not part of a trace type's
    hierarchy yet.
    */
    const DataType *lengthType() const noexcept
    {
        return this->_lengthType;
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& otherType) const override;

private:
    const FieldRef _length;
    mutable const DataType *_lengthType = nullptr;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DYNAMIC_ARRAY_TYPE_HPP
