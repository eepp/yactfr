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

#include <yactfr/internal/metadata/utils.hpp>

#include "dt.hpp"
#include "int-range-set.hpp"
#include "item.hpp"

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

    /// Type of the selector range set.
    using SelectorRangeSet = IntegerRangeSet<SelectorValueT>;

public:
    /*!
    @brief
        Builds a variant type option named \p name having the data type
        \p dataType, copying \p selectorRanges.

    @param[in] name
        Name of the variant type option.
    @param[in] dataType
        Data type of the variant type option.
    @param[in] selectorRanges
        Selector values for which this option is selected (copied).
    @param[in] userAttributes
        @parblock
        User attributes of this variant type option.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p dataType is set.
    @pre
        \p selectorRanges is not empty.
    */
    explicit VariantTypeOption(boost::optional<std::string> name, DataType::UP dataType,
                               const SelectorRangeSet& selectorRanges,
                               MapItem::UP userAttributes = nullptr) :
        _name {std::move(name)},
        _dt {std::move(dataType)},
        _selRanges {selectorRanges},
        _userAttrs {std::move(userAttributes)}
    {
        this->_setDispName();
    }

    /*!
    @brief
        Builds an unnamed variant type option having the type
        \p dataType, copying \p selectorRanges.

    @param[in] dataType
        Data type of the variant type option.
    @param[in] selectorRanges
        Selector values for which this option is selected (copied).
    @param[in] userAttributes
        @parblock
        User attributes of this variant type option.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p dataType is set.
    @pre
        \p selectorRanges is not empty.
    */
    explicit VariantTypeOption(DataType::UP dataType, const SelectorRangeSet& selectorRanges,
                               MapItem::UP userAttributes = nullptr) :
        VariantTypeOption {boost::none, std::move(dataType), selectorRanges, std::move(userAttributes)}
    {
    }

    /*!
    @brief
        Builds a variant type option named \p name having the type
        \p dataType, moving \p selectorRanges.

    @param[in] name
        Name of the variant type option.
    @param[in] dataType
        Data type of the variant type option.
    @param[in] selectorRanges
        Selector values for which this option is selected (moved).

    @pre
        \p dataType is set.
    @pre
        \p selectorRanges is not empty.
    */
    explicit VariantTypeOption(boost::optional<std::string> name, DataType::UP dataType,
                               SelectorRangeSet&& selectorRanges) :
        _name {std::move(name)},
        _dt {std::move(dataType)},
        _selRanges {std::move(selectorRanges)}
    {
        this->_setDispName();
    }

    /*!
    @brief
        Builds an unnamed variant type option having the dataType
        \p type, moving \p selectorRanges.

    @param[in] dataType
        Data type of the variant type option.
    @param[in] selectorRanges
        Selector values for which this option is selected (moved).

    @pre
        \p dataType is set.
    @pre
        \p selectorRanges is not empty.
    */
    explicit VariantTypeOption(DataType::UP dataType, SelectorRangeSet&& selectorRanges) :
        VariantTypeOption {boost::none, std::move(dataType), std::move(selectorRanges)}
    {
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
    const DataType& dataType() const noexcept
    {
        return *_dt;
    }

    /// Selector values for which this option is selected.
    const SelectorRangeSet& selectorRanges() const noexcept
    {
        return _selRanges;
    }

    /*!
    @brief
        User attributes.

    If set, each key of \p *userAttributes is a namespace.

    @note
        Even if the return value isn't \c nullptr, the returned map
        item may still be empty (which also means no user attributes).
    */
    const MapItem *userAttributes() const noexcept
    {
        return _userAttrs.get();
    }

    /// Clone (deep copy) of this variant type option.
    std::unique_ptr<const VariantTypeOption<SelectorValueT>> clone() const
    {
        return std::make_unique<const VariantTypeOption<SelectorValueT>>(_name, _dt->clone(),
                                                                         _selRanges,
                                                                         internal::tryCloneUserAttrs(this->userAttributes()));
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
        return _name == other._name && *_dt == *other._dt && _selRanges == other._selRanges;
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
    const SelectorRangeSet _selRanges;
    const MapItem::UP _userAttrs;
};

/*!
@brief
    Option of the type of data stream variants with an unsigned selector
    (VariantWithUnsignedIntegerSelectorType).

@ingroup metadata_dt
*/
using VariantWithUnsignedIntegerSelectorTypeOption = VariantTypeOption<unsigned long long>;

/*!
@brief
    Option of the type of data stream variants with a signed selector
    (VariantWithSignedIntegerSelectorType).

@ingroup metadata_dt
*/
using VariantWithSignedIntegerSelectorTypeOption = VariantTypeOption<long long>;

} // namespace yactfr

#endif // _YACTFR_METADATA_VAR_TYPE_OPT_HPP
