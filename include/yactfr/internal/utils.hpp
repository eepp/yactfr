/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_UTILS_HPP
#define _YACTFR_INTERNAL_UTILS_HPP

namespace yactfr {
namespace internal {

static inline bool isPowOfTwo(const unsigned long long x)
{
        return (x != 0) && ((x & (~x + 1)) == x);
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_UTILS_HPP
