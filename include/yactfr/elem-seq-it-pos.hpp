/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ELEM_SEQ_IT_POS_HPP
#define _YACTFR_ELEM_SEQ_IT_POS_HPP

#include <memory>

namespace yactfr {
namespace internal {

class Vm;
class VmPos;
class ItInfos;

} // namespace internal

/*!
@brief
    Element sequence iterator position.

@ingroup element_seq

An element sequence iterator position object contains the exact position
of an ElementSequenceIterator object, but does \em not contain a data
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
    using ItInfosUp = std::unique_ptr<internal::ItInfos>;

public:
    /*!
    @brief
        Creates an empty element sequence iterator position.

    Call ElementSequenceIterator::savePosition() with this object before
    restoring the position of an iterator with
    ElementSequenceIterator::restorePosition().
    */
    explicit ElementSequenceIteratorPosition();

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Element sequence iterator position to copy.
    */
    ElementSequenceIteratorPosition(const ElementSequenceIteratorPosition& other);

    /*!
    @brief
        Move constructor.

    This constructor resets \p other.

    @param[in] other
        Element sequence iterator position to move.
    */
    ElementSequenceIteratorPosition(ElementSequenceIteratorPosition&& other);

    ~ElementSequenceIteratorPosition();

    /*!
    @brief
        Sets this element sequence iterator position to a copy of
        \p other.

    The copy is fully independent from \p other.

    @param[in] other
        Other element sequence iterator position to copy.

    @returns
        This element sequence iterator position.
    */
    ElementSequenceIteratorPosition& operator=(const ElementSequenceIteratorPosition& other);

    /*!
    @brief
        Moves \p other as this element sequence iterator position,
        and resets \p other.

    @param[in] other
        Other element sequence iterator position to move and reset.

    @returns
        This element sequence iterator position.
    */
    ElementSequenceIteratorPosition& operator=(ElementSequenceIteratorPosition&& other);

    /*!
    @brief
        Returns whether or not this element sequence iterator position
        is \em empty.

    It's not possible to call ElementSequenceIterator::restorePosition()
    with an empty position.

    @returns
        \c true if this element sequence iterator position is
        \em not empty.
    */
    operator bool() const noexcept;

    /*!
    @brief
        Equality operator.

    @param[in] other
        Element sequence iterator position to compare to.

    @returns
        \c true if this element sequence iterator position is equal to
        \p other.

    @pre
        This element sequence iterator position and \p other \em must
        have been set (ElementSequenceIterator::savePosition()) by
        iterators created from the \em same element sequence.
    */
    bool operator==(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Element sequence iterator position to compare to.

    @returns
        \c true if this element sequence iterator position is \em not
        equal to \p other.

    @pre
        This element sequence iterator position and \p other \em must
        have been set (ElementSequenceIterator::savePosition()) by
        iterators created from the \em same element sequence.
    */
    bool operator!=(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Element sequence iterator position to compare to.

    @returns
        \c true if this element sequence iterator position is before
        \p other.

    @pre
        This element sequence iterator position and \p other \em must
        have been set (ElementSequenceIterator::savePosition()) by
        iterators created from the \em same element sequence.
    */
    bool operator<(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief
        Less-than or equality operator.

    @param[in] other
        Element sequence iterator position to compare to.

    @returns
        \c true if this element sequence iterator position is before
        or equal to \p other.

    @pre
        This element sequence iterator position and \p other \em must
        have been set (ElementSequenceIterator::savePosition()) by
        iterators created from the \em same element sequence.
    */
    bool operator<=(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief
        Greater-than operator.

    @param[in] other
        Element sequence iterator position to compare to.

    @returns
        \c true if this element sequence iterator position is after
        \p other.

    @pre
        This element sequence iterator position and \p other \em must
        have been set (ElementSequenceIterator::savePosition()) by
        iterators created from the \em same element sequence.
    */
    bool operator>(const ElementSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief
        Greater-than or equality operator.

    @param[in] other
        Element sequence iterator position to compare to.

    @returns
        \c true if this element sequence iterator position is after
        or equal to \p other.

    @pre
        This element sequence iterator position and \p other \em must
        have been set (ElementSequenceIterator::savePosition()) by
        iterators created from the \em same element sequence.
    */
    bool operator>=(const ElementSequenceIteratorPosition& other) const noexcept;

private:
    explicit ElementSequenceIteratorPosition(VmPosUp vmPos);

private:
    VmPosUp _vmPos;
    ItInfosUp _itInfos;
};

} // namespace yactfr

#endif // _YACTFR_ELEM_SEQ_IT_POS_HPP
