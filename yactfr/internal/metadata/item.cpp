/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/item.hpp>

namespace yactfr {

Item::Item(const Kind kind) :
    internal::ItemMixin<Kind> {kind}
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
    if (this->kind() != other.kind()) {
        return false;
    }

    return this->_isEqual(other);
}

Item::Up Item::clone() const
{
    return this->_clone();
}

ArrayItem::ArrayItem(Container&& items) :
    Item {ItemKind::Array},
    internal::ArrayItemMixin<Item> {std::move(items)}
{
}

ArrayItem::Up ArrayItem::clone() const
{
    Container items;

    for (const auto& item : this->_theItems) {
        items.push_back(item->clone());
    }

    return std::make_unique<const ArrayItem>(std::move(items));
}

Item::Up ArrayItem::_clone() const
{
    return this->clone();
}

bool ArrayItem::_isEqual(const Item& other) const noexcept
{
    return internal::ArrayItemMixin<Item>::_isEqual(other.asArray());
}

MapItem::MapItem(Container&& items) :
    Item {ItemKind::Map},
    internal::MapItemMixin<Item> {std::move(items)}
{
}

MapItem::Up MapItem::clone() const
{
    Container items;

    for (const auto& keyItemPair : this->_theItems) {
        items.insert(std::make_pair(keyItemPair.first, keyItemPair.second->clone()));
    }

    return std::make_unique<const MapItem>(std::move(items));
}

Item::Up MapItem::_clone() const
{
    return this->clone();
}

bool MapItem::_isEqual(const Item& other) const noexcept
{
    return internal::MapItemMixin<Item>::_isEqual(other.asMap());
}

BooleanItem::Up createItem(const bool value)
{
    return std::make_unique<const BooleanItem>(value);
}

SignedIntegerItem::Up createItem(const long long value)
{
    return std::make_unique<const SignedIntegerItem>(value);
}

UnsignedIntegerItem::Up createItem(const unsigned long long value)
{
    return std::make_unique<const UnsignedIntegerItem>(value);
}

RealItem::Up createItem(const double value)
{
    return std::make_unique<const RealItem>(value);
}

StringItem::Up createItem(std::string value)
{
    return std::make_unique<const StringItem>(std::move(value));
}

ArrayItem::Up createItem(ArrayItem::Container&& items)
{
    return std::make_unique<const ArrayItem>(std::move(items));
}

MapItem::Up createItem(MapItem::Container&& items)
{
    return std::make_unique<const MapItem>(std::move(items));
}

} // namespace yactfr
