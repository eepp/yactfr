/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_TSDL_PARSER_BASE_HPP
#define _YACTFR_METADATA_INTERNAL_TSDL_PARSER_BASE_HPP

#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>
#include <cassert>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/utility.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../../aliases.hpp"
#include "../../trace-env.hpp"
#include "../trace-type.hpp"
#include "../data-loc.hpp"
#include "../dst.hpp"
#include "../ert.hpp"
#include "../enum-type.hpp"
#include "../int-range.hpp"
#include "../aliases.hpp"
#include "../metadata-parse-error.hpp"
#include "str-scanner.hpp"
#include "pseudo-types.hpp"
#include "data-loc-map.hpp"

namespace yactfr {

template <typename ParserCharIt>
std::pair<TraceType::UP, TraceEnvironment> fromMetadataText(ParserCharIt, ParserCharIt);

namespace internal {

/*
 * TSDL metadata stream parser base.
 *
 * Everything in this base class doesn't depend on the type of the
 * iterator used in the templated `TsdlParser` class, but is still
 * accessible by any version of the concrete parser.
 */
class TsdlParserBase :
    boost::noncopyable
{
    template <typename ParserCharIt>
    friend std::pair<TraceType::UP, TraceEnvironment> yactfr::fromMetadataText(ParserCharIt,
                                                                               ParserCharIt);

public:
    /*
     * Releases and returns the parsed trace type.
     */
    TraceType::UP releaseTraceType()
    {
        return std::move(_traceType);
    }

    /*
     * Returns the parsed trace environment.
     */
    TraceEnvironment traceEnv()
    {
        if (_traceEnv) {
            return *_traceEnv;
        }

        return TraceEnvironment {};
    }

protected:
    TsdlParserBase() = default;

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

        explicit _LexicalScope(TsdlParserBase& mp, const _StackFrame::Kind frameKind) :
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
        TsdlParserBase *_parser;
        TsdlParserBase::_StackFrame::Kind _frameKind;
    };

    using _Attrs = std::vector<TsdlAttr>;

protected:
    /*
     * Applies various TSDL-specific metadata quirks.
     */
    void _applyQuirks();

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
    boost::optional<PseudoDataLoc> _pseudoDataLocFromAbsAllPathElems(const DataLocation::PathElements& allPathElems,
                                                                     const TextLocation& loc);

    /*
     * Tries to return a pseudo data location from the relative data
     * location path elements `allPathElems`, returning `boost::none` if
     * it can't.
     */
    boost::optional<PseudoDataLoc> _pseudoDataLocFromRelAllPathElems(const DataLocation::PathElements& allPathElems,
                                                                     const TextLocation& loc);

    /*
     * Returns a pseudo data location from the absolute or relative data
     * location path elements `allPathElems`, thowing on error.
     */
    PseudoDataLoc _pseudoDataLocFromAllPathElems(const DataLocation::PathElements& allPathElems,
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
     * IntegerType::IntegerType() expects a concrete byte order. What
     * could be done in the future is to avoid creating pseudo types
     * until we reach the `trace` block and reset.
     */
    ByteOrder _absNativeBo() const noexcept
    {
        return _nativeBo ? *_nativeBo : ByteOrder::LITTLE;
    }

    /*
     * Checks for duplicate named data types in `entries` (by name),
     * throwing an error if any is found.
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
    static void _throwMissingAttr(const std::string& name, const TextLocation& loc);

    /*
     * Checks for duplicate attributes in `attrs`, throwing an error if
     * any is found.
     */
    static void _checkDupAttr(const _Attrs& attrs);

    /*
     * Returns a UUID object from the canonical textual representation
     * `str`, or `boost::none` if the conversion fails for any reason.
     */
    static boost::optional<boost::uuids::uuid> _uuidFromStr(const std::string& str);

    template <typename EnumTypeT>
    void _validateEnumTypeMapping(const PseudoIntTypeWrapper& pseudoIntType,
                                  const std::string& name,
                                  const typename EnumTypeT::RangeSet& ranges) const;

    template <typename EnumTypeT>
    void _validateEnumTypeMappings(const PseudoIntTypeWrapper& pseudoIntType,
                                   const typename EnumTypeT::Mappings& mappings) const;

protected:
    static const char * const _EMF_URI_ATTR_NAME;
    static constexpr Size _MAX_FAST_INT_FT_STR_SIZE = 256;

protected:
    // final trace type
    TraceType::UP _traceType;

    // final trace environment
    boost::optional<TraceEnvironment> _traceEnv;

    // current native byte order
    boost::optional<ByteOrder> _nativeBo;

    // current pseudo trace type
    boost::optional<PseudoTraceType> _pseudoTraceType;

    // lexical scope stack
    std::vector<_StackFrame> _stack;
};


template <typename EnumTypeT>
void TsdlParserBase::_validateEnumTypeMapping(const PseudoIntTypeWrapper& pseudoIntType,
                                              const std::string& name,
                                              const typename EnumTypeT::RangeSet& ranges) const
{
    using Value = typename EnumTypeT::RangeSet::Value;

    const auto len = pseudoIntType.intType().length();
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
                  "] don't fit the range [" << minLower << ", " << maxUpper << "] "
                  "(with a length of " << len << " bit" << lenUnitSuffix << ").";
            throw MetadataParseError {ss.str(), pseudoIntType.loc()};
        }
    }
}

template <typename EnumTypeT>
void TsdlParserBase::_validateEnumTypeMappings(const PseudoIntTypeWrapper& pseudoIntType,
                                               const typename EnumTypeT::Mappings& mappings) const
{
    assert(pseudoIntType.intType().length() > 0);
    assert(pseudoIntType.intType().length() <= 64);

    if (mappings.empty()) {
        throw MetadataParseError {"Enumeration type has no mappings.", pseudoIntType.loc()};
    }

    for (const auto& nameRangesPair : mappings) {
        this->_validateEnumTypeMapping<EnumTypeT>(pseudoIntType, nameRangesPair.first,
                                                  nameRangesPair.second);
    }
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_TSDL_PARSER_BASE_HPP
