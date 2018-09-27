/*
 * Decoding errors.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>

#include <yactfr/decoding-errors.hpp>

namespace yactfr {

DecodingError::DecodingError(const std::string& reason, const Index offset) :
    std::runtime_error {reason},
    _reason {reason},
    _offset {offset}
{
}

UnknownDataStreamTypeDecodingError::UnknownDataStreamTypeDecodingError(const Index offset,
                                                                       const TypeId id) :
    DecodingError {
        [](const auto id) {
            std::ostringstream ss;

            ss << "Data stream type ID " << id <<
                  " does not select a valid data stream type.";
            return ss.str();
        }(id),
        offset
    },
    _id {id}
{
}

UnknownEventRecordTypeDecodingError::UnknownEventRecordTypeDecodingError(const Index offset,
                                                                         const TypeId id) :
    DecodingError {
        [](const auto id) {
            std::ostringstream ss;

            ss << "Event record type ID " << id <<
                  " does not select a valid event record type.";
            return ss.str();
        }(id),
        offset
    },
    _id {id}
{
}

ExpectedPacketTotalSizeNotMultipleOf8DecodingError::ExpectedPacketTotalSizeNotMultipleOf8DecodingError(const Index offset,
                                                                                                       const Size expectedSize) :
    DecodingError {
        [](const auto expectedSize) {
            std::ostringstream ss;

            ss << "Expected packet total size (" << expectedSize <<
                  ") is not a multiple of 8.";
            return ss.str();
        }(expectedSize),
        offset
    },
    _expectedSize {expectedSize}
{
}

ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError::ExpectedPacketTotalSizeLessThanExpectedPacketContentSizeDecodingError(const Index offset,
                                                                                                                                             const Size expectedTotalSize,
                                                                                                                                             const Size expectedContentSize) :
    DecodingError {
        [](const auto expectedTotalSize, const auto expectedContentSize) {
            std::ostringstream ss;

            ss << "Expected packet total size (" << expectedTotalSize <<
                  ") is less than expected packet content size (" <<
                  expectedContentSize << ").";
            return ss.str();
        }(expectedTotalSize, expectedContentSize),
        offset
    },
    _expectedTotalSize {expectedTotalSize},
    _expectedContentSize {expectedContentSize}
{
}

ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError::ExpectedPacketTotalSizeLessThanOffsetInPacketDecodingError(const Index offset,
                                                                                                                       const Size expectedSize,
                                                                                                                       const Index offsetInPacket) :
    DecodingError {
        [](const auto offsetInPacket, const auto expectedSize) {
            std::ostringstream ss;

            ss << "Expected packet total size (" << expectedSize <<
                  ") is less then current position in packet (" <<
                  offsetInPacket << ").";
            return ss.str();
        }(offsetInPacket, expectedSize),
        offset
    },
    _expectedSize {expectedSize},
    _offsetInPacket {offsetInPacket}
{
}

ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError::ExpectedPacketContentSizeLessThanOffsetInPacketDecodingError(const Index offset,
                                                                                                                           const Size expectedSize,
                                                                                                                           const Index offsetInPacket) :
    DecodingError {
        [](const auto offsetInPacket, const auto expectedSize) {
            std::ostringstream ss;

            ss << "Expected packet content size (" << expectedSize <<
                  ") is less then current position in packet (" <<
                  offsetInPacket << ").";
            return ss.str();
        }(offsetInPacket, expectedSize),
        offset
    },
    _expectedSize {expectedSize},
    _offsetInPacket {offsetInPacket}
{
}

CannotDecodeDataBeyondPacketContentDecodingError::CannotDecodeDataBeyondPacketContentDecodingError(const Index offset,
                                                                                                   const Size size,
                                                                                                   const Size remainingSize) :
    DecodingError {
        [](const auto size, const auto remainingSize) {
            std::ostringstream ss;

            ss << "Cannot read " << size << " bits at this point: would " <<
                  "move beyond the current packet's content (" <<
                  remainingSize << " bits remaining).";
            return ss.str();
        }(size, remainingSize),
        offset
    }
{
}

PrematureEndOfDataDecodingError::PrematureEndOfDataDecodingError(const Index offset,
                                                                 const Size size) :
    DecodingError {
        [](const auto size) {
            std::ostringstream ss;

            ss << "Cannot request " << size << " bits at this point: "
                  "reaching end of data source.";
            return ss.str();
        }(size),
        offset
    }
{
}

static inline const char *byteOrderString(const ByteOrder bo)
{
    return bo == ByteOrder::BIG ? "big" : "little";
}

ByteOrderChangeWithinByteDecodingError::ByteOrderChangeWithinByteDecodingError(const Index offset,
                                                                               const ByteOrder previousByteOrder,
                                                                               const ByteOrder nextByteOrder) :
    DecodingError {
        [](const auto previousBo, const auto nextBo) {
            std::ostringstream ss;

            ss << "Changing byte order within a byte from " <<
                  byteOrderString(previousBo) << "-endian to " <<
                  byteOrderString(nextBo) << "-endian.";
            return ss.str();
        }(previousByteOrder, nextByteOrder),
        offset
    },
    _previousByteOrder {previousByteOrder},
    _nextByteOrder {nextByteOrder}
{
}

static const auto formatUnknownVariantTagValueReason = [](const auto tagValue) {
    std::ostringstream ss;

    ss << "Tag value " << tagValue <<
          " does not select a valid variant option.";
    return ss.str();
};


UnknownVariantSignedTagValueDecodingError::UnknownVariantSignedTagValueDecodingError(const Index offset,
                                                                                     const std::int64_t tagValue) :
    DecodingError {
        formatUnknownVariantTagValueReason(tagValue),
        offset
    },
    _tagValue {tagValue}
{
}

UnknownVariantUnsignedTagValueDecodingError::UnknownVariantUnsignedTagValueDecodingError(const Index offset,
                                                                                         const std::uint64_t tagValue) :
    DecodingError {
        formatUnknownVariantTagValueReason(tagValue),
        offset
    },
    _tagValue {tagValue}
{
}

DynamicArrayLengthNotSetDecodingError::DynamicArrayLengthNotSetDecodingError(const Index offset) :
    DecodingError {"Dynamic array length is not set.", offset}
{
}

} // namespace yactfr
