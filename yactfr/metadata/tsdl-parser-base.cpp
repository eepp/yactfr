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

TsdlParserBase::_StackFrame::_StackFrame(const Kind kind) :
    kind {kind}
{
}

void TsdlParserBase::_setImplicitMappedClkTypeName(PseudoDt& basePseudoDt,
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
        auto& pseudoIntType = static_cast<PseudoUIntType&>(*pseudoDt);

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

void TsdlParserBase::_setImplicitMappedClkTypeName()
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

void TsdlParserBase::_setPseudoStaticArrayTypeTraceTypeUuidRole(PseudoDt& basePseudoDt,
                                                                const std::string& memberTypeName)
{
    const auto pseudoDts = findPseudoDtsByName(basePseudoDt, memberTypeName,
                                               [](auto& pseudoDt) {
        if (pseudoDt.kind() != PseudoDt::Kind::STATIC_ARRAY) {
            return false;
        }

        auto& pseudoArrayType = static_cast<const PseudoStaticArrayType&>(pseudoDt);

        if (pseudoArrayType.len() != 16) {
            return false;
        }

        if (!pseudoArrayType.pseudoElemType().isUInt()) {
            return false;
        }

        auto& pseudoElemDt = static_cast<const PseudoUIntType&>(pseudoArrayType.pseudoElemType());

        if (pseudoElemDt.len() != 8) {
            return false;
        }

        if (pseudoElemDt.align() > 8) {
            return false;
        }

        return true;
    });

    for (auto& pseudoDt : pseudoDts) {
        auto& pseudoArrayType = static_cast<PseudoStaticArrayType&>(*pseudoDt);

        pseudoArrayType.hasTraceTypeUuidRole(true);
    }
}

class DefClkTsRoleAdder :
    public PseudoDtVisitor
{
public:
    DefClkTsRoleAdder() = default;

    void visit(PseudoUIntType& pseudoDt) override
    {
        if (pseudoDt.mappedClkTypeName() &&
                !pseudoDt.hasRole(UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP)) {
            pseudoDt.addRole(UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP);
        }
    }

    void visit(PseudoUEnumType& pseudoDt) override
    {
        this->visit(static_cast<PseudoUIntType&>(pseudoDt));
    }

    void visit(PseudoStaticArrayType& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(PseudoDynArrayType& pseudoDt) override
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

void TsdlParserBase::_addPseudoDtRoles()
{
    /*
     * First, set an implicit mapped clock type name on specific
     * pseudo unsigned integer types.
     *
     * For example, if the current pseudo trace type contains a
     * single clock type, then any pseudo unsigned integer type
     * named `timestamp` within pseudo event record header types,
     * which are not already mapped to a clock type, are mapped to
     * this single clock type.
     */
    this->_setImplicitMappedClkTypeName();

    // add/set simple roles
    if (_pseudoTraceType->pseudoPktHeaderType()) {
        this->_addPseudoUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(), "magic",
                                      UnsignedIntegerTypeRole::PACKET_MAGIC_NUMBER);
        this->_addPseudoUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(), "stream_id",
                                      UnsignedIntegerTypeRole::DATA_STREAM_TYPE_ID);
        this->_addPseudoUIntTypeRoles(*_pseudoTraceType->pseudoPktHeaderType(),
                                      "stream_instance_id",
                                      UnsignedIntegerTypeRole::DATA_STREAM_ID);
        this->_setPseudoStaticArrayTypeTraceTypeUuidRole(*_pseudoTraceType->pseudoPktHeaderType(),
                                                         "uuid");
    }

    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        if (pseudoDst->pseudoPktCtxType()) {
            this->_addPseudoUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_size",
                                          UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH);
            this->_addPseudoUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "content_size",
                                          UnsignedIntegerTypeRole::PACKET_CONTENT_LENGTH);
            this->_addPseudoUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_size",
                                          UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH);
            this->_addPseudoUIntTypeRoles<true>(*pseudoDst->pseudoPktCtxType(), "timestamp_end",
                                                UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP);
            this->_addPseudoUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "discarded_events",
                                          UnsignedIntegerTypeRole::DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT);
            this->_addPseudoUIntTypeRoles(*pseudoDst->pseudoPktCtxType(), "packet_seq_num",
                                          UnsignedIntegerTypeRole::PACKET_ORIGIN_INDEX);
        }

        if (pseudoDst->pseudoErHeaderType()) {
            this->_addPseudoUIntTypeRoles(*pseudoDst->pseudoErHeaderType(), "id",
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

    void visit(PseudoUIntType& pseudoDt) override
    {
        if (pseudoDt.mappedClkTypeName()) {
            if (!_clkTypeName) {
                _clkTypeName = &*pseudoDt.mappedClkTypeName();
            }

            if (*pseudoDt.mappedClkTypeName() != *_clkTypeName) {
                std::ostringstream ss;

                ss << "Unsigned integer type is mapped to a clock type (`" <<
                      *pseudoDt.mappedClkTypeName() << "` which is "
                      "different than another mapped clock type (`" <<
                      *_clkTypeName << "`) within the same data stream type.";
                throwMetadataParseError(ss.str(), pseudoDt.loc());
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
                    throwMetadataParseError(ss.str(), pseudoDt.loc());
                }
            }
        }
    }

    void visit(PseudoUEnumType& pseudoDt) override
    {
        this->visit(static_cast<PseudoUIntType&>(pseudoDt));
    }

    void visit(PseudoStaticArrayType& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(PseudoDynArrayType& pseudoDt) override
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

void TsdlParserBase::_setPseudoDstDefClkType(PseudoDst& pseudoDst)
{
    PseudoDstDefClkTypeSetter visitor {*_pseudoTraceType, pseudoDst};

    try {
        if (pseudoDst.pseudoPktCtxType()) {
            try {
                pseudoDst.pseudoPktCtxType()->accept(visitor);
            } catch (MetadataParseError& exc) {
                appendMsgToMetadataParseError(exc, "In the packet context type:",
                                              pseudoDst.pseudoPktCtxType()->loc());
                throw;
            }
        }

        if (pseudoDst.pseudoErHeaderType()) {
            try {
                pseudoDst.pseudoErHeaderType()->accept(visitor);
            } catch (MetadataParseError& exc) {
                appendMsgToMetadataParseError(exc, "In the event record header type:",
                                              pseudoDst.pseudoErHeaderType()->loc());
                throw;
            }
        }
    } catch (MetadataParseError& exc) {
        std::ostringstream ss;

        ss << "In the data stream type with ID " << pseudoDst.id() << ":";
        appendMsgToMetadataParseError(exc, ss.str());
        throw;
    }
}

void TsdlParserBase::_setPseudoDstDefClkType()
{
    for (auto& idPseudoDstPair : _pseudoTraceType->pseudoDsts()) {
        auto& pseudoDst = idPseudoDstPair.second;

        this->_setPseudoDstDefClkType(*pseudoDst);
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

    // add roles to specific pseudo data types
    this->_addPseudoDtRoles();

    // set default clock type of pseudo data stream types
    this->_setPseudoDstDefClkType();

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
            throwMetadataParseError(ss.str(), loc);
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
            throwMetadataParseError(ss.str(), attr.nameTextLoc());
        }

        attrSet.insert(attr.name);
    }
}

void TsdlParserBase::_throwMissingAttr(const std::string& name, const TextLocation& loc)
{
    std::ostringstream ss;

    ss << "Missing attribute `" << name << "`.";
    throwMetadataParseError(ss.str(), loc);
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
                throwMetadataParseError("Expecting `packet.header` after `trace.`.", loc);
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
                throwMetadataParseError("Expecting `packet.context`, `event.header`, or "
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
                throwMetadataParseError("Expecting `context` or `fields` after `event.`.", loc);
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
            throwMetadataParseError(ss.str(), loc);
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
            throwMetadataParseError(ss.str(), loc);
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

    throwMetadataParseError("Invalid data location.", loc);
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
        throwMetadataParseError(ss.str(), curLoc);
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
