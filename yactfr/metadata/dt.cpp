/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>
#include <sstream>
#include <cassert>

#include <yactfr/metadata/dt.hpp>
#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/metadata/nt-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/dyn-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/internal/utils.hpp>

namespace yactfr {

DataType::DataType(const int kind, const unsigned int align) :
    DataType {static_cast<_Kind>(kind), align}
{
}

DataType::DataType(const _Kind kind, const unsigned int align) :
    _theKind {kind},
    _align {align}
{
}

bool DataType::operator==(const DataType& other) const noexcept
{
    return _theKind == other._theKind && _align == other._align && this->_compare(other);
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

const SignedFixedLengthEnumerationType& DataType::asFixedLengthSignedEnumerationType() const noexcept
{
    assert(this->isSignedFixedLengthEnumerationType());
    return static_cast<const SignedFixedLengthEnumerationType&>(*this);
}

const FixedLengthUnsignedEnumerationType& DataType::asFixedLengthUnsignedEnumerationType() const noexcept
{
    assert(this->isFixedLengthUnsignedEnumerationType());
    return static_cast<const FixedLengthUnsignedEnumerationType&>(*this);
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

const StaticArrayType& DataType::asStaticArrayType() const noexcept
{
    assert(this->isStaticArrayType());
    return static_cast<const StaticArrayType&>(*this);
}

const DynamicArrayType& DataType::asDynamicArrayType() const noexcept
{
    assert(this->isDynamicArrayType());
    return static_cast<const DynamicArrayType&>(*this);
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

const StructureType& DataType::asStructureType() const noexcept
{
    assert(this->isStructureType());
    return static_cast<const StructureType&>(*this);
}

const VariantWithUnsignedSelectorType& DataType::asVariantWithUnsignedSelectorType() const noexcept
{
    assert(this->isVariantWithUnsignedSelectorType());
    return static_cast<const VariantWithUnsignedSelectorType&>(*this);
}

const VariantWithSignedSelectorType& DataType::asVariantWithSignedSelectorType() const noexcept
{
    assert(this->isVariantWithSignedSelectorType());
    return static_cast<const VariantWithSignedSelectorType&>(*this);
}

} // namespace yactfr
