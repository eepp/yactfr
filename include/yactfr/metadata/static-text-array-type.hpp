/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_STATIC_TEXT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_STATIC_TEXT_ARRAY_TYPE_HPP

#include "static-array-type.hpp"
#include "dt-visitor.hpp"
#include "../aliases.hpp"

namespace yactfr {

/*!
@brief
    Static text array type.

@ingroup metadata_dt

A static text array type describes data stream static text arrays.
*/
class StaticTextArrayType final :
    public StaticArrayType
{
public:
    /*!
    @brief
        Builds a static text array type.

    @param[in] minimumAlignment
        Minimum alignment of data stream static text arrays described by
        this type.
    @param[in] length
        Length of data stream static text arrays described by this type
        (number of element).

    @pre
        \p minimumAlignment > 0.
    @pre
        \p minimumAlignment is a power of two.
    */
    explicit StaticTextArrayType(unsigned int minimumAlignment, Size length);

private:
    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STATIC_TEXT_ARRAY_TYPE_HPP
