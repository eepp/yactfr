/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TESTS_MEM_DATA_SRC_FACTORY_HPP
#define _YACTFR_TESTS_MEM_DATA_SRC_FACTORY_HPP

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <limits>

#include <yactfr/data-src-factory.hpp>

class MemDataSrcFactory;

class MemDataSrc :
    public yactfr::DataSource
{
    friend class MemDataSrcFactory;

private:
    explicit MemDataSrc(const std::uint8_t * const addr, const std::size_t size,
                        const std::size_t maxDataBlkSize) :
        _addr {addr},
        _size {size},
        _maxDataBlkSize {maxDataBlkSize}
    {
    }

    boost::optional<yactfr::DataBlock> _data(const yactfr::Index offset,
                                             const yactfr::Size minSize) override
    {
        if (offset >= _size) {
            return boost::none;
        }

        const auto blockSize = std::max(minSize, static_cast<yactfr::Size>(_maxDataBlkSize));

        return yactfr::DataBlock {
            static_cast<const void *>(_addr + offset),
            std::min(_size - offset, blockSize)
        };
    }

private:
    const std::uint8_t * const _addr;
    const std::size_t _size;
    const std::size_t _maxDataBlkSize;
};

class MemDataSrcFactory :
    public yactfr::DataSourceFactory
{
public:
    explicit MemDataSrcFactory(const std::uint8_t * const addr, const std::size_t size,
                               const std::size_t maxDataBlkSize = std::numeric_limits<std::size_t>::max()) :
        _addr {addr},
        _size {size},
        _maxDataBlkSize {maxDataBlkSize}
    {
    }

private:
    yactfr::DataSource::UP _createDataSource() override
    {
        return yactfr::DataSource::UP {
            new MemDataSrc {_addr, _size, _maxDataBlkSize}
        };
    }

private:
    const std::uint8_t * const _addr;
    const std::size_t _size;
    const std::size_t _maxDataBlkSize;
};

#endif // _YACTFR_TESTS_MEM_DATA_SRC_FACTORY_HPP
