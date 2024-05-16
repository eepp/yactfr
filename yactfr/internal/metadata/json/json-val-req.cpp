/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "json-val-req.hpp"
#include "../../../internal/utils.hpp"

namespace yactfr {
namespace internal {

JsonValReq::JsonValReq(boost::optional<JsonVal::Kind> kind, const bool allowNull) :
    _kind {std::move(kind)},
    _allowNull {(_kind && *_kind == JsonVal::Kind::Null) ? false : allowNull}
{
}

JsonValReq::Sp JsonValReq::shared(boost::optional<JsonVal::Kind> kind, const bool allowNull)
{
    return std::make_shared<JsonValReq>(std::move(kind), allowNull);
}

void JsonValReq::validate(const JsonVal& jsonVal) const
{
    if (_kind && jsonVal.kind() != *_kind && (!_allowNull || jsonVal.kind() != JsonVal::Kind::Null)) {
        std::ostringstream ss;

        ss << "Expecting ";

        switch (*_kind) {
        case JsonVal::Kind::Null:
            ss << "`null`";
            break;

        case JsonVal::Kind::Bool:
            ss << "a boolean";
            break;

        case JsonVal::Kind::SInt:
            ss << "a signed integer";
            break;

        case JsonVal::Kind::UInt:
            ss << "an unsigned integer";
            break;

        case JsonVal::Kind::Real:
            ss << "a real number";
            break;

        case JsonVal::Kind::Str:
            ss << "a string";
            break;

        case JsonVal::Kind::Array:
            ss << "an array";
            break;

        case JsonVal::Kind::Obj:
            ss << "an object";
            break;

        default:
            std::abort();
        }

        if (_allowNull) {
            ss << " or `null`";
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
    JsonValReq {JsonVal::Kind::UInt}
{
}

JsonValReq::Sp JsonUIntValIsAlignReq::shared()
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
    JsonValReq {JsonVal::Kind::Str},
    _regex {regex, std::regex::ECMAScript | std::regex::optimize}
{
}

JsonStrValMatchesRegexReq::JsonStrValMatchesRegexReq(std::regex regex) :
    JsonValReq {JsonVal::Kind::Str},
    _regex {std::move(regex)}
{
}

JsonValReq::Sp JsonStrValMatchesRegexReq::shared(std::regex regex)
{
    return std::make_shared<JsonStrValMatchesRegexReq>(std::move(regex));
}

JsonValReq::Sp JsonStrValMatchesRegexReq::shared(const char * const regex)
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
                                 JsonValReq::Sp elemValReq) :
    JsonValReq {JsonVal::Kind::Array},
    _minSize {minSize ? *minSize : std::numeric_limits<Size>::min()},
    _maxSize {maxSize ? *maxSize : std::numeric_limits<Size>::max()},
    _elemValReq {std::move(elemValReq)}
{
}

JsonArrayValReq::JsonArrayValReq(const Size exactSize, JsonValReq::Sp elemValReq) :
    JsonArrayValReq {exactSize, exactSize, std::move(elemValReq)}
{
}

JsonArrayValReq::JsonArrayValReq(JsonValReq::Sp elemValReq) :
    JsonArrayValReq {boost::none, boost::none, std::move(elemValReq)}
{
}

JsonValReq::Sp JsonArrayValReq::shared(const boost::optional<Size>& minSize,
                                       const boost::optional<Size>& maxSize,
                                       JsonValReq::Sp elemValReq)
{
    return std::make_shared<JsonArrayValReq>(minSize, maxSize, std::move(elemValReq));
}

JsonValReq::Sp JsonArrayValReq::shared(const Size exactSize, JsonValReq::Sp elemValReq)
{
    return std::make_shared<JsonArrayValReq>(exactSize, std::move(elemValReq));
}

JsonValReq::Sp JsonArrayValReq::shared(JsonValReq::Sp elemValReq)
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

JsonObjValPropReq::JsonObjValPropReq(JsonValReq::Sp valReq, const bool isRequired) :
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
    JsonValReq {JsonVal::Kind::Obj},
    _propReqs {std::move(propReqs)},
    _allowUnknownProps {allowUnknownProps}
{
}

JsonValReq::Sp JsonObjValReq::shared(PropReqs propReqs, const bool allowUnknownProps)
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
