/*
 * SPDX-FileCopyrightText: 2022-2024 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <cassert>

#include <yactfr/metadata/str-type.hpp>

namespace yactfr {

StringType::StringType(const _tKind kind, const unsigned int align, const StringEncoding encoding,
                       MapItem::Up attrs) :
    ScalarDataType {kind, align, std::move(attrs)},
    _encoding {encoding}
{
    assert(align >= 8);
}

bool StringType::_isEqual(const DataType& other) const noexcept
{
    return _encoding == static_cast<const StringType&>(other)._encoding;
}

} // namespace yactfr
