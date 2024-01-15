/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/nt-str-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

NullTerminatedStringType::NullTerminatedStringType(const unsigned int align, const StringEncoding encoding, MapItem::UP userAttrs) :
    StringType {_KIND_NT_STR, align, encoding, std::move(userAttrs)}
{
    assert(align >= 8);
}

NullTerminatedStringType::NullTerminatedStringType(const StringEncoding encoding,
                                                   MapItem::UP userAttrs) :
    NullTerminatedStringType {8, encoding, std::move(userAttrs)}
{
}

NullTerminatedStringType::NullTerminatedStringType(const NullTerminatedStringType& other) :
    StringType {
        _KIND_NT_STR, other.alignment(), other.encoding(),
        internal::tryCloneUserAttrs(other.userAttributes())
    }
{
}

DataType::UP NullTerminatedStringType::_clone() const
{
    return NullTerminatedStringType::create(this->alignment(), this->encoding(),
                                            internal::tryCloneUserAttrs(this->userAttributes()));
}

} // namespace yactfr
