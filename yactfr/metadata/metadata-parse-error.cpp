/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>

#include <yactfr/metadata/metadata-parse-error.hpp>

namespace yactfr {

MetadataParseErrorMessage::MetadataParseErrorMessage(std::string msg, TextLocation loc) :
    _msg {std::move(msg)},
    _loc {std::move(loc)}
{
}

MetadataParseError::MetadataParseError(std::string initMsg, TextLocation initLoc) :
    std::runtime_error {"Parse error"}
{
    _msgs.push_back(MetadataParseErrorMessage {std::move(initMsg), std::move(initLoc)});
    this->_buildFullError();
}

MetadataParseError::MetadataParseError(std::string initMsg) :
    MetadataParseError {std::move(initMsg), TextLocation {0, 0}}
{
}

void MetadataParseError::_appendErrorMsg(std::string msg, TextLocation loc)
{
    _msgs.push_back(MetadataParseErrorMessage {std::move(msg), std::move(loc)});
    this->_buildFullError();
}

void MetadataParseError::_appendErrorMsg(std::string msg)
{
    this->_appendErrorMsg(std::move(msg), TextLocation {0, 0});
}

void MetadataParseError::_buildFullError()
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

void throwMetadataParseError(std::string msg, TextLocation loc)
{
    throw MetadataParseError {std::move(msg), std::move(loc)};
}

void appendMsgToMetadataParseError(MetadataParseError& exc, std::string msg, TextLocation loc)
{
    exc._appendErrorMsg(std::move(msg), std::move(loc));
}

}

} // namespace yactfr
