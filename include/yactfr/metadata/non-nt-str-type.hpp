/*
 * SPDX-FileCopyrightText: 2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
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
