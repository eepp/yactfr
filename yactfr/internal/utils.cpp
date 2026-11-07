/*
 * SPDX-FileCopyrightText: 2017-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <system_error>
#include <errno.h>

#include "utils.hpp"

namespace yactfr::internal {

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
    return std::generic_category().message(errno);
}

} // namespace yactfr::internal
