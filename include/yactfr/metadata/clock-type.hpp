/*
 * CTF clock type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Classes related to clock types.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_CLOCK_TYPE_HPP
#define _YACTFR_METADATA_CLOCK_TYPE_HPP

// for std::string
#include <string>

// for boost::noncopyable
#include <boost/core/noncopyable.hpp>

// for boost::optional
#include <boost/optional.hpp>

// for boost::uuids::uuid
#include <boost/uuid/uuid.hpp>

// for Cycles
#include "aliases.hpp"

namespace yactfr {

/*!
@brief  Clock value interval.

@ingroup metadata
*/
class ClockValueInterval final
{
public:
    /*!
    Builds a clock value interval.

    @param lower    Lower bound of the interval (cycles, included).
    @param upper    Upper bound of the interval (cycles, included).
    */
    explicit ClockValueInterval(Cycles lower, Cycles upper) noexcept;

    /// Interval's lower bound (included).
    Cycles lower() const noexcept
    {
        return _lower;
    }

    /// Interval's upper bound (included).
    Cycles upper() const noexcept
    {
        return _upper;
    }

private:
    Cycles _lower;
    Cycles _upper;
};

/*!
@brief  Clock type offset.

@ingroup metadata

Object holding the offset property of a clock type.
*/
class ClockTypeOffset final
{
public:
    /*!
    @brief  Builds a clock type offset object.

    @param seconds  Seconds since origin (can be negative).
    @param cycles   Clock cycles since the origin plus \p seconds.
    */
    explicit ClockTypeOffset(long long seconds, Cycles cycles) noexcept;

    /// Seconds since origin.
    long long seconds() const noexcept
    {
        return _seconds;
    }

    /// Clock cycles since origin plus seconds().
    Cycles cycles() const noexcept
    {
        return _cycles;
    }

private:
    long long _seconds;
    Cycles _cycles;
};

/*!
@brief  Clock type.

@ingroup metadata

A clock type describes clocks which are instantiated per data stream.
*/
class ClockType final :
    boost::noncopyable
{
public:
    /*!
    @brief  Builds a clock type.

    @param name             Name.
    @param freq             Frequency (Hz).
    @param description      Description.
    @param uuid             UUID.
    @param error            Error (cycles).
    @param offset           Offset from origin.
    @param isAbsolute       \c true if this clock type describes
                            clocks of which the origin is
                            1970-01-01T00:00:00Z.

    \p offset.cycles() must be less than \p frequency.

    @throws InvalidMetadata The clock type is invalid.
    */
    explicit ClockType(const std::string& name,
                       unsigned long long freq,
                       const boost::optional<std::string>& description,
                       const boost::optional<boost::uuids::uuid>& uuid,
                       Cycles error, const ClockTypeOffset& offset,
                       bool isAbsolute);

    /// Name.
    const std::string& name() const noexcept
    {
        return _name;
    }

    /// Frequency (Hz).
    unsigned long long freq() const noexcept
    {
        return _freq;
    }

    /// UUID.
    const boost::optional<boost::uuids::uuid>& uuid() const noexcept
    {
        return _uuid;
    }

    /// Description.
    const boost::optional<std::string>& description() const noexcept
    {
        return _description;
    }

    /// Error (cycles).
    Cycles error() const noexcept
    {
        return _error;
    }

    /// Offset from origin.
    const ClockTypeOffset& offset() const noexcept
    {
        return _offset;
    }

    /*!
    @returns    Possible interval of clock values for a given
                value \p cycles considering this clock type's error.
    */
    ClockValueInterval clockValueInterval(Cycles cycles) const noexcept;

    /// \c true if this clock type describes clocks of which the origin
    /// is 1970-01-01T00:00:00Z.
    bool isAbsolute() const noexcept
    {
        return _isAbsolute;
    }

private:
    const std::string _name;
    const unsigned long long _freq;
    const boost::optional<std::string> _description;
    const boost::optional<boost::uuids::uuid> _uuid;
    const Cycles _error;
    const ClockTypeOffset _offset;
    const bool _isAbsolute;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_CLOCK_TYPE_HPP
