/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
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
    return ElementSequence::Iterator {*_dataSrcFactory, *_traceType, false};
}

ElementSequence::Iterator ElementSequence::end() noexcept
{
    return ElementSequence::Iterator {*_dataSrcFactory, *_traceType, true};
}

} // namespace yactfr
