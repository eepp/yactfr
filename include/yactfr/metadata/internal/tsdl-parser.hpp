/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_TSDL_PARSER_HPP
#define _YACTFR_METADATA_INTERNAL_TSDL_PARSER_HPP

#include <cstdlib>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
#include <cassert>
#include <utility>
#include <unordered_map>
#include <boost/utility.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include "../../aliases.hpp"
#include "../trace-type.hpp"
#include "../fl-int-type.hpp"
#include "../fl-float-type.hpp"
#include "../fl-enum-type.hpp"
#include "../nt-str-type.hpp"
#include "../sl-array-type.hpp"
#include "../sl-str-type.hpp"
#include "../dl-array-type.hpp"
#include "../dl-str-type.hpp"
#include "../struct-type.hpp"
#include "../struct-member-type.hpp"
#include "../var-type.hpp"
#include "../var-type-opt.hpp"
#include "../data-loc.hpp"
#include "../metadata-parse-error.hpp"
#include "../aliases.hpp"
#include "../../internal/utils.hpp"
#include "tsdl-parser-base.hpp"
#include "tsdl-attr.hpp"
#include "str-scanner.hpp"

namespace yactfr {

template <typename ParserCharIt>
std::pair<TraceType::UP, TraceEnvironment> fromMetadataText(ParserCharIt, ParserCharIt);

namespace internal {

/*
 * TSDL metadata stream parser.
 *
 * This parser parses a CTF (TSDL) metadata string and then contains:
 *
 * * A corresponding trace type object.
 * * A corresponding trace environment object.
 *
 * Parsing methods which return `bool` can backtrack: if they return
 * `false`, then the state of the parser is as it was when calling them.
 */
template <typename CharIt>
class TsdlParser final :
    public TsdlParserBase
{
    template <typename ParserCharIt>
    friend std::pair<TraceType::UP, TraceEnvironment> yactfr::fromMetadataText(ParserCharIt,
                                                                               ParserCharIt);

private:
    /*
     * Builds a metadata parser, wrapping a string between `begin`
     * (included) and `end` (excluded) and parses it.
     *
     * You can release the resulting trace type from this parser with
     * releaseTraceType() and get the trace environment with traceEnv().
     *
     * Throws `MetadataParseError` when there was a parsing error.
     */
    explicit TsdlParser(CharIt begin, CharIt end);

private:
    using _StrScannerRejecter = StrScannerRejecter<CharIt>;

    /*
     * A "fast" pseudo fixed-length integer type entry.
     *
     * Often, fixed-length integer types, which are usually the most
     * used data types, are written exactly the same in the metadata
     * string. For example, LTTng-modules 2.7 emits a whole bunch of
     * this exact string:
     *
     *     integer { size = 32; align = 8; signed = 1; encoding = none; base = 10; }
     *
     * To avoid parsing this substring as 5 attributes each time, we
     * keep it in a cache after the first time we parse it.
     *
     * This cache associates a substring, from `begin` to `end`, to the
     * parsed pseudo data type. If it is found using
     * _fastPseudoFlIntType(), then you can clone the cached pseudo data
     * type to have your own copy.
     *
     * The maximum size from `begin` to `end` is
     * `_MAX_FAST_FL_INT_TYPE_STR_SIZE`.
     *
     * Is it really worth it? I don't know! Is it a cool idea even
     * without benchmarks? I think so.
     */
    struct _FastPseudoFlIntTypeEntry final
    {
        CharIt begin;
        CharIt end;
        PseudoDt::UP pseudoDt;
    };

private:
    /*
     * Parses the whole metadata string, creating the resulting trace
     * type and trace environment on success, throwing an exception
     * otherwise.
     */
    void _parseMetadata();

    /*
     * Tries to parse one individual root block with a terminating `;`.
     * Root blocks can be explicit data type aliases (including data
     * type definitions), named enumeration/structure/variant types,
     * `trace`, `env`, `clock`, `stream`, `event`, and `callsite`
     * blocks.
     *
     * Returns whether or not a root block was parsed.
     */
    bool _tryParseRootBlock();

    /*
     * Tries to parse a data type alias given by a named
     * enumeration/structure/variant type, terminating with `;`, adding
     * it to the map of aliased pseudo data types of the current frame
     * on success.
     *
     * Returns whether or not a named enumeration/structure/variant type
     * was parsed.
     *
     * Examples:
     *
     *     struct hello {
     *         ...
     *     };
     *
     *     enum my_enum : some_int {
     *         ...
     *     };
     *
     *     variant my_variant {
     *         ...
     *     };
     *
     *     variant my_variant <event.fields.some.tag> {
     *         ...
     *     };
     */
    bool _tryParseFlEnumStructVarDtAlias();

    /*
     * Tries to parse a `typealias` or `typedef` block, adding it to the
     * map of aliased pseudo data types of the current frame on success.
     *
     * Returns whether or not a generic data type alias block was
     * parsed.
     *
     * Examples:
     *
     *     typealias integer {
     *         size = 23;
     *         align = 8;
     *     } := const unsigned int;
     *
     *     typealias string := my_string;
     *
     *     typealias struct {
     *         int a;
     *         int b;
     *     } align(16) := my_struct;
     *
     *     typedef integer {
     *         size = 23;
     *         align = 8;
     *     } const unsigned int;
     *
     *     typedef string my_string;
     *
     *     typedef struct {
     *         int a;
     *         int b;
     *     } align(16) my_struct;
     */
    bool _tryParseGenericDtAlias();

    /*
     * Tries to parse any data type alias, generic (`typealias`,
     * `typedef` keywords) or named enumeration/structure/variant type,
     * adding it to the map of aliased data types of the current frame
     * on success.
     *
     * Returns whether or not a data type alias was parsed.
     */
    bool _tryParseDtAlias();

    /*
     * Expects a generic attribute, with a terminating `;`.
     *
     * Returns the parsed attribute.
     *
     * Examples:
     *
     *     size = 23;
     *
     *     byte_order = be;
     *
     *     map = clock.name.value;
     *
     *     name = "my event";
     */
    TsdlAttr _expectAttr();

    /*
     * Tries to parse a scope data type with a terminating `;` and
     * returns it.
     *
     * `scopeDtStackFrameKind` is the kind of stack frame to push for
     * this scope data type.
     *
     * `firstName` and optional `secondName` are the one or two words
     * naming the scope, e.g., `event` and `header`, or just `context`.
     *
     * If `expect` is true, then the method throws if it cannot parse
     * the scope data type successfully. Otherwise, the method can
     * return `nullptr` if it cannot parse the scope data type.
     *
     * Examples:
     *
     *     packet.context := struct { ... };
     *
     *     fields := event_fields;
     *
     *     event.header := struct my_event_header;
     */
    PseudoDt::UP _tryParseScopeDt(const _StackFrame::Kind scopeDtStackFrameKind,
                                  const std::string& firstName,
                                  const boost::optional<std::string>& secondName = boost::none,
                                  bool expect = true);

    /*
     * Tries to parse an identifier followed by zero or more array
     * subscripts.
     *
     * This method sets `ident` to the parsed identifier.
     *
     * `innerPseudoDt` is the most nested pseudo data type to wrap. This
     * method returns it as is if there's only an identifier not
     * followed by an opening square bracket.
     *
     * Examples:
     *
     *     my_field
     *
     *     my_field[1]
     *
     *     my_field[event.context.some.location][23][len]
     */
    PseudoDt::UP _tryParseIdentArraySubscripts(std::string& ident, PseudoDt::UP innerPseudoDt);

    /*
     * Like _tryParseIdentArraySubscripts(), but without the identifier
     * part.
     *
     * Examples:
     *
     *     [1]
     *
     *     [length]
     *
     *     [event.context.some.location][23][len];
     */
    PseudoDt::UP _parseArraySubscripts(PseudoDt::UP innerType);

    /*
     * Parses a data type alias name, without parsing an identifier name
     * that would follow.
     *
     * On success, `dtAliasName` contains the name of the alias.
     *
     * If `expect` is true, then the method throws if it fails to parse
     * a data type alias name. Otherwise, returns whether or not a data
     * type alias name was parsed.
     *
     * Examples:
     *
     *     my_alias
     *
     *     const unsigned int
     *
     *     signed long long
     */
    bool _parseDtAliasName(std::string& dtAliasName, bool expect);

    /*
     * Expects a data location, returning a corresponding
     * pseudo data location on success.
     *
     * Throws if it cannot parse a data location successfully.
     *
     * Examples:
     *
     *     trace.packet.header.some_size
     *
     *     my.len
     *
     *     env.some_key
     */
    PseudoDataLoc _expectDataLoc();

    /*
     * Parses a reference to a data type alias, that is, one of:
     *
     * * `enum NAME` not followed by `:` or `{`
     * * `struct NAME` not followed by `{`
     * * `variant NAME` or `variant NAME <ABS-TAG>` not followed by `{`
     * * `some_alias_name` (keywords are excluded)
     *
     * This method returns the aliased pseudo data type, or `nullptr` if
     * it cannot find it.
     *
     * Examples:
     *
     *     enum my_enum
     *
     *     struct my_struct
     *
     *     variant my_variant
     *
     *     variant my_variant <stream.packet.context.my.tag>;
     *
     * Not supported (named variant type with relative selector
     * location):
     *
     *     variant my_variant <my.tag>;
     */
    PseudoDt::UP _tryParseDtAliasRef();

    /*
     * Expects a specific token, throwing an exception if not found.
     */
    void _expectToken(const std::string& token);

    /*
     * Tries to parse a member type/option or a data type alias, with a
     * terminating `;`, adding the result to `entries` if found, and
     * adding any parsed data type alias to the map of aliased data
     * types of the current frame on success.
     *
     * Examples:
     *
     *     integer { size = 23; } my_field[34];
     *
     *     struct some_struct {
     *         ...
     *     };
     *
     *     variant hello <stream.packet.context.tag> {
     *         ...
     *     } the_var;
     *
     *     typealias string := string_t;
     */
    bool _tryParseNamedDtOrDtAlias(PseudoNamedDts& entries);

    /*
     * Tries to parse a data type, which also includes a data type alias
     * reference.
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     */
    PseudoDt::UP _tryParseDt();

    /*
     * Tries to parse a data type block (excludes data type alias
     * references).
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     */
    PseudoDt::UP _tryParseFullDt();

    /*
     * Tries to parse a fixed-length integer type block.
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     *
     * Example:
     *
     *     integer {
     *         size = 32;
     *         align = 32;
     *         base = x;
     *         byte_order = be;
     *     }
     */
    PseudoDt::UP _tryParseFlIntType();

    /*
     * Tries to parse a fixed-length floating point number type block.
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     *
     * Example:
     *
     *     floating_point {
     *         mant_dig = 24;
     *         exp_dig = 8;
     *         byte_order = le;
     *     }
     */
    PseudoDt::UP _tryParseFlFloatType();

    /*
     * Tries to parse a null-terminated string type block.
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     *
     * Examples:
     *
     *     string
     *
     *     string {
     *         encoding = ascii;
     *     }
     */
    PseudoDt::UP _tryParseNtStrType();

    /*
     * Tries to parse a fixed-length enumeration type block.
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     *
     * If the parser makes it to the `:` or `{` token and the
     * fixed-length enumeration type is named, this method adds a data
     * type alias to the map of aliased data types of the current frame
     * if `addDtAlias` is true, and sets `*dtAliasName` to the name of
     * the data type alias.
     *
     * Example:
     *
     *     enum hello : my_int {
     *         MEOW,
     *         "MIX",
     *         ZOOM = 34,
     *         "HAR TENVAR" = -17 ... 28,
     *     }
     */
    PseudoDt::UP _tryParseFlEnumType(bool addDtAlias = true, std::string *dtAliasName = nullptr);

    template <typename FlEnumTypeT, typename CreatePseudoDtFuncT>
    PseudoDt::UP _finishParseFlEnumType(PseudoDt::UP pseudoDt, bool addDtAlias,
                                        std::string&& potDtAliasName,
                                        CreatePseudoDtFuncT&& createPseudoDtFunc);

    /*
     * Tries to parse a structure type block.
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     *
     * If the parser makes it to the opening `{` and the structure type
     * is named, this method adds a data type alias to the map of
     * aliased data types of the current frame if `addDtAlias` is true,
     * and sets `*dtAliasName` to the name of the data type alias.
     *
     * Example:
     *
     *     struct {
     *         my_int a;
     *         floating_point {
     *             mant_dig = 24;
     *             exp_dig = 8;
     *             align = 32;
     *         } b;
     *         struct {
     *             uint32 u;
     *             string s;
     *         } c;
     *     } align(64)
     */
    PseudoDt::UP _tryParseStructType(bool addDtAlias = true, std::string *dtAliasName = nullptr);

    /*
     * Tries to parse a variant type block.
     *
     * Returns the parsed pseudo data type, or `nullptr` if it can't.
     *
     * If the parser makes it to the opening `{` and the variant type is
     * named, this method adds a data type alias to the map of aliased
     * data types of the current frame if `addDtAlias` is true, and sets
     * `*dtAliasName` to the name of the data type alias.
     *
     * Example:
     *
     *     variant <path.to.tag> {
     *         string s;
     *         integer { size = 32; align = 32; } i;
     *     }
     */
    PseudoDt::UP _tryParseVarType(bool addDtAlias = true, std::string *dtAliasName = nullptr);

    /*
     * Tries to parse a trace environment block and sets `_traceEnv`
     * accordingly.
     *
     * Returns whether or not a trace environment block was parsed.
     *
     * Example:
     *
     *     env {
     *         some_int = -23;
     *         some_str = "some string";
     *     };
     */
    bool _tryParseEnvBlock();

    /*
     * Tries to parse a clock type block and appends it to the current
     * pseudo trace type data.
     *
     * Returns whether or not a clock type block was parsed.
     *
     * Example:
     *
     *     clock {
     *         name = "monotonic";
     *         uuid = "6a16447b-5fc6-4870-9762-87e183306de7";
     *         description = "Monotonic Clock";
     *         freq = 1000000000;
     *         offset = 1446222697389173303;
     *     };
     */
    bool _tryParseClkTypeBlock();

    /*
     * Tries to parse a callsite block and ignores it.
     *
     * Returns whether or not a callsite block was parsed.
     *
     * Example:
     *
     *     callsite {
     *         name = "event_name";
     *         func = "func_name";
     *         file = "myfile.c";
     *         line = 39;
     *         ip = 0x40096c;
     *     };
     */
    bool _tryParseCallsiteBlock();

    /*
     * Tries to parse a trace type block and sets its properties in the
     * current pseudo trace type data.
     *
     * Returns whether or not a trace type block was parsed.
     *
     * Example:
     *
     *     trace {
     *         major = 1;
     *         minor = 8;
     *         byte_order = be;
     *         packet.header := struct {
     *             uint32_t magic;
     *             uint8_t  uuid[16];
     *             uint32_t stream_id;
     *             uint64_t stream_instance_id;
     *         };
     *     };
     */
    bool _tryParseTraceTypeBlock();

    /*
     * Tries to parse a data stream type block and initializes a pseudo
     * stream type.
     *
     * Returns whether or not a data stream type block was parsed.
     *
     * Example:
     *
     *     stream {
     *         id = 2;
     *         packet.context := ...;
     *         event.header := ...;
     *         event.context := ...;
     *     };
     */
    bool _tryParseDstBlock();

    /*
     * Tries to parse an event record type block and inserts a resulting
     * pseudo event record type into its pseudo data stream type.
     *
     * Returns whether or not an event record type block was parsed.
     *
     * Example:
     *
     *     event {
     *         id = 2;
     *         name = sched_switch;
     *         loglevel = 23;
     *         model.emf.uri = "something";
     *         event.context := ...;
     *         event.fields := ...;
     *     };
     */
    bool _tryParseErtBlock();

    /*
     * Returns a fast pseudo fixed-length integer type clone from the
     * fast pseudo fixed-length integer type cache, or `nullptr` if not
     * found.
     */
    PseudoDt::UP _fastPseudoFlIntType(TextLocation loc);

    TextLocation _curLoc() const
    {
        return TextLocation {_ss.curLineNumber(), _ss.curColNumber()};
    }

    /*
     * Inserts a clone of the pseudo fixed-length integer type
     * `pseudoIntType` having the corresponding TSDL string from `begin`
     * (inclusive) to `end` (exclusive) into the fast pseudo
     * fixed-length integer type cache.
     */
    void _insertFastPseudoFlIntType(CharIt begin, CharIt end, const PseudoDt& pseudoIntType);

    Index _at() const
    {
        return std::distance(_ss.begin(), _ss.at());
    }

    void _skipCommentsAndWhitespacesAndSemicolons()
    {
        while (true) {
            _ss.skipCommentsAndWhitespaces();

            if (!_ss.scanToken(";")) {
                break;
            }
        }
    }

    void _addDtAlias(std::string&& name, const PseudoDt& pseudoDt)
    {
        TsdlParserBase::_addDtAlias(std::move(name), pseudoDt, this->_curLoc());
    }

private:
    /*
     * Escapes the literal string between `begin` (inclusive) and `end`
     * (exclusive).
     *
     * The passed substring excludes the double quotes.
     *
     * Examples:
     *
     *     salut\nvous -> "salut\nvous" (C string)
     *     lenovo\tx230 -> "lenovo\tx230" (C string)
     */
    static std::string _escapeLiteralStr(const CharIt begin, const CharIt end,
                                         const TextLocation& loc)
    {
        std::string str;

        str.reserve(end - begin);

        auto it = begin;

        while (it < end) {
            if (*it == '\\') {
                if (it + 2 < end) {
                    const auto eChar = *(it + 1);

                    switch (eChar) {
                    case '\\':
                    case '"':
                        str += eChar;
                        ++it;
                        break;

                    case 't':
                        str += '\t';
                        ++it;
                        break;

                    case 'n':
                        str += '\n';
                        ++it;
                        break;

                    case 'r':
                        str += '\r';
                        ++it;
                        break;

                    case 'v':
                        str += '\v';
                        ++it;
                        break;

                    default:
                        str += '\\';
                        break;
                    }
                } else {
                    str += '\\';
                }
            } else if (*it == 13) {
                // skip carriage return
                ++it;
                continue;
            } else if ((*it >= 0 && *it <= 8) || (*it >= 12 && *it <= 31) || *it == 127) {
                // disallow those control characters in the metadata text
                std::ostringstream ss;

                ss << "Illegal character found in literal string: 0x" <<
                      std::hex << static_cast<int>(*it) << ".";
                throwMetadataParseError(ss.str(), loc);
            } else {
                str += *it;
            }

            ++it;
        }

        return str;
    }

private:
    // underlying string scanner
    StrScanner<CharIt> _ss;

    // cache of TSDL substrings to pseudo fixed-length integer types
    std::vector<_FastPseudoFlIntTypeEntry> _fastPseudoFlIntTypes;
};

template <typename CharIt>
TsdlParser<CharIt>::TsdlParser(CharIt begin, CharIt end) :
    _ss {begin, end}
{
    assert(end >= begin);
    this->_parseMetadata();
}

template <typename CharIt>
void TsdlParser<CharIt>::_parseMetadata()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::ROOT};

    while (this->_tryParseRootBlock());

    // make sure we skip the remaining fruitless stuff
    this->_skipCommentsAndWhitespacesAndSemicolons();

    if (!_ss.isDone()) {
        throwMetadataParseError("Expecting data type alias (`typealias`, `typedef`, `enum NAME`, "
                                "`struct NAME`, or `variant NAME`), trace type block (`trace`), "
                                "environment block of trace type (`env`), "
                                "clock type block (`clock`), data stream type block (`stream`), "
                                "or event record type block (`event`). Did you forget the `;` "
                                "after the closing `}` of the block?",
                                this->_curLoc());
    }

    if (!_pseudoTraceType) {
        throwMetadataParseError("Missing `trace` block.");
    }

    // create a yactfr trace type from the pseudo trace type
    this->_createTraceType();
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseRootBlock()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto loc = this->_curLoc();

    if (this->_tryParseDtAlias()) {
        return true;
    }

    try {
        if (this->_tryParseErtBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        appendMsgToMetadataParseError(error, "In `event` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseDstBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        appendMsgToMetadataParseError(error, "In `stream` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseTraceTypeBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        appendMsgToMetadataParseError(error, "In `trace` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseEnvBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        appendMsgToMetadataParseError(error, "In `env` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseClkTypeBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        appendMsgToMetadataParseError(error, "In `clock` root block:", loc);
        throw;
    }

    try {
        // parse callsite, even if we don't care about it
        if (this->_tryParseCallsiteBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        appendMsgToMetadataParseError(error, "In `callsite` root block:", loc);
        throw;
    }

    return false;
}

template <typename CharIt>
void TsdlParser<CharIt>::_expectToken(const std::string& token)
{
    if (!_ss.scanToken(token)) {
        std::ostringstream ss;

        ss << "Expecting `" << token << "`.";
        throwMetadataParseError(ss.str(), this->_curLoc());
    }
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseFlEnumStructVarDtAlias()
{
    PseudoDt::UP pseudoDt;
    std::string dtAliasName;

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto loc = this->_curLoc();

    // try fixed-length enumeration type alias
    {
        _StrScannerRejecter ssRej {_ss};

        try {
            pseudoDt = this->_tryParseFlEnumType(false, &dtAliasName);
        } catch (MetadataParseError& error) {
            appendMsgToMetadataParseError(error, "In `enum` block:", loc);
            throw;
        }

        if (pseudoDt) {
            // parse `;` to make sure it's not a member type/option
            if (_ss.scanToken(";")) {
                // we have a winner
                ssRej.accept();

                /*
                 * Add data type alias if a data type alias name was found
                 * (safe to move here).
                 */
                if (!dtAliasName.empty()) {
                    this->_addDtAlias(std::move(dtAliasName), *pseudoDt);
                }

                return true;
            }
        }
    }

    // try structure type alias
    {
        _StrScannerRejecter ssRej {_ss};

        try {
            pseudoDt = this->_tryParseStructType(false, &dtAliasName);
        } catch (MetadataParseError& error) {
            appendMsgToMetadataParseError(error, "In `struct` block:", loc);
            throw;
        }

        if (pseudoDt) {
            // parse `;` to make sure it's not a member type/option
            if (_ss.scanToken(";")) {
                // we have a winner
                ssRej.accept();

                /*
                 * Add data type alias if a data type alias name was found
                 * (safe to move here).
                 */
                if (!dtAliasName.empty()) {
                    this->_addDtAlias(std::move(dtAliasName), *pseudoDt);
                }

                return true;
            }
        }
    }

    // try variant type alias
    {
        _StrScannerRejecter ssRej {_ss};

        try {
            pseudoDt = this->_tryParseVarType(false, &dtAliasName);
        } catch (MetadataParseError& error) {
            appendMsgToMetadataParseError(error, "In `variant` block:", loc);
            throw;
        }

        if (pseudoDt) {
            // parse `;` to make sure it's not a field/option
            if (_ss.scanToken(";")) {
                // we have a winner
                ssRej.accept();

                /*
                 * Add data type alias if a data type alias name was found
                 * (safe to move here).
                 */
                if (!dtAliasName.empty()) {
                    this->_addDtAlias(std::move(dtAliasName), *pseudoDt);
                }

                return true;
            }
        }
    }

    return false;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseGenericDtAlias()
{
    bool isTypealias = false;

    if (_ss.scanToken("typealias")) {
        isTypealias = true;
    } else if (!_ss.scanToken("typedef")) {
        return false;
    }

    PseudoDt::UP pseudoDt;
    std::string dtAliasName;

    {
        _LexicalScope lexScope {*this, _StackFrame::Kind::DT_ALIAS};

        // parse full data type
        pseudoDt = this->_tryParseFullDt();

        if (!pseudoDt) {
            /*
             * Cannot parse a full data type: try an existing data type
             * alias name.
             */
            std::string existingDtAliasName;
            CharIt begin, end;
            const auto loc = this->_curLoc();

            if (_ss.scanIdent(begin, end)) {
                existingDtAliasName.assign(begin, end);

                pseudoDt = this->_aliasedPseudoDt(existingDtAliasName, loc);

                if (!pseudoDt) {
                    throwMetadataParseError("Expecting explicit data type block (`integer`, `floating_point`, "
                                            "`enum`, `string`, `struct`, or `variant`) or "
                                            "existing data type alias name.",
                                            this->_curLoc());
                }
            } else {
                throwMetadataParseError("Expecting explicit data type block (`integer`, `floating_point`, "
                                        "`enum`, `string`, `struct`, or `variant`) or "
                                        "existing data type alias name.",
                                        this->_curLoc());
            }
        }

        // parse `:=` if `typealias` block
        if (isTypealias) {
            this->_expectToken(":=");
        }

        // parse name
        this->_parseDtAliasName(dtAliasName, true);
        pseudoDt = this->_parseArraySubscripts(std::move(pseudoDt));

        // parse `;`
        this->_expectToken(";");
    }

    // add parsed type alias to parent frame
    this->_addDtAlias(std::move(dtAliasName), *pseudoDt);
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseDtAlias()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto loc = this->_curLoc();

    try {
        if (this->_tryParseGenericDtAlias()) {
            return true;
        }
    } catch (MetadataParseError& exc) {
        appendMsgToMetadataParseError(exc, "In data type alias:", loc);
        throw;
    }

    if (this->_tryParseFlEnumStructVarDtAlias()) {
        return true;
    }

    return false;
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseDt()
{
    auto pseudoDt = this->_tryParseDtAliasRef();

    if (pseudoDt) {
        return pseudoDt;
    }

    pseudoDt = this->_tryParseFullDt();

    if (pseudoDt) {
        return pseudoDt;
    }

    return nullptr;
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseFullDt()
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = this->_curLoc();
    PseudoDt::UP pseudoDt;

    try {
        pseudoDt = this->_tryParseFlIntType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (MetadataParseError& exc) {
        appendMsgToMetadataParseError(exc, "In `integer` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseNtStrType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (MetadataParseError& exc) {
        appendMsgToMetadataParseError(exc, "In `string` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseFlEnumType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (MetadataParseError& exc) {
        appendMsgToMetadataParseError(exc, "In `enum` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseFlFloatType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (MetadataParseError& exc) {
        appendMsgToMetadataParseError(exc, "In `floating_point` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseStructType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (MetadataParseError& exc) {
        appendMsgToMetadataParseError(exc, "In `struct` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseVarType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (MetadataParseError& exc) {
        appendMsgToMetadataParseError(exc, "In `variant` block:", loc);
        throw;
    }

    return nullptr;
}

template <typename CharIt>
void TsdlParser<CharIt>::_insertFastPseudoFlIntType(CharIt begin, CharIt end,
                                                    const PseudoDt& pseudoDt)
{
    assert(end >= begin);

    if (static_cast<Size>(std::distance(begin, end)) > TsdlParser::_MAX_FAST_FL_INT_TYPE_STR_SIZE) {
        return;
    }

    _fastPseudoFlIntTypes.push_back({begin, end, pseudoDt.clone()});
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_fastPseudoFlIntType(TextLocation loc)
{
    for (const auto& entry : _fastPseudoFlIntTypes) {
        const auto entrySize = std::distance(entry.begin, entry.end);

        if (_ss.charsLeft() < static_cast<Size>(entrySize)) {
            // would not fit
            continue;
        }

        if (std::equal(entry.begin, entry.end, _ss.at(), _ss.at() + entrySize)) {
            // we have a match!
            _ss.at(_ss.at() + entrySize);

            auto dt = entry.pseudoDt->clone();

            dt->loc(std::move(loc));
            return dt;
        }
    }

    return nullptr;
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseFlIntType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beforeKwLoc = this->_curLoc();

    // parse `integer`
    if (!_ss.scanToken("integer")) {
        return nullptr;
    }

    _ss.skipCommentsAndWhitespaces();

    auto fastPseudoFlIntType = this->_fastPseudoFlIntType(beforeKwLoc);

    if (fastPseudoFlIntType) {
        return fastPseudoFlIntType;
    }

    const auto beginLoc = this->_curLoc();
    const auto beginAt = _ss.at();

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    const auto endAt = _ss.at();

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    auto align = 0U;
    auto size = 0U;
    auto bo = this->_absNativeBo();
    auto dispBase = DisplayBase::DECIMAL;
    auto isSigned = false;
    auto hasEncoding = false;
    boost::optional<std::string> mappedClkTypeName;
    boost::optional<TextLocation> mapAttrLoc;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "base") {
            dispBase = attr.dispBase();
        } else if (attr.name == "size") {
            attr.checkKind(TsdlAttr::Kind::UINT);

            if (attr.uintVal == 0) {
                std::ostringstream ss;

                ss << "Invalid `size` attribute (must be greater than 0): " <<
                      attr.uintVal << ".";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            if (attr.uintVal > 64) {
                std::ostringstream ss;

                ss << "`size` attribute is greater than 64 (unsupported): " <<
                      attr.uintVal << ".";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            size = attr.uintVal;
        } else if (attr.name == "align") {
            align = attr.align();
        } else if (attr.name == "byte_order") {
            const auto attrBo = attr.bo();

            if (attrBo) {
                bo = *attrBo;
            }
        } else if (attr.name == "encoding") {
            hasEncoding = attr.hasEncoding();
        } else if (attr.name == "signed") {
            isSigned = attr.boolEquiv();
        } else if (attr.name == "map") {
            mappedClkTypeName = std::move(attr.strVal);
            mapAttrLoc = attr.nameTextLoc();
        } else {
            attr.throwUnknown();
        }
    }

    // make sure length is set
    if (size == 0) {
        TsdlParser::_throwMissingAttr("size", beforeKwLoc);
    }

    // set default alignment
    if (align == 0) {
        if (size % 8 == 0) {
            align = 8;
        } else {
            align = 1;
        }
    }

    PseudoDt::UP pseudoDt;

    if (isSigned) {
        if (mappedClkTypeName) {
            throwMetadataParseError("Illegal `map` attribute for a fixed-length signed integer type.",
                                    *mapAttrLoc);
        }

        auto intType = std::make_unique<const FixedLengthSignedIntegerType>(align, size, bo, dispBase);

        pseudoDt = std::make_unique<PseudoScalarDtWrapper>(std::move(intType), hasEncoding,
                                                           beforeKwLoc);
    } else {
        pseudoDt = std::make_unique<PseudoFlUIntType>(align, size, bo, dispBase, hasEncoding,
                                                    mappedClkTypeName, beforeKwLoc);
    }

    assert(pseudoDt);

    if (beginLoc.lineNumber() == this->_curLoc().lineNumber()) {
        /*
         * Fast pseudo fixed-length integer type cache only supported
         * for single lines.
         */
        this->_insertFastPseudoFlIntType(beginAt, endAt, *pseudoDt);
    }

    return pseudoDt;
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseFlFloatType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();

    // parse `floating_point`
    if (!_ss.scanToken("floating_point")) {
        return nullptr;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    auto align = 8U;
    auto expDig = 0U;
    auto mantDig = 0U;
    auto bo = this->_absNativeBo();

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "exp_dig") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            expDig = attr.uintVal;
        } else if (attr.name == "mant_dig") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            mantDig = attr.uintVal;
        } else if (attr.name == "align") {
            align = attr.align();
        } else if (attr.name == "byte_order") {
            const auto attrBo = attr.bo();

            if (attrBo) {
                bo = *attrBo;
            }
        } else {
            attr.throwUnknown();
        }
    }

    // make sure `exp_dig` and `mant_dig` attributes are set
    if (expDig == 0) {
        TsdlParser::_throwMissingAttr("exp_dig", beginLoc);
    }

    if (mantDig == 0) {
        TsdlParser::_throwMissingAttr("mant_dig", beginLoc);
    }

    if (!(expDig == 8 && mantDig == 24) && !(expDig == 11 && mantDig == 53)) {
        std::ostringstream ss;

        ss << "Invalid `exp_dig` or `mant_dig` attribute combination: " <<
              "only (8, 24) and (11, 53) are supported.";
        throwMetadataParseError(ss.str(), beginLoc);
    }

    auto floatType = std::make_unique<const FixedLengthFloatingPointNumberType>(align,
                                                                                expDig + mantDig,
                                                                                bo);

    return std::make_unique<PseudoScalarDtWrapper>(std::move(floatType), beginLoc);
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseNtStrType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();

    // parse `string`
    if (!_ss.scanToken("string")) {
        return nullptr;
    }

    // try to parse `{`
    if (!_ss.scanToken("{")) {
        return std::make_unique<PseudoScalarDtWrapper>(std::make_unique<const NullTerminatedStringType>(8),
                                                       beginLoc);
    }

    // parse attributes
    _Attrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "encoding") {
            // only used to validate
            attr.hasEncoding();
        } else {
            attr.throwUnknown();
        }
    }

    return std::make_unique<PseudoScalarDtWrapper>(std::make_unique<const NullTerminatedStringType>(8), beginLoc);
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseFlEnumType(const bool addDtAlias,
                                                     std::string * const dtAliasName)
{
    _StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();

    // parse `enum`
    if (!_ss.scanToken("enum")) {
        return nullptr;
    }

    // try to parse name
    CharIt begin, end;
    std::string potDtAliasName;

    if (_ss.scanIdent(begin, end)) {
        potDtAliasName = "enum ";
        potDtAliasName.append(begin, end);

        if (dtAliasName) {
            *dtAliasName = potDtAliasName;
        }
    }

    {
        _StrScannerRejecter ssRejOp {_ss};

        if (!_ss.scanToken(":") && !_ss.scanToken("{")) {
            return nullptr;
        }
    }

    // accept the fixed-length enumeration type so far
    ssRej.accept();
    _ss.skipCommentsAndWhitespaces();

    PseudoDt::UP pseudoDt;

    // try to parse the fixed-length integer type
    if (_ss.scanToken(":")) {
        _ss.skipCommentsAndWhitespaces();

        // remember location
        const auto loc = this->_curLoc();

        // check for a data type alias name first
        std::string dtAliasName;

        if (this->_parseDtAliasName(dtAliasName, false)) {
            // find data type alias
            pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc);

            if (!pseudoDt) {
                std::ostringstream ss;

                ss << "Cannot find data type alias `" << dtAliasName << "`.";
                throwMetadataParseError(ss.str(), loc);
            }

            if (!pseudoDt->isInt()) {
                std::ostringstream ss;

                ss << "Data type alias `" << dtAliasName << "` isn't an integer type.";
                throwMetadataParseError(ss.str(), loc);
            }
        } else {
            // fall back to expecting `integer`
            pseudoDt = this->_tryParseFlIntType();

            if (!pseudoDt) {
                throwMetadataParseError("Expecting `integer` or existing fixed-length integer type alias name.",
                                        loc);
            }

            pseudoDt->loc(beginLoc);
        }
    } else {
        // use `int` type alias
        pseudoDt = this->_aliasedPseudoDt("int", beginLoc);

        if (!pseudoDt) {
            throwMetadataParseError("Implicit `int` data type alias doesn't exist in this scope.",
                                    beginLoc);
        }

        if (!pseudoDt->isInt()) {
            throwMetadataParseError("Implicit `int` data type alias isn't a fixed-length integer type.",
                                    beginLoc);
        }
    }

    // parse `{`
    this->_expectToken("{");

    // parse mappings
    assert(pseudoDt->isInt());

    if (pseudoDt->isUInt()) {
        return this->_finishParseFlEnumType<FixedLengthUnsignedEnumerationType>(std::move(pseudoDt), addDtAlias,
                                                                                std::move(potDtAliasName),
                                                                                [](const auto& pseudoDt,
                                                                                   const auto& mappings) {
            const auto& pseudoUIntType = static_cast<const PseudoFlUIntType&>(pseudoDt);

            return std::make_unique<PseudoFlUEnumType>(pseudoUIntType.align(),
                                                       pseudoUIntType.len(), pseudoUIntType.bo(),
                                                       pseudoUIntType.prefDispBase(), mappings,
                                                       pseudoUIntType.hasEncoding(),
                                                       pseudoUIntType.mappedClkTypeName(),
                                                       pseudoDt.loc());
        });
    } else {
        return this->_finishParseFlEnumType<SignedFixedLengthEnumerationType>(std::move(pseudoDt), addDtAlias,
                                                                              std::move(potDtAliasName),
                                                                              [](const auto& pseudoDt,
                                                                                 const auto& mappings) {
            auto& intType = static_cast<const PseudoScalarDtWrapper&>(pseudoDt).dt().asFixedLengthIntegerType();
            auto enumType = std::make_unique<SignedFixedLengthEnumerationType>(intType.alignment(),
                                                                               intType.length(),
                                                                               intType.byteOrder(),
                                                                               mappings,
                                                                               intType.preferredDisplayBase());

            return std::make_unique<PseudoScalarDtWrapper>(std::move(enumType), pseudoDt.loc());
        });
    }
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseStructType(const bool addDtAlias,
                                                     std::string * const dtAliasName)
{
    _StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();

    // parse `struct`
    if (!_ss.scanToken("struct")) {
        return nullptr;
    }

    // try to parse name
    CharIt begin, end;
    std::string potDtAliasName;
    PseudoDt::UP pseudoDt;

    {
        _LexicalScope dtAliasLexScope;

        if (_ss.scanIdent(begin, end)) {
            potDtAliasName = "struct ";
            potDtAliasName.append(begin, end);

            if (dtAliasName) {
                dtAliasLexScope = _LexicalScope {*this, _StackFrame::Kind::DT_ALIAS};
                *dtAliasName = potDtAliasName;
            }
        }

        {
            _LexicalScope structTypeLexScope {*this, _StackFrame::Kind::STRUCT_TYPE};

            // parse `{`
            if (!_ss.scanToken("{")) {
                return nullptr;
            }

            // parse data type aliases and member types
            PseudoNamedDts pseudoMemberTypes;

            while (true) {
                this->_skipCommentsAndWhitespacesAndSemicolons();

                if (_ss.scanToken("}")) {
                    break;
                }

                const auto loc = this->_curLoc();
                bool success;

                try {
                    success = this->_tryParseNamedDtOrDtAlias(pseudoMemberTypes);
                } catch (MetadataParseError& exc) {
                    appendMsgToMetadataParseError(exc, "While parsing body of `struct` block:", loc);
                    throw;
                }

                if (!success) {
                    throwMetadataParseError("Expecting member type with known data type "
                                            "or data type alias.",
                                            this->_curLoc());
                }
            }

            ssRej.accept();

            // check for duplicate member type
            TsdlParser::_checkDupPseudoNamedDt(pseudoMemberTypes, beginLoc);

            auto align = 1ULL;

            if (_ss.scanToken("align")) {
                this->_expectToken("(");

                if (!_ss.scanConstInt(align)) {
                    throwMetadataParseError("Expecting valid constant unsigned integer.",
                                            this->_curLoc());
                }

                if (!isPowOfTwo(align)) {
                    std::ostringstream ss;

                    ss << "Invalid minimum alignment for `struct` block " <<
                          "(must be a power of two): " << align << ".";
                    throwMetadataParseError(ss.str(), this->_curLoc());
                }

                this->_expectToken(")");
            }

            pseudoDt = std::make_unique<PseudoStructType>(align, std::move(pseudoMemberTypes),
                                                          beginLoc);
        }
    }

    if (addDtAlias && !potDtAliasName.empty()) {
        this->_addDtAlias(std::move(potDtAliasName), *pseudoDt);
    }

    return pseudoDt;
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseVarType(const bool addDtAlias,
                                                  std::string * const dtAliasName)
{
    _StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();

    // parse `variant`
    if (!_ss.scanToken("variant")) {
        return nullptr;
    }

    // try to parse name
    CharIt begin, end;
    std::string potDtAliasName;
    PseudoDt::UP pseudoDt;

    {
        _LexicalScope dtAliasLexScope;

        if (_ss.scanIdent(begin, end)) {
            potDtAliasName = "variant ";
            potDtAliasName.append(begin, end);

            if (dtAliasName) {
                dtAliasLexScope = _LexicalScope {*this, _StackFrame::Kind::DT_ALIAS};
                *dtAliasName = potDtAliasName;
            }
        }

        {
            _LexicalScope varTypeLexScope {*this, _StackFrame::Kind::VAR_TYPE};

            // try to parse `<`
            boost::optional<PseudoDataLoc> pseudoDataLoc;

            if (_ss.scanToken("<")) {
                pseudoDataLoc = this->_expectDataLoc();
                assert(pseudoDataLoc);

                if (pseudoDataLoc->isEnv()) {
                    throwMetadataParseError("Selector location of variant type "
                                            "cannot start with `env.`.",
                                            this->_curLoc());
                }

                this->_expectToken(">");
            }

            // parse `{`
            if (!_ss.scanToken("{")) {
                return nullptr;
            }

            // parse data type aliases and options
            PseudoNamedDts opts;

            while (true) {
                this->_skipCommentsAndWhitespacesAndSemicolons();

                if (_ss.scanToken("}")) {
                    break;
                }

                const auto loc = this->_curLoc();
                bool success;

                try {
                    success = this->_tryParseNamedDtOrDtAlias(opts);
                } catch (MetadataParseError& exc) {
                    appendMsgToMetadataParseError(exc, "While parsing body of `variant` block:",
                                                  loc);
                    throw;
                }

                if (!success) {
                    throwMetadataParseError("Expecting option or data type alias.",
                                            this->_curLoc());
                }
            }

            ssRej.accept();

            if (opts.empty()) {
                throwMetadataParseError("Variant type must contain at least one option.", beginLoc);
            }

            // check for duplicate option
            TsdlParser::_checkDupPseudoNamedDt(opts, beginLoc);

            pseudoDt = std::make_unique<PseudoVarType>(pseudoDataLoc, std::move(opts), beginLoc);
        }
    }

    if (addDtAlias && !potDtAliasName.empty()) {
        this->_addDtAlias(std::move(potDtAliasName), *pseudoDt);
    }

    return pseudoDt;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseEnvBlock()
{
    // parse `env`
    if (!_ss.scanToken("env")) {
        return false;
    }

    if (_traceEnv) {
        throwMetadataParseError("Duplicate `env` block.", this->_curLoc());
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    TraceEnvironment::Entries entries;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.kind != TsdlAttr::Kind::SINT && attr.kind != TsdlAttr::Kind::UINT
                && attr.kind != TsdlAttr::Kind::STR) {
            std::ostringstream ss;

            ss << "Environment entry `" << attr.name <<
                  "`: expecting constant integer or literal string.";
            throwMetadataParseError(ss.str(), attr.valTextLoc());
        }

        TraceEnvironment::Entry entry;

        if (attr.kind == TsdlAttr::Kind::SINT) {
            entry = attr.intVal;
        } else if (attr.kind == TsdlAttr::Kind::UINT) {
            if (attr.uintVal >= (1ULL << 63)) {
                std::ostringstream ss;

                ss << "Environment entry `" << attr.name <<
                      "`: value " << attr.uintVal << " is too large " <<
                      "(expecting a 64-bit signed integer).";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            entry = static_cast<long long>(attr.uintVal);
        } else if (attr.kind == TsdlAttr::Kind::STR) {
            entry = attr.strVal;
        }

        entries[attr.name] = entry;
    }

    _traceEnv = TraceEnvironment {entries};
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseCallsiteBlock()
{
    // parse `callsite`
    if (!_ss.scanToken("callsite")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;

    // pretty loose: we accept everything, even duplicates
    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseClkTypeBlock()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = this->_curLoc();

    // parse `clock`
    if (!_ss.scanToken("clock")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    if (!_pseudoTraceType) {
        return true;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    std::string name;
    boost::optional<std::string> descr;
    boost::optional<boost::uuids::uuid> uuid;
    auto freq = 1'000'000'000ULL;
    auto precision = 0ULL;
    auto offsetSecs = 0LL;
    Cycles offsetCycles = 0;
    auto originIsUnixEpoch = false;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "name") {
            if (attr.kind != TsdlAttr::Kind::IDENT && attr.kind != TsdlAttr::Kind::STR) {
                std::ostringstream ss;

                ss << "Attribute `name`: expecting identifier or literal string.";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            name = attr.strVal;
        } else if (attr.name == "description") {
            attr.checkKind(TsdlAttr::Kind::STR);
            descr = attr.strVal;
        } else if (attr.name == "uuid") {
            attr.checkKind(TsdlAttr::Kind::STR);

            const auto tmpUuid = TsdlParser::_uuidFromStr(attr.strVal);

            if (!tmpUuid) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            uuid = tmpUuid;
        } else if (attr.name == "freq") {
            attr.checkKind(TsdlAttr::Kind::UINT);

            if (attr.uintVal == 0) {
                std::ostringstream ss;

                ss << "Invalid `freq` attribute (must be greater than 0): " <<
                      attr.uintVal << ".";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            freq = static_cast<unsigned long long>(attr.uintVal);
        } else if (attr.name == "precision") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            precision = attr.uintVal;
        } else if (attr.name == "offset_s") {
            if (attr.kind != TsdlAttr::Kind::SINT && attr.kind != TsdlAttr::Kind::UINT) {
                throwMetadataParseError("Attribute `offset_s`: expecting constant signed integer.",
                                        attr.valTextLoc());
            }

            if (attr.kind == TsdlAttr::Kind::UINT) {
                using UT = decltype(attr.uintVal);

                if (attr.uintVal > static_cast<UT>(std::numeric_limits<long long>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `offset_s`: value is too large: " << attr.uintVal << ".";
                    throwMetadataParseError(ss.str(), attr.valTextLoc());
                }

                offsetSecs = static_cast<long long>(attr.uintVal);
            } else {
                offsetSecs = attr.intVal;
            }
        } else if (attr.name == "offset") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            offsetCycles = static_cast<Cycles>(attr.uintVal);
        } else if (attr.name == "absolute") {
            originIsUnixEpoch = attr.boolEquiv();
        } else {
            attr.throwUnknown();
        }
    }

    // make sure name is set
    if (name.empty()) {
        TsdlParser::_throwMissingAttr("name", beginLoc);
    }

    if (!_pseudoTraceType) {
        return true;
    }

    // make sure clock type doesn't exist
    const auto res = std::find_if(_pseudoTraceType->clkTypes().begin(),
                                  _pseudoTraceType->clkTypes().end(),
                                  [&name](const auto& clkType) {
        return clkType->name() == name;
    });

    if (res != _pseudoTraceType->clkTypes().end()) {
        std::ostringstream ss;

        ss << "Duplicate `clock` block named `" << name << "`.";
        throwMetadataParseError(ss.str(), beginLoc);
    }

    // adjust offset (make sure `offsetCycles` is less than `freq`)
    const auto completeSecsInOffsetCycles = offsetCycles / freq;

    offsetCycles -= completeSecsInOffsetCycles * freq;

    // TODO: throw if this would cause a `long long` overflow
    offsetSecs += completeSecsInOffsetCycles;

    auto clkType = std::make_unique<const ClockType>(freq, name, descr, uuid, precision,
                                                     ClockOffset {offsetSecs, offsetCycles},
                                                     originIsUnixEpoch);

    _pseudoTraceType->clkTypes().insert(std::move(clkType));
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseTraceTypeBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::TRACE_TYPE};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = this->_curLoc();

    // parse `trace`
    if (!_ss.scanToken("trace")) {
        return false;
    }

    if (_pseudoTraceType) {
        throwMetadataParseError("Duplicate `trace` block.", this->_curLoc());
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;
    PseudoDt::UP pseudoPktHeaderType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // try to parse packet header type
        auto pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::PKT_HEADER_TYPE, "packet",
                                               std::string {"header"});

        if (pseudoDt) {
            if (pseudoPktHeaderType) {
                throwMetadataParseError("Duplicate `packet.header` scope.", this->_curLoc());
            }

            pseudoPktHeaderType = std::move(pseudoDt);
            continue;
        }

        // try to parse data type alias
        if (this->_tryParseDtAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    boost::optional<unsigned int> majorVersion;
    boost::optional<unsigned int> minorVersion;
    boost::optional<ByteOrder> nativeBo;
    boost::optional<boost::uuids::uuid> uuid;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "major" || attr.name == "minor") {
            attr.checkKind(TsdlAttr::Kind::UINT);

            if (attr.name == "major") {
                if (attr.uintVal != 1) {
                    std::ostringstream ss;

                    ss << "Invalid `major` attribute: " <<
                          "unsupported major version (expecting 1): " <<
                          attr.uintVal << ".";
                    throwMetadataParseError(ss.str(), attr.valTextLoc());
                }

                majorVersion = attr.uintVal;
            } else if (attr.name == "minor") {
                if (attr.uintVal != 8) {
                    std::ostringstream ss;

                    ss << "Invalid `minor` attribute: " <<
                          "unsupported minor version (expecting 8): " <<
                          attr.uintVal << ".";
                    throwMetadataParseError(ss.str(), attr.valTextLoc());
                }

                minorVersion = attr.uintVal;
            }
        } else if (attr.name == "byte_order") {
            nativeBo = attr.bo();

            if (!nativeBo) {
                throwMetadataParseError("Invalid `byte_order` attribute: cannot be `native` here.",
                                        attr.valTextLoc());
            }
        } else if (attr.name == "uuid") {
            attr.checkKind(TsdlAttr::Kind::STR);

            if (attr.strVal.size() != 36) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            uuid = TsdlParser::_uuidFromStr(attr.strVal);

            if (!uuid) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }
        } else {
            attr.throwUnknown();
        }
    }

    /*
     * Make sure major/minor versions and native byte order properties
     * are set.
     */
    if (!majorVersion) {
        TsdlParser::_throwMissingAttr("major", beginLoc);
    }

    if (!minorVersion) {
        TsdlParser::_throwMissingAttr("minor", beginLoc);
    }

    if (!nativeBo) {
        TsdlParser::_throwMissingAttr("byte_order", beginLoc);
    }

    if (_nativeBo) {
        // second time we parse this: create pseudo trace type
        _pseudoTraceType = PseudoTraceType {
            *majorVersion, *minorVersion, *nativeBo,
            std::move(uuid), std::move(pseudoPktHeaderType)
        };
    } else {
        /*
         * Alright, we have the REAL native byte order now, so restart
         * the whooooole process. Luckily the `trace` block is early in
         * the input string, so we didn't waste too many precious
         * cycles. In practice (LTTng, barectf, CTF writer of
         * Babeltrace) this is always the case.
         */
        assert(nativeBo);
        _nativeBo = *nativeBo;
        _fastPseudoFlIntTypes.clear();
        assert(_stack.size() == 2);
        _stack[0].dtAliases.clear();
        _ss.reset();
    }

    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseDstBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::DST};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = this->_curLoc();

    // parse `stream`
    if (!_ss.scanToken("stream")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;
    PseudoDt::UP pseudoPktCtxType;
    PseudoDt::UP pseudoErHeaderType;
    PseudoDt::UP pseudoErCommonCtxType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // try to parse packet context type
        auto pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::PKT_CTX_TYPE, "packet",
                                               std::string {"context"});

        if (pseudoDt) {
            if (pseudoPktCtxType) {
                throwMetadataParseError("Duplicate `packet.context` scope.", this->_curLoc());
            }

            pseudoPktCtxType = std::move(pseudoDt);
            continue;
        }

        // try to parse event record header type
        pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_HEADER_TYPE, "event",
                                          std::string {"header"}, false);

        if (pseudoDt) {
            if (pseudoErHeaderType) {
                throwMetadataParseError("Duplicate `event.header` scope.", this->_curLoc());
            }

            pseudoErHeaderType = std::move(pseudoDt);
            continue;
        }

        // try to parse event record common context type
        pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_COMMON_CTX_TYPE, "event",
                                          std::string {"context"}, false);

        if (pseudoDt) {
            if (pseudoErCommonCtxType) {
                throwMetadataParseError("Duplicate `event.context` scope.", this->_curLoc());
            }

            pseudoErCommonCtxType = std::move(pseudoDt);
            continue;
        }

        // try to parse data type alias
        if (this->_tryParseDtAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    if (!_pseudoTraceType) {
        return true;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    // default data stream type ID is 0
    TypeId id = 0;

    // check for attributes
    for (const auto& attr : attrs) {
        if (attr.name == "id") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            id = attr.uintVal;
        } else {
            attr.throwUnknown();
        }
    }

    // make sure no data stream type exists with this ID
    if (this->_pseudoDstExists(id)) {
        std::ostringstream ss;

        ss << "Duplicate `stream` block with ID " << id << ".";
        throwMetadataParseError(ss.str(), beginLoc);
    }

    // create and initialize pseudo data stream type
    auto pseudoDst = std::make_unique<PseudoDst>(id, std::move(pseudoPktCtxType),
                                                 std::move(pseudoErHeaderType),
                                                 std::move(pseudoErCommonCtxType));
    _pseudoTraceType->pseudoDsts().insert(std::make_pair(id, std::move(pseudoDst)));
    _pseudoTraceType->pseudoOrphanErts()[id];

    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseErtBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::ERT};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = this->_curLoc();

    // parse `event`
    if (!_ss.scanToken("event")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;
    PseudoDt::UP pseudoSpecCtxType;
    PseudoDt::UP pseudoPayloadType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // try to parse specific context type
        auto pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_SPEC_CTX_TYPE, "context");

        if (pseudoDt) {
            if (pseudoSpecCtxType) {
                throwMetadataParseError("Duplicate `event.context` scope.", this->_curLoc());
            }

            pseudoSpecCtxType = std::move(pseudoDt);
            continue;
        }

        // try to parse payload type
        pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_PAYLOAD_TYPE, "fields");

        if (pseudoDt) {
            if (pseudoPayloadType) {
                throwMetadataParseError("Duplicate `event.fields` scope.", this->_curLoc());
            }

            pseudoPayloadType = std::move(pseudoDt);
            continue;
        }

        // try to parse data type alias
        if (this->_tryParseDtAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    if (!_pseudoTraceType) {
        return true;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    // default event and stream IDs are 0
    TypeId id = 0;
    TypeId dstId = 0;
    boost::optional<LogLevel> logLevel;
    boost::optional<std::string> emfUri;
    boost::optional<std::string> name;

    // check for attributes
    for (const auto& attr : attrs) {
        if (attr.name == "id") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            id = attr.uintVal;
        } else if (attr.name == "stream_id") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            dstId = attr.uintVal;
        } else if (attr.name == "loglevel") {
            if (attr.kind != TsdlAttr::Kind::SINT && attr.kind != TsdlAttr::Kind::UINT) {
                throwMetadataParseError("Attribute `loglevel`: expecting constant signed integer.",
                                        attr.valTextLoc());
            }

            if (attr.kind == TsdlAttr::Kind::UINT) {
                using UT = decltype(attr.uintVal);

                if (attr.uintVal > static_cast<UT>(std::numeric_limits<LogLevel>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `loglevel`: value is too large: " << attr.uintVal << ".";
                    throwMetadataParseError(ss.str(), attr.valTextLoc());
                }

                logLevel = static_cast<LogLevel>(attr.uintVal);
            } else {
                logLevel = static_cast<LogLevel>(attr.intVal);
            }
        } else if (attr.name == "model.emf.uri") {
            attr.checkKind(TsdlAttr::Kind::STR);
            emfUri = attr.strVal;
        } else if (attr.name == "name") {
            if (attr.kind != TsdlAttr::Kind::IDENT && attr.kind != TsdlAttr::Kind::STR) {
                std::ostringstream ss;

                ss << "Attribute `name`: expecting identifier or literal string.";
                throwMetadataParseError(ss.str(), attr.valTextLoc());
            }

            name = attr.strVal;
        } else {
            attr.throwUnknown();
        }
    }

    // get or create pseudo data stream type for orphan
    auto& dstPseudoOrphanErts = _pseudoTraceType->pseudoOrphanErts()[dstId];

    // check if the pseudo event record type exists
    if (dstPseudoOrphanErts.find(id) != dstPseudoOrphanErts.end()) {
        std::ostringstream ss;

        ss << "Duplicate `event` block with ID " << id <<
              " and data stream type ID " << dstId << ".";
        throwMetadataParseError(ss.str(), beginLoc);
    }

    // build event record type object
    dstPseudoOrphanErts.insert(std::make_pair(id, PseudoOrphanErt {
        PseudoErt {
            id, std::move(name), std::move(logLevel), std::move(emfUri),
            std::move(pseudoSpecCtxType), std::move(pseudoPayloadType)
        },
        beginLoc
    }));

    return true;
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseScopeDt(const _StackFrame::Kind scopeDtStackFrameKind,
                                                  const std::string& firstName,
                                                  const boost::optional<std::string>& secondName,
                                                  const bool expect)
{
    _StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();

    // parse name
    if (!_ss.scanToken(firstName)) {
        return nullptr;
    }

    try {
        if (secondName) {
            this->_expectToken(".");

            if (!_ss.scanToken(*secondName)) {
                if (expect) {
                    std::ostringstream ss;

                    ss << "Expecting `" << *secondName << "`.";
                    throwMetadataParseError(ss.str(), this->_curLoc());
                }

                return nullptr;
            }
        }

        // parse `:=`
        this->_expectToken(":=");
        _ss.skipCommentsAndWhitespaces();

        const auto dtLoc = this->_curLoc();

        // parse data type
        PseudoDt::UP pseudoDt;

        {
            _LexicalScope lexScope {*this, scopeDtStackFrameKind};

            pseudoDt = this->_tryParseDt();
        }

        if (!pseudoDt) {
            throwMetadataParseError("Expecting data type or data type alias name.", dtLoc);
        }

        if (pseudoDt->kind() != PseudoDt::Kind::STRUCT) {
            throwMetadataParseError("Expecting a structure type.", dtLoc);
        }

        // parse `;`
        this->_expectToken(";");
        ssRej.accept();
        return pseudoDt;
    } catch (MetadataParseError& exc) {
        std::string line;

        line = "In the `";
        line += firstName;

        if (secondName) {
            line += ".";
            line += *secondName;
        }

        line += "` scope:";
        appendMsgToMetadataParseError(exc, line, beginLoc);
        throw;
    }
}

template <typename CharIt>
TsdlAttr TsdlParser<CharIt>::_expectAttr()
{
    TsdlAttr attr;

    // parse name
    CharIt begin, end;
    auto nameIsFound = false;

    _ss.skipCommentsAndWhitespaces();
    attr.nameLoc = this->_curLoc();

    if (_ss.scanToken(TsdlParser::_EMF_URI_ATTR_NAME)) {
        nameIsFound = true;
        attr.name = TsdlParser::_EMF_URI_ATTR_NAME;
    } else if (_ss.scanIdent(begin, end)) {
        nameIsFound = true;
        attr.name.assign(begin, end);
    }

    if (!nameIsFound) {
        throwMetadataParseError("Expecting attribute name.", *attr.nameLoc);
    }

    // parse `=`
    this->_expectToken("=");

    // this it the source location of the attribute for an eventual error
    _ss.skipCommentsAndWhitespaces();
    attr.valLoc = this->_curLoc();

    // special case for the `map` attribute
    if (attr.name == "map") {
        attr.kind = TsdlAttr::Kind::CLK_NAME_VALUE;

        // parse `clock`
        this->_expectToken("clock");

        // parse `.`
        this->_expectToken(".");

        // parse name of clock type
        if (!_ss.scanIdent(begin, end)) {
            throwMetadataParseError("Expecting identifier (clock type name).", this->_curLoc());
        }

        attr.strVal.assign(begin, end);

        // parse `.`
        this->_expectToken(".");

        // parse `value`
        this->_expectToken("value");

        // parse `;`
        this->_expectToken(";");
        return attr;
    }

    if (_ss.scanLitStr(begin, end)) {
        // literal string
        const auto escapedStr = TsdlParser::_escapeLiteralStr(begin, end, attr.valTextLoc());

        attr.strVal = escapedStr;
        attr.kind = TsdlAttr::Kind::STR;
    } else if (_ss.scanIdent(begin, end)) {
        // identifier
        attr.strVal.assign(begin, end);
        attr.kind = TsdlAttr::Kind::IDENT;
    } else if (_ss.scanConstInt(attr.uintVal)) {
        // constant unsigned integer
        attr.kind = TsdlAttr::Kind::UINT;
    } else if (_ss.scanConstInt(attr.intVal)) {
        // constant signed integer
        attr.kind = TsdlAttr::Kind::SINT;
        assert(attr.intVal != 0 && attr.intVal != 1);
    } else {
        throwMetadataParseError("Expecting valid constant integer, literal string, or identifier.",
                                *attr.valLoc);
    }

    // parse `;`
    this->_expectToken(";");
    return attr;
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseDtAliasRef()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();
    CharIt begin, end;

    // try `enum`/`struct` followed by name
    {
        _StrScannerRejecter ssRej {_ss};

        if (_ss.scanIdent(begin, end)) {
            const std::string kw {begin, end};

            if (kw == "enum" || kw == "struct") {
                if (_ss.scanIdent(begin, end)) {
                    if (!_ss.scanToken("{") && !_ss.scanToken(":")) {
                        std::string dtAliasName = kw + ' ';

                        dtAliasName.append(begin, end);

                        // get from data type alias
                        auto pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc);

                        if (pseudoDt) {
                            ssRej.accept();
                            return pseudoDt;
                        }
                    }
                }
            }
        }
    }

    // try `variant` followed by name, followed by optional selector name
    {
        _StrScannerRejecter ssRej {_ss};

        if (_ss.scanToken("variant")) {
            if (_ss.scanIdent(begin, end)) {
                std::string dtAliasName {"variant "};

                dtAliasName.append(begin, end);

                // get from data type alias
                auto pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc);

                if (!pseudoDt) {
                    return nullptr;
                }

                auto& pseudoVarType = static_cast<PseudoVarType&>(*pseudoDt);

                if (pseudoVarType.pseudoSelLoc()) {
                    ssRej.accept();
                    return pseudoDt;
                }

                if (_ss.scanToken("<")) {
                    _ss.skipCommentsAndWhitespaces();

                    const auto selLoc = this->_curLoc();
                    auto pseudoSelLoc = this->_expectDataLoc();

                    if (pseudoSelLoc.isEnv()) {
                        throwMetadataParseError("Selector location of variant type cannot start with `env.`.",
                                                selLoc);
                    }

                    this->_expectToken(">");

                    if (!_ss.scanToken("{")) {
                        /*
                         * Create new pseudo variant type with this selector
                         * location.
                         */
                        auto pseudoDtClone = pseudoDt->clone();
                        auto& pseudoVarType = static_cast<PseudoVarType&>(*pseudoDtClone);

                        pseudoVarType.pseudoSelLoc(std::move(pseudoSelLoc));
                        ssRej.accept();
                        return pseudoDtClone;
                    }
                }
            }
        }
    }

    // try data type alias name
    {
        _StrScannerRejecter ssRej {_ss};
        std::string dtAliasName;

        if (this->_parseDtAliasName(dtAliasName, false)) {
            auto pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc);

            if (pseudoDt) {
                ssRej.accept();
                return pseudoDt;
            }
        }
    }

    return nullptr;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_parseDtAliasName(std::string& dtAliasName, const bool expect)
{
    bool isMulti = false;
    std::vector<std::string> parts;

    while (true) {
        _StrScannerRejecter ssRej {_ss};
        CharIt begin, end;

        _ss.skipCommentsAndWhitespaces();

        const auto loc = this->_curLoc();

        if (!_ss.scanIdent(begin, end)) {
            ssRej.accept();
            break;
        }

        std::string part {begin, end};

        // disallow reserved words
        if (part == "integer" || part == "floating_point" || part == "enum" || part == "string" ||
                part == "struct" || part == "variant" || part == "trace" || part == "stream" ||
                part == "clock" || part == "event" || part == "env") {
            if (expect) {
                std::ostringstream ss;

                ss << "Invalid keyword `" << part << "` in type alias name.";
                throwMetadataParseError(ss.str(), loc);
            } else {
                return false;
            }
        }

        if (part == "const" || part == "char" || part == "double" || part == "float" ||
                part == "int" || part == "long" || part == "short" || part == "signed" ||
                part == "unsigned" || part == "void" || part == "_Bool" || part == "_Complex" ||
                part == "_Imaginary") {
            isMulti = true;
        } else {
            if (isMulti) {
                // this must be the end of the data type alias name
                break;
            }
        }

        ssRej.accept();
        parts.push_back(part);

        if (!isMulti) {
            // single word data type alias name: break now
            break;
        }
    }

    if (parts.empty()) {
        if (expect) {
            throwMetadataParseError("Expecting data type alias name.", this->_curLoc());
        } else {
            return false;
        }
    }

    dtAliasName.clear();

    for (auto it = parts.begin(); it != parts.end(); ++it) {
        dtAliasName += *it;

        if (std::distance(it, parts.end()) > 1) {
            dtAliasName += ' ';
        }
    }

    return true;
}

template <typename CharIt>
PseudoDataLoc TsdlParser<CharIt>::_expectDataLoc()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = this->_curLoc();
    DataLocation::PathElements allPathElems;

    while (true) {
        CharIt begin, end;

        if (!_ss.scanIdent(begin, end)) {
            break;
        }

        allPathElems.push_back({begin, end});

        if (!_ss.scanToken(".")) {
            break;
        }
    }

    if (allPathElems.empty()) {
        throwMetadataParseError("Empty data location.", beginLoc);
    }

    return this->_pseudoDataLocFromAllPathElems(allPathElems, beginLoc);
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_tryParseIdentArraySubscripts(std::string& ident,
                                                               PseudoDt::UP innerPseudoDt)
{
    // parse identifier
    CharIt begin, end;

    if (!_ss.scanIdent(begin, end)) {
        return nullptr;
    }

    ident.assign(begin, end);
    return this->_parseArraySubscripts(std::move(innerPseudoDt));
}

template <typename CharIt>
PseudoDt::UP TsdlParser<CharIt>::_parseArraySubscripts(PseudoDt::UP innerPseudoDt)
{
    /*
     * A temporary array type subscript.
     *
     * If `isStatic` is true, then use `arrayLen` to build a
     * static-length array type. Otherwise use `dlArrayLenLoc`.
     *
     * TODO: Use `boost::variant`.
     */
    struct LenDescr final
    {
        bool isStatic;
        boost::optional<PseudoDataLoc> dlArrayLenLoc;
        Size arrayLen;
        TextLocation loc;
    };

    std::vector<LenDescr> lenDescrs;

    while (true) {
        if (!_ss.scanToken("[")) {
            break;
        }

        _ss.skipCommentsAndWhitespaces();

        const auto subscriptLoc = this->_curLoc();
        long long value;

        if (_ss.scanConstInt(value)) {
            if (value < 0) {
                std::ostringstream ss;

                ss << "Length of array type cannot be negative: " << value << ".";
                throwMetadataParseError(ss.str(), subscriptLoc);
            }

            lenDescrs.push_back({true, boost::none, static_cast<Size>(value), subscriptLoc});
        } else {
            boost::optional<PseudoDataLoc> pseudoDataLoc;

            try {
                pseudoDataLoc = this->_expectDataLoc();
            } catch (MetadataParseError& exc) {
                appendMsgToMetadataParseError(exc,
                                              "Expecting valid constant integer (static-length array type) or valid data location (dynamic-length array type):",
                                              subscriptLoc);
                throw;
            }

            assert(pseudoDataLoc);

            if (pseudoDataLoc->isEnv()) {
                // only the `env.KEY` format is accepted
                if (pseudoDataLoc->pathElems().size() != 1) {
                    throwMetadataParseError("Invalid environment location: expecting `env.KEY`, "
                                            "where KEY is the key of an existing environment entry.",
                                            subscriptLoc);
                }

                const auto& envKey = pseudoDataLoc->pathElems()[0];

                // find the value in the current environment
                if (!_traceEnv) {
                    std::ostringstream ss;

                    ss << "Static-length array type refers to the environment entry `" <<
                          envKey << "`, but no environment exists at this point.";
                    throwMetadataParseError(ss.str(), subscriptLoc);
                }

                const auto entry = (*_traceEnv)[envKey];

                if (!entry) {
                    std::ostringstream ss;

                    ss << "Cannot find environment entry `" << envKey << "`.";
                    throwMetadataParseError(ss.str(), subscriptLoc);
                }

                if (const auto entryVal = boost::get<long long>(entry)) {
                    if (*entryVal < 0) {
                        std::ostringstream ss;

                        ss << "Static-length array type cannot have a negative size: " << *entryVal << ".";
                        throwMetadataParseError(ss.str(), subscriptLoc);
                    }

                    lenDescrs.push_back({true, boost::none, static_cast<Size>(*entryVal),
                                        subscriptLoc});
                } else {
                    std::ostringstream ss;

                    ss << "Environment entry `" << envKey <<
                          "` isn't a valid static-length array type size.";
                    throwMetadataParseError(ss.str(), subscriptLoc);
                }
            } else {
                lenDescrs.push_back({false, *pseudoDataLoc, 0, subscriptLoc});
            }
        }

        this->_expectToken("]");
    }

    /*
     * We reverse the order here, so that, for example:
     *
     *     string s[2][len][4];
     *
     * becomes the class of a static-length array of two dynamic-length
     * arrays of `len` static-length arrays of four null-terminated
     * strings.
     *
     * At this point, `innerPseudoDt` is the null-terminated string type
     * in the example above.
     */
    for (const auto& lenDescr : boost::adaptors::reverse(lenDescrs)) {
        if (lenDescr.isStatic) {
            innerPseudoDt = std::make_unique<PseudoSlArrayType>(lenDescr.arrayLen,
                                                                std::move(innerPseudoDt),
                                                                lenDescr.loc);
        } else {
            assert(lenDescr.dlArrayLenLoc);
            innerPseudoDt = std::make_unique<PseudoDlArrayType>(*lenDescr.dlArrayLenLoc,
                                                                std::move(innerPseudoDt),
                                                                lenDescr.loc);
        }
    }

    return innerPseudoDt;
}

template <typename CharIt>
template <typename FlEnumTypeT, typename CreatePseudoDtFuncT>
PseudoDt::UP TsdlParser<CharIt>::_finishParseFlEnumType(PseudoDt::UP pseudoDt,
                                                        const bool addDtAlias,
                                                        std::string&& potDtAliasName,
                                                        CreatePseudoDtFuncT&& createPseudoDtFunc)
{
    // parse mappings (we're after `{`)
    std::unordered_map<std::string, std::set<typename FlEnumTypeT::RangeSet::Range>> pseudoMappings;
    typename FlEnumTypeT::RangeSet::Value curVal = 0;

    while (true) {
        CharIt begin, end;
        std::string name;

        _ss.skipCommentsAndWhitespaces();

        boost::optional<TextLocation> loc {this->_curLoc()};

        if (_ss.scanIdent(begin, end)) {
            name.assign(begin, end);
        } else if (_ss.scanLitStr(begin, end)) {
            name = TsdlParser::_escapeLiteralStr(begin, end, *loc);
        } else {
            throwMetadataParseError("Expecting mapping name (identifier or literal string).", *loc);
        }

        auto lower = curVal;
        auto upper = curVal;

        if (_ss.scanToken("=")) {
            _ss.skipCommentsAndWhitespaces();
            loc = this->_curLoc();

            decltype(curVal) value;

            if (!_ss.scanConstInt(value)) {
                if (std::is_signed<decltype(value)>::value) {
                    throwMetadataParseError("Expecting valid constant signed integer.",
                                            this->_curLoc());
                } else {
                    throwMetadataParseError("Expecting valid constant unsigned integer.",
                                            this->_curLoc());
                }
            }

            lower = value;
            upper = lower;
            curVal = lower;

            if (_ss.scanToken("...")) {
                if (!_ss.scanConstInt(value)) {
                    throwMetadataParseError("Expecting valid constant integer.", this->_curLoc());
                }

                upper = value;
                curVal = upper;
            }
        }

        ++curVal;

        /*
         * Insert integer range into pseudo mapping (create pseudo
         * mapping if it doesn't exist).
         */
        if (pseudoMappings.find(name) == pseudoMappings.end()) {
            pseudoMappings[name] = {};
        }

        if (lower > upper) {
            std::ostringstream ss;

            ss << "Lower value of range (" << lower << ") is greater than upper value (" <<
                  upper << ").";
            throwMetadataParseError(ss.str(), *loc);
        }

        pseudoMappings[name].insert(typename FlEnumTypeT::RangeSet::Range {lower, upper});

        const bool gotComma = _ss.scanToken(",");

        // end of member types?
        if (_ss.scanToken("}")) {
            break;
        }

        if (!gotComma) {
            throwMetadataParseError("Expecting `,` or `}`.", this->_curLoc());
        }
    }

    if (pseudoMappings.empty()) {
        throwMetadataParseError("Expecting at least one mapping.", pseudoDt->loc());
    }

    typename FlEnumTypeT::Mappings mappings;

    for (const auto& nameRangesPair : pseudoMappings) {
        mappings[nameRangesPair.first] = typename FlEnumTypeT::RangeSet {
            std::move(nameRangesPair.second)
        };
    }

    // validate mappings
    Size len;

    if (pseudoDt->kind() == PseudoDt::Kind::SCALAR_DT_WRAPPER) {
        const auto& pseudoDtWrapper = static_cast<const PseudoScalarDtWrapper&>(*pseudoDt);

        assert(pseudoDtWrapper.dt().isFixedLengthSignedIntegerType());
        len = pseudoDtWrapper.dt().asFixedLengthIntegerType().length();
    } else {
        assert(pseudoDt->kind() == PseudoDt::Kind::FL_UINT);

        const auto& pseudoUIntType = static_cast<const PseudoFlUIntType&>(*pseudoDt);

        len = pseudoUIntType.len();
    }

    this->_validateFlEnumTypeMappings<FlEnumTypeT>(len, pseudoDt->loc(), mappings);

    // create pseudo fixed-length enumeration type
    auto pseudoEnumType = std::forward<CreatePseudoDtFuncT>(createPseudoDtFunc)(*pseudoDt,
                                                                                mappings);

    // add data type alias if this fixed-length enumeration type has a name
    if (addDtAlias && !potDtAliasName.empty()) {
        this->_addDtAlias(std::move(potDtAliasName), *pseudoEnumType);
    }

    return pseudoEnumType;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseNamedDtOrDtAlias(PseudoNamedDts& pseudoNamedDts)
{
    /*
     * Here are the possible cases:
     *
     * 1. Explicit data type alias:
     *
     *        typealias integer {
     *            size = 23;
     *            align = 8;
     *        } := hello;
     *
     * 2. Fixed-length enumeration data type alias:
     *
     *        enum my_enum : some_int {
     *            ...
     *        };
     *
     * 3. Structure data type alias:
     *
     *        struct something {
     *            ...
     *        } align(16);
     *
     * 4. Variant data type alias:
     *
     *        variant my_var {
     *            ...
     *        };
     *
     *        variant <event.fields.my.tag> my_var {
     *            ...
     *        };
     *
     * 5. Identifier using a fixed-length enumeration type alias:
     *
     *        enum state my_state;
     *        enum state my_state[2];
     *
     * 6. Identifier using a structure type alias:
     *
     *        struct payload my_payload;
     *        struct payload my_payload[stuff.length];
     *
     * 7. Identifier using a variant type alias with an explicit
     *    selector location:
     *
     *        variant my_var <my.tag> my_variant;
     *        variant my_var <my.tag> my_variant[2][lol];
     *
     * 8. Identifier using full data type:
     *
     *        integer {
     *            size = 23;
     *            align = 16;
     *        } my_field[17];
     *
     * 9. Identifier using explicit data type alias:
     *
     *        my_type my_field;
     *        my_type my_field[9];
     *
     * We want to try cases 5, 6, 7, and 9 first because otherwise it
     * can be ambiguous when parsing a variant type:
     *
     * a) variant var_name <tag> field_name;
     * b) variant var_name <tag> { ... };
     * c) variant var_name { ... };
     * d) variant var_name <tag> { ... } field_name;
     * e) variant <tag> { ... } field_name;
     *
     * Here, b), c), and d) are invalid because we're creating a data
     * type alias (named variant) and using a relative selector location
     * at the same time (not supported). a) has a relative selector
     * location, but we're using an aliased variant type named
     * `var_name` which should already exist at this point: this is why
     * we try it first.
     */

    // try cases 5, 6, 7, and 9 first
    this->_skipCommentsAndWhitespacesAndSemicolons();

    {
        _StrScannerRejecter ssRej {_ss};
        const auto dtLoc = this->_curLoc();
        auto pseudoDt = this->_tryParseDtAliasRef();

        if (pseudoDt) {
            // let's try parsing an identifier + array subscripts
            std::string ident;
            auto effectivePseudoDt = this->_tryParseIdentArraySubscripts(ident, std::move(pseudoDt));

            if (effectivePseudoDt) {
                /*
                 * We have a winner: variant type must have a selector
                 * location at this point.
                 */
                if (TsdlParser::_isPseudoVarTypeWithoutSelLocRec(*effectivePseudoDt)) {
                    throwMetadataParseError("Variant type needs a selector location here.", dtLoc);
                }

                auto pseudoNamedDt = std::make_unique<PseudoNamedDt>(ident,
                                                                     std::move(effectivePseudoDt));

                pseudoNamedDts.push_back(std::move(pseudoNamedDt));
                this->_expectToken(";");
                ssRej.accept();
                this->_stackTop().idents.push_back(ident);
                return true;
            }
        }
    }

    // try type alias (cases 1, 2, 3, 4)
    {
        _StrScannerRejecter ssRej {_ss};

        if (this->_tryParseDtAlias()) {
            ssRej.accept();
            return true;
        }
    }

    // try full type (cases 8)
    {
        _StrScannerRejecter ssRej {_ss};
        auto pseudoDt = this->_tryParseFullDt();

        if (pseudoDt) {
            // let's try parsing an identifier + array subscripts
            std::string ident;
            auto effectivePseudoDt = this->_tryParseIdentArraySubscripts(ident, std::move(pseudoDt));

            if (effectivePseudoDt) {
                /*
                 * We have a winner: variant type must have a selector
                 * location at this point.
                 */
                if (TsdlParser::_isPseudoVarTypeWithoutSelLocRec(*effectivePseudoDt)) {
                    throwMetadataParseError("Variant type needs a selector here.", this->_curLoc());
                }

                auto pseudoNamedDt = std::make_unique<PseudoNamedDt>(ident,
                                                                     std::move(effectivePseudoDt));

                pseudoNamedDts.push_back(std::move(pseudoNamedDt));
                this->_expectToken(";");
                ssRej.accept();
                this->_stackTop().idents.push_back(ident);
                return true;
            } else {
                /*
                 * If there's a type, but no identifier, and we know that
                 * it's not a data type alias, then we expect an identifier
                 * at this point.
                 */
                _ss.skipCommentsAndWhitespaces();
                throwMetadataParseError("Expecting identifier (member type/option name).",
                                        this->_curLoc());
            }
        }
    }

    return false;
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_TSDL_PARSER_HPP
