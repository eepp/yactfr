/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/vl-bit-array-type.hpp>

namespace yactfr {

VariableLengthBitArrayType::VariableLengthBitArrayType(const int kind, const unsigned int align) :
    ScalarDataType {kind, align}
{
    assert(align >= 8);
}

VariableLengthBitArrayType::VariableLengthBitArrayType(const unsigned int align) :
    VariableLengthBitArrayType {_KIND_VL_BIT_ARRAY, align}
{
}

bool VariableLengthBitArrayType::_isEqual(const DataType& other) const noexcept
{
    return true;
}

} // namespace yactfr
