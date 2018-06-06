/*
 * Metadata functions.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Common metadata functions, types, and enumerations.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_METADATA_HPP
#define _YACTFR_METADATA_METADATA_HPP

#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/internal/tsdl-parser.hpp>
#include <boost/optional.hpp>
#include <istream>
#include <memory>

#include "metadata-base.hpp"
#include "metadata-stream.hpp"

namespace yactfr {

/*!
@brief  Invalid metadata stream error.

@ingroup metadata

This is thrown when there is an error while reading a metadata stream
(when you call createMetadataStream()) which is not an I/O error
(IOError is thrown in this case). In other words, the stream is
successfully read, but the binary content of the file is invalid.
*/
class InvalidMetadataStream final :
    public std::runtime_error
{
public:
    explicit InvalidMetadataStream(const std::string& msg, Index offset);

    /// Offset (bytes) in metadata stream at which the error occured.
    Index offset() const noexcept
    {
        return _offset;
    }

private:
    Index _offset;
};

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

/*!
@brief  Builds a metadata stream object by decoding the whole stream
        \p stream.

@ingroup metadata

The resulting stream is either a PlainTextMetadataStream or a
PacketizedMetadataStream.

\p stream is only used in this function and does not belong
to the returned metadata stream. This function does not seek within
\p stream.

@param stream   Metadata stream to read.

@throws IOError An I/O error occured.
@throws InvalidMetadataStream The metadata stream's content is invalid.
*/
std::unique_ptr<const MetadataStream> createMetadataStream(std::istream& stream);

} // namespace yactfr

#endif // _YACTFR_METADATA_METADATA_HPP
