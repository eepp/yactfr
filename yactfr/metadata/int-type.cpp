/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/int-type.hpp>

namespace yactfr {

IntegerType::IntegerType(const int kind, const unsigned int align, const unsigned int len,
                         const ByteOrder bo, const DisplayBase prefDispBase) :
    BitArrayType {_KIND_INT | kind, align, len, bo},
    _prefDispBase {prefDispBase}
{
}

bool IntegerType::_compare(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const IntegerType&>(other);

    return BitArrayType::_compare(other) && _prefDispBase == otherIntType._prefDispBase;
}

bool IntegerType::operator<(const IntegerType& other) const noexcept
{
    if (_prefDispBase < other._prefDispBase) {
        return true;
    }

    if (other._prefDispBase < _prefDispBase) {
        return false;
    }

    return BitArrayType::operator<(other);
}

SignedIntegerType::SignedIntegerType(const int kind, const unsigned int align,
                                     const unsigned int len, const ByteOrder bo,
                                     const DisplayBase prefDispBase) :
    IntegerType {_KIND_SINT | kind, align, len, bo, prefDispBase}
{
}

SignedIntegerType::SignedIntegerType(const unsigned int align, const unsigned int len,
                                     const ByteOrder bo, const DisplayBase prefDispBase) :
    IntegerType {_KIND_SINT, align, len, bo, prefDispBase}
{
}

DataType::UP SignedIntegerType::_clone() const
{
    return std::make_unique<SignedIntegerType>(this->alignment(), this->length(),
                                               this->byteOrder(), this->preferredDisplayBase());
}

UnsignedIntegerType::UnsignedIntegerType(const int kind, const unsigned int align,
                                         const unsigned int len, const ByteOrder bo,
                                         const DisplayBase prefDispBase,
                                         const ClockType * const mappedClkType) :
    IntegerType {_KIND_UINT | kind, align, len, bo, prefDispBase},
    _mappedClkType {mappedClkType}
{
}

UnsignedIntegerType::UnsignedIntegerType(const unsigned int align, const unsigned int len,
                                         const ByteOrder bo, const DisplayBase prefDispBase,
                                         const ClockType * const mappedClkType) :
    IntegerType {_KIND_UINT, align, len, bo, prefDispBase},
    _mappedClkType {mappedClkType}
{
}

UnsignedIntegerType::UnsignedIntegerType(const UnsignedIntegerType& other) :
    UnsignedIntegerType {
        other.alignment(), other.length(), other.byteOrder(),
        other.preferredDisplayBase(), other._mappedClkType
    }
{
}

DataType::UP UnsignedIntegerType::_clone() const
{
    return std::make_unique<UnsignedIntegerType>(this->alignment(), this->length(),
                                                 this->byteOrder(), this->preferredDisplayBase(),
                                                 _mappedClkType);
}

bool UnsignedIntegerType::_compare(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const UnsignedIntegerType&>(other);

    return IntegerType::_compare(other) && otherIntType._mappedClkType == _mappedClkType;
}

bool UnsignedIntegerType::operator<(const UnsignedIntegerType& other) const noexcept
{
    if (_mappedClkType < other._mappedClkType) {
        return true;
    }

    if (other._mappedClkType < _mappedClkType) {
        return false;
    }

    return IntegerType::operator<(other);
}

} // namespace yactfr
