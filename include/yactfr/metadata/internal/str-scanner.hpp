/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_STR_SCANNER_HPP
#define _YACTFR_METADATA_INTERNAL_STR_SCANNER_HPP

#include <cstdlib>
#include <memory>
#include <iterator>
#include <vector>
#include <limits>
#include <boost/utility.hpp>

#include "../../aliases.hpp"
#include "../../text-loc.hpp"

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
 * The string scanner automatically skips whitespaces and C/C++-style
 * comments when you call any scan*() method.
 *
 * When you call the various scan*() methods to scan some contents, the
 * the method advances the current iterator on success. You can control
 * the current iterator with the save(), accept(), and reject() methods.
 * The latter methods operate on an iterator stack, a stack of saved
 * positions which you can restore.
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
    const std::string *tryScanIdent()
    {
        this->skipCommentsAndWhitespaces();

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
    const std::string *tryScanLitStr(const char * const escapeSeqStartList)
    {
        this->skipCommentsAndWhitespaces();

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
     * Tries to scan a specific token, placing the current iterator
     * after this string on success.
     */
    bool tryScanToken(const std::string& str)
    {
        this->skipCommentsAndWhitespaces();

        auto strAt = str.begin();
        auto at = _at;

        while (strAt != str.end() && at != _end) {
            if (*at != *strAt) {
                return false;
            }

            ++at;
            ++strAt;
        }

        if (strAt != str.end()) {
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

    int _scanAnyChar()
    {
        if (this->isDone()) {
            return -1;
        }

        const auto c = *_at;

        ++_at;
        return c;
    }

    /*
     * Tries to append an escaped character to `_strBuf` from the
     * characters at the current position, considering the characters of
     * `escapeSeqStartList` and `"` as escape sequence starting
     * characters.
     */
    bool _tryAppendEscapedChar(const char * const escapeSeqStartList)
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
                return true;
            }

            ++escapeSeqStart;
        }

        return false;
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
};

template <typename CharIt>
template <typename ValueT>
bool StrScanner<CharIt>::scanConstInt(ValueT& value)
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

    auto convBufIt = _convBuf.begin();
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

                if (std::distance(_convBuf.begin(), convBufIt) > 64) {
                    // too many bits!
                    _at = at;
                    return false;
                }
            }

            if (convBufIt == _convBuf.begin()) {
                // `0b` followed by something else than `0` or `1`
                _at = at;
                return false;
            }

            auto tmpValue = 0ULL;
            auto curMul = 1ULL;
            value = 0;
            auto it = convBufIt - 1;

            while (true) {
                if (*it == '1') {
                    tmpValue += curMul;
                }

                curMul *= 2;

                if (it == _convBuf.begin()) {
                    break;
                }

                --it;
            }

            if (std::is_signed<ValueT>::value) {
                if (negate) {
                    if (tmpValue > llMaxAsUll + 1) {
                        _at = at;
                        return false;
                    }
                } else {
                    if (tmpValue > llMaxAsUll) {
                        _at = at;
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
    auto tmpValue = std::strtoull(&(*_at), &strEnd, 0);

    if ((tmpValue == 0 && &(*_at) == strEnd) || errno == ERANGE) {
        _at = at;
        errno = 0;
        return false;
    }

    if (std::is_signed<ValueT>::value) {
        if (negate) {
            if (tmpValue > llMaxAsUll + 1) {
                _at = at;
                return false;
            }
        } else {
            if (tmpValue > llMaxAsUll) {
                _at = at;
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

#endif // _YACTFR_METADATA_INTERNAL_STR_SCANNER_HPP
