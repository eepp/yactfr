/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>

#include <yactfr/text-parse-error.hpp>

namespace yactfr {

TextParseErrorMessage::TextParseErrorMessage(std::string msg, TextLocation loc) :
    _msg {std::move(msg)},
    _loc {std::move(loc)}
{
}

TextParseError::TextParseError(std::string initMsg, TextLocation initLoc) :
    std::runtime_error {"Parse error"}
{
    _msgs.push_back(TextParseErrorMessage {std::move(initMsg), std::move(initLoc)});
    this->_buildFullError();
}

TextParseError::TextParseError(std::string initMsg) :
    TextParseError {std::move(initMsg), TextLocation {0, 0, 0}}
{
}

void TextParseError::_appendErrorMsg(std::string msg, TextLocation loc)
{
    _msgs.push_back(TextParseErrorMessage {std::move(msg), std::move(loc)});
    this->_buildFullError();
}

void TextParseError::_appendErrorMsg(std::string msg)
{
    this->_appendErrorMsg(std::move(msg), TextLocation {0, 0, 0});
}

void TextParseError::_buildFullError()
{
    std::ostringstream ss;

    for (auto it = _msgs.rbegin(); it != _msgs.rend(); ++it) {
        ss << "[" << it->location().naturalLineNumber() << ":" <<
              it->location().naturalColumnNumber() << "] ";
        ss << it->message() << std::endl;
    }

    _fullError = ss.str();
}

namespace internal {

void throwTextParseError(std::string msg, TextLocation loc)
{
    throw TextParseError {std::move(msg), std::move(loc)};
}

void appendMsgToTextParseError(TextParseError& exc, std::string msg, TextLocation loc)
{
    exc._appendErrorMsg(std::move(msg), std::move(loc));
}

}

} // namespace yactfr
