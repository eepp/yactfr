/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/elem.hpp>
#include <yactfr/elem-visitor.hpp>

namespace yactfr {

ElementVisitor::~ElementVisitor()
{
}

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

void ElementVisitor::visit(const DataStreamIdElement& elem)
{
}

void ElementVisitor::visit(const PacketOriginIndexElement& elem)
{
}

void ElementVisitor::visit(const ExpectedPacketTotalLengthElement& elem)
{
}

void ElementVisitor::visit(const ExpectedPacketContentLengthElement& elem)
{
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

void ElementVisitor::visit(const PacketEndDefaultClockValueElement& elem)
{
}

void ElementVisitor::visit(const DataStreamTypeElement& elem)
{
}

void ElementVisitor::visit(const EventRecordTypeElement& elem)
{
}

void ElementVisitor::visit(const SignedIntegerElement& elem)
{
}

void ElementVisitor::visit(const UnsignedIntegerElement& elem)
{
}

void ElementVisitor::visit(const SignedEnumerationElement& elem)
{
   this->visit(static_cast<const SignedIntegerElement&>(elem));
}

void ElementVisitor::visit(const UnsignedEnumerationElement& elem)
{
   this->visit(static_cast<const UnsignedIntegerElement&>(elem));
}

void ElementVisitor::visit(const FloatingPointNumberElement& elem)
{
}

void ElementVisitor::visit(const StringBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const SubstringElement& elem)
{
}

void ElementVisitor::visit(const StaticArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StaticTextArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicTextArrayBeginningElement& elem)
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
