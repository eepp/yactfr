/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INVALID_METADATA_STREAM_HPP
#define _YACTFR_METADATA_INVALID_METADATA_STREAM_HPP

#include <stdexcept>
#include <string>

#include "../aliases.hpp"

namespace yactfr {

/*!
@brief
    Invalid metadata stream error.

@ingroup metadata

An instance is thrown when there's an error while reading a metadata
stream (when you call createMetadataStream()) which is \em not an I/O
error (createMetadataStream() throws an IOError instance in this case).

In other words, the stream is successfully read, but the binary content
of the file is invalid.
*/
class InvalidMetadataStream final :
    public std::runtime_error
{
public:
    explicit InvalidMetadataStream(std::string message, Index offset);

    /// Offset (bytes) in metadata stream at which the error occured.
    Index offset() const noexcept
    {
        return _offset;
    }

private:
    Index _offset;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_INVALID_METADATA_STREAM_HPP
