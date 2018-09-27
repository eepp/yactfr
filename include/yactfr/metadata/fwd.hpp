/*
 * Forward declarations.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Forward declarations of the metadata namespace.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_FWD_HPP
#define _YACTFR_METADATA_FWD_HPP

#include "aliases.hpp"
#include "scope.hpp"
#include "byte-order.hpp"
#include "encoding.hpp"

namespace yactfr {

class ArrayType;
class BitArrayType;
class ClockType;
class ClockTypeOffset;
class ClockValueInterval;
class CompoundType;
class DataStreamType;
class DataType;
class DataTypeVisitor;
class DynamicArrayType;
class DynamicTextArrayType;
class EventRecordType;
class FieldRef;
class FloatType;
class IntType;
class InvalidMetadata;
class InvalidMetadataStream;
class MetadataParseError;
class MetadataParseErrorMessage;
class MetadataStream;
class MetadataTextLocation;
class NamedDataType;
class NoSuchIndex;
class NoSuchName;
class NoSuchTypeId;
class PacketizedMetadataStream;
class ParseError;
class PlainTextMetadataStream;
class ScalarType;
class SignedEnumType;
class SignedIntType;
class StaticArrayType;
class StaticTextArrayType;
class StringType;
class StructType;
class StructTypeField;
class TraceType;
class TraceTypeEnv;
class UnsignedEnumType;
class UnsignedIntType;
class VariantType;
class VariantTypeOption;

} // namespace yactfr

#endif // _YACTFR_METADATA_FWD_HPP
