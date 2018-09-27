/*
 * CTF data stream type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>
#include <sstream>

#include <yactfr/metadata/data-type.hpp>
#include <yactfr/metadata/data-stream-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/dynamic-array-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/trace-type.hpp>

#include "../utils.hpp"

namespace yactfr {

DataStreamType::DataStreamType(const TypeId id,
                               EventRecordTypeSet&& eventRecordTypes,
                               DataType::UP packetContextType,
                               DataType::UP eventRecordHeaderType,
                               DataType::UP eventRecordFirstContextType) :
    _id {id},
    _eventRecordTypes {std::move(eventRecordTypes)},
    _packetContextType {std::move(packetContextType)},
    _eventRecordHeaderType {std::move(eventRecordHeaderType)},
    _eventRecordFirstContextType {std::move(eventRecordFirstContextType)}
{
    utils::throwIfScopeTypeIsNotStruct(_packetContextType.get(),
                                       "Packet context");
    utils::throwIfScopeTypeIsNotStruct(_eventRecordHeaderType.get(),
                                       "Event record header");
    utils::throwIfScopeTypeIsNotStruct(_eventRecordFirstContextType.get(),
                                       "Event record second context");
    this->_buildErtMap();
    this->_validate();
}

void DataStreamType::_buildErtMap()
{
    for (auto& ertUp : _eventRecordTypes) {
        if (_idsToEventRecordTypes.find(ertUp->id()) != std::end(_idsToEventRecordTypes)) {
            std::ostringstream ss;

            ss << "Invalid data stream type: duplicate event record type " <<
                  "with ID " << ertUp->id() << ".";
            throw InvalidMetadata {ss.str()};
        }

        _idsToEventRecordTypes[ertUp->id()] = ertUp.get();
    }
}

const EventRecordType *DataStreamType::operator[](const TypeId id) const
{
    auto it = _idsToEventRecordTypes.find(id);

    if (it == std::end(_idsToEventRecordTypes)) {
        return nullptr;
    }

    return it->second;
}

void DataStreamType::_validate() const
{
    const DataType *idType = nullptr;

    if (_eventRecordHeaderType && _eventRecordHeaderType->isStructType()) {
        idType = _eventRecordHeaderType->asStructType()->findTypeByDisplayName("id");
    }

    if (this->eventRecordTypes().size() > 1) {
        // more than one event: event header ID field must exist
        if (!_eventRecordHeaderType) {
            throw InvalidMetadata {
                "Invalid data stream type: expecting event header type since "
                "this data stream type contains more than one event record types."
            };
        }

        if (!idType) {
            throw InvalidMetadata {
                "Invalid data stream type: expecting at least one `id` field in "
                "event header type since this data stream type contains more "
                "than one event record type."
            };
        }
    }

    if (idType && !idType->isUnsignedIntType()) {
        throw InvalidMetadata {
            "Invalid data stream type: expecting unsigned integer type "
            "as `id` field of event header type."
        };
    }

    if (_packetContextType && _packetContextType->isStructType()) {
        auto pcType = _packetContextType->asStructType();
        auto pktSizeType = pcType->findTypeByDisplayName("packet_size");

        // `packet_size` field must have an unsigned integer type
        if (pktSizeType && !pktSizeType->isUnsignedIntType()) {
            throw InvalidMetadata {
                "Invalid data stream type: expecting unsigned integer type "
                "as `packet_size` field of packet context type."
            };
        }

        auto ctSizeType = pcType->findTypeByDisplayName("content_size");

        // `content_size` field must have an unsigned integer type
        if (ctSizeType && !ctSizeType->isUnsignedIntType()) {
            throw InvalidMetadata {
                "Invalid data stream type: expecting unsigned integer type "
                "as `content_size` field of packet context type."
            };
        }
    }

    for (auto& ertUp : _eventRecordTypes) {
        this->_validateEventRecordType(*ertUp);
    }
}

void DataStreamType::_validateEventRecordType(const EventRecordType& eventRecordType) const
{
    // make sure the event is not empty
    bool ehEmpty = this->_isTypeEmpty(this->eventRecordHeaderType());
    bool ecEmpty = this->_isTypeEmpty(this->eventRecordFirstContextType());
    bool cEmpty = this->_isTypeEmpty(eventRecordType.secondContextType());
    bool pEmpty = this->_isTypeEmpty(eventRecordType.payloadType());

    if (ehEmpty && ecEmpty && cEmpty && pEmpty) {
        std::ostringstream ss;

        ss << "Event record type " << eventRecordType.id() << " is empty.";

        throw InvalidMetadata {ss.str()};
    }
}

bool DataStreamType::_isTypeEmpty(const DataType* type) const
{
    if (!type) {
        return true;
    }

    if (type->isStructType()) {
        bool allEmpty = true;

        for (const auto& field : *type->asStructType()) {
            if (!this->_isTypeEmpty(&field->type())) {
                allEmpty = false;
                break;
            }
        }

        if (allEmpty) {
            return true;
        }
    }

    if (type->isStaticArrayType()) {
        if (type->asStaticArrayType()->length() == 0) {
            return true;
        }

        if (this->_isTypeEmpty(&type->asArrayType()->elemType())) {
            return true;
        }
    }

    if (type->isDynamicArrayType()) {
        if (this->_isTypeEmpty(&type->asArrayType()->elemType())) {
            return true;
        }
    }

    return false;
}

const DataType *DataStreamType::findDataType(const FieldRef& ref) const
{
    const DataType *scopeType = nullptr;

    if (_traceType) {
        const auto ft = _traceType->findDataType(ref);

        if (ft) {
            return ft;
        }
    }

    switch (ref.scope()) {
    case Scope::PACKET_CONTEXT:
        scopeType = this->packetContextType();
        break;

    case Scope::EVENT_RECORD_HEADER:
        scopeType = this->eventRecordHeaderType();
        break;

    case Scope::EVENT_RECORD_FIRST_CONTEXT:
        scopeType = this->eventRecordFirstContextType();
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

void DataStreamType::_setTraceType(const TraceType *traceType) const
{
    _traceType = traceType;
}

} // namespace yactfr
