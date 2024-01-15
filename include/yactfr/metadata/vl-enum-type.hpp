/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_VL_ENUM_TYPE_HPP
#define _YACTFR_METADATA_VL_ENUM_TYPE_HPP

#include <memory>
#include <utility>

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
    /// Unique pointer to constant variable-length signed enumeration type.
    using UP = std::unique_ptr<const VariableLengthSignedEnumerationType>;

public:
    /*!
    @brief
        Builds a variable-length signed enumeration type

    @param[in] alignment
        Alignment of data stream variable-length signed enumerations
        described by this type.
    @param[in] mappings
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length signed
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length signed
        enumerations described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit VariableLengthSignedEnumerationType(unsigned int alignment, Mappings mappings,
                                                 DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                 MapItem::UP attributes = nullptr);

    /*!
    @brief
        Builds a variable-length signed enumeration type,
        having a default alignment (8).

    @param[in] mappings
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length signed
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length signed
        enumerations described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit VariableLengthSignedEnumerationType(Mappings mappings,
                                                 DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                 MapItem::UP attributes = nullptr);

    /*!
    @brief
        Creates a constant variable-length signed enumeration type
        unique pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the variable-length signed enumeration
        type constructor.

    @returns
        Created constant variable-length signed enumeration type unique
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
    /// Unique pointer to constant variable-length unsigned enumeration type.
    using UP = std::unique_ptr<const VariableLengthUnsignedEnumerationType>;

public:
    /*!
    @brief
        Builds a variable-length unsigned enumeration type.

    @param[in] alignment
        Alignment of data stream variable-length unsigned enumerations
        described by this type.
    @param[in] mappings
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length unsigned
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length unsigned
        enumerations described by this type.

        If set, each key of \p *attributes is a namespace.
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
    explicit VariableLengthUnsignedEnumerationType(unsigned int alignment, Mappings mappings,
                                                   DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                   MapItem::UP attributes = nullptr,
                                                   UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a variable-length unsigned enumeration type,
        having a default alignment (8).

    @param[in] mappings
        Mappings.
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length unsigned
        enumerations described by this type.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length unsigned
        enumerations described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of variable-length unsigned enumerations described by this
        type.

    @pre
        <code>!mappings.empty()</code>
    @pre
        Each integer range set within \p mappings is not empty.
    */
    explicit VariableLengthUnsignedEnumerationType(Mappings mappings,
                                                   DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                                   MapItem::UP attributes = nullptr,
                                                   UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Creates a constant variable-length unsigned enumeration type
        unique pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the variable-length unsigned enumeration
        type constructor.

    @returns
        Created constant variable-length unsigned enumeration type
        unique pointer.

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

#endif // _YACTFR_METADATA_VL_ENUM_TYPE_HPP
