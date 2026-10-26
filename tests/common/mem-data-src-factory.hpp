/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_TESTS_MEM_DATA_SRC_FACTORY_HPP
#define YACTFR_TESTS_MEM_DATA_SRC_FACTORY_HPP

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <limits>

#include <yactfr/data-src.hpp>
#include <yactfr/data-src-factory.hpp>

class MemDataSrcFactory;

class MemDataSrc :
    public yactfr::DataSource
{
    friend class MemDataSrcFactory;

private:
    explicit MemDataSrc(const std::uint8_t * const addr, const std::size_t size,
                        const std::size_t maxDataBlkSize, bool * const dataNotAvail) :
        _addr {addr},
        _size {size},
        _maxDataBlkSize {maxDataBlkSize},
        _dataNotAvail {dataNotAvail}
    {
    }

    boost::optional<yactfr::DataBlock> _data(const yactfr::Index offset,
                                             const yactfr::Size minSize) override
    {
        if (_dataNotAvail) {
            *_dataNotAvail = !*_dataNotAvail;

            if (*_dataNotAvail) {
                // try again later
                throw yactfr::DataNotAvailable {};
            }
        }

        if (offset + minSize > _size) {
            // not enough data
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

    // shared with the factory; null if always available
    bool * const _dataNotAvail;
};

/*
 * Factory of data sources which return data blocks of at most
 * `maxDataBlkSize` bytes from memory.
 *
 * If `dataNotAvailEveryOtherCall` is true, then the data sources throw
 * `yactfr::DataNotAvailable` every other time the VM requests data,
 * starting with the first request. The factory keeps this state so
 * that retrying with a new data source (for example, calling
 * yactfr::ElementSequence::begin() again) eventually succeeds.
 */
class MemDataSrcFactory :
    public yactfr::DataSourceFactory
{
public:
    explicit MemDataSrcFactory(const std::uint8_t * const addr, const std::size_t size,
                               const std::size_t maxDataBlkSize = std::numeric_limits<std::size_t>::max(),
                               const bool dataNotAvailEveryOtherCall = false) :
        _addr {addr},
        _size {size},
        _maxDataBlkSize {maxDataBlkSize},
        _dataNotAvailEveryOtherCall {dataNotAvailEveryOtherCall}
    {
    }

private:
    yactfr::DataSource::Up _createDataSource() override
    {
        return yactfr::DataSource::Up {
            new MemDataSrc {
                _addr, _size, _maxDataBlkSize,
                _dataNotAvailEveryOtherCall ? &_dataNotAvail : nullptr
            }
        };
    }

private:
    const std::uint8_t * const _addr;
    const std::size_t _size;
    const std::size_t _maxDataBlkSize;
    const bool _dataNotAvailEveryOtherCall;
    bool _dataNotAvail = false;
};

#endif // YACTFR_TESTS_MEM_DATA_SRC_FACTORY_HPP
