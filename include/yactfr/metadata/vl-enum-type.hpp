/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_VL_ENUM_TYPE_HPP
#define _YACTFR_METADATA_VL_ENUM_TYPE_HPP

#include "vl-int-type.hpp"
#include "enum-type.hpp"

namespace yactfr {

/*!
@brief
    Variable-length signed enumeration type.

@ingroup metadata_dt

A variable-length signed enumeration type describes data stream
variable-length signed enumerations.
*/
class VariableLengthSignedEnumerationType final :
    public EnumerationType<VariableLengthSignedIntegerType,
                           internal::SignedEnumerationTypeValue>
{
public:
    /*!
    @brief
        Builds a variable-length signed enumeration type,
        copying \p mappings.

    @param[in] alignment
        Alignment of data stream variable-length signed enumerations
        described by this type.
    @param[in] mappings
        Mappings (copied).
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length signed
        enumerations described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length signed
        enumerations described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit VariableLengthSignedEnumerationType(unsigned int alignment, const Mappings& mappings,
                                                 DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                 MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a variable-length signed enumeration type,
        moving \p mappings.

    @param[in] alignment
        Alignment of data stream variable-length signed enumerations
        described by this type.
    @param[in] mappings
        Mappings (moved).
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length signed
        enumerations described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length signed
        enumerations described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit VariableLengthSignedEnumerationType(unsigned int alignment, Mappings&& mappings,
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
    Variable-length unsigned enumeration type.

@ingroup metadata_dt

A variable-length unsigned enumeration type describes data stream
variable-length unsigned enumerations.
*/
class VariableLengthUnsignedEnumerationType final :
    public EnumerationType<VariableLengthUnsignedIntegerType,
                           internal::UnsignedEnumerationTypeValue>
{
public:
    /*!
    @brief
        Builds a variable-length unsigned enumeration type,
        copying \p mappings.

    @param[in] alignment
        Alignment of data stream variable-length unsigned enumerations
        described by this type.
    @param[in] mappings
        Mappings (copied).
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length unsigned
        enumerations described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length unsigned
        enumerations described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of variable-length unsigned enumerations described by this
        type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit VariableLengthUnsignedEnumerationType(unsigned int alignment,
                                                   const Mappings& mappings,
                                                   DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                   MapItem::UP userAttributes = nullptr,
                                                   UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a variable-length unsigned enumeration type,
        moving \p mappings.

    @param[in] alignment
        Alignment of data stream variable-length unsigned enumerations
        described by this type.
    @param[in] mappings
        Mappings (moved).
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length unsigned
        enumerations described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length unsigned
        enumerations described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of variable-length unsigned enumerations described by this
        type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit VariableLengthUnsignedEnumerationType(unsigned int alignment, Mappings&& mappings,
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

#endif // _YACTFR_METADATA_VL_ENUM_TYPE_HPP
