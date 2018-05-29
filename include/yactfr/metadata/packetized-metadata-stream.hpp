/*
 * Packetized metadata stream.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Packetized metadata stream and related exception.

@ingroup metadata_stream
*/

#ifndef _YACTFR_METADATA_PACKETIZED_METADATA_STREAM_HPP
#define _YACTFR_METADATA_PACKETIZED_METADATA_STREAM_HPP

#include <cstdlib>
#include <string>
#include <memory>
#include <boost/uuid/uuid.hpp>

#include <yactfr/aliases.hpp>

#include "data-type.hpp"
#include "aliases.hpp"
#include "byte-order.hpp"
#include "metadata-stream.hpp"

namespace yactfr {

/*!
@brief  Packetized metadata stream.

@ingroup metadata_stream
*/
class PacketizedMetadataStream final :
    public MetadataStream
{
    friend std::unique_ptr<const MetadataStream> createMetadataStream(std::istream&);

private:
    explicit PacketizedMetadataStream(std::string&& text,
                                      Size packetCount,
                                      unsigned int majorVersion,
                                      unsigned int minorVersion,
                                      ByteOrder byteOrder,
                                      const boost::uuids::uuid& uuid);
    ~PacketizedMetadataStream();

public:
    /// Number of packets in this metadata stream.
    Size packetCount() const noexcept
    {
        return _packetCount;
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
        return _byteOrder;
    }

    /// UUID of this metadata stream.
    const boost::uuids::uuid& uuid() const noexcept
    {
        return _uuid;
    }

private:
    const Size _packetCount;
    const unsigned int _majorVersion;
    const unsigned int _minorVersion;
    const ByteOrder _byteOrder;
    const boost::uuids::uuid _uuid;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_PACKETIZED_METADATA_STREAM_HPP
