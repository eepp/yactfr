/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/vl-int-type.hpp>

namespace yactfr {

VariableLengthIntegerType::VariableLengthIntegerType(const int kind, const unsigned int align,
                                                     const DisplayBase prefDispBase) :
    VariableLengthBitArrayType {kind, align},
    IntegerTypeCommon {prefDispBase}
{
}

bool VariableLengthIntegerType::_isEqual(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const VariableLengthIntegerType&>(other);

    return VariableLengthBitArrayType::_isEqual(other) && IntegerTypeCommon::_isEqual(otherIntType);
}

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const int kind,
                                                                     const unsigned int align,
                                                                     const DisplayBase prefDispBase,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthIntegerType {kind, align, prefDispBase},
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

VariableLengthUnsignedIntegerType::VariableLengthUnsignedIntegerType(const unsigned int align,
                                                                     const DisplayBase prefDispBase,
                                                                     UnsignedIntegerTypeRoleSet roles) :
    VariableLengthUnsignedIntegerType {_KIND_VL_UINT, align, prefDispBase, std::move(roles)}
{
}

DataType::UP VariableLengthUnsignedIntegerType::_clone() const
{
    return std::make_unique<VariableLengthUnsignedIntegerType>(this->alignment(),
                                                               this->preferredDisplayBase(),
                                                               this->roles());
}

bool VariableLengthUnsignedIntegerType::_isEqual(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const VariableLengthUnsignedIntegerType&>(other);

    return VariableLengthIntegerType::_isEqual(other) && UnsignedIntegerTypeCommon::_isEqual(otherIntType);
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const int kind,
                                                                 const unsigned int align,
                                                                 const DisplayBase prefDispBase) :
    VariableLengthIntegerType {kind, align, prefDispBase}
{
}

VariableLengthSignedIntegerType::VariableLengthSignedIntegerType(const unsigned int align,
                                                                 const DisplayBase prefDispBase) :
    VariableLengthIntegerType {_KIND_VL_SINT, align, prefDispBase}
{
}

DataType::UP VariableLengthSignedIntegerType::_clone() const
{
    return std::make_unique<VariableLengthSignedIntegerType>(this->alignment(),
                                                             this->preferredDisplayBase());
}

} // namespace yactfr
