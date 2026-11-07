/*
 * SPDX-FileCopyrightText: 2016-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/elem-seq.hpp>
#include <yactfr/metadata/trace-type.hpp>

namespace yactfr {


ElementSequence::ElementSequence(const TraceType& traceType, DataSourceFactory& dataSrcFactory) :
    _traceType {&traceType},
    _dataSrcFactory {&dataSrcFactory}
{
}

ElementSequence::Iterator ElementSequence::at(const Index offset)
{
    auto it = this->begin();

    it.seekPacket(offset);
    return it;
}

ElementSequence::Iterator ElementSequence::begin()
{
    return ElementSequence::Iterator {*_dataSrcFactory, *_traceType};
}

} // namespace yactfr
