#include <sstream>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <yactfr/io-error.hpp>

#include "ds20-packet-view-factory-impl.hpp"
#include "utils.hpp"

namespace yactfr {
namespace internal {

DS20PacketViewFactoryImpl::DS20PacketViewFactoryImpl(const uint8_t *buffer, size_t bufferSize):
    _buffer {buffer},
    _bufferSize {bufferSize}
{
}

DS20PacketViewFactoryImpl::~DS20PacketViewFactoryImpl()
{
}

} // namespace internal
}
