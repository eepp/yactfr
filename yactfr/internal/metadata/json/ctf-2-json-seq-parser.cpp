/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <sstream>

#include "ctf-2-json-seq-parser.hpp"
#include "ctf-2-json-strs.hpp"
#include "json-val-from-text.hpp"
#include "item-from-json-val.hpp"
#include "../trace-type-from-pseudo-trace-type.hpp"

namespace yactfr {
namespace internal {
namespace {

JsonObjVal::UP createDefClkOffsetJsonObjVal()
{
    JsonObjVal::Container entries;

    entries.insert(std::make_pair(strs::SECS, createJsonVal(0LL, TextLocation {})));
    entries.insert(std::make_pair(strs::CYCLES, createJsonVal(0ULL, TextLocation {})));
    return createJsonVal(std::move(entries), TextLocation {});
}

} // namespace

Ctf2JsonSeqParser::Ctf2JsonSeqParser(const char * const begin, const char * const end) :
    _begin {begin},
    _end {end},
    _defClkOffsetVal {createDefClkOffsetJsonObjVal()}
{
    this->_parseMetadata();
}

void Ctf2JsonSeqParser::_createTraceType()
{
    if (!_pseudoTraceType) {
        throwTextParseError("Missing trace type.", TextLocation {});
    }

    // create yactfr trace type
    _traceType = traceTypeFromPseudoTraceType(*_pseudoTraceType);
}

void Ctf2JsonSeqParser::_parseMetadata()
{
    auto fragBegin = _begin;
    const char *fragEnd;
    Index fragIndex = 0;

    while (true) {
        // find the beginning pointer of the JSON fragment
        while (fragBegin != _end && *fragBegin == 30) {
            ++fragBegin;
        }

        if (fragBegin == _end) {
            // end of stream
            this->_createTraceType();
            return;
        }

        // find the end pointer of the JSON fragment
        fragEnd = fragBegin;

        while (fragEnd != _end && *fragEnd != 30) {
            ++fragEnd;
        }

        if (fragBegin == fragEnd) {
            throwTextParseError("Expecting a fragment.",
                                TextLocation {static_cast<Index>(fragBegin - _begin), 0, 0});
        }

        // parse fragment
        this->_parseFrag(fragBegin, fragEnd, fragIndex);

        // go to next fragment
        fragBegin = fragEnd;
        ++fragIndex;
    }
}

void Ctf2JsonSeqParser::_parseFrag(const char * const begin, const char * const end,
    const Index index)
{
    this->_handleFrag(*parseJson(begin, end, begin - _begin), index);
}

void Ctf2JsonSeqParser::_handleFrag(const JsonVal& jsonFrag, const Index index)
{
    // validate
    _fragValReq.validate(jsonFrag);

    // get type
    auto& jsonFragObj = jsonFrag.asObj();
    auto& type = jsonFragObj.getRawStrVal(strs::TYPE);

    // specific preamble fragment case
    if (index == 0) {
        if (type != strs::PRE) {
            throwTextParseError("Expecting the preamble fragment.", jsonFrag.loc());
        }

        // set metadata stream UUID, if any
        _metadataStreamUuid = uuidOfObj(jsonFragObj);

        // done with this fragment
        return;
    }

    // defer to specific method
    if (type == strs::PRE) {
        assert(index > 0);
        throwTextParseError("Preamble fragment must be the first fragment of "
                            "the metadata stream.", jsonFrag.loc());
    } else if (type == strs::FC_ALIAS) {
        this->_handleDtAliasFrag(jsonFragObj);
    } else if (type == strs::TC) {
        this->_handleTraceTypeFrag(jsonFragObj);
    } else if (type == strs::CC) {
        this->_handleClkTypeFrag(jsonFragObj);
    } else if (type == strs::DSC) {
        this->_handleDstFrag(jsonFragObj);
    } else {
        assert(type == strs::ERC);
        this->_handleErtFrag(jsonFragObj);
    }
}

void Ctf2JsonSeqParser::_handleDtAliasFrag(const JsonObjVal& jsonFrag)
{
    try {
        auto& jsonNameVal = jsonFrag.asObj()[strs::NAME]->asStr();

        _pseudoDtErector.addAlias(*jsonNameVal,
                                  _pseudoDtErector.pseudoDtOfJsonObj(jsonFrag, strs::FC),
                                  jsonNameVal.loc());
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In data type alias fragment:", jsonFrag.loc());
        throw;
    }
}

void Ctf2JsonSeqParser::_handleTraceTypeFrag(const JsonObjVal& jsonFrag)
{
    if (_pseudoTraceType) {
        throwTextParseError("Duplicate trace type fragment.", jsonFrag.loc());
    }

    // environment
    TraceEnvironment::Entries envEntries;

    const auto jsonEnv = jsonFrag[strs::ENV];

    if (jsonEnv) {
        for (auto& keyJsonValPair : jsonEnv->asObj()) {
            auto& jsonEntryVal = *keyJsonValPair.second;

            if (jsonEntryVal.isStr()) {
                envEntries.emplace(std::make_pair(keyJsonValPair.first, *jsonEntryVal.asStr()));
            } else if (jsonEntryVal.isSInt()) {
                envEntries.emplace(std::make_pair(keyJsonValPair.first, *jsonEntryVal.asSInt()));
            } else {
                assert(jsonEntryVal.isUInt());
                envEntries.emplace(std::make_pair(keyJsonValPair.first,
                                                  static_cast<long long>(*jsonEntryVal.asUInt())));
            }
        }
    }

    try {
        _pseudoTraceType = PseudoTraceType {
            2, 0, optStrOfObj(jsonFrag, strs::NS), optStrOfObj(jsonFrag, strs::NAME),
            optStrOfObj(jsonFrag, strs::UID),
            TraceEnvironment {std::move(envEntries)},
            this->_pseudoScopeDtOfJsonObj(jsonFrag, strs::PKT_HEADER_FC),
            attrsOfObj(jsonFrag)
        };
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In trace type fragment:", jsonFrag.loc());
        throw;
    }
}

void Ctf2JsonSeqParser::_handleClkTypeFrag(const JsonObjVal& jsonFrag)
{
    this->_ensureExistingPseudoTraceType();

    // internal ID
    auto id = jsonFrag.getRawStrVal(strs::ID);

    if (_pseudoTraceType->hasClkType(id)) {
        std::ostringstream ss;

        ss << "Duplicate clock type fragment with internal ID `" << id << "`.";
        throwTextParseError(ss.str(), jsonFrag.loc());
    }

    // offset
    auto& jsonOffsetFromOrigVal = jsonFrag.getVal(strs::OFFSET_FROM_ORIG, *_defClkOffsetVal);
    const auto jsonOffsetSecsVal = jsonOffsetFromOrigVal[strs::SECS];
    auto offsetFromOrigSecs = 0LL;

    if (jsonOffsetSecsVal) {
        offsetFromOrigSecs = rawIntValFromJsonIntVal<long long>(*jsonOffsetSecsVal);
    }

    const auto offsetFromOrigCycles = jsonOffsetFromOrigVal.getRawVal(strs::CYCLES, 0ULL);

    // origin
    boost::optional<ClockOrigin> orig;
    const auto jsonOrigVal = jsonFrag[strs::ORIG];

    if (jsonOrigVal) {
        if (jsonOrigVal->isStr()) {
            assert(*jsonOrigVal->asStr() == strs::UNIX_EPOCH);
            orig = ClockOrigin {};
        } else {
            assert(jsonOrigVal->isObj());

            auto& jsonOrigObjVal = jsonOrigVal->asObj();

            orig = ClockOrigin {
                optStrOfObj(jsonOrigObjVal, strs::NS),
                *jsonOrigObjVal[strs::NAME]->asStr(),
                *jsonOrigObjVal[strs::UID]->asStr()
            };
        }
    }

    // create corresponding clock type
    auto clkType = ClockType::create(std::move(id), optStrOfObj(jsonFrag, strs::NS),
                                     optStrOfObj(jsonFrag, strs::NAME),
                                     optStrOfObj(jsonFrag, strs::UID), boost::none,
                                     jsonFrag.getRawUIntVal(strs::FREQ),
                                     optStrOfObj(jsonFrag, strs::DESCR), std::move(orig),
                                     optUIntOfObj(jsonFrag, strs::PREC),
                                     optUIntOfObj(jsonFrag, strs::ACCURACY),
                                     ClockOffset {offsetFromOrigSecs, offsetFromOrigCycles},
                                     attrsOfObj(jsonFrag));

    // add to pseudo trace type
    _pseudoTraceType->clkTypes().insert(std::move(clkType));
}

namespace {

boost::optional<std::pair<std::string, TextLocation>> optStrOfObjWithLoc(const JsonObjVal& jsonObjVal,
                                                                         const std::string& propName)
{
    const auto jsonVal = jsonObjVal[propName];

    if (jsonVal) {
        return std::make_pair(*jsonVal->asStr(), jsonVal->loc());
    }

    return boost::none;
}

} // namespace

void Ctf2JsonSeqParser::_handleDstFrag(const JsonObjVal& jsonFrag)
{
    this->_ensureExistingPseudoTraceType();

    // ID
    const auto id = jsonFrag.getRawVal(strs::ID, 0ULL);

    if (_pseudoTraceType->hasPseudoDst(id)) {
        std::ostringstream ss;

        ss << "Duplicate data stream type with ID " << id << '.';
        throwTextParseError(ss.str(), jsonFrag.loc());
    }

    // default clock type internal ID
    const auto defClkTypeId = optStrOfObjWithLoc(jsonFrag, strs::DEF_CC_ID);
    const ClockType *defClkType = nullptr;

    if (defClkTypeId) {
        defClkType = _pseudoTraceType->findClkType(defClkTypeId->first);

        if (!defClkType) {
            std::ostringstream ss;

            ss << '`' << defClkTypeId->first << "` doesn't identify an existing clock type.";
            throwTextParseError(ss.str(), defClkTypeId->second);
        }
    }

    try {
        auto pseudoDst = std::make_unique<PseudoDst>(id, optStrOfObj(jsonFrag, strs::NS),
                                                     optStrOfObj(jsonFrag, strs::NAME),
                                                     optStrOfObj(jsonFrag, strs::UID),
                                                     this->_pseudoScopeDtOfJsonObj(jsonFrag,
                                                                                   strs::PKT_CTX_FC),
                                                     this->_pseudoScopeDtOfJsonObj(jsonFrag,
                                                                                   strs::ER_HEADER_FC),
                                                     this->_pseudoScopeDtOfJsonObj(jsonFrag,
                                                                                   strs::ER_COMMON_CTX_FC),
                                                     defClkType, attrsOfObj(jsonFrag));

        _pseudoTraceType->pseudoDsts().insert(std::make_pair(id, std::move(pseudoDst)));
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In data stream type fragment:", jsonFrag.loc());
        throw;
    }

    _pseudoTraceType->pseudoOrphanErts()[id];
}

void Ctf2JsonSeqParser::_handleErtFrag(const JsonObjVal& jsonFrag)
{
    this->_ensureExistingPseudoTraceType();

    // data stream type ID
    const auto jsonDstIdVal = jsonFrag[strs::DSC_ID];
    const auto dstId = jsonDstIdVal ? *jsonDstIdVal->asUInt() : 0ULL;

    if (!_pseudoTraceType->hasPseudoDst(dstId)) {
        std::ostringstream ss;

        ss << "No data stream type exists with ID " << dstId << '.';
        throwTextParseError(ss.str(), jsonDstIdVal ? jsonDstIdVal->loc() : jsonFrag.loc());
    }

    // ID
    const auto jsonIdVal = jsonFrag[strs::ID];
    const auto id = jsonIdVal ? *jsonIdVal->asUInt() : 0ULL;

    if (_pseudoTraceType->hasPseudoOrphanErt(dstId, id)) {
        std::ostringstream ss;

        ss << "Duplicate event record type with ID " << id <<
              " within data stream type " << dstId << '.';
        throwTextParseError(ss.str(), jsonIdVal ? jsonIdVal->loc() : jsonFrag.loc());
    }

    try {
        _pseudoTraceType->pseudoOrphanErts()[dstId].insert(std::make_pair(id, PseudoOrphanErt {
            PseudoErt {
                id, optStrOfObj(jsonFrag, strs::NS), optStrOfObj(jsonFrag, strs::NAME),
                optStrOfObj(jsonFrag, strs::UID),
                boost::none, boost::none,
                this->_pseudoScopeDtOfJsonObj(jsonFrag, strs::SPEC_CTX_FC),
                this->_pseudoScopeDtOfJsonObj(jsonFrag, strs::PAYLOAD_FC),
                attrsOfObj(jsonFrag)
            },
            jsonFrag.loc()
        }));
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In event record type fragment:", jsonFrag.loc());
        throw;
    }
}

void Ctf2JsonSeqParser::_ensureExistingPseudoTraceType()
{
    if (_pseudoTraceType) {
        // already initialized
        return;
    }

    // initialize default CTF 2 pseudo trace type
    _pseudoTraceType = PseudoTraceType {2, 0};
}

PseudoDt::UP Ctf2JsonSeqParser::_pseudoScopeDtOfJsonObj(const JsonObjVal& jsonObjVal,
                                                        const std::string& propName)
{
    auto pseudoDt = _pseudoDtErector.pseudoDtOfJsonObj(jsonObjVal, propName);

    if (!pseudoDt) {
        return nullptr;
    }

    if (pseudoDt->kind() != PseudoDt::Kind::STRUCT) {
        throwTextParseError("Root data type of scope must be structure type.", pseudoDt->loc());
    }

    return pseudoDt;
}

} // namespace internal
} // namespace yactfr
