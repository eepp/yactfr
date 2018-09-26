/*
 * Trace type from metadata text function.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Trace type from metadata text function.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_TRACE_TYPE_FROM_METADATA_TEXT_HPP
#define _YACTFR_METADATA_TRACE_TYPE_FROM_METADATA_TEXT_HPP

// for boost::optional
#include <boost/optional.hpp>

// for internal::TsdlParser
#include "internal/tsdl-parser.hpp"

// for TraceType
#include "trace-type.hpp"

namespace yactfr {

class TraceType;

/*!
@brief  Builds a trace type object by parsing the metadata text from
        \p begin to \p end.

Because this template uses another, quite heavy template, it is
recommended, if you are to use this function using the same
\p CharIt template parameter in different translation units, that you
create a non-templated, specialized version in its own source file,
for example:

@code
yactfr::TraceType::SP traceTypeFromMetadataText(const std::string& str,
                                                const boost::optional<boost::uuids::uuid>& expectedUuid)
{
    return yactfr::traceTypeFromMetadataText(std::begin(str), std::end(str),
                                             expectedUuid);
}
@endcode

@ingroup metadata

@tparam CharIt      Random access character iterator type.
@param begin        Beginning of string.
@param end          End of string.
@param expectedUuid UUID to expect (\c boost::none by default).
@returns            New trace type object.

@throws MetadataParseError  An error occured while parsing the document.
*/
template <typename CharIt>
TraceType::SP traceTypeFromMetadataText(CharIt begin, CharIt end,
                                        const boost::optional<boost::uuids::uuid>& expectedUuid)
{
    return internal::TsdlParser<CharIt> {begin, end, expectedUuid}.traceType();
}

} // namespace yactfr

#endif // _YACTFR_METADATA_TRACE_TYPE_FROM_METADATA_TEXT_HPP
