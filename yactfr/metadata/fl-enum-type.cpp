/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

FixedLengthSignedEnumerationType::FixedLengthSignedEnumerationType(const unsigned int align,
                                                                   const unsigned int len,
                                                                   const ByteOrder bo,
                                                                   Mappings mappings,
                                                                   const DisplayBase prefDispBase,
                                                                   MapItem::UP userAttrs) :
    EnumerationType<FixedLengthSignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_FL_SENUM, std::move(mappings), align, len, bo, prefDispBase, std::move(userAttrs)
    }
{
}

FixedLengthSignedEnumerationType::FixedLengthSignedEnumerationType(const unsigned int len,
                                                                   const ByteOrder bo,
                                                                   Mappings mappings,
                                                                   const DisplayBase prefDispBase,
                                                                   MapItem::UP userAttrs) :
    FixedLengthSignedEnumerationType {
        1, len, bo, std::move(mappings), prefDispBase, std::move(userAttrs)
    }
{
}

DataType::UP FixedLengthSignedEnumerationType::_clone() const
{
    return FixedLengthSignedEnumerationType::create(this->alignment(), this->length(),
                                                    this->byteOrder(), this->mappings(),
                                                    this->preferredDisplayBase(),
                                                    internal::tryCloneUserAttrs(this->userAttributes()));
}

FixedLengthUnsignedEnumerationType::FixedLengthUnsignedEnumerationType(const unsigned int align,
                                                                       const unsigned int len,
                                                                       const ByteOrder bo,
                                                                       Mappings mappings,
                                                                       const DisplayBase prefDispBase,
                                                                       MapItem::UP userAttrs,
                                                                       UnsignedIntegerTypeRoleSet roles) :
    EnumerationType<FixedLengthUnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_FL_UENUM, std::move(mappings), align, len, bo, prefDispBase,
        std::move(userAttrs), std::move(roles)
    }
{
}

FixedLengthUnsignedEnumerationType::FixedLengthUnsignedEnumerationType(const unsigned int len,
                                                                       const ByteOrder bo,
                                                                       Mappings mappings,
                                                                       const DisplayBase prefDispBase,
                                                                       MapItem::UP userAttrs,
                                                                       UnsignedIntegerTypeRoleSet roles) :
    FixedLengthUnsignedEnumerationType {
        1, len, bo, std::move(mappings), prefDispBase, std::move(userAttrs), std::move(roles)
    }
{
}

DataType::UP FixedLengthUnsignedEnumerationType::_clone() const
{
    return FixedLengthUnsignedEnumerationType::create(this->alignment(), this->length(),
                                                      this->byteOrder(), this->mappings(),
                                                      this->preferredDisplayBase(),
                                                      internal::tryCloneUserAttrs(this->userAttributes()),
                                                      this->roles());
}

} // namespace yactfr
