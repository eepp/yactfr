/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DYN_TEXT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_DYN_TEXT_ARRAY_TYPE_HPP

#include "dyn-array-type.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Dynamic text array type.

@ingroup metadata_dt

A dynamic text array type describes data stream dynamic text arrays.
*/
class DynamicTextArrayType final :
    public DynamicArrayType
{
public:
    /*!
    @brief
        Builds a dynamic text array type.

    @param[in] minimumAlignment
        Minimum alignment of data stream dynamic text arrays described
        by this type.
    @param[in] lengthLocation
        Location of lengths of data stream dynamic text arrays described
        by this type (number of elements).

    @pre
        \p minimumAlignment is a power of two.
    */
    explicit DynamicTextArrayType(unsigned int minimumAlignment, DataLocation lengthLocation);

private:
    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DYN_TEXT_ARRAY_TYPE_HPP
