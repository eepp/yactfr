/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_PACKETIZED_METADATA_STREAM_HPP
#define YACTFR_METADATA_PACKETIZED_METADATA_STREAM_HPP

#include <string>
#include <boost/uuid/uuid.hpp>

#include "../aliases.hpp"
#include "bo.hpp"

namespace yactfr {

/*!
@brief
    Packetized (CTF 1) metadata stream.

@ingroup metadata_stream
*/
class PacketizedMetadataStream final :
    public MetadataStream
{
    friend std::unique_ptr<const MetadataStream> createMetadataStream(std::istream&);

private:
    explicit PacketizedMetadataStream(std::string text, Size pktCount, unsigned int majorVersion,
                                      unsigned int minorVersion, ByteOrder bo,
                                      boost::uuids::uuid uuid);

public:
    ~PacketizedMetadataStream() = default;

    /// Number of packets in this metadata stream.
    Size packetCount() const noexcept
    {
        return _pktCount;
    }

    /// Major version number of this metadata stream.
    unsigned int majorVersion() const noexcept
    {
        return _majorVersion;
    }

    /// Minor version number of this metadata stream.
    unsigned int minorVersion() const noexcept
    {
        return _minorVersion;
    }

    /// Byte order of this metadata stream.
    ByteOrder byteOrder() const noexcept
    {
        return _bo;
    }

    /*!
    @brief
        UUID of the \em packets of this metadata stream.

    Not to be confused with the metadata stream UUID as found in either:

    <dl>
      <dt>CTF 1 (TSDL)
      <dd>The \c trace block (same as the trace UUID).

      <dt>CTF 2 (JSON text sequence)
      <dd>The \c uuid property of the preamble fragment.
    </dl>

    The only purpose of this UUID is to make sure all the metadata
    stream packets are part of the same stream.
    */
    const boost::uuids::uuid& uuid() const noexcept
    {
        return _uuid;
    }

private:
    const Size _pktCount;
    const unsigned int _majorVersion;
    const unsigned int _minorVersion;
    const ByteOrder _bo;
    const boost::uuids::uuid _uuid;
};

} // namespace yactfr

#endif // YACTFR_METADATA_PACKETIZED_METADATA_STREAM_HPP
