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
    virtual void visit(const BeginningElement& elem);
    virtual void visit(const BlobSectionElement& elem);
    virtual void visit(const DataStreamInfoElement& elem);
    virtual void visit(const DefaultClockValueElement& elem);
    virtual void visit(const DynamicLengthArrayBeginningElement& elem);
    virtual void visit(const DynamicLengthBlobBeginningElement& elem);
    virtual void visit(const DynamicLengthStringBeginningElement& elem);
    virtual void visit(const EndElement& elem);
    virtual void visit(const EventRecordBeginningElement& elem);
    virtual void visit(const EventRecordInfoElement& elem);
    virtual void visit(const FixedLengthBitArrayElement& elem);
    virtual void visit(const FixedLengthBooleanElement& elem);
    virtual void visit(const FixedLengthFloatingPointNumberElement& elem);
    virtual void visit(const FixedLengthSignedEnumerationElement& elem);
    virtual void visit(const FixedLengthSignedIntegerElement& elem);
    virtual void visit(const FixedLengthUnsignedEnumerationElement& elem);
    virtual void visit(const FixedLengthUnsignedIntegerElement& elem);
    virtual void visit(const NullTerminatedStringBeginningElement& elem);
    virtual void visit(const PacketBeginningElement& elem);
    virtual void visit(const PacketContentBeginningElement& elem);
    virtual void visit(const PacketInfoElement& elem);
    virtual void visit(const PacketMagicNumberElement& elem);
    virtual void visit(const ScopeBeginningElement& elem);
    virtual void visit(const StaticLengthArrayBeginningElement& elem);
    virtual void visit(const StaticLengthBlobBeginningElement& elem);
    virtual void visit(const StaticLengthStringBeginningElement& elem);
    virtual void visit(const StructureBeginningElement& elem);
    virtual void visit(const SubstringElement& elem);
    virtual void visit(const TraceTypeUuidElement& elem);
    virtual void visit(const VariableLengthBitArrayElement& elem);
    virtual void visit(const VariableLengthSignedEnumerationElement& elem);
    virtual void visit(const VariableLengthSignedIntegerElement& elem);
    virtual void visit(const VariableLengthUnsignedEnumerationElement& elem);
    virtual void visit(const VariableLengthUnsignedIntegerElement& elem);
    virtual void visit(const VariantBeginningElement& elem);
    virtual void visit(const VariantWithSignedIntegerSelectorBeginningElement& elem);
    virtual void visit(const VariantWithUnsignedIntegerSelectorBeginningElement& elem);
    virtual void visit(const OptionalBeginningElement& elem);
    virtual void visit(const OptionalWithBooleanSelectorBeginningElement& elem);
    virtual void visit(const OptionalWithSignedIntegerSelectorBeginningElement& elem);
    virtual void visit(const OptionalWithUnsignedIntegerSelectorBeginningElement& elem);
};

} // namespace yactfr

#endif // _YACTFR_ELEM_VISITOR_HPP
