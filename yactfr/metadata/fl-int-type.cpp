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
    FixedLengthBitArrayType {_KIND_FL_INT | kind, align, len, bo},
    _prefDispBase {prefDispBase}
{
}

bool FixedLengthIntegerType::_compare(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const FixedLengthIntegerType&>(other);

    return FixedLengthBitArrayType::_compare(other) && _prefDispBase == otherIntType._prefDispBase;
}

bool FixedLengthIntegerType::operator<(const FixedLengthIntegerType& other) const noexcept
{
    if (_prefDispBase < other._prefDispBase) {
        return true;
    }

    if (other._prefDispBase < _prefDispBase) {
        return false;
    }

    return FixedLengthBitArrayType::operator<(other);
}

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const int kind,
                                                           const unsigned int align,
                                                           const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase) :
    FixedLengthIntegerType {_KIND_FL_SINT | kind, align, len, bo, prefDispBase}
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
    FixedLengthIntegerType {_KIND_FL_UINT | kind, align, len, bo, prefDispBase},
    _roles {std::move(roles)}
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
        other.preferredDisplayBase(), other._roles
    }
{
}

DataType::UP FixedLengthUnsignedIntegerType::_clone() const
{
    return std::make_unique<FixedLengthUnsignedIntegerType>(this->alignment(), this->length(),
                                                            this->byteOrder(),
                                                            this->preferredDisplayBase(), _roles);
}

bool FixedLengthUnsignedIntegerType::_compare(const DataType& other) const noexcept
{
    auto& otherIntType = static_cast<const FixedLengthUnsignedIntegerType&>(other);

    return FixedLengthIntegerType::_compare(other) && otherIntType._roles == _roles;
}

bool FixedLengthUnsignedIntegerType::operator<(const FixedLengthUnsignedIntegerType& other) const noexcept
{
    if (_roles < other._roles) {
        return true;
    }

    if (other._roles < _roles) {
        return false;
    }

    return FixedLengthIntegerType::operator<(other);
}

} // namespace yactfr
