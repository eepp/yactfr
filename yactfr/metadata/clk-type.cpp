/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <optional>

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

ClockOrigin::ClockOrigin() :
    _ns {_unixEpochNs},
    _name {_unixEpochName},
    _uid {_unixEpochUid}
{
}

ClockOrigin::ClockOrigin(std::optional<std::string> ns, std::string name, std::string uid) :
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

ClockType::ClockType(std::optional<std::string> id, std::optional<std::string> ns,
                     std::optional<std::string> name, std::optional<std::string> uid,
                     std::optional<boost::uuids::uuid> origUuid, unsigned long long freq,
                     std::optional<std::string> descr, std::optional<ClockOrigin> orig,
                     std::optional<Cycles> prec, std::optional<Cycles> accuracy,
                     const ClockOffset& offsetFromOrig, MapItem::Up attrs) :
    _id {std::move(id)},
    _ns {std::move(ns)},
    _name {std::move(name)},
    _uid {std::move(uid)},
    _origUuid {std::move(origUuid)},
    _freq {freq},
    _descr {std::move(descr)},
    _orig {std::move(orig)},
    _prec {std::move(prec)},
    _accuracy {std::move(accuracy)},
    _offsetFromOrig {offsetFromOrig},
    _attrs {std::move(attrs)}
{
    assert(freq > 0);
    assert(offsetFromOrig.cycles() < freq);
}

ClockValueInterval ClockType::clockValueInterval(const Cycles val) const noexcept
{
    assert(_prec);
    assert(_accuracy);
    return ClockValueInterval {val - *_prec - *_accuracy, val + *_prec + *_accuracy};
}

} // namespace yactfr
