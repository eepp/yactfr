/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DL_STR_TYPE_HPP
#define _YACTFR_METADATA_DL_STR_TYPE_HPP

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
    /*!
    @brief
        Builds a dynamic-length string type.

    @param[in] alignment
        Alignment of data stream dynamic-length strings described by
        this type.
    @param[in] maximumLengthLocation
        Location of maximum lengths (bytes) of data stream
        dynamic-length strings described by this type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit DynamicLengthStringType(unsigned int alignment, DataLocation maximumLengthLocation);

    /// Location of maximum lengths (bytes) of data stream
    /// dynamic-length strings described by this type.
    const DataLocation& maximumLengthLocation() const noexcept
    {
        return _maxLenLoc;
    }

    /// Types of maximum lengths of data stream dynamic-length strings
    /// described by this type, or an empty set if this type is not part
    /// of a trace type yet.
    const DataTypeSet& maximumLengthTypes() const noexcept
    {
        return _theMaxLenTypes;
    }

private:
    DataType::UP _clone() const override;
    bool _compare(const DataType& other) const noexcept override;

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
