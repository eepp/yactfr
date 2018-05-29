/*
 * CTF variant type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/variant-type.hpp>

namespace yactfr {

VariantType::VariantType(const unsigned int align, VariantTypeChoices&& choices,
                         const FieldRef& tag) :
    StructVariantTypeBase<VariantTypeChoice> {
        _KIND_VARIANT, align, std::move(choices)
    },
    _tag {tag}
{
    if (this->_entries().empty()) {
        throw InvalidMetadata {
            "Variant type needs at least one choice."
        };
    }
}

DataType::UP VariantType::_clone() const
{
    VariantTypeChoices choices;

    this->_cloneEntries(choices);

    return std::make_unique<VariantType>(this->alignment(),
                                         std::move(choices), _tag);
}

bool VariantType::_compare(const DataType& otherType) const
{
    const auto& varType = static_cast<const VariantType&>(otherType);

    return varType.alignment() == this->alignment() &&
           varType.tag() == this->tag() &&
           this->_compareEntries(varType);
}

} // namespace yactfr
