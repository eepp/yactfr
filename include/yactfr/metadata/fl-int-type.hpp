/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FL_INT_TYPE_HPP
#define _YACTFR_METADATA_FL_INT_TYPE_HPP

#include <string>
#include <set>
#include <boost/optional.hpp>

#include "fl-bit-array-type.hpp"
#include "bo.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

/*!
@brief
    Integer display base.

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
    Abstract fixed-length integer type.

@ingroup metadata_dt

A fixed-length integer type describes data stream fixed-length integers.

Use the concrete FixedLengthSignedIntegerType and
FixedLengthUnsignedIntegerType depending on the signedness of the data
stream fixed-length integers to describe.
*/
class FixedLengthIntegerType :
    public FixedLengthBitArrayType
{
    friend class internal::TraceTypeImpl;

protected:
    explicit FixedLengthIntegerType(int kind, unsigned int align, unsigned int len, ByteOrder bo,
                                    DisplayBase prefDispBase);

public:
    /// Preferred display base of data stream fixed-length integers
    /// described by this type.
    DisplayBase preferredDisplayBase() const noexcept
    {
        return _prefDispBase;
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other fixed-length integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const FixedLengthIntegerType& other) const noexcept;

protected:
    bool _compare(const DataType& other) const noexcept override;

private:
    const DisplayBase _prefDispBase;
};

/*!
@brief
    Signed fixed-length integer type.

@ingroup metadata_dt

A signed fixed-length integer type describes data stream signed
integers.
*/
class FixedLengthSignedIntegerType :
    public FixedLengthIntegerType
{
protected:
    explicit FixedLengthSignedIntegerType(int kind, unsigned int align, unsigned int len,
                                          ByteOrder bo, DisplayBase prefDispBase);

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
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        integers described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit FixedLengthSignedIntegerType(unsigned int alignment, unsigned int length,
                                          ByteOrder byteOrder,
                                          DisplayBase preferredDisplayBase = DisplayBase::DECIMAL);

    /*!
    @brief
        Less-than operator.

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

protected:
    bool _compare(const DataType& other) const noexcept override
    {
        return FixedLengthIntegerType::_compare(other);
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
    Unsigned integer type role.

@ingroup metadata_dt
*/
enum class UnsignedIntegerTypeRole
{
    /// Packet magic number.
    PACKET_MAGIC_NUMBER,

    /// \link DataStreamType Data stream type\endlink ID.
    DATA_STREAM_TYPE_ID,

    /// Data stream ID.
    DATA_STREAM_ID,

    /// Packet total length.
    PACKET_TOTAL_LENGTH,

    /// Packet content length.
    PACKET_CONTENT_LENGTH,

    /// Default clock timestamp.
    DEFAULT_CLOCK_TIMESTAMP,

    /// Packet end default clock timestamp.
    PACKET_END_DEFAULT_CLOCK_TIMESTAMP,

    /// Discarded event record counter snapshot.
    DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT,

    /// Packet origin index.
    PACKET_ORIGIN_INDEX,

    /// \link EventRecordType Event record type\endlink ID.
    EVENT_RECORD_TYPE_ID,
};

/*!
@brief
    Fixed-length unsigned integer type role set.

@ingroup metadata_dt
*/
using UnsignedIntegerTypeRoleSet = std::set<UnsignedIntegerTypeRole>;

/*!
@brief
    Fixed-length unsigned integer type.

@ingroup metadata_dt

An fixed-length unsigned integer type describes data stream fixed-length
unsigned integers.
*/
class FixedLengthUnsignedIntegerType :
    public FixedLengthIntegerType
{
protected:
    explicit FixedLengthUnsignedIntegerType(int kind, unsigned int align, unsigned int len,
                                            ByteOrder bo, DisplayBase prefDispBase,
                                            UnsignedIntegerTypeRoleSet roles);

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
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        integers described by this type.
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
                                            DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                            UnsignedIntegerTypeRoleSet roles = {});

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

    /// Roles of fixed-length unsigned integers described by this type.
    const UnsignedIntegerTypeRoleSet& roles() const noexcept
    {
        return _roles;
    }

    /*!
    @brief
        Returns whether or not the fixed-length integers described by
        this type have the role \p role.

    @param[in] role
        Role to check.

    @returns
        \c true if the fixed-length integers described by this type have
        the role \p role.
    */
    bool hasRole(const UnsignedIntegerTypeRole role) const noexcept
    {
        return _roles.find(role) != _roles.end();
    }

protected:
    bool _compare(const DataType& other) const noexcept override;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const UnsignedIntegerTypeRoleSet _roles;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FL_INT_TYPE_HPP
