/*
 * Named data type base class.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Named data type base class.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_NAMED_DATA_TYPE_HPP
#define _YACTFR_METADATA_NAMED_DATA_TYPE_HPP

#include <memory>
#include <string>

#include "metadata-base.hpp"
#include "fwd.hpp"
#include "data-type.hpp"

namespace yactfr {

/*!
@brief  Named data type base class.

@ingroup metadata_dt
*/
class NamedDataType :
    public MetadataBase
{
protected:
    explicit NamedDataType(const std::string& name, DataType::UP type);

public:
    /// Data type.
    const DataType& type() const noexcept
    {
        return *_type;
    }

    /// Name.
    const std::string& name() const noexcept
    {
        return _name;
    }

    /// Display name (name() with first underscore removed, if any).
    const std::string& displayName() const noexcept
    {
        return _dispName;
    }

protected:
    bool operator==(const NamedDataType& otherNamedDataType) const;

private:
    const std::string _name;
    std::string _dispName;
    DataType::UP _type;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_NAMED_DATA_TYPE_HPP
