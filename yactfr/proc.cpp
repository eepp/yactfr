/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>

#include "proc.hpp"

namespace yactfr {
namespace internal {

static inline std::string _strName(const std::string& name)
{
    std::string rName;

    rName = "[\033[1m\033[36m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

static inline std::string _strEndName(const std::string& name)
{
    std::string rName;

    rName = "[\033[1m\033[32m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

static inline std::string _strSpecName(const std::string& name)
{
    std::string rName;

    rName = "[\033[1m\033[33m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

static inline std::string _strTopName(const std::string& name)
{
    std::string rName;

    rName = "{\033[1m\033[35m";
    rName += name;
    rName += "\033[0m}";
    return rName;
}

static inline std::string _strScopeName(const std::string& name)
{
    std::string rName;

    rName = "|\033[1m\033[33m";
    rName += name;
    rName += "\033[0m|";
    return rName;
}

void Proc::buildRawProcFromShared()
{
    // in case we call this more than once...
    _rawProc.clear();

    for (auto& instr : _sharedProc) {
        instr->buildRawProcFromShared();
        _rawProc.push_back(instr.get());
    }
}

std::string Proc::toStr(const Size indent) const
{
    std::ostringstream ss;

    for (const auto& instr : _sharedProc) {
        ss << instr->toStr(indent);
    }

    return ss.str();
}

void Proc::pushBack(std::shared_ptr<Instr> instr)
{
    _sharedProc.push_back(instr);
}

Proc::SharedIt Proc::insert(SharedIt it, std::shared_ptr<Instr> instr)
{
    return _sharedProc.insert(it, instr);
}

Instr::Instr(const Kind kind) noexcept :
    _theKind {kind}
{
}

std::string Instr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << std::endl;
    return ss.str();
}

std::string Instr::toStr(const Size indent) const
{
    std::string kindStr;

    switch (_theKind) {
    case Kind::UNSET:
        kindStr = "UNSET";
        break;

    case Kind::READ_FL_SINT_LE:
        kindStr = "READ_FL_SINT_LE";
        break;

    case Kind::READ_FL_SINT_BE:
        kindStr = "READ_FL_SINT_BE";
        break;

    case Kind::READ_FL_SINT_A8:
        kindStr = "READ_FL_SINT_A8";
        break;

    case Kind::READ_FL_SINT_A16_LE:
        kindStr = "READ_FL_SINT_A16_LE";
        break;

    case Kind::READ_FL_SINT_A32_LE:
        kindStr = "READ_FL_SINT_A32_LE";
        break;

    case Kind::READ_FL_SINT_A64_LE:
        kindStr = "READ_FL_SINT_A64_LE";
        break;

    case Kind::READ_FL_SINT_A16_BE:
        kindStr = "READ_FL_SINT_A16_BE";
        break;

    case Kind::READ_FL_SINT_A32_BE:
        kindStr = "READ_FL_SINT_A32_BE";
        break;

    case Kind::READ_FL_SINT_A64_BE:
        kindStr = "READ_FL_SINT_A64_BE";
        break;

    case Kind::READ_FL_UINT_LE:
        kindStr = "READ_FL_UINT_LE";
        break;

    case Kind::READ_FL_UINT_BE:
        kindStr = "READ_FL_UINT_BE";
        break;

    case Kind::READ_FL_UINT_A8:
        kindStr = "READ_FL_UINT_A8";
        break;

    case Kind::READ_FL_UINT_A16_LE:
        kindStr = "READ_FL_UINT_A16_LE";
        break;

    case Kind::READ_FL_UINT_A32_LE:
        kindStr = "READ_FL_UINT_A32_LE";
        break;

    case Kind::READ_FL_UINT_A64_LE:
        kindStr = "READ_FL_UINT_A64_LE";
        break;

    case Kind::READ_FL_UINT_A16_BE:
        kindStr = "READ_FL_UINT_A16_BE";
        break;

    case Kind::READ_FL_UINT_A32_BE:
        kindStr = "READ_FL_UINT_A32_BE";
        break;

    case Kind::READ_FL_UINT_A64_BE:
        kindStr = "READ_FL_UINT_A64_BE";
        break;

    case Kind::READ_FL_FLOAT_32_LE:
        kindStr = "READ_FL_FLOAT_32_LE";
        break;

    case Kind::READ_FL_FLOAT_32_BE:
        kindStr = "READ_FL_FLOAT_32_BE";
        break;

    case Kind::READ_FL_FLOAT_A32_LE:
        kindStr = "READ_FL_FLOAT_A32_LE";
        break;

    case Kind::READ_FL_FLOAT_A32_BE:
        kindStr = "READ_FL_FLOAT_A32_BE";
        break;

    case Kind::READ_FL_FLOAT_64_LE:
        kindStr = "READ_FL_FLOAT_64_LE";
        break;

    case Kind::READ_FL_FLOAT_64_BE:
        kindStr = "READ_FL_FLOAT_64_BE";
        break;

    case Kind::READ_FL_FLOAT_A64_LE:
        kindStr = "READ_FL_FLOAT_A64_LE";
        break;

    case Kind::READ_FL_FLOAT_A64_BE:
        kindStr = "READ_FL_FLOAT_A64_BE";
        break;

    case Kind::READ_FL_SENUM_LE:
        kindStr = "READ_FL_SENUM_LE";
        break;

    case Kind::READ_FL_SENUM_BE:
        kindStr = "READ_FL_SENUM_BE";
        break;

    case Kind::READ_FL_SENUM_A8:
        kindStr = "READ_FL_SENUM_A8";
        break;

    case Kind::READ_FL_SENUM_A16_LE:
        kindStr = "READ_FL_SENUM_A16_LE";
        break;

    case Kind::READ_FL_SENUM_A32_LE:
        kindStr = "READ_FL_SENUM_A32_LE";
        break;

    case Kind::READ_FL_SENUM_A64_LE:
        kindStr = "READ_FL_SENUM_A64_LE";
        break;

    case Kind::READ_FL_SENUM_A16_BE:
        kindStr = "READ_FL_SENUM_A16_BE";
        break;

    case Kind::READ_FL_SENUM_A32_BE:
        kindStr = "READ_FL_SENUM_A32_BE";
        break;

    case Kind::READ_FL_SENUM_A64_BE:
        kindStr = "READ_FL_SENUM_A64_BE";
        break;

    case Kind::READ_FL_UENUM_LE:
        kindStr = "READ_FL_UENUM_LE";
        break;

    case Kind::READ_FL_UENUM_BE:
        kindStr = "READ_FL_UENUM_BE";
        break;

    case Kind::READ_FL_UENUM_A8:
        kindStr = "READ_FL_UENUM_A8";
        break;

    case Kind::READ_FL_UENUM_A16_LE:
        kindStr = "READ_FL_UENUM_A16_LE";
        break;

    case Kind::READ_FL_UENUM_A32_LE:
        kindStr = "READ_FL_UENUM_A32_LE";
        break;

    case Kind::READ_FL_UENUM_A64_LE:
        kindStr = "READ_FL_UENUM_A64_LE";
        break;

    case Kind::READ_FL_UENUM_A16_BE:
        kindStr = "READ_FL_UENUM_A16_BE";
        break;

    case Kind::READ_FL_UENUM_A32_BE:
        kindStr = "READ_FL_UENUM_A32_BE";
        break;

    case Kind::READ_FL_UENUM_A64_BE:
        kindStr = "READ_FL_UENUM_A64_BE";
        break;

    case Kind::READ_STR:
        kindStr = "READ_STR";
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

    case Kind::BEGIN_READ_STATIC_ARRAY:
        kindStr = "BEGIN_READ_STATIC_ARRAY";
        break;

    case Kind::END_READ_STATIC_ARRAY:
        kindStr = "END_READ_STATIC_ARRAY";
        break;

    case Kind::BEGIN_READ_STATIC_TEXT_ARRAY:
        kindStr = "BEGIN_READ_STATIC_TEXT_ARRAY";
        break;

    case Kind::END_READ_STATIC_TEXT_ARRAY:
        kindStr = "END_READ_STATIC_TEXT_ARRAY";
        break;

    case Kind::BEGIN_READ_STATIC_UUID_ARRAY:
        kindStr = "BEGIN_READ_STATIC_UUID_ARRAY";
        break;

    case Kind::BEGIN_READ_DYN_ARRAY:
        kindStr = "BEGIN_READ_DYN_ARRAY";
        break;

    case Kind::END_READ_DYN_ARRAY:
        kindStr = "END_READ_DYN_ARRAY";
        break;

    case Kind::BEGIN_READ_DYN_TEXT_ARRAY:
        kindStr = "BEGIN_READ_DYN_TEXT_ARRAY";
        break;

    case Kind::END_READ_DYN_TEXT_ARRAY:
        kindStr = "END_READ_DYN_TEXT_ARRAY";
        break;

    case Kind::BEGIN_READ_VAR_SSEL:
        kindStr = "BEGIN_READ_VAR_SSEL";
        break;

    case Kind::BEGIN_READ_VAR_USEL:
        kindStr = "BEGIN_READ_VAR_USEL";
        break;

    case Kind::END_READ_VAR:
        kindStr = "END_READ_VAR";
        break;

    case Kind::SAVE_VAL:
        kindStr = "SAVE_VAL";
        break;

    case Kind::SET_PKT_END_DEF_CLK_VAL:
        kindStr = "SET_PKT_END_DEF_CLK_VAL";
        break;

    case Kind::UPDATE_DEF_CLK_VAL:
        kindStr = "UPDATE_DEF_CLK_VAL";
        break;

    case Kind::SET_CUR_ID:
        kindStr = "SET_CUR_ID";
        break;

    case Kind::SET_DST:
        kindStr = "SET_DST";
        break;

    case Kind::SET_ERT:
        kindStr = "SET_ERT";
        break;

    case Kind::SET_DS_ID:
        kindStr = "SET_DS_ID";
        break;

    case Kind::SET_PKT_ORIGIN_INDEX:
        kindStr = "SET_PKT_ORIGIN_INDEX";
        break;

    case Kind::SET_PKT_TOTAL_LEN:
        kindStr = "SET_PKT_TOTAL_LEN";
        break;

    case Kind::SET_PKT_CONTENT_LEN:
        kindStr = "SET_PKT_CONTENT_LEN";
        break;

    case Kind::SET_PKT_MAGIC_NUMBER:
        kindStr = "SET_PKT_MAGIC_NUMBER";
        break;

    case Kind::END_PKT_PREAMBLE_PROC:
        kindStr = "END_PKT_PREAMBLE_PROC";
        break;

    case Kind::END_DS_PKT_PREAMBLE_PROC:
        kindStr = "END_DS_PKT_PREAMBLE_PROC";
        break;

    case Kind::END_DS_ER_PREAMBLE_PROC:
        kindStr = "END_DS_ER_PREAMBLE_PROC";
        break;

    case Kind::END_ER_PROC:
        kindStr = "END_ER_PROC";
        break;

    case Kind::DECR_REMAINING_ELEMS:
        kindStr = "DECR_REMAINING_ELEMS";
        break;

    case Kind::SET_DS_INFO:
        kindStr = "SET_DS_INFO";
        break;

    case Kind::SET_PKT_INFO:
        kindStr = "SET_PKT_INFO";
        break;

    case Kind::SET_ER_INFO:
        kindStr = "SET_ER_INFO";
        break;

    default:
        std::abort();
    }

    std::ostringstream ss;

    ss << internal::indent(indent);

    if (this->isReadData() || this->isBeginReadScope()) {
        ss << _strName(kindStr);
    } else if (this->isEndReadCompound() || _theKind == Kind::END_READ_SCOPE || this->isEndProc()) {
        ss << _strEndName(kindStr);
    } else {
        ss << _strSpecName(kindStr);
    }

    ss << this->_toStr(indent);
    return ss.str();
}

void Instr::buildRawProcFromShared()
{
}

ReadDataInstr::ReadDataInstr(const Kind kind, const StructureMemberType * const memberType,
                             const DataType& dt) :
    Instr {kind},
    _memberType {memberType},
    _dt {&dt},
    _align {dt.alignment()}
{
}

std::string ReadDataInstr::_commonToStr() const
{
    std::ostringstream ss;

    if (_memberType) {
        ss << " " << _strProp("member-type-name") << "`" << _memberType->name() << "`";

        if (_memberType->name() != _memberType->displayName()) {
            ss << " " << _strProp("member-type-disp-name") << "`" <<
                  _memberType->displayName() << "`";
        }
    }

    ss << " " << _strProp("dt-addr") << _dt << " " << _strProp("align") << _align;

    return ss.str();
}

SaveValInstr::SaveValInstr(const Index pos) :
    Instr {Kind::SAVE_VAL},
    _pos {pos}
{
}

std::string SaveValInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("pos") << _pos << " " << std::endl;
    return ss.str();
}

SetPktEndDefClkValInstr::SetPktEndDefClkValInstr() :
    Instr {Kind::SET_PKT_END_DEF_CLK_VAL}
{
}

ReadFlBitArrayInstr::ReadFlBitArrayInstr(const Kind kind, const StructureMemberType * const member,
                                     const DataType& dt) :
    ReadDataInstr {kind, member, dt},
    _len {dt.asFixedLengthBitArrayType().length()},
    _bo {dt.asFixedLengthBitArrayType().byteOrder()}
{
}

std::string ReadFlBitArrayInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

std::string ReadFlBitArrayInstr::_commonToStr() const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr();
    ss << " " << _strProp("len") << _len;
    return ss.str();
}

ReadFlIntInstr::ReadFlIntInstr(const Kind kind, const StructureMemberType * const member,
                               const DataType& dt) :
    ReadFlBitArrayInstr {kind, member, dt}
{
    assert(dt.isFixedLengthIntegerType());
}

static inline Instr::Kind kindFromFlIntType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthIntegerType());

    Instr::Kind kind = Instr::Kind::UNSET;
    const auto& intType = dt.asFixedLengthIntegerType();

    if (dt.isFixedLengthUnsignedIntegerType()) {
        if (intType.byteOrder() == ByteOrder::LITTLE) {
            kind = Instr::Kind::READ_FL_UINT_LE;

            if (dt.alignment() % 8 == 0) {
                switch (intType.length()) {
                case 8:
                    return Instr::Kind::READ_FL_UINT_A8;

                case 16:
                    return Instr::Kind::READ_FL_UINT_A16_LE;

                case 32:
                    return Instr::Kind::READ_FL_UINT_A32_LE;

                case 64:
                    return Instr::Kind::READ_FL_UINT_A64_LE;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::READ_FL_UINT_BE;

            if (dt.alignment() % 8 == 0) {
                switch (intType.length()) {
                case 8:
                    return Instr::Kind::READ_FL_UINT_A8;

                case 16:
                    return Instr::Kind::READ_FL_UINT_A16_BE;

                case 32:
                    return Instr::Kind::READ_FL_UINT_A32_BE;

                case 64:
                    return Instr::Kind::READ_FL_UINT_A64_BE;

                default:
                    break;
                }
            }
        }
    } else {
        if (intType.byteOrder() == ByteOrder::LITTLE) {
            kind = Instr::Kind::READ_FL_SINT_LE;

            if (dt.alignment() % 8 == 0) {
                switch (intType.length()) {
                case 8:
                    return Instr::Kind::READ_FL_SINT_A8;

                case 16:
                    return Instr::Kind::READ_FL_SINT_A16_LE;

                case 32:
                    return Instr::Kind::READ_FL_SINT_A32_LE;

                case 64:
                    return Instr::Kind::READ_FL_SINT_A64_LE;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::READ_FL_SINT_BE;

            if (dt.alignment() % 8 == 0) {
                switch (intType.length()) {
                case 8:
                    return Instr::Kind::READ_FL_SINT_A8;

                case 16:
                    return Instr::Kind::READ_FL_SINT_A16_BE;

                case 32:
                    return Instr::Kind::READ_FL_SINT_A32_BE;

                case 64:
                    return Instr::Kind::READ_FL_SINT_A64_BE;

                default:
                    break;
                }
            }
        }
    }

    assert(kind != Instr::Kind::UNSET);
    return kind;
}

ReadFlSIntInstr::ReadFlSIntInstr(const Kind kind, const StructureMemberType * const member,
                                 const DataType& dt) :
    ReadFlIntInstr {kind, member, dt}
{
    assert(dt.isFixedLengthSignedIntegerType());
}

ReadFlSIntInstr::ReadFlSIntInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlSIntInstr {kindFromFlIntType(dt), member, dt}
{
}

std::string ReadFlSIntInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

ReadFlUIntInstr::ReadFlUIntInstr(const Kind kind, const StructureMemberType * const member,
                                 const DataType& dt) :
    ReadFlIntInstr {kind, member, dt}
{
    assert(dt.isFixedLengthUnsignedIntegerType());
}

ReadFlUIntInstr::ReadFlUIntInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlUIntInstr {kindFromFlIntType(dt), member, dt}
{
}

std::string ReadFlUIntInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

static inline Instr::Kind kindFromFlFloatType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthFloatingPointNumberType());

    const auto& floatType = dt.asFixedLengthFloatingPointNumberType();

    if (floatType.byteOrder() == ByteOrder::LITTLE) {
        if (dt.alignment() % 8 == 0) {
            switch (floatType.length()) {
            case 32:
                return Instr::Kind::READ_FL_FLOAT_A32_LE;

            case 64:
                return Instr::Kind::READ_FL_FLOAT_A64_LE;

            default:
                std::abort();
            }
        } else {
            switch (floatType.length()) {
            case 32:
                return Instr::Kind::READ_FL_FLOAT_32_LE;

            case 64:
                return Instr::Kind::READ_FL_FLOAT_64_LE;

            default:
                std::abort();
            }
        }
    } else {
        if (dt.alignment() % 8 == 0) {
            switch (floatType.length()) {
            case 32:
                return Instr::Kind::READ_FL_FLOAT_A32_BE;

            case 64:
                return Instr::Kind::READ_FL_FLOAT_A64_BE;

            default:
                std::abort();
            }
        } else {
            switch (floatType.length()) {
            case 32:
                return Instr::Kind::READ_FL_FLOAT_32_BE;

            case 64:
                return Instr::Kind::READ_FL_FLOAT_64_BE;

            default:
                std::abort();
            }
        }
    }
}

ReadFlFloatInstr::ReadFlFloatInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlBitArrayInstr {kindFromFlFloatType(dt), member, dt}
{
    assert(dt.isFixedLengthFloatingPointNumberType());
}

std::string ReadFlFloatInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

static inline Instr::Kind kindFromFlEnumType(const DataType& dt) noexcept
{
    switch (kindFromFlIntType(dt)) {
    case Instr::Kind::READ_FL_SINT_LE:
        return Instr::Kind::READ_FL_SENUM_LE;

    case Instr::Kind::READ_FL_SINT_BE:
        return Instr::Kind::READ_FL_SENUM_BE;

    case Instr::Kind::READ_FL_SINT_A8:
        return Instr::Kind::READ_FL_SENUM_A8;

    case Instr::Kind::READ_FL_SINT_A16_LE:
        return Instr::Kind::READ_FL_SENUM_A16_LE;

    case Instr::Kind::READ_FL_SINT_A32_LE:
        return Instr::Kind::READ_FL_SENUM_A32_LE;

    case Instr::Kind::READ_FL_SINT_A64_LE:
        return Instr::Kind::READ_FL_SENUM_A64_LE;

    case Instr::Kind::READ_FL_SINT_A16_BE:
        return Instr::Kind::READ_FL_SENUM_A16_BE;

    case Instr::Kind::READ_FL_SINT_A32_BE:
        return Instr::Kind::READ_FL_SENUM_A32_BE;

    case Instr::Kind::READ_FL_SINT_A64_BE:
        return Instr::Kind::READ_FL_SENUM_A64_BE;

    case Instr::Kind::READ_FL_UINT_LE:
        return Instr::Kind::READ_FL_UENUM_LE;

    case Instr::Kind::READ_FL_UINT_BE:
        return Instr::Kind::READ_FL_UENUM_BE;

    case Instr::Kind::READ_FL_UINT_A8:
        return Instr::Kind::READ_FL_UENUM_A8;

    case Instr::Kind::READ_FL_UINT_A16_LE:
        return Instr::Kind::READ_FL_UENUM_A16_LE;

    case Instr::Kind::READ_FL_UINT_A32_LE:
        return Instr::Kind::READ_FL_UENUM_A32_LE;

    case Instr::Kind::READ_FL_UINT_A64_LE:
        return Instr::Kind::READ_FL_UENUM_A64_LE;

    case Instr::Kind::READ_FL_UINT_A16_BE:
        return Instr::Kind::READ_FL_UENUM_A16_BE;

    case Instr::Kind::READ_FL_UINT_A32_BE:
        return Instr::Kind::READ_FL_UENUM_A32_BE;

    case Instr::Kind::READ_FL_UINT_A64_BE:
        return Instr::Kind::READ_FL_UENUM_A64_BE;

    default:
        std::abort();
    }
}

ReadFlSEnumInstr::ReadFlSEnumInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlSIntInstr {kindFromFlEnumType(dt), member, dt}
{
    assert(dt.isSignedFixedLengthEnumerationType());
}

std::string ReadFlSEnumInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

ReadFlUEnumInstr::ReadFlUEnumInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlUIntInstr {kindFromFlEnumType(dt), member, dt}
{
    assert(dt.isFixedLengthUnsignedEnumerationType());
}

std::string ReadFlUEnumInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

ReadStrInstr::ReadStrInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadDataInstr {Kind::READ_STR, member, dt}
{
    assert(dt.isStringType());
}

std::string ReadStrInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

BeginReadCompoundInstr::BeginReadCompoundInstr(const Kind kind,
                                               const StructureMemberType * const member,
                                               const DataType& dt) :
    ReadDataInstr {kind, member, dt}
{
}

void BeginReadCompoundInstr::buildRawProcFromShared()
{
    _proc.buildRawProcFromShared();
}

EndReadCompoundInstr::EndReadCompoundInstr(const Kind kind,
                                           const StructureMemberType * const member,
                                           const DataType& dt) :
    ReadDataInstr {kind, member, dt}
{
    assert(kind == Kind::END_READ_STRUCT ||
           kind == Kind::END_READ_STATIC_ARRAY ||
           kind == Kind::END_READ_STATIC_TEXT_ARRAY ||
           kind == Kind::END_READ_DYN_ARRAY ||
           kind == Kind::END_READ_DYN_TEXT_ARRAY ||
           kind == Kind::END_READ_VAR);
}

std::string EndReadCompoundInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

BeginReadStructInstr::BeginReadStructInstr(const StructureMemberType * const member,
                                           const DataType& dt) :
    BeginReadCompoundInstr {Kind::BEGIN_READ_STRUCT, member, dt}
{
    assert(dt.isStructureType());
}

std::string BeginReadStructInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    ss << this->_procToStr(indent + 1);
    return ss.str();
}

BeginReadVarUSelInstr::BeginReadVarUSelInstr(const StructureMemberType * const memberType,
                                             const DataType& dt) :
    BeginReadVarInstr {memberType, dt}
{
}

BeginReadVarSSelInstr::BeginReadVarSSelInstr(const StructureMemberType * const memberType,
                                             const DataType& dt) :
    BeginReadVarInstr {memberType, dt}
{
}

static std::string scopeStr(const Scope scope)
{
    switch (scope) {
    case Scope::PACKET_HEADER:
        return "PH";

    case Scope::PACKET_CONTEXT:
        return "PC";

    case Scope::EVENT_RECORD_HEADER:
        return "ERH";

    case Scope::EVENT_RECORD_COMMON_CONTEXT:
        return "ERCC";

    case Scope::EVENT_RECORD_SPECIFIC_CONTEXT:
        return "ERSC";

    case Scope::EVENT_RECORD_PAYLOAD:
        return "ERP";

    default:
        std::abort();
    }
}

BeginReadScopeInstr::BeginReadScopeInstr(const Scope scope, const unsigned int align) :
    Instr {Kind::BEGIN_READ_SCOPE},
    _scope {scope},
    _align {align}
{
}

std::string BeginReadScopeInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("scope") << scopeStr(_scope) <<
          " " << _strProp("align") << _align << std::endl;
    ss << _proc.toStr(indent + 1);
    return ss.str();
}

void BeginReadScopeInstr::buildRawProcFromShared()
{
    _proc.buildRawProcFromShared();
}

EndReadScopeInstr::EndReadScopeInstr(const Scope scope) :
    Instr {Kind::END_READ_SCOPE},
    _scope {scope}
{
}

std::string EndReadScopeInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("scope") << scopeStr(_scope) << std::endl;
    return ss.str();
}

BeginReadStaticArrayInstr::BeginReadStaticArrayInstr(const Kind kind,
                                                     const StructureMemberType * const member,
                                                     const DataType& dt) :
    BeginReadCompoundInstr {kind, member, dt},
    _len {dt.asStaticArrayType().length()}
{
}

BeginReadStaticArrayInstr::BeginReadStaticArrayInstr(const StructureMemberType * const member,
                                                     const DataType& dt) :
    BeginReadStaticArrayInstr {Kind::BEGIN_READ_STATIC_ARRAY, member, dt}
{
}

std::string BeginReadStaticArrayInstr::_commonToStr() const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("len") << _len;
    return ss.str();
}

std::string BeginReadStaticArrayInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl << this->_procToStr(indent + 1);
    return ss.str();
}

BeginReadStaticTextArrayInstr::BeginReadStaticTextArrayInstr(const StructureMemberType * const member,
                                                             const DataType& dt) :
    BeginReadStaticArrayInstr {Kind::BEGIN_READ_STATIC_TEXT_ARRAY, member, dt}
{
}

BeginReadStaticUuidArrayInstr::BeginReadStaticUuidArrayInstr(const StructureMemberType * const member,
                                                             const DataType& dt) :
    BeginReadStaticArrayInstr {Kind::BEGIN_READ_STATIC_UUID_ARRAY, member, dt}
{
}

BeginReadDynArrayInstr::BeginReadDynArrayInstr(const Kind kind,
                                               const StructureMemberType * const member,
                                               const DataType& dt) :
    BeginReadCompoundInstr {kind, member, dt}
{
}

BeginReadDynArrayInstr::BeginReadDynArrayInstr(const StructureMemberType * const member,
                                               const DataType& dt) :
    BeginReadDynArrayInstr {Kind::BEGIN_READ_DYN_ARRAY, member, dt}
{
}

std::string BeginReadDynArrayInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl << this->_procToStr(indent + 1);
    return ss.str();
}

std::string BeginReadDynArrayInstr::_commonToStr() const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("len-pos") << _lenPos;
    return ss.str();
}

BeginReadDynTextArrayInstr::BeginReadDynTextArrayInstr(const StructureMemberType * const member,
                                                       const DataType& dt) :
    BeginReadDynArrayInstr {Kind::BEGIN_READ_DYN_TEXT_ARRAY, member, dt}
{
}

SetCurIdInstr::SetCurIdInstr() :
    Instr {Kind::SET_CUR_ID}
{
}

SetTypeInstr::SetTypeInstr(const Kind kind, boost::optional<TypeId> fixedId) :
    Instr {kind},
    _fixedId {std::move(fixedId)}
{
}

std::string SetTypeInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    if (_fixedId) {
        ss << " " << _strProp("fixed-id") << *_fixedId;
    }

    ss << std::endl;
    return ss.str();
}

SetDstInstr::SetDstInstr(boost::optional<TypeId> fixedId) :
    SetTypeInstr {Kind::SET_DST, std::move(fixedId)}
{
}

SetErtInstr::SetErtInstr(boost::optional<TypeId> fixedId) :
    SetTypeInstr {Kind::SET_ERT, std::move(fixedId)}
{
}

SetPktOriginIndexInstr::SetPktOriginIndexInstr() :
    Instr {Kind::SET_PKT_ORIGIN_INDEX}
{
}

SetDsIdInstr::SetDsIdInstr() :
    Instr {Kind::SET_DS_ID}
{
}

SetDsInfoInstr::SetDsInfoInstr() :
    Instr {Kind::SET_DS_INFO}
{
}

SetPktInfoInstr::SetPktInfoInstr() :
    Instr {Kind::SET_PKT_INFO}
{
}

SetErInfoInstr::SetErInfoInstr() :
    Instr {Kind::SET_ER_INFO}
{
}

SetExpectedPktTotalLenInstr::SetExpectedPktTotalLenInstr() :
    Instr {Kind::SET_PKT_TOTAL_LEN}
{
}

SetExpectedPktContentLenInstr::SetExpectedPktContentLenInstr() :
    Instr {Kind::SET_PKT_CONTENT_LEN}
{
}

UpdateDefClkValInstr::UpdateDefClkValInstr(const Size len) :
    Instr {Kind::UPDATE_DEF_CLK_VAL},
    _len {len}
{
    assert(len <= 64);
}

std::string UpdateDefClkValInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << " " << _strProp("len") << _len << std::endl;
    return ss.str();
}

SetPktMagicNumberInstr::SetPktMagicNumberInstr() :
    Instr {Kind::SET_PKT_MAGIC_NUMBER}
{
}

EndPktPreambleProcInstr::EndPktPreambleProcInstr() :
    Instr {Kind::END_PKT_PREAMBLE_PROC}
{
}

EndDsPktPreambleProcInstr::EndDsPktPreambleProcInstr() :
    Instr {Kind::END_DS_PKT_PREAMBLE_PROC}
{
}

EndDsErPreambleProcInstr::EndDsErPreambleProcInstr() :
    Instr {Kind::END_DS_ER_PREAMBLE_PROC}
{
}

EndErProcInstr::EndErProcInstr() :
    Instr {Kind::END_ER_PROC}
{
}

DecrRemainingElemsInstr::DecrRemainingElemsInstr() :
    Instr {Kind::DECR_REMAINING_ELEMS}
{
}

ErProc::ErProc(const EventRecordType& eventRecordType) :
    _ert {&eventRecordType}
{
}

void ErProc::buildRawProcFromShared()
{
    _proc.buildRawProcFromShared();
}

std::string ErProc::toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << internal::indent(indent) << _strTopName("ER proc") <<
          " " << _strProp("ert-id") << _ert->id();

    if (_ert->name()) {
          ss << " " << _strProp("ert-name") << "`" << *_ert->name() << "`";
    }

    ss << std::endl;
    ss << internal::indent(indent + 1) << "<proc>" << std::endl;
    ss << _proc.toStr(indent + 2);
    return ss.str();
}

DsPktProc::DsPktProc(const DataStreamType& dst) :
    _dst {&dst}
{
    /*
     * Allocate twice the event record type count so that we tolerate
     * small "holes" in the event record type ID span.
     */
    _erProcsVec.resize(dst.eventRecordTypes().size() * 2);
}

void DsPktProc::buildRawProcFromShared()
{
    _pktPreambleProc.buildRawProcFromShared();
    _erPreambleProc.buildRawProcFromShared();

    this->forEachErProc([](ErProc& erProc) {
        erProc.buildRawProcFromShared();
    });
}

void DsPktProc::addErProc(std::unique_ptr<ErProc> erProc)
{
    const auto id = erProc->ert().id();

    if (id < _erProcsVec.size()) {
        _erProcsVec[id] = std::move(erProc);
    } else {
        _erProcsMap[id] = std::move(erProc);
    }
}

const ErProc *DsPktProc::operator[](const TypeId id) const noexcept
{
    if (id < _erProcsVec.size()) {
        return _erProcsVec[id].get();
    }

    // fall back on map
    auto erProcIt = _erProcsMap.find(id);

    if (erProcIt == _erProcsMap.end()) {
        return nullptr;
    }

    return erProcIt->second.get();
}

const ErProc *DsPktProc::singleErProc() const noexcept
{
    assert(this->erProcsCount() == 1);

    if (_erProcsMap.size() == 1) {
        auto erProcIt = _erProcsMap.begin();

        if (erProcIt == _erProcsMap.end()) {
            return nullptr;
        }

        return erProcIt->second.get();
    }

    for (auto& erProc : _erProcsVec) {
        if (erProc) {
            return erProc.get();
        }
    }

    return nullptr;
}

std::string DsPktProc::toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << internal::indent(indent) << _strTopName("DS packet proc") <<
          " " << _strProp("dst-id") << _dst->id() <<
          " " << _strProp("er-align") << _erAlign << std::endl;
    ss << internal::indent(indent + 1) << "<pkt preamble proc>" << std::endl;
    ss << _pktPreambleProc.toStr(indent + 2);
    ss << internal::indent(indent + 1) << "<ER preamble proc>" << std::endl;
    ss << _erPreambleProc.toStr(indent + 2);

    if (this->erProcsCount() > 0) {
        ss << internal::indent(indent + 1) << "<ER procs>" << std::endl;

        for (const auto& erProcUp : _erProcsVec) {
            if (erProcUp) {
                ss << erProcUp->toStr(indent + 2);
            }
        }

        for (const auto& idErProcUpPair : _erProcsMap) {
            ss << idErProcUpPair.second->toStr(indent + 2);
        }
    }

    return ss.str();
}

PktProc::PktProc(const TraceType& traceType) :
    _traceType {&traceType}
{
}

void PktProc::buildRawProcFromShared()
{
    _preambleProc.buildRawProcFromShared();

    for (const auto& idDsPktProcPair : _dsPktProcs) {
        idDsPktProcPair.second->buildRawProcFromShared();
    }
}

const DsPktProc *PktProc::operator[](const TypeId id) const noexcept
{
    auto dsPktProcIt = _dsPktProcs.find(id);

    if (dsPktProcIt == _dsPktProcs.end()) {
        return nullptr;
    }

    return dsPktProcIt->second.get();
}

const DsPktProc *PktProc::singleDsPktProc() const noexcept
{
    auto dsPktProcIt = _dsPktProcs.begin();

    if (dsPktProcIt == _dsPktProcs.end()) {
        return nullptr;
    }

    return dsPktProcIt->second.get();
}

void DsPktProc::setErAlign()
{
    assert(_dst);

    if (_dst->eventRecordHeaderType()) {
        _erAlign = _dst->eventRecordHeaderType()->alignment();
    } else if (_dst->eventRecordCommonContextType()) {
        _erAlign = _dst->eventRecordCommonContextType()->alignment();
    } else {
        assert(_dst->eventRecordTypes().size() <= 1);

        if (!_dst->eventRecordTypes().empty()) {
            auto& ert = **_dst->eventRecordTypes().begin();

            if (ert.specificContextType()) {
                _erAlign = ert.specificContextType()->alignment();
            } else if (ert.payloadType()) {
                _erAlign = ert.payloadType()->alignment();
            }
        }
    }
}

std::string PktProc::toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << internal::indent(indent) << _strTopName("pkt proc") << " " <<
          _strProp("saved-vals-count") << _savedValsCount << std::endl <<
          internal::indent(indent + 1) << "<preamble proc>" << std::endl <<
          _preambleProc.toStr(indent + 2);

    if (!_dsPktProcs.empty()) {
        ss << internal::indent(indent + 1) << "<DS pkt procs>" << std::endl;

        for (const auto& idDsPktProcPair : _dsPktProcs) {
            ss << idDsPktProcPair.second->toStr(indent + 2);
        }
    }

    return ss.str();
}

} // namespace internal
} // namespace yactfr
