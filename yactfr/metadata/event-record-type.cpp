/*
 * CTF event record type.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>
#include <sstream>

#include <yactfr/metadata/field-ref.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/data-stream-type.hpp>
#include <yactfr/metadata/event-record-type.hpp>

#include "../utils.hpp"

namespace yactfr {

EventRecordType::EventRecordType(const TypeId id,
                                 const boost::optional<std::string>& name,
                                 const boost::optional<LogLevel>& logLevel,
                                 const boost::optional<std::string>& modelEmfUri,
                                 std::unique_ptr<const DataType> secondContextType,
                                 std::unique_ptr<const DataType> payloadType) :
    _id {id},
    _name {name},
    _logLevel {logLevel},
    _modelEmfUri {modelEmfUri},
    _secondContextType {std::move(secondContextType)},
    _payloadType {std::move(payloadType)}
{
    utils::throwIfScopeTypeIsNotStruct(_secondContextType.get(),
                                       "Event record second context");
    utils::throwIfScopeTypeIsNotStruct(_payloadType.get(),
                                       "Event record payload");
}

const DataType *EventRecordType::findDataType(const FieldRef& ref) const
{
    const DataType *scopeType = nullptr;

    if (_dataStreamType) {
        const auto ft = _dataStreamType->findDataType(ref);

        if (ft) {
            return ft;
        }
    }

    switch (ref.scope()) {
    case Scope::EVENT_RECORD_SECOND_CONTEXT:
        scopeType = this->secondContextType();
        break;

    case Scope::EVENT_RECORD_PAYLOAD:
        scopeType = this->payloadType();
        break;

    default:
        return nullptr;
    }

    if (!scopeType) {
        return nullptr;
    }

    return utils::findType(scopeType, std::begin(ref.pathElements()),
                           std::end(ref.pathElements()));
}

void EventRecordType::_setDataStreamType(const DataStreamType *dataStreamType) const
{
    _dataStreamType = dataStreamType;
}

} // namespace yactfr
