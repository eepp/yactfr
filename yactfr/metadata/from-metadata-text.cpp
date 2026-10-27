/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string_view>

#include <yactfr/metadata/from-metadata-text.hpp>
#include <yactfr/text-parse-error.hpp>

#include "../internal/metadata/tsdl/tsdl-parser.hpp"
#include "../internal/metadata/json/ctf-2-json-seq-parser.hpp"

namespace yactfr {

template <typename ParserT, typename... ArgTs>
FromMetadataTextReturn fromMetadataText(const ArgTs... args)
{
    ParserT parser {args...};

    return {parser.releaseTraceType(), parser.metadataStreamUuid()};
}

FromMetadataTextReturn fromMetadataText(const std::string_view text)
{
    if (text.empty()) {
        internal::throwTextParseError("Empty metadata text.", TextLocation {});
    }

    if (text.front() == 30) {
        // starts with the RS byte: expect CTF 2
        return fromMetadataText<internal::Ctf2JsonSeqParser>(text);
    } else {
        // fall back to CTF 1.8
        return fromMetadataText<internal::TsdlParser>(text);
    }
}

} // namespace yactfr
