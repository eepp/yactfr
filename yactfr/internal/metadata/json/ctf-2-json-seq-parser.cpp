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

static JsonObjVal::UP createDefClkOffsetJsonObjVal()
{
    JsonObjVal::Container entries;

    entries.insert(std::make_pair(strs::SECS, createJsonVal(0LL, TextLocation {})));
    entries.insert(std::make_pair(strs::CYCLES, createJsonVal(0ULL, TextLocation {})));
    return createJsonVal(std::move(entries), TextLocation {});
}

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

void Ctf2JsonSeqParser::_handleTraceTypeFrag(const JsonObjVal& jsonFrag)
{
    if (_pseudoTraceType) {
        throwTextParseError("Duplicate trace type fragment.", jsonFrag.loc());
    }

    _pseudoTraceType = PseudoTraceType {
        2, 0, uuidOfObj(jsonFrag), TraceEnvironment {}, pseudoDtOfCtf2Obj(jsonFrag, strs::PKT_HEADER_FC),
        userAttrsOfObj(jsonFrag)
    };
}

void Ctf2JsonSeqParser::_handleClkTypeFrag(const JsonObjVal& jsonFrag)
{
    this->_ensureExistingPseudoTraceType();

    // name
    auto name = jsonFrag.getRawStrVal(strs::NAME);

    if (_pseudoTraceType->hasClkType(name)) {
        std::ostringstream ss;

        ss << "Duplicate clock type fragment named `" << name << "`.";
        throwTextParseError(ss.str(), jsonFrag.loc());
    }

    // description
    boost::optional<std::string> descr;
    const auto jsonDescrVal = jsonFrag[strs::DESCR];

    if (jsonDescrVal) {
        descr = *jsonDescrVal->asStr();
    }

    // offset
    auto& jsonOffsetVal = jsonFrag.getVal(strs::OFFSET, *_defClkOffsetVal);
    const auto jsonOffsetSecsVal = jsonOffsetVal[strs::SECS];
    auto offsetSecs = 0LL;

    if (jsonOffsetSecsVal) {
        offsetSecs = rawIntValFromJsonIntVal<long long>(*jsonOffsetSecsVal);
    }

    const auto offsetCycles = jsonOffsetVal.getRawVal(strs::CYCLES, 0ULL);

    // create corresponding clock type
    auto clkType = ClockType::create(jsonFrag.getRawUIntVal(strs::FREQ), std::move(name),
                                     std::move(descr), uuidOfObj(jsonFrag),
                                     jsonFrag.getRawVal(strs::PREC, 0ULL), ClockOffset {offsetSecs,
                                     offsetCycles},
                                     jsonFrag.getRawVal(strs::ORIG_IS_UNIX_EPOCH, true),
                                     userAttrsOfObj(jsonFrag));

    // add to pseudo trace type
    _pseudoTraceType->clkTypes().insert(std::move(clkType));
}

static boost::optional<std::pair<std::string, TextLocation>> optStrOfObjWithLoc(const JsonObjVal& jsonObjVal,
                                                                                const std::string& propName)
{
    const auto jsonVal = jsonObjVal[propName];

    if (jsonVal) {
        return std::make_pair(*jsonVal->asStr(), jsonVal->loc());
    }

    return boost::none;
}

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

    // default clock type name
    const auto defClkTypeName = optStrOfObjWithLoc(jsonFrag, strs::DEF_CC_NAME);
    const ClockType *defClkType = nullptr;

    if (defClkTypeName) {
        defClkType = _pseudoTraceType->findClkType(defClkTypeName->first);

        if (!defClkType) {
            std::ostringstream ss;

            ss << '`' << defClkTypeName->first << "` doesn't name an existing clock type.";
            throwTextParseError(ss.str(), defClkTypeName->second);
        }
    }

    auto pseudoDst = std::make_unique<PseudoDst>(id, optStrOfObj(jsonFrag, strs::NS),
                                                 optStrOfObj(jsonFrag, strs::NAME),
                                                 pseudoDtOfCtf2Obj(jsonFrag, strs::PKT_CTX_FC),
                                                 pseudoDtOfCtf2Obj(jsonFrag, strs::ER_HEADER_FC),
                                                 pseudoDtOfCtf2Obj(jsonFrag, strs::ER_COMMON_CTX_FC),
                                                 defClkType, userAttrsOfObj(jsonFrag));

    _pseudoTraceType->pseudoDsts().insert(std::make_pair(id, std::move(pseudoDst)));
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

    _pseudoTraceType->pseudoOrphanErts()[dstId].insert(std::make_pair(id, PseudoOrphanErt {
        PseudoErt {
            id, optStrOfObj(jsonFrag, strs::NS), optStrOfObj(jsonFrag, strs::NAME),
            boost::none, boost::none,
            pseudoDtOfCtf2Obj(jsonFrag, strs::SPEC_CTX_FC),
            pseudoDtOfCtf2Obj(jsonFrag, strs::PAYLOAD_FC),
            userAttrsOfObj(jsonFrag)
        },
        jsonFrag.loc()
    }));
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

} // namespace internal
} // namespace yactfr
