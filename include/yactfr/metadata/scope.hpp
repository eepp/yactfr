/*
 * CTF scope.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Scope.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_SCOPE_HPP
#define _YACTFR_METADATA_SCOPE_HPP

namespace yactfr {

/*!
@brief  Scope.

@ingroup metadata
*/
enum class Scope
{
    /// Packet header.
    PACKET_HEADER,

    /// Packet context.
    PACKET_CONTEXT,

    /// Event record's header.
    EVENT_RECORD_HEADER,

    /// Event record's first context.
    EVENT_RECORD_FIRST_CONTEXT,

    /// Event record's second context.
    EVENT_RECORD_SECOND_CONTEXT,

    /// Event record's payload.
    EVENT_RECORD_PAYLOAD,
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SCOPE_HPP
