/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/data-src.hpp>

namespace yactfr {

DataSource::~DataSource()
{
}

boost::optional<DataBlock> DataSource::data(const Index offset, const Size minSize)
{
    assert(minSize <= 9);

    const auto dataBlock = this->_data(offset, minSize);

    assert(!dataBlock || dataBlock->size() >= minSize);
    return dataBlock;
}

} // namespace yactfr
