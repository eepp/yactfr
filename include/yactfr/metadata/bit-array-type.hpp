/*
 * CTF bit array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Bit array type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_BITARRAY_TYPE_HPP
#define _YACTFR_METADATA_BITARRAY_TYPE_HPP

#include "data-type.hpp"
#include "scalar-type.hpp"
#include "aliases.hpp"
#include "byte-order.hpp"
#include "data-type-visitor.hpp"

namespace yactfr {

/*!
@brief  Bit array type.

@ingroup metadata_dt

A bit array type describes data stream bit arrays.
*/
class BitArrayType :
    public ScalarType
{
protected:
    explicit BitArrayType(int kind, unsigned int align, unsigned int size,
                          ByteOrder byteOrder);

public:
    /// Size of data stream bit arrays (bits) described by this type.
    unsigned int size() const noexcept
    {
        return _size;
    }

    /// Byte order of data stream bit arrays described by this type.
    ByteOrder byteOrder() const noexcept
    {
        return _byteOrder;
    }

    /*!
    @brief  Less-than operator.

    @param bitArrayType Other bit array type to compare with.
    @returns            \c true if this bit array type
                        is less than \p bitArrayType (respects total order).
    */
    bool operator<(const BitArrayType& bitArrayType) const noexcept;

private:
    bool _compare(const DataType& otherType) const noexcept override;

private:
    const unsigned int _size;
    const ByteOrder _byteOrder;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_BITARRAY_TYPE_HPP
