/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INT_TYPE_COMMON_HPP
#define _YACTFR_METADATA_INT_TYPE_COMMON_HPP

#include <set>

#include "bo.hpp"
#include "vl-bit-array-type.hpp"
#include "dt.hpp"

namespace yactfr {

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
    Common interface of FixedLengthIntegerType and
    VariableLengthIntegerType.

@ingroup metadata_dt
*/
class IntegerTypeCommon
{
protected:
    explicit IntegerTypeCommon(DisplayBase prefDispBase);

public:
    /// Preferred display base of an integer described by this type.
    DisplayBase preferredDisplayBase() const noexcept
    {
        return _prefDispBase;
    }

protected:
    bool _isEqual(const IntegerTypeCommon& other) const noexcept;

private:
    const DisplayBase _prefDispBase;
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

    /// Packet sequence number.
    PACKET_SEQUENCE_NUMBER,

    /// \link EventRecordType Event record type\endlink ID.
    EVENT_RECORD_TYPE_ID,
};

/*!
@brief
    Unsigned integer type role set.

@ingroup metadata_dt
*/
using UnsignedIntegerTypeRoleSet = std::set<UnsignedIntegerTypeRole>;

/*!
@brief
    Common interface of FixedLengthUnsignedIntegerType and
    VariableLengthUnsignedIntegerType.

@ingroup metadata_dt
*/
class UnsignedIntegerTypeCommon
{
protected:
    explicit UnsignedIntegerTypeCommon(UnsignedIntegerTypeRoleSet roles);

public:
    /// Roles of unsigned integers described by this type.
    const UnsignedIntegerTypeRoleSet& roles() const noexcept
    {
        return _roles;
    }

    /*!
    @brief
        Returns whether or not the unsigned integers described by this
        type have the role \p role.

    @param[in] role
        Role to check.

    @returns
        \c true if the unsigned integers described by this type have the
        role \p role.
    */
    bool hasRole(const UnsignedIntegerTypeRole role) const noexcept
    {
        return _roles.find(role) != _roles.end();
    }

protected:
    bool _isEqual(const UnsignedIntegerTypeCommon& other) const noexcept;

private:
    const UnsignedIntegerTypeRoleSet _roles;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_INT_TYPE_COMMON_HPP
