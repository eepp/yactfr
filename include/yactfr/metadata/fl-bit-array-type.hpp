/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_FL_BIT_ARRAY_TYPE_HPP
#define YACTFR_METADATA_FL_BIT_ARRAY_TYPE_HPP

#include <memory>
#include <utility>
#include <boost/optional/optional.hpp>

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
public:
    /// Unique pointer to constant fixed-length bit array type.
    using Up = std::unique_ptr<const FixedLengthBitArrayType>;

protected:
    explicit FixedLengthBitArrayType(_tKind kind, unsigned int align, unsigned int len,
                                     ByteOrder bo, const boost::optional<BitOrder>& bio,
                                     MapItem::Up attrs);

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
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length bit arrays described by
        this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length bit arrays described
        by this type.

        If set, each key of \p *attributes is a namespace.
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
                                     const boost::optional<BitOrder>& bitOrder = boost::none,
                                     MapItem::Up attributes = nullptr);

    /*!
    @brief
        Builds a fixed-length bit array type having a default alignment
        property (1).

    @param[in] length
        Length of data stream fixed-length bit arrays (bits) described
        by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length bit arrays described by
        this type.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length bit arrays described by
        this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length bit arrays described
        by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p length > 0.
    */
    explicit FixedLengthBitArrayType(unsigned int length, ByteOrder byteOrder,
                                     const boost::optional<BitOrder>& bitOrder = boost::none,
                                     MapItem::Up attributes = nullptr);

    /*!
    @brief
        Creates a constant fixed-length bit array type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the fixed-length bit array type
        constructor.

    @returns
        Created constant fixed-length bit array type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static Up create(ArgTs&&... args)
    {
        return std::make_unique<Up::element_type>(std::forward<ArgTs>(args)...);
    }

    /*!
    @brief
        Length of data stream fixed-length bit arrays (bits) described
        by this type.
    */
    unsigned int length() const noexcept
    {
        return _len;
    }

    /*!
    @brief
        Byte order of data stream fixed-length bit arrays described by
        this type.
    */
    ByteOrder byteOrder() const noexcept
    {
        return _bo;
    }

    /*!
    @brief
        Bit order of data stream fixed-length bit arrays described by
        this type.
    */
    BitOrder bitOrder() const noexcept
    {
        return _bio;
    }

    /*!
    @brief
        Less-than operator.

    @attention
        This operator doesn't consider attributes.

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
    DataType::Up _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const unsigned int _len;
    const ByteOrder _bo;
    const BitOrder _bio;
};

} // namespace yactfr

#endif // YACTFR_METADATA_FL_BIT_ARRAY_TYPE_HPP
