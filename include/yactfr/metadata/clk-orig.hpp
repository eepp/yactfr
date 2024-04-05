/*
 * Copyright (C) 2015-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_CLK_ORIG_HPP
#define YACTFR_METADATA_CLK_ORIG_HPP

#include <string>
#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>

#include "aliases.hpp"

namespace yactfr {

/*!
@brief
    Clock origin.

@ingroup metadata

Object holding the origin property of a clock type.
*/
class ClockOrigin final
{
public:
    /*
    @brief
        Builds a
        <a href="https://en.wikipedia.org/wiki/Unix_time">Unix epoch</a>
        (1970-01-01T00:00:00Z) clock origin object.

    This clock origin has the namespace
    <code>github.com/eepp/yactfr</code>, the name `unix-epoch`, and an
    empty UID.
    */
    ClockOrigin();

    /*
    @brief
        Builds a custom clock origin object.

    @param[in] nameSpace
        Namespace of the clock origin.
    @param[in] name
        Name of the clock origin.
    @param[in] uid
        Unique ID of the clock origin.
    */
    explicit ClockOrigin(boost::optional<std::string> nameSpace, std::string name, std::string uid);

    /*
    @brief
        Builds a custom clock origin object without a namespace.

    @param[in] name
        Name of the clock origin.
    @param[in] uid
        Unique ID of the clock origin.
    */
    explicit ClockOrigin(std::string name, std::string uid);

    /// Default copy constructor.
    ClockOrigin(const ClockOrigin&) = default;

    /// Default copy assignment operator.
    ClockOrigin& operator=(const ClockOrigin&) = default;

    /// Default move constructor.
    ClockOrigin(ClockOrigin&&) = default;

    /// Default move assignment operator.
    ClockOrigin& operator=(ClockOrigin&&) = default;

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other clock origin to compare to.

    @returns
        \c true if \p other is equal to this clock origin.
    */
    bool operator==(const ClockOrigin& other) const noexcept
    {
        return other._ns == _ns && other._name == _name && other._uid == _uid;
    }

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Other clock origin to compare to.

    @returns
        \c true if \p other is not equal to this clock origin.
    */
    bool operator!=(const ClockOrigin& other) const noexcept
    {
        return !(*this == other);
    }

    /// Namespace.
    const boost::optional<std::string>& nameSpace() const noexcept
    {
        return _ns;
    }

    /// Name.
    const std::string& name() const noexcept
    {
        return _name;
    }

    /// UID.
    const std::string& uid() const noexcept
    {
        return _uid;
    }

    /// Whether or not this clock origin is the Unix epoch.
    bool isUnixEpoch() const noexcept
    {
        return _ns && *_ns == _unixEpochNs &&
               _name == _unixEpochName &&
               _uid == _unixEpochUid;
    }

private:
    static const char * const _unixEpochNs;
    static const char * const _unixEpochName;
    static const char * const _unixEpochUid;

private:
    boost::optional<std::string> _ns;
    std::string _name;
    std::string _uid;
};

} // namespace yactfr

#endif // YACTFR_METADATA_CLK_ORIG_HPP
