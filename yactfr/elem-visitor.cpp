/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/elem.hpp>
#include <yactfr/elem-visitor.hpp>

namespace yactfr {

void ElementVisitor::visit(const BeginningElement&)
{
}

void ElementVisitor::visit(const EndElement&)
{
}

void ElementVisitor::visit(const PacketBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const PacketEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const ScopeBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const ScopeEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const PacketContentBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const PacketContentEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const EventRecordBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const EventRecordEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const PacketMagicNumberElement&)
{
}

void ElementVisitor::visit(const TraceTypeUuidElement&)
{
}

void ElementVisitor::visit(const DefaultClockValueElement&)
{
}

void ElementVisitor::visit(const DataStreamInfoElement&)
{
}

void ElementVisitor::visit(const PacketInfoElement&)
{
}

void ElementVisitor::visit(const EventRecordInfoElement&)
{
}

void ElementVisitor::visit(const FixedLengthBitArrayElement&)
{
}

void ElementVisitor::visit(const FixedLengthBooleanElement& elem)
{
    this->visit(static_cast<const FixedLengthBitArrayElement&>(elem));
}

void ElementVisitor::visit(const FixedLengthSignedIntegerElement& elem)
{
    this->visit(static_cast<const FixedLengthBitArrayElement&>(elem));
}

void ElementVisitor::visit(const FixedLengthUnsignedIntegerElement& elem)
{
    this->visit(static_cast<const FixedLengthBitArrayElement&>(elem));
}

void ElementVisitor::visit(const FixedLengthSignedEnumerationElement& elem)
{
   this->visit(static_cast<const FixedLengthSignedIntegerElement&>(elem));
}

void ElementVisitor::visit(const FixedLengthUnsignedEnumerationElement& elem)
{
   this->visit(static_cast<const FixedLengthUnsignedIntegerElement&>(elem));
}

void ElementVisitor::visit(const FixedLengthFloatingPointNumberElement& elem)
{
    this->visit(static_cast<const FixedLengthBitArrayElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthBitArrayBeginningElement&)
{
}

void ElementVisitor::visit(const VariableLengthSignedIntegerBeginningElement& elem)
{
    this->visit(static_cast<const VariableLengthBitArrayBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthUnsignedIntegerBeginningElement& elem)
{
    this->visit(static_cast<const VariableLengthBitArrayBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthSignedEnumerationBeginningElement& elem)
{
   this->visit(static_cast<const VariableLengthSignedIntegerBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthUnsignedEnumerationBeginningElement& elem)
{
   this->visit(static_cast<const VariableLengthUnsignedIntegerBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthBitArrayEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthSignedIntegerEndElement& elem)
{
    this->visit(static_cast<const VariableLengthBitArrayEndElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthUnsignedIntegerEndElement& elem)
{
    this->visit(static_cast<const VariableLengthBitArrayEndElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthSignedEnumerationEndElement& elem)
{
   this->visit(static_cast<const VariableLengthSignedIntegerEndElement&>(elem));
}

void ElementVisitor::visit(const VariableLengthUnsignedEnumerationEndElement& elem)
{
   this->visit(static_cast<const VariableLengthUnsignedIntegerEndElement&>(elem));
}

void ElementVisitor::visit(const NullTerminatedStringBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const NullTerminatedStringEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const SubstringElement&)
{
}

void ElementVisitor::visit(const BlobSectionElement&)
{
}

void ElementVisitor::visit(const ArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const ArrayEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const StaticLengthArrayBeginningElement& elem)
{
    this->visit(static_cast<const ArrayBeginningElement&>(elem));
}

void ElementVisitor::visit(const StaticLengthArrayEndElement& elem)
{
    this->visit(static_cast<const ArrayEndElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthArrayBeginningElement& elem)
{
    this->visit(static_cast<const ArrayBeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthArrayEndElement& elem)
{
    this->visit(static_cast<const ArrayEndElement&>(elem));
}

void ElementVisitor::visit(const NonNullTerminatedStringBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const NonNullTerminatedStringEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const StaticLengthStringBeginningElement& elem)
{
    this->visit(static_cast<const NonNullTerminatedStringBeginningElement&>(elem));
}

void ElementVisitor::visit(const StaticLengthStringEndElement& elem)
{
    this->visit(static_cast<const NonNullTerminatedStringEndElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthStringBeginningElement& elem)
{
    this->visit(static_cast<const NonNullTerminatedStringBeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthStringEndElement& elem)
{
    this->visit(static_cast<const NonNullTerminatedStringEndElement&>(elem));
}

void ElementVisitor::visit(const BlobBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const BlobEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const StaticLengthBlobBeginningElement& elem)
{
    this->visit(static_cast<const BlobBeginningElement&>(elem));
}

void ElementVisitor::visit(const StaticLengthBlobEndElement& elem)
{
    this->visit(static_cast<const BlobEndElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthBlobBeginningElement& elem)
{
    this->visit(static_cast<const BlobBeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthBlobEndElement& elem)
{
    this->visit(static_cast<const BlobEndElement&>(elem));
}

void ElementVisitor::visit(const StructureBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StructureEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const VariantBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const VariantWithSignedIntegerSelectorBeginningElement& elem)
{
    this->visit(static_cast<const VariantBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantWithSignedIntegerSelectorEndElement& elem)
{
    this->visit(static_cast<const VariantEndElement&>(elem));
}

void ElementVisitor::visit(const VariantWithUnsignedIntegerSelectorBeginningElement& elem)
{
    this->visit(static_cast<const VariantBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantWithUnsignedIntegerSelectorEndElement& elem)
{
    this->visit(static_cast<const VariantEndElement&>(elem));
}

void ElementVisitor::visit(const OptionalBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const OptionalEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const OptionalWithBooleanSelectorBeginningElement& elem)
{
    this->visit(static_cast<const OptionalBeginningElement&>(elem));
}

void ElementVisitor::visit(const OptionalWithBooleanSelectorEndElement& elem)
{
    this->visit(static_cast<const OptionalEndElement&>(elem));
}

void ElementVisitor::visit(const OptionalWithSignedIntegerSelectorBeginningElement& elem)
{
    this->visit(static_cast<const OptionalBeginningElement&>(elem));
}

void ElementVisitor::visit(const OptionalWithSignedIntegerSelectorEndElement& elem)
{
    this->visit(static_cast<const OptionalEndElement&>(elem));
}

void ElementVisitor::visit(const OptionalWithUnsignedIntegerSelectorBeginningElement& elem)
{
    this->visit(static_cast<const OptionalBeginningElement&>(elem));
}

void ElementVisitor::visit(const OptionalWithUnsignedIntegerSelectorEndElement& elem)
{
    this->visit(static_cast<const OptionalEndElement&>(elem));
}

} // namespace yactfr
