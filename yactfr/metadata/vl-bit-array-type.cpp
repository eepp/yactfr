/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/vl-bit-array-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

VariableLengthBitArrayType::VariableLengthBitArrayType(const int kind, const unsigned int align,
                                                       MapItem::UP userAttrs) :
    ScalarDataType {kind, align, std::move(userAttrs)}
{
    assert(align >= 8);
}

VariableLengthBitArrayType::VariableLengthBitArrayType(const unsigned int align,
                                                       MapItem::UP userAttrs) :
    VariableLengthBitArrayType {_KIND_VL_BIT_ARRAY, align, std::move(userAttrs)}
{
}

bool VariableLengthBitArrayType::_isEqual(const DataType& other) const noexcept
{
    return true;
}

DataType::UP VariableLengthBitArrayType::_clone() const
{
    return std::make_unique<VariableLengthBitArrayType>(this->alignment(),
                                                        internal::tryCloneUserAttrs(this->userAttributes()));
}

} // namespace yactfr
