/*
 * Environment of a trace type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/aliases.hpp>
#include <yactfr/metadata/exceptions.hpp>
#include <yactfr/metadata/trace-type-env.hpp>

namespace yactfr {

TraceTypeEnv::TraceTypeEnv()
{
}

TraceTypeEnv::TraceTypeEnv(const Entries& entries) :
    _entries {entries}
{
}

const TraceTypeEnv::Entry& TraceTypeEnv::operator[](const std::string& key) const
{
    auto it = _entries.find(key);

    if (it == _entries.end()) {
        throw NoSuchName {key};
    }

    return it->second;
}

} // namespace yactfr
