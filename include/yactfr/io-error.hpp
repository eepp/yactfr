/*
 * SPDX-FileCopyrightText: 2016-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#ifndef YACTFR_IO_ERROR_HPP
#define YACTFR_IO_ERROR_HPP

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

#endif // YACTFR_IO_ERROR_HPP
