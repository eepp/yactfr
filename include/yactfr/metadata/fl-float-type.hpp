/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FL_FLOAT_TYPE_HPP
#define _YACTFR_METADATA_FL_FLOAT_TYPE_HPP

#include <memory>
#include <utility>

#include "fl-bit-array-type.hpp"
#include "bo.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

class DataTypeVisitor;

/*!
@brief
    Fixed-length floating point number type.

@ingroup metadata_dt

A fixed-length floating point number type describes data stream
fixed-length single-precision and double-precision floating point
numbers.
*/
class FixedLengthFloatingPointNumberType final :
    public FixedLengthBitArrayType
{
public:
    /// Unique pointer to constant fixed-length floating point number type.
    using UP = std::unique_ptr<const FixedLengthFloatingPointNumberType>;

public:
    /*!
    @brief
        Builds a fixed-length floating point number type.

    @param[in] alignment
        Alignment of data stream fixed-length floating point numbers
        described by this floating point number type.
    @param[in] length
        Length of data stream fixed-length floating point numbers (bits)
        described by this floating point number type.
    @param[in] byteOrder
        Byte order of data stream fixed-length floating point numbers
        described by this floating point number type.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length floating point numbers
        described by this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::BIG
          <dd>BitOrder::LAST_TO_FIRST

          <dt>ByteOrder::LITTLE
          <dd>BitOrder::FIRST_TO_LAST
        </dl>
        @endparblock
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length floating point
        numbers described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length is 32 or 64.
    */
    explicit FixedLengthFloatingPointNumberType(unsigned int alignment, unsigned int length,
                                                ByteOrder byteOrder,
                                                const boost::optional<BitOrder>& bitOrder = boost::none,
                                                MapItem::UP attributes = nullptr);

    /*!
    @brief
        Builds a fixed-length floating point number type having a
        default alignment property (1).

    @param[in] length
        Length of data stream fixed-length floating point numbers (bits)
        described by this floating point number type.
    @param[in] byteOrder
        Byte order of data stream fixed-length floating point numbers
        described by this floating point number type.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length floating point numbers
        described by this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::BIG
          <dd>BitOrder::LAST_TO_FIRST

          <dt>ByteOrder::LITTLE
          <dd>BitOrder::FIRST_TO_LAST
        </dl>
        @endparblock
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length floating point
        numbers described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p length is 32 or 64.
    */
    explicit FixedLengthFloatingPointNumberType(unsigned int length, ByteOrder byteOrder,
                                                const boost::optional<BitOrder>& bitOrder = boost::none,
                                                MapItem::UP attributes = nullptr);

    /*!
    @brief
        Creates a constant fixed-length floating point number type
        unique pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the fixed-length floating point number
        type constructor.

    @returns
        Created constant fixed-length floating point number type unique
        pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Fixed-length floating point number type to copy.
    */
    FixedLengthFloatingPointNumberType(const FixedLengthFloatingPointNumberType& other);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FL_FLOAT_TYPE_HPP
