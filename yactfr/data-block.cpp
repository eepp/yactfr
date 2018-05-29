/*
 * Data block.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/data-block.hpp>

namespace yactfr {

DataBlock::DataBlock(const void *addr, Size size) :
    _addr {addr},
    _size {size}
{
}

} // namespace yactfr
