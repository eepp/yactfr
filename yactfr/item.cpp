/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/item.hpp>

namespace yactfr {

Item::Item(const Kind kind) :
    _kind {kind}
{
}

const BooleanItem& Item::asBoolean() const noexcept
{
    assert(this->isBoolean());
    return static_cast<const BooleanItem&>(*this);
}

const SignedIntegerItem& Item::asSignedInteger() const noexcept
{
    assert(this->isSignedInteger());
    return static_cast<const SignedIntegerItem&>(*this);
}

const UnsignedIntegerItem& Item::asUnsignedInteger() const noexcept
{
    assert(this->isUnsignedInteger());
    return static_cast<const UnsignedIntegerItem&>(*this);
}

const RealItem& Item::asReal() const noexcept
{
    assert(this->isReal());
    return static_cast<const RealItem&>(*this);
}

const StringItem& Item::asString() const noexcept
{
    assert(this->isString());
    return static_cast<const StringItem&>(*this);
}

const ArrayItem& Item::asArray() const noexcept
{
    assert(this->isArray());
    return static_cast<const ArrayItem&>(*this);
}

const MapItem& Item::asMap() const noexcept
{
    assert(this->isMap());
    return static_cast<const MapItem&>(*this);
}

bool Item::operator==(const Item& other) const noexcept
{
    if (_kind != other._kind) {
        return false;
    }

    return this->_isEqual(other);
}

Item::UP Item::clone() const
{
    return this->_clone();
}

StringItem::StringItem(std::string val) :
    Item {Kind::STRING},
    _val {std::move(val)}
{
}

Item::UP StringItem::_clone() const
{
    return std::make_unique<const StringItem>(_val);
}

bool StringItem::_isEqual(const Item& other) const noexcept
{
    return _val == other.asString()._val;
}

ArrayItem::ArrayItem(Container&& items) :
    CompoundItem<Container, Item::Kind::ARRAY> {std::move(items)}
{
}

Item::UP ArrayItem::_clone() const
{
    Container items;

    for (const auto& item : _items) {
        items.push_back(item->clone());
    }

    return std::make_unique<const ArrayItem>(std::move(items));
}

bool ArrayItem::_isEqual(const Item& other) const noexcept
{
    auto& otherArrayItem = other.asArray();

    if (_items.size() != otherArrayItem._items.size()) {
        return false;
    }

    auto it = _items.begin();
    auto otherIt = otherArrayItem._items.begin();

    for (; it != _items.end(); ++it, ++otherIt) {
        if ((!*it && *otherIt) || (*it && !*otherIt)) {
            return false;
        }

        if (!*it) {
            continue;
        }

        if (*it != *otherIt) {
            return false;
        }
    }

    return true;
}

MapItem::MapItem(Container&& items) :
    CompoundItem<Container, Item::Kind::MAP> {std::move(items)}
{
}

const Item *MapItem::operator[](const std::string& key) const noexcept
{
    const auto it = _items.find(key);

    assert(it != _items.end());
    return it->second.get();
}

bool MapItem::hasItem(const std::string& key) const noexcept
{
    return _items.find(key) != _items.end();
}

Item::UP MapItem::_clone() const
{
    Container items;

    for (const auto& keyItemPair : _items) {
        items.insert(std::make_pair(keyItemPair.first, keyItemPair.second->clone()));
    }

    return std::make_unique<const MapItem>(std::move(items));
}

bool MapItem::_isEqual(const Item& other) const noexcept
{
    auto& otherMapItem = other.asMap();

    if (_items.size() != otherMapItem._items.size()) {
        return false;
    }

    for (const auto& keyItemPair : _items) {
        if (!otherMapItem.hasItem(keyItemPair.first)) {
            return false;
        }

        const auto otherItem = otherMapItem[keyItemPair.first];
        const auto item = (*this)[keyItemPair.first];

        if ((!item && otherItem) || (item && !otherItem)) {
            return false;
        }

        if (!item) {
            continue;
        }

        if (*item != *otherItem) {
            return false;
        }
    }

    return true;
}

BooleanItem::UP createItem(const bool value)
{
    return std::make_unique<const BooleanItem>(value);
}

SignedIntegerItem::UP createItem(const long long value)
{
    return std::make_unique<const SignedIntegerItem>(value);
}

UnsignedIntegerItem::UP createItem(const unsigned long long value)
{
    return std::make_unique<const UnsignedIntegerItem>(value);
}

RealItem::UP createItem(const double value)
{
    return std::make_unique<const RealItem>(value);
}

StringItem::UP createItem(std::string value)
{
    return std::make_unique<const StringItem>(std::move(value));
}

ArrayItem::UP createItem(ArrayItem::Container&& items)
{
    return std::make_unique<const ArrayItem>(std::move(items));
}

MapItem::UP createItem(MapItem::Container&& items)
{
    return std::make_unique<const MapItem>(std::move(items));
}

} // namespace yactfr
