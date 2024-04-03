/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_SCOPE_HPP
#define YACTFR_METADATA_SCOPE_HPP

namespace yactfr {

/*!
@brief
    Scope.

@ingroup metadata_dt
*/
enum class Scope
{
    /// Packet header.
    PacketHeader,

    /// Packet context.
    PacketContext,

    /// Event record header.
    EventRecordHeader,

    /// Event record common context.
    EventRecordCommonContext,

    /// Event record specific context.
    EventRecordSpecificContext,

    /// Event record payload.
    EventRecordPayload,
};

} // namespace yactfr

#endif // YACTFR_METADATA_SCOPE_HPP
