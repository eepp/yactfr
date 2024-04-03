/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/opt-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

OptionalType::OptionalType(const _tKind kind, const unsigned int minAlign, DataType::Up dt,
                           DataLocation&& selLoc, MapItem::Up attrs) :
    CompoundDataType {kind, minAlign, 1, std::move(attrs)},
    _dt {std::move(dt)},
    _selLoc {std::move(selLoc)}
{
}

bool OptionalType::_isEqual(const DataType& other) const noexcept
{
    const auto& otherOptType = other.asOptionalType();

    return CompoundDataType::_isEqual(other) && *_dt == *otherOptType._dt &&
           _selLoc == otherOptType._selLoc;
}

OptionalWithBooleanSelectorType::OptionalWithBooleanSelectorType(const unsigned int minAlign,
                                                                 DataType::Up dt,
                                                                 DataLocation selLoc,
                                                                 MapItem::Up attrs) :
    OptionalType {
        _kindOptUIntSel, minAlign, std::move(dt),
        std::move(selLoc), std::move(attrs)
    }
{
}

OptionalWithBooleanSelectorType::OptionalWithBooleanSelectorType(DataType::Up dt,
                                                                 DataLocation selLoc,
                                                                 MapItem::Up attrs) :
    OptionalWithBooleanSelectorType {1, std::move(dt), std::move(selLoc), std::move(attrs)}
{
}

DataType::Up OptionalWithBooleanSelectorType::_clone() const
{
    return OptionalWithBooleanSelectorType::create(this->minimumAlignment(),
                                                   this->dataType().clone(),
                                                   this->selectorLocation(),
                                                   internal::tryCloneAttrs(this->attributes()));
}

OptionalWithUnsignedIntegerSelectorType::OptionalWithUnsignedIntegerSelectorType(const unsigned int minAlign,
                                                                                 DataType::Up dt,
                                                                                 DataLocation selLoc,
                                                                                 SelectorRangeSet selRanges,
                                                                                 MapItem::Up attrs) :
    OptionalWithIntegerSelectorType<unsigned long long> {
        _kindOptUIntSel, minAlign, std::move(dt),
        std::move(selLoc), std::move(selRanges), std::move(attrs)
    }
{
}

OptionalWithUnsignedIntegerSelectorType::OptionalWithUnsignedIntegerSelectorType(DataType::Up dt,
                                                                                 DataLocation selLoc,
                                                                                 SelectorRangeSet selRanges,
                                                                                 MapItem::Up attrs) :
    OptionalWithUnsignedIntegerSelectorType {
        1, std::move(dt), std::move(selLoc), std::move(selRanges), std::move(attrs)
    }
{
}

DataType::Up OptionalWithUnsignedIntegerSelectorType::_clone() const
{
    return OptionalWithUnsignedIntegerSelectorType::create(this->minimumAlignment(),
                                                           this->dataType().clone(),
                                                           this->selectorLocation(),
                                                           this->selectorRanges(),
                                                           internal::tryCloneAttrs(this->attributes()));
}

OptionalWithSignedIntegerSelectorType::OptionalWithSignedIntegerSelectorType(const unsigned int minAlign,
                                                                             DataType::Up dt,
                                                                             DataLocation selLoc,
                                                                             SelectorRangeSet selRanges,
                                                                             MapItem::Up attrs) :
    OptionalWithIntegerSelectorType<long long> {
        _kindOptSIntSel, minAlign, std::move(dt),
        std::move(selLoc), std::move(selRanges), std::move(attrs)
    }
{
}

OptionalWithSignedIntegerSelectorType::OptionalWithSignedIntegerSelectorType(DataType::Up dt,
                                                                             DataLocation selLoc,
                                                                             SelectorRangeSet selRanges,
                                                                             MapItem::Up attrs) :
    OptionalWithSignedIntegerSelectorType {
        1, std::move(dt), std::move(selLoc), std::move(selRanges), std::move(attrs)
    }
{
}

DataType::Up OptionalWithSignedIntegerSelectorType::_clone() const
{
    return OptionalWithSignedIntegerSelectorType::create(this->minimumAlignment(),
                                                         this->dataType().clone(),
                                                         this->selectorLocation(),
                                                         this->selectorRanges(),
                                                         internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
