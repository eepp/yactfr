/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_ENUM_TYPE_HPP
#define _YACTFR_METADATA_ENUM_TYPE_HPP

#include <set>
#include <utility>
#include <type_traits>
#include <iterator>
#include <string>
#include <unordered_map>
#include <limits>
#include <sstream>
#include <memory>
#include <boost/optional.hpp>

#include "bo.hpp"
#include "int-type.hpp"
#include "int-range-set.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Abstract enumeration type.

@ingroup metadata_dt

An enumeration type describes data stream enumerations.

Use the concrete SignedEnumerationType and UnsignedEnumerationType
depending on the signedness of the data stream enumerations to describe.

@tparam IntegerTypeParentT
    Parent integer type class.
@tparam ValueT
    Type of the lower and upper values of an integer range within a
    mapping.
*/
template <typename IntegerTypeParentT, typename ValueT>
class EnumerationType :
    public IntegerTypeParentT
{
public:
    /// Type of an integer range set within a mapping.
    using RangeSet = IntegerRangeSet<ValueT>;

    /// Type of mappings.
    using Mappings = std::unordered_map<std::string, RangeSet>;

protected:
    template <typename... ArgTs>
    explicit EnumerationType(const int kind, const Mappings& mappings, ArgTs&&... args) :
        IntegerTypeParentT {
            DataType::_KIND_ENUM | kind, std::forward<ArgTs>(args)...
        },
        _mappings {mappings}
    {
    }

    template <typename... ArgTs>
    explicit EnumerationType(const int kind, Mappings&& mappings, ArgTs&&... args) :
        IntegerTypeParentT {
            DataType::_KIND_ENUM | kind, std::forward<ArgTs>(args)...
        },
        _mappings {std::move(mappings)}
    {
        assert(!_mappings.empty());

        for (const auto& nameRangeSetPair : _mappings) {
            assert(!nameRangeSetPair.second.ranges().empty());
        }
    }

public:
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

    /// Constant mapping iterator set \em after the last mapping of this
    /// type.
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
    const RangeSet *operator[](const std::string& name) const noexcept
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
    bool hasValue(const ValueT value) const
    {
        for (const auto& nameRangeSetPair : _mappings) {
            if (nameRangeSetPair.second.contains(value)) {
                return true;
            }
        }

        return false;
    }

private:
    bool _compare(const DataType& other) const noexcept override
    {
        const auto& otherEnumType = static_cast<const EnumerationType<IntegerTypeParentT, ValueT>&>(other);

        return IntegerTypeParentT::_compare(other) && otherEnumType.mappings() == this->mappings();
    }

private:
    const Mappings _mappings;
};

namespace internal {

using SignedEnumerationTypeValue = long long;

} // namespace internal

/*!
@brief
    Signed enumeration type.

@ingroup metadata_dt

A signed enumeration type describes data stream signed enumerations.
*/
class SignedEnumerationType final :
    public EnumerationType<SignedIntegerType, internal::SignedEnumerationTypeValue>
{
public:
    /*!
    @brief
        Builds a signed enumeration type, copying \p mappings.

    @param[in] alignment
        Alignment of data stream signed enumerations described by this
        type.
    @param[in] length
        Length of data stream signed enumerations (bits) described by
        this type.
    @param[in] byteOrder
        Byte order of data stream signed enumerations described by this
        type.
    @param[in] mappings
        Mappings (copied).
    @param[in] preferredDisplayBase
        Preferred display base of data stream signed enumerations
        described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit SignedEnumerationType(unsigned int alignment, unsigned int length,
                                   ByteOrder byteOrder, const Mappings& mappings,
                                   DisplayBase preferredDisplayBase = DisplayBase::DECIMAL);

    /*!
    @brief
        Builds a signed enumeration type, moving \p mappings.

    @param[in] alignment
        Alignment of data stream signed enumerations described by this
        type.
    @param[in] length
        Length of data stream signed enumerations (bits) described by
        this type.
    @param[in] byteOrder
        Byte order of data stream signed enumerations described by this
        type.
    @param[in] mappings
        Mappings (moved).
    @param[in] preferredDisplayBase
        Preferred display base of data stream signed enumerations
        described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit SignedEnumerationType(unsigned int alignment, unsigned int length, ByteOrder byteOrder,
                                   Mappings&& mappings,
                                   DisplayBase preferredDisplayBase = DisplayBase::DECIMAL);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

namespace internal {

using UnsignedEnumerationTypeValue = std::make_unsigned_t<SignedEnumerationTypeValue>;

} // namespace internal

/*!
@brief
    Unsigned enumeration type.

@ingroup metadata_dt

An unsigned enumeration type describes data stream unsigned
enumerations.
*/
class UnsignedEnumerationType final :
    public EnumerationType<UnsignedIntegerType, internal::UnsignedEnumerationTypeValue>
{
public:
    /*!
    @brief
        Builds an unsigned enumeration type, copying \p mappings.

    @param[in] alignment
        Alignment of data stream unsigned enumerations described by this
        type.
    @param[in] length
        Length of data stream unsigned enumerations (bits) described by
        this type.
    @param[in] byteOrder
        Byte order of data stream unsigned enumerations described by
        this type.
    @param[in] mappings
        Mappings (copied).
    @param[in] preferredDisplayBase
        Preferred display base of data stream unsigned enumerations
        described by this type.
    @param[in] roles
        Roles of unsigned integers described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit UnsignedEnumerationType(unsigned int alignment, unsigned int length,
                                     ByteOrder byteOrder, const Mappings& mappings,
                                     DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                     UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds an unsigned enumeration type, moving \p mappings.

    @param[in] alignment
        Alignment of data stream unsigned enumerations described by this
        type.
    @param[in] length
        Length of data stream unsigned enumerations described by this
        type.
    @param[in] byteOrder
        Byte order of data stream unsigned enumerations described by
        this type.
    @param[in] mappings
        Mappings (moved).
    @param[in] preferredDisplayBase
        Preferred display base of data stream unsigned enumerations
        described by this type.
    @param[in] roles
        Roles of unsigned integers described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit UnsignedEnumerationType(unsigned int alignment, unsigned int length,
                                     ByteOrder byteOrder, Mappings&& mappings,
                                     DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                     UnsignedIntegerTypeRoleSet roles = {});

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_ENUM_TYPE_HPP
