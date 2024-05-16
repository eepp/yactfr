/*
 * Copyright (C) 2015-2021 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_CLK_OFFSET_HPP
#define YACTFR_METADATA_CLK_OFFSET_HPP

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>

#include "aliases.hpp"

namespace yactfr {

/*!
@brief
    Clock offset.

@ingroup metadata

Object holding the offset property of a clock type.
*/
class ClockOffset final
{
public:
    /*!
    @brief
        Builds a default clock offset object (0).
    */
    explicit ClockOffset() noexcept = default;

    /*!
    @brief
        Builds a clock offset object.

    @param[in] seconds
        Seconds since origin (can be negative).
    @param[in] cycles
        Clock cycles since the origin plus \p seconds.
    */
    explicit ClockOffset(long long seconds, Cycles cycles) noexcept;

    /// Default copy constructor.
    ClockOffset(const ClockOffset&) = default;

    /// Default copy assignment operator.
    ClockOffset& operator=(const ClockOffset&) = default;

    /// Seconds since origin.
    long long seconds() const noexcept
    {
        return _secs;
    }

    /// Clock cycles since origin plus secs().
    Cycles cycles() const noexcept
    {
        return _cycles;
    }

private:
    long long _secs;
    Cycles _cycles;
};

} // namespace yactfr

#endif // YACTFR_METADATA_CLK_OFFSET_HPP
