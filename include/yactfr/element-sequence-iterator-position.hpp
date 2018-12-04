/*
 * Element sequence iterator position.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Element sequence iterator position.

@ingroup element_seq
*/

#ifndef _YACTFR_ELEMENT_SEQUENCE_ITERATOR_POSITION_HPP
#define _YACTFR_ELEMENT_SEQUENCE_ITERATOR_POSITION_HPP

// for std::unique_ptr
#include <memory>

namespace yactfr {
namespace internal {

    class Vm;
    class VmPos;
    class IterInfos;

} // namespace internal

/*!
@brief  Element sequence iterator position.

An element sequence iterator position object contains the exact position
of an ElementSequenceIterator object, but does not contain a data
source.

Call ElementSequenceIterator::savePosition() to set an
ElementSequenceIteratorPosition object and
ElementSequenceIterator::restorePosition() to restore a position.
*/
class ElementSequenceIteratorPosition final
{
    friend class internal::Vm;

private:
    using VmPosUp = std::unique_ptr<internal::VmPos>;
    using IterInfosUp = std::unique_ptr<internal::IterInfos>;

public:
    /*!
    @brief  Creates an empty element sequence iterator position.

    Call ElementSequenceIterator::savePosition() with this object before
    restoring an iterator's position with
    ElementSequenceIterator::restorePosition().
    */
    ElementSequenceIteratorPosition();

    /*!
    @brief  Copy constructor.

    @param other    Element sequence iterator position to copy.
    */
    ElementSequenceIteratorPosition(const ElementSequenceIteratorPosition& other);

    /*!
    @brief  Move constructor.

    This constructor resets \p other.

    @param other    Element sequence iterator position to move.
    */
    ElementSequenceIteratorPosition(ElementSequenceIteratorPosition&& other);

    ~ElementSequenceIteratorPosition();

    /*!
    @brief  Sets this element sequence iterator position to a copy of
            \p other.

    The copy is fully independent from \p other.

    @param other    Other element sequence iterator position to copy.
    @returns        This element sequence iterator position.
    */
    ElementSequenceIteratorPosition& operator=(const ElementSequenceIteratorPosition& other);

    /*!
    @brief  Moves \p other as this element sequence iterator position,
            and resets \p other.

    @param other    Other element sequence iterator position to move, reset.
    @returns        This element sequence iterator position.
    */
    ElementSequenceIteratorPosition& operator=(ElementSequenceIteratorPosition&& other);

    /*!
    @brief  Returns whether or not this element sequence iterator
            position is \em empty.

    It is not possible to call ElementSequenceIterator::restorePosition()
    with an empty position.

    @returns    \c true if this element sequence iterator position is
                \em not empty.
    */
    operator bool() const noexcept;

    /*!
    @brief  Checks if this element sequence iterator position is equal to
            \p other.

    This element sequence iterator position and \p other \em must have
    been set (ElementSequenceIterator::savePosition()) by iterators
    created from the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is
                    equal to \p other.
    */
    bool operator==(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this element sequence iterator is \em not equal
            to \p other.

    This element sequence iterator position and \p other \em must have
    been set (ElementSequenceIterator::savePosition()) by iterators
    created from the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is \em not
                    equal to \p other.
    */
    bool operator!=(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this element sequence iterator is before \p other.

    This element sequence iterator position and \p other \em must have
    been set (ElementSequenceIterator::savePosition()) by iterators
    created from the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is before
                    \p other.
    */
    bool operator<(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this element sequence iterator is before or equal
            to \p other.

    This element sequence iterator position and \p other \em must have
    been set (ElementSequenceIterator::savePosition()) by iterators
    created from the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is before
                    or equal to \p other.
    */
    bool operator<=(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this element sequence iterator is after \p other.

    This element sequence iterator position and \p other \em must have
    been set (ElementSequenceIterator::savePosition()) by iterators
    created from the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is after
                    \p other.
    */
    bool operator>(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this element sequence iterator is after or equal
            to \p other.

    This element sequence iterator position and \p other \em must have
    been set (ElementSequenceIterator::savePosition()) by iterators
    created from the same element sequence. This operator does not check
    this.

    @param other    Element sequence iterator to compare to.
    @returns        \c true if this element sequence iterator is after
                    or equal to \p other.
    */
    bool operator>=(const ElementSequenceIteratorPosition& other) const noexcept;

private:
    explicit ElementSequenceIteratorPosition(VmPosUp vmPos);

private:
    VmPosUp _vmPos;
    IterInfosUp _iterInfos;
};

} // namespace yactfr

#endif // _YACTFR_ELEMENT_SEQUENCE_ITERATOR_POSITION_HPP
