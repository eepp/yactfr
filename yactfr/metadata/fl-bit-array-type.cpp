/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/fl-bit-array-type.hpp>

#include "utils.hpp"

namespace yactfr {

FixedLengthBitArrayType::FixedLengthBitArrayType(const int kind, const unsigned int align,
                                                 const unsigned int len, const ByteOrder bo,
                                                 MapItem::UP userAttrs) :
    ScalarDataType {kind, align, std::move(userAttrs)},
    _len {len},
    _bo {bo}
{
    assert(_len > 0);
    assert(_len <= 64);
}

FixedLengthBitArrayType::FixedLengthBitArrayType(const unsigned int align,
                                                 const unsigned int len, const ByteOrder bo,
                                                 MapItem::UP userAttrs) :
    FixedLengthBitArrayType {_KIND_FL_BIT_ARRAY, align, len, bo, std::move(userAttrs)}
{
}

bool FixedLengthBitArrayType::operator<(const FixedLengthBitArrayType& other) const noexcept
{
    if (this->alignment() < other.alignment()) {
        return true;
    }

    if (other.alignment() < this->alignment()) {
        return false;
    }

    if (_len < other._len) {
        return true;
    }

    if (other._len < _len) {
        return false;
    }

    if (_bo < other._bo) {
        return true;
    }

    return false;
}

bool FixedLengthBitArrayType::_isEqual(const DataType& other) const noexcept
{
    auto& otherBitArrayType = static_cast<const FixedLengthBitArrayType&>(other);

    return _len == otherBitArrayType._len && _bo == otherBitArrayType._bo;
}

DataType::UP FixedLengthBitArrayType::_clone() const
{
    return std::make_unique<FixedLengthBitArrayType>(this->alignment(), this->length(),
                                                     this->byteOrder(),
                                                     internal::tryCloneUserAttrs(this->userAttributes()));
}

} // namespace yactfr
