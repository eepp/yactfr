/*
 * Copyright (C) 2015-2021 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_CLK_VALUE_INTERVAL_HPP
#define YACTFR_METADATA_CLK_VALUE_INTERVAL_HPP

#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>

#include "aliases.hpp"

namespace yactfr {

/*!
@brief
    Clock value interval.

@ingroup metadata
*/
class ClockValueInterval final
{
public:
    /*!
    @brief
        Builds a clock value interval.

    @param[in] lower
        Lower bound of the interval (cycles, included).
    @param[in] upper
        Upper bound of the interval (cycles, included).
    */
    explicit ClockValueInterval(Cycles lower, Cycles upper) noexcept;

    /// Default copy constructor.
    ClockValueInterval(const ClockValueInterval&) = default;

    /// Default copy assignment operator.
    ClockValueInterval& operator=(const ClockValueInterval&) = default;

    /// Lower bound of the interval (included).
    Cycles lower() const noexcept
    {
        return _lower;
    }

    /// Upper bound of the interval (included).
    Cycles upper() const noexcept
    {
        return _upper;
    }

private:
    Cycles _lower;
    Cycles _upper;
};

} // namespace yactfr

#endif // YACTFR_METADATA_CLK_VALUE_INTERVAL_HPP
