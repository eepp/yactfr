/*
 * SPDX-FileCopyrightText: 2017-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <cassert>
#include <yactfr/data-src-factory.hpp>

namespace yactfr {

DataSourceFactory::~DataSourceFactory()
{
}

DataSource::Up DataSourceFactory::createDataSource()
{
    auto dataSourceUp = this->_createDataSource();

    assert(dataSourceUp);
    return dataSourceUp;
}

} // namespace yactfr
