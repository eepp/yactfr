/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_ITEM_HPP
#define YACTFR_METADATA_ITEM_HPP

#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

#include "../internal/metadata/item-mixin.hpp"

namespace yactfr {

/*!
@brief
    Kind of item.

@ingroup item

Prefer the Item::Kind alias.
*/
enum class ItemKind
{
    /// Boolean item (BooleanItem).
    Boolean,

    /// Signed integer item (SignedIntegerItem).
    SignedInteger,

    /// Unsigned integer item (UnsignedIntegerItem).
    UnsignedInteger,

    /// Real item (RealItem).
    Real,

    /// String item (StringItem).
    String,

    /// Array item (ArrayItem).
    Array,

    /// Map item (MapItem).
    Map,
};

template <typename, ItemKind>
class ScalarValueItem;

/*!
@brief
    Boolean item.

@ingroup item
*/
using BooleanItem = ScalarValueItem<bool, ItemKind::Boolean>;

/*!
@brief
    Signed integer item.

@ingroup item
*/
using SignedIntegerItem = ScalarValueItem<long long, ItemKind::SignedInteger>;

/*!
@brief
    Unsigned integer item.

@ingroup item
*/
using UnsignedIntegerItem = ScalarValueItem<unsigned long long, ItemKind::UnsignedInteger>;

/*!
@brief
    Real item.

@ingroup item
*/
using RealItem = ScalarValueItem<double, ItemKind::Real>;

/*!
@brief
    String item.

@ingroup item
*/
using StringItem = ScalarValueItem<std::string, ItemKind::String>;

class ArrayItem;
class MapItem;

/*!
@brief
    Item.

@ingroup item

An item holds some raw value or other items.
*/
class Item :
    public internal::ItemMixin<ItemKind>,
    boost::noncopyable
{
public:
    /// Unique pointer to constant item.
    using Up = std::unique_ptr<const Item>;

    /// Kind of item.
    using Kind = ItemKind;

protected:
    explicit Item(Kind kind);

public:
    virtual ~Item() = default;

    /// Kind of this item.
    Kind kind() const noexcept
    {
        return internal::ItemMixin<ItemKind>::_kind();
    }

    /// \c true if this item is a boolean item.
    bool isBoolean() const noexcept
    {
        return this->kind() == Kind::Boolean;
    }

    /// \c true if this item is a signed integer item.
    bool isSignedInteger() const noexcept
    {
        return this->kind() == Kind::SignedInteger;
    }

    /// \c true if this item is an unsigned integer item.
    bool isUnsignedInteger() const noexcept
    {
        return this->kind() == Kind::UnsignedInteger;
    }

    /// \c true if this item is a real item.
    bool isReal() const noexcept
    {
        return this->kind() == Kind::Real;
    }

    /// \c true if this item is a string item.
    bool isString() const noexcept
    {
        return this->kind() == Kind::String;
    }

    /// \c true if this item is an array item.
    bool isArray() const noexcept
    {
        return this->kind() == Kind::Array;
    }

    /// \c true if this item is a map item.
    bool isMap() const noexcept
    {
        return this->kind() == Kind::Map;
    }

    /*!
    @brief
        Returns this item as a boolean item.

    @pre
        This item is a boolean item.
    */
    const BooleanItem& asBoolean() const noexcept;

    /*!
    @brief
        Returns this item as a signed integer item.

    @pre
        This item is a signed integer item.
    */
    const SignedIntegerItem& asSignedInteger() const noexcept;

    /*!
    @brief
        Returns this item as an unsigned integer item.

    @pre
        This item is an unsigned integer item.
    */
    const UnsignedIntegerItem& asUnsignedInteger() const noexcept;

    /*!
    @brief
        Returns this item as a real item.

    @pre
        This item is a real item.
    */
    const RealItem& asReal() const noexcept;

    /*!
    @brief
        Returns this item as a string item.

    @pre
        This item is a string item.
    */
    const StringItem& asString() const noexcept;

    /*!
    @brief
        Returns this item as an array item.

    @pre
        This item is an array item.
    */
    const ArrayItem& asArray() const noexcept;

    /*!
    @brief
        Returns this item as a map item.

    @pre
        This item is a map item.
    */
    const MapItem& asMap() const noexcept;

    /*!
    @brief
        Creates and returns a clone (deep copy) of this item.

    @returns
        Clone (deep copy) of this item.
    */
    Up clone() const;

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other item to compare to.

    @returns
        \c true if \p other is equal to this item.
    */
    bool operator==(const Item& other) const noexcept;

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Other item to compare to.

    @returns
        \c true if \p other is not equal to this item.
    */
    bool operator!=(const Item& other) const noexcept
    {
        return !(other == *this);
    }

private:
    virtual Up _clone() const = 0;
    virtual bool _isEqual(const Item& other) const noexcept = 0;
};

/*!
@brief
    Scalar value item.

@ingroup item

This template class is the basis of BooleanItem, SignedIntegerItem,
UnsignedIntegerItem, and RealItem. Don't use this template class
directly; use the aforementioned aliases.
*/
template <typename ValueT, Item::Kind KindV>
class ScalarValueItem final :
    public Item,
    public internal::ScalarValItemMixin<ValueT>
{
public:
    /// Raw value type.
    using Value = ValueT;

    /// Unique pointer to constant scalar value item.
    using Up = std::unique_ptr<const ScalarValueItem<ValueT, KindV>>;

public:
    /*!
    @brief
        Builds a scalar value item having \p value as its raw value.

    @param[in] value
        Raw value of this item.
    */
    explicit ScalarValueItem(ValueT value) :
        Item {KindV},
        internal::ScalarValItemMixin<ValueT> {std::move(value)}
    {
    }

    /// Raw value of this item.
    const ValueT& value() const noexcept
    {
        return this->_val();
    }

    /// Raw value of this item.
    const ValueT& operator*() const noexcept
    {
        return this->_val();
    }

    /*!
    @brief
        Creates and returns a clone (deep copy) of this item.

    @returns
        Clone (deep copy) of this item.
    */
    Up clone() const
    {
        return std::make_unique<const ScalarValueItem<ValueT, KindV>>(this->_val());
    }

private:
    Item::Up _clone() const override
    {
        return this->clone();
    }

    bool _isEqual(const Item& other) const noexcept override
    {
        return internal::ScalarValItemMixin<ValueT>::_isEqual(static_cast<const ScalarValueItem<ValueT, KindV>&>(other));
    }
};

/*!
@brief
    Array item.

@ingroup item
*/
class ArrayItem final :
    public Item,
    public internal::ArrayItemMixin<Item>
{
public:
    /// Raw container.
    using Container = typename internal::ArrayItemMixin<Item>::_tContainer;

    /// Unique pointer to constant array item.
    using Up = std::unique_ptr<const ArrayItem>;

public:
    /*!
    @brief
        Builds an array item having \p items as its items.

    @param[in] items
        Items of this array item (moved).
    */
    explicit ArrayItem(Container&& items);

    /// Beginning iterator of the raw container of this item.
    typename Container::const_iterator begin() const noexcept
    {
        return this->_begin();
    }

    /// End iterator of the raw container of this item.
    typename Container::const_iterator end() const noexcept
    {
        return this->_end();
    }

    /// Number of elements in this item.
    Size size() const noexcept
    {
        return this->_size();
    }

    /// Whether or not this item is empty.
    bool isEmpty() const noexcept
    {
        return this->_isEmpty();
    }

    /*!
    @brief
        Returns the item at the index \p index.

    @param[in] index
        Index of the item to return.

    @returns
        Item at the index \p index.

    @pre
        \p index &lt; size()
    */
    const Item *operator[](const Index index) const noexcept
    {
        return this->_at(index);
    }

    /*!
    @brief
        Creates and returns a clone (deep copy) of this item.

    @returns
        Clone (deep copy) of this item.
    */
    Up clone() const;

private:
    Item::Up _clone() const override;
    bool _isEqual(const Item& other) const noexcept override;
};

/*!
@brief
    Map item.

@ingroup item
*/
class MapItem final :
    public Item,
    public internal::MapItemMixin<Item>
{
public:
    /// Raw container.
    using Container = typename internal::MapItemMixin<Item>::_tContainer;

    /// Unique pointer to constant map item.
    using Up = std::unique_ptr<const MapItem>;

public:
    /*!
    @brief
        Builds a map item having \p items as its items.

    @param[in] items
        Items of this map item (moved).
    */
    explicit MapItem(Container&& items);

    /// Beginning iterator of the raw container of this item.
    typename Container::const_iterator begin() const noexcept
    {
        return this->_begin();
    }

    /// End iterator of the raw container of this item.
    typename Container::const_iterator end() const noexcept
    {
        return this->_end();
    }

    /// Number of entries in this item.
    Size size() const noexcept
    {
        return this->_size();
    }

    /// Whether or not this item is empty.
    bool isEmpty() const noexcept
    {
        return this->_isEmpty();
    }

    /*!
    @brief
        Returns the item having the key \p key.

    @param[in] key
        Index of the item to return.

    @returns
        Item having the key \p key.

    @pre
        This map item has an item having the key \p key.

    @sa hasItem()
    */
    const Item *operator[](const std::string& key) const noexcept
    {
        return this->_at(key);
    }

    /*!
    @brief
        Returns whether or not this map item has an item having the
        key \p key.

    @param[in] key
        Key to check.

    @returns
        \c true if this map item has an item having the key \p key.
    */
    bool hasItem(const std::string& key) const noexcept
    {
        return this->_hasItem(key);
    }

    /*!
    @brief
        Creates and returns a clone (deep copy) of this item.

    @returns
        Clone (deep copy) of this item.
    */
    Up clone() const;

private:
    Item::Up _clone() const override;
    bool _isEqual(const Item& other) const noexcept override;
};

/*!
@brief
    Creates and returns a boolean item having \p value as its raw value.

@ingroup item

@param[in] value
    Raw value of the boolean item to create.

@returns
    Created boolean item.
*/
BooleanItem::Up createItem(bool value);

/*!
@brief
    Creates and returns a signed integer item having \p value as its raw value.

@ingroup item

@param[in] value
    Raw value of the signed integer item to create.

@returns
    Created signed integer item.
*/
SignedIntegerItem::Up createItem(long long value);

/*!
@brief
    Creates and returns a unsigned integer item having \p value as its
    raw value.

@ingroup item

@param[in] value
    Raw value of the unsigned integer item to create.

@returns
    Created unsigned integer item.
*/
UnsignedIntegerItem::Up createItem(unsigned long long value);

/*!
@brief
    Creates and returns a real item having \p value as its raw value.

@ingroup item

@param[in] value
    Raw value of the real item to create.

@returns
    Created real item.
*/
RealItem::Up createItem(double value);

/*!
@brief
    Creates and returns a string item having \p value as its raw value.

@ingroup item

@param[in] value
    Raw value of the string item to create.

@returns
    Created string item.
*/
StringItem::Up createItem(std::string value);

/*!
@brief
    Creates and returns an array item having \p items as its items.

@ingroup item

@param[in] items
    Items of the array item to create (moved).

@returns
    Created array item.
*/
ArrayItem::Up createItem(ArrayItem::Container&& items);

/*!
@brief
    Creates and returns a map item having \p items as its items.

@ingroup item

@param[in] items
    Items of the map item to create (moved).

@returns
    Created map item.
*/
MapItem::Up createItem(MapItem::Container&& items);

} // namespace yactfr

#endif // YACTFR_METADATA_ITEM_HPP
