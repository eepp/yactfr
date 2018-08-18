/*
 * Data stream consuming procedure item builder.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstdlib>
#include <string>
#include <sstream>
#include <type_traits>
#include <boost/uuid/uuid_io.hpp>
#include <boost/variant/variant.hpp>

#include <yactfr/metadata/io.hpp>
#include <yactfr/aliases.hpp>
#include <yactfr/metadata/data-type.hpp>
#include <yactfr/metadata/bit-array-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/string-type.hpp>
#include <yactfr/metadata/struct-type-field.hpp>
#include <yactfr/metadata/field-ref.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/array-type.hpp>
#include <yactfr/metadata/text-array-type.hpp>
#include <yactfr/metadata/sequence-type.hpp>
#include <yactfr/metadata/text-sequence-type.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/metadata/variant-type-option.hpp>
#include <yactfr/metadata/clock-type.hpp>
#include <yactfr/metadata/event-record-type.hpp>
#include <yactfr/metadata/data-stream-type.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/trace-type-env.hpp>

#include "../utils.hpp"

namespace yactfr {

namespace buuids = boost::uuids;
namespace u = utils;

std::string toString(const FieldRef& ref)
{
    std::ostringstream ss;

    switch (ref.scope()) {
    case Scope::PACKET_HEADER:
        ss << "PH:";
        break;

    case Scope::PACKET_CONTEXT:
        ss << "PC:";
        break;

    case Scope::EVENT_RECORD_HEADER:
        ss << "ERH:";
        break;

    case Scope::EVENT_RECORD_FIRST_CONTEXT:
        ss << "ER1C:";
        break;

    case Scope::EVENT_RECORD_SECOND_CONTEXT:
        ss << "ER2C:";
        break;

    case Scope::EVENT_RECORD_PAYLOAD:
        ss << "ERP:";
        break;
    }

    for (auto it = std::begin(ref.pathElements()); it != std::end(ref.pathElements()); ++it) {
        ss << *it;

        if (it < std::end(ref.pathElements()) - 1) {
            ss << '.';
        }
    }

    return ss.str();
}

std::string toString(const ByteOrder& byteOrder)
{
    switch (byteOrder) {
    case ByteOrder::BIG:
        return "be";

    case ByteOrder::LITTLE:
        return "le";
    }

    abort();
}

std::string toString(const Encoding& encoding)
{
    switch (encoding) {
    case Encoding::NONE:
        return "none";

    case Encoding::UTF8:
        return "UTF-8";
    }

    abort();
}

class ToStringDataTypeVisitor :
    public DataTypeVisitor
{
public:
    explicit ToStringDataTypeVisitor(const Size indent) :
        _indent {indent}
    {
    }

    void visit(const SignedIntType& type) override
    {
        _ss << this->_getIndentStr() << "Signed int type <" << &type <<
               "> (align: " << type.alignment() <<
               ", size: " << type.size() <<
               ", byte order: " << toString(type.byteOrder()) <<
               ", display base: " << static_cast<int>(type.displayBase()) <<
               ", encoding: " << toString(type.encoding());

        if (type.mappedClockTypeName()) {
            _ss << ", mapped clock type name: `" <<
                   *type.mappedClockTypeName() << "`";
        }

        _ss << ")" << std::endl;
    }

    void visit(const UnsignedIntType& type) override
    {
        _ss << this->_getIndentStr() << "Unsigned int type <" << &type <<
               "> (align: " << type.alignment() <<
               ", size: " << type.size() <<
               ", byte order: " << toString(type.byteOrder()) <<
               ", display base: " << static_cast<int>(type.displayBase()) <<
               ", encoding: " << toString(type.encoding());

        if (type.mappedClockTypeName()) {
            _ss << ", mapped clock type name: `" <<
                   *type.mappedClockTypeName() << "`";
        }

        _ss << ")" << std::endl;
    }

    void visit(const FloatType& type) override
    {
        _ss << this->_getIndentStr() << "Float type <" << &type <<
               "> (align: " << type.alignment() <<
               ", size: " << type.size() <<
               ", byte order: " << toString(type.byteOrder()) << ")" <<
               std::endl;
    }

    void visit(const SignedEnumType& type) override
    {
        this->visitEnumType(type);
    }

    void visit(const UnsignedEnumType& type) override
    {
        this->visitEnumType(type);
    }

    void visit(const StringType& type) override
    {
        _ss << this->_getIndentStr() << "String type <" << &type <<
               "> (align: " << type.alignment() << ")" << std::endl;
    }

    void visit(const StructType& type) override
    {
        _ss << this->_getIndentStr() << "Struct type <" << &type <<
               "> (align: " << type.alignment() << ")" << std::endl;

        for (const auto& field : type.fields()) {
            _ss << toString(*field, _indent + 1);
        }
    }

    void visit(const ArrayType& type) override
    {
        static const std::string nameArrayType = "Array type";
        static const std::string nameTextArrayType = "Text array type";

        _ss << this->_getIndentStr() <<
               (type.isTextArrayType() ? nameTextArrayType : nameArrayType) <<
               " <" << &type <<
               "> (align: " << type.alignment() <<
               ", length: " << type.length() << ")" << std::endl <<
               toString(type.elemType(), _indent + 1);
    }

    void visit(const TextArrayType& type) override
    {
        this->visit(static_cast<const ArrayType&>(type));
    }

    void visit(const SequenceType& type) override
    {
        static const std::string nameSeqType = "Sequence type";
        static const std::string nameTextSeqType = "Text sequence type";

        _ss << this->_getIndentStr() <<
               (type.isTextSequenceType() ? nameTextSeqType : nameSeqType) <<
               " <" << &type << "> (align: " << type.alignment() <<
               ", length: `" << toString(type.length()) << "`)" << std::endl <<
               toString(type.elemType(), _indent + 1);
    }

    void visit(const TextSequenceType& type) override
    {
        this->visit(static_cast<const SequenceType&>(type));
    }

    void visit(const VariantType& type) override
    {
        _ss << this->_getIndentStr() << "Variant type <" << &type <<
               "> (align: " << type.alignment() <<
               ", tag: `" << toString(type.tag()) << "`)" << std::endl;

        for (const auto& option : type.options()) {
            _ss << toString(*option, _indent + 1);
        }
    }

    std::string _getIndentStr() const
    {
        return u::indent(_indent);
    }

    std::string string() const
    {
        return _ss.str();
    }

    template <typename EnumType>
    void visitEnumType(const EnumType& type);

private:
    const Size _indent;
    std::ostringstream _ss;
};

template <typename EnumType>
void ToStringDataTypeVisitor::visitEnumType(const EnumType& type)
{
    const char *signedName;

    if (std::is_same<EnumType, SignedEnumType>::value) {
        signedName = "Signed";
    } else {
        signedName = "Unsigned";
    }

    _ss << this->_getIndentStr() << signedName << " enum type <" << &type <<
           "> (align: " << type.alignment() <<
           ", size: " << type.size() <<
           ", byte order: " << toString(type.byteOrder()) <<
           ", display base: " << static_cast<int>(type.displayBase()) <<
           ", encoding: " << toString(type.encoding());

    if (type.mappedClockTypeName()) {
        _ss << ", mapped clock type name: `" << *type.mappedClockTypeName() << "`";
    }

    _ss << ")" << std::endl;

    for (const auto& nameMemberPair : type.members()) {
        _ss << u::indent(_indent + 1) << "Member `" <<
               nameMemberPair.first << "`: " << std::endl;

        for (const auto& range : nameMemberPair.second.ranges()) {
            _ss << u::indent(_indent + 2) << "[" << range.lower() <<
                   ", " << range.upper() << "]" << std::endl;
        }
    }
}

std::string toString(const DataType& type, const Size indent)
{
    ToStringDataTypeVisitor visitor {indent};

    type.accept(visitor);
    return visitor.string();
}

std::string toString(const StructTypeField& field, const Size indent)
{
    std::ostringstream ss;

    ss << u::indent(indent) << "Field `" << field.name() << "`:" <<
          std::endl << toString(field.type(), indent + 1);
    return ss.str();
}

std::string toString(const VariantTypeOption& option, const Size indent)
{
    std::ostringstream ss;

    ss << u::indent(indent) << "Option `" << option.name() << "`:" <<
          std::endl << toString(option.type(), indent + 1);
    return ss.str();
}

std::string toString(const ClockType& clockType, const Size indent)
{
    std::ostringstream ss;

    ss << u::indent(indent) << "CT <" << &clockType <<
          "> (name: `" << clockType.name() << "`";

    if (clockType.description()) {
        ss << ", description: `" << *clockType.description() << "`";
    }

    if (clockType.uuid()) {
        ss << ", UUID: `" << buuids::to_string(*clockType.uuid()) << "`";
    }

    ss << ", frequency: " << clockType.freq() <<
          ", error (cycles): " << clockType.errorCycles() <<
          ", offset (s): " << clockType.offsetSeconds() <<
          ", offset (cycles): " << clockType.offsetCycles() <<
          ", absolute: " << clockType.isAbsolute() << ")" << std::endl;
    return ss.str();
}

std::string toString(const EventRecordType& eventRecordType,
                     const Size indent)
{
    std::ostringstream ss;

    ss << u::indent(indent) << "ERT <" << &eventRecordType <<
          "> (ID: " << eventRecordType.id();

    if (eventRecordType.name()) {
        ss << ", name: `" << *eventRecordType.name() << "`";
    }

    if (eventRecordType.logLevel()) {
        ss << ", log level: " << *eventRecordType.logLevel();
    }

    if (eventRecordType.modelEmfUri()) {
        ss << ", model EMF URI: `" << *eventRecordType.modelEmfUri() << "`";
    }

    ss << ")" << std::endl;

    if (eventRecordType.secondContextType()) {
        ss << u::indent(indent + 1) << "Context type:" << std::endl <<
              toString(*eventRecordType.secondContextType(), indent + 2);
    }

    if (eventRecordType.payloadType()) {
        ss << u::indent(indent + 1) << "Payload type:" << std::endl <<
              toString(*eventRecordType.payloadType(), indent + 2);
    }

    return ss.str();
}

std::string toString(const DataStreamType& dataStreamType,
                     const Size indent)
{
    std::ostringstream ss;

    ss << u::indent(indent) << "DST <" << &dataStreamType <<
          "> (ID: " << dataStreamType.id() << ")" << std::endl;

    if (dataStreamType.packetContextType()) {
        ss << u::indent(indent + 1) << "Packet context type:" << std::endl <<
              toString(*dataStreamType.packetContextType(), indent + 2);
    }

    if (dataStreamType.eventRecordHeaderType()) {
        ss << u::indent(indent + 1) << "Event record header type:" << std::endl <<
              toString(*dataStreamType.eventRecordHeaderType(), indent + 2);
    }

    if (dataStreamType.eventRecordFirstContextType()) {
        ss << u::indent(indent + 1) << "Event record context type:" << std::endl <<
              toString(*dataStreamType.eventRecordFirstContextType(), indent + 2);
    }

    for (const auto& ertUp : dataStreamType.eventRecordTypes()) {
        ss << toString(*ertUp, indent + 1);
    }

    return ss.str();
}

class _EnvEntryVisitor :
    boost::static_visitor<std::string>
{
public:
    std::string operator()(const std::string& value)
    {
        std::string entry("`");

        entry += value;
        entry += '`';
        return entry;
    }

    std::string operator()(const long long value)
    {
        std::ostringstream ss;

        ss << value;
        return ss.str();
    }
};

std::string toString(const TraceType& traceType, const Size indent)
{
    std::ostringstream ss;

    ss << u::indent(indent) << "TT <" << &traceType <<
          "> (major: " << traceType.majorVersion() <<
          ", minor: " << traceType.minorVersion();

    if (traceType.uuid()) {
        ss << ", UUID: `" << buuids::to_string(*traceType.uuid()) << "`)";
    }

    ss << std::endl;

    _EnvEntryVisitor visitor;

    for (const auto& nameValuePair : traceType.env().entries()) {
        ss << u::indent(indent + 1) << "Env. entry `" <<
              nameValuePair.first << "`: " <<
              boost::apply_visitor(visitor, nameValuePair.second) <<
              std::endl;
    }

    for (const auto& clockTypeUp : traceType.clockTypes()) {
        ss << toString(*clockTypeUp, indent + 1);
    }

    if (traceType.packetHeaderType()) {
        ss << u::indent(indent + 1) << "Packet header type:" << std::endl <<
              toString(*traceType.packetHeaderType(), indent + 2);
    }

    for (const auto& dstUp : traceType.dataStreamTypes()) {
        ss << toString(*dstUp, indent + 1);
    }

    return ss.str();
}

} // namespace yactfr
