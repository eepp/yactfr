/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TRACE_ENV_HPP
#define _YACTFR_TRACE_ENV_HPP

#include <unordered_map>
#include <string>
#include <boost/variant.hpp>

namespace yactfr {

/*!
@brief
    Trace environment.

@ingroup trace
*/
class TraceEnvironment final
{
public:
    /// A trace environment entry.
    using Entry = boost::variant<std::string, long long>;

    /// A collection of trace environment entries.
    using Entries = std::unordered_map<std::string, Entry>;

public:
    /// Builds an empty trace type environment.
    explicit TraceEnvironment() = default;

    /*!
    @brief
        Builds a trace environment.

    @param[in] entries
        Entries of the environment.
    */
    explicit TraceEnvironment(const Entries& entries);

    /// Default copy constructor.
    TraceEnvironment(const TraceEnvironment& other) = default;

    /// Default move constructor.
    TraceEnvironment(TraceEnvironment&& other) = default;

    /// Default copy assignment operator.
    TraceEnvironment& operator=(const TraceEnvironment& other) = default;

    /// Default move assignment operator.
    TraceEnvironment& operator=(TraceEnvironment&& other) = default;

    /// Entries.
    const Entries& entries() const noexcept
    {
        return _entries;
    }

    /*!
    @brief
        Returns the entry having the key \p key, or \c nullptr if not
        found.

    @param[in] key
        Key of the entry to find.

    @returns
        Entry having the key \p key, or \c nullptr if not found.
    */
    const Entry *operator[](const std::string& key) const noexcept;

private:
    Entries _entries;
};

} // namespace yactfr

#endif // _YACTFR_TRACE_ENV_HPP
