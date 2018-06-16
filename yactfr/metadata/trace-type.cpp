/*
 * CTF trace type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <functional>
#include <cstdlib>

#ifndef NDEBUG
# include <iostream>
#endif

#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/array-type.hpp>
#include <yactfr/metadata/sequence-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/trace-type-env.hpp>
#include <yactfr/aliases.hpp>

#include "trace-type-impl.hpp"
#include "field-resolver.hpp"
#include "../proc.hpp"
#include "../packet-proc-builder.hpp"
#include "../utils.hpp"

namespace yactfr {

TraceType::TraceType(const unsigned int majorVersion,
                     const unsigned int minorVersion,
                     const boost::optional<boost::uuids::uuid>& uuid,
                     DataType::UP packetHeaderType,
                     std::unique_ptr<const TraceTypeEnv> env,
                     ClockTypeSet&& clockTypes,
                     DataStreamTypeSet&& dataStreamTypes) :
    _pimpl {
        std::make_unique<internal::TraceTypeImpl>(majorVersion, minorVersion, uuid,
                                                  std::move(packetHeaderType),
                                                  std::move(env),
                                                  std::move(clockTypes),
                                                  std::move(dataStreamTypes),
                                                  this)
    }
{
#ifndef NDEBUG
    const auto var = std::getenv("YACTFR_DEBUG_PRINT_PROC");

    if (var && std::strcmp(var, "1") == 0) {
        auto& packetProc = _pimpl->packetProc();
        std::cout << packetProc.toString(0) << std::endl;
    }
#endif
}

TraceType::~TraceType()
{
}

unsigned int TraceType::majorVersion() const noexcept
{
    return _pimpl->majorVersion();
}

unsigned int TraceType::minorVersion() const noexcept
{
    return _pimpl->minorVersion();
}

const boost::optional<boost::uuids::uuid>& TraceType::uuid() const noexcept
{
    return _pimpl->uuid();
}

const TraceTypeEnv& TraceType::env() const noexcept
{
    return _pimpl->env();
}

const DataType* TraceType::packetHeaderType() const noexcept
{
    return _pimpl->packetHeaderType();
}

const ClockTypeSet& TraceType::clockTypes() const noexcept
{
    return _pimpl->clockTypes();
}

const DataStreamTypeSet& TraceType::dataStreamTypes() const noexcept
{
    return _pimpl->dataStreamTypes();
}

const DataStreamType *TraceType::operator[](const TypeId id) const
{
    return _pimpl->findDataStreamType(id);
}

const ClockType *TraceType::findClockType(const std::string& name) const
{
    return _pimpl->findClockType(name);
}

DataStreamTypeSet::const_iterator TraceType::begin() const noexcept
{
    return std::begin(_pimpl->dataStreamTypes());
}

DataStreamTypeSet::const_iterator TraceType::end() const noexcept
{
    return std::end(_pimpl->dataStreamTypes());
}

const DataType *TraceType::findDataType(const FieldRef& ref) const
{
    if (ref.scope() != Scope::PACKET_HEADER) {
        return nullptr;
    }

    auto scopeType = this->packetHeaderType();

    if (!scopeType) {
        return nullptr;
    }

    return utils::findType(scopeType, std::begin(ref.pathElements()),
                           std::end(ref.pathElements()));
}

} // namespace yactfr
