/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_FROM_METADATA_TEXT_HPP
#define _YACTFR_FROM_METADATA_TEXT_HPP

#include <utility>

#include "metadata/internal/tsdl-parser.hpp"
#include "metadata/trace-type.hpp"
#include "trace-env.hpp"

namespace yactfr {

/*!
@brief
    Builds trace type and trace environment objects by parsing the
    metadata text from \p begin to \p end.

@ingroup trace

Because this template uses another, quite heavy template, it's
recommended, if you are to use this function using the same
\p CharIt template parameter in different translation units, that you
create a non-templated, specialized version in its own source file, for
example:

@code
std::pair<yactfr::Trace::UP, yactfr::TraceEnvironment> fromMetadataText(const std::string& str)
{
    return yactfr::fromMetadataText(str.begin(), str.end());
}
@endcode

@tparam CharIt
    Random access character iterator type.
@param[in] begin
    Beginning of metadata text.
@param[in] end
    End of metadata text.

@returns
    @parblock
    Pair of:

    -# \link TraceType Trace type\endlink
    -# \link TraceEnvironment Trace environment\endlink
    @endparblock

@throws MetadataParseError
    An error occurred while parsing the document.
*/
template <typename CharIt>
std::pair<TraceType::UP, TraceEnvironment> fromMetadataText(const CharIt begin, const CharIt end)
{
    internal::TsdlParser<CharIt> parser {begin, end};

    return std::make_pair(parser.releaseTraceType(), parser.traceEnv());
}

} // namespace yactfr

#endif // _YACTFR_FROM_METADATA_TEXT_HPP
