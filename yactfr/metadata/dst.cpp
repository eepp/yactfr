/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>
#include <sstream>

#include <yactfr/metadata/data-loc.hpp>
#include <yactfr/metadata/dt.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/trace-type.hpp>

namespace yactfr {

DataStreamType::DataStreamType(const TypeId id, boost::optional<std::string> ns,
                               boost::optional<std::string> name, EventRecordTypeSet&& erts,
                               StructureType::UP pktCtxType, StructureType::UP erHeaderType,
                               StructureType::UP erCommonCtxType,
                               const ClockType * const defClkType, MapItem::UP userAttrs) :
    _id {id},
    _ns {std::move(ns)},
    _name {std::move(name)},
    _erts {std::move(erts)},
    _pktCtxType {std::move(pktCtxType)},
    _erHeaderType {std::move(erHeaderType)},
    _erCommonCtxType {std::move(erCommonCtxType)},
    _defClkType {defClkType},
    _userAttrs {std::move(userAttrs)}
{
    this->_buildErtMap();
    // TODO: Add validation.
}

DataStreamType::DataStreamType(const TypeId id, EventRecordTypeSet&& erts,
                               StructureType::UP pktCtxType, StructureType::UP erHeaderType,
                               StructureType::UP erCommonCtxType,
                               const ClockType * const defClkType, MapItem::UP userAttrs) :
    DataStreamType {
        id, boost::none, boost::none, std::move(erts),
        std::move(pktCtxType), std::move(erHeaderType), std::move(erCommonCtxType),
        defClkType, std::move(userAttrs)
    }
{
    this->_buildErtMap();
    // TODO: Add validation.
}

void DataStreamType::_buildErtMap()
{
    for (auto& ertUp : _erts) {
        _idsToErts[ertUp->id()] = ertUp.get();
    }
}

const EventRecordType *DataStreamType::operator[](const TypeId id) const
{
    const auto it = _idsToErts.find(id);

    if (it == _idsToErts.end()) {
        return nullptr;
    }

    return it->second;
}

void DataStreamType::_setTraceType(const TraceType& traceType) const
{
    _traceType = &traceType;
}

} // namespace yactfr
