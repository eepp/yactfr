/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ELEM_VISITOR_HPP
#define _YACTFR_ELEM_VISITOR_HPP

namespace yactfr {

class BeginningElement;
class ClockValueElement;
class DataStreamIdElement;
class DataStreamTypeElement;
class DynamicArrayBeginningElement;
class DynamicTextArrayBeginningElement;
class EndElement;
class EventRecordBeginningElement;
class EventRecordTypeElement;
class ExpectedPacketContentLengthElement;
class ExpectedPacketTotalLengthElement;
class FloatingPointNumberElement;
class PacketBeginningElement;
class PacketContentBeginningElement;
class PacketEndClockValueElement;
class PacketMagicNumberElement;
class PacketOriginIndexElement;
class ScopeBeginningElement;
class SignedEnumerationElement;
class SignedIntegerElement;
class StaticArrayBeginningElement;
class StaticTextArrayBeginningElement;
class StringBeginningElement;
class StructureBeginningElement;
class SubstringElement;
class TraceTypeUuidElement;
class UnsignedEnumerationElement;
class UnsignedIntegerElement;
class VariantBeginningElement;
class VariantWithSignedSelectorBeginningElement;
class VariantWithUnsignedSelectorBeginningElement;

/*!
@brief
    Element visitor.

@ingroup element_seq

You can pass a subclass instance to
Element::accept(ElementVisitor&) const.
*/
class ElementVisitor
{
public:
    virtual ~ElementVisitor();
    virtual void visit(const BeginningElement& elem);
    virtual void visit(const ClockValueElement& elem);
    virtual void visit(const DataStreamIdElement& elem);
    virtual void visit(const DataStreamTypeElement& elem);
    virtual void visit(const DynamicArrayBeginningElement& elem);
    virtual void visit(const DynamicTextArrayBeginningElement& elem);
    virtual void visit(const EndElement& elem);
    virtual void visit(const EventRecordBeginningElement& elem);
    virtual void visit(const EventRecordTypeElement& elem);
    virtual void visit(const ExpectedPacketContentLengthElement& elem);
    virtual void visit(const ExpectedPacketTotalLengthElement& elem);
    virtual void visit(const FloatingPointNumberElement& elem);
    virtual void visit(const PacketBeginningElement& elem);
    virtual void visit(const PacketContentBeginningElement& elem);
    virtual void visit(const PacketEndClockValueElement& elem);
    virtual void visit(const PacketMagicNumberElement& elem);
    virtual void visit(const PacketOriginIndexElement& elem);
    virtual void visit(const ScopeBeginningElement& elem);
    virtual void visit(const SignedEnumerationElement& elem);
    virtual void visit(const SignedIntegerElement& elem);
    virtual void visit(const StaticArrayBeginningElement& elem);
    virtual void visit(const StaticTextArrayBeginningElement& elem);
    virtual void visit(const StringBeginningElement& elem);
    virtual void visit(const StructureBeginningElement& elem);
    virtual void visit(const SubstringElement& elem);
    virtual void visit(const TraceTypeUuidElement& elem);
    virtual void visit(const UnsignedEnumerationElement& elem);
    virtual void visit(const UnsignedIntegerElement& elem);
    virtual void visit(const VariantBeginningElement& elem);
    virtual void visit(const VariantWithSignedSelectorBeginningElement& elem);
    virtual void visit(const VariantWithUnsignedSelectorBeginningElement& elem);
};

} // namespace yactfr

#endif // _YACTFR_ELEM_VISITOR_HPP
