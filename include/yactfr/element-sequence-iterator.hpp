/*
 * Element sequence iterator.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Element sequence iterator.

@ingroup element_seq
*/

#ifndef _YACTFR_ELEMENT_SEQUENCE_ITERATOR_HPP
#define _YACTFR_ELEMENT_SEQUENCE_ITERATOR_HPP

// for assert
#include <cassert>

// for std::ptrdiff_t
#include <cstddef>

// for std::input_iterator_tag
#include <iterator>

// for std::shared_ptr, std::unique_ptr
#include <memory>

// for ElementSequenceIteratorPosition
#include "element-sequence-iterator-position.hpp"

// for Index
#include "aliases.hpp"

namespace yactfr {
namespace internal {

    class Vm;

} // namespace internal

class Element;
class DataSourceFactory;
class TraceType;

/*!
@brief  Element sequence iterator.

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
    explicit ElementSequenceIterator(std::shared_ptr<DataSourceFactory> dataSourceFactory,
                                     std::shared_ptr<const TraceType> traceType,
                                     bool end);

private:
    static constexpr Index _END_OFFSET = static_cast<Index>(~0ULL);

public:
    /*!
    @brief  Copy constructor.

    The created element sequence iterator is at the same position that
    \p other is.

    The created element sequence iterator creates a new data source from
    its element sequence's data source factory. See savePosition() and
    restorePosition() for a mechanism which can save and restore element
    sequence iterator positions without creating new data sources.

    This method can throw any exception that the data source can throw
    on construction.

    @param other    Element sequence iterator to copy.

    @throws DataNotAvailable    Data is not available now from the
                                data source: try again later.
    */
    ElementSequenceIterator(const ElementSequenceIterator& other);

    /*!
    @brief  Move constructor.

    Once you move \p other, it is set at the end of its element sequence
    (ElementSequence::end()). This element sequence iterator is at the
    same position that \p other was before being moved.

    This move constructor invalidates the current element of \p other,
    if any.

    @param other    Element sequence iterator to move.
    */
    ElementSequenceIterator(ElementSequenceIterator&& other);

    // required because internal::Vm has no known size at this point
    ~ElementSequenceIterator();

    /*!
    @brief  Sets this element sequence iterator to a copy of \p other.

    This element sequence iterator is at the same position that
    \p other is, and it is fully independent from \p other.

    This element sequence iterator creates a new data source from its
    element sequence's data source factory. See savePosition() and
    restorePosition() for a mechanism which can save and restore element
    sequence iterator positions without creating new data sources.

    This method can throw any exception that the data source can throw
    on construction.

    @param other    Other element sequence iterator to copy.
    @returns        This element sequence iterator.

    @throws DataNotAvailable    Data is not available now from the data
                                source: try again later.
    */
    ElementSequenceIterator& operator=(const ElementSequenceIterator& other);

    /*!
    @brief  Moves \p other as this element sequence iterator, and sets
            \p other to the end of its element sequence.

    Once you move \p other, it is set at the end of its element sequence
    (ElementSequence::end()). This element sequence iterator is at the
    same position that \p other was before being moved.

    This move operator invalidates the current element of \p other,
    if any.

    @param other    Other element sequence iterator to move, invalidated.
    @returns        This element sequence iterator.
    */
    ElementSequenceIterator& operator=(ElementSequenceIterator&& other);

    /*!
    @brief  Advances this element sequence iterator to the next element.

    This method invalidates this iterator's current element.

    This method can throw any exception that the data source can throw
    when getting a new data block.

    @returns    This element sequence iterator.

    @throws DecodingError       Any derived decoding error
                                (see decoding-errors.hpp): advancing
                                led to a decoding error.
    @throws DataNotAvailable    Data is not available now from the data
                                source: try again later.
    */
    ElementSequenceIterator& operator++();

    /*!
    @brief  Returns the current element of this element sequence iterator.

    This element is only valid if this iterator is not equal to
    ElementSequence::end() on the element sequence which created this
    iterator.

    This element remains valid as long as:

    -# This iterator's element sequence exists.
    -# You do not call operator++(), seekPacket(), or restorePosition()
       on this iterator, \em or you do not move this iterator
       (move constructor or move assignment operator).

    @returns    Current element of this iterator.
    */
    reference operator*() const noexcept
    {
        assert(_curElement);
        assert(_offset < _END_OFFSET);
        return *_curElement;
    }

    pointer operator->() const
    {
        return _curElement;
    }

    /*!
    @brief  Returns the current offset, in bits, of this element sequence
            iterator's current element.

    The current offset is the offset, within the iterator's element
    sequence, of the first bit of the iterator's current element. It is
    possible that two consecutive elements have the same offset, as not
    all elements are data elements (for example, an UnsignedIntElement
    followed by a MagicNumberValidationResultElement would have the
    same offset).

    The returned value is undefined if this iterator is equal to
    ElementSequence::end() (on the element sequence which created this
    iterator).

    @returns    Current offset (bits) of this element sequence iterator's
                element within its element sequence.
    */
    Index offset() const noexcept
    {
        return _offset;
    }

    /*!
    @brief  Seeks the beginning of a packet, in the same element
            sequence, known to be located at offset \p offset (bytes).

    @warning
    You \em must make sure that this offset, in the same element
    sequence, corresponds to the very first byte of a packet, otherwise
    it is likely that you will get a DecodingError eventually (when
    calling operator++()), or bad data at best.

    This method invalidates this iterator's current element.

    This method can throw any exception that the data source can throw
    when getting a new data block.

    @param offset   Offset, in bytes, of the first byte of a packet
                    within the same element sequence.

    @throws DataNotAvailable    Data is not available now from the data
                                source: try again later.
    */
    void seekPacket(Index offset);

    /*!
    @brief  Saves this element sequence iterator's position into
            \p pos.

    This operation makes it possible to save many positions of the same
    iterator \em without creating new data sources (which
    the \link ElementSequenceIterator(const ElementSequenceIterator&) copy
    constructor\endlink and
    \link operator=(const ElementSequenceIterator&) copy assignment
    operator\endlink do).

    You can restore the position of this iterator, or another iterator
    created from the same element sequence, from \p pos with
    restorePosition().

    You may only call this method if this iterator is not equal to
    ElementSequence::end() on the element sequence which created this
    iterator.

    @param pos  Position to set.
    */
    void savePosition(ElementSequenceIteratorPosition& pos) const;

    /*!
    @brief  Restore's this element sequence iterator's position from
            \p pos.

    You must have set \p pos with savePosition() before calling this
    method.

    \p pos is still valid after calling this method: you can use it
    to restore the position of this element sequence iterator, or another
    iterator created from the same element sequence, again.

    @param pos  Position to use to restore this iterator's position.
    */
    void restorePosition(const ElementSequenceIteratorPosition& pos);

    /*!
    @brief  Checks if this element sequence iterator is equal to
            \p other.

    Two element sequence iterators are considered equal if they are at
    the same element sequence element or if both are
    ElementSequence::end().

    This element sequence iterator and \p other \em must have been
    created by the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is
                    equal to \p other.
    */
    bool operator==(const ElementSequenceIterator& other) const noexcept
    {
        return _offset == other._offset && _mark == other._mark;
    }

    /*!
    @brief  Checks if this element sequence iterator is \em not equal
            to \p other.

    Two element sequence iterators are considered equal if they are at
    the same element sequence element or if both are
    ElementSequence::end().

    This element sequence iterator and \p other \em must have been
    created by the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is \em not
                    equal to \p other.
    */
    bool operator!=(const ElementSequenceIterator& other) const noexcept
    {
        return _offset != other._offset || _mark != other._mark;
    }

    /*!
    @brief  Checks if this element sequence iterator is before \p other.

    This element sequence iterator and \p other \em must have been
    created by the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is before
                    \p other.
    */
    bool operator<(const ElementSequenceIterator& other) const noexcept
    {
        return _offset < other._offset ||
               (_offset == other._offset && _mark < other._mark);
    }

    /*!
    @brief  Checks if this element sequence iterator is before or equal
            to \p other.

    This element sequence iterator and \p other \em must have been
    created by the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is before
                    or equal to \p other.
    */
    bool operator<=(const ElementSequenceIterator& other) const noexcept
    {
        return _offset < other._offset ||
               (_offset == other._offset && _mark <= other._mark);
    }

    /*!
    @brief  Checks if this element sequence iterator is after \p other.

    This element sequence iterator and \p other \em must have been
    created by the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is after
                    \p other.
    */
    bool operator>(const ElementSequenceIterator& other) const noexcept
    {
        return _offset > other._offset ||
               (_offset == other._offset && _mark > other._mark);
    }

    /*!
    @brief  Checks if this element sequence iterator is after or equal
            to \p other.

    This element sequence iterator and \p other \em must have been
    created by the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is after
                    or equal to \p other.
    */
    bool operator>=(const ElementSequenceIterator& other) const noexcept
    {
        return _offset > other._offset ||
               (_offset == other._offset && _mark >= other._mark);
    }

private:
    void _resetOther(ElementSequenceIterator& other);

private:
    std::shared_ptr<DataSourceFactory> _dataSourceFactory;
    std::unique_ptr<internal::Vm> _vm;
    std::shared_ptr<const TraceType> _traceType;

    // current element
    const Element *_curElement = nullptr;

    // current offset within element sequence; _END_OFFSET means ended
    Index _offset = 0;

    /*
     * Current mark within current packet.
     *
     * This is internal, that is, it's not publicly available. The mark
     * is the index of the current element within its packet. It is used
     * to preserve total ordering when two different elements are at the
     * same element sequence offset, for example ScopeBeginningElement
     * followed with StructBeginningElement. In this case, an iterator
     * with StructBeginningElement as its current element would have a
     * greater mark then another iterator with ScopeBeginningElement as
     * its current element, even if both iterators have their offset()
     * method return the same value. Then, for both iterators, ordering
     * operators work as expected.
     *
     * The mark is reset to 0 when the current element is
     * PacketBeginningElement, because two different packets within the
     * same element sequence cannot be at the same offset anyway (yactfr
     * reads packets of at least one byte and with a size (in bits) that
     * is divisible by 8).
     */
    Index _mark = 0;
};

} // namespace yactfr

#endif // _YACTFR_ELEMENT_SEQUENCE_ITERATOR_HPP
