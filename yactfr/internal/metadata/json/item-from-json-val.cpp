/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/item.hpp>

#include "item-from-json-val.hpp"

namespace yactfr {
namespace internal {

class ItemFromJsonValConverter final :
    public JsonValVisitor
{
public:
    void visit(const JsonNullVal&) override
    {
        _item = nullptr;
    }

    void visit(const JsonBoolVal& jsonVal) override
    {
        this->_visitScalarVal(jsonVal);
    }

    void visit(const JsonSIntVal& jsonVal) override
    {
        this->_visitScalarVal(jsonVal);
    }

    void visit(const JsonUIntVal& jsonVal) override
    {
        this->_visitScalarVal(jsonVal);
    }

    void visit(const JsonRealVal& jsonVal) override
    {
        this->_visitScalarVal(jsonVal);
    }

    void visit(const JsonStrVal& jsonVal) override
    {
        this->_visitScalarVal(jsonVal);
    }

    void visit(const JsonArrayVal& jsonVal) override
    {
        ArrayItem::Container items;

        for (auto& jsonValElem : jsonVal) {
            jsonValElem->accept(*this);
            items.push_back(std::move(_item));
        }

        _item = createItem(std::move(items));
    }

    void visit(const JsonObjVal& jsonVal) override
    {
        MapItem::Container items;

        for (auto& keyJsonValPair : jsonVal) {
            keyJsonValPair.second->accept(*this);
            items.insert(std::make_pair(keyJsonValPair.first, std::move(_item)));
        }

        _item = createItem(std::move(items));
    }

    Item::Up releaseItem() noexcept
    {
        return std::move(_item);
    }

private:
    template <typename JsonValT>
    void _visitScalarVal(const JsonValT& jsonVal)
    {
        _item = createItem(*jsonVal);
    }

private:
    Item::Up _item;
};

Item::Up itemFromJsonVal(const JsonVal& val)
{
    ItemFromJsonValConverter converter;

    val.accept(converter);
    return converter.releaseItem();
}

} // namespace internal
} // namespace yactfr
