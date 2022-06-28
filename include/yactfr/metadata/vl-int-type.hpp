/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_VL_INT_TYPE_HPP
#define _YACTFR_METADATA_VL_INT_TYPE_HPP

#include <memory>
#include <utility>

#include "int-type-common.hpp"
#include "scalar-dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

/*!
@brief
    Variable-length integer type.

@ingroup metadata_dt

A variable-length integer type describes data stream variable-length
integers.
*/
class VariableLengthIntegerType :
    public ScalarDataType,
    public IntegerTypeCommon
{
    friend class internal::TraceTypeImpl;

protected:
    explicit VariableLengthIntegerType(_Kind kind, unsigned int align, DisplayBase prefDispBase,
                                       MapItem::UP userAttrs);

    bool _isEqual(const DataType& other) const noexcept override;
};

/*!
@brief
    Variable-length unsigned integer type.

@ingroup metadata_dt

A variable-length unsigned integer type describes data stream
variable-length unsigned integers.
*/
class VariableLengthUnsignedIntegerType :
    public VariableLengthIntegerType,
    public UnsignedIntegerTypeCommon
{
public:
    /// Unique pointer to constant variable-length unsigned integer type.
    using UP = std::unique_ptr<const VariableLengthUnsignedIntegerType>;

protected:
    explicit VariableLengthUnsignedIntegerType(_Kind kind, unsigned int align,
                                               DisplayBase prefDispBase,
                                               MapItem::UP userAttrs,
                                               UnsignedIntegerTypeRoleSet roles);

public:
    /*!
    @brief
        Builds a variable-length unsigned integer type.

    @param[in] alignment
        Alignment of data stream variable-length unsigned integers
        described by this type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length unsigned
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length unsigned integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of variable-length unsigned integers described by this
        type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit VariableLengthUnsignedIntegerType(unsigned int alignment,
                                               DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                               MapItem::UP userAttributes = nullptr,
                                               UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a variable-length unsigned integer type having
        a default alignment property (8).

    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length unsigned
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length unsigned integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of variable-length unsigned integers described by this
        type.
    */
    explicit VariableLengthUnsignedIntegerType(DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                               MapItem::UP userAttributes = nullptr,
                                               UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Creates a constant variable-length unsigned integer type unique
        pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the variable-length unsigned integer
        type constructor.

    @returns
        Created constant variable-length unsigned integer type unique
        pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variable-length signed integer type.

@ingroup metadata_dt

A variable-length signed integer type describes data stream
variable-length signed integers.
*/
class VariableLengthSignedIntegerType :
    public VariableLengthIntegerType
{
public:
    /// Unique pointer to constant variable-length signed integer type.
    using UP = std::unique_ptr<const VariableLengthSignedIntegerType>;

protected:
    explicit VariableLengthSignedIntegerType(_Kind kind, unsigned int align,
                                             DisplayBase prefDispBase, MapItem::UP userAttrs);

public:
    /*!
    @brief
        Builds a variable-length signed integer type.

    @param[in] alignment
        Alignment of data stream variable-length signed integers
        described by this type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length signed
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length signed integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit VariableLengthSignedIntegerType(unsigned int alignment,
                                             DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                             MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a variable-length signed integer type having a default
        alignment property (8).

    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length signed
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream variable-length signed integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    */
    explicit VariableLengthSignedIntegerType(DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                             MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a constant variable-length signed integer type unique
        pointer, forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the variable-length signed integer type
        constructor.

    @returns
        Created constant variable-length signed integer type unique
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

#endif // _YACTFR_METADATA_VL_INT_TYPE_HPP
