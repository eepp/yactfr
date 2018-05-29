/*
 * CTF field reference.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/field-ref.hpp>

namespace yactfr {

FieldRef::FieldRef(const Scope scope,
                   const std::vector<std::string>& pathElements) :
    _scope {scope},
    _pathElements {pathElements}
{
}

FieldRef::FieldRef(const Scope scope,
                  std::vector<std::string>&& pathElements) :
    _scope {scope},
    _pathElements {std::move(pathElements)}
{
}

FieldRef::FieldRef(const FieldRef& fieldRef) :
    _scope {fieldRef._scope},
    _pathElements {fieldRef._pathElements}
{
}

FieldRef::FieldRef(FieldRef&& fieldRef) :
    _scope {fieldRef._scope},
    _pathElements {std::move(fieldRef._pathElements)}
{
}

bool FieldRef::operator==(const FieldRef& fieldRef) const
{
    return _scope == fieldRef._scope &&
           _pathElements == fieldRef._pathElements;
}

} // namespace yactfr
