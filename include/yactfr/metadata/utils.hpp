/*
 * Copyright (C) 2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_UTILS_HPP
#define YACTFR_METADATA_UTILS_HPP

#include <string>

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
inline bool isStandardNamespace(const std::string& nameSpace) noexcept
{
    return nameSpace == "std" || nameSpace == "diamon.org,2012";
}

} // namespace yactfr

#endif // YACTFR_METADATA_UTILS_HPP
