/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/str-type.hpp>

namespace yactfr {

StringType::StringType(const _Kind kind, const unsigned int align, const StringEncoding encoding,
                       MapItem::UP attrs) :
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
