/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_NT_STR_TYPE_HPP
#define _YACTFR_METADATA_NT_STR_TYPE_HPP

#include "dt.hpp"
#include "scalar-dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Null-terminated string type.

@ingroup metadata_dt

A null-terminated string type describes data stream null-terminated
strings.
*/
class NullTerminatedStringType final :
    public ScalarDataType
{
public:
    /*!
    @brief
        Builds a null-terminated string type.

    @param[in] alignment
        Alignment of data stream null-terminated strings described by
        this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream null-terminated strings described
        by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit NullTerminatedStringType(unsigned int alignment, MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Null-terminated string type to copy.
    */
    NullTerminatedStringType(const NullTerminatedStringType& other);

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other null-terminated string type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const NullTerminatedStringType& other) const noexcept
    {
        return this->alignment() < other.alignment();
    }

private:
    DataType::UP _clone() const override;
    bool _isEqual(const DataType& other) const noexcept override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

};

} // namespace yactfr

#endif // _YACTFR_METADATA_NT_STR_TYPE_HPP
