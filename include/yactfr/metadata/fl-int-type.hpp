/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_FL_INT_TYPE_HPP
#define YACTFR_METADATA_FL_INT_TYPE_HPP

#include <boost/optional.hpp>

#include <memory>
#include <utility>

#include "fl-bit-array-type.hpp"
#include "int-type-common.hpp"
#include "bo.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

/*!
@brief
    Abstract fixed-length integer type having mapping values of type
    `MappingValueT`.

@ingroup metadata_dt

A fixed-length integer type describes data stream fixed-length integers.

Use the concrete FixedLengthSignedIntegerType and
FixedLengthUnsignedIntegerType depending on the signedness of the data
stream fixed-length integers to describe.
*/
template <typename MappingValueT>
class FixedLengthIntegerType :
    public FixedLengthBitArrayType,
    public IntegerTypeCommon<MappingValueT>
{
    friend class internal::TraceTypeImpl;

public:
    using typename IntegerTypeCommon<MappingValueT>::Mappings;
    using typename IntegerTypeCommon<MappingValueT>::MappingRangeSet;
    using typename IntegerTypeCommon<MappingValueT>::MappingValue;

protected:
    explicit FixedLengthIntegerType(_tKind kind, unsigned int align, unsigned int len, ByteOrder bo,
                                    const boost::optional<BitOrder>& bio, DisplayBase prefDispBase,
                                    Mappings&& mappings, MapItem::Up attrs) :
        FixedLengthBitArrayType {kind, align, len, bo, bio, std::move(attrs)},
        IntegerTypeCommon<MappingValueT> {prefDispBase, std::move(mappings)}
    {
    }

public:
    /*!
    @brief
        Less-than operator.

    @attention
        This operator doesn't consider attributes.

    @param[in] other
        Other fixed-length integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const FixedLengthIntegerType& other) const noexcept
    {
        if (this->mappings() < other.mappings()) {
            return true;
        }

        if (other.mappings() < this->mappings()) {
            return false;
        }

        if (this->preferredDisplayBase() < other.preferredDisplayBase()) {
            return true;
        }

        if (other.preferredDisplayBase() < this->preferredDisplayBase()) {
            return false;
        }

        return FixedLengthBitArrayType::operator<(other);
    }

protected:
    bool _isEqual(const DataType& other) const noexcept override
    {
        return FixedLengthBitArrayType::_isEqual(other) &&
               IntegerTypeCommon<MappingValueT>::_isEqual(static_cast<const FixedLengthIntegerType&>(other));
    }
};

/*!
@brief
    Signed fixed-length integer type.

@ingroup metadata_dt

A signed fixed-length integer type describes data stream signed
integers.
*/
class FixedLengthSignedIntegerType final :
    public FixedLengthIntegerType<internal::SignedIntegerTypeMappingValue>
{
public:
    /// Unique pointer to constant fixed-length signed integer type.
    using Up = std::unique_ptr<const FixedLengthSignedIntegerType>;

public:
    /*!
    @brief
        Builds a fixed-length signed integer type.

    @param[in] alignment
        Alignment of data stream fixed-length signed integers described
        by this type.
    @param[in] length
        Length of data stream fixed-length signed integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length signed integers described
        by this type.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length signed integers described
        by this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        integers described by this type.
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length signed integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit FixedLengthSignedIntegerType(unsigned int alignment, unsigned int length,
                                          ByteOrder byteOrder,
                                          const boost::optional<BitOrder>& bitOrder = boost::none,
                                          DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                          Mappings mappings = Mappings {},
                                          MapItem::Up attributes = nullptr);

    /*!
    @brief
        Builds a fixed-length signed integer type having a default
        alignment property (1).

    @param[in] length
        Length of data stream fixed-length signed integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length signed integers described
        by this type.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length signed integers described
        by this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        integers described by this type.
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length signed integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p length > 0.
    */
    explicit FixedLengthSignedIntegerType(unsigned int length, ByteOrder byteOrder,
                                          const boost::optional<BitOrder>& bitOrder = boost::none,
                                          DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                          Mappings mappings = Mappings {},
                                          MapItem::Up attributes = nullptr);

    /*!
    @brief
        Creates a constant fixed-length signed integer type unique
        pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the fixed-length signed integer type
        constructor.

    @returns
        Created constant fixed-length signed integer type unique
        pointer.

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
        Less-than operator.

    @attention
        This operator doesn't consider attributes.

    @param[in] other
        Other fixed-length signed integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const FixedLengthSignedIntegerType& other) const noexcept
    {
        return FixedLengthIntegerType::operator<(other);
    }

private:
    DataType::Up _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length unsigned integer type.

@ingroup metadata_dt

An fixed-length unsigned integer type describes data stream fixed-length
unsigned integers.
*/
class FixedLengthUnsignedIntegerType final :
    public FixedLengthIntegerType<internal::UnsignedIntegerTypeMappingValue>,
    public UnsignedIntegerTypeCommon
{
public:
    /// Unique pointer to constant fixed-length unsigned integer type.
    using Up = std::unique_ptr<const FixedLengthUnsignedIntegerType>;

public:
    /*!
    @brief
        Builds a fixed-length unsigned integer type.

    @param[in] alignment
        Alignment of data stream fixed-length unsigned integers
        described by this type.
    @param[in] length
        Length of data stream fixed-length unsigned integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length unsigned integers
        described by this type.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length unsigned integers
        described by this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        integers described by this type.
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length unsigned integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of fixed-length unsigned integers described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit FixedLengthUnsignedIntegerType(unsigned int alignment, unsigned int length,
                                            ByteOrder byteOrder,
                                            const boost::optional<BitOrder>& bitOrder = boost::none,
                                            DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                            Mappings mappings = Mappings {},
                                            MapItem::Up attributes = nullptr,
                                            UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a fixed-length unsigned integer type having a default
        alignment property (1).

    @param[in] length
        Length of data stream fixed-length unsigned integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length unsigned integers
        described by this type.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length unsigned integers
        described by this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        integers described by this type.
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length unsigned integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of fixed-length unsigned integers described by this type.

    @pre
        \p length > 0.
    */
    explicit FixedLengthUnsignedIntegerType(unsigned int length, ByteOrder byteOrder,
                                            const boost::optional<BitOrder>& bitOrder = boost::none,
                                            DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                            Mappings mappings = Mappings {},
                                            MapItem::Up attributes = nullptr,
                                            UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Creates a constant fixed-length unsigned integer type unique
        pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the fixed-length unsigned integer type
        constructor.

    @returns
        Created constant fixed-length unsigned integer type unique
        pointer.

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
        Copy constructor.

    @param[in] other
        Fixed-length unsigned integer type to copy.
    */
    FixedLengthUnsignedIntegerType(const FixedLengthUnsignedIntegerType& other);

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other fixed-length unsigned integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const FixedLengthUnsignedIntegerType& other) const noexcept;

private:
    bool _isEqual(const DataType& other) const noexcept override;
    DataType::Up _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // YACTFR_METADATA_FL_INT_TYPE_HPP
