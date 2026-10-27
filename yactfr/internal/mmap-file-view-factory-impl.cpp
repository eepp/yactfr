/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <limits>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <yactfr/io-error.hpp>

#include "mmap-file-view-factory-impl.hpp"
#include "utils.hpp"

namespace yactfr::internal {

MmapFileViewFactoryImpl::MmapFileViewFactoryImpl(std::string path,
                                                 const std::optional<Size>& preferredMmapSize,
                                                 const MemoryMappedFileViewFactory::AccessPattern accessPattern) :
    _path {std::move(path)},
    _accessPattern {accessPattern}
{
    /*
     * `O_NONBLOCK` so that opening a FIFO doesn't block until a writer
     * opens it: the check below rejects it anyway. This flag has no
     * effect on a regular file.
     *
     * `O_CLOEXEC` so that a child process which the user executes
     * doesn't inherit the file descriptor.
     */
    _fd = open(_path.c_str(), O_RDONLY | O_NONBLOCK | O_CLOEXEC);

    if (_fd < 0) {
        const auto error = internal::strError();
        std::ostringstream ss;

        ss << "Cannot open \"" << _path << "\" for reading: " << error;
        throw IOError {ss.str()};
    }

    struct stat stat;

    const auto ret = fstat(_fd, &stat);

    if (ret < 0) {
        const auto error = internal::strError();
        std::ostringstream ss;

        ss << "Cannot get file status for \"" << _path << "\": " << error;
        this->_close();
        throw IOError {ss.str()};
    }

    if (!S_ISREG(stat.st_mode)) {
        std::ostringstream ss;

        ss << "Cannot memory-map \"" << _path << "\": not a regular file";
        this->_close();
        throw IOError {ss.str()};
    }

    _fileSize = static_cast<Size>(stat.st_size);
    _mmapOffsetGranularity = sysconf(_SC_PAGE_SIZE);
    assert(_mmapOffsetGranularity >= 1);

    if (preferredMmapSize) {
        /*
         * Round up to a whole number of pages, with at least one page,
         * without overflowing.
         */
        const auto granularity = _mmapOffsetGranularity;
        const auto pageCount = std::max<Size>(*preferredMmapSize / granularity +
                                              (*preferredMmapSize % granularity != 0), 1);

        _mmapSize = std::min(pageCount, std::numeric_limits<Size>::max() / granularity) *
                    granularity;

        // the VM can request a minimum size of at most 9 bytes
        assert(_mmapSize >= 9);
    } else {
        // 512 MiB
        _mmapSize = 512 << 20;
    }
}

void MmapFileViewFactoryImpl::_close()
{
    assert(_fd >= 0);

    // TODO: check return value and log (do not throw) on error
    static_cast<void>(close(_fd));
    _fd = -1;
}

MmapFileViewFactoryImpl::~MmapFileViewFactoryImpl()
{
    this->_close();
}

} // namespace yactfr::internal
