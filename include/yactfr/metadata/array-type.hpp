/*
 * CTF array type base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Array type base.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_ARRAY_TYPE_HPP
#define _YACTFR_METADATA_ARRAY_TYPE_HPP

// for CompoundType
#include "compound-type.hpp"

// for DataType
#include "data-type.hpp"

namespace yactfr {

/*!
@brief  %Base class of static/dynamic array types.

@ingroup metadata_dt
*/
class ArrayType :
    public CompoundType
{
protected:
    explicit ArrayType(int kind, unsigned int minAlign, DataType::UP elemType);

public:
    /// Type of element fields contained in data stream arrays
    /// described by this array type.
    const DataType& elemType() const
    {
        return *_elemType;
    }

private:
    const DataType::UP _elemType;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_ARRAY_TYPE_HPP
