/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ELEM_HPP
#define _YACTFR_ELEM_HPP

#include <cstdint>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/optional/optional.hpp>

#include "metadata/fwd.hpp"
#include "metadata/dt.hpp"
#include "metadata/fl-bit-array-type.hpp"
#include "metadata/fl-bool-type.hpp"
#include "metadata/fl-float-type.hpp"
#include "metadata/fl-int-type.hpp"
#include "metadata/fl-enum-type.hpp"
#include "metadata/vl-bit-array-type.hpp"
#include "metadata/vl-int-type.hpp"
#include "metadata/vl-enum-type.hpp"
#include "metadata/sl-array-type.hpp"
#include "metadata/dl-array-type.hpp"
#include "metadata/sl-str-type.hpp"
#include "metadata/dl-str-type.hpp"
#include "metadata/sl-blob-type.hpp"
#include "metadata/dl-blob-type.hpp"
#include "metadata/var-type.hpp"
#include "metadata/opt-type.hpp"
#include "elem-visitor.hpp"
#include "aliases.hpp"

namespace yactfr {
namespace internal {

class Vm;
class VmPos;

} // namespace internal

/*!
@defgroup elems Elements
@brief
    Elements.
@ingroup element_seq
*/

/*!
@brief
    Value of an
    \link ElementSequenceIterator element sequence iterator\endlink.

@ingroup elems
*/
class Element
{
public:
    /// %Kind of element.
    enum class Kind
    {
        /// EndElement
        END,

        /// PacketBeginningElement
        PACKET_BEGINNING,

        /// ScopeBeginningElement
        SCOPE_BEGINNING,

        /// PacketContentBeginningElement
        PACKET_CONTENT_BEGINNING,

        /// EventRecordBeginningElement
        EVENT_RECORD_BEGINNING,

        /// PacketMagicNumberElement
        PACKET_MAGIC_NUMBER,

        /// TraceTypeUuidElement
        TRACE_TYPE_UUID,

        /// DataStreamInfoElement
        DATA_STREAM_INFO,

        /// DefaultClockValueElement
        DEFAULT_CLOCK_VALUE,

        /// PacketInfoElement
        PACKET_INFO,

        /// EventRecordInfoElement
        EVENT_RECORD_INFO,

        /// FixedLengthBitArrayElement
        FIXED_LENGTH_BIT_ARRAY,

        /// FixedLengthBooleanElement
        FIXED_LENGTH_BOOLEAN,

        /// FixedLengthSignedIntegerElement
        FIXED_LENGTH_SIGNED_INTEGER,

        /// FixedLengthUnsignedIntegerElement
        FIXED_LENGTH_UNSIGNED_INTEGER,

        /// FixedLengthFloatingPointNumberElement
        FIXED_LENGTH_FLOATING_POINT_NUMBER,

        /// FixedLengthSignedEnumerationElement
        FIXED_LENGTH_SIGNED_ENUMERATION,

        /// FixedLengthUnsignedEnumerationElement
        FIXED_LENGTH_UNSIGNED_ENUMERATION,

        /// VariableLengthBitArrayElement
        VARIABLE_LENGTH_BIT_ARRAY,

        /// VariableLengthSignedIntegerElement
        VARIABLE_LENGTH_SIGNED_INTEGER,

        /// VariableLengthUnsignedIntegerElement
        VARIABLE_LENGTH_UNSIGNED_INTEGER,

        /// VariableLengthSignedEnumerationElement
        VARIABLE_LENGTH_SIGNED_ENUMERATION,

        /// VariableLengthUnsignedEnumerationElement
        VARIABLE_LENGTH_UNSIGNED_ENUMERATION,

        /// NullTerminatedStringBeginningElement
        NULL_TERMINATED_STRING_BEGINNING,

        /// SubstringElement
        SUBSTRING,

        /// BlobSectionElement
        BLOB_SECTION,

        /// StructureBeginningElement
        STRUCTURE_BEGINNING,

        /// StaticLengthArrayBeginningElement
        STATIC_LENGTH_ARRAY_BEGINNING,

        /// DynamicLengthArrayBeginningElement
        DYNAMIC_LENGTH_ARRAY_BEGINNING,

        /// StaticLengthBlobBeginningElement
        STATIC_LENGTH_BLOB_BEGINNING,

        /// DynamicLengthBlobBeginningElement
        DYNAMIC_LENGTH_BLOB_BEGINNING,

        /// StaticLengthStringBeginningElement
        STATIC_LENGTH_STRING_BEGINNING,

        /// DynamicLengthStringBeginningElement
        DYNAMIC_LENGTH_STRING_BEGINNING,

        /// VariantWithSignedIntegerSelectorBeginningElement
        VARIANT_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING,

        /// VariantWithUnsignedIntegerSelectorBeginningElement
        VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING,

        /// OptionalWithBooleanSelectorBeginningElement
        OPTIONAL_WITH_BOOLEAN_SELECTOR_BEGINNING,

        /// OptionalWithSignedIntegerSelectorBeginningElement
        OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING,

        /// OptionalWithUnsignedIntegerSelectorBeginningElement
        OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING,
    };

protected:
    explicit Element(const Kind kind) :
        _kind {kind}
    {
    }

public:
    /*!
    @brief
        %Kind of this element.

    You can also use accept() with an \link ElementVisitor element
    visitor\endlink to get access to the concrete element.

    @returns
        %Kind of this element.
    */
    Kind kind() const noexcept
    {
        return _kind;
    }

    /*!
    @brief
        Accepts \p visitor to visit this element.

    @param[in] visitor
        Visitor to accept.
    */
    virtual void accept(ElementVisitor& visitor) const = 0;

private:
    Kind _kind;
};

/*!
@brief
    Beginning base element.

@ingroup elems

@sa EndElement
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
@brief
    End element.

@ingroup elems

@sa BeginningElement
*/
class EndElement :
    public Element
{
public:
    explicit EndElement() :
        Element {Kind::END}
    {
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Packet beginning element.

@ingroup elems
*/
class PacketBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketBeginningElement() :
        BeginningElement {Kind::PACKET_BEGINNING}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Scope beginning element.

@ingroup elems
*/
class ScopeBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit ScopeBeginningElement() :
        BeginningElement {Kind::SCOPE_BEGINNING}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /// Scope.
    Scope scope() const noexcept
    {
        return _scope;
    }

private:
    Scope _scope;
};

/*!
@brief
    Event record beginning element.

@ingroup elems
*/
class EventRecordBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit EventRecordBeginningElement() :
        BeginningElement {Kind::EVENT_RECORD_BEGINNING}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Packet content beginning element.

@ingroup elems

This element indicates the beginning of the \em content of the current
packet.

All the elements between this one and the following EndElement at the
same level within a given element sequence are part of the packet
content, which does \em not include the optional padding bits before the
end of the packet (indicated by an EndElement at a higher level).
*/
class PacketContentBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketContentBeginningElement() :
        BeginningElement {Kind::PACKET_CONTENT_BEGINNING}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Packet magic number element.

@ingroup elems

This element contains the magic number of the decoded packet as well as
the expected magic number (always 0xc1fc1fc1).

Call isValid() to get whether or not the decoded magic number is valid
as per the specification.
*/
class PacketMagicNumberElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketMagicNumberElement() :
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
        return _val == _expectedValue;
    }

    /// Decoded magic number value.
    unsigned long long value() const
    {
        return _val;
    }

    /// Expected magic number value.
    static constexpr unsigned long long expectedValue()
    {
        return UINT64_C(0xc1fc1fc1);
    }

private:
    unsigned long long _val;
    unsigned long long _expectedValue;
};

/*!
@brief
    Trace type UUID element.

@ingroup elems

This element contains the decoded trace type UUID as well as the
expected trace type UUID.

isValid() indicates whether or not the decoded UUID is valid, that is,
that it's equal to TraceType::uuid().
*/
class TraceTypeUuidElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit TraceTypeUuidElement() :
        Element {Kind::TRACE_TYPE_UUID}
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
@brief
    Data stream information element.

@ingroup elems

This element contains information about the current data stream, as
found in the header of the current packet.
*/
class DataStreamInfoElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DataStreamInfoElement() :
        Element {Kind::DATA_STREAM_INFO}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /// Type of the data stream of the current packet, or \c nullptr if
    /// the trace type has no data stream types.
    const DataStreamType *type() const noexcept
    {
        return _dst;
    }

    /*!
    @brief
        ID of the data stream of the current packet.

    @note
        Not to be confused with the \em type ID of the data stream of
        the current packet: use type() and then DataStreamType::id().
    */
    const boost::optional<unsigned long long>& id() const noexcept
    {
        return _id;
    }

private:
    void _reset() noexcept
    {
        _dst = nullptr;
        _id = boost::none;
    }

private:
    const DataStreamType *_dst = nullptr;
    boost::optional<unsigned long long> _id;
};

/*!
@brief
    Default clock value element.

@ingroup elems

This element provides the value of the default clock of the data stream
of the current packet.
*/
class DefaultClockValueElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DefaultClockValueElement() :
        Element {Kind::DEFAULT_CLOCK_VALUE}
    {
    }

public:
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
    Cycles _cycles;
};

/*!
@brief
    Packet information element.

@ingroup elems

This element contains information about the current packet, as found in
its context.

As per the CTF rules:

- <strong>If expectedTotalLength() and expectedContentLength() are both
  not set</strong>: the total and content lengths of this packet are the
  length of the current data stream (this packet is the only one within
  its data stream).

- <strong>If expectedTotalLength() is set, but expectedContentLength()
  isn't</strong>: the expected content length of this packet is its
  expected total length (value of expectedTotalLength()).

- <strong>If expectedContentLength() is set, but expectedTotalLength()
  isn't</strong>: the expected total length of this packet is its
  expected content length (value of expectedContentLength()).
*/
class PacketInfoElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketInfoElement() :
        Element {Kind::PACKET_INFO}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /*!
    @brief
        Numeric sequence number of the current packet
        within its <em>data stream</em> (\em not within its element
        sequence).
    */
    const boost::optional<Index>& sequenceNumber() const noexcept
    {
        return _seqNum;
    }

    /*!
    @brief
        Count of total discarded event records at the end of the current
        packet since the beginning of its <em>data stream</em> (\em not
        its element sequence).
    */
    const boost::optional<Size>& discardedEventRecordCounterSnapshot() const noexcept
    {
        return _discErCounterSnap;
    }

    /*!
    @brief
        Expected total length, in bits, of the current packet.

    This length \em includes the packet padding bits before the end of
    the packet, if any.
    */
    const boost::optional<Size>& expectedTotalLength() const noexcept
    {
        return _expectedTotalLen;
    }

    /*!
    @brief
        Expected content length, in bits, of the current packet.

    This length \em excludes the packet padding bits before the end of
    the packet, if any: the total length of the packet minus its content
    length provides its padding length.
    */
    const boost::optional<Size>& expectedContentLength() const noexcept
    {
        return _expectedContentLen;
    }

    /*!
    @brief
        Value of the default clock of the data stream of the current
        packet at its end

    During the packet decoding process, this default clock value is
    known \em before decoding the event records.

    @sa DefaultClockValueElement
    */
    const boost::optional<Cycles>& endDefaultClockValue() const noexcept
    {
        return _endDefClkVal;
    }

private:
    void _reset() noexcept
    {
        _seqNum = boost::none;
        _discErCounterSnap = boost::none;
        _expectedTotalLen = boost::none;
        _expectedContentLen = boost::none;
        _endDefClkVal = boost::none;
    }

private:
    boost::optional<Index> _seqNum;
    boost::optional<Size> _discErCounterSnap;
    boost::optional<Size> _expectedTotalLen;
    boost::optional<Size> _expectedContentLen;
    boost::optional<Cycles> _endDefClkVal;
};

/*!
@brief
    Event record information element.

@ingroup elems

This element contains information about the current event record, as
found in its header.
*/
class EventRecordInfoElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit EventRecordInfoElement() :
        Element {Kind::EVENT_RECORD_INFO}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /// Type of the current event record, or \c nullptr if the dat
    /// stream type has no event record types.
    const EventRecordType *type() const noexcept
    {
        return _ert;
    }

private:
    void _reset() noexcept
    {
        _ert = nullptr;
    }

private:
    const EventRecordType *_ert = nullptr;
};

/*!
@brief
    Data base element.

@ingroup elems
*/
class DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit DataElement() = default;

public:
    /// Type of the immediate structure member containing this element,
    /// or \c nullptr if none (scope).
    const StructureMemberType *structureMemberType() const noexcept
    {
        return _structMemberType;
    }

private:
    const StructureMemberType *_structMemberType;
};

/*!
@brief
    Bit array base element.

@ingroup elems
*/
class BitArrayElement :
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit BitArrayElement() = default;

public:
    /// Value as an unsigned integer.
    std::uint64_t unsignedIntegerValue() const noexcept
    {
        return _theVal.u;
    }

    /*!
    @brief
        Returns the value of the bit at the index \p index, where
        0 is the index of the least significant bit.

    @param[in] index
        Index of the bit to return.

    @returns
        Bit at the index \p index.

    @pre
        \p index < <code>type().length()</code>
    */
    bool operator[](const Index index) const noexcept
    {
        return static_cast<bool>((_theVal.u >> index) & 1);
    }

private:
    void _val(const std::uint64_t val) noexcept
    {
        _theVal.u = val;
    }

    void _val(const std::int64_t val) noexcept
    {
        _theVal.i = val;
    }

    void _val(const double val) noexcept
    {
        _theVal.d = val;
    }

protected:
    union {
        std::uint64_t u;
        std::int64_t i;
        double d;
    } _theVal;
};

/*!
@brief
    Fixed-length bit array element.

@ingroup elems
*/
class FixedLengthBitArrayElement :
    public Element,
    public BitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthBitArrayElement(const Kind kind) :
        Element {kind}
    {
    }

private:
    explicit FixedLengthBitArrayElement() :
        FixedLengthBitArrayElement {Kind::FIXED_LENGTH_BIT_ARRAY}
    {
    }

public:
    /// Fixed-length bit array type.
    const FixedLengthBitArrayType& type() const noexcept
    {
        return *_dt;
    }

    /*!
    @brief
        Returns the value of the bit at the index \p index, where
        0 is the index of the least significant bit.

    @param[in] index
        Index of the bit to return.

    @returns
        Bit at the index \p index.

    @pre
        \p index < <code>type().length()</code>
    */
    bool operator[](const Index index) const noexcept
    {
        assert(index < _dt->length());
        return BitArrayElement::operator[](index);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    void _val(const std::uint64_t val) noexcept
    {
        _theVal.u = val;
    }

    void _val(const std::int64_t val) noexcept
    {
        _theVal.i = val;
    }

    void _val(const double val) noexcept
    {
        _theVal.d = val;
    }

protected:
    const FixedLengthBitArrayType *_dt;

    union {
        std::uint64_t u;
        std::int64_t i;
        double d;
    } _theVal;
};

/*!
@brief
    Fixed-length boolean element.

@ingroup elems
*/
class FixedLengthBooleanElement final :
    public FixedLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthBooleanElement() :
        FixedLengthBitArrayElement {Kind::FIXED_LENGTH_BOOLEAN}
    {
    }

public:
    /// Fixed-length boolean type.
    const FixedLengthBooleanType& type() const noexcept
    {
        return *_dt;
    }

    /// Boolean value.
    bool value() const noexcept
    {
        return static_cast<bool>(_theVal.u);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const FixedLengthBooleanType *_dt;
};

/*!
@brief
    Fixed-length signed integer element.

@ingroup elems
*/
class FixedLengthSignedIntegerElement :
    public FixedLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthSignedIntegerElement(const Kind kind) :
        FixedLengthBitArrayElement {kind}
    {
    }

private:
    explicit FixedLengthSignedIntegerElement() :
        FixedLengthSignedIntegerElement {Kind::FIXED_LENGTH_SIGNED_INTEGER}
    {
    }

public:
    /// Fixed-length signed integer type.
    const FixedLengthSignedIntegerType& type() const noexcept
    {
        return _dt->asFixedLengthSignedIntegerType();
    }

    /// Integral value.
    long long value() const noexcept
    {
        return static_cast<long long>(_theVal.i);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length unsigned integer element.

@ingroup elems
*/
class FixedLengthUnsignedIntegerElement :
    public FixedLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthUnsignedIntegerElement(const Kind kind) :
        FixedLengthBitArrayElement {kind}
    {
    }

private:
    explicit FixedLengthUnsignedIntegerElement() :
        FixedLengthUnsignedIntegerElement {Kind::FIXED_LENGTH_UNSIGNED_INTEGER}
    {
    }

public:
    /// Fixed-length unsigned integer type.
    const FixedLengthUnsignedIntegerType& type() const noexcept
    {
        return _dt->asFixedLengthUnsignedIntegerType();
    }

    /// Integral value.
    unsigned long long value() const noexcept
    {
        return static_cast<unsigned long long>(_theVal.u);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length signed enumeration element.

@ingroup elems
*/
class FixedLengthSignedEnumerationElement final :
    public FixedLengthSignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthSignedEnumerationElement() :
        FixedLengthSignedIntegerElement {Kind::FIXED_LENGTH_SIGNED_ENUMERATION}
    {
    }

public:
    /// Fixed-length signed enumeration type.
    const FixedLengthSignedEnumerationType& type() const noexcept
    {
        return _dt->asFixedLengthSignedEnumerationType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length unsigned enumeration element.

@ingroup elems
*/
class FixedLengthUnsignedEnumerationElement final :
    public FixedLengthUnsignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthUnsignedEnumerationElement() :
        FixedLengthUnsignedIntegerElement {Kind::FIXED_LENGTH_UNSIGNED_ENUMERATION}
    {
    }

public:
    /// Fixed-length unsigned enumeration type.
    const FixedLengthUnsignedEnumerationType& type() const noexcept
    {
        return _dt->asFixedLengthUnsignedEnumerationType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length floating point number element.

@ingroup elems
*/
class FixedLengthFloatingPointNumberElement final :
    public FixedLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthFloatingPointNumberElement() :
        FixedLengthBitArrayElement {Kind::FIXED_LENGTH_FLOATING_POINT_NUMBER}
    {
    }

public:
    /// Fixed-length floating point number type.
    const FixedLengthFloatingPointNumberType& type() const noexcept
    {
        return _dt->asFixedLengthFloatingPointNumberType();
    }

    /// Real value.
    double value() const noexcept
    {
        return _theVal.d;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variable-length bit array element.

@ingroup elems
*/
class VariableLengthBitArrayElement :
    public Element,
    public BitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariableLengthBitArrayElement(const Kind kind) :
        Element {kind}
    {
    }

private:
    explicit VariableLengthBitArrayElement() :
        VariableLengthBitArrayElement {Kind::VARIABLE_LENGTH_BIT_ARRAY}
    {
    }

public:
    /// Variable-length bit array type.
    const VariableLengthBitArrayType& type() const noexcept
    {
        return *_dt;
    }

    /// Bit-array length (bits).
    Size length() const noexcept
    {
        return _len;
    }

    /*!
    @brief
        Returns the value of the bit at the index \p index, where
        0 is the index of the least significant bit.

    @param[in] index
        Index of the bit to return.

    @returns
        Bit at the index \p index.

    @pre
        \p index < <code>length()</code>
    */
    bool operator[](const Index index) const noexcept
    {
        assert(index < _len);
        return BitArrayElement::operator[](index);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const VariableLengthBitArrayType *_dt;

private:
    Size _len;
};

/*!
@brief
    Variable-length signed integer element.

@ingroup elems
*/
class VariableLengthSignedIntegerElement :
    public VariableLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariableLengthSignedIntegerElement(const Kind kind) :
        VariableLengthBitArrayElement {kind}
    {
    }

private:
    explicit VariableLengthSignedIntegerElement() :
        VariableLengthSignedIntegerElement {Kind::VARIABLE_LENGTH_SIGNED_INTEGER}
    {
    }

public:
    /// Variable-length signed integer type.
    const VariableLengthSignedIntegerType& type() const noexcept
    {
        return _dt->asVariableLengthSignedIntegerType();
    }

    /// Integral value.
    long long value() const noexcept
    {
        return static_cast<long long>(_theVal.i);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variable-length unsigned integer element.

@ingroup elems
*/
class VariableLengthUnsignedIntegerElement :
    public VariableLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariableLengthUnsignedIntegerElement(const Kind kind) :
        VariableLengthBitArrayElement {kind}
    {
    }

private:
    explicit VariableLengthUnsignedIntegerElement() :
        VariableLengthUnsignedIntegerElement {Kind::VARIABLE_LENGTH_UNSIGNED_INTEGER}
    {
    }

public:
    /// Variable-length unsigned integer type.
    const VariableLengthUnsignedIntegerType& type() const noexcept
    {
        return _dt->asVariableLengthUnsignedIntegerType();
    }

    /// Integral value.
    unsigned long long value() const noexcept
    {
        return static_cast<unsigned long long>(_theVal.u);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const VariableLengthUnsignedIntegerType *_dt;
};

/*!
@brief
    Variable-length signed enumeration element.

@ingroup elems
*/
class VariableLengthSignedEnumerationElement final :
    public VariableLengthSignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariableLengthSignedEnumerationElement() :
        VariableLengthSignedIntegerElement {Kind::VARIABLE_LENGTH_SIGNED_ENUMERATION}
    {
    }

public:
    /// Variable-length signed enumeration type.
    const VariableLengthSignedEnumerationType& type() const noexcept
    {
        return _dt->asVariableLengthSignedEnumerationType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variable-length unsigned enumeration element.

@ingroup elems
*/
class VariableLengthUnsignedEnumerationElement final :
    public VariableLengthUnsignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariableLengthUnsignedEnumerationElement() :
        VariableLengthUnsignedIntegerElement {Kind::VARIABLE_LENGTH_UNSIGNED_ENUMERATION}
    {
    }

public:
    /// Variable-length unsigned enumeration type.
    const VariableLengthUnsignedEnumerationType& type() const noexcept
    {
        return _dt->asVariableLengthUnsignedEnumerationType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Null-terminated string beginning element.

@ingroup elems

This element indicates the beginning of a data stream null-terminated
string.

The next SubstringElement elements before the next EndElement are
consecutive substrings of this beginning null-terminated string.

@sa SubstringElement
@sa EndElement
*/
class NullTerminatedStringBeginningElement final :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit NullTerminatedStringBeginningElement() :
        BeginningElement {Kind::NULL_TERMINATED_STRING_BEGINNING}
    {
    }

public:
    /// Null-terminated string type.
    const NullTerminatedStringType& type() const noexcept
    {
        return *_dt;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const NullTerminatedStringType *_dt;
};

/*!
@brief
    Substring element.

@ingroup elems

This element can occur:

<dl>
  <dt>Data stream null-terminated string</dt>
  <dd>
    Between NullTerminatedStringBeginningElement and EndElement elements.
  </dd>

  <dt>Data stream static-length string</dt>
  <dd>
    Between StaticLengthStringBeginningElement and EndElement elements.
  </dd>

  <dt>Data stream dynamic-length string</dt>
  <dd>
    Between DynamicLengthStringBeginningElement and EndElement elements.
  </dd>
</dl>

begin() points to the first character of the substring and end() points
to the character \em after the last character of the substring. Use
length() to compute the length of the substring.

Note that the substring can contain <em>zero or more</em> null bytes. If
there's a null byte between begin() and end(), the string finishes at
this point, but for static-length and dynamic-length strings, there can
be other non-null bytes before end() which are still part of the data
stream.
*/
class SubstringElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit SubstringElement() :
        Element {Kind::SUBSTRING}
    {
    }

public:
    /// Beginning of the data of this substring (\em not necessarily
    /// null-terminated).
    const char *begin() const noexcept
    {
        return _begin;
    }

    /// End of the data of this substring (points to the character \em
    /// after the last character of the substring).
    const char *end() const noexcept
    {
        return _end;
    }

    /// Size of this substring (bytes), including null characters and
    /// characters after that, if any.
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
@brief
    BLOB section element.

@ingroup elems

This element can occur:

<dl>
  <dt>Data stream static-length BLOB</dt>
  <dd>
    Between StaticLengthBlobBeginningElement and EndElement elements.
  </dd>

  <dt>Data stream dynamic-length BLOB</dt>
  <dd>
    Between DynamicLengthBlobBeginningElement and EndElement elements.
  </dd>
</dl>

begin() points to the first byte of the BLOB section and end() points to
the byte \em after the last byte of the BLOB section. Use length() to
compute the length of the BLOB section.
*/
class BlobSectionElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit BlobSectionElement() :
        Element {Kind::BLOB_SECTION}
    {
    }

public:
    /// Beginning of the data of this BLOB section.
    const std::uint8_t *begin() const noexcept
    {
        return _begin;
    }

    /// End of the data of this BLOB section.
    const std::uint8_t *end() const noexcept
    {
        return _end;
    }

    /// Size (bytes) of this BLOB section.
    Size size() const noexcept
    {
        return _end - _begin;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const std::uint8_t *_begin;
    const std::uint8_t *_end;
};

/*!
@brief
    Array beginning base element.

@ingroup elems
*/
class ArrayBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    ArrayBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Array type.
    const ArrayType& type() const noexcept
    {
        return *_dt;
    }

    /// Array length.
    Size length() const noexcept
    {
        return _len;
    }

protected:
    const ArrayType *_dt;
    Size _len;
};

/*!
@brief
    Static-length array beginning element.

@ingroup elems

This element indicates the beginning of a data stream static-length
array.

The next elements until the next EndElement at the same level are all
part of this static-length array.

@sa EndElement
*/
class StaticLengthArrayBeginningElement final :
    public ArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthArrayBeginningElement() :
        ArrayBeginningElement {Kind::STATIC_LENGTH_ARRAY_BEGINNING}
    {
    }

public:
    /// Static-length array type.
    const StaticLengthArrayType& type() const noexcept
    {
        return _dt->asStaticLengthArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length array beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic-length
array.

The next elements until the next EndElement at the same level are all
part of this dynamic-length array.

@sa EndElement
*/
class DynamicLengthArrayBeginningElement final :
    public ArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthArrayBeginningElement() :
        ArrayBeginningElement {Kind::DYNAMIC_LENGTH_ARRAY_BEGINNING}
    {
    }

public:
    /// Dynamic-length array type.
    const DynamicLengthArrayType& type() const noexcept
    {
        return _dt->asDynamicLengthArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Non null-terminated string beginning base element.

@ingroup elems
*/
class NonNullTerminatedStringBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    NonNullTerminatedStringBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Non null-terminated string type.
    const NonNullTerminatedStringType& type() const noexcept
    {
        return *_dt;
    }

    /// Maximum length (bytes).
    Size maximumLength() const noexcept
    {
        return _maxLen;
    }

protected:
    const NonNullTerminatedStringType *_dt;
    Size _maxLen;
};

/*!
@brief
    Static-length string beginning element.

@ingroup elems

This element indicates the beginning of a data stream static-length
string.

The next SubstringElement elements before the next EndElement are
consecutive substrings of this beginning static-length string.

@sa SubstringElement
@sa EndElement
*/
class StaticLengthStringBeginningElement final :
    public NonNullTerminatedStringBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthStringBeginningElement() :
        NonNullTerminatedStringBeginningElement {Kind::STATIC_LENGTH_STRING_BEGINNING}
    {
    }

public:
    /// Static-length string type.
    const StaticLengthStringType& type() const noexcept
    {
        return _dt->asStaticLengthStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length string beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic-length
string.

The next SubstringElement elements before the next EndElement are
consecutive substrings of this beginning dynamic-length string.

@sa SubstringElement
@sa EndElement
*/
class DynamicLengthStringBeginningElement final :
    public NonNullTerminatedStringBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthStringBeginningElement() :
        NonNullTerminatedStringBeginningElement {Kind::DYNAMIC_LENGTH_STRING_BEGINNING}
    {
    }

public:
    /// Dynamic-length string type.
    const DynamicLengthStringType& type() const noexcept
    {
        return _dt->asDynamicLengthStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    BLOB beginning base element.

@ingroup elems
*/
class BlobBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    BlobBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// BLOB type.
    const BlobType& type() const noexcept
    {
        return *_dt;
    }

    /// BLOB length (bytes).
    Size length() const noexcept
    {
        return _len;
    }

protected:
    const BlobType *_dt;
    Size _len;
};

/*!
@brief
    Static-length BLOB beginning element.

@ingroup elems

This element indicates the beginning of a data stream static-length
BLOB.

The next BlobSectionElement elements before the next EndElement are
consecutive BLOB sections of this beginning static-length BLOB.

@sa BlobSectionElement
@sa EndElement
*/
class StaticLengthBlobBeginningElement final :
    public BlobBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthBlobBeginningElement() :
        BlobBeginningElement {Kind::STATIC_LENGTH_BLOB_BEGINNING}
    {
    }

public:
    /// Static-length BLOB type.
    const StaticLengthBlobType& type() const noexcept
    {
        return _dt->asStaticLengthBlobType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length BLOB beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic-length
BLOB.

The next BlobSectionElement elements before the next EndElement are
consecutive BLOB sections of this beginning dynamic-length BLOB.

@sa EndElement
*/
class DynamicLengthBlobBeginningElement final :
    public BlobBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthBlobBeginningElement() :
        BlobBeginningElement {Kind::DYNAMIC_LENGTH_BLOB_BEGINNING}
    {
    }

public:
    /// Dynamic-length BLOB type.
    const DynamicLengthBlobType& type() const noexcept
    {
        return _dt->asDynamicLengthBlobType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Structure beginning element.

@ingroup elems

This element indicates the beginning of a data stream structure.

The next elements until the next EndElement at the same level are all
part of this structure.

@sa EndElement
*/
class StructureBeginningElement final :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StructureBeginningElement() :
        BeginningElement {Kind::STRUCTURE_BEGINNING}
    {
    }

public:
    /// Structure type.
    const StructureType& type() const noexcept
    {
        return *_dt;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const StructureType *_dt;
};

/*!
@brief
    Common variant beginning element.

@ingroup elems

@sa VariantWithUnsignedIntegerSelectorBeginningElement
@sa VariantWithSignedIntegerSelectorBeginningElement
@sa EndElement
*/
class VariantBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    VariantBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }
};

/*!
@brief
    Variant with integer selector beginning base element.

@ingroup elems

@sa VariantWithUnsignedIntegerSelectorBeginningElement
@sa VariantWithSignedIntegerSelectorBeginningElement
*/
template <typename VariantTypeT, typename SelectorValueT, Element::Kind KindV>
class VariantWithIntegerSelectorBeginningElement :
    public VariantBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariantWithIntegerSelectorBeginningElement() :
        VariantBeginningElement {KindV}
    {
    }

public:
    /// Variant type.
    const VariantTypeT& type() const noexcept
    {
        return *_dt;
    }

    /// Value of the variant selector.
    SelectorValueT selectorValue() const noexcept
    {
        return _selVal;
    }

    /// Selected option of the variant type.
    const typename VariantTypeT::Option& typeOption() const noexcept
    {
        return *_opt;
    }

private:
    const VariantTypeT *_dt;
    SelectorValueT _selVal;
    const typename VariantTypeT::Option *_opt;
};

/*!
@brief
    Variant with unsigned integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream variant with an
unsigned integer selector.

The next element is the selected element of this variant. Expect an
EndElement after this next element at the same level.

@sa EndElement
*/
class VariantWithUnsignedIntegerSelectorBeginningElement final :
    public VariantWithIntegerSelectorBeginningElement<VariantWithUnsignedIntegerSelectorType, unsigned long long,
                                                      Element::Kind::VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithUnsignedIntegerSelectorBeginningElement()
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variant with signed integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream variant with a
signed integer selector.

The next element is the selected element of this variant. Expect an
EndElement after this next element at the same level.

@sa EndElement
*/
class VariantWithSignedIntegerSelectorBeginningElement final :
    public VariantWithIntegerSelectorBeginningElement<VariantWithSignedIntegerSelectorType, long long,
                                                      Element::Kind::VARIANT_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithSignedIntegerSelectorBeginningElement()
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Common optional beginning element.

@ingroup elems

@sa OptionalWithBooleanSelectorBeginningElement
@sa OptionalWithUnsignedIntegerSelectorBeginningElement
@sa OptionalWithSignedIntegerSelectorBeginningElement
@sa EndElement
*/
class OptionalBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    OptionalBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Optional type.
    const OptionalType& type() const noexcept
    {
        return *_dt;
    }

    /// Whether or not this optional is enabled (contains data).
    bool isEnabled() const noexcept
    {
        return _isEnabled;
    }

protected:
    const OptionalType *_dt;

private:
    bool _isEnabled;
};

/*!
@brief
    Optional with boolean selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream optional with a
boolean selector.

The next element, if the isEnabled() returns \c true, is the contained
element of this optional. Expect an EndElement after this at the same
level.

@sa EndElement
*/
class OptionalWithBooleanSelectorBeginningElement final :
    public OptionalBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithBooleanSelectorBeginningElement() :
        OptionalBeginningElement {Element::Kind::OPTIONAL_WITH_BOOLEAN_SELECTOR_BEGINNING}
    {
    }

public:
    /// Optional type.
    const OptionalWithBooleanSelectorType& type() const noexcept
    {
        return static_cast<const OptionalWithBooleanSelectorType&>(*_dt);
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Optional with integer selector beginning base element.

@ingroup elems

@sa OptionalWithUnsignedIntegerSelectorBeginningElement
@sa OptionalWithSignedIntegerSelectorBeginningElement
*/
template <typename OptionalTypeT, typename SelectorValueT, Element::Kind KindV>
class OptionalWithIntegerSelectorBeginningElement :
    public OptionalBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit OptionalWithIntegerSelectorBeginningElement() :
        OptionalBeginningElement {KindV}
    {
    }

public:
    /// Optional type.
    const OptionalTypeT& type() const noexcept
    {
        return static_cast<const OptionalTypeT&>(*_dt);
    }

    /// Value of the optional selector.
    SelectorValueT selectorValue() const noexcept
    {
        return _selVal;
    }

private:
    SelectorValueT _selVal;
};

/*!
@brief
    Optional with unsigned integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream optional with an
unsigned integer selector.

The next element, if the isEnabled() returns \c true, is the contained
element of this optional. Expect an EndElement after this at the same
level.

@sa EndElement
*/
class OptionalWithUnsignedIntegerSelectorBeginningElement final :
    public OptionalWithIntegerSelectorBeginningElement<OptionalWithUnsignedIntegerSelectorType, unsigned long long,
                                                       Element::Kind::OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithUnsignedIntegerSelectorBeginningElement()
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Optional with signed integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream optional with a
signed integer selector.

The next element, if the isEnabled() returns \c true, is the contained
element of this optional. Expect an EndElement after this at the same
level.

@sa EndElement
*/
class OptionalWithSignedIntegerSelectorBeginningElement final :
    public OptionalWithIntegerSelectorBeginningElement<OptionalWithSignedIntegerSelectorType, long long,
                                                       Element::Kind::OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithSignedIntegerSelectorBeginningElement()
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_ELEM_HPP
