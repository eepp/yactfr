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
class ClockOffset;
class ClockType;
class ClockValueInterval;
class CompoundDataType;
class DataLocation;
class DataStreamType;
class DataType;
class DataTypeVisitor;
class DynamicArrayType;
class DynamicTextArrayType;
class EventRecordType;
class FixedLengthBitArrayType;
class FixedLengthFloatingPointNumberType;
class FixedLengthIntegerType;
class FixedLengthSignedIntegerType;
class FixedLengthUnsignedEnumerationType;
class FixedLengthUnsignedIntegerType;
class InvalidMetadataStream;
class MetadataParseError;
class MetadataParseErrorMessage;
class MetadataStream;
class MetadataTextLocation;
class NullTerminatedStringType;
class PacketizedMetadataStream;
class ParseError;
class PlainTextMetadataStream;
class ScalarDataType;
class SignedFixedLengthEnumerationType;
class StaticArrayType;
class StaticTextArrayType;
class StructureMemberType;
class StructureType;
class TraceType;
class VariantWithSignedSelectorType;
class VariantWithUnsignedSelectorType;

} // namespace yactfr

#endif // _YACTFR_METADATA_FWD_HPP
