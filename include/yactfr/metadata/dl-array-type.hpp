/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DL_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_DL_ARRAY_TYPE_HPP

#include <memory>
#include <utility>

#include "array-type.hpp"
#include "data-loc.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

class DataType;

/*!
@brief
    Dynamic-length array type.

@ingroup metadata_dt

A dynamic-length array type describes data stream dynamic-length arrays.
*/
class DynamicLengthArrayType final :
    public ArrayType
{
    friend class internal::TraceTypeImpl;

public:
    /// Unique pointer to constant dynamic-length array type.
    using UP = std::unique_ptr<const DynamicLengthArrayType>;

public:
    /*!
    @brief
        Builds a dynamic-length array type.

    @param[in] minimumAlignment
        Minimum alignment of data stream dynamic-length arrays described
        by this type.
    @param[in] elementType
        %Element type.
    @param[in] lengthLocation
        Location of lengths of data stream dynamic-length arrays
        described by this type (number of elements).
    @param[in] attributes
        @parblock
        Attributes of data stream dynamic-length arrays described
        by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    @pre
        \p elementType is set.
    @pre
        \p lengthLocation only locates unsigned integers.
    */
    explicit DynamicLengthArrayType(unsigned int minimumAlignment, DataType::UP elementType,
                                    DataLocation lengthLocation,
                                    MapItem::UP attributes = nullptr);

    /*!
    @brief
        Builds a dynamic-length array type having a default minimum
        alignment property (1).

    @param[in] elementType
        %Element type.
    @param[in] lengthLocation
        Location of lengths of data stream dynamic-length arrays
        described by this type (number of elements).
    @param[in] attributes
        @parblock
        Attributes of data stream dynamic-length arrays described
        by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p elementType is set.
    @pre
        \p lengthLocation only locates unsigned integers.
    */
    explicit DynamicLengthArrayType(DataType::UP elementType, DataLocation lengthLocation,
                                    MapItem::UP attributes = nullptr);

    /*!
    @brief
        Creates a constant dynamic-length array type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the dynamic-length array type
        constructor.

    @returns
        Created constant dynamic-length array type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

    /*!
    @brief
        Location of lengths of data stream dynamic-length arrays
        described by this type.
    */
    const DataLocation& lengthLocation() const noexcept
    {
        return _lenLoc;
    }

    /*!
    @brief
        Types of lengths of data stream dynamic-length arrays described
        by this type, or an empty set if this type is not part of a
        trace type yet.
    */
    const DataTypeSet& lengthTypes() const noexcept
    {
        return _theLenTypes;
    }

private:
    DataType::UP _clone() const override;
    bool _isEqual(const DataType& other) const noexcept override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    DataTypeSet& _lenTypes() const noexcept
    {
        return _theLenTypes;
    }

private:
    const DataLocation _lenLoc;
    mutable DataTypeSet _theLenTypes;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DL_ARRAY_TYPE_HPP
