/*
 * SPDX-FileCopyrightText: 2024 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#ifndef YACTFR_METADATA_UTILS_HPP
#define YACTFR_METADATA_UTILS_HPP

#include <string_view>

namespace yactfr {

/*!
@brief
    Returns whether or not the CTF&nbsp;2 namespace \p nameSpace is a
    <a href="https://diamon.org/ctf/#ns-def">standard namespace</a>.

@ingroup metadata

@param[in] nameSpace
    Namespace to check.

@returns
    \c true if \p nameSpace is a standard CTF&nbsp;2 namespace.
*/
inline bool isStandardNamespace(const std::string_view nameSpace) noexcept
{
    return nameSpace == "std" || nameSpace == "diamon.org,2012";
}

} // namespace yactfr

#endif // YACTFR_METADATA_UTILS_HPP
