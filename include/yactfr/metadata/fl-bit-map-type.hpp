/*
 * Copyright (C) 2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_FL_BIT_MAP_TYPE_HPP
#define YACTFR_METADATA_FL_BIT_MAP_TYPE_HPP

#include <memory>
#include <utility>
#include <unordered_set>
#include <map>

#include "fl-bit-array-type.hpp"
#include "int-range-set.hpp"
#include "bo.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

class DataTypeVisitor;

/*!
@brief
    Fixed-length bit map type.

@ingroup metadata_dt

A fixed-length bit map type describes data stream fixed-length bit maps.
*/
class FixedLengthBitMapType final :
    public FixedLengthBitArrayType
{
public:
    /// Unique pointer to constant fixed-length boolean type.
    using Up = std::unique_ptr<const FixedLengthBitMapType>;

    /// Type of a bit range set within a mapping.
    using FlagRangeSet = IntegerRangeSet<Index>;

    /// Type of flags.
    using Flags = std::map<std::string, FlagRangeSet>;

private:
    class _tFlagMask final
    {
    public:
        explicit _tFlagMask(const std::string& name, const FlagRangeSet& bitRanges);

        const std::string& name() const noexcept
        {
            return *_name;
        }

        unsigned long long mask() const noexcept
        {
            return _mask;
        }

        bool isActiveForVal(const unsigned long long val) const noexcept
        {
            return val & _mask;
        }

    private:
        const std::string *_name;
        unsigned long long _mask;
    };

public:
    /*!
    @brief
        Builds a fixed-length bit map type.

    @param[in] alignment
        Alignment of data stream fixed-length bit maps described by this
        type.
    @param[in] length
        Length of data stream fixed-length bit maps (bits) described by
        this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length bit maps described by
        this type.
    @param[in] flags
        Flags.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length bit maps described by
        this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length bit maps described
        by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    @pre
        \p flags contains at least one flag.
    @pre
        Each bit range within \p flags must not contain a value
        which is greater than or equal to \p length.
    */
    explicit FixedLengthBitMapType(unsigned int alignment, unsigned int length,
                                   ByteOrder byteOrder, Flags flags,
                                   const boost::optional<BitOrder>& bitOrder = boost::none,
                                   MapItem::Up attributes = nullptr);

    /*!
    @brief
        Builds a fixed-length bit map type having a default alignment
        property (1).

    @param[in] length
        Length of data stream fixed-length bit maps (bits) described by
        this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length bit maps described by
        this type.
    @param[in] flags
        Flags.
    @param[in] bitOrder
        @parblock
        Bit order of data stream fixed-length bit maps described by
        this type.

        If <code>boost::none</code>, then the value is, depending
        on \p byteOrder:

        <dl>
          <dt>ByteOrder::Big
          <dd>BitOrder::LastToFirst

          <dt>ByteOrder::Little
          <dd>BitOrder::FirstToLast
        </dl>
        @endparblock
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length bit maps described
        by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p length > 0.
    @pre
        \p flags contains at least one flag.
    @pre
        Each bit range within \p flags must not contain a value
        which is greater than or equal to \p length.
    */
    explicit FixedLengthBitMapType(unsigned int length, ByteOrder byteOrder, Flags flags,
                                   const boost::optional<BitOrder>& bitOrder = boost::none,
                                   MapItem::Up attributes = nullptr);

    /*!
    @brief
        Creates a constant fixed-length boolean type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the fixed-length boolean type
        constructor.

    @returns
        Created constant fixed-length boolean type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static Up create(ArgTs&&... args)
    {
        return std::make_unique<Up::element_type>(std::forward<ArgTs>(args)...);
    }

    /// Flags.
    const Flags& flags() const noexcept
    {
        return _flags;
    }

    /// Constant flag iterator set at the first flag of this type.
    typename Flags::const_iterator begin() const noexcept
    {
        return _flags.begin();
    }

    /*!
    @brief
        Constant flag iterator set \em after the last flag of this
        type.
    */
    typename Flags::const_iterator end() const noexcept
    {
        return _flags.end();
    }

    /*!
    @brief
        Returns the bit ranges of the flag named \p name, or \c nullptr
        if not found.

    @param[in] name
        Name of the flag to find.

    @returns
        Bit ranges of the flag named \p name, or \c nullptr if not found.
    */
    const FlagRangeSet *operator[](const std::string& name) const noexcept;

    /*!
    @brief
        Returns whether or not an active bit at index \p index would
        have at least one active flag.

    @param[in] index
        Index of the bit to check.

    @returns
        \c true if this type has at least one flag for the bit
        at index \p index.
    */
    bool bitHasActiveFlag(const Index index) const noexcept;

    /*!
    @brief
        Adds to \p names the names of the active flags for the active
        bits of the bit array \p value.

    @param[in] value
        Bit array to check, as an unsigned integer, the least
        significant bit being the first element of the array.
    @param[out] names
        @parblock
        Set of the names of active flags for the bit array \p value.

        The pointed strings remain valid as long as this type exists.
        @endparblock
    */
    void activeFlagNamesForUnsignedIntegerValue(unsigned long long value,
                                                std::unordered_set<const std::string *>& names) const;

private:
    DataType::Up _clone() const override;
    static std::vector<_tFlagMask> _flagMasksFromFlags(const Flags& flags);

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    Flags _flags;
    std::vector<_tFlagMask> _flagMasks;
};

} // namespace yactfr

#endif // YACTFR_METADATA_FL_BIT_MAP_TYPE_HPP
