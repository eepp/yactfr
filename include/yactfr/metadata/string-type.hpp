/*
 * CTF string type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  String type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_STRING_TYPE_HPP
#define _YACTFR_METADATA_STRING_TYPE_HPP

#include "data-type.hpp"
#include "scalar-type.hpp"
#include "data-type-visitor.hpp"

namespace yactfr {

/*!
@brief  String type.

@ingroup metadata_dt

A string type describes data stream strings.
*/
class StringType final :
    public ScalarType
{
public:
    /*!
    @brief  Builds a string type.

    @param align    Alignment of data stream strings described by this
                    string type (power of two, greater than 7).

    @throws InvalidMetadata The string type is invalid.
    */
    explicit StringType(unsigned int align);

    /*!
    @brief  Copy constructor.

    @param strType  String type to copy.
    */
    StringType(const StringType& strType);

    bool operator<(const StringType& strType) const noexcept
    {
        return this->alignment() < strType.alignment();
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& otherType) const noexcept override
    {
        return otherType.alignment() == this->alignment();
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STRING_TYPE_HPP
