/*
 * SPDX-FileCopyrightText: 2015-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/metadata-stream.hpp>
#include <yactfr/metadata/plain-text-metadata-stream.hpp>

namespace yactfr {

PlainTextMetadataStream::PlainTextMetadataStream(std::string text) :
    MetadataStream {std::move(text)}
{
}

} // namespace yactfr
