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
class BlobSectionElement;
class DataStreamInfoElement;
class DefaultClockValueElement;
class DynamicLengthArrayBeginningElement;
class DynamicLengthBlobBeginningElement;
class DynamicLengthStringBeginningElement;
class EndElement;
class EventRecordBeginningElement;
class EventRecordInfoElement;
class FixedLengthBitArrayElement;
class FixedLengthBooleanElement;
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
class StaticLengthArrayBeginningElement;
class StaticLengthBlobBeginningElement;
class StaticLengthStringBeginningElement;
class StructureBeginningElement;
class SubstringElement;
class TraceTypeUuidElement;
class VariableLengthBitArrayElement;
class VariableLengthSignedEnumerationElement;
class VariableLengthSignedIntegerElement;
class VariableLengthUnsignedEnumerationElement;
class VariableLengthUnsignedIntegerElement;
class VariantBeginningElement;
class VariantWithSignedIntegerSelectorBeginningElement;
class VariantWithUnsignedIntegerSelectorBeginningElement;
class OptionalBeginningElement;
class OptionalWithBooleanSelectorBeginningElement;
class OptionalWithSignedIntegerSelectorBeginningElement;
class OptionalWithUnsignedIntegerSelectorBeginningElement;

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
    virtual void visit(const BeginningElement&);
    virtual void visit(const BlobSectionElement&);
    virtual void visit(const DataStreamInfoElement&);
    virtual void visit(const DefaultClockValueElement&);
    virtual void visit(const DynamicLengthArrayBeginningElement&);
    virtual void visit(const DynamicLengthBlobBeginningElement&);
    virtual void visit(const DynamicLengthStringBeginningElement&);
    virtual void visit(const EndElement&);
    virtual void visit(const EventRecordBeginningElement&);
    virtual void visit(const EventRecordInfoElement&);
    virtual void visit(const FixedLengthBitArrayElement&);
    virtual void visit(const FixedLengthBooleanElement&);
    virtual void visit(const FixedLengthFloatingPointNumberElement&);
    virtual void visit(const FixedLengthSignedEnumerationElement&);
    virtual void visit(const FixedLengthSignedIntegerElement&);
    virtual void visit(const FixedLengthUnsignedEnumerationElement&);
    virtual void visit(const FixedLengthUnsignedIntegerElement&);
    virtual void visit(const NullTerminatedStringBeginningElement&);
    virtual void visit(const PacketBeginningElement&);
    virtual void visit(const PacketContentBeginningElement&);
    virtual void visit(const PacketInfoElement&);
    virtual void visit(const PacketMagicNumberElement&);
    virtual void visit(const ScopeBeginningElement&);
    virtual void visit(const StaticLengthArrayBeginningElement&);
    virtual void visit(const StaticLengthBlobBeginningElement&);
    virtual void visit(const StaticLengthStringBeginningElement&);
    virtual void visit(const StructureBeginningElement&);
    virtual void visit(const SubstringElement&);
    virtual void visit(const TraceTypeUuidElement&);
    virtual void visit(const VariableLengthBitArrayElement&);
    virtual void visit(const VariableLengthSignedEnumerationElement&);
    virtual void visit(const VariableLengthSignedIntegerElement&);
    virtual void visit(const VariableLengthUnsignedEnumerationElement&);
    virtual void visit(const VariableLengthUnsignedIntegerElement&);
    virtual void visit(const VariantBeginningElement&);
    virtual void visit(const VariantWithSignedIntegerSelectorBeginningElement&);
    virtual void visit(const VariantWithUnsignedIntegerSelectorBeginningElement&);
    virtual void visit(const OptionalBeginningElement&);
    virtual void visit(const OptionalWithBooleanSelectorBeginningElement&);
    virtual void visit(const OptionalWithSignedIntegerSelectorBeginningElement&);
    virtual void visit(const OptionalWithUnsignedIntegerSelectorBeginningElement&);
};

} // namespace yactfr

#endif // _YACTFR_ELEM_VISITOR_HPP
