/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FL_BIT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_FL_BIT_ARRAY_TYPE_HPP

#include "bo.hpp"
#include "scalar-dt.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Fixed-length bit array type.

@ingroup metadata_dt

A fixed-length bit array type describes data stream fixed-length bit
arrays.
*/
class FixedLengthBitArrayType :
    public ScalarDataType
{
protected:
    explicit FixedLengthBitArrayType(int kind, unsigned int align, unsigned int len, ByteOrder bo,
                                     MapItem::UP userAttrs);

public:
    /*!
    @brief
        Builds a fixed-length bit array type.

    @param[in] alignment
        Alignment of data stream fixed-length bit arrays described by
        this type.
    @param[in] length
        Length of data stream fixed-length bit arrays (bits) described
        by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length bit arrays described by
        this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length bit arrays described
        by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit FixedLengthBitArrayType(unsigned int alignment, unsigned int length,
                                     ByteOrder byteOrder,
                                     MapItem::UP userAttributes = nullptr);

    /// Length of data stream fixed-length bit arrays (bits) described
    /// by this type.
    unsigned int length() const noexcept
    {
        return _len;
    }

    /// Byte order of data stream fixed-length bit arrays described by
    /// this type.
    ByteOrder byteOrder() const noexcept
    {
        return _bo;
    }

    /*!
    @brief
        Less-than operator.

    @attention
        This operator doesn't consider user attributes.

    @param[in] other
        Other fixed-length bit array type to compare to.

    @returns
        \c true if this fixed-length bit array type is less than
        \p other (respects total order).
    */
    bool operator<(const FixedLengthBitArrayType& other) const noexcept;

protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const unsigned int _len;
    const ByteOrder _bo;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FL_BIT_ARRAY_TYPE_HPP
