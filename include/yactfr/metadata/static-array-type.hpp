/*
 * CTF static array data type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Static array data type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_STATIC_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_STATIC_ARRAY_TYPE_HPP

// for Size
#include "../aliases.hpp"

// for ArrayType
#include "array-type.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

// for DataType
#include "data-type.hpp"

namespace yactfr {

/*!
@brief  Static array type.

@ingroup metadata_dt

A static array type describes data stream static arrays.
*/
class StaticArrayType :
    public ArrayType
{
public:
    /*!
    @brief  Builds a static array data type.

    @param minAlign Minimal alignment of data stream static arrays
                    described by this static array type (power of two,
                    greater than 0).
    @param elemType Element's type.
    @param length   Length of data stream static arrays described by
                    this static array type (number of element).

    @throws InvalidMetadata The static array type is invalid.
    */
    explicit StaticArrayType(unsigned int minAlign, DataType::UP elemType,
                             Size length);

protected:
    explicit StaticArrayType(int kind, unsigned int align, DataType::UP elemType,
                             Size length);

public:
    /// Length of data stream static arrays described by this static
    /// array type (number of element).
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

#endif // _YACTFR_METADATA_STATIC_ARRAY_TYPE_HPP
