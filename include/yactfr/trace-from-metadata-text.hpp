/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TRACE_FROM_METADATA_TEXT_HPP
#define _YACTFR_TRACE_FROM_METADATA_TEXT_HPP

#include "metadata/internal/tsdl-parser.hpp"
#include "trace.hpp"

namespace yactfr {

/*!
@brief
    Builds a trace object by parsing the metadata text from
    \p begin to \p end.

@ingroup trace

Because this template uses another, quite heavy template, it is
recommended, if you are to use this function using the same
\p CharIt template parameter in different translation units, that you
create a non-templated, specialized version in its own source file, for
example:

@code
yactfr::Trace::UP traceFromMetadataText(const std::string& str)
{
    return yactfr::traceFromMetadataText(str.begin(), str.end());
}
@endcode

@tparam CharIt
    Random access character iterator type.
@param[in] begin
    Beginning of string.
@param[in] end
    End of string.

@returns
    New trace object.

@throws MetadataParseError
    An error occureed while parsing the document.
*/
template <typename CharIt>
Trace::UP traceFromMetadataText(const CharIt begin, const CharIt end)
{
    internal::TsdlParser<CharIt> parser {begin, end};

    return std::make_unique<Trace>(parser.releaseTraceType(), parser.traceEnv());
}

} // namespace yactfr

#endif // _YACTFR_TRACE_FROM_METADATA_TEXT_HPP
