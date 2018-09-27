/*
 * CTF dynamic text array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Dynamic text array type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_DYNAMIC_TEXT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_DYNAMIC_TEXT_ARRAY_TYPE_HPP

// for DynamicArrayType
#include "dynamic-array-type.hpp"

// for Encoding
#include "encoding.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

namespace yactfr {

class FieldRef;

/*!
@brief  Dynamic text array type.

@ingroup metadata_dt

A dynamic text array type describes data stream dynamic text arrays.
*/
class DynamicTextArrayType :
    public DynamicArrayType
{
public:
    /*!
    @brief  Builds a dynamic text array type.

    @param align    Alignment of data stream dynamic text arrays
                    described by this dynamic text array type (power of
                    two, greater than 7).
    @param encoding Encoding of data stream dynamic text arrays
                    described by this dynamic text array type.
    @param length   Field reference of the length of data stream dynamic
                    text arrays described by this dynamic text array
                    type (number of elements).

    @throws InvalidMetadata The dynamic text array type is invalid.
    */
    explicit DynamicTextArrayType(unsigned int align, Encoding encoding,
                                  const FieldRef& length);
private:
    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DYNAMIC_TEXT_ARRAY_TYPE_HPP
