/*
 * CTF byte order.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Byte order.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_BYTE_ORDER_HPP
#define _YACTFR_METADATA_BYTE_ORDER_HPP

namespace yactfr {

/*!
@brief  Byte order.

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

#endif // _YACTFR_METADATA_BYTE_ORDER_HPP
