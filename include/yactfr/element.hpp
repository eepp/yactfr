/*
 * Packet sequence iterator element.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  yactfr element: value type of a PacketSequenceIterator.

@ingroup packet_seq
*/

#ifndef _YACTFR_ELEMENT_HPP
#define _YACTFR_ELEMENT_HPP

#include <cstdint>
#include <cstdlib>
#include <string>
#include <cstring>
#include <boost/uuid/uuid.hpp>

#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/string-type.hpp>
#include <yactfr/metadata/array-type.hpp>
#include <yactfr/metadata/text-array-type.hpp>
#include <yactfr/metadata/sequence-type.hpp>
#include <yactfr/metadata/text-sequence-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/variant-type.hpp>

#include "element-visitor.hpp"

namespace yactfr {

class PacketSequence;

namespace internal {
    class Vm;
    class VmPos;
}

/*!
@brief  Value of a
        \link PacketSequenceIterator packet sequence iterator\endlink.
*/
class Element
{
public:
    /// %Kind of element.
    enum class Kind
    {
        /// PacketBeginningElement
        PACKET_BEGINNING,

        /// PacketEndElement
        PACKET_END,

        /// ScopeBeginningElement
        SCOPE_BEGINNING,

        /// ScopeEndElement
        SCOPE_END,

        /// PacketContentBeginningElement
        PACKET_CONTENT_BEGINNING,

        /// PacketContentEndElement
        PACKET_CONTENT_END,

        /// EventRecordBeginningElement
        EVENT_RECORD_BEGINNING,

        /// EventRecordEndElement
        EVENT_RECORD_END,

        /// DataStreamIdElement
        DATA_STREAM_ID,

        /// PacketOriginIndexElement
        PACKET_ORIGIN_INDEX,

        /// DataStreamTypeElement
        DATA_STREAM_TYPE,

        /// EventRecordTypeElement
        EVENT_RECORD_TYPE,

        /// ExpectedPacketTotalSizeElement
        EXPECTED_PACKET_TOTAL_SIZE,

        /// ExpectedPacketContentSizeElement
        EXPECTED_PACKET_CONTENT_SIZE,

        /// PacketMagicNumberElement
        PACKET_MAGIC_NUMBER,

        /// PacketUuidElement
        PACKET_UUID,

        /// ClockValueElement
        CLOCK_VALUE,

        /// PacketEndClockValueElement
        PACKET_END_CLOCK_VALUE,

        /// SignedIntElement
        SIGNED_INT,

        /// UnsignedIntElement
        UNSIGNED_INT,

        /// FloatElement
        FLOAT,

        /// SignedEnumElement
        SIGNED_ENUM,

        /// UnsignedEnumElement
        UNSIGNED_ENUM,

        /// StringBeginningElement
        STRING_BEGINNING,

        /// SubstringElement
        SUBSTRING,

        /// StringEndElement
        STRING_END,

        /// StructBeginningElement
        STRUCT_BEGINNING,

        /// StructEndElement
        STRUCT_END,

        /// ArrayBeginningElement
        ARRAY_BEGINNING,

        /// ArrayEndElement
        ARRAY_END,

        /// TextArrayBeginningElement
        TEXT_ARRAY_BEGINNING,

        /// TextArrayEndElement
        TEXT_ARRAY_END,

        /// SequenceBeginningElement
        SEQUENCE_BEGINNING,

        /// SequenceEndElement
        SEQUENCE_END,

        /// TextSequenceBeginningElement
        TEXT_SEQUENCE_BEGINNING,

        /// TextSequenceEndElement
        TEXT_SEQUENCE_END,

        /// VariantBeginningSignedTagElement
        VARIANT_BEGINNING_SIGNED_TAG,

        /// VariantBeginningUnsignedTagElement
        VARIANT_BEGINNING_UNSIGNED_TAG,

        /// VariantEndElement
        VARIANT_END,
    };

protected:
    explicit Element(const Kind kind) :
        _kind {kind}
    {
    }

public:
    /*!
    @brief  %Kind of this element.

    You can also use accept() with an \link ElementVisitor element
    visitor\endlink to get access to the concrete element.

    @returns    %Kind of this element.
    */
    Kind kind() const noexcept
    {
        return _kind;
    }

    /*!
    @brief  Accepts \p visitor to visit this element.

    @param visitor  Visitor to accept.
    */
    virtual void accept(ElementVisitor& visitor) const = 0;

private:
    Kind _kind;
};

/*!
@brief  Beginning base element.
*/
class BeginningElement :
    public Element
{
protected:
    explicit BeginningElement(const Kind kind) :
        Element {kind}
    {
    }
};

/*!
@brief  End base element.
*/
class EndElement :
    public Element
{
protected:
    explicit EndElement(const Kind kind) :
        Element {kind}
    {
    }
};

/*!
@brief  Packet beginning element.
*/
class PacketBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    PacketBeginningElement() :
        BeginningElement {Kind::PACKET_BEGINNING}
    {
    }
};

/*!
@brief  Packet end element.
*/
class PacketEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    PacketEndElement() :
        EndElement {Kind::PACKET_END}
    {
    }
};

class ScopeElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    /// Element's scope.
    Scope scope() const noexcept
    {
        return _scope;
    }

private:
    Scope _scope;
};

/*!
@brief  Scope beginning element.
*/
class ScopeBeginningElement final :
    public BeginningElement,
    public ScopeElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    ScopeBeginningElement() :
        BeginningElement {Kind::SCOPE_BEGINNING}
    {
    }
};

/*!
@brief  Scope end element.
*/
class ScopeEndElement final :
    public EndElement,
    public ScopeElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    ScopeEndElement() :
        EndElement {Kind::SCOPE_END}
    {
    }
};

/*!
@brief  Event record beginning element.
*/
class EventRecordBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    EventRecordBeginningElement() :
        BeginningElement {Kind::EVENT_RECORD_BEGINNING}
    {
    }
};

/*!
@brief  Event record end element.
*/
class EventRecordEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    EventRecordEndElement() :
        EndElement {Kind::EVENT_RECORD_END}
    {
    }
};

/*!
@brief  Packet content beginning element.

This element indicates the beginning of the current packet's content.
All the elements between this one and the following
PacketContentEndElement are part of the packet's content, which does \em
not include the optional padding bits before the end of the packet
(indicated by a PacketEndElement).
*/
class PacketContentBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    PacketContentBeginningElement() :
        BeginningElement {Kind::PACKET_CONTENT_BEGINNING}
    {
    }
};

/*!
@brief  Packet content end element.
*/
class PacketContentEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    PacketContentEndElement() :
        EndElement {Kind::PACKET_CONTENT_END}
    {
    }
};

/*!
@brief  Data stream ID element.

This element contains the ID of the current packet's data stream which
is known at this point. This is not to be confused with the current
packet's data stream \em type ID which is given by the
DataStreamTypeElement element.

This is sometimes called <em>stream instance ID</em> in the
specification's terminology
*/
class DataStreamIdElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    DataStreamIdElement() :
        Element {Kind::DATA_STREAM_ID}
    {
    }

public:
    /// Data stream ID.
    unsigned long long id() const noexcept
    {
        return _dataStreamId;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    unsigned long long _dataStreamId;
};

/*!
@brief  Packet's origin index element.

This element contains the numeric origin index of the current packet
within its <em>data stream</em> (\em NOT within its packet sequence)
which is known at this point.

This is sometimes called <em>packet sequence number</em> in the
specification's terminology, although this term would be confusing in
yactfr's scope since a PacketSequence object can "contain" packets from
different data streams.
*/
class PacketOriginIndexElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    PacketOriginIndexElement() :
        Element {Kind::PACKET_ORIGIN_INDEX}
    {
    }

public:
    /// Packet's origin index.
    Index index() const noexcept
    {
        return _index;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    Index _index;
};

/*!
@brief  Expected packet's total size element.

This element contains the expected total size, in bits, of the current
packet which is known at this point. This size \em includes the packet's
padding bits, if any.
*/
class ExpectedPacketTotalSizeElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    ExpectedPacketTotalSizeElement() :
        Element {Kind::EXPECTED_PACKET_TOTAL_SIZE}
    {
    }

public:
    /// Expected packet's total size (bits, multiple of 8).
    Size expectedSize() const noexcept
    {
        return _expectedSize;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    Size _expectedSize;
};

/*!
@brief  Packet's content size element.

This element contains the expected content size, in bits, of the current
packet which is known at this point. This size \em excludes the packet's
padding bits, if any: the packet's total size minus the packet's content
size provides the packet's padding size.
*/
class ExpectedPacketContentSizeElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    ExpectedPacketContentSizeElement() :
        Element {Kind::EXPECTED_PACKET_CONTENT_SIZE}
    {
    }

public:
    /// Expected packet's content size (bits).
    Size expectedSize() const noexcept
    {
        return _expectedSize;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    Size _expectedSize;
};

/*!
@brief  Packet magic number element.

This element contains the decoded packet's magic number as well as the
expected magic number. Call isValid() to get whether or not the decoded
magic number is valid as per the specification.
*/
class PacketMagicNumberElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    PacketMagicNumberElement() :
        Element {Kind::PACKET_MAGIC_NUMBER}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /// \c true if the decoded magic number is valid.
    bool isValid() const
    {
        return _value == _expectedValue;
    }

    /// Decoded magic number value.
    std::uint64_t value() const
    {
        return _value;
    }

    /// Expected magic number value.
    static constexpr std::uint64_t expectedValue()
    {
        return UINT64_C(0xc1fc1fc1);
    }

private:
    std::uint64_t _value;
    std::uint64_t _expectedValue;
};

/*!
@brief  Packet's UUID element.

This element contains the decoded packet's UUID as well as the expected
UUID. Call isValid() to get whether or not the decoded UUID is valid,
that is, that it's equal to the \link TraceType trace type\endlink's
UUID.
*/
class PacketUuidElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    PacketUuidElement() :
        Element {Kind::PACKET_UUID}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /// \c true if the decoded UUID is valid.
    bool isValid() const
    {
        return _uuid == _expectedUuid;
    }

    /// Decoded UUID.
    const boost::uuids::uuid& uuid() const
    {
        return _uuid;
    }

    /// Expected UUID.
    const boost::uuids::uuid& expectedUuid() const
    {
        return _expectedUuid;
    }

private:
    boost::uuids::uuid _uuid;
    boost::uuids::uuid _expectedUuid;
};

/*!
@brief  Clock value element.

This element provides the value of a current packet's data stream's
clock.
*/
class ClockValueElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    ClockValueElement() :
        Element {Kind::CLOCK_VALUE}
    {
    }

public:
    /// Type of the clock.
    const ClockType& clockType() const noexcept
    {
        return *_clockType;
    }

    /// Value of the clock (cycles).
    Cycles cycles() const noexcept
    {
        return _cycles;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const ClockType *_clockType;
    Cycles _cycles;
};

/*!
@brief  Packet end's clock value element.

This element provides the value of a current packet's data stream's
clock at the end of the packet.
*/
class PacketEndClockValueElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    PacketEndClockValueElement() :
        Element {Kind::PACKET_END_CLOCK_VALUE}
    {
    }

public:
    /// Type of the clock.
    const ClockType& clockType() const noexcept
    {
        return *_clockType;
    }

    /// Value of the clock (cycles) at the end of the current packet.
    Cycles cycles() const noexcept
    {
        return _cycles;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const ClockType *_clockType;
    Cycles _cycles;
};

/*!
@brief  Data stream type element.

This element contains the data stream type of the current packet which
is known at this point.
*/
class DataStreamTypeElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    DataStreamTypeElement() :
        Element {Kind::DATA_STREAM_TYPE}
    {
    }

public:
    /// Data stream type.
    const DataStreamType& dataStreamType() const noexcept
    {
        return *_dataStreamType;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const DataStreamType *_dataStreamType;
};

/*!
@brief  Event record type element.

This element contains the event record type of the current event record
which is known at this point.
*/
class EventRecordTypeElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    EventRecordTypeElement() :
        Element {Kind::EVENT_RECORD_TYPE}
    {
    }

public:
    /// Event record type.
    const EventRecordType& eventRecordType() const noexcept
    {
        return *_eventRecordType;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const EventRecordType *_eventRecordType;
};

/*!
@brief  Named data base element.
*/
class NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    /// Data name within its container, or \c nullptr if unnamed.
    const std::string *name() const noexcept
    {
        return _name;
    }

    /// Data display name within its container, or \c nullptr if unnamed.
    const std::string *displayName() const noexcept
    {
        return _dispName;
    }

private:
    const std::string *_name;
    const std::string *_dispName;
};

/*!
@brief  Signed integer data element.
*/
class SignedIntElement :
    public Element,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit SignedIntElement(const Kind kind) :
        Element {kind}
    {
    }

private:
    SignedIntElement() :
        SignedIntElement {Kind::SIGNED_INT}
    {
    }

public:
    /// Signed integer data type.
    const SignedIntType& type() const noexcept
    {
        return *_type;
    }

    /// Signed integer value.
    std::int64_t value() const noexcept
    {
        return _value;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const SignedIntType *_type;
    std::int64_t _value;
};

/*!
@brief  Unsigned integer data element.
*/
class UnsignedIntElement :
    public Element,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit UnsignedIntElement(const Kind kind) :
        Element {kind}
    {
    }

private:
    UnsignedIntElement() :
        UnsignedIntElement {Kind::UNSIGNED_INT}
    {
    }

public:
    /// Unsigned integer data type.
    const UnsignedIntType& type() const noexcept
    {
        return *_type;
    }

    /// Unsigned integer value.
    std::uint64_t value() const noexcept
    {
        return _value;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const UnsignedIntType *_type;
    std::uint64_t _value;
};

/*!
@brief  Signed enumeration data element.
*/
class SignedEnumElement final :
    public SignedIntElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    SignedEnumElement() :
        SignedIntElement {Kind::SIGNED_ENUM}
    {
    }

public:
    /// Signed enumeration data type.
    const SignedEnumType& type() const noexcept
    {
        return *static_cast<const SignedEnumType *>(_type);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Unsigned enumeration data element.
*/
class UnsignedEnumElement final :
    public UnsignedIntElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    UnsignedEnumElement() :
        UnsignedIntElement {Kind::UNSIGNED_ENUM}
    {
    }

public:
    /// Unsigned enumeration data type.
    const UnsignedEnumType& type() const noexcept
    {
        return *static_cast<const UnsignedEnumType *>(_type);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Floating point number data element.
*/
class FloatElement final :
    public Element,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    FloatElement() :
        Element {Kind::FLOAT}
    {
    }

public:
    /// Floating point number data type.
    const FloatType& type() const noexcept
    {
        return *_type;
    }

    /// Floating point number value.
    double value() const noexcept
    {
        return _value;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const FloatType *_type;
    double _value;
};

/*!
@brief  String data beginning element.

This element indicates the beginning of a data stream's string. The
next SubstringElement elements before the next StringEndElement are
consecutive substrings of this beginning string.
*/
class StringBeginningElement final :
    public BeginningElement,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    StringBeginningElement() :
        BeginningElement {Kind::STRING_BEGINNING}
    {
    }

public:
    /// String data type.
    const StringType& type() const noexcept
    {
        return *_type;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const StringType *_type;
};

/*!
@brief  String data end element.

This element indicates the end of a data stream's string started with
the last StringBeginningElement element.
*/
class StringEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    StringEndElement() :
        EndElement {Kind::STRING_END}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Substring data element.

This element can occur between StringBeginningElement and
StringEndElement elements for a data stream null-terminated string,
between TextArrayBeginningElement and TextArrayEndElement for a data
stream text array, or between TextSequenceBeginningElement and
TextSequenceEndElement for a data stream text sequence.

begin() points to the first character of the substring and end() points
to the character \em after the last character of the substring. Use
size() to compute the substring's length.

Note that the substring can contain <em>zero or more</em> null bytes. If
there's a null byte between begin() and end(), the string finishes at
this point, but for a text array/sequence, there can be other non-null
bytes before end() which are still part of the data stream data.
*/
class SubstringElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    SubstringElement() :
        Element {Kind::SUBSTRING}
    {
    }

public:
    /// Beginning of this substring's data (\em not necessarily null-terminated).
    const char *begin() const noexcept
    {
        return _begin;
    }

    /*!
    @brief  End of this substring's data (points to the character \em after
            the substring's last character).
    */
    const char *end() const noexcept
    {
        return _end;
    }

    /// Size of this substring (bytes).
    Size size() const noexcept
    {
        return _end - _begin;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const char *_begin;
    const char *_end;
};

/*!
@brief  Array data beginning element.

This element indicates the beginning of a data stream's array. The next
elements until the next ArrayEndElement at the same level are all part
of this array.
*/
class ArrayBeginningElement :
    public BeginningElement,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    ArrayBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

private:
    ArrayBeginningElement() :
        ArrayBeginningElement {Kind::ARRAY_BEGINNING}
    {
    }

public:
    /// Array data type.
    const ArrayType& type() const noexcept
    {
        return *_type;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const ArrayType *_type;
};

/*!
@brief  Array data end element.

This element indicates the end of a data stream's array started with
the last ArrayBeginningElement element at the same level.

size() returns the size of the whole array data, excluding any preceding
and following padding bits caused by alignment.
*/
class ArrayEndElement :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    ArrayEndElement(const Kind kind) :
        EndElement {kind}
    {
    }

private:
    ArrayEndElement() :
        ArrayEndElement {Kind::ARRAY_END}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Text array data beginning element.

This element indicates the beginning of a data stream's text array. The
next SubstringElement elements before the next TextArrayEndElement are
consecutive substrings of this beginning text array.
*/
class TextArrayBeginningElement final :
    public ArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    TextArrayBeginningElement() :
        ArrayBeginningElement {Kind::TEXT_ARRAY_BEGINNING}
    {
    }

public:
    /// Text array data type.
    const TextArrayType& type() const noexcept
    {
        return *static_cast<const TextArrayType *>(_type);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Text array data end element.

This element indicates the end of a data stream's text array started
with the last TextArrayBeginningElement element at the same level.
*/
class TextArrayEndElement final :
    public ArrayEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    TextArrayEndElement() :
        ArrayEndElement {Kind::TEXT_ARRAY_END}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Sequence data beginning element.

This element indicates the beginning of a data stream's sequence. The
next elements until the next SequenceEndElement at the same level are
all part of this sequence.
*/
class SequenceBeginningElement :
    public BeginningElement,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    SequenceBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

private:
    SequenceBeginningElement() :
        SequenceBeginningElement {Kind::SEQUENCE_BEGINNING}
    {
    }

public:
    /// Sequence data type.
    const SequenceType& type() const noexcept
    {
        return *_type;
    }

    /// Sequence length.
    Size length() const noexcept
    {
        return _length;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const SequenceType *_type;
    Size _length;
};

/*!
@brief  Sequence data end element.

This element indicates the end of a data stream's sequence started with
the last SequenceBeginningElement element at the same level.

size() returns the size of the whole sequence data, excluding any preceding
and following padding bits caused by alignment.
*/
class SequenceEndElement :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    SequenceEndElement(const Kind kind) :
        EndElement {kind}
    {
    }

private:
    SequenceEndElement() :
        SequenceEndElement {Kind::SEQUENCE_END}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Text sequence data beginning element.

This element indicates the beginning of a data stream's text sequence.
The next SubstringElement elements before the next
TextSequenceEndElement are consecutive substrings of this beginning text
sequence.
*/
class TextSequenceBeginningElement final :
    public SequenceBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    TextSequenceBeginningElement() :
        SequenceBeginningElement {Kind::TEXT_SEQUENCE_BEGINNING}
    {
    }

public:
    /// Text sequence data type.
    const TextSequenceType& type() const noexcept
    {
        return *static_cast<const TextSequenceType *>(_type);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Text sequence data end element.

This element indicates the end of a data stream's text sequence started
with the last TextSequenceBeginningElement element at the same level.
*/
class TextSequenceEndElement final :
    public SequenceEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    TextSequenceEndElement() :
        SequenceEndElement {Kind::TEXT_SEQUENCE_END}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Structure data beginning element.

This element indicates the beginning of a data stream's structure. The
next elements until the next StructEndElement at the same level are all
part of this structure.
*/
class StructBeginningElement final :
    public BeginningElement,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    StructBeginningElement() :
        BeginningElement {Kind::STRUCT_BEGINNING}
    {
    }

public:
    /// Structure data type.
    const StructType& type() const noexcept
    {
        return *_type;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const StructType *_type;
};

/*!
@brief  Structure data end element.

This element indicates the end of a data stream's structure started with
the last StructBeginningElement element at the same level.

size() returns the size of the whole structure data, excluding any
preceding and following padding bits caused by alignment.
*/
class StructEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    StructEndElement() :
        EndElement {Kind::STRUCT_END}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Common variant data beginning element.
*/
class VariantBeginningElement :
    public BeginningElement,
    public NamedDataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    VariantBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Variant data type.
    const VariantType& type() const noexcept
    {
        return *_type;
    }

private:
    const VariantType *_type;
};

/*!
@brief  Variant data beginning (with tag) base element.
*/
template <typename TagT, Element::Kind KindV>
class VariantBeginningWithTagElement :
    public VariantBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    VariantBeginningWithTagElement() :
        VariantBeginningElement {KindV}
    {
    }

public:
    /// Variant data type.
    const VariantType& type() const noexcept
    {
        return *_type;
    }

    /// Variant tag.
    TagT tag() const noexcept
    {
        return _tag;
    }

private:
    const VariantType *_type;
    TagT _tag;
};

/*!
@brief  Variant data beginning element (signed tag).

This element indicates the beginning of a data stream's variant with a
signed tag. The next element is the selected element of this variant.
Expect a VariantEndElement after this next element at the same level.
*/
class VariantBeginningSignedTagElement final :
    public VariantBeginningWithTagElement<std::int64_t,
                                          Element::Kind::VARIANT_BEGINNING_SIGNED_TAG>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    VariantBeginningSignedTagElement()
    {
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Variant data beginning element (unsigned tag).

This element indicates the beginning of a data stream's variant with a
unsigned tag. The next element is the selected element of this variant.
Expect a VariantEndElement after this next element at the same level.
*/
class VariantBeginningUnsignedTagElement final :
    public VariantBeginningWithTagElement<std::uint64_t,
                                          Element::Kind::VARIANT_BEGINNING_UNSIGNED_TAG>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    VariantBeginningUnsignedTagElement()
    {
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief  Variant data end element.

This element indicates the end of a data stream's variant started with
the last VariantBeginningElement element at the same level.

size() returns the size of the whole variant data, excluding any
preceding and following padding bits caused by alignment.
*/
class VariantEndElement :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    VariantEndElement() :
        EndElement {Kind::VARIANT_END}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_ELEMENT_HPP
