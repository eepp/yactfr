/*
 * SPDX-FileCopyrightText: 2017-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <cassert>

#include <yactfr/data-src.hpp>

namespace yactfr {

DataSource::~DataSource()
{
}

std::optional<DataBlock> DataSource::data(const Index offset, const Size minSize)
{
    assert(minSize <= 9);

    const auto dataBlock = this->_data(offset, minSize);

    assert(!dataBlock || dataBlock->size() >= minSize);
    return dataBlock;
}

} // namespace yactfr
