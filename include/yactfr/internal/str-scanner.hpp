/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_STR_SCANNER_HPP
#define _YACTFR_INTERNAL_STR_SCANNER_HPP

#include <cstdlib>
#include <memory>
#include <iterator>
#include <vector>
#include <limits>
#include <regex>
#include <cmath>
#include <boost/utility.hpp>
#include <boost/optional.hpp>

#include "../aliases.hpp"
#include "../text-loc.hpp"

namespace yactfr {
namespace internal {

/*
 * Invalid escape sequence error.
 */
class InvalEscapeSeq final :
    public std::runtime_error
{
public:
    explicit InvalEscapeSeq(std::string msg, TextLocation loc) :
        std::runtime_error {std::move(msg)},
        _loc {std::move(loc)}
    {
    }

    const TextLocation& loc() const noexcept
    {
        return _loc;
    }

private:
    TextLocation _loc;
};

/*
 * String scanner.
 *
 * A string scanner wraps an input string using two random access `char`
 * iterators and scans specific characters and sequences of characters,
 * managing a current iterator.
 *
 * It's a backtracking lexer.
 *
 * The string scanner automatically skips whitespaces and C/C++-style
 * comments when you call any tryScan*() method.
 *
 * When you call the various tryScan*() methods to scan some contents,
 * the the method advances the current iterator on success. You can
 * control the current iterator with the save(), accept(), and reject()
 * methods. The latter methods operate on an iterator stack, a stack of
 * saved positions which you can restore.
 *
 * Before scanning anything that could be reverted, call save(). Then,
 * if you must revert the iterator position, call reject(). If, on the
 * other hand, the advanced iterator position is okay, call accept().
 * You must call exactly one accept() or reject() method for each call
 * to save().
 *
 * It is recommended to use an auto-rejecter instead of using save(),
 * accept(), and reject() manually (see StrScannerRejecter) when
 * possible.
 *
 * tryScanIdent() doesn't copy anything: the `begin` and `end` iterator
 * reference parameters are set to the limits of the parsed string, if
 * any is found.
 */
template <typename CharIt>
class StrScanner final :
    private boost::noncopyable
{
public:
    /*
     * Builds a string scanner, wrapping a string between `begin`
     * (inclusive) and `end` (exclusive).
     *
     * Note that this string scanner does NOT own the container of those
     * iterators, so you must make sure that it's still alive when you
     * call its scanning methods.
     */
    explicit StrScanner(CharIt begin, CharIt end) :
        _begin {begin},
        _end {end},
        _at {begin},
        _lineBegin {begin},
        _realRegex {
            "^"                     // start of target
            "-?"                    // optional negation
            "(?:0|[1-9]\\d*)"       // integer part
            "(?=[eE.]\\d)"          // assertion: need fraction/exponent part
            "(?:\\.\\d+)?"          // optional fraction part
            "(?:[eE][+-]?\\d+)?",   // optional exponent part
            std::regex::optimize
        }
    {
    }

    /*
     * Returns the current iterator.
     */
    const CharIt& at() const
    {
        return _at;
    }

    /*
     * Sets the current iterator position.
     *
     * Note that this may corrupt the current location if the string
     * between the current position and new position includes one or
     * more newline characters.
     */
    void at(CharIt at)
    {
        _at = at;
    }

    /*
     * Returns the beginning iterator, the one with which this string
     * scanner was built.
     */
    const CharIt& begin() const
    {
        return _begin;
    }

    /*
     * Returns the ending iterator, the one with which this string
     * scanner was built.
     */
    const CharIt& end() const
    {
        return _end;
    }

    /*
     * Returns the number of characters left until the end of the
     * wrapped string.
     */
    Size charsLeft() const
    {
        return std::distance(_at, _end);
    }

    /*
     * Returns the current text location.
     */
    TextLocation loc() const
    {
        return TextLocation {
            static_cast<Index>(_at - _begin),
            _nbLines,
            static_cast<Index>(_at - _lineBegin)
        };
    }

    /*
     * Returns whether or not the end of the string is reached.
     */
    bool isDone() const
    {
        return _at == _end;
    }

    /*
     * Resets this string scanner, including the iterator stack.
     *
     * Resets the current iterator to begin().
     */
    void reset()
    {
        _stack.clear();
        _at = _begin;
        _nbLines = 0;
        _lineBegin = _begin;
    }

    /*
     * Pushes the current iterator position on the iterator stack.
     *
     * Call this before calling one or more parsing methods of which the
     * content could be rejected.
     *
     * You must remove this new entry on the stack by calling accept()
     * or reject().
     */
    void save()
    {
        _stack.push_back({_at, _lineBegin, _nbLines});
    }

    /*
     * Accepts the content parsed since the latest call to save().
     *
     * This method removes an entry from the top of the iterator stack
     * without changing the current iterator position.
     */
    void accept()
    {
        assert(!_stack.empty());
        _stack.pop_back();
    }

    /*
     * Rejects the content parsed since the latest call to save().
     *
     * This method removes an entry from the top of the iterator stack,
     * and also restores the position of the current iterator to the
     * saved position of the entry.
     */
    void reject()
    {
        assert(!_stack.empty());
        _at = _stack.back().at;
        _lineBegin = _stack.back().lineBegin;
        _nbLines = _stack.back().nbLines;
        _stack.pop_back();
    }

    /*
     * Tries to scan a C identifier, placing the current iterator after
     * this string on success.
     *
     * Returns the identifier string or `nullptr` if there's no
     * identifier.
     *
     * The returned string remains valid as long as you don't call any
     * method of this object.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    const std::string *tryScanIdent();

    /*
     * Alternative version which skips whitespaces and comments.
     */
    const std::string *tryScanIdent()
    {
        return this->tryScanIdent<true, true>();
    }

    /*
     * Tries to scan a double-quoted literal string, considering the
     * characters of `escapeSeqStartList` and `"` as escape sequence
     * starting characters, placing the current iterator after the
     * closing double quote on success.
     *
     * Returns the escaped string, without beginning/end double quotes,
     * on success, or `nullptr` if there's no double-quoted literal
     * string (or if the method reaches the end iterator before a
     * closing `"`).
     *
     * The returned string remains valid as long as you don't call any
     * method of this object.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    const std::string *tryScanLitStr(const char *escapeSeqStartList);

    /*
     * Alternative version which skips whitespaces and comments.
     */
    const std::string *tryScanLitStr(const char * const escapeSeqStartList)
    {
        return this->tryScanLitStr<true, true>(escapeSeqStartList);
    }

    /*
     * Tries to scan and decode a constant integer string, with an
     * optional `0`, `0x`/`0X`, or `0b`/`0B` prefix if `AllowPrefixV` is
     * true, and possibly negative if `ValT` is signed.
     *
     * Returns `boost::none` if it could not scan a constant integer.
     *
     * The current iterator is placed after this constant integer
     * string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV, typename ValT, bool AllowPrefixV = true>
    boost::optional<ValT> tryScanConstInt();

    /*
     * Alternative version which skips whitespaces and comments.
     */
    template <typename ValT, bool AllowPrefixV = true>
    boost::optional<ValT> tryScanConstInt()
    {
        return this->tryScanConstInt<true, true, ValT, AllowPrefixV>();
    }

    /*
     * Tries to scan and decode a constant unsigned integer string, with
     * an optional `0x`/`0X`, or `0b`/`0B` prefix if `AllowPrefixV` is
     * true.
     *
     * Returns `boost::none` if it could not scan a constant integer.
     *
     * The current iterator is placed after this constant integer
     * string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV, bool AllowPrefixV = true>
    boost::optional<unsigned long long> tryScanConstUInt()
    {
        return this->tryScanConstInt<SkipWsV, SkipCommentsV,
                                     unsigned long long, AllowPrefixV>();
    }

    /*
     * Alternative version which skips whitespaces and comments.
     */
    template <bool AllowPrefixV = true>
    boost::optional<unsigned long long> tryScanConstUInt()
    {
        return this->tryScanConstUInt<true, true, AllowPrefixV>();
    }

    /*
     * Tries to scan and decode a constant signed integer string, with
     * an optional `0x`/`0X`, or `0b`/`0B` prefix if `AllowPrefixV` is
     * true, and possibly negative.
     *
     * Returns `boost::none` if it could not scan a constant integer.
     *
     * The current iterator is placed after this constant integer
     * string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV, bool AllowPrefixV = true>
    boost::optional<long long> tryScanConstSInt()
    {
        return this->tryScanConstInt<SkipWsV, SkipCommentsV,
                                     long long, AllowPrefixV>();
    }

    /*
     * Alternative version which skips whitespaces and comments.
     */
    template <bool AllowPrefixV = true>
    boost::optional<long long> tryScanConstSInt()
    {
        return this->tryScanConstSInt<true, true, AllowPrefixV>();
    }

    /*
     * Scans and decodes a constant real number string, returning
     * `boost::none` if not possible.
     *
     * The format of the real number string to scan is the JSON
     * (<https://www.json.org/>) number one, _with_ a fraction or an
     * exponent part. Without a fraction/exponent part, this method
     * returns `boost::none`: use tryScanConstInt() to try scanning a
     * constant integer instead.
     *
     * The current iterator is placed after this constant real number
     * string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    boost::optional<double> tryScanConstReal();

    /*
     * Alternative version which skips whitespaces and comments.
     */
    boost::optional<double> tryScanConstReal()
    {
        return this->tryScanConstReal<true, true>();
    }

    /*
     * Tries to scan a specific token `token`, placing the current
     * iterator after this string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    bool tryScanToken(const char *token);

    /*
     * Alternative version which skips whitespaces and comments.
     */
    bool tryScanToken(const char * const token)
    {
        return this->tryScanToken<true, true>(token);
    }

    /*
     * Skips the following whitespaces (if `SkipWsV` is true) and
     * comments (if `SkipCommentsV` is true).
     */
    template <bool SkipWsV = true, bool SkipCommentsV = true>
    void skipCommentsAndWhitespaces()
    {
        if (!SkipWsV && !SkipCommentsV) {
            return;
        }

        while (!this->isDone()) {
            const auto at = _at;

            if (SkipWsV) {
                this->_skipWhitespaces();
            }

            if (SkipCommentsV) {
                this->_skipComment();
            }

            if (_at == at) {
                // no more whitespaces or comments
                return;
            }
        }
    }

private:
    // a frame of the iterator stack
    struct _StackFrame final
    {
        // position when save() was called
        CharIt at;

        // position of the beginning of the current line when save() was called
        CharIt lineBegin;

        // number of lines scanned so far when save was called()
        Size nbLines;
    };

private:
    template <typename ValT>
    static boost::optional<ValT> _tryNegateConstInt(unsigned long long ullVal, bool negate);

    template <typename ValT>
    boost::optional<ValT> _tryScanConstBinInt(bool negate);

    template <typename ValT, int BaseV>
    boost::optional<ValT> _tryScanConstInt(bool negate);

    void _skipComment();
    void _appendEscapedUnicodeChar(CharIt at);

    /*
     * Tries to append an escaped character to `_strBuf` from the
     * characters at the current position, considering the characters of
     * `escapeSeqStartList` and `"` as escape sequence starting
     * characters.
     */
    bool _tryAppendEscapedChar(const char *escapeSeqStartList);

    void _skipWhitespaces()
    {
        while (!this->isDone()) {
            if (*_at != ' ' && *_at != '\t' && *_at != '\v' && *_at != '\n' && *_at != '\r') {
                return;
            }

            this->_checkNewLine();
            ++_at;
        }
    }

    int _scanAnyChar()
    {
        if (this->isDone()) {
            return -1;
        }

        const auto c = *_at;

        ++_at;
        return c;
    }

    _StackFrame& _stackTop()
    {
        return _stack.back();
    }

    void _checkNewLine()
    {
        if (*_at == '\n') {
            ++_nbLines;
            _lineBegin = _at + 1;
        }
    }

private:
    // beginning of the substring to scan, given by user
    CharIt _begin;

    // end of the substring to scan, given by user
    CharIt _end;

    // current position
    CharIt _at;

    // position of the beginning of the current line
    CharIt _lineBegin;

    // number of lines scanned so far
    Size _nbLines = 0;

    // iterator stack
    std::vector<_StackFrame> _stack;

    // conversion buffer used to scan constant integers
    std::array<char, 72> _convBuf;

    // string buffer
    std::string _strBuf;

    // real number string regex
    std::regex _realRegex;
};

template <typename CharIt>
template <bool SkipWsV, bool SkipCommentsV>
const std::string *StrScanner<CharIt>::tryScanIdent()
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    // first character: `_` or alpha
    const auto c = this->_scanAnyChar();

    if (c < 0) {
        return nullptr;
    }

    auto chr = static_cast<char>(c);

    if (chr != '_' && !std::isalpha(chr)) {
        --_at;
        return nullptr;
    }

    _strBuf.clear();
    _strBuf.push_back(chr);

    // other characters: `_` or alphanumeric
    while (!this->isDone()) {
        chr = *_at;

        if (chr != '_' && !std::isalpha(chr) && !std::isdigit(chr)) {
            break;
        }

        _strBuf.push_back(chr);
        ++_at;
    }

    return &_strBuf;
}

template <typename CharIt>
template <bool SkipWsV, bool SkipCommentsV>
const std::string *StrScanner<CharIt>::tryScanLitStr(const char * const escapeSeqStartList)
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    const auto at = _at;
    const auto lineBegin = _lineBegin;
    const auto nbLines = _nbLines;

    // first character: `"` or alpha
    auto c = this->_scanAnyChar();

    if (c < 0) {
        return nullptr;
    }

    if (c != '"') {
        _at = at;
        _lineBegin = lineBegin;
        _nbLines = nbLines;
        return nullptr;
    }

    _strBuf.clear();

    while (!this->isDone()) {
        // try to append escape character first
        if (this->_tryAppendEscapedChar(escapeSeqStartList)) {
            continue;
        }

        // check for end of string
        if (*_at == '"') {
            ++_at;
            return &_strBuf;
        }

        // check for newline
        this->_checkNewLine();

        // append character
        _strBuf.push_back(*_at);

        // go to next character
        ++_at;
    }

    // could not find end of string
    _at = at;
    _lineBegin = lineBegin;
    _nbLines = nbLines;
    return nullptr;
}

template <typename CharIt>
template <bool SkipWsV, bool SkipCommentsV>
bool StrScanner<CharIt>::tryScanToken(const char * const token)
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    auto tokenAt = token;
    auto at = _at;

    while (*tokenAt != '\0' && at != _end) {
        if (*at != *tokenAt) {
            return false;
        }

        ++at;
        ++tokenAt;
    }

    if (*tokenAt != '\0') {
        return false;
    }

    _at = at;
    return true;
}

template <typename CharIt>
void StrScanner<CharIt>::_appendEscapedUnicodeChar(const CharIt at)
{
    // create array of four hex characters
    const std::string hexCpBuf {at, at + 4};

    // validate hex characters
    for (const auto ch : hexCpBuf) {
        if (!std::isxdigit(ch)) {
            std::ostringstream ss;

            ss << "In `\\u` escape sequence: unexpected character `" << ch << "`.";
            throw InvalEscapeSeq {ss.str(), this->loc()};
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
        throw InvalEscapeSeq {ss.str(), this->loc()};
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

template <typename CharIt>
bool StrScanner<CharIt>::_tryAppendEscapedChar(const char * const escapeSeqStartList)
{
    if (this->charsLeft() < 2) {
        return false;
    }

    if (_at[0] != '\\') {
        return false;
    }

    auto escapeSeqStart = escapeSeqStartList;

    while (*escapeSeqStart != '\0') {
        if (_at[1] == '"' || _at[1] == *escapeSeqStart) {
            if (_at[1] == 'u') {
                if (this->charsLeft() < 6) {
                    throw InvalEscapeSeq {
                        "`\\u` escape sequence needs four hexadecimal digits.",
                        this->loc()
                    };
                }

                this->_appendEscapedUnicodeChar(_at + 2);
                _at += 6;
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

template <typename CharIt>
void StrScanner<CharIt>::_skipComment()
{
    if (this->charsLeft() >= 2) {
        if (*_at == '/') {
            switch (*(_at + 1)) {
            case '/':
                // single-line comment
                _at += 2;

                while (!this->isDone()) {
                    /*
                     * TODO: Handle `\` to continue the comment on
                     * the next line.
                     */
                    if (*_at == '\n') {
                        /*
                         * We don't set a newline here because the
                         * current position is left at the newline
                         * character, which is considered excluded
                         * from the comment itself.
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

template <typename CharIt>
template <typename ValT>
boost::optional<ValT> StrScanner<CharIt>::_tryNegateConstInt(const unsigned long long ullVal,
                                                             const bool negate)
{
    // negate if needed
    if (std::is_signed<ValT>::value) {
        constexpr auto llMaxAsUll = static_cast<unsigned long long>(std::numeric_limits<long long>::max());

        if (negate) {
            if (ullVal > llMaxAsUll + 1) {
                return boost::none;
            }
        } else {
            if (ullVal > llMaxAsUll) {
                return boost::none;
            }
        }
    }

    // success: cast, negate if needed, and update position
    auto val = static_cast<ValT>(ullVal);

    if (negate) {
        val *= static_cast<ValT>(-1);
    }

    return val;
}

template <typename CharIt>
template <typename ValT>
boost::optional<ValT> StrScanner<CharIt>::_tryScanConstBinInt(const bool negate)
{
    const auto at = _at;

    // accumulate `0` and `1` characters into conversion buffer
    auto convBufIt = _convBuf.begin();

    while (!this->isDone()) {
        if (*_at != '0' && *_at != '1') {
            // no more
            break;
        }

        *convBufIt = *_at;
        ++_at;
        ++convBufIt;

        if (convBufIt - _convBuf.begin() > 64) {
            // too many bits!
            _at = at;
            return boost::none;
        }
    }

    if (convBufIt == _convBuf.begin()) {
        // `0b`/`0B` followed by something else than `0` or `1`
        _at = at;
        return boost::none;
    }

    // convert to unsigned integer value
    auto ullVal = 0ULL;
    auto curMul = 1ULL;
    auto it = convBufIt - 1;

    while (true) {
        if (*it == '1') {
            ullVal += curMul;
        }

        curMul *= 2;

        if (it == _convBuf.begin()) {
            break;
        }

        --it;
    }

    const auto val = this->_tryNegateConstInt<ValT>(ullVal, negate);

    if (!val) {
        _at = at;
    }

    return val;
}

template <typename CharIt>
template <typename ValT, int BaseV>
boost::optional<ValT> StrScanner<CharIt>::_tryScanConstInt(const bool negate)
{
    char *strEnd = nullptr;
    const auto ullVal = std::strtoull(&(*_at), &strEnd, BaseV);

    if ((ullVal == 0 && &(*_at) == strEnd) || errno == ERANGE) {
        // could not parse
        errno = 0;
        return boost::none;
    }

    const auto val = this->_tryNegateConstInt<ValT>(ullVal, negate);

    if (val) {
        // success: update position
        _at += (strEnd - &(*_at));
    }

    return val;
}

template <typename CharIt>
template <bool SkipWsV, bool SkipCommentsV, typename ValT, bool AllowPrefixV>
boost::optional<ValT> StrScanner<CharIt>::tryScanConstInt()
{
    static_assert(std::is_same<ValT, long long>::value ||
                  std::is_same<ValT, unsigned long long>::value,
                  "`ValT` is `long long` or `unsigned long long`.");

    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    const auto at = _at;
    const auto c = this->_scanAnyChar();

    if (c < 0) {
        // nothing left
        return boost::none;
    }

    // check for negation
    const bool negate = (c == '-');

    if (negate && !std::is_signed<ValT>::value) {
        _at = at;
        return boost::none;
    }

    if (!negate) {
        --_at;

        if (AllowPrefixV && c == '+') {
            ++_at;
        }
    }

    // check for radix prefix
    boost::optional<ValT> val;

    if (AllowPrefixV && *_at == '0' && this->charsLeft() >= 2) {
        if (_at[1] == 'b' || _at[1] == 'B' ||
                _at[1] == 'x' || _at[1] == 'X' ||
                _at[1] >= '1' && _at[1] <= '9') {
            if (_at[1] == 'b' || _at[1] == 'B') {
                // binary
                _at += 2;
                val = this->_tryScanConstBinInt<ValT>(negate);
            } else if (_at[1] == 'x' || _at[1] == 'X') {
                // hexadecimal
                _at += 2;
                val = this->_tryScanConstInt<ValT, 16>(negate);
            } else if (_at[1] >= '1' && _at[1] <= '9') {
                // octal: leave prefix to catch 0 too
                val = this->_tryScanConstInt<ValT, 8>(negate);
            }

            if (!val) {
                _at = at;
                return boost::none;
            }

            return val;
        }
    }

    // fall back to decimal
    val = this->_tryScanConstInt<ValT, 10>(negate);

    if (!val) {
        // no constant integer
        _at = at;
    }

    return val;
}

template <typename CharIt>
template <bool SkipWsV, bool SkipCommentsV>
boost::optional<double> StrScanner<CharIt>::tryScanConstReal()
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    const auto at = _at;

    /*
     * Validate JSON number format (with fraction and/or exponent part).
     *
     * This is needed because std::strtod() accepts more formats which
     * JSON doesn't support.
     */
    if (!std::regex_search(_at, _end, _realRegex)) {
        return boost::none;
    }

    // parse
    char *strEnd = nullptr;
    const auto val = std::strtod(&(*_at), &strEnd);

    if (val == HUGE_VAL || (val == 0 && &(*_at) == strEnd) || errno == ERANGE) {
        // could not parse
        errno = 0;
        return boost::none;
    }

    // success: update position and return value
    _at += (strEnd - &(*_at));
    return val;
}

/*
 * String scanner rejecter.
 *
 * This is some RAII magic to automatically call StrScanner::save() on
 * construction and StrScanner::reject() on destruction.
 *
 * The rejecter does NOT call StrScanner::reject() if accept() or
 * reject() is called manually on it. Do NOT call StrScanner::accept()
 * or StrScanner::reject() once a rejecter is built, as the rejecter is
 * NOT notified and WILL reject on destruction.
 */
template <typename CharIt>
class StrScannerRejecter final :
    private boost::noncopyable
{
public:
    /*
     * Builds a string scanner rejecter, managing the string scanner
     * `ss`.
     *
     * This constructor calls StrScanner::save() initially on `ss`.
     */
    explicit StrScannerRejecter(StrScanner<CharIt>& ss) :
        _ss {&ss}
    {
        _ss->save();
    }

    /*
     * Destroys the string scanner rejecter.
     *
     * If accept() or reject() was not called, this method calls
     * StrScanner::reject() on the managed string scanner.
     */
    ~StrScannerRejecter()
    {
        if (_reject) {
            _ss->reject();
        }
    }

    /*
     * Forwards the call to StrScanner::accept() on the managed string
     * scanner and inhibits a future rejection by this rejecter.
     */
    void accept()
    {
        _ss->accept();
        _reject = false;
    }

    /*
     * Forwards the call to StrScanner::reject() on the managed string
     * scanner and inhibits a future rejection by this rejecter.
     */
    void reject()
    {
        _ss->reject();
        _reject = false;
    }

private:
    bool _reject = true;
    StrScanner<CharIt> *_ss;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_STR_SCANNER_HPP
