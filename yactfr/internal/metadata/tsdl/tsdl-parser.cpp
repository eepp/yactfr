/*
 * SPDX-FileCopyrightText: 2015-2026 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <iostream>
#include <sstream>
#include <functional>
#include <limits>
#include <variant>
#include <type_traits>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/nt-str-type.hpp>

#include "tsdl-parser.hpp"
#include "../trace-type-from-pseudo-trace-type.hpp"
#include "../../utils.hpp"

namespace yactfr::internal {
namespace {

/*
 * Calls `func()` and returns its result, appending an error context
 * message at the text location `loc` to any thrown `TextParseError`.
 *
 * `msg` is either the message or a function which returns it: use the
 * latter to only build the message on error.
 */
template <typename MsgT, typename FuncT>
auto withErrCtx(const TextLocation& loc, MsgT&& msg, FuncT&& func) -> decltype(func())
{
    try {
        return func();
    } catch (TextParseError& exc) {
        if constexpr (std::is_invocable_v<MsgT>) {
            appendMsgToTextParseError(exc, msg(), loc);
        } else {
            appendMsgToTextParseError(exc, std::string {msg}, loc);
        }

        throw;
    }
}

} // namespace

TsdlParser::_tStackFrame::_tStackFrame(const Kind kind, const Index lexId) :
    kind {kind},
    lexId {lexId}
{
}

void TsdlParser::_setImplicitMappedClkTypeId(PseudoDt& basePseudoDt,
                                             const std::string& memberTypeName)
{
    /*
     * If there's exactly one clock type in the pseudo trace type:
     *     Use the internal ID of this clock type.
     *
     * If there's no clock type in the pseudo trace type:
     *     Create a default 1-GHz clock type and use its internal
     *     ID (`default`).
     *
     * If there's more than one clock type in the pseudo trace type:
     *     Leave it as is (no mapped clock type internal ID).
     */
    for (auto& pseudoDt : findPseudoUIntTypesByName(basePseudoDt, memberTypeName)) {
        assert(pseudoDt->isFlUInt() && pseudoDt->kind() != PseudoDt::Kind::ScalarDtWrapper);

        auto& pseudoIntType = static_cast<PseudoFlUIntType&>(*pseudoDt);

        if (pseudoIntType.mappedClkTypeId()) {
            continue;
        }

        if (_pseudoTraceType->clkTypes().empty()) {
            // create implicit 1-GHz clock type
            static const std::string defStr {"default"};

            _pseudoTraceType->clkTypes().insert(ClockType::create(defStr, std::nullopt, std::nullopt,
                                                                  std::nullopt, std::nullopt,
                                                                  1'000'000'000ULL,
                                                                  std::nullopt, std::nullopt,
                                                                  std::nullopt, std::nullopt,
                                                                  ClockOffset {}));
        }

        if (_pseudoTraceType->clkTypes().size() != 1) {
            // we don't know which clock type to choose: leave it unmapped
            continue;
        }

        const auto& clkType = *_pseudoTraceType->clkTypes().begin();

        assert(clkType->internalId());
        pseudoIntType.mappedClkTypeId(*clkType->internalId());
    }
}

void TsdlParser::_setImplicitMappedClkTypeId()
{
    for (auto& [id, pseudoDst] : _pseudoTraceType->pseudoDsts()) {
        if (pseudoDst->pseudoErHeaderType()) {
            this->_setImplicitMappedClkTypeId(*pseudoDst->pseudoErHeaderType(), "timestamp");
        }

        if (pseudoDst->pseudoPktCtxType()) {
            this->_setImplicitMappedClkTypeId(*pseudoDst->pseudoPktCtxType(), "timestamp_begin");
            this->_setImplicitMappedClkTypeId(*pseudoDst->pseudoPktCtxType(), "timestamp_end");
        }
    }
}

void TsdlParser::_setPseudoSlArrayTypeMetadataStreamUuidRole(PseudoDt& basePseudoDt,
                                                             const std::string& memberTypeName)
{
    const auto pseudoDts = findPseudoDtsByName(basePseudoDt, memberTypeName,
                                               [](auto& pseudoDt) {
        if (pseudoDt.kind() != PseudoDt::Kind::SlArray) {
            return false;
        }

        auto& pseudoArrayType = static_cast<const PseudoSlArrayType&>(pseudoDt);

        if (pseudoArrayType.len() != 16) {
            return false;
        }

        if (!pseudoArrayType.pseudoElemType().isUInt()) {
            return false;
        }

        assert(pseudoArrayType.pseudoElemType().isFlUInt() &&
               pseudoArrayType.pseudoElemType().kind() != PseudoDt::Kind::ScalarDtWrapper);

        {
            auto& pseudoElemDt = static_cast<const PseudoFlUIntType&>(pseudoArrayType.pseudoElemType());

            if (pseudoElemDt.len() != 8) {
                return false;
            }

            if (pseudoElemDt.align() != 8) {
                return false;
            }
        }

        return true;
    });

    for (auto& pseudoDt : pseudoDts) {
        auto& pseudoArrayType = static_cast<PseudoSlArrayType&>(*pseudoDt);

        pseudoArrayType.hasMetadataStreamUuidRole(true);
    }
}

namespace {

/*
 * Pseudo data type visitor which recursively visits the elements of
 * array types, the member types of structure types, and the options of
 * variant types.
 *
 * Override visit(PseudoFlUIntType&) to visit the pseudo fixed-length
 * unsigned integer types.
 */
class RecPseudoDtVisitor :
    public PseudoDtVisitor
{
protected:
    explicit RecPseudoDtVisitor() = default;

public:
    void visit(PseudoSlArrayType& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(PseudoDlArrayType& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(PseudoStructType& pseudoDt) override
    {
        for (const auto& pseudoMemberType : pseudoDt.pseudoMemberTypes()) {
            pseudoMemberType->pseudoDt().accept(*this);
        }
    }

    void visit(PseudoVarType& pseudoDt) override
    {
        for (const auto& pseudoOpt : pseudoDt.pseudoOpts()) {
            pseudoOpt->pseudoDt().accept(*this);
        }
    }

private:
    void _visit(PseudoArrayType& pseudoDt)
    {
        pseudoDt.pseudoElemType().accept(*this);
    }
};

class DefClkTsRoleAdder final :
    public RecPseudoDtVisitor
{
public:
    explicit DefClkTsRoleAdder() = default;

    using RecPseudoDtVisitor::visit;

    void visit(PseudoFlUIntType& pseudoDt) override
    {
        if (pseudoDt.mappedClkTypeId() &&
                !pseudoDt.hasRole(UnsignedIntegerTypeRole::PacketEndDefaultClockTimestamp)) {
            pseudoDt.addRole(UnsignedIntegerTypeRole::DefaultClockTimestamp);
        }
    }
};

} // namespace

void TsdlParser::_addPseudoDtRoles()
{
    /*
     * First, set an implicit mapped clock type internal ID on specific
     * pseudo fixed-length unsigned integer types.
     *
     * For example, if the current pseudo trace type contains a single
     * clock type, then any pseudo fixed-length unsigned integer type
     * named `timestamp` within pseudo event record header types, which
     * are not already mapped to a clock type, are mapped to this single
     * clock type.
     */
    this->_setImplicitMappedClkTypeId();

    // add/set simple roles
    if (_pseudoTraceType->pseudoPktHeaderType()) {
        this->_addPseudoFlUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(), "magic",
                                        UnsignedIntegerTypeRole::PacketMagicNumber);
        this->_addPseudoFlUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(), "stream_id",
                                        UnsignedIntegerTypeRole::DataStreamTypeId);
        this->_addPseudoFlUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(),
                                        "stream_instance_id",
                                        UnsignedIntegerTypeRole::DataStreamId);
        this->_setPseudoSlArrayTypeMetadataStreamUuidRole(*_pseudoTraceType->pseudoPktHeaderType(),
                                                          "uuid");
    }

    for (auto& [id, pseudoDst] : _pseudoTraceType->pseudoDsts()) {
        if (pseudoDst->pseudoPktCtxType()) {
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_size",
                                            UnsignedIntegerTypeRole::PacketTotalLength);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "content_size",
                                            UnsignedIntegerTypeRole::PacketContentLength);
            this->_addPseudoFlUIntTypeRoles<true>(*pseudoDst->pseudoPktCtxType(), "timestamp_end",
                                                  UnsignedIntegerTypeRole::PacketEndDefaultClockTimestamp);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "events_discarded",
                                            UnsignedIntegerTypeRole::DiscardedEventRecordCounterSnapshot);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_seq_num",
                                            UnsignedIntegerTypeRole::PacketSequenceNumber);
        }

        if (pseudoDst->pseudoErHeaderType()) {
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoErHeaderType(), "id",
                                            UnsignedIntegerTypeRole::EventRecordTypeId);
        }
    }

    // add "default clock timestamp" role
    DefClkTsRoleAdder visitor;

    for (auto& [id, pseudoDst] : _pseudoTraceType->pseudoDsts()) {
        if (pseudoDst->pseudoPktCtxType()) {
            pseudoDst->pseudoPktCtxType()->accept(visitor);
        }

        if (pseudoDst->pseudoErHeaderType()) {
            pseudoDst->pseudoErHeaderType()->accept(visitor);
        }
    }
}

namespace {

class PseudoDstDefClkTypeSetter final :
    public RecPseudoDtVisitor
{
public:
    explicit PseudoDstDefClkTypeSetter(PseudoTraceType& pseudoTraceType, PseudoDst& pseudoDst) :
        _pseudoTraceType {&pseudoTraceType},
        _pseudoDst {&pseudoDst}
    {
    }

    using RecPseudoDtVisitor::visit;

    void visit(PseudoFlUIntType& pseudoDt) override
    {
        if (pseudoDt.mappedClkTypeId()) {
            if (!_clkTypeId) {
                _clkTypeId = &*pseudoDt.mappedClkTypeId();
            }

            if (*pseudoDt.mappedClkTypeId() != *_clkTypeId) {
                std::ostringstream ss;

                ss << "Unsigned fixed-length integer type is mapped to a clock type (`" <<
                      *pseudoDt.mappedClkTypeId() << "`) which is "
                      "different than another mapped clock type (`" <<
                      *_clkTypeId << "`) within the same data stream type.";
                throwTextParseError(ss.str(), pseudoDt.loc());
            }

            if (!_pseudoDst->defClkType()) {
                for (auto& clkType : _pseudoTraceType->clkTypes()) {
                    assert(clkType->internalId());

                    if (*clkType->internalId() == *_clkTypeId) {
                        _pseudoDst->defClkType(*clkType);
                    }
                }

                if (!_pseudoDst->defClkType()) {
                    // not found
                    std::ostringstream ss;

                    ss << "`" << *_clkTypeId << "` doesn't identify an existing clock type.";
                    throwTextParseError(ss.str(), pseudoDt.loc());
                }
            }
        }
    }

private:
    PseudoTraceType * const _pseudoTraceType;
    PseudoDst * const _pseudoDst;
    const std::string *_clkTypeId = nullptr;
};

} // namespace

void TsdlParser::_setPseudoDstDefClkType(PseudoDst& pseudoDst)
{
    PseudoDstDefClkTypeSetter visitor {*_pseudoTraceType, pseudoDst};

    withErrCtx(pseudoDst.loc(), [&pseudoDst] {
        std::ostringstream ss;

        ss << "In the data stream type with ID " << pseudoDst.id() << ":";
        return ss.str();
    }, [&pseudoDst, &visitor] {
        if (const auto pseudoPktCtxType = pseudoDst.pseudoPktCtxType()) {
            withErrCtx(pseudoPktCtxType->loc(), "In the packet context type:", [&] {
                pseudoPktCtxType->accept(visitor);
            });
        }

        if (const auto pseudoErHeaderType = pseudoDst.pseudoErHeaderType()) {
            withErrCtx(pseudoErHeaderType->loc(), "In the event record header type:", [&] {
                pseudoErHeaderType->accept(visitor);
            });
        }
    });
}

void TsdlParser::_setPseudoDstDefClkType()
{
    for (auto& [id, pseudoDst] : _pseudoTraceType->pseudoDsts()) {
        this->_setPseudoDstDefClkType(*pseudoDst);
    }
}

void TsdlParser::_stackPush(const _tStackFrame::Kind kind)
{
    _stack.push_back(_tStackFrame {kind, _nextLexId});
    ++_nextLexId;
}

void TsdlParser::_stackPop()
{
    assert(!_stack.empty());
    _stack.pop_back();
}

void TsdlParser::_createTraceType()
{
    /*
     * Create default pseudo data stream type if there's at least one
     * orphan pseudo event record type for the DST ID 0 _and_ there's no
     * pseudo data stream types.
     */
    {
        const auto it = _pseudoTraceType->pseudoOrphanErts().find(0);

        if (it != _pseudoTraceType->pseudoOrphanErts().end() && !it->second.empty() &&
                _pseudoTraceType->pseudoDsts().empty()) {
            _pseudoTraceType->pseudoDsts()[0] = std::make_unique<PseudoDst>();
        }
    }

    // add roles to specific pseudo data types
    this->_addPseudoDtRoles();

    // set default clock type of pseudo data stream types
    this->_setPseudoDstDefClkType();

    // create yactfr trace type
    _traceType = traceTypeFromPseudoTraceType(*_pseudoTraceType);
}

void TsdlParser::_checkDupPseudoNamedDt(const PseudoNamedDts& entries, const TextLocation& loc)
{
    std::set<std::string> entryNames;

    for (const auto& entry : entries) {
        assert(entry->name());

        if (!entryNames.insert(*entry->name()).second) {
            std::ostringstream ss;

            ss << "Duplicate identifier (member type or option name) `" << *entry->name() << "`.";
            throwTextParseError(ss.str(), loc);
        }
    }
}

bool TsdlParser::_isPseudoVarTypeWithoutSelLocRec(const PseudoDt& pseudoDt)
{
    if (pseudoDt.kind() == PseudoDt::Kind::SlArray ||
            pseudoDt.kind() == PseudoDt::Kind::DlArray) {
        return TsdlParser::_isPseudoVarTypeWithoutSelLocRec(static_cast<const PseudoArrayType&>(pseudoDt).pseudoElemType());
    }

    if (pseudoDt.kind() != PseudoDt::Kind::Var) {
        return false;
    }

    return !static_cast<const PseudoVarType&>(pseudoDt).pseudoSelLoc().has_value();
}

void TsdlParser::_checkDupAttr(const _tAttrs& attrs)
{
    std::set<std::string> attrSet;

    for (const auto& attr : attrs) {
        if (!attrSet.insert(attr.name).second) {
            std::ostringstream ss;

            ss << "Duplicate attribute `" << attr.name << "`.";
            throwTextParseError(ss.str(), attr.nameTextLoc());
        }
    }
}

void TsdlParser::_throwMissingAttr(const std::string& name, const TextLocation& loc)
{
    std::ostringstream ss;

    ss << "Missing attribute `" << name << "`.";
    throwTextParseError(ss.str(), loc);
}

std::optional<boost::uuids::uuid> TsdlParser::_uuidFromStr(const std::string& str)
{
    try {
        return boost::uuids::string_generator {}(str);
    } catch (const std::runtime_error&) {
        return std::nullopt;
    }
}

namespace {

struct PseudoDataLocBase
{
    explicit PseudoDataLocBase(PseudoDataLoc::Kind kind,
                               const PseudoDataLoc::PathElems::const_iterator restPos) :
        kind {std::move(kind)},
        restPos {restPos}
    {
    }

    PseudoDataLoc::Kind kind;
    PseudoDataLoc::PathElems::const_iterator restPos;
};

/*
 * Root scope prefix of an absolute data location.
 */
struct RootScopePrefix final
{
    // first path element
    std::string_view firstElem;

    // remaining path elements (`thirdElem` is empty if none)
    std::string_view secondElem;
    std::string_view thirdElem;

    // corresponding scope
    Scope scope;
};

constexpr RootScopePrefix rootScopePrefixes[] = {
    {"trace",  "packet",  "header",  Scope::PacketHeader},
    {"stream", "packet",  "context", Scope::PacketContext},
    {"stream", "event",   "header",  Scope::EventRecordHeader},
    {"stream", "event",   "context", Scope::EventRecordCommonContext},
    {"event",  "context", {},        Scope::EventRecordSpecificContext},
    {"event",  "fields",  {},        Scope::EventRecordPayload},
};

/*
 * Throws that the root scope prefix of the data location at `loc`,
 * which starts with `firstElem`, is invalid.
 */
[[ noreturn ]] void throwInvalidRootScopePrefix(const std::string_view firstElem,
                                                const TextLocation& loc)
{
    std::vector<std::string> expected;

    for (auto& prefix : rootScopePrefixes) {
        if (prefix.firstElem != firstElem) {
            continue;
        }

        std::string str {"`"};

        str += prefix.secondElem;

        if (!prefix.thirdElem.empty()) {
            str += '.';
            str += prefix.thirdElem;
        }

        expected.push_back(str + '`');
    }

    assert(!expected.empty());

    std::ostringstream ss;

    ss << "Expecting ";

    for (auto i = 0U; i < expected.size(); ++i) {
        if (i > 0) {
            if (expected.size() > 2) {
                ss << ',';
            }

            ss << ' ';

            if (i == expected.size() - 1) {
                ss << "or ";
            }
        }

        ss << expected[i];
    }

    ss << " after `" << firstElem << ".`.";
    throwTextParseError(ss.str(), loc);
}

/*
 * Returns the base (kind and position of the remaining path elements)
 * of the data location `allPathElems`, or `std::nullopt` if it's a
 * relative data location.
 *
 * Throws if the data location starts with `trace.`, `stream.`, or
 * `event.`, but not with a valid root scope prefix.
 */
std::optional<PseudoDataLocBase> pseudoDataLocBase(const PseudoDataLoc::PathElems& allPathElems,
                                                   const TextLocation& loc)
{
    assert(!allPathElems.empty());

    const auto beginPos = allPathElems.begin();
    const auto& firstElem = *allPathElems[0];

    if (firstElem == "env") {
        return PseudoDataLocBase {PseudoDataLoc::Env {}, beginPos + 1};
    }

    if (allPathElems.size() < 2) {
        // single identifier: relative data location
        return std::nullopt;
    }

    auto firstElemIsRootScopeName = false;

    for (const auto& prefix : rootScopePrefixes) {
        if (prefix.firstElem != firstElem) {
            continue;
        }

        firstElemIsRootScopeName = true;

        if (*allPathElems[1] != prefix.secondElem) {
            continue;
        }

        if (prefix.thirdElem.empty()) {
            return PseudoDataLocBase {PseudoDataLoc::Abs {prefix.scope}, beginPos + 2};
        }

        if (allPathElems.size() >= 3 && *allPathElems[2] == prefix.thirdElem) {
            return PseudoDataLocBase {PseudoDataLoc::Abs {prefix.scope}, beginPos + 3};
        }
    }

    if (firstElemIsRootScopeName) {
        throwInvalidRootScopePrefix(firstElem, loc);
    }

    return std::nullopt;
}

/*
 * Returns the data location path elements `pathElems` joined with `.`.
 */
std::string pathElemsStr(const PseudoDataLoc::PathElems& pathElems)
{
    std::string str;

    for (const auto& pathElem : pathElems) {
        if (!str.empty()) {
            str += '.';
        }

        str += *pathElem;
    }

    return str;
}

} // namespace

std::optional<PseudoDataLoc> TsdlParser::_pseudoDataLocFromAbsAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                                             const TextLocation& loc)
{
    const auto psDataLocBase = pseudoDataLocBase(allPathElems, loc);

    if (!psDataLocBase) {
        return std::nullopt;
    }

    if (!std::holds_alternative<PseudoDataLoc::Env>(psDataLocBase->kind) &&
            psDataLocBase->restPos == allPathElems.end()) {
        std::ostringstream ss;

        ss << "Expecting a field name after `" << pathElemsStr(allPathElems) << "`.";
        throwTextParseError(ss.str(), loc);
    }

    /*
     * Data location is already absolute: skip the root scope part (or
     * `env`) to create the path elements.
     */
    PseudoDataLoc::PathElems pathElems;

    std::copy(psDataLocBase->restPos, allPathElems.end(), std::back_inserter(pathElems));

    return PseudoDataLoc {psDataLocBase->kind, std::move(pathElems), loc};
}

PseudoDataLoc TsdlParser::_pseudoDataLocFromRelAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                             const TextLocation& loc)
{
    /*
     * A CTF 1.8 relative data location is relative to where the TSDL
     * text defines it, NOT to where the data type containing it ends up
     * once data type aliases are expanded.
     *
     * For example:
     *
     *     fields := struct {
     *         int len;
     *
     *         typealias struct {
     *             string seq[len];
     *         } := my_struct;
     *
     *         struct {
     *             int len;
     *             my_struct a;
     *         } b;
     *     };
     *
     * Here, the length of `fields.b.a.seq` is `fields.len`,
     * NOT `fields.b.len`.
     *
     * Therefore, this method finds the first path element within the
     * identifiers of the `StructType` stack frames, from top to bottom,
     * crossing any data type alias frame. The identifiers of a
     * `StructType` frame are the names of the member types which
     * precede the data location.
     *
     * The returned pseudo data location refers to the lexical ID of the
     * frame which contains the first path element: this is also the
     * lexical ID of the pseudo structure type which the TSDL parser
     * creates from this frame, as well as of all its clones (data type
     * alias expansions). setPseudoDtDataLoc() later uses this lexical
     * ID to find the right ancestor structure type.
     */
    assert(!_stack.empty());
    assert(!allPathElems.empty());

    // find position of first path element in stack from top to bottom
    auto stackIt = _stack.cend() - 1;
    const auto& firstPathElem = *allPathElems.front();

    while (true) {
        if (stackIt->kind == _tStackFrame::Kind::StructType) {
            const auto& frameIdents = stackIt->idents;

            if (std::find(frameIdents.begin(), frameIdents.end(), firstPathElem) != frameIdents.end()) {
                // identifier found in this frame: win!
                return PseudoDataLoc {
                    PseudoDataLoc::Rel1 {stackIt->lexId}, allPathElems, loc
                };
            }
        }

        // identifier isn't in this frame: try next (lower) stack frame
        if (stackIt == _stack.cbegin()) {
            // no more frames: not found
            std::ostringstream ss;

            ss << "Invalid relative data location (`" << pathElemsStr(allPathElems) <<
                  "`): cannot find `" << firstPathElem << "` (first element).";
            throwTextParseError(ss.str(), loc);
        }

        --stackIt;
    }
}

PseudoDataLoc TsdlParser::_pseudoDataLocFromAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                         const TextLocation& loc)
{
    assert(!allPathElems.empty());

    if (const auto pseudoDataLoc = this->_pseudoDataLocFromAbsAllPathElems(allPathElems, loc)) {
        return *pseudoDataLoc;
    }

    return this->_pseudoDataLocFromRelAllPathElems(allPathElems, loc);
}

void TsdlParser::_addDtAlias(std::string&& name, const PseudoDt& pseudoDt,
                             const TextLocation& curLoc, _tStackFrame& frame)
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

        ss << "Duplicate data type alias named `" << name << "`.";
        throwTextParseError(ss.str(), curLoc);
    }

    // add alias
    frame.dtAliases[std::move(name)] = pseudoDt.clone();
}

void TsdlParser::_addDtAlias(std::string&& name, const PseudoDt& pseudoDt,
                             const TextLocation& curLoc)
{
    this->_addDtAlias(std::move(name), pseudoDt, curLoc, this->_stackTop());
}

void TsdlParser::_addDtAlias(std::string&& name, const PseudoDt& pseudoDt)
{
    this->_addDtAlias(std::move(name), pseudoDt, _ss.loc());
}

PseudoDt::Up TsdlParser::_aliasedPseudoDt(const std::string& name, TextLocation loc) const
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

TsdlParser::TsdlParser(const std::string_view str) :
    _ss {str}
{
    this->_parseMetadata();
}

std::optional<boost::uuids::uuid> TsdlParser::metadataStreamUuid() const noexcept
{
    assert(_pseudoTraceType);

    if (!_pseudoTraceType->uid()) {
        return std::nullopt;
    }

    return TsdlParser::_uuidFromStr(*_pseudoTraceType->uid());
}

void TsdlParser::_parseMetadata()
{
    _tLexScope lexScope {*this};

    while (this->_tryParseRootBlock());

    // make sure we skip the remaining fruitless stuff
    this->_skipCommentsAndWhitespacesAndSemicolons();

    if (!_ss.isDone()) {
        throwTextParseError("Expecting data type alias (`typealias`, `typedef`, `enum NAME`, "
                            "`struct NAME`, or `variant NAME`), trace type block (`trace`), "
                            "trace environment block (`env`), "
                            "clock type block (`clock`), data stream type block (`stream`), "
                            "or event record type block (`event`). Did you forget the `;` "
                            "after the closing `}` of the block?",
                            _ss.loc());
    }

    if (!_pseudoTraceType) {
        throwTextParseError("Missing `trace` block.");
    }

    // create a yactfr trace type from the pseudo trace type
    this->_createTraceType();
}

bool TsdlParser::_tryParseRootBlock()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto loc = _ss.loc();
    const auto kw = this->_peekKw();

    if (TsdlParser::_kwStartsDtAlias(kw)) {
        return this->_tryParseDtAlias();
    }

    // parse block which starts with the keyword `kw`
    void (TsdlParser::*parseFunc)();
    const char *name;

    switch (kw) {
    case _tKw::Event:
        parseFunc = &TsdlParser::_parseErtBlock;
        name = "event";
        break;

    case _tKw::Stream:
        parseFunc = &TsdlParser::_parseDstBlock;
        name = "stream";
        break;

    case _tKw::Trace:
        parseFunc = &TsdlParser::_parseTraceTypeBlock;
        name = "trace";
        break;

    case _tKw::Env:
        parseFunc = &TsdlParser::_parseEnvBlock;
        name = "env";
        break;

    case _tKw::Clock:
        parseFunc = &TsdlParser::_parseClkTypeBlock;
        name = "clock";
        break;

    case _tKw::Callsite:
        // parse callsite, even if we don't care about it
        parseFunc = &TsdlParser::_parseCallsiteBlock;
        name = "callsite";
        break;

    default:
        return false;
    }

    withErrCtx(loc, [name] {
        return std::string {"In `"} + name + "` root block:";
    }, [this, parseFunc] {
        (this->*parseFunc)();
    });

    return true;
}

void TsdlParser::_expectToken(const std::string_view token)
{
    if (!_ss.tryScanToken(token)) {
        std::ostringstream ss;

        ss << "Expecting `" << token << "`.";
        throwTextParseError(ss.str(), _ss.loc());
    }
}

bool TsdlParser::_tryParseFlEnumStructVarDtAlias()
{
    StrScannerRejecter ssRej {_ss};
    auto [pseudoDt, dtAliasName, isCompound] = this->_tryParseFullDt();

    // parse `;` to make sure it's not a member type/option
    if (!pseudoDt || !isCompound || !_ss.tryScanToken(";")) {
        return false;
    }

    // we have a winner
    ssRej.accept();

    if (!dtAliasName.empty()) {
        this->_addDtAlias(std::move(dtAliasName), *pseudoDt);
    }

    return true;
}

bool TsdlParser::_tryParseGenericDtAlias()
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();

    return withErrCtx(loc, "In data type alias:", [this] {
        return this->_tryParseGenericDtAliasNoErrCtx();
    });
}

bool TsdlParser::_tryParseGenericDtAliasNoErrCtx()
{
    auto isTypealias = false;

    if (_ss.tryScanToken("typealias")) {
        isTypealias = true;
    } else if (!_ss.tryScanToken("typedef")) {
        return false;
    }

    PseudoDt::Up pseudoDt;
    std::optional<std::string> dtAliasName;

    {
        _tLexScope lexScope {*this};

        // parse data type or data type alias reference
        auto [parsedPseudoDt, innerDtAliasName] = this->_tryParseDt();

        pseudoDt = std::move(parsedPseudoDt);

        if (!pseudoDt) {
            throwTextParseError("Expecting explicit data type block (`integer`, `floating_point`, "
                                "`enum`, `string`, `struct`, or `variant`) or "
                                "existing data type alias name.",
                                _ss.loc());
        }

        /*
         * If it's a named fixed-length enumeration, structure, or
         * variant type, then add a data type alias for its name (for
         * example, `struct foo`) to the parent frame, not to the data
         * type alias frame which `lexScope` manages: the latter only
         * exists while parsing this block.
         */
        if (!innerDtAliasName.empty()) {
            assert(_stack.size() >= 2);
            this->_addDtAlias(std::move(innerDtAliasName), *pseudoDt, _ss.loc(),
                              _stack[_stack.size() - 2]);
        }

        // parse `:=` if `typealias` block
        if (isTypealias) {
            this->_expectToken(":=");
        }

        // parse name
        dtAliasName = this->_parseDtAliasName(true);
        assert(dtAliasName);
        pseudoDt = this->_parseArraySubscripts(std::move(pseudoDt));

        // parse `;`
        this->_expectToken(";");
    }

    // add parsed type alias to parent frame
    this->_addDtAlias(std::move(*dtAliasName), *pseudoDt);
    return true;
}

bool TsdlParser::_tryParseDtAlias()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    if (this->_tryParseGenericDtAlias()) {
        return true;
    }

    if (this->_tryParseFlEnumStructVarDtAlias()) {
        return true;
    }

    return false;
}

std::tuple<PseudoDt::Up, std::string> TsdlParser::_tryParseDt()
{
    if (auto pseudoDt = this->_tryParseDtAliasRef()) {
        return {std::move(pseudoDt), std::string {}};
    }

    auto [pseudoDt, dtAliasName, isCompound] = this->_tryParseFullDt();

    return {std::move(pseudoDt), std::move(dtAliasName)};
}

std::tuple<PseudoDt::Up, std::string, bool> TsdlParser::_tryParseFullDt()
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();

    // only try what can start with the keyword at the current position
    switch (this->_peekKw()) {
    case _tKw::Integer:
        return {withErrCtx(loc, "In `integer` block:", [this] {
            return this->_tryParseFlIntType();
        }), std::string {}, false};

    case _tKw::String:
        return {withErrCtx(loc, "In `string` block:", [this] {
            return this->_tryParseNtStrType();
        }), std::string {}, false};

    case _tKw::Enum:
    {
        auto [pseudoDt, dtAliasName] = withErrCtx(loc, "In `enum` block:", [this] {
            return this->_tryParseFlEnumType();
        });

        return {std::move(pseudoDt), std::move(dtAliasName), true};
    }

    case _tKw::FloatingPoint:
        return {withErrCtx(loc, "In `floating_point` block:", [this] {
            return this->_tryParseFlFloatType();
        }), std::string {}, false};

    case _tKw::Struct:
    {
        auto [pseudoDt, dtAliasName] = withErrCtx(loc, "In `struct` block:", [this] {
            return this->_tryParseStructType();
        });

        return {std::move(pseudoDt), std::move(dtAliasName), true};
    }

    case _tKw::Variant:
    {
        auto [pseudoDt, dtAliasName] = withErrCtx(loc, "In `variant` block:", [this] {
            return this->_tryParseVarType();
        });

        return {std::move(pseudoDt), std::move(dtAliasName), true};
    }

    default:
        return {};
    }
}

void TsdlParser::_insertFastPseudoFlIntType(const std::string_view str,
                                            const PseudoDt& pseudoDt)
{
    if (str.size() > TsdlParser::_maxFastFlIntTypeStrSize) {
        return;
    }

    _fastPseudoFlIntTypes.push_back({str, pseudoDt.clone()});
}

PseudoDt::Up TsdlParser::_fastPseudoFlIntType(TextLocation loc)
{
    const auto rest = _ss.rest();

    for (const auto& entry : _fastPseudoFlIntTypes) {
        if (rest.compare(0, entry.str.size(), entry.str) == 0) {
            // we have a match!
            _ss.skip(entry.str.size());

            auto dt = entry.pseudoDt->clone();

            dt->loc(std::move(loc));
            return dt;
        }
    }

    return nullptr;
}

namespace {

[[ nodiscard ]] BitOrder bioFromBo(const ByteOrder bo) noexcept
{
    return bo == ByteOrder::Big ? BitOrder::LastToFirst : BitOrder::FirstToLast;
}

} // namespace

PseudoDt::Up TsdlParser::_tryParseFlIntType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beforeKwLoc = _ss.loc();

    // parse `integer`
    if (!_ss.tryScanToken("integer")) {
        return nullptr;
    }

    _ss.skipCommentsAndWhitespaces();

    if (auto fastPseudoFlIntType = this->_fastPseudoFlIntType(beforeKwLoc)) {
        return fastPseudoFlIntType;
    }

    const auto beginLoc = _ss.loc();
    const auto beginAt = _ss.at();

    // parse attributes
    const auto attrs = this->_expectAttrBlock();

    const auto endAt = _ss.at();

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    auto align = 0U;
    auto size = 0U;
    auto bo = this->_absNativeBo();
    auto dispBase = DisplayBase::Decimal;
    auto isSigned = false;
    std::optional<StringEncoding> encoding;
    std::optional<std::string> mappedClkTypeId;
    std::optional<TextLocation> mapAttrLoc;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "base") {
            dispBase = attr.dispBase();
        } else if (attr.name == "size") {
            const auto attrSize = attr.uintVal();

            if (attrSize == 0) {
                std::ostringstream ss;

                ss << "Invalid `size` attribute (must be greater than 0): " <<
                      attrSize << ".";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            if (attrSize > 64) {
                std::ostringstream ss;

                ss << "`size` attribute is greater than 64 (unsupported): " <<
                      attrSize << ".";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            size = attrSize;
        } else if (attr.name == "align") {
            align = attr.align();
        } else if (attr.name == "byte_order") {
            if (const auto attrBo = attr.bo()) {
                bo = *attrBo;
            }
        } else if (attr.name == "encoding") {
            if (attr.hasEncoding()) {
                // CTF 1.8 only supports UTF-8 (and ASCII, which is a subset)
                encoding = StringEncoding::Utf8;
            }
        } else if (attr.name == "signed") {
            isSigned = attr.boolEquiv();
        } else if (attr.name == "map") {
            mappedClkTypeId = attr.clkNameVal();
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

    auto pseudoDt = std::invoke([&]() -> PseudoDt::Up {
        if (isSigned) {
            if (mappedClkTypeId) {
                throwTextParseError("Illegal `map` attribute for a fixed-length signed integer type.",
                                    *mapAttrLoc);
            }

            return std::make_unique<PseudoScalarDtWrapper>(
                FixedLengthSignedIntegerType::create(align, size, bo, bioFromBo(bo), dispBase),
                encoding, beforeKwLoc
            );
        } else {
            return std::make_unique<PseudoFlUIntType>(align, size, bo, bioFromBo(bo), dispBase,
                                                      FixedLengthUnsignedIntegerType::Mappings {},
                                                      encoding, mappedClkTypeId, nullptr,
                                                      UnsignedIntegerTypeRoleSet {}, beforeKwLoc);
        }
    });

    assert(pseudoDt);

    if (beginLoc.lineNumber() == _ss.loc().lineNumber()) {
        /*
         * Fast pseudo fixed-length integer type cache only supported
         * for single lines.
         */
        this->_insertFastPseudoFlIntType(_ss.str().substr(beginAt, endAt - beginAt), *pseudoDt);
    }

    return pseudoDt;
}

PseudoDt::Up TsdlParser::_tryParseFlFloatType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `floating_point`
    if (!_ss.tryScanToken("floating_point")) {
        return nullptr;
    }

    // parse attributes
    const auto attrs = this->_expectAttrBlock();

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    auto align = 8U;
    auto expDig = 0ULL;
    auto mantDig = 0ULL;
    auto bo = this->_absNativeBo();

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "exp_dig") {
            expDig = attr.uintVal();
        } else if (attr.name == "mant_dig") {
            mantDig = attr.uintVal();
        } else if (attr.name == "align") {
            align = attr.align();
        } else if (attr.name == "byte_order") {
            if (const auto attrBo = attr.bo()) {
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

        ss << "Invalid `exp_dig`/`mant_dig` attribute combination: " <<
              "only 8/24 (single precision) and 11/53 (double precision) are supported.";
        throwTextParseError(ss.str(), beginLoc);
    }

    return std::make_unique<PseudoScalarDtWrapper>(
        FixedLengthFloatingPointNumberType::create(align,
                                                   static_cast<unsigned int>(expDig + mantDig),
                                                   bo, bioFromBo(bo)),
        beginLoc
    );
}

PseudoDt::Up TsdlParser::_tryParseNtStrType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `string`
    if (!_ss.tryScanToken("string")) {
        return nullptr;
    }

    // `string` without attributes?
    {
        StrScannerRejecter ssRej {_ss};

        if (!_ss.tryScanToken("{")) {
            return std::make_unique<PseudoScalarDtWrapper>(std::make_unique<const NullTerminatedStringType>(8),
                                                           beginLoc);
        }
    }

    // parse attributes
    const auto attrs = this->_expectAttrBlock();

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

    return std::make_unique<PseudoScalarDtWrapper>(std::make_unique<const NullTerminatedStringType>(8),
                                                   beginLoc);
}

std::tuple<PseudoDt::Up, std::string> TsdlParser::_tryParseFlEnumType()
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `enum`
    if (!_ss.tryScanToken("enum")) {
        return {};
    }

    // try to parse name
    std::string potDtAliasName;

    if (const auto ident = _ss.tryScanIdent()) {
        potDtAliasName = "enum ";
        potDtAliasName += *ident;
    }

    if (!this->_peekDtBlockBodyStart()) {
        return {};
    }

    // accept the fixed-length enumeration type so far
    ssRej.accept();
    _ss.skipCommentsAndWhitespaces();

    PseudoDt::Up pseudoDt;

    // try to parse the fixed-length integer type
    if (_ss.tryScanToken(":")) {
        _ss.skipCommentsAndWhitespaces();

        // remember location
        const auto loc = _ss.loc();

        // check for a data type alias name first
        if (const auto dtAliasName = this->_parseDtAliasName(false)) {
            // find data type alias
            pseudoDt = this->_aliasedPseudoDt(*dtAliasName, beginLoc);

            if (!pseudoDt) {
                std::ostringstream ss;

                ss << "Cannot find data type alias `" << *dtAliasName << "`.";
                throwTextParseError(ss.str(), loc);
            }

            if (!pseudoDt->isInt()) {
                std::ostringstream ss;

                ss << "Data type alias `" << *dtAliasName << "` isn't an integer type.";
                throwTextParseError(ss.str(), loc);
            }
        } else {
            // fall back to expecting `integer`
            pseudoDt = this->_tryParseFlIntType();

            if (!pseudoDt) {
                throwTextParseError("Expecting `integer` or existing fixed-length integer type alias name.",
                                        loc);
            }

            pseudoDt->loc(beginLoc);
        }
    } else {
        // use `int` type alias
        pseudoDt = this->_aliasedPseudoDt("int", beginLoc);

        if (!pseudoDt) {
            throwTextParseError("Implicit `int` data type alias doesn't exist in this scope.",
                                beginLoc);
        }

        if (!pseudoDt->isInt()) {
            throwTextParseError("Implicit `int` data type alias isn't a fixed-length integer type.",
                                beginLoc);
        }
    }

    // parse `{`
    this->_expectToken("{");

    // parse mappings
    assert(pseudoDt->isInt());

    PseudoDt::Up pseudoEnumType;

    if (pseudoDt->isUInt()) {
        pseudoEnumType = this->_finishParseFlEnumType<FixedLengthUnsignedIntegerType>(std::move(pseudoDt),
                                                                                      [](const auto& pseudoDt,
                                                                                         const auto& mappings) {
            const auto& pseudoUIntType = static_cast<const PseudoFlUIntType&>(pseudoDt);

            return std::make_unique<PseudoFlUIntType>(pseudoUIntType.align(), pseudoUIntType.len(),
                                                      pseudoUIntType.bo(), pseudoUIntType.bio(),
                                                      pseudoUIntType.prefDispBase(), mappings,
                                                      pseudoUIntType.encoding(),
                                                      pseudoUIntType.mappedClkTypeId(), nullptr,
                                                      UnsignedIntegerTypeRoleSet {},
                                                      pseudoDt.loc());
        });
    } else {
        pseudoEnumType = this->_finishParseFlEnumType<FixedLengthSignedIntegerType>(std::move(pseudoDt),
                                                                                    [](const auto& pseudoDt,
                                                                                       const auto& mappings) {
            auto& baseIntType = static_cast<const PseudoScalarDtWrapper&>(pseudoDt).dt().asFixedLengthSignedIntegerType();

            return std::make_unique<PseudoScalarDtWrapper>(
                FixedLengthSignedIntegerType::create(baseIntType.alignment(), baseIntType.length(),
                                                     baseIntType.byteOrder(),
                                                     baseIntType.bitOrder(),
                                                     baseIntType.preferredDisplayBase(), mappings),
                pseudoDt.loc()
            );
        });
    }

    return {std::move(pseudoEnumType), std::move(potDtAliasName)};
}

std::tuple<PseudoDt::Up, std::string> TsdlParser::_tryParseStructType()
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `struct`
    if (!_ss.tryScanToken("struct")) {
        return {};
    }

    // try to parse name
    std::string potDtAliasName;
    PseudoDt::Up pseudoDt;

    {
        std::optional<_tLexScope> dtAliasLexScope;

        if (const auto ident = _ss.tryScanIdent()) {
            potDtAliasName = "struct ";
            potDtAliasName += *ident;
            dtAliasLexScope.emplace(*this);
        }

        {
            _tLexScope structTypeLexScope {*this, _tStackFrame::Kind::StructType};
            const auto lexId = this->_stackTop().lexId;

            // parse `{`
            if (!_ss.tryScanToken("{")) {
                return {};
            }

            // parse data type aliases and member types
            auto pseudoMemberTypes = this->_parseStructVarTypeBody("struct",
                                                                   "Expecting member type with known data type "
                                                                   "or data type alias.");

            ssRej.accept();

            // check for duplicate member type
            TsdlParser::_checkDupPseudoNamedDt(pseudoMemberTypes, beginLoc);

            auto align = 1U;

            if (_ss.tryScanToken("align")) {
                this->_expectToken("(");

                if (const auto optAlign = _ss.tryScanConstUInt()) {
                    align = tsdlAlign(*optAlign, "minimum alignment for `struct` block",
                                      _ss.loc());
                    this->_expectToken(")");
                } else {
                    throwTextParseError("Expecting valid constant unsigned integer.",
                                        _ss.loc());
                }
            }

            pseudoDt = std::make_unique<PseudoStructType>(align, std::move(pseudoMemberTypes),
                                                          nullptr, beginLoc, lexId);
        }
    }

    return {std::move(pseudoDt), std::move(potDtAliasName)};
}

PseudoNamedDts TsdlParser::_parseStructVarTypeBody(const char * const blockName,
                                                   const char * const expectingMsg)
{
    PseudoNamedDts pseudoNamedDts;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        if (_ss.tryScanToken("}")) {
            return pseudoNamedDts;
        }

        const auto success = withErrCtx(_ss.loc(), [blockName] {
            return std::string {"While parsing body of `"} + blockName + "` block:";
        }, [this, &pseudoNamedDts] {
            return this->_tryParseNamedDtOrDtAlias(pseudoNamedDts);
        });

        if (!success) {
            throwTextParseError(expectingMsg, _ss.loc());
        }
    }
}

std::tuple<PseudoDt::Up, std::string> TsdlParser::_tryParseVarType()
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `variant`
    if (!_ss.tryScanToken("variant")) {
        return {};
    }

    // try to parse name
    std::string potDtAliasName;
    PseudoDt::Up pseudoDt;

    {
        std::optional<_tLexScope> dtAliasLexScope;

        if (const auto ident = _ss.tryScanIdent()) {
            potDtAliasName = "variant ";
            potDtAliasName += *ident;
            dtAliasLexScope.emplace(*this);
        }

        {
            _tLexScope varTypeLexScope {*this};

            // try to parse `<`
            std::optional<PseudoDataLoc> pseudoDataLoc;

            if (_ss.tryScanToken("<")) {
                _ss.skipCommentsAndWhitespaces();

                const auto selLoc = _ss.loc();

                pseudoDataLoc = this->_expectDataLoc();
                assert(pseudoDataLoc);

                if (pseudoDataLoc->isEnv()) {
                    throwTextParseError("Selector location of variant type "
                                        "cannot start with `env.`.",
                                        selLoc);
                }

                this->_expectToken(">");
            }

            // parse `{`
            if (!_ss.tryScanToken("{")) {
                return {};
            }

            // parse data type aliases and options
            auto opts = this->_parseStructVarTypeBody("variant",
                                                      "Expecting option or data type alias.");

            ssRej.accept();

            if (opts.empty()) {
                throwTextParseError("Variant type must contain at least one option.", beginLoc);
            }

            // check for duplicate option
            TsdlParser::_checkDupPseudoNamedDt(opts, beginLoc);

            pseudoDt = std::make_unique<PseudoVarType>(pseudoDataLoc, std::move(opts), nullptr,
                                                       beginLoc);
        }
    }

    return {std::move(pseudoDt), std::move(potDtAliasName)};
}

void TsdlParser::_parseEnvBlock()
{
    const auto loc = _ss.loc();

    // parse `env` (the caller peeked it)
    this->_expectToken("env");

    if (_envParsed) {
        throwTextParseError("Duplicate `env` block.", loc);
    }

    // parse attributes
    const auto attrs = this->_expectAttrBlock();

    // parse `;`
    this->_expectToken(";");

    if (this->_isFirstPass()) {
        // first pass: skip
        return;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    TraceEnvironment::Entries entries;

    // check attributes
    for (const auto& attr : attrs) {
        TraceEnvironment::Entry entry;

        if (std::holds_alternative<long long>(attr.val) ||
                std::holds_alternative<unsigned long long>(attr.val)) {
            entry = attr.sIntVal();
        } else if (const auto strVal = std::get_if<std::string>(&attr.val)) {
            entry = *strVal;
        } else {
            std::ostringstream ss;

            ss << "Trace environment entry `" << attr.name <<
                  "`: expecting constant integer or literal string.";
            throwTextParseError(ss.str(), attr.valTextLoc());
        }

        entries[attr.name] = std::move(entry);
    }

    assert(_pseudoTraceType);
    _pseudoTraceType->env(TraceEnvironment {std::move(entries)});
    _envParsed = true;
}

void TsdlParser::_parseCallsiteBlock()
{
    // parse `callsite` (the caller peeked it)
    this->_expectToken("callsite");

    // parse attributes (pretty loose: we accept everything, even duplicates)
    this->_expectAttrBlock();

    // parse `;`
    this->_expectToken(";");
}

void TsdlParser::_parseClkTypeBlock()
{
    const auto beginLoc = _ss.loc();

    // parse `clock` (the caller peeked it)
    this->_expectToken("clock");

    // parse attributes
    const auto attrs = this->_expectAttrBlock();

    // parse `;`
    this->_expectToken(";");

    if (this->_isFirstPass()) {
        return;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    std::string name;
    std::optional<std::string> descr;
    std::optional<std::string> uuidStr;
    std::optional<boost::uuids::uuid> uuid;
    auto freq = 1'000'000'000ULL;
    std::optional<Cycles> prec;
    auto offsetSecs = 0LL;
    Cycles offsetCycles = 0;
    std::optional<TextLocation> offsetCyclesLoc;
    auto isAbs = false;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "name") {
            name = attr.strOrIdentVal();
        } else if (attr.name == "description") {
            descr = attr.strVal();
        } else if (attr.name == "uuid") {
            const auto& attrUuidStr = attr.strVal();

            uuid = TsdlParser::_uuidFromStr(attrUuidStr);

            if (!uuid) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attrUuidStr << "`.";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            uuidStr = attrUuidStr;
        } else if (attr.name == "freq") {
            const auto attrFreq = attr.uintVal();

            if (attrFreq == 0) {
                std::ostringstream ss;

                ss << "Invalid `freq` attribute (must be greater than 0): " <<
                      attrFreq << ".";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            freq = attrFreq;
        } else if (attr.name == "precision") {
            prec = attr.uintVal();
        } else if (attr.name == "offset_s") {
            offsetSecs = attr.sIntVal();
        } else if (attr.name == "offset") {
            offsetCycles = static_cast<Cycles>(attr.uintVal());
            offsetCyclesLoc = attr.valTextLoc();
        } else if (attr.name == "absolute") {
            isAbs = attr.boolEquiv();
        } else {
            attr.throwUnknown();
        }
    }

    // make sure name is set
    if (name.empty()) {
        TsdlParser::_throwMissingAttr("name", beginLoc);
    }

    // make sure clock type doesn't exist
    if (_pseudoTraceType->hasClkType(name)) {
        std::ostringstream ss;

        ss << "Duplicate `clock` block named `" << name << "`.";
        throwTextParseError(ss.str(), beginLoc);
    }

    // adjust offset (make sure `offsetCycles` is less than `freq`)
    {
        const auto completeSecsInOffsetCycles = offsetCycles / freq;

        offsetCycles -= completeSecsInOffsetCycles * freq;

        /*
         * Maximum number of seconds to add to `offsetSecs`:
         * `LLONG_MAX - offsetSecs` doesn't fit a `long long` when
         * `offsetSecs` is negative, but always fits
         * an `unsigned long long`.
         */
        const auto maxSecsToAdd =
            static_cast<unsigned long long>(std::numeric_limits<long long>::max()) -
            static_cast<unsigned long long>(offsetSecs);

        if (completeSecsInOffsetCycles > maxSecsToAdd) {
            std::ostringstream ss;

            ss << "Attribute `offset`: complete seconds (" << completeSecsInOffsetCycles <<
                  ") added to `offset_s` (" << offsetSecs << ") don't fit a signed 64-bit integer.";
            throwTextParseError(ss.str(), *offsetCyclesLoc);
        }

        offsetSecs = static_cast<long long>(static_cast<unsigned long long>(offsetSecs) +
                                            completeSecsInOffsetCycles);
    }

    // create origin
    auto origin = std::invoke([&isAbs, this]() -> std::optional<ClockOrigin> {
        if (isAbs) {
            /*
             * CTF 1.8 says:
             *
             * > The field `absolute` is `TRUE` if the clock is a global
             * > reference across different clock UUID (e.g. NTP time).
             *
             * Although that sentence doesn't indicate that the
             * `absolute` property means Unix epoch, in practice many
             * tools do because there's no other way to specify a clock
             * origin with CTF 1.8. Therefore, follow that de
             * facto convention.
             */
            return ClockOrigin {};
        }

        /*
         * Special case for LTTng: its intention is to have a Unix epoch
         * origin, but an unknown precision/accuracy. This is possible
         * to communicate with CTF 2, but not with CTF 1.8.
         *
         * This means that two LTTng data streams are correlated because
         * they share the same origin, albeit with an unknown accuracy,
         * meaning it's not 100% safe to assume so.
         */
        {
            const auto entry = _pseudoTraceType->env()["tracer_name"];

            if (entry) {
                if (const auto entryVal = std::get_if<std::string>(entry)) {
                    if (boost::algorithm::starts_with(*entryVal, "lttng-")) {
                        return ClockOrigin {};
                    }
                }
            }
        }

        return std::nullopt;
    });

    _pseudoTraceType->clkTypes().insert(ClockType::create(name, std::nullopt, name, std::move(uuidStr),
                                                          std::move(uuid), freq, descr,
                                                          std::move(origin), std::move(prec),
                                                          std::nullopt,
                                                          ClockOffset {offsetSecs, offsetCycles}));
}

void TsdlParser::_parseTraceTypeBlock()
{
    _tLexScope lexScope {*this};

    const auto beginLoc = _ss.loc();

    // parse `trace` (the caller peeked it)
    this->_expectToken("trace");

    if (_traceTypeBlockParsed) {
        throwTextParseError("Duplicate `trace` block.", _ss.loc());
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;
    PseudoDt::Up pseudoPktHeaderType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
            break;
        }

        const auto kw = this->_peekKw();

        // try to parse packet header type
        if (kw == _tKw::Packet) {
            if (auto pseudoDt = this->_tryParseScopeDt("packet", "header")) {
                if (pseudoPktHeaderType) {
                    throwTextParseError("Duplicate `packet.header` scope.", _ss.loc());
                }

                pseudoPktHeaderType = std::move(pseudoDt);
                continue;
            }
        }

        // try to parse data type alias
        if (TsdlParser::_kwStartsDtAlias(kw) && this->_tryParseDtAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    std::optional<unsigned int> majorVersion;
    std::optional<unsigned int> minorVersion;
    std::optional<ByteOrder> nativeBo;
    std::optional<std::string> uuidStr;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "major" || attr.name == "minor") {
            const auto version = attr.uintVal();

            if (attr.name == "major") {
                if (version != 1) {
                    std::ostringstream ss;

                    ss << "Invalid `major` attribute: " <<
                          "unsupported major version (expecting 1): " <<
                          version << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
                }

                majorVersion = version;
            } else if (attr.name == "minor") {
                if (version != 8) {
                    std::ostringstream ss;

                    ss << "Invalid `minor` attribute: " <<
                          "unsupported minor version (expecting 8): " <<
                          version << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
                }

                minorVersion = version;
            }
        } else if (attr.name == "byte_order") {
            nativeBo = attr.bo();

            if (!nativeBo) {
                throwTextParseError("Invalid `byte_order` attribute: cannot be `native` here.",
                                    attr.valTextLoc());
            }
        } else if (attr.name == "uuid") {
            const auto& attrUuidStr = attr.strVal();

            if (attrUuidStr.size() != 36 || !TsdlParser::_uuidFromStr(attrUuidStr)) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attrUuidStr << "`.";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            uuidStr = attrUuidStr;
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

    if (this->_isFirstPass()) {
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

        /*
         * Placeholder pseudo trace type for the root blocks which
         * precede the `trace` block during the second pass.
         */
        _pseudoTraceType = PseudoTraceType {*majorVersion, *minorVersion};
    } else {
        // second pass: create pseudo trace type
        PseudoTraceType pseudoTraceType {
            *majorVersion, *minorVersion, std::nullopt, std::nullopt, std::move(uuidStr),
            TraceEnvironment {}, std::move(pseudoPktHeaderType)
        };

        /*
         * Keep what the root blocks preceding this `trace` block added
         * to the placeholder pseudo trace type.
         */
        assert(_pseudoTraceType);
        pseudoTraceType.env(_pseudoTraceType->env());
        pseudoTraceType.clkTypes() = std::move(_pseudoTraceType->clkTypes());
        pseudoTraceType.pseudoDsts() = std::move(_pseudoTraceType->pseudoDsts());
        pseudoTraceType.pseudoOrphanErts() = std::move(_pseudoTraceType->pseudoOrphanErts());
        _pseudoTraceType = std::move(pseudoTraceType);
        _traceTypeBlockParsed = true;
    }
}

void TsdlParser::_parseDstBlock()
{
    _tLexScope lexScope {*this};

    const auto beginLoc = _ss.loc();

    // parse `stream` (the caller peeked it)
    this->_expectToken("stream");

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;
    PseudoDt::Up pseudoPktCtxType;
    PseudoDt::Up pseudoErHeaderType;
    PseudoDt::Up pseudoErCommonCtxType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
            break;
        }

        const auto kw = this->_peekKw();

        if (kw == _tKw::Packet) {
            // try to parse packet context type
            if (auto pseudoDt = this->_tryParseScopeDt("packet", "context")) {
                if (pseudoPktCtxType) {
                    throwTextParseError("Duplicate `packet.context` scope.", _ss.loc());
                }

                pseudoPktCtxType = std::move(pseudoDt);
                continue;
            }
        } else if (kw == _tKw::Event) {
            // try to parse event record header type
            if (auto pseudoDt = this->_tryParseScopeDt("event", "header", false)) {
                if (pseudoErHeaderType) {
                    throwTextParseError("Duplicate `event.header` scope.", _ss.loc());
                }

                pseudoErHeaderType = std::move(pseudoDt);
                continue;
            }

            // try to parse event record common context type
            if (auto pseudoDt = this->_tryParseScopeDt("event", "context", false)) {
                if (pseudoErCommonCtxType) {
                    throwTextParseError("Duplicate `event.context` scope.", _ss.loc());
                }

                pseudoErCommonCtxType = std::move(pseudoDt);
                continue;
            }
        }

        // try to parse data type alias
        if (TsdlParser::_kwStartsDtAlias(kw) && this->_tryParseDtAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    if (this->_isFirstPass()) {
        return;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    // default data stream type ID is 0
    TypeId id = 0;

    // check for attributes
    for (const auto& attr : attrs) {
        if (attr.name == "id") {
            id = attr.uintVal();
        } else {
            attr.throwUnknown();
        }
    }

    // make sure no data stream type exists with this ID
    if (this->_pseudoDstExists(id)) {
        std::ostringstream ss;

        ss << "Duplicate `stream` block with ID " << id << ".";
        throwTextParseError(ss.str(), beginLoc);
    }

    // create and initialize pseudo data stream type
    _pseudoTraceType->pseudoDsts().try_emplace(
        id,
        std::make_unique<PseudoDst>(id, std::nullopt, std::nullopt, std::nullopt,
                                    std::move(pseudoPktCtxType), std::move(pseudoErHeaderType),
                                    std::move(pseudoErCommonCtxType), nullptr, nullptr,
                                    beginLoc)
    );
    _pseudoTraceType->pseudoOrphanErts()[id];
}

void TsdlParser::_parseErtBlock()
{
    _tLexScope lexScope {*this};

    const auto beginLoc = _ss.loc();

    // parse `event` (the caller peeked it)
    this->_expectToken("event");

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;
    PseudoDt::Up pseudoSpecCtxType;
    PseudoDt::Up pseudoPayloadType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
            break;
        }

        const auto kw = this->_peekKw();

        if (kw == _tKw::Context) {
            // try to parse specific context type
            if (auto pseudoDt = this->_tryParseScopeDt("context")) {
                if (pseudoSpecCtxType) {
                    throwTextParseError("Duplicate `event.context` scope.", _ss.loc());
                }

                pseudoSpecCtxType = std::move(pseudoDt);
                continue;
            }
        } else if (kw == _tKw::Fields) {
            // try to parse payload type
            if (auto pseudoDt = this->_tryParseScopeDt("fields")) {
                if (pseudoPayloadType) {
                    throwTextParseError("Duplicate `event.fields` scope.", _ss.loc());
                }

                pseudoPayloadType = std::move(pseudoDt);
                continue;
            }
        }

        // try to parse data type alias
        if (TsdlParser::_kwStartsDtAlias(kw) && this->_tryParseDtAlias()) {
            continue;
        }

        // fall back to parsing (expecting) attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    if (this->_isFirstPass()) {
        return;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    // default event and stream IDs are 0
    TypeId id = 0;
    TypeId dstId = 0;
    std::optional<LogLevel> logLevel;
    std::optional<std::string> emfUri;
    std::optional<std::string> name;

    // check for attributes
    for (const auto& attr : attrs) {
        if (attr.name == "id") {
            id = attr.uintVal();
        } else if (attr.name == "stream_id") {
            dstId = attr.uintVal();
        } else if (attr.name == "loglevel") {
            logLevel = attr.sIntVal();
        } else if (attr.name == "model.emf.uri") {
            emfUri = attr.strVal();
        } else if (attr.name == "name") {
            name = attr.strOrIdentVal();
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
        throwTextParseError(ss.str(), beginLoc);
    }

    // build event record type object
    dstPseudoOrphanErts.try_emplace(id, PseudoOrphanErt {
        PseudoErt {
            id, std::nullopt, std::move(name), std::nullopt, std::move(logLevel),
            std::move(emfUri), std::move(pseudoSpecCtxType),
            std::move(pseudoPayloadType), nullptr, beginLoc
        },
        beginLoc
    });
}

PseudoDt::Up TsdlParser::_tryParseScopeDt(const std::string_view firstName,
                                          const std::string_view secondName, const bool expect)
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse name
    if (!_ss.tryScanToken(firstName)) {
        return nullptr;
    }

    return withErrCtx(beginLoc, [&firstName, &secondName] {
        std::string line {"In the `"};

        line += firstName;

        if (!secondName.empty()) {
            line += ".";
            line += secondName;
        }

        return line + "` scope:";
    }, [&]() -> PseudoDt::Up {
        if (!secondName.empty()) {
            this->_expectToken(".");

            if (!_ss.tryScanToken(secondName)) {
                if (expect) {
                    std::ostringstream ss;

                    ss << "Expecting `" << secondName << "`.";
                    throwTextParseError(ss.str(), _ss.loc());
                }

                return nullptr;
            }
        }

        // parse `:=`
        this->_expectToken(":=");
        _ss.skipCommentsAndWhitespaces();

        const auto dtLoc = _ss.loc();

        // parse data type
        auto [pseudoDt, dtAliasName] = std::invoke([this] {
            _tLexScope lexScope {*this};

            /*
             * For a named structure type, add the data type alias below
             * to the current frame, not to the frame which `lexScope`
             * manages: the latter only exists while parsing this scope
             * data type.
             */
            return this->_tryParseDt();
        });

        if (!pseudoDt) {
            throwTextParseError("Expecting data type or data type alias name.", dtLoc);
        }

        if (pseudoDt->kind() != PseudoDt::Kind::Struct) {
            throwTextParseError("Expecting a structure type.", dtLoc);
        }

        // add data type alias if the structure type is named
        if (!dtAliasName.empty()) {
            this->_addDtAlias(std::move(dtAliasName), *pseudoDt);
        }

        // parse `;`
        this->_expectToken(";");
        ssRej.accept();
        return std::move(pseudoDt);
    });
}

TsdlParser::_tAttrs TsdlParser::_expectAttrBlock()
{
    this->_expectToken("{");

    _tAttrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
            return attrs;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }
}

TsdlAttr TsdlParser::_expectAttr()
{
    TsdlAttr attr;

    // parse name
    _ss.skipCommentsAndWhitespaces();
    attr.nameLoc = _ss.loc();

    if (_ss.tryScanToken("model.emf.uri")) {
        attr.name = "model.emf.uri";
    } else if (const auto ident = _ss.tryScanIdent()) {
        attr.name = *ident;
    } else {
        throwTextParseError("Expecting attribute name.", *attr.nameLoc);
    }

    // parse `=`
    this->_expectToken("=");

    // this it the source location of the attribute for an eventual error
    _ss.skipCommentsAndWhitespaces();
    attr.valLoc = _ss.loc();

    // special case for the `map` attribute
    if (attr.name == "map") {
        // parse `clock`
        this->_expectToken("clock");

        // parse `.`
        this->_expectToken(".");

        // parse internal ID (name) of clock type
        if (const auto ident = _ss.tryScanIdent()) {
            attr.val = TsdlAttr::ClkNameVal {std::string {*ident}};
        } else {
            throwTextParseError("Expecting identifier (clock type internal ID).", _ss.loc());
        }

        // parse `.`
        this->_expectToken(".");

        // parse `value`
        this->_expectToken("value");

        // parse `;`
        this->_expectToken(";");
        return attr;
    }

    if (const auto escapedStr = this->_tryScanLitStr()) {
        // literal string
        attr.val = std::string {*escapedStr};
    } else if (const auto ident = _ss.tryScanIdent()) {
        // identifier
        attr.val = TsdlAttr::Ident {std::string {*ident}};
    } else if (const auto val = _ss.tryScanConstUInt()) {
        // constant unsigned integer
        attr.val = *val;
    } else if (const auto val = _ss.tryScanConstSInt()) {
        // constant signed integer (starts with `-`)
        assert(*val <= 0);

        if (*val == 0) {
            // `-0`
            attr.val = 0ULL;
        } else {
            attr.val = *val;
        }
    } else {
        throwTextParseError("Expecting valid constant integer, literal string, or identifier.",
                            *attr.valLoc);
    }

    // parse `;`
    this->_expectToken(";");
    return attr;
}

PseudoDt::Up TsdlParser::_tryParseDtAliasRef()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // try `enum`/`struct` followed by name
    {
        StrScannerRejecter ssRej {_ss};

        if (auto ident = _ss.tryScanIdent()) {
            const auto kw = TsdlParser::_kwFromIdent(*ident);

            if (kw == _tKw::Enum || kw == _tKw::Struct) {
                if ((ident = _ss.tryScanIdent())) {
                    if (!this->_peekDtBlockBodyStart()) {
                        std::string dtAliasName {kw == _tKw::Enum ? "enum " : "struct "};

                        dtAliasName += *ident;

                        // get from data type alias
                        if (auto pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc)) {
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
        StrScannerRejecter ssRej {_ss};

        if (_ss.tryScanToken("variant")) {
            if (const auto ident = _ss.tryScanIdent()) {
                std::string dtAliasName {"variant "};

                dtAliasName += *ident;

                // get from data type alias
                auto pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc);

                if (!pseudoDt) {
                    return nullptr;
                }

                if (auto& pseudoVarType = static_cast<PseudoVarType&>(*pseudoDt);
                        pseudoVarType.pseudoSelLoc()) {
                    ssRej.accept();
                    return pseudoDt;
                }

                if (_ss.tryScanToken("<")) {
                    _ss.skipCommentsAndWhitespaces();

                    const auto selLoc = _ss.loc();
                    auto pseudoSelLoc = this->_expectDataLoc();

                    if (pseudoSelLoc.isEnv()) {
                        throwTextParseError("Selector location of variant type cannot start with `env.`.",
                                            selLoc);
                    }

                    this->_expectToken(">");

                    if (!_ss.tryScanToken("{")) {
                        /*
                         * Set the selector location of the pseudo
                         * variant type (already a clone).
                         */
                        static_cast<PseudoVarType&>(*pseudoDt).pseudoSelLoc(std::move(pseudoSelLoc));
                        ssRej.accept();
                        return pseudoDt;
                    }
                }
            }
        }
    }

    // try data type alias name
    {
        StrScannerRejecter ssRej {_ss};

        if (const auto dtAliasName = this->_parseDtAliasName(false)) {
            if (auto pseudoDt = this->_aliasedPseudoDt(*dtAliasName, beginLoc)) {
                ssRej.accept();
                return pseudoDt;
            }
        }
    }

    return nullptr;
}

std::optional<std::string> TsdlParser::_parseDtAliasName(const bool expect)
{
    auto isMulti = false;
    std::string dtAliasName;

    while (true) {
        StrScannerRejecter ssRej {_ss};

        _ss.skipCommentsAndWhitespaces();

        const auto loc = _ss.loc();
        const auto ident = _ss.tryScanIdent();

        if (!ident) {
            ssRej.accept();
            break;
        }

        const auto kw = TsdlParser::_kwFromIdent(*ident);

        // disallow reserved words
        switch (kw) {
        case _tKw::Integer:
        case _tKw::FloatingPoint:
        case _tKw::Enum:
        case _tKw::String:
        case _tKw::Struct:
        case _tKw::Variant:
        case _tKw::Trace:
        case _tKw::Stream:
        case _tKw::Clock:
        case _tKw::Event:
        case _tKw::Env:
            if (expect) {
                std::ostringstream ss;

                ss << "Invalid keyword `" << *ident << "` in type alias name.";
                throwTextParseError(ss.str(), loc);
            } else {
                return std::nullopt;
            }

        default:
            break;
        }

        if (TsdlParser::_kwIsCTypeWord(kw)) {
            isMulti = true;
        } else {
            if (isMulti) {
                // this must be the end of the data type alias name
                break;
            }
        }

        ssRej.accept();

        if (!dtAliasName.empty()) {
            dtAliasName += ' ';
        }

        dtAliasName += *ident;

        if (!isMulti) {
            // single word data type alias name: break now
            break;
        }
    }

    if (dtAliasName.empty()) {
        if (expect) {
            throwTextParseError("Expecting data type alias name.", _ss.loc());
        } else {
            return std::nullopt;
        }
    }

    return dtAliasName;
}

PseudoDataLoc TsdlParser::_expectDataLoc()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();
    PseudoDataLoc::PathElems allPathElems;

    while (true) {
        if (const auto ident = _ss.tryScanIdent()) {
            allPathElems.emplace_back(*ident);

            if (!_ss.tryScanToken(".")) {
                break;
            }
        } else {
            break;
        }
    }

    if (allPathElems.empty()) {
        throwTextParseError("Empty data location.", beginLoc);
    }

    return this->_pseudoDataLocFromAllPathElems(allPathElems, beginLoc);
}

std::tuple<PseudoDt::Up, std::string> TsdlParser::_tryParseIdentArraySubscripts(PseudoDt::Up innerPseudoDt)
{
    // parse identifier
    if (const auto ident = _ss.tryScanIdent()) {
        return {this->_parseArraySubscripts(std::move(innerPseudoDt)), std::string {*ident}};
    }

    return {};
}

PseudoDt::Up TsdlParser::_parseArraySubscripts(PseudoDt::Up innerPseudoDt)
{
    /*
     * A temporary array type subscript.
     *
     * If `len` holds a length, then use it to build a static-length
     * array type. Otherwise, `len` holds a pseudo data location: use it
     * to build a dynamic-length array type.
     */
    struct LenDescr final
    {
        std::variant<Size, PseudoDataLoc> len;
        TextLocation loc;
    };

    std::vector<LenDescr> lenDescrs;

    while (true) {
        if (!_ss.tryScanToken("[")) {
            break;
        }

        _ss.skipCommentsAndWhitespaces();

        const auto subscriptLoc = _ss.loc();

        if (const auto val = _ss.tryScanConstSInt()) {
            if (*val < 0) {
                std::ostringstream ss;

                ss << "Length of array type cannot be negative: " << *val << ".";
                throwTextParseError(ss.str(), subscriptLoc);
            }

            lenDescrs.push_back({static_cast<Size>(*val), subscriptLoc});
        } else {
            const auto pseudoDataLoc = withErrCtx(subscriptLoc,
                                                  "Expecting valid constant integer (static-length array type) or valid data location (dynamic-length array type):",
                                                  [this] {
                return this->_expectDataLoc();
            });

            if (pseudoDataLoc.isEnv()) {
                // only the `env.KEY` format is accepted
                if (pseudoDataLoc.pathElems().size() != 1) {
                    throwTextParseError("Invalid environment location: expecting `env.KEY`, "
                                        "where KEY is the key of an existing environment entry.",
                                        subscriptLoc);
                }

                const auto& envKey = *pseudoDataLoc.pathElems()[0];

                if (this->_isFirstPass()) {
                    /*
                     * First pass: the parser skips the `env` block, but
                     * also discards this data type once it parses the
                     * `trace` block: use a placeholder length.
                     */
                    lenDescrs.push_back({Size {0}, subscriptLoc});
                } else {
                    // find the value in the current environment
                    if (!_envParsed) {
                        std::ostringstream ss;

                        ss << "Static-length array type refers to the environment entry `" <<
                              envKey << "`, but no environment exists at this point.";
                        throwTextParseError(ss.str(), subscriptLoc);
                    }

                    assert(_pseudoTraceType);

                    const auto entry = _pseudoTraceType->env()[envKey];

                    if (!entry) {
                        std::ostringstream ss;

                        ss << "Cannot find environment entry `" << envKey << "`.";
                        throwTextParseError(ss.str(), subscriptLoc);
                    }

                    if (const auto entryVal = std::get_if<long long>(entry)) {
                        if (*entryVal < 0) {
                            std::ostringstream ss;

                            ss << "Static-length array type cannot have a negative size: " <<
                                  *entryVal << ".";
                            throwTextParseError(ss.str(), subscriptLoc);
                        }

                        lenDescrs.push_back({static_cast<Size>(*entryVal), subscriptLoc});
                    } else {
                        std::ostringstream ss;

                        ss << "Environment entry `" << envKey <<
                              "` isn't a valid static-length array type size.";
                        throwTextParseError(ss.str(), subscriptLoc);
                    }
                }
            } else {
                lenDescrs.push_back({pseudoDataLoc, subscriptLoc});
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
     * arrays of `len` static-length arrays of four
     * null-terminated strings.
     *
     * At this point, `innerPseudoDt` is the null-terminated string type
     * in the example above.
     */
    for (const auto& lenDescr : boost::adaptors::reverse(lenDescrs)) {
        if (const auto arrayLen = std::get_if<Size>(&lenDescr.len)) {
            innerPseudoDt = std::make_unique<PseudoSlArrayType>(*arrayLen,
                                                                std::move(innerPseudoDt), nullptr,
                                                                lenDescr.loc);
        } else {
            innerPseudoDt = std::make_unique<PseudoDlArrayType>(std::get<PseudoDataLoc>(lenDescr.len),
                                                                std::move(innerPseudoDt), nullptr,
                                                                lenDescr.loc);
        }
    }

    return innerPseudoDt;
}

bool TsdlParser::_tryParseNamedDt(PseudoDt::Up pseudoDt, const TextLocation& dtLoc,
                                  PseudoNamedDts& pseudoNamedDts)
{
    // try parsing an identifier + array subscripts
    auto [effectivePseudoDt, ident] = this->_tryParseIdentArraySubscripts(std::move(pseudoDt));

    if (!effectivePseudoDt) {
        return false;
    }

    // variant type must have a selector location at this point
    if (TsdlParser::_isPseudoVarTypeWithoutSelLocRec(*effectivePseudoDt)) {
        throwTextParseError("Variant type needs a selector location here.", dtLoc);
    }

    pseudoNamedDts.push_back(std::make_unique<PseudoNamedDt>(ident, std::move(effectivePseudoDt)));
    this->_expectToken(";");
    this->_stackTop().idents.push_back(std::move(ident));
    return true;
}

bool TsdlParser::_tryParseNamedDtOrDtAlias(PseudoNamedDts& pseudoNamedDts)
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
     * a) `variant var_name <tag> field_name;`
     * b) `variant var_name <tag> { ... };`
     * c) `variant var_name { ... };`
     * d) `variant var_name <tag> { ... } field_name;`
     * e) `variant <tag> { ... } field_name;`
     *
     * Here, b), c), and d) define a data type alias (named variant),
     * whereas a) has a relative selector location, but uses an aliased
     * variant type named `var_name` which should already exist at this
     * point: this is why we try it first.
     */

    // try cases 5, 6, 7, and 9 first
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto dtLoc = _ss.loc();

    {
        StrScannerRejecter ssRej {_ss};

        if (auto pseudoDt = this->_tryParseDtAliasRef()) {
            if (this->_tryParseNamedDt(std::move(pseudoDt), dtLoc, pseudoNamedDts)) {
                // we have a winner
                ssRej.accept();
                return true;
            }
        }
    }

    // try generic data type alias (case 1)
    if (this->_tryParseGenericDtAlias()) {
        return true;
    }

    /*
     * Try full data type (cases 2, 3, 4, and 8).
     *
     * Parse it only once, and then decide with what follows:
     *
     * `;`:
     *     Data type alias (cases 2, 3, and 4), only for a fixed-length
     *     enumeration, structure, or variant type.
     *
     *     An anonymous one, for example `struct { ... };`, is accepted
     *     and ignored.
     *
     * Identifier:
     *     Member type/option (case 8). A named fixed-length
     *     enumeration, structure, or variant type also defines a data
     *     type alias.
     */
    {
        StrScannerRejecter ssRej {_ss};

        if (auto [pseudoDt, dtAliasName, isCompound] = this->_tryParseFullDt(); pseudoDt) {
            const auto afterDtLoc = _ss.loc();

            if (isCompound && _ss.tryScanToken(";")) {
                // data type alias (cases 2, 3, and 4)
                ssRej.accept();

                if (!dtAliasName.empty()) {
                    this->_addDtAlias(std::move(dtAliasName), *pseudoDt);
                }

                return true;
            }

            // member type/option (case 8)
            if (!dtAliasName.empty()) {
                this->_addDtAlias(std::move(dtAliasName), *pseudoDt, afterDtLoc);
            }

            if (this->_tryParseNamedDt(std::move(pseudoDt), dtLoc, pseudoNamedDts)) {
                // we have a winner
                ssRej.accept();
                return true;
            }

            /*
             * If there's a type, but no identifier, and we know that
             * it's not a data type alias, then we expect an identifier
             * at this point.
             */
            _ss.skipCommentsAndWhitespaces();
            throwTextParseError("Expecting identifier (member type/option name).", _ss.loc());
        }
    }

    return false;
}

std::optional<std::string_view> TsdlParser::_tryScanLitStr()
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();

    if (const auto litStr = _ss.tryScanLitStr("abfnrtvx'?")) {
        for (const auto ch : *litStr) {
            if ((ch >= 0 && ch <= 8) || (ch >= 14 && ch <= 31) || ch == 127) {
                // disallow those control characters in the metadata text
                std::ostringstream ss;

                ss << "Illegal character found in literal string: 0x" <<
                      std::hex << static_cast<int>(ch) << ".";
                throwTextParseError(ss.str(), loc);
            }
        }

        return litStr;
    }

    return std::nullopt;
}

TsdlParser::_tKw TsdlParser::_kwFromIdent(const std::string_view ident) noexcept
{
    if (ident.empty()) {
        return _tKw::None;
    }

    // switch on the first character to limit string comparisons
    switch (ident.front()) {
    case '_':
        if (ident == "_Bool") {
            return _tKw::CBool;
        } else if (ident == "_Complex") {
            return _tKw::CComplex;
        } else if (ident == "_Imaginary") {
            return _tKw::CImaginary;
        }

        break;

    case 'c':
        if (ident == "callsite") {
            return _tKw::Callsite;
        } else if (ident == "char") {
            return _tKw::CChar;
        } else if (ident == "clock") {
            return _tKw::Clock;
        } else if (ident == "const") {
            return _tKw::CConst;
        } else if (ident == "context") {
            return _tKw::Context;
        }

        break;

    case 'd':
        if (ident == "double") {
            return _tKw::CDouble;
        }

        break;

    case 'e':
        if (ident == "enum") {
            return _tKw::Enum;
        } else if (ident == "env") {
            return _tKw::Env;
        } else if (ident == "event") {
            return _tKw::Event;
        }

        break;

    case 'f':
        if (ident == "fields") {
            return _tKw::Fields;
        } else if (ident == "float") {
            return _tKw::CFloat;
        } else if (ident == "floating_point") {
            return _tKw::FloatingPoint;
        }

        break;

    case 'i':
        if (ident == "int") {
            return _tKw::CInt;
        } else if (ident == "integer") {
            return _tKw::Integer;
        }

        break;

    case 'l':
        if (ident == "long") {
            return _tKw::CLong;
        }

        break;

    case 'p':
        if (ident == "packet") {
            return _tKw::Packet;
        }

        break;

    case 's':
        if (ident == "short") {
            return _tKw::CShort;
        } else if (ident == "signed") {
            return _tKw::CSigned;
        } else if (ident == "stream") {
            return _tKw::Stream;
        } else if (ident == "string") {
            return _tKw::String;
        } else if (ident == "struct") {
            return _tKw::Struct;
        }

        break;

    case 't':
        if (ident == "trace") {
            return _tKw::Trace;
        } else if (ident == "typealias") {
            return _tKw::Typealias;
        } else if (ident == "typedef") {
            return _tKw::Typedef;
        }

        break;

    case 'u':
        if (ident == "unsigned") {
            return _tKw::CUnsigned;
        }

        break;

    case 'v':
        if (ident == "variant") {
            return _tKw::Variant;
        } else if (ident == "void") {
            return _tKw::CVoid;
        }

        break;

    default:
        break;
    }

    return _tKw::None;
}

TsdlParser::_tKw TsdlParser::_peekKw()
{
    const auto ident = _ss.peekIdent();

    return ident ? TsdlParser::_kwFromIdent(*ident) : _tKw::None;
}

bool TsdlParser::_peekDtBlockBodyStart()
{
    StrScannerRejecter ssRej {_ss};

    return _ss.tryScanToken("{") || (!_ss.tryScanToken(":=") && _ss.tryScanToken(":"));
}

void TsdlParser::_skipCommentsAndWhitespacesAndSemicolons()
{
    while (true) {
        _ss.skipCommentsAndWhitespaces();

        if (!_ss.tryScanToken(";")) {
            break;
        }
    }
}

} // namespace yactfr::internal
