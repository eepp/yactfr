/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

FixedLengthBitArrayType::FixedLengthBitArrayType(const _tKind kind, const unsigned int align,
                                                 const unsigned int len, const ByteOrder bo,
                                                 const boost::optional<BitOrder>& bio,
                                                 MapItem::Up attrs) :
    ScalarDataType {kind, align, std::move(attrs)},
    _len {len},
    _bo {bo},
    _bio {bio ? *bio : (bo == ByteOrder::Big ? BitOrder::LastToFirst : BitOrder::FirstToLast)}
{
    assert(_len > 0);
    assert(_len <= 64);
}

FixedLengthBitArrayType::FixedLengthBitArrayType(const unsigned int align,
                                                 const unsigned int len, const ByteOrder bo,
                                                 const boost::optional<BitOrder>& bio,
                                                 MapItem::Up attrs) :
    FixedLengthBitArrayType {_kindFlBitArray, align, len, bo, bio, std::move(attrs)}
{
}

FixedLengthBitArrayType::FixedLengthBitArrayType(const unsigned int len, const ByteOrder bo,
                                                 const boost::optional<BitOrder>& bio,
                                                 MapItem::Up attrs) :
    FixedLengthBitArrayType {1, len, bo, bio, std::move(attrs)}
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

    if (other._bo < _bo) {
        return false;
    }

    if (_bio < other._bio) {
        return true;
    }

    return false;
}

bool FixedLengthBitArrayType::_isEqual(const DataType& other) const noexcept
{
    auto& otherBitArrayType = other.asFixedLengthBitArrayType();

    return _len == otherBitArrayType._len && _bo == otherBitArrayType._bo &&
           _bio == otherBitArrayType._bio;
}

DataType::Up FixedLengthBitArrayType::_clone() const
{
    return FixedLengthBitArrayType::create(this->alignment(), _len, _bo, _bio,
                                           internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
