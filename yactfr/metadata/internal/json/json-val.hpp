/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_JSON_JSON_VAL_HPP
#define _YACTFR_METADATA_INTERNAL_JSON_JSON_VAL_HPP

#include <cassert>
#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/text-loc.hpp>
#include <yactfr/internal/item-mixin.hpp>

namespace yactfr {
namespace internal {

enum class JsonValKind
{
    NUL,
    BOOL,
    SINT,
    UINT,
    REAL,
    STR,
    ARRAY,
    OBJ,
};

class JsonNullVal;

template <typename, JsonValKind>
class JsonScalarVal;

using JsonBoolVal = JsonScalarVal<bool, JsonValKind::BOOL>;
using JsonSIntVal = JsonScalarVal<long long, JsonValKind::SINT>;
using JsonUIntVal = JsonScalarVal<unsigned long long, JsonValKind::UINT>;
using JsonRealVal = JsonScalarVal<double, JsonValKind::REAL>;
using JsonStrVal = JsonScalarVal<std::string, JsonValKind::STR>;

class JsonArrayVal;
class JsonObjVal;
class JsonValVisitor;

/*
 * Visitor of JSON value.
 */
class JsonValVisitor
{
protected:
    explicit JsonValVisitor() = default;

public:
    virtual void visit(const JsonNullVal&)
    {
    }

    virtual void visit(const JsonBoolVal&)
    {
    }

    virtual void visit(const JsonSIntVal&)
    {
    }

    virtual void visit(const JsonUIntVal&)
    {
    }

    virtual void visit(const JsonRealVal&)
    {
    }

    virtual void visit(const JsonStrVal&)
    {
    }

    virtual void visit(const JsonArrayVal&)
    {
    }

    virtual void visit(const JsonObjVal&)
    {
    }
};

class JsonVal :
    public ItemMixin<JsonValKind>,
    boost::noncopyable
{
public:
    using UP = std::unique_ptr<const JsonVal>;
    using Kind = JsonValKind;

protected:
    explicit JsonVal(Kind kind, TextLocation&& loc);

public:
    virtual ~JsonVal() = default;

    Kind kind() const noexcept
    {
        return ItemMixin<JsonValKind>::_kind();
    }

    const TextLocation& loc() const noexcept
    {
        return _loc;
    }

    bool isNull() const noexcept
    {
        return this->kind() == Kind::NUL;
    }

    bool isBool() const noexcept
    {
        return this->kind() == Kind::BOOL;
    }

    bool isSInt() const noexcept
    {
        return this->kind() == Kind::SINT;
    }

    bool isUInt() const noexcept
    {
        return this->kind() == Kind::UINT;
    }

    bool isReal() const noexcept
    {
        return this->kind() == Kind::REAL;
    }

    bool isStr() const noexcept
    {
        return this->kind() == Kind::STR;
    }

    bool isArray() const noexcept
    {
        return this->kind() == Kind::ARRAY;
    }

    bool isObj() const noexcept
    {
        return this->kind() == Kind::OBJ;
    }

    const JsonNullVal& asNull() const noexcept;
    const JsonBoolVal& asBool() const noexcept;
    const JsonSIntVal& asSInt() const noexcept;
    const JsonUIntVal& asUInt() const noexcept;
    const JsonRealVal& asReal() const noexcept;
    const JsonStrVal& asStr() const noexcept;
    const JsonArrayVal& asArray() const noexcept;
    const JsonObjVal& asObj() const noexcept;
    UP clone() const;
    void accept(JsonValVisitor& visitor) const;
    bool operator==(const JsonVal& other) const noexcept;

    bool operator!=(const JsonVal& other) const noexcept
    {
        return !(other == *this);
    }

private:
    virtual UP _clone() const = 0;
    virtual void _accept(JsonValVisitor& visitor) const = 0;
    virtual bool _isEqual(const JsonVal& other) const noexcept = 0;

private:
    TextLocation _loc;
};

class JsonNullVal final :
    public JsonVal
{
public:
    using UP = std::unique_ptr<const JsonNullVal>;

public:
    explicit JsonNullVal(TextLocation loc);

private:
    JsonVal::UP _clone() const override;
    void _accept(JsonValVisitor& visitor) const override;
    bool _isEqual(const JsonVal& other) const noexcept override;
};

template <typename ValT, JsonVal::Kind KindV>
class JsonScalarVal final :
    public JsonVal,
    public ScalarValItemMixin<ValT>
{
public:
    using Val = ValT;
    using UP = std::unique_ptr<const JsonScalarVal<ValT, KindV>>;

public:
    explicit JsonScalarVal(ValT val, TextLocation loc) :
        JsonVal {KindV, std::move(loc)},
        ScalarValItemMixin<ValT> {std::move(val)}
    {
    }

    const ValT& val() const noexcept
    {
        return this->_val();
    }

    const ValT& operator*() const noexcept
    {
        return this->_val();
    }

private:
    JsonVal::UP _clone() const override
    {
        return std::make_unique<const JsonScalarVal<ValT, KindV>>(this->_val(), this->loc());
    }

    void _accept(JsonValVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _isEqual(const JsonVal& other) const noexcept override
    {
        return ScalarValItemMixin<ValT>::_isEqual(static_cast<const JsonScalarVal<ValT, KindV>&>(other));
    }
};

class JsonArrayVal final :
    public JsonVal,
    public ArrayItemMixin<JsonVal>
{
public:
    using Container = _Container;
    using UP = std::unique_ptr<const JsonArrayVal>;

public:
    explicit JsonArrayVal(Container&& items, TextLocation loc);

    typename Container::const_iterator begin() const noexcept
    {
        return this->_begin();
    }

    typename Container::const_iterator end() const noexcept
    {
        return this->_end();
    }

    Size size() const noexcept
    {
        return this->_size();
    }

    const JsonVal& operator[](const Index index) const noexcept
    {
        return *this->_at(index);
    }

private:
    JsonVal::UP _clone() const override;
    void _accept(JsonValVisitor& visitor) const override;
    bool _isEqual(const JsonVal& other) const noexcept override;
};

class JsonObjVal final :
    public JsonVal,
    public MapItemMixin<JsonVal>
{
public:
    using Container = _Container;
    using UP = std::unique_ptr<const JsonObjVal>;

public:
    explicit JsonObjVal(Container&& items, TextLocation loc);

    typename Container::const_iterator begin() const noexcept
    {
        return this->_begin();
    }

    typename Container::const_iterator end() const noexcept
    {
        return this->_end();
    }

    Size size() const noexcept
    {
        return this->_size();
    }

    bool hasVal(const std::string& key) const noexcept
    {
        return this->_hasItem(key);
    }

    const JsonVal *operator[](const std::string& key) const noexcept
    {
        return this->_tryAt(key);
    }

    template <typename JsonValT>
    const JsonValT& getVal(const std::string& key) const noexcept
    {
        return static_cast<const JsonValT&>(*this->_tryAt(key));
    }

    bool getRawBoolVal(const std::string& key) const noexcept
    {
        return *this->getVal<JsonBoolVal>(key);
    }

    unsigned long long getRawUIntVal(const std::string& key) const noexcept
    {
        return *this->getVal<JsonUIntVal>(key);
    }

    long long getRawSIntVal(const std::string& key) const noexcept
    {
        return *this->getVal<JsonSIntVal>(key);
    }

    double getRawRealVal(const std::string& key) const noexcept
    {
        return *this->getVal<JsonRealVal>(key);
    }

    const std::string& getRawStrVal(const std::string& key) const noexcept
    {
        return *this->getVal<JsonStrVal>(key);
    }

    template <typename JsonValT>
    const JsonValT& getVal(const std::string& key, const JsonValT& defJsonVal) const noexcept
    {
        const auto jsonVal = this->_tryAt(key);

        return jsonVal ? static_cast<const JsonValT&>(*jsonVal) : defJsonVal;
    }

    template <typename JsonValT>
    typename JsonValT::Val getRawVal(const std::string& key,
                                     const typename JsonValT::Val defVal) const noexcept
    {
        const auto jsonVal = this->_tryAt(key);

        return jsonVal ? *static_cast<const JsonValT&>(*jsonVal) : defVal;
    }

    bool getRawVal(const std::string& key, const bool defVal) const noexcept
    {
        return this->getRawVal<JsonBoolVal>(key, defVal);
    }

    unsigned long long getRawVal(const std::string& key,
                                 const unsigned long long defVal) const noexcept
    {
        return this->getRawVal<JsonUIntVal>(key, defVal);
    }

    long long getRawVal(const std::string& key, const long long defVal) const noexcept
    {
        return this->getRawVal<JsonSIntVal>(key, defVal);
    }

    double getRawVal(const std::string& key, const double defVal) const noexcept
    {
        return this->getRawVal<JsonRealVal>(key, defVal);
    }

    const char *getRawVal(const std::string& key, const char * const defVal) const noexcept
    {
        const auto jsonVal = this->_tryAt(key);

        return jsonVal ? (*jsonVal->asStr()).c_str() : defVal;
    }

private:
    JsonVal::UP _clone() const override;
    void _accept(JsonValVisitor& visitor) const override;
    bool _isEqual(const JsonVal& other) const noexcept override;
};

JsonNullVal::UP createJsonVal(TextLocation loc);
JsonBoolVal::UP createJsonVal(bool val, TextLocation loc);
JsonSIntVal::UP createJsonVal(long long val, TextLocation loc);
JsonUIntVal::UP createJsonVal(unsigned long long val, TextLocation loc);
JsonRealVal::UP createJsonVal(double val, TextLocation loc);
JsonStrVal::UP createJsonVal(std::string val, TextLocation loc);
JsonArrayVal::UP createJsonVal(JsonArrayVal::Container&& items, TextLocation loc);
JsonObjVal::UP createJsonVal(JsonObjVal::Container&& items, TextLocation loc);

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_JSON_JSON_VAL_HPP
