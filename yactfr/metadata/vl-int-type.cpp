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
                                                                     MapItem::UP attrs,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthIntegerType {
        _KIND_VL_UINT, align, prefDispBase, std::move(mappings), std::move(attrs)
    },
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const DisplayBase prefDispBase,
                                                                     Mappings mappings,
                                                                     MapItem::UP attrs,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthUnsignedIntegerType {
        8, prefDispBase, std::move(mappings), std::move(attrs), std::move(roles)
    }
{
}

DataType::UP VariableLengthUnsignedIntegerType::_clone() const
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
                                                                 MapItem::UP attrs) :
    VariableLengthIntegerType {
        _KIND_VL_SINT, align, prefDispBase, std::move(mappings), std::move(attrs)
    }
{
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const DisplayBase prefDispBase,
                                                                 Mappings mappings,
                                                                 MapItem::UP attrs) :
    VariableLengthSignedIntegerType {8, prefDispBase, std::move(mappings), std::move(attrs)}
{
}

DataType::UP VariableLengthSignedIntegerType::_clone() const
{
    return VariableLengthSignedIntegerType::create(this->alignment(), this->preferredDisplayBase(),
                                                   this->mappings(),
                                                   internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
