/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/metadata-stream.hpp>
#include <yactfr/metadata/packetized-metadata-stream.hpp>

namespace yactfr {

PacketizedMetadataStream::PacketizedMetadataStream(std::string text, const Size pktCount,
                                                   const ByteOrder bo, boost::uuids::uuid uuid) :
    MetadataStream {std::move(text)},
    _pktCount {pktCount},
    _bo {bo},
    _uuid {std::move(uuid)}
{
}

} // namespace yactfr
