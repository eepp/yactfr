/*
 * Decoding errors.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Decoding errors.

@ingroup packet_seq
*/

#ifndef _YACTFR_DECODING_ERRORS_HPP
#define _YACTFR_DECODING_ERRORS_HPP

// for std::runtime_error
#include <stdexcept>

// for std::string
#include <string>

// for ByteOrder
#include "metadata/byte-order.hpp"

// for TypeId
#include "metadata/aliases.hpp"

// for Index, Size
#include "aliases.hpp"

namespace yactfr {
namespace internal {

    class Vm;

} // namespace internal

/*!
@brief  %Base decoding error.

This is thrown when there's an error in the decoding process of a packet
sequence (PacketSequenceIterator::operator++(), for example).
*/
class DecodingError :
    public std::runtime_error
{
    friend class internal::Vm;

protected:
    explicit DecodingError(const std::string& reason, Index offset);

public:
    DecodingError(const DecodingError&) = default;
    DecodingError& operator=(const DecodingError&) = default;

    /// Reason of the error.
    const std::string& reason() const noexcept
    {
        return _reason;
    }

    /*!
    @brief  Offset (bits) from the beginning of the packet sequence
            which created this iterator.
    */
    Index offset() const noexcept
    {
        return _offset;
    }

private:
    std::string _reason;
    Index _offset;
};

/*!
@brief  "Unknown data stream type" decoding error.

This is thrown when a PacketSequenceIterator cannot find a data stream
type by ID during the decoding process.
*/
class UnknownDataStreamTypeDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit UnknownDataStreamTypeDecodingError(Index offset, TypeId id);

public:
    UnknownDataStreamTypeDecodingError(const UnknownDataStreamTypeDecodingError&) = default;
    UnknownDataStreamTypeDecodingError& operator=(const UnknownDataStreamTypeDecodingError&) = default;

    /// Unknown data stream type ID.
    TypeId id() const noexcept
    {
        return _id;
    }

private:
    TypeId _id;
};

/*!
@brief  "Unknown event record type" decoding error.

This is thrown when a PacketSequenceIterator cannot find an event record
type by ID during the decoding process.
*/
class UnknownEventRecordTypeDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit UnknownEventRecordTypeDecodingError(Index offset, TypeId id);

public:
    UnknownEventRecordTypeDecodingError(const UnknownEventRecordTypeDecodingError&) = default;
    UnknownEventRecordTypeDecodingError& operator=(const UnknownEventRecordTypeDecodingError&) = default;

    /// Unknown event record type ID.
    TypeId id() const noexcept
    {
        return _id;
    }

private:
    TypeId _id;
};

/*!
@brief  "Expected packet's total size is not a multiple of 8" decoding
        error.

This is thrown when a PacketSequenceIterator has decoded an
expected packet's total size and it's not a multiple of 8.
*/
class ExpectedPacketTotalSizeNotMultipleOf8DecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketTotalSizeNotMultipleOf8DecodingError(Index offset,
                                                                Size expectedSize);

public:
    ExpectedPacketTotalSizeNotMultipleOf8DecodingError(const ExpectedPacketTotalSizeNotMultipleOf8DecodingError&) = default;
    ExpectedPacketTotalSizeNotMultipleOf8DecodingError& operator=(const ExpectedPacketTotalSizeNotMultipleOf8DecodingError&) = default;

    /// Expected packet's total size (bits).
    Size expectedSize() const noexcept
    {
        return _expectedSize;
    }

private:
    Size _expectedSize;
};

/*!
@brief  "Expected packet's total size is less than expected packet's
        content size" decoding error.

This is thrown when a PacketSequenceIterator has decoded both an
expected packet's total size and an expected packet's content size, and
the total size is less than the content size.
*/
class ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError(Index offset,
                                                                                   Size expectedTotalSize,
                                                                                   Size expectedContentSize);

public:
    ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError(const ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError&) = default;
    ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError& operator=(const ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError&) = default;

    /// Expected packet's total size (bits).
    Size expectedTotalSize() const noexcept
    {
        return _expectedTotalSize;
    }

    /// Expected packet's content size (bits).
    Size expectedContentSize() const noexcept
    {
        return _expectedContentSize;
    }

private:
    Size _expectedTotalSize;
    Size _expectedContentSize;
};

/*!
@brief  "Expected packet's total size is less than current offset within
        packet" decoding error.

This is thrown when a PacketSequenceIterator has decoded an expected
packet's total size and it's is less than the current decoding offset
within this packet.
*/
class ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError(Index offset,
                                                                        Size expectedSize,
                                                                        Index offsetInPacket);

public:
    ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError(const ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError&) = default;
    ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError& operator=(const ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError&) = default;

    /// Expected packet's total size (bits).
    Size expectedSize() const noexcept
    {
        return _expectedSize;
    }

    /// Current offset in packet (bits).
    Index offsetInPacket() const noexcept
    {
        return _offsetInPacket;
    }

private:
    Size _expectedSize;
    Index _offsetInPacket;
};

/*!
@brief  "Expected packet's content size is less than current offset
        within packet" decoding error.

This is thrown when a PacketSequenceIterator has decoded an expected
packet's content size and it's is less than the current decoding offset
within this packet.
*/
class ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError(Index offset,
                                                                          Size expectedSize,
                                                                          Index offsetInPacket);

public:
    ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError(const ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError&) = default;
    ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError& operator=(const ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError&) = default;

    /// Expected packet's content size (bits).
    Size expectedSize() const noexcept
    {
        return _expectedSize;
    }

    /// Current offset in packet (bits).
    Index offsetInPacket() const noexcept
    {
        return _offsetInPacket;
    }

private:
    Size _expectedSize;
    Index _offsetInPacket;
};

/*!
@brief  "Cannot decode data beyond packet's content" decoding error.

This is thrown when a PacketSequenceIterator would need data passed the
current packet's content to continue decoding.
*/
class CannotDecodeDataBeyondPacketContentDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit CannotDecodeDataBeyondPacketContentDecodingError(Index offset,
                                                              Size size,
                                                              Size remainingSize);

public:
    CannotDecodeDataBeyondPacketContentDecodingError(const CannotDecodeDataBeyondPacketContentDecodingError&) = default;
    CannotDecodeDataBeyondPacketContentDecodingError& operator=(const CannotDecodeDataBeyondPacketContentDecodingError&) = default;

    /// Needed size (bits).
    Size size() const noexcept
    {
        return _size;
    }

    /// Remaining size in packet's content (bits).
    Size remainingSize() const noexcept
    {
        return _size;
    }

private:
    Size _size;
    Size _remainingSize;
};

/*!
@brief  "Premature end of data" decoding error.

This is thrown when a PacketSequenceIterator needs data to continue
decoding the current packet, but its data source indicates that there's
no more data at the requested offset.
*/
class PrematureEndOfDataDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit PrematureEndOfDataDecodingError(Index offset, Size size);

public:
    PrematureEndOfDataDecodingError(const PrematureEndOfDataDecodingError&) = default;
    PrematureEndOfDataDecodingError& operator=(const PrematureEndOfDataDecodingError&) = default;

    /// Needed size (bits).
    Size size() const noexcept
    {
        return _size;
    }

private:
    Size _size;
};

/*!
@brief  "Byte order change within byte" decoding error.

This is thrown when a PacketSequenceIterator previously decoded a data
stream datum with a given byte order and the following one has a
different byte order when the current offset is not a multiple of 8.
*/
class ByteOrderChangeWithinByteDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ByteOrderChangeWithinByteDecodingError(Index offset,
                                                    ByteOrder previousByteOrder,
                                                    ByteOrder nextByteOrder);

public:
    ByteOrderChangeWithinByteDecodingError(const ByteOrderChangeWithinByteDecodingError&) = default;
    ByteOrderChangeWithinByteDecodingError& operator=(const ByteOrderChangeWithinByteDecodingError&) = default;

    /// Previous byte order.
    ByteOrder previousByteOrder() const noexcept
    {
        return _previousByteOrder;
    }

    /// Next byte order.
    ByteOrder nextByteOrder() const noexcept
    {
        return _nextByteOrder;
    }

private:
    ByteOrder _previousByteOrder;
    ByteOrder _nextByteOrder;
};

/*!
@brief  "Unknown variant's signed tag value" decoding error.

This is thrown when a PacketSequenceIterator needs to select a variant
type's option, but the previously decoded signed tag value does not
select a option.
*/
class UnknownVariantSignedTagValueDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit UnknownVariantSignedTagValueDecodingError(Index offset,
                                                       std::int64_t tagValue);

public:
    UnknownVariantSignedTagValueDecodingError(const UnknownVariantSignedTagValueDecodingError&) = default;
    UnknownVariantSignedTagValueDecodingError& operator=(const UnknownVariantSignedTagValueDecodingError&) = default;

    /// Unknown tag value.
    std::int64_t tagValue() const noexcept
    {
        return _tagValue;
    }

private:
    std::int64_t _tagValue;
};

/*!
@brief  "Unknown variant's unsigned tag value" decoding error.

This is thrown when a PacketSequenceIterator needs to select a variant
type's option, but the previously decoded unsigned tag value does not
select a option.
*/
class UnknownVariantUnsignedTagValueDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit UnknownVariantUnsignedTagValueDecodingError(Index offset,
                                                         std::uint64_t tagValue);

public:
    UnknownVariantUnsignedTagValueDecodingError(const UnknownVariantUnsignedTagValueDecodingError&) = default;
    UnknownVariantUnsignedTagValueDecodingError& operator=(const UnknownVariantUnsignedTagValueDecodingError&) = default;

    /// Unknown tag value.
    std::uint64_t tagValue() const noexcept
    {
        return _tagValue;
    }

private:
    std::uint64_t _tagValue;
};

/*!
@brief  "Sequence length is not set" decoding error.

This is thrown when a PacketSequenceIterator needs to decode a data
stream sequence, but its length was not previously decoded.
*/
class SequenceLengthNotSetDecodingError :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit SequenceLengthNotSetDecodingError(Index offset);

public:
    SequenceLengthNotSetDecodingError(const SequenceLengthNotSetDecodingError&) = default;
    SequenceLengthNotSetDecodingError& operator=(const SequenceLengthNotSetDecodingError&) = default;
};

} // namespace yactfr

#endif // _YACTFR_DECODING_ERRORS_HPP
