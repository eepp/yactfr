/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/bit-array-type.hpp>

namespace yactfr {

BitArrayType::BitArrayType(const int kind, const unsigned int align, const unsigned int len,
                           const ByteOrder bo) :
    ScalarDataType {_KIND_BIT_ARRAY | kind, align},
    _len {len},
    _bo {bo}
{
    assert(_len > 0);
    assert(_len <= 64);
}

bool BitArrayType::operator<(const BitArrayType& other) const noexcept
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

bool BitArrayType::_compare(const DataType& other) const noexcept
{
    auto& otherBitArrayType = static_cast<const BitArrayType&>(other);

    return _len == otherBitArrayType._len && _bo == otherBitArrayType._bo;
}

} // namespace yactfr
