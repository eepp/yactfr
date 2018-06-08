/*
 * Metadata stream.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Metadata stream and related exception.

@ingroup metadata_stream
*/

#ifndef _YACTFR_METADATA_METADATA_STREAM_HPP
#define _YACTFR_METADATA_METADATA_STREAM_HPP

#include <cstdlib>
#include <string>
#include <stdexcept>
#include <memory>
#include <istream>
#include <boost/uuid/uuid.hpp>

#include <yactfr/aliases.hpp>

namespace yactfr {

/*!
@brief  Invalid metadata stream error.

@ingroup metadata

This is thrown when there is an error while reading a metadata stream
(when you call createMetadataStream()) which is not an I/O error
(IOError is thrown in this case). In other words, the stream is
successfully read, but the binary content of the file is invalid.
*/
class InvalidMetadataStream final :
    public std::runtime_error
{
public:
    explicit InvalidMetadataStream(const std::string& msg, Index offset);

    /// Offset (bytes) in metadata stream at which the error occured.
    Index offset() const noexcept
    {
        return _offset;
    }

private:
    Index _offset;
};

/*!
@brief  Metadata stream.

@ingroup metadata_stream
*/
class MetadataStream
{
protected:
    explicit MetadataStream(std::string&& text);

public:
    virtual ~MetadataStream();

    /// Metadata text.
    const std::string& text() const noexcept
    {
        return _text;
    }

    /// \c true if the metadata text has a recognized signature,
    /// that is, <code>/* CTF 1.8</code>.
    bool hasSignature() const noexcept;

private:
    const std::string _text;
};

/*!
@brief  Builds a metadata stream object by decoding the whole stream
        \p stream.

@ingroup metadata

The resulting stream is either a PlainTextMetadataStream or a
PacketizedMetadataStream.

\p stream is only used in this function and does not belong
to the returned metadata stream. This function does not seek within
\p stream.

@param stream   Metadata stream to read.

@throws IOError An I/O error occured.
@throws InvalidMetadataStream The metadata stream's content is invalid.
*/
std::unique_ptr<const MetadataStream> createMetadataStream(std::istream& stream);

} // namespace yactfr

#endif // _YACTFR_METADATA_METADATA_STREAM_HPP
