/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_SCOPE_HPP
#define _YACTFR_METADATA_SCOPE_HPP

namespace yactfr {

/*!
@brief
    Scope.

@ingroup metadata_dt
*/
enum class Scope
{
    /// Packet header.
    PACKET_HEADER,

    /// Packet context.
    PACKET_CONTEXT,

    /// Event record header.
    EVENT_RECORD_HEADER,

    /// Event record common context.
    EVENT_RECORD_COMMON_CONTEXT,

    /// Event record specific context.
    EVENT_RECORD_SPECIFIC_CONTEXT,

    /// Event record payload.
    EVENT_RECORD_PAYLOAD,
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SCOPE_HPP
