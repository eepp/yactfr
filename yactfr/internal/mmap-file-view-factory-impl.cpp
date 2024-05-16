/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <yactfr/io-error.hpp>

#include "mmap-file-view-factory-impl.hpp"
#include "utils.hpp"

namespace yactfr {
namespace internal {

MmapFileViewFactoryImpl::MmapFileViewFactoryImpl(std::string path,
                                                 const boost::optional<Size>& preferredMmapSize,
                                                 const MemoryMappedFileViewFactory::AccessPattern accessPattern) :
    _path {std::move(path)},
    _accessPattern {accessPattern}
{
    _fd = open(_path.c_str(), O_RDONLY);

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

    _fileSize = static_cast<Size>(stat.st_size);
    _mmapOffsetGranularity = sysconf(_SC_PAGE_SIZE);
    assert(_mmapOffsetGranularity >= 1);

    if (preferredMmapSize) {
        _mmapSize = (*preferredMmapSize + _mmapOffsetGranularity - 1) &
                    ~(_mmapOffsetGranularity - 1);

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

} // namespace internal
} // namespace yactfr
