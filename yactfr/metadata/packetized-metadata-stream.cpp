/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/metadata-stream.hpp>
#include <yactfr/metadata/packetized-metadata-stream.hpp>

namespace yactfr {

PacketizedMetadataStream::PacketizedMetadataStream(std::string&& text, const Size pktCount,
                                                   const unsigned int majorVersion,
                                                   const unsigned int minorVersion,
                                                   const ByteOrder bo, boost::uuids::uuid uuid) :
    MetadataStream {std::move(text)},
    _pktCount {pktCount},
    _majorVersion {majorVersion},
    _minorVersion {minorVersion},
    _bo {bo},
    _uuid {std::move(uuid)}
{
}

PacketizedMetadataStream::~PacketizedMetadataStream()
{
}

} // namespace yactfr
