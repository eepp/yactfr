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
                                             const DisplayBase preferedDispBase) :
    EnumerationType<SignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_SENUM, mappings, align, len, bo, preferedDispBase
    }
{
}

SignedEnumerationType::SignedEnumerationType(const unsigned int align, const unsigned int len,
                                             const ByteOrder bo, Mappings&& mappings,
                                             const DisplayBase preferedDispBase) :
    EnumerationType<SignedIntegerType, internal::SignedEnumerationTypeValue> {
        _KIND_SENUM, std::move(mappings), align, len, bo, preferedDispBase
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
                                                 const DisplayBase preferedDispBase,
                                                 const ClockType * const mappedClkType) :
    EnumerationType<UnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_UENUM, mappings, align, len, bo, preferedDispBase, mappedClkType
    }
{
}

UnsignedEnumerationType::UnsignedEnumerationType(const unsigned int align, const unsigned int len,
                                                 const ByteOrder bo, Mappings&& mappings,
                                                 const DisplayBase preferedDispBase,
                                                 const ClockType * const mappedClkType) :
    EnumerationType<UnsignedIntegerType, internal::UnsignedEnumerationTypeValue> {
        _KIND_UENUM, std::move(mappings), align, len, bo, preferedDispBase,
        mappedClkType
    }
{
}

DataType::UP UnsignedEnumerationType::_clone() const
{
    return std::make_unique<UnsignedEnumerationType>(this->alignment(), this->length(),
                                                     this->byteOrder(), this->mappings(),
                                                     this->preferredDisplayBase(),
                                                     this->mappedClockType());
}

} // namespace yactfr
