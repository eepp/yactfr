/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_DATA_SRC_FACTORY_HPP
#define _YACTFR_DATA_SRC_FACTORY_HPP

#include "data-src.hpp"

namespace yactfr {

/*!
@brief
    Data source factory.

@ingroup element_seq

This is an abstract class of which an instance represents a factory of
DataSource objects.
*/
class DataSourceFactory
{
public:
    virtual ~DataSourceFactory() = 0;

    /*!
    @brief
        Creates and returns a unique pointer to a data source.

    @returns
        Unique pointer to new data source.
    */
    DataSource::UP createDataSource();

protected:
    /*!
    @brief
        Creates and returns a unique pointer to a data source (user
        implementation).

    @returns
        Unique pointer to new data source.
    */
    virtual DataSource::UP _createDataSource() = 0;
};

} // namespace yactfr

#endif // _YACTFR_DATA_SRC_FACTORY_HPP
