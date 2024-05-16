/*
 * Copyright (C) 2015-2021 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_INT_RANGE_SET_HPP
#define YACTFR_METADATA_INT_RANGE_SET_HPP

#include <set>

#include "int-range.hpp"

namespace yactfr {

/*!
@brief
    Integer range set.

@ingroup metadata_dt

An integer range set is a set of
\link IntegerRange integer ranges\endlink.

@tparam ValueT
    Type of the lower and upper values of contained integer ranges.
@tparam ValidatePreconditionsV
    Kindly ignore this parameter which is currently only used internally
    and must remain \c true.
*/
template <typename ValueT, bool ValidatePreconditionsV = true>
class IntegerRangeSet final
{
public:
    /// Type of the lower and upper values of contained integer ranges.
    using Value = ValueT;

    /// Type of the contained integer ranges.
    using Range = IntegerRange<ValueT, ValidatePreconditionsV>;

public:
    /*!
    @brief
        Builds an empty integer range set.
    */
    explicit IntegerRangeSet()
    {
    }

    /*!
    @brief
        Builds an integer range set containing the integer ranges
        \p ranges.

    @param[in] ranges
        Integer ranges of this integer range set.
    */
    explicit IntegerRangeSet(const std::set<Range> ranges) :
        _ranges {std::move(ranges)}
    {
    }

    /// Default copy constructor.
    IntegerRangeSet(const IntegerRangeSet&) = default;

    /// Default move constructor.
    IntegerRangeSet(IntegerRangeSet&&) = default;

    /// Default copy assignment operator.
    IntegerRangeSet& operator=(const IntegerRangeSet&) = default;

    /// Default move assignment operator.
    IntegerRangeSet& operator=(IntegerRangeSet&&) = default;

    /// Ranges of this integer range set.
    const std::set<Range>& ranges() const noexcept
    {
        return _ranges;
    }

    /// Range set iterator at the first range of this set.
    typename std::set<Range>::const_iterator begin() const noexcept
    {
        return _ranges.begin();
    }

    /// Range set iterator \em after the last range of this set.
    typename std::set<Range>::const_iterator end() const noexcept
    {
        return _ranges.end();
    }

    /*!
    @brief
        Returns whether or not this integer range set contains the
        value \p value in at least one of its ranges.

    @param[in] value
        Value to check.

    @returns
        \c true if this integer range set contains \p value in at least
        one of its ranges.
    */
    bool contains(const Value value) const noexcept
    {
        // check all contained ranges
        for (auto& range : _ranges) {
            if (range.contains(value)) {
                return true;
            }
        }

        return false;
    }

    /*!
    @brief
        Returns whether or not at least one range contained in
        \p other intersects with at least one range contained
        in this integer range set.

    @param[in] other
        Other integer range set to check for intersection.

    @returns
        \c true if at least one range contained in \p other intersects
        with at least one range contained in this integer range set.
    */
    bool intersects(const IntegerRangeSet& other) const noexcept
    {
        for (auto& range : _ranges) {
            for (auto& otherRange : other.ranges()) {
                if (range.intersects(otherRange)) {
                    return true;
                }
            }
        }

        return false;
    }

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other integer range set to compare to.

    @returns
        \c true if \p other is equal to this integer range set.
    */
    bool operator==(const IntegerRangeSet& other) const noexcept
    {
        return other.ranges() == _ranges;
    }

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Other integer range set to compare to.

    @returns
        \c true if \p other is not equal to
        this integer range set.
    */
    bool operator!=(const IntegerRangeSet& other) const noexcept
    {
        return !(*this == other);
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other integer range set to compare to.

    @returns
        \c true if this integer range set is less than \p other
        (respects total order).
    */
    bool operator<(const IntegerRangeSet& other) const noexcept
    {
        if (_ranges < other._ranges) {
            return true;
        }

        return false;
    }

private:
    std::set<Range> _ranges;
};

} // namespace yactfr

#endif // YACTFR_METADATA_INT_RANGE_SET_HPP
