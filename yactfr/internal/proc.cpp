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
namespace {

std::string _strName(const std::string& name)
{
    std::string rName;

    rName = "[\033[1m\033[36m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

std::string _strEndName(const std::string& name)
{
    std::string rName;

    rName = "[\033[1m\033[32m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

std::string _strSpecName(const std::string& name)
{
    std::string rName;

    rName = "[\033[1m\033[33m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

std::string _strTopName(const std::string& name)
{
    std::string rName;

    rName = "{\033[1m\033[35m";
    rName += name;
    rName += "\033[0m}";
    return rName;
}

std::string _strScopeName(const std::string& name)
{
    std::string rName;

    rName = "|\033[1m\033[33m";
    rName += name;
    rName += "\033[0m|";
    return rName;
}

} // namespace

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

namespace {

bool isEndProc(const Instr& instr) noexcept
{
    switch (instr.kind()) {
    case Instr::Kind::EndDsErPreambleProc:
    case Instr::Kind::EndDsPktPreambleProc:
    case Instr::Kind::EndErProc:
    case Instr::Kind::EndPktPreambleProc:
        return true;

    default:
        return false;
    }
}

} // namespace

std::string Instr::toStr(const Size indent) const
{
    const std::string kindStr {wise_enum::to_string(_theKind)};
    std::ostringstream ss;

    ss << internal::indent(indent);

    if (this->isBeginReadData() || _theKind == Instr::Kind::BeginReadScope) {
        ss << _strName(kindStr);
    } else if (this->isEndReadData() || _theKind == Kind::EndReadScope || isEndProc(*this)) {
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
    Instr {Kind::SaveVal},
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
    Instr {Kind::SetPktEndDefClkVal}
{
}

namespace {

Instr::Kind kindFromFlBitArrayType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthBitArrayType());

    auto kind = Instr::Kind::Unset;
    auto& bitArrayType = dt.asFixedLengthBitArrayType();

    if (bitArrayType.byteOrder() == ByteOrder::Little) {
        if (bitArrayType.bitOrder() == BitOrder::FirstToLast) {
            kind = Instr::Kind::ReadFlBitArrayLe;

            if (dt.alignment() % 8 == 0) {
                switch (bitArrayType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitArrayA8;

                case 16:
                    return Instr::Kind::ReadFlBitArrayA16Le;

                case 32:
                    return Instr::Kind::ReadFlBitArrayA32Le;

                case 64:
                    return Instr::Kind::ReadFlBitArrayA64Le;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::ReadFlBitArrayLeRev;

            if (dt.alignment() % 8 == 0) {
                switch (bitArrayType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitArrayA8Rev;

                case 16:
                    return Instr::Kind::ReadFlBitArrayA16LeRev;

                case 32:
                    return Instr::Kind::ReadFlBitArrayA32LeRev;

                case 64:
                    return Instr::Kind::ReadFlBitArrayA64LeRev;

                default:
                    break;
                }
            }
        }
    } else {
        if (bitArrayType.bitOrder() == BitOrder::FirstToLast) {
            kind = Instr::Kind::ReadFlBitArrayBeRev;

            if (dt.alignment() % 8 == 0) {
                switch (bitArrayType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitArrayA8Rev;

                case 16:
                    return Instr::Kind::ReadFlBitArrayA16BeRev;

                case 32:
                    return Instr::Kind::ReadFlBitArrayA32BeRev;

                case 64:
                    return Instr::Kind::ReadFlBitArrayA64BeRev;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::ReadFlBitArrayBe;

            if (dt.alignment() % 8 == 0) {
                switch (bitArrayType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitArrayA8;

                case 16:
                    return Instr::Kind::ReadFlBitArrayA16Be;

                case 32:
                    return Instr::Kind::ReadFlBitArrayA32Be;

                case 64:
                    return Instr::Kind::ReadFlBitArrayA64Be;

                default:
                    break;
                }
            }
        }
    }

    assert(kind != Instr::Kind::Unset);
    return kind;
}

} // namespace

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

namespace {

Instr::Kind kindFromFlBitMapType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthBitMapType());

    auto kind = Instr::Kind::Unset;
    auto& bitMapType = dt.asFixedLengthBitMapType();

    if (bitMapType.byteOrder() == ByteOrder::Little) {
        if (bitMapType.bitOrder() == BitOrder::FirstToLast) {
            kind = Instr::Kind::ReadFlBitMapLe;

            if (dt.alignment() % 8 == 0) {
                switch (bitMapType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitMapA8;

                case 16:
                    return Instr::Kind::ReadFlBitMapA16Le;

                case 32:
                    return Instr::Kind::ReadFlBitMapA32Le;

                case 64:
                    return Instr::Kind::ReadFlBitMapA64Le;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::ReadFlBitMapLeRev;

            if (dt.alignment() % 8 == 0) {
                switch (bitMapType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitMapA8Rev;

                case 16:
                    return Instr::Kind::ReadFlBitMapA16LeRev;

                case 32:
                    return Instr::Kind::ReadFlBitMapA32LeRev;

                case 64:
                    return Instr::Kind::ReadFlBitMapA64LeRev;

                default:
                    break;
                }
            }
        }
    } else {
        if (bitMapType.bitOrder() == BitOrder::FirstToLast) {
            kind = Instr::Kind::ReadFlBitMapBeRev;

            if (dt.alignment() % 8 == 0) {
                switch (bitMapType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitMapA8Rev;

                case 16:
                    return Instr::Kind::ReadFlBitMapA16BeRev;

                case 32:
                    return Instr::Kind::ReadFlBitMapA32BeRev;

                case 64:
                    return Instr::Kind::ReadFlBitMapA64BeRev;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::ReadFlBitMapBe;

            if (dt.alignment() % 8 == 0) {
                switch (bitMapType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBitMapA8;

                case 16:
                    return Instr::Kind::ReadFlBitMapA16Be;

                case 32:
                    return Instr::Kind::ReadFlBitMapA32Be;

                case 64:
                    return Instr::Kind::ReadFlBitMapA64Be;

                default:
                    break;
                }
            }
        }
    }

    assert(kind != Instr::Kind::Unset);
    return kind;
}

} // namespace

ReadFlBitMapInstr::ReadFlBitMapInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlBitArrayInstr {kindFromFlBitMapType(dt), member, dt}
{
    assert(dt.isFixedLengthBitMapType());
}

namespace {

Instr::Kind kindFromFlBoolType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthBooleanType());

    auto kind = Instr::Kind::Unset;
    auto& boolType = dt.asFixedLengthBooleanType();

    if (boolType.byteOrder() == ByteOrder::Little) {
        if (boolType.bitOrder() == BitOrder::FirstToLast) {
            kind = Instr::Kind::ReadFlBoolLe;

            if (dt.alignment() % 8 == 0) {
                switch (boolType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBoolA8;

                case 16:
                    return Instr::Kind::ReadFlBoolA16Le;

                case 32:
                    return Instr::Kind::ReadFlBoolA32Le;

                case 64:
                    return Instr::Kind::ReadFlBoolA64Le;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::ReadFlBoolLeRev;

            if (dt.alignment() % 8 == 0) {
                switch (boolType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBoolA8Rev;

                case 16:
                    return Instr::Kind::ReadFlBoolA16LeRev;

                case 32:
                    return Instr::Kind::ReadFlBoolA32LeRev;

                case 64:
                    return Instr::Kind::ReadFlBoolA64LeRev;

                default:
                    break;
                }
            }
        }
    } else {
        if (boolType.bitOrder() == BitOrder::FirstToLast) {
            kind = Instr::Kind::ReadFlBoolBeRev;

            if (dt.alignment() % 8 == 0) {
                switch (boolType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBoolA8Rev;

                case 16:
                    return Instr::Kind::ReadFlBoolA16BeRev;

                case 32:
                    return Instr::Kind::ReadFlBoolA32BeRev;

                case 64:
                    return Instr::Kind::ReadFlBoolA64BeRev;

                default:
                    break;
                }
            }
        } else {
            kind = Instr::Kind::ReadFlBoolBe;

            if (dt.alignment() % 8 == 0) {
                switch (boolType.length()) {
                case 8:
                    return Instr::Kind::ReadFlBoolA8;

                case 16:
                    return Instr::Kind::ReadFlBoolA16Be;

                case 32:
                    return Instr::Kind::ReadFlBoolA32Be;

                case 64:
                    return Instr::Kind::ReadFlBoolA64Be;

                default:
                    break;
                }
            }
        }
    }

    assert(kind != Instr::Kind::Unset);
    return kind;
}

} // namespace

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

namespace {

Instr::Kind kindFromFlIntType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthIntegerType());

    auto kind = Instr::Kind::Unset;
    const auto& bitArrayType = dt.asFixedLengthBitArrayType();

    if (dt.isFixedLengthUnsignedIntegerType()) {
        if (bitArrayType.byteOrder() == ByteOrder::Little) {
            if (bitArrayType.bitOrder() == BitOrder::FirstToLast) {
                kind = Instr::Kind::ReadFlUIntLe;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlUIntA8;

                    case 16:
                        return Instr::Kind::ReadFlUIntA16Le;

                    case 32:
                        return Instr::Kind::ReadFlUIntA32Le;

                    case 64:
                        return Instr::Kind::ReadFlUIntA64Le;

                    default:
                        break;
                    }
                }
            } else {
                kind = Instr::Kind::ReadFlUIntLeRev;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlUIntA8Rev;

                    case 16:
                        return Instr::Kind::ReadFlUIntA16LeRev;

                    case 32:
                        return Instr::Kind::ReadFlUIntA32LeRev;

                    case 64:
                        return Instr::Kind::ReadFlUIntA64LeRev;

                    default:
                        break;
                    }
                }
            }
        } else {
            if (bitArrayType.bitOrder() == BitOrder::FirstToLast) {
                kind = Instr::Kind::ReadFlUIntBeRev;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlUIntA8Rev;

                    case 16:
                        return Instr::Kind::ReadFlUIntA16BeRev;

                    case 32:
                        return Instr::Kind::ReadFlUIntA32BeRev;

                    case 64:
                        return Instr::Kind::ReadFlUIntA64BeRev;

                    default:
                        break;
                    }
                }
            } else {
                kind = Instr::Kind::ReadFlUIntBe;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlUIntA8;

                    case 16:
                        return Instr::Kind::ReadFlUIntA16Be;

                    case 32:
                        return Instr::Kind::ReadFlUIntA32Be;

                    case 64:
                        return Instr::Kind::ReadFlUIntA64Be;

                    default:
                        break;
                    }
                }
            }
        }
    } else {
        if (bitArrayType.byteOrder() == ByteOrder::Little) {
            if (bitArrayType.bitOrder() == BitOrder::FirstToLast) {
                kind = Instr::Kind::ReadFlSIntLe;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlSIntA8;

                    case 16:
                        return Instr::Kind::ReadFlSIntA16Le;

                    case 32:
                        return Instr::Kind::ReadFlSIntA32Le;

                    case 64:
                        return Instr::Kind::ReadFlSIntA64Le;

                    default:
                        break;
                    }
                }
            } else {
                kind = Instr::Kind::ReadFlSIntLeRev;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlSIntA8Rev;

                    case 16:
                        return Instr::Kind::ReadFlSIntA16LeRev;

                    case 32:
                        return Instr::Kind::ReadFlSIntA32LeRev;

                    case 64:
                        return Instr::Kind::ReadFlSIntA64LeRev;

                    default:
                        break;
                    }
                }
            }
        } else {
            if (bitArrayType.bitOrder() == BitOrder::FirstToLast) {
                kind = Instr::Kind::ReadFlSIntBeRev;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlSIntA8Rev;

                    case 16:
                        return Instr::Kind::ReadFlSIntA16BeRev;

                    case 32:
                        return Instr::Kind::ReadFlSIntA32BeRev;

                    case 64:
                        return Instr::Kind::ReadFlSIntA64BeRev;

                    default:
                        break;
                    }
                }
            } else {
                kind = Instr::Kind::ReadFlSIntBe;

                if (dt.alignment() % 8 == 0) {
                    switch (bitArrayType.length()) {
                    case 8:
                        return Instr::Kind::ReadFlSIntA8;

                    case 16:
                        return Instr::Kind::ReadFlSIntA16Be;

                    case 32:
                        return Instr::Kind::ReadFlSIntA32Be;

                    case 64:
                        return Instr::Kind::ReadFlSIntA64Be;

                    default:
                        break;
                    }
                }
            }
        }
    }

    assert(kind != Instr::Kind::Unset);
    return kind;
}

} // namespace

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

namespace {

Instr::Kind kindFromFlFloatType(const DataType& dt) noexcept
{
    assert(dt.isFixedLengthFloatingPointNumberType());

    const auto& floatType = dt.asFixedLengthFloatingPointNumberType();

    if (floatType.byteOrder() == ByteOrder::Little) {
        if (floatType.bitOrder() == BitOrder::FirstToLast) {
            if (dt.alignment() % 8 == 0) {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloatA32Le;

                case 64:
                    return Instr::Kind::ReadFlFloatA64Le;

                default:
                    std::abort();
                }
            } else {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloat32Le;

                case 64:
                    return Instr::Kind::ReadFlFloat64Le;

                default:
                    std::abort();
                }
            }
        } else {
            if (dt.alignment() % 8 == 0) {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloatA32LeRev;

                case 64:
                    return Instr::Kind::ReadFlFloatA64LeRev;

                default:
                    std::abort();
                }
            } else {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloat32LeRev;

                case 64:
                    return Instr::Kind::ReadFlFloat64LeRev;

                default:
                    std::abort();
                }
            }
        }
    } else {
        if (floatType.bitOrder() == BitOrder::FirstToLast) {
            if (dt.alignment() % 8 == 0) {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloatA32BeRev;

                case 64:
                    return Instr::Kind::ReadFlFloatA64BeRev;

                default:
                    std::abort();
                }
            } else {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloat32BeRev;

                case 64:
                    return Instr::Kind::ReadFlFloat64BeRev;

                default:
                    std::abort();
                }
            }
        } else {
            if (dt.alignment() % 8 == 0) {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloatA32Be;

                case 64:
                    return Instr::Kind::ReadFlFloatA64Be;

                default:
                    std::abort();
                }
            } else {
                switch (floatType.length()) {
                case 32:
                    return Instr::Kind::ReadFlFloat32Be;

                case 64:
                    return Instr::Kind::ReadFlFloat64Be;

                default:
                    std::abort();
                }
            }
        }
    }
}

} // namespace

ReadFlFloatInstr::ReadFlFloatInstr(const StructureMemberType * const member, const DataType& dt) :
    ReadFlBitArrayInstr {kindFromFlFloatType(dt), member, dt}
{
    assert(dt.isFixedLengthFloatingPointNumberType());
}

namespace {

Instr::Kind kindFromVlIntType(const DataType& dt) noexcept
{
    assert(dt.isVariableLengthIntegerType());

    if (dt.isVariableLengthUnsignedIntegerType()) {
        return Instr::Kind::ReadVlUInt;
    } else {
        assert(dt.isVariableLengthSignedIntegerType());
        return Instr::Kind::ReadVlSInt;
    }
}

} // namespace

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

namespace {

Instr::Kind kindFromNtStrType(const NullTerminatedStringType& dt) noexcept
{
    switch (dt.encoding()) {
    case StringEncoding::Utf8:
        return Instr::Kind::ReadNtStrUtf8;

    case StringEncoding::Utf16Be:
    case StringEncoding::Utf16Le:
        return Instr::Kind::ReadNtStrUtf16;

    case StringEncoding::Utf32Be:
    case StringEncoding::Utf32Le:
        return Instr::Kind::ReadNtStrUtf32;
    }

    std::abort();
}

} // namespace

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
    assert(kind == Kind::EndReadStruct ||
           kind == Kind::EndReadSlArray ||
           kind == Kind::EndReadDlArray ||
           kind == Kind::EndReadSlStr ||
           kind == Kind::EndReadDlStr ||
           kind == Kind::EndReadSlBlob ||
           kind == Kind::EndReadDlBlob ||
           kind == Kind::EndReadVarUIntSel ||
           kind == Kind::EndReadVarSIntSel ||
           kind == Kind::EndReadOptBoolSel ||
           kind == Kind::EndReadOptUIntSel ||
           kind == Kind::EndReadOptSIntSel);
}

std::string EndReadDataInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << this->_commonToStr() << std::endl;
    return ss.str();
}

BeginReadStructInstr::BeginReadStructInstr(const StructureMemberType * const member,
                                           const DataType& dt) :
    BeginReadCompoundInstr {Kind::BeginReadStruct, member, dt}
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
    BeginReadOptInstr {Kind::BeginReadOptBoolSel, memberType, dt}
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

namespace {

std::string scopeStr(const Scope scope)
{
    switch (scope) {
    case Scope::PacketHeader:
        return "PH";

    case Scope::PacketContext:
        return "PC";

    case Scope::EventRecordHeader:
        return "ERH";

    case Scope::EventRecordCommonContext:
        return "ERCC";

    case Scope::EventRecordSpecificContext:
        return "ERSC";

    case Scope::EventRecordPayload:
        return "ERP";

    default:
        std::abort();
    }
}

} // namespace

BeginReadScopeInstr::BeginReadScopeInstr(const Scope scope, const unsigned int align) :
    Instr {Kind::BeginReadScope},
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
    Instr {Kind::EndReadScope},
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
    BeginReadSlArrayInstr {Kind::BeginReadSlArray, member, dt}
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
    ReadDataInstr {Kind::BeginReadSlStr, member, dt},
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
    BeginReadSlArrayInstr {Kind::BeginReadSlUuidArray, member, dt}
{
}

BeginReadDlArrayInstr::BeginReadDlArrayInstr(const StructureMemberType * const member,
                                             const DataType& dt) :
    BeginReadCompoundInstr {Kind::BeginReadDlArray, member, dt}
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
    ReadDataInstr {Kind::BeginReadDlStr, member, dt}
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
    BeginReadSlBlobInstr {Kind::BeginReadSlBlob, member, dt}
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
    BeginReadSlBlobInstr {Kind::BeginReadSlUuidBlob, member, dt}
{
}

BeginReadDlBlobInstr::BeginReadDlBlobInstr(const StructureMemberType * const member,
                                           const DataType& dt) :
    ReadDataInstr {Kind::BeginReadDlBlob, member, dt}
{
}

std::string BeginReadDlBlobInstr::_toStr(Size) const
{
    std::ostringstream ss;

    ss << ReadDataInstr::_commonToStr() << " " << _strProp("len-pos") << _lenPos << std::endl;
    return ss.str();
}

SetCurIdInstr::SetCurIdInstr() :
    Instr {Kind::SetCurId}
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
    SetTypeInstr {Kind::SetDst, std::move(fixedId)}
{
}

SetErtInstr::SetErtInstr(boost::optional<TypeId> fixedId) :
    SetTypeInstr {Kind::SetErt, std::move(fixedId)}
{
}

SetPktSeqNumInstr::SetPktSeqNumInstr() :
    Instr {Kind::SetPktSeqNum}
{
}

SetPktDiscErCounterSnapInstr::SetPktDiscErCounterSnapInstr() :
    Instr {Kind::SetPktDiscErCounterSnap}
{
}

SetDsIdInstr::SetDsIdInstr() :
    Instr {Kind::SetDsId}
{
}

SetDsInfoInstr::SetDsInfoInstr() :
    Instr {Kind::SetDsInfo}
{
}

SetPktInfoInstr::SetPktInfoInstr() :
    Instr {Kind::SetPktInfo}
{
}

SetErInfoInstr::SetErInfoInstr() :
    Instr {Kind::SetErInfo}
{
}

SetExpectedPktTotalLenInstr::SetExpectedPktTotalLenInstr() :
    Instr {Kind::SetPktTotalLen}
{
}

SetExpectedPktContentLenInstr::SetExpectedPktContentLenInstr() :
    Instr {Kind::SetPktContentLen}
{
}

UpdateDefClkValInstr::UpdateDefClkValInstr() :
    Instr {Kind::UpdateDefClkVal}
{
}

UpdateDefClkValInstr::UpdateDefClkValInstr(const Instr::Kind kind) :
    Instr {kind}
{
}


UpdateDefClkValFlInstr::UpdateDefClkValFlInstr(const Size len) :
    UpdateDefClkValInstr {Kind::UpdateDefClkValFl},
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
    Instr {Kind::SetPktMagicNumber}
{
}

EndPktPreambleProcInstr::EndPktPreambleProcInstr() :
    Instr {Kind::EndPktPreambleProc}
{
}

EndDsPktPreambleProcInstr::EndDsPktPreambleProcInstr() :
    Instr {Kind::EndDsPktPreambleProc}
{
}

EndDsErPreambleProcInstr::EndDsErPreambleProcInstr() :
    Instr {Kind::EndDsErPreambleProc}
{
}

EndErProcInstr::EndErProcInstr() :
    Instr {Kind::EndErProc}
{
}

DecrRemainingElemsInstr::DecrRemainingElemsInstr() :
    Instr {Kind::DecrRemainingElems}
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
