/*
 * Packet sequence.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Packet sequence.

@ingroup packet_seq
*/

#ifndef _YACTFR_PACKET_SEQUENCE_HPP
#define _YACTFR_PACKET_SEQUENCE_HPP

// for std::shared_ptr
#include <memory>

// for PacketSequenceIterator
#include "packet-sequence-iterator.hpp"

namespace yactfr {

class DataSourceFactory;
class TraceType;

/*!
@brief  Packet sequence.

A packet sequence represents a sequence of packets from which you can
create \link PacketSequenceIterator packet sequence iterators\endlink.
It is a read-only container of packet elements (see Element).

Once you create a packet sequence iterator with PacketSequence::begin(),
you can seek a packet which is known to be at a specific offset with
PacketSequenceIterator::seekPacket(). You can also use the
PacketSequence::at() helper.
*/
class PacketSequence final
{
public:
    using Iterator = PacketSequenceIterator;

    // for STL compliance: why not
    using iterator = Iterator;

public:
    /*!
    @brief  Builds a packet sequence described by the trace type
            \p traceType and of which the iterators create data sources
            with \p dataSourceFactory.

    @param traceType            Trace type which describes the packet
                                sequence to create.
    @param dataSourceFactory    Factory of data sources used by the
                                iterators which this packet sequence
                                creates.
    */
    explicit PacketSequence(std::shared_ptr<const TraceType> traceType,
                            std::shared_ptr<DataSourceFactory> dataSourceFactory);

    /*!
    @brief  Returns a packet sequence iterator at the beginning of this
            packet sequence.

    You can destroy the returned iterator before or after this packet
    sequence is destroyed.

    The created packet sequence iterator creates a new data source from
    this packet sequence's data source factory.

    This method can throw any exception that the iterator's data source
    can throw on construction.

    @returns    Packet sequence iterator at the beginning of this
                packet sequence.

    @throws DataNotAvailable Data is not available now, try again later.
    */
    Iterator begin();

    /*!
    @brief  Returns a packet sequence iterator at the end of this packet
            sequence, that is, \em after the last element.

    You can destroy the returned iterator before or after this packet
    sequence is destroyed.

    @returns    Packet sequence iterator at the end of this
                packet sequence.
    */
    Iterator end();

    /*!
    @brief  Creates an iterator at the specific offset \p offset (bytes)
            within this packet sequence.

    \p offset must be the exact offset of the beginning of a packet,
    that is, immediately after the previous packet's padding bytes, if
    any, or 0.

    This is a utility method which does the following:

    @code
    auto it = this->begin();
    it.seekPacket(offset);
    return it;
    @endcode

    The created packet sequence iterator creates a new data source from
    this packet sequence's data source factory.

    This method can throw any exception that the iterator's data source
    can throw on construction.

    @param offset   Offset (bytes) of the beginning of a packet within
                    this packet sequence.
    @returns        Packet sequence iterator at the beginning of the
                    packet at offset \p offset.

    @throws DataNotAvailable Data is not available now, try again later.
    */
    Iterator at(Index offset);

private:
    std::shared_ptr<const TraceType> _traceType;
    std::shared_ptr<DataSourceFactory> _dataSourceFactory;
};

} // namespace yactfr

#endif // _YACTFR_PACKET_SEQUENCE_HPP
