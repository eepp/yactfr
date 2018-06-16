/*
 * CTF enumeration types.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Classes related to enumeration types.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_ENUM_TYPE_HPP
#define _YACTFR_METADATA_ENUM_TYPE_HPP

// for std::set
#include <set>

// for std::move
#include <utility>

// for std::make_unsigned, std::is_integral
#include <type_traits>

// for std::begin, std::end
#include <iterator>

// for std::string
#include <string>

// for std::unordered_map
#include <unordered_map>

// for std::numeric_limits
#include <limits>

// for std::ostringstream
#include <sstream>

// for std::make_unique
#include <memory>

// for boost::optional
#include <boost/optional.hpp>

// for InvalidMetadata
#include "invalid-metadata.hpp"

// for ByteOrder
#include "byte-order.hpp"

// for Encoding
#include "encoding.hpp"

// for DisplayBase
#include "int-type.hpp"

// for DataType
#include "data-type.hpp"

// for DataTypeVisitor
#include "data-type-visitor.hpp"

namespace yactfr {
namespace internal {

using SignedEnumTypeValue = long long;
using UnsignedEnumTypeValue = std::make_unsigned<SignedEnumTypeValue>::type;

} // namespace internal

/*!
@brief  Enumeration type member range.

@ingroup metadata_dt

An enumeration type member range is a simple pair of lower and upper
values, both included in the range.
*/
template <typename ValueT>
class EnumTypeMemberRange
{
public:
    using Value = ValueT;
    static_assert(std::is_integral<Value>::value && sizeof(Value) >= sizeof(std::uint64_t),
                  "`ValueT` is an integral type of least 64 bits.");

public:
    explicit EnumTypeMemberRange(const ValueT lower, const ValueT upper) :
        _lower {lower},
        _upper {upper}
    {
        if (lower > upper) {
            throw InvalidMetadata {
                "Enumeration type's member range has its lower value greater than its upper value."
            };
        }
    }

    /// Lower bound of this enumeration type member range.
    ValueT lower() const noexcept
    {
        return _lower;
    }

    /// Lower bound of this enumeration type member range.
    ValueT upper() const noexcept
    {
        return _upper;
    }

    /*!
    @brief  Checks whether or not this enumeration type member
            range contains the value \p value.

    @param value    Value to check.
    @returns        \c true if this enumeration type member range
                    contains \p value.
    */
    bool contains(const ValueT value) const noexcept
    {
        return value >= _lower && value <= _upper;
    }

    /*!
    @brief  Checks whether or not the range \p range intersects with
            this enumeration type member range.

    @param range    Range to check for intersection.
    @returns        \c true if \p range intersects this enumeration
                    type member range.
    */
    bool intersects(const EnumTypeMemberRange<ValueT>& range) const noexcept
    {
        return _lower <= range.upper() &&
               range.lower() <= _upper;
    }

    /*!
    @brief  Equality operator.

    @param otherRange   Other range to compare with.
    @returns            \c true if \p otherRange is equal to this
                        enumeration type member range.
    */
    bool operator==(const EnumTypeMemberRange<ValueT>& otherRange) const noexcept
    {
        return otherRange.lower() == _lower &&
               otherRange.upper() == _upper;
    }

    /*!
    @brief  Non-equality operator.

    @param otherRange   Other range to compare with.
    @returns            \c true if \p otherRange is not equal to this
                        enumeration type member range.
    */
    bool operator!=(const EnumTypeMemberRange<ValueT>& otherRange) const noexcept
    {
        return !(*this == otherRange);
    }

    /*!
    @brief  Less-than operator.

    @param otherRange   Other range to compare with.
    @returns            \c true if this enumeration type
                        member range is less than \p otherRange
                        (respects total order).
    */
    bool operator<(const EnumTypeMemberRange<ValueT>& otherRange) const noexcept
    {
        if (_lower < otherRange._lower) {
            return true;
        }

        if (otherRange._lower < _lower) {
            return false;
        }

        if (_upper < otherRange._upper) {
            return true;
        }

        return false;
    }

private:
    const ValueT _lower;
    const ValueT _upper;
};

/*!
@brief  Enumeration type member.

@ingroup metadata_dt

An enumeration type member is a set of
\link EnumTypeMemberRange enumeration type member ranges\endlink.
*/
template <typename RangeT>
class EnumTypeMember
{
public:
    using Value = typename RangeT::Value;
    using Range = RangeT;

public:
    explicit EnumTypeMember(const std::set<RangeT>& ranges) :
        _ranges {ranges}
    {
    }

    explicit EnumTypeMember(std::set<RangeT>&& ranges) :
        _ranges {std::move(ranges)}
    {
    }

    explicit EnumTypeMember()
    {
    }

    /// Ranges of this enumeration type member.
    const std::set<RangeT>& ranges() const noexcept
    {
        return _ranges;
    }

    /*!
    @brief  Checks whether or not this enumeration type member
            contains the value \p value in at least one of its
            ranges.

    @param value    Value to check.
    @returns        \c true if this enumeration type member
                    contains \p value in at least one of its ranges.
    */
    bool contains(const Value value) const
    {
        // check all associated ranges
        for (const auto& range : _ranges) {
            if (range.contains(value)) {
                return true;
            }
        }

        return false;
    }

    /*!
    @brief  Checks whether or not at least one range contained in
            \p otherMember intersects with at least one range contained
            in this enumeration type member.

    @param otherMember  Other enumeration type member to check
                        for intersection.
    @returns            \c true if at least one range contained in
                        \p otherMember intersects with at least one
                        range contained in this enumeration type
                        member.
    */
    bool intersects(const EnumTypeMember<RangeT>& otherMember) const
    {
        for (const auto& range : _ranges) {
            for (const auto& otherRange : otherMember.ranges()) {
                if (range.intersects(otherRange)) {
                    return true;
                }
            }
        }

        return false;
    }

    /*!
    @brief  Equality operator.

    @param otherMember  Other member to compare with.
    @returns            \c true if \p otherMember is equal to this
                        enumeration type member.
    */
    bool operator==(const EnumTypeMember<RangeT>& otherMember) const
    {
        if (otherMember.ranges().size() != _ranges.size()) {
            return false;
        }

        const auto it1 = std::begin(_ranges);
        const auto it2 = std::begin(otherMember.ranges());

        while (it1 != std::end(_ranges)) {
            if (*it1 != *it2) {
                return false;
            }
        }

        return true;
    }

    /*!
    @brief  Non equality operator.

    @param otherMember  Other member to compare with.
    @returns            \c true if \p otherMember is not equal to
                        this enumeration type member.
    */
    bool operator!=(const EnumTypeMember<RangeT>& otherMember) const
    {
        return !(*this == otherMember);
    }

private:
    std::set<RangeT> _ranges;
};

/*!
@brief  Abstract enumeration type.

@ingroup metadata_dt

An enumeration type describes data stream enumerations. Use the concrete
SignedEnumType and UnsignedEnumType depending on the signedness of the
data stream enumerations to describe.
*/
template <typename IntTypeParentT, typename ValueT>
class EnumType :
    public IntTypeParentT
{
public:
    using Value = ValueT;
    using Range = EnumTypeMemberRange<ValueT>;
    using Member = EnumTypeMember<Range>;
    using Members = std::unordered_map<std::string, Member>;

protected:
    explicit EnumType(const int kind,
                      const unsigned int align, const unsigned int size,
                      const ByteOrder byteOrder, const DisplayBase displayBase,
                      const Encoding encoding,
                      const boost::optional<std::string>& mappedClockTypeName,
                      const Members& members) :
        IntTypeParentT {
            DataType::_KIND_ENUM | kind, align, size, byteOrder, displayBase,
            encoding, mappedClockTypeName
        },
        _members {members}
    {
        this->_validateMembers();
    }

    explicit EnumType(const int kind,
                      const unsigned int align, const unsigned int size,
                      const ByteOrder byteOrder, const DisplayBase displayBase,
                      const Encoding encoding,
                      const boost::optional<std::string>& mappedClockTypeName,
                      Members&& members) :
        IntTypeParentT {
            DataType::_KIND_ENUM | kind, align, size, byteOrder, displayBase,
            encoding, mappedClockTypeName
        },
        _members {std::move(members)}
    {
        this->_validateMembers();
    }

public:
    /// Members of this enumeration type.
    const Members& members() const noexcept
    {
        return _members;
    }

    /*!
    @brief  Returns whether or not this enumeration type has a
            member named \p label.

    @param label    Name of member to check.
    @returns        \c true if this enumeration type has a member
                    named \p label.
    */
    bool hasMember(const std::string& label) const
    {
        return _members.find(label) != _members.end();
    }

    /*!
    @brief  Returns whether or not this enumeration type has at
            least one member range containing the value \p value.

    @param value    Value to check.
    @returns        \c true if this enumeration type has at least
                    one member range containing \p value.
    */
    bool hasValue(const ValueT value) const
    {
        for (const auto& nameMemberPair : _members) {
            const auto& member = nameMemberPair.second;

            if (member.contains(value)) {
                return true;
            }
        }

        return false;
    }

private:
    bool _compare(const DataType& otherType) const noexcept override
    {
        const auto& enumType = static_cast<const EnumType<IntTypeParentT, ValueT>&>(otherType);

        return enumType.alignment() == this->alignment() &&
               enumType.size() == this->size() &&
               enumType.byteOrder() == this->byteOrder() &&
               enumType.displayBase() == this->displayBase() &&
               enumType.encoding() == this->encoding() &&
               enumType.mappedClockTypeName() == this->mappedClockTypeName() &&
               enumType.members() == this->members();
    }

    void _validateMembers() const
    {
        assert(this->size() <= 64);

        if (_members.empty()) {
            throw InvalidMetadata {
                "Enumeration type has no members."
            };
        }

        for (const auto& nameMemberPair : _members) {
            this->_validateMember(nameMemberPair.first, nameMemberPair.second);
        }
    }

    void _validateMember(const std::string& name,
                         const Member& member) const
    {
        for (const auto& range : member.ranges()) {
            // validate range storage size
            ValueT minLower, maxUpper;

            if (std::is_signed<ValueT>::value) {
                if (this->size() < 63) {
                    minLower = -(1LL << (this->size() - 1));
                    maxUpper = (1LL << (this->size() - 1)) - 1;
                } else {
                    minLower = std::numeric_limits<ValueT>::min();
                    maxUpper = std::numeric_limits<ValueT>::max();
                }
            } else {
                minLower = std::numeric_limits<ValueT>::min();

                if (this->size() < 64) {
                    maxUpper = (1ULL << this->size()) - 1;
                } else {
                    maxUpper = std::numeric_limits<ValueT>::max();
                }
            }

            if (range.lower() < minLower || range.upper() > maxUpper) {
                std::ostringstream ss;

                ss << "In enumeration type's member `" << name <<
                      "`: some values of the range [" << range.lower() <<
                      ", " << range.upper() <<
                      "] do not fit the underlying integer type's [" <<
                      minLower << ", " << maxUpper << "].";

                throw InvalidMetadata {ss.str()};
            }
        }
    }

protected:
    const Members _members;
};

/*!
@brief  Signed enumeration type.

@ingroup metadata_dt

A signed enumeration type describes data stream signed enumerations.
*/
class SignedEnumType final :
    public EnumType<SignedIntType, internal::SignedEnumTypeValue>
{
public:
    /*!
    @brief  Builds a signed enumeration type.

    @param align                Alignment of data stream signed
                                enumerations described by this signed
                                enumeration type (power of two, greater
                                than 0).
    @param size                 Size of data stream signed enumerations
                                described by this signed enumeration
                                type.
    @param byteOrder            Byte order of data stream signed
                                enumerations described by this signed
                                enumeration type.
    @param displayBase          Preferred display base of data stream
                                signed enumeration described by
                                this signed enumeration type.
    @param encoding             Encoding of data stream signed
                                enumerations described by this signed
                                enumeration type.
    @param mappedClockTypeName  Name of a clock type, in the same trace
                                type, to which this signed enumeration
                                type is mapped.
    @param members              Members.

    @throws InvalidMetadata The signed enumeration type
                                     is invalid.
    */
    explicit SignedEnumType(const unsigned int align, const unsigned int size,
                            const ByteOrder byteOrder,
                            const DisplayBase displayBase,
                            const Encoding encoding,
                            const boost::optional<std::string>& mappedClockTypeName,
                            const Members& members) :
        EnumType<SignedIntType, internal::SignedEnumTypeValue> {
            _KIND_SIGNED_ENUM, align, size, byteOrder, displayBase, encoding,
            mappedClockTypeName, members
        }
    {
    }

    /*!
    @brief  Builds a signed enumeration type.

    @param align                Alignment of data stream signed
                                enumerations described by this signed
                                enumeration type (power of two, greater
                                than 0).
    @param size                 Size of data stream signed enumerations
                                described by this signed enumeration
                                type.
    @param byteOrder            Byte order of data stream signed
                                enumerations described by this signed
                                enumeration type.
    @param displayBase          Preferred display base of data stream
                                signed enumeration described by
                                this signed enumeration type.
    @param encoding             Encoding of data stream signed
                                enumerations described by this signed
                                enumeration type.
    @param mappedClockTypeName  Name of a clock type, in the same trace
                                type, to which this signed enumeration
                                type is mapped.
    @param members              Members (moved to this).

    @throws InvalidMetadata The signed enumeration type
                                     is invalid.
    */
    explicit SignedEnumType(const unsigned int align, const unsigned int size,
                            const ByteOrder byteOrder,
                            const DisplayBase displayBase,
                            const Encoding encoding,
                            const boost::optional<std::string>& mappedClockTypeName,
                            Members&& members) :
        EnumType<SignedIntType, internal::SignedEnumTypeValue> {
            _KIND_SIGNED_ENUM, align, size, byteOrder, displayBase, encoding,
            mappedClockTypeName, std::move(members)
        }
    {
    }

private:
    DataType::UP _clone() const override
    {
        return std::make_unique<SignedEnumType>(this->alignment(),
                                                this->size(),
                                                this->byteOrder(),
                                                this->displayBase(),
                                                this->encoding(),
                                                this->mappedClockTypeName(),
                                                _members);
    }

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Unsigned enumeration type.

@ingroup metadata_dt

An unsigned enumeration type describes data stream unsigned enumerations.
*/
class UnsignedEnumType final :
    public EnumType<UnsignedIntType, internal::UnsignedEnumTypeValue>
{
public:
    /*!
    @brief  Builds an unsigned enumeration type.

    @param align                Alignment of data stream unsigned
                                enumerations described by this unsigned
                                enumeration type (power of two, greater
                                than 0).
    @param size                 Size of data stream unsigned
                                enumerations described by this unsigned
                                enumeration type.
    @param byteOrder            Byte order of data stream unsigned
                                enumerations described by this unsigned
                                enumeration type.
    @param displayBase          Preferred display base of data stream
                                unsigned enumeration described by this
                                unsigned enumeration type.
    @param encoding             Encoding of data stream unsigned
                                enumeration described by this unsigned
                                enumeration type.
    @param mappedClockTypeName  Name of a clock type, in the same trace
                                type, to which this unsigned enumeration
                                type is mapped.
    @param members              Members.

    @throws InvalidMetadata The unsigned enumeration type
                                     is invalid.
    */
    explicit UnsignedEnumType(const unsigned int align, const unsigned int size,
                              const ByteOrder byteOrder,
                              const DisplayBase displayBase, const Encoding encoding,
                              const boost::optional<std::string>& mappedClockTypeName,
                              const Members& members) :
        EnumType<UnsignedIntType, internal::UnsignedEnumTypeValue> {
            _KIND_UNSIGNED_ENUM, align, size, byteOrder, displayBase, encoding,
            mappedClockTypeName, members
        }
    {
    }

    /*!
    @brief  Builds an unsigned enumeration type.

    @param align                Alignment of data stream unsigned
                                enumerations described by this unsigned
                                enumeration type (power of two, greater
                                than 0).
    @param size                 Size of data stream unsigned
                                enumerations described by this unsigned
                                enumeration type.
    @param byteOrder            Byte order of data stream unsigned
                                enumerations described by this unsigned
                                enumeration type.
    @param displayBase          Preferred display base of data stream
                                unsigned enumeration described by this
                                unsigned enumeration type.
    @param encoding             Encoding of data stream unsigned
                                enumeration described by this unsigned
                                enumeration type.
    @param mappedClockTypeName  Name of a clock type, in the same trace
                                type, to which this unsigned enumeration
                                type is mapped.
    @param members              Members (moved to this).

    @throws InvalidMetadata The unsigned enumeration type
                                     is invalid.
    */
    explicit UnsignedEnumType(const unsigned int align, const unsigned int size,
                              const ByteOrder byteOrder,
                              const DisplayBase displayBase, const Encoding encoding,
                              const boost::optional<std::string>& mappedClockTypeName,
                              Members&& members) :
        EnumType<UnsignedIntType, internal::UnsignedEnumTypeValue> {
            _KIND_UNSIGNED_ENUM, align, size, byteOrder, displayBase, encoding,
            mappedClockTypeName, std::move(members)
        }
    {
    }

private:
    DataType::UP _clone() const override
    {
        return std::make_unique<UnsignedEnumType>(this->alignment(),
                                                  this->size(),
                                                  this->byteOrder(),
                                                  this->displayBase(),
                                                  this->encoding(),
                                                  this->mappedClockTypeName(),
                                                  _members);
    }

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_ENUM_TYPE_HPP
