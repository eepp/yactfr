/*
 * A non-predictive recursive descent CTF 1.8 TSDL parser.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
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
#include <unordered_map>
#include <boost/utility.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/string-type.hpp>
#include <yactfr/metadata/array-type.hpp>
#include <yactfr/metadata/text-array-type.hpp>
#include <yactfr/metadata/sequence-type.hpp>
#include <yactfr/metadata/text-sequence-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/struct-type-field.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/metadata/variant-type-choice.hpp>
#include <yactfr/metadata/field-ref.hpp>
#include <yactfr/metadata/exceptions.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/internal/utils.hpp>

#include "tsdl-parser-base.hpp"
#include "string-scanner.hpp"

namespace yactfr {

template <typename ParserCharIt>
TraceType::SP traceTypeFromMetadataText(ParserCharIt, ParserCharIt,
                                        const boost::optional<boost::uuids::uuid>&);

namespace internal {

/*
 * CTF metadata parser.
 *
 * This parser parses a CTF (TSDL) metadata string and then contains an
 * equivalent shared trace type object.
 *
 * Parsing methods which return `bool` can backtrack: if they return
 * `false`, then the parser's state is as it was when calling them.
 */
template <typename CharIt>
class TsdlParser :
    public TsdlParserBase
{
    template <typename ParserCharIt>
    friend TraceType::SP yactfr::traceTypeFromMetadataText(ParserCharIt, ParserCharIt,
                                                           const boost::optional<boost::uuids::uuid>&);

private:
    /*
     * Builds a metadata parser, wrapping a string between `begin`
     * (included) and `end` (excluded), expecting a specific metadata
     * UUID, `expectedUuid`, and parses it.
     *
     * The result of the parsing process can be obtained with
     * traceType().
     *
     * Throws MetadataParseError when there was a parsing error.
     */
    explicit TsdlParser(CharIt begin, CharIt end,
                        const boost::optional<boost::uuids::uuid>& expectedUuid);

    /*
     * A fast integer type entry. Often integer types, which are usually
     * the most used data types, are written exactly the same in the
     * metadata string. For example, LTTng-modules 2.7 emits a whole
     * bunch of this exact string:
     *
     *     integer { size = 32; align = 8; signed = 1; encoding = none; base = 10; }
     *
     * To avoid parsing this substring as 5 attributes each time, we
     * keep it in a cache after the first time it is parsed. This cache
     * associates a substring, from `begin` to `end`, to the parsed data
     * type. If it is found using _getFastIntType(), then you can clone
     * the cached data type to have your own copy. The maximum size from
     * `begin` to `end` is given by `_MAX_FAST_INT_FT_STRING_SIZE`.
     *
     * Is it really worth it? I don't know! Is it a cool idea even
     * without benchmarks? I think so.
     */
    struct _FastIntTypeEntry {
        CharIt begin;
        CharIt end;
        DataType::UP type;
    };

private:
    /*
     * Parses the whole metadata string, creating the resulting trace
     * type on success.
     */
    void _parseMetadata();

    /*
     * Tries to parse one individual root block with a terminating `;`.
     * Root blocks can be explicit type aliases (including type
     * definitions), named enumerations/structures/variants, `trace`,
     * `env`, `clock`, `stream`, `event`, and `callsite` blocks. Returns
     * whether or not a root block was parsed.
     */
    bool _tryParseRootBlock();

    /*
     * Tries to parse a type alias given by a named
     * enumeration/structure/variant type, terminating with `;`, adding
     * it to the current frame's map of aliased types on success.
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
    bool _tryParseEnumStructVariantTypeAlias();

    /*
     * Tries to parse a `typealias` or `typedef` block, adding it to the
     * current frame's map of aliased types on success. Returns whether
     * or not a generic type alias block was parsed.
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
    bool _tryParseGenericTypeAlias();

    /*
     * Tries to parses any type alias, generic (`typealias`, `typedef`
     * keywords) or named enumeration/structure/variant type, adding it
     * to the current frame's map of aliased types on success. Returns
     * whether or not a type alias was parsed.
     */
    bool _tryParseTypeAlias();

    /*
     * Expects a generic attribute, with a terminating `;`. `attr` is
     * the returned attribute. Returns the parsed attribute.
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
    _Attribute _expectAttribute();

    /*
     * Tries to parse a scope definition with a terminating `;` and
     * returns the type. `scopeDefStackFrameKind` is the kind of stack
     * frame to push for this scope definition. `firstName` and optional
     * `secondName` are the one or two words naming the scope, e.g.,
     * `event` and `header`, or just `context`. If `expect` is true,
     * then the method throws if it cannot parse the scope definition
     * successfully. Otherwise, the method can return `nullptr` if it
     * cannot parse the scope definition.
     *
     * Examples:
     *
     *     packet.context := struct { ... };
     *
     *     fields := event_fields;
     *
     *     event.header := struct my_event_header;
     */
    PseudoDataType::UP _tryParseScopeDef(const _StackFrame::Kind scopeDefStackFrameKind,
                                         const char *firstName,
                                         const char *secondName = nullptr,
                                         bool expect = true);

    /*
     * Tries to parse a field name followed by zero or more
     * array/sequence lengths. `fieldName` is set to the parsed field
     * name. `innerType` is the most nested pseudo data type to wrap. It
     * is returned as is if there's only a field name not followed by an
     * opening square bracket.
     *
     * Examples:
     *
     *     my_field
     *
     *     my_field[1]
     *
     *     my_field[event.context.some.location][23][len]
     */
    PseudoDataType::UP _tryParseFieldNameArraysSequences(std::string& fieldName,
                                                         PseudoDataType::UP innerType);

    /*
     * Like _tryParseFieldNameArraysSequences(), but without the field
     * name part.
     *
     * Examples:
     *
     *     [1]
     *
     *     [length]
     *
     *     [event.context.some.location][23][len];
     */
    PseudoDataType::UP _parseArraySeqLengths(PseudoDataType::UP innerType);

    /*
     * Parses a type alias name, without parsing a field name that would
     * follow. On success, `aliasName` contains the name of the alias.
     * If `expect` is true, then the method throws if it fails to parse
     * a type alias name. Otherwise, returns whether or not a type alias
     * name was parsed.
     *
     * Examples:
     *
     *     my_alias
     *
     *     const unsigned int
     *
     *     signed long long
     */
    bool _parseTypeAliasName(std::string& aliasName, bool expect);

    /*
     * Parses a field reference. Fills `pseudoFieldRef` with the parsed
     * pseudo field reference on success, and returns true. If `expect`
     * is true, throws if it cannot parse a field reference
     * successfully.
     *
     * Examples:
     *
     *     trace.packet.header.some_size
     *
     *     my.len
     *
     *     env.some_key
     */
    bool _parseFieldRef(PseudoFieldRef& pseudoFieldRef, bool expect);

    /*
     * Parses a reference to a type alias, that is:
     *
     * * `enum NAME` not followed by `:` or `{`
     * * `struct NAME` not followed by `{`
     * * `variant NAME` or `variant NAME <ABS-TAG>` not followed by `{`
     * * `some_alias_name` (keywords are excluded)
     *
     * This method returns the aliased type, or `nullptr` if it cannot
     * find it.
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
     * Not supported (named variant with relative tag field reference):
     *
     *     variant my_variant <my.tag>;
     */
    PseudoDataType::UP _tryParseGetTypeAliasRef();

    /*
     * Expects a specific token, throwing an exception if not found.
     */
    void _expectToken(const char *token);

    /*
     * Tries to parse a field/choice or a type alias, with a terminating
     * `;`, adding the field to `entries` if found, and adding any
     * parsed type alias to the current frame's map of aliased types on
     * success.
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
    bool _tryParseNamedDataTypeOrTypeAlias(PseudoNamedDataTypes& entries);

    /*
     * Tries to parse a type, which also includes a type alias
     * reference. Returns whether or not a type was successfully parsed.
     */
    PseudoDataType::UP _tryParseType();

    /*
     * Tries to parse a type block (excludes type alias references).
     * Returns whether or not a full type was successfully parsed.
     */
    PseudoDataType::UP _tryParseFullType();

    /*
     * Tries to parse an integer type block. Returns whether or not an
     * integer type was successfully parsed.
     */
    PseudoDataType::UP _tryParseIntType();

    /*
     * Tries to parse a floating point number type block. Returns
     * whether or not a floating point number type was successfully
     * parsed.
     */
    PseudoDataType::UP _tryParseFloatType();

    /*
     * Tries to parse a string type block. Returns whether or not a
     * string type was successfully parsed.
     */
    PseudoDataType::UP _tryParseStringType();

    /*
     * Tries to parse an enumeration type block. Returns whether or not
     * an enumeration type was successfully parsed.
     *
     * If the parser makes it to the `:` or `{` token and the
     * enumeration is named, this method adds a type alias to the current
     * frame's map of aliased types if `addAlias` is true, and sets
     * `*aliasName` to the name of the alias.
     */
    PseudoDataType::UP _tryParseEnumType(bool addAlias = true,
                                         std::string *aliasName = nullptr);

    template <typename EnumTypeT, typename PseudoMemberT>
    PseudoDataType::UP _finishParseEnumType(const DataType& intType,
                                            const MetadataTextLocation& beginLocation,
                                            bool addAlias,
                                            const std::string& potAliasName);

    /*
     * Tries to parse a structure type block. Returns whether or not a
     * structure type was successfully parsed.
     *
     * If the parser makes it to the opening `{` and the structure is
     * named, this method adds a type alias to the current frame's map
     * of aliased types if `addAlias` is true, and sets `*aliasName` to
     * the name of the alias.
     */
    PseudoDataType::UP _tryParseStructType(bool addAlias = true,
                                           std::string *aliasName = nullptr);

    /*
     * Tries to parse a variant type block. Returns whether or not a
     * variant type was successfully parsed.
     *
     * If the parser makes it to the opening `{` and the variant is
     * named, this method adds a type alias to the current frame's map
     * of aliased types if `addAlias` is true, and sets `*aliasName` to
     * the name of the alias.
     */
    PseudoDataType::UP _tryParseVariantType(bool addAlias = true,
                                            std::string *aliasName = nullptr);

    /*
     * Tries to parse a trace type environment block and sets it in the
     * current trace type data. Returns whether or not a trace type
     * environment block was parsed.
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
     * trace type data. Returns whether or not a clock type block was
     * parsed.
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
    bool _tryParseClockBlock();

    /*
     * Tries to parse a callsite block and ignores it. Returns whether
     * or not a callsite block was parsed.
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
     * current trace type data. Returns whether or not a trace type
     * block was parsed.
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
    bool _tryParseTraceBlock();

    /*
     * Tries to parse a data stream type block and initializes a pseudo
     * stream type. Returns whether or not a data stream type block was
     * parsed.
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
    bool _tryParseStreamBlock();

    /*
     * Tries to parse an event record type block and inserts it into its
     * pseudo data stream type. Returns whether or not an event record
     * type block was parsed.
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
    bool _tryParseEventBlock();

    /*
     * Tries to gets a fast integer type clone from the fast integer
     * type cache. See the description of `_FastIntTypeEntry`.
     */
    DataType::UP _getFastIntType();

    MetadataTextLocation _curLocation() const
    {
        return MetadataTextLocation {_ss.curLineNumber(), _ss.curColNumber()};
    }

    // inserts a fast integer type
    void _insertFastIntType(CharIt begin, CharIt end, const DataType& type);

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

private:
    /*
     * Escapes the literal string between `begin` (inclusive) and `end`
     * (exclusive). The passed substring excludes the double quotes.
     *
     * Examples:
     *
     *     salut\nvous -> "salut\nvous"
     *     lenovo\tx230 -> "lenovo\tx230"
     */
    static std::string _escapeLiteralString(CharIt begin, CharIt end,
                                            const MetadataTextLocation& location)
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
                throw MetadataParseError {ss.str(), location};
            } else {
                str += *it;
            }

            ++it;
        }

        return str;
    }

private:
    // underlying string scanner
    StringScanner<CharIt> _ss;

    // expected UUID
    boost::optional<boost::uuids::uuid> _expectedUuid;

    // cache of TSDL substring to integer type
    std::vector<_FastIntTypeEntry> _fastIntTypes;
};

template <typename CharIt>
TsdlParser<CharIt>::TsdlParser(CharIt begin, CharIt end,
                               const boost::optional<boost::uuids::uuid>& expectedUuid) :
    _ss {begin, end},
    _expectedUuid {expectedUuid}
{
    assert(end >= begin);
    _pseudoTraceType.uuid = boost::uuids::nil_generator {}();
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
        throw MetadataParseError {
            "Expecting type alias (`typealias`, `typedef`, `enum NAME`, "
            "`struct NAME`, or `variant NAME`), trace type block (`trace`), "
            "trace type's environment block (`env`), "
            "clock type block (`clock`), data stream type block (`stream`), "
            "or event record type block (`event`). Did you forget the `;` "
            "after the block's closing `}`?", this->_curLocation()
        };
    }

    this->_applyQuirks();
    this->_createTraceType();
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseRootBlock()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto location = this->_curLocation();

    if (this->_tryParseTypeAlias()) {
        return true;
    }

    try {
        if (this->_tryParseEventBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `event` root block:", location);
        throw;
    }

    try {
        if (this->_tryParseStreamBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `stream` root block:", location);
        throw;
    }

    try {
        if (this->_tryParseTraceBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `trace` root block:", location);
        throw;
    }

    try {
        if (this->_tryParseEnvBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `env` root block:", location);
        throw;
    }

    try {
        if (this->_tryParseClockBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `clock` root block:", location);
        throw;
    }

    try {
        // parse callsite, even if we don't care about it
        if (this->_tryParseCallsiteBlock()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `callsite` root block:", location);
        throw;
    }

    return false;
}

template <typename CharIt>
void TsdlParser<CharIt>::_expectToken(const char * const token)
{
    if (!_ss.scanToken(token)) {
        std::ostringstream ss;

        ss << "Expecting `" << token << "`.";
        throw MetadataParseError {ss.str(), this->_curLocation()};
    }
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseEnumStructVariantTypeAlias()
{
    PseudoDataType::UP type;
    std::string aliasName;

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto location = this->_curLocation();

    // try enum FT alias definition
    _ss.save();

    try {
        type = this->_tryParseEnumType(false, &aliasName);
    } catch (MetadataParseError& error) {
        _ss.reject();
        error._appendErrorMessage("In `enum` block:", location);
        throw;
    }

    if (type) {
        // parse `;` to make sure it's not a field/choice
        if (_ss.scanToken(";")) {
            // we have a winner
            _ss.accept();

            // add alias if an alias name was found (safe to move here)
            if (!aliasName.empty()) {
                this->_addTypeAlias(aliasName, *type, this->_curLocation());
            }

            return true;
        }
    }

    _ss.reject();

    // try struct FT alias definition
    _ss.save();

    try {
        type = this->_tryParseStructType(false, &aliasName);
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `struct` block:", location);
        _ss.reject();
        throw;
    }

    if (type) {
        // parse `;` to make sure it's not a field/choice
        if (_ss.scanToken(";")) {
            // we have a winner
            _ss.accept();

            // add alias if an alias name was found (safe to move here)
            if (!aliasName.empty()) {
                this->_addTypeAlias(aliasName, *type, this->_curLocation());
            }

            return true;
        }
    }

    _ss.reject();

    // try variant FT alias definition
    _ss.save();

    try {
        type = this->_tryParseVariantType(false, &aliasName);
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `variant` block:", location);
        _ss.reject();
        throw;
    }

    if (type) {
        // parse `;` to make sure it's not a field/choice
        if (_ss.scanToken(";")) {
            // we have a winner
            _ss.accept();

            // add alias if an alias name was found (safe to move here)
            if (!aliasName.empty()) {
                this->_addTypeAlias(aliasName, *type, this->_curLocation());
            }

            return true;
        }
    }

    _ss.reject();
    return false;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseGenericTypeAlias()
{
    bool isTypealias = false;

    if (_ss.scanToken("typealias")) {
        isTypealias = true;
    } else if (!_ss.scanToken("typedef")) {
        return false;
    }

    _LexicalScope lexScope {*this, _StackFrame::Kind::TYPE_ALIAS};

    // parse type
    auto type = this->_tryParseFullType();

    if (!type) {
        // cannot parse a full type: try an existing type alias name
        std::string existingAliasName;
        CharIt begin, end;

        if (_ss.scanIdentifier(begin, end)) {
            existingAliasName.assign(begin, end);

            type = this->_getAliasedType(existingAliasName);

            if (!type) {
                throw MetadataParseError {
                    "Expecting explicit type block (`integer`, `floating_point`, "
                    "`enum`, `string`, `struct`, or `variant`) or "
                    "existing type alias name.",
                    this->_curLocation()
                };
            }
        } else {
            throw MetadataParseError {
                "Expecting explicit type block (`integer`, `floating_point`, "
                "`enum`, `string`, `struct`, or `variant`) or "
                "existing type alias name.",
                this->_curLocation()
            };
        }
    }

    // parse `:=` if `typealias` block
    if (isTypealias) {
        this->_expectToken(":=");
    }

    // parse name
    std::string aliasName;

    this->_parseTypeAliasName(aliasName, true);
    type = this->_parseArraySeqLengths(std::move(type));

    // parse `;`
    this->_expectToken(";");

    // add parsed type alias to parent frame
    lexScope.exit();
    this->_addTypeAlias(aliasName, *type, this->_curLocation());
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseTypeAlias()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto location = this->_curLocation();

    try {
        if (this->_tryParseGenericTypeAlias()) {
            return true;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In type alias:", location);
        throw;
    }

    if (this->_tryParseEnumStructVariantTypeAlias()) {
        return true;
    }

    return false;
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseType()
{
    auto type = this->_tryParseGetTypeAliasRef();

    if (type) {
        return type;
    }

    type = this->_tryParseFullType();

    if (type) {
        return type;
    }

    return nullptr;
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseFullType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto location = this->_curLocation();
    PseudoDataType::UP type;

    try {
        type = this->_tryParseIntType();

        if (type) {
            return type;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `integer` block:", location);
        throw;
    }

    try {
        type = this->_tryParseStringType();

        if (type) {
            return type;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `string` block:", location);
        throw;
    }

    try {
        type = this->_tryParseEnumType();

        if (type) {
            return type;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `enum` block:", location);
        throw;
    }

    try {
        type = this->_tryParseFloatType();

        if (type) {
            return type;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `floating_point` block:", location);
        throw;
    }

    try {
        type = this->_tryParseStructType();

        if (type) {
            return type;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `struct` block:", location);
        throw;
    }

    try {
        type = this->_tryParseVariantType();

        if (type) {
            return type;
        }
    } catch (MetadataParseError& error) {
        error._appendErrorMessage("In `variant` block:", location);
        throw;
    }

    return nullptr;
}

template <typename CharIt>
void TsdlParser<CharIt>::_insertFastIntType(CharIt begin, CharIt end,
                                            const DataType& type)
{
    assert(end >= begin);

    if (static_cast<Size>(std::distance(begin, end)) >
            _MAX_FAST_INT_FT_STRING_SIZE) {
        return;
    }

    _fastIntTypes.push_back({begin, end, type.clone()});
}

template <typename CharIt>
DataType::UP TsdlParser<CharIt>::_getFastIntType()
{
    for (const auto& entry : _fastIntTypes) {
        auto entrySize = std::distance(entry.begin, entry.end);

        if (_ss.charsLeft() < static_cast<Size>(entrySize)) {
            // would not fit
            continue;
        }

        if (std::equal(entry.begin, entry.end,
                       _ss.at(), _ss.at() + entrySize)) {
            // we have a match!
            _ss.at(_ss.at() + entrySize);
            return entry.type->clone();
        }
    }

    return nullptr;
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseIntType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beforeKwLocation = this->_curLocation();

    // parse `integer`
    if (!_ss.scanToken("integer")) {
        return nullptr;
    }

    _ss.skipCommentsAndWhitespaces();

    auto fastIntUp = this->_getFastIntType();

    if (fastIntUp) {
        return std::make_unique<PseudoScalarTypeWrapper>(std::move(fastIntUp));
    }

    const auto beginLocation = this->_curLocation();
    const auto beginAt = _ss.at();

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attributes attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttribute());
    }

    const auto endAt = _ss.at();

    // check for duplicate attributes
    TsdlParser::_checkDupAttribute(attrs);

    unsigned int align = 0;
    unsigned int size = 0;
    int byteOrder = _pseudoTraceType.defaultByteOrder; // temp. default value
    DisplayBase dispBase = DisplayBase::DECIMAL;
    bool isSigned = false;
    Encoding encoding = Encoding::NONE;
    boost::optional<std::string> mappedClockTypeName = boost::none;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "base") {
            dispBase = attr.displayBase();
        } else if (attr.name == "size") {
            attr.checkKind(_Attribute::Kind::UINT);

            if (attr.uintValue == 0) {
                std::ostringstream ss;

                ss << "Invalid `size` attribute (must be greater than 0): " <<
                      attr.uintValue << ".";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            if (attr.uintValue > 64) {
                std::ostringstream ss;

                ss << "`size` attribute is greater than 64 (unsupported): " <<
                      attr.uintValue << ".";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            size = attr.uintValue;
        } else if (attr.name == "align") {
            align = attr.alignment();
        } else if (attr.name == "byte_order") {
            byteOrder = attr.byteOrder();

            if (byteOrder == -1) {
                byteOrder = _pseudoTraceType.defaultByteOrder;
            }
        } else if (attr.name == "encoding") {
            encoding = attr.encoding();
        } else if (attr.name == "signed") {
            isSigned = attr.boolEquiv();
        } else if (attr.name == "map") {
            mappedClockTypeName = std::move(attr.strValue);
        } else {
            attr.throwUnknown();
        }
    }

    // make sure size is set
    if (size == 0) {
        TsdlParser::_throwMissingAttribute("size", beforeKwLocation);
    }

    // set default alignment()
    if (align == 0) {
        if (size % 8 == 0) {
            align = 8;
        } else {
            align = 1;
        }
    }

    DataType::UP intTypeUp;

    if (isSigned) {
        intTypeUp = std::make_unique<const SignedIntType>(align, size,
                                                          static_cast<ByteOrder>(byteOrder),
                                                          dispBase, encoding,
                                                          mappedClockTypeName);
    } else {
        intTypeUp = std::make_unique<const UnsignedIntType>(align, size,
                                                            static_cast<ByteOrder>(byteOrder),
                                                            dispBase, encoding,
                                                            mappedClockTypeName);
    }

    assert(intTypeUp);

    if (beginLocation.lineNumber() == this->_curLocation().lineNumber()) {
        // fast integer FT cache only supported for single lines
        this->_insertFastIntType(beginAt, endAt, *intTypeUp);
    }

    return std::make_unique<PseudoScalarTypeWrapper>(std::move(intTypeUp));
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseFloatType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLocation = this->_curLocation();

    // parse `floating_point`
    if (!_ss.scanToken("floating_point")) {
        return nullptr;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attributes attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttribute());
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttribute(attrs);

    unsigned int align = 8;
    unsigned int expDig = 0;
    unsigned int mantDig = 0;
    int byteOrder = _pseudoTraceType.defaultByteOrder;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "exp_dig") {
            attr.checkKind(_Attribute::Kind::UINT);
            expDig = attr.uintValue;
        } else if (attr.name == "mant_dig") {
            attr.checkKind(_Attribute::Kind::UINT);
            mantDig = attr.uintValue;
        } else if (attr.name == "align") {
            align = attr.alignment();
        } else if (attr.name == "byte_order") {
            byteOrder = attr.byteOrder();

            if (byteOrder == -1) {
                byteOrder = _pseudoTraceType.defaultByteOrder;
            }
        } else {
            attr.throwUnknown();
        }
    }

    // make sure exp_dig and mant_dig is set
    if (expDig == 0) {
        TsdlParser::_throwMissingAttribute("exp_dig", beginLocation);
    }

    if (mantDig == 0) {
        TsdlParser::_throwMissingAttribute("mant_dig", beginLocation);
    }

    if (!(expDig == 8 && mantDig == 24) && !(expDig == 11 && mantDig == 53)) {
        std::ostringstream ss;

        ss << "Invalid `exp_dig` or `mant_dig` attribute combination: " <<
              "only (8, 24) and (11, 53) are supported.";
        throw MetadataParseError {ss.str(), beginLocation};
    }

    auto floatTypeUp = std::make_unique<const FloatType>(align, expDig + mantDig,
                                                         static_cast<ByteOrder>(byteOrder));

    return std::make_unique<PseudoScalarTypeWrapper>(std::move(floatTypeUp));
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseStringType()
{
    // parse `string`
    if (!_ss.scanToken("string")) {
        return nullptr;
    }

    // try to parse `{`
    if (!_ss.scanToken("{")) {
        auto stringTypeUp = std::make_unique<const StringType>(8);
        return std::make_unique<PseudoScalarTypeWrapper>(std::move(stringTypeUp));
    }

    // parse attributes
    _Attributes attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttribute());
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttribute(attrs);

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "encoding") {
            attr.encoding();
        } else {
            attr.throwUnknown();
        }
    }

    auto stringTypeUp = std::make_unique<const StringType>(8);

    return std::make_unique<PseudoScalarTypeWrapper>(std::move(stringTypeUp));
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseEnumType(const bool addAlias,
                                                         std::string * const aliasName)
{
    StringScannerRejecter<CharIt> ssRejecter {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLocation = this->_curLocation();

    // parse `enum`
    if (!_ss.scanToken("enum")) {
        return nullptr;
    }

    // try to parse name
    CharIt begin, end;
    std::string potAliasName;

    if (_ss.scanIdentifier(begin, end)) {
        potAliasName = "enum ";
        potAliasName.append(begin, end);

        if (aliasName) {
            *aliasName = potAliasName;
        }
    }

    {
        StringScannerRejecter<CharIt> ssRejecterOp {_ss};

        if (!_ss.scanToken(":") && !_ss.scanToken("{")) {
            return nullptr;
        }
    }

    // accept the enum so far
    ssRejecter.accept();
    _ss.skipCommentsAndWhitespaces();

    PseudoDataType::UP pseudoIntType;

    // try to parse the integer type
    if (_ss.scanToken(":")) {
        _ss.skipCommentsAndWhitespaces();

        // remember location
        const auto location = this->_curLocation();

        // check for a type alias name first
        std::string aliasName;

        if (this->_parseTypeAliasName(aliasName, false)) {
            // find type alias
            pseudoIntType = this->_getAliasedType(aliasName);

            if (!pseudoIntType) {
                std::ostringstream ss;

                ss << "Cannot find type alias `" << aliasName << "`.";
                throw MetadataParseError {ss.str(), location};
            }

            if (!pseudoIntType->isIntType()) {
                std::ostringstream ss;

                ss << "Field type alias `" << aliasName << "` is not an " <<
                      "integer type.";
                throw MetadataParseError {ss.str(), location};
            }
        } else {
            // fall back to expecting `integer`
            pseudoIntType = this->_tryParseIntType();

            if (!pseudoIntType) {
                throw MetadataParseError {
                    "Expecting `integer` or existing integer type "
                    "alias name.",
                    location
                };
            }
        }
    } else {
        // use "int" type alias
        pseudoIntType = this->_getAliasedType("int");

        if (!pseudoIntType) {
            throw MetadataParseError {
                "Implicit `int` type alias does not exist in this scope.",
                beginLocation
            };
        }

        if (!pseudoIntType->isIntType()) {
            throw MetadataParseError {
                "Implicit `int` type alias is not an integer type.",
                beginLocation
            };
        }
    }

    // parse `{`
    this->_expectToken("{");

    // parse members
    const auto& scalarTypeWrapper = static_cast<const PseudoScalarTypeWrapper&>(*pseudoIntType);
    auto intType = scalarTypeWrapper.type->asIntType();

    if (intType->isSignedIntType()) {
        return this->_finishParseEnumType<SignedEnumType,
                                          PseudoSignedEnumTypeMember>(*intType,
                                                                       beginLocation,
                                                                       addAlias,
                                                                       potAliasName);
    } else {
        return this->_finishParseEnumType<UnsignedEnumType,
                                          PseudoUnsignedEnumTypeMember>(*intType,
                                                                         beginLocation,
                                                                         addAlias,
                                                                         potAliasName);
    }
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseStructType(const bool addAlias,
                                                           std::string * const aliasName)
{
    StringScannerRejecter<CharIt> ssRejecter {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLocation = this->_curLocation();

    // parse `struct`
    if (!_ss.scanToken("struct")) {
        return nullptr;
    }

    // try to parse name
    CharIt begin, end;
    std::string potAliasName;
    _LexicalScope typeAliasLexScope;

    if (_ss.scanIdentifier(begin, end)) {
        potAliasName = "struct ";
        potAliasName.append(begin, end);

        if (aliasName) {
            typeAliasLexScope = _LexicalScope {*this, _StackFrame::Kind::TYPE_ALIAS};
            *aliasName = potAliasName;
        }
    }

    _LexicalScope structTypeLexScope {*this, _StackFrame::Kind::STRUCT_TYPE};

    // parse `{`
    if (!_ss.scanToken("{")) {
        return nullptr;
    }

    // parse type aliases and fields
    PseudoNamedDataTypes fields;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        if (_ss.scanToken("}")) {
            break;
        }

        const auto location = this->_curLocation();
        bool success;

        try {
            success = this->_tryParseNamedDataTypeOrTypeAlias(fields);
        } catch (MetadataParseError& error) {
            error._appendErrorMessage("While parsing `struct` block's body:",
                                      location);
            throw;
        }

        if (!success) {
            throw MetadataParseError {
                "Expecting field with known type or type alias.",
                this->_curLocation()
            };
        }
    }

    ssRejecter.accept();

    // check for duplicate field
    TsdlParser::_checkDupNamedDataType(fields, beginLocation);

    unsigned long long align = 1;

    if (_ss.scanToken("align")) {
        this->_expectToken("(");

        if (!_ss.scanConstInt(align)) {
            throw MetadataParseError {
                "Expecting valid constant unsigned integer.",
                this->_curLocation()
            };
        }

        if (!ispow2(align)) {
            std::ostringstream ss;

            ss << "Invalid minimum alignment for `struct` block " <<
                  "(must be a power of two): " << align << ".";
            throw MetadataParseError {ss.str(), this->_curLocation()};
        }

        this->_expectToken(")");
    }

    auto pseudoStructType = std::make_unique<PseudoStructType>(align,
                                                               std::move(fields));

    structTypeLexScope.exit();
    typeAliasLexScope.exit();

    if (addAlias && !potAliasName.empty()) {
        this->_addTypeAlias(potAliasName, *pseudoStructType,
                            this->_curLocation());
    }

    return pseudoStructType;
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseVariantType(const bool addAlias,
                                                            std::string * const aliasName)
{
    StringScannerRejecter<CharIt> ssRejecter {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLocation = this->_curLocation();

    // parse `variant`
    if (!_ss.scanToken("variant")) {
        return nullptr;
    }

    // try to parse name
    CharIt begin, end;
    std::string potAliasName;
    _LexicalScope typeAliasLexScope;

    if (_ss.scanIdentifier(begin, end)) {
        potAliasName = "variant ";
        potAliasName.append(begin, end);

        if (aliasName) {
            typeAliasLexScope = _LexicalScope {*this, _StackFrame::Kind::TYPE_ALIAS};
            *aliasName = potAliasName;
        }
    }

    _LexicalScope variantTypeLexScope {*this, _StackFrame::Kind::VARIANT_TYPE};

    // try to parse `<`
    PseudoFieldRef pseudoFieldRef;

    if (_ss.scanToken("<")) {
        this->_parseFieldRef(pseudoFieldRef, true);

        if (pseudoFieldRef.isEnv) {
            throw MetadataParseError {
                "Variant type's tag field reference cannot start with `env.`.",
                this->_curLocation()
            };
        }

        this->_expectToken(">");
    }

    // parse `{`
    if (!_ss.scanToken("{")) {
        return nullptr;
    }

    // parse type aliases and choices
    PseudoNamedDataTypes choices;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        if (_ss.scanToken("}")) {
            break;
        }

        const auto location = this->_curLocation();
        bool success;

        try {
            success = this->_tryParseNamedDataTypeOrTypeAlias(choices);
        } catch (MetadataParseError& error) {
            error._appendErrorMessage("While parsing `variant` block's body:",
                                      location);
            throw;
        }

        if (!success) {
            throw MetadataParseError {
                "Expecting choice or type alias.", this->_curLocation()
            };
        }
    }

    ssRejecter.accept();

    if (choices.empty()) {
        throw MetadataParseError {
            "Variant type must contain at least one choice.",
            beginLocation
        };
    }

    // check for duplicate choice
    TsdlParser::_checkDupNamedDataType(choices, beginLocation);

    auto varType = std::make_unique<PseudoVariantType>(pseudoFieldRef,
                                                       std::move(choices));

    variantTypeLexScope.exit();
    typeAliasLexScope.exit();

    if (addAlias && !potAliasName.empty()) {
        this->_addTypeAlias(potAliasName, *varType, this->_curLocation());
    }

    return varType;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseEnvBlock()
{
    // parse `env`
    if (!_ss.scanToken("env")) {
        return false;
    }

    if (_pseudoTraceType.env) {
        throw MetadataParseError {
            "Duplicate `env` block.", this->_curLocation()
        };
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attributes attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttribute());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    this->_checkDupAttribute(attrs);

    TraceTypeEnv::Entries entries;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.kind != _Attribute::Kind::INT &&
                attr.kind != _Attribute::Kind::UINT &&
                attr.kind != _Attribute::Kind::STRING) {
            std::ostringstream ss;

            ss << "Environment entry `" << attr.name <<
                  "`: expecting constant integer or literal string.";
            throw MetadataParseError {ss.str(), attr.valueTextLocation()};
        }

        TraceTypeEnv::Entry entry;

        if (attr.kind == _Attribute::Kind::INT) {
            entry = attr.intValue;
        } else if (attr.kind == _Attribute::Kind::UINT) {
            if (attr.uintValue >= (1ULL << 63)) {
                std::ostringstream ss;

                ss << "Environment entry `" << attr.name <<
                      "`: value " << attr.uintValue << " is too large " <<
                      "(expecting a 64-bit signed integer).";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            entry = static_cast<long long>(attr.uintValue);
        } else if (attr.kind == _Attribute::Kind::STRING) {
            entry = attr.strValue;
        }

        entries[attr.name] = entry;
    }

    _pseudoTraceType.env = std::make_unique<const TraceTypeEnv>(entries);
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
    _Attributes attrs;

    // pretty loose: we accept everything, even duplicates
    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttribute());
    }

    // parse `;`
    this->_expectToken(";");
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseClockBlock()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLocation = this->_curLocation();

    // parse `clock`
    if (!_ss.scanToken("clock")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attributes attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttribute());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    this->_checkDupAttribute(attrs);

    std::string name;
    boost::optional<std::string> description = boost::none;
    boost::optional<boost::uuids::uuid> uuid = boost::none;
    unsigned long long freq = 1'000'000'000ULL;
    unsigned long long precision = 0;
    long long offsetSeconds = 0;
    Cycles offsetCycles = 0;
    bool isAbsolute = false;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "name") {
            if (attr.kind != _Attribute::Kind::IDENTIFIER &&
                    attr.kind != _Attribute::Kind::STRING) {
                std::ostringstream ss;

                ss << "Attribute `" << attr.name <<
                      "`: expecting identifier or literal string.";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            name = attr.strValue;
        } else if (attr.name == "description") {
            attr.checkKind(_Attribute::Kind::STRING);
            description = attr.strValue;
        } else if (attr.name == "uuid") {
            attr.checkKind(_Attribute::Kind::STRING);
            auto tmpUuid = TsdlParser::_uuidFromString(attr.strValue);

            if (tmpUuid.is_nil()) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" <<
                      attr.strValue << "`.";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            uuid = tmpUuid;
        } else if (attr.name == "freq") {
            attr.checkKind(_Attribute::Kind::UINT);

            if (attr.uintValue == 0) {
                std::ostringstream ss;

                ss << "Invalid `freq` attribute (must be greater than 0): " <<
                      attr.uintValue << ".";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            freq = static_cast<unsigned long long>(attr.uintValue);
        } else if (attr.name == "precision") {
            attr.checkKind(_Attribute::Kind::UINT);
            precision = attr.uintValue;
        } else if (attr.name == "offset_s") {
            if (attr.kind != _Attribute::Kind::INT &&
                    attr.kind != _Attribute::Kind::UINT) {
                throw MetadataParseError {
                    "Attribute `offset_s`: expecting constant signed integer.",
                    attr.valueTextLocation()
                };
            }

            if (attr.kind == _Attribute::Kind::UINT) {
                using UT = decltype(attr.uintValue);

                if (attr.uintValue > static_cast<UT>(std::numeric_limits<long long>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `offset_s`: value is too large: " <<
                          attr.uintValue << ".";
                    throw MetadataParseError {ss.str(), attr.valueTextLocation()};
                }

                offsetSeconds = static_cast<long long>(attr.uintValue);
            } else {
                offsetSeconds = attr.intValue;
            }
        } else if (attr.name == "offset") {
            attr.checkKind(_Attribute::Kind::UINT);
            offsetCycles = static_cast<Cycles>(attr.uintValue);
        } else if (attr.name == "absolute") {
            isAbsolute = attr.boolEquiv();
        } else {
            attr.throwUnknown();
        }
    }

    // make sure name is set
    if (name.empty()) {
        TsdlParser::_throwMissingAttribute("name", beginLocation);
    }

    // make sure clock type does not exist
    auto res = std::find_if(std::begin(_pseudoTraceType.clockTypes),
                            std::end(_pseudoTraceType.clockTypes),
                            [&name](const std::unique_ptr<const ClockType>& clockType) {
                                return clockType->name() == name;
                            });

    if (res != std::end(_pseudoTraceType.clockTypes)) {
        std::ostringstream ss;

        ss << "Duplicate `clock` block named `" << name << "`.";
        throw MetadataParseError {ss.str(), beginLocation};
    }

    auto clockType = std::make_unique<const ClockType>(name, freq, description,
                                                       uuid, precision,
                                                       offsetSeconds,
                                                       offsetCycles,
                                                       isAbsolute);

    _pseudoTraceType.clockTypes.insert(std::move(clockType));
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseTraceBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::TRACE};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLocation = this->_curLocation();

    // parse `trace`
    if (!_ss.scanToken("trace")) {
        return false;
    }

    if (_pseudoTraceType.majorVersion != 0) {
        throw MetadataParseError {
            "Duplicate `trace` block.",
            this->_curLocation()
        };
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attributes attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // try to parse packet header type
        auto type = this->_tryParseScopeDef(_StackFrame::Kind::PACKET_HEADER_TYPE,
                                            "packet", "header");

        if (type) {
            if (_pseudoTraceType.packetHeaderType) {
                throw MetadataParseError {
                    "Duplicate `packet.header` scope.",
                    this->_curLocation()
                };
            }

            _pseudoTraceType.packetHeaderType = std::move(type);
            continue;
        }

        // try to parse type alias
        if (this->_tryParseTypeAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttribute());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    this->_checkDupAttribute(attrs);

    int defaultByteOrder = -1;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "major" || attr.name == "minor") {
            attr.checkKind(_Attribute::Kind::UINT);

            if (attr.name == "major") {
                if (attr.uintValue != 1) {
                    std::ostringstream ss;

                    ss << "Invalid `major` attribute: " <<
                          "unsupported major version (expecting 1): " <<
                          attr.uintValue << ".";
                    throw MetadataParseError {ss.str(), attr.valueTextLocation()};
                }

                _pseudoTraceType.majorVersion = attr.uintValue;
            } else if (attr.name == "minor") {
                if (attr.uintValue != 8) {
                    std::ostringstream ss;

                    ss << "Invalid `minor` attribute: " <<
                          "unsupported minor version (expecting 8): " <<
                          attr.uintValue << ".";
                    throw MetadataParseError {ss.str(), attr.valueTextLocation()};
                }

                _pseudoTraceType.minorVersion = attr.uintValue;
            }
        } else if (attr.name == "byte_order") {
            defaultByteOrder = attr.byteOrder();

            if (defaultByteOrder == -1) {
                throw MetadataParseError {
                    "Invalid `byte_order` attribute: cannot be `native` here.",
                    attr.valueTextLocation()
                };
            }
        } else if (attr.name == "uuid") {
            attr.checkKind(_Attribute::Kind::STRING);

            if (attr.strValue.size() != 36) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" <<
                      attr.strValue << "`.";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            _pseudoTraceType.uuid = TsdlParser::_uuidFromString(attr.strValue);

            if (_pseudoTraceType.uuid.is_nil()) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" <<
                      attr.strValue << "`.";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            if (_expectedUuid) {
                if (_pseudoTraceType.uuid != *_expectedUuid) {
                    std::ostringstream ss;

                    ss << "Invalid `uuid` attribute (`" <<
                          attr.strValue << "`): expecting `" <<
                          boost::uuids::to_string(*_expectedUuid) << "`.";
                    throw MetadataParseError {ss.str(), attr.valueTextLocation()};
                }
            }
        } else {
            attr.throwUnknown();
        }
    }

    // make sure major, minor, and byte order properties are set
    if (_pseudoTraceType.majorVersion == 0) {
        this->_throwMissingAttribute("major", beginLocation);
    }

    if (_pseudoTraceType.minorVersion == 0) {
        this->_throwMissingAttribute("minor", beginLocation);
    }

    if (defaultByteOrder == -1) {
        this->_throwMissingAttribute("byte_order", beginLocation);
    }

    /*
     * Alright, we have the REAL byte order now, so restart the
     * whooooole process. Luckily the `trace` block is early in the
     * input string, so we didn't waste too many precious cycles. In
     * practice (LTTng, barectf, Babeltrace's CTF writer) this is always
     * the case.
     */
    if (_pseudoTraceType.defaultByteOrder == -1) {
        _pseudoTraceType.clear();
        _pseudoTraceType.defaultByteOrder = defaultByteOrder;
        _fastIntTypes.clear();
        assert(_stack.size() == 2);
        _stack[0].typeAliases.clear();
        _ss.reset();
        return true;
    }

    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseStreamBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::STREAM};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLocation = this->_curLocation();

    // parse `stream`
    if (!_ss.scanToken("stream")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attributes attrs;
    PseudoDataType::UP packetContextType;
    PseudoDataType::UP eventHeaderType;
    PseudoDataType::UP eventContextType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // try to parse packet context type
        auto type = this->_tryParseScopeDef(_StackFrame::Kind::STREAM_PACKET_CONTEXT_TYPE,
                                            "packet", "context");

        if (type) {
            if (packetContextType) {
                throw MetadataParseError {
                    "Duplicate `packet.context` scope.",
                    this->_curLocation()
                };
            }

            packetContextType = std::move(type);
            continue;
        }

        // try to parse event header type
        type = this->_tryParseScopeDef(_StackFrame::Kind::STREAM_EVENT_HEADER_TYPE,
                                       "event", "header", false);

        if (type) {
            if (eventHeaderType) {
                throw MetadataParseError {
                    "Duplicate `event.header` scope.",
                    this->_curLocation()
                };
            }

            eventHeaderType = std::move(type);
            continue;
        }

        // try to parse event context type
        type = this->_tryParseScopeDef(_StackFrame::Kind::STREAM_EVENT_CONTEXT_TYPE,
                                       "event", "context", false);

        if (type) {
            if (eventContextType) {
                throw MetadataParseError {
                    "Duplicate `event.context` scope.",
                    this->_curLocation()
                };
            }

            eventContextType = std::move(type);
            continue;
        }

        // try to parse type alias
        if (this->_tryParseTypeAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttribute());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    this->_checkDupAttribute(attrs);

    // default stream ID is 0
    TypeId id = 0;

    // check for attributes
    for (const auto& attr : attrs) {
        if (attr.name == "id") {
            attr.checkKind(_Attribute::Kind::UINT);
            id = attr.uintValue;
        } else {
            attr.throwUnknown();
        }
    }

    // make sure data stream type does not exist with this ID
    if (this->_pseudoDataStreamTypeExists(id)) {
        std::ostringstream ss;

        ss << "Duplicate `stream` block with ID " << id << ".";
        throw MetadataParseError {ss.str(), beginLocation};
    }

    // create and initialize pseudo data stream type
    auto pseudoDataStreamType = std::make_unique<PseudoDataStreamType>();

    pseudoDataStreamType->id = id;
    pseudoDataStreamType->packetContextType = std::move(packetContextType);
    pseudoDataStreamType->eventHeaderType = std::move(eventHeaderType);
    pseudoDataStreamType->eventContextType = std::move(eventContextType);
    _pseudoTraceType.dataStreamTypes[id] = std::move(pseudoDataStreamType);
    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseEventBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::EVENT};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLocation = this->_curLocation();

    // parse `event`
    if (!_ss.scanToken("event")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attributes attrs;
    PseudoDataType::UP eventContextType;
    PseudoDataType::UP eventPayloadType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.scanToken("}")) {
            break;
        }

        // try to parse context type
        auto type = this->_tryParseScopeDef(_StackFrame::Kind::EVENT_CONTEXT_TYPE,
                                            "context");

        if (type) {
            if (eventContextType) {
                throw MetadataParseError {
                    "Duplicate `event.context` scope.",
                    this->_curLocation()
                };
            }

            eventContextType = std::move(type);
            continue;
        }

        // try to parse payload type
        type = this->_tryParseScopeDef(_StackFrame::Kind::EVENT_PAYLOAD_TYPE,
                                       "fields");

        if (type) {
            if (eventPayloadType) {
                throw MetadataParseError {
                    "Duplicate `event.fields` scope.",
                    this->_curLocation()
                };
            }

            eventPayloadType = std::move(type);
            continue;
        }

        // try to parse type alias
        if (this->_tryParseTypeAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttribute());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    this->_checkDupAttribute(attrs);

    // default event and stream IDs are 0
    TypeId id = 0;
    TypeId dataStreamTypeId = 0;
    boost::optional<LogLevel> logLevel = boost::none;
    boost::optional<std::string> modelEmfUri;
    boost::optional<std::string> name;

    // check for attributes
    for (const auto& attr : attrs) {
        if (attr.name == "id") {
            attr.checkKind(_Attribute::Kind::UINT);
            id = attr.uintValue;
        } else if (attr.name == "stream_id") {
            attr.checkKind(_Attribute::Kind::UINT);
            dataStreamTypeId = attr.uintValue;
        } else if (attr.name == "loglevel") {
            if (attr.kind != _Attribute::Kind::INT &&
                    attr.kind != _Attribute::Kind::UINT) {
                throw MetadataParseError {
                    "Attribute `loglevel`: expecting constant signed integer.",
                    attr.valueTextLocation()
                };
            }

            if (attr.kind == _Attribute::Kind::UINT) {
                using UT = decltype(attr.uintValue);

                if (attr.uintValue > static_cast<UT>(std::numeric_limits<LogLevel>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `loglevel`: value is too large: " <<
                          attr.uintValue << ".";
                    throw MetadataParseError {ss.str(), attr.valueTextLocation()};
                }

                logLevel = static_cast<LogLevel>(attr.uintValue);
            } else {
                logLevel = static_cast<LogLevel>(attr.intValue);
            }
        } else if (attr.name == "model.emf.uri") {
            attr.checkKind(_Attribute::Kind::STRING);
            modelEmfUri = attr.strValue;
        } else if (attr.name == "name") {
            if (attr.kind != _Attribute::Kind::IDENTIFIER &&
                    attr.kind != _Attribute::Kind::STRING) {
                std::ostringstream ss;

                ss << "Attribute `" << attr.name <<
                      "`: expecting identifier or literal string.";
                throw MetadataParseError {ss.str(), attr.valueTextLocation()};
            }

            name = attr.strValue;
        } else {
            attr.throwUnknown();
        }
    }

    // check if the data stream type exists
    if (!this->_pseudoDataStreamTypeExists(dataStreamTypeId)) {
        if (_pseudoTraceType.dataStreamTypes.empty() && dataStreamTypeId == 0) {
            /*
             * If there are no data stream typees yet and the data stream type
             * ID is 0, create a data stream type now. This is needed
             * because an event record type without an explicit
             * data stream type ID is an implicit 0, and there can
             * be one nonwritten data stream type which has the ID 0.
             */
            _pseudoTraceType.dataStreamTypes[0] = std::make_unique<PseudoDataStreamType>();
        } else {
            std::ostringstream ss;

            ss << "Event record type refers to a data stream type ID (" <<
                  dataStreamTypeId << ") that does not exist.";
            throw MetadataParseError {ss.str(), beginLocation};
        }
    }

    // get this pseudo data stream type
    auto& pseudoDataStreamType = _pseudoTraceType.dataStreamTypes[dataStreamTypeId];

    // check if the event record type exists
    if (pseudoDataStreamType->eventRecordTypes.find(id) !=
            std::end(pseudoDataStreamType->eventRecordTypes)) {
        std::ostringstream ss;

        ss << "Duplicate `event` block with ID " << id <<
              " and data stream type ID " << dataStreamTypeId << ".";
        throw MetadataParseError {ss.str(), beginLocation};
    }

    // build event record type object
    auto eventRecordType = std::make_unique<PseudoEventRecordType>();

    eventRecordType->id = id;
    eventRecordType->name = std::move(name);
    eventRecordType->logLevel = logLevel;
    eventRecordType->modelEmfUri = std::move(modelEmfUri);
    eventRecordType->contextType = std::move(eventContextType);
    eventRecordType->payloadType = std::move(eventPayloadType);

    // add to pseudo data stream type
    pseudoDataStreamType->eventRecordTypes[id] = std::move(eventRecordType);
    return true;
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseScopeDef(const _StackFrame::Kind scopeDefStackFrameKind,
                                                         const char * const firstName,
                                                         const char * const secondName,
                                                         const bool expect)
{
    StringScannerRejecter<CharIt> ssRejecter {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLocation = this->_curLocation();

    // parse name
    if (!_ss.scanToken(firstName)) {
        return nullptr;
    }

    try {
        if (secondName) {
            this->_expectToken(".");

            if (!_ss.scanToken(secondName)) {
                if (expect) {
                    std::ostringstream ss;

                    ss << "Expecting `" << secondName << "`.";
                    throw MetadataParseError {ss.str(), this->_curLocation()};
                }

                return nullptr;
            }
        }

        // parse `:=`
        this->_expectToken(":=");
        _ss.skipCommentsAndWhitespaces();

        const auto typeLocation = this->_curLocation();

        // parse type
        PseudoDataType::UP type;

        {
            _LexicalScope lexScope {*this, scopeDefStackFrameKind};

            type = this->_tryParseType();
        }

        if (!type) {
            throw MetadataParseError {
                "Expecting type or type alias name.",
                this->_curLocation()
            };
        }

        if (type->kind() != PseudoDataType::Kind::STRUCT) {
            throw MetadataParseError {
                "Expecting a structure type.",
                typeLocation
            };
        }

        // parse `;`
        this->_expectToken(";");
        ssRejecter.accept();
        return type;
    } catch (MetadataParseError& error) {
        std::string line;

        line = "In the `";
        line += firstName;

        if (secondName) {
            line += ".";
            line += secondName;
        }

        line += "` scope:";
        error._appendErrorMessage(line, beginLocation);
        throw;
    }
}

template <typename CharIt>
TsdlParserBase::_Attribute TsdlParser<CharIt>::_expectAttribute()
{
    _Attribute attr;

    // parse name
    CharIt begin, end;
    bool nameIsFound = false;

    _ss.skipCommentsAndWhitespaces();
    attr.nameLocation = this->_curLocation();

    if (_ss.scanToken(_MODEL_EMF_URI_ATTR)) {
        nameIsFound = true;
        attr.name = _MODEL_EMF_URI_ATTR;
    } else if (_ss.scanIdentifier(begin, end)) {
        nameIsFound = true;
        attr.name.assign(begin, end);
    }

    if (!nameIsFound) {
        throw MetadataParseError {
            "Expecting attribute name.", this->_curLocation()
        };
    }

    // parse `=`
    this->_expectToken("=");

    // this it the source location of the attribute for an eventual error
    _ss.skipCommentsAndWhitespaces();
    attr.valueLocation = this->_curLocation();

    // special case for the `map` attribute
    if (attr.name == "map") {
        attr.kind = _Attribute::Kind::CLOCK_NAME_VALUE;

        // parse `clock`
        this->_expectToken("clock");

        // parse `.`
        this->_expectToken(".");

        // parse clock type's name
        if (!_ss.scanIdentifier(begin, end)) {
            throw MetadataParseError {
                "Expecting C identifier (clock type's name).",
                this->_curLocation()
            };
        }

        attr.strValue.assign(begin, end);

        // parse `.`
        this->_expectToken(".");

        // parse `value`
        this->_expectToken("value");

        // parse `;`
        this->_expectToken(";");
        return attr;
    }

    if (_ss.scanLiteralString(begin, end)) {
        // literal string
        const auto escapedStr = TsdlParser::_escapeLiteralString(begin, end,
                                                                 attr.valueTextLocation());

        attr.strValue = escapedStr;
        attr.kind = _Attribute::Kind::STRING;
    } else if (_ss.scanIdentifier(begin, end)) {
        // identifier
        attr.strValue.assign(begin, end);
        attr.kind = _Attribute::Kind::IDENTIFIER;
    } else if (_ss.scanConstInt(attr.uintValue)) {
        // constant integer
        attr.kind = _Attribute::Kind::UINT;
    } else if (_ss.scanConstInt(attr.intValue)) {
        // constant integer
        attr.kind = _Attribute::Kind::INT;
        assert(attr.intValue != 0 && attr.intValue != 1);
    } else {
        throw MetadataParseError {
            "Expecting valid constant integer, literal string, or identifier.",
            this->_curLocation()
        };
    }

    // parse `;`
    this->_expectToken(";");
    return attr;
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseGetTypeAliasRef()
{
    CharIt begin, end;

    // try `enum`/`struct` followed by name
    _ss.save();

    if (_ss.scanIdentifier(begin, end)) {
        std::string kw(begin, end);

        if (kw == "enum" || kw == "struct") {
            if (_ss.scanIdentifier(begin, end)) {
                if (!_ss.scanToken("{") && !_ss.scanToken(":")) {
                    std::string aliasName = kw + ' ';

                    aliasName.append(begin, end);

                    // get from alias
                    auto type = this->_getAliasedType(aliasName);

                    if (type) {
                        _ss.accept();
                        return type;
                    }
                }
            }
        }
    }

    _ss.reject();

    // try `variant` followed by name, followed by optional tag name
    _ss.save();

    if (_ss.scanToken("variant")) {
        if (_ss.scanIdentifier(begin, end)) {
            std::string aliasName("variant ");

            aliasName.append(begin, end);

            // get from alias
            auto type = this->_getAliasedType(aliasName);

            if (!type || type->kind() != PseudoDataType::Kind::VARIANT) {
                _ss.reject();
                return nullptr;
            }

            auto& variantType = static_cast<PseudoVariantType&>(*type);

            if (!variantType.tagFieldRef.pathElements.empty()) {
                _ss.accept();
                return type;
            }

            if (_ss.scanToken("<")) {
                PseudoFieldRef pseudoFieldRef;

                _ss.skipCommentsAndWhitespaces();

                const auto tagLocation = this->_curLocation();

                this->_parseFieldRef(pseudoFieldRef, true);

                if (pseudoFieldRef.isEnv) {
                    throw MetadataParseError {
                        "Variant type's tag field reference cannot start with `env.`.",
                        tagLocation
                    };
                }

                this->_expectToken(">");

                if (!_ss.scanToken("{")) {
                    // create new pseudo variant type with this tag
                    auto newType = type->clone();
                    auto& newVarType = static_cast<PseudoVariantType&>(*newType);

                    newVarType.tagFieldRef = pseudoFieldRef;
                    _ss.accept();
                    return newType;
                }
            }
        }
    }

    _ss.reject();

    // try type alias name
    _ss.save();

    std::string aliasName;

    if (this->_parseTypeAliasName(aliasName, false)) {
        auto type = this->_getAliasedType(aliasName);

        if (type) {
            _ss.accept();
            return type;
        }
    }

    _ss.reject();
    return nullptr;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_parseTypeAliasName(std::string& aliasName,
                                             const bool expect)
{
    bool isMulti = false;
    VofS parts;

    while (true) {
        CharIt begin, end;
        StringScannerRejecter<CharIt> ssRejecter {_ss};

        _ss.skipCommentsAndWhitespaces();

        const auto location = this->_curLocation();

        if (!_ss.scanIdentifier(begin, end)) {
            ssRejecter.accept();
            break;
        }

        std::string part(begin, end);

        // disallow reserved words
        if (part == "integer" || part == "floating_point" || part == "enum" ||
                part == "string" || part == "struct" || part == "variant" ||
                part == "trace" || part == "stream" || part == "clock" ||
                part == "event" || part == "env") {
            if (expect) {
                std::ostringstream ss;

                ss << "Invalid keyword `" << part <<
                      "` in type alias's name.";
                throw MetadataParseError {ss.str(), location};
            } else {
                return false;
            }
        }

        if (part == "const" || part == "char" || part == "double" ||
                part == "float" || part == "int" || part == "long" ||
                part == "short" || part == "signed" || part == "unsigned" ||
                part == "void" || part == "_Bool" || part == "_Complex" ||
                part == "_Imaginary") {
            isMulti = true;
        } else {
            if (isMulti) {
                // this must be the end of the alias name
                break;
            }
        }

        ssRejecter.accept();
        parts.push_back(part);

        if (!isMulti) {
            // single word alias name: break now
            break;
        }
    }

    if (parts.empty()) {
        if (expect) {
            throw MetadataParseError {
                "Expecting type alias's name.",
                this->_curLocation()
            };
        } else {
            return false;
        }
    }

    aliasName.clear();

    for (auto it = std::begin(parts); it != std::end(parts); ++it) {
        aliasName += *it;

        if (std::distance(it, std::end(parts)) > 1) {
            aliasName += ' ';
        }
    }

    return true;
}

template <typename CharIt>
bool TsdlParser<CharIt>::_parseFieldRef(PseudoFieldRef& pseudoFieldRef,
                                        const bool expect)
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLocation = this->_curLocation();
    VofS allPathElements;

    while (true) {
        CharIt begin, end;

        if (!_ss.scanIdentifier(begin, end)) {
            break;
        }

        allPathElements.push_back({begin, end});

        if (!_ss.scanToken(".")) {
            break;
        }
    }

    if (allPathElements.empty()) {
        throw MetadataParseError {"Empty field reference.", beginLocation};
    }

    return this->_pseudoFieldRefFromAllPathElements(allPathElements,
                                                    beginLocation,
                                                    pseudoFieldRef,
                                                    expect);
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_tryParseFieldNameArraysSequences(std::string& fieldName,
                                                                         PseudoDataType::UP innerType)
{
    // parse name
    CharIt begin, end;

    if (!_ss.scanIdentifier(begin, end)) {
        return nullptr;
    }

    fieldName.assign(begin, end);
    return this->_parseArraySeqLengths(std::move(innerType));
}

template <typename CharIt>
PseudoDataType::UP TsdlParser<CharIt>::_parseArraySeqLengths(PseudoDataType::UP innerType)
{
    /*
     * A temporary array or sequence type length. If `isArrayType` is
     * true, then use `arrayLength` to build an array type. Otherwise
     * use `seqLengthFieldRef`.
     */
    struct PseudoArrayTypeOrSequenceTypeLength {
        PseudoFieldRef seqLengthFieldRef;
        Size arrayLength;
        bool isArrayType;
    };

    std::vector<PseudoArrayTypeOrSequenceTypeLength> lengths;

    while (true) {
        if (!_ss.scanToken("[")) {
            break;
        }

        _ss.skipCommentsAndWhitespaces();

        const auto lengthLocation = this->_curLocation();
        long long value;

        if (_ss.scanConstInt(value)) {
            if (value < 0) {
                std::ostringstream ss;

                ss << "Array type's length cannot be negative: " << value << ".";
                throw MetadataParseError {ss.str(), lengthLocation};
            }

            lengths.push_back({{}, static_cast<Size>(value), true});
        } else {
            PseudoFieldRef pseudoFieldRef;

            try {
                this->_parseFieldRef(pseudoFieldRef, true);
            } catch (MetadataParseError& error) {
                error._appendErrorMessage("Expecting valid constant integer (array type) or valid field reference (sequence type):", lengthLocation);
                throw;
            }

            if (pseudoFieldRef.isEnv) {
                // only the `env.NAME` format is accepted
                if (pseudoFieldRef.pathElements.size() != 1) {
                    throw MetadataParseError {
                        "Invalid environment reference: expecting `env.NAME`, "
                        "where NAME is the name of an existing environment entry.",
                        lengthLocation
                    };
                }

                const auto& envName = pseudoFieldRef.pathElements[0];

                // find the value in the current environment
                if (!_pseudoTraceType.env) {
                    std::ostringstream ss;

                    ss << "Array type is refering to the environment entry `" <<
                          envName << "`, but no environment is defined at this point.";
                    throw MetadataParseError {ss.str(), lengthLocation};
                }

                if (!_pseudoTraceType.env->hasEntry(envName)) {
                    std::ostringstream ss;

                    ss << "Cannot find environment entry `" << envName << "`.";
                    throw MetadataParseError {ss.str(), lengthLocation};
                }

                auto& entry = (*_pseudoTraceType.env)[envName];

                if (const auto entryValue = boost::get<long long>(&entry)) {
                    if (*entryValue < 0) {
                        std::ostringstream ss;

                        ss << "Array type cannot have a negative size: " <<
                              *entryValue << ".";
                        throw MetadataParseError {ss.str(), lengthLocation};
                    }

                    lengths.push_back({
                        PseudoFieldRef {},
                        static_cast<Size>(*entryValue),
                        true
                    });
                } else {
                    std::ostringstream ss;

                    ss << "Environment entry `" << envName <<
                          "` is not a valid array type's size.";
                    throw MetadataParseError {ss.str(), lengthLocation};
                }
            } else {
                lengths.push_back({pseudoFieldRef, 0, false});
            }
        }

        this->_expectToken("]");
    }

    for (const auto& length : lengths) {
        if (length.isArrayType) {
            innerType = std::make_unique<PseudoArrayType>(length.arrayLength,
                                                          std::move(innerType));
        } else {
            innerType = std::make_unique<PseudoSequenceType>(length.seqLengthFieldRef,
                                                             std::move(innerType));
        }
    }

    return innerType;
}

template <typename CharIt>
template <typename EnumTypeT, typename PseudoMemberT>
PseudoDataType::UP TsdlParser<CharIt>::_finishParseEnumType(const DataType& intType,
                                                            const MetadataTextLocation& beginLocation,
                                                            const bool addAlias,
                                                            const std::string& potAliasName)
{
    // parse members (we're after `{`)
    std::unordered_map<std::string, PseudoMemberT> pseudoMembers;
    typename EnumTypeT::Value curVal = 0;

    while (true) {
        CharIt begin, end;
        std::string name;

        _ss.skipCommentsAndWhitespaces();

        MutableMetadataTextLocation location {this->_curLocation()};

        if (_ss.scanIdentifier(begin, end)) {
            name.assign(begin, end);
        } else if (_ss.scanLiteralString(begin, end)) {
            name = TsdlParser::_escapeLiteralString(begin, end,
                                                    location.location());
        } else {
            throw MetadataParseError {
                "Expecting member name (identifier or literal string).",
                location.location()
            };
        }

        auto lower = curVal;
        auto upper = curVal;

        if (_ss.scanToken("=")) {
            _ss.skipCommentsAndWhitespaces();
            location = this->_curLocation();

            typename EnumTypeT::Value value;

            if (!_ss.scanConstInt(value)) {
                if (std::is_signed<typename EnumTypeT::Value>::value) {
                    throw MetadataParseError {
                        "Expecting valid constant signed integer.",
                        this->_curLocation()
                    };
                } else {
                    throw MetadataParseError {
                        "Expecting valid constant unsigned integer.",
                        this->_curLocation()
                    };
                }
            }

            lower = static_cast<typename EnumTypeT::Value>(value);
            upper = lower;
            curVal = lower;

            if (_ss.scanToken("...")) {
                if (!_ss.scanConstInt(value)) {
                    throw MetadataParseError {
                        "Expecting valid constant integer.", this->_curLocation()
                    };
                }

                upper = static_cast<typename EnumTypeT::Value>(value);
                curVal = upper;
            }
        }

        ++curVal;

        // insert range into pseudo member (create if it does not exist)
        if (pseudoMembers.find(name) == pseudoMembers.end()) {
            pseudoMembers[name] = PseudoMemberT {};
        }

        try {
            pseudoMembers[name].ranges.insert(typename EnumTypeT::Range {lower, upper});
        } catch (const InvalidMetadata& ex) {
            MetadataParseError error {ex.what(), location.location()};
            std::ostringstream ss;

            ss << "Invalid range in enumeration type member `" <<
                  name << "`:";
            error._appendErrorMessage(ss.str(), location.location());
            throw error;
        }

        const bool gotComma = _ss.scanToken(",");

        // end of members?
        if (_ss.scanToken("}")) {
            break;
        }

        if (!gotComma) {
            throw MetadataParseError {
                "Expecting `,` or `}`.",
                this->_curLocation()
            };
        }
    }

    auto& undIntType = static_cast<const IntType&>(intType);
    typename EnumTypeT::Members members;

    try {
        for (const auto& namePseudoMemberPair : pseudoMembers) {
            members[namePseudoMemberPair.first] = typename EnumTypeT::Member {
                namePseudoMemberPair.second.ranges
            };
        }
    } catch (const InvalidMetadata& ex) {
        MetadataParseError error {ex.what(), beginLocation};

        error._appendErrorMessage("Invalid enumeration type's member:",
                                  beginLocation);
        throw error;
    }

    // validate enumeration type members
    try {
        // create enumeration type
        DataType::UP enumTypeUp = std::make_unique<const EnumTypeT>(
            undIntType.alignment(), undIntType.size(), undIntType.byteOrder(),
            undIntType.displayBase(), undIntType.encoding(),
            undIntType.mappedClockTypeName(), members
        );
        auto pseudoEnumTypeUp = std::make_unique<PseudoScalarTypeWrapper>(std::move(enumTypeUp));

        // add type alias if this enumeration type has a name
        if (addAlias && !potAliasName.empty()) {
            this->_addTypeAlias(potAliasName, *pseudoEnumTypeUp,
                                this->_curLocation());
        }

        return pseudoEnumTypeUp;
    } catch (const InvalidMetadata& ex) {
        MetadataParseError error {ex.what(), beginLocation};

        error._appendErrorMessage("Invalid enumeration type:",
                                  beginLocation);
        throw error;
    }
}

template <typename CharIt>
bool TsdlParser<CharIt>::_tryParseNamedDataTypeOrTypeAlias(PseudoNamedDataTypes& entries)
{
    /*
     * Here are the possible situations:
     *
     * 1. Explicit type alias:
     *
     *        typealias integer {
     *            size = 23;
     *            align = 8;
     *        } := hello;
     *
     * 2. Enumeration type alias:
     *
     *        enum my_enum : some_int {
     *            ...
     *        };
     *
     * 3. Structure type alias:
     *
     *        struct something {
     *            ...
     *        } align(16);
     *
     * 4. Variant type alias:
     *
     *        variant option {
     *            ...
     *        };
     *
     *        variant <event.fields.my.tag> option {
     *            ...
     *        };
     *
     * 5. Field using an enumeration type alias:
     *
     *        enum state my_state;
     *        enum state my_state[2];
     *
     * 6. Field using a structure type alias:
     *
     *        struct payload my_payload;
     *        struct payload my_payload[stuff.length];
     *
     * 7. Field using a variant type alias with an explicit tag:
     *
     *        variant option <my.tag> my_variant;
     *        variant option <my.tag> my_variant[2][lol];
     *
     * 8. Field using explicit type:
     *
     *        integer {
     *            size = 23;
     *            align = 16;
     *        } my_field[17];
     *
     * 9. Field using explicit type alias:
     *
     *        my_type my_field;
     *        my_type my_field[9];
     *
     * We want to try situations 5, 6, 7, and 9 first because otherwise
     * it can be ambiguous when parsing a variant type:
     *
     *     a) variant var_name <tag> field_name;
     *     b) variant var_name <tag> { ... };
     *     c) variant var_name { ... };
     *     d) variant var_name <tag> { ... } field_name;
     *     e) variant <tag> { ... } field_name;
     *
     * Here, b), c), and d) are invalid because we're creating a type
     * alias (named variant) and using a relative tag at the same time
     * (not supported). a) has a relative tag, but we're using an
     * aliased variant type named `var_name` which should already exist
     * at this point: this is why we try it first.
     */

    // try situations 5, 6, 7, and 9 first
    this->_skipCommentsAndWhitespacesAndSemicolons();
    _ss.save();

    const auto typeSrcLocation = this->_curLocation();
    auto type = this->_tryParseGetTypeAliasRef();

    if (type) {
        // let's try parsing a field name
        std::string fieldName;
        auto realType = this->_tryParseFieldNameArraysSequences(fieldName, std::move(type));

        if (realType) {
            // we have a winner: variant must have a tag by now
            if (TsdlParser::_isVariantTypeUntaggedRec(*realType)) {
                throw MetadataParseError {
                    "Variant type needs a tag here.", typeSrcLocation
                };
            }

            auto fieldUp = std::make_unique<PseudoNamedDataType>(fieldName,
                                                                 std::move(realType));

            entries.push_back(std::move(fieldUp));
            this->_expectToken(";");
            _ss.accept();
            this->_stackTop().fieldNames.push_back(fieldName);
            return true;
        }
    }

    _ss.reject();

    // try type alias (situations 1, 2, 3, 4)
    _ss.save();

    if (this->_tryParseTypeAlias()) {
        _ss.accept();
        return true;
    }

    _ss.reject();

    // try full type (situations 8)
    _ss.save();

    type = this->_tryParseFullType();

    if (type) {
        // let's try parsing a field name
        std::string fieldName;
        auto realType = this->_tryParseFieldNameArraysSequences(fieldName, std::move(type));

        if (realType) {
            // we have a winner: variant must have a tag by now
            if (TsdlParser::_isVariantTypeUntaggedRec(*realType)) {
                throw MetadataParseError {
                    "Variant type needs a tag here.", this->_curLocation()
                };
            }

            auto fieldUp = std::make_unique<PseudoNamedDataType>(fieldName,
                                                                 std::move(realType));

            entries.push_back(std::move(fieldUp));
            this->_expectToken(";");
            _ss.accept();
            this->_stackTop().fieldNames.push_back(fieldName);
            return true;
        } else {
            /*
             * If there's a type, but no field name, and we know that
             * it's not a type alias, then we expect a field name at
             * this point.
             */
            _ss.skipCommentsAndWhitespaces();
            throw MetadataParseError {
                "Expecting field or choice name.",
                this->_curLocation()
            };
        }
    }

    _ss.reject();
    return false;
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_TSDL_PARSER_HPP
