/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/metadata-stream.hpp>
#include <yactfr/metadata/plain-text-metadata-stream.hpp>

namespace yactfr {

PlainTextMetadataStream::PlainTextMetadataStream(std::string&& text) :
    MetadataStream {std::move(text)}
{
}

PlainTextMetadataStream::~PlainTextMetadataStream()
{
}

} // namespace yactfr
