/*
 * CTF clock type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <boost/optional.hpp>

#include <yactfr/metadata/clock-type.hpp>
#include <yactfr/metadata/invalid-metadata.hpp>

namespace yactfr {

ClockValueInterval::ClockValueInterval(const Cycles lower, const Cycles upper) noexcept :
    _lower {lower},
    _upper {upper}
{
}

ClockTypeOffset::ClockTypeOffset(const long long seconds, const Cycles cycles) noexcept :
    _seconds {seconds},
    _cycles {cycles}
{
}

ClockType::ClockType(const std::string& name,
                     const unsigned long long freq,
                     const boost::optional<std::string>& description,
                     const boost::optional<boost::uuids::uuid>& uuid,
                     const Cycles error, const ClockTypeOffset& offset,
                     const bool isAbsolute) :
    _name {name},
    _freq {freq},
    _description {description},
    _uuid {uuid},
    _error {error},
    _offset {offset},
    _isAbsolute {isAbsolute}
{
    if (name.empty()) {
        throw InvalidMetadata {
            "Clock type's name is empty."
        };
    }

    if (freq == 0) {
        throw InvalidMetadata {
            "Clock type's frequency is 0 Hz."
        };
    }
}

ClockValueInterval ClockType::clockValueInterval(const Cycles cycles) const noexcept
{
    return ClockValueInterval {cycles - _error, cycles + _error};
}

} // namespace yactfr
