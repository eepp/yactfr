/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/static-array-type.hpp>

namespace yactfr {

StaticArrayType::StaticArrayType(const unsigned int minAlign, DataType::UP elemType,
                                 const Size len, const bool hasTraceTypeUuidRole) :
    StaticArrayType {_KIND_STATIC_ARRAY, minAlign, std::move(elemType), len, hasTraceTypeUuidRole}
{
}

StaticArrayType::StaticArrayType(const int kind, const unsigned int minAlign,
                                 DataType::UP elemType, const Size len,
                                 const bool hasTraceTypeUuidRole) :
    ArrayType {_KIND_STATIC_ARRAY | kind, minAlign, std::move(elemType)},
    _len {len},
    _hasTraceTypeUuidRole {hasTraceTypeUuidRole}
{
}

DataType::UP StaticArrayType::_clone() const
{
    return std::make_unique<StaticArrayType>(this->minimumAlignment(), this->elementType().clone(),
                                             _len, _hasTraceTypeUuidRole);
}

bool StaticArrayType::_compare(const DataType& other) const noexcept
{
    auto& otherStaticArrayType = static_cast<const StaticArrayType&>(other);

    return ArrayType::_compare(other) && _len == otherStaticArrayType._len &&
           otherStaticArrayType._hasTraceTypeUuidRole == _hasTraceTypeUuidRole;
}

} // namespace yactfr
