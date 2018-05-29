/*
 * CTF text sequence type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Text sequence type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_TEXT_SEQUENCE_TYPE_HPP
#define _YACTFR_METADATA_TEXT_SEQUENCE_TYPE_HPP

#include "field-ref.hpp"
#include "encoding.hpp"
#include "sequence-type.hpp"

namespace yactfr {

/*!
@brief  Text sequence type.

@ingroup metadata_dt

A text sequence type describes data stream text sequences.
*/
class TextSequenceType :
    public SequenceType
{
public:
    /*!
    @brief  Builds a text sequence type.

    @param align    Alignment of data stream text sequences described by
                    this text sequence type (power of two, greater than
                    7).
    @param encoding Encoding of data stream text sequences described by
                    this text sequence type.
    @param length   Field reference of the length of data stream text
                    sequences described by this text sequence type
                    (number of elements).

    @throws InvalidMetadata The text sequence type is invalid.
    */
    explicit TextSequenceType(unsigned int align, Encoding encoding,
                              const FieldRef& length);
private:
    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_TEXT_SEQUENCE_TYPE_HPP
