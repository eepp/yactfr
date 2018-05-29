/*
 * CTF bit array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/bit-array-type.hpp>
#include <yactfr/metadata/exceptions.hpp>

namespace yactfr {

BitArrayType::BitArrayType(const int kind, const unsigned int align,
                           const unsigned int size,
                           const ByteOrder byteOrder) :
    ScalarType {_KIND_BIT_ARRAY | kind, align},
    _size {size},
    _byteOrder {byteOrder}
{
    if (_size == 0) {
        throw InvalidMetadata {
            "Bit array type's size is 0."
        };
    }

    if (_size > 64) {
        throw InvalidMetadata {
            "The maximum supported size for a bit array type is 64 bits."
        };
    }
}

bool BitArrayType::operator<(const BitArrayType& bitArrayType) const noexcept
{
    if (this->alignment() < bitArrayType.alignment()) {
        return true;
    }

    if (bitArrayType.alignment() < this->alignment()) {
        return false;
    }

    if (this->size() < bitArrayType.size()) {
        return true;
    }

    if (bitArrayType.size() < this->size()) {
        return false;
    }

    if (this->byteOrder() < bitArrayType.byteOrder()) {
        return true;
    }

    return false;
}

bool BitArrayType::_compare(const DataType& otherType) const noexcept
{
    auto& bitArrayType = static_cast<const BitArrayType&>(otherType);

    return bitArrayType.alignment() == this->alignment() &&
           bitArrayType.size() == this->size() &&
           bitArrayType.byteOrder() == this->byteOrder();
}

} // namespace yactfr
