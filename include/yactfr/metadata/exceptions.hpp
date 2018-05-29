/*
 * Metadata exceptions.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Metadata exceptions.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_EXCEPTIONS_HPP
#define _YACTFR_METADATA_EXCEPTIONS_HPP

#include <stdexcept>
#include <vector>

#include <yactfr/aliases.hpp>
#include "metadata-base.hpp"
#include "metadata-text-location.hpp"
#include "aliases.hpp"

namespace yactfr {

/*!
@brief  No such type ID.

@ingroup metadata
*/
class NoSuchTypeId final :
    public std::runtime_error,
    public MetadataBase
{
public:
    explicit NoSuchTypeId(const TypeId id) :
        std::runtime_error {"No such type ID"},
        _id {id}
    {
    }

    /// Type ID which cannot be found.
    TypeId id() const noexcept
    {
        return _id;
    }

private:
    const TypeId _id;
};

/*!
@brief  No such index.

@ingroup metadata
*/
class NoSuchIndex final :
    public std::runtime_error,
    public MetadataBase
{
public:
    explicit NoSuchIndex(const Index index) :
        std::runtime_error {"No such index"},
        _index {index}
    {
    }

    /// Index which cannot be found.
    Index index() const noexcept
    {
        return _index;
    }

private:
    const std::size_t _index;
};

/// No such field name.
class NoSuchName :
    public std::runtime_error,
    public MetadataBase
{
public:
    explicit NoSuchName(const std::string& name) :
        std::runtime_error {"No such name"},
        _name {name}
    {
    }

    /// Field name which cannot be found.
    const std::string& name() const noexcept
    {
        return _name;
    }

private:
    const std::string _name;
};

/*!
@brief  Invalid metadata.

@ingroup metadata
*/
class InvalidMetadata final :
    public std::runtime_error
{
public:
    explicit InvalidMetadata(const std::string& msg) :
        std::runtime_error {msg}
    {
    }
};

namespace internal {
    template <typename CharIt>
    class TsdlParser;

    class TsdlParserBase;
}

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
the original text, considering that the first character of the string
is at line number 0 and column number 0.
*/
class MetadataParseError final :
    public std::runtime_error,
    public MetadataBase
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

#endif // _YACTFR_METADATA_EXCEPTIONS_HPP
