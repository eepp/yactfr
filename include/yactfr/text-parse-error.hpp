/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_TEXT_PARSE_ERROR_HPP
#define YACTFR_TEXT_PARSE_ERROR_HPP

#include <string>
#include <vector>
#include <stdexcept>

#include "text-loc.hpp"

namespace yactfr {

class TextParseError;

/*!
@brief
    Single error message of a
    \link TextParseError text parse error\endlink.

@ingroup common
*/
class TextParseErrorMessage final
{
    friend class TextParseError;

private:
    explicit TextParseErrorMessage(std::string message, TextLocation location);

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

class TextParseError;

namespace internal {

[[ noreturn ]] void throwTextParseError(std::string msg, TextLocation loc = TextLocation {});
void appendMsgToTextParseError(TextParseError& exc, std::string msg, TextLocation loc = TextLocation {});

} // namespace internal

/*!
@brief
    Text parse error.

@ingroup common

An instance is thrown when there is a text parse error.

The exception object contains a stack of error messages (in reverse
order) which place the error in its parsing context. Each error message
has a text location (offset and line/column numbers) to indicate where
it's located in the original text.
*/
class TextParseError final :
    public std::runtime_error
{
    friend void internal::throwTextParseError(std::string, TextLocation);
    friend void internal::appendMsgToTextParseError(TextParseError&, std::string, TextLocation);

private:
    explicit TextParseError(std::string initMsg, TextLocation initLoc);
    explicit TextParseError(std::string initMsg);

public:
    /// Error messages (the first message is the most precise).
    const std::vector<TextParseErrorMessage>& messages() const noexcept
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
    std::vector<TextParseErrorMessage> _msgs;
    std::string _fullError;
};

} // namespace yactfr

#endif // YACTFR_TEXT_PARSE_ERROR_HPP
