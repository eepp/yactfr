/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms of the
 * MIT license. See the LICENSE file for details.
 */

/*
 * Here are the possible instructions for the yactfr VM.
 *
 * No numeric bytecode is involved here: the VM deals with a sequence of
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
 * The top-level procedure is a `PktProc`. A `PktProc` object contains
 * all the instructions to apply for a whole packet.
 *
 * At the beginning of a packet:
 *
 * * Execute the preamble procedure of the packet procedure.
 *
 * A `DsPktProc` object contains the instructions to execute after the
 * preamble procedure of the packet procedure for any data stream of a
 * specific type.
 *
 * To execute a data stream packet procedure:
 *
 * 1. Execute the per-packet preamble procedure.
 *
 * 2. Until the end of the packet, repeat:
 *
 *    a) Execute the common event record preamble procedure.
 *
 *    b) Depending on the chosen event record type, execute the
 *       corresponding event record procedure (`ErProc`).
 *
 * An `ErProc` object contains a single procedure, that is, the
 * instructions to execute after the common event record preamble
 * procedure of its parent `DsPktProc`.
 *
 * Details such as how to choose the current data stream and event
 * record types, and how to determine the end of the packet, are left to
 * the implementation of the VM.
 */

#ifndef _YACTFR_PROC_HPP
#define _YACTFR_PROC_HPP

#include <cstdlib>
#include <cassert>
#include <sstream>
#include <list>
#include <vector>
#include <utility>
#include <functional>
#include <type_traits>
#include <boost/optional/optional.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/dt.hpp>
#include <yactfr/metadata/int-type.hpp>
#include <yactfr/metadata/float-type.hpp>
#include <yactfr/metadata/enum-type.hpp>
#include <yactfr/metadata/str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/dyn-array-type.hpp>
#include <yactfr/metadata/dyn-text-array-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/clk-type.hpp>
#include <yactfr/metadata/ert.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/trace-type.hpp>

#include "utils.hpp"

namespace yactfr {
namespace internal {

class BeginReadDynArrayInstr;
class BeginReadDynTextArrayInstr;
class BeginReadScopeInstr;
class BeginReadStaticArrayInstr;
class BeginReadStaticTextArrayInstr;
class BeginReadStaticUuidArrayInstr;
class BeginReadStructInstr;
class BeginReadVarSSelInstr;
class BeginReadVarUSelInstr;
class DecrRemainingElemsInstr;
class EndDsErPreambleProcInstr;
class EndDsPktPreambleProcInstr;
class EndErProcInstr;
class EndPktPreambleProcInstr;
class EndReadCompoundInstr;
class EndReadScopeInstr;
class Instr;
class ReadBitArrayInstr;
class ReadDataInstr;
class ReadFloatInstr;
class ReadSEnumInstr;
class ReadSIntInstr;
class ReadStrInstr;
class ReadUEnumInstr;
class ReadUIntInstr;
class SaveValInstr;
class SetCurIdInstr;
class SetDsIdInstr;
class SetDstInstr;
class SetErtInstr;
class SetExpectedPktContentLenInstr;
class SetPktEndDefClkValInstr;
class SetPktMagicNumberInstr;
class SetPktOriginIndexInstr;
class SetExpectedPktTotalLenInstr;
class UpdateDefClkValInstr;

/*
 * A classic abstract visitor class for procedure instructions.
 *
 * Used by `PktProcBuilder`, NOT by the VM.
 */
class InstrVisitor
{
protected:
    explicit InstrVisitor() = default;

public:
    virtual ~InstrVisitor() = default;

    virtual void visit(ReadSIntInstr& instr)
    {
    }

    virtual void visit(ReadUIntInstr& instr)
    {
    }

    virtual void visit(ReadFloatInstr& instr)
    {
    }

    virtual void visit(ReadSEnumInstr& instr)
    {
    }

    virtual void visit(ReadUEnumInstr& instr)
    {
    }

    virtual void visit(ReadStrInstr& instr)
    {
    }

    virtual void visit(BeginReadScopeInstr& instr)
    {
    }

    virtual void visit(EndReadScopeInstr& instr)
    {
    }

    virtual void visit(BeginReadStructInstr& instr)
    {
    }

    virtual void visit(BeginReadStaticArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadStaticUuidArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadStaticTextArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadDynArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadDynTextArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadVarUSelInstr& instr)
    {
    }

    virtual void visit(BeginReadVarSSelInstr& instr)
    {
    }

    virtual void visit(EndReadCompoundInstr& instr)
    {
    }

    virtual void visit(UpdateDefClkValInstr& instr)
    {
    }

    virtual void visit(SetCurIdInstr& instr)
    {
    }

    virtual void visit(SetDstInstr& instr)
    {
    }

    virtual void visit(SetErtInstr& instr)
    {
    }

    virtual void visit(SetDsIdInstr& instr)
    {
    }

    virtual void visit(SetPktOriginIndexInstr& instr)
    {
    }

    virtual void visit(SetExpectedPktTotalLenInstr& instr)
    {
    }

    virtual void visit(SetExpectedPktContentLenInstr& instr)
    {
    }

    virtual void visit(SaveValInstr& instr)
    {
    }

    virtual void visit(SetPktEndDefClkValInstr& instr)
    {
    }

    virtual void visit(SetPktMagicNumberInstr& instr)
    {
    }

    virtual void visit(EndPktPreambleProcInstr& instr)
    {
    }

    virtual void visit(EndDsPktPreambleProcInstr& instr)
    {
    }

    virtual void visit(EndDsErPreambleProcInstr& instr)
    {
    }

    virtual void visit(EndErProcInstr& instr)
    {
    }

    virtual void visit(DecrRemainingElemsInstr& instr)
    {
    }
};

/*
 * A procedure, that is, a sequence of instructions.
 *
 * The procedure is first built as a list of shared pointers because the
 * build process needs to insert and replace instructions and it's
 * easier with a linked list.
 *
 * Then, when the build is complete, we call buildRawProcFromShared()
 * which builds a vector of raw instruction object (weak) pointers from
 * the list of shared pointers. The list must remain alive as it keeps
 * the instructions alive. Going from raw pointer to raw pointer in a
 * vector seems more efficient than going from shared pointer to shared
 * pointer in a linked list. I did not measure the difference yet
 * however.
 *
 * Instructions are shared because sometimes they are reused, for
 * example multiple range procedures of a `BeginReadVarInstr`
 * instruction can refer to the exact same instructions.
 */
class Proc final
{
public:
    using Raw = std::vector<const Instr *>;
    using Shared = std::list<std::shared_ptr<Instr>>;
    using RawIt = Raw::const_iterator;
    using SharedIt = Shared::iterator;

public:
    void buildRawProcFromShared();
    std::string toStr(Size indent = 0) const;
    void pushBack(std::shared_ptr<Instr> instr);
    SharedIt insert(SharedIt it, std::shared_ptr<Instr> instr);

    Shared& sharedProc() noexcept
    {
        return _sharedProc;
    }

    const Shared& sharedProc() const noexcept
    {
        return _sharedProc;
    }

    const Raw& rawProc() const noexcept
    {
        return _rawProc;
    }

    SharedIt begin() noexcept
    {
        return _sharedProc.begin();
    }

    SharedIt end() noexcept
    {
        return _sharedProc.end();
    }

private:
    Raw _rawProc;
    Shared _sharedProc;
};

/*
 * A pair of procedure and instruction iterator.
 */
struct InstrLoc final
{
    Proc::Shared *proc = nullptr;
    Proc::Shared::iterator it;
};

/*
 * List of instruction locations.
 */
using InstrLocs = std::vector<InstrLoc>;

/*
 * Procedure instruction abstract class.
 */
class Instr
{
public:
    // kind of instruction (opcode)
    enum class Kind
    {
        UNSET,
        BEGIN_READ_DYN_ARRAY,
        BEGIN_READ_DYN_TEXT_ARRAY,
        BEGIN_READ_SCOPE,
        BEGIN_READ_STATIC_ARRAY,
        BEGIN_READ_STATIC_TEXT_ARRAY,
        BEGIN_READ_STATIC_UUID_ARRAY,
        BEGIN_READ_STRUCT,
        BEGIN_READ_VAR_SSEL,
        BEGIN_READ_VAR_USEL,
        DECR_REMAINING_ELEMS,
        END_DS_ER_PREAMBLE_PROC,
        END_DS_PKT_PREAMBLE_PROC,
        END_ER_PROC,
        END_PKT_PREAMBLE_PROC,
        END_READ_DYN_ARRAY,
        END_READ_DYN_TEXT_ARRAY,
        END_READ_SCOPE,
        END_READ_STATIC_ARRAY,
        END_READ_STATIC_TEXT_ARRAY,
        END_READ_STRUCT,
        END_READ_VAR,
        READ_FLOAT_32_BE,
        READ_FLOAT_32_LE,
        READ_FLOAT_64_BE,
        READ_FLOAT_64_LE,
        READ_FLOAT_A32_BE,
        READ_FLOAT_A32_LE,
        READ_FLOAT_A64_BE,
        READ_FLOAT_A64_LE,
        READ_SENUM_A16_BE,
        READ_SENUM_A16_LE,
        READ_SENUM_A32_BE,
        READ_SENUM_A32_LE,
        READ_SENUM_A64_BE,
        READ_SENUM_A64_LE,
        READ_SENUM_A8,
        READ_SENUM_BE,
        READ_SENUM_LE,
        READ_SINT_A16_BE,
        READ_SINT_A16_LE,
        READ_SINT_A32_BE,
        READ_SINT_A32_LE,
        READ_SINT_A64_BE,
        READ_SINT_A64_LE,
        READ_SINT_A8,
        READ_SINT_BE,
        READ_SINT_LE,
        READ_STR,
        READ_UENUM_A16_BE,
        READ_UENUM_A16_LE,
        READ_UENUM_A32_BE,
        READ_UENUM_A32_LE,
        READ_UENUM_A64_BE,
        READ_UENUM_A64_LE,
        READ_UENUM_A8,
        READ_UENUM_BE,
        READ_UENUM_LE,
        READ_UINT_A16_BE,
        READ_UINT_A16_LE,
        READ_UINT_A32_BE,
        READ_UINT_A32_LE,
        READ_UINT_A64_BE,
        READ_UINT_A64_LE,
        READ_UINT_A8,
        READ_UINT_BE,
        READ_UINT_LE,
        SAVE_VAL,
        SET_CUR_ID,
        SET_DS_ID,
        SET_DST,
        SET_ERT,
        SET_PKT_CONTENT_LEN,
        SET_PKT_END_DEF_CLK_VAL,
        SET_PKT_MAGIC_NUMBER,
        SET_PKT_ORIGIN_INDEX,
        SET_PKT_TOTAL_LEN,
        UPDATE_DEF_CLK_VAL,
    };

public:
    using SP = std::shared_ptr<Instr>;
    using FindInstrsCurrent = std::unordered_map<const Instr *, Index>;

protected:
    explicit Instr() noexcept = default;
    explicit Instr(Kind kind) noexcept;

public:
    virtual ~Instr() = default;
    virtual void accept(InstrVisitor& visitor) = 0;
    virtual void buildRawProcFromShared();

    // only used for debugging purposes
    std::string toStr(Size indent = 0) const;

    Kind kind() const noexcept
    {
        assert(_theKind != Kind::UNSET);
        return _theKind;
    }

    /*
     * Please DO NOT FREAK OUT about the isX() methods belows.
     *
     * They are only helpers which are used when _building_ the
     * procedures. The yactfr VM uses kind() directly and a function
     * table.
     */

    bool isReadData() const noexcept
    {
        return this->isReadInt() ||
               this->isReadFloat() ||
               this->isReadStr() ||
               this->isBeginReadCompound() ||
               this->isBeginReadVar();
    }

    bool isBeginReadScope() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_SCOPE;
    }

    bool isBeginReadCompound() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_STRUCT ||
               _theKind == Kind::BEGIN_READ_STATIC_ARRAY ||
               _theKind == Kind::BEGIN_READ_STATIC_UUID_ARRAY ||
               _theKind == Kind::BEGIN_READ_STATIC_TEXT_ARRAY ||
               _theKind == Kind::BEGIN_READ_DYN_ARRAY ||
               _theKind == Kind::BEGIN_READ_DYN_TEXT_ARRAY;
    }

    bool isReadInt() const noexcept
    {
        return this->isReadSInt() || this->isReadUInt();
    }

    bool isReadSInt() const noexcept
    {
        return _theKind == Kind::READ_SINT_LE ||
               _theKind == Kind::READ_SINT_BE ||
               _theKind == Kind::READ_SINT_A8 ||
               _theKind == Kind::READ_SINT_A16_LE ||
               _theKind == Kind::READ_SINT_A32_LE ||
               _theKind == Kind::READ_SINT_A64_LE ||
               _theKind == Kind::READ_SINT_A16_BE ||
               _theKind == Kind::READ_SINT_A32_BE ||
               _theKind == Kind::READ_SINT_A64_BE ||
               this->isReadSEnum();
    }

    bool isReadUInt() const noexcept
    {
        return _theKind == Kind::READ_UINT_LE ||
               _theKind == Kind::READ_UINT_BE ||
               _theKind == Kind::READ_UINT_A8 ||
               _theKind == Kind::READ_UINT_A16_LE ||
               _theKind == Kind::READ_UINT_A32_LE ||
               _theKind == Kind::READ_UINT_A64_LE ||
               _theKind == Kind::READ_UINT_A16_BE ||
               _theKind == Kind::READ_UINT_A32_BE ||
               _theKind == Kind::READ_UINT_A64_BE ||
               this->isReadUEnum();
    }

    bool isReadFloat() const noexcept
    {
        return _theKind == Kind::READ_FLOAT_32_LE ||
               _theKind == Kind::READ_FLOAT_32_BE ||
               _theKind == Kind::READ_FLOAT_A32_LE ||
               _theKind == Kind::READ_FLOAT_A32_BE ||
               _theKind == Kind::READ_FLOAT_64_LE ||
               _theKind == Kind::READ_FLOAT_64_BE ||
               _theKind == Kind::READ_FLOAT_A64_LE ||
               _theKind == Kind::READ_FLOAT_A64_BE;
    }

    bool isReadEnum() const noexcept
    {
        return this->isReadSEnum() || this->isReadUEnum();
    }

    bool isReadSEnum() const noexcept
    {
        return _theKind == Kind::READ_SENUM_LE ||
               _theKind == Kind::READ_SENUM_BE ||
               _theKind == Kind::READ_SENUM_A8 ||
               _theKind == Kind::READ_SENUM_A16_LE ||
               _theKind == Kind::READ_SENUM_A32_LE ||
               _theKind == Kind::READ_SENUM_A64_LE ||
               _theKind == Kind::READ_SENUM_A16_BE ||
               _theKind == Kind::READ_SENUM_A32_BE ||
               _theKind == Kind::READ_SENUM_A64_BE;
    }

    bool isReadUEnum() const noexcept
    {

        return _theKind == Kind::READ_UENUM_LE ||
               _theKind == Kind::READ_UENUM_BE ||
               _theKind == Kind::READ_UENUM_A8 ||
               _theKind == Kind::READ_UENUM_A16_LE ||
               _theKind == Kind::READ_UENUM_A32_LE ||
               _theKind == Kind::READ_UENUM_A64_LE ||
               _theKind == Kind::READ_UENUM_A16_BE ||
               _theKind == Kind::READ_UENUM_A32_BE ||
               _theKind == Kind::READ_UENUM_A64_BE;
    }

    bool isReadStr() const noexcept
    {
        return _theKind == Kind::READ_STR;
    }

    bool isBeginReadStaticArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_STATIC_ARRAY ||
               _theKind == Kind::BEGIN_READ_STATIC_UUID_ARRAY ||
               _theKind == Kind::BEGIN_READ_STATIC_TEXT_ARRAY;
    }

    bool isBeginReadStaticTextArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_STATIC_TEXT_ARRAY;
    }

    bool isBeginReadStaticUuidArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_STATIC_UUID_ARRAY;
    }

    bool isBeginReadDynArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_DYN_ARRAY ||
               _theKind == Kind::BEGIN_READ_DYN_TEXT_ARRAY;
    }

    bool isBeginReadDynTextArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_DYN_TEXT_ARRAY;
    }

    bool isBeginReadStruct() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_STRUCT;
    }

    bool isBeginReadVar() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_VAR_SSEL ||
               _theKind == Kind::BEGIN_READ_VAR_USEL;
    }

    bool isBeginReadVarSSel() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_VAR_SSEL;
    }

    bool isBeginReadVarUSel() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_VAR_USEL;
    }

    bool isEndReadCompound() const noexcept
    {
        return _theKind == Kind::END_READ_STRUCT ||
               _theKind == Kind::END_READ_STATIC_ARRAY ||
               _theKind == Kind::END_READ_STATIC_TEXT_ARRAY ||
               _theKind == Kind::END_READ_DYN_ARRAY ||
               _theKind == Kind::END_READ_DYN_TEXT_ARRAY ||
               _theKind == Kind::END_READ_VAR;
    }

    bool isEndProc() const noexcept
    {
        return _theKind == Kind::END_PKT_PREAMBLE_PROC ||
               _theKind == Kind::END_DS_PKT_PREAMBLE_PROC ||
               _theKind == Kind::END_DS_ER_PREAMBLE_PROC ||
               _theKind == Kind::END_ER_PROC;
    }

private:
    virtual std::string _toStr(Size indent = 0) const;

private:
    const Kind _theKind = Kind::UNSET;
};

/*
 * "Read data" procedure instruction abstract class.
 */
class ReadDataInstr :
    public Instr
{
protected:
    explicit ReadDataInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

public:
    /*
     * `memberType` can be `nullptr` if this is the scope's root read
     * instruction.
     */
    explicit ReadDataInstr(const StructureMemberType *memberType, const DataType& dt);

    const DataType& dt() const noexcept
    {
        return *_dt;
    }

    const StructureMemberType *memberType() const noexcept
    {
        return _memberType;
    }

    unsigned int align() const noexcept
    {
        return _align;
    }

protected:
    std::string _commonToStr() const;

private:
    const StructureMemberType * const _memberType;
    const DataType * const _dt;
    const unsigned int _align;
};

/*
 * "Save value" procedure instruction.
 *
 * This instruction requires the VM to save the last decoded integer
 * value to a position (index) in its saved value vector so that it can
 * be used later (for the length of a dynamic array or for the selector
 * of a variant).
 */
class SaveValInstr :
    public Instr
{
public:
    explicit SaveValInstr(Index pos);

    const Index pos() const noexcept
    {
        return _pos;
    }

    void pos(const Index pos) noexcept
    {
        _pos = pos;
    }

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    Index _pos;
};

/*
 * "Set packet end clock value" procedure instruction.
 *
 * This instruction indicates to the VM that the last decoded integer
 * value is the packet end clock value.
 */
class SetPktEndDefClkValInstr :
    public Instr
{
public:
    explicit SetPktEndDefClkValInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Read bit array" procedure instruction abstract class.
 */
class ReadBitArrayInstr :
    public ReadDataInstr
{
protected:
    explicit ReadBitArrayInstr(Kind kind, const StructureMemberType *memberType,
                               const DataType& dt);

public:
    unsigned int len() const noexcept
    {
        return _len;
    }

    ByteOrder bo() const noexcept
    {
        return _bo;
    }

protected:
    std::string _commonToStr() const;

private:
    std::string _toStr(const Size indent = 0) const override;

private:
    const unsigned int _len;
    const ByteOrder _bo;
};

/*
 * "Read integer" procedure instruction abstract class.
 */
class ReadIntInstr :
    public ReadBitArrayInstr
{
protected:
    explicit ReadIntInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

public:
    explicit ReadIntInstr(const StructureMemberType *memberType, const DataType& dt);

    const IntegerType& intType() const noexcept
    {
        return static_cast<const IntegerType&>(this->dt());
    }
};

/*
 * "Read signed integer" procedure instruction.
 */
class ReadSIntInstr :
    public ReadIntInstr
{
protected:
    explicit ReadSIntInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

public:
    explicit ReadSIntInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const SignedIntegerType& sIntType() const noexcept
    {
        return static_cast<const SignedIntegerType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read unsigned integer" procedure instruction.
 */
class ReadUIntInstr :
    public ReadIntInstr
{
protected:
    explicit ReadUIntInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

public:
    explicit ReadUIntInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const UnsignedIntegerType& uIntType() const noexcept
    {
        return static_cast<const UnsignedIntegerType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read floating point number" procedure instruction.
 */
class ReadFloatInstr :
    public ReadBitArrayInstr
{
public:
    explicit ReadFloatInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FloatingPointNumberType& floatType() const noexcept
    {
        return static_cast<const FloatingPointNumberType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read signed enumeration" procedure instruction.
 */
class ReadSEnumInstr :
    public ReadSIntInstr
{
public:
    explicit ReadSEnumInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const SignedEnumerationType& sEnumType() const noexcept
    {
        return static_cast<const SignedEnumerationType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read unsigned enumeration" procedure instruction.
 */
class ReadUEnumInstr :
    public ReadUIntInstr
{
public:
    explicit ReadUEnumInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const UnsignedEnumerationType& uEnumType() const noexcept
    {
        return static_cast<const UnsignedEnumerationType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read null-terminated string" procedure instruction.
 */
class ReadStrInstr :
    public ReadDataInstr
{
public:
    explicit ReadStrInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StringType& strType() const noexcept
    {
        return static_cast<const StringType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Begin reading compound data" procedure instruction abstract class.
 *
 * This instruction contains a subprocedure to execute.
 */
class BeginReadCompoundInstr :
    public ReadDataInstr
{
protected:
    explicit BeginReadCompoundInstr(Kind kind, const StructureMemberType *memberType,
                                    const DataType& dt);

public:
    const Proc& proc() const noexcept
    {
        return _proc;
    }

    Proc& proc() noexcept
    {
        return _proc;
    }

    void buildRawProcFromShared() override;

protected:
    std::string _procToStr(const Size indent) const
    {
        return _proc.toStr(indent);
    }

private:
    Proc _proc;
};

/*
 * "End reading compound data" procedure instruction.
 *
 * If the kind of this instruction is `END_READ_STRUCT`, then the VM
 * must stop executing the current procedure and continue executing the
 * parent procedure.
 *
 * For all instruction kinds, this instruction requires the VM to set a
 * `StructEndElement` as the current element.
 */
class EndReadCompoundInstr :
    public ReadDataInstr
{
public:
    explicit EndReadCompoundInstr(Kind kind, const StructureMemberType *memberType,
                                  const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Begin reading structure" procedure instruction.
 */
class BeginReadStructInstr :
    public BeginReadCompoundInstr
{
public:
    explicit BeginReadStructInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StructureType& structType() const noexcept
    {
        return static_cast<const StructureType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Begin reading scope" procedure instruction.
 *
 * This is the top-level instruction to start reading a whole scope
 * (packet header, packet context, event record payload, etc.).
 */
class BeginReadScopeInstr :
    public Instr
{
public:
    explicit BeginReadScopeInstr(Scope scope, unsigned int align);
    void buildRawProcFromShared() override;

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

    unsigned int align() const noexcept
    {
        return _align;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const Scope _scope;
    const unsigned int _align = 1;
    Proc _proc;
};

/*
 * "End reading scope" procedure instruction.
 *
 * This requires the VM to stop executing the current procedure and
 * continue executing the parent procedure.
 */
class EndReadScopeInstr :
    public Instr
{
public:
    explicit EndReadScopeInstr(Scope scope);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    Scope scope() const noexcept
    {
        return _scope;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const Scope _scope;
};

/*
 * "Begin reading static array" procedure instruction.
 *
 * The VM must execute the subprocedure `len()` times.
 */
class BeginReadStaticArrayInstr :
    public BeginReadCompoundInstr
{
protected:
    explicit BeginReadStaticArrayInstr(Kind kind, const StructureMemberType *memberType,
                                       const DataType& dt);

public:
    explicit BeginReadStaticArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StaticArrayType& staticArrayType() const noexcept
    {
        return static_cast<const StaticArrayType&>(this->dt());
    }

    Size len() const noexcept
    {
        return _len;
    }

protected:
    std::string _commonToStr() const;

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const Size _len;
};

/*
 * "Begin reading static text array" procedure instruction.
 */
class BeginReadStaticTextArrayInstr :
    public BeginReadStaticArrayInstr
{
public:
    explicit BeginReadStaticTextArrayInstr(const StructureMemberType *memberType,
                                           const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StaticTextArrayType& staticTextArrayType() const noexcept
    {
        return static_cast<const StaticTextArrayType&>(this->dt());
    }
};

/*
 * "Begin reading static UUID array" procedure instruction.
 *
 * This is a specialized instruction to read the UUID field (16 bytes)
 * of a packet header to emit `TraceTypeUuidElement`.
 */
class BeginReadStaticUuidArrayInstr :
    public BeginReadStaticArrayInstr
{
public:
    explicit BeginReadStaticUuidArrayInstr(const StructureMemberType *memberType,
                                           const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Begin reading dynamic array" procedure instruction.
 *
 * The VM must use `lenPos()` to retrieve the saved value which contains
 * the length of the dynamic array, and then execute the subprocedure
 * this number of times.
 */
class BeginReadDynArrayInstr :
    public BeginReadCompoundInstr
{
protected:
    explicit BeginReadDynArrayInstr(Kind kind, const StructureMemberType *memberType,
                                    const DataType& dt);

public:
    explicit BeginReadDynArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const DynamicArrayType& dynArrayType() const noexcept
    {
        return static_cast<const DynamicArrayType&>(this->dt());
    }

    const Index lenPos() const noexcept
    {
        return _lenPos;
    }

    void lenPos(const Index lenPos) noexcept
    {
        _lenPos = lenPos;
    }

protected:
    std::string _commonToStr() const;

private:
    std::string _toStr(Size indent = 0) const override;

private:
    Index _lenPos = -1ULL;
};

/*
 * "Begin reading dynamic text array" procedure instruction.
 */
class BeginReadDynTextArrayInstr :
    public BeginReadDynArrayInstr
{
public:
    explicit BeginReadDynTextArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const DynamicTextArrayType& dynTextArrayType() const noexcept
    {
        return static_cast<const DynamicTextArrayType&>(this->dt());
    }
};

/*
 * Option of a "read variant" procedure instruction.
 */
template <typename VarTypeOptT>
class ReadVarInstrOpt
{
public:
    using Opt = VarTypeOptT;
    using RangeSet = typename Opt::RangeSet;
    using Val = typename RangeSet::Value;

public:
    explicit ReadVarInstrOpt() = default;
    ReadVarInstrOpt(const ReadVarInstrOpt<VarTypeOptT>& opt) = default;
    ReadVarInstrOpt(ReadVarInstrOpt<VarTypeOptT>&& opt) = default;
    ReadVarInstrOpt<VarTypeOptT>& operator=(const ReadVarInstrOpt<VarTypeOptT>& opt) = default;
    ReadVarInstrOpt<VarTypeOptT>& operator=(ReadVarInstrOpt<VarTypeOptT>&& opt) = default;

    explicit ReadVarInstrOpt(const VarTypeOptT& opt) :
        _opt {&opt}
    {
    }

    void buildRawProcFromShared()
    {
        _proc.buildRawProcFromShared();
    }

    bool contains(const Val val) const noexcept
    {
        return _opt->ranges().contains(val);
    }

    const Opt& opt() const noexcept
    {
        return *_opt;
    }

    const RangeSet& ranges() const noexcept
    {
        return _opt->ranges();
    }

    const Proc& proc() const noexcept
    {
        return _proc;
    }

    Proc& proc() noexcept
    {
        return _proc;
    }

    std::string toStr(const Size indent = 0) const
    {
        std::ostringstream ss;

        ss << internal::indent(indent) << "<var opt>";

        for (const auto& range : _opt->ranges()) {
            ss << " [" << range.lower() << ", " << range.upper() << "]";
        }

        ss << std::endl << _proc.toStr(indent + 1);
        return ss.str();
    }

private:
    const Opt *_opt;

    /*
     * Contained pointers are not owned by this object: they are owned
     * by the variant instruction object which contains the options.
     */
    Proc _proc;
};

static inline std::string _strProp(const std::string& prop)
{
    std::string rProp;

    rProp = "\033[1m";
    rProp += prop;
    rProp += "\033[0m=";
    return rProp;
}

/*
 * "Begin reading variant" procedure instruction template.
 *
 * The VM must use `selPos()` to retrieve the saved value which is the
 * selector of the variant, find the corresponding option for this
 * selector value, and then execute the subprocedure of the option.
 */
template <typename VarTypeT, Instr::Kind SelfKind>
class BeginReadVarInstr :
    public ReadDataInstr
{
public:
    using Opt = ReadVarInstrOpt<typename VarTypeT::Option>;
    using Opts = std::vector<Opt>;

protected:
    explicit BeginReadVarInstr(const StructureMemberType * const memberType, const DataType& dt) :
        ReadDataInstr {SelfKind, memberType, dt}
    {
        auto& varType = static_cast<const VarTypeT&>(dt);

        for (auto& opt : varType.options()) {
            _opts.emplace_back(*opt);
        }
    }

public:
    void buildRawProcFromShared() override
    {
        for (auto& opt : _opts) {
            opt.buildRawProcFromShared();
        }
    }

    const VarTypeT& varType() const noexcept
    {
        return static_cast<const VarTypeT&>(this->dt());
    }

    const Opts& opts() const noexcept
    {
        return _opts;
    }

    Opts& opts() noexcept
    {
        return _opts;
    }

    const Proc *procForSelVal(const typename Opt::Val selVal) const noexcept
    {
        for (auto& opt : _opts) {
            if (opt.contains(selVal)) {
                return &opt.proc();
            }
        }

        return nullptr;
    }

    const Index selPos() const noexcept
    {
        return _selPos;
    }

    void selPos(const Index pos) noexcept
    {
        _selPos = pos;
    }

private:
    std::string _toStr(const Size indent = 0) const override
    {
        std::ostringstream ss;

        ss << this->_commonToStr() << " " << _strProp("sel-pos") << _selPos << std::endl;

        for (const auto& opt : _opts) {
            ss << opt.toStr(indent + 1);
        }

        return ss.str();
    }

private:
    Opts _opts;
    Index _selPos;
};

class BeginReadVarUSelInstr :
    public BeginReadVarInstr<VariantWithUnsignedSelectorType, Instr::Kind::BEGIN_READ_VAR_USEL>
{
public:
    explicit BeginReadVarUSelInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

class BeginReadVarSSelInstr :
    public BeginReadVarInstr<VariantWithSignedSelectorType, Instr::Kind::BEGIN_READ_VAR_SSEL>
{
public:
    explicit BeginReadVarSSelInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set current ID" procedure instruction.
 *
 * This instruction requires the VM to set the current ID to the last
 * decoded value. This is either the current data stream type ID or the
 * current event record type ID.
 */
class SetCurIdInstr :
    public Instr
{
public:
    explicit SetCurIdInstr();

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
 *
 * TODO: This ☝ doesn't seem like the correct approach.
 */
class SetTypeInstr :
    public Instr
{
protected:
    explicit SetTypeInstr(Kind kind, boost::optional<TypeId> fixedId);

public:
    const boost::optional<TypeId>& fixedId() const noexcept
    {
        return _fixedId;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const boost::optional<TypeId> _fixedId;
};

/*
 * "Set current data stream type" procedure instruction.
 */
class SetDstInstr :
    public SetTypeInstr
{
public:
    explicit SetDstInstr(boost::optional<TypeId> fixedId = boost::none);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set current event record type" procedure instruction.
 */
class SetErtInstr :
    public SetTypeInstr
{
public:
    explicit SetErtInstr(boost::optional<TypeId> fixedId = boost::none);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set packet origin index" procedure instruction.
 *
 * This instruction requires the VM to set the packet origin index
 * (sequence number) to the last decoded value.
 */
class SetPktOriginIndexInstr :
    public Instr
{
public:
    explicit SetPktOriginIndexInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set data stream ID" procedure instruction.
 *
 * This instruction requires the VM to set the data stream ID to the
 * last decoded value.
 *
 * This is NOT the current data stream _type_ ID. It's sometimes called
 * the "data stream instance ID".
 */
class SetDsIdInstr :
    public Instr
{
public:
    explicit SetDsIdInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set expected packet total length" procedure instruction.
 *
 * This instruction requires the VM to set the expected packet total
 * length (bits) to the last decoded value.
 */
class SetExpectedPktTotalLenInstr :
    public Instr
{
public:
    explicit SetExpectedPktTotalLenInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set expected packet content length" procedure instruction.
 *
 * This instruction requires the VM to set the expected packet content
 * length (bits) to the last decoded value.
 */
class SetExpectedPktContentLenInstr :
    public Instr
{
public:
    explicit SetExpectedPktContentLenInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Update clock value" procedure instruction.
 *
 * This instruction requires the VM to update the value of the default
 * clock from the last decoded value.
 */
class UpdateDefClkValInstr :
    public Instr
{
public:
    explicit UpdateDefClkValInstr(Size len);

    Size len() const noexcept
    {
        return _len;
    }

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const Size _len;
};

/*
 * "Set packet magic number" procedure instruction.
 *
 * This instruction requires the VM to use the last decoded value as the
 * packet magic number.
 */
class SetPktMagicNumberInstr :
    public Instr
{
public:
    explicit SetPktMagicNumberInstr();

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
class EndPktPreambleProcInstr :
    public Instr
{
public:
    explicit EndPktPreambleProcInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "End data stream packet preamble procedure" procedure instruction.
 *
 * This instruction indicates that the data stream packet preamble
 * procedure containing it has no more instructions.
 */
class EndDsPktPreambleProcInstr :
    public Instr
{
public:
    explicit EndDsPktPreambleProcInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "End data stream event record preamble procedure" procedure
 * instruction.
 *
 * This instruction indicates that the data stream event record preamble
 * procedure containing it has no more instructions.
 */
class EndDsErPreambleProcInstr :
    public Instr
{
public:
    explicit EndDsErPreambleProcInstr();

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
class EndErProcInstr :
    public Instr
{
public:
    explicit EndErProcInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Decrement remaining elements" procedure instruction.
 *
 * When reading an array, this instruction requires the VM to decrement
 * the number of remaining elements to read.
 *
 * It's placed just before an "end read compound data" instruction as a
 * trade-off between checking if we're in an array every time we end a
 * compound data, or having this decrementation instruction even for
 * simple arrays of scalar elements.
 */
class DecrRemainingElemsInstr :
    public Instr
{
public:
    explicit DecrRemainingElemsInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * Event record procedure.
 */
class ErProc
{
public:
    explicit ErProc(const EventRecordType& ert);
    std::string toStr(Size indent) const;
    void buildRawProcFromShared();

    Proc& proc() noexcept
    {
        return _proc;
    }

    const Proc& proc() const noexcept
    {
        return _proc;
    }

    const EventRecordType& ert() const noexcept
    {
        return *_ert;
    }

private:
    const EventRecordType * const _ert;
    Proc _proc;
};

/*
 * Packet procedure for any data stream of a given type.
 */
class DsPktProc
{
public:
    using ErProcsMap = std::unordered_map<TypeId, std::unique_ptr<ErProc>>;
    using ErProcsVec = std::vector<std::unique_ptr<ErProc>>;
    using ForEachErProcFunc = std::function<void (ErProc&)>;

public:
    explicit DsPktProc(const DataStreamType& dst);
    const ErProc *operator[](TypeId id) const noexcept;
    const ErProc *singleErProc() const noexcept;
    void addErProc(std::unique_ptr<ErProc> erProc);
    std::string toStr(Size indent) const;
    void buildRawProcFromShared();
    void setErAlign();

    template <typename FuncT>
    void forEachErProc(FuncT&& func)
    {
        for (auto& erProc : _erProcsVec) {
            if (erProc) {
                std::forward<FuncT>(func)(*erProc);
            }
        }

        for (auto& idErProcUpPair : _erProcsMap) {
            std::forward<FuncT>(func)(*idErProcUpPair.second);
        }
    }

    Proc& pktPreambleProc() noexcept
    {
        return _pktPreambleProc;
    }

    const Proc& pktPreambleProc() const noexcept
    {
        return _pktPreambleProc;
    }

    Proc& erPreambleProc() noexcept
    {
        return _erPreambleProc;
    }

    const Proc& erPreambleProc() const noexcept
    {
        return _erPreambleProc;
    }

    ErProcsMap& erProcsMap() noexcept
    {
        return _erProcsMap;
    }

    ErProcsVec& erProcsVec() noexcept
    {
        return _erProcsVec;
    }

    Size erProcsCount() const noexcept
    {
        return _erProcsMap.size() + _erProcsVec.size();
    }

    const DataStreamType& dst() const noexcept
    {
        return *_dst;
    }

    unsigned int erAlign() const noexcept
    {
        return _erAlign;
    }

private:
    const DataStreamType * const _dst;
    Proc _pktPreambleProc;
    Proc _erPreambleProc;
    unsigned int _erAlign = 1;

    /*
     * We have both a vector and a map here to store event record
     * procedures. Typically, event record type IDs are contiguous
     * within a given trace; storing them in the vector makes a more
     * efficient lookup afterwards if this is possible. For outliers, we
     * use the (slower) map.
     *
     * _erProcsVec can contain both event record procedures and null
     * pointers. _erProcsMap contains only event record procedures.
     */
    ErProcsVec _erProcsVec;
    ErProcsMap _erProcsMap;
};

/*
 * Packet procedure.
 *
 * Such an object is owned by a `TraceType` object, and it's not public.
 * This means that all the pointers to anything inside the owning
 * `TraceType` object are always safe to use.
 *
 * Any object which needs to access a `PktProc` object must own its
 * owning `TraceType` object. For example (ownership tree):
 *
 *     User
 *       Element sequence iterator
 *         VM
 *           Trace type
 *             Packet procedure
 */
class PktProc
{
public:
    using DsPktProcs = std::unordered_map<TypeId, std::unique_ptr<DsPktProc>>;

public:
    explicit PktProc(const TraceType &traceType);
    const DsPktProc *operator[](TypeId id) const noexcept;
    const DsPktProc *singleDsPktProc() const noexcept;
    std::string toStr(Size indent) const;
    void buildRawProcFromShared();

    const TraceType& traceType() const noexcept
    {
        return *_traceType;
    }

    DsPktProcs& dsPktProcs() noexcept
    {
        return _dsPktProcs;
    }

    Size dsPktProcsCount() const noexcept
    {
        return _dsPktProcs.size();
    }

    Proc& preambleProc() noexcept
    {
        return _preambleProc;
    }

    const Proc& preambleProc() const noexcept
    {
        return _preambleProc;
    }

    Size savedValsCount() const noexcept
    {
        return _savedValsCount;
    }

    void savedValsCount(const Size savedValsCount)
    {
        _savedValsCount = savedValsCount;
    }

private:
    const TraceType * const _traceType;
    DsPktProcs _dsPktProcs;
    Size _savedValsCount;
    Proc _preambleProc;
};

static inline ReadDataInstr& instrAsReadData(Instr& instr) noexcept
{
    return static_cast<ReadDataInstr&>(instr);
}

static inline BeginReadScopeInstr& instrAsBeginReadScope(Instr& instr) noexcept
{
    return static_cast<BeginReadScopeInstr&>(instr);
}

static inline BeginReadStructInstr& instrAsBeginReadStruct(Instr& instr) noexcept
{
    return static_cast<BeginReadStructInstr&>(instr);
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_PROC_HPP
