/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/var-type.hpp>

#include "internal/utils.hpp"

namespace yactfr {

VariantWithUnsignedIntegerSelectorType::VariantWithUnsignedIntegerSelectorType(const unsigned int minAlign,
                                                                               Options&& opts,
                                                                               DataLocation selLoc,
                                                                               MapItem::UP userAttrs) :
    VariantType {
        DataType::_KIND_VAR_UINT_SEL, minAlign, std::move(opts),
        std::move(selLoc), std::move(userAttrs)
    }
{
}

DataType::UP VariantWithUnsignedIntegerSelectorType::_clone() const
{
    return std::make_unique<VariantWithUnsignedIntegerSelectorType>(this->minimumAlignment(),
                                                                    this->_cloneOpts(),
                                                                    this->selectorLocation(),
                                                                    internal::tryCloneUserAttrs(this->userAttributes()));
}

VariantWithSignedIntegerSelectorType::VariantWithSignedIntegerSelectorType(const unsigned int minAlign,
                                                                           Options&& opts,
                                                                           DataLocation selLoc,
                                                                           MapItem::UP userAttrs) :
    VariantType {
        DataType::_KIND_VAR_SINT_SEL, minAlign, std::move(opts),
        std::move(selLoc), std::move(userAttrs)
    }
{
}

DataType::UP VariantWithSignedIntegerSelectorType::_clone() const
{
    return std::make_unique<VariantWithSignedIntegerSelectorType>(this->minimumAlignment(),
                                                                  this->_cloneOpts(),
                                                                  this->selectorLocation(),
                                                                  internal::tryCloneUserAttrs(this->userAttributes()));
}

} // namespace yactfr
