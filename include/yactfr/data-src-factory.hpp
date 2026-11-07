/*
 * SPDX-FileCopyrightText: 2017-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#ifndef YACTFR_DATA_SRC_FACTORY_HPP
#define YACTFR_DATA_SRC_FACTORY_HPP

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
    [[ nodiscard ]] DataSource::Up createDataSource();

protected:
    /*!
    @brief
        Creates and returns a unique pointer to a data source (user
        implementation).

    @returns
        Unique pointer to new data source.
    */
    virtual DataSource::Up _createDataSource() = 0;
};

} // namespace yactfr

#endif // YACTFR_DATA_SRC_FACTORY_HPP
