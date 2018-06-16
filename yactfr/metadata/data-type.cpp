/*
 * Field type.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>
#include <sstream>
#include <cassert>

#include <yactfr/metadata/data-type.hpp>
#include <yactfr/metadata/bit-array-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/string-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/array-type.hpp>
#include <yactfr/metadata/text-array-type.hpp>
#include <yactfr/metadata/sequence-type.hpp>
#include <yactfr/metadata/text-sequence-type.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/internal/utils.hpp>

namespace yactfr {

DataType::~DataType()
{
}

DataType::DataType(const int kind, const unsigned int alignment) :
    DataType {static_cast<_Kind>(kind), alignment}
{
    this->_setAlign(alignment);
}

DataType::DataType(const _Kind kind, const unsigned int alignment) :
    _kind {kind}
{
    this->_setAlign(alignment);
}

bool DataType::operator==(const DataType& otherType) const
{
    return _kind == otherType._kind && this->_compare(otherType);
}

bool DataType::operator!=(const DataType& otherType) const
{
    return !(*this == otherType);
}

DataType::UP DataType::clone() const
{
    return this->_clone();
}

void DataType::accept(DataTypeVisitor& visitor) const
{
    this->_accept(visitor);
}

void DataType::_setAlign(const unsigned int align)
{
    if (!internal::ispow2(align)) {
        throw InvalidMetadata {
            "Data type's alignment is not a power of two."
        };
    }

    _align = align;
}

const BitArrayType *DataType::asBitArrayType() const
{
    assert(this->isBitArrayType());
    return static_cast<const BitArrayType *>(this);
}

const IntType *DataType::asIntType() const
{
    assert(this->isIntType());
    return static_cast<const IntType *>(this);
}

const SignedIntType *DataType::asSignedIntType() const
{
    assert(this->isSignedIntType());
    return static_cast<const SignedIntType *>(this);
}

const UnsignedIntType *DataType::asUnsignedIntType() const
{
    assert(this->isUnsignedIntType());
    return static_cast<const UnsignedIntType *>(this);
}

const FloatType *DataType::asFloatType() const
{
    assert(this->isFloatType());
    return static_cast<const FloatType *>(this);
}

const SignedEnumType *DataType::asSignedEnumType() const
{
    assert(this->isSignedEnumType());
    return static_cast<const SignedEnumType *>(this);
}

const UnsignedEnumType *DataType::asUnsignedEnumType() const
{
    assert(this->isUnsignedEnumType());
    return static_cast<const UnsignedEnumType *>(this);
}

const StringType *DataType::asStringType() const
{
    assert(this->isStringType());
    return static_cast<const StringType *>(this);
}

const ArrayType *DataType::asArrayType() const
{
    assert(this->isArrayType());
    return static_cast<const ArrayType *>(this);
}

const ArrayType *DataType::asTextArrayType() const
{
    assert(this->isTextArrayType());
    return static_cast<const TextArrayType *>(this);
}

const SequenceType *DataType::asSequenceType() const
{
    assert(this->isSequenceType());
    return static_cast<const SequenceType *>(this);
}

const TextSequenceType *DataType::asTextSequenceType() const
{
    assert(this->isTextSequenceType());
    return static_cast<const TextSequenceType *>(this);
}

const StructType *DataType::asStructType() const
{
    assert(this->isStructType());
    return static_cast<const StructType *>(this);
}

const VariantType *DataType::asVariantType() const
{
    assert(this->isVariantType());
    return static_cast<const VariantType *>(this);
}

} // namespace yactfr
