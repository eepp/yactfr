/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/elem.hpp>
#include <yactfr/elem-visitor.hpp>

namespace yactfr {

void ElementVisitor::visit(const BeginningElement& elem)
{
}

void ElementVisitor::visit(const EndElement& elem)
{
}

void ElementVisitor::visit(const PacketBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const ScopeBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const PacketContentBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const EventRecordBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const PacketMagicNumberElement& elem)
{
}

void ElementVisitor::visit(const TraceTypeUuidElement& elem)
{
}

void ElementVisitor::visit(const DefaultClockValueElement& elem)
{
}

void ElementVisitor::visit(const DataStreamInfoElement& elem)
{
}

void ElementVisitor::visit(const PacketInfoElement& elem)
{
}

void ElementVisitor::visit(const EventRecordInfoElement& elem)
{
}

void ElementVisitor::visit(const FixedLengthBitArrayElement& elem)
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

void ElementVisitor::visit(const NullTerminatedStringBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const SubstringElement& elem)
{
}

void ElementVisitor::visit(const StaticLengthArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StaticLengthStringBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicLengthStringBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StructureBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantWithSignedSelectorBeginningElement& elem)
{
    this->visit(static_cast<const VariantBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantWithUnsignedSelectorBeginningElement& elem)
{
    this->visit(static_cast<const VariantBeginningElement&>(elem));
}

} // namespace yactfr
