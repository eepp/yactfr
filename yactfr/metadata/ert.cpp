/*
 * SPDX-FileCopyrightText: 2016-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <string>

#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/ert.hpp>

namespace yactfr {

EventRecordType::EventRecordType(const TypeId id, std::optional<std::string> ns,
                                 std::optional<std::string> name,
                                 std::optional<std::string> uid,
                                 std::optional<LogLevel> logLevel,
                                 std::optional<std::string> emfUri,
                                 StructureType::Up specCtxType, StructureType::Up payloadType,
                                 MapItem::Up attrs) :
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
