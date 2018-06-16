/*
 * CTF floating point number type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/invalid-metadata.hpp>

namespace yactfr {

FloatType::FloatType(const unsigned int align, const unsigned int size,
                     const ByteOrder byteOrder) :
    BitArrayType {_KIND_FLOAT, align, size, byteOrder}
{
    if (size != 32 && size != 64) {
        throw InvalidMetadata {
            "This version only supports 32-bit and 64-bit floating "
            "point number types."
        };
    }
}

FloatType::FloatType(const FloatType& floatType) :
    FloatType {floatType.alignment(), floatType.size(), floatType.byteOrder()}
{
}

bool FloatType::operator<(const FloatType& floatType) const noexcept
{
    if (this->alignment() < floatType.alignment()) {
        return true;
    }

    if (floatType.alignment() < this->alignment()) {
        return false;
    }

    if (this->size() < floatType.size()) {
        return true;
    }

    if (floatType.size() < this->size()) {
        return false;
    }

    if (this->byteOrder() < floatType.byteOrder()) {
        return true;
    }

    return false;
}

DataType::UP FloatType::_clone() const
{
    return std::make_unique<FloatType>(this->alignment(), this->size(),
                                       this->byteOrder());
}

bool FloatType::_compare(const DataType& otherType) const noexcept
{
    auto& floatType = static_cast<const FloatType&>(otherType);

    return floatType.alignment() == this->alignment() &&
           floatType.size() == this->size() &&
           floatType.byteOrder() == this->byteOrder();
}

} // namespace yactfr
