/*
 * Field of a CTF structure type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <utility>

#include <yactfr/metadata/struct-type-field.hpp>

namespace yactfr {

StructTypeField::StructTypeField(const std::string& name, DataType::UP type) :
    NamedDataType {name, std::move(type)}
{
}

std::unique_ptr<const StructTypeField> StructTypeField::clone() const
{
    return std::make_unique<StructTypeField>(this->name(),
                                             this->type().clone());
}

} // namespace yactfr
