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
#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/fl-bool-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/metadata/nt-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/dl-blob-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/clk-type.hpp>
#include <yactfr/metadata/ert.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/trace-type.hpp>

#include "utils.hpp"

namespace yactfr {
namespace internal {

class BeginReadDlArrayInstr;
class BeginReadDlStrInstr;
class BeginReadScopeInstr;
class BeginReadSlArrayInstr;
class BeginReadSlStrInstr;
class BeginReadSlUuidArrayInstr;
class BeginReadDlBlobInstr;
class BeginReadSlBlobInstr;
class BeginReadSlUuidBlobInstr;
class BeginReadStructInstr;
class BeginReadVarSSelInstr;
class BeginReadVarUSelInstr;
class DecrRemainingElemsInstr;
class EndDsErPreambleProcInstr;
class EndDsPktPreambleProcInstr;
class EndErProcInstr;
class EndPktPreambleProcInstr;
class EndReadDataInstr;
class EndReadScopeInstr;
class Instr;
class ReadDataInstr;
class ReadFlBitArrayInstr;
class ReadFlBoolInstr;
class ReadFlFloatInstr;
class ReadFlSEnumInstr;
class ReadFlSIntInstr;
class ReadNtStrInstr;
class ReadFlUEnumInstr;
class ReadFlUIntInstr;
class ReadVlBitArrayInstr;
class SaveValInstr;
class SetCurIdInstr;
class SetDsIdInstr;
class SetDstInstr;
class SetDsInfoInstr;
class SetErtInstr;
class SetErInfoInstr;
class SetExpectedPktContentLenInstr;
class SetPktEndDefClkValInstr;
class SetPktMagicNumberInstr;
class SetPktOriginIndexInstr;
class SetExpectedPktTotalLenInstr;
class SetPktInfoInstr;
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

    virtual void visit(ReadFlBitArrayInstr& instr)
    {
    }

    virtual void visit(ReadFlBoolInstr& instr)
    {
    }

    virtual void visit(ReadFlSIntInstr& instr)
    {
    }

    virtual void visit(ReadFlUIntInstr& instr)
    {
    }

    virtual void visit(ReadFlFloatInstr& instr)
    {
    }

    virtual void visit(ReadFlSEnumInstr& instr)
    {
    }

    virtual void visit(ReadFlUEnumInstr& instr)
    {
    }

    virtual void visit(ReadVlBitArrayInstr& instr)
    {
    }

    virtual void visit(ReadNtStrInstr& instr)
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

    virtual void visit(BeginReadSlArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadSlUuidArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadDlArrayInstr& instr)
    {
    }

    virtual void visit(BeginReadSlStrInstr& instr)
    {
    }

    virtual void visit(BeginReadDlStrInstr& instr)
    {
    }

    virtual void visit(BeginReadSlBlobInstr& instr)
    {
    }

    virtual void visit(BeginReadSlUuidBlobInstr& instr)
    {
    }

    virtual void visit(BeginReadDlBlobInstr& instr)
    {
    }

    virtual void visit(BeginReadVarUSelInstr& instr)
    {
    }

    virtual void visit(BeginReadVarSSelInstr& instr)
    {
    }

    virtual void visit(EndReadDataInstr& instr)
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

    virtual void visit(SetErInfoInstr& instr)
    {
    }

    virtual void visit(SetDsIdInstr& instr)
    {
    }

    virtual void visit(SetDsInfoInstr& instr)
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

    virtual void visit(SetPktInfoInstr& instr)
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
    enum class Kind : unsigned int
    {
        UNSET,
        BEGIN_READ_DL_ARRAY,
        BEGIN_READ_DL_STR,
        BEGIN_READ_DL_BLOB,
        BEGIN_READ_SCOPE,
        BEGIN_READ_SL_ARRAY,
        BEGIN_READ_SL_STR,
        BEGIN_READ_SL_UUID_ARRAY,
        BEGIN_READ_SL_BLOB,
        BEGIN_READ_SL_UUID_BLOB,
        BEGIN_READ_STRUCT,
        BEGIN_READ_VAR_SSEL,
        BEGIN_READ_VAR_USEL,
        DECR_REMAINING_ELEMS,
        END_DS_ER_PREAMBLE_PROC,
        END_DS_PKT_PREAMBLE_PROC,
        END_ER_PROC,
        END_PKT_PREAMBLE_PROC,
        END_READ_SL_ARRAY,
        END_READ_DL_ARRAY,
        END_READ_SCOPE,
        END_READ_SL_STR,
        END_READ_DL_STR,
        END_READ_SL_BLOB,
        END_READ_DL_BLOB,
        END_READ_STRUCT,
        END_READ_VAR,
        READ_FL_BIT_ARRAY_A16_BE,
        READ_FL_BIT_ARRAY_A16_LE,
        READ_FL_BIT_ARRAY_A32_BE,
        READ_FL_BIT_ARRAY_A32_LE,
        READ_FL_BIT_ARRAY_A64_BE,
        READ_FL_BIT_ARRAY_A64_LE,
        READ_FL_BIT_ARRAY_A8,
        READ_FL_BIT_ARRAY_BE,
        READ_FL_BIT_ARRAY_LE,
        READ_FL_FLOAT_32_BE,
        READ_FL_FLOAT_32_LE,
        READ_FL_FLOAT_64_BE,
        READ_FL_FLOAT_64_LE,
        READ_FL_FLOAT_A32_BE,
        READ_FL_FLOAT_A32_LE,
        READ_FL_FLOAT_A64_BE,
        READ_FL_FLOAT_A64_LE,
        READ_FL_SENUM_A16_BE,
        READ_FL_SENUM_A16_LE,
        READ_FL_SENUM_A32_BE,
        READ_FL_SENUM_A32_LE,
        READ_FL_SENUM_A64_BE,
        READ_FL_SENUM_A64_LE,
        READ_FL_SENUM_A8,
        READ_FL_SENUM_BE,
        READ_FL_SENUM_LE,
        READ_FL_SINT_A16_BE,
        READ_FL_SINT_A16_LE,
        READ_FL_SINT_A32_BE,
        READ_FL_SINT_A32_LE,
        READ_FL_SINT_A64_BE,
        READ_FL_SINT_A64_LE,
        READ_FL_SINT_A8,
        READ_FL_SINT_BE,
        READ_FL_SINT_LE,
        READ_NT_STR,
        READ_FL_UENUM_A16_BE,
        READ_FL_UENUM_A16_LE,
        READ_FL_UENUM_A32_BE,
        READ_FL_UENUM_A32_LE,
        READ_FL_UENUM_A64_BE,
        READ_FL_UENUM_A64_LE,
        READ_FL_UENUM_A8,
        READ_FL_UENUM_BE,
        READ_FL_UENUM_LE,
        READ_FL_UINT_A16_BE,
        READ_FL_UINT_A16_LE,
        READ_FL_UINT_A32_BE,
        READ_FL_UINT_A32_LE,
        READ_FL_UINT_A64_BE,
        READ_FL_UINT_A64_LE,
        READ_FL_UINT_A8,
        READ_FL_UINT_BE,
        READ_FL_UINT_LE,
        READ_FL_BOOL_A16_BE,
        READ_FL_BOOL_A16_LE,
        READ_FL_BOOL_A32_BE,
        READ_FL_BOOL_A32_LE,
        READ_FL_BOOL_A64_BE,
        READ_FL_BOOL_A64_LE,
        READ_FL_BOOL_A8,
        READ_FL_BOOL_BE,
        READ_FL_BOOL_LE,
        READ_VL_BIT_ARRAY,
        READ_VL_UINT,
        READ_VL_SINT,
        READ_VL_UENUM,
        READ_VL_SENUM,
        SAVE_VAL,
        SET_CUR_ID,
        SET_DS_ID,
        SET_DS_INFO,
        SET_DST,
        SET_ERT,
        SET_ER_INFO,
        SET_PKT_CONTENT_LEN,
        SET_PKT_END_DEF_CLK_VAL,
        SET_PKT_MAGIC_NUMBER,
        SET_PKT_ORIGIN_INDEX,
        SET_PKT_TOTAL_LEN,
        SET_PKT_INFO,
        UPDATE_DEF_CLK_VAL,
        UPDATE_DEF_CLK_VAL_FL,
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
        return this->isReadFlBitArray() ||
               this->isReadVlBitArray() ||
               this->isReadNtStr() ||
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
               _theKind == Kind::BEGIN_READ_SL_ARRAY ||
               _theKind == Kind::BEGIN_READ_SL_UUID_ARRAY ||
               _theKind == Kind::BEGIN_READ_DL_ARRAY;
    }

    bool isReadFlBitArray() const noexcept
    {
        return _theKind == Kind::READ_FL_BIT_ARRAY_LE ||
               _theKind == Kind::READ_FL_BIT_ARRAY_BE ||
               _theKind == Kind::READ_FL_BIT_ARRAY_A8 ||
               _theKind == Kind::READ_FL_BIT_ARRAY_A16_LE ||
               _theKind == Kind::READ_FL_BIT_ARRAY_A32_LE ||
               _theKind == Kind::READ_FL_BIT_ARRAY_A64_LE ||
               _theKind == Kind::READ_FL_BIT_ARRAY_A16_BE ||
               _theKind == Kind::READ_FL_BIT_ARRAY_A32_BE ||
               _theKind == Kind::READ_FL_BIT_ARRAY_A64_BE ||
               this->isReadFlBool() ||
               this->isReadFlInt() ||
               this->isReadFlFloat();
    }

    bool isReadFlBool() const noexcept
    {
        return _theKind == Kind::READ_FL_BOOL_LE ||
               _theKind == Kind::READ_FL_BOOL_BE ||
               _theKind == Kind::READ_FL_BOOL_A8 ||
               _theKind == Kind::READ_FL_BOOL_A16_LE ||
               _theKind == Kind::READ_FL_BOOL_A32_LE ||
               _theKind == Kind::READ_FL_BOOL_A64_LE ||
               _theKind == Kind::READ_FL_BOOL_A16_BE ||
               _theKind == Kind::READ_FL_BOOL_A32_BE ||
               _theKind == Kind::READ_FL_BOOL_A64_BE;
    }

    bool isReadFlInt() const noexcept
    {
        return this->isReadFlSInt() || this->isReadFlUInt();
    }

    bool isReadFlSInt() const noexcept
    {
        return _theKind == Kind::READ_FL_SINT_LE ||
               _theKind == Kind::READ_FL_SINT_BE ||
               _theKind == Kind::READ_FL_SINT_A8 ||
               _theKind == Kind::READ_FL_SINT_A16_LE ||
               _theKind == Kind::READ_FL_SINT_A32_LE ||
               _theKind == Kind::READ_FL_SINT_A64_LE ||
               _theKind == Kind::READ_FL_SINT_A16_BE ||
               _theKind == Kind::READ_FL_SINT_A32_BE ||
               _theKind == Kind::READ_FL_SINT_A64_BE ||
               this->isReadFlSEnum();
    }

    bool isReadFlUInt() const noexcept
    {
        return _theKind == Kind::READ_FL_UINT_LE ||
               _theKind == Kind::READ_FL_UINT_BE ||
               _theKind == Kind::READ_FL_UINT_A8 ||
               _theKind == Kind::READ_FL_UINT_A16_LE ||
               _theKind == Kind::READ_FL_UINT_A32_LE ||
               _theKind == Kind::READ_FL_UINT_A64_LE ||
               _theKind == Kind::READ_FL_UINT_A16_BE ||
               _theKind == Kind::READ_FL_UINT_A32_BE ||
               _theKind == Kind::READ_FL_UINT_A64_BE ||
               this->isReadFlUEnum();
    }

    bool isReadFlFloat() const noexcept
    {
        return _theKind == Kind::READ_FL_FLOAT_32_LE ||
               _theKind == Kind::READ_FL_FLOAT_32_BE ||
               _theKind == Kind::READ_FL_FLOAT_A32_LE ||
               _theKind == Kind::READ_FL_FLOAT_A32_BE ||
               _theKind == Kind::READ_FL_FLOAT_64_LE ||
               _theKind == Kind::READ_FL_FLOAT_64_BE ||
               _theKind == Kind::READ_FL_FLOAT_A64_LE ||
               _theKind == Kind::READ_FL_FLOAT_A64_BE;
    }

    bool isReadFlEnum() const noexcept
    {
        return this->isReadFlSEnum() || this->isReadFlUEnum();
    }

    bool isReadFlSEnum() const noexcept
    {
        return _theKind == Kind::READ_FL_SENUM_LE ||
               _theKind == Kind::READ_FL_SENUM_BE ||
               _theKind == Kind::READ_FL_SENUM_A8 ||
               _theKind == Kind::READ_FL_SENUM_A16_LE ||
               _theKind == Kind::READ_FL_SENUM_A32_LE ||
               _theKind == Kind::READ_FL_SENUM_A64_LE ||
               _theKind == Kind::READ_FL_SENUM_A16_BE ||
               _theKind == Kind::READ_FL_SENUM_A32_BE ||
               _theKind == Kind::READ_FL_SENUM_A64_BE;
    }

    bool isReadFlUEnum() const noexcept
    {

        return _theKind == Kind::READ_FL_UENUM_LE ||
               _theKind == Kind::READ_FL_UENUM_BE ||
               _theKind == Kind::READ_FL_UENUM_A8 ||
               _theKind == Kind::READ_FL_UENUM_A16_LE ||
               _theKind == Kind::READ_FL_UENUM_A32_LE ||
               _theKind == Kind::READ_FL_UENUM_A64_LE ||
               _theKind == Kind::READ_FL_UENUM_A16_BE ||
               _theKind == Kind::READ_FL_UENUM_A32_BE ||
               _theKind == Kind::READ_FL_UENUM_A64_BE;
    }

    bool isReadVlBitArray() const noexcept
    {
        return _theKind == Kind::READ_VL_BIT_ARRAY ||
               this->isReadVlInt();
    }

    bool isReadVlInt() const noexcept
    {
        return this->isReadVlUInt() || this->isReadVlSInt();
    }

    bool isReadVlUInt() const noexcept
    {
        return _theKind == Kind::READ_VL_UINT ||
               _theKind == Kind::READ_VL_UENUM;
    }

    bool isReadVlSInt() const noexcept
    {
        return _theKind == Kind::READ_VL_SINT ||
               _theKind == Kind::READ_VL_SENUM;
    }

    bool isReadUInt() const noexcept
    {
        return this->isReadFlUInt() || this->isReadVlUInt();
    }

    bool isReadNtStr() const noexcept
    {
        return _theKind == Kind::READ_NT_STR;
    }

    bool isBeginReadSlArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_SL_ARRAY ||
               _theKind == Kind::BEGIN_READ_SL_UUID_ARRAY;
    }

    bool isBeginReadSlStr() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_SL_STR;
    }

    bool isBeginReadSlUuidArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_SL_UUID_ARRAY;
    }

    bool isBeginReadDlArray() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_DL_ARRAY;
    }

    bool isBeginReadDlStr() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_DL_STR;
    }

    bool isBeginReadSlBlob() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_SL_BLOB;
    }

    bool isBeginReadSlUuidBlob() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_SL_UUID_BLOB;
    }

    bool isBeginReadDlBlob() const noexcept
    {
        return _theKind == Kind::BEGIN_READ_DL_BLOB;
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

    bool isEndReadData() const noexcept
    {
        return _theKind == Kind::END_READ_STRUCT ||
               _theKind == Kind::END_READ_SL_ARRAY ||
               _theKind == Kind::END_READ_DL_ARRAY ||
               _theKind == Kind::END_READ_SL_STR ||
               _theKind == Kind::END_READ_DL_STR ||
               _theKind == Kind::END_READ_SL_BLOB ||
               _theKind == Kind::END_READ_DL_BLOB ||
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
 * be used later (for the length of a dynamic-length array/string or for
 * the selector of a variant).
 */
class SaveValInstr final :
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
class SetPktEndDefClkValInstr final :
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
 * "Read fixed-length bit array" procedure instruction.
 */
class ReadFlBitArrayInstr :
    public ReadDataInstr
{
protected:
    explicit ReadFlBitArrayInstr(Kind kind, const StructureMemberType *memberType,
                                 const DataType& dt);

public:
    explicit ReadFlBitArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    unsigned int len() const noexcept
    {
        return _len;
    }

    ByteOrder bo() const noexcept
    {
        return _bo;
    }

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FixedLengthBitArrayType& flBitArrayType() const noexcept
    {
        return static_cast<const FixedLengthBitArrayType&>(this->dt());
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
 * "Read fixed-length boolean" procedure instruction.
 */
class ReadFlBoolInstr :
    public ReadFlBitArrayInstr
{
public:
    explicit ReadFlBoolInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FixedLengthBooleanType& boolType() const noexcept
    {
        return static_cast<const FixedLengthBooleanType&>(this->dt());
    }
};

/*
 * "Read fixed-length integer" procedure instruction.
 */
class ReadFlIntInstr :
    public ReadFlBitArrayInstr
{
protected:
    explicit ReadFlIntInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

public:
    explicit ReadFlIntInstr(const StructureMemberType *memberType, const DataType& dt);

    const FixedLengthIntegerType& intType() const noexcept
    {
        return static_cast<const FixedLengthIntegerType&>(this->dt());
    }
};

/*
 * "Read fixed-length signed integer" procedure instruction.
 */
class ReadFlSIntInstr :
    public ReadFlIntInstr
{
protected:
    explicit ReadFlSIntInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

public:
    explicit ReadFlSIntInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FixedLengthSignedIntegerType& sIntType() const noexcept
    {
        return static_cast<const FixedLengthSignedIntegerType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read fixed-length unsigned integer" procedure instruction.
 */
class ReadFlUIntInstr :
    public ReadFlIntInstr
{
protected:
    explicit ReadFlUIntInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

public:
    explicit ReadFlUIntInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FixedLengthUnsignedIntegerType& uIntType() const noexcept
    {
        return static_cast<const FixedLengthUnsignedIntegerType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read fixed-length floating point number" procedure instruction.
 */
class ReadFlFloatInstr final :
    public ReadFlBitArrayInstr
{
public:
    explicit ReadFlFloatInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FixedLengthFloatingPointNumberType& floatType() const noexcept
    {
        return static_cast<const FixedLengthFloatingPointNumberType&>(this->dt());
    }
};

/*
 * "Read fixed-length signed enumeration" procedure instruction.
 */
class ReadFlSEnumInstr final :
    public ReadFlSIntInstr
{
public:
    explicit ReadFlSEnumInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FixedLengthSignedEnumerationType& sEnumType() const noexcept
    {
        return static_cast<const FixedLengthSignedEnumerationType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read fixed-length unsigned enumeration" procedure instruction.
 */
class ReadFlUEnumInstr final :
    public ReadFlUIntInstr
{
public:
    explicit ReadFlUEnumInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const FixedLengthUnsignedEnumerationType& uEnumType() const noexcept
    {
        return static_cast<const FixedLengthUnsignedEnumerationType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read variable-length bit array" procedure instruction.
 */
class ReadVlBitArrayInstr :
    public ReadDataInstr
{
public:
    explicit ReadVlBitArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const VariableLengthBitArrayType& vlBitArrayType() const noexcept
    {
        return static_cast<const VariableLengthBitArrayType&>(this->dt());
    }

private:
    std::string _toStr(Size indent = 0) const override;
};

/*
 * "Read null-terminated string" procedure instruction.
 */
class ReadNtStrInstr final :
    public ReadDataInstr
{
public:
    explicit ReadNtStrInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const NullTerminatedStringType& strType() const noexcept
    {
        return static_cast<const NullTerminatedStringType&>(this->dt());
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
 * "End reading data" procedure instruction.
 *
 * If the kind of this instruction is `END_READ_STRUCT`, then the VM
 * must stop executing the current procedure and continue executing the
 * parent procedure.
 *
 * For all instruction kinds, this instruction requires the VM to set an
 * `EndElement` as the current element.
 */
class EndReadDataInstr :
    public ReadDataInstr
{
public:
    explicit EndReadDataInstr(Kind kind, const StructureMemberType *memberType, const DataType& dt);

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
class BeginReadStructInstr final :
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
class BeginReadScopeInstr final :
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
class EndReadScopeInstr final :
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
 * "Begin reading static-length array" procedure instruction.
 *
 * The VM must execute the subprocedure `len()` times.
 */
class BeginReadSlArrayInstr :
    public BeginReadCompoundInstr
{
protected:
    explicit BeginReadSlArrayInstr(Kind kind, const StructureMemberType *memberType,
                                   const DataType& dt);

public:
    explicit BeginReadSlArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StaticLengthArrayType& slArrayType() const noexcept
    {
        return static_cast<const StaticLengthArrayType&>(this->dt());
    }

    Size len() const noexcept
    {
        return _len;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const Size _len;
};

/*
 * "Begin reading static-length string" procedure instruction.
 *
 * maxLen() indicates the maximum length (bytes) of the static-length
 * string to read.
 */
class BeginReadSlStrInstr final :
    public ReadDataInstr
{
public:
    explicit BeginReadSlStrInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StaticLengthStringType& slStrType() const noexcept
    {
        return static_cast<const StaticLengthStringType&>(this->dt());
    }

    Size maxLen() const noexcept
    {
        return _maxLen;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const Size _maxLen;
};

/*
 * "Begin reading static-length UUID array" procedure instruction.
 *
 * This is a specialized instruction to read the 16 trace type UUID
 * bytes of a packet header to emit `TraceTypeUuidElement`.
 */
class BeginReadSlUuidArrayInstr final :
    public BeginReadSlArrayInstr
{
public:
    explicit BeginReadSlUuidArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Begin reading dynamic-length array" procedure instruction.
 *
 * The VM must use lenPos() to retrieve the saved value which contains
 * the length of the dynamic-length array, and then execute the
 * subprocedure this number of times.
 */
class BeginReadDlArrayInstr final :
    public BeginReadCompoundInstr
{
public:
    explicit BeginReadDlArrayInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const DynamicLengthArrayType& dlArrayType() const noexcept
    {
        return static_cast<const DynamicLengthArrayType&>(this->dt());
    }

    const Index lenPos() const noexcept
    {
        return _lenPos;
    }

    void lenPos(const Index lenPos) noexcept
    {
        _lenPos = lenPos;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    Index _lenPos = -1ULL;
};

/*
 * "Begin reading dynamic-length string" procedure instruction.
 *
 * The VM must use maxLenPos() to retrieve the saved value which
 * contains the maximum length (bytes) of the dynamic-length string.
 */
class BeginReadDlStrInstr final :
    public ReadDataInstr
{
public:
    explicit BeginReadDlStrInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const DynamicLengthStringType& dlStrType() const noexcept
    {
        return static_cast<const DynamicLengthStringType&>(this->dt());
    }

    const Index maxLenPos() const noexcept
    {
        return _maxLenPos;
    }

    void maxLenPos(const Index maxLenPos) noexcept
    {
        _maxLenPos = maxLenPos;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    Index _maxLenPos = -1ULL;
};

/*
 * "Begin reading static-length BLOB" procedure instruction.
 *
 * len() indicates the length (bytes) of the static-length BLOB to read.
 */
class BeginReadSlBlobInstr :
    public ReadDataInstr
{
protected:
    explicit BeginReadSlBlobInstr(Kind kind, const StructureMemberType *memberType,
                                  const DataType& dt);

public:
    explicit BeginReadSlBlobInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const StaticLengthBlobType& slBlobType() const noexcept
    {
        return static_cast<const StaticLengthBlobType&>(this->dt());
    }

    Size len() const noexcept
    {
        return _len;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    const Size _len;
};

/*
 * "Begin reading static-length UUID BLOB" procedure instruction.
 *
 * This is a specialized instruction to read the 16 UUID bytes of a
 * packet header to emit `TraceTypeUuidElement`.
 */
class BeginReadSlUuidBlobInstr final :
    public BeginReadSlBlobInstr
{
public:
    explicit BeginReadSlUuidBlobInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Begin reading dynamic-length BLOB" procedure instruction.
 *
 * The VM must use lenPos() to retrieve the saved value which contains
 * the length (bytes) of the dynamic-length BLOB.
 */
class BeginReadDlBlobInstr final :
    public ReadDataInstr
{
public:
    explicit BeginReadDlBlobInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }

    const DynamicLengthBlobType& dlBlobType() const noexcept
    {
        return static_cast<const DynamicLengthBlobType&>(this->dt());
    }

    const Index lenPos() const noexcept
    {
        return _lenPos;
    }

    void lenPos(const Index lenPos) noexcept
    {
        _lenPos = lenPos;
    }

private:
    std::string _toStr(Size indent = 0) const override;

private:
    Index _lenPos = -1ULL;
};

/*
 * Option of a "read variant" procedure instruction.
 */
template <typename VarTypeOptT>
class ReadVarInstrOpt final
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
 * The VM must use selPos() to retrieve the saved value which is the
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

class BeginReadVarUSelInstr final :
    public BeginReadVarInstr<VariantWithUnsignedSelectorType, Instr::Kind::BEGIN_READ_VAR_USEL>
{
public:
    explicit BeginReadVarUSelInstr(const StructureMemberType *memberType, const DataType& dt);

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

class BeginReadVarSSelInstr final :
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
class SetCurIdInstr final :
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
class SetDstInstr final :
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
class SetErtInstr final :
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
class SetPktOriginIndexInstr final :
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
class SetDsIdInstr final :
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
 * "Set data stream info" procedure instruction.
 *
 * This instruction requires the VM to set and emit the data stream
 * info element.
 */
class SetDsInfoInstr final :
    public Instr
{
public:
    explicit SetDsInfoInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set packet info" procedure instruction.
 *
 * This instruction requires the VM to set and emit the packet info
 * element.
 */
class SetPktInfoInstr final :
    public Instr
{
public:
    explicit SetPktInfoInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Set event record info" procedure instruction.
 *
 * This instruction requires the VM to set and emit the event record
 * info element.
 */
class SetErInfoInstr final :
    public Instr
{
public:
    explicit SetErInfoInstr();

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
class SetExpectedPktTotalLenInstr final :
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
class SetExpectedPktContentLenInstr final :
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
 * clock from the last decoded unsigned integer value.
 */
class UpdateDefClkValInstr :
    public Instr
{
protected:
    explicit UpdateDefClkValInstr(Instr::Kind kind);

public:
    explicit UpdateDefClkValInstr();

    void accept(InstrVisitor& visitor) override
    {
        visitor.visit(*this);
    }
};

/*
 * "Update clock value from fixed-length unsigned integer" procedure
 * instruction.
 *
 * This instruction requires the VM to update the value of the default
 * clock from the last decoded fixed-length unsigned integer value.
 */
class UpdateDefClkValFlInstr final :
    public UpdateDefClkValInstr
{
public:
    explicit UpdateDefClkValFlInstr(Size len);

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
class SetPktMagicNumberInstr final :
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
class EndPktPreambleProcInstr final :
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
class EndDsPktPreambleProcInstr final :
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
class EndDsErPreambleProcInstr final :
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
class EndErProcInstr final :
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
class DecrRemainingElemsInstr final :
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
class ErProc final
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
class DsPktProc final
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
class PktProc final
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
