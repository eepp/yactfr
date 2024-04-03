/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_FWD_HPP
#define YACTFR_METADATA_FWD_HPP

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
class FixedLengthBitMapType;
class FixedLengthBooleanType;
class FixedLengthFloatingPointNumberType;
class FixedLengthSignedIntegerType;
class FixedLengthUnsignedIntegerType;
class InvalidMetadataStream;
class MetadataStream;
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
class StringType;
class StructureMemberType;
class StructureType;
class TraceType;
class VariableLengthSignedIntegerType;
class VariableLengthUnsignedIntegerType;
class VariantType;
class VariantWithSignedIntegerSelectorType;
class VariantWithUnsignedIntegerSelectorType;

} // namespace yactfr

#endif // YACTFR_METADATA_FWD_HPP
