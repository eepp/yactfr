/*
 * Memory-mapped file view factory implementation.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_MEMORY_MAPPED_FILE_VIEW_FACTORY_IMPL_HPP
#define _YACTFR_MEMORY_MAPPED_FILE_VIEW_FACTORY_IMPL_HPP

#include <string>
#include <yactfr/aliases.hpp>
#include <yactfr/memory-mapped-file-view-factory.hpp>

namespace yactfr {
namespace internal {

/*
 * A MemoryMappedFileViewFactoryImpl object is shared by zero or more
 * MemoryMappedFileView objects, and also by the public
 * MemoryMappedFileViewFactory object which builds it. Its only purpose
 * is to open a file and keep its file descriptor so that a
 * MemoryMappedFileView object can perform memory map operations on it
 * and guarantee its lifetime.
 *
 * MemoryMappedFileView objects also have access to some parameters like
 * the preferred memory map size and whether or not we're expecting
 * sequential accesses on this file.
 */
class MemoryMappedFileViewFactoryImpl
{
public:
    explicit MemoryMappedFileViewFactoryImpl(const std::string& path,
                                             Size preferredMmapSize,
                                             MemoryMappedFileViewFactory::AccessPattern accessPattern);
    ~MemoryMappedFileViewFactoryImpl();

    int fd() const noexcept
    {
        return _fd;
    }

    Size fileSize() const noexcept
    {
        return _fileSize;
    }

    Size mmapOffsetGranularity() const noexcept
    {
        return _mmapOffsetGranularity;
    }

    const std::string& path() const noexcept
    {
        return _path;
    }

    Size mmapSize() const noexcept
    {
        return _mmapSize;
    }

    MemoryMappedFileViewFactory::AccessPattern accessPattern() const noexcept
    {
        return _accessPattern;
    }

    void accessPattern(const MemoryMappedFileViewFactory::AccessPattern accessPattern) noexcept
    {
        _accessPattern = accessPattern;
    }

private:
    void _close();

private:
    const std::string _path;
    Size _mmapSize;
    MemoryMappedFileViewFactory::AccessPattern _accessPattern;
    int _fd = -1;
    Size _fileSize;
    Size _mmapOffsetGranularity;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_MEMORY_MAPPED_FILE_VIEW_FACTORY_IMPL_HPP
