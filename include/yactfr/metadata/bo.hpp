/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_BO_HPP
#define YACTFR_METADATA_BO_HPP

namespace yactfr {

/*!
@brief
    Byte order.

@ingroup metadata
*/
enum class ByteOrder
{
    /// Big-endian.
    Big,

    /// Little-endian.
    Little,
};

/*!
@brief
    Bit order.

@ingroup metadata
*/
enum class BitOrder
{
    /// First to last.
    FirstToLast,

    /// Last to first.
    LastToFirst,
};

} // namespace yactfr

#endif // YACTFR_METADATA_BO_HPP
