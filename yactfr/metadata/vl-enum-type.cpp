/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/vl-enum-type.hpp>

namespace yactfr {

VariableLengthSignedEnumerationType::VariableLengthSignedEnumerationType(const unsigned int align,
                                                                         const Mappings& mappings,
                                                                         const DisplayBase prefDispBase) :
    EnumerationType<VariableLengthSignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_VL_SENUM, mappings, align, prefDispBase
    }
{
}

VariableLengthSignedEnumerationType::VariableLengthSignedEnumerationType(const unsigned int align,
                                                                         Mappings&& mappings,
                                                                         const DisplayBase prefDispBase) :
    EnumerationType<VariableLengthSignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_VL_SENUM, std::move(mappings), align, prefDispBase
    }
{
}

DataType::UP VariableLengthSignedEnumerationType::_clone() const
{
    return std::make_unique<VariableLengthSignedEnumerationType>(this->alignment(),
                                                                 this->mappings(),
                                                                 this->preferredDisplayBase());
}

VariableLengthUnsignedEnumerationType::VariableLengthUnsignedEnumerationType(const unsigned int align,
                                                                             const Mappings& mappings,
                                                                             const DisplayBase prefDispBase,
                                                                             UnsignedIntegerTypeRoleSet roles) :
    EnumerationType<VariableLengthUnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_FL_UENUM, mappings, align, prefDispBase, std::move(roles)
    }
{
}

VariableLengthUnsignedEnumerationType::VariableLengthUnsignedEnumerationType(const unsigned int align,
                                                                             Mappings&& mappings,
                                                                             const DisplayBase prefDispBase,
                                                                             UnsignedIntegerTypeRoleSet roles) :
    EnumerationType<VariableLengthUnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_FL_UENUM, std::move(mappings), align, prefDispBase, std::move(roles)
    }
{
}

DataType::UP VariableLengthUnsignedEnumerationType::_clone() const
{
    return std::make_unique<VariableLengthUnsignedEnumerationType>(this->alignment(),
                                                                   this->mappings(),
                                                                   this->preferredDisplayBase(),
                                                                   this->roles());
}

} // namespace yactfr
