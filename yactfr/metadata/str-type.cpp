/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/str-type.hpp>

namespace yactfr {

StringType::StringType(const unsigned int align) :
    ScalarDataType {_KIND_STR, align}
{
    assert(align >= 8);
}

StringType::StringType(const StringType& other) :
    ScalarDataType {_KIND_STR, other.alignment()}
{
}

DataType::UP StringType::_clone() const
{
    return std::make_unique<StringType>(this->alignment());
}

bool StringType::_compare(const DataType& other) const noexcept
{
    return true;
}

} // namespace yactfr
