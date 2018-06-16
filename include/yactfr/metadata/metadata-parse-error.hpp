/*
 * Metadata parse error.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Metadata parse error.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_METADATA_PARSE_ERROR_HPP
#define _YACTFR_METADATA_METADATA_PARSE_ERROR_HPP

// for std::string
#include <string>

// for std::vector
#include <vector>

// for std::runtime_error
#include <stdexcept>

// for MetadataTextLocation
#include "metadata-text-location.hpp"

namespace yactfr {
namespace internal {

template <typename CharIt>
class TsdlParser;

class TsdlParserBase;

} // namespace internal

class MetadataParseError;

/*!
@brief  Single error message of a MetadataParseError.

@ingroup metadata
*/
class MetadataParseErrorMessage final
{
    template <typename CharIt>
    friend class internal::TsdlParser;

    friend class MetadataParseError;

private:
    explicit MetadataParseErrorMessage(const std::string& message,
                                       const MetadataTextLocation& location);

public:
    /// Source location where this error message occured.
    const MetadataTextLocation& location() const noexcept
    {
        return _location;
    }

    /// Message.
    const std::string& message() const noexcept
    {
        return _message;
    }

private:
    std::string _message;
    MetadataTextLocation _location;
};

/*!
@brief  Metadata parsing error.

@ingroup metadata

This is thrown when there is a metadata text parsing error.

The exception object contains a stack of error messages (in reverse
order) which place the error in its parsing context. Each error message
has a source location (line and column numbers) where it is located in
the original text.
*/
class MetadataParseError final :
    public std::runtime_error
{
    friend class internal::TsdlParserBase;

    template <typename CharIt>
    friend class internal::TsdlParser;

private:
    explicit MetadataParseError(const std::string& initMessage,
                                const MetadataTextLocation& initLocation);

    explicit MetadataParseError(const std::string& initMessage);

public:
    /*!
    @brief  Error messages.

    The first message is the closest to the location where this
    error occured.
    */
    const std::vector<MetadataParseErrorMessage>& errorMessages() const noexcept
    {
        return _errorMessages;
    }

    const char* what() const noexcept override
    {
        return _fullError.c_str();
    }

private:
    void _appendErrorMessage(const std::string& message,
                             const MetadataTextLocation& location);
    void _buildFullError();

private:
    std::vector<MetadataParseErrorMessage> _errorMessages;
    std::string _fullError;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_METADATA_PARSE_ERROR_HPP
