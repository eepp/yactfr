/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_REQ_HPP
#define _YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_REQ_HPP

#include <cassert>
#include <string>
#include <memory>
#include <regex>
#include <unordered_map>
#include <set>
#include <limits>
#include <sstream>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include <yactfr/text-parse-error.hpp>

#include "json-val.hpp"

namespace yactfr {
namespace internal {

/*
 * JSON value requirement.
 *
 * This is the base of any JSON requirement class.
 *
 * An instance of this class validates that a JSON value has a given
 * type.
 */
class JsonValReq :
    boost::noncopyable
{
public:
    // shared pointer to constant JSON value requirement
    using SP = std::shared_ptr<const JsonValReq>;

public:
    /*
     * Builds a JSON value requirement: if `kind` is set, then
     * validate() validates that the kind of the JSON value is `*kind`.
     */
    explicit JsonValReq(boost::optional<JsonVal::Kind> kind = boost::none);

    virtual ~JsonValReq() = default;

    /*
     * Validates that `jsonVal` satisfies this requirement.
     */
    void validate(const JsonVal& jsonVal) const;

    /*
     * Returns a shared pointer to JSON value requirement, forwarding
     * the parameter to the constructor.
     */
    static SP shared(boost::optional<JsonVal::Kind> kind);

protected:
    /*
     * Requirement-specific validation.
     */
    virtual void _validate(const JsonVal& jsonVal) const;

private:
    // required JSON value kind
    boost::optional<JsonVal::Kind> _kind;
};

/*
 * JSON integer value in range requirement template.
 *
 * An instance of this class validates that, given a JSON value V of
 * type `JsonValT`:
 *
 * * V has the kind `KindV`.
 * * The raw value of V is within a given range.
 */
template <typename JsonValT, JsonVal::Kind KindV>
class JsonIntValInRangeReq :
    public JsonValReq
{
private:
    // raw value type
    using _Val = typename JsonValT::Val;

public:
    /*
     * Builds a JSON integer value in range requirement: _validate()
     * validates that the raw value of the JSON integer value is:
     *
     * * If `minVal` is set: greater than or equal to `*minVal`.
     * * If `maxVal` is set: less than or equal to `*maxVal`.
     */
    explicit JsonIntValInRangeReq(const boost::optional<_Val>& minVal,
                                  const boost::optional<_Val>& maxVal) :
        JsonValReq {KindV},
        _minVal {minVal ? *minVal : std::numeric_limits<_Val>::min()},
        _maxVal {maxVal ? *maxVal : std::numeric_limits<_Val>::max()}
    {
    }

    /*
     * Builds a JSON integer value in range requirement: _validate()
     * validates that the raw value of the JSON integer value is exactly
     * `exactVal`.
     */
    explicit JsonIntValInRangeReq(const _Val exactVal) :
        JsonIntValInRangeReq {exactVal, exactVal}
    {
    }

    /*
     * Returns a shared pointer to JSON integer value in range
     * requirement, forwarding the parameters to the constructor.
     */
    static SP shared(const boost::optional<_Val>& minVal, const boost::optional<_Val>& maxVal)
    {
        return std::make_shared<JsonIntValInRangeReq>(minVal, maxVal);
    }

    /*
     * Returns a shared pointer to JSON integer value in range
     * requirement, forwarding the parameter to the constructor.
     */
    static SP shared(const _Val exactVal)
    {
        return std::make_shared<JsonIntValInRangeReq>(exactVal);
    }

protected:
    void _validate(const JsonVal& jsonVal) const override
    {
        auto& jsonIntVal = static_cast<const JsonValT&>(jsonVal);

        if (*jsonIntVal < _minVal) {
            std::ostringstream ss;

            ss << "Integer " << *jsonIntVal << " is too small: " <<
                  "expecting at least " << _minVal << ".";
            throwTextParseError(ss.str(), jsonVal.loc());
        }

        if (*jsonIntVal > _maxVal) {
            std::ostringstream ss;

            ss << "Integer " << *jsonIntVal << " is too large: " <<
                  "expecting at most " << _maxVal << ".";
            throwTextParseError(ss.str(), jsonVal.loc());
        }
    }

private:
    // minimum raw value
    _Val _minVal;

    // maximum raw value
    _Val _maxVal;
};

/*
 * JSON unsigned integer value in range requirement.
 */
using JsonUIntValInRangeReq = JsonIntValInRangeReq<JsonUIntVal, JsonVal::Kind::UINT>;

/*
 * JSON signed integer value in range requirement.
 */
using JsonSIntValInRangeReq = JsonIntValInRangeReq<JsonSIntVal, JsonVal::Kind::SINT>;

template <typename ValT>
void writeRawVal(std::ostringstream& ss, const ValT& val)
{
    ss << val;
}

template <>
inline void writeRawVal<std::string>(std::ostringstream& ss, const std::string& val)
{
    ss << '`' << val << '`';
}

template <>
inline void writeRawVal<bool>(std::ostringstream& ss, const bool& val)
{
    writeRawVal(ss, std::string {val ? "true" : "false"});
}

/*
 * JSON scalar value in set requirement template.
 *
 * An instance of this class validates that, given a JSON value V of
 * type `JsonValT`:
 *
 * * V has the kind `KindV`.
 * * The raw value of V is an element of a given set.
 */
template <typename JsonValT, JsonVal::Kind KindV>
class JsonScalarValInSetReq :
    public JsonValReq
{
private:
    // raw value type
    using _Val = typename JsonValT::Val;

public:
    // raw value set type
    using Set = std::set<_Val>;

public:
    /*
     * Builds a JSON scalar value set requirement: _validate() validates
     * that the raw value of the JSON scalar value is an element of
     * `set`.
     */
    explicit JsonScalarValInSetReq(Set set) :
        JsonValReq {KindV},
        _set {std::move(set)}
    {
    }

    /*
     * Builds a JSON scalar value set requirement: _validate() validates
     * that the raw value of the JSON scalar value is exactly `val`.
     */
    explicit JsonScalarValInSetReq(_Val val) :
        JsonScalarValInSetReq {Set {std::move(val)}}
    {
    }

    /*
     * Returns a shared pointer to JSON scalar value in set requirement,
     * forwarding the parameter to the constructor.
     */
    static SP shared(Set set)
    {
        return std::make_shared<JsonScalarValInSetReq>(std::move(set));
    }

    /*
     * Returns a shared pointer to JSON scalar value in set requirement,
     * forwarding the parameter to the constructor.
     */
    static SP shared(_Val val)
    {
        return std::make_shared<JsonScalarValInSetReq>(std::move(val));
    }

protected:
    void _validate(const JsonVal& jsonVal) const override
    {
        auto& specJsonVal = static_cast<const JsonValT&>(jsonVal);

        if (_set.find(*specJsonVal) == _set.end()) {
            std::ostringstream ss;

            ss << "Unexpected value ";
            writeRawVal(ss, *specJsonVal);
            ss << ": expecting " << this->_setStr() << '.';
            throwTextParseError(ss.str(), jsonVal.loc());
        }
    }

    /*
     * Serializes the raw values of `_set` and returns the resulting
     * string.
     */
    std::string _setStr() const
    {
        std::ostringstream ss;

        if (_set.size() == 1) {
            // special case: direct value
            writeRawVal(ss, *_set.begin());
            return ss.str();
        } else if (_set.size() == 2) {
            // special case: "or" word without any comma
            writeRawVal(ss, *_set.begin());
            ss << " or ";
            writeRawVal(ss, *std::next(_set.begin()));
            return ss.str();
        }

        // enumeration with at least one comma
        const auto lastIt = std::prev(_set.end());

        for (auto it = _set.begin(); it != lastIt; ++it) {
            writeRawVal(ss, *it);
            ss << ", ";
        }

        ss << "or ";
        writeRawVal(ss, *lastIt);
        return ss.str();
    }

private:
    // set of expected raw values
    Set _set;
};

/*
 * JSON boolean value in set requirement template.
 */
using JsonBoolValInSetReq = JsonScalarValInSetReq<JsonBoolVal, JsonVal::Kind::BOOL>;

/*
 * JSON unsigned integer value in set requirement template.
 */
using JsonUIntValInSetReq = JsonScalarValInSetReq<JsonUIntVal, JsonVal::Kind::UINT>;

/*
 * JSON signed integer value in set requirement template.
 */
using JsonSIntValInSetReq = JsonScalarValInSetReq<JsonSIntVal, JsonVal::Kind::SINT>;

/*
 * JSON string value in set requirement template.
 */
using JsonStrValInSetReq = JsonScalarValInSetReq<JsonStrVal, JsonVal::Kind::STR>;

/*
 * JSON unsigned integer value is alignment requirement.
 *
 * An instance of this class validates that, given a JSON value V:
 *
 * * V is a JSON unsigned integer value.
 *
 * * The raw value of V is a valid alignment (greater than zero, power
 *   of two).
 */
class JsonUIntValIsAlignReq :
    public JsonValReq
{
public:
    /*
     * Builds a JSON unsigned integer value alignment requirement:
     * _validate() validates that the raw value of the JSON unsigned
     * integer value is a valid alignment.
     */
    explicit JsonUIntValIsAlignReq();

    /*
     * Returns a shared pointer to JSON unsigned integer value alignment
     * requirement.
     */
    static SP shared();

protected:
    void _validate(const JsonVal& jsonVal) const override;
};

/*
 * JSON string value matches regular expression requirement.
 *
 * An instance of this class validates that, given a JSON value V:
 *
 * * V is a JSON string value.
 * * The raw value of V matches a given regular expression.
 */
class JsonStrValMatchesRegexReq :
    public JsonValReq
{
public:
    /*
     * Builds a JSON string value matches regular expression
     * requirement: _validate() validates that the raw value of the JSON
     * string value matches the regular expression `regex`.
     */
    explicit JsonStrValMatchesRegexReq(std::regex regex);

    /*
     * Builds a JSON string value matches regular expression
     * requirement: _validate() validates that the raw value of the JSON
     * string value matches the regular expression `regex` (ECMAScript
     * engine).
     */
    explicit JsonStrValMatchesRegexReq(const char *regex);

    /*
     * Returns a shared pointer to JSON string value matches regular
     * expression requirement, forwarding the parameter to the
     * constructor.
     */
    static SP shared(std::regex regex);

    /*
     * Returns a shared pointer to JSON string value matches regular
     * expression requirement, forwarding the parameter to the
     * constructor.
     */
    static SP shared(const char *regex);

protected:
    void _validate(const JsonVal& jsonVal) const override;

private:
    std::regex _regex;
};

/*
 * JSON array value requirement.
 *
 * An instance of this class validates that, given a JSON value V:
 *
 * * V is a JSON array value.
 * * The size of V is within a given range.
 * * All the elements of V satisfy a given JSON value requirement.
 */
class JsonArrayValReq :
    public JsonValReq
{
public:
    /*
     * Builds a JSON array value requirement: _validate() validates
     * that, for a given JSON array value V:
     *
     * * If `minSize` is set: the size of V is greater than or equal to
     *   `*minSize`.
     *
     * * If `maxSize` is set: the size of V is less than or equal to
     *   `*maxSize`.
     *
     * * If `elemValReq` is not `nullptr`: all the elements of V satisfy
     *   `*elemValReq`.
     */
    explicit JsonArrayValReq(const boost::optional<Size>& minSize,
                             const boost::optional<Size>& maxSize,
                             JsonValReq::SP elemValReq = nullptr);

    /*
     * Builds a JSON array value requirement: _validate() validates
     * that, for a given JSON array value V:
     *
     * * The size of V is exactly `exactSize`.
     *
     * * If `elemValReq` is not `nullptr`: all the elements of V satisfy
     *   `*elemValReq`.
     */
    explicit JsonArrayValReq(Size exactSize, JsonValReq::SP elemValReq = nullptr);

    /*
     * Builds a JSON array value requirement: _validate() validates
     * that, if `elemValReq` is not `nullptr`, all the elements of a
     * given JSON array value satisfy `*elemValReq`.
     */
    explicit JsonArrayValReq(JsonValReq::SP elemValReq = nullptr);

    /*
     * Returns a shared pointer to JSON array value requirement,
     * forwarding the parameters to the constructor.
     */
    static SP shared(const boost::optional<Size>& minSize, const boost::optional<Size>& maxSize,
                     JsonValReq::SP elemValReq = nullptr);

    /*
     * Returns a shared pointer to JSON array value requirement,
     * forwarding the parameters to the constructor.
     */
    static SP shared(Size exactSize, JsonValReq::SP elemValReq = nullptr);

    /*
     * Returns a shared pointer to JSON array value requirement,
     * forwarding the parameter to the constructor.
     */
    static SP shared(JsonValReq::SP elemValReq = nullptr);

protected:
    void _validate(const JsonVal& jsonVal) const override;

private:
    Size _minSize;
    Size _maxSize;
    JsonValReq::SP _elemValReq;
};

/*
 * JSON object value property requirement.
 *
 * An instance of this class contains the requirements of a single
 * JSON object value property, that is:
 *
 * * Whether or not it's required.
 * * The requirement of the JSON value of the property.
 */
class JsonObjValPropReq final
{
public:
    /*
     * Builds a JSON object value property requirement, required if
     * `isRequired` is true: if `valReq` is set, then validate()
     * validates that a JSON value satisfies `*valReq`.
     *
     * Not `explicit` to make building `JsonObjValReq` lighter.
     */
    JsonObjValPropReq(JsonValReq::SP valReq = nullptr, bool isRequired = false);

    // default copy/move operations
    JsonObjValPropReq(const JsonObjValPropReq&) = default;
    JsonObjValPropReq(JsonObjValPropReq&&) = default;
    JsonObjValPropReq& operator=(const JsonObjValPropReq&) = default;
    JsonObjValPropReq& operator=(JsonObjValPropReq&&) = default;

    /*
     * Whether or not the property is required.
     */
    bool isRequired() const noexcept
    {
        return _isRequired;
    }

    /*
     * Validates that `jsonVal` satisfies this requirement.
     */
    void validate(const JsonVal& jsonVal) const;

private:
    // whether or not this property is required
    bool _isRequired = false;

    // requirement of the JSON value
    JsonValReq::SP _valReq;
};

/*
 * JSON object value requirement.
 *
 * An instance of this class validates that, given a JSON value V:
 *
 * * V is a JSON object value.
 *
 * * The properties of V satisfy a given set of JSON object value
 *   property requirements.
 */
class JsonObjValReq :
    public JsonValReq
{
public:
    // property name to property requirement mapping
    using PropReqs = std::unordered_map<std::string, JsonObjValPropReq>;

    // single entry (pair) of `PropReqs`
    using PropReqsEntry = PropReqs::value_type;

public:
    /*
     * Builds a JSON object value requirement: _validate() validates
     * that, for a given JSON object value V:
     *
     * * If `allowUnknownProps` is false, then V has no value of which
     *   the key is not an element of the keys of `propReqs`.
     *
     * * For each property requirement PR having the key K in
     *   `propReqs`: if `PR.isRequired()`, then a value having the key K
     *   exists in V.
     *
     * * For each value VV having the key K in V: VV satisfies the JSON
     *   value requirement, if any, of `propReqs[K]`.
     */
    explicit JsonObjValReq(PropReqs propReqs, bool allowUnknownProps = false);

    /*
     * Returns a shared pointer to JSON object value requirement,
     * forwarding the parameters to the constructor.
     */
    static SP shared(PropReqs propReqs, bool allowUnknownProps = false);

protected:
    void _validate(const JsonVal& jsonVal) const override;

private:
    PropReqs _propReqs;
    bool _allowUnknownProps;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_JSON_JSON_VAL_REQ_HPP
