/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <boost/optional.hpp>

#include <yactfr/metadata/clk-type.hpp>

namespace yactfr {

ClockValueInterval::ClockValueInterval(const Cycles lower, const Cycles upper) noexcept :
    _lower {lower},
    _upper {upper}
{
}

ClockOffset::ClockOffset(const long long secs, const Cycles cycles) noexcept :
    _secs {secs},
    _cycles {cycles}
{
}

ClockType::ClockType(const unsigned long long freq, boost::optional<std::string> name,
                     boost::optional<std::string> descr, boost::optional<boost::uuids::uuid> uuid,
                     const Cycles prec, const ClockOffset& offset, const bool originIsUnixEpoch,
                     MapItem::UP userAttrs) :
    _freq {freq},
    _name {std::move(name)},
    _descr {std::move(descr)},
    _uuid {std::move(uuid)},
    _prec {prec},
    _offset {offset},
    _originIsUnixEpoch {originIsUnixEpoch},
    _userAttrs {std::move(userAttrs)}
{
    assert(freq > 0);
    assert(offset.cycles() < freq);
}

ClockValueInterval ClockType::clockValueInterval(const Cycles cycles) const noexcept
{
    return ClockValueInterval {cycles - _prec, cycles + _prec};
}

} // namespace yactfr
