/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ELEM_SEQ_HPP
#define _YACTFR_ELEM_SEQ_HPP

#include <memory>

#include "elem-seq-it.hpp"

namespace yactfr {

class DataSourceFactory;
class TraceType;

/*!
@brief
    Element sequence.

@ingroup element_seq

An element sequence represents a sequence of elements from which you can
create \link ElementSequenceIterator element sequence iterators\endlink.
It is a read-only container of \link Element elements\endlink.

Once you create an element sequence iterator with
ElementSequence::begin(), you can seek a packet which is known to be at
a specific offset with ElementSequenceIterator::seekPacket(). You can
also use the ElementSequence::at() helper.
*/
class ElementSequence final
{
public:
    /// Element sequence iterator type.
    using Iterator = ElementSequenceIterator;

    /// For STL compliance.
    using iterator = Iterator;

public:
    /*!
    @brief
        Builds an element sequence described by the trace type
        \p traceType and of which the iterators create data sources
        with \p dataSourceFactory.

    \p traceType and \p dataSourceFactory must exist as long as this
    element sequence, or any \link ElementSequenceIterator element
    sequence iterator\endlink created from this element sequence,
    exists.

    @param[in] traceType
        Trace type which describes the element sequence to create.
    @param[in] dataSourceFactory
        Factory of data sources used by the iterators which this element
        sequence creates.
    */
    explicit ElementSequence(const TraceType& traceType, DataSourceFactory& dataSourceFactory);

    /*!
    @brief
        Returns an element sequence iterator at the beginning of this
        element sequence.

    You can destroy the returned iterator before or after this element
    sequence is destroyed.

    The created element sequence iterator creates a new data source from
    the data source factory of this element sequence.

    @returns
        Element sequence iterator at the beginning of this element
        sequence.

    @throws ?
        Any exception that the data source of the iterator can throw on
        construction.
    @throws DataNotAvailable
        Data is not available now; try again later.
    */
    Iterator begin();

    /*!
    @brief
        Returns an element sequence iterator at the end of this element
        sequence, that is, \em after the last element.

    You can destroy the returned iterator before or after this element
    sequence is destroyed.

    @returns
        Element sequence iterator at the end of this element sequence.
    */
    Iterator end() noexcept;

    /*!
    @brief
        Creates an iterator at the specific offset \p offset (bytes)
        within this element sequence.

    This is a utility method which does the following:

    @code
    auto it = this->begin();
    it.seekPacket(offset);
    return it;
    @endcode

    The created element sequence iterator creates a new data source from
    the data source factory of this element sequence.

    @param[in] offset
        Offset (bytes) of the beginning of a packet within this element
        sequence.
    @returns
        Element sequence iterator at the beginning of the packet at
        offset \p offset.

    @pre
        \p offset corresponds to the very first byte of a packet.

    @throws ?
        Any exception that the data source of this iterator can throw on
        construction.
    @throws DataNotAvailable
        Data is not available now; try again later.
    */
    Iterator at(Index offset);

private:
    const TraceType *_traceType;
    DataSourceFactory *_dataSrcFactory;
};

} // namespace yactfr

#endif // _YACTFR_ELEM_SEQ_HPP
