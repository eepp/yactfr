/*
 * "No such type ID" exception.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  "No such type ID" exception.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_NO_SUCH_TYPE_ID_HPP
#define _YACTFR_METADATA_NO_SUCH_TYPE_ID_HPP

// for std::runtime_error
#include <stdexcept>

// for TypeId
#include "aliases.hpp"

namespace yactfr {

/*!
@brief  "No such type ID" exception.

@ingroup metadata
*/
class NoSuchTypeId final :
    public std::runtime_error
{
public:
    explicit NoSuchTypeId(const TypeId id) :
        std::runtime_error {"No such type ID"},
        _id {id}
    {
    }

    /// Type ID which cannot be found.
    TypeId id() const noexcept
    {
        return _id;
    }

private:
    const TypeId _id;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_NO_SUCH_TYPE_ID_HPP
