/*
 * Element sequence.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/element-sequence.hpp>
#include <yactfr/metadata/trace-type.hpp>

namespace yactfr {


ElementSequence::ElementSequence(TraceType::SP traceType,
                               std::shared_ptr<DataSourceFactory> dataSourceFactory) :
    _traceType {traceType},
    _dataSourceFactory {dataSourceFactory}
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
    return ElementSequence::Iterator {_dataSourceFactory, _traceType, false};
}

ElementSequence::Iterator ElementSequence::end()
{
    return ElementSequence::Iterator {_dataSourceFactory, _traceType, true};
}

} // namespace yactfr
