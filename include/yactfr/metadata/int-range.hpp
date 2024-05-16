/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_INT_RANGE_HPP
#define YACTFR_METADATA_INT_RANGE_HPP

#include <cassert>

namespace yactfr {

/*!
@brief
    Integer range.

@ingroup metadata_dt

An integer range is a simple pair of lower and upper values, both
included in the range.

@tparam ValueT
    Type of the lower and upper values.
@tparam ValidatePreconditionsV
    Kindly ignore this parameter which is currently only used internally
    and must remain \c true.
*/
template <typename ValueT, bool ValidatePreconditionsV = true>
class IntegerRange final
{
public:
    /// Type of the lower and upper values.
    using Value = ValueT;

public:
    /*!
    @brief
        Builds an integer range
        [<code>lower</code>,&nbsp;<code>upper</code>].

    @param[in] lower
        Lower value of the integer range (included).
    @param[in] upper
        Upper value of the integer range (included).

    @pre
        \p upper ≥ \p lower.
    */
    explicit IntegerRange(const ValueT lower, const ValueT upper) :
        _lower {lower},
        _upper {upper}
    {
        if (ValidatePreconditionsV) {
            assert(lower <= upper);
        }
    }

    /// Default copy constructor.
    IntegerRange(const IntegerRange&) noexcept = default;

    /// Default copy assignment operator.
    IntegerRange& operator=(const IntegerRange&) noexcept = default;

    /// Lower bound of this integer range.
    ValueT lower() const noexcept
    {
        return _lower;
    }

    /// Upper bound of this integer range.
    ValueT upper() const noexcept
    {
        return _upper;
    }

    /*!
    @brief
        Returns whether or not this integer range contains the value
        \p value.

    @param[in] value
        Value to check.

    @returns
        \c true if this integer range contains \p value.
    */
    bool contains(const ValueT value) const noexcept
    {
        return value >= _lower && value <= _upper;
    }

    /*!
    @brief
        Returns whether or not the integer range \p range intersects
        with this integer range.

    @param[in] range
        Integer range to check for intersection.

    @returns
        \c true if \p range intersects with this integer range.
    */
    bool intersects(const IntegerRange& range) const noexcept
    {
        return _lower <= range.upper() && range.lower() <= _upper;
    }

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other integer range to compare to.

    @returns
        \c true if \p other is equal to this integer range.
    */
    bool operator==(const IntegerRange& other) const noexcept
    {
        return other.lower() == _lower && other.upper() == _upper;
    }

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Other integer range to compare to.

    @returns
        \c true if \p other is not equal to this integer range.
    */
    bool operator!=(const IntegerRange& other) const noexcept
    {
        return !(*this == other);
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other integer range to compare to.

    @returns
        \c true if this integer range is less than \p other (respects
        total order).
    */
    bool operator<(const IntegerRange& other) const noexcept
    {
        if (_lower < other._lower) {
            return true;
        }

        if (other._lower < _lower) {
            return false;
        }

        if (_upper < other._upper) {
            return true;
        }

        return false;
    }

private:
    ValueT _lower;
    ValueT _upper;
};

} // namespace yactfr

#endif // YACTFR_METADATA_INT_RANGE_HPP
