/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FL_ENUM_TYPE_HPP
#define _YACTFR_METADATA_FL_ENUM_TYPE_HPP

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
#include "fl-int-type.hpp"
#include "int-range-set.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Abstract fixed-length enumeration type.

@ingroup metadata_dt

A fixed-length enumeration type describes data stream enumerations.

Use the concrete SignedFixedLengthEnumerationType and
FixedLengthUnsignedEnumerationType depending on the signedness of the
data stream fixed-length enumerations to describe.

@tparam FixedLengthIntegerTypeParentT
    Parent fixed-length integer type class.
@tparam ValueT
    Type of the lower and upper values of an integer range within a
    mapping.
*/
template <typename FixedLengthIntegerTypeParentT, typename ValueT>
class FixedLengthEnumerationType :
    public FixedLengthIntegerTypeParentT
{
public:
    /// Type of an integer range set within a mapping.
    using RangeSet = IntegerRangeSet<ValueT>;

    /// Type of mappings.
    using Mappings = std::unordered_map<std::string, RangeSet>;

protected:
    template <typename... ArgTs>
    explicit FixedLengthEnumerationType(const int kind, const Mappings& mappings, ArgTs&&... args) :
        FixedLengthIntegerTypeParentT {
            DataType::_KIND_FL_ENUM | kind, std::forward<ArgTs>(args)...
        },
        _mappings {mappings}
    {
    }

    template <typename... ArgTs>
    explicit FixedLengthEnumerationType(const int kind, Mappings&& mappings, ArgTs&&... args) :
        FixedLengthIntegerTypeParentT {
            DataType::_KIND_FL_ENUM | kind, std::forward<ArgTs>(args)...
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
        const auto& otherEnumType = static_cast<const FixedLengthEnumerationType<FixedLengthIntegerTypeParentT, ValueT>&>(other);

        return FixedLengthIntegerTypeParentT::_compare(other) &&
               otherEnumType.mappings() == this->mappings();
    }

private:
    const Mappings _mappings;
};

namespace internal {

using SignedFixedLengthEnumerationTypeValue = long long;

} // namespace internal

/*!
@brief
    Signed fixed-length enumeration type.

@ingroup metadata_dt

A signed fixed-length enumeration type describes data stream
fixed-length signed enumerations.
*/
class SignedFixedLengthEnumerationType final :
    public FixedLengthEnumerationType<FixedLengthSignedIntegerType,
                                      internal::SignedFixedLengthEnumerationTypeValue>
{
public:
    /*!
    @brief
        Builds a fixed-length signed enumeration type,
        copying \p mappings.

    @param[in] alignment
        Alignment of data stream fixed-length signed enumerations
        described by this type.
    @param[in] length
        Length of data stream fixed-length signed enumerations (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length signed enumerations
        described by this type.
    @param[in] mappings
        Mappings (copied).
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        enumerations described by this type.

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
    explicit SignedFixedLengthEnumerationType(unsigned int alignment, unsigned int length,
                                              ByteOrder byteOrder, const Mappings& mappings,
                                              DisplayBase preferredDisplayBase = DisplayBase::DECIMAL);

    /*!
    @brief
        Builds a fixed-length signed enumeration type,
        moving \p mappings.

    @param[in] alignment
        Alignment of data stream fixed-length signed enumerations
        described by this type.
    @param[in] length
        Length of data stream fixed-length signed enumerations (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length signed enumerations
        described by this type.
    @param[in] mappings
        Mappings (moved).
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        enumerations described by this type.

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
    explicit SignedFixedLengthEnumerationType(unsigned int alignment, unsigned int length,
                                              ByteOrder byteOrder, Mappings&& mappings,
                                              DisplayBase preferredDisplayBase = DisplayBase::DECIMAL);

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

namespace internal {

using FixedLengthUnsignedEnumerationTypeValue = std::make_unsigned_t<SignedFixedLengthEnumerationTypeValue>;

} // namespace internal

/*!
@brief
    Fixed-length unsigned enumeration type.

@ingroup metadata_dt

A fixed-length unsigned enumeration type describes data stream
fixed-length unsigned enumerations.
*/
class FixedLengthUnsignedEnumerationType final :
    public FixedLengthEnumerationType<FixedLengthUnsignedIntegerType,
                                      internal::FixedLengthUnsignedEnumerationTypeValue>
{
public:
    /*!
    @brief
        Builds a fixed-length unsigned enumeration type,
        copying \p mappings.

    @param[in] alignment
        Alignment of data stream fixed-length unsigned enumerations
        described by this type.
    @param[in] length
        Length of data stream fixed-length unsigned enumerations (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length unsigned enumerations
        described by this type.
    @param[in] mappings
        Mappings (copied).
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        enumerations described by this type.
    @param[in] roles
        Roles of fixed-length unsigned integers described by this type.

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
    explicit FixedLengthUnsignedEnumerationType(unsigned int alignment, unsigned int length,
                                                ByteOrder byteOrder, const Mappings& mappings,
                                                DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a fixed-length unsigned enumeration type,
        moving \p mappings.

    @param[in] alignment
        Alignment of data stream fixed-length unsigned enumerations
        described by this type.
    @param[in] length
        Length of data stream fixed-length unsigned enumerations
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length unsigned enumerations
        described by this type.
    @param[in] mappings
        Mappings (moved).
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        enumerations described by this type.
    @param[in] roles
        Roles of fixed-length unsigned integers described by this type.

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
    explicit FixedLengthUnsignedEnumerationType(unsigned int alignment, unsigned int length,
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

#endif // _YACTFR_METADATA_FL_ENUM_TYPE_HPP
