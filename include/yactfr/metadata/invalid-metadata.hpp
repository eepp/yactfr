/*
 * "Invalid metadata" exception.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  "Invalid metadata" exception.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_INVALID_METADATA_HPP
#define _YACTFR_METADATA_INVALID_METADATA_HPP

// for std::runtime_error
#include <stdexcept>

// for std::string
#include <string>

namespace yactfr {

/*!
@brief  "Invalid metadata" exception.

@ingroup metadata
*/
class InvalidMetadata final :
    public std::runtime_error
{
public:
    explicit InvalidMetadata(const std::string& msg) :
        std::runtime_error {msg}
    {
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_INVALID_METADATA_HPP
