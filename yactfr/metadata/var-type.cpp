/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/var-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {

VariantType::VariantType(const _tKind kind, const unsigned int minAlign, DataLocation&& selLoc,
                         MapItem::Up attrs) :
    CompoundDataType {kind, minAlign, 1, std::move(attrs)},
    _selLoc {std::move(selLoc)}
{
}

VariantWithUnsignedIntegerSelectorType::VariantWithUnsignedIntegerSelectorType(const unsigned int minAlign,
                                                                               Options&& opts,
                                                                               DataLocation selLoc,
                                                                               MapItem::Up attrs) :
    VariantWithIntegerSelectorType {
        _kindVarUIntSel, minAlign, std::move(opts),
        std::move(selLoc), std::move(attrs)
    }
{
}

VariantWithUnsignedIntegerSelectorType::VariantWithUnsignedIntegerSelectorType(Options&& opts,
                                                                               DataLocation selLoc,
                                                                               MapItem::Up attrs) :
    VariantWithUnsignedIntegerSelectorType {
        1, std::move(opts), std::move(selLoc), std::move(attrs)
    }
{
}

DataType::Up VariantWithUnsignedIntegerSelectorType::_clone() const
{
    return VariantWithUnsignedIntegerSelectorType::create(this->minimumAlignment(),
                                                          this->_cloneOpts(),
                                                          this->selectorLocation(),
                                                          internal::tryCloneAttrs(this->attributes()));
}

VariantWithSignedIntegerSelectorType::VariantWithSignedIntegerSelectorType(const unsigned int minAlign,
                                                                           Options&& opts,
                                                                           DataLocation selLoc,
                                                                           MapItem::Up attrs) :
    VariantWithIntegerSelectorType {
        _kindVarSIntSel, minAlign, std::move(opts),
        std::move(selLoc), std::move(attrs)
    }
{
}

VariantWithSignedIntegerSelectorType::VariantWithSignedIntegerSelectorType(Options&& opts,
                                                                           DataLocation selLoc,
                                                                           MapItem::Up attrs) :
    VariantWithSignedIntegerSelectorType {
        1, std::move(opts), std::move(selLoc), std::move(attrs)
    }
{
}

DataType::Up VariantWithSignedIntegerSelectorType::_clone() const
{
    return VariantWithSignedIntegerSelectorType::create(this->minimumAlignment(),
                                                        this->_cloneOpts(),
                                                        this->selectorLocation(),
                                                        internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
