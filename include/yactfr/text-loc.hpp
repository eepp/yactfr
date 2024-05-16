/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_TEXT_LOC_HPP
#define YACTFR_TEXT_LOC_HPP

#include "aliases.hpp"

namespace yactfr {

/*!
@brief
    Location in a multiline text.

@ingroup common
*/
class TextLocation final
{
public:
    /*!
    @brief
        Builds a default text location (first line, first column).
    */
    explicit TextLocation() = default;

    /*!
    @brief
        Builds a text location which targets offset \p offset bytes,
        zero-based line number \p lineNumber, zero-based column number
        \p columnNumber.

    @param[in] offset
        Offset (bytes).
    @param[in] lineNumber
        Line number (zero-based) of the text location.
    @param[in] columnNumber
        Column number (zero-based) of the text location.
    */
    explicit TextLocation(Index offset, Index lineNumber, Index columnNumber) noexcept;

    /// Default copy constructor.
    TextLocation(const TextLocation&) = default;

    /// Default move constructor.
    TextLocation(TextLocation&&) = default;

    /// Default copy assignment operator.
    TextLocation& operator=(const TextLocation&) = default;

    /// Default move assignment operator.
    TextLocation& operator=(TextLocation&&) = default;

    /// Offset (bytes).
    Index offset() const noexcept
    {
        return _offset;
    }

    /// Line number (zero-based).
    Index lineNumber() const noexcept
    {
        return _lineNumber;
    }

    /// Column number (zero-based).
    Index columnNumber() const noexcept
    {
        return _colNumber;
    }

    /// Line number (one-based).
    Index naturalLineNumber() const noexcept
    {
        return _lineNumber + 1;
    }

    /// Column number (one-based).
    Index naturalColumnNumber() const noexcept
    {
        return _colNumber + 1;
    }

private:
    Index _offset = 0;
    Index _lineNumber = 0;
    Index _colNumber = 0;
};

} // namespace yactfr

#endif // YACTFR_TEXT_LOC_HPP
