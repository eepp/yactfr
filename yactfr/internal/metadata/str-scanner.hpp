/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_STR_SCANNER_HPP
#define YACTFR_INTERNAL_METADATA_STR_SCANNER_HPP

#include <cassert>
#include <vector>
#include <limits>
#include <regex>
#include <optional>
#include <string>
#include <string_view>
#include <charconv>
#include <system_error>

#include <yactfr/aliases.hpp>
#include <yactfr/text-loc.hpp>

namespace yactfr::internal {

/*
 * String scanner.
 *
 * A string scanner wraps an input string view and scans specific
 * characters and sequences of characters, managing a current position
 * (offset within the input string).
 *
 * It's a backtracking lexer.
 *
 * The string scanner automatically skips whitespaces and C/C++-style
 * comments when you call any tryScan*() method if needed.
 *
 * When you call the various tryScan*() methods to scan some contents,
 * they advance the current position on success. You can control the
 * current position with the save(), accept(), and reject() methods. The
 * latter methods operate on a position stack, a stack of saved
 * positions which you can restore.
 *
 * Before scanning anything that could be reverted, call save(). Then,
 * if you must revert the current position, call reject(). If, on the
 * other hand, the advanced current position is okay, call accept(). You
 * must call exactly one accept() or reject() method for each call
 * to save().
 *
 * It's recommended to use an auto-rejecter instead of using save(),
 * accept(), and reject() manually (see StrScannerRejecter)
 * when possible.
 */
class StrScanner final
{
public:
    /*
     * Builds a string scanner, wrapping the string `str`.
     *
     * ┌───────────────────────────────────────────────────────────────┐
     * │ NOTE: This string scanner does NOT own the string which `str` │
     * │ views, so you must make sure that it's still alive when you   │
     * │ call its scanning methods.                                    │
     * └───────────────────────────────────────────────────────────────┘
     */
    explicit StrScanner(std::string_view str) noexcept;

    StrScanner(const StrScanner&) = delete;
    StrScanner& operator=(const StrScanner&) = delete;

    /*
     * Returns the whole string, the one with which this string scanner
     * was built.
     */
    std::string_view str() const noexcept
    {
        return _str;
    }

    /*
     * Returns the current position, an offset within str().
     */
    Index at() const noexcept
    {
        return _at;
    }

    /*
     * Returns the rest of the string, from the current position until
     * the end of str().
     */
    std::string_view rest() const noexcept
    {
        return this->_substr(_at, _str.size());
    }

    /*
     * Advances the current position by `count` characters.
     *
     * ┌────────────────────────────────────────────────────────────┐
     * │ NOTE: This may corrupt the current location (loc()) if the │
     * │ `count` skipped characters include one or more             │
     * │ newline characters.                                        │
     * └────────────────────────────────────────────────────────────┘
     */
    void skip(const Size count) noexcept
    {
        assert(count <= this->_charsLeft());
        _at += count;
    }

    /*
     * Returns the current text location.
     */
    TextLocation loc() const
    {
        return TextLocation {_at, _nbLines, _at - _lineBegin};
    }

    /*
     * Returns whether or not the end of the string is reached.
     */
    bool isDone() const noexcept
    {
        return _at == _str.size();
    }

    /*
     * Resets this string scanner, including the position stack.
     *
     * Resets the current position to the beginning of str().
     */
    void reset();

    /*
     * Pushes the current position on the position stack.
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
     * This method removes an entry from the top of the position stack
     * without changing the current position.
     */
    void accept()
    {
        assert(!_stack.empty());
        _stack.pop_back();
    }

    /*
     * Rejects the content parsed since the latest call to save().
     *
     * This method removes an entry from the top of the position stack,
     * and also restores the current position to the saved position of
     * the entry.
     */
    void reject();

    /*
     * Tries to scan a C identifier, placing the current position after
     * this string on success.
     *
     * Returns the identifier string or `std::nullopt` if there's
     * no identifier.
     *
     * The returned string view is a view of str(), therefore it remains
     * valid as long as the string which str() views.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    [[ nodiscard ]] std::optional<std::string_view> tryScanIdent();

    /*
     * Alternative version which skips whitespaces and comments.
     */
    [[ nodiscard ]] std::optional<std::string_view> tryScanIdent()
    {
        return this->tryScanIdent<true, true>();
    }

    /*
     * Skips whitespaces and comments, and then returns the C identifier
     * at the current position, without consuming it, or `std::nullopt`
     * if there's no identifier.
     *
     * The returned string view is a view of str(), therefore it remains
     * valid as long as the string which str() views.
     */
    [[ nodiscard ]] std::optional<std::string_view> peekIdent()
    {
        this->skipCommentsAndWhitespaces();
        this->_lexIdent();

        if (_identEnd == _identBegin) {
            return std::nullopt;
        }

        return this->_substr(_identBegin, _identEnd);
    }

    /*
     * Tries to scan a double-quoted literal string, considering the
     * characters of `escapeSeqStartList`, `"`, and `\` as escape
     * sequence starting characters, placing the current position after
     * the closing double quote on success.
     *
     * Returns the escaped string, without beginning/end double quotes,
     * on success, or `std::nullopt` if there's no double-quoted literal
     * string (or if the method reaches the end of the string before
     * a closing `"`).
     *
     * The returned string view remains valid as long as you don't call
     * any method of this object.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    [[ nodiscard ]] std::optional<std::string_view> tryScanLitStr(std::string_view escapeSeqStartList);

    /*
     * Alternative version which skips whitespaces and comments.
     */
    [[ nodiscard ]] std::optional<std::string_view> tryScanLitStr(const std::string_view escapeSeqStartList)
    {
        return this->tryScanLitStr<true, true>(escapeSeqStartList);
    }

    /*
     * Tries to scan and decode a constant integer string, with an
     * optional `0`, `0x`/`0X`, or `0b`/`0B` prefix if `AllowPrefixV` is
     * true, and possibly negative if `ValT` is signed.
     *
     * Returns `std::nullopt` if it could not scan a constant integer.
     *
     * The current position is placed after this constant integer string
     * on success.
     */
    template <bool SkipWsV, bool SkipCommentsV, typename ValT, bool AllowPrefixV = true>
    [[ nodiscard ]] std::optional<ValT> tryScanConstInt();

    /*
     * Alternative version which skips whitespaces and comments.
     */
    template <typename ValT, bool AllowPrefixV = true>
    [[ nodiscard ]] std::optional<ValT> tryScanConstInt()
    {
        return this->tryScanConstInt<true, true, ValT, AllowPrefixV>();
    }

    /*
     * Tries to scan and decode a constant unsigned integer string, with
     * an optional `0x`/`0X`, or `0b`/`0B` prefix if `AllowPrefixV`
     * is true.
     *
     * Returns `std::nullopt` if it could not scan a constant
     * unsigned integer.
     *
     * The current position is placed after this constant unsigned
     * integer string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV, bool AllowPrefixV = true>
    [[ nodiscard ]] std::optional<unsigned long long> tryScanConstUInt()
    {
        return this->tryScanConstInt<SkipWsV, SkipCommentsV,
                                     unsigned long long, AllowPrefixV>();
    }

    /*
     * Alternative version which skips whitespaces and comments.
     */
    template <bool AllowPrefixV = true>
    [[ nodiscard ]] std::optional<unsigned long long> tryScanConstUInt()
    {
        return this->tryScanConstUInt<true, true, AllowPrefixV>();
    }

    /*
     * Tries to scan and decode a constant signed integer string, with
     * an optional `0x`/`0X`, or `0b`/`0B` prefix if `AllowPrefixV` is
     * true, and possibly negative.
     *
     * Returns `std::nullopt` if it could not scan a constant
     * signed integer.
     *
     * The current position is placed after this constant signed
     * integer string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV, bool AllowPrefixV = true>
    [[ nodiscard ]] std::optional<long long> tryScanConstSInt()
    {
        return this->tryScanConstInt<SkipWsV, SkipCommentsV,
                                     long long, AllowPrefixV>();
    }

    /*
     * Alternative version which skips whitespaces and comments.
     */
    template <bool AllowPrefixV = true>
    [[ nodiscard ]] std::optional<long long> tryScanConstSInt()
    {
        return this->tryScanConstSInt<true, true, AllowPrefixV>();
    }

    /*
     * Tries to scan and decode a constant real number string, returning
     * `std::nullopt` if not possible.
     *
     * The format of the real number string to scan is the JSON
     * (<https://www.json.org/>) number one, _with_ a fraction or an
     * exponent part. Without a fraction/exponent part, this method
     * returns `std::nullopt`: use tryScanConstInt() to try scanning a
     * constant integer instead.
     *
     * The current position is placed after this constant real number
     * string on success.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    [[ nodiscard ]] std::optional<double> tryScanConstReal();

    /*
     * Alternative version which skips whitespaces and comments.
     */
    [[ nodiscard ]] std::optional<double> tryScanConstReal()
    {
        return this->tryScanConstReal<true, true>();
    }

    /*
     * Tries to scan a specific token `token`, placing the current
     * position after this string on success.
     *
     * If `token` ends with a C identifier character, then this method
     * only succeeds if the following character isn't a C identifier
     * character: for example, `struct` doesn't match `structure`.
     */
    template <bool SkipWsV, bool SkipCommentsV>
    [[ nodiscard ]] bool tryScanToken(std::string_view token);

    /*
     * Alternative version which skips whitespaces and comments.
     */
    [[ nodiscard ]] bool tryScanToken(const std::string_view token)
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
        if constexpr (!SkipWsV && !SkipCommentsV) {
            return;
        }

        /*
         * A backtracking parser often skips from the same position
         * many times, mostly from a position where there's
         * nothing to skip.
         *
         * Skipping from a given position always leads to the same
         * position (and line), so remember the last skip when skipping
         * both whitespaces and comments.
         */
        constexpr auto useCache = SkipWsV && SkipCommentsV;

        if constexpr (useCache) {
            if (_at == _skipTo) {
                // nothing to skip here
                return;
            }

            if (_at == _skipFrom) {
                _at = _skipTo;
                _lineBegin = _skipToLineBegin;
                _nbLines = _skipToNbLines;
                return;
            }
        }

        const auto from = _at;

        while (!this->isDone()) {
            const auto at = _at;

            if constexpr (SkipWsV) {
                this->_skipWhitespaces();
            }

            if constexpr (SkipCommentsV) {
                this->_skipComment();
            }

            if (_at == at) {
                // no more whitespaces or comments
                break;
            }
        }

        if constexpr (useCache) {
            _skipFrom = from;
            _skipTo = _at;
            _skipToLineBegin = _lineBegin;
            _skipToNbLines = _nbLines;
        }
    }

private:
    /*
     * A frame of the position stack.
     */
    struct _tStackFrame final
    {
        // position when save() was called
        Index at;

        // position of the beginning of the current line when save() was called
        Index lineBegin;

        // number of lines scanned so far when save was called()
        Size nbLines;
    };

    // "no position" value of the caches
    static constexpr auto _noPos = std::numeric_limits<Index>::max();

private:
    template <typename ValT>
    [[ nodiscard ]] static std::optional<ValT> _tryNegateConstInt(unsigned long long ullVal, bool negate);

    template <typename ValT, int BaseV>
    [[ nodiscard ]] std::optional<ValT> _tryScanConstInt(bool negate);

    static bool _isIdentFirstChar(const char ch) noexcept
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
    }

    static bool _isIdentChar(const char ch) noexcept
    {
        return _isIdentFirstChar(ch) || (ch >= '0' && ch <= '9');
    }

    /*
     * Returns the substring of str() from `begin` (included) to
     * `end` (excluded).
     *
     * Unlike std::string_view::substr(), this method doesn't check
     * its parameters.
     */
    std::string_view _substr(const Index begin, const Index end) const noexcept
    {
        assert(begin <= end);
        assert(end <= _str.size());
        return {_str.data() + begin, static_cast<std::string_view::size_type>(end - begin)};
    }

    /*
     * Returns the number of characters left until the end of str().
     */
    Size _charsLeft() const noexcept
    {
        return _str.size() - _at;
    }

    /*
     * Makes `_identBegin` and `_identEnd` describe the C identifier at
     * the current position (empty if none).
     *
     * Parsers often try to scan the same identifier many times when
     * backtracking: this method doesn't scan again if `_identBegin` is
     * the current position.
     */
    void _lexIdent()
    {
        if (_identBegin == _at) {
            // already lexed
            return;
        }

        auto end = _at;

        if (end != _str.size() && StrScanner::_isIdentFirstChar(_str[end])) {
            ++end;

            while (end != _str.size() && StrScanner::_isIdentChar(_str[end])) {
                ++end;
            }
        }

        _identBegin = _at;
        _identEnd = end;
    }

    void _skipComment();
    void _skipWhitespaces();

    /*
     * Validates and returns the code unit of the first four hexadecimal
     * digits of `hexDigits`.
     */
    unsigned long _scanEscapedUnicodeCodeUnit(std::string_view hexDigits);

    /*
     * Appends to `_strBuf` the UTF-8 encoding of the codepoint of the
     * `\u` escape sequence of which `hexDigits` starts with the first
     * hexadecimal digit, possibly followed with another `\u` escape
     * sequence (surrogate pair).
     *
     * Returns the number of characters after the first `\u` which
     * the escape sequence(s) spans.
     */
    Size _appendEscapedUnicodeChar(std::string_view hexDigits);

    /*
     * Appends to `_strBuf` the byte of the first two hexadecimal digits
     * of `hexDigits` (`\x` escape sequence).
     */
    void _appendEscapedHexChar(std::string_view hexDigits);

    /*
     * Tries to append an escaped character to `_strBuf` from the
     * characters at the current position, considering the characters of
     * `escapeSeqStartList`, `"`, and `\` as escape sequence
     * starting characters.
     */
    [[ nodiscard ]] bool _tryAppendEscapedChar(std::string_view escapeSeqStartList);

    _tStackFrame& _stackTop()
    {
        return _stack.back();
    }

    void _checkNewLine()
    {
        if (_str[_at] == '\n') {
            ++_nbLines;
            _lineBegin = _at + 1;
        }
    }

private:
    // string to scan, given by user
    std::string_view _str;

    // current position
    Index _at = 0;

    // position of the beginning of the current line
    Index _lineBegin = 0;

    // number of lines scanned so far
    Size _nbLines = 0;

    // position stack
    std::vector<_tStackFrame> _stack;

    // string buffer
    std::string _strBuf;

    /*
     * Last skip of whitespaces and comments (see
     * skipCommentsAndWhitespaces()): from `_skipFrom` to `_skipTo`, the
     * latter being at line `_skipToNbLines` which begins
     * at `_skipToLineBegin`.
     */
    Index _skipFrom = _noPos;
    Index _skipTo = _noPos;
    Index _skipToLineBegin = 0;
    Size _skipToNbLines = 0;

    // last lexed identifier (see _lexIdent())
    Index _identBegin = _noPos;
    Index _identEnd = _noPos;

    // real number string regex
    static const std::regex _realRegex;
};

template <bool SkipWsV, bool SkipCommentsV>
std::optional<std::string_view> StrScanner::tryScanIdent()
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();
    this->_lexIdent();

    if (_identEnd == _identBegin) {
        // no identifier
        return std::nullopt;
    }

    _at = _identEnd;
    return this->_substr(_identBegin, _identEnd);
}

template <bool SkipWsV, bool SkipCommentsV>
std::optional<std::string_view> StrScanner::tryScanLitStr(const std::string_view escapeSeqStartList)
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    // first character: `"`
    if (this->isDone() || _str[_at] != '"') {
        return std::nullopt;
    }

    const auto at = _at;
    const auto lineBegin = _lineBegin;
    const auto nbLines = _nbLines;

    ++_at;
    _strBuf.clear();

    while (!this->isDone()) {
        // try to append escape character first
        if (this->_tryAppendEscapedChar(escapeSeqStartList)) {
            continue;
        }

        const auto ch = _str[_at];

        // check for end of string
        if (ch == '"') {
            ++_at;
            return std::string_view {_strBuf};
        }

        // check for newline
        this->_checkNewLine();

        // append character
        _strBuf.push_back(ch);

        // go to next character
        ++_at;
    }

    // could not find end of string
    _at = at;
    _lineBegin = lineBegin;
    _nbLines = nbLines;
    return std::nullopt;
}

template <bool SkipWsV, bool SkipCommentsV>
bool StrScanner::tryScanToken(const std::string_view token)
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    const auto rest = this->rest();

    if (rest.compare(0, token.size(), token) != 0) {
        return false;
    }

    // check token boundary
    if (!token.empty() && StrScanner::_isIdentChar(token.back()) &&
            rest.size() > token.size() && StrScanner::_isIdentChar(rest[token.size()])) {
        return false;
    }

    _at += token.size();
    return true;
}

template <typename ValT>
std::optional<ValT> StrScanner::_tryNegateConstInt(const unsigned long long ullVal,
                                                     const bool negate)
{
    static constexpr auto llMaxAsUll = static_cast<unsigned long long>(std::numeric_limits<long long>::max());

    // negate if needed
    if constexpr (std::is_signed_v<ValT>) {
        if (negate) {
            if (ullVal > llMaxAsUll + 1) {
                return std::nullopt;
            }
        } else {
            if (ullVal > llMaxAsUll) {
                return std::nullopt;
            }
        }
    }

    // success: cast and negate if needed
    if (!negate) {
        return static_cast<ValT>(ullVal);
    }

    if constexpr (std::is_signed_v<ValT>) {
        if (ullVal == llMaxAsUll + 1) {
            /*
             * Cannot negate `static_cast<ValT>(ullVal)`
             * without overflowing.
             */
            return std::numeric_limits<ValT>::min();
        }

        return -static_cast<ValT>(ullVal);
    } else {
        // unsigned: wrap around
        return static_cast<ValT>(0ULL - ullVal);
    }
}

template <typename ValT, int BaseV>
std::optional<ValT> StrScanner::_tryScanConstInt(const bool negate)
{
    const auto rest = this->rest();

    /*
     * Reject a hexadecimal radix prefix at this point: we already
     * scanned any prefix, if allowed.
     *
     * Without this, std::from_chars() would scan the `0` of `0x`.
     *
     * std::from_chars() itself rejects whitespaces, `-` (unsigned
     * type), and `+`.
     */
    if (rest.size() >= 2 && rest[0] == '0' && (rest[1] == 'x' || rest[1] == 'X')) {
        return std::nullopt;
    }

    unsigned long long ullVal;
    const auto res = std::from_chars(rest.data(), rest.data() + rest.size(), ullVal, BaseV);

    if (res.ec != std::errc {}) {
        // could not parse or out of range
        return std::nullopt;
    }

    {
        const auto val = this->_tryNegateConstInt<ValT>(ullVal, negate);

        if (val) {
            // success: update position
            _at += res.ptr - rest.data();
        }

        return val;
    }
}

template <bool SkipWsV, bool SkipCommentsV, typename ValT, bool AllowPrefixV>
std::optional<ValT> StrScanner::tryScanConstInt()
{
    static_assert(std::is_same_v<ValT, long long> || std::is_same_v<ValT, unsigned long long>,
                  "`ValT` is `long long` or `unsigned long long`.");

    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    if (this->isDone()) {
        // nothing left
        return std::nullopt;
    }

    const auto at = _at;

    // check for negation
    const bool negate = (_str[_at] == '-');

    if constexpr (!std::is_signed_v<ValT>) {
        if (negate) {
            return std::nullopt;
        }
    }

    if (negate || (AllowPrefixV && _str[_at] == '+')) {
        ++_at;
    }

    // check for radix prefix
    const auto rest = this->rest();
    std::optional<ValT> val;

    if (AllowPrefixV && rest.size() >= 2 && rest[0] == '0' &&
            (rest[1] == 'b' || rest[1] == 'B' ||
             rest[1] == 'x' || rest[1] == 'X' ||
             (rest[1] >= '1' && rest[1] <= '9'))) {
        if (rest[1] == 'b' || rest[1] == 'B') {
            // binary
            _at += 2;
            val = this->_tryScanConstInt<ValT, 2>(negate);
        } else if (rest[1] == 'x' || rest[1] == 'X') {
            // hexadecimal
            _at += 2;
            val = this->_tryScanConstInt<ValT, 16>(negate);
        } else {
            // octal: leave prefix to catch 0 too
            assert(rest[1] >= '1' && rest[1] <= '9');
            val = this->_tryScanConstInt<ValT, 8>(negate);
        }
    } else {
        // fall back to decimal
        val = this->_tryScanConstInt<ValT, 10>(negate);
    }

    if (!val) {
        // no constant integer
        _at = at;
    }

    return val;
}

template <bool SkipWsV, bool SkipCommentsV>
std::optional<double> StrScanner::tryScanConstReal()
{
    this->skipCommentsAndWhitespaces<SkipWsV, SkipCommentsV>();

    const auto rest = this->rest();

    /*
     * Validate JSON number format (with fraction and/or exponent part).
     *
     * This is needed because std::from_chars() accepts more formats
     * which JSON doesn't support.
     */
    if (!std::regex_search(rest.begin(), rest.end(), StrScanner::_realRegex)) {
        return std::nullopt;
    }

    // parse
    double val;
    const auto res = std::from_chars(rest.data(), rest.data() + rest.size(), val);

    if (res.ec != std::errc {}) {
        // could not parse or out of range
        return std::nullopt;
    }

    // success: update position and return value
    _at += res.ptr - rest.data();
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
class StrScannerRejecter final
{
public:
    /*
     * Builds a string scanner rejecter, managing the string scanner
     * `ss`.
     *
     * This constructor calls StrScanner::save() initially on `ss`.
     */
    explicit StrScannerRejecter(StrScanner& ss) :
        _ss {&ss}
    {
        _ss->save();
    }

    StrScannerRejecter(const StrScannerRejecter&) = delete;
    StrScannerRejecter& operator=(const StrScannerRejecter&) = delete;

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
    StrScanner *_ss;
};

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_METADATA_STR_SCANNER_HPP
