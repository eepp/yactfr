/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/text-loc.hpp>

namespace yactfr {

TextLocation::TextLocation(const Index offset, const Index lineNumber, const Index colNumber) noexcept :
    _offset {offset},
    _lineNumber {lineNumber},
    _colNumber {colNumber}
{
}

} // namespace yactfr
