/*
 * Element visitor.
 *
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/element.hpp>
#include <yactfr/element-visitor.hpp>

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

void ElementVisitor::visit(const DataStreamIdElement& elem)
{
}

void ElementVisitor::visit(const PacketOriginIndexElement& elem)
{
}

void ElementVisitor::visit(const ExpectedPacketTotalSizeElement& elem)
{
}

void ElementVisitor::visit(const ExpectedPacketContentSizeElement& elem)
{
}

void ElementVisitor::visit(const PacketMagicNumberElement& elem)
{
}

void ElementVisitor::visit(const PacketUuidElement& elem)
{
}

void ElementVisitor::visit(const ClockValueElement& elem)
{
}

void ElementVisitor::visit(const PacketEndClockValueElement& elem)
{
}

void ElementVisitor::visit(const DataStreamTypeElement& elem)
{
}

void ElementVisitor::visit(const EventRecordTypeElement& elem)
{
}

void ElementVisitor::visit(const SignedIntElement& elem)
{
}

void ElementVisitor::visit(const UnsignedIntElement& elem)
{
}

void ElementVisitor::visit(const SignedEnumElement& elem)
{
   this->visit(static_cast<const SignedIntElement&>(elem));
}

void ElementVisitor::visit(const UnsignedEnumElement& elem)
{
   this->visit(static_cast<const UnsignedIntElement&>(elem));
}

void ElementVisitor::visit(const FloatElement& elem)
{
}

void ElementVisitor::visit(const StringBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StringEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const SubstringElement& elem)
{
}

void ElementVisitor::visit(const StaticArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StaticArrayEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const StaticTextArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StaticTextArrayEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const DynamicArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicArrayEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const DynamicTextArrayBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const DynamicTextArrayEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const StructBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const StructEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

void ElementVisitor::visit(const VariantBeginningElement& elem)
{
    this->visit(static_cast<const BeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantBeginningSignedTagElement& elem)
{
    this->visit(static_cast<const VariantBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantBeginningUnsignedTagElement& elem)
{
    this->visit(static_cast<const VariantBeginningElement&>(elem));
}

void ElementVisitor::visit(const VariantEndElement& elem)
{
    this->visit(static_cast<const EndElement&>(elem));
}

} // namespace yactfr
