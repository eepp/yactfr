/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FWD_HPP
#define _YACTFR_METADATA_FWD_HPP

#include "aliases.hpp"
#include "scope.hpp"
#include "bo.hpp"

namespace yactfr {

class ArrayType;
class BlobType;
class ClockOffset;
class ClockType;
class ClockValueInterval;
class CompoundDataType;
class DataLocation;
class DataStreamType;
class DataType;
class DataTypeVisitor;
class DynamicLengthArrayType;
class DynamicLengthBlobType;
class DynamicLengthStringType;
class EventRecordType;
class FixedLengthBitArrayType;
class FixedLengthBooleanType;
class FixedLengthFloatingPointNumberType;
class FixedLengthIntegerType;
class FixedLengthSignedEnumerationType;
class FixedLengthSignedIntegerType;
class FixedLengthUnsignedEnumerationType;
class FixedLengthUnsignedIntegerType;
class InvalidMetadataStream;
class MetadataParseError;
class MetadataParseErrorMessage;
class MetadataStream;
class MetadataTextLocation;
class NonNullTerminatedStringType;
class NullTerminatedStringType;
class OptionalType;
class OptionalWithBooleanSelectorType;
class OptionalWithSignedIntegerSelectorType;
class OptionalWithUnsignedIntegerSelectorType;
class PacketizedMetadataStream;
class ParseError;
class PlainTextMetadataStream;
class ScalarDataType;
class StaticLengthArrayType;
class StaticLengthBlobType;
class StaticLengthStringType;
class StructureMemberType;
class StructureType;
class TraceType;
class VariableLengthBitArrayType;
class VariableLengthIntegerType;
class VariableLengthSignedEnumerationType;
class VariableLengthSignedIntegerType;
class VariableLengthUnsignedEnumerationType;
class VariableLengthUnsignedIntegerType;
class VariantWithSignedIntegerSelectorType;
class VariantWithUnsignedIntegerSelectorType;

} // namespace yactfr

#endif // _YACTFR_METADATA_FWD_HPP
