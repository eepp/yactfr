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

VariantType::VariantType(const unsigned int align, VariantTypeOptions&& options,
                         const FieldRef& tag) :
    StructVariantTypeBase<VariantTypeOption> {
        _KIND_VARIANT, align, std::move(options)
    },
    _tag {tag}
{
    if (this->_entries().empty()) {
        throw InvalidMetadata {
            "Variant type needs at least one option."
        };
    }
}

DataType::UP VariantType::_clone() const
{
    VariantTypeOptions options;

    this->_cloneEntries(options);

    return std::make_unique<VariantType>(this->alignment(),
                                         std::move(options), _tag);
}

bool VariantType::_compare(const DataType& otherType) const
{
    const auto& varType = static_cast<const VariantType&>(otherType);

    return varType.alignment() == this->alignment() &&
           varType.tag() == this->tag() &&
           this->_compareEntries(varType);
}

} // namespace yactfr
