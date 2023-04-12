/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_TSDL_TSDL_PARSER_HPP
#define _YACTFR_INTERNAL_METADATA_TSDL_TSDL_PARSER_HPP

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

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/metadata/nt-str-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/struct-member-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/var-type-opt.hpp>
#include <yactfr/metadata/data-loc.hpp>
#include <yactfr/metadata/trace-env.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/text-parse-error.hpp>

#include "tsdl-attr.hpp"
#include "../pseudo-types.hpp"
#include "../pseudo-dt-utils.hpp"
#include "../str-scanner.hpp"

namespace yactfr {
namespace internal {

/*
 * TSDL metadata stream parser.
 *
 * This parser parses a CTF 1 (TSDL) metadata string and then contains:
 *
 * * A corresponding trace type object.
 * * A corresponding trace environment object.
 *
 * Parsing methods which return `bool` can backtrack: if they return
 * `false`, then the state of the parser is as it was when calling them.
 */
class TsdlParser final
{
public:
    /*
     * Builds a metadata parser, wrapping a string between `begin`
     * (included) and `end` (excluded), and parses it.
     *
     * You can release the resulting trace type from this parser with
     * releaseTraceType() and get the trace environment with traceEnv().
     *
     * Throws `TextParseError` when there was a parsing error.
     */
    explicit TsdlParser(const char *begin, const char *end);

    /*
     * Releases and returns the parsed trace type.
     */
    TraceType::UP releaseTraceType()
    {
        return std::move(_traceType);
    }

    /*
     * Returns the UUID of the metadata stream which, for CTF 1.8, is
     * the trace UID as a UUID canonical textual representation.
     */
    const boost::optional<boost::uuids::uuid> metadataStreamUuid() const noexcept;

private:
    /*
     * One frame of the parser context stack.
     *
     * Each frame has:
     *
     * * A kind, which indicates what kind of frame/scope this
     *   represents.
     *
     * * A map of data type alias names to full pseudo data types, local
     *   to the frame. Frames which are higher in the stack have access
     *   to the aliased data types of the frames below them.
     *
     * * A vector of the current member/option names, when the kind of
     *   this frame is `STRUCT_TYPE` or `VAR_TYPE`. This is used to
     *   ensure that a relative data location doesn't target a data type
     *   which is located outside the topmost data type alias frame.
     *
     *   Even if CTF 1.8 officially supports this feature, yactfr
     *   doesn't.
     *
     * You can use _stackPush() and _stackPop() manually, but it's
     * recommended to use an RAII `_LexicalScope` instead to
     * automatically push and pop scopes and avoid errors.
     */
    struct _StackFrame final
    {
        enum class Kind
        {
            // root
            ROOT,

            // trace type
            TRACE_TYPE,

            // packet header type
            PKT_HEADER_TYPE,

            // data stream type
            DST,

            // packet context type
            PKT_CTX_TYPE,

            // event record header type
            ER_HEADER_TYPE,

            // event record common context type
            ER_COMMON_CTX_TYPE,

            // event record type
            ERT,

            // event record specific context type
            ER_SPEC_CTX_TYPE,

            // event record payload type
            ER_PAYLOAD_TYPE,

            // data type alias
            DT_ALIAS,

            // structure type
            STRUCT_TYPE,

            // variant type
            VAR_TYPE,
        };

        explicit _StackFrame(Kind kind);

        // kind of this frame
        const Kind kind;

        // data type aliases of this frame
        std::unordered_map<std::string, PseudoDt::UP> dtAliases;

        // identifiers of this frame so far (member/option names)
        std::vector<std::string> idents;
    };

    /*
     * RAII class to automatically manage lexical scopes.
     *
     * The constructor of a `_LexicalScope` instance expects a TSDL
     * parser reference. The RAII object automatically calls
     * _stackPush() and _stackPop() on said parser.
     */
    class _LexicalScope final :
        private boost::noncopyable
    {
    public:
        _LexicalScope() noexcept :
            _parser {nullptr},
            _frameKind {_StackFrame::Kind::ROOT}
        {
        }

        explicit _LexicalScope(TsdlParser& mp, const _StackFrame::Kind frameKind) :
            _parser {&mp},
            _frameKind {frameKind}
        {
            _parser->_stackPush(frameKind);
        }

        ~_LexicalScope()
        {
            this->exit();
        }

        void operator=(const _LexicalScope& lexicalScope)
        {
            this->exit();
            _parser = lexicalScope._parser;
            _frameKind = lexicalScope._frameKind;
            _parser->_stackPush(_frameKind);
        }

        void exit()
        {
            if (_parser) {
                _parser->_stackPop();
            }

            _parser = nullptr;
        }

    private:
        TsdlParser *_parser;
        TsdlParser::_StackFrame::Kind _frameKind;
    };

    using _Attrs = std::vector<TsdlAttr>;

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
        const char *begin;
        const char *end;
        PseudoDt::UP pseudoDt;
    };

private:
    /*
     * Parses the whole metadata string, creating the resulting trace
     * type and trace environment on success, throwing `TextParseError`
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
     * If `expect` is true, then the method throws `TextParseError` if
     * it cannot parse the scope data type successfully. Otherwise, the
     * method can return `nullptr` if it cannot parse the scope data
     * type.
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
                                  const char *firstName, const char *secondName = nullptr,
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
     * If `expect` is true, then the method throws `TextParseError` if
     * it fails to parse a data type alias name. Otherwise, returns
     * whether or not a data type alias name was parsed.
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
     * Expects the specific token `token`, throwing `TextParseError` if
     * not found.
     */
    void _expectToken(const char *token);

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
     * Tries to parse a trace environment block and sets the trace
     * environment of the current pseudo trace type accordingly.
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

    /*
     * Inserts a clone of the pseudo fixed-length integer type
     * `pseudoIntType` having the corresponding TSDL string from `begin`
     * (inclusive) to `end` (exclusive) into the fast pseudo
     * fixed-length integer type cache.
     */
    void _insertFastPseudoFlIntType(const char *begin, const char *end,
                                    const PseudoDt& pseudoIntType);

    void _skipCommentsAndWhitespacesAndSemicolons();
    const std::string *_tryScanLitStr();
    void _addDtAlias(std::string&& name, const PseudoDt& pseudoDt);

    Index _at() const
    {
        return _ss.at() - _ss.begin();
    }

    /*
     * Creates the yactfr trace type from the pseudo trace type.
     */
    void _createTraceType();

    /*
     * Pushes a new frame of kind `kind` to the lexical scope stack.
     */
    void _stackPush(_StackFrame::Kind kind);

    /*
     * Pops from the lexical scope stack.
     */
    void _stackPop();

    /*
     * Returns the top frame of the lexical scope stack.
     */
    _StackFrame& _stackTop()
    {
        assert(!_stack.empty());
        return _stack.back();
    }

    /*
     * Tries to return a pseudo data location from from the absolute
     * data location path elements `allPathElems`, returning
     * `boost::none` if it can't.
     */
    boost::optional<PseudoDataLoc> _pseudoDataLocFromAbsAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                                     const TextLocation& loc);

    /*
     * Tries to return a pseudo data location from the relative data
     * location path elements `allPathElems`, returning `boost::none` if
     * it can't.
     */
    boost::optional<PseudoDataLoc> _pseudoDataLocFromRelAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                                     const TextLocation& loc);

    /*
     * Returns a pseudo data location from the absolute or relative data
     * location path elements `allPathElems`, thowing on error.
     */
    PseudoDataLoc _pseudoDataLocFromAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                 const TextLocation& loc);

    /*
     * Returns whether or not a pseudo data stream type currently exists
     * with the ID `id`.
     */
    bool _pseudoDstExists(const TypeId id) const
    {
        assert(_pseudoTraceType);
        return _pseudoTraceType->pseudoDsts().find(id) != _pseudoTraceType->pseudoDsts().end();
    }

    /*
     * Returns a _cloned_ pseudo data type corresponding to a data type
     * alias name within the context of the current frame.
     */
    PseudoDt::UP _aliasedPseudoDt(const std::string& name, TextLocation loc) const;

    /*
     * Calls the other _addDtAlias() with the current frame.
     */
    void _addDtAlias(std::string&& name, const PseudoDt& pseudoDt, const TextLocation& curLoc);

    /*
     * Adds a data type alias named `name` to the register of the
     * specific stack frame `frame`, cloning `pseudoDt`.
     */
    void _addDtAlias(std::string&& name, const PseudoDt& pseudoDt, const TextLocation& curLoc,
                     _StackFrame& frame);

    /*
     * Returns the current native byte order, or a random one if
     * not available.
     *
     * Returning a random one only happens when we didn't reach the
     * `trace` block yet, which means all the data types we create will
     * blow up anyway because we'll call PseudoTraceType::clear() when
     * reaching said block.
     *
     * We just need at least something because
     * FixedLengthIntegerType::FixedLengthIntegerType() expects a
     * concrete byte order. What could be done in the future is to avoid
     * creating pseudo types until we reach the `trace` block and reset.
     */
    ByteOrder _absNativeBo() const noexcept
    {
        return _nativeBo ? *_nativeBo : ByteOrder::LITTLE;
    }

    /*
     * Checks for duplicate named data types in `entries` (by name),
     * throwing `TextParseError` if any is found.
     */
    static void _checkDupPseudoNamedDt(const PseudoNamedDts& entries, const TextLocation& loc);

    /*
     * Returns whether or not `pseudoDt` is recursively a variant type
     * (passing through array types) _without_ a selector data location.
     */
    static bool _isPseudoVarTypeWithoutSelLocRec(const PseudoDt& pseudoDt);

    /*
     * Throws that the attribute named `name` is missing at location
     * `loc`.
     */
    [[ noreturn ]] static void _throwMissingAttr(const std::string& name, const TextLocation& loc);

    /*
     * Checks for duplicate attributes in `attrs`, throwing
     * `TextParseError` if any is found.
     */
    static void _checkDupAttr(const _Attrs& attrs);

    /*
     * Returns a UUID object from the canonical textual representation
     * `str`, or `boost::none` if the conversion fails for any reason.
     */
    static boost::optional<boost::uuids::uuid> _uuidFromStr(const std::string& str);

    template <typename FlEnumTypeT>
    void _validateFlEnumTypeMapping(Size len, const TextLocation& loc, const std::string& name,
                                    const typename FlEnumTypeT::RangeSet& ranges) const;

    template <typename FlEnumTypeT>
    void _validateFlEnumTypeMappings(Size len, const TextLocation& loc,
                                     const typename FlEnumTypeT::Mappings& mappings) const;

    /*
     * Sets an implicit mapped clock type name for specific pseudo
     * fixed-length unsigned integer types named `memberTypeName` within
     * `basePseudoDt`.
     */
    void _setImplicitMappedClkTypeName(PseudoDt& basePseudoDt, const std::string& memberTypeName);

    /*
     * Sets an implicit mapped clock type name for specific pseudo
     * fixed-length unsigned integer types.
     */
    void _setImplicitMappedClkTypeName();

    /*
     * Add the role `role` to all pseudo fixed-length unsigned integer
     * types named `name` within `basePseudoDt`.
     */
    template <bool OnlyIfMappedClkTypeName = false>
    void _addPseudoFlUIntTypeRoles(PseudoDt& basePseudoDt, const std::string& name,
                                   UnsignedIntegerTypeRole role);

    void _addPseudoFlUIntTypeDefClkTsRole(PseudoDt& basePseudoDt, const std::string& name);

    /*
     * Sets the "has metadata stream UUID role" property of all pseudo
     * static-length array types named `name` within `basePseudoDt`.
     */
    void _setPseudoSlArrayTypeMetadataStreamUuidRole(PseudoDt& basePseudoDt,
                                                     const std::string& name);

    /*
     * Adds roles to pseudo data types.
     */
    void _addPseudoDtRoles();

    /*
     * Set default clock type of the pseudo data stream type
     * `pseudoDst`.
     */
    void _setPseudoDstDefClkType(PseudoDst& pseudoDst);

    /*
     * Set default clock type of pseudo data stream types.
     */
    void _setPseudoDstDefClkType();

private:
    static constexpr Size _MAX_FAST_FL_INT_TYPE_STR_SIZE = 256;

private:
    // underlying string scanner
    StrScanner _ss;

    // cache of TSDL substrings to pseudo fixed-length integer types
    std::vector<_FastPseudoFlIntTypeEntry> _fastPseudoFlIntTypes;

    // final trace type
    TraceType::UP _traceType;

    // current native byte order
    boost::optional<ByteOrder> _nativeBo;

    // current pseudo trace type
    boost::optional<PseudoTraceType> _pseudoTraceType;

    // whether or not an `env` block was parsed
    bool _envParsed = false;

    // lexical scope stack
    std::vector<_StackFrame> _stack;
};

template <typename FlEnumTypeT, typename CreatePseudoDtFuncT>
PseudoDt::UP TsdlParser::_finishParseFlEnumType(PseudoDt::UP pseudoDt, const bool addDtAlias,
                                                std::string&& potDtAliasName,
                                                CreatePseudoDtFuncT&& createPseudoDtFunc)
{
    // parse mappings (we're after `{`)
    std::unordered_map<std::string, std::set<typename FlEnumTypeT::RangeSet::Range>> pseudoMappings;
    typename FlEnumTypeT::RangeSet::Value curVal = 0;

    while (true) {
        std::string name;

        _ss.skipCommentsAndWhitespaces();

        boost::optional<TextLocation> loc {_ss.loc()};

        if (const auto ident = _ss.tryScanIdent()) {
            name = *ident;
        } else if (const auto escapedStr = this->_tryScanLitStr()) {
            name = *escapedStr;
        } else {
            throwTextParseError("Expecting mapping name (identifier or literal string).", *loc);
        }

        auto lower = curVal;
        auto upper = curVal;

        if (_ss.tryScanToken("=")) {
            using Val = decltype(curVal);

            _ss.skipCommentsAndWhitespaces();
            loc = _ss.loc();

            auto val = _ss.template tryScanConstInt<Val>();

            if (!val) {
                if (std::is_signed<Val>::value) {
                    throwTextParseError("Expecting valid constant signed integer.",
                                        _ss.loc());
                } else {
                    throwTextParseError("Expecting valid constant unsigned integer.",
                                        _ss.loc());
                }
            }

            lower = *val;
            upper = lower;
            curVal = lower;

            if (_ss.tryScanToken("...")) {
                val = _ss.template tryScanConstInt<Val>();

                if (!val) {
                    throwTextParseError("Expecting valid constant integer.", _ss.loc());
                }

                upper = *val;
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
            throwTextParseError(ss.str(), *loc);
        }

        pseudoMappings[name].insert(typename FlEnumTypeT::RangeSet::Range {lower, upper});

        const bool gotComma = _ss.tryScanToken(",");

        // end of member types?
        if (_ss.tryScanToken("}")) {
            break;
        }

        if (!gotComma) {
            throwTextParseError("Expecting `,` or `}`.", _ss.loc());
        }
    }

    if (pseudoMappings.empty()) {
        throwTextParseError("Expecting at least one mapping.", pseudoDt->loc());
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

template <typename FlEnumTypeT>
void TsdlParser::_validateFlEnumTypeMapping(const Size len, const TextLocation& loc,
                                            const std::string& name,
                                            const typename FlEnumTypeT::RangeSet& ranges) const
{
    using Value = typename FlEnumTypeT::RangeSet::Value;

    const auto lenUnitSuffix = (len == 1) ? "" : "s";

    for (auto& range : ranges) {
        // validate range storage length
        Value minLower, maxUpper;

        if (std::is_signed<Value>::value) {
            if (len < 63) {
                minLower = -(1LL << (len - 1));
                maxUpper = (1LL << (len - 1)) - 1;
            } else {
                minLower = std::numeric_limits<Value>::min();
                maxUpper = std::numeric_limits<Value>::max();
            }
        } else {
            minLower = std::numeric_limits<Value>::min();

            if (len < 64) {
                maxUpper = (1ULL << len) - 1;
            } else {
                maxUpper = std::numeric_limits<Value>::max();
            }
        }

        if (range.lower() < minLower || range.upper() > maxUpper) {
            std::ostringstream ss;

            ss << "In mapping `" << name << "` of enumeration type: "
                  "at least one value of the range [" << range.lower() <<
                  ", " << range.upper() <<
                  "] doesn't fit the range [" << minLower << ", " << maxUpper << "] "
                  "(with a length of " << len << " bit" << lenUnitSuffix << ").";
            throwTextParseError(ss.str(), loc);
        }
    }
}

template <typename FlEnumTypeT>
void TsdlParser::_validateFlEnumTypeMappings(const Size len, const TextLocation& loc,
                                             const typename FlEnumTypeT::Mappings& mappings) const
{
    assert(len > 0);
    assert(len <= 64);

    if (mappings.empty()) {
        throwTextParseError("Fixed-length enumeration type has no mappings.", loc);
    }

    for (const auto& nameRangesPair : mappings) {
        this->_validateFlEnumTypeMapping<FlEnumTypeT>(len, loc, nameRangesPair.first,
                                                      nameRangesPair.second);
    }
}

template <bool OnlyIfMappedClkTypeName>
void TsdlParser::_addPseudoFlUIntTypeRoles(PseudoDt& basePseudoDt,
                                           const std::string& memberTypeName,
                                           const UnsignedIntegerTypeRole role)
{
    for (auto& pseudoDt : findPseudoUIntTypesByName(basePseudoDt, memberTypeName)) {
        assert(pseudoDt->isFlUInt());
        auto& pseudoIntType = static_cast<PseudoFlUIntType&>(*pseudoDt);

        if (OnlyIfMappedClkTypeName && !pseudoIntType.mappedClkTypeName()) {
            continue;
        }

        pseudoIntType.addRole(role);
    }
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_TSDL_TSDL_PARSER_HPP
