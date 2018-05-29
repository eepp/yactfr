/*
 * I/O error.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  I/O error.
*/

#ifndef _YACTFR_IO_ERROR_HPP
#define _YACTFR_IO_ERROR_HPP

#include <exception>
#include <string>

namespace yactfr {

/*!
@brief  Generic I/O error.
*/
class IOError final :
    public std::runtime_error
{
public:
    explicit IOError(const std::string& msg) :
        std::runtime_error {msg}
    {
    }
};

} // namespace yactfr

#endif // _YACTFR_IO_ERROR_HPP
