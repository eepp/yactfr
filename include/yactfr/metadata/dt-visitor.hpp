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
        Visits the fixed-length signed enumeration type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const SignedFixedLengthEnumerationType& type)
    {
    }

    /*!
    @brief
        Visits the fixed-length unsigned enumeration type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const FixedLengthUnsignedEnumerationType& type)
    {
    }

    /*!
    @brief
        Visits the string type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const StringType& type)
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
        Visits the static array type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const StaticArrayType& type)
    {
    }

    /*!
    @brief
        Visits the static text array type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const StaticTextArrayType& type)
    {
    }

    /*!
    @brief
        Visits the dynamic array type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const DynamicArrayType& type)
    {
    }

    /*!
    @brief
        Visits the dynamic text array type \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const DynamicTextArrayType& type)
    {
    }

    /*!
    @brief
        Visits the type of data stream variants with an unsigned
        selector \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const VariantWithUnsignedSelectorType& type)
    {
    }

    /*!
    @brief
        Visits the type of data stream variants with a signed
        selector \p type.

    @param[in] type
        Data type to visit.
    */
    virtual void visit(const VariantWithSignedSelectorType& type)
    {
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DT_VISITOR_HPP
