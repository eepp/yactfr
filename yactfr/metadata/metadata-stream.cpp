/*
 * SPDX-FileCopyrightText: 2016-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <cassert>
#include <cstring>

#include <yactfr/metadata/metadata-stream.hpp>

namespace yactfr {

MetadataStream::MetadataStream(std::string&& text) :
    _text {std::move(text)}
{
}

unsigned int MetadataStream::majorVersion() const noexcept
{
    if (_text.empty()) {
        /*
         * Only a packetized metadata stream, which is always CTF 1,
         * may have an empty text (all its packets are empty).
         */
        return 1;
    }

    // CTF 2 if the text starts with a record separator (RS) byte
    return _text[0] == 30 ? 2 : 1;
}

bool MetadataStream::hasCtf1Signature() const noexcept
{
    static const std::string sig {"/* CTF 1.8"};

    // using std::strncmp() to avoid exceptions
    return std::strncmp(_text.c_str(), sig.c_str(), sig.size()) == 0;
}

} // namespace yactfr
