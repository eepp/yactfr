/*
 * CTF integer types.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Integer types.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_INT_TYPE_HPP
#define _YACTFR_METADATA_INT_TYPE_HPP

// for std::string
#include <string>

// for boost::optional
#include <boost/optional.hpp>

// for BitArrayType
#include "bit-array-type.hpp"

// for DisplayBase
#include "int-type.hpp"

// for Encoding
#include "encoding.hpp"

// for ByteOrder
#include "byte-order.hpp"

// for DataType
#include "data-type.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

class ClockType;

/*!
@brief  Integer type display base.

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
@brief  Abstract integer type.

@ingroup metadata_dt

An integer type describes data stream integers. Use the concrete
SignedIntType and UnsignedIntType depending on the signedness of the
data stream integers to describe.
*/
class IntType :
    public BitArrayType
{
    friend class internal::TraceTypeImpl;

protected:
    explicit IntType(int kind, unsigned int alignment,
                     unsigned int size, ByteOrder byteOrder,
                     DisplayBase displayBase, Encoding encoding,
                     const boost::optional<std::string>& mappedClockTypeName);

public:
    /// Preferred display base of data stream integers described by this type.
    DisplayBase displayBase() const noexcept
    {
        return _displayBase;
    }

    /// Encoding of data stream integers described by this type.
    Encoding encoding() const noexcept
    {
        return _encoding;
    }

    /// Name of a clock type, in the same trace type, to which this
    /// integer type is mapped.
    const boost::optional<std::string>& mappedClockTypeName() const noexcept
    {
        return _mappedClockTypeName;
    }

    /*!
    @brief  Mapped clock type.

    This is only valid when this integer type is part of a trace type.

    @returns    Mapped clock type or \c nullptr if this integer
                type is not mapped to a clock type.
    */
    const ClockType *mappedClockType() const noexcept
    {
        return _mappedClkType;
    }

private:
    bool _compare(const DataType& otherType) const noexcept override;

    void _mappedClockType(const ClockType& clockType) const noexcept
    {
        _mappedClkType = &clockType;
    }

protected:
    bool operator<(const IntType& intType) const noexcept;

private:
    const DisplayBase _displayBase;
    const Encoding _encoding;
    const boost::optional<std::string> _mappedClockTypeName;
    mutable const ClockType *_mappedClkType = nullptr;
};

/*!
@brief  Signed integer type.

@ingroup metadata_dt

A signed integer type describes data stream signed integers.
*/
class SignedIntType :
    public IntType
{
protected:
    explicit SignedIntType(int kind, unsigned int alignment, unsigned int size,
                           ByteOrder byteOrder, DisplayBase displayBase,
                           Encoding encoding,
                           const boost::optional<std::string>& mappedClockTypeName);

public:
    /*!
    @brief  Builds a signed integer type.

    @param alignment            Alignment of data stream signed integers
                                described by this signed integer type
                                (power of two, greater than 0).
    @param size                 Size of data stream signed integers
                                described by this signed integer type.
    @param byteOrder            Byte order of data stream signed
                                integers described by this signed
                                integer type.
    @param displayBase          Preferred display base of data stream
                                signed integers described by this signed
                                integer type.
    @param encoding             Encoding of data stream signed integers
                                described by this signed integer type.
    @param mappedClockTypeName  Name of a clock type, in the same trace
                                type, to which this signed integer type
                                is mapped.

    @throws InvalidMetadata The signed integer type is invalid.
    */
    explicit SignedIntType(unsigned int alignment, unsigned int size,
                           ByteOrder byteOrder, DisplayBase displayBase,
                           Encoding encoding,
                           const boost::optional<std::string>& mappedClockTypeName);

    /*!
    @brief  Copy constructor.

    @param signedIntType    Signed integer type to copy.
    */
    SignedIntType(const SignedIntType& signedIntType);

    /*!
    @brief  Less-than operator.

    @param signedIntType    Other signed integer type to compare with.
    @returns                \c true if this signed integer type is
                            less than \p signedIntType (respects total order).
    */
    bool operator<(const SignedIntType& signedIntType) const noexcept
    {
        return IntType::operator<(signedIntType);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Unsigned integer type.

@ingroup metadata_dt

An unsigned integer type describes data stream unsigned integers.
*/
class UnsignedIntType :
    public IntType
{
protected:
    explicit UnsignedIntType(int kind, unsigned int alignment,
                             unsigned int size, ByteOrder byteOrder,
                             DisplayBase displayBase, Encoding encoding,
                             const boost::optional<std::string>& mappedClockTypeName);

public:
    /*!
    @brief  Builds an unsigned integer type.

    @param alignment            Alignment of data stream unsigned
                                integers described by this unsigned
                                integer type (power of two, greater than
                                0).
    @param size                 Size of data stream unsigned integers
                                described by this unsigned integer type.
    @param byteOrder            Byte order of data stream unsigned
                                integers described by this unsigned
                                integer type.
    @param displayBase          Preferred display base of data stream
                                unsigned integers described by this
                                unsigned integer type.
    @param encoding             Encoding of data stream unsigned
                                integers described by this unsigned
                                integer type.
    @param mappedClockTypeName  Name of a clock type, in the same trace
                                type, to which this unsigned integer
                                type is mapped.

    @throws InvalidMetadata The unsigned integer type is invalid.
    */
    explicit UnsignedIntType(unsigned int alignment, unsigned int size,
                             ByteOrder byteOrder, DisplayBase displayBase,
                             Encoding encoding,
                             const boost::optional<std::string>& mappedClockTypeName);

    /*!
    @brief  Copy constructor.

    @param unsignedIntType  Unsigned integer type to copy.
    */
    UnsignedIntType(const UnsignedIntType& unsignedIntType);

    /*!
    @brief  Less-than operator.

    @param unsignedIntType  Other unsigned integer type to compare with.
    @returns                \c true if this unsigned integer type
                            is less than \p unsignedIntType (respects
                            total order).
    */
    bool operator<(const UnsignedIntType& unsignedIntType) const noexcept
    {
        return IntType::operator<(unsignedIntType);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_INT_TYPE_HPP
