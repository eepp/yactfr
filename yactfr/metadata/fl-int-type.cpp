/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/fl-int-type.hpp>

namespace yactfr {

FixedLengthIntegerType::FixedLengthIntegerType(const int kind, const unsigned int align,
                                               const unsigned int len, const ByteOrder bo,
                                               const DisplayBase prefDispBase) :
    FixedLengthBitArrayType {kind, align, len, bo},
    IntegerTypeCommon {prefDispBase}
{
}

bool FixedLengthIntegerType::_isEqual(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const FixedLengthIntegerType&>(other);

    return FixedLengthBitArrayType::_isEqual(other) && IntegerTypeCommon::_isEqual(otherIntType);
}

bool FixedLengthIntegerType::operator<(const FixedLengthIntegerType& other) const noexcept
{
    if (this->preferredDisplayBase() < other.preferredDisplayBase()) {
        return true;
    }

    if (other.preferredDisplayBase() < this->preferredDisplayBase()) {
        return false;
    }

    return FixedLengthBitArrayType::operator<(other);
}

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const int kind,
                                                           const unsigned int align,
                                                           const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase) :
    FixedLengthIntegerType {kind, align, len, bo, prefDispBase}
{
}

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const unsigned int align,
                                                           const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase) :
    FixedLengthIntegerType {_KIND_FL_SINT, align, len, bo, prefDispBase}
{
}

DataType::UP FixedLengthSignedIntegerType::_clone() const
{
    return std::make_unique<FixedLengthSignedIntegerType>(this->alignment(), this->length(),
                                                          this->byteOrder(),
                                                          this->preferredDisplayBase());
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const int kind,
                                                               const unsigned int align,
                                                               const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthIntegerType {kind, align, len, bo, prefDispBase},
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const unsigned int align,
                                                               const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthUnsignedIntegerType {_KIND_FL_UINT, align, len, bo, prefDispBase, std::move(roles)}
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const FixedLengthUnsignedIntegerType& other) :
    FixedLengthUnsignedIntegerType {
        other.alignment(), other.length(), other.byteOrder(),
        other.preferredDisplayBase(), other.roles()
    }
{
}

DataType::UP FixedLengthUnsignedIntegerType::_clone() const
{
    return std::make_unique<FixedLengthUnsignedIntegerType>(this->alignment(), this->length(),
                                                            this->byteOrder(),
                                                            this->preferredDisplayBase(),
                                                            this->roles());
}

bool FixedLengthUnsignedIntegerType::_isEqual(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const FixedLengthUnsignedIntegerType&>(other);

    return FixedLengthIntegerType::_isEqual(other) && UnsignedIntegerTypeCommon::_isEqual(otherIntType);
}

bool FixedLengthUnsignedIntegerType::operator<(const FixedLengthUnsignedIntegerType& other) const noexcept
{
    if (this->roles() < other.roles()) {
        return true;
    }

    if (other.roles() < this->roles()) {
        return false;
    }

    return FixedLengthIntegerType::operator<(other);
}

} // namespace yactfr
