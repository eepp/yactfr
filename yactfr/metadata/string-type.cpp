/*
 * CTF string type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/string-type.hpp>
#include <yactfr/metadata/invalid-metadata.hpp>

namespace yactfr {

StringType::StringType(const unsigned int align) :
    ScalarType {_KIND_STRING, align}
{
    if (align < 8) {
        throw InvalidMetadata {
            "String type's alignment() must be at least 8."
        };
    }
}

StringType::StringType(const StringType& strType) :
    ScalarType {_KIND_STRING, strType.alignment()}
{
}

DataType::UP StringType::_clone() const
{
    return std::make_unique<StringType>(this->alignment());
}

} // namespace yactfr
