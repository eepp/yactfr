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
#include <memory>
#include <utility>

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
    explicit OptionalType(_Kind kind, const unsigned int minAlign, DataType::UP dt,
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
    /// Unique pointer to constant type of data stream optionals
    /// with a boolean selector.
    using UP = std::unique_ptr<const OptionalWithBooleanSelectorType>;

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
        \p dataType is set.
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
        \p dataType is set.
    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithBooleanSelectorType(DataType::UP dataType, DataLocation selectorLocation,
                                             MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a unique pointer to constant type of data stream
        optionals with a boolean selector, forwarding \p args to the
        constructor.

    @param[in] args
        Arguments to forward to the constructor of the type of data
        stream optionals with a boolean selector.

    @returns
        Created unique pointer to constant type of data stream optionals
        with a boolean selector.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

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

    /// Type of the selector range set.
    using SelectorRangeSet = IntegerRangeSet<SelectorValueT>;

protected:
    explicit OptionalWithIntegerSelectorType(_Kind kind, unsigned int minAlign, DataType::UP dt,
                                             DataLocation&& selLoc, SelectorRangeSet&& selRanges,
                                             MapItem::UP userAttrs) :
        OptionalType {kind, minAlign, std::move(dt), std::move(selLoc), std::move(userAttrs)},
        _selRanges {std::move(selRanges)}
    {
    }

public:
    /// Selector values for which an instance of this type is enabled.
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
    /// Unique pointer to constant type of data stream optionals
    /// with an unsigned integer selector.
    using UP = std::unique_ptr<const OptionalWithUnsignedIntegerSelectorType>;

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
        Selector values for which an instance of this type is enabled.
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
        \p dataType is set.
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
        Selector values for which an instance of this type is enabled.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p dataType is set.
    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithUnsignedIntegerSelectorType(DataType::UP dataType,
                                                     DataLocation selectorLocation,
                                                     SelectorRangeSet selectorRanges,
                                                     MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a unique pointer to constant type of data stream
        optionals with an unsigned integer selector, forwarding \p args
        to the constructor.

    @param[in] args
        Arguments to forward to the constructor of the type of data
        stream optionals with an unsigned integer selector.

    @returns
        Created unique pointer to constant type of data stream optionals
        with an unsigned integer selector.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

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
    /// Unique pointer to constant type of data stream optionals
    /// with a signed integer selector.
    using UP = std::unique_ptr<const OptionalWithSignedIntegerSelectorType>;

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
        Selector values for which an instance of this type is enabled.
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
        \p dataType is set.
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
        Selector values for which an instance of this type is enabled.
    @param[in] userAttributes
        @parblock
        User attributes of data stream optionals described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p dataType is set.
    @pre
        \p selectorLocation only locates booleans.
    */
    explicit OptionalWithSignedIntegerSelectorType(DataType::UP dataType,
                                                   DataLocation selectorLocation,
                                                   SelectorRangeSet selectorRanges,
                                                   MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a unique pointer to constant type of data stream
        optionals with a signed integer selector, forwarding \p args
        to the constructor.

    @param[in] args
        Arguments to forward to the constructor of the type of data
        stream optionals with a signed integer selector.

    @returns
        Created unique pointer to constant type of data stream optionals
        with a signed integer selector.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_OPT_TYPE_HPP
