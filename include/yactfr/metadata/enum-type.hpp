/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_ENUM_TYPE_HPP
#define _YACTFR_METADATA_ENUM_TYPE_HPP

#include <set>
#include <utility>
#include <type_traits>
#include <iterator>
#include <string>
#include <unordered_map>
#include <limits>
#include <sstream>
#include <memory>
#include <boost/optional.hpp>

#include "bo.hpp"
#include "int-range-set.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Abstract enumeration type.

@ingroup metadata_dt

An enumeration type describes data stream enumerations.

Use the concrete FixedLengthSignedEnumerationType,
FixedLengthUnsignedEnumerationType, VariableLengthSignedEnumerationType,
VariableLengthUnsignedEnumerationType depending on the length type and
signedness of the data stream enumerations to describe.

@tparam IntegerTypeParentT
    Parent integer type class.
@tparam ValueT
    Type of the lower and upper values of an integer range within a
    mapping.
*/
template <typename IntegerTypeParentT, typename ValueT>
class EnumerationType :
    public IntegerTypeParentT
{
public:
    /// Type of an integer range set within a mapping.
    using RangeSet = IntegerRangeSet<ValueT>;

    /// Type of mappings.
    using Mappings = std::unordered_map<std::string, RangeSet>;

protected:
    template <typename... ArgTs>
    explicit EnumerationType(const int kind, const Mappings& mappings, ArgTs&&... args) :
        IntegerTypeParentT {kind, std::forward<ArgTs>(args)...},
        _mappings {mappings}
    {
        assert(this->_mappingsAreValid());
    }

    template <typename... ArgTs>
    explicit EnumerationType(const int kind, Mappings&& mappings, ArgTs&&... args) :
        IntegerTypeParentT {kind, std::forward<ArgTs>(args)...},
        _mappings {std::move(mappings)}
    {
        assert(this->_mappingsAreValid());
    }

public:
    /// Mappings.
    const Mappings& mappings() const noexcept
    {
        return _mappings;
    }

    /// Constant mapping iterator set at the first mapping of this type.
    typename Mappings::const_iterator begin() const noexcept
    {
        return _mappings.begin();
    }

    /// Constant mapping iterator set \em after the last mapping of this
    /// type.
    typename Mappings::const_iterator end() const noexcept
    {
        return _mappings.end();
    }

    /*!
    @brief
        Returns the ranges of the mapping named \p name, or \c nullptr
        if not found.

    @param[in] name
        Name of the mapping to find.

    @returns
        Ranges of the mapping named \p name, or \c nullptr if not found.
    */
    const RangeSet *operator[](const std::string& name) const noexcept
    {
        const auto it = _mappings.find(name);

        if (it == _mappings.end()) {
            return nullptr;
        }

        return &it->second;
    }

    /*!
    @brief
        Returns whether or not this type has at least one mapping
        integer range which contains the value \p value.

    @param[in] value
        Value to check.

    @returns
        \c true if this type has at least one mapping integer range
        containing \p value.
    */
    bool hasValue(const ValueT value) const
    {
        for (const auto& nameRangeSetPair : _mappings) {
            if (nameRangeSetPair.second.contains(value)) {
                return true;
            }
        }

        return false;
    }

private:
    bool _mappingsAreValid() noexcept
    {
        if (_mappings.empty()) {
            return false;
        }

        for (const auto& nameRangeSetPair : _mappings) {
            if (nameRangeSetPair.second.ranges().empty()) {
                return false;
            }
        }

        return true;
    }

    bool _isEqual(const DataType& other) const noexcept override
    {
        const auto& otherEnumType = static_cast<const EnumerationType<IntegerTypeParentT, ValueT>&>(other);

        return IntegerTypeParentT::_isEqual(other) && otherEnumType.mappings() == this->mappings();
    }

private:
    const Mappings _mappings;
};

namespace internal {

using SignedEnumerationTypeValue = long long;
using UnsignedEnumerationTypeValue = std::make_unsigned_t<SignedEnumerationTypeValue>;

} // namespace internal

} // namespace yactfr

#endif // _YACTFR_METADATA_ENUM_TYPE_HPP
