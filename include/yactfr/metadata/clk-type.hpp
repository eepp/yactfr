/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_CLK_TYPE_HPP
#define _YACTFR_METADATA_CLK_TYPE_HPP

#include <string>
#include <memory>
#include <utility>
#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>

#include "aliases.hpp"
#include "clk-offset.hpp"
#include "clk-orig.hpp"
#include "clk-value-interval.hpp"
#include "item.hpp"

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
    /// Unique pointer to constant clock type.
    using UP = std::unique_ptr<const ClockType>;

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
    @param[in] origin
        Origin of data stream clocks described by this type, or
        \c boost::none if the origin is unknown.
    @param[in] precision
        Precision (cycles) of data stream clocks described by this type.
    @param[in] offsetFromOrigin
        Offset from origin of data stream clocks described by this type.
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
                       boost::optional<ClockOrigin> origin = boost::none, Cycles precision = 0,
                       const ClockOffset& offsetFromOrigin = ClockOffset {},
                       MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a constant clock type unique pointer, forwarding \p args
        to the constructor.

    @param[in] args
        Arguments to forward to the clock type constructor.

    @returns
        Created constant clock type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

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

    /// Origin of data stream clocks described by this type, or
    /// \c boost::none if the origin is unknown.
    const boost::optional<ClockOrigin>& origin() const noexcept
    {
        return _orig;
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
    const ClockOffset& offsetFromOrigin() const noexcept
    {
        return _offsetFromOrig;
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

    /*!
    @brief
        User attributes.

    If set, each key of \p *userAttributes is a namespace.

    @note
        Even if the return value isn't \c nullptr, the returned map
        item may still be empty (which also means no user attributes).
    */
    const MapItem *userAttributes() const noexcept
    {
        return _userAttrs.get();
    }

private:
    const unsigned long long _freq;
    const boost::optional<std::string> _name;
    const boost::optional<std::string> _descr;
    const boost::optional<ClockOrigin> _orig;
    const Cycles _prec;
    const ClockOffset _offsetFromOrig;
    const MapItem::UP _userAttrs;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_CLK_TYPE_HPP
