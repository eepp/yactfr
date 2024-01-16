/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const unsigned int align,
                                                           const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase,
                                                           Mappings mappings,
                                                           MapItem::UP attrs) :
    FixedLengthIntegerType {
        _KIND_FL_SINT, align, len, bo, prefDispBase, std::move(mappings), std::move(attrs)
    }
{
}

FixedLengthSignedIntegerType::FixedLengthSignedIntegerType(const unsigned int len,
                                                           const ByteOrder bo,
                                                           const DisplayBase prefDispBase,
                                                           Mappings mappings,
                                                           MapItem::UP attrs) :
    FixedLengthSignedIntegerType {1, len, bo, prefDispBase, std::move(mappings), std::move(attrs)}
{
}

DataType::UP FixedLengthSignedIntegerType::_clone() const
{
    return FixedLengthSignedIntegerType::create(this->alignment(), this->length(),
                                                this->byteOrder(), this->preferredDisplayBase(),
                                                this->mappings(),
                                                internal::tryCloneAttrs(this->attributes()));
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const unsigned int align,
                                                               const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               Mappings mappings,
                                                               MapItem::UP attrs,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthIntegerType {
        _KIND_FL_UINT, align, len, bo, prefDispBase,
        std::move(mappings), std::move(attrs)
    },
    UnsignedIntegerTypeCommon {std::move(roles)}
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const unsigned int len,
                                                               const ByteOrder bo,
                                                               const DisplayBase prefDispBase,
                                                               Mappings mappings,
                                                               MapItem::UP attrs,
                                                               UnsignedIntegerTypeRoleSet roles) :
    FixedLengthUnsignedIntegerType {
        1, len, bo, prefDispBase, std::move(mappings), std::move(attrs), std::move(roles)
    }
{
}

FixedLengthUnsignedIntegerType::FixedLengthUnsignedIntegerType(const FixedLengthUnsignedIntegerType& other) :
    FixedLengthUnsignedIntegerType {
        other.alignment(), other.length(), other.byteOrder(),
        other.preferredDisplayBase(), other.mappings(),
        internal::tryCloneAttrs(other.attributes()), other.roles()
    }
{
}

DataType::UP FixedLengthUnsignedIntegerType::_clone() const
{
    return FixedLengthUnsignedIntegerType::create(this->alignment(), this->length(),
                                                  this->byteOrder(), this->preferredDisplayBase(),
                                                  this->mappings(),
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
