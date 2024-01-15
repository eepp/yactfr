/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/vl-int-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

VariableLengthIntegerType::VariableLengthIntegerType(const _Kind kind, const unsigned int align,
                                                     const DisplayBase prefDispBase,
                                                     MapItem::UP attrs) :
    ScalarDataType {kind, align, std::move(attrs)},
    IntegerTypeCommon {prefDispBase}
{
    assert(align >= 8);
}

bool VariableLengthIntegerType::_isEqual(const DataType& other) const noexcept
{
    return IntegerTypeCommon::_isEqual(other.asVariableLengthIntegerType());
}

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const _Kind kind,
                                                                     const unsigned int align,
                                                                     const DisplayBase prefDispBase,
                                                                     MapItem::UP attrs,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthIntegerType {kind, align, prefDispBase, std::move(attrs)},
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const unsigned int align,
                                                                     const DisplayBase prefDispBase,
                                                                     MapItem::UP attrs,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthUnsignedIntegerType {
        _KIND_VL_UINT, align, prefDispBase, std::move(attrs), std::move(roles)
    }
{
}

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const DisplayBase prefDispBase,
                                                                     MapItem::UP attrs,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthUnsignedIntegerType {
        8, prefDispBase, std::move(attrs), std::move(roles)
    }
{
}

DataType::UP VariableLengthUnsignedIntegerType::_clone() const
{
    return VariableLengthUnsignedIntegerType::create(this->alignment(),
                                                     this->preferredDisplayBase(),
                                                     internal::tryCloneAttrs(this->attributes()),
                                                     this->roles());
}

bool VariableLengthUnsignedIntegerType::_isEqual(const DataType& other) const noexcept
{
    return VariableLengthIntegerType::_isEqual(other) &&
           UnsignedIntegerTypeCommon::_isEqual(other.asVariableLengthUnsignedIntegerType());
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const _Kind kind,
                                                                 const unsigned int align,
                                                                 const DisplayBase prefDispBase,
                                                                 MapItem::UP attrs) :
    VariableLengthIntegerType {kind, align, prefDispBase, std::move(attrs)}
{
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const unsigned int align,
                                                                 const DisplayBase prefDispBase,
                                                                 MapItem::UP attrs) :
    VariableLengthIntegerType {_KIND_VL_SINT, align, prefDispBase, std::move(attrs)}
{
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const DisplayBase prefDispBase,
                                                                 MapItem::UP attrs) :
    VariableLengthSignedIntegerType {8, prefDispBase, std::move(attrs)}
{
}

DataType::UP VariableLengthSignedIntegerType::_clone() const
{
    return VariableLengthSignedIntegerType::create(this->alignment(), this->preferredDisplayBase(),
                                                   internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
