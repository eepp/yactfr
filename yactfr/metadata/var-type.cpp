/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/var-type.hpp>

#include "utils.hpp"

namespace yactfr {

VariantWithUnsignedSelectorType::VariantWithUnsignedSelectorType(const unsigned int minAlign,
                                                                 Options&& opts,
                                                                 DataLocation selLoc,
                                                                 MapItem::UP userAttrs) :
    VariantType {
        DataType::_KIND_VAR_USEL, minAlign, std::move(opts),
        std::move(selLoc), std::move(userAttrs)
    }
{
}

DataType::UP VariantWithUnsignedSelectorType::_clone() const
{
    return std::make_unique<VariantWithUnsignedSelectorType>(this->minimumAlignment(),
                                                             this->_cloneOpts(),
                                                             this->selectorLocation(),
                                                             internal::tryCloneUserAttrs(this->userAttributes()));
}

VariantWithSignedSelectorType::VariantWithSignedSelectorType(const unsigned int minAlign,
                                                             Options&& opts, DataLocation selLoc,
                                                             MapItem::UP userAttrs) :
    VariantType {
        DataType::_KIND_VAR_SSEL, minAlign, std::move(opts),
        std::move(selLoc), std::move(userAttrs)
    }
{
}

DataType::UP VariantWithSignedSelectorType::_clone() const
{
    return std::make_unique<VariantWithSignedSelectorType>(this->minimumAlignment(),
                                                           this->_cloneOpts(),
                                                           this->selectorLocation(),
                                                           internal::tryCloneUserAttrs(this->userAttributes()));
}

} // namespace yactfr
