/*
 * Data source factory.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Data source factory.

@ingroup packet_seq
*/

#ifndef _YACTFR_DATA_SOURCE_FACTORY_HPP
#define _YACTFR_DATA_SOURCE_FACTORY_HPP

#include <memory>
#include <cstddef>

#include "data-source.hpp"

namespace yactfr {

/*!
@brief  Data source factory.

This is an abstract class which represents a factory of DataSource
objects.
*/
class DataSourceFactory
{
public:
    virtual ~DataSourceFactory() = 0;

    /*!
    @brief  Creates and returns a unique pointer to a data source.

    @returns    Unique pointer to new data source.
    */
    DataSource::UP createDataSource();

protected:
    /*!
    @brief  Creates and returns a unique pointer to a data source
            (user implementation).

    @returns    Unique pointer to new data source.
    */
    virtual DataSource::UP _createDataSource() = 0;
};

} // namespace yactfr

#endif // _YACTFR_DATA_SOURCE_FACTORY_HPP
