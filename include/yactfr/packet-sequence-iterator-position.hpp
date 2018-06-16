/*
 * Packet sequence iterator position.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Packet sequence iterator position.

@ingroup packet_seq
*/

#ifndef _YACTFR_PACKET_SEQUENCE_ITERATOR_POSITION_HPP
#define _YACTFR_PACKET_SEQUENCE_ITERATOR_POSITION_HPP

// for std::unique_ptr
#include <memory>

namespace yactfr {
namespace internal {

    class Vm;
    class VmPos;
    class IterInfos;

} // namespace internal

/*!
@brief  Packet sequence iterator position.

A packet sequence iterator position object contains the exact position
of a PacketSequenceIterator object, but does not contain a data source.

Call PacketSequenceIterator::savePosition() to set a
PacketSequenceIteratorPosition object and
PacketSequenceIterator::restorePosition() to restore a position.
*/
class PacketSequenceIteratorPosition final
{
    friend class internal::Vm;

private:
    using VmPosUp = std::unique_ptr<internal::VmPos>;
    using IterInfosUp = std::unique_ptr<internal::IterInfos>;

public:
    /*!
    @brief  Creates an empty packet sequence iterator position.

    Call PacketSequenceIterator::savePosition() with this object before
    restoring an iterator's position with
    PacketSequenceIterator::restorePosition().
    */
    PacketSequenceIteratorPosition();

    /*!
    @brief  Copy constructor.

    @param other    Packet sequence iterator position to copy.
    */
    PacketSequenceIteratorPosition(const PacketSequenceIteratorPosition& other);

    /*!
    @brief  Move constructor.

    This constructor resets \p other.

    @param other    Packet sequence iterator position to move.
    */
    PacketSequenceIteratorPosition(PacketSequenceIteratorPosition&& other);

    ~PacketSequenceIteratorPosition();

    /*!
    @brief  Sets this packet sequence iterator position to a copy of
            \p other.

    The copy is fully independent from \p other.

    @param other    Other packet sequence iterator position to copy.
    @returns        This packet sequence iterator position.
    */
    PacketSequenceIteratorPosition& operator=(const PacketSequenceIteratorPosition& other);

    /*!
    @brief  Moves \p other as this packet sequence iterator position,
            and resets \p other.

    @param other    Other packet sequence iterator position to move, reset.
    @returns        This packet sequence iterator position.
    */
    PacketSequenceIteratorPosition& operator=(PacketSequenceIteratorPosition&& other);

    /*!
    @brief  Returns whether or not this packet sequence iterator
            position is \em empty.

    It is not possible to call PacketSequenceIterator::restorePosition()
    with an empty position.

    @returns    \c true if this packet sequence iterator position is
                \em not empty.
    */
    operator bool() const noexcept;

    /*!
    @brief  Checks if this packet sequence iterator position is equal to
            \p other.

    This packet sequence iterator position and \p other \em must have
    been set (PacketSequenceIterator::savePosition()) by iterators
    created from the same packet sequence. This operator does not check
    this.

    @param other    Packet sequence iterator to compare to.
    @returns        \c true if this packet sequence iterator is
                    equal to \p other.
    */
    bool operator==(const PacketSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this packet sequence iterator is \em not equal
            to \p other.

    This packet sequence iterator position and \p other \em must have
    been set (PacketSequenceIterator::savePosition()) by iterators
    created from the same packet sequence. This operator does not check
    this.

    @param other    Packet sequence iterator to compare to.
    @returns        \c true if this packet sequence iterator is \em not
                    equal to \p other.
    */
    bool operator!=(const PacketSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this packet sequence iterator is before \p other.

    This packet sequence iterator position and \p other \em must have
    been set (PacketSequenceIterator::savePosition()) by iterators
    created from the same packet sequence. This operator does not check
    this.

    @param other    Packet sequence iterator to compare to.
    @returns        \c true if this packet sequence iterator is before
                    \p other.
    */
    bool operator<(const PacketSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this packet sequence iterator is before or equal
            to \p other.

    This packet sequence iterator position and \p other \em must have
    been set (PacketSequenceIterator::savePosition()) by iterators
    created from the same packet sequence. This operator does not check
    this.

    @param other    Packet sequence iterator to compare to.
    @returns        \c true if this packet sequence iterator is before
                    or equal to \p other.
    */
    bool operator<=(const PacketSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this packet sequence iterator is after \p other.

    This packet sequence iterator position and \p other \em must have
    been set (PacketSequenceIterator::savePosition()) by iterators
    created from the same packet sequence. This operator does not check
    this.

    @param other    Packet sequence iterator to compare to.
    @returns        \c true if this packet sequence iterator is after
                    \p other.
    */
    bool operator>(const PacketSequenceIteratorPosition& other) const noexcept;

    /*!
    @brief  Checks if this packet sequence iterator is after or equal
            to \p other.

    This packet sequence iterator position and \p other \em must have
    been set (PacketSequenceIterator::savePosition()) by iterators
    created from the same packet sequence. This operator does not check
    this.

    @param other    Packet sequence iterator to compare to.
    @returns        \c true if this packet sequence iterator is after
                    or equal to \p other.
    */
    bool operator>=(const PacketSequenceIteratorPosition& other) const noexcept;

private:
    explicit PacketSequenceIteratorPosition(VmPosUp vmPos);

private:
    VmPosUp _vmPos;
    IterInfosUp _iterInfos;
};

} // namespace yactfr

#endif // _YACTFR_PACKET_SEQUENCE_ITERATOR_POSITION_HPP
