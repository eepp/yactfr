#pragma once

#include <string>
#include <yactfr/aliases.hpp>
#include <yactfr/ds20-packet-view-factory.hpp>


namespace yactfr {
namespace internal {

class DS20PacketViewFactoryImpl final
{
public:
    explicit DS20PacketViewFactoryImpl(uint8_t *buffer, size_t bufferSize);
    ~DS20PacketViewFactoryImpl();

    Size _packetSize() const noexcept
    {
        return _bufferSize;
    }

    uint8_t* path() const noexcept
    {
        return _buffer;
    }

private:
    uint8_t *_buffer;
    Size _bufferSize;
};

} // namespace internal
} // namespace yactfr
