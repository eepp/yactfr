/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_VL_BIT_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_VL_BIT_ARRAY_TYPE_HPP

#include "scalar-dt.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Variable-length bit array type.

@ingroup metadata_dt

A variable-length bit array type describes data stream variable-length
bit arrays.
*/
class VariableLengthBitArrayType :
    public ScalarDataType
{
protected:
    explicit VariableLengthBitArrayType(_Kind kind, unsigned int align, MapItem::UP userAttrs);

public:
    /*!
    @brief
        Builds a variable-length bit array type.

    @param[in] alignment
        Alignment of data stream variable-length bit arrays described by
        this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length bit arrays
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit VariableLengthBitArrayType(unsigned int alignment,
                                        MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a variable-length bit array type having a default
        alignment property (8).

    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length bit arrays
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    */
    explicit VariableLengthBitArrayType(MapItem::UP userAttributes = nullptr);


protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_VL_BIT_ARRAY_TYPE_HPP
