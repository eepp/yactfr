/*
 * Data block.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Data block.

@ingroup element_seq
*/

#ifndef _YACTFR_DATA_BLOCK_HPP
#define _YACTFR_DATA_BLOCK_HPP

// for Size
#include "aliases.hpp"

namespace yactfr {

/*!
@brief  Data block.

A data block is a simple pair of an address from which to read data
(bytes) and a size in bytes. The data pointed to by addr() belongs
to the user function which returns this data block (in other words,
<strong>the caller never frees this memory</strong>).
*/
class DataBlock
{
public:
    /*!
    @brief  Builds a data block where the starting address is \p addr
            and the size \p size bytes.

    @param addr Address of data.
    @param size Size of data (bytes).
    */
    explicit DataBlock(const void *addr, Size size);

    /// Address of data.
    const void *addr() const noexcept
    {
        return _addr;
    }

    /// Size of data (bytes).
    Size size() const noexcept
    {
        return _size;
    }

private:
    const void *_addr = nullptr;
    Size _size = 0;
};

} // namespace yactfr

#endif // _YACTFR_DATA_BLOCK_HPP
