/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstring>
#include <sstream>
#include <sys/mman.h>

#include <yactfr/mmap-file-view-factory.hpp>
#include <yactfr/io-error.hpp>

#include "internal/mmap-file-view-factory-impl.hpp"
#include "internal/utils.hpp"

namespace yactfr {
namespace internal {

class MemoryMappedFileView final :
    public DataSource
{
public:
    explicit MemoryMappedFileView(std::shared_ptr<internal::MmapFileViewFactoryImpl> mmapFileViewFactoryImpl);
    ~MemoryMappedFileView();

private:
    boost::optional<DataBlock> _data(Index offset, Size minSize) override;
    void _doMmap(Index offset);
    void _doMunmap();

private:
    std::shared_ptr<internal::MmapFileViewFactoryImpl> _mmapFileViewFactoryImpl;
    void *_mmapAddr = nullptr;
    Size _mmapLength = 0;
    Index _mmapOffset;
    std::array<std::uint8_t, 16> _tmpBuf;
};

MemoryMappedFileView::MemoryMappedFileView(std::shared_ptr<internal::MmapFileViewFactoryImpl> mmapFileViewFactoryImpl) :
    _mmapFileViewFactoryImpl {mmapFileViewFactoryImpl}
{
}

MemoryMappedFileView::~MemoryMappedFileView()
{
    this->_doMunmap();
}

boost::optional<DataBlock> MemoryMappedFileView::_data(const Index offset, const Size minSize)
{
    if ((offset + minSize) > _mmapFileViewFactoryImpl->fileSize()) {
        // no more data
        return boost::none;
    }

    if (!_mmapAddr) {
        // no current memory map
        this->_doMmap(offset);
    }

    if (offset < _mmapOffset || offset >= (_mmapOffset + _mmapLength)) {
        // requested offset is outside the current memory-mapped region
        this->_doMmap(offset);
    }

    assert(_mmapAddr);

    const auto offsetFromMmapOffset = offset - _mmapOffset;
    const void * const addr = static_cast<const void *>(static_cast<const std::uint8_t *>(_mmapAddr) + offsetFromMmapOffset);
    const auto availSize = _mmapLength - offsetFromMmapOffset;

    if (availSize < minSize) {
        /*
         * We don't have enough memory mapped data to satisfy the
         * requested minimum size.
         *
         * Copy the available data to our temporary buffer, perform a
         * new memory map operation to map the region just after the
         * current region, and append what's left to get `minSize` bytes
         * in the temporary buffer.
         */
        std::memcpy(_tmpBuf.data(), addr, availSize);
        this->_doMmap(_mmapOffset + _mmapLength);
        std::memcpy(_tmpBuf.data() + availSize, _mmapAddr, minSize - availSize);

        // return `minSize` bytes from our temporary buffer
        return DataBlock {static_cast<const void *>(_tmpBuf.data()), minSize};
    } else {
        return DataBlock {addr, availSize};
    }
}

void MemoryMappedFileView::_doMunmap()
{
    if (_mmapAddr) {
        munmap(_mmapAddr, static_cast<size_t>(_mmapLength));
        _mmapAddr = nullptr;
    }
}

void MemoryMappedFileView::_doMmap(const Index offset)
{
    this->_doMunmap();
    _mmapOffset = offset & ~(_mmapFileViewFactoryImpl->mmapOffsetGranularity() - 1);
    _mmapLength = std::min(_mmapFileViewFactoryImpl->fileSize() - _mmapOffset,
                           _mmapFileViewFactoryImpl->mmapSize());
    _mmapAddr = mmap(NULL, static_cast<size_t>(_mmapLength), PROT_READ,
                     MAP_PRIVATE, _mmapFileViewFactoryImpl->fd(),
                     static_cast<off_t>(_mmapOffset));

    if (_mmapAddr == MAP_FAILED) {
        const auto error = internal::strError();
        std::ostringstream ss;

        ss << "Cannot memory-map region [" << _mmapOffset << ", " <<
              (_mmapOffset + _mmapLength) << "[ of file \"" <<
              _mmapFileViewFactoryImpl->path() << "\": " << error;
        _mmapAddr = nullptr;
        throw IOError {ss.str()};
    }

    switch (_mmapFileViewFactoryImpl->accessPattern()) {
    case MemoryMappedFileViewFactory::AccessPattern::NORMAL:
        (void) madvise(_mmapAddr, static_cast<size_t>(_mmapLength), MADV_NORMAL);
        break;
    case MemoryMappedFileViewFactory::AccessPattern::SEQUENTIAL:
        (void) madvise(_mmapAddr, static_cast<size_t>(_mmapLength), MADV_SEQUENTIAL);
        break;
    case MemoryMappedFileViewFactory::AccessPattern::RANDOM:
        (void) madvise(_mmapAddr, static_cast<size_t>(_mmapLength), MADV_RANDOM);
        break;
    }
}

} // namespace internal

MemoryMappedFileViewFactory::MemoryMappedFileViewFactory(std::string path,
                                                         const boost::optional<Size>& preferredMmapSize,
                                                         const MemoryMappedFileViewFactory::AccessPattern accessPattern) :
    _pimpl {
        std::make_shared<internal::MmapFileViewFactoryImpl>(std::move(path), preferredMmapSize,
                                                            accessPattern)
    }
{
}

MemoryMappedFileViewFactory::AccessPattern MemoryMappedFileViewFactory::expectedAccessPattern() const noexcept
{
    return _pimpl->accessPattern();
}

void MemoryMappedFileViewFactory::expectedAccessPattern(const AccessPattern expectedAccessPattern) noexcept
{
    _pimpl->accessPattern(expectedAccessPattern);
}

DataSource::UP MemoryMappedFileViewFactory::_createDataSource()
{
    return std::make_unique<internal::MemoryMappedFileView>(_pimpl);
}

} // namespace yactfr
