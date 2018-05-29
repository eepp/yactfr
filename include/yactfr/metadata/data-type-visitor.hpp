/*
 * Data type visitor.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Data type visitor.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_DATA_TYPE_VISITOR_HPP
#define _YACTFR_METADATA_DATA_TYPE_VISITOR_HPP

#include <boost/noncopyable.hpp>

#include "fwd.hpp"
#include "metadata-base.hpp"

namespace yactfr {

/*!
@brief  Data type visitor.

@ingroup metadata_dt

A subclass instance can be passed to DataType::accept(DataTypeVisitor&) const.
*/
class DataTypeVisitor :
    public MetadataBase,
    boost::noncopyable
{
public:
    virtual ~DataTypeVisitor()
    {
    }

    /*!
    @brief  Visits the signed integer type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const SignedIntType& type)
    {
    }

    /*!
    @brief  Visits the unsigned integer type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const UnsignedIntType& type)
    {
    }

    /*!
    @brief  Visits the floating point number type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const FloatType& type)
    {
    }

    /*!
    @brief  Visits the signed enumeration type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const SignedEnumType& type)
    {
    }

    /*!
    @brief  Visits the unsigned enumeration type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const UnsignedEnumType& type)
    {
    }

    /*!
    @brief  Visits the string type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const StringType& type)
    {
    }

    /*!
    @brief  Visits the structure type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const StructType& type)
    {
    }

    /*!
    @brief  Visits the array type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const ArrayType& type)
    {
    }

    /*!
    @brief  Visits the text array type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const TextArrayType& type)
    {
    }

    /*!
    @brief  Visits the sequence type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const SequenceType& type)
    {
    }

    /*!
    @brief  Visits the text sequence type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const TextSequenceType& type)
    {
    }

    /*!
    @brief  Visits the variant type \p type.

    @param type   Data type to visit.
    */
    virtual void visit(const VariantType& type)
    {
    }

protected:
    explicit DataTypeVisitor();
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DATA_TYPE_VISITOR_HPP
