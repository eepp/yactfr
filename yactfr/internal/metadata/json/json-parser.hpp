/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_JSON_JSON_PARSER_HPP
#define _YACTFR_INTERNAL_METADATA_JSON_JSON_PARSER_HPP

#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

#include <yactfr/text-parse-error.hpp>

#include "../str-scanner.hpp"

namespace yactfr {
namespace internal {

/*
 * JSON text parser.
 *
 * This parser parses a single JSON value, calling the methods of a JSON
 * event listener of type `ListenerT` for each JSON event.
 *
 * The requirements of `ListenerT` are the following public methods:
 *
 *     void onNull(const TextLocation&);
 *     void onScalarVal(bool, const TextLocation&);
 *     void onScalarVal(unsigned long long, const TextLocation&);
 *     void onScalarVal(long long, const TextLocation&);
 *     void onScalarVal(double, const TextLocation&);
 *     void onScalarVal(const std::string&, const TextLocation&);
 *     void onArrayBegin(const TextLocation&);
 *     void onArrayEnd(const TextLocation&);
 *     void onObjBegin(const TextLocation&);
 *     void onObjKey(const std::string&, const TextLocation&);
 *     void onObjEnd(const TextLocation&);
 *
 * The received text location always indicate the location of the
 * _beginning_ of the text representing the JSON value.
 */
template <typename ListenerT>
class JsonParser final
{
public:
    /*
     * Builds a JSON text parser, wrapping a string between `begin`
     * (included) and `end` (excluded), and parses it, calling the
     * methods of the JSON event listener `listener`.
     *
     * Throws `TextParseError` when there's a parsing error, including
     * when it can't fully parse the JSON string as a valid JSON value.
     */
    explicit JsonParser(const char *begin, const char *end, ListenerT& listener);

private:
    /*
     * Parses the whole JSON string.
     */
    void _parse();

    /*
     * Expects a JSON value.
     */
    void _expectVal();

    /*
     * Tries to parse `null`, calling the event listener on success.
     */
    bool _tryParseNull();

    /*
     * Tries to parse `true` or `false`, calling the event listener on
     * success.
     */
    bool _tryParseBool();

    /*
     * Tries to parse a JSON number, calling the event listener on
     * success.
     */
    bool _tryParseNumber();

    /*
     * Tries to parse a JSON object key, calling the event listener on
     * success.
     */
    bool _tryParseObjKey();

    /*
     * Tries to parse a JSON string.
     */
    bool _tryParseStr();

    /*
     * Tries to parse a JSON array.
     */
    bool _tryParseArray();

    /*
     * Tries to parse a JSON object.
     */
    bool _tryParseObj();

    /*
     * Expects a specific token, throwing an exception if not found.
     */
    void _expectToken(const char * const token)
    {
        if (!this->_tryScanToken(token)) {
            std::ostringstream ss;

            ss << "Expecting `" << token << "`.";
            throwTextParseError(ss.str(), _ss.loc());
        }
    }

    bool _tryScanToken(const char * const token)
    {
        return _ss.template tryScanToken<true, false>(token);
    }

    void _skipWhitespaces()
    {
        _ss.template skipCommentsAndWhitespaces<true, false>();
    }

    Index _at() const
    {
        return std::distance(_ss.begin(), _ss.at());
    }

    const std::string *_tryScanLitStr()
    {
        return _ss.template tryScanLitStr<true, false>("/bfnrtu");
    }

    bool _ssCurCharLikeConstRealFracOrExp() const noexcept
    {
        return *_ss.at() == '.' || *_ss.at() == 'E' || *_ss.at() == 'e';
    }

private:
    // underlying string scanner
    StrScanner _ss;

    // event listener
    ListenerT *_listener;

    // object key sets, one for each level
    std::vector<std::unordered_set<std::string>> _keys;
};

template <typename ListenerT>
JsonParser<ListenerT>::JsonParser(const char * const begin, const char * const end,
                                  ListenerT& listener) :
    _ss {begin, end},
    _listener {&listener}
{
    assert(end >= begin);
    this->_parse();
}

template <typename ListenerT>
void JsonParser<ListenerT>::_expectVal()
{
    if (this->_tryParseNull()) {
        return;
    }

    if (this->_tryParseBool()) {
        return;
    }

    if (this->_tryParseStr()) {
        return;
    }

    if (this->_tryParseArray()) {
        return;
    }

    if (this->_tryParseObj()) {
        return;
    }

    /*
     * This one is last because it's potentially slow due to calling
     * StrScanner::tryScanConstReal().
     */
    if (this->_tryParseNumber()) {
        return;
    }

    // nothing valid found
    throwTextParseError("Expecting a JSON value: `null`, `true`, `false`, a supported number "
                        "(for an integer: -9,223,372,036,854,775,808 to 18,446,744,073,709,551,615), "
                        "`\"` (a string), `[` (an array), or `{` (an object).", _ss.loc());
}

template <typename ListenerT>
void JsonParser<ListenerT>::_parse()
{
    // expect a single JSON value
    this->_expectVal();

    // skip trailing whitespaces
    this->_skipWhitespaces();

    // make sure all the text is consumed
    if (!_ss.isDone()) {
        throwTextParseError("Extra data after parsed JSON value.", _ss.loc());
    }
}

template <typename ListenerT>
bool JsonParser<ListenerT>::_tryParseNull()
{
    this->_skipWhitespaces();

    const auto loc = _ss.loc();

    if (this->_tryScanToken("null")) {
        _listener->onNull(loc);
        return true;
    }

    return false;
}

template <typename ListenerT>
bool JsonParser<ListenerT>::_tryParseBool()
{
    this->_skipWhitespaces();

    const auto loc = _ss.loc();

    if (this->_tryScanToken("true")) {
        _listener->onScalarVal(true, loc);
        return true;
    } else if (this->_tryScanToken("false")) {
        _listener->onScalarVal(false, loc);
        return true;
    }

    return false;
}

template <typename ListenerT>
bool JsonParser<ListenerT>::_tryParseNumber()
{
    this->_skipWhitespaces();

    const auto loc = _ss.loc();

    /*
     * The tryScanConstReal() method call below is somewhat expensive
     * currently because it involves calling std::regex_search() to
     * confirm the JSON constant real number form.
     *
     * The strategy below is to:
     *
     * 1. Call the tryScanConstUInt() and tryScanConstSInt() methods
     *    first.
     *
     *    If either one succeeds, make sure the scanned JSON number
     *    can't be in fact a real number. If it can, then reset the
     *    position of the string scanner to before the parsed JSON
     *    number.
     *
     * 2. Call the tryScanConstReal() method.
     */
    {
        StrScannerRejecter ssRej {_ss};

        if (const auto val = _ss.template tryScanConstUInt<true, false, false>()) {
            if (!this->_ssCurCharLikeConstRealFracOrExp()) {
                // confirmed unsigned integer form
                _listener->onScalarVal(*val, loc);
                ssRej.accept();
                return true;
            }
        } else if (const auto val = _ss.template tryScanConstSInt<true, false, false>()) {
            if (!this->_ssCurCharLikeConstRealFracOrExp()) {
                // confirmed signed integer form
                _listener->onScalarVal(*val, loc);
                ssRej.accept();
                return true;
            }
        }
    }

    if (const auto val = _ss.template tryScanConstReal<true, false>()) {
        _listener->onScalarVal(*val, loc);
        return true;
    }

    return false;
}

template <typename ListenerT>
bool JsonParser<ListenerT>::_tryParseStr()
{
    this->_skipWhitespaces();

    const auto loc = _ss.loc();

    if (const auto str = this->_tryScanLitStr()) {
        _listener->onScalarVal(*str, loc);
        return true;
    }

    return false;
}

template <typename ListenerT>
bool JsonParser<ListenerT>::_tryParseObjKey()
{
    this->_skipWhitespaces();

    const auto loc = _ss.loc();

    if (const auto str = this->_tryScanLitStr()) {
        assert(!_keys.empty());

        if (_keys.back().count(*str) != 0) {
            std::ostringstream ss;

            ss << "Duplicate JSON object key `" << *str << "`.";
            throwTextParseError(ss.str(), loc);
        }

        _keys.back().insert(*str);
        _listener->onObjKey(*str, loc);
        return true;
    }

    return false;
}

template <typename ListenerT>
bool JsonParser<ListenerT>::_tryParseArray()
{
    this->_skipWhitespaces();

    const auto loc = _ss.loc();

    if (!this->_tryScanToken("[")) {
        return false;
    }

    // beginning of array
    _listener->onArrayBegin(loc);

    if (this->_tryScanToken("]")) {
        // empty array
        _listener->onArrayEnd(loc);
        return true;
    }

    while (true) {
        // element
        this->_expectVal();

        if (!this->_tryScanToken(",")) {
            // end of array
            break;
        }
    }

    // end of array
    this->_expectToken("]");
    _listener->onArrayEnd(loc);
    return true;
}

template <typename ListenerT>
bool JsonParser<ListenerT>::_tryParseObj()
{
    this->_skipWhitespaces();

    const auto loc = _ss.loc();

    if (!this->_tryScanToken("{")) {
        return false;
    }

    // beginning of object
    _listener->onObjBegin(loc);

    if (this->_tryScanToken("}")) {
        // empty object
        _listener->onObjEnd(loc);
        return true;
    }

    _keys.push_back({});

    while (true) {
        // key
        this->_skipWhitespaces();

        if (!this->_tryParseObjKey()) {
            throwTextParseError("Expecting a JSON object key (double-quoted string).", _ss.loc());
        }

        // colon
        this->_expectToken(":");

        // element
        this->_expectVal();

        if (!this->_tryScanToken(",")) {
            // end of object
            break;
        }
    }

    // end of object
    assert(!_keys.empty());
    _keys.pop_back();
    this->_expectToken("}");
    _listener->onObjEnd(loc);
    return true;
}

template <typename ListenerT>
void parseJson(const char * const begin, const char * const end, ListenerT& listener)
{
    JsonParser<ListenerT> {begin, end, listener}; //-V607
}

template <typename ListenerT>
void parseJson(const std::string& str, ListenerT& listener)
{
    JsonParser<ListenerT> {str.data(), str.data() + str.size(), listener}; //-V607
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_JSON_JSON_PARSER_HPP
