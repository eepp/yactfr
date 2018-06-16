/*
 * CTF sequence type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Sequence type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_SEQUENCE_TYPE_HPP
#define _YACTFR_METADATA_SEQUENCE_TYPE_HPP

// for ArraySequenceTypeBase
#include "array-sequence-type-base.hpp"

// for FieldRef
#include "field-ref.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

namespace yactfr {

class DataType;

/*!
@brief  Sequence type.

@ingroup metadata_dt

A sequence type describes data stream sequences.
*/
class SequenceType :
    public ArraySequenceTypeBase
{
public:
    /*!
    @brief  Builds a sequence type.

    @param minAlign Minimal alignment of data stream sequences
                    described by this structure type (power of two,
                    greater than 0).
    @param elemType Element's type.
    @param length   Field reference of the length of data stream
                    sequences described by this sequence type (number of
                    elements).

    @throws InvalidMetadata The sequence type is invalid.
    */
    explicit SequenceType(unsigned int minAlign, DataType::UP elemType,
                          const FieldRef& length);

protected:
    explicit SequenceType(int kind, unsigned int minAlign,
                          DataType::UP elemType, const FieldRef& length);

public:
    /*!
    @brief  Field reference of the length of data stream sequences
            described by this sequence type (number of elements).
    */
    const FieldRef& length() const noexcept
    {
        return _length;
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& otherType) const override;

private:
    const FieldRef _length;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SEQUENCE_TYPE_HPP
