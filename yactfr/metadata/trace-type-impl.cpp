/*
 * CTF trace type implementation.
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

#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/dynamic-array-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/trace-type-env.hpp>
#include <yactfr/metadata/io.hpp>
#include <yactfr/aliases.hpp>

#include "trace-type-impl.hpp"
#include "field-resolver.hpp"
#include "../proc.hpp"
#include "../packet-proc-builder.hpp"
#include "../utils.hpp"

namespace yactfr {
namespace internal {

TraceTypeImpl::TraceTypeImpl(const unsigned int majorVersion,
                             const unsigned int minorVersion,
                             const boost::optional<boost::uuids::uuid>& uuid,
                             DataType::UP packetHeaderType,
                             std::unique_ptr<const TraceTypeEnv> env,
                             ClockTypeSet&& clockTypes,
                             DataStreamTypeSet&& dataStreamTypes,
                             const TraceType *traceType) :
    _majorVersion {majorVersion},
    _minorVersion {minorVersion},
    _uuid {uuid},
    _packetHeaderType {std::move(packetHeaderType)},
    _env {env ? std::move(env) : std::make_unique<const TraceTypeEnv>()},
    _clockTypes {std::move(clockTypes)},
    _dataStreamTypes {std::move(dataStreamTypes)},
    _traceType {traceType}
{
    utils::throwIfScopeTypeIsNotStruct(_packetHeaderType.get(),
                                       "Packet header");
    this->_buildDstMap();
    this->_validate(traceType);
}

void TraceTypeImpl::_buildDstMap()
{
    for (auto& dstUp : _dataStreamTypes) {
        if (_idsToDataStreamTypes.find(dstUp->id()) != std::end(_idsToDataStreamTypes)) {
            std::ostringstream ss;

            ss << "Invalid trace type: duplicate data stream type with ID " <<
                  dstUp->id() << ".";
            throw InvalidMetadata {ss.str()};
        }

        _idsToDataStreamTypes[dstUp->id()] = dstUp.get();
    }
}

/*
 * TODO:
 *
 * * Validate that all variant and dynamic array FTs point to something
 *   that COULD exist at read time.
 */
void TraceTypeImpl::_validate(const TraceType *traceType)
{
    this->_validateSpecialFields();
    this->_validateUniqueClockTypes();
    this->_validateMappedClockTypeNames();
    this->_createParentLinks(traceType);
    this->_resolveDynamicTypes();
}

void TraceTypeImpl::_validateSpecialFields()
{
    if (_packetHeaderType && _packetHeaderType->isStructType()) {
        auto pktType = _packetHeaderType->asStructType();

        // validate `magic` field
        auto magicType = pktType->findTypeByDisplayName("magic");

        if (magicType) {
            if (!magicType->isUnsignedIntType() || magicType->asIntType()->size() != 32) {
                throw InvalidMetadata {
                    "Invalid trace type: expecting 32-bit unsigned integer "
                    "type as `magic` field of packet header type."
                };
            }

            // must be the first field
            const auto& firstField = (*pktType)[0];

            // use name because integer field type pointer is probably shared
            if (firstField.displayName() != "magic") {
                throw InvalidMetadata {
                    "Invalid trace type: the packet header type's "
                    "`magic` field, when it exists, must be the first field."
                };
            }
        }

        // validate `stream_id`
        auto streamIdType = pktType->findTypeByDisplayName("stream_id");

        if (streamIdType && !streamIdType->isUnsignedIntType()) {
            throw InvalidMetadata {
                "Invalid trace type: expecting unsigned integer type "
                "as `stream_id` field of packet header type."
            };
        }

        // validate `stream_instance_id`
        auto streamInstIdType = pktType->findTypeByDisplayName("stream_instance_id");

        if (streamInstIdType && !streamInstIdType->isUnsignedIntType()) {
            throw InvalidMetadata {
                "Invalid trace type: expecting unsigned integer type "
                "as `stream_instance_id` field of "
                "packet header type."
            };
        }

        // validate `uuid`
        auto uuidType = pktType->findTypeByDisplayName("uuid");

        if (uuidType) {
            if (!uuidType->isArrayType()) {
                throw InvalidMetadata {
                    "Invalid trace type: expecting array "
                    "type as `uuid` field of packet header type."
                };
            }

            auto uuidArrayFt = uuidType->asStaticArrayType();

            if (!uuidArrayFt || uuidArrayFt->length() != 16 ||
                    !uuidArrayFt->elemType().isUnsignedIntType() ||
                    uuidArrayFt->elemType().asIntType()->size() != 8 ||
                    uuidArrayFt->elemType().asIntType()->alignment() != 8) {
                throw InvalidMetadata {
                    "Invalid trace type: expecting array "
                    "type of 16 8-bit aligned, 8-bit unsigned integer "
                    "types as `uuid` field of packet header type."
                };
            }

            if (!_uuid) {
                throw InvalidMetadata {
                    "Invalid trace type: packet header type contains a "
                    "UUID field, but trace type has no UUID."
                };
            }
        }
    }

    if (_dataStreamTypes.size() > 1) {
        // check that `stream_id` exists in the packet header type
        if (!_packetHeaderType) {
            throw InvalidMetadata {
                "Invalid trace type: expecting a packet header type "
                "since this trace type contains more than one data stream type."
            };
        }

        if (_packetHeaderType->isStructType()) {
            auto streamIdType = _packetHeaderType->asStructType()->findTypeByDisplayName("stream_id");

            if (!streamIdType) {
                throw InvalidMetadata {
                    "Invalid trace type: expecting `stream_id` field in packet "
                    "header type since this trace type contains more than "
                    "one data stream type."
                };
            }
        }
    }
}

void TraceTypeImpl::_validateUniqueClockTypes()
{
    for (auto& clkTypeUp : _clockTypes) {
        if (_clockTypes.count(clkTypeUp) != 1) {
            std::ostringstream ss;

            ss << "Invalid trace type: duplicate clock type with name `" <<
                  clkTypeUp->name() << "`.";
            throw InvalidMetadata {ss.str()};
        }
    }
}

void TraceTypeImpl::_stackPush(const _StackFrame& frame)
{
    _resolveState.stack.push_back(frame);
}

void TraceTypeImpl::_stackPop()
{
    assert(!_resolveState.stack.empty());
    _resolveState.stack.pop_back();
}

TraceTypeImpl::_StackFrame& TraceTypeImpl::_stackTop()
{
    assert(!_resolveState.stack.empty());
    return _resolveState.stack.back();
}

FieldResolver::Entry TraceTypeImpl::_getEntryAt(const Scope scope,
                                                const FieldResolver::Position& pos)
{
    FieldResolver::Entry entry;

    if (scope == Scope::PACKET_HEADER) {
        entry.type = _resolveState.packetHeaderType;
    } else if (scope == Scope::PACKET_CONTEXT) {
        entry.type = _resolveState.packetContextType;
    } else if (scope == Scope::EVENT_RECORD_HEADER) {
        entry.type = _resolveState.eventRecordHeaderType;
    } else if (scope == Scope::EVENT_RECORD_FIRST_CONTEXT) {
        entry.type = _resolveState.eventRecordFirstContextType;
    } else if (scope == Scope::EVENT_RECORD_SECOND_CONTEXT) {
        entry.type = _resolveState.eventRecordSecondContextType;
    } else if (scope == Scope::EVENT_RECORD_PAYLOAD) {
        entry.type = _resolveState.eventRecordPayloadType;
    }

    if (!entry.type) {
        return FieldResolver::Entry {};
    }

    auto indexToCheckIt = std::begin(pos);

    while (indexToCheckIt != std::end(pos)) {
        if (entry.type->isStructType()) {
            auto structType = entry.type->asStructType();

            if (!structType->hasField(*indexToCheckIt)) {
                return FieldResolver::Entry {};
            }

            auto& field = (*structType)[*indexToCheckIt];

            entry.type = &field.type();
            entry.name = &field.name();
        } else if (entry.type->isVariantType()) {
            auto variantType = entry.type->asVariantType();

            if (!variantType->hasOption(*indexToCheckIt)) {
                return FieldResolver::Entry {};
            }

            auto& option = (*variantType)[*indexToCheckIt];

            entry.type = &option.type();
            entry.name = &option.name();
        } else if (entry.type->isArrayType()) {
            auto arrayType = entry.type->asArrayType();

            if (*indexToCheckIt != -1ULL) {
                return FieldResolver::Entry {};
            }

            entry.type = &arrayType->elemType();
            entry.name = nullptr;
        } else if (entry.type->isDynamicArrayType()) {
            auto seqType = entry.type->asDynamicArrayType();

            if (*indexToCheckIt != -1ULL) {
                return FieldResolver::Entry {};
            }

            entry.type = &seqType->elemType();
            entry.name = nullptr;
        } else {
            return FieldResolver::Entry {};
        }

        ++indexToCheckIt;
    }

    return entry;
}

FieldResolver::Position TraceTypeImpl::_curPos()
{
    FieldResolver::Position pos;

    for (const auto& frame : _resolveState.stack) {
        pos.push_back(frame.curChildIndex);
    }

    return pos;
}

const ClockType *TraceTypeImpl::findClockType(const std::string& name) const
{
    // decadent linear search
    for (auto& clockTypeUp : _clockTypes) {
        if (clockTypeUp->name() == name) {
            return clockTypeUp.get();
        }
    }

    return nullptr;
}

const DataStreamType *TraceTypeImpl::findDataStreamType(const TypeId id) const
{
    auto it = _idsToDataStreamTypes.find(id);

    if (it == std::end(_idsToDataStreamTypes)) {
        return nullptr;
    }

    return it->second;
}

void TraceTypeImpl::_createParentLinks(const TraceType *traceType)
{
    for (const auto& dstUp : _dataStreamTypes) {
        dstUp->_setTraceType(traceType);

        for (const auto& ertUp : dstUp->eventRecordTypes()) {
            ertUp->_setDataStreamType(dstUp.get());
        }
    }
}

void TraceTypeImpl::_validateMappedClockTypeNames()
{
    this->_validateMappedClockTypeName(_packetHeaderType.get());

    for (const auto& dstUp : _dataStreamTypes) {
        this->_validateMappedClockTypeName(dstUp->packetContextType());
        this->_validateMappedClockTypeName(dstUp->eventRecordHeaderType());
        this->_validateMappedClockTypeName(dstUp->eventRecordFirstContextType());

        for (const auto& ertUp : dstUp->eventRecordTypes()) {
            this->_validateMappedClockTypeName(ertUp->secondContextType());
            this->_validateMappedClockTypeName(ertUp->payloadType());
        }
    }
}

void TraceTypeImpl::_validateMappedClockTypeName(const DataType *type)
{
    if (!type) {
        return;
    }

    if (type->isStructType()) {
        for (const auto& field : type->asStructType()->fields()) {
            this->_validateMappedClockTypeName(&field->type());
        }
    } else if (type->isArrayType()) {
        this->_validateMappedClockTypeName(&type->asArrayType()->elemType());
    } else if (type->isDynamicArrayType()) {
        this->_validateMappedClockTypeName(&type->asDynamicArrayType()->elemType());
    } else if (type->isVariantType()) {
        for (const auto& option : type->asVariantType()->options()) {
            this->_validateMappedClockTypeName(&option->type());
        }
    } else if (type->isIntType()) {
        auto& mappedClockTypeName = type->asIntType()->mappedClockTypeName();

        if (mappedClockTypeName) {
            auto mappedClockType = this->findClockType(*mappedClockTypeName);

            if (!mappedClockType) {
                std::ostringstream ss;

                ss << "Cannot find mapped clock type named `" <<
                      *mappedClockTypeName << "`.";
                throw InvalidMetadata {ss.str()};
            }

            type->asIntType()->_mappedClockType(*mappedClockType);
        }
    }
}

void TraceTypeImpl::_validateVariantTypeTagType(const DataType *variantType,
                                                const DataType *tagType)
{
    const VariantType *asVariantType = variantType->asVariantType();

    if (!tagType->isEnumType()) {
        std::ostringstream ss;

        ss << "Variant type's tag type is not an enumeration type: `" <<
              asVariantType->tag() << "`.";

        throw InvalidMetadata {ss.str()};
    }

    std::unordered_set<std::string> memberNames;

    // TODO: use template here
    if (tagType->isSignedEnumType()) {
        const SignedEnumType *asEnumType = tagType->asSignedEnumType();

        for (const auto& nameMemberPair : asEnumType->members()) {
            memberNames.insert(nameMemberPair.first);
        }
    } else {
        const UnsignedEnumType *asEnumType = tagType->asUnsignedEnumType();

        for (const auto& nameMemberPair : asEnumType->members()) {
            memberNames.insert(nameMemberPair.first);
        }
    }

    for (const auto& memberName : memberNames) {
        if (!asVariantType->hasOption(memberName)) {
            std::ostringstream ss;

            ss << "Variant type's tag type contains a member name which is not a variant type's option: `" <<
                  memberName << "`.";

            throw InvalidMetadata {ss.str()};
        }
    }
}

void TraceTypeImpl::_resolveDynamicTypeInScope(const Scope scope,
                                               const DataType *type,
                                               const FieldResolver& fieldResolver)
{
    if (type->isStructType()) {
        this->_stackPush(_StackFrame {type, 0});

        auto structType = type->asStructType();

        for (Index index = 0; index < structType->fields().size(); ++index) {
            this->_stackTop().curChildIndex = index;

            auto childType = &(*structType)[index].type();

            this->_resolveDynamicTypeInScope(scope, childType, fieldResolver);
        }

        this->_stackPop();
    } else if (type->isArrayType()) {
        this->_stackPush(_StackFrame {type, -1ULL});
        this->_resolveDynamicTypeInScope(scope, &type->asArrayType()->elemType(),
                                         fieldResolver);
        this->_stackPop();
    } else if (type->isDynamicArrayType()) {
        const auto result = fieldResolver.resolve(scope, this->_curPos(),
                                                  type->asDynamicArrayType()->length());

        if (!result.type) {
            std::ostringstream ss;

            ss << "Cannot find the length type of dynamic array type: `" <<
                  toString(type->asDynamicArrayType()->length()) << "`.";

            throw InvalidMetadata {ss.str()};
        }

        if (!result.type->isUnsignedIntType()) {
            std::ostringstream ss;

            ss << "Dynamic array type's length type is not an unsigned integer type: `" <<
                  toString(type->asDynamicArrayType()->length()) << "`.";

            throw InvalidMetadata {ss.str()};
        }

        type->asDynamicArrayType()->_lengthType = result.type;
        this->_stackPush(_StackFrame {type, -1ULL});
        this->_resolveDynamicTypeInScope(scope, &type->asDynamicArrayType()->elemType(),
                                         fieldResolver);
        this->_stackPop();
    } else if (type->isVariantType()) {
        auto variantType = type->asVariantType();
        const auto result = fieldResolver.resolve(scope, this->_curPos(),
                                                  variantType->tag());

        if (!result.type) {
            std::ostringstream ss;

            ss << "Cannot find the tag type of variant type: `" <<
                  toString(type->asVariantType()->tag()) << "`.";

            throw InvalidMetadata {ss.str()};
        }

        this->_validateVariantTypeTagType(type, result.type);
        variantType->_tagType = result.type;
        this->_stackPush(_StackFrame {type, 0});

        for (Index index = 0; index < variantType->options().size(); ++index) {
            this->_stackTop().curChildIndex = index;

            auto childType = &(*variantType)[index].type();

            this->_resolveDynamicTypeInScope(scope, childType, fieldResolver);
        }

        this->_stackPop();
    }
}

void TraceTypeImpl::_resolveDynamicTypesInScope(const Scope scope,
                                                 const DataType *type,
                                                 const FieldResolver& fieldResolver)
{
    if (!type) {
        return;
    }

    this->_resolveDynamicTypeInScope(scope, type, fieldResolver);
}

void TraceTypeImpl::_resolveDynamicTypes()
{
    FieldResolver resolver {
        std::bind(&TraceTypeImpl::_getEntryAt, this, std::placeholders::_1, std::placeholders::_2)
    };

    _resolveState.packetHeaderType = _packetHeaderType.get();
    this->_resolveDynamicTypesInScope(Scope::PACKET_HEADER,
                                      _resolveState.packetHeaderType,
                                      resolver);

    for (const auto& dstUp : _dataStreamTypes) {
        _resolveState.packetContextType = dstUp->packetContextType();
        _resolveState.eventRecordHeaderType = nullptr;
        _resolveState.eventRecordFirstContextType = nullptr;
        _resolveState.eventRecordSecondContextType = nullptr;
        _resolveState.eventRecordPayloadType = nullptr;
        this->_resolveDynamicTypesInScope(Scope::PACKET_CONTEXT,
                                          _resolveState.packetContextType,
                                          resolver);
        _resolveState.eventRecordHeaderType = dstUp->eventRecordHeaderType();
        this->_resolveDynamicTypesInScope(Scope::EVENT_RECORD_HEADER,
                                          _resolveState.eventRecordHeaderType,
                                          resolver);
        _resolveState.eventRecordFirstContextType = dstUp->eventRecordFirstContextType();
        this->_resolveDynamicTypesInScope(Scope::EVENT_RECORD_FIRST_CONTEXT,
                                          _resolveState.eventRecordFirstContextType,
                                          resolver);

        for (const auto& ertUp : dstUp->eventRecordTypes()) {
            _resolveState.eventRecordSecondContextType = ertUp->secondContextType();
            _resolveState.eventRecordPayloadType = nullptr;
            this->_resolveDynamicTypesInScope(Scope::EVENT_RECORD_SECOND_CONTEXT,
                                              _resolveState.eventRecordSecondContextType,
                                              resolver);
            _resolveState.eventRecordPayloadType = ertUp->payloadType();
            this->_resolveDynamicTypesInScope(Scope::EVENT_RECORD_PAYLOAD,
                                              _resolveState.eventRecordPayloadType,
                                              resolver);
        }
    }
}

const PacketProc& TraceTypeImpl::packetProc() const
{
    if (!_packetProc) {
        _packetProc = internal::PacketProcBuilder {*_traceType}.takePacketProc();
    }

    return *_packetProc;
}

} // namespace internal
} // namespace yactfr
