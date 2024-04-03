/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_VL_INT_TYPE_HPP
#define YACTFR_METADATA_VL_INT_TYPE_HPP

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
template <typename MappingValueT>
class VariableLengthIntegerType :
    public ScalarDataType,
    public IntegerTypeCommon<MappingValueT>
{
    friend class internal::TraceTypeImpl;

public:
    using typename IntegerTypeCommon<MappingValueT>::Mappings;
    using typename IntegerTypeCommon<MappingValueT>::MappingRangeSet;
    using typename IntegerTypeCommon<MappingValueT>::MappingValue;

protected:
    explicit VariableLengthIntegerType(_tKind kind, unsigned int align, DisplayBase prefDispBase,
                                       Mappings&& mappings,
                                       MapItem::Up attrs) :
        ScalarDataType {kind, align, std::move(attrs)},
        IntegerTypeCommon<MappingValueT> {prefDispBase, std::move(mappings)}
    {
    }

    bool _isEqual(const DataType& other) const noexcept override
    {
        return IntegerTypeCommon<MappingValueT>::_isEqual(static_cast<const VariableLengthIntegerType&>(other));
    }
};

/*!
@brief
    Variable-length unsigned integer type.

@ingroup metadata_dt

A variable-length unsigned integer type describes data stream
variable-length unsigned integers.
*/
class VariableLengthUnsignedIntegerType final :
    public VariableLengthIntegerType<internal::UnsignedIntegerTypeMappingValue>,
    public UnsignedIntegerTypeCommon
{
public:
    /// Unique pointer to constant variable-length unsigned integer type.
    using Up = std::unique_ptr<const VariableLengthUnsignedIntegerType>;

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
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length unsigned integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
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
                                               DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                               Mappings mappings = Mappings {},
                                               MapItem::Up attributes = nullptr,
                                               UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a variable-length unsigned integer type having
        a default alignment property (8).

    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length unsigned
        integers described by this type.
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length unsigned integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of variable-length unsigned integers described by this
        type.
    */
    explicit VariableLengthUnsignedIntegerType(DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                               Mappings mappings = Mappings {},
                                               MapItem::Up attributes = nullptr,
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
    static Up create(ArgTs&&... args)
    {
        return std::make_unique<Up::element_type>(std::forward<ArgTs>(args)...);
    }

private:
    bool _isEqual(const DataType& other) const noexcept override;
    DataType::Up _clone() const override;

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
class VariableLengthSignedIntegerType final :
    public VariableLengthIntegerType<internal::SignedIntegerTypeMappingValue>
{
public:
    /// Unique pointer to constant variable-length signed integer type.
    using Up = std::unique_ptr<const VariableLengthSignedIntegerType>;

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
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length signed integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit VariableLengthSignedIntegerType(unsigned int alignment,
                                             DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                             Mappings mappings = Mappings {},
                                             MapItem::Up attributes = nullptr);

    /*!
    @brief
        Builds a variable-length signed integer type having a default
        alignment property (8).

    @param[in] preferredDisplayBase
        Preferred display base of data stream variable-length signed
        integers described by this type.
    @param[in] mappings
        Mappings.
    @param[in] attributes
        @parblock
        Attributes of data stream variable-length signed integers
        described by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    */
    explicit VariableLengthSignedIntegerType(DisplayBase preferredDisplayBase = DisplayBase::Decimal,
                                             Mappings mappings = Mappings {},
                                             MapItem::Up attributes = nullptr);

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
    static Up create(ArgTs&&... args)
    {
        return std::make_unique<Up::element_type>(std::forward<ArgTs>(args)...);
    }

private:
    DataType::Up _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // YACTFR_METADATA_VL_INT_TYPE_HPP
