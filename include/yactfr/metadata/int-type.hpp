/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INT_TYPE_HPP
#define _YACTFR_METADATA_INT_TYPE_HPP

#include <string>
#include <boost/optional.hpp>

#include "bit-array-type.hpp"
#include "bo.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

class ClockType;

/*!
@brief
    \link IntegerType Integer type\endlink display base.

@ingroup metadata_dt
*/
enum class DisplayBase
{
    /// Binary.
    BINARY = 2,

    /// Octal.
    OCTAL = 8,

    /// Decimal.
    DECIMAL = 10,

    /// Hexadecimal.
    HEXADECIMAL = 16,
};

/*!
@brief
    Abstract integer type.

@ingroup metadata_dt

An integer type describes data stream integers.

Use the concrete SignedIntegerType and UnsignedIntegerType depending on
the signedness of the data stream integers to describe.
*/
class IntegerType :
    public BitArrayType
{
    friend class internal::TraceTypeImpl;

protected:
    explicit IntegerType(int kind, unsigned int align, unsigned int len, ByteOrder bo,
                         DisplayBase dispBase);

public:
    /// Preferred display base of data stream integers described by
    /// this type.
    DisplayBase preferredDisplayBase() const noexcept
    {
        return _prefDispBase;
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const IntegerType& other) const noexcept;

protected:
    bool _compare(const DataType& other) const noexcept override;

private:
    const DisplayBase _prefDispBase;
};

/*!
@brief
    Signed integer type.

@ingroup metadata_dt

A signed integer type describes data stream signed integers.
*/
class SignedIntegerType :
    public IntegerType
{
protected:
    explicit SignedIntegerType(int kind, unsigned int align, unsigned int len, ByteOrder bo,
                               DisplayBase dispBase);

public:
    /*!
    @brief
        Builds a signed integer type.

    @param[in] alignment
        Alignment of data stream signed integers described by this type.
    @param[in] length
        Length of data stream signed integers (bits) described by this
        type.
    @param[in] byteOrder
        Byte order of data stream signed integers described by this
        type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream signed integers
        described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit SignedIntegerType(unsigned int alignment, unsigned int length, ByteOrder byteOrder,
                               DisplayBase preferredDisplayBase = DisplayBase::DECIMAL);

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other signed integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const SignedIntegerType& other) const noexcept
    {
        return IntegerType::operator<(other);
    }

protected:
    bool _compare(const DataType& other) const noexcept override
    {
        return IntegerType::_compare(other);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Unsigned integer type.

@ingroup metadata_dt

An unsigned integer type describes data stream unsigned integers.
*/
class UnsignedIntegerType :
    public IntegerType
{
protected:
    explicit UnsignedIntegerType(int kind, unsigned int align, unsigned int len, ByteOrder bo,
                                 DisplayBase dispBase, const ClockType *mappedClkType);

public:
    /*!
    @brief
        Builds an unsigned integer type.

    @param[in] alignment
        Alignment of data stream unsigned integers described by this
        type.
    @param[in] length
        Length of data stream unsigned integers (bits) described by
        this type.
    @param[in] byteOrder
        Byte order of data stream unsigned integers described by this
        type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream unsigned integers
        described by this type.
    @param[in] mappedClockType
        Type of the clocks to which the data stream unsigned integers
        described by this type are mapped, or \c nullptr if none.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit UnsignedIntegerType(unsigned int alignment, unsigned int length, ByteOrder byteOrder,
                                 DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                 const ClockType *mappedClockType = nullptr);

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Unsigned integer type to copy.
    */
    UnsignedIntegerType(const UnsignedIntegerType& other);

    /// Type of the clocks to which data stream integers described by
    /// this type are mapped, or \c nullptr if none.
    const ClockType *mappedClockType() const noexcept
    {
        return _mappedClkType;
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other unsigned integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const UnsignedIntegerType& other) const noexcept;

protected:
    bool _compare(const DataType& other) const noexcept override;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const ClockType *_mappedClkType = nullptr;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_INT_TYPE_HPP
