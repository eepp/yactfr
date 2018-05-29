/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TESTS_MEM_DATA_SOURCE_FACTORY_HPP
#define _YACTFR_TESTS_MEM_DATA_SOURCE_FACTORY_HPP

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <limits>

#include <yactfr/data-source-factory.hpp>

class MemDataSourceFactory;

class MemDataSource :
    public yactfr::DataSource
{
    friend class MemDataSourceFactory;

private:
    MemDataSource(const std::uint8_t * const addr, const std::size_t size,
                  const std::size_t maxDataBlockSize) :
        _addr {addr},
        _size {size},
        _maxDataBlockSize {maxDataBlockSize}
    {
    }

    boost::optional<yactfr::DataBlock> _data(const yactfr::Index offset,
                                             const yactfr::Size minSize) override
    {
        if (offset >= _size) {
            return boost::none;
        }

        const auto blockSize = std::max(minSize,
                                        static_cast<yactfr::Size>(_maxDataBlockSize));

        return yactfr::DataBlock {
            static_cast<const void *>(_addr + offset),
            std::min(_size - offset, blockSize)
        };
    }

private:
    const std::uint8_t * const _addr;
    const std::size_t _size;
    const std::size_t _maxDataBlockSize;
};

class MemDataSourceFactory :
    public yactfr::DataSourceFactory
{
public:
    MemDataSourceFactory(const std::uint8_t * const addr, const std::size_t size,
                         const std::size_t maxDataBlockSize = std::numeric_limits<std::size_t>::max()) :
        _addr {addr},
        _size {size},
        _maxDataBlockSize {maxDataBlockSize}
    {
    }

private:
    yactfr::DataSource::UP _createDataSource() override
    {
        return yactfr::DataSource::UP {
            new MemDataSource {_addr, _size, _maxDataBlockSize}
        };
    }

private:
    const std::uint8_t * const _addr;
    const std::size_t _size;
    const std::size_t _maxDataBlockSize;
};

#endif // _YACTFR_TESTS_MEM_DATA_SOURCE_FACTORY_HPP
