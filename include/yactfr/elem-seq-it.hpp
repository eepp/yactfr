/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ELEM_SEQ_IT_HPP
#define _YACTFR_ELEM_SEQ_IT_HPP

#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>

#include "elem-seq-it-pos.hpp"
#include "aliases.hpp"

namespace yactfr {
namespace internal {

class Vm;

} // namespace internal

class Element;
class DataSourceFactory;
class TraceType;

/*!
@brief
    Element sequence iterator.

@ingroup element_seq

Use ElementSequence::begin(), ElementSequence::end(), or
ElementSequence::at() to create an element sequence iterator.
*/
class ElementSequenceIterator final
{
    friend class ElementSequence;
    friend class internal::Vm;

public:
    // for STL to be happy
    using difference_type = std::ptrdiff_t;
    using value_type = const Element;
    using reference = const Element&;
    using pointer = const Element *;
    using iterator_category = std::input_iterator_tag;

private:
    explicit ElementSequenceIterator(DataSourceFactory& dataSrcFactory,
                                     const TraceType& traceType, bool end);

private:
    static const Index _END_OFFSET;

public:
    /*!
    @brief
        Copy constructor.

    The created element sequence iterator creates a new data source from
    the data source factory of its element sequence. See savePosition()
    and restorePosition() for an alternative which can save and restore
    element sequence iterator positions without creating new data
    sources.

    @param[in] other
        Element sequence iterator to copy.

    @post
        The created element sequence iterator is at the same position
        that \p other is.

    @throws ?
        Any exception that the data source can throw on construction.
    @throws DataNotAvailable
        Data is not available now from the data source: try again later.
    */
    ElementSequenceIterator(const ElementSequenceIterator& other);

    /*!
    @brief
        Move constructor.

    @param[in] other
        Element sequence iterator to move.

    @post
        \p other is set at the end of its element sequence
        (ElementSequence::end()).
    @post
        This element sequence iterator is at the same position that \p
        other was before being moved.
    @post
        The current element of \p other, if any, is invalidated.
    */
    ElementSequenceIterator(ElementSequenceIterator&& other);

    // required because internal::Vm has no known size at this point
    ~ElementSequenceIterator();

    /*!
    @brief
        Sets this element sequence iterator to a copy of \p other.

    This element sequence iterator creates a new data source from the
    data source factory of its element sequence. See savePosition() and
    restorePosition() for an alternative which can save and restore
    element sequence iterator positions without creating new data
    sources.

    @param[in] other
        Other element sequence iterator to copy.

    @returns
        This element sequence iterator.

    @post
        This element sequence iterator is at the same position that
        \p other is, and it is fully independent from \p other.

    @throws ?
        Any exception that the data source can throw on construction.

    @throws DataNotAvailable
        Data is not available now from the data source: try again later.
    */
    ElementSequenceIterator& operator=(const ElementSequenceIterator& other);

    /*!
    @brief
        Moves \p other as this element sequence iterator, and sets
        \p other to the end of its element sequence.

    @param[in] other
        Other element sequence iterator to move.

    @returns
        This element sequence iterator.

    @post
        \p other is set at the end of its element sequence
        (ElementSequence::end()).
    @post
        This element sequence iterator is at the same position that
        \p other was before being moved.
    @post
        The current element of \p other, if any, is invalidated.
    */
    ElementSequenceIterator& operator=(ElementSequenceIterator&& other);

    /*!
    @brief
        Advances this element sequence iterator to the next element.

    @returns
        This element sequence iterator.

    @post
        The current element of this iterator is invalidated.

    @throws ?
        Any exception that the data source can throw when getting a new
        data block.
    @throws DecodingError
        Any derived decoding error (see decoding-errors.hpp): advancing
        led to a decoding error.
    @throws DataNotAvailable
        Data is not available now from the data source: try again later.
    */
    ElementSequenceIterator& operator++();

    /*!
    @brief
        Returns the current element of this element sequence iterator.

    The returned element remains valid as long as:

    -# The element sequence of this iterator exists.
    -# You do not call operator++(), seekPacket(), or restorePosition()
       on this iterator, \em or you do not move this iterator
       (move constructor or move assignment operator).

    @returns
        Current element of this iterator.

    @pre
        This iterator is not equal to ElementSequence::end() on the
        element sequence which created this iterator.
    */
    reference operator*() const noexcept
    {
        assert(_curElem);
        assert(_offset < _END_OFFSET);
        return *_curElem;
    }

    pointer operator->() const
    {
        return _curElem;
    }

    /*!
    @brief
        Returns the current offset, in bits, of the current element
        of this element sequence iterator.

    The current offset is the offset, within the element sequence of the
    iterator, of the first bit of the current element of the iterator.
    It is possible that two consecutive elements have the same offset,
    as not all elements are data elements (for example, an
    FixedLengthUnsignedIntegerElement followed by a PacketMagicNumberElement would
    have the same offset).

    @returns
        Current offset (bits) of the element of this element sequence
        iterator within its element sequence.

    @pre
        This iterator is not equal to ElementSequence::end() on the
        element sequence which created this iterator.
    */
    Index offset() const noexcept
    {
        return _offset;
    }

    /*!
    @brief
        Seeks the beginning of a packet, in the same element sequence,
        known to be located at offset \p offset (bytes).

    @param[in] offset
        Offset, in bytes, of the first byte of a packet within the same
        element sequence.

    @pre
        \p offset corresponds to the very first byte of a packet within
        the same element sequence.

    @post
        The current element of this iterator is invalidated.

    @throws ?
        Any exception that the data source can throw when getting a new
        data block.
    @throws DataNotAvailable
        Data is not available now from the data source: try again later.
    */
    void seekPacket(Index offset);

    /*!
    @brief
        Saves the position of this element sequence iterator
        into \p pos.

    This operation makes it possible to save many positions of the same
    iterator \em without creating new data sources (which
    the \link ElementSequenceIterator(const ElementSequenceIterator&) copy
    constructor\endlink and
    \link operator=(const ElementSequenceIterator&) copy assignment
    operator\endlink do).

    You can restore the position of this iterator, or another iterator
    created from the same element sequence, from \p pos with
    restorePosition().

    @param[in] pos
        Position to set.

    @pre
        This iterator is not equal to ElementSequence::end() on the
        element sequence which created this iterator.
    */
    void savePosition(ElementSequenceIteratorPosition& pos) const;

    /*!
    @brief
        Restores the position of this element sequence iterator from
        \p pos.

    @note
        \p pos is still valid after calling this method: you can use it
        to restore the position of this element sequence iterator, or
        another iterator created from the same element sequence, again.

    @param[in] pos
        Position to use to restore the position of this iterator.

    @pre
        \p pos was previously set with savePosition().
    */
    void restorePosition(const ElementSequenceIteratorPosition& pos);

    /*!
    @brief
        Equality operator.

    Two element sequence iterators are considered equal if they are at
    the same element sequence element or if both are
    ElementSequence::end().

    @param[in] other
        Element sequence iterator to compare to.

    @returns
        \c true if this element sequence iterator is equal to \p other.

    @pre
        This element sequence iterator and \p other \em must have been
        created by the \em same element sequence.
    */
    bool operator==(const ElementSequenceIterator& other) const noexcept
    {
        return _offset == other._offset && _mark == other._mark;
    }

    /*!
    @brief
        Non-equality operator.

    Two element sequence iterators are considered equal if they are at
    the same element sequence element or if both are
    ElementSequence::end().

    @param[in] other
        Element sequence iterator to compare to.

    @returns
        \c true if this element sequence iterator is \em not equal
        to \p other.

    @pre
        This element sequence iterator and \p other \em must have been
        created by the \em same element sequence.
    */
    bool operator!=(const ElementSequenceIterator& other) const noexcept
    {
        return _offset != other._offset || _mark != other._mark;
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Element sequence iterator to compare to.

    @returns
        \c true if this element sequence iterator is before \p other.

    @pre
        This element sequence iterator and \p other \em must have been
        created by the \em same element sequence.
    */
    bool operator<(const ElementSequenceIterator& other) const noexcept
    {
        return _offset < other._offset || (_offset == other._offset && _mark < other._mark);
    }

    /*!
    @brief
        Less-than or equality operator.

    Two element sequence iterators are considered equal if they are at
    the same element sequence element or if both are
    ElementSequence::end().

    @param[in] other
        Element sequence iterator to compare to.

    @returns
        \c true if this element sequence iterator is before or equal
        to \p other.

    @pre
        This element sequence iterator and \p other \em must have been
        created by the \em same element sequence.
    */
    bool operator<=(const ElementSequenceIterator& other) const noexcept
    {
        return _offset < other._offset || (_offset == other._offset && _mark <= other._mark);
    }

    /*!
    @brief
        Greater-than operator.

    @param[in] other
        Element sequence iterator to compare to.

    @returns
        \c true if this element sequence iterator is after \p other.

    @pre
        This element sequence iterator and \p other \em must have been
        created by the \em same element sequence.
    */
    bool operator>(const ElementSequenceIterator& other) const noexcept
    {
        return _offset > other._offset || (_offset == other._offset && _mark > other._mark);
    }

    /*!
    @brief
        Greater-than or equality operator.

    Two element sequence iterators are considered equal if they are at
    the same element sequence element or if both are
    ElementSequence::end().

    @param[in] other
        Element sequence iterator to compare to.

    @returns
        \c true if this element sequence iterator is after or equal
        to \p other.

    @pre
        This element sequence iterator and \p other \em must have been
        created by the \em same element sequence.
    */
    bool operator>=(const ElementSequenceIterator& other) const noexcept
    {
        return _offset > other._offset || (_offset == other._offset && _mark >= other._mark);
    }

private:
    void _resetOther(ElementSequenceIterator& other);

private:
    DataSourceFactory *_dataSrcFactory;
    const TraceType *_traceType;
    std::unique_ptr<internal::Vm> _vm;

    // current element
    const Element *_curElem = nullptr;

    // current offset within element sequence; _END_OFFSET means ended
    Index _offset = 0;

    /*
     * Current mark within current packet.
     *
     * This is internal, that is, it's not publicly available.
     *
     * The mark is the index of the current element within its packet.
     * It's used to preserve total ordering when two different elements
     * are at the same element sequence offset, for example
     * ScopeBeginningElement followed with StructureBeginningElement. In
     * this case, an iterator with StructureBeginningElement as its
     * current element would have a greater mark then another iterator
     * with ScopeBeginningElement as its current element, even if both
     * iterators have their offset() method return the same value. Then,
     * for both iterators, ordering operators work as expected.
     *
     * The mark is reset to 0 when the current element is
     * PacketBeginningElement, because two different packets within the
     * same element sequence cannot be at the same offset anyway (yactfr
     * reads packets of at least one byte and with a length (in bits)
     * that's a multiple of 8.
     */
    Index _mark = 0;
};

} // namespace yactfr

#endif // _YACTFR_ELEM_SEQ_IT_HPP
