/*
 * Metadata parse error.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>

#include <yactfr/metadata/exceptions.hpp>

namespace yactfr {

MetadataParseErrorMessage::MetadataParseErrorMessage(const std::string& message,
                                                     const MetadataTextLocation& location) :
    _message {message},
    _location {location}
{
}

MetadataParseError::MetadataParseError(const std::string& initMessage,
                                       const MetadataTextLocation& initLocation) :
    std::runtime_error {"Parse error"}
{
    _errorMessages.push_back(MetadataParseErrorMessage {initMessage, initLocation});
    this->_buildFullError();
}

MetadataParseError::MetadataParseError(const std::string& initMessage) :
    MetadataParseError {initMessage, MetadataTextLocation {0, 0}}
{
}

void MetadataParseError::_appendErrorMessage(const std::string& message,
                                             const MetadataTextLocation& location)
{
    _errorMessages.push_back(MetadataParseErrorMessage {message, location});
    this->_buildFullError();
}


void MetadataParseError::_buildFullError()
{
    std::ostringstream ss;

    for (auto it = _errorMessages.rbegin(); it != _errorMessages.rend(); ++it) {
        ss << "[" << it->location().natLineNumber() << ":" <<
              it->location().natColNumber() << "] ";
        ss << it->message() << std::endl;
    }

    _fullError = ss.str();
}

} // namespace yactfr
