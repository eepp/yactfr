/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_FROM_METADATA_TEXT_HPP
#define _YACTFR_FROM_METADATA_TEXT_HPP

#include <utility>
#include <string>

#include "metadata/trace-type.hpp"
#include "trace-env.hpp"

namespace yactfr {

/*!
@brief
    Builds trace type and trace environment objects by parsing the
    metadata text from \p begin to \p end.

@ingroup trace

This method automatically discovers whether the text between \p begin
and \p end is a CTF&nbsp;1.8 or CTF&nbsp;2 metadata text.

@param[in] begin
    Beginning of metadata text.
@param[in] end
    End of metadata text.

@returns
    @parblock
    Pair of:

    -# \link TraceType Trace type\endlink
    -# \link TraceEnvironment Trace environment\endlink (always empty
       with a CTF 2 metadata text)
    @endparblock

@throws TextParseError
    An error occurred while parsing the document.
*/
std::pair<TraceType::UP, TraceEnvironment> fromMetadataText(const char *begin, const char *end);

/*!
@brief
    Builds trace type and trace environment objects by parsing the
    metadata text \p text.

@ingroup trace

This method automatically discovers whether \p text is a CTF&nbsp;1.8 or
CTF&nbsp;2 metadata text.

@param[in] text
    Metadata text.

@returns
    @parblock
    Pair of:

    -# \link TraceType Trace type\endlink
    -# \link TraceEnvironment Trace environment\endlink (always empty
       with a CTF 2 metadata text)
    @endparblock

@throws TextParseError
    An error occurred while parsing the document.
*/
static inline std::pair<TraceType::UP, TraceEnvironment> fromMetadataText(const std::string& text)
{
    return fromMetadataText(text.data(), text.data() + text.size());
}

} // namespace yactfr

#endif // _YACTFR_FROM_METADATA_TEXT_HPP
