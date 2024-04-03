/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>

#include <yactfr/decoding-errors.hpp>

namespace yactfr {

DecodingError::DecodingError(std::string reason, const Index offset) :
    std::runtime_error {reason},
    _reason {std::move(reason)},
    _offset {offset}
{
}

UnknownDataStreamTypeDecodingError::UnknownDataStreamTypeDecodingError(const Index offset,
                                                                       const TypeId id) :
    DecodingError {
        [](const auto id) {
            std::ostringstream ss;

            ss << "Data stream type ID " << id << " doesn't select an existing data stream type.";
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

            ss << "Event record type ID " << id << " doesn't select an existing event record type.";
            return ss.str();
        }(id),
        offset
    },
    _id {id}
{
}

ExpectedPacketTotalLengthNotMultipleOf8DecodingError::ExpectedPacketTotalLengthNotMultipleOf8DecodingError(const Index offset,
                                                                                                           const Size expectedLen) :
    DecodingError {
        [](const auto expectedLen) {
            std::ostringstream ss;

            ss << "Expected packet total length (" << expectedLen << ") is not a multiple of 8.";
            return ss.str();
        }(expectedLen),
        offset
    },
    _expectedLen {expectedLen}
{
}

ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError::ExpectedPacketTotalLengthLessThanExpectedPacketContentLengthDecodingError(const Index offset,
                                                                                                                                                     const Size expectedTotalLen,
                                                                                                                                                     const Size expectedContentLen) :
    DecodingError {
        [](const auto expectedTotalLen, const auto expectedContentLen) {
            std::ostringstream ss;

            ss << "Expected packet total length (" << expectedTotalLen <<
                  ") is less than expected packet content length (" <<
                  expectedContentLen << ").";
            return ss.str();
        }(expectedTotalLen, expectedContentLen),
        offset
    },
    _expectedTotalLen {expectedTotalLen},
    _expectedContentLen {expectedContentLen}
{
}

ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError::ExpectedPacketTotalLengthLessThanOffsetInPacketDecodingError(const Index offset,
                                                                                                                           const Size expectedLen,
                                                                                                                           const Index offsetInPkt) :
    DecodingError {
        [](const auto offsetInPkt, const auto expectedLen) {
            std::ostringstream ss;

            ss << "Expected packet total length (" << expectedLen <<
                  ") is less then current position in packet (" <<
                  offsetInPkt << ").";
            return ss.str();
        }(offsetInPkt, expectedLen),
        offset
    },
    _expectedLen {expectedLen},
    _offsetInPkt {offsetInPkt}
{
}

ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError::ExpectedPacketContentLengthLessThanOffsetInPacketDecodingError(const Index offset,
                                                                                                                               const Size expectedLen,
                                                                                                                               const Index offsetInPkt) :
    DecodingError {
        [](const auto offsetInPkt, const auto expectedLen) {
            std::ostringstream ss;

            ss << "Expected packet content length (" << expectedLen <<
                  ") is less then current position in packet (" <<
                  offsetInPkt << ").";
            return ss.str();
        }(offsetInPkt, expectedLen),
        offset
    },
    _expectedLen {expectedLen},
    _offsetInPkt {offsetInPkt}
{
}

CannotDecodeDataBeyondPacketContentDecodingError::CannotDecodeDataBeyondPacketContentDecodingError(const Index offset,
                                                                                                   const Size reqLen,
                                                                                                   const Size remLen) :
    DecodingError {
        [](const auto reqLen, const auto remLen) {
            std::ostringstream ss;

            ss << "Cannot read " << reqLen << " bit" << (reqLen == 1 ? "" : "s") <<
                  " at this point: would move beyond the content of the current packet "
                  "(" << remLen <<
                  " bit" << (remLen == 1 ? "" : "s") << " remaining).";
            return ss.str();
        }(reqLen, remLen),
        offset
    },
    _reqLen {reqLen},
    _remLen {remLen}
{
}

PrematureEndOfDataDecodingError::PrematureEndOfDataDecodingError(const Index offset,
                                                                 const Size reqLen) :
    DecodingError {
        [](const auto reqLen) {
            std::ostringstream ss;

            ss << "Cannot read " << reqLen <<
                  " bit" << (reqLen == 1 ? "" : "s") << " at this point: "
                  "reaching end of data source.";
            return ss.str();
        }(reqLen),
        offset
    },
    _reqLen {reqLen}
{
}

namespace {

const char *byteOrderString(const ByteOrder bo)
{
    return bo == ByteOrder::Big ? "big" : "little";
}

} // namespace

ByteOrderChangeWithinByteDecodingError::ByteOrderChangeWithinByteDecodingError(const Index offset,
                                                                               const ByteOrder previousBo,
                                                                               const ByteOrder nextBo) :
    DecodingError {
        [](const auto previousBo, const auto nextBo) {
            std::ostringstream ss;

            ss << "Changing byte order within a byte from " <<
                  byteOrderString(previousBo) << "-endian to " <<
                  byteOrderString(nextBo) << "-endian.";
            return ss.str();
        }(previousBo, nextBo),
        offset
    },
    _previousBo {previousBo},
    _nextBo {nextBo}
{
}

template <typename SelValueT>
const std::string formatInvalidVarSelValueReason(const SelValueT selVal)
{
    std::ostringstream ss;

    ss << "Selector value " << selVal << " doesn't select a valid variant option.";
    return ss.str();
};

InvalidVariantSignedIntegerSelectorValueDecodingError::InvalidVariantSignedIntegerSelectorValueDecodingError(const Index offset,
                                                                                                             const long long selVal) :
    DecodingError {
        formatInvalidVarSelValueReason(selVal),
        offset
    },
    _selVal {selVal}
{
}

InvalidVariantUnsignedIntegerSelectorValueDecodingError::InvalidVariantUnsignedIntegerSelectorValueDecodingError(const Index offset,
                                                                                                                 const unsigned long long selVal) :
    DecodingError {
        formatInvalidVarSelValueReason(selVal),
        offset
    },
    _selVal {selVal}
{
}

OversizedVariableLengthIntegerDecodingError::OversizedVariableLengthIntegerDecodingError(const Index offset) :
    DecodingError {
        "Oversized variable-length integer.",
        offset
    }
{
}

} // namespace yactfr
