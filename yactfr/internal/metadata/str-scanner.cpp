/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <charconv>

#include <yactfr/text-parse-error.hpp>

#include "str-scanner.hpp"

namespace yactfr::internal {

const std::regex StrScanner::_realRegex {
    "^"                     // start of target
    "-?"                    // optional negation
    "(?:0|[1-9]\\d*)"       // integer part
    "(?=[eE.]\\d)"          // assertion: need fraction/exponent part
    "(?:\\.\\d+)?"          // optional fraction part
    "(?:[eE][+-]?\\d+)?",   // optional exponent part
    std::regex::optimize
};

StrScanner::StrScanner(const std::string_view str) noexcept :
    _str {str}
{
}

void StrScanner::reset()
{
    _stack.clear();
    _at = 0;
    _nbLines = 0;
    _lineBegin = 0;
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
        const auto ch = _str[_at];

        if (ch != ' ' && ch != '\t' && ch != '\v' && ch != '\n' && ch != '\r') {
            return;
        }

        this->_checkNewLine();
        ++_at;
    }
}

unsigned long StrScanner::_scanEscapedUnicodeCodeUnit(const std::string_view hexDigits)
{
    assert(hexDigits.size() >= 4);

    // four hex characters
    const auto hexCp = hexDigits.substr(0, 4);

    // validate hex characters
    for (const auto ch : hexCp) {
        if (!std::isxdigit(static_cast<unsigned char>(ch))) {
            std::ostringstream ss;

            ss << "In `\\u` escape sequence: unexpected character `" << ch << "`.";
            throwTextParseError(ss.str(), this->loc());
        }
    }

    // convert hex characters to integral code unit (always works)
    unsigned long codeUnit = 0;

    std::from_chars(hexCp.data(), hexCp.data() + hexCp.size(), codeUnit, 16);
    return codeUnit;
}

namespace {

bool isHighSurrogate(const unsigned long codeUnit) noexcept
{
    return codeUnit >= 0xd800 && codeUnit <= 0xdbff;
}

bool isLowSurrogate(const unsigned long codeUnit) noexcept
{
    return codeUnit >= 0xdc00 && codeUnit <= 0xdfff;
}

std::string cpStr(const unsigned long cp)
{
    std::ostringstream ss;

    ss << "U+" << std::uppercase << std::hex << std::setfill('0') << std::setw(4) << cp;
    return ss.str();
}

} // namespace

Size StrScanner::_appendEscapedUnicodeChar(const std::string_view hexDigits)
{
    /*
     * `hexDigits` starts with the first hexadecimal digit of a `\u`
     * escape sequence.
     *
     * Like in JSON (RFC 8259, section 7), a codepoint outside the BMP
     * is a UTF-16 surrogate pair, that is, a `\u` escape sequence
     * having a high surrogate followed with another one having a low
     * surrogate.
     */
    auto cp = this->_scanEscapedUnicodeCodeUnit(hexDigits);
    Size len = 4;

    if (isLowSurrogate(cp)) {
        std::ostringstream ss;

        ss << "In `\\u` escape sequence: unexpected low surrogate " << cpStr(cp) <<
              " without a preceding high surrogate.";
        throwTextParseError(ss.str(), this->loc());
    }

    if (isHighSurrogate(cp)) {
        const auto low = hexDigits.substr(4);

        if (low.size() < 6 || low[0] != '\\' || low[1] != 'u') {
            std::ostringstream ss;

            ss << "In `\\u` escape sequence: expecting a `\\u` escape sequence having a "
                  "low surrogate after the high surrogate " << cpStr(cp) << ".";
            throwTextParseError(ss.str(), this->loc());
        }

        const auto lowCodeUnit = this->_scanEscapedUnicodeCodeUnit(low.substr(2));

        if (!isLowSurrogate(lowCodeUnit)) {
            std::ostringstream ss;

            ss << "In `\\u` escape sequence: expecting a low surrogate after the high "
                  "surrogate " << cpStr(cp) << ", got " << cpStr(lowCodeUnit) << ".";
            throwTextParseError(ss.str(), this->loc());
        }

        cp = 0x10000 + ((cp - 0xd800) << 10) + (lowCodeUnit - 0xdc00);
        len += 6;
    }

    // append UTF-8 bytes from integral codepoint
    if (cp <= 0x7f) {
        _strBuf.push_back(static_cast<char>(cp));
    } else if (cp <= 0x7ff) {
        _strBuf.push_back(static_cast<char>((cp >> 6) + 192));
        _strBuf.push_back(static_cast<char>((cp & 63) + 128));
    } else if (cp <= 0xffff) {
        _strBuf.push_back(static_cast<char>((cp >> 12) + 224));
        _strBuf.push_back(static_cast<char>(((cp >> 6) & 63) + 128));
        _strBuf.push_back(static_cast<char>((cp & 63) + 128));
    } else {
        assert(cp <= 0x10ffff);
        _strBuf.push_back(static_cast<char>((cp >> 18) + 240));
        _strBuf.push_back(static_cast<char>(((cp >> 12) & 63) + 128));
        _strBuf.push_back(static_cast<char>(((cp >> 6) & 63) + 128));
        _strBuf.push_back(static_cast<char>((cp & 63) + 128));
    }

    return len;
}

void StrScanner::_appendEscapedHexChar(const std::string_view hexDigits)
{
    assert(hexDigits.size() >= 2);

    // two hex characters
    const auto hexByte = hexDigits.substr(0, 2);

    // validate hex characters
    for (const auto ch : hexByte) {
        if (!std::isxdigit(static_cast<unsigned char>(ch))) {
            std::ostringstream ss;

            ss << "In `\\x` escape sequence: unexpected character `" << ch << "`.";
            throwTextParseError(ss.str(), this->loc());
        }
    }

    // convert hex characters to byte (always works)
    unsigned int byte = 0;

    std::from_chars(hexByte.data(), hexByte.data() + hexByte.size(), byte, 16);

    // validate value
    if (byte == 0) {
        throwTextParseError("Invalid `\\x00` escape sequence.", this->loc());
    }

    // append byte
    _strBuf.push_back(static_cast<char>(byte));
}

bool StrScanner::_tryAppendEscapedChar(const std::string_view escapeSeqStartList)
{
    const auto rest = this->rest();

    if (rest.size() < 2 || rest[0] != '\\') {
        return false;
    }

    const auto ch = rest[1];

    if (ch != '"' && ch != '\\' && escapeSeqStartList.find(ch) == std::string_view::npos) {
        // not an escape sequence
        return false;
    }

    if (ch == 'u') {
        if (rest.size() < 6) {
            throwTextParseError("`\\u` escape sequence needs four hexadecimal digits.",
                                this->loc());
        }

        _at += 2 + this->_appendEscapedUnicodeChar(rest.substr(2));
    } else if (ch == 'x') {
        if (rest.size() < 4) {
            throwTextParseError("`\\x` escape sequence needs two hexadecimal digits.",
                                this->loc());
        }

        this->_appendEscapedHexChar(rest.substr(2));
        _at += 4;
    } else {
        switch (ch) {
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
            _strBuf.push_back(ch);
            break;
        }

        _at += 2;
    }

    return true;
}

void StrScanner::_skipComment()
{
    const auto rest = this->rest();

    if (rest.size() < 2 || rest[0] != '/') {
        return;
    }

    switch (rest[1]) {
    case '/':
        // single-line comment
        _at += 2;

        while (!this->isDone()) {
            if (_str[_at] == '\\') {
                /*
                 * Like in C, a `\` character immediately followed by a
                 * newline (LF or CRLF) continues the comment on the
                 * next line.
                 */
                auto next = _at + 1;

                if (next != _str.size() && _str[next] == '\r') {
                    ++next;
                }

                if (next != _str.size() && _str[next] == '\n') {
                    _at = next;
                    this->_checkNewLine();
                    ++_at;
                    continue;
                }
            }

            if (_str[_at] == '\n') {
                /*
                 * We don't set a newline here because the current
                 * position is left at the newline character, which is
                 * considered excluded from the comment itself.
                 */
                return;
            }

            ++_at;
        }
        break;

    case '*':
    {
        // multi-line comment
        const auto commentLoc = this->loc();

        _at += 2;

        while (!this->isDone()) {
            if (this->_charsLeft() >= 2 && _str[_at] == '*' && _str[_at + 1] == '/') {
                _at += 2;
                return;
            }

            this->_checkNewLine();
            ++_at;
        }

        throwTextParseError("Unterminated multi-line comment: expecting `*/`.", commentLoc);
    }

    default:
        break;
    }
}

} // namespace yactfr::internal
