/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_STR_TYPE_HPP
#define _YACTFR_METADATA_STR_TYPE_HPP

#include "dt.hpp"
#include "scalar-dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    String type.

@ingroup metadata_dt

A string type describes data stream null-terminated strings.
*/
class StringType final :
    public ScalarDataType
{
public:
    /*!
    @brief
        Builds a string type.

    @param[in] alignment
        Alignment of data stream strings described by this type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit StringType(unsigned int alignment);

    /*!
    @brief
        Copy constructor.

    @param[in] other
        String type to copy.
    */
    StringType(const StringType& other);

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other string type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const StringType& other) const noexcept
    {
        return this->alignment() < other.alignment();
    }

private:
    DataType::UP _clone() const override;
    bool _compare(const DataType& other) const noexcept override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

};

} // namespace yactfr

#endif // _YACTFR_METADATA_STR_TYPE_HPP
