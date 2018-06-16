/*
 * Environment of a trace type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Classes related to trace type environments.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_TRACE_TYPE_ENV_HPP
#define _YACTFR_METADATA_TRACE_TYPE_ENV_HPP

// for std::unordered_map
#include <unordered_map>

// for std::string
#include <string>

// for boost::variant
#include <boost/variant.hpp>

namespace yactfr {

/*!
@brief  Trace type environment.

@ingroup metadata
*/
class TraceTypeEnv final
{
public:
    /// A trace type environment entry.
    using Entry = boost::variant<std::string, long long>;

    /// A collection of trace type environment entries.
    using Entries = std::unordered_map<std::string, Entry>;

public:
    /// Builds an empty trace type environment.
    TraceTypeEnv();

    /*!
    @brief  Builds a trace type environment.

    @param entries  Entries of the environment.
    */
    explicit TraceTypeEnv(const Entries& entries);

    /*!
    @brief  Trace type environment's entries.
    */
    const Entries& entries() const noexcept
    {
        return _entries;
    }

    /*!
    @brief  Returns whether or not this environment has an
            entry named \p key.

    @param key  Key of entry to check.
    @returns    \c true if this environment has an entry named \p key.
    */
    bool hasEntry(const std::string& key) const
    {
        return _entries.find(key) != _entries.end();
    }

    /*!
    @brief  Finds an entry by key name.

    @param key  Entry's name.
    @returns    Entry named \p key.

    @throws NoSuchName There's no entry named \p key.
    */
    const Entry& operator[](const std::string& key) const;

private:
    const Entries _entries;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_TRACE_TYPE_ENV_HPP
