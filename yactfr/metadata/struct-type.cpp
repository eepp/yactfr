/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/struct-type.hpp>

#include "../internal/metadata/utils.hpp"

namespace yactfr {

static inline unsigned int realMinAlign(const StructureType::MemberTypes& memberTypes) noexcept
{
    unsigned int align = 1;

    for (const auto& member : memberTypes) {
        align = std::max(align, member->type().alignment());
    }

    return align;
}

StructureType::StructureType(const unsigned int minAlign, StructureType::MemberTypes&& memberTypes,
                             MapItem::UP userAttrs) :
    CompoundDataType {_KIND_STRUCT, minAlign, realMinAlign(memberTypes), std::move(userAttrs)},
    _memberTypes {std::move(memberTypes)}
{
    this->_initNamesToMemberTypes();
}

void StructureType::_initNamesToMemberTypes()
{
    for (const auto& member : _memberTypes) {
        assert(_namesToMemberTypes.find(member->name()) == _namesToMemberTypes.end());
        _namesToMemberTypes[member->name()] = member.get();
        _dispNamesToMemberTypes[member->displayName()] = member.get();
    }
}

DataType::UP StructureType::_clone() const
{
    MemberTypes memberTypes;

    for (const auto& memberType : _memberTypes) {
        memberTypes.push_back(memberType->clone());
    }

    return std::make_unique<StructureType>(this->minimumAlignment(), std::move(memberTypes),
                                           internal::tryCloneUserAttrs(this->userAttributes()));
}

bool StructureType::_isEqual(const DataType& other) const noexcept
{
    if (!CompoundDataType::_isEqual(other)) {
        return false;
    }

    const auto& otherStructType = static_cast<const StructureType&>(other);

    if (_memberTypes.size() != otherStructType._memberTypes.size()) {
        return false;
    }

    auto memberIt = _memberTypes.begin();
    auto otherMemberIt = otherStructType._memberTypes.begin();

    for (; memberIt != _memberTypes.end(); ++memberIt, ++otherMemberIt) {
        if (**memberIt != **otherMemberIt) {
            return false;
        }
    }

    return true;
}

const StructureMemberType *StructureType::operator[](const std::string& name) const noexcept
{
    const auto it = std::find_if(_memberTypes.begin(), _memberTypes.end(),
                                 [&name](const auto& member) {
        return member->name() == name;
    });

    if (it == _memberTypes.end()) {
        return nullptr;
    }

    return it->get();
}

const StructureMemberType *StructureType::memberTypeByDisplayName(const std::string& dispName) const noexcept
{
    const auto it = std::find_if(_memberTypes.begin(), _memberTypes.end(),
                                 [&dispName](const auto& member) {
        return member->displayName() == dispName;
    });

    if (it == _memberTypes.end()) {
        return nullptr;
    }

    return it->get();
}

} // namespace yactfr
