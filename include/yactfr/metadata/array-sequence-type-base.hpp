/*
 * CTF array/sequence type base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Array/sequence type base.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_ARRAY_SEQUENCE_TYPE_BASE_HPP
#define _YACTFR_METADATA_ARRAY_SEQUENCE_TYPE_BASE_HPP

#include "compound-type.hpp"

namespace yactfr {

/*!
@brief  %Base class of array and sequence types.

@ingroup metadata_dt
*/
class ArraySequenceTypeBase :
    public CompoundType
{
protected:
    explicit ArraySequenceTypeBase(int kind, unsigned int minAlign,
                                   DataType::UP elemType);

public:
    /// Type of elements fields contained in data stream arrays
    /// described by this compound type.
    const DataType& elemType() const
    {
        return *_elemType;
    }

private:
    const DataType::UP _elemType;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_ARRAY_SEQUENCE_TYPE_BASE_HPP
