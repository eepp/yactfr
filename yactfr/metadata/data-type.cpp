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
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/dynamic-array-type.hpp>
#include <yactfr/metadata/dynamic-text-array-type.hpp>
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

const StaticArrayType *DataType::asStaticArrayType() const
{
    assert(this->isStaticArrayType());
    return static_cast<const StaticArrayType *>(this);
}

const StaticTextArrayType *DataType::asStaticTextArrayType() const
{
    assert(this->isStaticTextArrayType());
    return static_cast<const StaticTextArrayType *>(this);
}

const DynamicArrayType *DataType::asDynamicArrayType() const
{
    assert(this->isDynamicArrayType());
    return static_cast<const DynamicArrayType *>(this);
}

const DynamicTextArrayType *DataType::asDynamicTextArrayType() const
{
    assert(this->isDynamicTextArrayType());
    return static_cast<const DynamicTextArrayType *>(this);
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
