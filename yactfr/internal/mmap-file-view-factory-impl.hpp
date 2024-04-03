/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_MMAP_FILE_VIEW_FACTORY_IMPL_HPP
#define YACTFR_INTERNAL_MMAP_FILE_VIEW_FACTORY_IMPL_HPP

#include <string>
#include <yactfr/aliases.hpp>
#include <yactfr/mmap-file-view-factory.hpp>

namespace yactfr {
namespace internal {

/*
 * An `MmapFileViewFactoryImpl` object is shared by zero or more
 * `MemoryMappedFileView` objects, and also by the public
 * `MemoryMappedFileViewFactory` object which builds it. Its only
 * purpose is to open a file and keep its file descriptor open so that a
 * `MemoryMappedFileView` object can perform memory map operations on it
 * and guarantee its lifetime.
 *
 * `MemoryMappedFileView` objects also have access to some parameters
 * like the preferred memory map size and the expected data access
 * pattern.
 */
class MmapFileViewFactoryImpl final
{
public:
    explicit MmapFileViewFactoryImpl(std::string path,
                                     const boost::optional<Size>& preferredMmapSize,
                                     MemoryMappedFileViewFactory::AccessPattern accessPattern);
    ~MmapFileViewFactoryImpl();

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

#endif // YACTFR_INTERNAL_MMAP_FILE_VIEW_FACTORY_IMPL_HPP
