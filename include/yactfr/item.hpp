/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ITEM_HPP
#define _YACTFR_ITEM_HPP

#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <boost/noncopyable.hpp>

#include "aliases.hpp"

namespace yactfr {

/*!
@brief
    Kind of item.

@ingroup item

Please use the Item::Kind alias.
*/
enum class ItemKind
{
    /// Boolean item (BooleanItem).
    BOOLEAN,

    /// Signed integer item (SignedIntegerItem).
    SIGNED_INTEGER,

    /// Unsigned integer item (UnsignedIntegerItem).
    UNSIGNED_INTEGER,

    /// Real item (RealItem).
    REAL,

    /// String item (StringItem).
    STRING,

    /// Array item (ArrayItem).
    ARRAY,

    /// Map item (MapItem).
    MAP,
};

template <typename, ItemKind>
class ScalarValueItem;

/*!
@brief
    Boolean item.

@ingroup item
*/
using BooleanItem = ScalarValueItem<bool, ItemKind::BOOLEAN>;

/*!
@brief
    Signed integer item.

@ingroup item
*/
using SignedIntegerItem = ScalarValueItem<long long, ItemKind::SIGNED_INTEGER>;

/*!
@brief
    Unsigned integer item.

@ingroup item
*/
using UnsignedIntegerItem = ScalarValueItem<unsigned long long, ItemKind::UNSIGNED_INTEGER>;

/*!
@brief
    Real item.

@ingroup item
*/
using RealItem = ScalarValueItem<double, ItemKind::REAL>;

class StringItem;
class ArrayItem;
class MapItem;

/*!
@brief
    Item.

@ingroup item

An item holds some raw value or other items.
*/
class Item :
    boost::noncopyable
{
public:
    /// Unique pointer to constant item.
    using UP = std::unique_ptr<const Item>;

    /// Kind of item.
    using Kind = ItemKind;

protected:
    explicit Item(Kind kind);

public:
    virtual ~Item() = default;

    /// Kind of this item.
    Kind kind() const noexcept
    {
        return _kind;
    }

    /// \c true if this item is a boolean item.
    bool isBoolean() const noexcept
    {
        return _kind == Kind::BOOLEAN;
    }

    /// \c true if this item is a signed integer item.
    bool isSignedInteger() const noexcept
    {
        return _kind == Kind::SIGNED_INTEGER;
    }

    /// \c true if this item is an unsigned integer item.
    bool isUnsignedInteger() const noexcept
    {
        return _kind == Kind::UNSIGNED_INTEGER;
    }

    /// \c true if this item is a real item.
    bool isReal() const noexcept
    {
        return _kind == Kind::REAL;
    }

    /// \c true if this item is a string item.
    bool isString() const noexcept
    {
        return _kind == Kind::STRING;
    }

    /// \c true if this item is an array item.
    bool isArray() const noexcept
    {
        return _kind == Kind::ARRAY;
    }

    /// \c true if this item is a map item.
    bool isMap() const noexcept
    {
        return _kind == Kind::MAP;
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
    UP clone() const;

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
    virtual UP _clone() const = 0;
    virtual bool _isEqual(const Item& other) const noexcept = 0;

private:
    const Kind _kind;
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
    public Item
{
public:
    /// Raw value type.
    using Value = ValueT;

    /// Unique pointer to constant scalar value item.
    using UP = std::unique_ptr<const ScalarValueItem<ValueT, KindV>>;

public:
    /*!
    @brief
        Builds a scalar value item having \p value as its raw value.

    @param[in] value
        Raw value of this item.
    */
    explicit ScalarValueItem(const ValueT value) :
        Item {KindV},
        _val {value}
    {
    }

    /// Raw value of this item.
    ValueT value() const noexcept
    {
        return _val;
    }

private:
    Item::UP _clone() const override
    {
        return std::make_unique<const ScalarValueItem<ValueT, KindV>>(_val);
    }

    bool _isEqual(const Item& other) const noexcept override
    {
        return _val == static_cast<const ScalarValueItem<ValueT, KindV>&>(other)._val;
    }

private:
    const ValueT _val;
};

/*!
@brief
    String item.

@ingroup item
*/
class StringItem final :
    public Item
{
public:
    /// Unique pointer to constant string item.
    using UP = std::unique_ptr<const StringItem>;

public:
    /*!
    @brief
        Builds a string item having \p value as its raw value.

    @param[in] value
        Raw value of this item.
    */
    explicit StringItem(std::string value);

    /// Raw value of this item.
    const std::string& value() const noexcept
    {
        return _val;
    }

private:
    Item::UP _clone() const override;
    bool _isEqual(const Item& other) const noexcept override;

private:
    const std::string _val;
};

/*!
@brief
    Abstract base of ArrayItem and MapItem.

@ingroup item
*/
template <typename ContainerT, Item::Kind KindV>
class CompoundItem :
    public Item
{
public:
    /// Raw container type.
    using Container = ContainerT;

protected:
    explicit CompoundItem(ContainerT&& items) :
        Item {KindV},
        _items {std::move(items)}
    {
    }

public:
    /// Beginning iterator of the raw container of this item.
    typename ContainerT::const_iterator begin() const noexcept
    {
        return _items.begin();
    }

    /// End iterator of the raw container of this item.
    typename ContainerT::const_iterator end() const noexcept
    {
        return _items.end();
    }

    /// Number of items in this item.
    Size size() const noexcept
    {
        return _items.size();
    }

protected:
    const ContainerT _items;
};

/*!
@brief
    Array item.

@ingroup item
*/
class ArrayItem final :
    public CompoundItem<std::vector<Item::UP>, Item::Kind::ARRAY>
{
public:
    /// Unique pointer to constant array item.
    using UP = std::unique_ptr<const ArrayItem>;

public:
    /*!
    @brief
        Builds an array item having \p items as its items.

    @param[in] items
        Items of this array item (moved).
    */
    explicit ArrayItem(Container&& items);

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
        assert(index < _items.size());
        return _items[index].get();
    }

private:
    Item::UP _clone() const override;
    bool _isEqual(const Item& other) const noexcept override;
};

/*!
@brief
    Map item.

@ingroup item
*/
class MapItem final :
    public CompoundItem<std::unordered_map<std::string, Item::UP>, Item::Kind::MAP>
{
public:
    /// Unique pointer to constant map item.
    using UP = std::unique_ptr<const MapItem>;

public:
    /*!
    @brief
        Builds a map item having \p items as its items.

    @param[in] items
        Items of this map item (moved).
    */
    explicit MapItem(Container&& items);

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
    const Item *operator[](const std::string& key) const noexcept;

    /*!
    @brief
        Returns whether or not this map item has an item having the
        key \p key.

    @param[in] key
        Key to check.

    @returns
        \c true if this map item has an item having the key \p key.
    */
    bool hasItem(const std::string& key) const noexcept;

private:
    Item::UP _clone() const override;
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
BooleanItem::UP createItem(bool value);

/*!
@brief
    Creates and returns a signed integer item having \p value as its raw value.

@ingroup item

@param[in] value
    Raw value of the signed integer item to create.

@returns
    Created signed integer item.
*/
SignedIntegerItem::UP createItem(long long value);

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
UnsignedIntegerItem::UP createItem(unsigned long long value);

/*!
@brief
    Creates and returns a real item having \p value as its raw value.

@ingroup item

@param[in] value
    Raw value of the real item to create.

@returns
    Created real item.
*/
RealItem::UP createItem(double value);

/*!
@brief
    Creates and returns a string item having \p value as its raw value.

@ingroup item

@param[in] value
    Raw value of the string item to create.

@returns
    Created string item.
*/
StringItem::UP createItem(std::string value);

/*!
@brief
    Creates and returns an array item having \p items as its items.

@ingroup item

@param[in] items
    Items of the array item to create (moved).

@returns
    Created array item.
*/
ArrayItem::UP createItem(ArrayItem::Container&& items);

/*!
@brief
    Creates and returns a map item having \p items as its items.

@ingroup item

@param[in] items
    Items of the map item to create (moved).

@returns
    Created map item.
*/
MapItem::UP createItem(MapItem::Container&& items);

} // namespace yactfr

#endif // _YACTFR_ITEM_HPP
