/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_COMPOUND_DT_HPP
#define _YACTFR_METADATA_COMPOUND_DT_HPP

#include "dt.hpp"

namespace yactfr {

/*!
@brief
    %Base class of compound data types.

@ingroup metadata_dt

A compound data type contains another data type.
*/
class CompoundDataType :
    public DataType
{
protected:
    explicit CompoundDataType(_Kind kind, unsigned int minAlign, unsigned int align,
                              MapItem::UP attrs);

public:
    /*!
    @brief
        Minimum alignment of the first data stream bit described by this
        type.
    */
    unsigned int minimumAlignment() const noexcept
    {
        return _minAlign;
    }

protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    const unsigned int _minAlign;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_COMPOUND_DT_HPP

