/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "tsdl-parser.hpp"
#include "trace-type-from-pseudo-trace-type.hpp"
#include "../utils.hpp"

namespace yactfr {
namespace internal {

TsdlParser::_StackFrame::_StackFrame(const Kind kind) :
    kind {kind}
{
}

void TsdlParser::_setImplicitMappedClkTypeName(PseudoDt& basePseudoDt,
                                               const std::string& memberTypeName)
{
    /*
     * If there's exactly one clock type in the pseudo trace type:
     *     Use the name of this clock type.
     *
     * If there's no clock type in the pseudo trace type:
     *     Create a default 1-GHz clock type and use this name.
     *
     * If there's more than one clock type in the pseudo trace type:
     *     Leave it as is (no mapped clock type name).
     */
    for (auto& pseudoDt : findPseudoUIntTypesByName(basePseudoDt, memberTypeName)) {
        assert(pseudoDt->isFlUInt());

        auto& pseudoIntType = static_cast<PseudoFlUIntType&>(*pseudoDt);

        if (pseudoIntType.mappedClkTypeName()) {
            continue;
        }

        if (_pseudoTraceType->clkTypes().empty()) {
            // create implicit 1-GHz clock type
            _pseudoTraceType->clkTypes().insert(std::make_unique<const ClockType>(1'000'000'000ULL));
        }

        if (_pseudoTraceType->clkTypes().size() != 1) {
            // we don't know which clock type to choose: leave it unmapped
            continue;
        }

        const auto& clkType = *_pseudoTraceType->clkTypes().begin();

        assert(clkType->name());
        pseudoIntType.mappedClkTypeName(*clkType->name());
    }
}

void TsdlParser::_setImplicitMappedClkTypeName()
{
   for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        if (pseudoDst->pseudoErHeaderType()) {
            this->_setImplicitMappedClkTypeName(*pseudoDst->pseudoErHeaderType(), "timestamp");
        }

        if (pseudoDst->pseudoPktCtxType()) {
            this->_setImplicitMappedClkTypeName(*pseudoDst->pseudoPktCtxType(), "timestamp_begin");
            this->_setImplicitMappedClkTypeName(*pseudoDst->pseudoPktCtxType(), "timestamp_end");
        }
    }
}

void TsdlParser::_setPseudoSlArrayTypeTraceTypeUuidRole(PseudoDt& basePseudoDt,
                                                        const std::string& memberTypeName)
{
    const auto pseudoDts = findPseudoDtsByName(basePseudoDt, memberTypeName,
                                               [](auto& pseudoDt) {
        if (pseudoDt.kind() != PseudoDt::Kind::SL_ARRAY) {
            return false;
        }

        auto& pseudoArrayType = static_cast<const PseudoSlArrayType&>(pseudoDt);

        if (pseudoArrayType.len() != 16) {
            return false;
        }

        if (!pseudoArrayType.pseudoElemType().isUInt()) {
            return false;
        }

        assert(pseudoArrayType.pseudoElemType().isFlUInt());

        auto& pseudoElemDt = static_cast<const PseudoFlUIntType&>(pseudoArrayType.pseudoElemType());

        if (pseudoElemDt.len() != 8) {
            return false;
        }

        if (pseudoElemDt.align() != 8) {
            return false;
        }

        return true;
    });

    for (auto& pseudoDt : pseudoDts) {
        auto& pseudoArrayType = static_cast<PseudoSlArrayType&>(*pseudoDt);

        pseudoArrayType.hasTraceTypeUuidRole(true);
    }
}

class DefClkTsRoleAdder :
    public PseudoDtVisitor
{
public:
    explicit DefClkTsRoleAdder() = default;

    void visit(PseudoFlUIntType& pseudoDt) override
    {
        if (pseudoDt.mappedClkTypeName() &&
                !pseudoDt.hasRole(UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP)) {
            pseudoDt.addRole(UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP);
        }
    }

    void visit(PseudoFlUEnumType& pseudoDt) override
    {
        this->visit(static_cast<PseudoFlUIntType&>(pseudoDt));
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
     * First, set an implicit mapped clock type name on specific pseudo
     * fixed-length unsigned integer types.
     *
     * For example, if the current pseudo trace type contains a single
     * clock type, then any pseudo fixed-length unsigned integer type
     * named `timestamp` within pseudo event record header types, which
     * are not already mapped to a clock type, are mapped to this single
     * clock type.
     */
    this->_setImplicitMappedClkTypeName();

    // add/set simple roles
    if (_pseudoTraceType->pseudoPktHeaderType()) {
        this->_addPseudoFlUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(), "magic",
                                        UnsignedIntegerTypeRole::PACKET_MAGIC_NUMBER);
        this->_addPseudoFlUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(), "stream_id",
                                        UnsignedIntegerTypeRole::DATA_STREAM_TYPE_ID);
        this->_addPseudoFlUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(),
                                        "stream_instance_id",
                                        UnsignedIntegerTypeRole::DATA_STREAM_ID);
        this->_setPseudoSlArrayTypeTraceTypeUuidRole(*_pseudoTraceType->pseudoPktHeaderType(),
                                                     "uuid");
    }

    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        if (pseudoDst->pseudoPktCtxType()) {
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_size",
                                            UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "content_size",
                                            UnsignedIntegerTypeRole::PACKET_CONTENT_LENGTH);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_size",
                                            UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH);
            this->_addPseudoFlUIntTypeRoles<true>(*pseudoDst->pseudoPktCtxType(), "timestamp_end",
                                                  UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "discarded_events",
                                            UnsignedIntegerTypeRole::DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT);
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_seq_num",
                                            UnsignedIntegerTypeRole::PACKET_ORIGIN_INDEX);
        }

        if (pseudoDst->pseudoErHeaderType()) {
            this->_addPseudoFlUIntTypeRoles(*pseudoDst->pseudoErHeaderType(), "id",
                                            UnsignedIntegerTypeRole::EVENT_RECORD_TYPE_ID);
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
        if (pseudoDt.mappedClkTypeName()) {
            if (!_clkTypeName) {
                _clkTypeName = &*pseudoDt.mappedClkTypeName();
            }

            if (*pseudoDt.mappedClkTypeName() != *_clkTypeName) {
                std::ostringstream ss;

                ss << "Unsigned fixed-length integer type is mapped to a clock type (`" <<
                      *pseudoDt.mappedClkTypeName() << "` which is "
                      "different than another mapped clock type (`" <<
                      *_clkTypeName << "`) within the same data stream type.";
                throwTextParseError(ss.str(), pseudoDt.loc());
            }

            if (!_pseudoDst->defClkType()) {
                for (auto& clkType : _pseudoTraceType->clkTypes()) {
                    assert(clkType->name());

                    if (*clkType->name() == *_clkTypeName) {
                        _pseudoDst->defClkType(*clkType);
                    }
                }

                if (!_pseudoDst->defClkType()) {
                    // not found
                    std::ostringstream ss;

                    ss << "`" << *_clkTypeName << "` doesn't name an existing clock type.";
                    throwTextParseError(ss.str(), pseudoDt.loc());
                }
            }
        }
    }

    void visit(PseudoFlUEnumType& pseudoDt) override
    {
        this->visit(static_cast<PseudoFlUIntType&>(pseudoDt));
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
    const std::string *_clkTypeName = nullptr;
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
        appendMsgToTextParseError(exc, ss.str());
        throw;
    }
}

void TsdlParser::_setPseudoDstDefClkType()
{
    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        this->_setPseudoDstDefClkType(*pseudoDst);
    }
}

void TsdlParser::_stackPush(const _StackFrame::Kind kind)
{
    _stack.push_back(_StackFrame {kind});
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
    const auto it = _pseudoTraceType->pseudoOrphanErts().find(0);

    if (it != _pseudoTraceType->pseudoOrphanErts().end() && !it->second.empty() &&
            _pseudoTraceType->pseudoDsts().empty()) {
        _pseudoTraceType->pseudoDsts()[0] = std::make_unique<PseudoDst>();
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
        if (entryNames.find(entry->name()) != entryNames.end()) {
            std::ostringstream ss;

            ss << "Duplicate identifier (member type or option name) `" << entry->name() << "`.";
            throwTextParseError(ss.str(), loc);
        }

        entryNames.insert(entry->name());
    }
}

bool TsdlParser::_isPseudoVarTypeWithoutSelLocRec(const PseudoDt& pseudoDt)
{
    if (pseudoDt.kind() == PseudoDt::Kind::SL_ARRAY ||
            pseudoDt.kind() == PseudoDt::Kind::DL_ARRAY) {
        auto& pseudoArrayType = static_cast<const PseudoArrayType&>(pseudoDt);

        return TsdlParser::_isPseudoVarTypeWithoutSelLocRec(pseudoArrayType.pseudoElemType());
    }

    if (pseudoDt.kind() != PseudoDt::Kind::VAR) {
        return false;
    }

    auto& pseudoVarType = static_cast<const PseudoVarType&>(pseudoDt);

    return !pseudoVarType.pseudoSelLoc().has_value();
}

void TsdlParser::_checkDupAttr(const _Attrs& attrs)
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

boost::optional<PseudoDataLoc> TsdlParser::_pseudoDataLocFromAbsAllPathElems(const DataLocation::PathElements& allPathElems,
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
                throwTextParseError("Expecting `packet.header` after `trace.`.", loc);
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
                throwTextParseError("Expecting `packet.context`, `event.header`, or "
                                    "`event.context` after `stream.`.", loc);
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
                throwTextParseError("Expecting `context` or `fields` after `event.`.", loc);
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

boost::optional<PseudoDataLoc> TsdlParser::_pseudoDataLocFromRelAllPathElems(const DataLocation::PathElements& allPathElems,
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
     * the dynamic-length array type `seq[a]` contained in `my_struct b`
     * is NOT `int a` immediately before, but rather `my_int a`. In
     * practice, this trick of using a data type which is external to a
     * data type alias for dynamic-length array type lengths or variant
     * type selectors is rarely, if ever, used.
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
            throwTextParseError(ss.str(), loc);
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
            throwTextParseError(ss.str(), loc);
        }

        --stackIt;
    }

    return boost::none;
}

PseudoDataLoc TsdlParser::_pseudoDataLocFromAllPathElems(const DataLocation::PathElements& allPathElems,
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

    throwTextParseError("Invalid data location.", loc);
}

void TsdlParser::_addDtAlias(std::string&& name, const PseudoDt& pseudoDt,
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

PseudoDt::UP TsdlParser::_aliasedPseudoDt(const std::string& name, TextLocation loc) const
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

void TsdlParser::_parseMetadata()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::ROOT};

    while (this->_tryParseRootBlock());

    // make sure we skip the remaining fruitless stuff
    this->_skipCommentsAndWhitespacesAndSemicolons();

    if (!_ss.isDone()) {
        throwTextParseError("Expecting data type alias (`typealias`, `typedef`, `enum NAME`, "
                            "`struct NAME`, or `variant NAME`), trace type block (`trace`), "
                            "environment block of trace type (`env`), "
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

    if (this->_tryParseDtAlias()) {
        return true;
    }

    try {
        if (this->_tryParseErtBlock()) {
            return true;
        }
    } catch (TextParseError& error) {
        appendMsgToTextParseError(error, "In `event` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseDstBlock()) {
            return true;
        }
    } catch (TextParseError& error) {
        appendMsgToTextParseError(error, "In `stream` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseTraceTypeBlock()) {
            return true;
        }
    } catch (TextParseError& error) {
        appendMsgToTextParseError(error, "In `trace` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseEnvBlock()) {
            return true;
        }
    } catch (TextParseError& error) {
        appendMsgToTextParseError(error, "In `env` root block:", loc);
        throw;
    }

    try {
        if (this->_tryParseClkTypeBlock()) {
            return true;
        }
    } catch (TextParseError& error) {
        appendMsgToTextParseError(error, "In `clock` root block:", loc);
        throw;
    }

    try {
        // parse callsite, even if we don't care about it
        if (this->_tryParseCallsiteBlock()) {
            return true;
        }
    } catch (TextParseError& error) {
        appendMsgToTextParseError(error, "In `callsite` root block:", loc);
        throw;
    }

    return false;
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
    PseudoDt::UP pseudoDt;
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

bool TsdlParser::_tryParseGenericDtAlias()
{
    bool isTypealias = false;

    if (_ss.tryScanToken("typealias")) {
        isTypealias = true;
    } else if (!_ss.tryScanToken("typedef")) {
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

    const auto loc = _ss.loc();

    try {
        if (this->_tryParseGenericDtAlias()) {
            return true;
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In data type alias:", loc);
        throw;
    }

    if (this->_tryParseFlEnumStructVarDtAlias()) {
        return true;
    }

    return false;
}

PseudoDt::UP TsdlParser::_tryParseDt()
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

PseudoDt::UP TsdlParser::_tryParseFullDt()
{
    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();
    PseudoDt::UP pseudoDt;

    try {
        pseudoDt = this->_tryParseFlIntType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In `integer` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseNtStrType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In `string` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseFlEnumType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In `enum` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseFlFloatType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In `floating_point` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseStructType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In `struct` block:", loc);
        throw;
    }

    try {
        pseudoDt = this->_tryParseVarType();

        if (pseudoDt) {
            return pseudoDt;
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In `variant` block:", loc);
        throw;
    }

    return nullptr;
}

void TsdlParser::_insertFastPseudoFlIntType(const char * const begin, const char * const end,
                                            const PseudoDt& pseudoDt)
{
    assert(end >= begin);

    if (static_cast<Size>(end - begin) > TsdlParser::_MAX_FAST_FL_INT_TYPE_STR_SIZE) {
        return;
    }

    _fastPseudoFlIntTypes.push_back({begin, end, pseudoDt.clone()});
}

PseudoDt::UP TsdlParser::_fastPseudoFlIntType(TextLocation loc)
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

PseudoDt::UP TsdlParser::_tryParseFlIntType()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beforeKwLoc = _ss.loc();

    // parse `integer`
    if (!_ss.tryScanToken("integer")) {
        return nullptr;
    }

    _ss.skipCommentsAndWhitespaces();

    auto fastPseudoFlIntType = this->_fastPseudoFlIntType(beforeKwLoc);

    if (fastPseudoFlIntType) {
        return fastPseudoFlIntType;
    }

    const auto beginLoc = _ss.loc();
    const auto beginAt = _ss.at();

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;

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
            throwTextParseError("Illegal `map` attribute for a fixed-length signed integer type.",
                                *mapAttrLoc);
        }

        auto intType = std::make_unique<const FixedLengthSignedIntegerType>(align, size, bo, dispBase);

        pseudoDt = std::make_unique<PseudoScalarDtWrapper>(std::move(intType), hasEncoding,
                                                           nullptr, beforeKwLoc);
    } else {
        pseudoDt = std::make_unique<PseudoFlUIntType>(align, size, bo, dispBase, hasEncoding,
                                                      mappedClkTypeName, nullptr, beforeKwLoc);
    }

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

PseudoDt::UP TsdlParser::_tryParseFlFloatType()
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
    _Attrs attrs;

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
        throwTextParseError(ss.str(), beginLoc);
    }

    auto floatType = std::make_unique<const FixedLengthFloatingPointNumberType>(align,
                                                                                expDig + mantDig,
                                                                                bo);

    return std::make_unique<PseudoScalarDtWrapper>(std::move(floatType), nullptr, beginLoc);
}

PseudoDt::UP TsdlParser::_tryParseNtStrType()
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
                                                       nullptr, beginLoc);
    }

    // parse attributes
    _Attrs attrs;

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
                                                   nullptr, beginLoc);
}

PseudoDt::UP TsdlParser::_tryParseFlEnumType(const bool addDtAlias,
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

    PseudoDt::UP pseudoDt;

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
        return this->_finishParseFlEnumType<FixedLengthUnsignedEnumerationType>(std::move(pseudoDt), addDtAlias,
                                                                                std::move(potDtAliasName),
                                                                                [](const auto& pseudoDt,
                                                                                   const auto& mappings) {
            const auto& pseudoUIntType = static_cast<const PseudoFlUIntType&>(pseudoDt);

            return std::make_unique<PseudoFlUEnumType>(pseudoUIntType.align(),
                                                       pseudoUIntType.len(), pseudoUIntType.bo(),
                                                       pseudoUIntType.prefDispBase(), mappings,
                                                       pseudoUIntType.hasEncoding(),
                                                       pseudoUIntType.mappedClkTypeName(), nullptr,
                                                       pseudoDt.loc());
        });
    } else {
        return this->_finishParseFlEnumType<FixedLengthSignedEnumerationType>(std::move(pseudoDt), addDtAlias,
                                                                              std::move(potDtAliasName),
                                                                              [](const auto& pseudoDt,
                                                                                 const auto& mappings) {
            auto& intType = static_cast<const PseudoScalarDtWrapper&>(pseudoDt).dt().asFixedLengthIntegerType();
            auto enumType = std::make_unique<FixedLengthSignedEnumerationType>(intType.alignment(),
                                                                               intType.length(),
                                                                               intType.byteOrder(),
                                                                               mappings,
                                                                               intType.preferredDisplayBase());

            return std::make_unique<PseudoScalarDtWrapper>(std::move(enumType), nullptr,
                                                           pseudoDt.loc());
        });
    }
}

PseudoDt::UP TsdlParser::_tryParseStructType(const bool addDtAlias,
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
    PseudoDt::UP pseudoDt;

    {
        _LexicalScope dtAliasLexScope;

        if (const auto ident = _ss.tryScanIdent()) {
            potDtAliasName = "struct ";
            potDtAliasName += *ident;

            if (dtAliasName) {
                dtAliasLexScope = _LexicalScope {*this, _StackFrame::Kind::DT_ALIAS};
                *dtAliasName = potDtAliasName;
            }
        }

        {
            _LexicalScope structTypeLexScope {*this, _StackFrame::Kind::STRUCT_TYPE};

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
                const auto optAlign = _ss.tryScanConstUInt();

                if (!optAlign) {
                    throwTextParseError("Expecting valid constant unsigned integer.",
                                        _ss.loc());
                }

                if (!isPowOfTwo(*optAlign)) {
                    std::ostringstream ss;

                    ss << "Invalid minimum alignment for `struct` block " <<
                          "(must be a power of two): " << *optAlign << ".";
                    throwTextParseError(ss.str(), _ss.loc());
                }

                align = *optAlign;
                this->_expectToken(")");
            }

            pseudoDt = std::make_unique<PseudoStructType>(align, std::move(pseudoMemberTypes),
                                                          nullptr, beginLoc);
        }
    }

    if (addDtAlias && !potDtAliasName.empty()) {
        this->_addDtAlias(std::move(potDtAliasName), *pseudoDt);
    }

    return pseudoDt;
}

PseudoDt::UP TsdlParser::_tryParseVarType(const bool addDtAlias, std::string * const dtAliasName)
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
    PseudoDt::UP pseudoDt;

    {
        _LexicalScope dtAliasLexScope;

        if (const auto ident = _ss.tryScanIdent()) {
            potDtAliasName = "variant ";
            potDtAliasName += *ident;

            if (dtAliasName) {
                dtAliasLexScope = _LexicalScope {*this, _StackFrame::Kind::DT_ALIAS};
                *dtAliasName = potDtAliasName;
            }
        }

        {
            _LexicalScope varTypeLexScope {*this, _StackFrame::Kind::VAR_TYPE};

            // try to parse `<`
            boost::optional<PseudoDataLoc> pseudoDataLoc;

            if (_ss.tryScanToken("<")) {
                pseudoDataLoc = this->_expectDataLoc();
                assert(pseudoDataLoc);

                if (pseudoDataLoc->isEnv()) {
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
    // parse `env`
    if (!_ss.tryScanToken("env")) {
        return false;
    }

    if (_traceEnv) {
        throwTextParseError("Duplicate `env` block.", _ss.loc());
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;

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
            throwTextParseError(ss.str(), attr.valTextLoc());
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
                throwTextParseError(ss.str(), attr.valTextLoc());
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

bool TsdlParser::_tryParseCallsiteBlock()
{
    // parse `callsite`
    if (!_ss.tryScanToken("callsite")) {
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
    _Attrs attrs;

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
                throwTextParseError(ss.str(), attr.valTextLoc());
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
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            uuid = tmpUuid;
        } else if (attr.name == "freq") {
            attr.checkKind(TsdlAttr::Kind::UINT);

            if (attr.uintVal == 0) {
                std::ostringstream ss;

                ss << "Invalid `freq` attribute (must be greater than 0): " <<
                      attr.uintVal << ".";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            freq = static_cast<unsigned long long>(attr.uintVal);
        } else if (attr.name == "precision") {
            attr.checkKind(TsdlAttr::Kind::UINT);
            precision = attr.uintVal;
        } else if (attr.name == "offset_s") {
            if (attr.kind != TsdlAttr::Kind::SINT && attr.kind != TsdlAttr::Kind::UINT) {
                throwTextParseError("Attribute `offset_s`: expecting constant signed integer.",
                                    attr.valTextLoc());
            }

            if (attr.kind == TsdlAttr::Kind::UINT) {
                using UT = decltype(attr.uintVal);

                if (attr.uintVal > static_cast<UT>(std::numeric_limits<long long>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `offset_s`: value is too large: " << attr.uintVal << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
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
        throwTextParseError(ss.str(), beginLoc);
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

bool TsdlParser::_tryParseTraceTypeBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::TRACE_TYPE};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = _ss.loc();

    // parse `trace`
    if (!_ss.tryScanToken("trace")) {
        return false;
    }

    if (_pseudoTraceType) {
        throwTextParseError("Duplicate `trace` block.", _ss.loc());
    }

    // parse `{`
    this->_expectToken("{");

    // parse attributes
    _Attrs attrs;
    PseudoDt::UP pseudoPktHeaderType;

    while (true) {
        this->_skipCommentsAndWhitespacesAndSemicolons();

        // end of block?
        if (_ss.tryScanToken("}")) {
            break;
        }

        // try to parse packet header type
        auto pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::PKT_HEADER_TYPE, "packet",
                                               "header");

        if (pseudoDt) {
            if (pseudoPktHeaderType) {
                throwTextParseError("Duplicate `packet.header` scope.", _ss.loc());
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
            attr.checkKind(TsdlAttr::Kind::STR);

            if (attr.strVal.size() != 36) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwTextParseError(ss.str(), attr.valTextLoc());
            }

            uuid = TsdlParser::_uuidFromStr(attr.strVal);

            if (!uuid) {
                std::ostringstream ss;

                ss << "Malformed `uuid` attribute: `" << attr.strVal << "`.";
                throwTextParseError(ss.str(), attr.valTextLoc());
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

bool TsdlParser::_tryParseDstBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::DST};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = _ss.loc();

    // parse `stream`
    if (!_ss.tryScanToken("stream")) {
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
        if (_ss.tryScanToken("}")) {
            break;
        }

        // try to parse packet context type
        auto pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::PKT_CTX_TYPE, "packet",
                                               "context");

        if (pseudoDt) {
            if (pseudoPktCtxType) {
                throwTextParseError("Duplicate `packet.context` scope.", _ss.loc());
            }

            pseudoPktCtxType = std::move(pseudoDt);
            continue;
        }

        // try to parse event record header type
        pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_HEADER_TYPE, "event", "header",
                                          false);

        if (pseudoDt) {
            if (pseudoErHeaderType) {
                throwTextParseError("Duplicate `event.header` scope.", _ss.loc());
            }

            pseudoErHeaderType = std::move(pseudoDt);
            continue;
        }

        // try to parse event record common context type
        pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_COMMON_CTX_TYPE, "event",
                                          "context", false);

        if (pseudoDt) {
            if (pseudoErCommonCtxType) {
                throwTextParseError("Duplicate `event.context` scope.", _ss.loc());
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
        throwTextParseError(ss.str(), beginLoc);
    }

    // create and initialize pseudo data stream type
    auto pseudoDst = std::make_unique<PseudoDst>(id, boost::none, boost::none,
                                                 std::move(pseudoPktCtxType),
                                                 std::move(pseudoErHeaderType),
                                                 std::move(pseudoErCommonCtxType));
    _pseudoTraceType->pseudoDsts().insert(std::make_pair(id, std::move(pseudoDst)));
    _pseudoTraceType->pseudoOrphanErts()[id];

    return true;
}

bool TsdlParser::_tryParseErtBlock()
{
    _LexicalScope lexScope {*this, _StackFrame::Kind::ERT};

    this->_skipCommentsAndWhitespacesAndSemicolons();

    const auto beginLoc = _ss.loc();

    // parse `event`
    if (!_ss.tryScanToken("event")) {
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
        if (_ss.tryScanToken("}")) {
            break;
        }

        // try to parse specific context type
        auto pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_SPEC_CTX_TYPE, "context");

        if (pseudoDt) {
            if (pseudoSpecCtxType) {
                throwTextParseError("Duplicate `event.context` scope.", _ss.loc());
            }

            pseudoSpecCtxType = std::move(pseudoDt);
            continue;
        }

        // try to parse payload type
        pseudoDt = this->_tryParseScopeDt(_StackFrame::Kind::ER_PAYLOAD_TYPE, "fields");

        if (pseudoDt) {
            if (pseudoPayloadType) {
                throwTextParseError("Duplicate `event.fields` scope.", _ss.loc());
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
                throwTextParseError("Attribute `loglevel`: expecting constant signed integer.",
                                    attr.valTextLoc());
            }

            if (attr.kind == TsdlAttr::Kind::UINT) {
                using UT = decltype(attr.uintVal);

                if (attr.uintVal > static_cast<UT>(std::numeric_limits<LogLevel>::max())) {
                    std::ostringstream ss;

                    ss << "Attribute `loglevel`: value is too large: " << attr.uintVal << ".";
                    throwTextParseError(ss.str(), attr.valTextLoc());
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
            id, boost::none, std::move(name), std::move(logLevel),
            std::move(emfUri), std::move(pseudoSpecCtxType),
            std::move(pseudoPayloadType)
        },
        beginLoc
    }));

    return true;
}

PseudoDt::UP TsdlParser::_tryParseScopeDt(const _StackFrame::Kind scopeDtStackFrameKind,
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
        PseudoDt::UP pseudoDt;

        {
            _LexicalScope lexScope {*this, scopeDtStackFrameKind};

            pseudoDt = this->_tryParseDt();
        }

        if (!pseudoDt) {
            throwTextParseError("Expecting data type or data type alias name.", dtLoc);
        }

        if (pseudoDt->kind() != PseudoDt::Kind::STRUCT) {
            throwTextParseError("Expecting a structure type.", dtLoc);
        }

        // parse `;`
        this->_expectToken(";");
        ssRej.accept();
        return pseudoDt;
    } catch (TextParseError& exc) {
        std::string line;

        line = "In the `";
        line += firstName;

        if (secondName) {
            line += ".";
            line += secondName;
        }

        line += "` scope:";
        appendMsgToTextParseError(exc, line, beginLoc);
        throw;
    }
}

TsdlAttr TsdlParser::_expectAttr()
{
    TsdlAttr attr;

    // parse name
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

    // parse `=`
    this->_expectToken("=");

    // this it the source location of the attribute for an eventual error
    _ss.skipCommentsAndWhitespaces();
    attr.valLoc = _ss.loc();

    // special case for the `map` attribute
    if (attr.name == "map") {
        attr.kind = TsdlAttr::Kind::CLK_NAME_VALUE;

        // parse `clock`
        this->_expectToken("clock");

        // parse `.`
        this->_expectToken(".");

        // parse name of clock type
        const auto ident = _ss.tryScanIdent();

        if (!ident) {
            throwTextParseError("Expecting identifier (clock type name).", _ss.loc());
        }

        attr.strVal = *ident;

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
        attr.kind = TsdlAttr::Kind::STR;
    } else if (const auto ident = _ss.tryScanIdent()) {
        // identifier
        attr.strVal = *ident;
        attr.kind = TsdlAttr::Kind::IDENT;
    } else if (const auto val = _ss.tryScanConstUInt()) {
        // constant unsigned integer
        attr.uintVal = *val;
        attr.kind = TsdlAttr::Kind::UINT;
    } else if (const auto val = _ss.tryScanConstSInt()) {
        // constant signed integer
        attr.intVal = *val;
        attr.kind = TsdlAttr::Kind::SINT;
        assert(attr.intVal != 0 && attr.intVal != 1);
    } else {
        throwTextParseError("Expecting valid constant integer, literal string, or identifier.",
                            *attr.valLoc);
    }

    // parse `;`
    this->_expectToken(";");
    return attr;
}

PseudoDt::UP TsdlParser::_tryParseDtAliasRef()
{
    _ss.skipCommentsAndWhitespaces();

    const auto beginLoc = _ss.loc();

    // try `enum`/`struct` followed by name
    {
        StrScannerRejecter ssRej {_ss};

        if (auto ident = _ss.tryScanIdent()) {
            const std::string kw {*ident};

            if (kw == "enum" || kw == "struct") {
                if ((ident = _ss.tryScanIdent())) {
                    if (!_ss.tryScanToken("{") && !_ss.tryScanToken(":")) {
                        std::string dtAliasName = kw + ' ';

                        dtAliasName += *ident;

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

                    if (pseudoSelLoc.isEnv()) {
                        throwTextParseError("Selector location of variant type cannot start with `env.`.",
                                            selLoc);
                    }

                    this->_expectToken(">");

                    if (!_ss.tryScanToken("{")) {
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
        StrScannerRejecter ssRej {_ss};
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

bool TsdlParser::_parseDtAliasName(std::string& dtAliasName, const bool expect)
{
    bool isMulti = false;
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

        // disallow reserved words
        if (*ident == "integer" || *ident == "floating_point" || *ident == "enum" ||
                *ident == "string" || *ident == "struct" || *ident == "variant" ||
                *ident == "trace" || *ident == "stream" ||
                *ident == "clock" || *ident == "event" || *ident == "env") {
            if (expect) {
                std::ostringstream ss;

                ss << "Invalid keyword `" << *ident << "` in type alias name.";
                throwTextParseError(ss.str(), loc);
            } else {
                return false;
            }
        }

        if (*ident == "const" || *ident == "char" || *ident == "double" || *ident == "float" ||
                *ident == "int" || *ident == "long" || *ident == "short" || *ident == "signed" ||
                *ident == "unsigned" || *ident == "void" || *ident == "_Bool" ||
                *ident == "_Complex" || *ident == "_Imaginary") {
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
    DataLocation::PathElements allPathElems;

    while (true) {
        const auto ident = _ss.tryScanIdent();

        if (!ident) {
            break;
        }

        allPathElems.push_back(*ident);

        if (!_ss.tryScanToken(".")) {
            break;
        }
    }

    if (allPathElems.empty()) {
        throwTextParseError("Empty data location.", beginLoc);
    }

    return this->_pseudoDataLocFromAllPathElems(allPathElems, beginLoc);
}

PseudoDt::UP TsdlParser::_tryParseIdentArraySubscripts(std::string& ident,
                                                               PseudoDt::UP innerPseudoDt)
{
    // parse identifier
    const auto identRes = _ss.tryScanIdent();

    if (!identRes) {
        return nullptr;
    }

    ident = *identRes;
    return this->_parseArraySubscripts(std::move(innerPseudoDt));
}

PseudoDt::UP TsdlParser::_parseArraySubscripts(PseudoDt::UP innerPseudoDt)
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

            if (pseudoDataLoc->isEnv()) {
                // only the `env.KEY` format is accepted
                if (pseudoDataLoc->pathElems().size() != 1) {
                    throwTextParseError("Invalid environment location: expecting `env.KEY`, "
                                        "where KEY is the key of an existing environment entry.",
                                        subscriptLoc);
                }

                const auto& envKey = pseudoDataLoc->pathElems()[0];

                // find the value in the current environment
                if (!_traceEnv) {
                    std::ostringstream ss;

                    ss << "Static-length array type refers to the environment entry `" <<
                          envKey << "`, but no environment exists at this point.";
                    throwTextParseError(ss.str(), subscriptLoc);
                }

                const auto entry = (*_traceEnv)[envKey];

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
     * arrays of `len` static-length arrays of four null-terminated
     * strings.
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
        StrScannerRejecter ssRej {_ss};
        const auto dtLoc = _ss.loc();
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
                    throwTextParseError("Variant type needs a selector location here.", dtLoc);
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
        StrScannerRejecter ssRej {_ss};

        if (this->_tryParseDtAlias()) {
            ssRej.accept();
            return true;
        }
    }

    // try full type (cases 8)
    {
        StrScannerRejecter ssRej {_ss};
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
                    throwTextParseError("Variant type needs a selector here.", _ss.loc());
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
                throwTextParseError("Expecting identifier (member type/option name).",
                                    _ss.loc());
            }
        }
    }

    return false;
}

const std::string *TsdlParser::_tryScanLitStr()
{
    const std::string *litStr = nullptr;

    _ss.skipCommentsAndWhitespaces();

    const auto loc = _ss.loc();

    litStr = _ss.tryScanLitStr("abfnrtv'?");

    if (!litStr) {
        return nullptr;
    }

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
