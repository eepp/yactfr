/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_METADATA_STREAM_HPP
#define YACTFR_METADATA_METADATA_STREAM_HPP

#include <string>
#include <istream>
#include <memory>

namespace yactfr {

/*!
@brief
    Metadata stream.

@ingroup metadata_stream
*/
class MetadataStream
{
protected:
    explicit MetadataStream(std::string&& text);

public:
    virtual ~MetadataStream() = default;

    /// Metadata text.
    const std::string& text() const noexcept
    {
        return _text;
    }

    /// Major CTF version (1 or 2).
    unsigned int majorVersion() const noexcept;

    /// @brief
    ///     \c true if the metadata text has a recognized initial
    ///     CTF&nbsp;1 signature, that is, <code>/* CTF 1.8</code>.
    bool hasCtf1Signature() const noexcept;

private:
    const std::string _text;
};

/*!
@brief
    Builds a metadata stream object by decoding the whole stream
    \p stream.

@ingroup metadata_stream

The resulting stream is either a
\link PlainTextMetadataStream plain text metadata stream\endlink or a
\link PacketizedMetadataStream packetized metadata stream\endlink.

Only this function uses \p stream: it doesn't belong to the returned
metadata stream. This function doesn't seek within \p stream.

@param[in] stream
    Metadata input stream to read.

@throws IOError
    An I/O error occurred.
@throws InvalidMetadataStream
    The content of the metadata stream is invalid.
*/
std::unique_ptr<const MetadataStream> createMetadataStream(std::istream& stream);

} // namespace yactfr

#endif // YACTFR_METADATA_METADATA_STREAM_HPP
