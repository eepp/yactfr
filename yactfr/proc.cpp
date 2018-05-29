/*
 * Procedure instructions.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>

#include "proc.hpp"

namespace yactfr {
namespace internal {

InstrVisitor::InstrVisitor()
{
}

InstrVisitor::~InstrVisitor()
{
}

void Proc::buildRawProcFromShared()
{
    // in case we call this more than once...
    _rawProc.clear();

    for (auto& instrSp : _sharedProc) {
        instrSp->buildRawProcFromShared();
        _rawProc.push_back(instrSp.get());
    }
}

std::string Proc::toString(const Size indent) const
{
    std::ostringstream ss;

    for (const auto& instrSp : _sharedProc) {
        ss << instrSp->toString(indent);
    }

    return ss.str();
}

void Proc::pushBack(std::shared_ptr<Instr> instr)
{
    _sharedProc.push_back(instr);
}

void Proc::insert(SharedIterator iter, std::shared_ptr<Instr> instr)
{
    _sharedProc.insert(iter, instr);
}

Instr::Instr() :
    _kind {Kind::UNSET}
{
}

Instr::Instr(Kind kind) :
    _kind {kind}
{
}

std::string Instr::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << std::endl;
    return ss.str();
}

std::string Instr::toString(const Size indent) const
{
    const char *kindStr;

    switch (_kind) {
    case Kind::UNSET:
        kindStr = "UNSET";
        break;

    case Kind::READ_SIGNED_INT_LE:
        kindStr = "READ_SIGNED_INT_LE";
        break;

    case Kind::READ_SIGNED_INT_BE:
        kindStr = "READ_SIGNED_INT_BE";
        break;

    case Kind::READ_SIGNED_INT_A8:
        kindStr = "READ_SIGNED_INT_A8";
        break;

    case Kind::READ_SIGNED_INT_A16_LE:
        kindStr = "READ_SIGNED_INT_A16_LE";
        break;

    case Kind::READ_SIGNED_INT_A32_LE:
        kindStr = "READ_SIGNED_INT_A32_LE";
        break;

    case Kind::READ_SIGNED_INT_A64_LE:
        kindStr = "READ_SIGNED_INT_A64_LE";
        break;

    case Kind::READ_SIGNED_INT_A16_BE:
        kindStr = "READ_SIGNED_INT_A16_BE";
        break;

    case Kind::READ_SIGNED_INT_A32_BE:
        kindStr = "READ_SIGNED_INT_A32_BE";
        break;

    case Kind::READ_SIGNED_INT_A64_BE:
        kindStr = "READ_SIGNED_INT_A64_BE";
        break;

    case Kind::READ_UNSIGNED_INT_LE:
        kindStr = "READ_UNSIGNED_INT_LE";
        break;

    case Kind::READ_UNSIGNED_INT_BE:
        kindStr = "READ_UNSIGNED_INT_BE";
        break;

    case Kind::READ_UNSIGNED_INT_A8:
        kindStr = "READ_UNSIGNED_INT_A8";
        break;

    case Kind::READ_UNSIGNED_INT_A16_LE:
        kindStr = "READ_UNSIGNED_INT_A16_LE";
        break;

    case Kind::READ_UNSIGNED_INT_A32_LE:
        kindStr = "READ_UNSIGNED_INT_A32_LE";
        break;

    case Kind::READ_UNSIGNED_INT_A64_LE:
        kindStr = "READ_UNSIGNED_INT_A64_LE";
        break;

    case Kind::READ_UNSIGNED_INT_A16_BE:
        kindStr = "READ_UNSIGNED_INT_A16_BE";
        break;

    case Kind::READ_UNSIGNED_INT_A32_BE:
        kindStr = "READ_UNSIGNED_INT_A32_BE";
        break;

    case Kind::READ_UNSIGNED_INT_A64_BE:
        kindStr = "READ_UNSIGNED_INT_A64_BE";
        break;

    case Kind::READ_FLOAT_32_LE:
        kindStr = "READ_FLOAT_32_LE";
        break;

    case Kind::READ_FLOAT_32_BE:
        kindStr = "READ_FLOAT_32_BE";
        break;

    case Kind::READ_FLOAT_A32_LE:
        kindStr = "READ_FLOAT_A32_LE";
        break;

    case Kind::READ_FLOAT_A32_BE:
        kindStr = "READ_FLOAT_A32_BE";
        break;

    case Kind::READ_FLOAT_64_LE:
        kindStr = "READ_FLOAT_64_LE";
        break;

    case Kind::READ_FLOAT_64_BE:
        kindStr = "READ_FLOAT_64_BE";
        break;

    case Kind::READ_FLOAT_A64_LE:
        kindStr = "READ_FLOAT_A64_LE";
        break;

    case Kind::READ_FLOAT_A64_BE:
        kindStr = "READ_FLOAT_A64_BE";
        break;

    case Kind::READ_SIGNED_ENUM_LE:
        kindStr = "READ_SIGNED_ENUM_LE";
        break;

    case Kind::READ_SIGNED_ENUM_BE:
        kindStr = "READ_SIGNED_ENUM_BE";
        break;

    case Kind::READ_SIGNED_ENUM_A8:
        kindStr = "READ_SIGNED_ENUM_A8";
        break;

    case Kind::READ_SIGNED_ENUM_A16_LE:
        kindStr = "READ_SIGNED_ENUM_A16_LE";
        break;

    case Kind::READ_SIGNED_ENUM_A32_LE:
        kindStr = "READ_SIGNED_ENUM_A32_LE";
        break;

    case Kind::READ_SIGNED_ENUM_A64_LE:
        kindStr = "READ_SIGNED_ENUM_A64_LE";
        break;

    case Kind::READ_SIGNED_ENUM_A16_BE:
        kindStr = "READ_SIGNED_ENUM_A16_BE";
        break;

    case Kind::READ_SIGNED_ENUM_A32_BE:
        kindStr = "READ_SIGNED_ENUM_A32_BE";
        break;

    case Kind::READ_SIGNED_ENUM_A64_BE:
        kindStr = "READ_SIGNED_ENUM_A64_BE";
        break;

    case Kind::READ_UNSIGNED_ENUM_LE:
        kindStr = "READ_UNSIGNED_ENUM_LE";
        break;

    case Kind::READ_UNSIGNED_ENUM_BE:
        kindStr = "READ_UNSIGNED_ENUM_BE";
        break;

    case Kind::READ_UNSIGNED_ENUM_A8:
        kindStr = "READ_UNSIGNED_ENUM_A8";
        break;

    case Kind::READ_UNSIGNED_ENUM_A16_LE:
        kindStr = "READ_UNSIGNED_ENUM_A16_LE";
        break;

    case Kind::READ_UNSIGNED_ENUM_A32_LE:
        kindStr = "READ_UNSIGNED_ENUM_A32_LE";
        break;

    case Kind::READ_UNSIGNED_ENUM_A64_LE:
        kindStr = "READ_UNSIGNED_ENUM_A64_LE";
        break;

    case Kind::READ_UNSIGNED_ENUM_A16_BE:
        kindStr = "READ_UNSIGNED_ENUM_A16_BE";
        break;

    case Kind::READ_UNSIGNED_ENUM_A32_BE:
        kindStr = "READ_UNSIGNED_ENUM_A32_BE";
        break;

    case Kind::READ_UNSIGNED_ENUM_A64_BE:
        kindStr = "READ_UNSIGNED_ENUM_A64_BE";
        break;

    case Kind::READ_STRING:
        kindStr = "READ_STRING";
        break;

    case Kind::BEGIN_READ_SCOPE:
        kindStr = "BEGIN_READ_SCOPE";
        break;

    case Kind::END_READ_SCOPE:
        kindStr = "END_READ_SCOPE";
        break;

    case Kind::BEGIN_READ_STRUCT:
        kindStr = "BEGIN_READ_STRUCT";
        break;

    case Kind::END_READ_STRUCT:
        kindStr = "END_READ_STRUCT";
        break;

    case Kind::BEGIN_READ_ARRAY:
        kindStr = "BEGIN_READ_ARRAY";
        break;

    case Kind::END_READ_ARRAY:
        kindStr = "END_READ_ARRAY";
        break;

    case Kind::BEGIN_READ_TEXT_ARRAY:
        kindStr = "BEGIN_READ_TEXT_ARRAY";
        break;

    case Kind::END_READ_TEXT_ARRAY:
        kindStr = "END_READ_TEXT_ARRAY";
        break;

    case Kind::BEGIN_READ_UUID_ARRAY:
        kindStr = "BEGIN_READ_UUID_ARRAY";
        break;

    case Kind::BEGIN_READ_SEQUENCE:
        kindStr = "BEGIN_READ_SEQUENCE";
        break;

    case Kind::END_READ_SEQUENCE:
        kindStr = "END_READ_SEQUENCE";
        break;

    case Kind::BEGIN_READ_TEXT_SEQUENCE:
        kindStr = "BEGIN_READ_TEXT_SEQUENCE";
        break;

    case Kind::END_READ_TEXT_SEQUENCE:
        kindStr = "END_READ_TEXT_SEQUENCE";
        break;

    case Kind::BEGIN_READ_VARIANT_SIGNED_TAG:
        kindStr = "BEGIN_READ_VARIANT_SIGNED_TAG";
        break;

    case Kind::BEGIN_READ_VARIANT_UNSIGNED_TAG:
        kindStr = "BEGIN_READ_VARIANT_UNSIGNED_TAG";
        break;

    case Kind::BEGIN_READ_UNKNOWN_VARIANT:
        kindStr = "BEGIN_READ_UNKNOWN_VARIANT";
        break;

    case Kind::END_READ_VARIANT:
        kindStr = "END_READ_VARIANT";
        break;

    case Kind::SAVE_VALUE:
        kindStr = "SAVE_VALUE";
        break;

    case Kind::SET_PACKET_END_CLOCK_VALUE:
        kindStr = "SET_PACKET_END_CLOCK_VALUE";
        break;

    case Kind::UPDATE_CLOCK_VALUE:
        kindStr = "UPDATE_CLOCK_VALUE";
        break;

    case Kind::SET_CURRENT_ID:
        kindStr = "SET_CURRENT_ID";
        break;

    case Kind::SET_DATA_STREAM_TYPE:
        kindStr = "SET_DATA_STREAM_TYPE";
        break;

    case Kind::SET_EVENT_RECORD_TYPE:
        kindStr = "SET_EVENT_RECORD_TYPE";
        break;

    case Kind::SET_DATA_STREAM_ID:
        kindStr = "SET_DATA_STREAM_ID";
        break;

    case Kind::SET_PACKET_ORIGIN_INDEX:
        kindStr = "SET_PACKET_ORIGIN_INDEX";
        break;

    case Kind::SET_PACKET_TOTAL_SIZE:
        kindStr = "SET_PACKET_TOTAL_SIZE";
        break;

    case Kind::SET_PACKET_CONTENT_SIZE:
        kindStr = "SET_PACKET_CONTENT_SIZE";
        break;

    case Kind::SET_PACKET_MAGIC_NUMBER:
        kindStr = "SET_PACKET_MAGIC_NUMBER";
        break;

    case Kind::END_PACKET_PREAMBLE_PROC:
        kindStr = "END_PACKET_PREAMBLE_PROC";
        break;

    case Kind::END_DST_PACKET_PREAMBLE_PROC:
        kindStr = "END_DST_PACKET_PREAMBLE_PROC";
        break;

    case Kind::END_DST_ERT_PREAMBLE_PROC:
        kindStr = "END_DST_ERT_PREAMBLE_PROC";
        break;

    case Kind::END_ERT_PROC:
        kindStr = "END_ERT_PROC";
        break;

    case Kind::DECR_REMAINING_ELEMENTS:
        kindStr = "DECR_REMAINING_ELEMENTS";
        break;

    default:
        abort();
    }

    std::ostringstream ss;

    ss << utils::indent(indent);

    if (this->isReadData() || this->isBeginReadScope()) {
        ss << _strName(kindStr);
    } else if (this->isEndReadCompound() || _kind == Kind::END_READ_SCOPE ||
            this->isEndProc()) {
        ss << _strEndName(kindStr);
    } else {
        ss << _strSpecName(kindStr);
    }

    ss << this->_toString(indent);
    return ss.str();
}

Instr::~Instr()
{
}

void Instr::buildRawProcFromShared()
{
}

InstrReadData::InstrReadData(const std::string *fieldName,
                             const std::string *fieldDisplayName,
                             const DataType *type) :
    _fieldName {fieldName},
    _fieldDisplayName {fieldDisplayName},
    _type {type},
    _alignment {type ? type->alignment() : 1}
{
    assert(type);
}

std::string InstrReadData::_commonToString() const
{
    std::ostringstream ss;

    if (_fieldName) {
        ss << " " << _strProp("field-name") << "`" << *_fieldName << "`";

        if (_fieldDisplayName && *_fieldName != *_fieldDisplayName) {
            ss << " " << _strProp("field-disp-name") << "`" << *_fieldDisplayName << "`";
        }
    }

    if (_type) {
        ss << " " << _strProp("type") << _type <<
              " " << _strProp("alignment") << _alignment;
    }

    return ss.str();
}

InstrLocation InstrReadData::findInstr(std::vector<std::string>::const_iterator begin,
                                       std::vector<std::string>::const_iterator end)
{
    return {};
}

InstrSaveValue::InstrSaveValue(const Index pos) :
    _pos {pos}
{
    this->_setKind(Kind::SAVE_VALUE);
}

std::string InstrSaveValue::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("pos") << _pos << " " << std::endl;
    return ss.str();
}

InstrSetPacketEndClockValue::InstrSetPacketEndClockValue(const ClockType& clockType,
                                                         const Index index) :
    _clockType {&clockType},
    _index {index}
{
    this->_setKind(Kind::SET_PACKET_END_CLOCK_VALUE);
}

std::string InstrSetPacketEndClockValue::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("clock-type") << _clockType <<
          " " << _strProp("index") << _index << std::endl;
    return ss.str();
}

InstrReadBitArray::InstrReadBitArray(const std::string *fieldName,
                                     const std::string *fieldDisplayName,
                                     const DataType *type) :
    InstrReadData {fieldName, fieldDisplayName, type},
    _size {type->asBitArrayType()->size()},
    _byteOrder {type->asBitArrayType()->byteOrder()}
{
    assert(type->isBitArrayType());
}

std::string InstrReadBitArray::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
}

std::string InstrReadBitArray::_commonToString() const
{
    std::ostringstream ss;

    ss << InstrReadData::_commonToString();
    ss << " " << _strProp("size") << _size;
    return ss.str();
}

InstrReadIntBase::InstrReadIntBase(const std::string *fieldName,
                                   const std::string *fieldDisplayName,
                                   const DataType *type) :
    InstrReadBitArray {fieldName, fieldDisplayName, type}
{
}

InstrReadSignedInt::InstrReadSignedInt(const std::string *fieldName,
                                       const std::string *fieldDisplayName,
                                       const DataType *type) :
    InstrReadIntBase {fieldName, fieldDisplayName, type}
{
    assert(type->isSignedIntType());

    Kind kind = Kind::UNSET;
    auto intType = this->signedIntType();

    if (intType.byteOrder() == ByteOrder::LITTLE) {
        kind = Kind::READ_SIGNED_INT_LE;

        if (intType.alignment() % 8 == 0) {
            switch (intType.size()) {
            case 8:
                kind = Kind::READ_SIGNED_INT_A8;
                break;

            case 16:
                kind = Kind::READ_SIGNED_INT_A16_LE;
                break;

            case 32:
                kind = Kind::READ_SIGNED_INT_A32_LE;
                break;

            case 64:
                kind = Kind::READ_SIGNED_INT_A64_LE;
                break;

            default:
                break;
            }
        }
    } else {
        kind = Kind::READ_SIGNED_INT_BE;

        if (intType.alignment() % 8 == 0) {
            switch (intType.size()) {
            case 8:
                kind = Kind::READ_SIGNED_INT_A8;
                break;

            case 16:
                kind = Kind::READ_SIGNED_INT_A16_BE;
                break;

            case 32:
                kind = Kind::READ_SIGNED_INT_A32_BE;
                break;

            case 64:
                kind = Kind::READ_SIGNED_INT_A64_BE;
                break;

            default:
                break;
            }
        }
    }

    assert(kind != Kind::UNSET);
    this->_setKind(kind);
}

std::string InstrReadSignedInt::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
};

InstrReadUnsignedInt::InstrReadUnsignedInt(const std::string *fieldName,
                                           const std::string *fieldDisplayName,
                                           const DataType *type) :
    InstrReadIntBase {fieldName, fieldDisplayName, type}
{
    assert(type->isUnsignedIntType());

    Kind kind = Kind::UNSET;
    auto intType = this->unsignedIntType();

    if (intType.byteOrder() == ByteOrder::LITTLE) {
        kind = Kind::READ_UNSIGNED_INT_LE;

        if (intType.alignment() % 8 == 0) {
            switch (intType.size()) {
            case 8:
                kind = Kind::READ_UNSIGNED_INT_A8;
                break;

            case 16:
                kind = Kind::READ_UNSIGNED_INT_A16_LE;
                break;

            case 32:
                kind = Kind::READ_UNSIGNED_INT_A32_LE;
                break;

            case 64:
                kind = Kind::READ_UNSIGNED_INT_A64_LE;
                break;

            default:
                break;
            }
        }
    } else {
        kind = Kind::READ_UNSIGNED_INT_BE;

        if (intType.alignment() % 8 == 0) {
            switch (intType.size()) {
            case 8:
                kind = Kind::READ_UNSIGNED_INT_A8;
                break;

            case 16:
                kind = Kind::READ_UNSIGNED_INT_A16_BE;
                break;

            case 32:
                kind = Kind::READ_UNSIGNED_INT_A32_BE;
                break;

            case 64:
                kind = Kind::READ_UNSIGNED_INT_A64_BE;
                break;

            default:
                break;
            }
        }
    }

    assert(kind != Kind::UNSET);
    this->_setKind(kind);
}

std::string InstrReadUnsignedInt::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
}

InstrReadFloat::InstrReadFloat(const std::string *fieldName,
                               const std::string *fieldDisplayName,
                               const DataType *type) :
    InstrReadBitArray {fieldName, fieldDisplayName, type}
{
    assert(type->isFloatType());

    Kind kind = Kind::UNSET;
    auto floatType = this->floatType();

    if (floatType.byteOrder() == ByteOrder::LITTLE) {
        if (floatType.alignment() % 8 == 0) {
            switch (floatType.size()) {
            case 32:
                kind = Kind::READ_FLOAT_A32_LE;
                break;

            case 64:
                kind = Kind::READ_FLOAT_A64_LE;
                break;

            default:
                abort();
            }
        } else {
            switch (floatType.size()) {
            case 32:
                kind = Kind::READ_FLOAT_32_LE;
                break;

            case 64:
                kind = Kind::READ_FLOAT_64_LE;
                break;

            default:
                abort();
            }
        }
    } else {
        if (floatType.alignment() % 8 == 0) {
            switch (floatType.size()) {
            case 32:
                kind = Kind::READ_FLOAT_A32_BE;
                break;

            case 64:
                kind = Kind::READ_FLOAT_A64_BE;
                break;

            default:
                abort();
            }
        } else {
            switch (floatType.size()) {
            case 32:
                kind = Kind::READ_FLOAT_32_BE;
                break;

            case 64:
                kind = Kind::READ_FLOAT_64_BE;
                break;

            default:
                abort();
            }
        }
    }

    assert(kind != Kind::UNSET);
    this->_setKind(kind);
}

std::string InstrReadFloat::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
}

InstrReadSignedEnum::InstrReadSignedEnum(const std::string *fieldName,
                                         const std::string *fieldDisplayName,
                                         const DataType *type) :
    InstrReadSignedInt {fieldName, fieldDisplayName, type}
{
    assert(type->isSignedEnumType());

    switch (this->kind()) {
    case Kind::READ_SIGNED_INT_LE:
        this->_setKind(Kind::READ_SIGNED_ENUM_LE);
        break;

    case Kind::READ_SIGNED_INT_BE:
        this->_setKind(Kind::READ_SIGNED_ENUM_BE);
        break;

    case Kind::READ_SIGNED_INT_A8:
        this->_setKind(Kind::READ_SIGNED_ENUM_A8);
        break;

    case Kind::READ_SIGNED_INT_A16_LE:
        this->_setKind(Kind::READ_SIGNED_ENUM_A16_LE);
        break;

    case Kind::READ_SIGNED_INT_A32_LE:
        this->_setKind(Kind::READ_SIGNED_ENUM_A32_LE);
        break;

    case Kind::READ_SIGNED_INT_A64_LE:
        this->_setKind(Kind::READ_SIGNED_ENUM_A64_LE);
        break;

    case Kind::READ_SIGNED_INT_A16_BE:
        this->_setKind(Kind::READ_SIGNED_ENUM_A16_BE);
        break;

    case Kind::READ_SIGNED_INT_A32_BE:
        this->_setKind(Kind::READ_SIGNED_ENUM_A32_BE);
        break;

    case Kind::READ_SIGNED_INT_A64_BE:
        this->_setKind(Kind::READ_SIGNED_ENUM_A64_BE);
        break;

    default:
        abort();
    }
}

std::string InstrReadSignedEnum::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
}

InstrReadUnsignedEnum::InstrReadUnsignedEnum(const std::string *fieldName,
                                             const std::string *fieldDisplayName,
                                             const DataType *type) :
    InstrReadUnsignedInt {fieldName, fieldDisplayName, type}
{
    assert(type->isUnsignedEnumType());

    switch (this->kind()) {
    case Kind::READ_UNSIGNED_INT_LE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_LE);
        break;

    case Kind::READ_UNSIGNED_INT_BE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_BE);
        break;

    case Kind::READ_UNSIGNED_INT_A8:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_A8);
        break;

    case Kind::READ_UNSIGNED_INT_A16_LE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_A16_LE);
        break;

    case Kind::READ_UNSIGNED_INT_A32_LE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_A32_LE);
        break;

    case Kind::READ_UNSIGNED_INT_A64_LE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_A64_LE);
        break;

    case Kind::READ_UNSIGNED_INT_A16_BE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_A16_BE);
        break;

    case Kind::READ_UNSIGNED_INT_A32_BE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_A32_BE);
        break;

    case Kind::READ_UNSIGNED_INT_A64_BE:
        this->_setKind(Kind::READ_UNSIGNED_ENUM_A64_BE);
        break;

    default:
        abort();
    }
}

std::string InstrReadUnsignedEnum::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
}

InstrReadString::InstrReadString(const std::string *fieldName,
                                 const std::string *fieldDisplayName,
                                 const DataType *type) :
    InstrReadData {fieldName, fieldDisplayName, type},
    _alignment {type->asStringType()->alignment()}
{
    assert(type->isStringType());
    this->_setKind(Kind::READ_STRING);
}

std::string InstrReadString::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
}

InstrBeginReadCompound::InstrBeginReadCompound(const std::string *fieldName,
                                               const std::string *fieldDisplayName,
                                               const DataType *type) :
    InstrReadData {fieldName, fieldDisplayName, type}
{
}

Instr *InstrBeginReadCompound::findInstrByFieldName(const std::string& fieldName)
{
    for (auto& instr : _proc) {
        if (!instr->isReadData()) {
            continue;
        }

        auto& instrRead = static_cast<InstrReadData&>(*instr);

        if (instrRead.fieldName() && *instrRead.fieldName() == fieldName) {
            return instr.get();
        }
    }

    return nullptr;
}

void InstrBeginReadCompound::buildRawProcFromShared()
{
    _proc.buildRawProcFromShared();
}

InstrEndReadCompound::InstrEndReadCompound(const Kind kind,
                                           const std::string *fieldName,
                                           const std::string *fieldDisplayName,
                                           const DataType *type) :
    InstrReadData {fieldName, fieldDisplayName, type}
{
    assert(kind == Kind::END_READ_STRUCT ||
           kind == Kind::END_READ_ARRAY ||
           kind == Kind::END_READ_TEXT_ARRAY ||
           kind == Kind::END_READ_SEQUENCE ||
           kind == Kind::END_READ_TEXT_SEQUENCE ||
           kind == Kind::END_READ_VARIANT);
    this->_setKind(kind);
}

std::string InstrEndReadCompound::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    return ss.str();
}

InstrBeginReadStruct::InstrBeginReadStruct(const std::string *fieldName,
                                           const std::string *fieldDisplayName,
                                           const DataType *type) :
    InstrBeginReadCompound {fieldName, fieldDisplayName, type}
{
    assert(type->isStructType());
    this->_setKind(Kind::BEGIN_READ_STRUCT);
}

std::string InstrBeginReadStruct::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    ss << this->_procToString(indent + 1);
    return ss.str();
}

InstrLocation InstrBeginReadStruct::findInstr(std::vector<std::string>::const_iterator begin,
                                                          std::vector<std::string>::const_iterator end)
{
    if (begin == end) {
        return {};
    }

    for (auto it = std::begin(this->proc()); it != std::end(this->proc()); ++it) {
        auto& instr = *it;

        if (!instr->isReadData()) {
            continue;
        }

        auto& instrRead = static_cast<InstrReadData&>(*instr);

        if (!instrRead.fieldName()) {
            continue;
        }

        if (*instrRead.fieldName() == *begin) {
            ++begin;

            if (begin == end) {
                return {&this->proc().sharedProc(), it};
            }

            return instrRead.findInstr(begin, end);
        }
    }

    return {};
}

static const char *scopeToString(const Scope scope)
{
    switch (scope) {
    case Scope::PACKET_HEADER:
        return "PACKET_HEADER";

    case Scope::PACKET_CONTEXT:
        return "PACKET_CONTEXT";

    case Scope::EVENT_RECORD_HEADER:
        return "EVENT_RECORD_HEADER";

    case Scope::EVENT_RECORD_FIRST_CONTEXT:
        return "EVENT_RECORD_FIRST_CONTEXT";

    case Scope::EVENT_RECORD_SECOND_CONTEXT:
        return "EVENT_RECORD_SECOND_CONTEXT";

    case Scope::EVENT_RECORD_PAYLOAD:
        return "EVENT_RECORD_PAYLOAD";

    default:
        abort();
    }
}

InstrBeginReadScope::InstrBeginReadScope(const Scope scope) :
    _scope {scope}
{
    this->_setKind(Kind::BEGIN_READ_SCOPE);
}

std::string InstrBeginReadScope::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("scope") << scopeToString(_scope) << std::endl;
    ss << _proc.toString(indent + 1);
    return ss.str();
}

void InstrBeginReadScope::buildRawProcFromShared()
{
    _proc.buildRawProcFromShared();
}

InstrEndReadScope::InstrEndReadScope(const Scope scope) :
    _scope {scope}
{
    this->_setKind(Kind::END_READ_SCOPE);
}

std::string InstrEndReadScope::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("scope") << scopeToString(_scope) << std::endl;
    return ss.str();
}

InstrLocation InstrBeginReadScope::findInstr(const FieldRef& fieldRef)
{
    if (fieldRef.scope() != _scope) {
        return {};
    }

    for (auto& instr : _proc) {
        if (!instr->isBeginReadStruct()) {
            continue;
        }

        auto& instrReadStruct = static_cast<InstrBeginReadStruct&>(*instr);
        auto beginIt = std::begin(fieldRef.pathElements());
        auto endIt = std::end(fieldRef.pathElements());

        return instrReadStruct.findInstr(beginIt, endIt);
    }

    return {};
}

InstrBeginReadArray::InstrBeginReadArray(const std::string *fieldName,
                                         const std::string *fieldDisplayName,
                                         const DataType *type) :
    InstrBeginReadCompound {fieldName, fieldDisplayName, type},
    _length {type->asArrayType()->length()}
{
    assert(type->isArrayType());
    this->_setKind(Kind::BEGIN_READ_ARRAY);
}

Instr *InstrBeginReadArray::findInstrByFieldName(const std::string& fieldName)
{
    for (auto& instrUp : this->proc()) {
        if (instrUp->isReadData()) {
            return instrUp.get();
        }
    }

    return nullptr;
}

std::string InstrBeginReadArray::_commonToString() const
{
    std::ostringstream ss;

    ss << InstrReadData::_commonToString();
    ss << " " << _strProp("length") << _length;

    return ss.str();
}

std::string InstrBeginReadArray::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    ss << this->_procToString(indent + 1);
    return ss.str();
}

InstrLocation InstrBeginReadArray::findInstr(std::vector<std::string>::const_iterator begin,
                                                         std::vector<std::string>::const_iterator end)
{
    for (auto& instr : this->proc()) {
        if (!instr->isReadData()) {
            continue;
        }

        auto& instrReadData = static_cast<InstrReadData&>(*instr);

        return instrReadData.findInstr(begin, end);
    }

    return {};
}

InstrBeginReadTextArray::InstrBeginReadTextArray(const std::string *fieldName,
                                                 const std::string *fieldDisplayName,
                                                 const DataType *type) :
    InstrBeginReadArray {fieldName, fieldDisplayName, type}
{
    this->_setKind(Kind::BEGIN_READ_TEXT_ARRAY);
}

InstrBeginReadUuidArray::InstrBeginReadUuidArray(const std::string *fieldName,
                                                 const std::string *fieldDisplayName,
                                                 const DataType *type) :
    InstrBeginReadArray {fieldName, fieldDisplayName, type}
{
    this->_setKind(Kind::BEGIN_READ_UUID_ARRAY);
}

InstrBeginReadSequence::InstrBeginReadSequence(const std::string *fieldName,
                                               const std::string *fieldDisplayName,
                                               const DataType *type) :
    InstrBeginReadCompound {fieldName, fieldDisplayName, type}
{
    assert(type->isSequenceType());
    this->_setKind(Kind::BEGIN_READ_SEQUENCE);
}

Instr *InstrBeginReadSequence::findInstrByFieldName(const std::string& fieldName)
{
    for (auto& instrUp : this->proc()) {
        if (instrUp->isReadData()) {
            return instrUp.get();
        }
    }

    return nullptr;
}

std::string InstrBeginReadSequence::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() << std::endl;
    ss << this->_procToString(indent + 1);
    return ss.str();
}

std::string InstrBeginReadSequence::_commonToString() const
{
    std::ostringstream ss;

    ss << InstrReadData::_commonToString();
    ss << " " << _strProp("length-pos") << _lengthPos;
    return ss.str();
}

InstrLocation InstrBeginReadSequence::findInstr(std::vector<std::string>::const_iterator begin,
                                                std::vector<std::string>::const_iterator end)
{
    for (auto& instr : this->proc()) {
        if (!instr->isReadData()) {
            continue;
        }

        auto& instrReadData = static_cast<InstrReadData&>(*instr);

        return instrReadData.findInstr(begin, end);
    }

    return {};
}

InstrBeginReadTextSequence::InstrBeginReadTextSequence(const std::string *fieldName,
                                                       const std::string *fieldDisplayName,
                                                       const DataType *type) :
    InstrBeginReadSequence {fieldName, fieldDisplayName, type}
{
    this->_setKind(Kind::BEGIN_READ_TEXT_SEQUENCE);
}

InstrBeginReadUnknownVariant::InstrBeginReadUnknownVariant(const std::string *fieldName,
                                                           const std::string *fieldDisplayName,
                                                           const DataType *type) :
    InstrReadData {fieldName, fieldDisplayName, type}
{
    assert(type->isVariantType());
    this->_setKind(Kind::BEGIN_READ_UNKNOWN_VARIANT);
}

std::string InstrBeginReadUnknownVariant::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToString() <<
          " " << _strProp("tag-pos") << _tagPos <<
          std::endl;

    for (const auto& choice : _choices) {
        ss << utils::indent(indent + 1) << "<procedure for choice `" <<
              choice.first << "`>" << std::endl;
        ss << choice.second.toString(indent + 2);
    }

    return ss.str();
}

InstrLocation InstrBeginReadUnknownVariant::findInstr(std::vector<std::string>::const_iterator begin,
                                                      std::vector<std::string>::const_iterator end)
{
    if (begin == end) {
        return {};
    }

    for (auto& choice : _choices) {
        const auto& choiceName = choice.first;

        if (choiceName != *begin) {
            continue;
        }

        /*
         * Name matches: "read data" instruction is the procedure's
         * first instruction.
         */
        auto& proc = choice.second;

        assert(!proc.sharedProc().empty());
        assert(proc.sharedProc().front()->isReadData());
        ++begin;

        auto instrReadIt = std::begin(proc);

        if (begin == end) {
            return {&proc.sharedProc(), instrReadIt};
        } else {
            auto& instrRead = static_cast<InstrReadData&>(**instrReadIt);

            return instrRead.findInstr(begin, end);
        }
    }

    return {};
}

InstrBeginReadVariantUnsignedTag::InstrBeginReadVariantUnsignedTag(const InstrBeginReadUnknownVariant& instrReadUnkVariant,
                                                                   const EnumType& tagType) :
    InstrBeginReadVariant<UnsignedEnumType, Kind::BEGIN_READ_VARIANT_UNSIGNED_TAG> {
        instrReadUnkVariant, tagType
    }
{
}

InstrBeginReadVariantSignedTag::InstrBeginReadVariantSignedTag(const InstrBeginReadUnknownVariant& instrReadUnkVariant,
                                                               const EnumType& tagType) :
    InstrBeginReadVariant<SignedEnumType, Kind::BEGIN_READ_VARIANT_SIGNED_TAG> {
        instrReadUnkVariant, tagType
    }
{
}

InstrSetCurrentId::InstrSetCurrentId()
{
    this->_setKind(Kind::SET_CURRENT_ID);
}

InstrSetType::InstrSetType(const boost::optional<TypeId>& fixedId) :
    _fixedId {fixedId}
{
}

std::string InstrSetType::_toString(const Size indent) const
{
    std::ostringstream ss;

    if (_fixedId) {
        ss << " " << _strProp("fixed-id") << *_fixedId;
    }

    ss << std::endl;
    return ss.str();
}

InstrSetDataStreamType::InstrSetDataStreamType(const boost::optional<TypeId>& fixedId) :
    InstrSetType {fixedId}
{
    this->_setKind(Kind::SET_DATA_STREAM_TYPE);
}

InstrSetEventRecordType::InstrSetEventRecordType(const boost::optional<TypeId>& fixedId) :
    InstrSetType {fixedId}
{
    this->_setKind(Kind::SET_EVENT_RECORD_TYPE);
}

InstrSetPacketOriginIndex::InstrSetPacketOriginIndex()
{
    this->_setKind(Kind::SET_PACKET_ORIGIN_INDEX);
}

InstrSetDataStreamId::InstrSetDataStreamId()
{
    this->_setKind(Kind::SET_DATA_STREAM_ID);
}

InstrSetPacketTotalSize::InstrSetPacketTotalSize()
{
    this->_setKind(Kind::SET_PACKET_TOTAL_SIZE);
}

InstrSetPacketContentSize::InstrSetPacketContentSize()
{
    this->_setKind(Kind::SET_PACKET_CONTENT_SIZE);
}

InstrUpdateClockValue::InstrUpdateClockValue(const ClockType& clockType,
                                             const Index index,
                                             const Size size) :
    _clockType {&clockType},
    _index {index},
    _size {size}
{
    assert(size <= 64);
    this->_setKind(Kind::UPDATE_CLOCK_VALUE);
}

std::string InstrUpdateClockValue::_toString(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("clock-type") << _clockType <<
          " " << _strProp("index") << _index <<
          " " << _strProp("size") << _size << std::endl;
    return ss.str();
}

InstrSetPacketMagicNumber::InstrSetPacketMagicNumber()
{
    this->_setKind(Kind::SET_PACKET_MAGIC_NUMBER);
}

InstrEndPacketPreambleProc::InstrEndPacketPreambleProc()
{
    this->_setKind(Kind::END_PACKET_PREAMBLE_PROC);
}

InstrEndDstPacketPreambleProc::InstrEndDstPacketPreambleProc()
{
    this->_setKind(Kind::END_DST_PACKET_PREAMBLE_PROC);
}

InstrEndDstErtPreambleProc::InstrEndDstErtPreambleProc()
{
    this->_setKind(Kind::END_DST_ERT_PREAMBLE_PROC);
}

InstrEndErtProc::InstrEndErtProc()
{
    this->_setKind(Kind::END_ERT_PROC);
}

InstrDecrRemainingElements::InstrDecrRemainingElements()
{
    this->_setKind(Kind::DECR_REMAINING_ELEMENTS);
}

EventRecordTypeProc::EventRecordTypeProc(const EventRecordType& eventRecordType) :
    _eventRecordType {&eventRecordType}
{
}

void EventRecordTypeProc::buildRawProcFromShared()
{
    _proc.buildRawProcFromShared();
}

std::string EventRecordTypeProc::toString(const Size indent) const
{
    std::ostringstream ss;

    ss << utils::indent(indent) << _strTopName("event record type proc") << " " <<
          _strProp("event-record-type-id") << _eventRecordType->id();

    if (_eventRecordType->name()) {
          ss << " " << _strProp("event-record-type-name") << "`" <<
                *_eventRecordType->name() << "`";
    }

    ss << std::endl;
    ss << utils::indent(indent + 1) << "<procedure>" << std::endl;
    ss << _proc.toString(indent + 2);
    return ss.str();
}

InstrLocation EventRecordTypeProc::findInstr(const FieldRef& fieldRef)
{
    assert(fieldRef.scope() == Scope::EVENT_RECORD_SECOND_CONTEXT ||
           fieldRef.scope() == Scope::EVENT_RECORD_PAYLOAD);

    for (auto& instr : _proc) {
        if (!instr->isBeginReadScope()) {
            continue;
        }

        auto& instrReadScope = instrAsBeginReadScope(*instr);

        if (instrReadScope.scope() != fieldRef.scope()) {
            continue;
        }

        auto loc = instrReadScope.findInstr(fieldRef);

        if (loc.proc) {
            return loc;
        }
    }

    return {};
}

DataStreamTypePacketProc::DataStreamTypePacketProc(const DataStreamType& dataStreamType) :
    _dataStreamType {&dataStreamType}
{
    /*
     * Allocate twice the event record type count so that we tolerate
     * small "holes" in the event record type ID span.
     */
    _eventRecordTypeProcsVec.resize(dataStreamType.eventRecordTypes().size() * 2);
}

void DataStreamTypePacketProc::buildRawProcFromShared()
{
    _packetPreambleProc.buildRawProcFromShared();
    _eventRecordPreambleProc.buildRawProcFromShared();

    this->forEachEventRecordTypeProc([](EventRecordTypeProc& ertProc) {
        ertProc.buildRawProcFromShared();
    });
}

void DataStreamTypePacketProc::forEachEventRecordTypeProc(ForEachEventRecordTypeProcFunc func)
{
    for (auto& ertProcUp : _eventRecordTypeProcsVec) {
        if (ertProcUp) {
            func(*ertProcUp);
        }
    }

    for (auto& idErtProcUpPair : _eventRecordTypeProcsMap) {
        func(*idErtProcUpPair.second);
    }
}

void DataStreamTypePacketProc::addEventRecordTypeProc(std::unique_ptr<EventRecordTypeProc> ertProc)
{
    const auto id = ertProc->eventRecordType().id();

    if (id < _eventRecordTypeProcsVec.size()) {
        _eventRecordTypeProcsVec[id] = std::move(ertProc);
    } else {
        _eventRecordTypeProcsMap[id] = std::move(ertProc);
    }
}

const EventRecordTypeProc *DataStreamTypePacketProc::operator[](const TypeId id) const
{
    if (id < _eventRecordTypeProcsVec.size()) {
        return _eventRecordTypeProcsVec[id].get();
    }

    // fall back on map
    auto eventRecordTypeProcIt = _eventRecordTypeProcsMap.find(id);

    if (eventRecordTypeProcIt == std::end(_eventRecordTypeProcsMap)) {
        return nullptr;
    }

    return eventRecordTypeProcIt->second.get();
}

const EventRecordTypeProc *DataStreamTypePacketProc::singleEventRecordTypeProc() const
{
    assert(this->eventRecordTypeProcsCount() == 1);

    if (_eventRecordTypeProcsMap.size() == 1) {
        auto eventRecordTypeProcIt = std::begin(_eventRecordTypeProcsMap);

        if (eventRecordTypeProcIt == std::end(_eventRecordTypeProcsMap)) {
            return nullptr;
        }

        return eventRecordTypeProcIt->second.get();
    }

    for (auto& ertProcUp : _eventRecordTypeProcsVec) {
        if (ertProcUp) {
            return ertProcUp.get();
        }
    }

    return nullptr;
}

std::string DataStreamTypePacketProc::toString(const Size indent) const
{
    std::ostringstream ss;

    ss << utils::indent(indent) << _strTopName("data stream type packet proc") << " " <<
          _strProp("data-stream-type-id") <<
          _dataStreamType->id() << std::endl;
    ss << utils::indent(indent + 1) << "<packet preamble procedure>" << std::endl;
    ss << _packetPreambleProc.toString(indent + 2);
    ss << utils::indent(indent + 1) << "<event record preamble procedure>" << std::endl;
    ss << _eventRecordPreambleProc.toString(indent + 2);

    if (this->eventRecordTypeProcsCount() > 0) {
        ss << utils::indent(indent + 1) << "<event record type procs>" << std::endl;

        for (const auto& ertProcUp : _eventRecordTypeProcsVec) {
            if (ertProcUp) {
                ss << ertProcUp->toString(indent + 2);
            }
        }

        for (const auto& idEventRecordTypeProcUpPair : _eventRecordTypeProcsMap) {
            ss << idEventRecordTypeProcUpPair.second->toString(indent + 2);
        }
    }

    return ss.str();
}

InstrLocation DataStreamTypePacketProc::findInstr(const FieldRef& fieldRef)
{
    assert(fieldRef.scope() == Scope::PACKET_CONTEXT ||
           fieldRef.scope() == Scope::EVENT_RECORD_HEADER ||
           fieldRef.scope() == Scope::EVENT_RECORD_FIRST_CONTEXT);

    if (fieldRef.scope() == Scope::PACKET_CONTEXT) {
        for (auto& instr : _packetPreambleProc) {
            if (!instr->isBeginReadScope()) {
                continue;
            }

            auto loc = instrAsBeginReadScope(*instr).findInstr(fieldRef);

            if (loc.proc) {
                return loc;
            }
        }

        return {};
    }

    for (auto& instr : _eventRecordPreambleProc) {
        if (!instr->isBeginReadScope()) {
            continue;
        }

        auto& instrReadScope = instrAsBeginReadScope(*instr);

        if (instrReadScope.scope() != fieldRef.scope()) {
            continue;
        }

        auto loc = instrReadScope.findInstr(fieldRef);

        if (loc.proc) {
            return loc;
        }
    }

    return {};
}

PacketProc::PacketProc(const TraceType &traceType) :
    _traceType {&traceType}
{
}

void PacketProc::buildRawProcFromShared()
{
    _preambleProc.buildRawProcFromShared();

    for (const auto& idDataStreamTypePacketProcUpPair : _dataStreamTypePacketProcs) {
        idDataStreamTypePacketProcUpPair.second->buildRawProcFromShared();
    }
}

const DataStreamTypePacketProc *PacketProc::operator[](const TypeId id) const
{
    auto dataStreamTypePacketProcIt = _dataStreamTypePacketProcs.find(id);

    if (dataStreamTypePacketProcIt == std::end(_dataStreamTypePacketProcs)) {
        return nullptr;
    }

    return dataStreamTypePacketProcIt->second.get();
}

const DataStreamTypePacketProc *PacketProc::singleDataStreamTypePacketProc() const
{
    auto dataStreamTypePacketProcIt = std::begin(_dataStreamTypePacketProcs);

    if (dataStreamTypePacketProcIt == std::end(_dataStreamTypePacketProcs)) {
        return nullptr;
    }

    return dataStreamTypePacketProcIt->second.get();
}

std::string PacketProc::toString(const Size indent) const
{
    std::ostringstream ss;

    ss << utils::indent(indent) << _strTopName("packet proc") << " " <<
          _strProp("saved-values-count") << _savedValuesCounts << std::endl;

    if (!_indexedClockTypes.empty()) {
        Index i = 0;

        ss << utils::indent(indent + 1) << "<indexed clock types>" << std::endl;

        for (auto clockType : _indexedClockTypes) {
            ss << utils::indent(indent + 2) << i << ": \033[1m" <<
                  clockType->name().c_str() <<
                  "\033[0m (" << clockType << ")" << std::endl;
            ++i;
        }
    }

    ss << utils::indent(indent + 1) << "<preamble procedure>" << std::endl;
    ss << _preambleProc.toString(indent + 2);

    if (!_dataStreamTypePacketProcs.empty()) {
        ss << utils::indent(indent + 1) << "<data stream type procs>" << std::endl;

        for (const auto& idDataStreamTypePacketProcUpPair : _dataStreamTypePacketProcs) {
            ss << idDataStreamTypePacketProcUpPair.second->toString(indent + 2);
        }
    }

    return ss.str();
}

InstrLocation PacketProc::findInstr(const FieldRef& fieldRef)
{
    assert(fieldRef.scope() == Scope::PACKET_HEADER);

    for (auto& instr : _preambleProc) {
        if (!instr->isBeginReadScope()) {
            continue;
        }

        return instrAsBeginReadScope(*instr).findInstr(fieldRef);
    }

    return {};
}

Index PacketProc::clockTypeIndex(const std::string& clockTypeName)
{
    // check if this clock type is already indexed
    auto pred = [&clockTypeName](const ClockType *ccType) {
        return ccType->name() == clockTypeName;
    };
    auto ccIt = std::find_if(std::begin(_indexedClockTypes),
                             std::end(_indexedClockTypes), pred);
    Index index;

    if (ccIt != std::end(_indexedClockTypes)) {
        index = std::distance(std::begin(_indexedClockTypes), ccIt);
    } else {
        // find and index clock type
        index = _indexedClockTypes.size();

        auto ccType = _traceType->findClockType(clockTypeName);

        assert(ccType);
        _indexedClockTypes.push_back(ccType);
    }

    return index;
}

} // namespace internal
} // namespace yactfr
