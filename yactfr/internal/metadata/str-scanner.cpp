/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/text-parse-error.hpp>

#include "str-scanner.hpp"

namespace yactfr {
namespace internal {

const std::regex StrScanner::_realRegex {
    "^"                     // start of target
    "-?"                    // optional negation
    "(?:0|[1-9]\\d*)"       // integer part
    "(?=[eE.]\\d)"          // assertion: need fraction/exponent part
    "(?:\\.\\d+)?"          // optional fraction part
    "(?:[eE][+-]?\\d+)?",   // optional exponent part
    std::regex::optimize
};

StrScanner::StrScanner(const char * const begin, const char * const end) : //-V730
    _begin {begin},
    _end {end},
    _at {begin},
    _lineBegin {begin}
{
}

void StrScanner::reset()
{
    _stack.clear();
    _at = _begin;
    _nbLines = 0;
    _lineBegin = _begin;
}

void StrScanner::reject()
{
    assert(!_stack.empty());
    _at = _stack.back().at;
    _lineBegin = _stack.back().lineBegin;
    _nbLines = _stack.back().nbLines;
    _stack.pop_back();
}

void StrScanner::_skipWhitespaces()
{
    while (!this->isDone()) {
        if (*_at != ' ' && *_at != '\t' && *_at != '\v' && *_at != '\n' && *_at != '\r') {
            return;
        }

        this->_checkNewLine();
        ++_at;
    }
}

void StrScanner::_appendEscapedUnicodeChar(const char * const at)
{
    // create array of four hex characters
    const std::string hexCpBuf {at, at + 4};

    // validate hex characters
    for (const auto ch : hexCpBuf) {
        if (!std::isxdigit(ch)) {
            std::ostringstream ss;

            ss << "In `\\u` escape sequence: unexpected character `" << ch << "`.";
            throwTextParseError(ss.str(), this->loc());
        }
    }

    // convert hex characters to integral codepoint (always works)
    const auto cp = std::strtoull(hexCpBuf.data(), nullptr, 16);

    // append UTF-8 bytes from integral codepoint
    if (cp <= 0x7f) {
        _strBuf.push_back(cp);
    } else if (cp <= 0x7ff) {
        _strBuf.push_back(static_cast<char>((cp >> 6) + 192));
        _strBuf.push_back(static_cast<char>((cp & 63) + 128));
    } else if (cp > 0xd800 && cp <= 0xdfff) {
        std::ostringstream ss;

        ss << "In `\\u` escape sequence: invalid codepoint " << cp << ".";
        throwTextParseError(ss.str(), this->loc());
    } else if (cp <= 0xffff) {
        _strBuf.push_back(static_cast<char>((cp >> 12) + 224));
        _strBuf.push_back(static_cast<char>(((cp >> 6) & 63) + 128));
        _strBuf.push_back(static_cast<char>((cp & 63) + 128));
    } else if (cp <= 0x10ffff) {
        _strBuf.push_back(static_cast<char>((cp >> 18) + 240));
        _strBuf.push_back(static_cast<char>(((cp >> 12) & 63) + 128));
        _strBuf.push_back(static_cast<char>(((cp >> 6) & 63) + 128));
        _strBuf.push_back(static_cast<char>((cp & 63) + 128));
    }
}

void StrScanner::_appendEscapedHexChar(const char * const at)
{
    // create array of two hex characters
    const std::string hexByteBuf {at, at + 2};

    // validate hex characters
    for (const auto ch : hexByteBuf) {
        if (!std::isxdigit(ch)) {
            std::ostringstream ss;

            ss << "In `\\x` escape sequence: unexpected character `" << ch << "`.";
            throwTextParseError(ss.str(), this->loc());
        }
    }

    // convert hex characters to byte (always works)
    const auto byte = std::strtoull(hexByteBuf.data(), nullptr, 16);

    // validate value
    if (byte == 0) {
        throwTextParseError("Invalid `\\x00` escape sequence.", this->loc());
    }

    // append byte
    _strBuf.push_back(static_cast<char>(byte));
}

bool StrScanner::_tryAppendEscapedChar(const char * const escapeSeqStartList)
{
    if (this->charsLeft() < 2) {
        return false;
    }

    if (_at[0] != '\\') {
        return false;
    }

    auto escapeSeqStart = escapeSeqStartList;

    while (*escapeSeqStart != '\0') {
        if (_at[1] == '"' || _at[1] == '\\' || _at[1] == *escapeSeqStart) {
            if (_at[1] == 'u') {
                if (this->charsLeft() < 6) {
                    throwTextParseError("`\\u` escape sequence needs four hexadecimal digits.",
                                        this->loc());
                }

                this->_appendEscapedUnicodeChar(_at + 2);
                _at += 6;
            } else if (_at[1] == 'x') {
                if (this->charsLeft() < 4) {
                    throwTextParseError("`\\x` escape sequence needs two hexadecimal digits.",
                                        this->loc());
                }

                this->_appendEscapedHexChar(_at + 2);
                _at += 4;
            } else {
                switch (_at[1]) {
                case 'a':
                    _strBuf.push_back('\a');
                    break;

                case 'b':
                    _strBuf.push_back('\b');
                    break;

                case 'f':
                    _strBuf.push_back('\f');
                    break;

                case 'n':
                    _strBuf.push_back('\n');
                    break;

                case 'r':
                    _strBuf.push_back('\r');
                    break;

                case 't':
                    _strBuf.push_back('\t');
                    break;

                case 'v':
                    _strBuf.push_back('\v');
                    break;

                default:
                    // as is
                    _strBuf.push_back(_at[1]);
                    break;
                }

                _at += 2;
            }

            return true;
        }

        ++escapeSeqStart;
    }

    return false;
}

void StrScanner::_skipComment()
{
    if (this->charsLeft() >= 2) {
        if (*_at == '/') {
            switch (*(_at + 1)) {
            case '/':
                // single-line comment
                _at += 2;

                while (!this->isDone()) {
                    /*
                     * TODO: Handle `\` to continue the comment on the
                     * next line.
                     */
                    if (*_at == '\n') {
                        /*
                         * We don't set a newline here because the
                         * current position is left at the newline
                         * character, which is considered excluded from
                         * the comment itself.
                         */
                        return;
                    }

                    ++_at;
                }
                break;

            case '*':
                // multi-line comment
                _at += 2;

                while (!this->isDone()) {
                    if (this->charsLeft() >= 2) {
                        if (*_at == '*' && *(_at + 1) == '/') {
                            _at += 2;
                            return;
                        }
                    }

                    this->_checkNewLine();
                    ++_at;
                }
                break;

            default:
                break;
            }
        }
    }
}

} // namespace internal
} // namespace yactfr
