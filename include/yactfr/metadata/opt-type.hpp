/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_OPT_TYPE_HPP
#define _YACTFR_METADATA_OPT_TYPE_HPP

#include <algorithm>
#include <string>

#include "data-loc.hpp"
#include "var-type-opt.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"
#include "compound-dt.hpp"
#include "../aliases.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

/*!
@brief
    Optional type.

@ingroup metadata_dt

An optional type describes data stream optionals.
*/
class OptionalType :
    public CompoundDataType
{
    friend class internal::TraceTypeImpl;

protected:
    explicit OptionalType(const int kind, const unsigned int minAlign, DataType::UP dt,
                          DataLocation&& selLoc, MapItem::UP userAttrs);

public:
    /// Location of selectors of data stream optionals described by this
    /// type.
    const DataLocation& selectorLocation() const noexcept
    {
        return _selLoc;
    }

    /// Types of selectors of data stream optionals described by this
    /// type, or an empty set if this type is not part of a trace type
    /// yet.
    const DataTypeSet& selectorTypes() const noexcept
    {
        return _theSelTypes;
    }

    /// Type of the data contained by data stream optionals described
    /// by this type.
    const DataType& dataType() const noexcept
    {
        return *_dt;
    }

private:
    bool _isEqual(const DataType& other) const noexcept override;

    DataTypeSet& _selTypes() const noexcept
    {
        return _theSelTypes;
    }

private:
    const DataType::UP _dt;
    const DataLocation _selLoc;
    mutable DataTypeSet _theSelTypes;
};

/*!
@brief
    Type of data stream optionals with a boolean selector.

@ingroup metadata_dt
*/
class OptionalWithBooleanSelectorType :
    public OptionalType
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief
        Builds a type of data stream optionals with a boolean selector.

    @param[in] minimumAlignment
        Minimum alignment of data stream optionals described by this
        type.
    @param[in] dataType
        Type of the data contained by data stream optionals described by
        this type.
    @param[in] selectorLocation
        Location of selectors of data stream optionals described by this
        type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithBooleanSelectorType(unsigned int minimumAlignment, DataType::UP dataType,
                                             DataLocation selectorLocation,
                                             MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a type of data stream optionals with a boolean selector,
        having a default minimum alignment property (1).

    @param[in] dataType
        Type of the data contained by data stream optionals described by
        this type.
    @param[in] selectorLocation
        Location of selectors of data stream optionals described by this
        type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithBooleanSelectorType(DataType::UP dataType, DataLocation selectorLocation,
                                             MapItem::UP userAttributes = nullptr);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Type of data stream optionals with an integer selector.

@ingroup metadata_dt
*/
template <typename SelectorValueT>
class OptionalWithIntegerSelectorType :
    public OptionalType
{
    friend class internal::TraceTypeImpl;

public:
    /// Type of the value of a selector.
    using SelectorValue = SelectorValueT;

    /// Type of the integer range set.
    using SelectorRangeSet = IntegerRangeSet<SelectorValueT>;

protected:
    explicit OptionalWithIntegerSelectorType(int kind, unsigned int minAlign, DataType::UP dt,
                                             DataLocation&& selLoc, SelectorRangeSet&& selRanges,
                                             MapItem::UP userAttrs) :
        OptionalType {kind, minAlign, std::move(dt), std::move(selLoc), std::move(userAttrs)},
        _selRanges {std::move(selRanges)}
    {
    }

public:
    /// Selector range set of this optional type.
    const SelectorRangeSet& selectorRanges() const noexcept
    {
        return _selRanges;
    }

private:
    const SelectorRangeSet _selRanges;
};

/*!
@brief
    Type of data stream optionals with an unsigned integer selector.

@ingroup metadata_dt
*/
class OptionalWithUnsignedIntegerSelectorType :
    public OptionalWithIntegerSelectorType<unsigned long long>
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief
        Builds a type of data stream optionals with an unsigned integer
        selector.

    @param[in] minimumAlignment
        Minimum alignment of data stream optionals described by this
        type.
    @param[in] dataType
        Type of the data contained by data stream optionals described by
        this type.
    @param[in] selectorLocation
        Location of selectors of data stream optionals described by this
        type.
    @param[in] selectorRanges
        Selector range set of this optional type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithUnsignedIntegerSelectorType(unsigned int minimumAlignment,
                                                     DataType::UP dataType,
                                                     DataLocation selectorLocation,
                                                     SelectorRangeSet selectorRanges,
                                                     MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a type of data stream optionals with an unsigned integer
        selector, having a default minimum alignment property (1).

    @param[in] dataType
        Type of the data contained by data stream optionals described by
        this type.
    @param[in] selectorLocation
        Location of selectors of data stream optionals described by this
        type.
    @param[in] selectorRanges
        Selector range set of this optional type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithUnsignedIntegerSelectorType(DataType::UP dataType,
                                                     DataLocation selectorLocation,
                                                     SelectorRangeSet selectorRanges,
                                                     MapItem::UP userAttributes = nullptr);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Type of data stream optionals with a signed integer selector.

@ingroup metadata_dt
*/
class OptionalWithSignedIntegerSelectorType :
    public OptionalWithIntegerSelectorType<long long>
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief
        Builds a type of data stream optionals with a signed integer
        selector.

    @param[in] minimumAlignment
        Minimum alignment of data stream optionals described by this
        type.
    @param[in] dataType
        Type of the data contained by data stream optionals described by
        this type.
    @param[in] selectorLocation
        Location of selectors of data stream optionals described by this
        type.
    @param[in] selectorRanges
        Selector range set of this optional type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithSignedIntegerSelectorType(unsigned int minimumAlignment,
                                                   DataType::UP dataType,
                                                   DataLocation selectorLocation,
                                                   SelectorRangeSet selectorRanges,
                                                   MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a type of data stream optionals with a signed integer
        selector, having a default minimum alignment property (1).

    @param[in] dataType
        Type of the data contained by data stream optionals described by
        this type.
    @param[in] selectorLocation
        Location of selectors of data stream optionals described by this
        type.
    @param[in] selectorRanges
        Selector range set of this optional type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithSignedIntegerSelectorType(DataType::UP dataType,
                                                   DataLocation selectorLocation,
                                                   SelectorRangeSet selectorRanges,
                                                   MapItem::UP userAttributes = nullptr);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_OPT_TYPE_HPP
