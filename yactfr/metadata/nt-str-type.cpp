/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/nt-str-type.hpp>

#include "../internal/metadata/utils.hpp"

namespace yactfr {

NullTerminatedStringType::NullTerminatedStringType(const unsigned int align, MapItem::UP userAttrs) :
    ScalarDataType {_KIND_NT_STR, align, std::move(userAttrs)}
{
    assert(align >= 8);
}

NullTerminatedStringType::NullTerminatedStringType(const NullTerminatedStringType& other) :
    ScalarDataType {
        _KIND_NT_STR, other.alignment(), internal::tryCloneUserAttrs(other.userAttributes())
    }
{
}

DataType::UP NullTerminatedStringType::_clone() const
{
    return std::make_unique<NullTerminatedStringType>(this->alignment(),
                                                      internal::tryCloneUserAttrs(this->userAttributes()));
}

bool NullTerminatedStringType::_isEqual(const DataType& other) const noexcept
{
    return true;
}

} // namespace yactfr
