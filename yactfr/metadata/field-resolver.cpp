/*
 * Field resolver.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <iterator>
#include <cassert>

#include "field-resolver.hpp"

#define ZF_LOG_TAG  "FIELDRES"
#include "../logging/zf_log.h"

namespace yactfr {
namespace internal {

FieldResolver::FieldResolver(const GetEntryAtFn& getEntryAtFn) noexcept :
    _getEntryAtFn {getEntryAtFn}
{
}

FieldResolver::Result FieldResolver::resolve(const Scope sourceScope,
                                             const Position& sourcePos,
                                             const FieldRef& tgtFieldRef) const
{
    return this->_resolveAbsolute(sourceScope, sourcePos, tgtFieldRef);
}

FieldResolver::Result FieldResolver::_resolveAbsolute(const Scope sourceScope,
                                                      const Position& sourcePos,
                                                      const FieldRef& tgtFieldRef) const
{
    Position tgtPosition;

    if (!this->_forwardSearch(tgtFieldRef.scope(), {},
                              tgtFieldRef.pathElements(), tgtPosition)) {
        // cannot find target
        return Result {};
    }

    // validate target position
    if (!this->_validateAbsolutePos(sourceScope, sourcePos,
                                    tgtFieldRef.scope(), tgtPosition)) {
        return Result {};
    }

    // get the corresponding result (field reference should be the same)
    return this->_resultFromAbsPos(tgtFieldRef.scope(), tgtPosition);
}

FieldResolver::Result FieldResolver::_resultFromAbsPos(const Scope scope,
                                                       const Position& pos) const
{
    std::vector<std::string> pathElements;
    auto scopeEntry = _getEntryAtFn(scope, {0});
    const DataType *resultType = scopeEntry.type;

    assert(resultType);

    Position curPos;

    for (const auto& index : pos) {
        curPos.push_back(index);

        auto entry = _getEntryAtFn(scope, curPos);

        assert(entry.type);
        resultType = entry.type;

        if (entry.name) {
            pathElements.push_back(*entry.name);
        }
    }

    return {FieldRef {scope, pathElements}, resultType};
}

FieldResolver::Order FieldResolver::_posOrder(const Scope baseScope,
                                              const Position& basePos,
                                              const Scope scope,
                                              const Position& pos) const
{
    if (baseScope < scope) {
        return Order::AFTER;
    }

    if (baseScope > scope) {
        return Order::BEFORE;
    }

    auto baseIt = std::begin(basePos);
    auto it = std::begin(pos);

    // zip
    while (baseIt != std::end(basePos) && it != std::end(pos)) {
        if (*baseIt < *it) {
            return Order::AFTER;
        }

        if (*baseIt > *it) {
            return Order::BEFORE;
        }

        ++baseIt;
        ++it;
    }

    /*
     * At this point we know that both positions are equal up to the
     * minimum length of the positions. Examples:
     *
     *     base: 1 5 2 8
     *     ?:    1 5 2 8
     *
     *     base: 1 5 2
     *     ?:    1 5 2 8
     *
     *     base: 1 5 2 8
     *     ?:    1 5 2
     */
    if (basePos.size() == pos.size()) {
        return Order::SAME;
    }

    if (basePos.size() > pos.size()) {
        return Order::BEFORE;
    }

    return Order::AFTER;
}

FieldResolver::Position FieldResolver::_lcaPos(const Position& pos1,
                                               const Position& pos2) const
{
    auto it1 = std::begin(pos1);
    auto it2 = std::begin(pos2);
    Position lcaPos;

    // zip
    while (it1 != std::end(pos1) && it2 != std::end(pos2)) {
        if (*it1 != *it2) {
            break;
        }

        lcaPos.push_back(*it1);
        ++it1;
        ++it2;
    }

    return lcaPos;
}

bool FieldResolver::_validateAbsolutePos(const Scope sourceScope,
                                         const Position& sourcePos,
                                         const Scope tgtScope,
                                         const Position& tgtPos) const
{
    // rule 1: the target exists
    auto entry = _getEntryAtFn(tgtScope, tgtPos);

    if (!entry.type) {
        return false;
    }

    // rule 2: target is before source
    if (this->_posOrder(sourceScope, sourcePos, tgtScope, tgtPos) != Order::BEFORE) {
        return false;
    }

    if (sourceScope == tgtScope) {
        // rule 3: if the source and target scopes are the same, the
        // lowest common ancestor is a structure type
        auto lcaPos = this->_lcaPos(sourcePos, tgtPos);
        auto entry = _getEntryAtFn(tgtScope, lcaPos);

        assert(entry.type);

        if (!entry.type->isStructType()) {
            return false;
        }

        // rule 4: the target is not a parent of the source
        if (lcaPos == tgtPos) {
            return false;
        }

        // rule 5: from the lowest common ancestor to the target,
        // there are only structures
        Position pos = lcaPos;

        for (auto it = std::begin(tgtPos) + lcaPos.size(); it != std::end(tgtPos) - 1; ++it) {
            pos.push_back(*it);

            auto entry = _getEntryAtFn(tgtScope, pos);

            if (!entry.type || !entry.type->isStructType()) {
                return false;
            }
        }
    } else {
        // rule 6: from the scope's root field to the target,
        // there's no array or sequence
        for (auto it = std::begin(tgtPos); it != std::end(tgtPos); ++it) {
            if (*it == -1ULL) {
                return false;
            }
        }
    }

    return true;
}

bool FieldResolver::_forwardSearch(const Scope scope, const Position& parentPos,
                                   const std::vector<std::string>& pathElements,
                                   Position& result) const
{
    return this->_forwardSearchRec(scope, parentPos, pathElements, result);
}

bool FieldResolver::_forwardSearchRec(const Scope scope,
                                      const Position& parentPos,
                                      const std::vector<std::string>& pathElements,
                                      Position& result) const
{
    if (pathElements.empty()) {
        result = parentPos;
        return true;
    }

    auto parentEntry = _getEntryAtFn(scope, parentPos);

    if (!parentEntry.type) {
        return false;
    }

    if (parentEntry.type->isArrayType() ||
            parentEntry.type->isSequenceType()) {
        Position pos = parentPos;

        pos.push_back(-1ULL);
        return this->_forwardSearchRec(scope, pos, pathElements, result);
    }

    Position pos = parentPos;
    Index i = 0;

    pos.push_back(0);

    while (true) {
        pos.back() = i;

        auto curEntry = _getEntryAtFn(scope, pos);

        if (!curEntry.type) {
            return false;
        }

        if (parentEntry.type->isStructType() || parentEntry.type->isVariantType()) {
            if (*curEntry.name == pathElements.front()) {
                if (this->_forwardSearchRec(scope, pos,
                                            std::vector<std::string> {std::begin(pathElements) + 1,
                                                                      std::end(pathElements)},
                                            result)) {
                    return true;
                }

                return false;
            }
        }

        ++i;
    }
}

} // namespace internal
} // namespace yactfr
