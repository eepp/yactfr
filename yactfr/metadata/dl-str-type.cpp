/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/bo.hpp>

namespace yactfr {

DynamicLengthStringType::DynamicLengthStringType(const unsigned int align, DataLocation maxLenLoc) :
    NonNullTerminatedStringType {_KIND_DL_STR, align},
    _maxLenLoc {std::move(maxLenLoc)}
{
}

DataType::UP DynamicLengthStringType::_clone() const
{
    return std::make_unique<DynamicLengthStringType>(this->alignment(), _maxLenLoc);
}

bool DynamicLengthStringType::_isEqual(const DataType& other) const noexcept
{
    auto& otherDlStrType = static_cast<const DynamicLengthStringType&>(other);

    return _maxLenLoc == otherDlStrType._maxLenLoc;
}

} // namespace yactfr

