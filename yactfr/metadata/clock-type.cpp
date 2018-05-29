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
#include <yactfr/metadata/exceptions.hpp>

namespace yactfr {

ClockUncertainty::ClockUncertainty(const Cycles lower, const Cycles upper) noexcept :
    _lower {lower},
    _upper {upper}
{
}

ClockType::ClockType(const std::string& name,
                     const unsigned long long freq,
                     const boost::optional<std::string>& description,
                     const boost::optional<boost::uuids::uuid>& uuid,
                     const Cycles errorCycles,
                     const long long offsetSeconds,
                     const Cycles offsetCycles,
                     const bool isAbsolute) :
    _name {name},
    _freq {freq},
    _description {description},
    _uuid {uuid},
    _errorCycles {errorCycles},
    _offsetSeconds {offsetSeconds},
    _offsetCycles {offsetCycles},
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

ClockUncertainty ClockType::uncertainty(const Cycles cycles) const noexcept
{
    return ClockUncertainty {cycles - _errorCycles, cycles + _errorCycles};
}

} // namespace yactfr
