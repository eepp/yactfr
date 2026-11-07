/*
 * SPDX-FileCopyrightText: 2017-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/data-blk.hpp>

namespace yactfr {

DataBlock::DataBlock(const void * const addr, const Size size) :
    _addr {addr},
    _size {size}
{
}

} // namespace yactfr
