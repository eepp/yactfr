/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_UTILS_HPP
#define YACTFR_INTERNAL_UTILS_HPP

#include <string>
#include <vector>
#include <boost/optional.hpp>

#include <yactfr/aliases.hpp>

namespace yactfr {
namespace internal {

std::string indent(Size indent);
std::string strError();

inline bool isPowOfTwo(const unsigned long long x)
{
        return (x != 0) && ((x & (~x + 1)) == x);
}

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_UTILS_HPP
