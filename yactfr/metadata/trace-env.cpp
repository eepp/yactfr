/*
 * SPDX-FileCopyrightText: 2016-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <string>

#include <yactfr/metadata/trace-env.hpp>

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
