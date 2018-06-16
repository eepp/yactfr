/*
 * CTF compound type base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Compound type base.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_COMPOUND_TYPE_HPP
#define _YACTFR_METADATA_COMPOUND_TYPE_HPP

// for DataType
#include "data-type.hpp"

namespace yactfr {

/*!
@brief  %Base class of compound types.

@ingroup metadata_dt
*/
class CompoundType :
    public DataType
{
protected:
    explicit CompoundType(int kind, unsigned int align);
};

} // namespace yactfr

#endif // _YACTFR_METADATA_COMPOUND_TYPE_HPP

