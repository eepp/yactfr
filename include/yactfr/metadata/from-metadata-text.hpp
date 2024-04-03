/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_FROM_METADATA_TEXT_HPP
#define YACTFR_METADATA_FROM_METADATA_TEXT_HPP

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
using FromMetadataTextReturn = std::pair<TraceType::Up, boost::optional<boost::uuids::uuid>>;

/*!
@brief
    Builds trace type and metadata stream UUID objects by parsing the
    metadata text from \p begin to \p end.

@ingroup metadata

This function automatically discovers whether the text between \p begin
and \p end is a CTF&nbsp;1.8 or CTF&nbsp;2 metadata text.

@note
    @parblock
    For CTF&nbsp;1.8, this function sets the following
    \link ClockType clock type\endlink properties accordingly
    from a TSDL clock type <em>CC</em>:

    <dl>
      <dt>Internal ID</dt>
      <dd>Value of the \c name attribute of \em CC.</dd>

      <dt>Namespace</dt>
      <dd>None.</dd>

      <dt>Name</dt>
      <dd>
        Value of the \c name attribute of <em>CC</em>,
        or none if missing.
      </dd>

      <dt>Unique ID (UID)</dt>
      <dd>
        Value of the \c uuid attribute of <em>CC</em>,
        or none if it's is missing.
      </dd>

      <dt>Original UUID</dt>
      <dd>
        Equivalent UUID of the value of the \c uuid attribute of \em CC,
        or \c boost::none if missing.
      </dd>

      <dt>Origin</dt>
      <dd>
        Unix epoch if the \c absolute attribute of \em CC is true,
        or \c boost::none if missing.
      </dd>

      <dt>Precision</dt>
      <dd>
        Value of the \c precision attribute of \em CC,
        or \c boost::none if missing.
      </dd>

      <dt>Accuracy</dt>
      <dd>\c boost::none.
    </dl>
    @endparblock

@note
    For CTF&nbsp;1.8, if the TSDL trace type has a \c uuid attribute,
    then this function sets the unique ID property to the value of the
    \c uuid attribute.

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

This function effectively calls
fromMetadataText(const char *, const char *), therefore refer to its
documentation.

@param[in] text
    Metadata text.

@returns
    Resulting trace type and optional metadata stream UUID pair.

@throws TextParseError
    An error occurred while parsing the document.
*/
inline FromMetadataTextReturn fromMetadataText(const std::string& text)
{
    return fromMetadataText(text.data(), text.data() + text.size());
}

} // namespace yactfr

#endif // YACTFR_METADATA_FROM_METADATA_TEXT_HPP
