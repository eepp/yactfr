/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

FixedLengthIntegerType::FixedLengthIntegerType(const _Kind kind, const unsigned int align,
                                               const unsigned int len, const ByteOrder bo,
                                               const DisplayBase prefDispBase,
                                               MapItem::UP attrs) :
    FixedLengthBitArrayType {kind, align, len, bo, std::move(attrs)},
    IntegerTypeCommon {prefDispBase}
{
}

bool FixedLengthIntegerType::_isEqual(const DataType& other) const noexcept
{
    return FixedLengthBitArrayType::_isEqual(other) &&
           IntegerTypeCommon::_isEqual(other.asFixedLengthIntegerType());
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

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const _Kind kind,
                                                           const unsigned int align,
                                                           const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase,
                                                           MapItem::UP attrs) :
    FixedLengthIntegerType {kind, align, len, bo, prefDispBase, std::move(attrs)}
{
}

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const unsigned int align,
                                                           const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase,
                                                           MapItem::UP attrs) :
    FixedLengthIntegerType {_KIND_FL_SINT, align, len, bo, prefDispBase, std::move(attrs)}
{
}

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase,
                                                           MapItem::UP attrs) :
    FixedLengthSignedIntegerType {1, len, bo, prefDispBase, std::move(attrs)}
{
}

DataType::UP FixedLengthSignedIntegerType::_clone() const
{
    return FixedLengthSignedIntegerType::create(this->alignment(), this->length(),
                                                this->byteOrder(), this->preferredDisplayBase(),
                                                internal::tryCloneAttrs(this->attributes()));
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const _Kind kind,
                                                               const unsigned int align,
                                                               const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               MapItem::UP attrs,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthIntegerType {kind, align, len, bo, prefDispBase, std::move(attrs)},
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const unsigned int align,
                                                               const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               MapItem::UP attrs,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthUnsignedIntegerType {
        _KIND_FL_UINT, align, len, bo, prefDispBase,
        std::move(attrs), std::move(roles)
    }
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               MapItem::UP attrs,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthUnsignedIntegerType {
        1, len, bo, prefDispBase, std::move(attrs), std::move(roles)
    }
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const FixedLengthUnsignedIntegerType& other) :
    FixedLengthUnsignedIntegerType {
        other.alignment(), other.length(), other.byteOrder(),
        other.preferredDisplayBase(), internal::tryCloneAttrs(other.attributes()), other.roles()
    }
{
}

DataType::UP FixedLengthUnsignedIntegerType::_clone() const
{
    return FixedLengthUnsignedIntegerType::create(this->alignment(), this->length(),
                                                  this->byteOrder(), this->preferredDisplayBase(),
                                                  internal::tryCloneAttrs(this->attributes()),
                                                  this->roles());
}

bool FixedLengthUnsignedIntegerType::_isEqual(const DataType& other) const noexcept
{
    return FixedLengthIntegerType::_isEqual(other) &&
           UnsignedIntegerTypeCommon::_isEqual(other.asFixedLengthUnsignedIntegerType());
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
