/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FLOAT_TYPE_HPP
#define _YACTFR_METADATA_FLOAT_TYPE_HPP

#include "bit-array-type.hpp"
#include "bo.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

class DataTypeVisitor;

/*!
@brief
    Floating point number type.

@ingroup metadata_dt

A floating point number type describes data stream single-precision and
double-precision floating point numbers.
*/
class FloatingPointNumberType final :
    public BitArrayType
{
public:
    /*!
    @brief
        Builds a floating point number type.

    @param[in] alignment
        Alignment of data stream floating point numbers described by
        this floating point number type.
    @param[in] length
        Length of data stream floating point numbers (bits) described
        by this floating point number type.
    @param[in] byteOrder
        Byte order of data stream floating point numbers described by
        this floating point number type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length is 32 or 64.
    */
    explicit FloatingPointNumberType(unsigned int alignment, unsigned int length,
                                     ByteOrder byteOrder);

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Real type to copy.
    */
    FloatingPointNumberType(const FloatingPointNumberType& other);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FLOAT_TYPE_HPP
