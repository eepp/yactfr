/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_VAR_TYPE_OPT_HPP
#define _YACTFR_METADATA_VAR_TYPE_OPT_HPP

#include <string>
#include <vector>
#include <memory>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

#include "dt.hpp"
#include "int-range-set.hpp"
#include "../item.hpp"

namespace yactfr {

/*!
@brief
    Generic \link VariantType variant type\endlink option.

@ingroup metadata_dt
*/
template <typename SelectorValueT>
class VariantTypeOption final :
    boost::noncopyable
{
public:
    /// Type of the value of a selector.
    using SelectorValue = SelectorValueT;

    /// Type of the integer range set.
    using RangeSet = IntegerRangeSet<SelectorValueT>;

public:
    /*!
    @brief
        Builds a variant type option named \p name having the type
        \p type, copying \p ranges.

    @param[in] name
        Name of the variant type option.
    @param[in] type
        Data type of the variant type option.
    @param[in] ranges
        Ranges for which this variant type option is selected (copied).
    @param[in] userAttributes
        @parblock
        User attributes of this variant type option.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p ranges is not empty.
    */
    explicit VariantTypeOption(boost::optional<std::string> name, DataType::UP type,
                               const RangeSet& ranges,
                               MapItem::UP userAttributes = nullptr) :
        _name {std::move(name)},
        _dt {std::move(type)},
        _ranges {ranges},
        _userAttrs {std::move(userAttributes)}
    {
        this->_setDispName();
    }

    /*!
    @brief
        Builds a variant type option named \p name having the type
        \p type, moving \p ranges.

    @param[in] name
        Name of the variant type option.
    @param[in] type
        Data type of the variant type option.
    @param[in] ranges
        Ranges for which this variant type option is selected (moved).

    @pre
        \p ranges is not empty.
    */
    explicit VariantTypeOption(boost::optional<std::string> name, DataType::UP type,
                               RangeSet&& ranges) :
        _name {std::move(name)},
        _dt {std::move(type)},
        _ranges {std::move(ranges)}
    {
        this->_setDispName();
    }

public:
    /// Name of this variant type option.
    const boost::optional<std::string>& name() const noexcept
    {
        return _name;
    }

    /// Display name (name() with first underscore removed, if any)
    /// of this variant type option.
    const boost::optional<std::string>& displayName() const noexcept
    {
        return _dispName;
    }

    /// Data type of this variant type option.
    const DataType& type() const noexcept
    {
        return *_dt;
    }

    /// Range set of this variant type option.
    const RangeSet& ranges() const noexcept
    {
        return _ranges;
    }

    /*!
    @brief
        User attributes.

    If set, each key of \p *userAttributes is a namespace.
    */
    const MapItem *userAttributes() const noexcept
    {
        return _userAttrs.get();
    }

    /// Clone (deep copy) of this variant type option.
    std::unique_ptr<const VariantTypeOption<SelectorValueT>> clone() const
    {
        return std::make_unique<const VariantTypeOption<SelectorValueT>>(_name, _dt->clone(),
                                                                         _ranges);
    }

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other variant type option to compare to.

    @returns
        \c true if \p other is equal to this variant type option.
    */
    bool operator==(const VariantTypeOption<SelectorValueT>& other) const
    {
        return _name == other._name && *_dt == *other._dt && _ranges == other._ranges;
    }

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Other variant type option to compare to.

    @returns
        \c true if \p other is not equal to this variant type option.
    */
    bool operator!=(const VariantTypeOption<SelectorValueT>& other) const
    {
        return !(*this == other);
    }

private:
    void _setDispName()
    {
        if (_name) {
            if ((*_name)[0] == '_') {
                _dispName = _name->substr(1);
            } else {
                _dispName = _name;
            }
        }
    }

private:
    const boost::optional<std::string> _name;
    boost::optional<std::string> _dispName;
    const DataType::UP _dt;
    const RangeSet _ranges;
    const MapItem::UP _userAttrs;
};

/*!
@brief
    Option of the type of data stream variants with an unsigned selector
    (VariantWithUnsignedSelectorType).

@ingroup metadata_dt
*/
using VariantWithUnsignedSelectorTypeOption = VariantTypeOption<unsigned long long>;

/*!
@brief
    Option of the type of data stream variants with a signed selector
    (VariantWithSignedSelectorType).

@ingroup metadata_dt
*/
using VariantWithSignedSelectorTypeOption = VariantTypeOption<long long>;

} // namespace yactfr

#endif // _YACTFR_METADATA_VAR_TYPE_OPT_HPP
