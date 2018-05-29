/*
 * CTF trace type implementation.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_TRACE_TYPE_IMPL_HPP
#define _YACTFR_METADATA_TRACE_TYPE_IMPL_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <functional>

#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/aliases.hpp>

#include "field-resolver.hpp"
#include "../proc.hpp"
#include "../utils.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl
{
public:
    TraceTypeImpl(const unsigned int majorVersion,
                  const unsigned int minorVersion,
                  const boost::optional<boost::uuids::uuid>& uuid,
                  DataType::UP packetHeaderType,
                  std::unique_ptr<const TraceTypeEnv> env,
                  ClockTypeSet&& clockTypes,
                  DataStreamTypeSet&& dataStreamTypes,
                  const TraceType *traceType);

    unsigned int majorVersion() const noexcept
    {
        return _majorVersion;
    }

    unsigned int minorVersion() const noexcept
    {
        return _minorVersion;
    }

    const boost::optional<boost::uuids::uuid>& uuid() const noexcept
    {
        return _uuid;
    }

    const DataType *packetHeaderType() const noexcept
    {
        return _packetHeaderType.get();
    }

    const TraceTypeEnv& env() const noexcept
    {
        return *_env;
    }

    const ClockTypeSet& clockTypes() const noexcept
    {
        return _clockTypes;
    }

    const DataStreamTypeSet& dataStreamTypes() const noexcept
    {
        return _dataStreamTypes;
    }

    const DataStreamType *findDataStreamType(TypeId id) const;
    const ClockType *findClockType(const std::string& name) const;

    /*
     * It is safe to keep a pointer to the returned object as long as
     * this trace type lives.
     */
    const PacketProc& packetProc() const;

private:
    struct _StackFrame
    {
        const DataType *parentType;
        Index curChildIndex;
    };

private:
    void _buildDstMap();
    void _validate(const TraceType *traceType);
    void _validateSpecialFields();
    void _resolveDynamicTypes();
    void _resolveDynamicTypesInScope(const Scope scope, const DataType *type,
                                     const FieldResolver& fieldResolver);
    void _resolveDynamicTypeInScope(const Scope scope, const DataType *type,
                                    const FieldResolver& fieldResolver);
    void _validateVariantTypeTagType(const DataType *variantType,
                                     const DataType *tagType);
    FieldResolver::Entry _getEntryAt(const Scope scope,
                                     const FieldResolver::Position& pos);
    void _stackPush(const _StackFrame& frame);
    void _stackPop();
    _StackFrame& _stackTop();
    FieldResolver::Position _curPos();
    void _validateMappedClockTypeName(const DataType *type);
    void _validateMappedClockTypeNames();
    void _validateUniqueClockTypes();
    void _createParentLinks(const TraceType *traceType);

private:
    const unsigned int _majorVersion;
    const unsigned int _minorVersion;
    const boost::optional<boost::uuids::uuid> _uuid;
    DataType::UP _packetHeaderType;
    std::unique_ptr<const TraceTypeEnv> _env;
    const ClockTypeSet _clockTypes;
    const DataStreamTypeSet _dataStreamTypes;
    std::unordered_map<TypeId, const DataStreamType *> _idsToDataStreamTypes;
    const TraceType *_traceType;

    // packet procedure cache; created the first time we need it
    mutable std::unique_ptr<const PacketProc> _packetProc;

    struct {
        const DataType *packetHeaderType;
        const DataType *packetContextType;
        const DataType *eventRecordHeaderType;
        const DataType *eventRecordFirstContextType;
        const DataType *eventRecordSecondContextType;
        const DataType *eventRecordPayloadType;
        std::vector<_StackFrame> stack;
    } _resolveState;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_TRACE_TYPE_IMPL_HPP
