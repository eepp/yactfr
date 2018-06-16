/*
 * CTF floating point number type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Floating point number type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_FLOAT_TYPE_HPP
#define _YACTFR_METADATA_FLOAT_TYPE_HPP

// for BitArrayType
#include "bit-array-type.hpp"

// for ByteOrder
#include "byte-order.hpp"

// for DataType
#include "data-type.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

namespace yactfr {

class DataTypeVisitor;

/*!
@brief  Floating point number type.

@ingroup metadata_dt

A floating point number type describes data stream floating point numbers.
*/
class FloatType final :
    public BitArrayType
{
public:
    /*!
    @brief  Builds a floating point number type.

    @param align        Alignment of data stream floating point numbers
                        described by this floating point number type
                        (power of two, greater than 0).
    @param size         Size of data stream floating point numbers
                        described by this floating point number type.
    @param byteOrder    Byte order of data stream floating point numbers
                        described by this floating point number type.

    @throws InvalidMetadata The floating point number
                                     type is invalid.
    */
    explicit FloatType(unsigned int align, unsigned int size,
                       ByteOrder byteOrder);

    /*!
    @brief  Copy constructor.

    @param floatType  Floating point number type to copy.
    */
    FloatType(const FloatType& floatType);

    /*!
    @brief  Less-than operator.

    @param floatType    Other floating point number type to compare with.
    @returns            \c true if this floating point number type
                        is less than \p floatType (respects total order).
    */
    bool operator<(const FloatType& floatType) const noexcept;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& otherType) const noexcept override;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FLOAT_TYPE_HPP
