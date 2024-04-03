/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_DECODING_ERRORS_HPP
#define YACTFR_DECODING_ERRORS_HPP

#include <stdexcept>
#include <string>

#include "metadata/bo.hpp"
#include "metadata/aliases.hpp"
#include "aliases.hpp"

namespace yactfr {
namespace internal {

class Vm;

} // namespace internal

/*!
@defgroup dec_errors Decoding errors

@brief
    Decoding errors.

@ingroup element_seq
*/

/*!
@brief
    %Base decoding error.

@ingroup dec_errors

This is thrown when there's an error in the decoding process of an
element sequence (ElementSequenceIterator::operator++(), for example).
*/
class DecodingError :
    public std::runtime_error
{
    friend class internal::Vm;

protected:
    explicit DecodingError(std::string reason, Index offset);

public:
    DecodingError(const DecodingError&) = default;
    DecodingError& operator=(const DecodingError&) = default;

public:
    /// Reason of the error.
    const std::string& reason() const noexcept
    {
        return _reason;
    }

    /*!
    @brief
        Offset (bits) from the beginning of the element sequence which
        created this iterator.
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
@brief
    Unknown data stream type decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink
cannot find a data stream type by ID during the decoding process.
*/
class UnknownDataStreamTypeDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit UnknownDataStreamTypeDecodingError(Index offset, TypeId id);

public:
    /// Default copy constructor.
    UnknownDataStreamTypeDecodingError(const UnknownDataStreamTypeDecodingError&) = default;

    /// Default copy assignment operator.
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
@brief
    Unknown event record type decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink cannot
find an event record type by ID during the decoding process.
*/
class UnknownEventRecordTypeDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit UnknownEventRecordTypeDecodingError(Index offset, TypeId id);

public:
    /// Default copy constructor.
    UnknownEventRecordTypeDecodingError(const UnknownEventRecordTypeDecodingError&) = default;

    /// Default copy assignment operator.
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
@brief
    Expected total length of packet is not a multiple of 8 decoding
    error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink has
decoded an expected total length of packet and it's not a multiple of 8.
*/
class ExpectedPacketTotalLengthNotMultipleOf8DecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketTotalLengthNotMultipleOf8DecodingError(Index offset, Size expectedLen);

public:
    /// Default copy constructor.
    ExpectedPacketTotalLengthNotMultipleOf8DecodingError(const ExpectedPacketTotalLengthNotMultipleOf8DecodingError&) = default;

    /// Default copy assignment operator.
    ExpectedPacketTotalLengthNotMultipleOf8DecodingError& operator=(const ExpectedPacketTotalLengthNotMultipleOf8DecodingError&) = default;

    /// Expected total length of packet (bits).
    Size expectedLength() const noexcept
    {
        return _expectedLen;
    }

private:
    Size _expectedLen;
};

/*!
@brief
    Expected total length of packet is less than expected content
    length of packet decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink has
decoded both an expected total length of packet and an expected content
length of packet, and the total length is less than the content length.
*/
class ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError(Index offset,
                                                                                       Size expectedTotalLen,
                                                                                       Size expectedContentLen);

public:
    /// Default copy constructor.
    ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError(const ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError&) = default;

    /// Default copy assignment operator.
    ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError& operator=(const ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError&) = default;

    /// Expected total length of packet (bits).
    Size expectedTotalLength() const noexcept
    {
        return _expectedTotalLen;
    }

    /// Expected content length of packet (bits).
    Size expectedContentLength() const noexcept
    {
        return _expectedContentLen;
    }

private:
    Size _expectedTotalLen;
    Size _expectedContentLen;
};

/*!
@brief
    Expected total length of packet is less than current offset within
    packet decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink has
decoded an expected total length of packet and it's is less than the
current decoding offset within this packet.
*/
class ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError(Index offset,
                                                                          Size expectedLen,
                                                                          Index offsetInPkt);

public:
    /// Default copy constructor.
    ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError(const ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError&) = default;

    /// Default copy assignment operator.
    ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError& operator=(const ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError&) = default;

    /// Expected total length of packet (bits).
    Size expectedLength() const noexcept
    {
        return _expectedLen;
    }

    /// Current offset in packet (bits).
    Index offsetInPacket() const noexcept
    {
        return _offsetInPkt;
    }

private:
    Size _expectedLen;
    Index _offsetInPkt;
};

/*!
@brief
    Expected content length of packet is less than current offset within
    packet decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink has
decoded an expected content length of packet and it's is less than the
current decoding offset within this packet.
*/
class ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError(Index offset,
                                                                            Size expectedLen,
                                                                            Index offsetInPkt);

public:
    /// Default copy constructor.
    ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError(const ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError&) = default;

    /// Default copy assignment operator.
    ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError& operator=(const ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError&) = default;

    /// Expected content length of packet (bits).
    Size expectedLength() const noexcept
    {
        return _expectedLen;
    }

    /// Current offset in packet (bits).
    Index offsetInPacket() const noexcept
    {
        return _offsetInPkt;
    }

private:
    Size _expectedLen;
    Index _offsetInPkt;
};

/*!
@brief
    Cannot decode data beyond the packet content decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink would
need data passed the content of the current packet to continue decoding.
*/
class CannotDecodeDataBeyondPacketContentDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit CannotDecodeDataBeyondPacketContentDecodingError(Index offset, Size reqLen,
                                                              Size remLen);

public:
    /// Default copy constructor.
    CannotDecodeDataBeyondPacketContentDecodingError(const CannotDecodeDataBeyondPacketContentDecodingError&) = default;

    /// Default copy assignment operator.
    CannotDecodeDataBeyondPacketContentDecodingError& operator=(const CannotDecodeDataBeyondPacketContentDecodingError&) = default;

    /// Required length (bits).
    Size requiredLength() const noexcept
    {
        return _reqLen;
    }

    /// Remaining length in packet content (bits).
    Size remainingLength() const noexcept
    {
        return _remLen;
    }

private:
    Size _reqLen;
    Size _remLen;
};

/*!
@brief
    Premature end of data decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink needs
data to continue decoding the current packet, but its data source
indicates that there's no more data at the requested offset.
*/
class PrematureEndOfDataDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit PrematureEndOfDataDecodingError(Index offset, Size reqLen);

public:
    /// Default copy constructor.
    PrematureEndOfDataDecodingError(const PrematureEndOfDataDecodingError&) = default;

    /// Default copy assignment operator.
    PrematureEndOfDataDecodingError& operator=(const PrematureEndOfDataDecodingError&) = default;

    /// Required size (bits).
    Size requiredLength() const noexcept
    {
        return _reqLen;
    }

private:
    Size _reqLen;
};

/*!
@brief
    Byte order change within byte decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink
previously decoded a data stream datum with a given byte order and the
following one has a different byte order when the current offset is not
a multiple of 8.
*/
class ByteOrderChangeWithinByteDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit ByteOrderChangeWithinByteDecodingError(Index offset, ByteOrder previousBo,
                                                    ByteOrder nextBo);

public:
    /// Default copy constructor.
    ByteOrderChangeWithinByteDecodingError(const ByteOrderChangeWithinByteDecodingError&) = default;

    /// Default copy assignment operator.
    ByteOrderChangeWithinByteDecodingError& operator=(const ByteOrderChangeWithinByteDecodingError&) = default;

    /// Previous byte order.
    ByteOrder previousByteOrder() const noexcept
    {
        return _previousBo;
    }

    /// Next byte order.
    ByteOrder nextByteOrder() const noexcept
    {
        return _nextBo;
    }

private:
    ByteOrder _previousBo;
    ByteOrder _nextBo;
};

/*!
@brief
    Invalid signed integer selector value of variant decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink needs to
select an option of a variant type, but the previously decoded signed
integer selector value doesn't select any option.
*/
class InvalidVariantSignedIntegerSelectorValueDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit InvalidVariantSignedIntegerSelectorValueDecodingError(Index offset, long long selVal);

public:
    /// Default copy constructor.
    InvalidVariantSignedIntegerSelectorValueDecodingError(const InvalidVariantSignedIntegerSelectorValueDecodingError&) = default;

    /// Default copy assignment operator.
    InvalidVariantSignedIntegerSelectorValueDecodingError& operator=(const InvalidVariantSignedIntegerSelectorValueDecodingError&) = default;

    /// Invalid selector value.
    long long selectorValue() const noexcept
    {
        return _selVal;
    }

private:
    long long _selVal;
};

/*!
@brief
    Invalid unsigned integer selector value of variant decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink needs to
select an option of a variant type, but the previously decoded unsigned
integer selector value does not select any option.
*/
class InvalidVariantUnsignedIntegerSelectorValueDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit InvalidVariantUnsignedIntegerSelectorValueDecodingError(Index offset,
                                                                     unsigned long long selVal);

public:
    /// Default copy constructor.
    InvalidVariantUnsignedIntegerSelectorValueDecodingError(const InvalidVariantUnsignedIntegerSelectorValueDecodingError&) = default;

    /// Default copy assignment operator.
    InvalidVariantUnsignedIntegerSelectorValueDecodingError& operator=(const InvalidVariantUnsignedIntegerSelectorValueDecodingError&) = default;

    /// Invalid selector value.
    unsigned long long selectorValue() const noexcept
    {
        return _selVal;
    }

private:
    unsigned long long _selVal;
};

/*!
@brief
    Oversized variable-length integer decoding error.

@ingroup dec_errors

This is thrown when an
\link ElementSequenceIterator element sequence iterator\endlink is in
the process of decoding a variable-length integer, but (any of):

- It contains more than ten bytes.

- It contains ten bytes, and:

  <dl>
    <dt>Unsigned</dt>
    <dd>Its last byte is not 1.</dd>

    <dt>Signed</dt>
    <dd>Its last byte is not 0 or 127.</dd>
  </dl>
*/
class OversizedVariableLengthIntegerDecodingError final :
    public DecodingError
{
    friend class internal::Vm;

private:
    explicit OversizedVariableLengthIntegerDecodingError(Index offset);

public:
    /// Default copy constructor.
    OversizedVariableLengthIntegerDecodingError(const OversizedVariableLengthIntegerDecodingError&) = default;

    /// Default copy assignment operator.
    OversizedVariableLengthIntegerDecodingError& operator=(const OversizedVariableLengthIntegerDecodingError&) = default;
};

} // namespace yactfr

#endif // YACTFR_DECODING_ERRORS_HPP
