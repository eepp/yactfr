/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/from-metadata-text.hpp>

#include "metadata/tsdl-parser.hpp"

namespace yactfr {

std::pair<TraceType::UP, TraceEnvironment> fromMetadataText(const char * const begin,
                                                            const char * const end)
{
    internal::TsdlParser parser {begin, end};

    return std::make_pair(parser.releaseTraceType(), parser.traceEnv());
}

} // namespace yactfr
