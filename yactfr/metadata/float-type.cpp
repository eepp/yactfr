/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/float-type.hpp>

namespace yactfr {

FloatingPointNumberType::FloatingPointNumberType(const unsigned int align, const unsigned int len,
                                                 const ByteOrder bo) :
    BitArrayType {_KIND_FLOAT, align, len, bo}
{
    assert(len == 32 || len == 64);
}

FloatingPointNumberType::FloatingPointNumberType(const FloatingPointNumberType& other) :
    FloatingPointNumberType {other.alignment(), other.length(), other.byteOrder()}
{
}

DataType::UP FloatingPointNumberType::_clone() const
{
    return std::make_unique<FloatingPointNumberType>(this->alignment(), this->length(),
                                                     this->byteOrder());
}

} // namespace yactfr
