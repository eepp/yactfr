/*
 * CTF array data type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Array data type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_ARRAY_TYPE_HPP

// for Size
#include "../aliases.hpp"

// for ArraySequenceTypeBase
#include "array-sequence-type-base.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

// for DataType
#include "data-type.hpp"

namespace yactfr {

/*!
@brief  Array type.

@ingroup metadata_dt

An array type describes data stream arrays.
*/
class ArrayType :
    public ArraySequenceTypeBase
{
public:
    /*!
    @brief  Builds an array data type.

    @param minAlign Minimal alignment of data stream arrays
                    described by this array type (power of two,
                    greater than 0).
    @param elemType Element's type.
    @param length   Length of data stream arrays described by this array
                    type (number of element).

    @throws InvalidMetadata The array type is invalid.
    */
    explicit ArrayType(unsigned int minAlign, DataType::UP elemType,
                       Size length);

protected:
    explicit ArrayType(int kind, unsigned int align, DataType::UP elemType,
                       Size length);

public:
    /// Length of data stream arrays described by this array type
    /// (number of element).
    Size length() const noexcept
    {
        return _length;
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& otherType) const override;

private:
    const Size _length;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_ARRAY_TYPE_HPP
