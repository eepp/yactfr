/*
 * "No such name" exception.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  "No such name" exception.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_NO_SUCH_NAME_HPP
#define _YACTFR_METADATA_NO_SUCH_NAME_HPP

// for std::runtime_error
#include <stdexcept>

// for std::string
#include <string>

namespace yactfr {

/*!
@brief  "No such name" exception.
*/
class NoSuchName :
    public std::runtime_error
{
public:
    explicit NoSuchName(const std::string& name) :
        std::runtime_error {"No such name"},
        _name {name}
    {
    }

    /// Field name which cannot be found.
    const std::string& name() const noexcept
    {
        return _name;
    }

private:
    const std::string _name;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_NO_SUCH_NAME_HPP
