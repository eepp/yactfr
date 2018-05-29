/*
 * CTF scalar type base.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Scalar type base.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_SCALAR_TYPE_HPP
#define _YACTFR_METADATA_SCALAR_TYPE_HPP

#include "data-type.hpp"

namespace yactfr {

/*!
@brief  %Base class of scalar types.

@ingroup metadata_dt
*/
class ScalarType :
    public DataType
{
protected:
    explicit ScalarType(int kind, unsigned int align);
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SCALAR_TYPE_HPP

