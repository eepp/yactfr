/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <boost/optional.hpp>

#include <yactfr/metadata/clk-type.hpp>
#include <yactfr/metadata/clk-orig.hpp>

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

const char *ClockOrigin::_UNIX_EPOCH_NS = "github.com/eepp/yactfr";
const char *ClockOrigin::_UNIX_EPOCH_NAME = "unix-epoch";
const char *ClockOrigin::_UNIX_EPOCH_UID = "";

ClockOrigin::ClockOrigin() :
    _ns {_UNIX_EPOCH_NS},
    _name {_UNIX_EPOCH_NAME},
    _uid {_UNIX_EPOCH_UID}
{
}

ClockOrigin::ClockOrigin(boost::optional<std::string> ns, std::string name, std::string uid) :
    _ns {std::move(ns)},
    _name {std::move(name)},
    _uid {std::move(uid)}
{
}

ClockOrigin::ClockOrigin(std::string name, std::string uid) :
    _name {std::move(name)},
    _uid {std::move(uid)}
{
}

ClockType::ClockType(const unsigned long long freq, boost::optional<std::string> name,
                     boost::optional<std::string> descr, boost::optional<ClockOrigin> orig,
                     const Cycles prec, const ClockOffset& offsetFromOrig, MapItem::UP userAttrs) :
    _freq {freq},
    _name {std::move(name)},
    _descr {std::move(descr)},
    _orig {std::move(orig)},
    _prec {prec},
    _offsetFromOrig {offsetFromOrig},
    _userAttrs {std::move(userAttrs)}
{
    assert(freq > 0);
    assert(offsetFromOrig.cycles() < freq);
}

ClockValueInterval ClockType::clockValueInterval(const Cycles cycles) const noexcept
{
    return ClockValueInterval {cycles - _prec, cycles + _prec};
}

} // namespace yactfr
