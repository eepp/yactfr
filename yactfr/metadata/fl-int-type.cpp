/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/fl-int-type.hpp>

#include "../internal/metadata/utils.hpp"

namespace yactfr {

FixedLengthIntegerType::FixedLengthIntegerType(const int kind, const unsigned int align,
                                               const unsigned int len, const ByteOrder bo,
                                               const DisplayBase prefDispBase,
                                               MapItem::UP userAttrs) :
    FixedLengthBitArrayType {kind, align, len, bo, std::move(userAttrs)},
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
                                                           const DisplayBase prefDispBase,
                                                           MapItem::UP userAttrs) :
    FixedLengthIntegerType {kind, align, len, bo, prefDispBase, std::move(userAttrs)}
{
}

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const unsigned int align,
                                                           const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase,
                                                           MapItem::UP userAttrs) :
    FixedLengthIntegerType {_KIND_FL_SINT, align, len, bo, prefDispBase, std::move(userAttrs)}
{
}

DataType::UP FixedLengthSignedIntegerType::_clone() const
{
    return std::make_unique<FixedLengthSignedIntegerType>(this->alignment(), this->length(),
                                                          this->byteOrder(),
                                                          this->preferredDisplayBase(),
                                                          internal::tryCloneUserAttrs(this->userAttributes()));
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const int kind,
                                                               const unsigned int align,
                                                               const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               MapItem::UP userAttrs,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthIntegerType {kind, align, len, bo, prefDispBase, std::move(userAttrs)},
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const unsigned int align,
                                                               const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               MapItem::UP userAttrs,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthUnsignedIntegerType {
        _KIND_FL_UINT, align, len, bo, prefDispBase,
        std::move(userAttrs), std::move(roles)
    }
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const FixedLengthUnsignedIntegerType& other) :
    FixedLengthUnsignedIntegerType {
        other.alignment(), other.length(), other.byteOrder(),
        other.preferredDisplayBase(), internal::tryCloneUserAttrs(other.userAttributes()), other.roles()
    }
{
}

DataType::UP FixedLengthUnsignedIntegerType::_clone() const
{
    return std::make_unique<FixedLengthUnsignedIntegerType>(this->alignment(), this->length(),
                                                            this->byteOrder(),
                                                            this->preferredDisplayBase(),
                                                            internal::tryCloneUserAttrs(this->userAttributes()),
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
