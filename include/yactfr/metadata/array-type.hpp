/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_ARRAY_TYPE_HPP
#define YACTFR_METADATA_ARRAY_TYPE_HPP

#include "compound-dt.hpp"
#include "dt.hpp"

namespace yactfr {

/*!
@brief
    %Base class of static-length and dynamic-length array types.

@ingroup metadata_dt
*/
class ArrayType :
    public CompoundDataType
{
protected:
    explicit ArrayType(_tKind kind, unsigned int minAlign, DataType::Up elemType,
                       MapItem::Up attrs);

public:
    /*!
    @brief
        Type of fields (elements) contained in data stream arrays
        described by this type.
    */
    const DataType& elementType() const
    {
        return *_elemType;
    }

protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    const DataType::Up _elemType;
};

} // namespace yactfr

#endif // YACTFR_METADATA_ARRAY_TYPE_HPP
