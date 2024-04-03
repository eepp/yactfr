/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_NON_NT_STR_TYPE_HPP
#define YACTFR_METADATA_NON_NT_STR_TYPE_HPP

#include "str-type.hpp"
#include "dt.hpp"

namespace yactfr {

/*!
@brief
    %Base class of static-length and dynamic-length string types.

@ingroup metadata_dt
*/
class NonNullTerminatedStringType :
    public StringType
{
protected:
    explicit NonNullTerminatedStringType(_tKind kind, unsigned int align, StringEncoding encoding,
                                         MapItem::Up attrs);
};

} // namespace yactfr

#endif // YACTFR_METADATA_NON_NT_STR_TYPE_HPP
