/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/vl-enum-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

VariableLengthSignedEnumerationType::VariableLengthSignedEnumerationType(const unsigned int align,
                                                                         Mappings mappings,
                                                                         const DisplayBase prefDispBase,
                                                                         MapItem::UP userAttrs) :
    EnumerationType<VariableLengthSignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_VL_SENUM, std::move(mappings), align, prefDispBase, std::move(userAttrs)
    }
{
}

VariableLengthSignedEnumerationType::VariableLengthSignedEnumerationType(Mappings mappings,
                                                                         const DisplayBase prefDispBase,
                                                                         MapItem::UP userAttrs) :
    VariableLengthSignedEnumerationType {
        8, std::move(mappings), prefDispBase, std::move(userAttrs)
    }
{
}

DataType::UP VariableLengthSignedEnumerationType::_clone() const
{
    return VariableLengthSignedEnumerationType::create(this->alignment(), this->mappings(),
                                                       this->preferredDisplayBase(),
                                                       internal::tryCloneUserAttrs(this->userAttributes()));
}

VariableLengthUnsignedEnumerationType::VariableLengthUnsignedEnumerationType(const unsigned int align,
                                                                             Mappings mappings,
                                                                             const DisplayBase prefDispBase,
                                                                             MapItem::UP userAttrs,
                                                                             UnsignedIntegerTypeRoleSet roles) :
    EnumerationType<VariableLengthUnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_VL_UENUM, std::move(mappings), align, prefDispBase,
        std::move(userAttrs), std::move(roles)
    }
{
}

VariableLengthUnsignedEnumerationType::VariableLengthUnsignedEnumerationType(Mappings mappings,
                                                                             const DisplayBase prefDispBase,
                                                                             MapItem::UP userAttrs,
                                                                             UnsignedIntegerTypeRoleSet roles) :
    VariableLengthUnsignedEnumerationType {
        8, std::move(mappings), prefDispBase, std::move(userAttrs), std::move(roles)
    }
{
}

DataType::UP VariableLengthUnsignedEnumerationType::_clone() const
{
    return VariableLengthUnsignedEnumerationType::create(this->alignment(), this->mappings(),
                                                         this->preferredDisplayBase(),
                                                         internal::tryCloneUserAttrs(this->userAttributes()),
                                                         this->roles());
}

} // namespace yactfr
