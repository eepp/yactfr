/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

StaticLengthStringType::StaticLengthStringType(const unsigned int align, const Size maxLen,
                                               MapItem::UP userAttrs) :
    NonNullTerminatedStringType {_KIND_SL_STR, align, std::move(userAttrs)},
    _maxLen {maxLen}
{
}

DataType::UP StaticLengthStringType::_clone() const
{
    return std::make_unique<StaticLengthStringType>(this->alignment(), _maxLen,
                                                    internal::tryCloneUserAttrs(this->userAttributes()));
}

bool StaticLengthStringType::_isEqual(const DataType& other) const noexcept
{
    auto& otherSlStrType = static_cast<const StaticLengthStringType&>(other);

    return _maxLen == otherSlStrType._maxLen;
}

} // namespace yactfr
