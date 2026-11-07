/*
 * SPDX-FileCopyrightText: 2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

DynamicLengthStringType::DynamicLengthStringType(const unsigned int align, DataLocation maxLenLoc,
                                                 const StringEncoding encoding,
                                                 MapItem::Up attrs) :
    NonNullTerminatedStringType {_kindDlStr, align, encoding, std::move(attrs)},
    _maxLenLoc {std::move(maxLenLoc)}
{
}

DynamicLengthStringType::DynamicLengthStringType(DataLocation maxLenLoc,
                                                 const StringEncoding encoding,
                                                 MapItem::Up attrs) :
    DynamicLengthStringType {8, std::move(maxLenLoc), encoding, std::move(attrs)}
{
}

DataType::Up DynamicLengthStringType::_clone() const
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

