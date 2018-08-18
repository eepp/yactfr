/*
 * Option of a CTF variant type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/variant-type-option.hpp>

namespace yactfr {

VariantTypeOption::VariantTypeOption(const std::string& name, DataType::UP type) :
    NamedDataType {name, std::move(type)}
{
}

std::unique_ptr<const VariantTypeOption> VariantTypeOption::clone() const
{
    return std::make_unique<VariantTypeOption>(this->name(),
                                               this->type().clone());
}

} // namespace yactfr
