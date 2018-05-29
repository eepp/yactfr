/*
 * Plain text metadata stream.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Plain text metadata stream.

@ingroup metadata_stream
*/

#ifndef _YACTFR_METADATA_PLAIN_TEXT_METADATA_STREAM_HPP
#define _YACTFR_METADATA_PLAIN_TEXT_METADATA_STREAM_HPP

#include <string>
#include <cstdlib>
#include <memory>
#include <boost/uuid/uuid.hpp>

#include <yactfr/aliases.hpp>

#include "metadata-stream.hpp"

namespace yactfr {

namespace internal {
struct PlainTextMetadataStreamImpl;
}

/*!
@brief  Plain text metadata stream.

@ingroup metadata_stream

A plain text metadata stream is roughly a string container.
*/
class PlainTextMetadataStream final :
    public MetadataStream
{
    friend std::unique_ptr<const MetadataStream> createMetadataStream(std::istream&);

private:
    explicit PlainTextMetadataStream(std::string&& text);

public:
    ~PlainTextMetadataStream();
};

} // namespace yactfr

#endif // _YACTFR_METADATA_PLAIN_TEXT_METADATA_STREAM_HPP
