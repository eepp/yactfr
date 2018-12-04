/*
 * Data source and related exceptions.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Data source and related exceptions.

@ingroup element_seq
*/

#ifndef _YACTFR_DATA_SOURCE_HPP
#define _YACTFR_DATA_SOURCE_HPP

// for std::unique_ptr
#include <memory>

// for std::exception
#include <stdexcept>

// for boost::optional
#include <boost/optional.hpp>

// for DataBlock
#include "data-block.hpp"

// for Index, Size
#include "aliases.hpp"

namespace yactfr {

/*!
@brief  Data is not available now: try again later.

A \link DataSource data source\endlink can throw this. This means that
data at the requested offset is not available now: you should try again
later.
*/
class DataNotAvailable final :
    public std::exception
{
};

/*!
@brief  Data source.

This is an abstract class which represents a source of data.
*/
class DataSource
{
public:
    /// Unique pointer to data source.
    using UP = std::unique_ptr<DataSource>;

public:
    virtual ~DataSource() = 0;

    /*!
    @brief  Returns a block of data of at least \p minSize bytes from
            this source at offset \p offset.

    This method, on success, <strong>invalidates the last returned
    DataBlock</strong>, if any.

    This method returns \c boost::none to indicate that there's no data
    at offset \p offset.

    This method can throw DataNotAvailable if data is not available
    currently (with at least \p minSize bytes), but it \em could become
    available later. In this case, you should call this method again
    later with the same parameter values. You can also try to call it
    immediately with a smaller \p minSize value. It is possible that,
    when you call this method again, it returns \c boost::none (no more
    data).

    The \em maximum allowed value of \p minSize is 9.

    @param offset   Offset at which to get data from this source. This
                    value does not need to be aligned in any special
                    way.
    @param minSize  Minimum size of the data block to get (bytes),
                    9 or less.
    @returns        Data block, which remains valid until this method is
                    called again or until this source is destroyed, or
                    \c boost::none if there's no data at offset \p offset.

    @throws DataNotAvailable The requested minimum number of bytes
                             (\p minSize) at the requested offset
                             (\p offset) is not available now: try
                             again later.
    */
    boost::optional<DataBlock> data(Index offset, Size minSize);

private:
    /*!
    @brief  Returns a block of data of at least \p minSize bytes from
            this source at offset \p offset (user implementation).

    This method, on success, <strong>invalidates the last returned
    DataBlock, if any</strong>.

    The returned data block's size can be arbitrarily large, as long as
    it contains at least \p minSize bytes.

    When you iterate an element sequence with
    ElementSequenceIterator::operator++(), it is \em guaranteed that the
    requested offsets increase in a monotonic fashion. However, it is
    possible that two consecutive returned data blocks contain
    overlapping data:

    <pre>
    ================
               ==============
                             =======
                                  =============
                                            =====================
    </pre>

    This method can return \c boost::none to indicate that there's no
    data at offset \p offset.

    @param offset   Offset at which to get data from this source. There
                    is not guarantee that this value is aligned in any
                    way.
    @param minSize  Minimum size of the data block to return (bytes),
                    at most 9.
    @returns        Data block, which \em must remain valid until this
                    method is called again and until this source is
                    destroyed, or \c boost::none to indicate that
                    there's no data at offset \p offset.

    @throws DataNotAvailable The requested minimum number of bytes (\p
                             minSize) at the requested offset (\p
                             offset) is not available now: try again
                             later.
    */
    virtual boost::optional<DataBlock> _data(Index offset, Size minSize) = 0;
};

} // namespace yactfr

#endif // _YACTFR_DATA_SOURCE_HPP
