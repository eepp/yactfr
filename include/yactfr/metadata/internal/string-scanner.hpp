/*
 * String scanner (lexer).
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_STRING_SCANNER_HPP
#define _YACTFR_METADATA_INTERNAL_STRING_SCANNER_HPP

#include <cstdlib>
#include <memory>
#include <iterator>
#include <vector>
#include <limits>
#include <boost/utility.hpp>

#include "../../aliases.hpp"
#include "../../metadata/metadata-text-location.hpp"

namespace yactfr {
namespace internal {

/*
 * String scanner.
 *
 * A string scanner wraps an input string using two random access `char`
 * iterators and scans specific characters and sequences of characters,
 * managing a current iterator.
 *
 * It's a backtracking lexer.
 *
 * The string scanner automatically skips whitespaces and comments when
 * any scan*() method is called.
 *
 * When calling the various scan*() methods to scan some content, the
 * current iterator is advanced on success. The current iterator can be
 * controlled with the save(), accept(), and reject() methods. The
 * latter methods operate on an iterator stack, a stack of saved
 * positions that can be restored.
 *
 * Before scanning anything that could be reverted, call save(). Then,
 * if the iterator position must be reverted, call reject(). If, on the
 * other hand, the advanced iterator position is okay, call accept().
 * Exactly one accept() or reject() must be called for each call to
 * save().
 *
 * It is recommended to use an auto-rejecter instead of using save(),
 * accept(), and reject() manually (see StringScannerRejecter) when
 * possible.
 *
 * For the methods parsing variable strings, like scanIdentifier() and
 * scanLiteralString(), no copy is performed: the `begin` and `end`
 * iterator reference parameters are set to the limits of the parsed
 * string, if any is found.
 */
template <typename CharIt>
class StringScanner :
    private boost::noncopyable
{
public:
    /*
     * Builds a string scanner, wrapping a string between `begin`
     * (inclusive) and `end` (exclusive).
     *
     * Note that this string scanner does NOT own the container of those
     * iterators, so you must make sure that it's still alive when you
     * call the scanning methods.
     */
    explicit StringScanner(CharIt begin, CharIt end) :
        _begin {begin},
        _end {end},
        _at {begin},
        _lineBegin {begin}
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
     * Returns the zero-based line number at which the current
     * iterator is.
     */
    Index curLineNumber() const
    {
        return _nbLines;
    }

    /*
     * Returns the zero-based column number within the current line.
     */
    Index curColNumber() const
    {
        return _at - _lineBegin;
    }

    /*
     * Returns whether or not the end of the string is reached.
     */
    bool isDone() const
    {
        return _at == _end;
    }

    /*
     * Resets this string scanner, including the iterator stack. The
     * current iterator is reset to begin().
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
     * You can remove this new entry on the stack by calling accept() or
     * reject().
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
     * entry's saved position.
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
     * Scans a C identifier, placing the current iterator after this
     * string on success.
     */
    bool scanIdentifier(CharIt& begin, CharIt& end)
    {
        this->skipCommentsAndWhitespaces();
        begin = _at;

        // first character: '_' or alpha
        const auto c = this->_scanAnyChar();

        if (c < 0) {
            return false;
        }

        auto chr = static_cast<char>(c);

        if (chr != '_' && !std::isalpha(chr)) {
            --_at;
            return false;
        }

        // other characters: '_' or alphanumeric
        while (!this->isDone()) {
            chr = *_at;

            if (chr != '_' && !std::isalpha(chr) && !std::isdigit(chr)) {
                break;
            }

            ++_at;
        }

        end = _at;
        return true;
    }

    /*
     * Scans a double-quoted literal string, advancing the current
     * iterator after the closing double quote on success.
     *
     * The string from `begin` to `end` excludes the double quotes,
     * but includes escape characters.
     */
    bool scanLiteralString(CharIt& begin, CharIt& end)
    {
        this->skipCommentsAndWhitespaces();

        const auto at = _at;
        const auto lineBegin = _lineBegin;
        const auto nbLines = _nbLines;

        // first character: '"' or alpha
        auto c = this->_scanAnyChar();

        if (c < 0) {
            return false;
        }

        if (c != '"') {
            _at = at;
            _lineBegin = lineBegin;
            _nbLines = nbLines;
            return false;
        }

        begin = _at;

        while (!this->isDone()) {
            // scan escape character first
            if (this->_scanEscapeChar("\\nrtv\"") > 0) {
                continue;
            }

            // check for end of string
            if (*_at == '"') {
                end = _at;
                ++_at;
                return true;
            }

            // check for newline
            this->_checkNewLine();

            // go to next character
            ++_at;
        }

        // could not find end of string
        _at = at;
        _lineBegin = lineBegin;
        _nbLines = nbLines;
        return false;
    }

    /*
     * Scans and decodes a constant integer string, with an optional
     * `0`, `0x`, or `0b` prefix, and possibly negative.
     *
     * The current iterator is placed after this constant integer
     * string on success.
     */
    template <typename ValueT>
    bool scanConstInt(ValueT& value);

    /*
     * Scans a specific token, placing the current iterator after this
     * string on success.
     */
    bool scanToken(const char * const str)
    {
        this->skipCommentsAndWhitespaces();

        auto strAt = str;
        auto at = _at;

        while (*strAt != '\0' && at != _end) {
            if (*at != *strAt) {
                return false;
            }

            ++at;
            ++strAt;
        }

        if (*strAt != '\0') {
            return false;
        }

        _at = at;
        return true;
    }

    /*
     * Skips the following comments and whitespaces.
     */
    void skipCommentsAndWhitespaces()
    {
        while (!this->isDone()) {
            const auto at = _at;

            this->_skipWhitespaces();
            this->_skipComment();

            if (_at == at) {
                // no more whitespaces or comments
                return;
            }
        }
    }

private:
    // a frame of the iterator stack
    struct _StackFrame {
        // position when save() was called
        CharIt at;

        // position of the beginning of the current line when save() was called
        CharIt lineBegin;

        // number of lines scanned so far when save was called()
        Size nbLines;
    };

private:
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

    void _skipComment()
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
                         *       next line.
                         */
                        if (*_at == '\n') {
                            /*
                             * We don't set a new line here because the
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

    int _scanAnyChar()
    {
        if (this->isDone()) {
            return -1;
        }

        const int c = *_at;

        ++_at;
        return c;
    }

    int _scanEscapeChar(const char * const escape)
    {
        if (this->charsLeft() < 2) {
            return -1;
        }

        if (_at[0] != '\\') {
            return -1;
        }

        auto c = escape;

        while (*c != '\0') {
            if (_at[1] == *c) {
                const char chr = _at[1];

                _at += 2;
                return chr;
            }

            ++c;
        }

        return -1;
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
};

template <typename CharIt>
template <typename ValueT>
bool StringScanner<CharIt>::scanConstInt(ValueT& value)
{
    static_assert(std::is_same<ValueT, long long>::value ||
                  std::is_same<ValueT, unsigned long long>::value,
                  "`ValueT` is `long long` or `unsigned long long`.");
    this->skipCommentsAndWhitespaces();

    const auto at = _at;
    const auto c = this->_scanAnyChar();

    if (c < 0) {
        return false;
    }

    const bool negate = (c == '-');

    if (negate && !std::is_signed<ValueT>::value) {
        _at = at;
        return false;
    }

    if (!negate) {
        --_at;
    }

    auto convBufIt = std::begin(_convBuf);
    constexpr auto llMaxAsUll = static_cast<unsigned long long>(std::numeric_limits<long long>::max());

    if (this->charsLeft() >= 2) {
        if (*_at == '0' && (*(_at + 1) == 'b' || *(_at + 1) == 'B')) {
            // binary
            _at += 2;

            while (!this->isDone()) {
                if (*_at != '0' && *_at != '1') {
                    break;
                }

                *convBufIt = *_at;
                ++_at;
                ++convBufIt;

                if (std::distance(std::begin(_convBuf), convBufIt) > 64) {
                    // too many bits!
                    _at = at;
                    return false;
                }
            }

            if (convBufIt == std::begin(_convBuf)) {
                // 0b followed by something else than 0 or 1
                _at = at;
                return false;
            }

            unsigned long long tmpValue = 0;
            unsigned long long curMul = 1;
            value = 0;
            auto it = convBufIt - 1;

            while (true) {
                if (*it == '1') {
                    tmpValue += curMul;
                }

                curMul *= 2;

                if (it == std::begin(_convBuf)) {
                    break;
                }

                --it;
            }

            if (std::is_signed<ValueT>::value) {
                if (negate) {
                    if (tmpValue > llMaxAsUll + 1) {
                        return false;
                    }
                } else {
                    if (tmpValue > llMaxAsUll) {
                        return false;
                    }
                }
            }

            value = static_cast<ValueT>(tmpValue);

            if (negate) {
                value *= static_cast<ValueT>(-1);
            }

            return true;
        }
    }

    char *strEnd = nullptr;
    unsigned long long tmpValue = std::strtoull(&(*_at), &strEnd, 0);

    if ((tmpValue == 0 && &(*_at) == strEnd) || errno == ERANGE) {
        _at = at;
        errno = 0;
        return false;
    }

    if (std::is_signed<ValueT>::value) {
        if (negate) {
            if (tmpValue > llMaxAsUll + 1) {
                return false;
            }
        } else {
            if (tmpValue > llMaxAsUll) {
                return false;
            }
        }
    }

    value = static_cast<ValueT>(tmpValue);
    _at += (strEnd - &(*_at));

    if (negate) {
        value *= static_cast<ValueT>(-1);
    }

    return true;
}

/*
 * String scanner rejecter.
 *
 * This is some RAII magic to automatically call StringScanner::save()
 * on construction and StringScanner::reject() on destruction.
 *
 * The scope does NOT call StringScanner::reject() if accept() or
 * reject() is called manually on it. Do NOT call
 * StringScanner::accept() or StringScanner::reject() once a rejecter is
 * built, as the rejecter is NOT notified and WILL reject on
 * destruction.
 */
template <typename CharIt>
class StringScannerRejecter :
    private boost::noncopyable
{
public:
    /*
     * Builds a string scanner scope, managing the string scanner `ss`.
     *
     * StringScanner::save() is called initially on `ss`.
     */
    explicit StringScannerRejecter(StringScanner<CharIt>& ss) :
        _ss {&ss}
    {
        _ss->save();
    }

    /*
     * Destroys the string scanner scope.
     *
     * If accept() or reject() was not called, StringScanner::reject()
     * is called on the managed string scanner.
     */
    ~StringScannerRejecter()
    {
        if (_reject) {
            _ss->reject();
        }
    }

    /**
     * Forwards the call to StringScanner::accept() on the managed
     * string scanner and inhibits a future rejection by this scope.
     */
    void accept()
    {
        _ss->accept();
        _reject = false;
    }

    /**
     * Forwards the call to StringScanner::reject() on the managed
     * string scanner and inhibits a future rejection by this scope.
     */
    void reject()
    {
        _ss->reject();
        _reject = false;
    }

private:
    bool _reject = true;
    StringScanner<CharIt> *_ss;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_STRING_SCANNER_HPP
