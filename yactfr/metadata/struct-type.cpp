/*
 * CTF structure type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/struct-type.hpp>

namespace yactfr {

StructType::StructType(const unsigned int minAlign, StructTypeFields&& fields) :
    StructVariantTypeBase<StructTypeField> {
        _KIND_STRUCT, minAlign, std::move(fields)
    }
{
    this->_setRealAlign();
}

DataType::UP StructType::_clone() const
{
    StructTypeFields fields;

    this->_cloneEntries(fields);

    return std::make_unique<StructType>(this->alignment(),
                                        std::move(fields));
}

bool StructType::_compare(const DataType& otherType) const
{
    const auto& structType = static_cast<const StructType&>(otherType);

    return structType.alignment() == this->alignment() &&
           this->_compareEntries(structType);
}

void StructType::_setRealAlign()
{
    for (const auto& field : this->fields()) {
        const auto fieldAlign = field->type().alignment();

        if (fieldAlign > this->alignment()) {
            this->_setAlign(fieldAlign);
        }
    }
}

} // namespace yactfr
