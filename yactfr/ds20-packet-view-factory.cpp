/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstring>
#include <cstdint>
#include <sstream>
#include <array>
#include <sys/mman.h>

#include <yactfr/ds20-packet-view-factory.hpp>
#include <yactfr/io-error.hpp>

#include "internal/ds20-packet-view-factory-impl.hpp"
#include "internal/utils.hpp"

namespace yactfr {
namespace internal {

class DS20PacketView final :
    public DataSource
{
public:
    explicit DS20PacketView(std::shared_ptr<internal::DS20PacketViewFactoryImpl> ds20PacketViewFactoryImpl);
    ~DS20PacketView();

private:
    boost::optional<DataBlock> _data(Index offset, Size minSize) override;

private:
    std::shared_ptr<internal::DS20PacketViewFactoryImpl> _ds20PacketViewFactoryImpl;
    uint8_t *_packetAddr = NULL;
    Size _packetLength = 0;
    Index _packetOffset = 0;
    std::array<std::uint8_t, 16> _tmpBuf;
};

DS20PacketView::DS20PacketView(std::shared_ptr<internal::DS20PacketViewFactoryImpl> ds20PacketViewFactoryImpl) :
    _ds20PacketViewFactoryImpl {ds20PacketViewFactoryImpl}
{
}

DS20PacketView::~DS20PacketView()
{
}

boost::optional<DataBlock> DS20PacketView::_data(const Index offset, const Size minSize)
{

    if ((offset + minSize) > _ds20PacketViewFactoryImpl->_packetSize()) {
        // no more data
        return boost::none;
    }

    assert(_packetAddr);

    const auto offsetFromEndPacket = offset - _packetLength;
    const void * const addr = static_cast<const void *>(static_cast<const std::uint8_t *>(_packetAddr) + offsetFromEndPacket);
    const auto availSize = _packetLength - offsetFromEndPacket;

// This should not be happening
#if 0
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
        std::memcpy(_tmpBuf.data() + availSize, _mmapAddr, minSize - availSize);

        // return `minSize` bytes from our temporary buffer
        return DataBlock {static_cast<const void *>(_tmpBuf.data()), minSize};
    } else {
        return DataBlock {addr, availSize};
    }
#endif
        return DataBlock {addr, availSize};
}

} // namespace internal

DS20PacketViewFactory::DS20PacketViewFactory(uint8_t *buffer, size_t bufferSize):
    _pimpl {
        std::make_shared<internal::DS20PacketViewFactoryImpl>(buffer, bufferSize)
    }
{
}

DataSource::UP DS20PacketViewFactory::_createDataSource()
{
    return std::make_unique<internal::DS20PacketView>(_pimpl);
}

} // namespace yactfr
