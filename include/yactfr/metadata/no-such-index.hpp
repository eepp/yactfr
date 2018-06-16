/*
 * "No such index" exception.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  "No such index" exception.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_NO_SUCH_INDEX_HPP
#define _YACTFR_METADATA_NO_SUCH_INDEX_HPP

// for std::runtime_error
#include <stdexcept>

// for Index
#include "../aliases.hpp"

namespace yactfr {

/*!
@brief  "No such index" exception.

@ingroup metadata
*/
class NoSuchIndex final :
    public std::runtime_error
{
public:
    explicit NoSuchIndex(const Index index) :
        std::runtime_error {"No such index"},
        _index {index}
    {
    }

    /// Index which cannot be found.
    Index index() const noexcept
    {
        return _index;
    }

private:
    const Index _index;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_NO_SUCH_INDEX_HPP
