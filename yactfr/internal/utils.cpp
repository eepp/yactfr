/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <vector>
#include <string.h>
#include <errno.h>

#include "utils.hpp"

namespace yactfr {
namespace internal {

std::string indent(const Size indent)
{
    std::string ind;

    ind.reserve(indent * 2);

    for (Index i = 0; i < indent; ++i) {
        ind.append("  ");
    }

    return ind;
}

std::string strError()
{
        std::vector<char> buf;

        buf.reserve(1024);
        strerror_r(errno, buf.data(), buf.capacity());
        return buf.data();
}

} // namespace internal
} // namespace yactfr
