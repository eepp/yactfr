/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_IO_ERROR_HPP
#define _YACTFR_IO_ERROR_HPP

#include <stdexcept>
#include <string>

namespace yactfr {

/*!
@brief
    Generic I/O error.

@ingroup common
*/
class IOError final :
    public std::runtime_error
{
public:
    explicit IOError(std::string message) :
        std::runtime_error {std::move(message)}
    {
    }
};

} // namespace yactfr

#endif // _YACTFR_IO_ERROR_HPP
