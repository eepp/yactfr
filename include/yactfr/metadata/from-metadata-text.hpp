/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FROM_METADATA_TEXT_HPP
#define _YACTFR_METADATA_FROM_METADATA_TEXT_HPP

#include <utility>
#include <string>
#include <boost/uuid/uuid.hpp>

#include "trace-type.hpp"

namespace yactfr {

/*!
@brief
    Return type of fromMetadataText().

@ingroup metadata

Pair of:

-# \link TraceType Trace type\endlink
-# Optional metadata stream UUID
*/
using FromMetadataTextReturn = std::pair<TraceType::UP, boost::optional<boost::uuids::uuid>>;

/*!
@brief
    Builds trace type and metadata stream UUID objects by parsing the
    metadata text from \p begin to \p end.

@ingroup metadata

This method automatically discovers whether the text between \p begin
and \p end is a CTF&nbsp;1.8 or CTF&nbsp;2 metadata text.

@param[in] begin
    Beginning of metadata text.
@param[in] end
    End of metadata text.

@returns
    Resulting trace type and optional metadata stream UUID pair.

@throws TextParseError
    An error occurred while parsing the document.
*/
FromMetadataTextReturn fromMetadataText(const char *begin, const char *end);

/*!
@brief
    Builds trace type and metadata stream UUID objects by parsing the
    metadata text \p text.

@ingroup metadata

This method automatically discovers whether \p text is a CTF&nbsp;1.8 or
CTF&nbsp;2 metadata text.

@param[in] text
    Metadata text.

@returns
    Resulting trace type and optional metadata stream UUID pair.

@throws TextParseError
    An error occurred while parsing the document.
*/
static inline FromMetadataTextReturn fromMetadataText(const std::string& text)
{
    return fromMetadataText(text.data(), text.data() + text.size());
}

} // namespace yactfr

#endif // _YACTFR_METADATA_FROM_METADATA_TEXT_HPP
