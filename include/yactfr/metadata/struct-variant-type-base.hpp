/*
 * CTF structure and variant type base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Structure and variant type base class.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_STRUCT_VARIANT_TYPE_BASE_HPP
#define _YACTFR_METADATA_STRUCT_VARIANT_TYPE_BASE_HPP

// for std::unordered_map
#include <unordered_map>

// for std::string
#include <string>

// for std::vector
#include <vector>

// for std::move
#include <utility>

// for std::begin, std::end
#include <iterator>

// for std::ostringstream
#include <sstream>

// for InvalidMetadata
#include "invalid-metadata.hpp"

// for CompoundType
#include "compound-type.hpp"

// for NoSuchIndex
#include "no-such-index.hpp"

// for NoSuchName
#include "no-such-name.hpp"

// for Index
#include "../aliases.hpp"

namespace yactfr {

class DataType;

/*!
@brief  Abstract base of StructType and VariantType.

@ingroup metadata_dt
*/
template <typename EntryT>
class StructVariantTypeBase :
    public CompoundType
{
private:
    using _NamesToEntriesT = std::unordered_map<std::string, const EntryT *>;
    using _EntriesT = std::vector<std::unique_ptr<const EntryT>>;

protected:
    explicit StructVariantTypeBase(const _Kind kind, const unsigned int align,
                                   _EntriesT&& entries) :
        CompoundType {kind, align},
        _entriesVec {std::move(entries)}
    {
        this->_initNamesToEntries();
    }

    const _EntriesT& _entries() const noexcept
    {
        return _entriesVec;
    }

    typename _EntriesT::const_iterator _begin() const noexcept
    {
        return std::begin(_entriesVec);
    }

    typename _EntriesT::const_iterator _end() const noexcept
    {
        return std::end(_entriesVec);
    }

    bool _hasEntry(const Index index) const
    {
        return index < _entriesVec.size();
    }

    bool _hasEntry(const std::string& name) const
    {
        return _namesToEntries.find(name) != _namesToEntries.end();
    }

    const EntryT& operator[](const Index index) const
    {
        if (index >= _entriesVec.size()) {
            throw NoSuchIndex {index};
        }

        return *(_entriesVec[index]);
    }

    const EntryT& operator[](const std::string& name) const
    {
        if (!this->_hasEntry(name)) {
            throw NoSuchName {name};
        }

        return *_namesToEntries.find(name)->second;
    }

    const DataType *_findEntryType(const std::string& name) const
    {
        if (!this->_hasEntry(name)) {
            return nullptr;
        }

        return &_namesToEntries.find(name)->second->type();
    }

    const DataType *_findEntryTypeByDisplayName(const std::string& dispName) const
    {
        const auto pairIt = _displayNamesToEntries.find(dispName);

        if (pairIt == std::end(_displayNamesToEntries)) {
            return nullptr;
        }

        return &pairIt->second->type();
    }

    void _cloneEntries(_EntriesT& entries) const
    {
        for (const auto& entry : _entriesVec) {
            std::unique_ptr<const EntryT> entryClone = entry->clone();
            entries.push_back(std::move(entryClone));
        }
    }

    bool _compareEntries(const StructVariantTypeBase& structVariantTypeBase) const
    {
        if (_entriesVec.size() != structVariantTypeBase._entries().size()) {
            return false;
        }

        auto thisIt = std::begin(_entriesVec);
        auto otherIt = std::begin(structVariantTypeBase._entries());

        while (thisIt != std::end(_entriesVec)) {
            const auto& thisUp = *thisIt;
            const auto& otherUp = *otherIt;

            if (*thisUp != *otherUp) {
                return false;
            }

            ++thisIt;
            ++otherIt;
        }

        return true;
    }

private:
    void _initNamesToEntries()
    {
        for (auto& entry : _entriesVec) {
            if (_namesToEntries.find(entry->name()) != std::end(_namesToEntries)) {
                std::ostringstream ss;

                ss << "Duplicate entry `" << entry->name() <<
                      "` in structure or variant entry type.";

                throw InvalidMetadata {ss.str()};
            }

            _namesToEntries[entry->name()] = entry.get();
            _displayNamesToEntries[entry->displayName()] = entry.get();
        }
    }

private:
    const _EntriesT _entriesVec;
    _NamesToEntriesT _namesToEntries;
    _NamesToEntriesT _displayNamesToEntries;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STRUCT_VARIANT_TYPE_BASE_HPP
