/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FL_ENUM_TYPE_HPP
#define _YACTFR_METADATA_FL_ENUM_TYPE_HPP

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
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length signed enumerations
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
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
                                              MapItem::UP userAttributes = nullptr);

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
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length signed enumerations
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
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
                                              MapItem::UP userAttributes = nullptr);

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
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length unsigned
        enumerations described by this type.

        If set, each key of \p *userAttributes is a namespace.
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
                                                MapItem::UP userAttributes = nullptr,
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
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length unsigned
        enumerations described by this type.

        If set, each key of \p *userAttributes is a namespace.
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
                                                MapItem::UP userAttributes = nullptr,
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
