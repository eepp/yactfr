/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/data-loc.hpp>

namespace yactfr {

DataLocation::DataLocation(const Scope scope, const std::vector<std::string>& pathElems) :
    _scope {scope},
    _pathElems {pathElems}
{
}

DataLocation::DataLocation(const Scope scope, std::vector<std::string>&& pathElems) :
    _scope {scope},
    _pathElems {std::move(pathElems)}
{
}

bool DataLocation::operator==(const DataLocation& loc) const
{
    return _scope == loc._scope && _pathElems == loc._pathElems;
}

} // namespace yactfr
