/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/from-metadata-text.hpp>
#include <yactfr/text-parse-error.hpp>

#include "internal/metadata/tsdl/tsdl-parser.hpp"
#include "internal/metadata/json/ctf-2-json-seq-parser.hpp"

namespace yactfr {

std::pair<TraceType::UP, TraceEnvironment> fromMetadataText(const char * const begin,
                                                            const char * const end)
{
    if (begin == end) {
        internal::throwTextParseError("Empty metadata text.", TextLocation {});
    }

    if (*begin == 30) {
        // starts with the RS byte: expect CTF 2
        internal::Ctf2JsonSeqParser parser {begin, end};

        return std::make_pair(parser.releaseTraceType(), TraceEnvironment {});
    } else {
        // fall back to CTF 1.8
        internal::TsdlParser parser {begin, end};

        return std::make_pair(parser.releaseTraceType(), parser.traceEnv());
    }
}

} // namespace yactfr
