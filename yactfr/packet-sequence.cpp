/*
 * Packet sequence.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/packet-sequence.hpp>
#include <yactfr/metadata/trace-type.hpp>

namespace yactfr {


PacketSequence::PacketSequence(TraceType::SP traceType,
                               std::shared_ptr<DataSourceFactory> dataSourceFactory) :
    _traceType {traceType},
    _dataSourceFactory {dataSourceFactory}
{
}

PacketSequence::Iterator PacketSequence::at(const Index offset)
{
    auto it = this->begin();
    it.seekPacket(offset);
    return it;
}

PacketSequence::Iterator PacketSequence::begin()
{
    return PacketSequence::Iterator {_dataSourceFactory, _traceType, false};
}

PacketSequence::Iterator PacketSequence::end()
{
    return PacketSequence::Iterator {_dataSourceFactory, _traceType, true};
}

} // namespace yactfr
