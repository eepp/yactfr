/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>

#include <yactfr/trace-env.hpp>

namespace yactfr {

TraceEnvironment::TraceEnvironment(Entries entries) :
    _entries {std::move(entries)}
{
}

const TraceEnvironment::Entry *TraceEnvironment::operator[](const std::string& key) const noexcept
{
    const auto it = _entries.find(key);

    if (it == _entries.end()) {
        return nullptr;
    }

    return &it->second;
}

} // namespace yactfr
