/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_CLK_TYPE_HPP
#define _YACTFR_METADATA_CLK_TYPE_HPP

#include <string>
#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>

#include "aliases.hpp"
#include "clk-offset.hpp"
#include "clk-value-interval.hpp"
#include "../item.hpp"

namespace yactfr {

/*!
@brief
    Clock type.

@ingroup metadata

A clock type describes data stream clocks.
*/
class ClockType final :
    boost::noncopyable
{
public:
    /*!
    @brief
        Builds a clock type.

    @param[in] name
        Name.
    @param[in] frequency
        Frequency (Hz) of data stream clocks described by this type.
    @param[in] description
        Description.
    @param[in] uuid
        UUID of data stream clocks described by this type.
    @param[in] precision
        Precision (cycles) of data stream clocks described by this type.
    @param[in] offset
        Offset from origin of data stream clocks described by this type.
    @param[in] originIsUnixEpoch
        \c true if this clock type describes clocks of which the origin
        is 1970-01-01T00:00:00Z.
    @param[in] userAttributes
        @parblock
        User attributes of data stream clocks described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p frequency is greater than 0.
    @pre
        <code>offset.cycles()</code> is less than \p frequency.
    */
    explicit ClockType(unsigned long long frequency,
                       boost::optional<std::string> name = boost::none,
                       boost::optional<std::string> description = boost::none,
                       boost::optional<boost::uuids::uuid> uuid = boost::none,
                       Cycles precision = 0, const ClockOffset& offset = ClockOffset {},
                       bool originIsUnixEpoch = true, MapItem::UP userAttributes = nullptr);

    /// Name.
    const boost::optional<std::string>& name() const noexcept
    {
        return _name;
    }

    /// Frequency (Hz) of data stream clocks described by this type.
    unsigned long long frequency() const noexcept
    {
        return _freq;
    }

    /// UUID of data stream clocks described by this type.
    const boost::optional<boost::uuids::uuid>& uuid() const noexcept
    {
        return _uuid;
    }

    /// Description.
    const boost::optional<std::string>& description() const noexcept
    {
        return _descr;
    }

    /// Precision (cycles) of data stream clocks described by this type.
    Cycles precision() const noexcept
    {
        return _prec;
    }

    /// Offset from origin of data stream clocks described by this type.
    const ClockOffset& offset() const noexcept
    {
        return _offset;
    }

    /*!
    @brief
        Returns the interval of possible data stream clock values for a
        given value \p cycles considering the precision (precision())
        of this clock type.

    @param[in] cycles
        Data stream clock value for which to get the interval of
        possible values considering the precision of this clock type.

    @returns
        Interval of possible values for \p cycles considering the
        precision of this clock type.
    */
    ClockValueInterval clockValueInterval(Cycles cycles) const noexcept;

    /// \c true if this clock type describes data stream clocks of which
    /// the origin is 1970-01-01T00:00:00Z.
    bool originIsUnixEpoch() const noexcept
    {
        return _originIsUnixEpoch;
    }

    /*!
    @brief
        User attributes.

    If set, each key of \p *userAttributes is a namespace.
    */
    const MapItem *userAttributes() const noexcept
    {
        return _userAttrs.get();
    }

private:
    const unsigned long long _freq;
    const boost::optional<std::string> _name;
    const boost::optional<std::string> _descr;
    const boost::optional<boost::uuids::uuid> _uuid;
    const Cycles _prec;
    const ClockOffset _offset;
    const bool _originIsUnixEpoch;
    const MapItem::UP _userAttrs;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_CLK_TYPE_HPP
