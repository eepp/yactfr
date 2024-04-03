/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_SCALAR_DT_HPP
#define YACTFR_METADATA_SCALAR_DT_HPP

#include "dt.hpp"

namespace yactfr {

/*!
@brief
    %Base class of scalar data types.

@ingroup metadata_dt

A scalar data type doesn't contain another data type.
*/
class ScalarDataType :
    public DataType
{
protected:
    explicit ScalarDataType(_tKind kind, unsigned int align, MapItem::Up attrs);
};

} // namespace yactfr

#endif // YACTFR_METADATA_SCALAR_DT_HPP
