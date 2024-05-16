/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

StaticLengthStringType::StaticLengthStringType(const unsigned int align, const Size maxLen,
                                               const StringEncoding encoding,
                                               MapItem::Up attrs) :
    NonNullTerminatedStringType {_kindSlStr, align, encoding, std::move(attrs)},
    _maxLen {maxLen}
{
}

StaticLengthStringType::StaticLengthStringType(const Size maxLen, const StringEncoding encoding,
                                               MapItem::Up attrs) :
    StaticLengthStringType {8, maxLen, encoding, std::move(attrs)}
{
}

DataType::Up StaticLengthStringType::_clone() const
{
    return StaticLengthStringType::create(this->alignment(), _maxLen, this->encoding(),
                                          internal::tryCloneAttrs(this->attributes()));
}

bool StaticLengthStringType::_isEqual(const DataType& other) const noexcept
{
    return StringType::_isEqual(other) &&
           _maxLen == other.asStaticLengthStringType()._maxLen;
}

} // namespace yactfr
