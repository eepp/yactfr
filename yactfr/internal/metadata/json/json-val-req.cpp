/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include "json-val-req.hpp"
#include "../../../internal/utils.hpp"

namespace yactfr {
namespace internal {

JsonValReq::JsonValReq(boost::optional<JsonVal::Kind> kind) :
    _kind {kind}
{
}

JsonValReq::SP JsonValReq::shared(boost::optional<JsonVal::Kind> kind)
{
    return std::make_shared<JsonValReq>(std::move(kind));
}

void JsonValReq::validate(const JsonVal& jsonVal) const
{
    if (_kind && jsonVal.kind() != *_kind) {
        std::ostringstream ss;

        ss << "Expecting ";

        switch (*_kind) {
        case JsonVal::Kind::NUL:
            ss << "`null`";
            break;

        case JsonVal::Kind::BOOL:
            ss << "a boolean";
            break;

        case JsonVal::Kind::SINT:
            ss << "a signed integer";
            break;

        case JsonVal::Kind::UINT:
            ss << "an unsigned integer";
            break;

        case JsonVal::Kind::REAL:
            ss << "a real number";
            break;

        case JsonVal::Kind::STR:
            ss << "a string";
            break;

        case JsonVal::Kind::ARRAY:
            ss << "an array";
            break;

        case JsonVal::Kind::OBJ:
            ss << "an object";
            break;

        default:
            std::abort();
        }

        ss << '.';
        throwTextParseError(ss.str(), jsonVal.loc());
    }

    this->_validate(jsonVal);
}

void JsonValReq::_validate(const JsonVal&) const
{
}

JsonUIntValIsAlignReq::JsonUIntValIsAlignReq() :
    JsonValReq {JsonVal::Kind::UINT}
{
}

JsonValReq::SP JsonUIntValIsAlignReq::shared()
{
    return std::make_shared<JsonUIntValIsAlignReq>();
}

void JsonUIntValIsAlignReq::_validate(const JsonVal& jsonVal) const
{
    const auto val = *jsonVal.asUInt();

    if (!isPowOfTwo(val)) {
        std::ostringstream ss;

        ss << "Invalid alignment: " << val << " is not a power of two.";
        throwTextParseError(ss.str(), jsonVal.loc());
    }
}

JsonStrValMatchesRegexReq::JsonStrValMatchesRegexReq(const char * const regex) :
    JsonValReq {JsonVal::Kind::STR},
    _regex {regex, std::regex::ECMAScript | std::regex::optimize}
{
}

JsonStrValMatchesRegexReq::JsonStrValMatchesRegexReq(std::regex regex) :
    JsonValReq {JsonVal::Kind::STR},
    _regex {std::move(regex)}
{
}

JsonValReq::SP JsonStrValMatchesRegexReq::shared(std::regex regex)
{
    return std::make_shared<JsonStrValMatchesRegexReq>(std::move(regex));
}

JsonValReq::SP JsonStrValMatchesRegexReq::shared(const char * const regex)
{
    return std::make_shared<JsonStrValMatchesRegexReq>(regex);
}

void JsonStrValMatchesRegexReq::_validate(const JsonVal& jsonVal) const
{
    const auto& val = *jsonVal.asStr();

    if (!std::regex_match(val, _regex)) {
        std::ostringstream ss;

        ss << "Invalid string `" << val << "`.";
        throwTextParseError(ss.str(), jsonVal.loc());
    }
}

JsonArrayValReq::JsonArrayValReq(const boost::optional<Size>& minSize,
                                 const boost::optional<Size>& maxSize,
                                 JsonValReq::SP elemValReq) :
    JsonValReq {JsonVal::Kind::ARRAY},
    _minSize {minSize ? *minSize : std::numeric_limits<Size>::min()},
    _maxSize {maxSize ? *maxSize : std::numeric_limits<Size>::max()},
    _elemValReq {std::move(elemValReq)}
{
}

JsonArrayValReq::JsonArrayValReq(const Size exactSize, JsonValReq::SP elemValReq) :
    JsonArrayValReq {exactSize, exactSize, std::move(elemValReq)}
{
}

JsonArrayValReq::JsonArrayValReq(JsonValReq::SP elemValReq) :
    JsonArrayValReq {boost::none, boost::none, std::move(elemValReq)}
{
}

JsonValReq::SP JsonArrayValReq::shared(const boost::optional<Size>& minSize,
                                       const boost::optional<Size>& maxSize,
                                       JsonValReq::SP elemValReq)
{
    return std::make_shared<JsonArrayValReq>(minSize, maxSize, std::move(elemValReq));
}

JsonValReq::SP JsonArrayValReq::shared(const Size exactSize, JsonValReq::SP elemValReq)
{
    return std::make_shared<JsonArrayValReq>(exactSize, std::move(elemValReq));
}

JsonValReq::SP JsonArrayValReq::shared(JsonValReq::SP elemValReq)
{
    return std::make_shared<JsonArrayValReq>(std::move(elemValReq));
}

void JsonArrayValReq::_validate(const JsonVal& jsonVal) const
{
    auto& jsonArrayVal = jsonVal.asArray();

    if (jsonArrayVal.size() < _minSize) {
        std::ostringstream ss;

        ss << "Size of array (" << jsonArrayVal.size() << ") is too small: " <<
              "expecting at least " << _minSize << " elements.";
        throwTextParseError(ss.str(), jsonVal.loc());
    }

    if (jsonArrayVal.size() > _maxSize) {
        std::ostringstream ss;

        ss << "Size of array (" << jsonArrayVal.size() << ") is too large: " <<
              "expecting at most " << _maxSize << " elements    .";
        throwTextParseError(ss.str(), jsonVal.loc());
    }

    if (_elemValReq) {
        for (auto i = 0U; i < jsonArrayVal.size(); ++i) {
            auto& jsonElemVal = jsonArrayVal[i];

            try {
                _elemValReq->validate(jsonElemVal);
            } catch (TextParseError& exc) {
                std::ostringstream ss;

                ss << "In array element #" << (i + 1) << ":";
                appendMsgToTextParseError(exc, ss.str(), jsonElemVal.loc());
                throw;
            }
        }
    }
}

JsonObjValPropReq::JsonObjValPropReq(JsonValReq::SP valReq, const bool isRequired) :
    _isRequired {isRequired},
    _valReq {std::move(valReq)}
{
}

void JsonObjValPropReq::validate(const JsonVal& jsonVal) const
{
    if (_valReq) {
        _valReq->validate(jsonVal);
    }
}

JsonObjValReq::JsonObjValReq(PropReqs propReqs, const bool allowUnknownProps) :
    JsonValReq {JsonVal::Kind::OBJ},
    _propReqs {std::move(propReqs)},
    _allowUnknownProps {allowUnknownProps}
{
}

JsonValReq::SP JsonObjValReq::shared(PropReqs propReqs, const bool allowUnknownProps)
{
    return std::make_shared<JsonObjValReq>(std::move(propReqs), allowUnknownProps);
}

void JsonObjValReq::_validate(const JsonVal& jsonVal) const
{
    auto& jsonObjVal = jsonVal.asObj();

    for (auto& keyPropReqPair : _propReqs) {
        auto& key = keyPropReqPair.first;

        if (keyPropReqPair.second.isRequired() && !jsonObjVal.hasVal(key)) {
            std::ostringstream ss;

            ss << "Missing mandatory object property `" << key << "`.";
            throwTextParseError(ss.str(), jsonVal.loc());
        }
    }

    for (auto& keyJsonValPair : jsonObjVal) {
        auto& key = keyJsonValPair.first;
        const auto keyPropReqPairIt = _propReqs.find(key);

        if (keyPropReqPairIt == _propReqs.end()) {
            // no property requirement found
            if (_allowUnknownProps) {
                continue;
            } else {
                std::ostringstream ss;

                ss << "Unknown object property `" << key << "`.";
                throwTextParseError(ss.str(), keyJsonValPair.second->loc());
            }
        }

        auto& propJsonVal = *keyJsonValPair.second;

        try {
            keyPropReqPairIt->second.validate(propJsonVal);
        } catch (TextParseError& exc) {
            std::ostringstream ss;

            ss << "In object property `" << key << "`:";
            appendMsgToTextParseError(exc, ss.str(), propJsonVal.loc());
            throw;
        }
    }
}

} // namespace internal
} // namespace yactfr
