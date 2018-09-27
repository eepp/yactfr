/*
 * Procedure and instructions.
 *
 * Here are the possible instructions for the yactfr abstract VM. It's a
 * very specialized, not-general-purpose-at-all VM, but it's still a VM.
 * No bytecode is involved here: the VM deals with a sequence of
 * procedure instruction objects, some of them also containing a
 * subprocedure, and so on.
 *
 * Some definitions:
 *
 * Procedure:
 *     A sequence of procedure instructions.
 *
 * Subprocedure:
 *     A procedure contained in a procedure instruction.
 *
 * Procedure instruction:
 *     An instruction for the yactfr VM, possibly containing one or
 *     more subprocedures.
 *
 * The top-level procedure is a PacketProc. A PacketProc object contains
 * all the instructions to apply for a whole packet. At the beginning
 * of a packet, execute:
 *
 * * The packet procedure's preamble procedure.
 *
 * A DataStreamTypePacketProc object contains the instructions to
 * execute after the packet procedure's preamble procedure for a
 * specific data stream type. To execute a data stream type packet
 * procedure:
 *
 * 1. Execute the per-packet preamble procedure.
 * 2. Until the end of the packet, repeat:
 *   a) Execute the per-event record type preamble procedure.
 *   b) Depending on the chosen event record type, execute the
 *      corresponding event record type procedure
 *      (EventRecordTypeProc).
 *
 * An EventRecordTypeProc object contains a single procedure, that is,
 * the instructions to execute after the per-event record type preamble
 * procedure of its parent DataStreamTypePacketProc.
 *
 * Details such as how to choose the current data stream and event
 * record types, and how to determine the end of the packet, are left to
 * the implementation of the VM.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms of the
 * MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_PROC_HPP
#define _YACTFR_PROC_HPP

#include <cstdlib>
#include <cassert>
#include <sstream>
#include <list>
#include <vector>
#include <functional>
#include <type_traits>
#include <boost/optional/optional.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/data-type.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/string-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/dynamic-array-type.hpp>
#include <yactfr/metadata/dynamic-text-array-type.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/metadata/clock-type.hpp>
#include <yactfr/metadata/event-record-type.hpp>
#include <yactfr/metadata/data-stream-type.hpp>
#include <yactfr/metadata/trace-type.hpp>

#include "utils.hpp"

namespace yactfr {
namespace internal {

class Instr;
class InstrReadData;
class InstrReadBitArray;
class InstrReadSignedInt;
class InstrReadUnsignedInt;
class InstrReadFloat;
class InstrReadSignedEnum;
class InstrReadUnsignedEnum;
class InstrReadString;
class InstrBeginReadScope;
class InstrEndReadScope;
class InstrBeginReadStruct;
class InstrBeginReadStaticArray;
class InstrBeginReadStaticTextArray;
class InstrBeginReadStaticUuidArray;
class InstrBeginReadDynamicArray;
class InstrBeginReadDynamicTextArray;
class InstrBeginReadVariantUnknownTag;
class InstrBeginReadVariantSignedTag;
class InstrBeginReadVariantUnsignedTag;
class InstrEndReadCompound;
class InstrUpdateClockValue;
class InstrSetPacketEndClockValue;
class InstrSaveValue;
class InstrSetCurrentId;
class InstrSetDataStreamType;
class InstrSetEventRecordType;
class InstrSetDataStreamId;
class InstrSetPacketOriginIndex;
class InstrSetPacketTotalSize;
class InstrSetPacketContentSize;
class InstrSetPacketMagicNumber;
class InstrEndPacketPreambleProc;
class InstrEndDstPacketPreambleProc;
class InstrEndDstErtPreambleProc;
class InstrEndErtProc;
class InstrDecrRemainingElements;

/*
 * A classic abstract visitor class for procedure instructions.
 *
 * Used by PacketProcBuilder, NOT by the VM.
 */
class InstrVisitor
{
protected:
    InstrVisitor();

public:
    virtual ~InstrVisitor();

    virtual void visit(InstrReadSignedInt& instr)
    {
    }

    virtual void visit(InstrReadUnsignedInt& instr)
    {
    }

    virtual void visit(InstrReadFloat& instr)
    {
    }

    virtual void visit(InstrReadSignedEnum& instr)
    {
    }

    virtual void visit(InstrReadUnsignedEnum& instr)
    {
    }

    virtual void visit(InstrReadString& instr)
    {
    }

    virtual void visit(InstrBeginReadScope& instr)
    {
    }

    virtual void visit(InstrEndReadScope& instr)
    {
    }

    virtual void visit(InstrBeginReadStruct& instr)
    {
    }

    virtual void visit(InstrBeginReadStaticArray& instr)
    {
    }

    virtual void visit(InstrBeginReadStaticUuidArray& instr)
    {
    }

    virtual void visit(InstrBeginReadStaticTextArray& instr)
    {
    }

    virtual void visit(InstrBeginReadDynamicArray& instr)
    {
    }

    virtual void visit(InstrBeginReadDynamicTextArray& instr)
    {
    }

    virtual void visit(InstrBeginReadVariantUnknownTag& instr)
    {
    }

    virtual void visit(InstrBeginReadVariantSignedTag& instr)
    {
    }

    virtual void visit(InstrBeginReadVariantUnsignedTag& instr)
    {
    }

    virtual void visit(InstrEndReadCompound& instr)
    {
    }

    virtual void visit(InstrUpdateClockValue& instr)
    {
    }

    virtual void visit(InstrSetCurrentId& instr)
    {
    }

    virtual void visit(InstrSetDataStreamType& instr)
    {
    }

    virtual void visit(InstrSetEventRecordType& instr)
    {
    }

    virtual void visit(InstrSetDataStreamId& instr)
    {
    }

    virtual void visit(InstrSetPacketOriginIndex& instr)
    {
    }

    virtual void visit(InstrSetPacketTotalSize& instr)
    {
    }

    virtual void visit(InstrSetPacketContentSize& instr)
    {
    }

    virtual void visit(InstrSaveValue& instr)
    {
    }

    virtual void visit(InstrSetPacketEndClockValue& instr)
    {
    }

    virtual void visit(InstrSetPacketMagicNumber& instr)
    {
    }

    virtual void visit(InstrEndPacketPreambleProc& instr)
    {
    }

    virtual void visit(InstrEndDstPacketPreambleProc& instr)
    {
    }

    virtual void visit(InstrEndDstErtPreambleProc& instr)
    {
    }

    virtual void visit(InstrEndErtProc& instr)
    {
    }

    virtual void visit(InstrDecrRemainingElements& instr)
    {
    }
};

/*
 * A procedure, that is, a sequence of instructions.
 *
 * The procedure is first built as a list of shared pointers because
 * the build process needs to insert and replace instructions and it's
 * easier with a linked list.
 *
 * Then, when the build is complete, we call buildRawProcFromShared()
 * which builds a vector of raw instruction object (weak) pointers from
 * the list of shared pointers. The list must remain alive because it
 * keeps the instructions alive. Going from raw pointer to raw pointer
 * in a vector seems more efficient than going from shared pointer to
 * shared pointer in a linked list. I did not measure the difference yet
 * however.
 *
 * Instructions are shared because sometimes they are reused, for
 * example multiple range procedures of a InstrBeginReadVariantSignedTag
 * or InstrBeginReadVariantUnsignedTag instruction can refer to the
 * exact same instructions.
 */
class Proc final
{
public:
    using RawProc = std::vector<const Instr*>;
    using SharedProc = std::list<std::shared_ptr<Instr>>;
    using RawIterator = RawProc::const_iterator;
    using SharedIterator = SharedProc::iterator;

public:
    void buildRawProcFromShared();
    std::string toString(Size indent = 0) const;
    void pushBack(std::shared_ptr<Instr> instr);
    void insert(SharedIterator iter, std::shared_ptr<Instr> instr);

    std::list<std::shared_ptr<Instr>>& sharedProc() noexcept
    {
        return _sharedProc;
    }

    const std::list<std::shared_ptr<Instr>>& sharedProc() const noexcept
    {
        return _sharedProc;
    }

    const std::vector<const Instr*>& rawProc() const noexcept
    {
        return _rawProc;
    }

    SharedIterator begin()
    {
        return std::begin(_sharedProc);
    }

    SharedIterator end()
    {
        return std::end(_sharedProc);
    }

private:
    std::vector<const Instr*> _rawProc;
    std::list<std::shared_ptr<Instr>> _sharedProc;
};

static inline std::string _strName(const char *name)
{
    std::string rName;

    rName = "[\033[1m\033[36m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

static inline std::string _strEndName(const char *name)
{
    std::string rName;

    rName = "[\033[1m\033[32m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

static inline std::string _strSpecName(const char *name)
{
    std::string rName;

    rName = "[\033[1m\033[33m";
    rName += name;
    rName += "\033[0m]";
    return rName;
}

static inline std::string _strProp(const char *prop)
{
    std::string rProp;

    rProp = "\033[1m";
    rProp += prop;
    rProp += "\033[0m=";
    return rProp;
}

static inline std::string _strTopName(const char *name)
{
    std::string rName;

    rName = "{\033[1m\033[35m";
    rName += name;
    rName += "\033[0m}";
    return rName;
}

static inline std::string _strScopeName(const char *name)
{
    std::string rName;

    rName = "|\033[1m\033[33m";
    rName += name;
    rName += "\033[0m|";
    return rName;
}

// A pair of procedure and instruction iterator.
struct InstrLocation
{
    Proc::SharedProc *proc = nullptr;
    Proc::SharedProc::iterator it;
};

// Procedure instruction abstract class.
class Instr
{
public:
    enum class Kind
    {
        UNSET,
        READ_SIGNED_INT_LE,
        READ_SIGNED_INT_BE,
        READ_SIGNED_INT_A8,
        READ_SIGNED_INT_A16_LE,
        READ_SIGNED_INT_A32_LE,
        READ_SIGNED_INT_A64_LE,
        READ_SIGNED_INT_A16_BE,
        READ_SIGNED_INT_A32_BE,
        READ_SIGNED_INT_A64_BE,
        READ_UNSIGNED_INT_LE,
        READ_UNSIGNED_INT_BE,
        READ_UNSIGNED_INT_A8,
        READ_UNSIGNED_INT_A16_LE,
        READ_UNSIGNED_INT_A32_LE,
        READ_UNSIGNED_INT_A64_LE,
        READ_UNSIGNED_INT_A16_BE,
        READ_UNSIGNED_INT_A32_BE,
        READ_UNSIGNED_INT_A64_BE,
        READ_FLOAT_32_LE,
        READ_FLOAT_32_BE,
        READ_FLOAT_A32_LE,
        READ_FLOAT_A32_BE,
        READ_FLOAT_64_LE,
        READ_FLOAT_64_BE,
        READ_FLOAT_A64_LE,
        READ_FLOAT_A64_BE,
        READ_SIGNED_ENUM_LE,
        READ_SIGNED_ENUM_BE,
        READ_SIGNED_ENUM_A8,
        READ_SIGNED_ENUM_A16_LE,
        READ_SIGNED_ENUM_A32_LE,
        READ_SIGNED_ENUM_A64_LE,
        READ_SIGNED_ENUM_A16_BE,
        READ_SIGNED_ENUM_A32_BE,
        READ_SIGNED_ENUM_A64_BE,
        READ_UNSIGNED_ENUM_LE,
        READ_UNSIGNED_ENUM_BE,
        READ_UNSIGNED_ENUM_A8,
        READ_UNSIGNED_ENUM_A16_LE,
        READ_UNSIGNED_ENUM_A32_LE,
        READ_UNSIGNED_ENUM_A64_LE,
        READ_UNSIGNED_ENUM_A16_BE,
        READ_UNSIGNED_ENUM_A32_BE,
        READ_UNSIGNED_ENUM_A64_BE,
        READ_STRING,
        BEGIN_READ_SCOPE,
        END_READ_SCOPE,
        BEGIN_READ_STRUCT,
        END_READ_STRUCT,
        BEGIN_READ_STATIC_ARRAY,
        END_READ_STATIC_ARRAY,
        BEGIN_READ_STATIC_TEXT_ARRAY,
        END_READ_STATIC_TEXT_ARRAY,
        BEGIN_READ_STATIC_UUID_ARRAY,
        BEGIN_READ_DYNAMIC_ARRAY,
        END_READ_DYNAMIC_ARRAY,
        BEGIN_READ_DYNAMIC_TEXT_ARRAY,
        END_READ_DYNAMIC_TEXT_ARRAY,
        BEGIN_READ_VARIANT_SIGNED_TAG,
        BEGIN_READ_VARIANT_UNSIGNED_TAG,
        BEGIN_READ_VARIANT_UNKNOWN_TAG,
        END_READ_VARIANT,
        SAVE_VALUE,
        SET_PACKET_END_CLOCK_VALUE,
        UPDATE_CLOCK_VALUE,
        SET_CURRENT_ID,
        SET_DATA_STREAM_TYPE,
        SET_EVENT_RECORD_TYPE,
        SET_DATA_STREAM_ID,
        SET_PACKET_ORIGIN_INDEX,
        SET_PACKET_TOTAL_SIZE,
        SET_PACKET_CONTENT_SIZE,
        SET_PACKET_MAGIC_NUMBER,
        END_PACKET_PREAMBLE_PROC,
        END_DST_PACKET_PREAMBLE_PROC,
        END_DST_ERT_PREAMBLE_PROC,
        END_ERT_PROC,
        DECR_REMAINING_ELEMENTS,
    };

public:
    using SP = std::shared_ptr<Instr>;

protected:
    Instr();
    explicit Instr(Kind kind);

public:
    virtual ~Instr();
    virtual void accept(InstrVisitor& visitor) = 0;
    virtual void buildRawProcFromShared();

    // only used for debugging purposes
    std::string toString(Size indent = 0) const;

    Kind kind() const noexcept
    {
        assert(_kind != Kind::UNSET);
        return _kind;
    }

    /*
     * Please DO NOT FREAK OUT about the isX() methods belows. They are
     * only helpers which are used when building the procedures. The
     * yactfr VM uses kind() directly and a function table.
     */

    bool isReadData() const noexcept
    {
        return this->isReadInt() || this->isReadFloat() ||
               this->isReadString() || this->isBeginReadCompound() ||
               this->isBeginReadVariant();
    }

    bool isBeginReadScope() const noexcept
    {
        return _kind == Kind::BEGIN_READ_SCOPE;
    }

    bool isBeginReadCompound() const noexcept
    {
        return _kind == Kind::BEGIN_READ_STRUCT ||
               _kind == Kind::BEGIN_READ_STATIC_ARRAY ||
               _kind == Kind::BEGIN_READ_STATIC_UUID_ARRAY ||
               _kind == Kind::BEGIN_READ_STATIC_TEXT_ARRAY ||
               _kind == Kind::BEGIN_READ_DYNAMIC_ARRAY ||
               _kind == Kind::BEGIN_READ_DYNAMIC_TEXT_ARRAY;
    }

    bool isReadInt() const noexcept
    {
        return this->isReadSignedInt() || this->isReadUnsignedInt();
    }

    bool isReadSignedInt() const noexcept
    {
        return _kind == Kind::READ_SIGNED_INT_LE ||
               _kind == Kind::READ_SIGNED_INT_BE ||
               _kind == Kind::READ_SIGNED_INT_A8 ||
               _kind == Kind::READ_SIGNED_INT_A16_LE ||
               _kind == Kind::READ_SIGNED_INT_A32_LE ||
               _kind == Kind::READ_SIGNED_INT_A64_LE ||
               _kind == Kind::READ_SIGNED_INT_A16_BE ||
               _kind == Kind::READ_SIGNED_INT_A32_BE ||
               _kind == Kind::READ_SIGNED_INT_A64_BE ||
               this->isReadSignedEnum();
    }

    bool isReadUnsignedInt() const noexcept
    {
        return _kind == Kind::READ_UNSIGNED_INT_LE ||
               _kind == Kind::READ_UNSIGNED_INT_BE ||
               _kind == Kind::READ_UNSIGNED_INT_A8 ||
               _kind == Kind::READ_UNSIGNED_INT_A16_LE ||
               _kind == Kind::READ_UNSIGNED_INT_A32_LE ||
               _kind == Kind::READ_UNSIGNED_INT_A64_LE ||
               _kind == Kind::READ_UNSIGNED_INT_A16_BE ||
               _kind == Kind::READ_UNSIGNED_INT_A32_BE ||
               _kind == Kind::READ_UNSIGNED_INT_A64_BE ||
               this->isReadUnsignedEnum();
    }

    bool isReadFloat() const noexcept
    {
        return _kind == Kind::READ_FLOAT_32_LE ||
               _kind == Kind::READ_FLOAT_32_BE ||
               _kind == Kind::READ_FLOAT_A32_LE ||
               _kind == Kind::READ_FLOAT_A32_BE ||
               _kind == Kind::READ_FLOAT_64_LE ||
               _kind == Kind::READ_FLOAT_64_BE ||
               _kind == Kind::READ_FLOAT_A64_LE ||
               _kind == Kind::READ_FLOAT_A64_BE;
    }

    bool isReadEnum() const noexcept
    {
        return this->isReadSignedEnum() || this->isReadUnsignedEnum();
    }

    bool isReadSignedEnum() const noexcept
    {
        return _kind == Kind::READ_SIGNED_ENUM_LE ||
               _kind == Kind::READ_SIGNED_ENUM_BE ||
               _kind == Kind::READ_SIGNED_ENUM_A8 ||
               _kind == Kind::READ_SIGNED_ENUM_A16_LE ||
               _kind == Kind::READ_SIGNED_ENUM_A32_LE ||
               _kind == Kind::READ_SIGNED_ENUM_A64_LE ||
               _kind == Kind::READ_SIGNED_ENUM_A16_BE ||
               _kind == Kind::READ_SIGNED_ENUM_A32_BE ||
               _kind == Kind::READ_SIGNED_ENUM_A64_BE;
    }

    bool isReadUnsignedEnum() const noexcept
    {

        return _kind == Kind::READ_UNSIGNED_ENUM_LE ||
               _kind == Kind::READ_UNSIGNED_ENUM_BE ||
               _kind == Kind::READ_UNSIGNED_ENUM_A8 ||
               _kind == Kind::READ_UNSIGNED_ENUM_A16_LE ||
               _kind == Kind::READ_UNSIGNED_ENUM_A32_LE ||
               _kind == Kind::READ_UNSIGNED_ENUM_A64_LE ||
               _kind == Kind::READ_UNSIGNED_ENUM_A16_BE ||
               _kind == Kind::READ_UNSIGNED_ENUM_A32_BE ||
               _kind == Kind::READ_UNSIGNED_ENUM_A64_BE;
    }

    bool isReadString() const noexcept
    {
        return _kind == Kind::READ_STRING;
    }

    bool isBeginReadStaticArray() const noexcept
    {
        return _kind == Kind::BEGIN_READ_STATIC_ARRAY ||
               _kind == Kind::BEGIN_READ_STATIC_UUID_ARRAY ||
               _kind == Kind::BEGIN_READ_STATIC_TEXT_ARRAY;
    }

    bool isBeginReadStaticTextArray() const noexcept
    {
        return _kind == Kind::BEGIN_READ_STATIC_TEXT_ARRAY;
    }

    bool isBeginReadStaticUuidArray() const noexcept
    {
        return _kind == Kind::BEGIN_READ_STATIC_UUID_ARRAY;
    }

    bool isBeginReadDynamicArray() const noexcept
    {
        return _kind == Kind::BEGIN_READ_DYNAMIC_ARRAY ||
               _kind == Kind::BEGIN_READ_DYNAMIC_TEXT_ARRAY;
    }

    bool isBeginReadDynamicTextArray() const noexcept
    {
        return _kind == Kind::BEGIN_READ_DYNAMIC_TEXT_ARRAY;
    }

    bool isBeginReadStruct() const noexcept
    {
        return _kind == Kind::BEGIN_READ_STRUCT;
    }

    bool isBeginReadVariant() const noexcept
    {
        return _kind == Kind::BEGIN_READ_VARIANT_UNKNOWN_TAG ||
               _kind == Kind::BEGIN_READ_VARIANT_SIGNED_TAG ||
               _kind == Kind::BEGIN_READ_VARIANT_UNSIGNED_TAG;
    }

    bool isBeginReadVariantSignedTag() const noexcept
    {
        return _kind == Kind::BEGIN_READ_VARIANT_SIGNED_TAG;
    }

    bool isBeginReadVariantUnsignedTag() const noexcept
    {
        return _kind == Kind::BEGIN_READ_VARIANT_UNSIGNED_TAG;
    }

    bool isBeginReadUnknownVariant() const noexcept
    {
        return _kind == Kind::BEGIN_READ_VARIANT_UNKNOWN_TAG;
    }

    bool isEndReadCompound() const noexcept
    {
        return _kind == Kind::END_READ_STRUCT ||
               _kind == Kind::END_READ_STATIC_ARRAY ||
               _kind == Kind::END_READ_STATIC_TEXT_ARRAY ||
               _kind == Kind::END_READ_DYNAMIC_ARRAY ||
               _kind == Kind::END_READ_DYNAMIC_TEXT_ARRAY ||
               _kind == Kind::END_READ_VARIANT;
    }

    bool isEndProc() const noexcept
    {
        return _kind == Kind::END_PACKET_PREAMBLE_PROC ||
               _kind == Kind::END_DST_PACKET_PREAMBLE_PROC ||
               _kind == Kind::END_DST_ERT_PREAMBLE_PROC ||
               _kind == Kind::END_ERT_PROC;
    }

protected:
    void _setKind(const Kind kind) noexcept
    {
        _kind = kind;
    }

private:
    virtual std::string _toString(Size indent = 0) const;

private:
    Kind _kind;
};

// "Read (something)" procedure instruction abstract class.
class InstrReadData :
    public Instr
{
public:
    /*
     * `fieldName`, `fieldDispName`, and `type` point to members of
     * their containing named data type object (part of the trace type
     * hierarchy). `fieldName` and `fieldDisplayName` can be null if
     * this is the scope's root read instruction.
     */
    explicit InstrReadData(const std::string *fieldName,
                           const std::string *fieldDisplayName,
                           const DataType *type);
    virtual InstrLocation findInstr(std::vector<std::string>::const_iterator begin,
                                    std::vector<std::string>::const_iterator end);

    const DataType *type() const noexcept
    {
        return _type;
    }

    const std::string *fieldName() const noexcept
    {
        return _fieldName;
    }

    const std::string *fieldDisplayName() const noexcept
    {
        return _fieldDisplayName;
    }

    unsigned int alignment() const noexcept
    {
        return _alignment;
    }

protected:
    std::string _commonToString() const;

private:
    const std::string *_fieldName;
    const std::string *_fieldDisplayName;
    const DataType *_type;
    const unsigned int _alignment;
};

/*
 * "Save value" procedure instruction.
 *
 * This instruction asks the VM to save the last decoded integer value
 * to a given position (index) in its saved value vector so that it can
 * be used later (for the length of a dynamic array or for the tag of a
 * variant).
 */
class InstrSaveValue :
    public Instr
{
public:
    explicit InstrSaveValue(Index pos);

    Index pos() const noexcept
    {
        return _pos;
    }

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    const Index _pos;
};

/*
 * "Save packet end clock value" procedure instruction.
 *
 * This instruction asks the VM that the last decoded integer value is
 * the packet end clock value. Use `index()` to get the index of the
 * clock type which represents the clock of which the value is saved.
 */
class InstrSetPacketEndClockValue :
    public Instr
{
public:
    explicit InstrSetPacketEndClockValue(const ClockType& clockType,
                                         Index index);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const ClockType& clockType() const noexcept
    {
        return *_clockType;
    }

    Index index() const noexcept
    {
        return _index;
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    const ClockType *_clockType;
    const Index _index;
};

// "Read bit array" procedure.
class InstrReadBitArray :
    public InstrReadData
{
protected:
    explicit InstrReadBitArray(const std::string *fieldName,
                               const std::string *fieldDisplayName,
                               const DataType *type);

public:
    unsigned int size() const noexcept
    {
        return _size;
    }

    ByteOrder byteOrder() const noexcept
    {
        return _byteOrder;
    }

protected:
    std::string _commonToString() const;

private:
    std::string _toString(const Size indent = 0) const override;

private:
    const unsigned int _size;
    const ByteOrder _byteOrder;
};

// "Read integer" procedure instruction abstract class.
class InstrReadIntBase :
    public InstrReadBitArray
{
public:
    explicit InstrReadIntBase(const std::string *fieldName,
                              const std::string *fieldDisplayName,
                              const DataType *type);

    const IntType& intType() const noexcept
    {
        return static_cast<const IntType&>(*this->type());
    }
};

// "Read signed integer" procedure instruction.
class InstrReadSignedInt :
    public InstrReadIntBase
{
public:
    explicit InstrReadSignedInt(const std::string *fieldName,
                                const std::string *fieldDisplayName,
                                const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const SignedIntType& signedIntType() const noexcept
    {
        return static_cast<const SignedIntType&>(*this->type());
    }

private:
    std::string _toString(Size indent = 0) const override;
};

// "Read unsigned integer" procedure instruction.
class InstrReadUnsignedInt :
    public InstrReadIntBase
{
public:
    explicit InstrReadUnsignedInt(const std::string *fieldName,
                                  const std::string *fieldDisplayName,
                                  const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const UnsignedIntType& unsignedIntType() const noexcept
    {
        return static_cast<const UnsignedIntType&>(*this->type());
    }

private:
    std::string _toString(Size indent = 0) const override;
};

// "Read floating point number" procedure instruction.
class InstrReadFloat :
    public InstrReadBitArray
{
public:
    explicit InstrReadFloat(const std::string *fieldName,
                            const std::string *fieldDisplayName,
                            const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FloatType& floatType() const noexcept
    {
        return static_cast<const FloatType&>(*this->type());
    }

private:
    std::string _toString(Size indent = 0) const override;
};

// "Read signed enumeration" procedure instruction.
class InstrReadSignedEnum :
    public InstrReadSignedInt
{
public:
    explicit InstrReadSignedEnum(const std::string *fieldName,
                                 const std::string *fieldDisplayName,
                                 const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const SignedEnumType& signedEnumType() const noexcept
    {
        return static_cast<const SignedEnumType&>(*this->type());
    }

private:
    std::string _toString(Size indent = 0) const override;
};

// "Read unsigned enumeration" procedure instruction.
class InstrReadUnsignedEnum :
    public InstrReadUnsignedInt
{
public:
    explicit InstrReadUnsignedEnum(const std::string *fieldName,
                                   const std::string *fieldDisplayName,
                                   const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const UnsignedEnumType& unsignedEnumType() const noexcept
    {
        return static_cast<const UnsignedEnumType&>(*this->type());
    }

private:
    std::string _toString(Size indent = 0) const override;
};

// "Read null-terminated string" procedure instruction.
class InstrReadString :
    public InstrReadData
{
public:
    explicit InstrReadString(const std::string *fieldName,
                             const std::string *fieldDisplayName,
                             const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    unsigned int alignment() const noexcept
    {
        return _alignment;
    }

    const StringType& stringType() const noexcept
    {
        return static_cast<const StringType&>(*this->type());
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    const unsigned int _alignment;
};

/*
 * "Begin reading compound data" procedure instruction abstract class.
 *
 * This instruction contains a subprocedure to execute.
 */
class InstrBeginReadCompound :
    public InstrReadData
{
protected:
    explicit InstrBeginReadCompound(const std::string *fieldName,
                                    const std::string *fieldDisplayName,
                                    const DataType *type);

public:
    const Proc& proc() const noexcept
    {
        return _proc;
    }

    Proc& proc() noexcept
    {
        return _proc;
    }

    virtual Instr *findInstrByFieldName(const std::string& fieldName);
    void buildRawProcFromShared() override;

protected:
    std::string _procToString(const Size indent) const
    {
        return _proc.toString(indent);
    }

private:
    Proc _proc;
};

/*
 * "End reading compound data" procedure instruction.
 *
 * If this instruction's kind is END_READ_STRUCT, then the VM must stop
 * executing the current procedure and continue executing the parent
 * procedure. For all kinds, this instruction tells the VM to set a
 * StructEndElement as the current element.
 */
class InstrEndReadCompound :
    public InstrReadData
{
public:
    explicit InstrEndReadCompound(Kind kind,
                                  const std::string *fieldName,
                                  const std::string *fieldDisplayName,
                                  const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string _toString(Size indent = 0) const override;
};

// "Begin reading structure" procedure instruction.
class InstrBeginReadStruct :
    public InstrBeginReadCompound
{
public:
    explicit InstrBeginReadStruct(const std::string *fieldName,
                                  const std::string *fieldDisplayName,
                                  const DataType *type);
    InstrLocation findInstr(std::vector<std::string>::const_iterator begin,
                            std::vector<std::string>::const_iterator end) override;

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StructType& structType() const noexcept
    {
        return static_cast<const StructType&>(*this->type());
    }

private:
    std::string _toString(Size indent = 0) const override;
};

/*
 * "Begin reading scope" procedure instruction.
 *
 * This is the top-level instruction to start reading a whole scope
 * (packet header, packet context, event record payload, etc.).
 */
class InstrBeginReadScope :
    public Instr
{
public:
    explicit InstrBeginReadScope(Scope scope);
    void buildRawProcFromShared() override;
    InstrLocation findInstr(const FieldRef& fieldRef);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    Scope scope() const noexcept
    {
        return _scope;
    }

    const Proc& proc() const noexcept
    {
        return _proc;
    }

    Proc& proc() noexcept
    {
        return _proc;
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    const Scope _scope;
    Proc _proc;
};

/*
 * "End reading scope" procedure instruction.
 *
 * This asks the VM to stop executing the current procedure and continue
 * executing the parent procedure.
 */
class InstrEndReadScope :
    public Instr
{
public:
    explicit InstrEndReadScope(Scope scope);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    Scope scope() const noexcept
    {
        return _scope;
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    const Scope _scope;
};

/*
 * "Begin reading static array" procedure instruction.
 *
 * The VM must execute the subprocedure `length()` times.
 */
class InstrBeginReadStaticArray :
    public InstrBeginReadCompound
{
public:
    explicit InstrBeginReadStaticArray(const std::string *fieldName,
                                       const std::string *fieldDisplayName,
                                       const DataType *type);
    InstrLocation findInstr(std::vector<std::string>::const_iterator begin,
                            std::vector<std::string>::const_iterator end) override;
    Instr *findInstrByFieldName(const std::string& fieldName) override;

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StaticArrayType& staticArrayType() const noexcept
    {
        return static_cast<const StaticArrayType&>(*this->type());
    }

    Size length() const noexcept
    {
        return _length;
    }

protected:
    std::string _commonToString() const;

private:
    std::string _toString(Size indent = 0) const override;

private:
    const Size _length;
};

// "Begin reading static text array" procedure instruction.
class InstrBeginReadStaticTextArray :
    public InstrBeginReadStaticArray
{
public:
    explicit InstrBeginReadStaticTextArray(const std::string *fieldName,
                                           const std::string *fieldDisplayName,
                                           const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StaticTextArrayType& staticTextArrayType() const noexcept
    {
        return static_cast<const StaticTextArrayType&>(*this->type());
    }
};

/*
 * "Begin reading static UUID array" procedure instruction.
 *
 * This is a specialized instruction to read a packet header's UUID
 * field (16 bytes) and then validate the resulting UUID against the
 * expected one.
 */
class InstrBeginReadStaticUuidArray :
    public InstrBeginReadStaticArray
{
public:
    explicit InstrBeginReadStaticUuidArray(const std::string *fieldName,
                                           const std::string *fieldDisplayName,
                                           const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Begin reading dynamic array" procedure instruction.
 *
 * The VM must use `lengthPos()` to retrieve the saved value which
 * represents the dynamic array's length, and then execute the
 * subprocedure this number of times.
 */
class InstrBeginReadDynamicArray :
    public InstrBeginReadCompound
{
public:
    explicit InstrBeginReadDynamicArray(const std::string *fieldName,
                                        const std::string *fieldDisplayName,
                                        const DataType *type);
    InstrLocation findInstr(std::vector<std::string>::const_iterator begin,
                            std::vector<std::string>::const_iterator end) override;
    Instr *findInstrByFieldName(const std::string& fieldName) override;

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const DynamicArrayType& dynamicArrayType() const noexcept
    {
        return static_cast<const DynamicArrayType&>(*this->type());
    }

    const Index& lengthPos() const noexcept
    {
        return _lengthPos;
    }

    void lengthPos(const Index lengthPos) noexcept
    {
        _lengthPos = lengthPos;
    }

protected:
    std::string _commonToString() const;

private:
    std::string _toString(Size indent = 0) const override;

private:
    Index _lengthPos = Index {-1ULL};
};

// "Begin reading dynamic text array" procedure instruction.
class InstrBeginReadDynamicTextArray :
    public InstrBeginReadDynamicArray
{
public:
    explicit InstrBeginReadDynamicTextArray(const std::string *fieldName,
                                            const std::string *fieldDisplayName,
                                            const DataType *type);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const DynamicTextArrayType& dynamicTextArrayType() const noexcept
    {
        return static_cast<const DynamicTextArrayType&>(*this->type());
    }
};

/*
 * "Begin reading variant with unknown tag" (temporary) procedure
 * instruction.
 *
 * This is a temporary procedure instruction which needs to be replaced
 * with an InstrBeginReadVariantSignedTag or a
 * InstrBeginReadVariantUnsignedTag at procedure build time. In other
 * words, it should never exist once a complete PacketProc is built.
 *
 * It exists because, in the early stage of procedure build time, it's
 * easier to create the procedure for each individual variant type
 * option, and then, in another pass, check if the variant reading
 * instruction should have subprocedures for unsigned or signed ranges.
 * To do this we do not need to create new procedure instructions for
 * the options, we simply reuse the same because they are shared.
 */
class InstrBeginReadVariantUnknownTag :
    public InstrReadData
{
public:
    using Options = std::unordered_map<std::string, Proc>;

public:
    explicit InstrBeginReadVariantUnknownTag(const std::string *fieldName,
                                             const std::string *fieldDisplayName,
                                             const DataType *type);
    InstrLocation findInstr(std::vector<std::string>::const_iterator begin,
                            std::vector<std::string>::const_iterator end) override;

    const VariantType& variantType() const noexcept
    {
        return static_cast<const VariantType&>(*this->type());
    }

    const Options& options() const noexcept
    {
        return _options;
    }

    Options& options() noexcept
    {
        return _options;
    }

    const Index& tagPos() const noexcept
    {
        return _tagPos;
    }

    void tagPos(const Index tagPos) noexcept
    {
        _tagPos = tagPos;
    }

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    Options _options;
    Index _tagPos = Index {-1ULL};
};

/*
 * Range of a "read variant" procedure instruction.
 *
 * `ValueT` is the type of the lower and upper values of the range. Such
 * a range contains a subprocedure to execute when a variant's current
 * tag value is within the range.
 */
template <typename ValueT>
class InstrReadVariantRange
{
public:
    using Value = ValueT;

public:
    explicit InstrReadVariantRange() :
        _lower {0},
        _upper {0}
    {
    }

    explicit InstrReadVariantRange(const ValueT lower, const ValueT upper,
                                   const Proc& proc) :
        _lower {lower},
        _upper {upper},
        _proc {proc}
    {
    }

    void buildRawProcFromShared()
    {
        _proc.buildRawProcFromShared();
    }

    InstrReadVariantRange(const InstrReadVariantRange<ValueT>& range) noexcept :
        _lower {range._lower},
        _upper {range._upper},
        _proc {range._proc}
    {
    }

    InstrReadVariantRange<ValueT>& operator=(const InstrReadVariantRange<ValueT>& range) noexcept
    {
        _lower = range._lower;
        _upper = range._upper;
        _proc = range._proc;
        return *this;
    }

    bool contains(const ValueT value) const noexcept
    {
        return value >= _lower && value <= _upper;
    }

    ValueT lower() const noexcept
    {
        return _lower;
    }

    ValueT upper() const noexcept
    {
        return _upper;
    }

    const Proc& proc() const
    {
        return _proc;
    }

    std::string toString(const Size indent = 0) const
    {
        std::ostringstream ss;

        ss << utils::indent(indent);

        if (std::is_signed<ValueT>::value) {
            ss << "<variant range procedure (signed tag)>";
        } else {
            ss << "<variant range procedure (unsigned tag)>";
        }

        ss << " " << _strProp("lower") << _lower <<
              " " << _strProp("upper") << _upper << std::endl;
        ss << _proc.toString(indent + 1);
        return ss.str();
    }

    bool operator<(const InstrReadVariantRange<ValueT>& otherRange) const noexcept
    {
        if (this->lower() < otherRange.lower()) {
            return true;
        }

        if (otherRange.lower() < this->lower()) {
            return false;
        }

        if (this->upper() < otherRange.upper()) {
            return true;
        }

        if (otherRange.upper() < this->upper()) {
            return false;
        }

        return false;
    }

private:
    ValueT _lower,
           _upper;

    /*
     * Contained pointers are not owned by this object: they are owned
     * by the variant instruction object which contains the ranges.
     */
    Proc _proc;
};

using InstrReadVariantSignedRange = InstrReadVariantRange<long long>;
using InstrReadVariantUnsignedRange = InstrReadVariantRange<unsigned long long>;

/*
 * "Begin reading variant" procedure instruction template.
 *
 * The VM must use `tagPos()` to retrieve the saved value which
 * represents the variant's tag, find the corresponding range for this
 * tag value, and then execute the range's subprocedure.
 *
 * `EnumTypeT` is the enumeration type to use for the instruction's
 * ranges (`UnsignedEnumType` or `SignedEnumType`).
 */
template <typename EnumTypeT, Instr::Kind SelfKind>
class InstrBeginReadVariant :
    public InstrReadData
{
public:
    using Range = InstrReadVariantRange<typename EnumTypeT::Value>;
    using Ranges = std::vector<Range>;
    using Value = typename EnumTypeT::Value;
    using EnumType = EnumTypeT;

public:
    explicit InstrBeginReadVariant(const InstrBeginReadVariantUnknownTag& instrReadUnkVariant,
                                   const EnumTypeT& tagType) :
        InstrReadData {
            instrReadUnkVariant.fieldName(),
            instrReadUnkVariant.fieldDisplayName(),
            instrReadUnkVariant.type()
        },
        _tagPos {instrReadUnkVariant.tagPos()}
    {
        this->_setKind(SelfKind);
        this->_buildRangesFromOptions(instrReadUnkVariant, tagType);
    }

    void buildRawProcFromShared() override
    {
        for (auto& range : _ranges) {
            range.buildRawProcFromShared();
        }
    }

    const VariantType& variantType() const noexcept
    {
        return static_cast<const VariantType&>(*this->type());
    }

    const Ranges& ranges() const noexcept
    {
        return _ranges;
    }

    const Proc *findProc(const Value tag) const
    {
        for (auto& range : _ranges) {
            if (range.contains(tag)) {
                return &range.proc();
            }
        }

        return nullptr;
    }

    const Index& tagPos() const noexcept
    {
        return _tagPos;
    }

private:
    std::string _toString(const Size indent = 0) const override
    {
        std::ostringstream ss;

        ss << this->_commonToString() <<
              " " << _strProp("tag-pos") << _tagPos <<
              std::endl;

        for (const auto& range : _ranges) {
            ss << range.toString(indent + 1);
        }

        return ss.str();
    }

private:
    void _buildRangesFromOptions(const InstrBeginReadVariantUnknownTag& instrReadUnkVariant,
                                 const EnumType& tagType)
    {
        for (const auto& memberPair : tagType.members()) {
            auto& memberName = memberPair.first;
            auto& member = memberPair.second;

            if (!this->variantType().hasOption(memberName)) {
                continue;
            }

            auto& proc = instrReadUnkVariant.options().at(memberName);

            for (const auto& range : member.ranges()) {
                // copy linked list, but content is shared
                _ranges.push_back(Range {range.lower(), range.upper(), proc});
            }
        }

        std::sort(std::begin(_ranges), std::end(_ranges));
    }

private:
    Ranges _ranges;
    const Index _tagPos;
};

// "Read variant with unsigned tag" procedure instruction.
class InstrBeginReadVariantUnsignedTag :
    public InstrBeginReadVariant<UnsignedEnumType,
                                 Instr::Kind::BEGIN_READ_VARIANT_UNSIGNED_TAG>
{
public:
    explicit InstrBeginReadVariantUnsignedTag(const InstrBeginReadVariantUnknownTag& instrReadUnkVariant,
                                              const EnumType& tagType);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

// "Read variant with signed tag" procedure instruction.
class InstrBeginReadVariantSignedTag :
    public InstrBeginReadVariant<SignedEnumType,
                                 Instr::Kind::BEGIN_READ_VARIANT_SIGNED_TAG>
{
public:
    explicit InstrBeginReadVariantSignedTag(const InstrBeginReadVariantUnknownTag& instrReadUnkVariant,
                                            const EnumType& tagType);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set current ID" procedure instruction.
 *
 * This instruction asks the VM to set the current ID to the last
 * decoded value. This is either the current data stream type ID or the
 * current event record type ID.
 */
class InstrSetCurrentId :
    public Instr
{
public:
    InstrSetCurrentId();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set current type" procedure instruction abstract class.
 *
 * This instruction asks the VM to set the current data stream or event
 * record type using the current ID, or using `fixedId()` if it exists.
 */
class InstrSetType :
    public Instr
{
protected:
    explicit InstrSetType(const boost::optional<TypeId>& fixedId);

public:
    const boost::optional<TypeId>& fixedId() const noexcept
    {
        return _fixedId;
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    const boost::optional<TypeId> _fixedId;
};

// "Set current data stream type" procedure instruction.
class InstrSetDataStreamType :
    public InstrSetType
{
public:
    explicit InstrSetDataStreamType(const boost::optional<TypeId>& fixedId);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

// "Set current event record type" procedure instruction.
class InstrSetEventRecordType :
    public InstrSetType
{
public:
    explicit InstrSetEventRecordType(const boost::optional<TypeId>& fixedId);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set current packet index" procedure instruction.
 *
 * This instruction asks the VM to set the current packet index
 * (sequence number) to the last decoded value.
 */
class InstrSetPacketOriginIndex :
    public Instr
{
public:
    InstrSetPacketOriginIndex();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set data stream ID" procedure instruction.
 *
 * This instruction asks the VM to set the current data stream ID to the
 * last decoded value. This is NOT the current data stream type ID. It
 * is sometimes called the "data stream instance ID".
 */
class InstrSetDataStreamId :
    public Instr
{
public:
    InstrSetDataStreamId();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set packet's total size" procedure instruction.
 *
 * This instruction asks the VM to set the current packet's total size
 * (bits) to the last decoded value.
 */
class InstrSetPacketTotalSize :
    public Instr
{
public:
    InstrSetPacketTotalSize();
    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set packet's content size" procedure instruction.
 *
 * This instruction asks the VM to set the current packet's content size
 * (bits) to the last decoded value.
 */
class InstrSetPacketContentSize :
    public Instr
{
public:
    InstrSetPacketContentSize();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Update clock value" procedure instruction.
 *
 * This instruction asks the VM to update the current value of the clock
 * of which the type's index is `index()` from the last decoded value.
 */
class InstrUpdateClockValue :
    public Instr
{
public:
    explicit InstrUpdateClockValue(const ClockType& clockType, Index index,
                                   Size size);

    const ClockType& clockType() const noexcept
    {
        return *_clockType;
    }

    Index index() const noexcept
    {
        return _index;
    }

    Size size() const noexcept
    {
        return _size;
    }

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string _toString(Size indent = 0) const override;

private:
    const ClockType *_clockType;
    const Index _index;
    const Size _size;
};

/*
 * "Set packet magic number" procedure instruction.
 *
 * This instruction asks the VM to use the last decoded value as the
 * packet's magic number.
 */
class InstrSetPacketMagicNumber :
    public Instr
{
public:
    InstrSetPacketMagicNumber();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "End packet preamble procedure" procedure instruction.
 *
 * This instruction indicates that the packet preamble procedure
 * containing it has no more instructions.
 */
class InstrEndPacketPreambleProc :
    public Instr
{
public:
    InstrEndPacketPreambleProc();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "End data stream type packet preamble procedure" procedure
 * instruction.
 *
 * This instruction indicates that the data stream type packet preamble
 * procedure containing it has no more instructions.
 */
class InstrEndDstPacketPreambleProc :
    public Instr
{
public:
    InstrEndDstPacketPreambleProc();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "End data stream type event record type preamble procedure" procedure
 * instruction.
 *
 * This instruction indicates that the data stream type event record
 * type preamble procedure containing it has no more instructions.
 */
class InstrEndDstErtPreambleProc :
    public Instr
{
public:
    InstrEndDstErtPreambleProc();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "End event record type procedure" procedure instruction.
 *
 * This instruction indicates that the event record type procedure
 * containing it has no more instructions.
 */
class InstrEndErtProc :
    public Instr
{
public:
    InstrEndErtProc();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Decrement remaining elements" procedure instruction.
 *
 * When reading an array, this instruction asks the VM to decrement the
 * number of remaining elements to read. It is placed just before an
 * "end read compound data" instruction as a trade-off between checking
 * if we're in an array every time we end a compound data, or having
 * this decrementation instruction even for simple arrays of scalar
 * elements.
 */
class InstrDecrRemainingElements :
    public Instr
{
public:
    InstrDecrRemainingElements();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

// Event record type procedure.
class EventRecordTypeProc
{
public:
    explicit EventRecordTypeProc(const EventRecordType& eventRecordType);
    std::string toString(Size indent) const;
    InstrLocation findInstr(const FieldRef& fieldRef);
    void buildRawProcFromShared();

    Proc& proc() noexcept
    {
        return _proc;
    }

    const Proc& proc() const noexcept
    {
        return _proc;
    }

    const EventRecordType& eventRecordType() const noexcept
    {
        return *_eventRecordType;
    }

private:
    const EventRecordType *_eventRecordType;
    Proc _proc;
};

// Packet procedure for a given data stream type.
class DataStreamTypePacketProc
{
public:
    using EventRecordTypeProcsMap = std::unordered_map<TypeId, std::unique_ptr<EventRecordTypeProc>>;
    using EventRecordTypeProcsVec = std::vector<std::unique_ptr<EventRecordTypeProc>>;
    using ForEachEventRecordTypeProcFunc = std::function<void (EventRecordTypeProc&)>;

public:
    explicit DataStreamTypePacketProc(const DataStreamType& dataStreamType);
    void forEachEventRecordTypeProc(ForEachEventRecordTypeProcFunc func);
    const EventRecordTypeProc *operator[](TypeId id) const;
    const EventRecordTypeProc *singleEventRecordTypeProc() const;
    void addEventRecordTypeProc(std::unique_ptr<EventRecordTypeProc> ertProc);
    std::string toString(Size indent) const;
    InstrLocation findInstr(const FieldRef& fieldRef);
    void buildRawProcFromShared();

    Proc& packetPreambleProc() noexcept
    {
        return _packetPreambleProc;
    }

    const Proc& packetPreambleProc() const noexcept
    {
        return _packetPreambleProc;
    }

    Proc& eventRecordPreambleProc() noexcept
    {
        return _eventRecordPreambleProc;
    }

    const Proc& eventRecordPreambleProc() const noexcept
    {
        return _eventRecordPreambleProc;
    }

    EventRecordTypeProcsMap& eventRecordTypeProcsMap()
    {
        return _eventRecordTypeProcsMap;
    }

    EventRecordTypeProcsVec& eventRecordTypeProcsVec()
    {
        return _eventRecordTypeProcsVec;
    }

    Size eventRecordTypeProcsCount() const noexcept
    {
        return _eventRecordTypeProcsMap.size() +
               _eventRecordTypeProcsVec.size();
    }

    const DataStreamType& dataStreamType() const noexcept
    {
        return *_dataStreamType;
    }

private:
    const DataStreamType *_dataStreamType;
    Proc _packetPreambleProc;
    Proc _eventRecordPreambleProc;

    /*
     * We have both a vector and a map here to store event record type
     * procedures. Typically, event record type IDs are contiguous
     * within a given trace; storing them in the vector makes a more
     * efficient lookup afterwards if this is possible. For outliers, we
     * use the (slower) map.
     *
     * _eventRecordTypeProcsVec can contain both event record type
     * procedures and null pointers. _eventRecordTypeProcsMap contains
     * only event record type procedures.
     */
    EventRecordTypeProcsVec _eventRecordTypeProcsVec;
    EventRecordTypeProcsMap _eventRecordTypeProcsMap;
};

/*
 * Packet procedure.
 *
 * Such an object is owned by a TraceType object, and it is not public.
 * This means that all the pointers to anything inside the owning
 * TraceType object are always safe to use.
 *
 * Any object which needs to access a PacketProc object must own its
 * owning TraceType object. For example (ownership tree):
 *
 * User
 *   Packet sequence iterator
 *     VM
 *       TraceType
 *         PacketProc
 */
class PacketProc
{
public:
    using DataStreamTypePacketProcs = std::unordered_map<TypeId,
                                                         std::unique_ptr<DataStreamTypePacketProc>>;

public:
    explicit PacketProc(const TraceType &traceType);
    const DataStreamTypePacketProc *operator[](TypeId id) const;
    const DataStreamTypePacketProc *singleDataStreamTypePacketProc() const;
    std::string toString(Size indent) const;
    InstrLocation findInstr(const FieldRef& fieldRef);
    void buildRawProcFromShared();

    const TraceType& traceType() const noexcept
    {
        return *_traceType;
    }

    DataStreamTypePacketProcs& dataStreamTypePacketProcs()
    {
        return _dataStreamTypePacketProcs;
    }


    Size dataStreamTypePacketProcsCount() const noexcept
    {
        return _dataStreamTypePacketProcs.size();
    }

    Proc& preambleProc() noexcept
    {
        return _preambleProc;
    }

    const Proc& preambleProc() const noexcept
    {
        return _preambleProc;
    }

    std::vector<const ClockType *>& indexedClockTypes() noexcept
    {
        return _indexedClockTypes;
    }

    const std::vector<const ClockType *>& indexedClockTypes() const noexcept
    {
        return _indexedClockTypes;
    }

    Index clockTypeIndex(const std::string& clockTypeName);

    Size savedValuesCount() const noexcept
    {
        return _savedValuesCounts;
    }

    void savedValuesCount(const Size savedValuesCount)
    {
        _savedValuesCounts = savedValuesCount;
    }

private:
    const TraceType *_traceType;
    DataStreamTypePacketProcs _dataStreamTypePacketProcs;
    std::vector<const ClockType *> _indexedClockTypes;
    Size _savedValuesCounts;
    Proc _preambleProc;
};

static inline InstrReadData& instrAsReadData(Instr& instr) noexcept
{
    return static_cast<InstrReadData&>(instr);
}

static inline InstrBeginReadScope& instrAsBeginReadScope(Instr& instr) noexcept
{
    return static_cast<InstrBeginReadScope&>(instr);
}

static inline InstrBeginReadStruct& instrAsBeginReadStruct(Instr& instr) noexcept
{
    return static_cast<InstrBeginReadStruct&>(instr);
}

static inline InstrBeginReadVariantUnknownTag& instrAsBeginReadVariantUnknownTag(Instr& instr) noexcept
{
    return static_cast<InstrBeginReadVariantUnknownTag&>(instr);
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_PROC_HPP
