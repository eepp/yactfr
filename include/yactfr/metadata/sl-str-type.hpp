/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_SL_STR_TYPE_HPP
#define _YACTFR_METADATA_SL_STR_TYPE_HPP

#include "non-nt-str-type.hpp"
#include "dt-visitor.hpp"
#include "../aliases.hpp"

namespace yactfr {

/*!
@brief
    Static-length string type.

@ingroup metadata_dt

A static-length string type describes data stream static-length strings.
*/
class StaticLengthStringType final :
    public NonNullTerminatedStringType
{
public:
    /*!
    @brief
        Builds a static-length string type.

    @param[in] alignment
        Alignment of data stream static-length strings described by this
        type.
    @param[in] maximumLength
        Maximum length (bytes) of data stream static-length strings
        described by this type.

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit StaticLengthStringType(unsigned int alignment, Size maximumLength);

    /// Maximum length (bytes) of data stream static-length strings
    /// described by this type.
    Size maximumLength() const noexcept
    {
        return _maxLen;
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _compare(const DataType& other) const noexcept override;

private:
    const Size _maxLen;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SL_STR_TYPE_HPP