/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_METADATA_PARSE_ERROR_HPP
#define _YACTFR_METADATA_METADATA_PARSE_ERROR_HPP

#include <string>
#include <vector>
#include <stdexcept>

#include "../text-loc.hpp"

namespace yactfr {
namespace internal {

template <typename CharIt>
class TsdlParser;

} // namespace internal

class MetadataParseError;

/*!
@brief
    Single error message of a
    \link MetadataParseError message parse error\endlink.

@ingroup metadata
*/
class MetadataParseErrorMessage final
{
    template <typename CharIt>
    friend class internal::TsdlParser;

    friend class MetadataParseError;

private:
    explicit MetadataParseErrorMessage(std::string message, TextLocation location);

public:
    /// Source location where this error message occurred.
    const TextLocation& location() const noexcept
    {
        return _loc;
    }

    /// Message.
    const std::string& message() const noexcept
    {
        return _msg;
    }

private:
    std::string _msg;
    TextLocation _loc;
};

class MetadataParseError;

namespace internal {

[[ noreturn ]] void throwMetadataParseError(std::string msg, TextLocation loc = {});
void appendMsgToMetadataParseError(MetadataParseError& exc, std::string msg, TextLocation loc = {});

} // namespace internal

/*!
@brief
    Metadata parse error.

@ingroup metadata

An instance is thrown when there is a metadata text parse error.

The exception object contains a stack of error messages (in reverse
order) which place the error in its parsing context. Each error message
has a text location (line and column numbers) to indicate where it's
located in the original text.
*/
class MetadataParseError final :
    public std::runtime_error
{
    friend void internal::throwMetadataParseError(std::string, TextLocation);
    friend void internal::appendMsgToMetadataParseError(MetadataParseError&, std::string, TextLocation);

private:
    explicit MetadataParseError(std::string initMsg, TextLocation initLoc);
    explicit MetadataParseError(std::string initMsg);

public:
    /// Error messages (the first message is the most precise).
    const std::vector<MetadataParseErrorMessage>& messages() const noexcept
    {
        return _msgs;
    }

    const char *what() const noexcept override
    {
        return _fullError.c_str();
    }

private:
    void _appendErrorMsg(std::string msg, TextLocation loc);
    void _appendErrorMsg(std::string msg);
    void _buildFullError();

private:
    std::vector<MetadataParseErrorMessage> _msgs;
    std::string _fullError;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_METADATA_PARSE_ERROR_HPP
