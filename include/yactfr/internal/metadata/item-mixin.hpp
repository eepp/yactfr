/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_ITEM_MIXIN_HPP
#define _YACTFR_INTERNAL_METADATA_ITEM_MIXIN_HPP

#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "../../aliases.hpp"

namespace yactfr {
namespace internal {

template <typename KindT>
class ItemMixin
{
protected:
    explicit ItemMixin(const KindT kind) :
        _theKind {kind}
    {
    }

    KindT _kind() const noexcept
    {
        return _theKind;
    }

private:
    KindT _theKind;
};

template <typename ValT>
class ScalarValItemMixin
{
protected:
    using _Val = ValT;

protected:
    explicit ScalarValItemMixin(ValT val) :
        _theVal {std::move(val)}
    {
    }

    const ValT& _val() const noexcept
    {
        return _theVal;
    }

    bool _isEqual(const ScalarValItemMixin<ValT>& other) const noexcept
    {
        return _theVal == other._theVal;
    }

private:
    ValT _theVal;
};

template <typename ContainerT>
class CompoundItemMixin
{
protected:
    using _Container = ContainerT;

protected:
    explicit CompoundItemMixin(ContainerT&& items) :
        _theItems {std::move(items)}
    {
    }

    typename ContainerT::const_iterator _begin() const noexcept
    {
        return _theItems.begin();
    }

    typename ContainerT::const_iterator _end() const noexcept
    {
        return _theItems.end();
    }

    Size _size() const noexcept
    {
        return _theItems.size();
    }

    bool _isEmpty() const noexcept
    {
        return _theItems.empty();
    }

protected:
    ContainerT _theItems;
};

template <typename ItemT>
class ArrayItemMixin :
    public CompoundItemMixin<std::vector<typename ItemT::UP>>
{
protected:
    using typename CompoundItemMixin<std::vector<typename ItemT::UP>>::_Container;

protected:
    explicit ArrayItemMixin(_Container&& items) :
        CompoundItemMixin<std::vector<typename ItemT::UP>> {std::move(items)}
    {
    }

    const ItemT *_at(const Index index) const noexcept
    {
        assert(index < this->_theItems.size());
        return this->_theItems[index].get();
    }

    bool _isEqual(const ArrayItemMixin& other) const noexcept
    {
        if (this->_theItems.size() != other._theItems.size()) {
            return false;
        }

        auto it = this->_theItems.begin();
        auto otherIt = other._theItems.begin();

        for (; it != this->_theItems.end(); ++it, ++otherIt) {
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
};

template <typename ItemT>
class MapItemMixin :
    public CompoundItemMixin<std::map<std::string, typename ItemT::UP>>
{
protected:
    using typename CompoundItemMixin<std::map<std::string, typename ItemT::UP>>::_Container;

protected:
    explicit MapItemMixin(_Container&& items) :
        CompoundItemMixin<std::map<std::string, typename ItemT::UP>> {std::move(items)}
    {
    }

    const ItemT *_tryAt(const std::string& key) const noexcept
    {
        const auto it = this->_theItems.find(key);

        if (it == this->_theItems.end()) {
            return nullptr;
        }

        return it->second.get();
    }

    const ItemT *_at(const std::string& key) const noexcept
    {
        const auto it = this->_theItems.find(key);

        assert(it != this->_theItems.end());
        return it->second.get();
    }

    bool _hasItem(const std::string& key) const noexcept
    {
        return this->_theItems.find(key) != this->_theItems.end();
    }

    bool _isEqual(const MapItemMixin& other) const noexcept
    {
        if (this->_theItems.size() != other._theItems.size()) {
            return false;
        }

        for (const auto& keyItemPair : this->_theItems) {
            if (!other._hasItem(keyItemPair.first)) {
                return false;
            }

            const auto otherItem = other._at(keyItemPair.first);
            const auto item = this->_at(keyItemPair.first);

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
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_ITEM_MIXIN_HPP
