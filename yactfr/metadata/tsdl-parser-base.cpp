/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>
#include <tuple>
#include <set>

#include <yactfr/text-loc.hpp>
#include <yactfr/metadata/internal/tsdl-attr.hpp>
#include <yactfr/metadata/internal/tsdl-parser-base.hpp>
#include <yactfr/metadata/internal/trace-type-from-pseudo-trace-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/dyn-array-type.hpp>
#include <yactfr/metadata/dyn-text-array-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/metadata-parse-error.hpp>
#include <yactfr/internal/utils.hpp>

namespace yactfr {
namespace internal {

const char * const TsdlParserBase::_EMF_URI_ATTR_NAME = "model.emf.uri";

struct TsMemberQuirkProcessor
{
    explicit TsMemberQuirkProcessor(std::unordered_set<std::string> memberNames,
                                    PseudoTraceType& pseudoTraceType, PseudoDt& rootDt) :
        _memberNames {std::move(memberNames)},
        _pseudoTraceType {&pseudoTraceType}
    {
        this->_process(rootDt);
    }

private:
    void _process(PseudoDt& pseudoDt)
    {
        switch (pseudoDt.kind()) {
        case PseudoDt::Kind::INT_TYPE_WRAPPER:
            this->_process(static_cast<PseudoIntTypeWrapper&>(pseudoDt));
            break;

        case PseudoDt::Kind::STATIC_ARRAY:
            this->_process(static_cast<PseudoStaticArrayType&>(pseudoDt));
            break;

        case PseudoDt::Kind::DYN_ARRAY:
            this->_process(static_cast<PseudoDynArrayType&>(pseudoDt));
            break;

        case PseudoDt::Kind::STRUCT:
            this->_process(static_cast<PseudoStructType&>(pseudoDt));
            break;

        case PseudoDt::Kind::VAR:
            this->_process(static_cast<PseudoVarType&>(pseudoDt));
            break;

        default:
            return;
        }
    }

    void _process(PseudoIntTypeWrapper& pseudoDt)
    {
        if (!_curIdent) {
            // non-structure or non-variant type root?
            return;
        }

        auto doProcess = false;

        for (const auto& memberName : _memberNames) {
            if (memberName == *_curIdent) {
                doProcess = true;
                break;
            }

            // also check the display name
            if (!_curIdent->empty() && (*_curIdent)[0] == '_' &&
                    _curIdent->compare(1, _curIdent->size() - 1, memberName) == 0) {
                doProcess = true;
                break;
            }
        }

        if (!doProcess) {
            return;
        }

        if (pseudoDt.mappedClkTypeName()) {
            return;
        }

        if (_pseudoTraceType->clkTypes().empty()) {
            // create implicit 1-GHz clock type
            _pseudoTraceType->clkTypes().insert(std::make_unique<const ClockType>(1'000'000'000ULL));
        }

        if (_pseudoTraceType->clkTypes().size() != 1) {
            // we don't know which clock type to choose: leave it unmapped
            return;
        }

        const auto& clkType = *_pseudoTraceType->clkTypes().begin();

        assert(clkType->name());
        pseudoDt.mappedClkTypeName(*clkType->name());
    }

    void _process(PseudoStaticArrayType& pseudoDt) {
        this->_process(pseudoDt.pseudoElemType());
    }

    void _process(PseudoDynArrayType& pseudoDt) {
        this->_process(pseudoDt.pseudoElemType());
    }

    void _process(PseudoStructType& pseudoDt) {
        for (auto& pseudoMemberType : pseudoDt.pseudoMemberTypes()) {
            _curIdent = &pseudoMemberType->name();
            this->_process(pseudoMemberType->pseudoDt());
        }
    }

    void _process(PseudoVarType& pseudoDt) {
        for (auto& pseudoOpt : pseudoDt.pseudoOpts()) {
            this->_process(pseudoOpt->pseudoDt());
        }
    }

private:
    const std::unordered_set<std::string> _memberNames;
    PseudoTraceType *_pseudoTraceType;
    const std::string *_curIdent = nullptr;
};

TsdlParserBase::_StackFrame::_StackFrame(const Kind kind) :
    kind {kind}
{
}

void TsdlParserBase::_applyQuirks()
{
    /*
     * For all the timestamp pseudo member types in pseudo event record
     * type headers and packet context types, if it doesn't have a
     * mapped clock type name, then:
     *
     * If there's exactly one clock type:
     *     Use the name of this clock type.
     *
     * If there's no clock type:
     *     Create a default 1-GHz clock type named `default` and use
     *     this name.
     *
     * If there's more than one clock type:
     *     Leave it as is (no mapped clock type name).
     */
    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        if (pseudoDst->pseudoErHeaderType()) {
            TsMemberQuirkProcessor {
                {"timestamp"}, *_pseudoTraceType, *pseudoDst->pseudoErHeaderType()
            };
        }

        if (pseudoDst->pseudoPktCtxType()) {
            TsMemberQuirkProcessor {
                {"timestamp_begin", "timestamp_end"},
                *_pseudoTraceType, *pseudoDst->pseudoPktCtxType()
            };
        }
    }
}

void TsdlParserBase::_stackPush(const _StackFrame::Kind kind)
{
    _stack.push_back(_StackFrame {kind});
}

void TsdlParserBase::_stackPop()
{
    assert(!_stack.empty());
    _stack.pop_back();
}

void TsdlParserBase::_createTraceType()
{
    /*
     * Create default pseudo data stream type if there's at least one
     * orphan pseudo event record type for the DST ID 0 _and_ there's no
     * pseudo data stream types.
     */
    const auto it = _pseudoTraceType->pseudoOrphanErts().find(0);

    if (it != _pseudoTraceType->pseudoOrphanErts().end() && !it->second.empty() &&
            _pseudoTraceType->pseudoDsts().empty()) {
        _pseudoTraceType->pseudoDsts()[0] = std::make_unique<PseudoDst>();
    }

    // create yactfr trace type
    _traceType = traceTypeFromPseudoTraceType(*_pseudoTraceType);
}

void TsdlParserBase::_checkDupPseudoNamedDt(const PseudoNamedDts& entries, const TextLocation& loc)
{
    std::set<std::string> entryNames;

    for (const auto& entry : entries) {
        if (entryNames.find(entry->name()) != entryNames.end()) {
            std::ostringstream ss;

            ss << "Duplicate identifier (member type or option name) `" << entry->name() << "`.";
            throw MetadataParseError {ss.str(), loc};
        }

        entryNames.insert(entry->name());
    }
}

bool TsdlParserBase::_isPseudoVarTypeWithoutSelLocRec(const PseudoDt& pseudoDt)
{
    if (pseudoDt.kind() == PseudoDt::Kind::STATIC_ARRAY ||
            pseudoDt.kind() == PseudoDt::Kind::DYN_ARRAY) {
        auto& pseudoArrayType = static_cast<const PseudoArrayType&>(pseudoDt);

        return TsdlParserBase::_isPseudoVarTypeWithoutSelLocRec(pseudoArrayType.pseudoElemType());
    }

    if (pseudoDt.kind() != PseudoDt::Kind::VAR) {
        return false;
    }

    auto& pseudoVarType = static_cast<const PseudoVarType&>(pseudoDt);

    return !pseudoVarType.pseudoSelLoc().has_value();
}

void TsdlParserBase::_checkDupAttr(const _Attrs& attrs)
{
    std::set<std::string> attrSet;

    for (const auto& attr : attrs) {
        if (attrSet.find(attr.name) != attrSet.end()) {
            std::ostringstream ss;

            ss << "Duplicate attribute `" << attr.name << "`.";
            throw MetadataParseError {ss.str(), attr.nameTextLoc()};
        }

        attrSet.insert(attr.name);
    }
}

void TsdlParserBase::_throwMissingAttr(const std::string& name, const TextLocation& loc)
{
    std::ostringstream ss;

    ss << "Missing attribute `" << name << "`.";
    throw MetadataParseError {ss.str(), loc};
}

boost::optional<boost::uuids::uuid> TsdlParserBase::_uuidFromStr(const std::string& str)
{
    try {
        return boost::uuids::string_generator {}(str);
    } catch (const std::runtime_error&) {
        return boost::none;
    }
}

boost::optional<PseudoDataLoc> TsdlParserBase::_pseudoDataLocFromAbsAllPathElems(const DataLocation::PathElements& allPathElems,
                                                                                 const TextLocation& loc)
{
    bool isAbs = false;
    bool isEnv = false;
    Scope scope;
    DataLocation::PathElements pathElems;
    auto restPos = allPathElems.begin();

    if (allPathElems.size() >= 3) {
        if (allPathElems[0] == "trace") {
            if (allPathElems[1] == "packet") {
                if (allPathElems[2] == "header") {
                    scope = Scope::PACKET_HEADER;
                    isAbs = true;
                }
            }

            if (!isAbs) {
                throw MetadataParseError {"Expecting `packet.header` after `trace.`.", loc};
            }
        } else if (allPathElems[0] == "stream") {
            if (allPathElems[1] == "packet") {
                if (allPathElems[2] == "context") {
                    scope = Scope::PACKET_CONTEXT;
                    isAbs = true;
                }
            } else if (allPathElems[1] == "event") {
                if (allPathElems[2] == "header") {
                    scope = Scope::EVENT_RECORD_HEADER;
                    isAbs = true;
                } else if (allPathElems[2] == "context") {
                    scope = Scope::EVENT_RECORD_COMMON_CONTEXT;
                    isAbs = true;
                }
            }

            if (!isAbs) {
                throw MetadataParseError {
                    "Expecting `packet.context`, `event.header`, or "
                    "`event.context` after `stream.`.",
                    loc
                };
            }
        }

        if (isAbs) {
            restPos = allPathElems.begin() + 3;
        }
    }

    if (!isAbs && allPathElems.size() >= 2) {
        if (allPathElems[0] == "event") {
            if (allPathElems[1] == "context") {
                scope = Scope::EVENT_RECORD_SPECIFIC_CONTEXT;
                isAbs = true;
            } else if (allPathElems[1] == "fields") {
                scope = Scope::EVENT_RECORD_PAYLOAD;
                isAbs = true;
            }

            if (!isAbs) {
                throw MetadataParseError {
                    "Expecting `context` or `fields` after `event.`.",
                    loc
                };
            }
        }

        if (isAbs) {
            restPos = allPathElems.begin() + 2;
        }
    }

    if (!isAbs && allPathElems.size() >= 1 && allPathElems[0] == "env") {
        isAbs = true;
        isEnv = true;
        restPos = allPathElems.begin() + 1;
    }

    if (!isAbs) {
        return boost::none;
    }

    /*
     * Data location is already absolute: skip the root scope part (or
     * `env`) to create the path elements.
     */
    std::copy(restPos, allPathElems.end(), std::back_inserter(pathElems));

    return PseudoDataLoc {isEnv, isAbs, scope, std::move(pathElems), loc};
}

boost::optional<PseudoDataLoc> TsdlParserBase::_pseudoDataLocFromRelAllPathElems(const DataLocation::PathElements& allPathElems,
                                                                                 const TextLocation& loc)
{
    /*
     * In this method, we only want to make sure that the relative data
     * location doesn't target a datum which is outside the topmost data
     * type alias scope, if any, within the current stack.
     *
     * For example, this is okay:
     *
     *     typealias struct {
     *         int a;
     *         struct {
     *             string seq[a];
     *         } b;
     *     } := some_name;
     *
     * This isn't (it _should_, in fact, but it's not supported as of
     * this version of yactfr):
     *
     *     typealias struct {
     *         my_int a;
     *
     *         typealias struct {
     *             string seq[a];
     *         } := my_struct;
     *
     *         struct {
     *             int a;
     *             my_struct b;
     *         };
     *     } := some_name;
     *
     * In this last example, the location of the length data type for
     * the dynamic array type `seq[a]` contained in `my_struct b` is NOT
     * `int a` immediately before, but rather `my_int a`. In practice,
     * this trick of using a data type which is external to a data type
     * alias for dynamic array type lengths or variant type selectors is
     * rarely, if ever, used.
     *
     * So this is easy to detect, because each time this parser "enters"
     * a data type alias (with the `typealias` keyword or with a named
     * structure/variant type), it pushes a data type alias frame onto
     * the stack. We just need to check if we can find the first path
     * element within the identifiers of the stack frames, from top to
     * bottom, until we reach a data type alias or the root frame (both
     * lead to an exception).
     */
    assert(!_stack.empty());
    assert(!allPathElems.empty());

    // find position of first path element in stack from top to bottom
    auto stackIt = _stack.cend() - 1;
    const auto& firstPathElem = allPathElems.front();

    while (true) {
        if (stackIt->kind == _StackFrame::Kind::DT_ALIAS) {
            std::ostringstream ss;

            ss << "First element of data location, `" <<
                  firstPathElem << "`, refers to an identifier which crosses a "
                  "data type alias (or named structure/variant type) boundary. "
                  "CTF 1.8 allows this, but this version of yactfr doesn't "
                  "support it.";
            throw MetadataParseError {ss.str(), loc};
        } else if (stackIt->kind == _StackFrame::Kind::STRUCT_TYPE) {
            const auto& frameIdents = stackIt->idents;

            if (std::find(frameIdents.begin(), frameIdents.end(), firstPathElem) != frameIdents.end()) {
                // identifier found in this frame: win!
                return PseudoDataLoc {false, false, Scope::PACKET_HEADER, allPathElems, loc};
            }
        }

        // identifier isn't in this frame: try next (lower) stack frame
        if (stackIt == _stack.cbegin()) {
            // no more frames: not found
            std::ostringstream ss;

            ss << "Invalid relative data location (`";

            for (auto it = allPathElems.begin(); it != allPathElems.end(); ++it) {
                ss << *it;

                if (it != allPathElems.end() - 1) {
                    ss << ".";
                }
            }

            ss << "`): cannot find `" << firstPathElem << "` (first element).";
            throw MetadataParseError {ss.str(), loc};
        }

        --stackIt;
    }

    return boost::none;
}

PseudoDataLoc TsdlParserBase::_pseudoDataLocFromAllPathElems(const DataLocation::PathElements& allPathElems,
                                                             const TextLocation& loc)
{
    assert(!allPathElems.empty());

    auto pseudoDataLoc = this->_pseudoDataLocFromAbsAllPathElems(allPathElems, loc);

    if (pseudoDataLoc) {
        return *pseudoDataLoc;
    }

    pseudoDataLoc = this->_pseudoDataLocFromRelAllPathElems(allPathElems, loc);

    if (pseudoDataLoc) {
        return *pseudoDataLoc;
    }

    throw MetadataParseError {"Invalid data location.", loc};
}

void TsdlParserBase::_addDtAlias(std::string&& name, const PseudoDt& pseudoDt,
                                 const TextLocation& curLoc, _StackFrame& frame)
{
    assert(!name.empty());

    /*
     * Check for existing data type alias with this name. We only check
     * in the top frame of the lexical scope stack because a data type
     * alias with a given name can shadow a deeper one with the same
     * name in TSDL.
     */
    if (frame.dtAliases.find(name) != frame.dtAliases.end()) {
        std::ostringstream ss;

        ss << "Duplicate data type alias: `" << name << "`.";
        throw MetadataParseError {ss.str(), curLoc};
    }

    // add alias
    frame.dtAliases[std::move(name)] = pseudoDt.clone();
}

void TsdlParserBase::_addDtAlias(std::string&& name, const PseudoDt& pseudoDt,
                                 const TextLocation& curLoc)
{
    this->_addDtAlias(std::move(name), pseudoDt, curLoc, this->_stackTop());
}

PseudoDt::UP TsdlParserBase::_aliasedPseudoDt(const std::string& name, TextLocation loc) const
{
    for (auto it = _stack.crbegin(); it != _stack.crend(); ++it) {
        const auto& frame = *it;
        const auto findIt = frame.dtAliases.find(name);

        if (findIt == frame.dtAliases.end()) {
            continue;
        }

        auto dt = findIt->second->clone();

        dt->loc(std::move(loc));
        return dt;
    }

    return nullptr;
}

} // namespace internal
} // namespace yactfr
