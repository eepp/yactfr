/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DL_STR_TYPE_HPP
#define _YACTFR_METADATA_DL_STR_TYPE_HPP

#include <memory>
#include <utility>

#include "non-nt-str-type.hpp"
#include "data-loc.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

/*!
@brief
    Dynamic-length string type.

@ingroup metadata_dt

A dynamic-length string type describes data stream dynamic-length
strings.
*/
class DynamicLengthStringType final :
    public NonNullTerminatedStringType
{
    friend class internal::TraceTypeImpl;

public:
    /// Unique pointer to constant dynamic-length string type.
    using UP = std::unique_ptr<const DynamicLengthStringType>;

public:
    /*!
    @brief
        Builds a dynamic-length string type.

    @param[in] alignment
        Alignment of data stream dynamic-length strings described by
        this type.
    @param[in] maximumLengthLocation
        Location of maximum lengths (UTF-8 bytes) of data stream
        dynamic-length strings described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream dynamic-length strings described
        by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit DynamicLengthStringType(unsigned int alignment, DataLocation maximumLengthLocation,
                                     MapItem::UP userAttributes = nullptr);


    /*!
    @brief
        Builds a dynamic-length string type having a default
        alignment property (8).

    @param[in] maximumLengthLocation
        Location of maximum lengths (UTF-8 bytes) of data stream
        dynamic-length strings described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream dynamic-length strings described
        by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    */
    explicit DynamicLengthStringType(DataLocation maximumLengthLocation,
                                     MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a constant dynamic-length string type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the dynamic-length string type
        constructor.

    @returns
        Created constant dynamic-length string type unique pointer.

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
        Location of maximum lengths (UTF-8 bytes) of data stream
        dynamic-length strings described by this type.
    */
    const DataLocation& maximumLengthLocation() const noexcept
    {
        return _maxLenLoc;
    }

    /*!
    @brief
        Types of maximum lengths of data stream dynamic-length strings
        described by this type, or an empty set if this type is not part
        of a trace type yet.
    */
    const DataTypeSet& maximumLengthTypes() const noexcept
    {
        return _theMaxLenTypes;
    }

private:
    DataType::UP _clone() const override;
    bool _isEqual(const DataType& other) const noexcept override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    DataTypeSet& _maxLenTypes() const noexcept
    {
        return _theMaxLenTypes;
    }

private:
    const DataLocation _maxLenLoc;
    mutable DataTypeSet _theMaxLenTypes;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DL_STR_TYPE_HPP
