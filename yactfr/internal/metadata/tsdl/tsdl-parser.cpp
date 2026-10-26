/*
 * Copyright (C) 2015-2026 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <iostream>
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "tsdl-parser.hpp"
#include "../trace-type-from-pseudo-trace-type.hpp"
#include "../../utils.hpp"

namespace yactfr {
namespace internal {

TsdlParser::_tStackFrame::_tStackFrame(const Kind kind, const Index lexId) :
    kind {kind},
    lexId {lexId}
{
}

constexpr Size TsdlParser::_maxFastFlIntTypeStrSize = 256;

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

            _pseudoTraceType->clkTypes().insert(ClockType::create(defStr, boost::none, boost::none,
                                                                  boost::none, boost::none,
                                                                  1'000'000'000ULL,
                                                                  boost::none, boost::none,
                                                                  boost::none, boost::none,
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
   for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

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

class DefClkTsRoleAdder :
    public PseudoDtVisitor
{
public:
    explicit DefClkTsRoleAdder() = default;

    void visit(PseudoFlUIntType& pseudoDt) override
    {
        if (pseudoDt.mappedClkTypeId() &&
                !pseudoDt.hasRole(UnsignedIntegerTypeRole::PacketEndDefaultClockTimestamp)) {
            pseudoDt.addRole(UnsignedIntegerTypeRole::DefaultClockTimestamp);
        }
    }

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

    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        if (pseudoDst->pseudoPktCtxType()) {
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_size",
                                            UnsignedIntegerTypeRole::PacketTotalLength);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "content_size",
                                            UnsignedIntegerTypeRole::PacketContentLength);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_size",
                                            UnsignedIntegerTypeRole::PacketTotalLength);
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

    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        if (pseudoDst->pseudoPktCtxType()) {
            pseudoDst->pseudoPktCtxType()->accept(visitor);
        }

        if (pseudoDst->pseudoErHeaderType()) {
            pseudoDst->pseudoErHeaderType()->accept(visitor);
        }
    }
}

class PseudoDstDefClkTypeSetter :
    public PseudoDtVisitor
{
public:
    explicit PseudoDstDefClkTypeSetter(PseudoTraceType& pseudoTraceType, PseudoDst& pseudoDst) :
        _pseudoTraceType {&pseudoTraceType},
        _pseudoDst {&pseudoDst}
    {
    }

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

private:
    PseudoTraceType * const _pseudoTraceType;
    PseudoDst * const _pseudoDst;
    const std::string *_clkTypeId = nullptr;
};

void TsdlParser::_setPseudoDstDefClkType(PseudoDst& pseudoDst)
{
    PseudoDstDefClkTypeSetter visitor {*_pseudoTraceType, pseudoDst};

    try {
        if (pseudoDst.pseudoPktCtxType()) {
            try {
                pseudoDst.pseudoPktCtxType()->accept(visitor);
            } catch (TextParseError& exc) {
                appendMsgToTextParseError(exc, "In the packet context type:",
                                          pseudoDst.pseudoPktCtxType()->loc());
                throw;
            }
        }

        if (pseudoDst.pseudoErHeaderType()) {
            try {
                pseudoDst.pseudoErHeaderType()->accept(visitor);
            } catch (TextParseError& exc) {
                appendMsgToTextParseError(exc, "In the event record header type:",
                                          pseudoDst.pseudoErHeaderType()->loc());
                throw;
            }
        }
    } catch (TextParseError& exc) {
        std::ostringstream ss;

        ss << "In the data stream type with ID " << pseudoDst.id() << ":";
        appendMsgToTextParseError(exc, ss.str(), pseudoDst.loc());
        throw;
    }
}

void TsdlParser::_setPseudoDstDefClkType()
{
    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        this->_setPseudoDstDefClkType(*idPseudoDstPair.second);
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

        if (entryNames.find(*entry->name()) != entryNames.end()) {
            std::ostringstream ss;

            ss << "Duplicate identifier (member type or option name) `" << *entry->name() << "`.";
            throwTextParseError(ss.str(), loc);
        }

        entryNames.insert(*entry->name());
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
        if (attrSet.find(attr.name) != attrSet.end()) {
            std::ostringstream ss;

            ss << "Duplicate attribute `" << attr.name << "`.";
            throwTextParseError(ss.str(), attr.nameTextLoc());
        }

        attrSet.insert(attr.name);
    }
}

void TsdlParser::_throwMissingAttr(const std::string& name, const TextLocation& loc)
{
    std::ostringstream ss;

    ss << "Missing attribute `" << name << "`.";
    throwTextParseError(ss.str(), loc);
}

boost::optional<boost::uuids::uuid> TsdlParser::_uuidFromStr(const std::string& str)
{
    try {
        return boost::uuids::string_generator {}(str);
    } catch (const std::runtime_error&) {
        return boost::none;
    }
}

struct PseudoDataLocBase
{
    explicit PseudoDataLocBase(const PseudoDataLoc::Kind kind, boost::optional<Scope> scope,
                               const PseudoDataLoc::PathElems::const_iterator restPos) :
        kind {kind},
        scope {std::move(scope)},
        restPos {restPos}
    {
    }

    PseudoDataLoc::Kind kind;
    boost::optional<Scope> scope;
    PseudoDataLoc::PathElems::const_iterator restPos;
};

namespace {

boost::optional<PseudoDataLocBase> pseudoDataLocBase(const PseudoDataLoc::PathElems& allPathElems,
                                                     const TextLocation& loc)
{
    const auto beginPos = allPathElems.begin();

    if (allPathElems.size() >= 3) {
        if (*allPathElems[0] == "trace") {
            if (*allPathElems[1] == "packet") {
                if (*allPathElems[2] == "header") {
                    return PseudoDataLocBase {
                        PseudoDataLoc::Kind::Abs, Scope::PacketHeader, beginPos + 3
                    };
                }
            }

            throwTextParseError("Expecting `packet.header` after `trace.`.", loc);
        } else if (*allPathElems[0] == "stream") {
            if (*allPathElems[1] == "packet") {
                if (*allPathElems[2] == "context") {
                    return PseudoDataLocBase {
                        PseudoDataLoc::Kind::Abs, Scope::PacketContext, beginPos + 3
                    };
                }
            } else if (*allPathElems[1] == "event") {
                if (*allPathElems[2] == "header") {
                    return PseudoDataLocBase {
                        PseudoDataLoc::Kind::Abs, Scope::EventRecordHeader, beginPos + 3
                    };
                } else if (*allPathElems[2] == "context") {
                    return PseudoDataLocBase {
                        PseudoDataLoc::Kind::Abs, Scope::EventRecordCommonContext, beginPos + 3
                    };
                }
            }

            throwTextParseError("Expecting `packet.context`, `event.header`, or "
                                "`event.context` after `stream.`.", loc);
        }
    }

    if (allPathElems.size() >= 2) {
        if (*allPathElems[0] == "event") {
            if (*allPathElems[1] == "context") {
                return PseudoDataLocBase {
                    PseudoDataLoc::Kind::Abs, Scope::EventRecordSpecificContext, beginPos + 2
                };
            } else if (*allPathElems[1] == "fields") {
                return PseudoDataLocBase {
                    PseudoDataLoc::Kind::Abs, Scope::EventRecordPayload, beginPos + 2
                };
            }

            throwTextParseError("Expecting `context` or `fields` after `event.`.", loc);
        }
    }

    if (allPathElems.size() >= 1 && *allPathElems[0] == "env") {
        return PseudoDataLocBase {
            PseudoDataLoc::Kind::Env, boost::none, beginPos + 1
        };
    }

    return boost::none;
}

} // namespace

boost::optional<PseudoDataLoc> TsdlParser::_pseudoDataLocFromAbsAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                                             const TextLocation& loc)
{
    const auto psDataLocBase = pseudoDataLocBase(allPathElems, loc);

    if (!psDataLocBase || (psDataLocBase->kind != PseudoDataLoc::Kind::Abs &&
                           psDataLocBase->kind != PseudoDataLoc::Kind::Env)) {
        return boost::none;
    }

    /*
     * Data location is already absolute: skip the root scope part (or
     * `env`) to create the path elements.
     */
    PseudoDataLoc::PathElems pathElems;

    std::copy(psDataLocBase->restPos, allPathElems.end(), std::back_inserter(pathElems));

    return PseudoDataLoc {
        psDataLocBase->kind, psDataLocBase->scope, std::move(pathElems), loc
    };
}

boost::optional<PseudoDataLoc> TsdlParser::_pseudoDataLocFromRelAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
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
                    PseudoDataLoc::Kind::Rel1, boost::none, allPathElems, loc, stackIt->lexId
                };
            }
        }

        // identifier isn't in this frame: try next (lower) stack frame
        if (stackIt == _stack.cbegin()) {
            // no more frames: not found
            std::ostringstream ss;

            ss << "Invalid relative data location (`";

            for (auto it = allPathElems.begin(); it != allPathElems.end(); ++it) {
                ss << **it;

                if (it != allPathElems.end() - 1) {
                    ss << ".";
                }
            }

            ss << "`): cannot find `" << firstPathElem << "` (first element).";
            throwTextParseError(ss.str(), loc);
        }

        --stackIt;
    }

    return boost::none;
}

PseudoDataLoc TsdlParser::_pseudoDataLocFromAllPathElems(const PseudoDataLoc::PathElems& allPathElems,
                                                         const TextLocation& loc)
{
    assert(!allPathElems.empty());

    if (const auto pseudoDataLoc = this->_pseudoDataLocFromAbsAllPathElems(allPathElems, loc)) {
        return *pseudoDataLoc;
    }

    if (const auto pseudoDataLoc = this->_pseudoDataLocFromRelAllPathElems(allPathElems, loc)) {
        return *pseudoDataLoc;
    }

    throwTextParseError("Invalid data location.", loc);
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

TsdlParser::TsdlParser(const char * const begin, const char * const end) :
    _ss {begin, end}
{
    assert(end >= begin);
    this->_parseMetadata();
}

const boost::optional<boost::uuids::uuid> TsdlParser::metadataStreamUuid() const noexcept
{
    assert(_pseudoTraceType);

    if (!_pseudoTraceType->uid()) {
        return boost::none;
    }

    return TsdlParser::_uuidFromStr(*_pseudoTraceType->uid());
}

void TsdlParser::_parseMetadata()
{
    _tLexScope lexScope {*this, _tStackFrame::Kind::Root};

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

    const auto tryParseBlock = [this, &loc](bool (TsdlParser::*parseFunc)(),
                                            const char * const name) {
        try {
            return (this->*parseFunc)();
        } catch (TextParseError& error) {
            appendMsgToTextParseError(error, std::string {"In `"} + name + "` root block:", loc);
            throw;
        }
    };

    switch (kw) {
    case _tKw::Event:
        return tryParseBlock(&TsdlParser::_tryParseErtBlock, "event");

    case _tKw::Stream:
        return tryParseBlock(&TsdlParser::_tryParseDstBlock, "stream");

    case _tKw::Trace:
        return tryParseBlock(&TsdlParser::_tryParseTraceTypeBlock, "trace");

    case _tKw::Env:
        return tryParseBlock(&TsdlParser::_tryParseEnvBlock, "env");

    case _tKw::Clock:
        return tryParseBlock(&TsdlParser::_tryParseClkTypeBlock, "clock");

    case _tKw::Callsite:
        // parse callsite, even if we don't care about it
        return tryParseBlock(&TsdlParser::_tryParseCallsiteBlock, "callsite");

    default:
        return false;
    }
}

void TsdlParser::_expectToken(const char * const token)
{
    if (!_ss.tryScanToken(token)) {
        std::ostringstream ss;

        ss << "Expecting `" << token << "`.";
        throwTextParseError(ss.str(), _ss.loc());
    }
}

bool TsdlParser::_tryParseFlEnumStructVarDtAlias()
{
    PseudoDt::Up pseudoDt;
    std::string dtAliasName;

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto loc = _ss.loc();

    // try fixed-length enumeration type alias
    {
        StrScannerRejecter ssRej {_ss};

        try {
            pseudoDt = this->_tryParseFlEnumType(false, &dtAliasName);
        } catch (TextParseError& error) {
            appendMsgToTextParseError(error, "In `enum` block:", loc);
            throw;
        }

        if (pseudoDt) {
            // parse `;` to make sure it's not a member type/option
            if (_ss.tryScanToken(";")) {
                // we have a winner
                ssRej.accept();

                /*
                 * Add data type alias if a data type alias name was
                 * found (safe to move here).
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
        StrScannerRejecter ssRej {_ss};

        try {
            pseudoDt = this->_tryParseStructType(false, &dtAliasName);
        } catch (TextParseError& error) {
            appendMsgToTextParseError(error, "In `struct` block:", loc);
            throw;
        }

        if (pseudoDt) {
            // parse `;` to make sure it's not a member type/option
            if (_ss.tryScanToken(";")) {
                // we have a winner
                ssRej.accept();

                /*
                 * Add data type alias if a data type alias name was
                 * found (safe to move here).
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
        StrScannerRejecter ssRej {_ss};

        try {
            pseudoDt = this->_tryParseVarType(false, &dtAliasName);
        } catch (TextParseError& error) {
            appendMsgToTextParseError(error, "In `variant` block:", loc);
            throw;
        }

        if (pseudoDt) {
            // parse `;` to make sure it's not a field/option
            if (_ss.tryScanToken(";")) {
                // we have a winner
                ssRej.accept();

                /*
                 * Add data type alias if a data type alias name was
                 * found (safe to move here).
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

bool TsdlParser::_tryParseGenericDtAlias()
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();

    try {
        return this->_tryParseGenericDtAliasNoErrCtx();
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In data type alias:", loc);
        throw;
    }
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
    std::string dtAliasName;

    {
        _tLexScope lexScope {*this, _tStackFrame::Kind::DtAlias};

        /*
         * Parse full data type.
         *
         * If it's a named fixed-length enumeration, structure, or
         * variant type, then add a data type alias for its name (for
         * example, `struct foo`) to the parent frame, not to the data
         * type alias frame which `lexScope` manages: the latter only
         * exists while parsing this block.
         */
        std::string innerDtAliasName;

        pseudoDt = this->_tryParseFullDt(false, &innerDtAliasName);

        if (pseudoDt && !innerDtAliasName.empty()) {
            assert(_stack.size() >= 2);
            this->_addDtAlias(std::move(innerDtAliasName), *pseudoDt, _ss.loc(),
                              _stack[_stack.size() - 2]);
        }

        if (!pseudoDt) {
            /*
             * Cannot parse a full data type: try an existing data type
             * alias name.
             */
            const auto loc = _ss.loc();

            if (const auto ident = _ss.tryScanIdent()) {
                pseudoDt = this->_aliasedPseudoDt(*ident, loc);

                if (!pseudoDt) {
                    throwTextParseError("Expecting explicit data type block (`integer`, `floating_point`, "
                                        "`enum`, `string`, `struct`, or `variant`) or "
                                        "existing data type alias name.",
                                        _ss.loc());
                }
            } else {
                throwTextParseError("Expecting explicit data type block (`integer`, `floating_point`, "
                                    "`enum`, `string`, `struct`, or `variant`) or "
                                    "existing data type alias name.",
                                    _ss.loc());
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

PseudoDt::Up TsdlParser::_tryParseDt(const bool addDtAlias, std::string * const dtAliasName)
{
    if (auto pseudoDt = this->_tryParseDtAliasRef()) {
        if (dtAliasName) {
            dtAliasName->clear();
        }

        return pseudoDt;
    }

    if (auto pseudoDt = this->_tryParseFullDt(addDtAlias, dtAliasName)) {
        return pseudoDt;
    }

    return nullptr;
}

PseudoDt::Up TsdlParser::_tryParseFullDt(const bool addDtAlias, std::string * const dtAliasName,
                                         bool * const isCompound)
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();

    /*
     * A failed attempt below may set `*dtAliasName` (for example,
     * `enum foo` without `:` or `{`), so always start from an
     * empty name.
     */
    if (dtAliasName) {
        dtAliasName->clear();
    }

    const auto tryParse = [&loc](auto&& parseFunc, const char * const name) {
        try {
            return parseFunc();
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, std::string {"In `"} + name + "` block:", loc);
            throw;
        }
    };

    PseudoDt::Up pseudoDt;
    auto parsedCompound = false;

    // only try what can start with the keyword at the current position
    switch (this->_peekKw()) {
    case _tKw::Integer:
        pseudoDt = tryParse([this] {
            return this->_tryParseFlIntType();
        }, "integer");
        break;

    case _tKw::String:
        pseudoDt = tryParse([this] {
            return this->_tryParseNtStrType();
        }, "string");
        break;

    case _tKw::Enum:
        pseudoDt = tryParse([this, addDtAlias, dtAliasName] {
            return this->_tryParseFlEnumType(addDtAlias, dtAliasName);
        }, "enum");
        parsedCompound = true;
        break;

    case _tKw::FloatingPoint:
        pseudoDt = tryParse([this] {
            return this->_tryParseFlFloatType();
        }, "floating_point");
        break;

    case _tKw::Struct:
        pseudoDt = tryParse([this, addDtAlias, dtAliasName] {
            return this->_tryParseStructType(addDtAlias, dtAliasName);
        }, "struct");
        parsedCompound = true;
        break;

    case _tKw::Variant:
        pseudoDt = tryParse([this, addDtAlias, dtAliasName] {
            return this->_tryParseVarType(addDtAlias, dtAliasName);
        }, "variant");
        parsedCompound = true;
        break;

    default:
        break;
    }

    if (!pseudoDt) {
        if (dtAliasName) {
            dtAliasName->clear();
        }

        return nullptr;
    }

    if (isCompound) {
        *isCompound = parsedCompound;
    }

    return pseudoDt;
}

void TsdlParser::_insertFastPseudoFlIntType(const char * const begin, const char * const end,
                                            const PseudoDt& pseudoDt)
{
    assert(end >= begin);

    if (static_cast<Size>(end - begin) > TsdlParser::_maxFastFlIntTypeStrSize) {
        return;
    }

    _fastPseudoFlIntTypes.push_back({begin, end, pseudoDt.clone()});
}

PseudoDt::Up TsdlParser::_fastPseudoFlIntType(TextLocation loc)
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

namespace {

BitOrder bioFromBo(const ByteOrder bo) noexcept
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

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
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
    auto dispBase = DisplayBase::Decimal;
    auto isSigned = false;
    boost::optional<StringEncoding> encoding;
    boost::optional<std::string> mappedClkTypeId;
    boost::optional<TextLocation> mapAttrLoc;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "base") {
            dispBase = attr.dispBase();
        } else if (attr.name == "size") {
            attr.checkKind(TsdlAttr::Kind::UInt);

            if (attr.uintVal == 0) {
                std::ostringstream ss;

                ss << "Invalid `size` attribute (must be greater than 0): " <<
                      attr.uintVal << ".";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            if (attr.uintVal > 64) {
                std::ostringstream ss;

                ss << "`size` attribute is greater than 64 (unsupported): " <<
                      attr.uintVal << ".";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            size = attr.uintVal;
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
            mappedClkTypeId = std::move(attr.strVal);
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

    auto pseudoDt = call([&]() -> PseudoDt::Up {
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
        this->_insertFastPseudoFlIntType(beginAt, endAt, *pseudoDt);
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

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
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
            attr.checkKind(TsdlAttr::Kind::UInt);
            expDig = attr.uintVal;
        } else if (attr.name == "mant_dig") {
            attr.checkKind(TsdlAttr::Kind::UInt);
            mantDig = attr.uintVal;
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
        FixedLengthFloatingPointNumberType::create(align, expDig + mantDig, bo, bioFromBo(bo)),
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

    // try to parse `{`
    if (!_ss.tryScanToken("{")) {
        return std::make_unique<PseudoScalarDtWrapper>(std::make_unique<const NullTerminatedStringType>(8),
                                                       beginLoc);
    }

    // parse attributes
    _tAttrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
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

    return std::make_unique<PseudoScalarDtWrapper>(std::make_unique<const NullTerminatedStringType>(8),
                                                   beginLoc);
}

PseudoDt::Up TsdlParser::_tryParseFlEnumType(const bool addDtAlias,
                                             std::string * const dtAliasName)
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `enum`
    if (!_ss.tryScanToken("enum")) {
        return nullptr;
    }

    // try to parse name
    std::string potDtAliasName;

    if (const auto ident = _ss.tryScanIdent()) {
        potDtAliasName = "enum ";
        potDtAliasName += *ident;

        if (dtAliasName) {
            *dtAliasName = potDtAliasName;
        }
    }

    {
        StrScannerRejecter ssRejOp {_ss};

        if (!_ss.tryScanToken(":") && !_ss.tryScanToken("{")) {
            return nullptr;
        }
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
        std::string dtAliasName;

        if (this->_parseDtAliasName(dtAliasName, false)) {
            // find data type alias
            pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc);

            if (!pseudoDt) {
                std::ostringstream ss;

                ss << "Cannot find data type alias `" << dtAliasName << "`.";
                throwTextParseError(ss.str(), loc);
            }

            if (!pseudoDt->isInt()) {
                std::ostringstream ss;

                ss << "Data type alias `" << dtAliasName << "` isn't an integer type.";
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

    if (pseudoDt->isUInt()) {
        return this->_finishParseFlEnumType<FixedLengthUnsignedIntegerType>(std::move(pseudoDt),
                                                                            addDtAlias,
                                                                            std::move(potDtAliasName),
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
        return this->_finishParseFlEnumType<FixedLengthSignedIntegerType>(std::move(pseudoDt), addDtAlias,
                                                                          std::move(potDtAliasName),
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
}

PseudoDt::Up TsdlParser::_tryParseStructType(const bool addDtAlias,
                                             std::string * const dtAliasName)
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `struct`
    if (!_ss.tryScanToken("struct")) {
        return nullptr;
    }

    // try to parse name
    std::string potDtAliasName;
    PseudoDt::Up pseudoDt;

    {
        _tLexScope dtAliasLexScope;

        if (const auto ident = _ss.tryScanIdent()) {
            potDtAliasName = "struct ";
            potDtAliasName += *ident;

            if (dtAliasName) {
                dtAliasLexScope = _tLexScope {*this, _tStackFrame::Kind::DtAlias};
                *dtAliasName = potDtAliasName;
            }
        }

        {
            _tLexScope structTypeLexScope {*this, _tStackFrame::Kind::StructType};
            const auto lexId = this->_stackTop().lexId;

            // parse `{`
            if (!_ss.tryScanToken("{")) {
                return nullptr;
            }

            // parse data type aliases and member types
            PseudoNamedDts pseudoMemberTypes;

            while (true) {
                this->_skipCommentsAndWhitespacesAndSemicolons();

                if (_ss.tryScanToken("}")) {
                    break;
                }

                const auto loc = _ss.loc();
                bool success;

                try {
                    success = this->_tryParseNamedDtOrDtAlias(pseudoMemberTypes);
                } catch (TextParseError& exc) {
                    appendMsgToTextParseError(exc, "While parsing body of `struct` block:", loc);
                    throw;
                }

                if (!success) {
                    throwTextParseError("Expecting member type with known data type "
                                        "or data type alias.",
                                        _ss.loc());
                }
            }

            ssRej.accept();

            // check for duplicate member type
            TsdlParser::_checkDupPseudoNamedDt(pseudoMemberTypes, beginLoc);

            auto align = 1ULL;

            if (_ss.tryScanToken("align")) {
                this->_expectToken("(");

                if (const auto optAlign = _ss.tryScanConstUInt()) {
                    if (!isPowOfTwo(*optAlign)) {
                        std::ostringstream ss;

                        ss << "Invalid minimum alignment for `struct` block " <<
                              "(must be a power of two): " << *optAlign << ".";
                        throwTextParseError(ss.str(), _ss.loc());
                    }

                    align = *optAlign;
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

    if (addDtAlias && !potDtAliasName.empty()) {
        this->_addDtAlias(std::move(potDtAliasName), *pseudoDt);
    }

    return pseudoDt;
}

PseudoDt::Up TsdlParser::_tryParseVarType(const bool addDtAlias, std::string * const dtAliasName)
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse `variant`
    if (!_ss.tryScanToken("variant")) {
        return nullptr;
    }

    // try to parse name
    std::string potDtAliasName;
    PseudoDt::Up pseudoDt;

    {
        _tLexScope dtAliasLexScope;

        if (const auto ident = _ss.tryScanIdent()) {
            potDtAliasName = "variant ";
            potDtAliasName += *ident;

            if (dtAliasName) {
                dtAliasLexScope = _tLexScope {*this, _tStackFrame::Kind::DtAlias};
                *dtAliasName = potDtAliasName;
            }
        }

        {
            _tLexScope varTypeLexScope {*this, _tStackFrame::Kind::VarType};

            // try to parse `<`
            boost::optional<PseudoDataLoc> pseudoDataLoc;

            if (_ss.tryScanToken("<")) {
                pseudoDataLoc = this->_expectDataLoc();
                assert(pseudoDataLoc);

                if (pseudoDataLoc->kind() == PseudoDataLoc::Kind::Env) {
                    throwTextParseError("Selector location of variant type "
                                        "cannot start with `env.`.",
                                        _ss.loc());
                }

                this->_expectToken(">");
            }

            // parse `{`
            if (!_ss.tryScanToken("{")) {
                return nullptr;
            }

            // parse data type aliases and options
            PseudoNamedDts opts;

            while (true) {
                this->_skipCommentsAndWhitespacesAndSemicolons();

                if (_ss.tryScanToken("}")) {
                    break;
                }

                const auto loc = _ss.loc();
                bool success;

                try {
                    success = this->_tryParseNamedDtOrDtAlias(opts);
                } catch (TextParseError& exc) {
                    appendMsgToTextParseError(exc, "While parsing body of `variant` block:", loc);
                    throw;
                }

                if (!success) {
                    throwTextParseError("Expecting option or data type alias.", _ss.loc());
                }
            }

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

    if (addDtAlias && !potDtAliasName.empty()) {
        this->_addDtAlias(std::move(potDtAliasName), *pseudoDt);
    }

    return pseudoDt;
}

bool TsdlParser::_tryParseEnvBlock()
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();

    // parse `env`
    if (!_ss.tryScanToken("env")) {
        return false;
    }

    if (_envParsed) {
        throwTextParseError("Duplicate `env` block.", loc);
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");

    if (!_pseudoTraceType) {
        // first pass: skip
        return true;
    }

    // check for duplicate attributes
    TsdlParser::_checkDupAttr(attrs);

    TraceEnvironment::Entries entries;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.kind != TsdlAttr::Kind::SInt && attr.kind != TsdlAttr::Kind::UInt
                && attr.kind != TsdlAttr::Kind::Str) {
            std::ostringstream ss;

            ss << "Trace environment entry `" << attr.name <<
                  "`: expecting constant integer or literal string.";
            throwTextParseError(ss.str(), attr.valTextLoc());
        }

        TraceEnvironment::Entry entry;

        if (attr.kind == TsdlAttr::Kind::SInt) {
            entry = attr.intVal;
        } else if (attr.kind == TsdlAttr::Kind::UInt) {
            if (attr.uintVal >= (1ULL << 63)) {
                std::ostringstream ss;

                ss << "Trace environment entry `" << attr.name <<
                      "`: value " << attr.uintVal << " is too large " <<
                      "(expecting a 64-bit signed integer).";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            entry = static_cast<long long>(attr.uintVal);
        } else if (attr.kind == TsdlAttr::Kind::Str) {
            entry = attr.strVal;
        }

        entries[attr.name] = std::move(entry);
    }

    assert(_pseudoTraceType);
    _pseudoTraceType->env(TraceEnvironment {std::move(entries)});
    _envParsed = true;
    return true;
}

bool TsdlParser::_tryParseCallsiteBlock()
{
    // parse `callsite`
    if (!_ss.tryScanToken("callsite")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;

    // pretty loose: we accept everything, even duplicates
    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
            break;
        }

        // parse attribute
        attrs.push_back(this->_expectAttr());
    }

    // parse `;`
    this->_expectToken(";");
    return true;
}

bool TsdlParser::_tryParseClkTypeBlock()
{
    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = _ss.loc();

    // parse `clock`
    if (!_ss.tryScanToken("clock")) {
        return false;
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _tAttrs attrs;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
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
    boost::optional<std::string> uuidStr;
    boost::optional<boost::uuids::uuid> uuid;
    auto freq = 1'000'000'000ULL;
    boost::optional<Cycles> prec;
    auto offsetSecs = 0LL;
    Cycles offsetCycles = 0;
    auto isAbs = false;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "name") {
            if (attr.kind != TsdlAttr::Kind::Ident && attr.kind != TsdlAttr::Kind::Str) {
                std::ostringstream ss;

                ss << "Attribute `name`: expecting identifier or literal string.";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            name = attr.strVal;
        } else if (attr.name == "description") {
            attr.checkKind(TsdlAttr::Kind::Str);
            descr = attr.strVal;
        } else if (attr.name == "uuid") {
            attr.checkKind(TsdlAttr::Kind::Str);
            uuid = TsdlParser::_uuidFromStr(attr.strVal);

            if (!uuid) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            uuidStr = attr.strVal;
        } else if (attr.name == "freq") {
            attr.checkKind(TsdlAttr::Kind::UInt);

            if (attr.uintVal == 0) {
                std::ostringstream ss;

                ss << "Invalid `freq` attribute (must be greater than 0): " <<
                      attr.uintVal << ".";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            freq = static_cast<unsigned long long>(attr.uintVal);
        } else if (attr.name == "precision") {
            attr.checkKind(TsdlAttr::Kind::UInt);
            prec = attr.uintVal;
        } else if (attr.name == "offset_s") {
            if (attr.kind != TsdlAttr::Kind::SInt && attr.kind != TsdlAttr::Kind::UInt) {
                throwTextParseError("Attribute `offset_s`: expecting constant signed integer.",
                                    attr.valTextLoc());
            }

            if (attr.kind == TsdlAttr::Kind::UInt) {
                if (attr.uintVal > static_cast<decltype(attr.uintVal)>(std::numeric_limits<long long>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `offset_s`: value is too large: " << attr.uintVal << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
                }

                offsetSecs = static_cast<long long>(attr.uintVal);
            } else {
                offsetSecs = attr.intVal;
            }
        } else if (attr.name == "offset") {
            attr.checkKind(TsdlAttr::Kind::UInt);
            offsetCycles = static_cast<Cycles>(attr.uintVal);
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

    if (!_pseudoTraceType) {
        return true;
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

        // TODO: throw if this would cause a `long long` overflow
        offsetSecs += completeSecsInOffsetCycles;
    }

    // create origin
    auto origin = call([&isAbs, this]() -> boost::optional<ClockOrigin> {
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
                if (const auto entryVal = boost::get<std::string>(entry)) {
                    if (boost::algorithm::starts_with(*entryVal, "lttng-")) {
                        return ClockOrigin {};
                    }
                }
            }
        }

        return boost::none;
    });

    _pseudoTraceType->clkTypes().insert(ClockType::create(name, boost::none, name, std::move(uuidStr),
                                                          std::move(uuid), freq, descr,
                                                          std::move(origin), std::move(prec),
                                                          boost::none,
                                                          ClockOffset {offsetSecs, offsetCycles}));
    return true;
}

bool TsdlParser::_tryParseTraceTypeBlock()
{
    _tLexScope lexScope {*this, _tStackFrame::Kind::TraceType};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = _ss.loc();

    // parse `trace`
    if (!_ss.tryScanToken("trace")) {
        return false;
    }

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
            if (auto pseudoDt = this->_tryParseScopeDt(_tStackFrame::Kind::PktHeaderType,
                                                       "packet", "header")) {
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

    boost::optional<unsigned int> majorVersion;
    boost::optional<unsigned int> minorVersion;
    boost::optional<ByteOrder> nativeBo;
    boost::optional<std::string> uuidStr;

    // check attributes
    for (const auto& attr : attrs) {
        if (attr.name == "major" || attr.name == "minor") {
            attr.checkKind(TsdlAttr::Kind::UInt);

            if (attr.name == "major") {
                if (attr.uintVal != 1) {
                    std::ostringstream ss;

                    ss << "Invalid `major` attribute: " <<
                          "unsupported major version (expecting 1): " <<
                          attr.uintVal << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
                }

                majorVersion = attr.uintVal;
            } else if (attr.name == "minor") {
                if (attr.uintVal != 8) {
                    std::ostringstream ss;

                    ss << "Invalid `minor` attribute: " <<
                          "unsupported minor version (expecting 8): " <<
                          attr.uintVal << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
                }

                minorVersion = attr.uintVal;
            }
        } else if (attr.name == "byte_order") {
            nativeBo = attr.bo();

            if (!nativeBo) {
                throwTextParseError("Invalid `byte_order` attribute: cannot be `native` here.",
                                    attr.valTextLoc());
            }
        } else if (attr.name == "uuid") {
            attr.checkKind(TsdlAttr::Kind::Str);

            if (attr.strVal.size() != 36) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            if (!TsdlParser::_uuidFromStr(attr.strVal)) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            uuidStr = attr.strVal;
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
        PseudoTraceType pseudoTraceType {
            *majorVersion, *minorVersion, boost::none, boost::none, std::move(uuidStr),
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

        /*
         * Placeholder pseudo trace type for the root blocks which
         * precede the `trace` block during the second pass.
         */
        _pseudoTraceType = PseudoTraceType {*majorVersion, *minorVersion};
    }

    return true;
}

bool TsdlParser::_tryParseDstBlock()
{
    _tLexScope lexScope {*this, _tStackFrame::Kind::Dst};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = _ss.loc();

    // parse `stream`
    if (!_ss.tryScanToken("stream")) {
        return false;
    }

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
            if (auto pseudoDt = this->_tryParseScopeDt(_tStackFrame::Kind::PktCtxType,
                                                       "packet", "context")) {
                if (pseudoPktCtxType) {
                    throwTextParseError("Duplicate `packet.context` scope.", _ss.loc());
                }

                pseudoPktCtxType = std::move(pseudoDt);
                continue;
            }
        } else if (kw == _tKw::Event) {
            // try to parse event record header type
            if (auto pseudoDt = this->_tryParseScopeDt(_tStackFrame::Kind::ErHeaderType,
                                                       "event", "header", false)) {
                if (pseudoErHeaderType) {
                    throwTextParseError("Duplicate `event.header` scope.", _ss.loc());
                }

                pseudoErHeaderType = std::move(pseudoDt);
                continue;
            }

            // try to parse event record common context type
            if (auto pseudoDt = this->_tryParseScopeDt(_tStackFrame::Kind::ErCommonCtxType,
                                                       "event", "context", false)) {
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
            attr.checkKind(TsdlAttr::Kind::UInt);
            id = attr.uintVal;
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
    _pseudoTraceType->pseudoDsts().insert(std::make_pair(
        id,
        std::make_unique<PseudoDst>(id, boost::none, boost::none, boost::none,
                                    std::move(pseudoPktCtxType), std::move(pseudoErHeaderType),
                                    std::move(pseudoErCommonCtxType), nullptr, nullptr,
                                    beginLoc)
    ));
    _pseudoTraceType->pseudoOrphanErts()[id];
    return true;
}

bool TsdlParser::_tryParseErtBlock()
{
    _tLexScope lexScope {*this, _tStackFrame::Kind::Ert};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = _ss.loc();

    // parse `event`
    if (!_ss.tryScanToken("event")) {
        return false;
    }

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
            if (auto pseudoDt = this->_tryParseScopeDt(_tStackFrame::Kind::ErSpecCtxType,
                                                       "context")) {
                if (pseudoSpecCtxType) {
                    throwTextParseError("Duplicate `event.context` scope.", _ss.loc());
                }

                pseudoSpecCtxType = std::move(pseudoDt);
                continue;
            }
        } else if (kw == _tKw::Fields) {
            // try to parse payload type
            if (auto pseudoDt = this->_tryParseScopeDt(_tStackFrame::Kind::ErPayloadType,
                                                       "fields")) {
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
            attr.checkKind(TsdlAttr::Kind::UInt);
            id = attr.uintVal;
        } else if (attr.name == "stream_id") {
            attr.checkKind(TsdlAttr::Kind::UInt);
            dstId = attr.uintVal;
        } else if (attr.name == "loglevel") {
            if (attr.kind != TsdlAttr::Kind::SInt && attr.kind != TsdlAttr::Kind::UInt) {
                throwTextParseError("Attribute `loglevel`: expecting constant signed integer.",
                                    attr.valTextLoc());
            }

            if (attr.kind == TsdlAttr::Kind::UInt) {
                if (attr.uintVal > static_cast<decltype(attr.uintVal)>(std::numeric_limits<LogLevel>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `loglevel`: value is too large: " << attr.uintVal << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
                }

                logLevel = static_cast<LogLevel>(attr.uintVal);
            } else {
                logLevel = static_cast<LogLevel>(attr.intVal);
            }
        } else if (attr.name == "model.emf.uri") {
            attr.checkKind(TsdlAttr::Kind::Str);
            emfUri = attr.strVal;
        } else if (attr.name == "name") {
            if (attr.kind != TsdlAttr::Kind::Ident && attr.kind != TsdlAttr::Kind::Str) {
                std::ostringstream ss;

                ss << "Attribute `name`: expecting identifier or literal string.";
                throwTextParseError(ss.str(), attr.valTextLoc());
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
        throwTextParseError(ss.str(), beginLoc);
    }

    // build event record type object
    dstPseudoOrphanErts.insert(std::make_pair(id, PseudoOrphanErt {
        PseudoErt {
            id, boost::none, std::move(name), boost::none, std::move(logLevel),
            std::move(emfUri), std::move(pseudoSpecCtxType),
            std::move(pseudoPayloadType), nullptr, beginLoc
        },
        beginLoc
    }));

    return true;
}

PseudoDt::Up TsdlParser::_tryParseScopeDt(const _tStackFrame::Kind scopeDtStackFrameKind,
                                                  const char * const firstName,
                                                  const char * const secondName, const bool expect)
{
    StrScannerRejecter ssRej {_ss};

    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // parse name
    if (!_ss.tryScanToken(firstName)) {
        return nullptr;
    }

    try {
        if (secondName) {
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
        PseudoDt::Up pseudoDt;
        std::string dtAliasName;

        {
            _tLexScope lexScope {*this, scopeDtStackFrameKind};

            /*
             * Don't let the structure type parser add a data type alias
             * for a named structure type: it would add it to the frame
             * which `lexScope` manages, which only exists while parsing
             * this scope data type.
             *
             * Add it to the current frame below instead.
             */
            pseudoDt = this->_tryParseDt(false, &dtAliasName);
        }

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
        return pseudoDt;
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, call([&firstName, &secondName] {
            auto line = std::string {"In the `"} + firstName;

            if (secondName) {
                line += ".";
                line += secondName;
            }

            return line + "` scope:";
        }), beginLoc);

        throw;
    }
}

TsdlAttr TsdlParser::_expectAttr()
{
    TsdlAttr attr;

    // parse name
    {
        auto nameIsFound = false;

        _ss.skipCommentsAndWhitespaces();
        attr.nameLoc = _ss.loc();

        if (_ss.tryScanToken("model.emf.uri")) {
            nameIsFound = true;
            attr.name = "model.emf.uri";
        } else if (const auto ident = _ss.tryScanIdent()) {
            nameIsFound = true;
            attr.name = *ident;
        }

        if (!nameIsFound) {
            throwTextParseError("Expecting attribute name.", *attr.nameLoc);
        }
    }

    // parse `=`
    this->_expectToken("=");

    // this it the source location of the attribute for an eventual error
    _ss.skipCommentsAndWhitespaces();
    attr.valLoc = _ss.loc();

    // special case for the `map` attribute
    if (attr.name == "map") {
        attr.kind = TsdlAttr::Kind::ClkNameValue;

        // parse `clock`
        this->_expectToken("clock");

        // parse `.`
        this->_expectToken(".");

        // parse internal ID (name) of clock type
        if (const auto ident = _ss.tryScanIdent()) {
            attr.strVal = *ident;
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
        attr.strVal = *escapedStr;
        attr.kind = TsdlAttr::Kind::Str;
    } else if (const auto ident = _ss.tryScanIdent()) {
        // identifier
        attr.strVal = *ident;
        attr.kind = TsdlAttr::Kind::Ident;
    } else if (const auto val = _ss.tryScanConstUInt()) {
        // constant unsigned integer
        attr.uintVal = *val;
        attr.kind = TsdlAttr::Kind::UInt;
    } else if (const auto val = _ss.tryScanConstSInt()) {
        // constant signed integer
        attr.intVal = *val;
        attr.kind = TsdlAttr::Kind::SInt;
        assert(attr.intVal != 0 && attr.intVal != 1);
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
                    if (!_ss.tryScanToken("{") && !_ss.tryScanToken(":")) {
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

                auto& pseudoVarType = static_cast<PseudoVarType&>(*pseudoDt);

                if (pseudoVarType.pseudoSelLoc()) {
                    ssRej.accept();
                    return pseudoDt;
                }

                if (_ss.tryScanToken("<")) {
                    _ss.skipCommentsAndWhitespaces();

                    const auto selLoc = _ss.loc();
                    auto pseudoSelLoc = this->_expectDataLoc();

                    if (pseudoSelLoc.kind() == PseudoDataLoc::Kind::Env) {
                        throwTextParseError("Selector location of variant type cannot start with `env.`.",
                                            selLoc);
                    }

                    this->_expectToken(">");

                    if (!_ss.tryScanToken("{")) {
                        /*
                         * Create new pseudo variant type with this
                         * selector location.
                         */
                        auto pseudoDtClone = pseudoDt->clone();

                        static_cast<PseudoVarType&>(*pseudoDtClone).pseudoSelLoc(std::move(pseudoSelLoc));
                        ssRej.accept();
                        return pseudoDtClone;
                    }
                }
            }
        }
    }

    // try data type alias name
    {
        StrScannerRejecter ssRej {_ss};
        std::string dtAliasName;

        if (this->_parseDtAliasName(dtAliasName, false)) {
            if (auto pseudoDt = this->_aliasedPseudoDt(dtAliasName, beginLoc)) {
                ssRej.accept();
                return pseudoDt;
            }
        }
    }

    return nullptr;
}

bool TsdlParser::_parseDtAliasName(std::string& dtAliasName, const bool expect)
{
    auto isMulti = false;
    std::vector<std::string> parts;

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
                return false;
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
        parts.push_back(*ident);

        if (!isMulti) {
            // single word data type alias name: break now
            break;
        }
    }

    if (parts.empty()) {
        if (expect) {
            throwTextParseError("Expecting data type alias name.", _ss.loc());
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

PseudoDataLoc TsdlParser::_expectDataLoc()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();
    PseudoDataLoc::PathElems allPathElems;

    while (true) {
        if (const auto ident = _ss.tryScanIdent()) {
            allPathElems.push_back(*ident);

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

PseudoDt::Up TsdlParser::_tryParseIdentArraySubscripts(std::string& ident,
                                                       PseudoDt::Up innerPseudoDt)
{
    // parse identifier
    if (const auto identRes = _ss.tryScanIdent()) {
        ident = *identRes;
        return this->_parseArraySubscripts(std::move(innerPseudoDt));
    }

    return nullptr;
}

PseudoDt::Up TsdlParser::_parseArraySubscripts(PseudoDt::Up innerPseudoDt)
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

            lenDescrs.push_back({true, boost::none, static_cast<Size>(*val), subscriptLoc});
        } else {
            boost::optional<PseudoDataLoc> pseudoDataLoc;

            try {
                pseudoDataLoc = this->_expectDataLoc();
            } catch (TextParseError& exc) {
                appendMsgToTextParseError(exc,
                                          "Expecting valid constant integer (static-length array type) or valid data location (dynamic-length array type):",
                                          subscriptLoc);
                throw;
            }

            assert(pseudoDataLoc);

            if (pseudoDataLoc->kind() == PseudoDataLoc::Kind::Env) {
                // only the `env.KEY` format is accepted
                if (pseudoDataLoc->pathElems().size() != 1) {
                    throwTextParseError("Invalid environment location: expecting `env.KEY`, "
                                        "where KEY is the key of an existing environment entry.",
                                        subscriptLoc);
                }

                const auto& envKey = *pseudoDataLoc->pathElems()[0];

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

                if (const auto entryVal = boost::get<long long>(entry)) {
                    if (*entryVal < 0) {
                        std::ostringstream ss;

                        ss << "Static-length array type cannot have a negative size: " << *entryVal << ".";
                        throwTextParseError(ss.str(), subscriptLoc);
                    }

                    lenDescrs.push_back({true, boost::none, static_cast<Size>(*entryVal),
                                        subscriptLoc});
                } else {
                    std::ostringstream ss;

                    ss << "Environment entry `" << envKey <<
                          "` isn't a valid static-length array type size.";
                    throwTextParseError(ss.str(), subscriptLoc);
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
     * arrays of `len` static-length arrays of four
     * null-terminated strings.
     *
     * At this point, `innerPseudoDt` is the null-terminated string type
     * in the example above.
     */
    for (const auto& lenDescr : boost::adaptors::reverse(lenDescrs)) {
        if (lenDescr.isStatic) {
            innerPseudoDt = std::make_unique<PseudoSlArrayType>(lenDescr.arrayLen,
                                                                std::move(innerPseudoDt), nullptr,
                                                                lenDescr.loc);
        } else {
            assert(lenDescr.dlArrayLenLoc);
            innerPseudoDt = std::make_unique<PseudoDlArrayType>(*lenDescr.dlArrayLenLoc,
                                                                std::move(innerPseudoDt), nullptr,
                                                                lenDescr.loc);
        }
    }

    return innerPseudoDt;
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

    {
        StrScannerRejecter ssRej {_ss};
        const auto dtLoc = _ss.loc();

        if (auto pseudoDt = this->_tryParseDtAliasRef()) {
            std::string ident;

            // let's try parsing an identifier + array subscripts
            if (auto effectivePseudoDt = this->_tryParseIdentArraySubscripts(ident,
                                                                             std::move(pseudoDt))) {
                /*
                 * We have a winner: variant type must have a selector
                 * location at this point.
                 */
                if (TsdlParser::_isPseudoVarTypeWithoutSelLocRec(*effectivePseudoDt)) {
                    throwTextParseError("Variant type needs a selector location here.", dtLoc);
                }

                pseudoNamedDts.push_back(std::make_unique<PseudoNamedDt>(ident,
                                                                         std::move(effectivePseudoDt)));
                this->_expectToken(";");
                ssRej.accept();
                this->_stackTop().idents.push_back(ident);
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
        std::string dtAliasName;
        auto isCompound = false;

        if (auto pseudoDt = this->_tryParseFullDt(false, &dtAliasName, &isCompound)) {
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

            // let's try parsing an identifier + array subscripts
            std::string ident;

            if (auto effectivePseudoDt = this->_tryParseIdentArraySubscripts(ident,
                                                                             std::move(pseudoDt))) {
                /*
                 * We have a winner: variant type must have a selector
                 * location at this point.
                 */
                if (TsdlParser::_isPseudoVarTypeWithoutSelLocRec(*effectivePseudoDt)) {
                    throwTextParseError("Variant type needs a selector here.", _ss.loc());
                }

                pseudoNamedDts.push_back(std::make_unique<PseudoNamedDt>(ident,
                                                                         std::move(effectivePseudoDt)));
                this->_expectToken(";");
                ssRej.accept();
                this->_stackTop().idents.push_back(ident);
                return true;
            } else {
                /*
                 * If there's a type, but no identifier, and we know
                 * that it's not a data type alias, then we expect an
                 * identifier at this point.
                 */
                _ss.skipCommentsAndWhitespaces();
                throwTextParseError("Expecting identifier (member type/option name).",
                                    _ss.loc());
            }
        }
    }

    return false;
}

const std::string *TsdlParser::_tryScanLitStr()
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

    return nullptr;
}

TsdlParser::_tKw TsdlParser::_kwFromIdent(const std::string& ident) noexcept
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

    case 'a':
        if (ident == "align") {
            return _tKw::Align;
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

void TsdlParser::_skipCommentsAndWhitespacesAndSemicolons()
{
    while (true) {
        _ss.skipCommentsAndWhitespaces();

        if (!_ss.tryScanToken(";")) {
            break;
        }
    }
}

} // namespace internal
} // namespace yactfr
