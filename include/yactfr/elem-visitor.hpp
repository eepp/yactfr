/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_ELEM_VISITOR_HPP
#define YACTFR_ELEM_VISITOR_HPP

namespace yactfr {

class ArrayBeginningElement;
class ArrayEndElement;
class BeginningElement;
class BlobBeginningElement;
class BlobEndElement;
class DataStreamInfoElement;
class DefaultClockValueElement;
class DynamicLengthArrayBeginningElement;
class DynamicLengthArrayEndElement;
class DynamicLengthBlobBeginningElement;
class DynamicLengthBlobEndElement;
class DynamicLengthStringBeginningElement;
class DynamicLengthStringEndElement;
class EndElement;
class EventRecordBeginningElement;
class EventRecordEndElement;
class EventRecordInfoElement;
class FixedLengthBitArrayElement;
class FixedLengthBitMapElement;
class FixedLengthBooleanElement;
class FixedLengthFloatingPointNumberElement;
class FixedLengthSignedIntegerElement;
class FixedLengthUnsignedIntegerElement;
class MetadataStreamUuidElement;
class NonNullTerminatedStringBeginningElement;
class NonNullTerminatedStringEndElement;
class NullTerminatedStringBeginningElement;
class NullTerminatedStringEndElement;
class OptionalBeginningElement;
class OptionalEndElement;
class OptionalWithBooleanSelectorBeginningElement;
class OptionalWithBooleanSelectorEndElement;
class OptionalWithSignedIntegerSelectorBeginningElement;
class OptionalWithSignedIntegerSelectorEndElement;
class OptionalWithUnsignedIntegerSelectorBeginningElement;
class OptionalWithUnsignedIntegerSelectorEndElement;
class PacketBeginningElement;
class PacketContentBeginningElement;
class PacketContentEndElement;
class PacketEndElement;
class PacketInfoElement;
class PacketMagicNumberElement;
class RawDataElement;
class ScopeBeginningElement;
class ScopeEndElement;
class StaticLengthArrayBeginningElement;
class StaticLengthArrayEndElement;
class StaticLengthBlobBeginningElement;
class StaticLengthBlobEndElement;
class StaticLengthStringBeginningElement;
class StaticLengthStringEndElement;
class StructureBeginningElement;
class StructureEndElement;
class VariableLengthIntegerElement;
class VariableLengthSignedIntegerElement;
class VariableLengthUnsignedIntegerElement;
class VariantBeginningElement;
class VariantEndElement;
class VariantWithSignedIntegerSelectorBeginningElement;
class VariantWithSignedIntegerSelectorEndElement;
class VariantWithUnsignedIntegerSelectorBeginningElement;
class VariantWithUnsignedIntegerSelectorEndElement;

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
    virtual void visit(const ArrayBeginningElement&);
    virtual void visit(const ArrayEndElement&);
    virtual void visit(const BeginningElement&);
    virtual void visit(const BlobBeginningElement&);
    virtual void visit(const BlobEndElement&);
    virtual void visit(const DataStreamInfoElement&);
    virtual void visit(const DefaultClockValueElement&);
    virtual void visit(const DynamicLengthArrayBeginningElement&);
    virtual void visit(const DynamicLengthArrayEndElement&);
    virtual void visit(const DynamicLengthBlobBeginningElement&);
    virtual void visit(const DynamicLengthBlobEndElement&);
    virtual void visit(const DynamicLengthStringBeginningElement&);
    virtual void visit(const DynamicLengthStringEndElement&);
    virtual void visit(const EndElement&);
    virtual void visit(const EventRecordBeginningElement&);
    virtual void visit(const EventRecordEndElement&);
    virtual void visit(const EventRecordInfoElement&);
    virtual void visit(const FixedLengthBitArrayElement&);
    virtual void visit(const FixedLengthBitMapElement&);
    virtual void visit(const FixedLengthBooleanElement&);
    virtual void visit(const FixedLengthFloatingPointNumberElement&);
    virtual void visit(const FixedLengthSignedIntegerElement&);
    virtual void visit(const FixedLengthUnsignedIntegerElement&);
    virtual void visit(const MetadataStreamUuidElement&);
    virtual void visit(const NonNullTerminatedStringBeginningElement&);
    virtual void visit(const NonNullTerminatedStringEndElement&);
    virtual void visit(const NullTerminatedStringBeginningElement&);
    virtual void visit(const NullTerminatedStringEndElement&);
    virtual void visit(const OptionalBeginningElement&);
    virtual void visit(const OptionalEndElement&);
    virtual void visit(const OptionalWithBooleanSelectorBeginningElement&);
    virtual void visit(const OptionalWithBooleanSelectorEndElement&);
    virtual void visit(const OptionalWithSignedIntegerSelectorBeginningElement&);
    virtual void visit(const OptionalWithSignedIntegerSelectorEndElement&);
    virtual void visit(const OptionalWithUnsignedIntegerSelectorBeginningElement&);
    virtual void visit(const OptionalWithUnsignedIntegerSelectorEndElement&);
    virtual void visit(const PacketBeginningElement&);
    virtual void visit(const PacketContentBeginningElement&);
    virtual void visit(const PacketContentEndElement&);
    virtual void visit(const PacketEndElement&);
    virtual void visit(const PacketInfoElement&);
    virtual void visit(const PacketMagicNumberElement&);
    virtual void visit(const RawDataElement&);
    virtual void visit(const ScopeBeginningElement&);
    virtual void visit(const ScopeEndElement&);
    virtual void visit(const StaticLengthArrayBeginningElement&);
    virtual void visit(const StaticLengthArrayEndElement&);
    virtual void visit(const StaticLengthBlobBeginningElement&);
    virtual void visit(const StaticLengthBlobEndElement&);
    virtual void visit(const StaticLengthStringBeginningElement&);
    virtual void visit(const StaticLengthStringEndElement&);
    virtual void visit(const StructureBeginningElement&);
    virtual void visit(const StructureEndElement&);
    virtual void visit(const VariableLengthIntegerElement&);
    virtual void visit(const VariableLengthSignedIntegerElement&);
    virtual void visit(const VariableLengthUnsignedIntegerElement&);
    virtual void visit(const VariantBeginningElement&);
    virtual void visit(const VariantEndElement&);
    virtual void visit(const VariantWithSignedIntegerSelectorBeginningElement&);
    virtual void visit(const VariantWithSignedIntegerSelectorEndElement&);
    virtual void visit(const VariantWithUnsignedIntegerSelectorBeginningElement&);
    virtual void visit(const VariantWithUnsignedIntegerSelectorEndElement&);
};

} // namespace yactfr

#endif // YACTFR_ELEM_VISITOR_HPP
