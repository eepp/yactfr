/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/bo.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

DynamicLengthStringType::DynamicLengthStringType(const unsigned int align, DataLocation maxLenLoc,
                                                 const StringEncoding encoding,
                                                 MapItem::UP attrs) :
    NonNullTerminatedStringType {_KIND_DL_STR, align, encoding, std::move(attrs)},
    _maxLenLoc {std::move(maxLenLoc)}
{
}

DynamicLengthStringType::DynamicLengthStringType(DataLocation maxLenLoc,
                                                 const StringEncoding encoding,
                                                 MapItem::UP attrs) :
    DynamicLengthStringType {8, std::move(maxLenLoc), encoding, std::move(attrs)}
{
}

DataType::UP DynamicLengthStringType::_clone() const
{
    return DynamicLengthStringType::create(this->alignment(), _maxLenLoc, this->encoding(),
                                           internal::tryCloneAttrs(this->attributes()));
}

bool DynamicLengthStringType::_isEqual(const DataType& other) const noexcept
{
    return StringType::_isEqual(other) &&
           _maxLenLoc == other.asDynamicLengthStringType()._maxLenLoc;
}

} // namespace yactfr

