/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include "json-val.hpp"

namespace yactfr {
namespace internal {

JsonVal::JsonVal(const Kind kind, TextLocation&& loc) :
    internal::ItemMixin<Kind> {kind},
    _loc {std::move(loc)}
{
}

const JsonNullVal& JsonVal::asNull() const noexcept
{
    assert(this->isNull());
    return static_cast<const JsonNullVal&>(*this);
}

const JsonBoolVal& JsonVal::asBool() const noexcept
{
    assert(this->isBool());
    return static_cast<const JsonBoolVal&>(*this);
}

const JsonSIntVal& JsonVal::asSInt() const noexcept
{
    assert(this->isSInt());
    return static_cast<const JsonSIntVal&>(*this);
}

const JsonUIntVal& JsonVal::asUInt() const noexcept
{
    assert(this->isUInt());
    return static_cast<const JsonUIntVal&>(*this);
}

const JsonRealVal& JsonVal::asReal() const noexcept
{
    assert(this->isReal());
    return static_cast<const JsonRealVal&>(*this);
}

const JsonStrVal& JsonVal::asStr() const noexcept
{
    assert(this->isStr());
    return static_cast<const JsonStrVal&>(*this);
}

const JsonArrayVal& JsonVal::asArray() const noexcept
{
    assert(this->isArray());
    return static_cast<const JsonArrayVal&>(*this);
}

const JsonObjVal& JsonVal::asObj() const noexcept
{
    assert(this->isObj());
    return static_cast<const JsonObjVal&>(*this);
}

bool JsonVal::operator==(const JsonVal& other) const noexcept
{
    if (this->kind() != other.kind()) {
        return false;
    }

    return this->_isEqual(other);
}

JsonVal::UP JsonVal::clone() const
{
    return this->_clone();
}

void JsonVal::accept(JsonValVisitor& visitor) const
{
    return this->_accept(visitor);
}

JsonNullVal::JsonNullVal(TextLocation loc) :
    JsonVal {Kind::NUL, std::move(loc)}
{
}

JsonVal::UP JsonNullVal::_clone() const
{
    return std::make_unique<const JsonNullVal>(this->loc());
}

void JsonNullVal::_accept(JsonValVisitor& visitor) const
{
    visitor.visit(*this);
}

bool JsonNullVal::_isEqual(const JsonVal& other) const noexcept
{
    return true;
}

JsonArrayVal::JsonArrayVal(Container&& items, TextLocation loc) :
    JsonVal {Kind::ARRAY, std::move(loc)},
    internal::ArrayItemMixin<JsonVal> {std::move(items)}
{
}

JsonVal::UP JsonArrayVal::_clone() const
{
    Container items;

    for (const auto& item : this->_theItems) {
        items.push_back(item->clone());
    }

    return std::make_unique<const JsonArrayVal>(std::move(items), this->loc());
}

void JsonArrayVal::_accept(JsonValVisitor& visitor) const
{
    visitor.visit(*this);
}

bool JsonArrayVal::_isEqual(const JsonVal& other) const noexcept
{
    return internal::ArrayItemMixin<JsonVal>::_isEqual(other.asArray());
}

JsonObjVal::JsonObjVal(Container&& items, TextLocation loc) :
    JsonVal {Kind::OBJ, std::move(loc)},
    internal::MapItemMixin<JsonVal> {std::move(items)}
{
}

JsonVal::UP JsonObjVal::_clone() const
{
    Container items;

    for (const auto& keyItemPair : this->_theItems) {
        items.insert(std::make_pair(keyItemPair.first, keyItemPair.second->clone()));
    }

    return std::make_unique<const JsonObjVal>(std::move(items), this->loc());
}

void JsonObjVal::_accept(JsonValVisitor& visitor) const
{
    visitor.visit(*this);
}

bool JsonObjVal::_isEqual(const JsonVal& other) const noexcept
{
    return internal::MapItemMixin<JsonVal>::_isEqual(other.asObj());
}

JsonNullVal::UP createJsonVal(TextLocation loc)
{
    return std::make_unique<const JsonNullVal>(std::move(loc));
}

JsonBoolVal::UP createJsonVal(const bool val, TextLocation loc)
{
    return std::make_unique<const JsonBoolVal>(val, std::move(loc));
}

JsonSIntVal::UP createJsonVal(const long long val, TextLocation loc)
{
    return std::make_unique<const JsonSIntVal>(val, std::move(loc));
}

JsonUIntVal::UP createJsonVal(const unsigned long long val, TextLocation loc)
{
    return std::make_unique<const JsonUIntVal>(val, std::move(loc));
}

JsonRealVal::UP createJsonVal(const double val, TextLocation loc)
{
    return std::make_unique<const JsonRealVal>(val, std::move(loc));
}

JsonStrVal::UP createJsonVal(std::string val, TextLocation loc)
{
    return std::make_unique<const JsonStrVal>(std::move(val), std::move(loc));
}

JsonArrayVal::UP createJsonVal(JsonArrayVal::Container&& items, TextLocation loc)
{
    return std::make_unique<const JsonArrayVal>(std::move(items), std::move(loc));
}

JsonObjVal::UP createJsonVal(JsonObjVal::Container&& items, TextLocation loc)
{
    return std::make_unique<const JsonObjVal>(std::move(items), std::move(loc));
}

} // namespace internal
} // namespace yactfr
