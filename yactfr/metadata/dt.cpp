/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>
#include <sstream>
#include <cassert>

#include <yactfr/metadata/dt.hpp>
#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/fl-bool-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/metadata/vl-bit-array-type.hpp>
#include <yactfr/metadata/vl-int-type.hpp>
#include <yactfr/metadata/vl-enum-type.hpp>
#include <yactfr/metadata/nt-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/dl-blob-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/opt-type.hpp>

namespace yactfr {

DataType::DataType(const int kind, const unsigned int align, MapItem::UP userAttrs) :
    DataType {static_cast<_Kind>(kind), align, std::move(userAttrs)}
{
}

DataType::DataType(const _Kind kind, const unsigned int align, MapItem::UP userAttrs) :
    _theKind {kind},
    _align {align},
    _userAttrs {std::move(userAttrs)}
{
}

bool DataType::operator==(const DataType& other) const noexcept
{
    return _theKind == other._theKind && _align == other._align &&
           _userAttrs == other._userAttrs && this->_isEqual(other);
}

bool DataType::operator!=(const DataType& other) const noexcept
{
    return !(*this == other);
}

DataType::UP DataType::clone() const
{
    return this->_clone();
}

void DataType::accept(DataTypeVisitor& visitor) const
{
    this->_accept(visitor);
}

const FixedLengthBitArrayType& DataType::asFixedLengthBitArrayType() const noexcept
{
    assert(this->isFixedLengthBitArrayType());
    return static_cast<const FixedLengthBitArrayType&>(*this);
}

const FixedLengthBooleanType& DataType::asFixedLengthBooleanType() const noexcept
{
    assert(this->isFixedLengthBooleanType());
    return static_cast<const FixedLengthBooleanType&>(*this);
}

const FixedLengthIntegerType& DataType::asFixedLengthIntegerType() const noexcept
{
    assert(this->isFixedLengthIntegerType());
    return static_cast<const FixedLengthIntegerType&>(*this);
}

const FixedLengthSignedIntegerType& DataType::asFixedLengthSignedIntegerType() const noexcept
{
    assert(this->isFixedLengthSignedIntegerType());
    return static_cast<const FixedLengthSignedIntegerType&>(*this);
}

const FixedLengthUnsignedIntegerType& DataType::asFixedLengthUnsignedIntegerType() const noexcept
{
    assert(this->isFixedLengthUnsignedIntegerType());
    return static_cast<const FixedLengthUnsignedIntegerType&>(*this);
}

const FixedLengthFloatingPointNumberType& DataType::asFixedLengthFloatingPointNumberType() const noexcept
{
    assert(this->isFixedLengthFloatingPointNumberType());
    return static_cast<const FixedLengthFloatingPointNumberType&>(*this);
}

const FixedLengthSignedEnumerationType& DataType::asFixedLengthSignedEnumerationType() const noexcept
{
    assert(this->isFixedLengthSignedEnumerationType());
    return static_cast<const FixedLengthSignedEnumerationType&>(*this);
}

const FixedLengthUnsignedEnumerationType& DataType::asFixedLengthUnsignedEnumerationType() const noexcept
{
    assert(this->isFixedLengthUnsignedEnumerationType());
    return static_cast<const FixedLengthUnsignedEnumerationType&>(*this);
}

const VariableLengthBitArrayType& DataType::asVariableLengthBitArrayType() const noexcept
{
    assert(this->isVariableLengthBitArrayType());
    return static_cast<const VariableLengthBitArrayType&>(*this);
}

const VariableLengthIntegerType& DataType::asVariableLengthIntegerType() const noexcept
{
    assert(this->isVariableLengthIntegerType());
    return static_cast<const VariableLengthIntegerType&>(*this);
}

const VariableLengthSignedIntegerType& DataType::asVariableLengthSignedIntegerType() const noexcept
{
    assert(this->isVariableLengthSignedIntegerType());
    return static_cast<const VariableLengthSignedIntegerType&>(*this);
}

const VariableLengthUnsignedIntegerType& DataType::asVariableLengthUnsignedIntegerType() const noexcept
{
    assert(this->isVariableLengthUnsignedIntegerType());
    return static_cast<const VariableLengthUnsignedIntegerType&>(*this);
}

const VariableLengthSignedEnumerationType& DataType::asVariableLengthSignedEnumerationType() const noexcept
{
    assert(this->isVariableLengthSignedEnumerationType());
    return static_cast<const VariableLengthSignedEnumerationType&>(*this);
}

const VariableLengthUnsignedEnumerationType& DataType::asVariableLengthUnsignedEnumerationType() const noexcept
{
    assert(this->isVariableLengthUnsignedEnumerationType());
    return static_cast<const VariableLengthUnsignedEnumerationType&>(*this);
}

const NullTerminatedStringType& DataType::asNullTerminatedStringType() const noexcept
{
    assert(this->isNullTerminatedStringType());
    return static_cast<const NullTerminatedStringType&>(*this);
}

const ArrayType& DataType::asArrayType() const noexcept
{
    assert(this->isArrayType());
    return static_cast<const ArrayType&>(*this);
}

const StaticLengthArrayType& DataType::asStaticLengthArrayType() const noexcept
{
    assert(this->isStaticLengthArrayType());
    return static_cast<const StaticLengthArrayType&>(*this);
}

const DynamicLengthArrayType& DataType::asDynamicLengthArrayType() const noexcept
{
    assert(this->isDynamicLengthArrayType());
    return static_cast<const DynamicLengthArrayType&>(*this);
}

const NonNullTerminatedStringType& DataType::asNonNullTerminatedStringType() const noexcept
{
    assert(this->isNonNullTerminatedStringType());
    return static_cast<const NonNullTerminatedStringType&>(*this);
}

const StaticLengthStringType& DataType::asStaticLengthStringType() const noexcept
{
    assert(this->isStaticLengthStringType());
    return static_cast<const StaticLengthStringType&>(*this);
}

const DynamicLengthStringType& DataType::asDynamicLengthStringType() const noexcept
{
    assert(this->isDynamicLengthStringType());
    return static_cast<const DynamicLengthStringType&>(*this);
}

const BlobType& DataType::asBlobType() const noexcept
{
    assert(this->isBlobType());
    return static_cast<const BlobType&>(*this);
}

const StaticLengthBlobType& DataType::asStaticLengthBlobType() const noexcept
{
    assert(this->isStaticLengthBlobType());
    return static_cast<const StaticLengthBlobType&>(*this);
}

const DynamicLengthBlobType& DataType::asDynamicLengthBlobType() const noexcept
{
    assert(this->isDynamicLengthBlobType());
    return static_cast<const DynamicLengthBlobType&>(*this);
}

const StructureType& DataType::asStructureType() const noexcept
{
    assert(this->isStructureType());
    return static_cast<const StructureType&>(*this);
}

const VariantWithUnsignedIntegerSelectorType& DataType::asVariantWithUnsignedIntegerSelectorType() const noexcept
{
    assert(this->isVariantWithUnsignedIntegerSelectorType());
    return static_cast<const VariantWithUnsignedIntegerSelectorType&>(*this);
}

const VariantWithSignedIntegerSelectorType& DataType::asVariantWithSignedIntegerSelectorType() const noexcept
{
    assert(this->isVariantWithSignedIntegerSelectorType());
    return static_cast<const VariantWithSignedIntegerSelectorType&>(*this);
}

const OptionalType& DataType::asOptionalType() const noexcept
{
    assert(this->isOptionalType());
    return static_cast<const OptionalType&>(*this);
}

const OptionalWithBooleanSelectorType& DataType::asOptionalWithBooleanSelectorType() const noexcept
{
    assert(this->isOptionalWithBooleanSelectorType());
    return static_cast<const OptionalWithBooleanSelectorType&>(*this);
}

const OptionalWithUnsignedIntegerSelectorType& DataType::asOptionalWithUnsignedIntegerSelectorType() const noexcept
{
    assert(this->isOptionalWithUnsignedIntegerSelectorType());
    return static_cast<const OptionalWithUnsignedIntegerSelectorType&>(*this);
}

const OptionalWithSignedIntegerSelectorType& DataType::asOptionalWithSignedIntegerSelectorType() const noexcept
{
    assert(this->isOptionalWithSignedIntegerSelectorType());
    return static_cast<const OptionalWithSignedIntegerSelectorType&>(*this);
}


} // namespace yactfr
