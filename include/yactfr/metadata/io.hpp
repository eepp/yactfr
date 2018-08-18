/*
 * Master yactfr header file.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  I/O functions.

@ingroup metadata

The functions declared in this file format yactfr metadata objects as
strings. The resulting string is \em not TSDL (CTF&nbsp;1's metadata
language): it is a custom representation to be used for debugging only.
*/

#ifndef _YACTFR_METADATA_IO_HPP
#define _YACTFR_METADATA_IO_HPP

#include <string>
#include <ostream>

// for Size
#include "../aliases.hpp"

// for other types
#include "fwd.hpp"

namespace yactfr {

/*!
@brief  Returns a string representation of \p ref.

@param ref       Field reference.
@returns         String representation of \p ref.
*/
std::string toString(const FieldRef& ref);

/*!
@brief  Returns a string representation of \p byteOrder.

@param byteOrder    Byte order.
@returns            String representation of \p byteOrder.
*/
std::string toString(const ByteOrder& byteOrder);

/*!
@brief  Returns a string representation of \p encoding.

@param encoding     Encoding.
@returns            String representation of \p encoding.
*/
std::string toString(const Encoding& encoding);

/*!
@brief  Returns a string representation of \p dataType.

@param dataType  Data type.
@param indent    Indentation.
@returns         String representation of \p dataType.
*/
std::string toString(const DataType& dataType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p intType.

@param intType  Signed integer type.
@param indent   Indentation.
@returns        String representation of \p intType.
*/
std::string toString(const SignedIntType& intType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p intType.

@param intType  Unsigned integer type.
@param indent   Indentation.
@returns        String representation of \p intType.
*/
std::string toString(const UnsignedIntType& intType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p floatType.

@param floatType    Floating point number type.
@param indent       Indentation.
@returns            String representation of \p floatType.
*/
std::string toString(const FloatType& floatType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p enumType.

@param enumType Signed enumeration type.
@param indent   Indentation.
@returns        String representation of \p enumType.
*/
std::string toString(const SignedEnumType& enumType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p enumType.

@param enumType Unsigned enumeration type.
@param indent   Indentation.
@returns        String representation of \p enumType.
*/
std::string toString(const UnsignedEnumType& enumType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p stringType.

@param stringType   String type.
@param indent       Indentation.
@returns            String representation of \p stringType.
*/
std::string toString(const StringType& stringType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p arrayType.

@param arrayType    Array type.
@param indent       Indentation.
@returns            String representation of \p arrayType.
*/
std::string toString(const ArrayType& arrayType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p textArrayType.

@param textArrayType    Text array type.
@param indent           Indentation.
@returns                String representation of \p textArrayType.
*/
std::string toString(const TextArrayType& textArrayType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p seqType.

@param seqType  Sequence type.
@param indent   Indentation.
@returns        String representation of \p seqType.
*/
std::string toString(const SequenceType& seqType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p textSeqType.

@param textSeqType  Text sequence type.
@param indent       Indentation.
@returns            String representation of \p textSeqType.
*/
std::string toString(const TextSequenceType& textSeqType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p structType.

@param structType   Structure type.
@param indent       Indentation.
@returns            String representation of \p structType.
*/
std::string toString(const StructType& structType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p varType.

@param varType  Variant type.
@param indent   Indentation.
@returns        String representation of \p varType.
*/
std::string toString(const VariantType& varType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p structTypeField.

@param structTypeField  Structure type's field.
@param indent           Indentation.
@returns                String representation of \p structTypeField.
*/
std::string toString(const StructTypeField& structTypeField,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p variantTypeOption.

@param variantTypeOption    Variant type's option.
@param indent               Indentation.
@returns                    String representation of \p variantTypeOption.
*/
std::string toString(const VariantTypeOption& variantTypeOption,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p clockType.

@param clockType    Clock type.
@param indent       Indentation.
@returns            String representation of \p clockType.
*/
std::string toString(const ClockType& clockType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p eventRecordType.

@param eventRecordType  Event record type.
@param indent           Indentation.
@returns                String representation of \p eventRecordType.
*/
std::string toString(const EventRecordType& eventRecordType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p dataStreamType.

@param dataStreamType   Data stream type.
@param indent           Indentation.
@returns                String representation of \p dataStreamType.
*/
std::string toString(const DataStreamType& dataStreamType,
                     const Size indent = 0);

/*!
@brief  Returns a string representation of \p traceType.

@param traceType    Trace type.
@param indent       Indentation.
@returns            String representation of \p traceType.
*/
std::string toString(const TraceType& traceType,
                     const Size indent = 0);

/*!
@brief  Writes \p ref to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const FieldRef& ref)
{
       os << toString(ref);
       return os;
}

/*!
@brief  Writes \p byteOrder to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const ByteOrder& byteOrder)
{
       os << toString(byteOrder);
       return os;
}

/*!
@brief  Writes \p encoding to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const Encoding& encoding)
{
       os << toString(encoding);
       return os;
}

/*!
@brief  Writes \p dataType to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const DataType& dataType)
{
       os << toString(dataType);
       return os;
}

/*!
@brief  Writes \p structTypeField to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const StructTypeField& structTypeField)
{
       os << toString(structTypeField);
       return os;
}

/*!
@brief  Writes \p variantTypeOption to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const VariantTypeOption& variantTypeOption)
{
       os << toString(variantTypeOption);
       return os;
}

/*!
@brief  Writes \p clockType to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const ClockType& clockType)
{
       os << toString(clockType);
       return os;
}

/*!
@brief  Writes \p eventRecordType to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const EventRecordType& eventRecordType)
{
       os << toString(eventRecordType);
       return os;
}

/*!
@brief  Writes \p dataStreamType to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const DataStreamType& dataStreamType)
{
       os << toString(dataStreamType);
       return os;
}

/*!
@brief  Writes \p traceType to the output stream \p os.
*/
static inline std::ostream& operator<<(std::ostream& os,
                                       const TraceType& traceType)
{
       os << toString(traceType);
       return os;
}

} // namespace yactfr

#endif // _YACTFR_METADATA_IO_HPP
