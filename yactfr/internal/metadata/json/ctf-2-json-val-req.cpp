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
class JsonBoValReq :
    public JsonStrValInSetReq
{
public:
    explicit JsonBoValReq() :
        JsonStrValInSetReq {JsonStrValInSetReq::Set {strs::BE, strs::LE}}
    {
    }

    static SP shared()
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
 * CTF 2 JSON UUID value requirement.
 */
class JsonUuidValReq :
    public JsonArrayValReq
{
public:
    explicit JsonUuidValReq() :
        JsonArrayValReq {16, JsonUIntValInRangeReq::shared(0, 255)}
    {
    }

    static SP shared()
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
class JsonDataLocValReq :
    public JsonArrayValReq
{
public:
    explicit JsonDataLocValReq() :
        JsonArrayValReq {2, boost::none, JsonValReq::shared(JsonVal::Kind::STR)},
        _scopeValReq {{
            strs::PKT_HEADER,
            strs::PKT_CTX,
            strs::ER_HEADER,
            strs::ER_COMMON_CTX,
            strs::ER_SPEC_CTX,
            strs::ER_PAYLOAD,
        }}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonDataLocValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonArrayValReq::_validate(jsonVal);

            auto& firstJsonItem = jsonVal.asArray()[0];

            try {
                _scopeValReq.validate(firstJsonItem);
            } catch (TextParseError& exc) {
                appendMsgToTextParseError(exc, "Invalid scope name:", firstJsonItem.loc());
                throw;
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid data location:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonStrValInSetReq _scopeValReq;
};

/*
 * CTF 2 JSON user attributes value requirement.
 */
class JsonUserAttrsValReq :
    public JsonObjValReq
{
public:
    explicit JsonUserAttrsValReq() :
        JsonObjValReq {{}, true}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonUserAttrsValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid user attributes:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON extensions value requirement.
 */
class JsonExtValReq :
    public JsonObjValReq
{
public:
    explicit JsonExtValReq() :
        JsonObjValReq {{}, true}
    {
    }

    static SP shared()
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
    static SP shared()
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
class JsonUIntValReq :
    public JsonValReq
{
public:
    explicit JsonUIntValReq() :
        JsonValReq {JsonVal::Kind::UINT}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonUIntValReq>();
    }
};

/*
 * JSON signed integer value (range) requirement.
 */
class JsonSIntValReq :
    public JsonIntValReq
{
public:
    static SP shared()
    {
        return std::make_shared<JsonSIntValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        JsonIntValReq::_validate(jsonVal);

        if (jsonVal.isSInt()) {
            return;
        }

        constexpr auto llMaxAsUll = static_cast<unsigned long long>(std::numeric_limits<long long>::max());

        if (*jsonVal.asUInt() > llMaxAsUll) {
            std::ostringstream ss;

            ss << "Expecting a signed integer: " << *jsonVal.asUInt() <<
                  " is greater than " << llMaxAsUll << '.';
            throwTextParseError(ss.str(), jsonVal.loc());
        }
    }
};

/*
 * CTF 2 JSON integer range value requirement.
 *
 * An instance of this class validates that a given JSON value is
 * a CTF 2 integer range, both contained values satisfying
 * an instance of `JsonIntValReqT`.
 */
template <typename JsonIntValReqT>
class JsonIntRangeValReqBase :
    public JsonArrayValReq
{
public:
    explicit JsonIntRangeValReqBase() :
        JsonArrayValReq {2, JsonIntValReqT::shared()}
    {
    }

    static SP shared()
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
class JsonIntRangeSetValReqBase :
    public JsonArrayValReq
{
public:
    explicit JsonIntRangeSetValReqBase() :
        JsonArrayValReq {1, boost::none, JsonIntRangeValReqBase<JsonIntValReqT>::shared()}
    {
    }

    static SP shared()
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
class JsonRolesValReq :
    public JsonArrayValReq
{
public:
    explicit JsonRolesValReq(JsonStrValInSetReq::Set validRoles) :
        JsonArrayValReq {JsonStrValInSetReq::shared(std::move(validRoles))}
    {
    }

    static SP shared(JsonStrValInSetReq::Set validRoles)
    {
        return std::make_shared<JsonRolesValReq>(std::move(validRoles));
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

/*
 * Adds a JSON object value property requirement having the key
 * `key` to `propReqs`, passing `valReq` and `isRequired` to its
 * constructor.
 */
static void addToPropReqs(JsonObjValReq::PropReqs& propReqs, std::string&& key,
                          JsonValReq::SP valReq, const bool isRequired = false)
{
    propReqs.emplace(std::make_pair(std::move(key),
                                    JsonObjValPropReq {std::move(valReq), isRequired}));
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object type object
 * property requirement.
 */
static JsonObjValReq::PropReqsEntry objTypePropReqEntry(std::string&& type)
{
    return {strs::TYPE, {JsonStrValInSetReq::shared(std::move(type)), true}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 user attributes
 * object property requirement.
 */
static JsonObjValReq::PropReqsEntry userAttrsPropReqEntry()
{
    return {strs::USER_ATTRS, {JsonUserAttrsValReq::shared()}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 extensions object
 * property requirement.
 */
static JsonObjValReq::PropReqsEntry extPropReqEntry()
{
    return {strs::EXT, {JsonExtValReq::shared()}};
}

/*
 * CTF 2 JSON data type value abstract requirement.
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
        propReqs.insert(userAttrsPropReqEntry());
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

    static SP shared()
    {
        return std::make_shared<JsonFlBitArrayTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::FL_BIT_ARRAY;
    }

private:
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
        addToPropReqs(propReqs, strs::LEN, JsonUIntValInRangeReq::shared(1, 64), true);
        addToPropReqs(propReqs, strs::BO, JsonBoValReq::shared(), true);
        addToPropReqs(propReqs, strs::ALIGN, JsonUIntValIsAlignReq::shared());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON fixed-length boolean type value requirement.
 */
class JsonFlBoolTypeValReq :
    public JsonFlBitArrayTypeValReq
{
public:
    explicit JsonFlBoolTypeValReq() :
        JsonFlBitArrayTypeValReq {this->typeStr()}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonFlBoolTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::FL_BOOL;
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

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 integer type
 * preferred display base object property requirement.
 */
static JsonObjValReq::PropReqsEntry intTypePrefDispBasePropReqEntry()
{
    return {strs::PREF_DISP_BASE, {JsonUIntValInSetReq::shared({2, 8, 10, 16})}};
}

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

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 unsigned integer
 * type roles object property requirement.
 */
static JsonObjValReq::PropReqsEntry uIntTypeRolesPropReqEntry(const JsonStrValInSetReq::Set& roles)
{
    return {strs::ROLES, {JsonRolesValReq::shared(roles)}};
}

/*
 * CTF 2 JSON fixed-length unsigned integer type value requirement.
 */
class JsonFlUIntTypeValReq :
    public JsonFlIntTypeValReq
{
protected:
    explicit JsonFlUIntTypeValReq(std::string&& type, const JsonStrValInSetReq::Set& roles,
                                  PropReqs&& propReqs = {}) :
        JsonFlIntTypeValReq {std::move(type), this->_buildPropReqs(roles, std::move(propReqs))}
    {
    }

public:
    explicit JsonFlUIntTypeValReq(const JsonStrValInSetReq::Set& roles) :
        JsonFlUIntTypeValReq {this->typeStr(), roles}
    {
    }

    static SP shared(const JsonStrValInSetReq::Set& roles)
    {
        return std::make_shared<JsonFlUIntTypeValReq>(roles);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::FL_UINT;
    }

private:
    static PropReqs _buildPropReqs(const JsonStrValInSetReq::Set& roles, PropReqs&& propReqs)
    {
        if (!roles.empty()) {
            propReqs.insert(uIntTypeRolesPropReqEntry(roles));
        }

        return std::move(propReqs);
    }

    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
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
class JsonFlSIntTypeValReq :
    public JsonFlIntTypeValReq
{
protected:
    explicit JsonFlSIntTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonFlIntTypeValReq {std::move(type), std::move(propReqs)}
    {
    }

public:
    explicit JsonFlSIntTypeValReq() :
        JsonFlIntTypeValReq {this->typeStr()}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonFlSIntTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::FL_SINT;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length signed integer type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON enumeration type mappings value requirement,
 *
 * An instance of this class validates that a given JSON value is
 * a CTF 2 enumeration type mappings object, each integer value within
 * the integer ranges satisfying an instance of `JsonIntValReqT`.
 */
template <typename JsonIntValReqT>
class JsonEnumTypeMappingsValReq :
    public JsonObjValReq
{
public:
    explicit JsonEnumTypeMappingsValReq() :
        JsonObjValReq {{}, true}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonEnumTypeMappingsValReq>();
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonObjValReq::_validate(jsonVal);

            if (jsonVal.asObj().size() < 1) {
                throwTextParseError("Expecting at least one mapping.", jsonVal.loc());
            }

            for (auto& keyJsonValPair : jsonVal.asObj()) {
                try {
                    _rangeSetReq.validate(*keyJsonValPair.second);
                } catch (TextParseError& exc) {
                    std::ostringstream ss;

                    ss << "In mapping `" << keyJsonValPair.first << "`:";
                    appendMsgToTextParseError(exc, ss.str(), jsonVal.loc());
                    throw;
                }
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid enumeration type mappings:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonIntRangeSetValReqBase<JsonIntValReqT> _rangeSetReq;
};

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 enumeration type
 * mappings object property requirement.
 */
template <typename JsonIntValReqT>
JsonObjValReq::PropReqsEntry enumTypeMappingsPropReqEntry()
{
    return {strs::MAPPINGS, {JsonEnumTypeMappingsValReq<JsonIntValReqT>::shared(), true}};
}

/*
 * CTF 2 JSON fixed-length unsigned enumeration type value requirement.
 */
class JsonFlUEnumTypeValReq :
    public JsonFlUIntTypeValReq
{
public:
    explicit JsonFlUEnumTypeValReq(const JsonStrValInSetReq::Set& roles) :
        JsonFlUIntTypeValReq {
            this->typeStr(), roles, {enumTypeMappingsPropReqEntry<JsonUIntValReq>()}
        }
    {
    }

    static SP shared(const JsonStrValInSetReq::Set& roles)
    {
        return std::make_shared<JsonFlUEnumTypeValReq>(roles);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::FL_UENUM;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length unsigned enumeration type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON fixed-length signed enumeration type value requirement.
 */
class JsonFlSEnumTypeValReq :
    public JsonFlSIntTypeValReq
{
public:
    explicit JsonFlSEnumTypeValReq() :
        JsonFlSIntTypeValReq {this->typeStr(), {enumTypeMappingsPropReqEntry<JsonSIntValReq>()}}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonFlSEnumTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::FL_SENUM;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid fixed-length signed enumeration type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON fixed-length floating-point number type value requirement.
 */
class JsonFlFloatTypeValReq :
    public JsonFlBitArrayTypeValReq
{
public:
    explicit JsonFlFloatTypeValReq() :
        JsonFlBitArrayTypeValReq {this->typeStr()}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonFlFloatTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::FL_FLOAT;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);

            auto& jsonLenVal = *jsonVal.asObj()[strs::LEN];
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
 * CTF 2 JSON variable-length bit array type value requirement.
 */
class JsonVlBitArrayTypeValReq :
    public JsonDtValReq
{
protected:
    explicit JsonVlBitArrayTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonDtValReq {std::move(type), std::move(propReqs)}
    {
    }

public:
    explicit JsonVlBitArrayTypeValReq() :
        JsonVlBitArrayTypeValReq {this->typeStr()}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonVlBitArrayTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::VL_BIT_ARRAY;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variable-length bit array type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON variable-length integer type value abstract requirement.
 */
class JsonVlIntTypeValReq :
    public JsonVlBitArrayTypeValReq
{
protected:
    explicit JsonVlIntTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonVlBitArrayTypeValReq {std::move(type), this->_buildPropReqs(std::move(propReqs))}
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
class JsonVlUIntTypeValReq :
    public JsonVlIntTypeValReq
{
protected:
    explicit JsonVlUIntTypeValReq(std::string&& type, const JsonStrValInSetReq::Set& roles,
                                  PropReqs&& propReqs = {}) :
        JsonVlIntTypeValReq {std::move(type), this->_buildPropReqs(roles, std::move(propReqs))}
    {
    }

public:
    explicit JsonVlUIntTypeValReq(const JsonStrValInSetReq::Set& roles) :
        JsonVlUIntTypeValReq {this->typeStr(), roles}
    {
    }

    static SP shared(const JsonStrValInSetReq::Set& roles)
    {
        return std::make_shared<JsonVlUIntTypeValReq>(roles);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::VL_UINT;
    }

private:
    static PropReqs _buildPropReqs(const JsonStrValInSetReq::Set& roles, PropReqs&& propReqs)
    {
        if (!roles.empty()) {
            propReqs.insert(uIntTypeRolesPropReqEntry(roles));
        }

        return std::move(propReqs);
    }

    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
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
class JsonVlSIntTypeValReq :
    public JsonVlIntTypeValReq
{
protected:
    explicit JsonVlSIntTypeValReq(std::string&& type, PropReqs&& propReqs = {}) :
        JsonVlIntTypeValReq {std::move(type), std::move(propReqs)}
    {
    }

public:
    explicit JsonVlSIntTypeValReq() :
        JsonVlSIntTypeValReq {this->typeStr()}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonVlSIntTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::VL_SINT;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variable-length signed integer type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON variable-length unsigned enumeration type value
 * requirement.
 */
class JsonVlUEnumTypeValReq :
    public JsonVlUIntTypeValReq
{
public:
    explicit JsonVlUEnumTypeValReq(const JsonStrValInSetReq::Set& roles) :
        JsonVlUIntTypeValReq {
            this->typeStr(), roles, {enumTypeMappingsPropReqEntry<JsonUIntValReq>()}
        }
    {
    }

    static SP shared(const JsonStrValInSetReq::Set& roles)
    {
        return std::make_shared<JsonVlUEnumTypeValReq>(roles);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::VL_UENUM;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variable-length unsigned enumeration type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON variable-length signed enumeration type value requirement.
 */
class JsonVlSEnumTypeValReq :
    public JsonVlSIntTypeValReq
{
public:
    explicit JsonVlSEnumTypeValReq() :
        JsonVlSIntTypeValReq {this->typeStr(), {enumTypeMappingsPropReqEntry<JsonSIntValReq>()}}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonVlSEnumTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::VL_SENUM;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variable-length signed enumeration type:",
                                      jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON null-terminated string type value requirement.
 */
class JsonNtStrTypeValReq :
    public JsonDtValReq
{
public:
    explicit JsonNtStrTypeValReq() :
        JsonDtValReq {this->typeStr()}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonNtStrTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::NT_STR;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid null-terminated string type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 static-length data
 * type length object property requirement.
 */
static JsonObjValReq::PropReqsEntry slDtLenPropReqEntry()
{
    return {strs::LEN, {JsonValReq::shared(JsonVal::Kind::UINT), true}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 dynamic-length data
 * type length location object property requirement.
 */
static JsonObjValReq::PropReqsEntry dlDtLenFieldLocPropReqEntry()
{
    return {strs::LEN_FIELD_LOC, {JsonDataLocValReq::shared(), true}};
}

/*
 * CTF 2 JSON static-length string type value requirement.
 */
class JsonSlStrTypeValReq :
    public JsonDtValReq
{
public:
    explicit JsonSlStrTypeValReq() :
        JsonDtValReq {this->typeStr(), {slDtLenPropReqEntry()}}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonSlStrTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::SL_STR;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid static-length string type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON dynamic-length string type value requirement.
 */
class JsonDlStrTypeValReq :
    public JsonDtValReq
{
public:
    explicit JsonDlStrTypeValReq() :
        JsonDtValReq {this->typeStr(), {dlDtLenFieldLocPropReqEntry()}}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonDlStrTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::DL_STR;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);
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
        addToPropReqs(propReqs, strs::MEDIA_TYPE, JsonValReq::shared(JsonVal::Kind::STR));
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON static-length BLOB type value requirement.
 */
class JsonSlBlobTypeValReq :
    public JsonBlobTypeValReq
{
public:
    explicit JsonSlBlobTypeValReq(const bool acceptTraceTypeUuidRole) :
        JsonBlobTypeValReq {this->typeStr(), this->_buildPropReqs(acceptTraceTypeUuidRole)}
    {
    }

    static SP shared(const bool acceptTraceTypeUuidRole)
    {
        return std::make_shared<JsonSlBlobTypeValReq>(acceptTraceTypeUuidRole);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::SL_BLOB;
    }

private:
    static PropReqs _buildPropReqs(const bool acceptTraceTypeUuidRole)
    {
        PropReqs propReqs;

        propReqs.insert(slDtLenPropReqEntry());

        if (acceptTraceTypeUuidRole) {
            propReqs.insert({
                strs::ROLES,
                JsonRolesValReq::shared({
                    strs::TC_UUID
                })
            });
        }

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
class JsonDlBlobTypeValReq :
    public JsonBlobTypeValReq
{
public:
    explicit JsonDlBlobTypeValReq() :
        JsonBlobTypeValReq {this->typeStr(), {dlDtLenFieldLocPropReqEntry()}}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonDlBlobTypeValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::DL_BLOB;
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

class JsonAnyDtValReq;

/*
 * CTF 2 data types are recursive, in that some data types may contain
 * other data types.
 *
 * To make it possible to build a `JsonAnyDtValReq` instance without a
 * shared pointer, the constructor of compound data type requirements
 * accepts a `const JsonAnyDtValReq *` (raw pointer) parameter. The raw
 * pointer must therefore remain valid as long as the compound data type
 * using it exists.
 *
 * Because JSON value requirements work with shared pointers to
 * `JsonValReq` (`JsonValReq::SP`), this `JsonAnyDtValReqWrapper` class
 * simply wraps such a `const JsonAnyDtValReq *` value: its _validate()
 * method forwards the call. A `JsonAnyDtValReqWrapper` instance doesn't
 * own the raw pointer.
 */
class JsonAnyDtValReqWrapper :
    public JsonValReq
{
public:
    explicit JsonAnyDtValReqWrapper(const JsonAnyDtValReq& anyDtValReq) :
        _anyDtValReq {&anyDtValReq}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonAnyDtValReqWrapper>(anyDtValReq);
    }

private:
    void _validate(const JsonVal& jsonVal) const override;

private:
    const JsonAnyDtValReq *_anyDtValReq;
};

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 data type object
 * property requirement having the key `key`.
 */
static JsonObjValReq::PropReqsEntry anyDtPropReqEntry(std::string&& key,
                                                      const JsonAnyDtValReq& anyDtValReq)
{
    return {std::move(key), {JsonAnyDtValReqWrapper::shared(anyDtValReq), true}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object name object
 * property requirement.
 */
static JsonObjValReq::PropReqsEntry namePropReqEntry(const bool isRequired)
{
    return {strs::NAME, {JsonValReq::shared(JsonVal::Kind::STR), isRequired}};
}

/*
 * CTF 2 JSON structure field member type value requirement.
 */
class JsonStructMemberTypeValReq :
    public JsonObjValReq
{
public:
    explicit JsonStructMemberTypeValReq(const JsonAnyDtValReq& anyDtValReq) :
        JsonObjValReq {{
            namePropReqEntry(true),
            anyDtPropReqEntry(strs::FC, anyDtValReq),
            userAttrsPropReqEntry(),
            extPropReqEntry(),
        }}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonStructMemberTypeValReq>(anyDtValReq);
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

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 minimum alignment
 * object property requirement.
 */
static JsonObjValReq::PropReqsEntry minAlignPropReqEntry()
{
    return {strs::MIN_ALIGN, JsonUIntValIsAlignReq::shared()};
}

static void validateUniqueEntryNames(const JsonVal& jsonVal, const char * const propName,
                                     const char * const what)
{
    const auto jsonEntries = jsonVal.asObj()[propName];

    if (!jsonEntries) {
        // empty
        return;
    }

    std::unordered_set<std::string> names;

    for (auto& jsonEntryVal : jsonEntries->asArray()) {
        const auto jsonNameVal = jsonEntryVal->asObj()[strs::NAME];

        if (!jsonNameVal) {
            continue;
        }

        auto& jsonNameStrVal = jsonNameVal->asStr();

        if (names.count(*jsonNameStrVal) != 0) {
            std::ostringstream ss;

            ss << "Duplicate " << what << " name `" << *jsonNameStrVal << "`.";
            throwTextParseError(ss.str(), jsonNameVal->loc());
        }

        names.insert(*jsonNameStrVal);
    }
}

/*
 * CTF 2 JSON structure type value requirement.
 */
class JsonStructTypeValReq :
    public JsonDtValReq
{
public:
    explicit JsonStructTypeValReq(const JsonAnyDtValReq& anyDtValReq) :
        JsonDtValReq {this->typeStr(), {
            {strs::MEMBER_CLSS, {
                JsonArrayValReq::shared(JsonStructMemberTypeValReq::shared(anyDtValReq))
            }},
            minAlignPropReqEntry(),
        }}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonStructTypeValReq>(anyDtValReq);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::STRUCT;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);

            // validate that member type names are unique
            validateUniqueEntryNames(jsonVal, strs::MEMBER_CLSS, "structure member type");
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
    explicit JsonArrayTypeValReq(std::string&& type, const JsonAnyDtValReq& anyDtValReq,
                                 PropReqs&& propReqs = {}) :
        JsonDtValReq {std::move(type), this->_buildPropReqs(anyDtValReq, std::move(propReqs))}
    {
    }

private:
    static PropReqs _buildPropReqs(const JsonAnyDtValReq& anyDtValReq, PropReqs&& propReqs)
    {
        propReqs.insert(anyDtPropReqEntry(strs::ELEM_FC, anyDtValReq));
        propReqs.insert(minAlignPropReqEntry());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 JSON static-length array type value requirement.
 */
class JsonSlArrayTypeValReq :
    public JsonArrayTypeValReq
{
public:
    explicit JsonSlArrayTypeValReq(const JsonAnyDtValReq& anyDtValReq) :
        JsonArrayTypeValReq {this->typeStr(), anyDtValReq, {slDtLenPropReqEntry()}}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonSlArrayTypeValReq>(anyDtValReq);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::SL_ARRAY;
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
class JsonDlArrayTypeValReq :
    public JsonArrayTypeValReq
{
public:
    explicit JsonDlArrayTypeValReq(const JsonAnyDtValReq& anyDtValReq) :
        JsonArrayTypeValReq {this->typeStr(), anyDtValReq, {dlDtLenFieldLocPropReqEntry()}}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonDlArrayTypeValReq>(anyDtValReq);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::DL_ARRAY;
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

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 selector location
 * object property requirement.
 */
static JsonObjValReq::PropReqsEntry selLocPropReqEntry()
{
    return {strs::SEL_FIELD_LOC, {JsonDataLocValReq::shared(), true}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 selector ranges
 * object property requirement.
 */
static JsonObjValReq::PropReqsEntry selRangesPropReqEntry(const bool isRequired)
{
    return {strs::SEL_FIELD_RANGES, {JsonIntRangeSetValReq::shared(), isRequired}};
}

/*
 * CTF 2 JSON optional type value requirement.
 */
class JsonOptTypeValReq :
    public JsonDtValReq
{
public:
    explicit JsonOptTypeValReq(const JsonAnyDtValReq& anyDtValReq) :
        JsonDtValReq {this->typeStr(), {
            anyDtPropReqEntry(strs::FC, anyDtValReq),
            selLocPropReqEntry(),
            selRangesPropReqEntry(false),
        }}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonOptTypeValReq>(anyDtValReq);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::OPT;
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
class JsonVarTypeOptValReq :
    public JsonObjValReq
{
public:
    explicit JsonVarTypeOptValReq(const JsonAnyDtValReq& anyDtValReq) :
        JsonObjValReq {{
            namePropReqEntry(false),
            anyDtPropReqEntry(strs::FC, anyDtValReq),
            selRangesPropReqEntry(true),
            userAttrsPropReqEntry(),
            extPropReqEntry(),
        }}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonVarTypeOptValReq>(anyDtValReq);
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
class JsonVarTypeValReq :
    public JsonDtValReq
{
public:
    explicit JsonVarTypeValReq(const JsonAnyDtValReq& anyDtValReq) :
        JsonDtValReq {this->typeStr(), {
            {strs::OPTS, {
                JsonArrayValReq::shared(1, boost::none, JsonVarTypeOptValReq::shared(anyDtValReq)),
                true
            }},
            selLocPropReqEntry(),
        }}
    {
    }

    static SP shared(const JsonAnyDtValReq& anyDtValReq)
    {
        return std::make_shared<JsonVarTypeValReq>(anyDtValReq);
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::VAR;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonDtValReq::_validate(jsonVal);

            // validate that option names are unique
            validateUniqueEntryNames(jsonVal, strs::OPTS, "variant type option");
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid variant type:", jsonVal.loc());
            throw;
        }
    }
};

/*
 * CTF 2 JSON (any) data type value requirement.
 */
class JsonAnyDtValReq :
    public JsonObjValReq
{
public:
    explicit JsonAnyDtValReq(const JsonStrValInSetReq::Set& uIntTypeRoles = {},
                             const bool slBlobHasTraceTypeUuidRole = false) :
        JsonObjValReq {{
            {strs::TYPE, {
                JsonStrValInSetReq::shared({
                    JsonFlBitArrayTypeValReq::typeStr(),
                    JsonFlBoolTypeValReq::typeStr(),
                    JsonFlUIntTypeValReq::typeStr(),
                    JsonFlSIntTypeValReq::typeStr(),
                    JsonFlUEnumTypeValReq::typeStr(),
                    JsonFlSEnumTypeValReq::typeStr(),
                    JsonFlFloatTypeValReq::typeStr(),
                    JsonVlBitArrayTypeValReq::typeStr(),
                    JsonVlUIntTypeValReq::typeStr(),
                    JsonVlSIntTypeValReq::typeStr(),
                    JsonVlUEnumTypeValReq::typeStr(),
                    JsonVlSEnumTypeValReq::typeStr(),
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
        _flUIntTypeValReq {uIntTypeRoles},
        _flUEnumTypeValReq {uIntTypeRoles},
        _vlUIntTypeValReq {uIntTypeRoles},
        _vlUEnumTypeValReq {uIntTypeRoles},
        _slBlobTypeValReq {slBlobHasTraceTypeUuidRole},
        _structTypeValReq {*this},
        _slArrayTypeValReq {*this},
        _dlArrayTypeValReq {*this},
        _optTypeValReq {*this},
        _varTypeValReq {*this}
    {
        this->_addToDtValReqs(_flBitArrayTypeValReq);
        this->_addToDtValReqs(_flBoolTypeValReq);
        this->_addToDtValReqs(_flUIntTypeValReq);
        this->_addToDtValReqs(_flSIntTypeValReq);
        this->_addToDtValReqs(_flUEnumTypeValReq);
        this->_addToDtValReqs(_flSEnumTypeValReq);
        this->_addToDtValReqs(_flFloatTypeValReq);
        this->_addToDtValReqs(_vlBitArrayTypeValReq);
        this->_addToDtValReqs(_vlUIntTypeValReq);
        this->_addToDtValReqs(_vlSIntTypeValReq);
        this->_addToDtValReqs(_vlUEnumTypeValReq);
        this->_addToDtValReqs(_vlSEnumTypeValReq);
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

    static SP shared()
    {
        return std::make_shared<JsonAnyDtValReq>();
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
            appendMsgToTextParseError(exc, "Invalid type:", jsonVal.loc());
            throw;
        }

        /*
         * This part doesn't need to be catched because the specific
         * _validate() method already appends a message like
         * "Invalid xyz type:" to the exception.
         */
        const auto it = _dtValReqs.find(*jsonVal.asObj()[strs::TYPE]->asStr());

        assert(it != _dtValReqs.end());
        it->second->validate(jsonVal);
    }

private:
    JsonFlBitArrayTypeValReq _flBitArrayTypeValReq;
    JsonFlBoolTypeValReq _flBoolTypeValReq;
    JsonFlUIntTypeValReq _flUIntTypeValReq;
    JsonFlSIntTypeValReq _flSIntTypeValReq;
    JsonFlUEnumTypeValReq _flUEnumTypeValReq;
    JsonFlSEnumTypeValReq _flSEnumTypeValReq;
    JsonFlFloatTypeValReq _flFloatTypeValReq;
    JsonVlBitArrayTypeValReq _vlBitArrayTypeValReq;
    JsonVlUIntTypeValReq _vlUIntTypeValReq;
    JsonVlSIntTypeValReq _vlSIntTypeValReq;
    JsonVlUEnumTypeValReq _vlUEnumTypeValReq;
    JsonVlSEnumTypeValReq _vlSEnumTypeValReq;
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
    // delegate
    _anyDtValReq->validate(jsonVal);
}

/*
 * CTF 2 JSON scope data type value requirement.
 *
 * This is like `JsonStructTypeValReq`, but provides its own
 * `JsonAnyDtValReq` instance.
 */
class JsonScopeTypeValReq :
    public JsonValReq
{
public:
    /*
     * `uIntTypeRoles` and `slBlobHasTraceTypeUuidRole` are forwarded to
     * the constructor of the underlying `JsonAnyDtValReq` instance.
     */
    explicit JsonScopeTypeValReq(const JsonStrValInSetReq::Set& uIntTypeRoles = {},
                                 const bool slBlobHasTraceTypeUuidRole = false) :
        _anyDtValReq {uIntTypeRoles, slBlobHasTraceTypeUuidRole},
        _structTypeValReq {_anyDtValReq}
    {
    }

    static SP shared(const JsonStrValInSetReq::Set& uIntTypeRoles = {},
                     const bool slBlobHasTraceTypeUuidRole = false)
    {
        return std::make_shared<JsonScopeTypeValReq>(uIntTypeRoles, slBlobHasTraceTypeUuidRole);
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            _structTypeValReq.validate(jsonVal);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "Invalid scope type:", jsonVal.loc());
            throw;
        }
    }

private:
    JsonAnyDtValReq _anyDtValReq;
    JsonStructTypeValReq _structTypeValReq;
};

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
        propReqs.insert(userAttrsPropReqEntry());
        propReqs.insert(extPropReqEntry());
        return std::move(propReqs);
    }
};

/*
 * CTF 2 preamble fragment value requirement.
 */
class JsonPreFragValReq :
    public JsonFragValReq
{
public:
    explicit JsonPreFragValReq() :
        JsonFragValReq {this->typeStr(), {
            {strs::VERSION, {JsonUIntValInSetReq::shared(2), true}},
        }}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonPreFragValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::PRE;
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
 * CTF 2 JSON clock offset value requirement.
 */
class JsonClkOffsetValReq :
    public JsonObjValReq
{
public:
    explicit JsonClkOffsetValReq() :
        JsonObjValReq {{
            {strs::SECS, {JsonSIntValReq::shared()}},
            {strs::CYCLES, {JsonValReq::shared(JsonVal::Kind::UINT)}},
        }}
    {
    }

    static SP shared()
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

/*
 * CTF 2 clock type fragment value requirement.
 */
class JsonClkTypeFragValReq :
    public JsonFragValReq
{
public:
    explicit JsonClkTypeFragValReq() :
        JsonFragValReq {this->typeStr(), {
            namePropReqEntry(true),
            {strs::FREQ, {JsonUIntValInRangeReq::shared(1, boost::none), true}},
            {strs::DESCR, {JsonValReq::shared(JsonVal::Kind::STR)}},
            {strs::UUID, {JsonUuidValReq::shared()}},
            {strs::ORIG_IS_UNIX_EPOCH, {JsonValReq::shared(JsonVal::Kind::BOOL)}},
            {strs::OFFSET, {JsonClkOffsetValReq::shared()}},
            {strs::PREC, {JsonValReq::shared(JsonVal::Kind::UINT)}},
        }}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonClkTypeFragValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::CC;
    }

private:
    void _validate(const JsonVal& jsonVal) const override
    {
        try {
            JsonFragValReq::_validate(jsonVal);

            auto& jsonObjVal = jsonVal.asObj();
            const auto jsonOffsetVal = jsonObjVal[strs::OFFSET];

            if (jsonOffsetVal) {
                const auto jsonCyclesVal = jsonOffsetVal->asObj()[strs::CYCLES];

                if (jsonCyclesVal) {
                    const auto cycles = *jsonCyclesVal->asUInt();
                    const auto freq = *jsonObjVal[strs::FREQ]->asUInt();

                    if (cycles >= freq) {
                        std::ostringstream ss;

                        ss << "Invalid `" << strs::CYCLES << "` property of " <<
                              "`" << strs::OFFSET << "` property: " <<
                              "value " << cycles << " is greater than the value of the " <<
                              "`" << strs::FREQ << "` property (" << freq << ").";
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
 * CTF 2 trace type fragment value requirement.
 */
class JsonTraceTypeFragValReq :
    public JsonFragValReq
{
public:
    explicit JsonTraceTypeFragValReq() :
        JsonFragValReq {this->typeStr(), {
            {strs::UUID, {JsonUuidValReq::shared()}},
            {strs::PKT_HEADER_FC, {JsonScopeTypeValReq::shared({
                strs::DSC_ID,
                strs::DS_ID,
                strs::PKT_MAGIC_NUMBER,
            }, true)}},
        }}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonTraceTypeFragValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::TC;
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
};

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object namespace
 * object property requirement.
 */
static JsonObjValReq::PropReqsEntry nsPropReqEntry()
{
    return {strs::NS, {JsonValReq::shared(JsonVal::Kind::STR)}};
}

/*
 * Returns the pair (suitable for insertion into a
 * `JsonObjValReq::PropReqs` instance) for the CTF 2 object numeric ID
 * object property requirement.
 */
static JsonObjValReq::PropReqsEntry idPropReqEntry()
{
    return {strs::ID, {JsonValReq::shared(JsonVal::Kind::UINT)}};
}

/*
 * CTF 2 data stream type fragment value requirement.
 */
class JsonDstFragValReq :
    public JsonFragValReq
{
public:
    explicit JsonDstFragValReq() :
        JsonFragValReq {this->typeStr(), {
            namePropReqEntry(false),
            nsPropReqEntry(),
            idPropReqEntry(),
            {strs::DEF_CC_NAME, {JsonValReq::shared(JsonVal::Kind::STR)}},
            {strs::PKT_CTX_FC, {JsonScopeTypeValReq::shared({
                strs::DEF_CLK_TS,
                strs::DISC_ER_COUNTER_SNAP,
                strs::PKT_CONTENT_LEN,
                strs::PKT_TOTAL_LEN,
                strs::PKT_END_DEF_CLK_TS,
                strs::PKT_SEQ_NUM,
                strs::PKT_TOTAL_LEN,
            })}},
            {strs::ER_HEADER_FC, {JsonScopeTypeValReq::shared({
                strs::DEF_CLK_TS,
                strs::ERC_ID,
            })}},
            {strs::ER_COMMON_CTX_FC, {JsonScopeTypeValReq::shared()}},
        }}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonDstFragValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::DSC;
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
};

/*
 * CTF 2 event record type fragment value requirement.
 */
class JsonErtFragValReq :
    public JsonFragValReq
{
public:
    explicit JsonErtFragValReq() :
        JsonFragValReq {this->typeStr(), {
            namePropReqEntry(false),
            nsPropReqEntry(),
            idPropReqEntry(),
            {strs::DSC_ID, {JsonValReq::shared(JsonVal::Kind::UINT)}},
            {strs::SPEC_CTX_FC, {JsonScopeTypeValReq::shared()}},
            {strs::PAYLOAD_FC, {JsonScopeTypeValReq::shared()}},
        }}
    {
    }

    static SP shared()
    {
        return std::make_shared<JsonErtFragValReq>();
    }

    static constexpr const char *typeStr() noexcept
    {
        return strs::ERC;
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
};

/*
 * CTF 2 JSON (any) fragment value requirement (implementation).
 */
class JsonAnyFragValReqImpl :
    public JsonObjValReq
{
public:
    explicit JsonAnyFragValReqImpl() :
        JsonObjValReq {{
            {strs::TYPE, {
                JsonStrValInSetReq::shared({
                    JsonPreFragValReq::typeStr(),
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
        this->_addToFragValReqs(_traceClsFragValReq);
        this->_addToFragValReqs(_clkClsFragValReq);
        this->_addToFragValReqs(_dsClsFragValReq);
        this->_addToFragValReqs(_erClsFragValReq);
    }

    static SP shared()
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
        const auto it = _fragValReqs.find(*jsonVal.asObj()[strs::TYPE]->asStr());

        assert(it != _fragValReqs.end());
        it->second->validate(jsonVal);
    }

private:
    JsonPreFragValReq _preFragValReq;
    JsonTraceTypeFragValReq _traceClsFragValReq;
    JsonClkTypeFragValReq _clkClsFragValReq;
    JsonDstFragValReq _dsClsFragValReq;
    JsonErtFragValReq _erClsFragValReq;
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