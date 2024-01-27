/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INT_TYPE_COMMON_HPP
#define _YACTFR_METADATA_INT_TYPE_COMMON_HPP

#include <cassert>
#include <set>
#include <map>
#include <string>
#include <unordered_set>
#include <type_traits>
#include <boost/optional/optional.hpp>

#include "bo.hpp"
#include "dt.hpp"
#include "int-range-set.hpp"

namespace yactfr {

/*!
@brief
    Integer display base.

@ingroup metadata_dt
*/
enum class DisplayBase
{
    /// Binary.
    BINARY = 2,

    /// Octal.
    OCTAL = 8,

    /// Decimal.
    DECIMAL = 10,

    /// Hexadecimal.
    HEXADECIMAL = 16,
};

/*!
@brief
    Common interface of FixedLengthIntegerType and
    VariableLengthIntegerType.

@ingroup metadata_dt
*/
template <typename MappingValueT>
class IntegerTypeCommon
{
public:
    /// Type of the value of an integer range within a mapping.
    using MappingValue = MappingValueT;

    /// Type of an integer range set within a mapping.
    using MappingRangeSet = IntegerRangeSet<MappingValueT>;

    /// Type of mappings.
    using Mappings = std::map<std::string, MappingRangeSet>;

protected:
    explicit IntegerTypeCommon(const DisplayBase prefDispBase, Mappings&& mappings) :
        _prefDispBase {prefDispBase},
        _mappings {std::move(mappings)}
    {
        assert(this->_mappingsAreValid());
    }

public:
    /// Preferred display base of an integer described by this type.
    DisplayBase preferredDisplayBase() const noexcept
    {
        return _prefDispBase;
    }

    /// Mappings.
    const Mappings& mappings() const noexcept
    {
        return _mappings;
    }

    /// Constant mapping iterator set at the first mapping of this type.
    typename Mappings::const_iterator begin() const noexcept
    {
        return _mappings.begin();
    }

    /*!
    @brief
        Constant mapping iterator set \em after the last mapping of this
        type.
    */
    typename Mappings::const_iterator end() const noexcept
    {
        return _mappings.end();
    }

    /*!
    @brief
        Returns the ranges of the mapping named \p name, or \c nullptr
        if not found.

    @param[in] name
        Name of the mapping to find.

    @returns
        Ranges of the mapping named \p name, or \c nullptr if not found.
    */
    const MappingRangeSet *operator[](const std::string& name) const noexcept
    {
        const auto it = _mappings.find(name);

        if (it == _mappings.end()) {
            return nullptr;
        }

        return &it->second;
    }

    /*!
    @brief
        Returns whether or not this type has at least one mapping
        integer range which contains the value \p value.

    @param[in] value
        Value to check.

    @returns
        \c true if this type has at least one mapping integer range
        containing \p value.
    */
    bool valueIsMapped(const MappingValueT value) const
    {
        for (const auto& nameRangeSetPair : _mappings) {
            if (nameRangeSetPair.second.contains(value)) {
                return true;
            }
        }

        return false;
    }

    /*!
    @brief
        Adds to \p names the names of the mappings for the integer
        value \p value.

    @param[in] value
        Integer value to check.
    @param[out] names
        @parblock
        Set of the names of mappings for the integer value \p value.

        The pointed strings remain valid as long as this type exists.
        @endparblock
    */
    void mappingNamesForValue(const MappingValueT value,
                              std::unordered_set<const std::string *>& names) const
    {
        for (auto& nameRangesPair : _mappings) {
            if (nameRangesPair.second.contains(value)) {
                names.insert(&nameRangesPair.first);
            }
        }
    }

protected:
    bool _isEqual(const IntegerTypeCommon& other) const noexcept
    {
        return _prefDispBase == other._prefDispBase &&
               _mappings == other._mappings;
    }

private:
    bool _mappingsAreValid() noexcept
    {
        for (const auto& nameRangeSetPair : _mappings) {
            if (nameRangeSetPair.second.ranges().empty()) {
                return false;
            }
        }

        return true;
    }

private:
    const DisplayBase _prefDispBase;
    const Mappings _mappings;
};

namespace internal {

using SignedIntegerTypeMappingValue = long long;
using UnsignedIntegerTypeMappingValue = std::make_unsigned_t<SignedIntegerTypeMappingValue>;

} // namespace internal

/*!
@brief
    Unsigned integer type role.

@ingroup metadata_dt
*/
enum class UnsignedIntegerTypeRole
{
    /// Packet magic number.
    PACKET_MAGIC_NUMBER,

    /// \link DataStreamType Data stream type\endlink ID.
    DATA_STREAM_TYPE_ID,

    /// Data stream ID.
    DATA_STREAM_ID,

    /// Packet total length.
    PACKET_TOTAL_LENGTH,

    /// Packet content length.
    PACKET_CONTENT_LENGTH,

    /// Default clock timestamp.
    DEFAULT_CLOCK_TIMESTAMP,

    /// Packet end default clock timestamp.
    PACKET_END_DEFAULT_CLOCK_TIMESTAMP,

    /// Discarded event record counter snapshot.
    DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT,

    /// Packet sequence number.
    PACKET_SEQUENCE_NUMBER,

    /// \link EventRecordType Event record type\endlink ID.
    EVENT_RECORD_TYPE_ID,
};

/*!
@brief
    Unsigned integer type role set.

@ingroup metadata_dt
*/
using UnsignedIntegerTypeRoleSet = std::set<UnsignedIntegerTypeRole>;

/*!
@brief
    Common interface of FixedLengthUnsignedIntegerType and
    VariableLengthUnsignedIntegerType.

@ingroup metadata_dt
*/
class UnsignedIntegerTypeCommon
{
protected:
    explicit UnsignedIntegerTypeCommon(UnsignedIntegerTypeRoleSet&& roles);

public:
    /// Roles of unsigned integers described by this type.
    const UnsignedIntegerTypeRoleSet& roles() const noexcept
    {
        return _roles;
    }

    /*!
    @brief
        Returns whether or not the unsigned integers described by this
        type have the role \p role.

    @param[in] role
        Role to check.

    @returns
        \c true if the unsigned integers described by this type have the
        role \p role.
    */
    bool hasRole(const UnsignedIntegerTypeRole role) const noexcept
    {
        return _roles.find(role) != _roles.end();
    }

protected:
    bool _isEqual(const UnsignedIntegerTypeCommon& other) const noexcept;

private:
    const UnsignedIntegerTypeRoleSet _roles;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_INT_TYPE_COMMON_HPP
