/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/fl-bool-type.hpp>

#include "utils.hpp"

namespace yactfr {

FixedLengthBooleanType::FixedLengthBooleanType(const unsigned int align, const unsigned int len,
                                               const ByteOrder bo, MapItem::UP userAttrs) :
    FixedLengthBitArrayType {_KIND_FL_BOOL, align, len, bo, std::move(userAttrs)}
{
}

FixedLengthBooleanType::FixedLengthBooleanType(const FixedLengthBooleanType& other) :
    FixedLengthBooleanType {other.alignment(), other.length(), other.byteOrder()}
{
}

DataType::UP FixedLengthBooleanType::_clone() const
{
    return std::make_unique<FixedLengthBooleanType>(this->alignment(), this->length(),
                                                    this->byteOrder(),
                                                    internal::tryCloneUserAttrs(this->userAttributes()));
}

} // namespace yactfr
