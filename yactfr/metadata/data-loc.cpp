/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/data-loc.hpp>

namespace yactfr {

DataLocation::DataLocation(const Scope scope, std::vector<std::string> pathElems) :
    _scope {scope},
    _pathElems {std::move(pathElems)}
{
}

bool DataLocation::operator==(const DataLocation& loc) const
{
    return _scope == loc._scope && _pathElems == loc._pathElems;
}

} // namespace yactfr
