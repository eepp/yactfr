/*
 * CTF text array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Text array type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_TEXT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_TEXT_ARRAY_TYPE_HPP

#include "array-type.hpp"
#include "int-type.hpp"

namespace yactfr {

/*!
@brief  Text array type.

@ingroup metadata_dt

A text array type describes data stream text arrays.
*/
class TextArrayType final :
    public ArrayType
{
public:
    /*!
    @brief  Builds a text array type.

    @param align    Alignment of data stream text arrays described by
                    this text array type (power of two, greater than 7).
    @param encoding Encoding of data stream text arrays described by
                    this text array type.
    @param length   Length of data stream text arrays described by this
                    text array type (number of elements).

    @throws InvalidMetadata The text array type is invalid.
    */
    explicit TextArrayType(unsigned int align, Encoding encoding, Size length);

private:
    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_TEXT_ARRAY_TYPE_HPP
