/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <yactfr/data-src-factory.hpp>

namespace yactfr {

DataSourceFactory::~DataSourceFactory()
{
}

DataSource::UP DataSourceFactory::createDataSource()
{
    auto dataSourceUp = this->_createDataSource();

    assert(dataSourceUp);
    return dataSourceUp;
}

} // namespace yactfr
