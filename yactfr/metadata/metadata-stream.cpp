/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstring>

#include <yactfr/metadata/metadata-stream.hpp>

namespace yactfr {

MetadataStream::MetadataStream(std::string&& text) :
    _text {std::move(text)}
{
}

unsigned int MetadataStream::majorVersion() const noexcept
{
    return 1;
}

bool MetadataStream::hasCtf1Signature() const noexcept
{
    static const std::string sig {"/* CTF 1.8"};

    // using std::strncmp() to avoid exceptions
    return std::strncmp(_text.c_str(), sig.c_str(), sig.size()) == 0;
}

} // namespace yactfr
