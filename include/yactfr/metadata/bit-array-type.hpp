/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_BIT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_BIT_ARRAY_TYPE_HPP

#include "bo.hpp"
#include "scalar-dt.hpp"
#include "dt.hpp"

namespace yactfr {

/*!
@brief
    Bit array type.

@ingroup metadata_dt

A bit array type describes data stream bit arrays.
*/
class BitArrayType :
    public ScalarDataType
{
protected:
    explicit BitArrayType(int kind, unsigned int align, unsigned int len, ByteOrder bo);

public:
    /// Length of data stream bit arrays (bits) described by this type.
    unsigned int length() const noexcept
    {
        return _len;
    }

    /// Byte order of data stream bit arrays described by this type.
    ByteOrder byteOrder() const noexcept
    {
        return _bo;
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other bit array type to compare to.

    @returns
        \c true if this bit array type is less than \p other
        (respects total order).
    */
    bool operator<(const BitArrayType& other) const noexcept;

protected:
    bool _compare(const DataType& other) const noexcept override;

private:
    const unsigned int _len;
    const ByteOrder _bo;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_BIT_ARRAY_TYPE_HPP
