/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/fl-enum-type.hpp>

namespace yactfr {

SignedFixedLengthEnumerationType::SignedFixedLengthEnumerationType(const unsigned int align,
                                                                   const unsigned int len,
                                                                   const ByteOrder bo,
                                                                   const Mappings& mappings,
                                                                   const DisplayBase preferredDispBase) :
    FixedLengthEnumerationType<FixedLengthSignedIntegerType,
                               internal::SignedFixedLengthEnumerationTypeValue> {
        _KIND_FL_SENUM, mappings, align, len, bo, preferredDispBase
    }
{
}

SignedFixedLengthEnumerationType::SignedFixedLengthEnumerationType(const unsigned int align,
                                                                   const unsigned int len,
                                                                   const ByteOrder bo,
                                                                   Mappings&& mappings,
                                                                   const DisplayBase preferredDispBase) :
    FixedLengthEnumerationType<FixedLengthSignedIntegerType,
                               internal::SignedFixedLengthEnumerationTypeValue> {
        _KIND_FL_SENUM, std::move(mappings), align, len, bo, preferredDispBase
    }
{
}

DataType::UP SignedFixedLengthEnumerationType::_clone() const
{
    return std::make_unique<SignedFixedLengthEnumerationType>(this->alignment(), this->length(),
                                                              this->byteOrder(), this->mappings(),
                                                              this->preferredDisplayBase());
}

FixedLengthUnsignedEnumerationType::FixedLengthUnsignedEnumerationType(const unsigned int align,
                                                                       const unsigned int len,
                                                                       const ByteOrder bo,
                                                                       const Mappings& mappings,
                                                                       const DisplayBase preferredDispBase,
                                                                       UnsignedIntegerTypeRoleSet roles) :
    FixedLengthEnumerationType<FixedLengthUnsignedIntegerType,
                               internal::FixedLengthUnsignedEnumerationTypeValue> {
        _KIND_FL_UENUM, mappings, align, len, bo, preferredDispBase, std::move(roles)
    }
{
}

FixedLengthUnsignedEnumerationType::FixedLengthUnsignedEnumerationType(const unsigned int align,
                                                                       const unsigned int len,
                                                                       const ByteOrder bo,
                                                                       Mappings&& mappings,
                                                                       const DisplayBase preferredDispBase,
                                                                       UnsignedIntegerTypeRoleSet roles) :
    FixedLengthEnumerationType<FixedLengthUnsignedIntegerType,
                               internal::FixedLengthUnsignedEnumerationTypeValue> {
        _KIND_FL_UENUM, std::move(mappings), align, len, bo, preferredDispBase, std::move(roles)
    }
{
}

DataType::UP FixedLengthUnsignedEnumerationType::_clone() const
{
    return std::make_unique<FixedLengthUnsignedEnumerationType>(this->alignment(), this->length(),
                                                                this->byteOrder(),
                                                                this->mappings(),
                                                                this->preferredDisplayBase(),
                                                                this->roles());
}

} // namespace yactfr
