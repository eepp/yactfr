/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/var-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

VariantType::VariantType(const _Kind kind, const unsigned int minAlign, DataLocation&& selLoc,
                         MapItem::UP attrs) :
    CompoundDataType {kind, minAlign, 1, std::move(attrs)},
    _selLoc {std::move(selLoc)}
{
}

VariantWithUnsignedIntegerSelectorType::VariantWithUnsignedIntegerSelectorType(const unsigned int minAlign,
                                                                               Options&& opts,
                                                                               DataLocation selLoc,
                                                                               MapItem::UP attrs) :
    VariantWithIntegerSelectorType {
        DataType::_KIND_VAR_UINT_SEL, minAlign, std::move(opts),
        std::move(selLoc), std::move(attrs)
    }
{
}

VariantWithUnsignedIntegerSelectorType::VariantWithUnsignedIntegerSelectorType(Options&& opts,
                                                                               DataLocation selLoc,
                                                                               MapItem::UP attrs) :
    VariantWithUnsignedIntegerSelectorType {
        1, std::move(opts), std::move(selLoc), std::move(attrs)
    }
{
}

DataType::UP VariantWithUnsignedIntegerSelectorType::_clone() const
{
    return VariantWithUnsignedIntegerSelectorType::create(this->minimumAlignment(),
                                                          this->_cloneOpts(),
                                                          this->selectorLocation(),
                                                          internal::tryCloneAttrs(this->attributes()));
}

VariantWithSignedIntegerSelectorType::VariantWithSignedIntegerSelectorType(const unsigned int minAlign,
                                                                           Options&& opts,
                                                                           DataLocation selLoc,
                                                                           MapItem::UP attrs) :
    VariantWithIntegerSelectorType {
        DataType::_KIND_VAR_SINT_SEL, minAlign, std::move(opts),
        std::move(selLoc), std::move(attrs)
    }
{
}

VariantWithSignedIntegerSelectorType::VariantWithSignedIntegerSelectorType(Options&& opts,
                                                                           DataLocation selLoc,
                                                                           MapItem::UP attrs) :
    VariantWithSignedIntegerSelectorType {
        1, std::move(opts), std::move(selLoc), std::move(attrs)
    }
{
}

DataType::UP VariantWithSignedIntegerSelectorType::_clone() const
{
    return VariantWithSignedIntegerSelectorType::create(this->minimumAlignment(),
                                                        this->_cloneOpts(),
                                                        this->selectorLocation(),
                                                        internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
