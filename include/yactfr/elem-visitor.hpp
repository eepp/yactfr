/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ELEM_VISITOR_HPP
#define _YACTFR_ELEM_VISITOR_HPP

namespace yactfr {

class BeginningElement;
class DataStreamInfoElement;
class DefaultClockValueElement;
class DynamicArrayBeginningElement;
class DynamicTextArrayBeginningElement;
class EndElement;
class EventRecordBeginningElement;
class EventRecordInfoElement;
class FixedLengthFloatingPointNumberElement;
class FixedLengthSignedEnumerationElement;
class FixedLengthSignedIntegerElement;
class FixedLengthUnsignedEnumerationElement;
class FixedLengthUnsignedIntegerElement;
class NullTerminatedStringBeginningElement;
class PacketBeginningElement;
class PacketContentBeginningElement;
class PacketEndDefaultClockValueElement;
class PacketInfoElement;
class PacketMagicNumberElement;
class ScopeBeginningElement;
class StaticArrayBeginningElement;
class StaticTextArrayBeginningElement;
class StructureBeginningElement;
class SubstringElement;
class TraceTypeUuidElement;
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
    virtual ~ElementVisitor() = default;
    virtual void visit(const BeginningElement& elem);
    virtual void visit(const DataStreamInfoElement& elem);
    virtual void visit(const DefaultClockValueElement& elem);
    virtual void visit(const DynamicArrayBeginningElement& elem);
    virtual void visit(const DynamicTextArrayBeginningElement& elem);
    virtual void visit(const EndElement& elem);
    virtual void visit(const EventRecordBeginningElement& elem);
    virtual void visit(const EventRecordInfoElement& elem);
    virtual void visit(const FixedLengthFloatingPointNumberElement& elem);
    virtual void visit(const FixedLengthSignedEnumerationElement& elem);
    virtual void visit(const FixedLengthSignedIntegerElement& elem);
    virtual void visit(const FixedLengthUnsignedEnumerationElement& elem);
    virtual void visit(const FixedLengthUnsignedIntegerElement& elem);
    virtual void visit(const PacketBeginningElement& elem);
    virtual void visit(const PacketContentBeginningElement& elem);
    virtual void visit(const PacketInfoElement& elem);
    virtual void visit(const PacketMagicNumberElement& elem);
    virtual void visit(const ScopeBeginningElement& elem);
    virtual void visit(const StaticArrayBeginningElement& elem);
    virtual void visit(const StaticTextArrayBeginningElement& elem);
    virtual void visit(const NullTerminatedStringBeginningElement& elem);
    virtual void visit(const StructureBeginningElement& elem);
    virtual void visit(const SubstringElement& elem);
    virtual void visit(const TraceTypeUuidElement& elem);
    virtual void visit(const VariantBeginningElement& elem);
    virtual void visit(const VariantWithSignedSelectorBeginningElement& elem);
    virtual void visit(const VariantWithUnsignedSelectorBeginningElement& elem);
};

} // namespace yactfr

#endif // _YACTFR_ELEM_VISITOR_HPP
