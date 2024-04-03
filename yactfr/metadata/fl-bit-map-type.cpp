/*
 * Copyright (C) 2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/fl-bit-map-type.hpp>
#include <yactfr/internal/metadata/utils.hpp>

namespace yactfr {
namespace {

unsigned long long maskFromBitRanges(const FixedLengthBitMapType::FlagRangeSet& bitRanges) noexcept
{
    auto mask = 0ULL;

    for (auto& bitRange : bitRanges) {
        for (auto bitIndex = bitRange.lower(); bitIndex <= bitRange.upper(); ++bitIndex) {
            assert(bitIndex < 64);
            mask |= (1ULL << bitIndex);
        }
    }

    return mask;
}

} // namespace

FixedLengthBitMapType::_tFlagMask::_tFlagMask(const std::string& name, const FlagRangeSet& bitRanges) :
    _name {&name},
    _mask {maskFromBitRanges(bitRanges)}
{
}

FixedLengthBitMapType::FixedLengthBitMapType(const unsigned int align, const unsigned int len,
                                             const ByteOrder bo, Flags flags,
                                             const boost::optional<BitOrder>& bio,
                                             MapItem::Up attrs) :
    FixedLengthBitArrayType {_kindFlBitMap, align, len, bo, bio, std::move(attrs)},
    _flags {std::move(flags)},
    _flagMasks {this->_flagMasksFromFlags(_flags)}
{
}

FixedLengthBitMapType::FixedLengthBitMapType(const unsigned int len, const ByteOrder bo,
                                             Flags flags, const boost::optional<BitOrder>& bio,
                                             MapItem::Up attrs) :
    FixedLengthBitMapType {1, len, bo, std::move(flags), bio, std::move(attrs)}
{
}

std::vector<FixedLengthBitMapType::_tFlagMask> FixedLengthBitMapType::_flagMasksFromFlags(const Flags& flags)
{
    std::vector<_tFlagMask> flagMasks;

    for (auto& flag : flags) {
        flagMasks.emplace_back(flag.first, flag.second);
    }

    return flagMasks;
}

const FixedLengthBitMapType::FlagRangeSet *FixedLengthBitMapType::operator[](const std::string& name) const noexcept
{
    const auto it = _flags.find(name);

    if (it == _flags.end()) {
        return nullptr;
    }

    return &it->second;
}

bool FixedLengthBitMapType::bitHasActiveFlag(const Index index) const noexcept
{
    for (auto& nameRangeSetPair : _flags) {
        if (nameRangeSetPair.second.contains(index)) {
            return true;
        }
    }

    return false;
}

void FixedLengthBitMapType::activeFlagNamesForUnsignedIntegerValue(const unsigned long long val,
                                                                   std::unordered_set<const std::string *>& names) const
{
    for (auto& flagMask : _flagMasks) {
        if (flagMask.isActiveForVal(val)) {
            names.insert(&flagMask.name());
        }
    }
}

DataType::Up FixedLengthBitMapType::_clone() const
{
    return FixedLengthBitMapType::create(this->alignment(), this->length(), this->byteOrder(),
                                         _flags, this->bitOrder(),
                                         internal::tryCloneAttrs(this->attributes()));
}

} // namespace yactfr
