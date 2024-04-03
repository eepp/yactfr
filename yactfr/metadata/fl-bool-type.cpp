/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/fl-bool-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

FixedLengthBooleanType::FixedLengthBooleanType(const unsigned int align, const unsigned int len,
                                               const ByteOrder bo,
                                               const boost::optional<BitOrder>& bio,
                                               MapItem::Up attrs) :
    FixedLengthBitArrayType {_kindFlBool, align, len, bo, bio, std::move(attrs)}
{
}

FixedLengthBooleanType::FixedLengthBooleanType(const unsigned int len, const ByteOrder bo,
                                               const boost::optional<BitOrder>& bio,
                                               MapItem::Up attrs) :
    FixedLengthBooleanType {1, len, bo, bio, std::move(attrs)}
{
}

FixedLengthBooleanType::FixedLengthBooleanType(const FixedLengthBooleanType& other) :
    FixedLengthBooleanType {other.alignment(), other.length(), other.byteOrder(), other.bitOrder()}
{
}

DataType::Up FixedLengthBooleanType::_clone() const
{
    return FixedLengthBooleanType::create(this->alignment(), this->length(), this->byteOrder(),
                                          this->bitOrder(),
                                          internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
