/*
 * Copyright (C) 2016-2024 Philippe Proulx <eepp.ca>
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

std::string Instr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << std::endl;
    return ss.str();
}

static bool isEndProc(const Instr& instr) noexcept
{
    switch (instr.kind()) {
    case Instr::Kind::END_DS_ER_PREAMBLE_PROC:
    case Instr::Kind::END_DS_PKT_PREAMBLE_PROC:
    case Instr::Kind::END_ER_PROC:
    case Instr::Kind::END_PKT_PREAMBLE_PROC:
        return true;

    default:
        return false;
    }
}

std::string Instr::toStr(const Size indent) const
{
    std::string kindStr;

    switch (_theKind) {
    case Kind::UNSET:
        kindStr = "UNSET";
        break;

    case Kind::READ_FL_BIT_ARRAY_LE:
        kindStr = "READ_FL_BIT_ARRAY_LE";
        break;

    case Kind::READ_FL_BIT_ARRAY_BE:
        kindStr = "READ_FL_BIT_ARRAY_BE";
        break;

    case Kind::READ_FL_BIT_ARRAY_A8:
        kindStr = "READ_FL_BIT_ARRAY_A8";
        break;

    case Kind::READ_FL_BIT_ARRAY_A16_LE:
        kindStr = "READ_FL_BIT_ARRAY_A16_LE";
        break;

    case Kind::READ_FL_BIT_ARRAY_A32_LE:
        kindStr = "READ_FL_BIT_ARRAY_A32_LE";
        break;

    case Kind::READ_FL_BIT_ARRAY_A64_LE:
        kindStr = "READ_FL_BIT_ARRAY_A64_LE";
        break;

    case Kind::READ_FL_BIT_ARRAY_A16_BE:
        kindStr = "READ_FL_BIT_ARRAY_A16_BE";
        break;

    case Kind::READ_FL_BIT_ARRAY_A32_BE:
        kindStr = "READ_FL_BIT_ARRAY_A32_BE";
        break;

    case Kind::READ_FL_BIT_ARRAY_A64_BE:
        kindStr = "READ_FL_BIT_ARRAY_A64_BE";
        break;

    case Kind::READ_FL_BOOL_LE:
        kindStr = "READ_FL_BOOL_LE";
        break;

    case Kind::READ_FL_BOOL_BE:
        kindStr = "READ_FL_BOOL_BE";
        break;

    case Kind::READ_FL_BOOL_A8:
        kindStr = "READ_FL_BOOL_A8";
        break;

    case Kind::READ_FL_BOOL_A16_LE:
        kindStr = "READ_FL_BOOL_A16_LE";
        break;

    case Kind::READ_FL_BOOL_A32_LE:
        kindStr = "READ_FL_BOOL_A32_LE";
        break;

    case Kind::READ_FL_BOOL_A64_LE:
        kindStr = "READ_FL_BOOL_A64_LE";
        break;

    case Kind::READ_FL_BOOL_A16_BE:
        kindStr = "READ_FL_BOOL_A16_BE";
        break;

    case Kind::READ_FL_BOOL_A32_BE:
        kindStr = "READ_FL_BOOL_A32_BE";
        break;

    case Kind::READ_FL_BOOL_A64_BE:
        kindStr = "READ_FL_BOOL_A64_BE";
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

    case Kind::READ_VL_UINT:
        kindStr = "READ_VL_UINT";
        break;

    case Kind::READ_VL_SINT:
        kindStr = "READ_VL_SINT";
        break;

    case Kind::READ_NT_STR_UTF_8:
        kindStr = "READ_NT_STR_UTF_8";
        break;

    case Kind::READ_NT_STR_UTF_16:
        kindStr = "READ_NT_STR_UTF_16";
        break;

    case Kind::READ_NT_STR_UTF_32:
        kindStr = "READ_NT_STR_UTF_32";
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

    case Kind::BEGIN_READ_SL_ARRAY:
        kindStr = "BEGIN_READ_SL_ARRAY";
        break;

    case Kind::END_READ_SL_ARRAY:
        kindStr = "END_READ_SL_ARRAY";
        break;

    case Kind::BEGIN_READ_SL_STR:
        kindStr = "BEGIN_READ_SL_STR";
        break;

    case Kind::END_READ_SL_STR:
        kindStr = "END_READ_SL_STR";
        break;

    case Kind::BEGIN_READ_SL_UUID_ARRAY:
        kindStr = "BEGIN_READ_SL_UUID_ARRAY";
        break;

    case Kind::BEGIN_READ_DL_ARRAY:
        kindStr = "BEGIN_READ_DL_ARRAY";
        break;

    case Kind::END_READ_DL_ARRAY:
        kindStr = "END_READ_DL_ARRAY";
        break;

    case Kind::BEGIN_READ_DL_STR:
        kindStr = "BEGIN_READ_DL_STR";
        break;

    case Kind::END_READ_DL_STR:
        kindStr = "END_READ_DL_STR";
        break;

    case Kind::BEGIN_READ_SL_BLOB:
        kindStr = "BEGIN_READ_SL_BLOB";
        break;

    case Kind::BEGIN_READ_SL_UUID_BLOB:
        kindStr = "BEGIN_READ_SL_UUID_BLOB";
        break;

    case Kind::END_READ_SL_BLOB:
        kindStr = "END_READ_SL_BLOB";
        break;

    case Kind::BEGIN_READ_DL_BLOB:
        kindStr = "BEGIN_READ_DL_BLOB";
        break;

    case Kind::END_READ_DL_BLOB:
        kindStr = "END_READ_DL_BLOB";
        break;

    case Kind::BEGIN_READ_VAR_SINT_SEL:
        kindStr = "BEGIN_READ_VAR_SINT_SEL";
        break;

    case Kind::BEGIN_READ_VAR_UINT_SEL:
        kindStr = "BEGIN_READ_VAR_UINT_SEL";
        break;

    case Kind::BEGIN_READ_OPT_BOOL_SEL:
        kindStr = "BEGIN_READ_OPT_BOOL_SEL";
        break;

    case Kind::BEGIN_READ_OPT_SINT_SEL:
        kindStr = "BEGIN_READ_OPT_SINT_SEL";
        break;

    case Kind::BEGIN_READ_OPT_UINT_SEL:
        kindStr = "BEGIN_READ_OPT_UINT_SEL";
        break;

    case Kind::END_READ_VAR_SINT_SEL:
        kindStr = "END_READ_VAR_SINT_SEL";
        break;

    case Kind::END_READ_VAR_UINT_SEL:
        kindStr = "END_READ_VAR_UINT_SEL";
        break;

    case Kind::END_READ_OPT_BOOL_SEL:
        kindStr = "END_READ_OPT_BOOL_SEL";
        break;

    case Kind::END_READ_OPT_SINT_SEL:
        kindStr = "END_READ_OPT_SINT_SEL";
        break;

    case Kind::END_READ_OPT_UINT_SEL:
        kindStr = "END_READ_OPT_UINT_SEL";
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

    case Kind::UPDATE_DEF_CLK_VAL_FL:
        kindStr = "UPDATE_DEF_CLK_VAL_FL";
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

    case Kind::SET_PKT_SEQ_NUM:
        kindStr = "SET_PKT_SEQ_NUM";
        break;

    case Kind::SET_PKT_DISC_ER_COUNTER_SNAP:
        kindStr = "SET_PKT_DISC_ER_COUNTER_SNAP";
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

    if (this->isBeginReadData() || _theKind == Instr::Kind::BEGIN_READ_SCOPE) {
        ss << _strName(kindStr);
    } else if (this->isEndReadData() || _theKind == Kind::END_READ_SCOPE || isEndProc(*this)) {
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
                  *_memberType->displayName() << "`";
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

std::string SaveValInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << " " << _strProp("pos") << _pos << " " << std::endl;
    return ss.str();
}

SetPktEndDefClkValInstr::SetPktEndDefClkValInstr() :
    Instr {Kind::SET_PKT_END_DEF_CLK_VAL}
{
}

static inline Instr::Kind kindFromFlBitArrayType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthBitArrayType());

    auto kind = Instr::Kind::UNSET;
    auto& bitArrayType = dt.asFixedLengthBitArrayType();

    if (bitArrayType.byteOrder() == ByteOrder::LITTLE) {
        kind = Instr::Kind::READ_FL_BIT_ARRAY_LE;

        if (dt.alignment() % 8 == 0) {
            switch (bitArrayType.length()) {
            case 8:
                return Instr::Kind::READ_FL_BIT_ARRAY_A8;

            case 16:
                return Instr::Kind::READ_FL_BIT_ARRAY_A16_LE;

            case 32:
                return Instr::Kind::READ_FL_BIT_ARRAY_A32_LE;

            case 64:
                return Instr::Kind::READ_FL_BIT_ARRAY_A64_LE;

            default:
                break;
            }
        }
    } else {
        kind = Instr::Kind::READ_FL_BIT_ARRAY_BE;

        if (dt.alignment() % 8 == 0) {
            switch (bitArrayType.length()) {
            case 8:
                return Instr::Kind::READ_FL_BIT_ARRAY_A8;

            case 16:
                return Instr::Kind::READ_FL_BIT_ARRAY_A16_BE;

            case 32:
                return Instr::Kind::READ_FL_BIT_ARRAY_A32_BE;

            case 64:
                return Instr::Kind::READ_FL_BIT_ARRAY_A64_BE;

            default:
                break;
            }
        }
    }

    assert(kind != Instr::Kind::UNSET);
    return kind;
}

ReadFlBitArrayInstr::ReadFlBitArrayInstr(const Kind kind, const StructureMemberType * const member,
                                         const DataType& dt) :
    ReadDataInstr {kind, member, dt},
    _len {dt.asFixedLengthBitArrayType().length()},
    _bo {dt.asFixedLengthBitArrayType().byteOrder()}
{
}

ReadFlBitArrayInstr::ReadFlBitArrayInstr(const StructureMemberType * const member,
                                         const DataType& dt) :
    ReadFlBitArrayInstr {kindFromFlBitArrayType(dt), member, dt}
{
}

std::string ReadFlBitArrayInstr::_toStr(Size) const
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

static inline Instr::Kind kindFromFlBoolType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthBooleanType());

    auto kind = Instr::Kind::UNSET;
    auto& boolType = dt.asFixedLengthBooleanType();

    if (boolType.byteOrder() == ByteOrder::LITTLE) {
        kind = Instr::Kind::READ_FL_BOOL_LE;

        if (dt.alignment() % 8 == 0) {
            switch (boolType.length()) {
            case 8:
                return Instr::Kind::READ_FL_BOOL_A8;

            case 16:
                return Instr::Kind::READ_FL_BOOL_A16_LE;

            case 32:
                return Instr::Kind::READ_FL_BOOL_A32_LE;

            case 64:
                return Instr::Kind::READ_FL_BOOL_A64_LE;

            default:
                break;
            }
        }
    } else {
        kind = Instr::Kind::READ_FL_BOOL_BE;

        if (dt.alignment() % 8 == 0) {
            switch (boolType.length()) {
            case 8:
                return Instr::Kind::READ_FL_BOOL_A8;

            case 16:
                return Instr::Kind::READ_FL_BOOL_A16_BE;

            case 32:
                return Instr::Kind::READ_FL_BOOL_A32_BE;

            case 64:
                return Instr::Kind::READ_FL_BOOL_A64_BE;

            default:
                break;
            }
        }
    }

    assert(kind != Instr::Kind::UNSET);
    return kind;
}

ReadFlBoolInstr::ReadFlBoolInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlBitArrayInstr {kindFromFlBoolType(dt), member, dt}
{
    assert(dt.isFixedLengthBooleanType());
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

    auto kind = Instr::Kind::UNSET;
    const auto& bitArrayType = dt.asFixedLengthBitArrayType();

    if (dt.isFixedLengthUnsignedIntegerType()) {
        if (bitArrayType.byteOrder() == ByteOrder::LITTLE) {
            kind = Instr::Kind::READ_FL_UINT_LE;

            if (dt.alignment() % 8 == 0) {
                switch (bitArrayType.length()) {
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
                switch (bitArrayType.length()) {
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
        if (bitArrayType.byteOrder() == ByteOrder::LITTLE) {
            kind = Instr::Kind::READ_FL_SINT_LE;

            if (dt.alignment() % 8 == 0) {
                switch (bitArrayType.length()) {
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
                switch (bitArrayType.length()) {
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

std::string ReadFlSIntInstr::_toStr(Size) const
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

std::string ReadFlUIntInstr::_toStr(Size) const
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

static inline Instr::Kind kindFromVlIntType(const DataType& dt) noexcept
{
    assert(dt.isVariableLengthIntegerType());

    if (dt.isVariableLengthUnsignedIntegerType()) {
        return Instr::Kind::READ_VL_UINT;
    } else {
        assert(dt.isVariableLengthSignedIntegerType());
        return Instr::Kind::READ_VL_SINT;
    }
}

ReadVlIntInstr::ReadVlIntInstr(const StructureMemberType * const member,
                                         const DataType& dt) :
    ReadDataInstr {kindFromVlIntType(dt), member, dt}
{
}

std::string ReadVlIntInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

static inline Instr::Kind kindFromNtStrType(const NullTerminatedStringType& dt) noexcept
{
    switch (dt.encoding()) {
    case StringEncoding::UTF_8:
        return Instr::Kind::READ_NT_STR_UTF_8;

    case StringEncoding::UTF_16BE:
    case StringEncoding::UTF_16LE:
        return Instr::Kind::READ_NT_STR_UTF_16;

    case StringEncoding::UTF_32BE:
    case StringEncoding::UTF_32LE:
        return Instr::Kind::READ_NT_STR_UTF_32;
    }

    std::abort();
}

ReadNtStrInstr::ReadNtStrInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadDataInstr {kindFromNtStrType(dt.asNullTerminatedStringType()), member, dt}
{
}

std::string ReadNtStrInstr::_toStr(Size) const
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

EndReadDataInstr::EndReadDataInstr(const Kind kind, const StructureMemberType * const member,
                                   const DataType& dt) :
    ReadDataInstr {kind, member, dt}
{
    assert(kind == Kind::END_READ_STRUCT ||
           kind == Kind::END_READ_SL_ARRAY ||
           kind == Kind::END_READ_DL_ARRAY ||
           kind == Kind::END_READ_SL_STR ||
           kind == Kind::END_READ_DL_STR ||
           kind == Kind::END_READ_SL_BLOB ||
           kind == Kind::END_READ_DL_BLOB ||
           kind == Kind::END_READ_VAR_UINT_SEL ||
           kind == Kind::END_READ_VAR_SINT_SEL ||
           kind == Kind::END_READ_OPT_BOOL_SEL ||
           kind == Kind::END_READ_OPT_UINT_SEL ||
           kind == Kind::END_READ_OPT_SINT_SEL);
}

std::string EndReadDataInstr::_toStr(Size) const
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

BeginReadVarUIntSelInstr::BeginReadVarUIntSelInstr(const StructureMemberType * const memberType,
                                                   const DataType& dt) :
    BeginReadVarInstr {memberType, dt}
{
}

BeginReadVarSIntSelInstr::BeginReadVarSIntSelInstr(const StructureMemberType * const memberType,
                                                   const DataType& dt) :
    BeginReadVarInstr {memberType, dt}
{
}

BeginReadOptInstr::BeginReadOptInstr(const Kind kind, const StructureMemberType * const memberType,
                                     const DataType& dt) :
    BeginReadCompoundInstr {kind, memberType, dt}
{
}

std::string BeginReadOptInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("sel-pos") << _selPos << std::endl <<
          this->_procToStr(indent + 1);
    return ss.str();
}

BeginReadOptBoolSelInstr::BeginReadOptBoolSelInstr(const StructureMemberType * const memberType,
                                                   const DataType& dt) :
    BeginReadOptInstr {Kind::BEGIN_READ_OPT_BOOL_SEL, memberType, dt}
{
}

BeginReadOptUIntSelInstr::BeginReadOptUIntSelInstr(const StructureMemberType * const memberType,
                                                   const DataType& dt) :
    BeginReadOptIntSelInstr {memberType, dt}
{
}

BeginReadOptSIntSelInstr::BeginReadOptSIntSelInstr(const StructureMemberType * const memberType,
                                                   const DataType& dt) :
    BeginReadOptIntSelInstr {memberType, dt}
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

    ss << " " << _strProp("scope") << _strScopeName(scopeStr(_scope)) <<
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

std::string EndReadScopeInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << " " << _strProp("scope") << scopeStr(_scope) << std::endl;
    return ss.str();
}

BeginReadSlArrayInstr::BeginReadSlArrayInstr(const Kind kind,
                                             const StructureMemberType * const member,
                                             const DataType& dt) :
    BeginReadCompoundInstr {kind, member, dt},
    _len {dt.asStaticLengthArrayType().length()}
{
}

BeginReadSlArrayInstr::BeginReadSlArrayInstr(const StructureMemberType * const member,
                                             const DataType& dt) :
    BeginReadSlArrayInstr {Kind::BEGIN_READ_SL_ARRAY, member, dt}
{
}

std::string BeginReadSlArrayInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("len") << _len << std::endl <<
          this->_procToStr(indent + 1);
    return ss.str();
}

BeginReadSlStrInstr::BeginReadSlStrInstr(const StructureMemberType * const member,
                                         const DataType& dt) :
    ReadDataInstr {Kind::BEGIN_READ_SL_STR, member, dt},
    _maxLen {dt.asStaticLengthStringType().maximumLength()}
{
}

std::string BeginReadSlStrInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("max-len") << _maxLen << std::endl;
    return ss.str();
}

BeginReadSlUuidArrayInstr::BeginReadSlUuidArrayInstr(const StructureMemberType * const member,
                                                     const DataType& dt) :
    BeginReadSlArrayInstr {Kind::BEGIN_READ_SL_UUID_ARRAY, member, dt}
{
}

BeginReadDlArrayInstr::BeginReadDlArrayInstr(const StructureMemberType * const member,
                                             const DataType& dt) :
    BeginReadCompoundInstr {Kind::BEGIN_READ_DL_ARRAY, member, dt}
{
}

std::string BeginReadDlArrayInstr::_toStr(const Size indent) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("len-pos") << _lenPos << std::endl <<
          this->_procToStr(indent + 1);
    return ss.str();
}

BeginReadDlStrInstr::BeginReadDlStrInstr(const StructureMemberType * const member,
                                         const DataType& dt) :
    ReadDataInstr {Kind::BEGIN_READ_DL_STR, member, dt}
{
}

std::string BeginReadDlStrInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("max-len-pos") << _maxLenPos << std::endl;
    return ss.str();
}

BeginReadSlBlobInstr::BeginReadSlBlobInstr(const Kind kind, const StructureMemberType * const member,
                                           const DataType& dt) :
    ReadDataInstr {kind, member, dt},
    _len {dt.asStaticLengthBlobType().length()}
{
}

BeginReadSlBlobInstr::BeginReadSlBlobInstr(const StructureMemberType * const member,
                                           const DataType& dt) :
    BeginReadSlBlobInstr {Kind::BEGIN_READ_SL_BLOB, member, dt}
{
}

std::string BeginReadSlBlobInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("len") << _len << std::endl;
    return ss.str();
}

BeginReadSlUuidBlobInstr::BeginReadSlUuidBlobInstr(const StructureMemberType * const member,
                                                     const DataType& dt) :
    BeginReadSlBlobInstr {Kind::BEGIN_READ_SL_UUID_BLOB, member, dt}
{
}

BeginReadDlBlobInstr::BeginReadDlBlobInstr(const StructureMemberType * const member,
                                           const DataType& dt) :
    ReadDataInstr {Kind::BEGIN_READ_DL_BLOB, member, dt}
{
}

std::string BeginReadDlBlobInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("len-pos") << _lenPos << std::endl;
    return ss.str();
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

std::string SetTypeInstr::_toStr(Size) const
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

SetPktSeqNumInstr::SetPktSeqNumInstr() :
    Instr {Kind::SET_PKT_SEQ_NUM}
{
}

SetPktDiscErCounterSnapInstr::SetPktDiscErCounterSnapInstr() :
    Instr {Kind::SET_PKT_DISC_ER_COUNTER_SNAP}
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

UpdateDefClkValInstr::UpdateDefClkValInstr() :
    Instr {Kind::UPDATE_DEF_CLK_VAL}
{
}

UpdateDefClkValInstr::UpdateDefClkValInstr(const Instr::Kind kind) :
    Instr {kind}
{
}


UpdateDefClkValFlInstr::UpdateDefClkValFlInstr(const Size len) :
    UpdateDefClkValInstr {Kind::UPDATE_DEF_CLK_VAL_FL},
    _len {len}
{
    assert(len <= 64);
}

std::string UpdateDefClkValFlInstr::_toStr(Size) const
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
