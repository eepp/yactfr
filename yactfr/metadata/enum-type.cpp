/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/enum-type.hpp>

namespace yactfr {

SignedEnumerationType::SignedEnumerationType(const unsigned int align, const unsigned int len,
                                             const ByteOrder bo, const Mappings& mappings,
                                             const DisplayBase preferredDispBase) :
    EnumerationType<SignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_SENUM, mappings, align, len, bo, preferredDispBase
    }
{
}

SignedEnumerationType::SignedEnumerationType(const unsigned int align, const unsigned int len,
                                             const ByteOrder bo, Mappings&& mappings,
                                             const DisplayBase preferredDispBase) :
    EnumerationType<SignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_SENUM, std::move(mappings), align, len, bo, preferredDispBase
    }
{
}

DataType::UP SignedEnumerationType::_clone() const
{
    return std::make_unique<SignedEnumerationType>(this->alignment(), this->length(),
                                                   this->byteOrder(), this->mappings(),
                                                   this->preferredDisplayBase());
}

UnsignedEnumerationType::UnsignedEnumerationType(const unsigned int align, const unsigned int len,
                                                 const ByteOrder bo, const Mappings& mappings,
                                                 const DisplayBase preferredDispBase,
                                                 UnsignedIntegerTypeRoleSet roles) :
    EnumerationType<UnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_UENUM, mappings, align, len, bo, preferredDispBase, std::move(roles)
    }
{
}

UnsignedEnumerationType::UnsignedEnumerationType(const unsigned int align, const unsigned int len,
                                                 const ByteOrder bo, Mappings&& mappings,
                                                 const DisplayBase preferredDispBase,
                                                 UnsignedIntegerTypeRoleSet roles) :
    EnumerationType<UnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_UENUM, std::move(mappings), align, len, bo, preferredDispBase, std::move(roles)
    }
{
}

DataType::UP UnsignedEnumerationType::_clone() const
{
    return std::make_unique<UnsignedEnumerationType>(this->alignment(), this->length(),
                                                     this->byteOrder(), this->mappings(),
                                                     this->preferredDisplayBase(), this->roles());
}

} // namespace yactfr
