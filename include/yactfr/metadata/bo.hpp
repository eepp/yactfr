/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_BO_HPP
#define _YACTFR_METADATA_BO_HPP

namespace yactfr {

/*!
@brief
    Byte order.

@ingroup metadata
*/
enum class ByteOrder
{
    /// Big-endian.
    BIG,

    /// Little-endian.
    LITTLE,
};

} // namespace yactfr

#endif // _YACTFR_METADATA_BO_HPP
