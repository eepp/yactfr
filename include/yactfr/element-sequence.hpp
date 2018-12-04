/*
 * Element sequence.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Element sequence.

@ingroup element_seq
*/

#ifndef _YACTFR_ELEMENT_SEQUENCE_HPP
#define _YACTFR_ELEMENT_SEQUENCE_HPP

// for std::shared_ptr
#include <memory>

// for ElementSequenceIterator
#include "element-sequence-iterator.hpp"

namespace yactfr {

class DataSourceFactory;
class TraceType;

/*!
@brief  Element sequence.

An element sequence represents a sequence of elements from which you can
create \link ElementSequenceIterator element sequence iterators\endlink.
It is a read-only container of elements (see Element).

Once you create an element sequence iterator with
ElementSequence::begin(), you can seek a packet which is known to be at
a specific offset with ElementSequenceIterator::seekPacket(). You can
also use the ElementSequence::at() helper.
*/
class ElementSequence final
{
public:
    using Iterator = ElementSequenceIterator;

    // for STL compliance: why not
    using iterator = Iterator;

public:
    /*!
    @brief  Builds an element sequence described by the trace type
            \p traceType and of which the iterators create data sources
            with \p dataSourceFactory.

    @param traceType            Trace type which describes the element
                                sequence to create.
    @param dataSourceFactory    Factory of data sources used by the
                                iterators which this element sequence
                                creates.
    */
    explicit ElementSequence(std::shared_ptr<const TraceType> traceType,
                            std::shared_ptr<DataSourceFactory> dataSourceFactory);

    /*!
    @brief  Returns an element sequence iterator at the beginning of
            this element sequence.

    You can destroy the returned iterator before or after this element
    sequence is destroyed.

    The created element sequence iterator creates a new data source from
    this element sequence's data source factory.

    This method can throw any exception that the iterator's data source
    can throw on construction.

    @returns    Element sequence iterator at the beginning of this
                element sequence.

    @throws DataNotAvailable Data is not available now, try again later.
    */
    Iterator begin();

    /*!
    @brief  Returns an element sequence iterator at the end of this
            element sequence, that is, \em after the last element.

    You can destroy the returned iterator before or after this element
    sequence is destroyed.

    @returns    Element sequence iterator at the end of this
                element sequence.
    */
    Iterator end();

    /*!
    @brief  Creates an iterator at the specific offset \p offset (bytes)
            within this element sequence.

    \p offset must be the exact offset of the beginning of a packet,
    that is, immediately after the previous packet's padding bytes, if
    any, or 0.

    This is a utility method which does the following:

    @code
    auto it = this->begin();
    it.seekPacket(offset);
    return it;
    @endcode

    The created element sequence iterator creates a new data source from
    this element sequence's data source factory.

    This method can throw any exception that the iterator's data source
    can throw on construction.

    @param offset   Offset (bytes) of the beginning of a packet within
                    this element sequence.
    @returns        Element sequence iterator at the beginning of the
                    packet at offset \p offset.

    @throws DataNotAvailable Data is not available now, try again later.
    */
    Iterator at(Index offset);

private:
    std::shared_ptr<const TraceType> _traceType;
    std::shared_ptr<DataSourceFactory> _dataSourceFactory;
};

} // namespace yactfr

#endif // _YACTFR_ELEMENT_SEQUENCE_HPP
