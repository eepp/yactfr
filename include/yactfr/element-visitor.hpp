/*
 * Element sequence iterator element visitor.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  yactfr element visitor.

@ingroup element_seq
*/

#ifndef _YACTFR_ELEMENT_VISITOR_HPP
#define _YACTFR_ELEMENT_VISITOR_HPP

namespace yactfr {

class BeginningElement;
class EndElement;
class PacketBeginningElement;
class PacketEndElement;
class ScopeBeginningElement;
class ScopeEndElement;
class PacketContentBeginningElement;
class PacketContentEndElement;
class EventRecordBeginningElement;
class EventRecordEndElement;
class DataStreamIdElement;
class PacketOriginIndexElement;
class ExpectedPacketTotalSizeElement;
class ExpectedPacketContentSizeElement;
class PacketMagicNumberElement;
class PacketUuidElement;
class ClockValueElement;
class PacketEndClockValueElement;
class DataStreamTypeElement;
class EventRecordTypeElement;
class SignedIntElement;
class UnsignedIntElement;
class SignedEnumElement;
class UnsignedEnumElement;
class FloatElement;
class StringBeginningElement;
class StringEndElement;
class SubstringElement;
class StaticArrayBeginningElement;
class StaticArrayEndElement;
class StaticTextArrayBeginningElement;
class StaticTextArrayEndElement;
class DynamicArrayBeginningElement;
class DynamicArrayEndElement;
class DynamicTextArrayBeginningElement;
class DynamicTextArrayEndElement;
class StructBeginningElement;
class StructEndElement;
class VariantBeginningElement;
class VariantBeginningSignedTagElement;
class VariantBeginningUnsignedTagElement;
class VariantEndElement;

/*!
@brief  Element visitor.

A subclass instance can be passed to Element::accept(ElementVisitor&) const.
*/
class ElementVisitor
{
public:
    virtual ~ElementVisitor();
    virtual void visit(const BeginningElement& elem);
    virtual void visit(const EndElement& elem);
    virtual void visit(const PacketBeginningElement& elem);
    virtual void visit(const PacketEndElement& elem);
    virtual void visit(const ScopeBeginningElement& elem);
    virtual void visit(const ScopeEndElement& elem);
    virtual void visit(const PacketContentBeginningElement& elem);
    virtual void visit(const PacketContentEndElement& elem);
    virtual void visit(const EventRecordBeginningElement& elem);
    virtual void visit(const EventRecordEndElement& elem);
    virtual void visit(const DataStreamIdElement& elem);
    virtual void visit(const PacketOriginIndexElement& elem);
    virtual void visit(const ExpectedPacketTotalSizeElement& elem);
    virtual void visit(const ExpectedPacketContentSizeElement& elem);
    virtual void visit(const PacketMagicNumberElement& elem);
    virtual void visit(const PacketUuidElement& elem);
    virtual void visit(const ClockValueElement& elem);
    virtual void visit(const PacketEndClockValueElement& elem);
    virtual void visit(const DataStreamTypeElement& elem);
    virtual void visit(const EventRecordTypeElement& elem);
    virtual void visit(const SignedIntElement& elem);
    virtual void visit(const UnsignedIntElement& elem);
    virtual void visit(const SignedEnumElement& elem);
    virtual void visit(const UnsignedEnumElement& elem);
    virtual void visit(const FloatElement& elem);
    virtual void visit(const StringBeginningElement& elem);
    virtual void visit(const StringEndElement& elem);
    virtual void visit(const SubstringElement& elem);
    virtual void visit(const StaticArrayBeginningElement& elem);
    virtual void visit(const StaticArrayEndElement& elem);
    virtual void visit(const StaticTextArrayBeginningElement& elem);
    virtual void visit(const StaticTextArrayEndElement& elem);
    virtual void visit(const DynamicArrayBeginningElement& elem);
    virtual void visit(const DynamicArrayEndElement& elem);
    virtual void visit(const DynamicTextArrayBeginningElement& elem);
    virtual void visit(const DynamicTextArrayEndElement& elem);
    virtual void visit(const StructBeginningElement& elem);
    virtual void visit(const StructEndElement& elem);
    virtual void visit(const VariantBeginningElement& elem);
    virtual void visit(const VariantBeginningSignedTagElement& elem);
    virtual void visit(const VariantBeginningUnsignedTagElement& elem);
    virtual void visit(const VariantEndElement& elem);
};

} // namespace yactfr

#endif // _YACTFR_ELEMENT_VISITOR_HPP
