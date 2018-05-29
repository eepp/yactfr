/*
 * Memory mapped file view factory.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Memory mapped file view factory.

@ingroup packet_seq
*/

#ifndef _YACTFR_MEMORY_MAPPED_FILE_VIEW_FACTORY_HPP
#define _YACTFR_MEMORY_MAPPED_FILE_VIEW_FACTORY_HPP

#include <memory>
#include <boost/noncopyable.hpp>

#include "data-source-factory.hpp"

namespace yactfr {

namespace internal {
    class MemoryMappedFileViewFactoryImpl;
}

/*!
@brief  Memory mapped file view factory.

This is a factory of memory mapped file views, which are valid data
sources for packet sequences. All the memory mapped file views that such
a factory creates operate on the same file handle/descriptor.
*/
class MemoryMappedFileViewFactory final :
    public DataSourceFactory,
    boost::noncopyable
{
public:
    /*!
    @brief  Creates a memory mapped file view factory which can create
            memory mapped file views on the file located at \p path.

    \p preferredMmapSize is the preferred size, in bytes, of each
    individual memory map operations performed by the memory map file
    views which this factory creates. The actual memory map size can be
    larger than \p preferredMmapSize if the platform imposes a minimum
    size. The actual memory map size can also be smaller than \p
    preferredMmapSize.

    If \p expectSequentialAccesses is \c true, the memory map file views
    which this factory creates are optimized for a sequential traversal
    if possible. What this does exactly depends on the platform.

    This factory can throw IOError on construction and when creating a
    data source. Its created data source can throw IOError when getting
    a new data block.

    @param path                     Path of file on which to create
                                    memory mapped file views.
    @param preferredMmapSize        Preferred maximum size (bytes) of
                                    each memory map operation, or 0 to
                                    let the implementation decide.
    @param expectSequentialAccesses \c true to optimize for sequential
                                    traversals of the memory mapped file
                                    views created by this factory.

    @throws IOError An I/O error occured (file not found, permission
                    denied, etc.).
    */
    MemoryMappedFileViewFactory(const std::string& path,
                                Size preferredMmapSize = 0,
                                bool expectSequentialAccesses = true);
    ~MemoryMappedFileViewFactory();

private:
    DataSource::UP _createDataSource() override;

private:
    /*
     * Shared because memory mapped file views also keep a reference
     * to keep the file descriptor opened.
     */
    std::shared_ptr<internal::MemoryMappedFileViewFactoryImpl> _pimpl;
};

} // namespace yactfr

#endif // _YACTFR_MEMORY_MAPPED_FILE_VIEW_FACTORY_HPP
