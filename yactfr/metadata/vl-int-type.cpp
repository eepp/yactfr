/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/vl-int-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const unsigned int align,
                                                                     const DisplayBase prefDispBase,
                                                                     Mappings mappings,
                                                                     MapItem::Up attrs,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthIntegerType {
        _kindVlUInt, align, prefDispBase, std::move(mappings), std::move(attrs)
    },
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const DisplayBase prefDispBase,
                                                                     Mappings mappings,
                                                                     MapItem::Up attrs,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthUnsignedIntegerType {
        8, prefDispBase, std::move(mappings), std::move(attrs), std::move(roles)
    }
{
}

DataType::Up VariableLengthUnsignedIntegerType::_clone() const
{
    return VariableLengthUnsignedIntegerType::create(this->alignment(),
                                                     this->preferredDisplayBase(),
                                                     this->mappings(),
                                                     internal::tryCloneAttrs(this->attributes()),
                                                     this->roles());
}

bool VariableLengthUnsignedIntegerType::_isEqual(const DataType& other) const noexcept
{
    return VariableLengthIntegerType::_isEqual(other) &&
           UnsignedIntegerTypeCommon::_isEqual(other.asVariableLengthUnsignedIntegerType());
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const unsigned int align,
                                                                 const DisplayBase prefDispBase,
                                                                 Mappings mappings,
                                                                 MapItem::Up attrs) :
    VariableLengthIntegerType {
        _kindVlSInt, align, prefDispBase, std::move(mappings), std::move(attrs)
    }
{
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const DisplayBase prefDispBase,
                                                                 Mappings mappings,
                                                                 MapItem::Up attrs) :
    VariableLengthSignedIntegerType {8, prefDispBase, std::move(mappings), std::move(attrs)}
{
}

DataType::Up VariableLengthSignedIntegerType::_clone() const
{
    return VariableLengthSignedIntegerType::create(this->alignment(), this->preferredDisplayBase(),
                                                   this->mappings(),
                                                   internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
