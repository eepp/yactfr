/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/from-metadata-text.hpp>
#include <yactfr/text-parse-error.hpp>

#include "../internal/metadata/tsdl/tsdl-parser.hpp"
#include "../internal/metadata/json/ctf-2-json-seq-parser.hpp"

namespace yactfr {

template <typename ParserT>
FromMetadataTextReturn fromMetadataText(const char * const begin, const char * const end)
{
    ParserT parser {begin, end};

    return std::make_pair(parser.releaseTraceType(), parser.metadataStreamUuid());
}

FromMetadataTextReturn fromMetadataText(const char * const begin,
                                                            const char * const end)
{
    if (begin == end) {
        internal::throwTextParseError("Empty metadata text.", TextLocation {});
    }

    if (*begin == 30) {
        // starts with the RS byte: expect CTF 2
        return fromMetadataText<internal::Ctf2JsonSeqParser>(begin, end);
    } else {
        // fall back to CTF 1.8
        return fromMetadataText<internal::TsdlParser>(begin, end);
    }
}

} // namespace yactfr
