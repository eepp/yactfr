/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
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
class BitArrayType;
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
class FloatingPointNumberType;
class IntegerType;
class InvalidMetadataStream;
class MetadataParseError;
class MetadataParseErrorMessage;
class MetadataStream;
class MetadataTextLocation;
class PacketizedMetadataStream;
class ParseError;
class PlainTextMetadataStream;
class ScalarDataType;
class SignedEnumerationType;
class SignedIntegerType;
class StaticArrayType;
class StaticTextArrayType;
class StringType;
class StructureType;
class StructureMemberType;
class TraceType;
class UnsignedEnumerationType;
class UnsignedIntegerType;
class VariantWithSignedSelectorType;
class VariantWithUnsignedSelectorType;

} // namespace yactfr

#endif // _YACTFR_METADATA_FWD_HPP
