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
#include <yactfr/metadata/bit-array-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/dyn-array-type.hpp>
#include <yactfr/metadata/dyn-text-array-type.hpp>
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

const BitArrayType& DataType::asBitArrayType() const noexcept
{
    assert(this->isBitArrayType());
    return static_cast<const BitArrayType&>(*this);
}

const IntegerType& DataType::asIntegerType() const noexcept
{
    assert(this->isIntegerType());
    return static_cast<const IntegerType&>(*this);
}

const SignedIntegerType& DataType::asSignedIntegerType() const noexcept
{
    assert(this->isSignedIntegerType());
    return static_cast<const SignedIntegerType&>(*this);
}

const UnsignedIntegerType& DataType::asUnsignedIntegerType() const noexcept
{
    assert(this->isUnsignedIntegerType());
    return static_cast<const UnsignedIntegerType&>(*this);
}

const FloatingPointNumberType& DataType::asFloatingPointNumberType() const noexcept
{
    assert(this->isFloatingPointNumberType());
    return static_cast<const FloatingPointNumberType&>(*this);
}

const SignedEnumerationType& DataType::asSignedEnumerationType() const noexcept
{
    assert(this->isSignedEnumerationType());
    return static_cast<const SignedEnumerationType&>(*this);
}

const UnsignedEnumerationType& DataType::asUnsignedEnumerationType() const noexcept
{
    assert(this->isUnsignedEnumerationType());
    return static_cast<const UnsignedEnumerationType&>(*this);
}

const StringType& DataType::asStringType() const noexcept
{
    assert(this->isStringType());
    return static_cast<const StringType&>(*this);
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

const StaticTextArrayType& DataType::asStaticTextArrayType() const noexcept
{
    assert(this->isStaticTextArrayType());
    return static_cast<const StaticTextArrayType&>(*this);
}

const DynamicArrayType& DataType::asDynamicArrayType() const noexcept
{
    assert(this->isDynamicArrayType());
    return static_cast<const DynamicArrayType&>(*this);
}

const DynamicTextArrayType& DataType::asDynamicTextArrayType() const noexcept
{
    assert(this->isDynamicTextArrayType());
    return static_cast<const DynamicTextArrayType&>(*this);
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
