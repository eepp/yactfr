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
#include "metadata/fl-enum-type.hpp"
#include "metadata/static-text-array-type.hpp"
#include "metadata/dyn-text-array-type.hpp"
#include "metadata/var-type.hpp"
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

        /// FixedLengthSignedIntegerElement
        FIXED_LENGTH_SIGNED_INTEGER,

        /// FixedLengthUnsignedIntegerElement
        FIXED_LENGTH_UNSIGNED_INTEGER,

        /// FixedLengthFloatingPointNumberElement
        FIXED_LENGTH_FLOATING_POINT_NUMBER,

        /// FixedLengthSignedEnumerationElement
        FIXED_LENGTH_SIGNED_ENUMERATION,

        /// FixedLengthUnsignedEnumerationElement
        FIXED_LENGTH_UNFIXED_LENGTH_SIGNED_ENUMERATION,

        /// NullTerminatedStringBeginningElement
        NULL_TERMINATED_STRING_BEGINNING,

        /// SubstringElement
        SUBSTRING,

        /// StructureBeginningElement
        STRUCTURE_BEGINNING,

        /// StaticArrayBeginningElement
        STATIC_ARRAY_BEGINNING,

        /// StaticTextArrayBeginningElement
        STATIC_TEXT_ARRAY_BEGINNING,

        /// DynamicArrayBeginningElement
        DYNAMIC_ARRAY_BEGINNING,

        /// DynamicTextArrayBeginningElement
        DYNAMIC_TEXT_ARRAY_BEGINNING,

        /// VariantWithSignedSelectorBeginningElement
        VARIANT_WITH_SIGNED_SELECTOR_BEGINNING,

        /// VariantWithUnsignedSelectorBeginningElement
        VARIANT_WITH_UNSIGNED_SELECTOR_BEGINNING,
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

This element contains the decoded trace type UUID as well as the expected
trace type UUID.

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
        Numeric origin index of the current packet
        within its <em>data stream</em> (\em not within its element
        sequence).

    @note
        This is sometimes called <em>packet sequence number</em> in the
        specification terminology, although this term would be confusing
        in yactfr's scope since an ElementSequence object can "contain"
        packets from different data streams.
    */
    const boost::optional<Index>& originIndex() const noexcept
    {
        return _originIndex;
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
        _originIndex = boost::none;
        _expectedTotalLen = boost::none;
        _expectedContentLen = boost::none;
        _endDefClkVal = boost::none;
    }

private:
    boost::optional<Index> _originIndex;
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
    Fixed-length signed integer element.

@ingroup elems
*/
class FixedLengthSignedIntegerElement :
    public Element,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthSignedIntegerElement(const Kind kind) :
        Element {kind}
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
        return *_dt;
    }

    /// Integral value.
    long long value() const noexcept
    {
        return _val;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const FixedLengthSignedIntegerType *_dt;
    long long _val;
};

/*!
@brief
    Fixed-length unsigned integer element.

@ingroup elems
*/
class FixedLengthUnsignedIntegerElement :
    public Element,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthUnsignedIntegerElement(const Kind kind) :
        Element {kind}
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
        return *_dt;
    }

    /// Integral value.
    unsigned long long value() const noexcept
    {
        return _val;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    const FixedLengthUnsignedIntegerType *_dt;
    unsigned long long _val;
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
    const SignedFixedLengthEnumerationType& type() const noexcept
    {
        return *static_cast<const SignedFixedLengthEnumerationType *>(_dt);
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
        FixedLengthUnsignedIntegerElement {Kind::FIXED_LENGTH_UNFIXED_LENGTH_SIGNED_ENUMERATION}
    {
    }

public:
    /// Fixed-length unsigned enumeration type.
    const FixedLengthUnsignedEnumerationType& type() const noexcept
    {
        return *static_cast<const FixedLengthUnsignedEnumerationType *>(_dt);
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
    public Element,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthFloatingPointNumberElement() :
        Element {Kind::FIXED_LENGTH_FLOATING_POINT_NUMBER}
    {
    }

public:
    /// Fixed-length floating point number type.
    const FixedLengthFloatingPointNumberType& type() const noexcept
    {
        return *_dt;
    }

    /// Real value.
    double value() const noexcept
    {
        return _val;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const FixedLengthFloatingPointNumberType *_dt;
    double _val;
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

  <dt>Data stream static text array</dt>
  <dd>
    Between StaticTextArrayBeginningElement and EndElement elements.
  </dd>

  <dt>Data stream dynamic text array</dt>
  <dd>
    Between DynamicTextArrayBeginningElement and EndElement elements.
  </dd>
</dl>

begin() points to the first character of the substring and end() points
to the character \em after the last character of the substring. Use
length() to compute the length of the substring.

Note that the substring can contain <em>zero or more</em> null bytes. If
there's a null byte between begin() and end(), the string finishes at
this point, but for a text array, there can be other non-null bytes
before end() which are still part of the data stream.
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
    Static array beginning element.

@ingroup elems

This element indicates the beginning of a data stream static array.

The next elements until the next EndElement at the same level are
all part of this static array.

@sa EndElement
*/
class StaticArrayBeginningElement :
    public ArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    StaticArrayBeginningElement(const Kind kind) :
        ArrayBeginningElement {kind}
    {
    }

private:
    explicit StaticArrayBeginningElement() :
        StaticArrayBeginningElement {Kind::STATIC_ARRAY_BEGINNING}
    {
    }

public:
    /// Static array type.
    const StaticArrayType& type() const noexcept
    {
        return _dt->asStaticArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Static text array beginning element.

@ingroup elems

This element indicates the beginning of a data stream static text
array.

The next SubstringElement elements before the next EndElement are
consecutive substrings of this beginning static text array.

@sa SubstringElement
@sa EndElement
*/
class StaticTextArrayBeginningElement final :
    public StaticArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticTextArrayBeginningElement() :
        StaticArrayBeginningElement {Kind::STATIC_TEXT_ARRAY_BEGINNING}
    {
    }

public:
    /// Static text array type.
    const StaticTextArrayType& type() const noexcept
    {
        return _dt->asStaticTextArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic array beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic array.

The next elements until the next EndElement at the same level are all
part of this dynamic array.

@sa EndElement
*/
class DynamicArrayBeginningElement :
    public ArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    DynamicArrayBeginningElement(const Kind kind) :
        ArrayBeginningElement {kind}
    {
    }

private:
    explicit DynamicArrayBeginningElement() :
        DynamicArrayBeginningElement {Kind::DYNAMIC_ARRAY_BEGINNING}
    {
    }

public:
    /// Dynamic array type.
    const DynamicArrayType& type() const noexcept
    {
        return _dt->asDynamicArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic text array beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic text
array.

The next SubstringElement elements before the next EndElement are
consecutive substrings of this beginning dynamic text array.

@sa SubstringElement
@sa EndElement
*/
class DynamicTextArrayBeginningElement final :
    public DynamicArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicTextArrayBeginningElement() :
        DynamicArrayBeginningElement {Kind::DYNAMIC_TEXT_ARRAY_BEGINNING}
    {
    }

public:
    /// Dynamic text array type.
    const DynamicTextArrayType& type() const noexcept
    {
        return _dt->asDynamicTextArrayType();
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

@sa VariantWithUnsignedSelectorBeginningElement
@sa VariantWithSignedSelectorBeginningElement
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
    Variant with selector beginning base element.

@ingroup elems

@sa VariantWithUnsignedSelectorBeginningElement
@sa VariantWithSignedSelectorBeginningElement
*/
template <typename VariantTypeT, typename SelectorValueT, Element::Kind KindV>
class VariantWithSelectorBeginningElement :
    public VariantBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariantWithSelectorBeginningElement() :
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
    Variant with unsigned selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream variant with a
unsigned selector.

The next element is the selected element of this variant.
Expect an EndElement after this next element at the same level.

@sa EndElement
*/
class VariantWithUnsignedSelectorBeginningElement final :
    public VariantWithSelectorBeginningElement<VariantWithUnsignedSelectorType, unsigned long long,
                                               Element::Kind::VARIANT_WITH_UNSIGNED_SELECTOR_BEGINNING>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithUnsignedSelectorBeginningElement()
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
    Variant with signed selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream variant with a
signed selector.

The next element is the selected element of this variant. Expect an
EndElement after this next element at the same level.

@sa EndElement
*/
class VariantWithSignedSelectorBeginningElement final :
    public VariantWithSelectorBeginningElement<VariantWithSignedSelectorType, long long,
                                               Element::Kind::VARIANT_WITH_SIGNED_SELECTOR_BEGINNING>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithSignedSelectorBeginningElement()
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
