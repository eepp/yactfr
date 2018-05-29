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

#include <string>
#include <utility>
#include <boost/uuid/uuid.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include "metadata-base.hpp"
#include "aliases.hpp"

namespace yactfr {

/*!
@brief  Clock uncertainty.

@ingroup metadata
*/
class ClockUncertainty final
{
public:
    /*!
    Builds a clock uncertainty.

    @param lower    Lower bound of the uncertainty (cycles, included).
    @param upper    Upper bound of the uncertainty (cycles, included).
    */
    explicit ClockUncertainty(Cycles lower, Cycles upper) noexcept;

    /// Uncertainty's lower bound.
    Cycles lower() const noexcept
    {
        return _lower;
    }

    /// Uncertainty's upper bound.
    Cycles upper() const noexcept
    {
        return _upper;
    }

private:
    const Cycles _lower;
    const Cycles _upper;
};

/*!
@brief  Clock type.

@ingroup metadata

A clock type describes clocks which are instantiated per data stream.
*/
class ClockType final :
    public MetadataBase,
    boost::noncopyable
{
public:
    /*!
    @brief  Builds a clock type.

    @param name             Name.
    @param freq             Frequency (Hz).
    @param description      Description.
    @param uuid             UUID.
    @param errorCycles      Clock error (cycles).
    @param offsetSeconds    Offset (seconds).
    @param offsetCycles     Offset (cycles).
    @param isAbsolute       \c true if this clock type describes
                            clocks that are absolute references of time.

    @throws InvalidMetadata The clock type is invalid.
    */
    explicit ClockType(const std::string& name,
                       unsigned long long freq,
                       const boost::optional<std::string>& description,
                       const boost::optional<boost::uuids::uuid>& uuid,
                       Cycles errorCycles, long long offsetSeconds,
                       Cycles offsetCycles, bool isAbsolute);

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

    /// Clock error (cycles).
    Cycles errorCycles() const noexcept
    {
        return _errorCycles;
    }

    /// Offset (cycles).
    Cycles offsetCycles() const noexcept
    {
        return _offsetCycles;
    }

    /// Offset (seconds).
    long long offsetSeconds() const noexcept
    {
        return _offsetSeconds;
    }

    /*!
    @returns    Uncertainty bounds of a given timestamp
                \p cycles in cycles.
    */
    ClockUncertainty uncertainty(Cycles cycles) const noexcept;

    /// \c true if this clock type describes clocks that are considered
    /// absolute references of time.
    bool isAbsolute() const noexcept
    {
        return _isAbsolute;
    }

private:
    const std::string _name;
    const unsigned long long _freq;
    const boost::optional<std::string> _description;
    const boost::optional<boost::uuids::uuid> _uuid;
    const Cycles _errorCycles;
    const long long _offsetSeconds;
    const Cycles _offsetCycles;
    const bool _isAbsolute;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_CLOCK_TYPE_HPP
