/*
 * CTF integer type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/int-type.hpp>

namespace yactfr {

IntType::IntType(const int kind, const unsigned int alignment,
                 const unsigned int size, const ByteOrder byteOrder,
                 const DisplayBase displayBase, const Encoding encoding,
                 const boost::optional<std::string>& mappedClockTypeName) :
    BitArrayType {_KIND_INT | kind, alignment, size, byteOrder},
    _displayBase {displayBase},
    _encoding {encoding},
    _mappedClockTypeName {mappedClockTypeName}
{
}

bool IntType::_compare(const DataType& otherType) const noexcept
{
    auto& intType = static_cast<const IntType&>(otherType);

    return intType.alignment() == this->alignment() &&
           intType.size() == this->size() &&
           intType.byteOrder() == this->byteOrder() &&
           intType.displayBase() == this->displayBase() &&
           intType.encoding() == this->encoding() &&
           intType.mappedClockTypeName() == this->mappedClockTypeName();
}

bool IntType::operator<(const IntType& intType) const noexcept
{
    if (this->alignment() < intType.alignment()) {
        return true;
    }

    if (intType.alignment() < this->alignment()) {
        return false;
    }

    if (this->size() < intType.size()) {
        return true;
    }

    if (intType.size() < this->size()) {
        return false;
    }

    if (this->byteOrder() < intType.byteOrder()) {
        return true;
    }

    if (intType.byteOrder() < this->byteOrder()) {
        return false;
    }

    if (this->displayBase() < intType.displayBase()) {
        return true;
    }

    if (intType.displayBase() < this->displayBase()) {
        return false;
    }

    if (this->encoding() < intType.encoding()) {
        return true;
    }

    if (intType.encoding() < this->encoding()) {
        return false;
    }

    if (this->mappedClockTypeName() < intType.mappedClockTypeName()) {
        return true;
    }

    return false;
}

SignedIntType::SignedIntType(const int kind, const unsigned int alignment,
                             const unsigned int size, const ByteOrder byteOrder,
                             const DisplayBase displayBase, const Encoding encoding,
                             const boost::optional<std::string>& mappedClockTypeName) :
    IntType {
        _KIND_SIGNED_INT | kind, alignment, size,
        byteOrder, displayBase, encoding, mappedClockTypeName
    }
{
}

SignedIntType::SignedIntType(const unsigned int alignment, const unsigned int size,
                             const ByteOrder byteOrder, const DisplayBase displayBase,
                             const Encoding encoding,
                             const boost::optional<std::string>& mappedClockTypeName) :
    IntType {
        _KIND_SIGNED_INT, alignment, size, byteOrder, displayBase, encoding,
        mappedClockTypeName
    }
{
}

SignedIntType::SignedIntType(const SignedIntType& signedIntType) :
    SignedIntType {
        signedIntType.alignment(), signedIntType.size(),
        signedIntType.byteOrder(), signedIntType.displayBase(),
        signedIntType.encoding(), signedIntType.mappedClockTypeName()
    }
{
}

DataType::UP SignedIntType::_clone() const
{
    return std::make_unique<SignedIntType>(this->alignment(), this->size(),
                                           this->byteOrder(), this->displayBase(),
                                           this->encoding(),
                                           this->mappedClockTypeName());
}

UnsignedIntType::UnsignedIntType(const int kind, const unsigned int alignment,
                                 const unsigned int size, const ByteOrder byteOrder,
                                 const DisplayBase displayBase, const Encoding encoding,
                                 const boost::optional<std::string>& mappedClockTypeName) :
    IntType {
        _KIND_UNSIGNED_INT | kind, alignment, size,
        byteOrder, displayBase, encoding, mappedClockTypeName
    }
{
}

UnsignedIntType::UnsignedIntType(const unsigned int alignment,
                                 const unsigned int size, const ByteOrder byteOrder,
                                 const DisplayBase displayBase, const Encoding encoding,
                                 const boost::optional<std::string>& mappedClockTypeName) :
    IntType {
        _KIND_UNSIGNED_INT, alignment, size, byteOrder, displayBase,
        encoding, mappedClockTypeName
    }
{
}

UnsignedIntType::UnsignedIntType(const UnsignedIntType& unsignedIntType) :
    UnsignedIntType {
        unsignedIntType.alignment(), unsignedIntType.size(),
        unsignedIntType.byteOrder(), unsignedIntType.displayBase(),
        unsignedIntType.encoding(), unsignedIntType.mappedClockTypeName()
    }
{
}

DataType::UP UnsignedIntType::_clone() const
{
    return std::make_unique<UnsignedIntType>(this->alignment(),
                                             this->size(),
                                             this->byteOrder(),
                                             this->displayBase(),
                                             this->encoding(),
                                             this->mappedClockTypeName());
}

} // namespace yactfr
