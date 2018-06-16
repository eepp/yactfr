/*
 * "Invalid metadata" exception.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  "Invalid metadata" exception.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_INVALID_METADATA_STREAM_HPP
#define _YACTFR_METADATA_INVALID_METADATA_STREAM_HPP

// for std::runtime_error
#include <stdexcept>

// for std::string
#include <string>

// for Index
#include "../aliases.hpp"

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

} // namespace yactfr

#endif // _YACTFR_METADATA_INVALID_METADATA_STREAM_HPP
