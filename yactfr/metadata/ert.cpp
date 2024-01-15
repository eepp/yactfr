/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>
#include <sstream>

#include <yactfr/metadata/data-loc.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/ert.hpp>

namespace yactfr {

EventRecordType::EventRecordType(const TypeId id, boost::optional<std::string> ns,
                                 boost::optional<std::string> name,
                                 boost::optional<std::string> uid,
                                 boost::optional<LogLevel> logLevel,
                                 boost::optional<std::string> emfUri,
                                 StructureType::UP specCtxType, StructureType::UP payloadType,
                                 MapItem::UP attrs) :
    _id {id},
    _ns {std::move(ns)},
    _name {std::move(name)},
    _uid {std::move(uid)},
    _logLevel {std::move(logLevel)},
    _emfUri {std::move(emfUri)},
    _specCtxType {std::move(specCtxType)},
    _payloadType {std::move(payloadType)},
    _attrs {std::move(attrs)}
{
}

void EventRecordType::_setDst(const DataStreamType& dst) const noexcept
{
    _dst = &dst;
}

} // namespace yactfr
