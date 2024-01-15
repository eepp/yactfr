/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FL_ENUM_TYPE_HPP
#define _YACTFR_METADATA_FL_ENUM_TYPE_HPP

#include <memory>
#include <utility>

#include "fl-int-type.hpp"
#include "enum-type.hpp"

namespace yactfr {

/*!
@brief
    Fixed-length signed enumeration type.

@ingroup metadata_dt

A fixed-length signed enumeration type describes data stream
fixed-length signed enumerations.
*/
class FixedLengthSignedEnumerationType final :
    public EnumerationType<FixedLengthSignedIntegerType, internal::SignedEnumerationTypeValue>
{
public:
    /// Unique pointer to constant fixed-length signed enumeration type.
    using UP = std::unique_ptr<const FixedLengthSignedEnumerationType>;

public:
    /*!
    @brief
        Builds a fixed-length signed enumeration type.

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
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length signed enumerations
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

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
    explicit FixedLengthSignedEnumerationType(unsigned int alignment, unsigned int length,
                                              ByteOrder byteOrder, Mappings mappings,
                                              DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                              MapItem::UP attributes = nullptr);

    /*!
    @brief
        Builds a fixed-length signed enumeration type, having a default
        alignment property (1).

    @param[in] length
        Length of data stream fixed-length signed enumerations (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length signed enumerations
        described by this type.
    @param[in] mappings
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length signed enumerations
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p length > 0.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit FixedLengthSignedEnumerationType(unsigned int length, ByteOrder byteOrder,
                                              Mappings mappings,
                                              DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                              MapItem::UP attributes = nullptr);

    /*!
    @brief
        Creates a constant fixed-length signed enumeration type unique
        pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the fixed-length signed enumeration type
        constructor.

    @returns
        Created constant fixed-length signed enumeration type unique
        pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length unsigned enumeration type.

@ingroup metadata_dt

A fixed-length unsigned enumeration type describes data stream
fixed-length unsigned enumerations.
*/
class FixedLengthUnsignedEnumerationType final :
    public EnumerationType<FixedLengthUnsignedIntegerType, internal::UnsignedEnumerationTypeValue>
{
public:
    /// Unique pointer to constant fixed-length unsigned enumeration type.
    using UP = std::unique_ptr<const FixedLengthUnsignedEnumerationType>;

public:
    /*!
    @brief
        Builds a fixed-length unsigned enumeration type.

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
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length unsigned
        enumerations described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
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
                                                ByteOrder byteOrder, Mappings mappings,
                                                DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                MapItem::UP attributes = nullptr,
                                                UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a fixed-length unsigned enumeration type, having a
        default alignment property (1).

    @param[in] length
        Length of data stream fixed-length unsigned enumerations (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length unsigned enumerations
        described by this type.
    @param[in] mappings
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream fixed-length unsigned
        enumerations described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of fixed-length unsigned integers described by this type.

    @pre
        \p length > 0.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit FixedLengthUnsignedEnumerationType(unsigned int length, ByteOrder byteOrder,
                                                Mappings mappings,
                                                DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                MapItem::UP attributes = nullptr,
                                                UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Creates a constant fixed-length unsigned enumeration type unique
        pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the fixed-length unsigned enumeration
        type constructor.

    @returns
        Created constant fixed-length unsigned enumeration type unique
        pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FL_ENUM_TYPE_HPP
