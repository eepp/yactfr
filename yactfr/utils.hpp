/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_UTILS_HPP
#define _YACTFR_UTILS_HPP

#include <string>
#include <vector>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/dt.hpp>

namespace yactfr {
namespace internal {

std::string indent(Size indent);
std::string strError();

static inline bool isPowOfTwo(const unsigned long long x)
{
        return (x != 0) && ((x & (~x + 1)) == x);
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_UTILS_HPP
