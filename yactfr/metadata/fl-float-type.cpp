/*
 * SPDX-FileCopyrightText: 2015-2024 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <cassert>

#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

FixedLengthFloatingPointNumberType::FixedLengthFloatingPointNumberType(const unsigned int align,
                                                                       const unsigned int len,
                                                                       const ByteOrder bo,
                                                                       const std::optional<BitOrder>& bio,
                                                                       MapItem::Up attrs) :
    FixedLengthBitArrayType {_kindFlFloat, align, len, bo, bio, std::move(attrs)}
{
    assert(len == 16 || len == 32 || len == 64);
}

FixedLengthFloatingPointNumberType::FixedLengthFloatingPointNumberType(const unsigned int len,
                                                                       const ByteOrder bo,
                                                                       const std::optional<BitOrder>& bio,
                                                                       MapItem::Up attrs) :
    FixedLengthFloatingPointNumberType {1, len, bo, bio, std::move(attrs)}
{
}

FixedLengthFloatingPointNumberType::FixedLengthFloatingPointNumberType(const FixedLengthFloatingPointNumberType& other) :
    FixedLengthFloatingPointNumberType {other.alignment(), other.length(), other.byteOrder(), other.bitOrder()}
{
}

DataType::Up FixedLengthFloatingPointNumberType::_clone() const
{
    return FixedLengthFloatingPointNumberType::create(this->alignment(), this->length(),
                                                      this->byteOrder(), this->bitOrder(),
                                                      internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
