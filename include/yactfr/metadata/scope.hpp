/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
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
