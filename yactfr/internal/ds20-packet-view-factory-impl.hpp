#pragma once

#include <string>
#include <yactfr/aliases.hpp>
#include <yactfr/ds20-packet-view-factory.hpp>


namespace yactfr {
namespace internal {

class DS20PacketViewFactoryImpl final
{
public:
    explicit DS20PacketViewFactoryImpl(const uint8_t *buffer, size_t bufferSize);
    ~DS20PacketViewFactoryImpl();

    Size _packetSize(void) const noexcept
    {
        return _bufferSize;
    }

    const uint8_t* _PacketAddr(void) const noexcept
    {
        return _buffer;
    }

private:
    const uint8_t *_buffer;
    Size _bufferSize;
};

} // namespace internal
} // namespace yactfr
