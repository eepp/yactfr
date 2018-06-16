/*
 * CTF named data type base class.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/invalid-metadata.hpp>
#include <yactfr/metadata/named-data-type.hpp>

namespace yactfr {

NamedDataType::NamedDataType(const std::string& name, DataType::UP type) :
    _name {name},
    _type {std::move(type)}
{
    if (name.empty()) {
        throw InvalidMetadata {
            "Field has no name."
        };
    }

    if (!_type) {
        throw InvalidMetadata {
            "Field has no data type."
        };
    }

    if (name[0] == '_') {
        _dispName = name.substr(1);
    } else {
        _dispName = name;
    }
}

bool NamedDataType::operator==(const NamedDataType& otherNamedDataType) const
{
    return otherNamedDataType.name() == this->name() &&
           otherNamedDataType.type() == this->type();
}

} // namespace yactfr
