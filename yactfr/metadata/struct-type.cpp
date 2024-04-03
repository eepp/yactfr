/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>

#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {
namespace {

unsigned int realMinAlign(const StructureType::MemberTypes& memberTypes) noexcept
{
    unsigned int align = 1;

    for (const auto& member : memberTypes) {
        align = std::max(align, member->dataType().alignment());
    }

    return align;
}

} // namespace

StructureType::StructureType(const unsigned int minAlign, StructureType::MemberTypes&& memberTypes,
                             MapItem::UP attrs) :
    CompoundDataType {_KIND_STRUCT, minAlign, realMinAlign(memberTypes), std::move(attrs)},
    _memberTypes {std::move(memberTypes)}
{
    this->_initNamesToMemberTypes();
}

StructureType::StructureType(StructureType::MemberTypes&& memberTypes, MapItem::UP attrs) :
    StructureType {1, std::move(memberTypes), std::move(attrs)}
{
}

void StructureType::_initNamesToMemberTypes()
{
    for (const auto& member : _memberTypes) {
        assert(_namesToMemberTypes.find(member->name()) == _namesToMemberTypes.end());
        _namesToMemberTypes[member->name()] = member.get();
    }
}

DataType::UP StructureType::_clone() const
{
    MemberTypes memberTypes;

    for (const auto& memberType : _memberTypes) {
        memberTypes.push_back(memberType->clone());
    }

    return StructureType::create(this->minimumAlignment(), std::move(memberTypes),
                                 internal::tryCloneAttrs(this->attributes()));
}

bool StructureType::_isEqual(const DataType& other) const noexcept
{
    if (!CompoundDataType::_isEqual(other)) {
        return false;
    }

    const auto& otherStructType = other.asStructureType();

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

} // namespace yactfr
