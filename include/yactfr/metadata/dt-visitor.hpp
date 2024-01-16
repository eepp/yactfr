/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DT_VISITOR_HPP
#define _YACTFR_METADATA_DT_VISITOR_HPP

#include "fwd.hpp"

namespace yactfr {

/*!
@brief
    Data type visitor.

@ingroup metadata_dt

You can pass a subclass instance to DataType::accept().
*/
class DataTypeVisitor
{
protected:
    explicit DataTypeVisitor() = default;

public:
    virtual ~DataTypeVisitor()
    {
    }

// parameter names kept for Doxygen
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

    /*!
    @brief
        Visits the fixed-length bit array type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const FixedLengthBitArrayType& type)
    {
    }

    /*!
    @brief
        Visits the fixed-length boolean type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const FixedLengthBooleanType& type)
    {
    }

    /*!
    @brief
        Visits the fixed-length signed integer type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const FixedLengthSignedIntegerType& type)
    {
    }

    /*!
    @brief
        Visits the fixed-length unsigned integer type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const FixedLengthUnsignedIntegerType& type)
    {
    }

    /*!
    @brief
        Visits the fixed-length floating point number type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const FixedLengthFloatingPointNumberType& type)
    {
    }

    /*!
    @brief
        Visits the variable-length signed integer type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const VariableLengthSignedIntegerType& type)
    {
    }

    /*!
    @brief
        Visits the variable-length unsigned integer type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const VariableLengthUnsignedIntegerType& type)
    {
    }

    /*!
    @brief
        Visits the null-terminated string type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const NullTerminatedStringType& type)
    {
    }

    /*!
    @brief
        Visits the structure type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const StructureType& type)
    {
    }

    /*!
    @brief
        Visits the static-length array type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const StaticLengthArrayType& type)
    {
    }

    /*!
    @brief
        Visits the dynamic-length array type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const DynamicLengthArrayType& type)
    {
    }

    /*!
    @brief
        Visits the static-length string type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const StaticLengthStringType& type)
    {
    }

    /*!
    @brief
        Visits the dynamic-length string type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const DynamicLengthStringType& type)
    {
    }

    /*!
    @brief
        Visits the static-length BLOB type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const StaticLengthBlobType& type)
    {
    }

    /*!
    @brief
        Visits the dynamic-length BLOB type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const DynamicLengthBlobType& type)
    {
    }

    /*!
    @brief
        Visits the type of data stream variants with an unsigned integer
        selector \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const VariantWithUnsignedIntegerSelectorType& type)
    {
    }

    /*!
    @brief
        Visits the type of data stream variants with a signed integer
        selector \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const VariantWithSignedIntegerSelectorType& type)
    {
    }

    /*!
    @brief
        Visits the type of data stream optionals with a boolean selector
        \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const OptionalWithBooleanSelectorType& type)
    {
    }

    /*!
    @brief
        Visits the type of data stream optionals with an unsigned
        integer selector \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const OptionalWithUnsignedIntegerSelectorType& type)
    {
    }

    /*!
    @brief
        Visits the type of data stream optionals with a signed integer
        selector \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const OptionalWithSignedIntegerSelectorType& type)
    {
    }

#pragma GCC diagnostic pop
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DT_VISITOR_HPP
