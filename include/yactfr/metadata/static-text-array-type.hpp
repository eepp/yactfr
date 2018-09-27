/*
 * CTF static text array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Static text array type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_STATIC_TEXT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_STATIC_TEXT_ARRAY_TYPE_HPP

// for StaticArrayType
#include "static-array-type.hpp"

// for Encoding
#include "encoding.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

// for Size
#include "../aliases.hpp"

namespace yactfr {

/*!
@brief  Static text array type.

@ingroup metadata_dt

A static text array type describes data stream static text arrays.
*/
class StaticTextArrayType final :
    public StaticArrayType
{
public:
    /*!
    @brief  Builds a static text array type.

    @param align    Alignment of data stream static text arrays
                    described by this static text array type (power of
                    two, greater than 7).
    @param encoding Encoding of data stream static text arrays described by
                    this static text array type.
    @param length   Length of data stream static text arrays described
                    by this static text array type (number of elements).

    @throws InvalidMetadata The static text array type is invalid.
    */
    explicit StaticTextArrayType(unsigned int align, Encoding encoding,
                                 Size length);

private:
    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STATIC_TEXT_ARRAY_TYPE_HPP
