/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <unordered_set>
#include <string>

#include <yactfr/text-parse-error.hpp>

#include "ctf-2-json-val-req.hpp"
#include "ctf-2-json-strs.hpp"

namespace yactfr {
namespace internal {

/*
 * CTF 2 JSON byte order value requirement.
 */
class JsonBoValReq final :
    public JsonStrValInSetReq
{
public:
    explicit JsonBoValReq() :
        JsonStrValInSetReq {JsonStrValInSetReq::Set {strs::be, strs::le}}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonBoValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonStrValInSetReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid byte order:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON bit order value requirement.
 */
class JsonBioValReq final :
    public JsonStrValInSetReq
{
public:
    explicit JsonBioValReq() :
        JsonStrValInSetReq {JsonStrValInSetReq::Set {strs::ftl, strs::ltf}}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonBioValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonStrValInSetReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid bit order:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON UUID value requirement.
 */
class JsonUuidValReq final :
    public JsonArrayValReq
{
public:
    explicit JsonUuidValReq() :
        JsonArrayValReq {16, JsonUIntValInRangeReq::shared(0, 255)}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonUuidValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonArrayValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid UUID:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON data location value requirement.
 */
class JsonDataLocValReq final :
    public JsonObjValReq
{
public:
    explicit JsonDataLocValReq() :
        JsonObjValReq {{
            {strs::orig, {JsonStrValInSetReq::shared({
                strs::pktHeader,
                strs::pktCtx,
                strs::erHeader,
                strs::erCommonCtx,
                strs::erSpecCtx,
                strs::erPayload,
            })}},
            {strs::path, {
                JsonArrayValReq::shared(1, boost::none,
                                        JsonValReq::shared(JsonVal::Kind::Str, true)),
                true
            }},
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonDataLocValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);

            const auto& jsonLastPathElem = **(jsonVal.asObj()[strs::path]->asArray().end() - 1);

            if (jsonLastPathElem.isNull()) {
                throwTextParseError("Path ends with `null`.", jsonLastPathElem.loc());
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid data location:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON attributes value requirement.
 */
class JsonAttrsValReq final :
    public JsonObjValReq
{
public:
    explicit JsonAttrsValReq() :
        JsonObjValReq {{}, true}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonAttrsValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid attributes:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON extensions value requirement.
 */
class JsonExtValReq final :
    public JsonObjValReq
{
public:
    explicit JsonExtValReq() :
        JsonObjValReq {{}, true}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonExtValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid extensions:", jsonVal.loc());
            throw;
        }

        if (jsonVal.asObj().size() > 0) {
            // never valid
            throwTextParseError("yactfr doesn't support any extension.", jsonVal.loc());
        }
    }
};

/*
 * JSON (any) integer value requirement.
 */
class JsonIntValReq :
    public JsonValReq
{
public:
    static Sp shared()
    {
        return std::make_shared<JsonIntValReq>();
    }

protected:
    void _validate(const JsonVal& jsonVal) const override
    {
        if (!jsonVal.isUInt() && !jsonVal.isSInt()) {
            throwTextParseError("Expecting an integer.", jsonVal.loc());
        }
    }
};

/*
 * JSON unsigned integer value requirement.
 */
class JsonUIntValReq final :
    public JsonValReq
{
public:
    explicit JsonUIntValReq() :
        JsonValReq {JsonVal::Kind::UInt}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonUIntValReq>();
    }
};

namespace {

void validateSIntUll(const JsonVal& jsonVal)
{
    if (!jsonVal.isUInt()) {
        return;
    }

    static constexpr auto llMaxAsUll = static_cast<unsigned long long>(std::numeric_limits<long long>::max());

    if (*jsonVal.asUInt() > llMaxAsUll) {
        std::ostringstream ss;

        ss << "Expecting a signed integer: " << *jsonVal.asUInt() <<
              " is greater than " << llMaxAsUll << '.';
        throwTextParseError(ss.str(), jsonVal.loc());
    }
}

} // namespace

/*
 * JSON signed integer value (range) requirement.
 */
class JsonSIntValReq final :
    public JsonIntValReq
{
public:
    static Sp shared()
    {
        return std::make_shared<JsonSIntValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        JsonIntValReq::_validate(jsonVal);
        validateSIntUll(jsonVal);
    }
};

/*
 * CTF 2 JSON integer range value requirement.
 *
 * An instance of this class validates that a given JSON value is a CTF
 * 2 integer range, both contained values satisfying an instance
 * of `JsonIntValReqT`.
 */
template <typename JsonIntValReqT>
class JsonIntRangeValReqBase final :
    public JsonArrayValReq
{
public:
    explicit JsonIntRangeValReqBase() :
        JsonArrayValReq {2, JsonIntValReqT::shared()}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonIntRangeValReqBase>();
    }

private:
    template <typename LowerT, typename UpperT>
    static void _throwLowerGtUpper(const LowerT lower, const UpperT upper, const TextLocation& loc)
    {
        std::ostringstream ss;

        ss << lower << " is greater than " << upper << '.';
        throwTextParseError(ss.str(), loc);
    }

    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonArrayValReq::_validate(jsonVal);

            /*
             * Here's the truth table:
             *
             * ╔════╦════════════╦════════════╦═══════════════════════════╗
             * ║ ID ║ Lower      ║ Upper      ║ Valid?                    ║
             * ╠════╬════════════╬════════════╬═══════════════════════════╣
             * ║ 1  ║ Unsigned   ║ Unsigned   ║ Lower < upper             ║
             * ║ 2  ║ Signed     ║ Signed     ║ Lower < upper             ║
             * ║ 3  ║ Unsigned   ║ Signed ≥ 0 ║ Lower < upper as unsigned ║
             * ║ 4  ║ Unsigned   ║ Signed < 0 ║ No                        ║
             * ║ 5  ║ Signed ≥ 0 ║ Unsigned   ║ Lower as unsigned < upper ║
             * ║ 6  ║ Signed < 0 ║ Unsigned   ║ Yes                       ║
             * ╚════╩════════════╩════════════╩═══════════════════════════╝
             */
            auto& lowerJsonVal = jsonVal.asArray()[0];
            auto& upperJsonVal = jsonVal.asArray()[1];

            if (lowerJsonVal.isUInt()) {
                const auto uLower = *lowerJsonVal.asUInt();

                if (upperJsonVal.isUInt()) {
                    const auto uUpper = *upperJsonVal.asUInt();

                    if (uUpper < uLower) {
                        // ID 1
                        this->_throwLowerGtUpper(uLower, uUpper, jsonVal.loc());
                    }
                } else {
                    const auto sUpper = *upperJsonVal.asSInt();

                    if (sUpper < 0) {
                        // ID 4
                        this->_throwLowerGtUpper(uLower, sUpper, jsonVal.loc());
                    }

                    if (static_cast<unsigned long long>(sUpper) < uLower) {
                        // ID 3
                        this->_throwLowerGtUpper(uLower, sUpper, jsonVal.loc());
                    }
                }
            } else {
                const auto sLower = *lowerJsonVal.asSInt();

                if (upperJsonVal.isSInt()) {
                    const auto sUpper = *upperJsonVal.asSInt();

                    if (sUpper < sLower) {
                        // ID 2
                        this->_throwLowerGtUpper(sLower, sUpper, jsonVal.loc());
                    }
                } else if (sLower >= 0) {
                    const auto uUpper = *upperJsonVal.asUInt();

                    if (uUpper < static_cast<unsigned long long>(sLower)) {
                        // ID 5
                        this->_throwLowerGtUpper(sLower, uUpper, jsonVal.loc());
                    }
                }
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid integer range:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON unsigned integer range value requirement.
 */
using JsonUIntRangeValReq = JsonIntRangeValReqBase<JsonUIntValReq>;

/*
 * CTF 2 JSON signed integer range value requirement.
 */
using JsonSIntRangeValReq = JsonIntRangeValReqBase<JsonSIntValReq>;

/*
 * CTF 2 JSON integer range value requirement.
 */
using JsonIntRangeValReq = JsonIntRangeValReqBase<JsonIntValReq>;

/*
 * CTF 2 JSON integer range set value requirement.
 *
 * An instance of this class validates that a given JSON value is a
 * CTF 2 integer range set, each element satisfying an instance of
 * `JsonIntRangeValReqBase<JsonIntValReqT>`.
 */
template <typename JsonIntValReqT>
class JsonIntRangeSetValReqBase final :
    public JsonArrayValReq
{
public:
    explicit JsonIntRangeSetValReqBase() :
        JsonArrayValReq {1, boost::none, JsonIntRangeValReqBase<JsonIntValReqT>::shared()}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonIntRangeSetValReqBase>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonArrayValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid integer range set:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON unsigned integer range set value requirement.
 */
using JsonUIntRangeSetValReq = JsonIntRangeSetValReqBase<JsonUIntValReq>;

/*
 * CTF 2 JSON signed integer range set value requirement.
 */
using JsonSIntRangeSetValReq = JsonIntRangeSetValReqBase<JsonSIntValReq>;

/*
 * CTF 2 JSON integer range set value requirement.
 */
using JsonIntRangeSetValReq = JsonIntRangeSetValReqBase<JsonIntValReq>;

/*
 * CTF 2 JSON roles value requirement.
 */
class JsonRolesValReq final :
    public JsonArrayValReq
{
public:
    explicit JsonRolesValReq() :
        JsonArrayValReq {JsonValReq::shared(JsonVal::Kind::Str)}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonRolesValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonArrayValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid roles:", jsonVal.loc());
            throw;
        }
    }
};

namespace {

/*
 * Adds a JSON object value property requirement having the key `key` to
 * `propReqs`, passing `valReq` and `isRequired` to its constructor.
 */
void addToPropReqs(JsonObjValReq::PropReqs& propReqs, std::string&& key,
                          JsonValReq::Sp valReq, const bool isRequired = false)
{
    propReqs.emplace(std::make_pair(std::move(key),
                                    JsonObjValPropReq {std::move(valReq), isRequired}));
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object type object
 * property requirement.
 */
JsonObjValReq::PropReqsEntry objTypePropReqEntry(std::string&& type)
{
    return {strs::type, {JsonStrValInSetReq::shared(std::move(type)), true}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 attributes object
 * property requirement.
 */
JsonObjValReq::PropReqsEntry attrsPropReqEntry()
{
    return {strs::attrs, {JsonAttrsValReq::shared()}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 extensions object
 * property requirement.
 */
JsonObjValReq::PropReqsEntry extPropReqEntry()
{
    return {strs::ext, {JsonExtValReq::shared()}};
}

} // namespace

/*
 * CTF 2 JSON full data type value abstract requirement.
 */
class JsonDtValReq :
    public JsonObjValReq
{
protected:
    explicit JsonDtValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonObjValReq {this->_buildPropReqs(std::move(type), std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(std::string&& type, PropReqs&& propReqs)
    {
        propReqs.insert(objTypePropReqEntry(std::move(type)));
        propReqs.insert(attrsPropReqEntry());
        propReqs.insert(extPropReqEntry());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON fixed-length bit array type value requirement.
 */
class JsonFlBitArrayTypeValReq :
    public JsonDtValReq
{
protected:
    explicit JsonFlBitArrayTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonDtValReq {std::move(type), this->_buildPropReqs(std::move(propReqs))}
    {
    }

public:
    explicit JsonFlBitArrayTypeValReq() :
        JsonFlBitArrayTypeValReq {this->typeStr()}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonFlBitArrayTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::flBitArray;
    }

protected:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length bit array type:",
                                      jsonVal.loc());
            throw;
        }
    }

private:
    static PropReqs _buildPropReqs(PropReqs&& propReqs)
    {
        addToPropReqs(propReqs, strs::len, JsonUIntValInRangeReq::shared(1, 64), true);
        addToPropReqs(propReqs, strs::bo, JsonBoValReq::shared(), true);
        addToPropReqs(propReqs, strs::bio, JsonBioValReq::shared());
        addToPropReqs(propReqs, strs::align, JsonUIntValIsAlignReq::shared());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON integer type mappings or bit map flags value requirement.
 *
 * An instance of this class validates that a given JSON value is a
 * CTF 2 integer type mappings object or a CTF 2 bit map flags object,
 * each integer value within the integer ranges satisfying an instance
 * of `JsonIntValReqT`.
 */
template <typename JsonIntValReqT>
class JsonIntTypeMappingsFlagsValReq final :
    public JsonObjValReq
{
public:
    explicit JsonIntTypeMappingsFlagsValReq(const char * const propName,
                                            const char * const objName,
                                            const bool allowEmpty = true) :
        JsonObjValReq {{}, true},
        _propName {propName},
        _objName {objName},
        _allowEmpty {allowEmpty}
    {
    }

    static Sp shared(const char * const propName, const char * const objName,
                     const bool allowEmpty = true)
    {
        return std::make_shared<JsonIntTypeMappingsFlagsValReq>(propName, objName, allowEmpty);
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);

            if (!_allowEmpty && jsonVal.asObj().size() < 1) {
                std::ostringstream ss;

                ss << "Expecting at least one " << _propName << '.';
                throwTextParseError(ss.str(), jsonVal.loc());
            }

            for (auto& keyJsonValPair : jsonVal.asObj()) {
                try {
                    _rangeSetReq.validate(*keyJsonValPair.second);
                } catch (TextParseError& exc) {
                    std::ostringstream ss;

                    ss << "In " << _propName << " `" << keyJsonValPair.first << "`:";
                    appendMsgToTextParseError(exc, ss.str(), jsonVal.loc());
                    throw;
                }
            }
        } catch (TextParseError& exc) {
            std::ostringstream ss;

            ss << "Invalid " << _objName << ":";
            appendMsgToTextParseError(exc, ss.str(), jsonVal.loc());
            throw;
        }
    }

private:
    JsonIntRangeSetValReqBase<JsonIntValReqT> _rangeSetReq;
    const char *_propName;
    const char *_objName;
    bool _allowEmpty;
};

/*
 * CTF 2 JSON fixed-length bit map type value requirement.
 */
class JsonFlBitMapTypeValReq final :
    public JsonFlBitArrayTypeValReq
{
public:
    explicit JsonFlBitMapTypeValReq() :
        JsonFlBitArrayTypeValReq {this->typeStr(), {
            {strs::flags, {
                JsonIntTypeMappingsFlagsValReq<JsonUIntValReq>::shared("flag",
                                                                       "fixed-length bit map type flags",
                                                                       false),
                true,
            }},
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonFlBitMapTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::flBitMap;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length bit map type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON fixed-length boolean type value requirement.
 */
class JsonFlBoolTypeValReq final :
    public JsonFlBitArrayTypeValReq
{
public:
    explicit JsonFlBoolTypeValReq() :
        JsonFlBitArrayTypeValReq {this->typeStr()}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonFlBoolTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::flBool;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length boolean type:", jsonVal.loc());
            throw;
        }
    }
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 integer type
 * preferred display base object property requirement.
 */
JsonObjValReq::PropReqsEntry intTypePrefDispBasePropReqEntry()
{
    return {strs::prefDispBase, {JsonUIntValInSetReq::shared({2, 8, 10, 16})}};
}

} // namespace

/*
 * CTF 2 JSON fixed-length integer type value abstract requirement.
 */
class JsonFlIntTypeValReq :
    public JsonFlBitArrayTypeValReq
{
protected:
    explicit JsonFlIntTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonFlBitArrayTypeValReq {std::move(type), this->_buildPropReqs(std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(PropReqs&& propReqs)
    {
        propReqs.insert(intTypePrefDispBasePropReqEntry());
        return std::move(propReqs);
    }
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 data type roles
 * object property requirement.
 */
JsonObjValReq::PropReqsEntry rolesPropReqEntry()
{
    return {strs::roles, {JsonRolesValReq::shared()}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 integer type
 * mappings object property requirement.
 */
template <typename JsonIntValReqT>
JsonObjValReq::PropReqsEntry intTypeMappingsPropReqEntry()
{
    return {strs::mappings, {JsonIntTypeMappingsFlagsValReq<JsonIntValReqT>::shared("mapping",
                                                                                    "integer type mappings")}};
}

} // namespace

/*
 * CTF 2 JSON fixed-length unsigned integer type value requirement.
 */
class JsonFlUIntTypeValReq final :
    public JsonFlIntTypeValReq
{
public:
    explicit JsonFlUIntTypeValReq() :
        JsonFlIntTypeValReq {
            this->typeStr(),
            {
                rolesPropReqEntry(),
                intTypeMappingsPropReqEntry<JsonUIntValReq>(),
            },
        }
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonFlUIntTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::flUInt;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFlIntTypeValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length unsigned integer type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON fixed-length signed integer type value requirement.
 */
class JsonFlSIntTypeValReq final :
    public JsonFlIntTypeValReq
{
public:
    explicit JsonFlSIntTypeValReq() :
        JsonFlIntTypeValReq {this->typeStr(), {intTypeMappingsPropReqEntry<JsonSIntValReq>()}}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonFlSIntTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::flSInt;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFlIntTypeValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length signed integer type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON fixed-length floating-point number type value requirement.
 */
class JsonFlFloatTypeValReq final :
    public JsonFlBitArrayTypeValReq
{
public:
    explicit JsonFlFloatTypeValReq() :
        JsonFlBitArrayTypeValReq {this->typeStr()}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonFlFloatTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::flFloat;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);

            auto& jsonLenVal = *jsonVal.asObj()[strs::len];
            const auto len = *jsonLenVal.asUInt();

            if (len != 32 && len != 64) {
                std::ostringstream ss;

                ss << "Unexpected length " << len << ": yactfr only supports 32 and 64.";
                throwTextParseError(ss.str(), jsonLenVal.loc());
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc,
                                      "Invalid fixed-length floating-point number type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON variable-length integer type value abstract requirement.
 */
class JsonVlIntTypeValReq :
    public JsonDtValReq
{
protected:
    explicit JsonVlIntTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonDtValReq {std::move(type), this->_buildPropReqs(std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(PropReqs&& propReqs)
    {
        propReqs.insert(intTypePrefDispBasePropReqEntry());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON variable-length unsigned integer type value requirement.
 */
class JsonVlUIntTypeValReq final :
    public JsonVlIntTypeValReq
{
public:
    explicit JsonVlUIntTypeValReq() :
        JsonVlIntTypeValReq {
            this->typeStr(),
            {
                rolesPropReqEntry(),
                intTypeMappingsPropReqEntry<JsonUIntValReq>(),
            },
        }
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonVlUIntTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::vlUInt;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonVlIntTypeValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variable-length unsigned integer type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON variable-length signed integer type value requirement.
 */
class JsonVlSIntTypeValReq final :
    public JsonVlIntTypeValReq
{
public:
    explicit JsonVlSIntTypeValReq() :
        JsonVlIntTypeValReq {this->typeStr(), {intTypeMappingsPropReqEntry<JsonSIntValReq>()}}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonVlSIntTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::vlSInt;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonVlIntTypeValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variable-length signed integer type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON string type value abstract requirement.
 */
class JsonStrTypeValReq :
    public JsonDtValReq
{
protected:
    explicit JsonStrTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonDtValReq {std::move(type), this->_buildPropReqs(std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(PropReqs&& propReqs)
    {
        addToPropReqs(propReqs, strs::encoding, JsonStrValInSetReq::shared({
            strs::utf8,
            strs::utf16Be,
            strs::utf16Le,
            strs::utf32Be,
            strs::utf32Le,
        }));
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON null-terminated string type value requirement.
 */
class JsonNtStrTypeValReq final :
    public JsonStrTypeValReq
{
public:
    explicit JsonNtStrTypeValReq() :
        JsonStrTypeValReq {this->typeStr()}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonNtStrTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::ntStr;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonStrTypeValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid null-terminated string type:", jsonVal.loc());
            throw;
        }
    }
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 static-length data
 * type length object property requirement.
 */
JsonObjValReq::PropReqsEntry slDtLenPropReqEntry()
{
    return {strs::len, {JsonValReq::shared(JsonVal::Kind::UInt), true}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 dynamic-length data
 * type length location object property requirement.
 */
JsonObjValReq::PropReqsEntry dlDtLenFieldLocPropReqEntry()
{
    return {strs::lenFieldLoc, {JsonDataLocValReq::shared(), true}};
}

} // namespace

/*
 * CTF 2 JSON static-length string type value requirement.
 */
class JsonSlStrTypeValReq final :
    public JsonStrTypeValReq
{
public:
    explicit JsonSlStrTypeValReq() :
        JsonStrTypeValReq {this->typeStr(), {slDtLenPropReqEntry()}}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonSlStrTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::slStr;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonStrTypeValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid static-length string type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON dynamic-length string type value requirement.
 */
class JsonDlStrTypeValReq final :
    public JsonStrTypeValReq
{
public:
    explicit JsonDlStrTypeValReq() :
        JsonStrTypeValReq {this->typeStr(), {dlDtLenFieldLocPropReqEntry()}}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonDlStrTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::dlStr;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonStrTypeValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid dynamic-length string type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON BLOB type value abstract requirement.
 */
class JsonBlobTypeValReq :
    public JsonDtValReq
{
protected:
    explicit JsonBlobTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonDtValReq {std::move(type), this->_buildPropReqs(std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(PropReqs&& propReqs)
    {
        addToPropReqs(propReqs, strs::mediaType, JsonValReq::shared(JsonVal::Kind::Str));
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON static-length BLOB type value requirement.
 */
class JsonSlBlobTypeValReq final :
    public JsonBlobTypeValReq
{
public:
    explicit JsonSlBlobTypeValReq() :
        JsonBlobTypeValReq {this->typeStr(), this->_buildPropReqs()}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonSlBlobTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::slBlob;
    }

private:
    static PropReqs _buildPropReqs()
    {
        PropReqs propReqs;

        propReqs.insert(slDtLenPropReqEntry());
        propReqs.insert(rolesPropReqEntry());
        return propReqs;
    }

    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid static-length BLOB type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON dynamic-length BLOB type value requirement.
 */
class JsonDlBlobTypeValReq final :
    public JsonBlobTypeValReq
{
public:
    explicit JsonDlBlobTypeValReq() :
        JsonBlobTypeValReq {this->typeStr(), {dlDtLenFieldLocPropReqEntry()}}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonDlBlobTypeValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::dlBlob;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid dynamic-length BLOB type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

class JsonAnyFullDtValReq;

/*
 * CTF 2 data types are recursive, in that some data types may contain
 * other data types.
 *
 * To make it possible to build a `JsonAnyFullDtValReq` instance without
 * a shared pointer, the constructor of compound data type requirements
 * accepts a `const JsonAnyFullDtValReq *` (raw pointer) parameter. The
 * raw pointer must therefore remain valid as long as the compound data
 * type using it exists.
 *
 * Because JSON value requirements work with shared pointers to
 * `JsonValReq` (`JsonValReq::Sp`), this `JsonAnyDtValReqWrapper` class
 * simply wraps such a `const JsonAnyFullDtValReq *` value: its
 * _validate() method forwards the call. A `JsonAnyDtValReqWrapper`
 * instance doesn't own the raw pointer.
 */
class JsonAnyDtValReqWrapper final :
    public JsonValReq
{
public:
    explicit JsonAnyDtValReqWrapper(const JsonAnyFullDtValReq& anyFullDtValReq) :
        _anyFullDtValReq {&anyFullDtValReq}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonAnyDtValReqWrapper>(anyFullDtValReq);
    }

private:
    void _validate(const JsonVal& jsonVal) const override;

private:
    const JsonAnyFullDtValReq *_anyFullDtValReq;
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 data type property
 * requirement having the key `key`.
 */
JsonObjValReq::PropReqsEntry anyDtPropReqEntry(std::string&& key,
                                               const JsonAnyFullDtValReq& anyFullDtValReq,
                                               const bool isRequired = false)
{
    return {std::move(key), {JsonAnyDtValReqWrapper::shared(anyFullDtValReq), isRequired}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object name object
 * property requirement.
 */
JsonObjValReq::PropReqsEntry namePropReqEntry(const bool isRequired)
{
    return {strs::name, {JsonValReq::shared(JsonVal::Kind::Str), isRequired}};
}

} // namespace

/*
 * CTF 2 JSON structure field member type value requirement.
 */
class JsonStructMemberTypeValReq final :
    public JsonObjValReq
{
public:
    explicit JsonStructMemberTypeValReq(const JsonAnyFullDtValReq& anyFullDtValReq) :
        JsonObjValReq {{
            namePropReqEntry(true),
            anyDtPropReqEntry(strs::fc, anyFullDtValReq, true),
            attrsPropReqEntry(),
            extPropReqEntry(),
        }}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonStructMemberTypeValReq>(anyFullDtValReq);
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid structure member type:", jsonVal.loc());
            throw;
        }
    }
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 minimum alignment
 * object property requirement.
 */
JsonObjValReq::PropReqsEntry minAlignPropReqEntry()
{
    return {strs::minAlign, JsonUIntValIsAlignReq::shared()};
}

void validateUniqueEntryNames(const JsonVal& jsonVal, const char * const propName,
                              const char * const what)
{
    if (const auto jsonEntries = jsonVal.asObj()[propName]) {
        std::unordered_set<std::string> names;

        for (auto& jsonEntryVal : jsonEntries->asArray()) {
            if (const auto jsonNameVal = jsonEntryVal->asObj()[strs::name]) {
                auto& jsonNameStrVal = jsonNameVal->asStr();

                if (names.count(*jsonNameStrVal) != 0) {
                    std::ostringstream ss;

                    ss << "Duplicate " << what << " name `" << *jsonNameStrVal << "`.";
                    throwTextParseError(ss.str(), jsonNameVal->loc());
                }

                names.insert(*jsonNameStrVal);
            }
        }
    }
}

} // namespace

/*
 * CTF 2 JSON structure type value requirement.
 */
class JsonStructTypeValReq final :
    public JsonDtValReq
{
public:
    explicit JsonStructTypeValReq(const JsonAnyFullDtValReq& anyFullDtValReq) :
        JsonDtValReq {this->typeStr(), {
            {strs::memberClss, {
                JsonArrayValReq::shared(JsonStructMemberTypeValReq::shared(anyFullDtValReq))
            }},
            minAlignPropReqEntry(),
        }}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonStructTypeValReq>(anyFullDtValReq);
    }

    static const char *typeStr() noexcept
    {
        return strs::structure;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);

            // validate that member type names are unique
            validateUniqueEntryNames(jsonVal, strs::memberClss, "structure member type");
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid structure type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON array type value abstract requirement.
 */
class JsonArrayTypeValReq :
    public JsonDtValReq
{
protected:
    explicit JsonArrayTypeValReq(std::string&& type, const JsonAnyFullDtValReq& anyFullDtValReq,
                                 PropReqs&& propReqs = {}) :
        JsonDtValReq {std::move(type), this->_buildPropReqs(anyFullDtValReq, std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(const JsonAnyFullDtValReq& anyFullDtValReq, PropReqs&& propReqs)
    {
        propReqs.insert(anyDtPropReqEntry(strs::elemFc, anyFullDtValReq, true));
        propReqs.insert(minAlignPropReqEntry());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON static-length array type value requirement.
 */
class JsonSlArrayTypeValReq final :
    public JsonArrayTypeValReq
{
public:
    explicit JsonSlArrayTypeValReq(const JsonAnyFullDtValReq& anyFullDtValReq) :
        JsonArrayTypeValReq {this->typeStr(), anyFullDtValReq, {slDtLenPropReqEntry()}}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonSlArrayTypeValReq>(anyFullDtValReq);
    }

    static const char *typeStr() noexcept
    {
        return strs::slArray;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid static-length array type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON dynamic-length array type value requirement.
 */
class JsonDlArrayTypeValReq final :
    public JsonArrayTypeValReq
{
public:
    explicit JsonDlArrayTypeValReq(const JsonAnyFullDtValReq& anyFullDtValReq) :
        JsonArrayTypeValReq {this->typeStr(), anyFullDtValReq, {dlDtLenFieldLocPropReqEntry()}}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonDlArrayTypeValReq>(anyFullDtValReq);
    }

    static const char *typeStr() noexcept
    {
        return strs::dlArray;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid dynamic-length array type:", jsonVal.loc());
            throw;
        }
    }
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 selector location
 * object property requirement.
 */
JsonObjValReq::PropReqsEntry selLocPropReqEntry()
{
    return {strs::selFieldLoc, {JsonDataLocValReq::shared(), true}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 selector ranges
 * object property requirement.
 */
JsonObjValReq::PropReqsEntry selRangesPropReqEntry(const bool isRequired)
{
    return {strs::selFieldRanges, {JsonIntRangeSetValReq::shared(), isRequired}};
}

} // namespace

/*
 * CTF 2 JSON optional type value requirement.
 */
class JsonOptTypeValReq final :
    public JsonDtValReq
{
public:
    explicit JsonOptTypeValReq(const JsonAnyFullDtValReq& anyFullDtValReq) :
        JsonDtValReq {this->typeStr(), {
            anyDtPropReqEntry(strs::fc, anyFullDtValReq, true),
            selLocPropReqEntry(),
            selRangesPropReqEntry(false),
        }}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonOptTypeValReq>(anyFullDtValReq);
    }

    static const char *typeStr() noexcept
    {
        return strs::opt;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid optional type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON variant type option value requirement.
 */
class JsonVarTypeOptValReq final :
    public JsonObjValReq
{
public:
    explicit JsonVarTypeOptValReq(const JsonAnyFullDtValReq& anyFullDtValReq) :
        JsonObjValReq {{
            namePropReqEntry(false),
            anyDtPropReqEntry(strs::fc, anyFullDtValReq, true),
            selRangesPropReqEntry(true),
            attrsPropReqEntry(),
            extPropReqEntry(),
        }}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonVarTypeOptValReq>(anyFullDtValReq);
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        /*
         * Not checking for integer range overlaps here because we don't
         * know the signedness of those ranges yet (depends on the
         * effective selector type(s)).
         *
         * This will be easier to do once we know the signedness,
         * comparing only integers having the same type.
         */
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variant type option:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON variant type value requirement.
 */
class JsonVarTypeValReq final :
    public JsonDtValReq
{
public:
    explicit JsonVarTypeValReq(const JsonAnyFullDtValReq& anyFullDtValReq) :
        JsonDtValReq {this->typeStr(), {
            {strs::opts, {
                JsonArrayValReq::shared(1, boost::none,
                                        JsonVarTypeOptValReq::shared(anyFullDtValReq)),
                true
            }},
            selLocPropReqEntry(),
        }}
    {
    }

    static Sp shared(const JsonAnyFullDtValReq& anyFullDtValReq)
    {
        return std::make_shared<JsonVarTypeValReq>(anyFullDtValReq);
    }

    static const char *typeStr() noexcept
    {
        return strs::var;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);

            // validate that option names are unique
            validateUniqueEntryNames(jsonVal, strs::opts, "variant type option");
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variant type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON (any) data type value requirement.
 */
class JsonAnyFullDtValReq final :
    public JsonObjValReq
{
public:
    explicit JsonAnyFullDtValReq() :
        JsonObjValReq {{
            {strs::type, {
                JsonStrValInSetReq::shared({
                    JsonFlBitArrayTypeValReq::typeStr(),
                    JsonFlBitMapTypeValReq::typeStr(),
                    JsonFlBoolTypeValReq::typeStr(),
                    JsonFlUIntTypeValReq::typeStr(),
                    JsonFlSIntTypeValReq::typeStr(),
                    JsonFlFloatTypeValReq::typeStr(),
                    JsonVlUIntTypeValReq::typeStr(),
                    JsonVlSIntTypeValReq::typeStr(),
                    JsonNtStrTypeValReq::typeStr(),
                    JsonSlStrTypeValReq::typeStr(),
                    JsonDlStrTypeValReq::typeStr(),
                    JsonSlBlobTypeValReq::typeStr(),
                    JsonDlBlobTypeValReq::typeStr(),
                    JsonStructTypeValReq::typeStr(),
                    JsonSlArrayTypeValReq::typeStr(),
                    JsonDlArrayTypeValReq::typeStr(),
                    JsonOptTypeValReq::typeStr(),
                    JsonVarTypeValReq::typeStr(),
                }),
                true
            }},
        }, true},
        _structTypeValReq {*this},
        _slArrayTypeValReq {*this},
        _dlArrayTypeValReq {*this},
        _optTypeValReq {*this},
        _varTypeValReq {*this}
    {
        this->_addToDtValReqs(_flBitArrayTypeValReq);
        this->_addToDtValReqs(_flBitMapTypeValReq);
        this->_addToDtValReqs(_flBoolTypeValReq);
        this->_addToDtValReqs(_flUIntTypeValReq);
        this->_addToDtValReqs(_flSIntTypeValReq);
        this->_addToDtValReqs(_flFloatTypeValReq);
        this->_addToDtValReqs(_vlUIntTypeValReq);
        this->_addToDtValReqs(_vlSIntTypeValReq);
        this->_addToDtValReqs(_ntStrTypeValReq);
        this->_addToDtValReqs(_slStrTypeValReq);
        this->_addToDtValReqs(_dlStrTypeValReq);
        this->_addToDtValReqs(_slBlobTypeValReq);
        this->_addToDtValReqs(_dlBlobTypeValReq);
        this->_addToDtValReqs(_structTypeValReq);
        this->_addToDtValReqs(_slArrayTypeValReq);
        this->_addToDtValReqs(_dlArrayTypeValReq);
        this->_addToDtValReqs(_optTypeValReq);
        this->_addToDtValReqs(_varTypeValReq);
    }

    static Sp shared()
    {
        return std::make_shared<JsonAnyFullDtValReq>();
    }

private:
    template <typename JsonValReqT>
    void _addToDtValReqs(const JsonValReqT& valReq)
    {
        const auto typeStr = JsonValReqT::typeStr();

        assert(_dtValReqs.find(typeStr) == _dtValReqs.end());
        _dtValReqs.insert(std::make_pair(typeStr, &valReq));
    }

    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid data type:", jsonVal.loc());
            throw;
        }

        /*
         * This part doesn't need to be catched because the specific
         * _validate() method already appends a message like
         * "Invalid xyz type:" to the exception.
         */
        const auto it = _dtValReqs.find(*jsonVal.asObj()[strs::type]->asStr());

        assert(it != _dtValReqs.end());
        it->second->validate(jsonVal);
    }

private:
    JsonFlBitArrayTypeValReq _flBitArrayTypeValReq;
    JsonFlBitMapTypeValReq _flBitMapTypeValReq;
    JsonFlBoolTypeValReq _flBoolTypeValReq;
    JsonFlUIntTypeValReq _flUIntTypeValReq;
    JsonFlSIntTypeValReq _flSIntTypeValReq;
    JsonFlFloatTypeValReq _flFloatTypeValReq;
    JsonVlUIntTypeValReq _vlUIntTypeValReq;
    JsonVlSIntTypeValReq _vlSIntTypeValReq;
    JsonNtStrTypeValReq _ntStrTypeValReq;
    JsonSlStrTypeValReq _slStrTypeValReq;
    JsonDlStrTypeValReq _dlStrTypeValReq;
    JsonSlBlobTypeValReq _slBlobTypeValReq;
    JsonDlBlobTypeValReq _dlBlobTypeValReq;
    JsonStructTypeValReq _structTypeValReq;
    JsonSlArrayTypeValReq _slArrayTypeValReq;
    JsonDlArrayTypeValReq _dlArrayTypeValReq;
    JsonOptTypeValReq _optTypeValReq;
    JsonVarTypeValReq _varTypeValReq;
    std::unordered_map<std::string, const JsonValReq *> _dtValReqs;
};

void JsonAnyDtValReqWrapper::_validate(const JsonVal& jsonVal) const
{
    // check for data type alias name (JSON string)
    if (jsonVal.isStr()) {
        /*
         * Always valid: PseudoDtErector::pseudoDtOfCtf2Obj() will
         * validate that the data type alias exists.
         */
        return;
    }

    // delegate
    _anyFullDtValReq->validate(jsonVal);
}

/*
 * CTF 2 JSON fragment value abstract requirement.
 */
class JsonFragValReq :
    public JsonObjValReq
{
protected:
    explicit JsonFragValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonObjValReq {this->_buildPropReqs(std::move(type), std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(std::string&& type, PropReqs&& propReqs)
    {
        propReqs.insert(objTypePropReqEntry(std::move(type)));
        propReqs.insert(attrsPropReqEntry());
        propReqs.insert(extPropReqEntry());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 preamble fragment value requirement.
 */
class JsonPreFragValReq final :
    public JsonFragValReq
{
public:
    explicit JsonPreFragValReq() :
        JsonFragValReq {this->typeStr(), {
            {strs::version, {JsonUIntValInSetReq::shared(2), true}},
            {strs::uuid, {JsonUuidValReq::shared()}},
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonPreFragValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::pre;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFragValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid preamble fragment:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 data type alias fragment value requirement.
 */
class JsonDtAliasFragValReq final :
    public JsonFragValReq
{
public:
    explicit JsonDtAliasFragValReq() :
        JsonFragValReq {this->typeStr(), {
            namePropReqEntry(true),
            anyDtPropReqEntry(strs::fc, _anyFullDtValReq, true), //-V1050
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonDtAliasFragValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::fcAlias;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFragValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid data type alias fragment:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonAnyFullDtValReq _anyFullDtValReq;
};

/*
 * CTF 2 JSON clock offset value requirement.
 */
class JsonClkOffsetValReq final :
    public JsonObjValReq
{
public:
    explicit JsonClkOffsetValReq() :
        JsonObjValReq {{
            {strs::secs, {JsonSIntValReq::shared()}},
            {strs::cycles, {JsonValReq::shared(JsonVal::Kind::UInt)}},
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonClkOffsetValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid clock offset:", jsonVal.loc());
            throw;
        }
    }
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object namespace
 * object property requirement.
 */
JsonObjValReq::PropReqsEntry nsPropReqEntry()
{
    return {strs::ns, {JsonValReq::shared(JsonVal::Kind::Str)}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object unique ID
 * object property requirement.
 */
JsonObjValReq::PropReqsEntry uidPropReqEntry(const bool isRequired)
{
    return {strs::uid, {JsonValReq::shared(JsonVal::Kind::Str), isRequired}};
}

} // namespace

/*
 * CTF 2 JSON clock origin value requirement.
 */
class JsonClkOrigValReq final :
    public JsonObjValReq
{
public:
    explicit JsonClkOrigValReq() :
        JsonObjValReq {{
            nsPropReqEntry(),
            namePropReqEntry(true),
            uidPropReqEntry(true),
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonClkOrigValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid clock origin:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON clock type origin property requirement.
 */
class JsonClkTypeOrigPropValReq final :
    public JsonValReq
{
public:
    explicit JsonClkTypeOrigPropValReq() = default;

    static Sp shared()
    {
        return std::make_shared<JsonClkTypeOrigPropValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            if (jsonVal.isStr()) {
                if (*jsonVal.asStr() != strs::unixEpoch) {
                    std::ostringstream ss;

                    ss << "Expecting `" << strs::unixEpoch << "` or a clock origin object.";
                    throwTextParseError(ss.str(), jsonVal.loc());
                }
            } else {
                if (!jsonVal.isObj()) {
                    throwTextParseError("Expecting a string or an object.", jsonVal.loc());
                }

                _objReq.validate(jsonVal);
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid clock origin:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonClkOrigValReq _objReq;
};

namespace {

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object numeric ID
 * object property requirement.
 */
JsonObjValReq::PropReqsEntry idPropReqEntry()
{
    return {strs::id, {JsonValReq::shared(JsonVal::Kind::UInt)}};
}

} // namespace

/*
 * CTF 2 clock type fragment value requirement.
 */
class JsonClkTypeFragValReq final :
    public JsonFragValReq
{
public:
    explicit JsonClkTypeFragValReq() :
        JsonFragValReq {this->typeStr(), {
            {strs::id, {JsonValReq::shared(JsonVal::Kind::Str), true}},
            nsPropReqEntry(),
            namePropReqEntry(false),
            uidPropReqEntry(false),
            {strs::freq, {JsonUIntValInRangeReq::shared(1, boost::none), true}},
            {strs::descr, {JsonValReq::shared(JsonVal::Kind::Str)}},
            {strs::orig, {JsonClkTypeOrigPropValReq::shared()}},
            {strs::offsetFromOrig, {JsonClkOffsetValReq::shared()}},
            {strs::prec, {JsonValReq::shared(JsonVal::Kind::UInt)}},
            {strs::accuracy, {JsonValReq::shared(JsonVal::Kind::UInt)}},
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonClkTypeFragValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::cc;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFragValReq::_validate(jsonVal);

            auto& jsonObjVal = jsonVal.asObj();

            if (const auto jsonOffsetFromOrigVal = jsonObjVal[strs::offsetFromOrig]) {
                if (const auto jsonCyclesVal = jsonOffsetFromOrigVal->asObj()[strs::cycles]) {
                    const auto cycles = *jsonCyclesVal->asUInt();
                    const auto freq = *jsonObjVal[strs::freq]->asUInt();

                    if (cycles >= freq) {
                        std::ostringstream ss;

                        ss << "Invalid `" << strs::cycles << "` property of " <<
                              "`" << strs::offsetFromOrig << "` property: " <<
                              "value " << cycles << " is greater than the value of the " <<
                              "`" << strs::freq << "` property (" << freq << ").";
                        throwTextParseError(ss.str(), jsonCyclesVal->loc());
                    }
                }
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid clock type fragment:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON trace environment value requirement.
 */
class JsonTraceEnvValReq final :
    public JsonObjValReq
{
public:
    explicit JsonTraceEnvValReq() :
        JsonObjValReq {{}, true}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonTraceEnvValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);

            // validate each entry
            for (auto& keyJsonValPair : jsonVal.asObj()) {
                auto& jsonEntryVal = *keyJsonValPair.second;

                try {
                    if (!jsonEntryVal.isUInt() && !jsonEntryVal.isSInt() && !jsonEntryVal.isStr()) {
                        throwTextParseError("Expecting an integer or a string.", jsonEntryVal.loc());
                    }

                    validateSIntUll(jsonEntryVal);
                } catch (TextParseError& exc) {
                    std::ostringstream ss;

                    ss << "Invalid trace environment entry `" << keyJsonValPair.first << "`:";
                    appendMsgToTextParseError(exc, ss.str(), jsonEntryVal.loc());
                    throw;
                }
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid trace environment:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 trace type fragment value requirement.
 */
class JsonTraceTypeFragValReq final :
    public JsonFragValReq
{
public:
    explicit JsonTraceTypeFragValReq() :
        JsonFragValReq {this->typeStr(), {
            nsPropReqEntry(),
            namePropReqEntry(false),
            uidPropReqEntry(false),
            anyDtPropReqEntry(strs::pktHeaderFc, _anyFullDtValReq), //-V1050
            {strs::env, {JsonTraceEnvValReq::shared()}},
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonTraceTypeFragValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::tc;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFragValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid trace type fragment:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonAnyFullDtValReq _anyFullDtValReq;
};

/*
 * CTF 2 data stream type fragment value requirement.
 */
class JsonDstFragValReq final :
    public JsonFragValReq
{
public:
    explicit JsonDstFragValReq() :
        JsonFragValReq {this->typeStr(), {
            nsPropReqEntry(),
            namePropReqEntry(false),
            uidPropReqEntry(false),
            idPropReqEntry(),
            {strs::defCcId, {JsonValReq::shared(JsonVal::Kind::Str)}},
            anyDtPropReqEntry(strs::pktCtxFc, _anyFullDtValReq), //-V1050
            anyDtPropReqEntry(strs::erHeaderFc, _anyFullDtValReq), //-V1050
            anyDtPropReqEntry(strs::erCommonCtxFc, _anyFullDtValReq), //-V1050
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonDstFragValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::dsc;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFragValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid data stream type fragment:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonAnyFullDtValReq _anyFullDtValReq;
};

/*
 * CTF 2 event record type fragment value requirement.
 */
class JsonErtFragValReq final :
    public JsonFragValReq
{
public:
    explicit JsonErtFragValReq() :
        JsonFragValReq {this->typeStr(), {
            nsPropReqEntry(),
            namePropReqEntry(false),
            uidPropReqEntry(false),
            idPropReqEntry(),
            {strs::dscId, {JsonValReq::shared(JsonVal::Kind::UInt)}},
            anyDtPropReqEntry(strs::specCtxFc, _anyFullDtValReq), //-V1050
            anyDtPropReqEntry(strs::payloadFc, _anyFullDtValReq), //-V1050
        }}
    {
    }

    static Sp shared()
    {
        return std::make_shared<JsonErtFragValReq>();
    }

    static const char *typeStr() noexcept
    {
        return strs::erc;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFragValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid event record type fragment:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonAnyFullDtValReq _anyFullDtValReq;
};

/*
 * CTF 2 JSON (any) fragment value requirement (implementation).
 */
class JsonAnyFragValReqImpl final :
    public JsonObjValReq
{
public:
    explicit JsonAnyFragValReqImpl() :
        JsonObjValReq {{
            {strs::type, {
                JsonStrValInSetReq::shared({
                    JsonPreFragValReq::typeStr(),
                    JsonDtAliasFragValReq::typeStr(),
                    JsonTraceTypeFragValReq::typeStr(),
                    JsonClkTypeFragValReq::typeStr(),
                    JsonDstFragValReq::typeStr(),
                    JsonErtFragValReq::typeStr(),
                }),
                true
            }},
        }, true}
    {
        this->_addToFragValReqs(_preFragValReq);
        this->_addToFragValReqs(_dtAliasFragValReq);
        this->_addToFragValReqs(_traceTypeFragValReq);
        this->_addToFragValReqs(_clkTypeFragValReq);
        this->_addToFragValReqs(_dstFragValReq);
        this->_addToFragValReqs(_ertFragValReq);
    }

    static Sp shared()
    {
        return std::make_shared<JsonAnyFragValReqImpl>();
    }

private:
    template <typename JsonValReqT>
    void _addToFragValReqs(const JsonValReqT& valReq)
    {
        const auto typeStr = JsonValReqT::typeStr();

        assert(_fragValReqs.find(typeStr) == _fragValReqs.end());
        _fragValReqs.insert(std::make_pair(typeStr, &valReq));
    }

    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fragment:", jsonVal.loc());
            throw;
        }

        /*
         * This part doesn't need to be catched because the specific
         * _validate() method already appends a message like
         * "Invalid xyz fragment:" to the exception.
         */
        const auto it = _fragValReqs.find(*jsonVal.asObj()[strs::type]->asStr());

        assert(it != _fragValReqs.end());
        it->second->validate(jsonVal);
    }

private:
    JsonPreFragValReq _preFragValReq;
    JsonDtAliasFragValReq _dtAliasFragValReq;
    JsonTraceTypeFragValReq _traceTypeFragValReq;
    JsonClkTypeFragValReq _clkTypeFragValReq;
    JsonDstFragValReq _dstFragValReq;
    JsonErtFragValReq _ertFragValReq;
    std::unordered_map<std::string, const JsonValReq *> _fragValReqs;
};

JsonAnyFragValReq::JsonAnyFragValReq() :
    _impl {new JsonAnyFragValReqImpl}
{
}

JsonAnyFragValReq::~JsonAnyFragValReq()
{
}

void JsonAnyFragValReq::_validate(const JsonVal& jsonVal) const
{
    _impl->validate(jsonVal);
}

} // namespace internal
} // namespace yactfr
