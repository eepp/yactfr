/*
 * Copyright (C) 2016-2025 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms of the
 * MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_PGM_HPP
#define YACTFR_INTERNAL_PGM_HPP

/*
 * This is the program and instruction system for the yactfr VM.
 *
 * CONCEPT
 * ━━━━━━━
 * Some definitions of the concept:
 *
 * Program:
 *     A sequence of program nucleotides in memory.
 *
 *     A program doesn't contain its own length, but an outer
 *     instruction field may (if needed).
 *
 * Program nucleotide:
 *     A single, 64-bit element within a program.
 *
 * Instruction:
 *     One or more contiguous program nucleotides forming a unit which
 *     the yactfr VM understands.
 *
 *     An instruction may itself contain one or more programs.
 *
 * It might seem weird that an instruction may contain a program, but
 * because the yactfr VM is very specialized, we don't need
 * general-purpose instructions such as "push onto stack", "jump
 * conditionally", or "increment register". The VM state, together with
 * a loaded program and a current program position, is enough to decide
 * what to do next. For example, a "read static-length array"
 * instruction contains a program to read its element and the number of
 * times to execute it.
 *
 * IMPLEMENTATION
 * ━━━━━━━━━━━━━━
 * First, it's important to note that many parts of this implementation
 * rely on compiler specifics. This is why there are many static
 * assertions to make sure, as much as possible, that the memory layout
 * of instances of the classes below is expected.
 *
 * The fundamental type is `PgmNucleo` (program nucleotide). A
 * `PgmNucleo` is a union of 64-bit integers and an array of eight
 * bytes. Various static assertions make sure that its instance size
 * really is eight bytes and that it's possible to tightly pack them.
 *
 * A `PgmNucleos` instance is a simple, dumb container of nucleotides. A
 * `PgmNucleos` instance is really only used to build and own programs
 * at the top level of the VM. The instructions all work with program
 * _views_.
 *
 * A `PgmView` (program view) is a view of a program (sequence of
 * nucleotides). A `PgmView` is really lightweight: it only holds a
 * pointer to the first nucleotide of a program in memory. It doesn't
 * contain the program length as this is not always required. The class
 * offers the begin() method as well as program nucleotide and
 * instruction access.
 *
 * Instruction
 * ───────────
 * An instruction is an object which the VM can execute.
 *
 * The design of this system is such that:
 *
 * • `InstrBase` object contains a single program nucleotide.
 *
 *   It uses one byte of said nucleotide to store the opcode; the seven
 *   others are free for derived instructions.
 *
 * • Each instruction class inherits `InstrBase`, possibly adding more
 *   nucleotide members to contain more data.
 *
 *   A derived instruction may also write to and read from its first
 *   nucleotide, as long as it doesn't overwrite the opcode.
 *
 * • What an actual instruction class instance contains is called its
 *   static part. Call its specific staticLen() method to get the number
 *   of nucleotides of its static part.
 *
 * • You can cast any program nucleotide to an instruction instance to
 *   read its static part.
 *
 * • Any instruction may conceptually contain dynamic data after its
 *   static part, for example integer ranges or a program.
 *
 *   This is not part of the instruction object itself, but since an
 *   instruction object knows the address of its first nucleotide (the
 *   value of `this`, basically), it can reach its dynamic data and
 *   present it safely at zero cost.
 *
 *   Call the specific len() method of the instruction to get its total
 *   number of nucleotides.
 *
 * What a VM repeatedly needs to do when reading a program is, as long
 * as there are available nucleotides:
 *
 * 1. Use PgmView::instrBaseAt() to get the current nucleotide as an
 *    `InstrBase` reference A so as to get the opcode (`A.opcode()`).
 *
 * 2. Once the opcode is known and therefore also the corresponding
 *    instruction class IC, use one of the `A.as*()` methods to get the
 *    same current nucleotide as an IC reference B.
 *
 * 3. Advance to the next instruction using `B.len()`.
 *
 *    Do NOT use `A.len()` because this is always one (`InstrBase`
 *    contains a single nucleotide, and there's no virtual table
 *    in there).
 *
 * The comment above each instruction class below shows the expected
 * memory layout, including dynamic parts.
 *
 * Build a program
 * ───────────────
 * To build a program, append instructions to it with the specific
 * appendToPgmNucleos() static methods, for example:
 *
 *     PgmNucleos nucleos;
 *
 *     {
 *         PgmNucleos structNucleos;
 *
 *         ReadDataInstr::appendToPgmNucleos(structNucleos,
 *                                           InstrBase::Opcode::ReadFlSIntA32Le,
 *                                           someMemberType, someDataType);
 *         ReadDataInstr::appendToPgmNucleos(structNucleos,
 *                                           InstrBase::Opcode::ReadNtStrUtf32Be,
 *                                           someOtherMemberType,
 *                                           someOtherDataType);
 *         ReadStructInstr::appendToPgmNucleos(nucleos, nullptr, structDt,
 *                                             structNucleos);
 *     }
 *
 *     InstrBase::appendToPgmNucleos(nucleos, InstrBase::Opcode::SetPktInfo);
 *
 * In this last example, all the nucleotides of `structNucleos` are now
 * part of `nucleos`, therefore it's safe to destroy the
 * temporary `structNucleos`.
 *
 * There are no public instruction constructors: the
 * appendToPgmNucleos() methods use protected and private ones to build
 * the static part of the instruction to append.
 */

#include <vector>
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <array>
#include <cassert>
#include <type_traits>
#include <unordered_map>
#include <boost/noncopyable.hpp>
#include <boost/optional/optional.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/fwd.hpp>
#include <yactfr/metadata/int-range.hpp>
#include <yactfr/metadata/int-range-set.hpp>
#include <yactfr/metadata/opt-type.hpp>
#include <yactfr/metadata/var-type.hpp>

#include "vendor/wise-enum/wise_enum.h"

namespace yactfr {
namespace internal {

/*
 * The 64-bit fundamental element of a program.
 *
 * An instruction spans one or more nucleotides.
 */
union PgmNucleo
{
    explicit PgmNucleo() noexcept :
        u {0}
    {
    }

    explicit PgmNucleo(const std::uint64_t val) noexcept :
        u {val}
    {
    }

    explicit PgmNucleo(const std::int64_t val) noexcept :
        i {val}
    {
    }

    std::array<std::uint8_t, 8> bytes;
    std::uint64_t u;
    std::int64_t i;
};

// a few checks to make sure we're on the right track
static_assert(sizeof(PgmNucleo) == 8, "Size of a `PgmNucleo` instance is 8 bytes");
static_assert(alignof(PgmNucleo) <= 8, "Alignment of a `PgmNucleo` instance is at most 8 bytes");
static_assert(sizeof(PgmNucleo[2]) == 2 * sizeof(PgmNucleo),
              "Two contiguous `PgmNucleo` instances are packed");
static_assert(sizeof(std::uintptr_t) <= sizeof(PgmNucleo),
              "A `PgmNucleo` instance may contain an entire object address");

/*
 * Nucleotide sequence.
 */
using PgmNucleos = std::vector<PgmNucleo>;

// needed for PgmView::instrBaseAt()
class InstrBase;

/*
 * A view of a program.
 *
 * begin() points to the beginning of the viewed program.
 *
 * Get a single nucleotide with operator[]().
 *
 * Get an `InstrBase` reference for some index with instrBaseAt().
 *
 * instrAt() is like instrBaseAt(), but casts to a specific
 * instruction type.
 */
class PgmView final
{
public:
    /*
     * Builds a view of the program starting at `begin`.
     */
    explicit PgmView(const PgmNucleo * const begin) noexcept :
        _begin {begin}
    {
    }

    /*
     * Builds a view of the nucleotide sequence `nucleos`.
     *
     * Intentionally not explicit.
     */
    PgmView(const PgmNucleos& nucleos) noexcept :
        PgmView {nucleos.data()}
    {
    }

    /*
     * First nucleotide of the viewed program.
     */
    const PgmNucleo *begin() const noexcept
    {
        return _begin;
    }

    /*
     * Returns the nucleotide at the index `index` within the
     * viewed program.
     */
    const PgmNucleo& operator[](const Index index) const noexcept
    {
        return *(_begin + index);
    }

    /*
     * Returns the nucleotide at the index `index`, within the
     * instruction nucleotides of the viewed program, as an
     * `InstrBase` reference.
     *
     * You may use the InstrBase::as*() methods on the returned
     * reference depending on InstrBase::opcode().
     */
    const InstrBase& instrBaseAt(Index index) const noexcept;

    /*
     * Like instrBaseAt(), but also casts the returned reference
     * to `const InstrT&`.
     *
     * You must be sure that the instruction base of the nucleotide at
     * index `index` has the effective type `InstrT`.
     */
    template <typename InstrT>
    const InstrT& instrAt(const Index index) const noexcept
    {
        return static_cast<const InstrBase&>(this->instrBaseAt(index));
    }

    /*
     * Appends (copies) the first `len` nucleotides of this viewed program
     * to the nucleotide sequence `nucleos`.
     */
    void appendToPgmNucleos(PgmNucleos& nucleos, const Size len) const
    {
        for (Index i = 0U; i < len; ++i) {
            nucleos.push_back((*this)[i]);
        }
    }

private:
    const PgmNucleo *_begin;
};

// forward declarations needed for the InstrBase::as*() methods
class ReadDataInstr;
class ReadDlArrayInstr;
class ReadDlDataInstr;
class ReadOddFlBitArrayInstr;
class ReadOptWithBoolSelInstr;
class ReadScopeInstr;
class ReadSlArrayInstr;
class ReadSlDataInstr;
class ReadStructInstr;
class SaveCurIntInstr;
class UpdateDefClkValFlFromCurIntInstr;

template <typename, std::uint8_t, std::uint8_t>
class ReadOptWithIntSelInstr;

template <typename, std::uint8_t, std::uint8_t>
class ReadVarInstr;

/*
 * The base of any instruction.
 *
 * An instruction base contains a single (64-bit) program nucleotide,
 * itself containing a single-byte opcode (of type `InstrBase::Opcode`).
 * Its data bytes 6 to 0 remain available.
 *
 * The big-endian memory layout of an instruction base is:
 *
 *               ┏━━━━━━━━━━━━━━━┯━━━━━━┓
 *     Nucleo 0: ┃ Opcode [7, 7] │ Free ┃
 *               ┗━━━━━━━━━━━━━━━┷━━━━━━┛
 *
 * You can't publicly build an `InstrBase` object: use
 * appendToPgmNucleos() to append one to a nucleotide sequence. The
 * appendToPgmNucleos() methods take care of also appending their own
 * `InstrBase::Opcode::EndRead*` instruction.
 *
 * Get the corresponding nucleotide address with asNucleo().
 *
 * Get an `InstrBase` reference from a nucleotide address
 * with fromNucleo().
 *
 * A derived instruction class may write to and read from the non-opcode
 * bytes of the underlying nucleotide with the protected _writeToBase()
 * and _readFromBase() methods. Those ones ensure that the opcode is
 * protected at compile time.
 *
 * Any derived instruction class must implement, if different
 * from `InstrBase`:
 *
 * staticLen():
 *     Number of program nucleotides which the static part of the
 *     instruction spans.
 *
 *     Use the _staticLen() helper.
 *
 *     Must be `static constexpr`.
 *
 * A derived instruction class may use the _appendStaticToPgmNucleos()
 * helper to append the static part of itself within its own
 * appendToPgmNucleos() method.
 */
class InstrBase :
    boost::noncopyable
{
public:
    /*
     * Opcode of any instruction.
     *
     * Comments show the instruction classes which correspond to
     * specific opcodes.
     */
    WISE_ENUM_CLASS_MEMBER((Opcode, std::uint8_t),
        // `ReadDataInstr`
        ReadFlBitArrayA16Be,
        ReadFlBitArrayA16BeRev,
        ReadFlBitArrayA16Le,
        ReadFlBitArrayA16LeRev,
        ReadFlBitArrayA32Be,
        ReadFlBitArrayA32BeRev,
        ReadFlBitArrayA32Le,
        ReadFlBitArrayA32LeRev,
        ReadFlBitArrayA64Be,
        ReadFlBitArrayA64BeRev,
        ReadFlBitArrayA64Le,
        ReadFlBitArrayA64LeRev,
        ReadFlBitArrayA8,
        ReadFlBitArrayA8Rev,
        ReadFlBitMapA16Be,
        ReadFlBitMapA16BeRev,
        ReadFlBitMapA16Le,
        ReadFlBitMapA16LeRev,
        ReadFlBitMapA32Be,
        ReadFlBitMapA32BeRev,
        ReadFlBitMapA32Le,
        ReadFlBitMapA32LeRev,
        ReadFlBitMapA64Be,
        ReadFlBitMapA64BeRev,
        ReadFlBitMapA64Le,
        ReadFlBitMapA64LeRev,
        ReadFlBitMapA8,
        ReadFlBitMapA8Rev,
        ReadFlBoolA16Be,
        ReadFlBoolA16BeRev,
        ReadFlBoolA16Le,
        ReadFlBoolA16LeRev,
        ReadFlBoolA32Be,
        ReadFlBoolA32BeRev,
        ReadFlBoolA32Le,
        ReadFlBoolA32LeRev,
        ReadFlBoolA64Be,
        ReadFlBoolA64BeRev,
        ReadFlBoolA64Le,
        ReadFlBoolA64LeRev,
        ReadFlBoolA8,
        ReadFlBoolA8Rev,
        ReadFlFloatA32Be,
        ReadFlFloatA32BeRev,
        ReadFlFloatA32Le,
        ReadFlFloatA32LeRev,
        ReadFlFloatA64Be,
        ReadFlFloatA64BeRev,
        ReadFlFloatA64Le,
        ReadFlFloatA64LeRev,
        ReadFlSIntA16Be,
        ReadFlSIntA16BeRev,
        ReadFlSIntA16Le,
        ReadFlSIntA16LeRev,
        ReadFlSIntA32Be,
        ReadFlSIntA32BeRev,
        ReadFlSIntA32Le,
        ReadFlSIntA32LeRev,
        ReadFlSIntA64Be,
        ReadFlSIntA64BeRev,
        ReadFlSIntA64Le,
        ReadFlSIntA64LeRev,
        ReadFlSIntA8,
        ReadFlSIntA8Rev,
        ReadFlUIntA16Be,
        ReadFlUIntA16BeRev,
        ReadFlUIntA16Le,
        ReadFlUIntA16LeRev,
        ReadFlUIntA32Be,
        ReadFlUIntA32BeRev,
        ReadFlUIntA32Le,
        ReadFlUIntA32LeRev,
        ReadFlUIntA64Be,
        ReadFlUIntA64BeRev,
        ReadFlUIntA64Le,
        ReadFlUIntA64LeRev,
        ReadFlUIntA8,
        ReadFlUIntA8Rev,
        ReadNtStrUtf16,
        ReadNtStrUtf32,
        ReadNtStrUtf8,
        ReadVlSInt,
        ReadVlUInt,

        // `ReadOddFlBitArrayInstr`
        ReadFlBitArrayBe,
        ReadFlBitArrayBeRev,
        ReadFlBitArrayLe,
        ReadFlBitArrayLeRev,
        ReadFlBitMapBe,
        ReadFlBitMapBeRev,
        ReadFlBitMapLe,
        ReadFlBitMapLeRev,
        ReadFlBoolBe,
        ReadFlBoolBeRev,
        ReadFlBoolLe,
        ReadFlBoolLeRev,
        ReadFlFloat32Be,
        ReadFlFloat32BeRev,
        ReadFlFloat32Le,
        ReadFlFloat32LeRev,
        ReadFlFloat64Be,
        ReadFlFloat64BeRev,
        ReadFlFloat64Le,
        ReadFlFloat64LeRev,
        ReadFlSIntBe,
        ReadFlSIntBeRev,
        ReadFlSIntLe,
        ReadFlSIntLeRev,
        ReadFlUIntBe,
        ReadFlUIntBeRev,
        ReadFlUIntLe,
        ReadFlUIntLeRev,

        // `ReadSlDataInstr`
        ReadSlBlob,
        ReadSlStr,
        ReadSlUuidBlob,

        // `ReadSlArrayInstr`
        ReadSlArray,
        ReadSlUuidArray,

        // `ReadDlDataInstr`
        ReadDlBlob,
        ReadDlStr,

        // `ReadDlArrayInstr`
        ReadDlArray,

        // `ReadOptWithBoolSelInstr`
        ReadOptWithBoolSel,

        // `ReadOptWithSIntSelInstr`
        ReadOptWithSIntSel,

        // `ReadOptWithUIntSelInstr`
        ReadOptWithUIntSel,

        // `ReadStructInstr`
        ReadStruct,

        // `ReadVarWithSIntSelInstr`
        ReadVarWithSIntSel,

        // `ReadVarWithUIntSelInstr`
        ReadVarWithUIntSel,

        // `ReadScopeInstr`
        ReadScope,

        // `SaveCurIntInstr`
        SaveCurInt,

        // `UpdateDefClkValFlFromCurIntInstr`
        UpdateDefClkValFlFromCurInt,

        // `InstrBase`
        EndReadArrayElem,
        EndReadDlArray,
        EndReadDlBlob,
        EndReadDlStr,
        EndReadDsErPreamble,
        EndReadDsPktPreamble,
        EndReadEr,
        EndReadOptWithBoolSel,
        EndReadOptWithSIntSel,
        EndReadOptWithUIntSel,
        EndReadPktPreamble,
        EndReadScope,
        EndReadSlArray,
        EndReadSlUuidArray,
        EndReadSlBlob,
        EndReadSlStr,
        EndReadSlUuidBlob,
        EndReadStruct,
        EndReadVarOpt,
        EndReadVarWithSIntSel,
        EndReadVarWithUIntSel,
        SetCurTypeIdFromCurInt,
        SetDsIdFromCurInt,
        SetDsInfo,
        SetDstFromCurTypeId,
        SetDstFromUnique,
        SetErInfo,
        SetErtFromCurTypeId,
        SetErtFromUnique,
        SetPktContentLenFromCurInt,
        SetPktDiscErCounterSnapFromCurInt,
        SetPktEndDefClkValFromCurInt,
        SetPktInfo,
        SetPktMagicNumberFromCurInt,
        SetPktSeqNumFromCurInt,
        SetPktTotalLenFromCurInt,
        UpdateDefClkValVlFromCurInt
    )

protected:
    /*
     * A byte range, from `upper` to `lower`, both included.
     *
     * For example, `{3, 1}` is the 3-byte range from byte 3 to byte 1.
     */
    struct _tByteRange final
    {
        Index upper;
        Index lower;
    };

private:
    // opcode byte range
    static constexpr _tByteRange _opByteRange() noexcept
    {
        return {7, 7};
    }

protected:
    /*
     * Builds an instruction base having the opcode `opcode`.
     */
    explicit InstrBase(Opcode opcode) noexcept;

    template <typename InstrT>
    static constexpr Size _staticLen() noexcept
    {
        return sizeof(InstrT) / sizeof(PgmNucleo);
    }

public:
    /*
     * Opcode of this instruction.
     */
    Opcode opcode() const noexcept
    {
        return static_cast<Opcode>(this->_unsafeReadDataU<_opByteRange().upper,
                                                          _opByteRange().lower>());
    }

    /*
     * Returns whether or not this instruction is a "read
     * data" instruction.
     */
    bool isReadData() const noexcept
    {
        if (this->isReadOddFlBitArray() || this->isReadSlData() || this->isReadDlData()) {
            return true;
        }

        switch (this->opcode()) {
        case Opcode::ReadFlBitArrayA16Be:
        case Opcode::ReadFlBitArrayA16BeRev:
        case Opcode::ReadFlBitArrayA16Le:
        case Opcode::ReadFlBitArrayA16LeRev:
        case Opcode::ReadFlBitArrayA32Be:
        case Opcode::ReadFlBitArrayA32BeRev:
        case Opcode::ReadFlBitArrayA32Le:
        case Opcode::ReadFlBitArrayA32LeRev:
        case Opcode::ReadFlBitArrayA64Be:
        case Opcode::ReadFlBitArrayA64BeRev:
        case Opcode::ReadFlBitArrayA64Le:
        case Opcode::ReadFlBitArrayA64LeRev:
        case Opcode::ReadFlBitArrayA8:
        case Opcode::ReadFlBitArrayA8Rev:
        case Opcode::ReadFlBitMapA16Be:
        case Opcode::ReadFlBitMapA16BeRev:
        case Opcode::ReadFlBitMapA16Le:
        case Opcode::ReadFlBitMapA16LeRev:
        case Opcode::ReadFlBitMapA32Be:
        case Opcode::ReadFlBitMapA32BeRev:
        case Opcode::ReadFlBitMapA32Le:
        case Opcode::ReadFlBitMapA32LeRev:
        case Opcode::ReadFlBitMapA64Be:
        case Opcode::ReadFlBitMapA64BeRev:
        case Opcode::ReadFlBitMapA64Le:
        case Opcode::ReadFlBitMapA64LeRev:
        case Opcode::ReadFlBitMapA8:
        case Opcode::ReadFlBitMapA8Rev:
        case Opcode::ReadFlBoolA16Be:
        case Opcode::ReadFlBoolA16BeRev:
        case Opcode::ReadFlBoolA16Le:
        case Opcode::ReadFlBoolA16LeRev:
        case Opcode::ReadFlBoolA32Be:
        case Opcode::ReadFlBoolA32BeRev:
        case Opcode::ReadFlBoolA32Le:
        case Opcode::ReadFlBoolA32LeRev:
        case Opcode::ReadFlBoolA64Be:
        case Opcode::ReadFlBoolA64BeRev:
        case Opcode::ReadFlBoolA64Le:
        case Opcode::ReadFlBoolA64LeRev:
        case Opcode::ReadFlBoolA8:
        case Opcode::ReadFlBoolA8Rev:
        case Opcode::ReadFlFloatA32Be:
        case Opcode::ReadFlFloatA32BeRev:
        case Opcode::ReadFlFloatA32Le:
        case Opcode::ReadFlFloatA32LeRev:
        case Opcode::ReadFlFloatA64Be:
        case Opcode::ReadFlFloatA64BeRev:
        case Opcode::ReadFlFloatA64Le:
        case Opcode::ReadFlFloatA64LeRev:
        case Opcode::ReadFlSIntA16Be:
        case Opcode::ReadFlSIntA16BeRev:
        case Opcode::ReadFlSIntA16Le:
        case Opcode::ReadFlSIntA16LeRev:
        case Opcode::ReadFlSIntA32Be:
        case Opcode::ReadFlSIntA32BeRev:
        case Opcode::ReadFlSIntA32Le:
        case Opcode::ReadFlSIntA32LeRev:
        case Opcode::ReadFlSIntA64Be:
        case Opcode::ReadFlSIntA64BeRev:
        case Opcode::ReadFlSIntA64Le:
        case Opcode::ReadFlSIntA64LeRev:
        case Opcode::ReadFlSIntA8:
        case Opcode::ReadFlSIntA8Rev:
        case Opcode::ReadFlUIntA16Be:
        case Opcode::ReadFlUIntA16BeRev:
        case Opcode::ReadFlUIntA16Le:
        case Opcode::ReadFlUIntA16LeRev:
        case Opcode::ReadFlUIntA32Be:
        case Opcode::ReadFlUIntA32BeRev:
        case Opcode::ReadFlUIntA32Le:
        case Opcode::ReadFlUIntA32LeRev:
        case Opcode::ReadFlUIntA64Be:
        case Opcode::ReadFlUIntA64BeRev:
        case Opcode::ReadFlUIntA64Le:
        case Opcode::ReadFlUIntA64LeRev:
        case Opcode::ReadFlUIntA8:
        case Opcode::ReadFlUIntA8Rev:
        case Opcode::ReadNtStrUtf16:
        case Opcode::ReadNtStrUtf32:
        case Opcode::ReadNtStrUtf8:
        case Opcode::ReadVlSInt:
        case Opcode::ReadVlUInt:
        case Opcode::ReadOptWithBoolSel:
        case Opcode::ReadOptWithSIntSel:
        case Opcode::ReadOptWithUIntSel:
        case Opcode::ReadStruct:
        case Opcode::ReadVarWithSIntSel:
        case Opcode::ReadVarWithUIntSel:
            return true;

        default:
            return false;
        }
    }

    /*
     * Returns whether or not this instruction is a "read oddly aligned
     * fixed-length bit array" instruction.
     */
    bool isReadOddFlBitArray() const noexcept
    {
        switch (this->opcode()) {
        case Opcode::ReadFlBitArrayBe:
        case Opcode::ReadFlBitArrayBeRev:
        case Opcode::ReadFlBitArrayLe:
        case Opcode::ReadFlBitArrayLeRev:
        case Opcode::ReadFlBitMapBe:
        case Opcode::ReadFlBitMapBeRev:
        case Opcode::ReadFlBitMapLe:
        case Opcode::ReadFlBitMapLeRev:
        case Opcode::ReadFlBoolBe:
        case Opcode::ReadFlBoolBeRev:
        case Opcode::ReadFlBoolLe:
        case Opcode::ReadFlBoolLeRev:
        case Opcode::ReadFlFloat32Be:
        case Opcode::ReadFlFloat32BeRev:
        case Opcode::ReadFlFloat32Le:
        case Opcode::ReadFlFloat32LeRev:
        case Opcode::ReadFlFloat64Be:
        case Opcode::ReadFlFloat64BeRev:
        case Opcode::ReadFlFloat64Le:
        case Opcode::ReadFlFloat64LeRev:
        case Opcode::ReadFlSIntBe:
        case Opcode::ReadFlSIntBeRev:
        case Opcode::ReadFlSIntLe:
        case Opcode::ReadFlSIntLeRev:
        case Opcode::ReadFlUIntBe:
        case Opcode::ReadFlUIntBeRev:
        case Opcode::ReadFlUIntLe:
        case Opcode::ReadFlUIntLeRev:
            return true;

        default:
            return false;
        }
    }

    /*
     * Returns whether or not this instruction is a "read static-length
     * data" instruction.
     */
    bool isReadSlData() const noexcept
    {
        if (this->isReadSlArray()) {
            return true;
        }

        switch (this->opcode()) {
        case Opcode::ReadSlBlob:
        case Opcode::ReadSlStr:
        case Opcode::ReadSlUuidBlob:
            return true;

        default:
            return false;
        }
    }

    /*
     * Returns whether or not this instruction is a "read static-length
     * array" instruction.
     */
    bool isReadSlArray() const noexcept
    {
        return this->opcode() == Opcode::ReadSlArray ||
               this->opcode() == Opcode::ReadSlUuidArray;
    }

    /*
     * Returns whether or not this instruction is a "read dynamic-length
     * data" instruction.
     */
    bool isReadDlData() const noexcept
    {
        return this->opcode() == Opcode::ReadDlBlob ||
               this->opcode() == Opcode::ReadDlStr ||
               this->opcode() == Opcode::ReadDlArray;
    }

    /*
     * Number of program nucleotides (NOT bytes) which the static part
     * of this instruction spans.
     */
    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<InstrBase>();
    }

    /*
     * Returns whether or not, within an instance of `InstrT` which
     * inherits `InstrBase`, the private `InstrBase::_data` member is at
     * offset 0, meaning the instruction base comes before the rest.
     *
     * This exists to support static assertions which can't access the
     * private `_data` member.
     */
    template <typename InstrT>
    static constexpr bool baseIsBefore() noexcept
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
        return offsetof(InstrT, _data) == 0;
#pragma GCC diagnostic pop
    }

    /*
     * Address of the corresponding program nucleotide.
     */
    const PgmNucleo *asNucleo() const noexcept
    {
        return reinterpret_cast<const PgmNucleo *>(this);
    }

    /*
     * Instruction base reference for the nucleotide at address `addr`.
     */
    static const InstrBase& fromNucleo(const PgmNucleo * const addr) noexcept
    {
        return *reinterpret_cast<const InstrBase *>(addr);
    }

    /*
     * Appends an instruction base having the opcode `opcode` to the
     * nucleotide sequence `nucleos`.
     */
    static void appendToPgmNucleos(PgmNucleos& nucleos, Opcode opcode);

    /*
     * This instruction base as a "read data" instruction.
     */
    const ReadDataInstr& asReadData() const noexcept;

    /*
     * This instruction base as a "read oddly aligned fixed-length bit
     * array" instruction.
     */
    const ReadOddFlBitArrayInstr& asReadOddFlBitArray() const noexcept;

    /*
     * This instruction base as a "read static-length data" instruction.
     */
    const ReadSlDataInstr& asReadSlData() const noexcept;

    /*
     * This instruction base as a "read static-length
     * array" instruction.
     */
    const ReadSlArrayInstr& asReadSlArray() const noexcept;

    /*
     * This instruction base as a "read dynamic-length
     * data" instruction.
     */
    const ReadDlDataInstr& asReadDlData() const noexcept;

    /*
     * This instruction base as a "read dynamic-length
     * array" instruction.
     */
    const ReadDlArrayInstr& asReadDlArray() const noexcept;

    /*
     * This instruction base as a "read structure" instruction.
     */
    const ReadStructInstr& asReadStruct() const noexcept;

    /*
     * This instruction base as a "read optional with boolean
     * selector" instruction.
     */
    const ReadOptWithBoolSelInstr& asReadOptWithBoolSel() const noexcept;

    /*
     * This instruction base as a "read optional with unsigned integer
     * selector" instruction.
     */
    const ReadOptWithIntSelInstr<OptionalWithUnsignedIntegerSelectorType::SelectorValue,
                                 static_cast<std::uint8_t>(Opcode::ReadOptWithUIntSel),
                                 static_cast<std::uint8_t>(Opcode::EndReadOptWithUIntSel)>& asReadOptWithUIntSel() const noexcept;

    /*
     * This instruction base as a "read optional with signed integer
     * selector" instruction.
     */
    const ReadOptWithIntSelInstr<OptionalWithSignedIntegerSelectorType::SelectorValue,
                                 static_cast<std::uint8_t>(Opcode::ReadOptWithSIntSel),
                                 static_cast<std::uint8_t>(Opcode::EndReadOptWithSIntSel)>& asReadOptWithSIntSel() const noexcept;

    /*
     * This instruction base as a "read variant with unsigned integer
     * selector" instruction.
     */
    const ReadVarInstr<VariantWithUnsignedIntegerSelectorType::Option::SelectorValue,
                       static_cast<std::uint8_t>(Opcode::ReadVarWithUIntSel),
                       static_cast<std::uint8_t>(Opcode::EndReadVarWithUIntSel)>& asReadVarWithUIntSel() const noexcept;

    /*
     * This instruction base as a "read variant with signed integer
     * selector" instruction.
     */
    const ReadVarInstr<VariantWithSignedIntegerSelectorType::Option::SelectorValue,
                       static_cast<std::uint8_t>(Opcode::ReadVarWithSIntSel),
                       static_cast<std::uint8_t>(Opcode::EndReadVarWithSIntSel)>& asReadVarWithSIntSel() const noexcept;

    /*
     * This instruction base as a "read scope" instruction.
     */
    const ReadScopeInstr& asReadScope() const noexcept;

    /*
     * This instruction base as a "save current integer" instruction.
     */
    const SaveCurIntInstr& asSaveCurInt() const noexcept;

    /*
     * This instruction base as an "update default clock value (fixed
     * length) from current integer" instruction.
     */
    const UpdateDefClkValFlFromCurIntInstr& asUpdateDefClkValFlFromCurInt() const noexcept;

protected:
    /*
     * Appends the static part of an instruction of type `InstrT` to the
     * nucleotide sequence `nucleos`.
     *
     * `args` are forwarded to the constructor of `InstrT`.
     */
    template <typename InstrT, typename... ArgTs>
    static void _appendStaticToPgmNucleos(PgmNucleos& nucleos, ArgTs&&... args)
    {
        const InstrT instr {std::forward<ArgTs>(args)...};

        for (Index i = 0; i < instr.staticLen(); ++i) {
            nucleos.push_back(instr.asNucleo()[i]);
        }
    }

    /*
     * Writes `val` to the instruction base data from byte `UpperV` to
     * byte `LowerV`, both included.
     */
    template <Index UpperV, Index LowerV>
    void _writeToBase(const unsigned long long val) noexcept
    {
        static_assert(UpperV < this->_opByteRange().upper, "Not overwriting opcode");
        this->_unsafeWriteDataU<UpperV, LowerV>(val);
    }

    /*
     * Returns the value of the instruction base data from byte `UpperV`
     * to byte `LowerV`, both included.
     */
    template <Index UpperV, Index LowerV>
    unsigned long long _readFromBase() const noexcept
    {
        static_assert(UpperV < _opByteRange().upper, "Not reading opcode");
        return this->_unsafeReadDataU<UpperV, LowerV>();
    }

private:
    template <Index UpperV, Index LowerV>
    std::uint64_t _dataUMask() const noexcept
    {
        const auto len = (UpperV - LowerV + 1) * 8;

        return ((1ULL << len) - 1) << (LowerV * 8);
    }

    template <Index UpperV, Index LowerV>
    void _unsafeWriteDataU(const unsigned long long val) noexcept
    {
        static_assert(UpperV >= LowerV, "`UpperV` is greater than or equal to `LowerV`");
        static_assert(UpperV < 8, "`UpperV` is less than 8");
        assert(val < (1ULL << (UpperV - LowerV + 1) * 8));

        const auto mask = this->_dataUMask<UpperV, LowerV>();

        _data.u = (_data.u & ~mask) | ((val << (LowerV * 8)) & mask);
    }

    template <Index UpperV, Index LowerV>
    unsigned long long _unsafeReadDataU() const noexcept
    {
        static_assert(UpperV >= LowerV, "`UpperV` is greater than or equal to `LowerV`");
        static_assert(UpperV < 8, "`UpperV` is less than 8");

        const auto mask = this->_dataUMask<UpperV, LowerV>();

        return (_data.u & mask) >> (LowerV * 8);
    }

private:
    // data of an instruction base: a single program nucleotide
    PgmNucleo _data;
};

/*
 * We want to make sure that an instruction base may be located anywhere
 * within a program. This means:
 *
 * • It has the size of a program nucleotide.
 * • Its alignment requirement is the same as a program nucleotide.
 * • Its static length are one program nucleotide.
 */
static_assert(sizeof(InstrBase) == sizeof(PgmNucleo),
              "An `InstrBase` instance contains one nucleotide");
static_assert(alignof(InstrBase) == alignof(PgmNucleo),
              "Alignment requirement of an `InstrBase` instance matches alignment requirement of a `PgmNucleo` instance");
static_assert(InstrBase::staticLen() == 1,
              "Length of static part of `InstrBase` is one nucleotide");

inline const InstrBase& PgmView::instrBaseAt(const Index index) const noexcept
{
    return InstrBase::fromNucleo(_begin + index);
}

/*
 * "Read data" instruction: instructs the VM to read some data.
 *
 * Such an instruction contains the data alignment requirement within
 * its base, as well as a structure member type pointer (optional) and a
 * data type pointer (always exists). The base data bytes 3 to 0
 * remain available.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *               ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━┓
 *     Nucleo 0: ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Free ┃
 *               ┠───────────────┴────────────────────┴──────┨
 *     Nucleo 1: ┃ Structure member type address             ┃
 *               ┠───────────────────────────────────────────┨
 *     Nucleo 2: ┃ Data type address                         ┃
 *               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the alignment requirement of the data to read with align().
 *
 * Get the structure member type with memberType().
 *
 * Get the data type with dt().
 *
 * This is the base class of all data reading instruction classes.
 */
class ReadDataInstr :
    public InstrBase
{
    friend class InstrBase;

private:
    // alignment requirement byte range
    static constexpr _tByteRange _alignByteRange() noexcept
    {
        return {6, 4};
    }

protected:
    /*
     * Builds a "read data" instruction having the opcode `opcode`, the
     * structure member type `memberType`, and the data type `dt`.
     *
     * This constructor uses the alignment requirement of `dt` to set
     * its own base.
     */
    explicit ReadDataInstr(Opcode opcode, const StructureMemberType *memberType,
                           const DataType& dt) noexcept;

public:
    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadDataInstr>();
    }

    /*
     * Alignment of data to read.
     */
    Size align() const noexcept
    {
        return this->_readFromBase<_alignByteRange().upper,
                                   _alignByteRange().lower>();
    }

    const StructureMemberType *memberType() const noexcept
    {
        return reinterpret_cast<const StructureMemberType *>(_memberTypeAddr.u);
    }

    const DataType& dt() const noexcept
    {
        return *reinterpret_cast<const DataType *>(_dtAddr.u);
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, Opcode opcode,
                                   const StructureMemberType *memberType,
                                   const DataType& dt);

private:
    PgmNucleo _memberTypeAddr;
    PgmNucleo _dtAddr;
};

static_assert(InstrBase::baseIsBefore<ReadDataInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadDataInstr`");
static_assert(ReadDataInstr::staticLen() == 3,
              "Total length of `ReadDataInstr` is three nucleotides");

inline const ReadDataInstr& InstrBase::asReadData() const noexcept
{
    assert(this->isReadData());
    return static_cast<const ReadDataInstr&>(*this);
}

/*
 * "Read odd fixed-length bit array" instruction: instructs the VM to
 * read an unconventional fixed-length bit array.
 *
 * "Odd" here means "unconventional", in that either the alignment or
 * the size isn't considered standard.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *               ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━┯━━━━━━┓
 *     Nucleo 0: ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Data len. [3, 3] │ Free ┃
 *               ┠───────────────┴────────────────────┴──────────────────┴──────┨
 *     Nucleo 1: ┃ Structure member type address                                ┃
 *               ┠──────────────────────────────────────────────────────────────┨
 *     Nucleo 2: ┃ Fixed-length bit array type address                          ┃
 *               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the fixed-length bit array length (bits) with dataLen().
 */
class ReadOddFlBitArrayInstr final :
    public ReadDataInstr
{
    friend class InstrBase;

private:
    // data length byte range
    static constexpr _tByteRange _dataLenByteRange() noexcept
    {
        return {3, 3};
    }

private:
    /*
     * Builds a "read odd fixed-length bit array" instruction having the
     * opcode `opcode`, the structure member type `memberType`, and the
     * data type `dt`.
     *
     * This constructor uses the length (bits) of `dt` to set its
     * own base.
     */
    explicit ReadOddFlBitArrayInstr(Opcode opcode, const StructureMemberType * memberType,
                                    const DataType& dt) noexcept;

public:
    /*
     * Length (bits) of fixed-length bit array to read.
     */
    Size dataLen() const noexcept
    {
        return this->_readFromBase<_dataLenByteRange().upper,
                                   _dataLenByteRange().lower>();
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, Opcode opcode,
                                   const StructureMemberType *memberType,
                                   const DataType& dt);
};

inline const ReadOddFlBitArrayInstr& InstrBase::asReadOddFlBitArray() const noexcept
{
    assert(this->isReadOddFlBitArray());
    return static_cast<const ReadOddFlBitArrayInstr&>(*this);
}

/*
 * "Save current unsigned integer" instruction: instructs the VM to save
 * the current unsigned integer to a known position.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *               ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0: ┃ Opcode [7, 7] │ Position [6, 0] ┃
 *               ┗━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━┛
 *
 * Get the position where to save the current unsigned integer
 * with pos().
 */
class SaveCurIntInstr final :
    public InstrBase
{
    friend class InstrBase;

private:
    // position byte range
    static constexpr _tByteRange _posByteRange() noexcept
    {
        return {6, 0};
    }

private:
    /*
     * Builds a "save current unsigned integer" instruction with the
     * position `pos`.
     */
    explicit SaveCurIntInstr(Index pos) noexcept;

public:
    /*
     * Position where to save the current unsigned integer.
     */
    Index pos() const noexcept
    {
        return this->_readFromBase<_posByteRange().upper,
                                   _posByteRange().lower>();
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, Index pos);
};

inline const SaveCurIntInstr& InstrBase::asSaveCurInt() const noexcept
{
    assert(this->opcode() == Opcode::SaveCurInt);
    return static_cast<const SaveCurIntInstr&>(*this);
}

/*
 * "Update default clock value (fixed length) from current unsigned
 * integer" instruction: instructs the VM to update the default clock
 * value using the current unsigned integer having a known fixed
 * length (bits).
 *
 * The big-endian memory layout of such an instruction is:
 *
 *               ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━┓
 *     Nucleo 0: ┃ Opcode [7, 7] │ Cur. int. length [6, 6] │ Free ┃
 *               ┗━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━┛
 *
 * Get the length (bits) of the current unsigned integer
 * with curIntLen().
 */
class UpdateDefClkValFlFromCurIntInstr final :
    public InstrBase
{
    friend class InstrBase;

private:
    // current unsigned integer length byte range
    static constexpr _tByteRange _curIntLenByteRange() noexcept
    {
        return {6, 6};
    }

private:
    /*
     * Builds an "update default clock value (fixed length) from current
     * unsigned integer" instruction with the current unsigned integer
     * length `curIntLen` bits.
     */
    explicit UpdateDefClkValFlFromCurIntInstr(Size curIntLen) noexcept;

public:
    /*
     * Length of the current unsigned integer (bits).
     */
    Size curIntLen() const noexcept
    {
        return this->_readFromBase<_curIntLenByteRange().upper,
                                   _curIntLenByteRange().lower>();
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, Size curIntLen);
};

inline const UpdateDefClkValFlFromCurIntInstr& InstrBase::asUpdateDefClkValFlFromCurInt() const noexcept
{
    assert(this->opcode() == Opcode::UpdateDefClkValFlFromCurInt);
    return static_cast<const UpdateDefClkValFlFromCurIntInstr&>(*this);
}

/*
 * "Read scope" instruction: instructs the VM to read a scope.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *                  ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━┯━━━━━━┓
 *     Nucleo 0:    ┃ Opcode [7, 7] │ Scope [6, 6] │ Free ┃
 *                  ┠───────────────┴──────────────┴──────┨
 *     Nucleo 1...: ┃ Scope program...                    ┃
 *                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the scope to read with scope().
 *
 * Get the program to execute to read the scope with pgm().
 */
class ReadScopeInstr final :
    public InstrBase
{
    friend class InstrBase;

private:
    // scope byte range
    static constexpr _tByteRange _scopeByteRange() noexcept
    {
        return {6, 6};
    }

private:
    /*
     * Builds a "read scope" instruction with the
     * scope `scope`.
     */
    explicit ReadScopeInstr(Scope scope) noexcept;

public:
    /*
     * Scope to read.
     */
    Scope scope() const noexcept
    {
        return static_cast<Scope>(this->_readFromBase<_scopeByteRange().upper,
                                                      _scopeByteRange().lower>());
    }

    /*
     * Program to execute to read the scope.
     */
    PgmView pgm() const noexcept
    {
        // immediately follows the static part
        return PgmView {this->asNucleo() + this->staticLen()};
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, Scope scope,
                                   const PgmNucleos& scopePgmNucleos);
};

inline const ReadScopeInstr& InstrBase::asReadScope() const noexcept
{
    assert(this->opcode() == Opcode::ReadScope);
    return static_cast<const ReadScopeInstr&>(*this);
}

/*
 * "Read static-length data" instruction: instructs the VM to read some
 * data having a known number of elements.
 *
 * Such an instruction contains the number of elements to read.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *               ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━┓
 *     Nucleo 0: ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Free ┃
 *               ┠───────────────┴────────────────────┴──────┨
 *     Nucleo 1: ┃ Structure member type address             ┃
 *               ┠───────────────────────────────────────────┨
 *     Nucleo 2: ┃ Static-length data type address           ┃
 *               ┠───────────────────────────────────────────┨
 *     Nucleo 3: ┃ Element count                             ┃
 *               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the number of elements to read with elemCount().
 */
class ReadSlDataInstr :
    public ReadDataInstr
{
    friend class InstrBase;

protected:
    /*
     * Builds a "read static-length data" instruction having the opcode
     * `opcode`, the structure member type `memberType`, and the data
     * type `dt`.
     *
     * This constructor uses the length of `dt` to set its own base.
     */
    explicit ReadSlDataInstr(Opcode opcode, const StructureMemberType * memberType,
                             const DataType& dt) noexcept;

public:
    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadSlDataInstr>();
    }

    /*
     * Number of elements to read.
     *
     * This is, depending on the opcode:
     *
     * `Opcode::ReadSlBlob`:
     * `Opcode::ReadSlStr`:
     * `Opcode::ReadSlUuidBlob`:
     *     Number of bytes to read.
     *
     * `Opcode::ReadSlArray`:
     * `Opcode::ReadSlUuidArray`:
     *     Number of times to execute the element program.
     */
    Size elemCount() const noexcept
    {
        return _elemCount.u;
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, Opcode opcode,
                                   const StructureMemberType *memberType,
                                   const DataType& dt);

private:
    PgmNucleo _elemCount;
};

static_assert(InstrBase::baseIsBefore<ReadSlDataInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadSlDataInstr`");
static_assert(ReadSlDataInstr::staticLen() == 4,
              "Length of static part of `ReadSlDataInstr` is four nucleotides");

inline const ReadSlDataInstr& InstrBase::asReadSlData() const noexcept
{
    assert(this->isReadSlData());
    return static_cast<const ReadSlDataInstr&>(*this);
}

/*
 * "Read static-length array" instruction: instructs the VM to read a
 * static-length array.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *                  ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0:    ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Element program length [3, 0] ┃
 *                  ┠───────────────┴────────────────────┴───────────────────────────────┨
 *     Nucleo 1:    ┃ Structure member type address                                      ┃
 *                  ┠────────────────────────────────────────────────────────────────────┨
 *     Nucleo 2:    ┃ Static-length array type address                                   ┃
 *                  ┠────────────────────────────────────────────────────────────────────┨
 *     Nucleo 3:    ┃ Element count                                                      ┃
 *                  ┠────────────────────────────────────────────────────────────────────┨
 *     Nucleo 4...: ┃ Element program...                                                 ┃
 *                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the program to execute to read an element with elemPgm() and its
 * length with elemPgmLen().
 */
class ReadSlArrayInstr final :
    public ReadSlDataInstr
{
    friend class InstrBase;

private:
    // element program length byte range
    static constexpr _tByteRange _elemPgmByteRange() noexcept
    {
        return {3, 0};
    }

private:
    /*
     * Builds a "read static-length array" instruction having the opcode
     * `opcode`, the structure member type `memberType`, and the data
     * type `dt`.
     */
    explicit ReadSlArrayInstr(Opcode opcode, const StructureMemberType * memberType,
                              const DataType& dt, Size elemPgmLen) noexcept;

public:
    Size len() const noexcept
    {
        return this->staticLen() + this->elemPgmLen();
    }

    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadSlArrayInstr>();
    }

    /*
     * Program, of length elemPgmLen(), to execute elemCount() times.
     */
    PgmView elemPgm() const noexcept
    {
        // immediately follows the static part
        return PgmView {this->asNucleo() + this->staticLen()};
    }

    /*
     * Length of elemPgm().
     */
    Size elemPgmLen() const noexcept
    {
        return static_cast<Size>(this->_readFromBase<_elemPgmByteRange().upper,
                                                     _elemPgmByteRange().lower>());
    }

    /*
     * `elemPgmNucleos` must end with an "end read array
     * element" instruction.
     */
    static void appendToPgmNucleos(PgmNucleos& nucleos, Opcode opcode,
                                   const StructureMemberType *memberType,
                                   const DataType& dt, const PgmNucleos& elemPgmNucleos);
};

static_assert(InstrBase::baseIsBefore<ReadSlArrayInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadSlArrayInstr`");
static_assert(ReadSlArrayInstr::staticLen() == 4,
              "Length of static part of `ReadSlArrayInstr` is four nucleotides");

inline const ReadSlArrayInstr& InstrBase::asReadSlArray() const noexcept
{
    assert(this->isReadSlArray());
    return static_cast<const ReadSlArrayInstr&>(*this);
}

/*
 * "Read dynamic-length data" instruction: instructs the VM to read some
 * data having a number of elements known at execution time.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *               ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0: ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Saved EC pos. [3, 0] ┃
 *               ┠───────────────┴────────────────────┴──────────────────────┨
 *     Nucleo 1: ┃ Structure member type address                             ┃
 *               ┠───────────────────────────────────────────────────────────┨
 *     Nucleo 2: ┃ Dynamic-length data type address                          ┃
 *               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the position of the saved element count with savedElemCountPos().
 */
class ReadDlDataInstr :
    public ReadDataInstr
{
    friend class InstrBase;

private:
    // saved element count position byte range
    static constexpr _tByteRange _savedElemCountPosByteRange() noexcept
    {
        return {3, 0};
    }

protected:
    /*
     * Builds a "read dynamic-length data" instruction having the opcode
     * `opcode`, the structure member type `memberType`, the data type
     * `dt`, and the saved element count position `savedElemCountPos`.
     */
    explicit ReadDlDataInstr(Opcode opcode, const StructureMemberType * memberType,
                             const DataType& dt, Index savedElemCountPos) noexcept;

public:
    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadDlDataInstr>();
    }

    /*
     * Position of the saved element count.
     *
     * The saved element count is the number of elements to read.
     *
     * This is, depending on the opcode:
     *
     * `Opcode::ReadDlBlob`:
     * `Opcode::ReadDlStr`:
     *     Number of bytes to read.
     *
     * `Opcode::ReadDlArray`:
     *     Number of times to execute the element program.
     */
    Index savedElemCountPos() const noexcept
    {
        return this->_readFromBase<_savedElemCountPosByteRange().upper,
                                   _savedElemCountPosByteRange().lower>();
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, Opcode opcode,
                                   const StructureMemberType *memberType,
                                   const DataType& dt, Index savedElemCountPos);
};

inline const ReadDlDataInstr& InstrBase::asReadDlData() const noexcept
{
    assert(this->isReadDlData());
    return static_cast<const ReadDlDataInstr&>(*this);
}

/*
 * "Read dynamic-length array" instruction: instructs the VM to read a
 * dynamic-length array.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *                  ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0:    ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Saved EC pos. [3, 0] ┃
 *                  ┠───────────────┴────────────────────┴──────────────────────┨
 *     Nucleo 1:    ┃ Structure member type address                             ┃
 *                  ┠───────────────────────────────────────────────────────────┨
 *     Nucleo 2:    ┃ Dynamic-length array type address                         ┃
 *                  ┠───────────────────────────────────────────────────────────┨
 *     Nucleo 3:    ┃ Element program length                                    ┃
 *                  ┠───────────────────────────────────────────────────────────┨
 *     Nucleo 4...: ┃ Element program...                                        ┃
 *                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the program to execute to read an element with elemPgm() and its
 * length with elemPgmLen().
 */
class ReadDlArrayInstr final :
    public ReadDlDataInstr
{
    friend class InstrBase;

private:
    /*
     * Builds a "read dynamic-length array" instruction having the
     * structure member type `memberType`, the data type `dt`, and the
     * saved element count position `savedElemCountPos`.
     */
    explicit ReadDlArrayInstr(const StructureMemberType * memberType, const DataType& dt,
                              Index savedElemCountPos, Size elemPgmLen) noexcept;

public:
    Size len() const noexcept
    {
        return this->staticLen() + this->elemPgmLen();
    }

    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadDlArrayInstr>();
    }

    /*
     * Program, of length elemPgmLen(), to execute to read an element.
     */
    PgmView elemPgm() const noexcept
    {
        // immediately follows the static part
        return PgmView {this->asNucleo() + this->staticLen()};
    }

    /*
     * Length of elemPgm().
     */
    Size elemPgmLen() const noexcept
    {
        return _elemPgmLen.u;
    }

    /*
     * This function appends an "end read array element" instruction
     * to `elemPgmNucleos`.
     */
    static void appendToPgmNucleos(PgmNucleos& nucleos, const StructureMemberType *memberType,
                                   const DataType& dt, Index savedElemCountPos,
                                   const PgmNucleos& elemPgmNucleos);

private:
    PgmNucleo _elemPgmLen;
};

static_assert(InstrBase::baseIsBefore<ReadDlArrayInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadDlArrayInstr`");
static_assert(ReadDlArrayInstr::staticLen() == 4,
              "Length of static part of `ReadDlArrayInstr` is four nucleotides");

inline const ReadDlArrayInstr& InstrBase::asReadDlArray() const noexcept
{
    assert(this->opcode() == Opcode::ReadDlArray);
    return static_cast<const ReadDlArrayInstr&>(*this);
}

/*
 * "Read structure" instruction: instructs the VM to read a structure.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *                  ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━┓
 *     Nucleo 0:    ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Free ┃
 *                  ┠───────────────┴────────────────────┴──────┨
 *     Nucleo 1:    ┃ Structure member type address             ┃
 *                  ┠───────────────────────────────────────────┨
 *     Nucleo 2:    ┃ Structure type address                    ┃
 *                  ┠───────────────────────────────────────────┨
 *     Nucleo 3...: ┃ Members program...                        ┃
 *                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the program to execute to read the members with membersPgm().
 */
class ReadStructInstr final :
    public ReadDataInstr
{
    friend class InstrBase;

private:
    /*
     * Builds a "read structure" instruction having the structure member
     * type `memberType` and the data type `dt`.
     */
    explicit ReadStructInstr(const StructureMemberType * memberType, const DataType& dt) noexcept;

public:
    /*
     * Program to execute to read the members.
     *
     * The program length is unknown here, but you don't need to know
     * it to execute it (an "end read structure" instruction follows).
     */
    PgmView membersPgm() const noexcept
    {
        // immediately follows the static part
        return PgmView {this->asNucleo() + this->staticLen()};
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, const StructureMemberType *memberType,
                                   const DataType& dt, const PgmNucleos& membersPgm);
};

inline const ReadStructInstr& InstrBase::asReadStruct() const noexcept
{
    assert(this->opcode() == Opcode::ReadStruct);
    return static_cast<const ReadStructInstr&>(*this);
}

/*
 * "Read optional with boolean selector" instruction: instructs the VM
 * to read an optional having a boolean selector.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *                  ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0:    ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Saved sel. pos. [3, 0] ┃
 *                  ┠───────────────┴────────────────────┴────────────────────────┨
 *     Nucleo 1:    ┃ Structure member type address                               ┃
 *                  ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 2:    ┃ Optional type address                                       ┃
 *                  ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 3:    ┃ Optional program length                                     ┃
 *                  ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 4...: ┃ Optional program...                                         ┃
 *                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the position of the saved selector with savedSelPos().
 *
 * When decoding, depending on the value of the selector:
 *
 * True:
 *     Get the program to execute to read the data with pgm().
 *
 * False:
 *     Skip the whole optional program of length pgmLen().
 */
class ReadOptWithBoolSelInstr final :
    public ReadDataInstr
{
    friend class InstrBase;

private:
    // saved selector position byte range
    static constexpr _tByteRange _savedSelPosByteRange() noexcept
    {
        return {3, 0};
    }

private:
    /*
     * Builds a "read optional with boolean selector" instruction having
     * the structure member type `memberType`, the data type `dt`, and
     * the saved selector position `savedSelPos`.
     */
    explicit ReadOptWithBoolSelInstr(const StructureMemberType * memberType, const DataType& dt,
                                     Index savedSelPos, Size pgmLen) noexcept;

public:
    Size len() const noexcept
    {
        return this->staticLen() + this->pgmLen();
    }

    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadOptWithBoolSelInstr>();
    }

    /*
     * Position of the saved selector.
     */
    Index savedSelPos() const noexcept
    {
        return this->_readFromBase<_savedSelPosByteRange().upper,
                                   _savedSelPosByteRange().lower>();
    }

    /*
     * Program, of length pgmLen(), to execute to read the optional.
     */
    PgmView pgm() const noexcept
    {
        // immediately follows the static part
        return PgmView {this->asNucleo() + this->staticLen()};
    }

    /*
     * Length of pgm().
     */
    Size pgmLen() const noexcept
    {
        return _pgmLen.u;
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos, const StructureMemberType *memberType,
                                   const DataType& dt, Index savedSelPos,
                                   const PgmNucleos& pgmNucleos);

private:
    PgmNucleo _pgmLen;
};

static_assert(InstrBase::baseIsBefore<ReadOptWithBoolSelInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadOptWithBoolSelInstr`");
static_assert(ReadOptWithBoolSelInstr::staticLen() == 4,
              "Length of static part of `ReadOptWithBoolSelInstr` is four nucleotides");

inline const ReadOptWithBoolSelInstr& InstrBase::asReadOptWithBoolSel() const noexcept
{
    assert(this->opcode() == Opcode::ReadOptWithBoolSel);
    return static_cast<const ReadOptWithBoolSelInstr&>(*this);
}

/*
 * An integer range of `ValT` values within a program.
 *
 * A program integer range instance contains a lower value and an upper
 * value, both included in the range.
 *
 * The memory layout of a program integer range is:
 *
 *               ┏━━━━━━━━━━━━━┓
 *     Nucleo 0: ┃ Lower value ┃
 *               ┠─────────────┨
 *     Nucleo 1: ┃ Upper value ┃
 *               ┗━━━━━━━━━━━━━┛
 */
template <typename ValT>
class PgmIntRange final
{
    static_assert(std::is_integral<ValT>::value, "`ValT` is an integral type");

private:
    using _tPgmNucleoInt = std::conditional_t<std::is_signed<ValT>::value,
                                              std::int64_t,
                                              std::uint64_t>;

private:
    /*
     * Builds a program integer range from the yactfr integer
     * range `range`.
     */
    explicit PgmIntRange(const IntegerRange<ValT>& range) noexcept :
        _lower {static_cast<_tPgmNucleoInt>(range.lower())},
        _upper {static_cast<_tPgmNucleoInt>(range.upper())}
    {
        assert(this->lower() <= this->upper());
    }

public:
    /*
     * Lower value of this integer range (included).
     */
    ValT lower() const noexcept
    {
        return static_cast<ValT>(_lower.u);
    }

    /*
     * Upper value of this integer range (included).
     */
    ValT upper() const noexcept
    {
        return static_cast<ValT>(_upper.u);
    }

    /*
     * Returns whether or not this integer range contains `val`.
     */
    bool contains(const ValT val) const noexcept
    {
        return val >= this->lower() && val <= this->upper();
    }

    /*
     * Appends a program integer range to `nucleos` from the yactfr
     * integer range `range`.
     */
    static void appendToPgmNucleos(PgmNucleos& nucleos, const IntegerRange<ValT>& range)
    {
        const PgmIntRange pgmRange {range};

        nucleos.push_back(pgmRange._lower);
        nucleos.push_back(pgmRange._upper);
    }

private:
    PgmNucleo _lower;
    PgmNucleo _upper;
};

using PgmUIntRange = PgmIntRange<unsigned long long>;
using PgmSIntRange = PgmIntRange<long long>;

static_assert(sizeof(PgmUIntRange) == 2 * sizeof(PgmNucleo),
              "A `PgmUIntRange` instance contains two nucleotides");
static_assert(alignof(PgmUIntRange) == alignof(PgmNucleo),
              "Alignment requirement of a `PgmUIntRange` instance matches alignment requirement of a `PgmNucleo` instance");

/*
 * A view of a set of integer ranges of `ValT` within a program.
 *
 * An integer range set in memory doesn't include its range count.
 *
 * Example of memory layout for a set of three integer ranges:
 *
 *               ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0: ┃ Lower value of first range  ┃
 *               ┠─────────────────────────────┨
 *     Nucleo 1: ┃ Upper value of first range  ┃
 *               ┠─────────────────────────────┨
 *     Nucleo 2: ┃ Lower value of second range ┃
 *               ┠─────────────────────────────┨
 *     Nucleo 3: ┃ Upper value of second range ┃
 *               ┠─────────────────────────────┨
 *     Nucleo 4: ┃ Lower value of third range  ┃
 *               ┠─────────────────────────────┨
 *     Nucleo 5: ┃ Upper value of third range  ┃
 *               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */
template <typename ValT>
class PgmIntRangeSetView final
{
public:
    using Range = PgmIntRange<ValT>;

public:
    /*
     * Builds a view of the set of `count` integer ranges starting at
     * the nucleotide `begin`.
     */
    explicit PgmIntRangeSetView(const PgmNucleo * const begin, const Size count) noexcept :
        _begin {begin},
        _count {count}
    {
        assert(count >= 1);
    }

public:
    /*
     * First integer range of the viewed integer range set.
     */
    const Range *begin() const noexcept
    {
        return reinterpret_cast<const Range *>(_begin);
    }

    /*
     * Number of contained integer ranges.
     */
    Size count() const noexcept
    {
        return _count;
    }

    /*
     * Integer range _after_ the last integer range of the viewed
     * integer range set.
     */
    const Range *end() const noexcept
    {
        return this->begin() + _count;
    }

    /*
     * Returns the integer range at the index `index` within the viewed
     * integer range set.
     *
     * `index` must be less than what count() returns.
     */
    const Range& operator[](const Index index) const noexcept
    {
        assert(index < _count);
        return *(this->begin() + index);
    }

    /*
     * Returns whether or not any of the contained integer ranges
     * contains `val`.
     */
    bool contains(const ValT val) const noexcept
    {
        for (auto& range : *this) {
            if (range.contains(val)) {
                return true;
            }
        }

        return false;
    }

    /*
     * Appends the ranges of `ranges` to `nucleos` _without_ appending
     * any count.
     */
    static void appendRangesToPgmNucleos(PgmNucleos& nucleos, const IntegerRangeSet<ValT>& ranges)
    {
        for (auto& range : ranges) {
            Range::appendToPgmNucleos(nucleos, range);
        }
    }

private:
    const PgmNucleo *_begin;
    Size _count;
};

using PgmUIntRangeSetView = PgmIntRangeSetView<unsigned long long>;
using PgmSIntRangeSetView = PgmIntRangeSetView<long long>;

/*
 * "Read optional with integer selector" instruction template: instructs
 * the VM to read an optional having an integer selector of type `SelT`.
 *
 * Such an instruction contains the number of integer ranges to search.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *                   ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0:     ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Saved sel. pos. [3, 0] ┃
 *                   ┠───────────────┴────────────────────┴────────────────────────┨
 *     Nucleo 1:     ┃ Structure member type address                               ┃
 *                   ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 2:     ┃ Optional type address                                       ┃
 *                   ┠──────────────────────────────────┬──────────────────────────┨
 *     Nucleo 3:     ┃ Selector int. range count [7, 4] │ Opt. program len. [3, 0] ┃
 *                   ┠──────────────────────────────────┴──────────────────────────┨
 *     Nucleo 4...A: ┃ Selector integer ranges...                                  ┃
 *                   ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo B...C: ┃ Optional program...                                         ┃
 *                   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the position of the saved selector with savedSelPos().
 *
 * Get the selector range set with selRangeSet().
 *
 * When decoding, depending on the value of the selector:
 *
 * Part of the selector integer ranges:
 *     Get the program to execute to read the data with pgm().
 *
 * Otherwise:
 *     Skip the whole optional program of length pgmLen().
 */
template <typename SelT, std::uint8_t OpcodeV, std::uint8_t EndReadOptOpcodeV>
class ReadOptWithIntSelInstr final :
    public ReadDataInstr
{
    friend class InstrBase;

private:
    // saved selector position byte range
    static constexpr _tByteRange _savedSelPosByteRange() noexcept
    {
        return {3, 0};
    }

public:
    using Sel = SelT;
    using RangeSetView = PgmIntRangeSetView<SelT>;

private:
    /*
     * Builds a "read optional with integer selector" instruction having
     * the structure member type `memberType`, the data type `dt`, and
     * the saved selector position `savedSelPos`.
     *
     * This constructor uses the selector range set of `dt` to set the
     * range count within its own base.
     */
    explicit ReadOptWithIntSelInstr(const StructureMemberType * const memberType, const DataType& dt,
                                    const Index savedSelPos, const Size pgmLen) noexcept :
        ReadDataInstr {static_cast<Opcode>(OpcodeV), memberType, dt}
    {
        this->_writeToBase<_savedSelPosByteRange().upper,
                           _savedSelPosByteRange().lower>(savedSelPos);
        _selRangeCountAndOptPgmLen.parts.selRangeCount = ReadOptWithIntSelInstr::_optTypeFromDt(dt).selectorRanges().ranges().size();
        _selRangeCountAndOptPgmLen.parts.optPgmLen = pgmLen;
    }

public:
    Size len() const noexcept
    {
        return this->staticLen() + this->_selRangesLen() + this->pgmLen();
    }

    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadOptWithIntSelInstr>();
    }

    /*
     * Position of the saved selector.
     */
    Index savedSelPos() const noexcept
    {
        return this->_readFromBase<_savedSelPosByteRange().upper,
                                   _savedSelPosByteRange().lower>();
    }

    /*
     * Selector range set.
     */
    RangeSetView selRangeSet() const noexcept
    {
        // immediately follows the static part
        return RangeSetView {
            this->asNucleo() + this->staticLen(),
            _selRangeCountAndOptPgmLen.parts.selRangeCount
        };
    }

    /*
     * Program, of length pgmLen(), to execute to read the optional.
     */
    PgmView pgm() const noexcept
    {
        // immediately follows the selector ranges
        return PgmView {this->asNucleo() + this->staticLen() + this->_selRangesLen()};
    }

    /*
     * Length of pgm().
     */
    Size pgmLen() const noexcept
    {
        return _selRangeCountAndOptPgmLen.parts.optPgmLen;
    }

    static void appendToPgmNucleos(PgmNucleos& nucleos,
                                   const StructureMemberType * const memberType,
                                   const DataType& dt, const Index savedSelPos,
                                   const PgmNucleos& pgmNucleos)
    {
        // append static part
        InstrBase::_appendStaticToPgmNucleos<ReadOptWithIntSelInstr>(nucleos, memberType, dt,
                                                                     savedSelPos, pgmNucleos.size());

        // append selector ranges
        RangeSetView::appendRangesToPgmNucleos(nucleos,
                                               ReadOptWithIntSelInstr::_optTypeFromDt(dt).selectorRanges());

        // append optional program
        nucleos.insert(nucleos.end(), pgmNucleos.begin(), pgmNucleos.end());

        // append "end read" instruction
        InstrBase::appendToPgmNucleos(nucleos, static_cast<Opcode>(EndReadOptOpcodeV));
    }

private:
    static const OptionalWithIntegerSelectorType<SelT>& _optTypeFromDt(const DataType& dt) noexcept
    {
        return static_cast<const OptionalWithIntegerSelectorType<SelT>&>(dt);
    }

    Size _selRangesLen() const noexcept
    {
        return 2 * _selRangeCountAndOptPgmLen.parts.selRangeCount;
    }

private:
    /*
     * A single nucleotide containing both the number of selector
     * integer ranges and the length of pgm().
     */
    union _tData {
        _tData() :
            nucleo {}
        {
        }

        PgmNucleo nucleo;

        struct {
            std::uint32_t selRangeCount;
            std::uint32_t optPgmLen;
        } parts;
    };

    static_assert(sizeof(_tData) == sizeof(PgmNucleo),
                  "A `ReadOptWithIntSelInstr::_tData` instance contains one nucleotide");

private:
    _tData _selRangeCountAndOptPgmLen;
};

using ReadOptWithUIntSelInstr = ReadOptWithIntSelInstr<OptionalWithUnsignedIntegerSelectorType::SelectorValue,
                                                       static_cast<std::uint8_t>(InstrBase::Opcode::ReadOptWithUIntSel),
                                                       static_cast<std::uint8_t>(InstrBase::Opcode::EndReadOptWithUIntSel)>;

static_assert(InstrBase::baseIsBefore<ReadOptWithUIntSelInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadOptWithUIntSelInstr`");
static_assert(ReadOptWithUIntSelInstr::staticLen() == 4,
              "Length of static part of `ReadOptWithUIntSelInstr` is four nucleotides");

inline const ReadOptWithUIntSelInstr& InstrBase::asReadOptWithUIntSel() const noexcept
{
    assert(this->opcode() == Opcode::ReadOptWithUIntSel);
    return static_cast<const ReadOptWithUIntSelInstr&>(*this);
}

using ReadOptWithSIntSelInstr = ReadOptWithIntSelInstr<OptionalWithSignedIntegerSelectorType::SelectorValue,
                                                       static_cast<std::uint8_t>(InstrBase::Opcode::ReadOptWithSIntSel),
                                                       static_cast<std::uint8_t>(InstrBase::Opcode::EndReadOptWithSIntSel)>;

static_assert(InstrBase::baseIsBefore<ReadOptWithSIntSelInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadOptWithSIntSelInstr`");
static_assert(ReadOptWithSIntSelInstr::staticLen() == 4,
              "Length of static part of `ReadOptWithSIntSelInstr` is four nucleotides");

inline const ReadOptWithSIntSelInstr& InstrBase::asReadOptWithSIntSel() const noexcept
{
    assert(this->opcode() == Opcode::ReadOptWithSIntSel);
    return static_cast<const ReadOptWithSIntSelInstr&>(*this);
}

/*
 * A template of an option within a "read variant" instruction.
 *
 * A "read variant" instruction option contains a total length (number
 * of nucleotides), a selector integer range count, a selector integer
 * range set, and an option program.
 *
 * The memory layout of a "read variant" instruction option is:
 *
 *                   ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0:     ┃ Total option length [7, 4] │ Selector integer range count [3, 0] ┃
 *                   ┠────────────────────────────┴─────────────────────────────────────┨
 *     Nucleo 1...A: ┃ Selector integer ranges...                                       ┃
 *                   ┠──────────────────────────────────────────────────────────────────┨
 *     Nucleo B...:  ┃ Option program...                                                ┃
 *                   ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * Get the total length (number of nucleotides) with len().
 *
 * Get the selector range set with selRangeSet().
 *
 * Get the program to execute to read the option with pgm()
 * when its selector ranges contain the variant selector.
 */
template <typename SelT>
class ReadVarInstrOpt final
{
    template <typename>
    friend class PgmIntRangeSetView;

    template <typename, std::uint8_t, std::uint8_t>
    friend class ReadVarInstr;

public:
    using Sel = SelT;
    using VarTypeOpt = VariantTypeOption<SelT>;
    using RangeSetView = PgmIntRangeSetView<SelT>;

private:
    /*
     * Builds a "read variant" instruction option from the yactfr
     * variant type option `opt`.
     */
    explicit ReadVarInstrOpt(const VarTypeOpt& opt, const Size pgmLen) noexcept
    {
        _lenAndSelRangeCount.parts.selRangeCount = opt.selectorRanges().ranges().size();
        _lenAndSelRangeCount.parts.len = this->_len(opt, pgmLen);
    }

public:
    /*
     * Total length (number of nucleotides) of this option.
     */
    Size len() const noexcept
    {
        return _lenAndSelRangeCount.parts.len;
    }

    /*
     * Selector range set.
     */
    RangeSetView selRangeSet() const noexcept
    {
        // immediately follows the first nucleotide
        return RangeSetView {
            &_lenAndSelRangeCount.nucleo + 1, _lenAndSelRangeCount.parts.selRangeCount
        };
    }

    /*
     * Returns whether or not this option is selected by the
     * selector `sel`.
     */
    bool isSel(const SelT sel) const noexcept
    {
        return this->selRangeSet().contains(sel);
    }

    /*
     * Program, of length pgmLen(), to execute to read the option.
     */
    PgmView pgm() const noexcept
    {
        // immediately follows the selector ranges
        return PgmView {&_lenAndSelRangeCount.nucleo + 1 + this->_selRangesLen()};
    }

    Size pgmLen() const noexcept
    {
        return this->len() - 1 - this->_selRangesLen();
    }

    /*
     * This function appends an "end read variant option" instruction to
     * `pgmNucleos`.
     */
    static void appendToPgmNucleos(PgmNucleos& nucleos, const VarTypeOpt& opt,
                                   const PgmNucleos& pgmNucleos)
    {
        /*
         * Add one to account for the "end read variant option"
         * instruction we append at the end (part of the program).
         */
        const ReadVarInstrOpt instrOpt {opt, pgmNucleos.size() + 1};

        // append static part
        nucleos.push_back(PgmNucleo {instrOpt._lenAndSelRangeCount.nucleo});

        // append selector ranges
        RangeSetView::appendRangesToPgmNucleos(nucleos, opt.selectorRanges());

        // append option program
        nucleos.insert(nucleos.end(), pgmNucleos.begin(), pgmNucleos.end());
        InstrBase::appendToPgmNucleos(nucleos, InstrBase::Opcode::EndReadVarOpt);
    }

private:
    /*
     * `pgmLen` is the length of the whole program, _including_ the
     * trailing "end read variant option" instruction.
     */
    static Size _len(const VarTypeOpt& opt, const Size pgmLen) noexcept
    {
        return 1 + ReadVarInstrOpt::_selRangesLen(opt) + pgmLen;
    }

    Size _selRangesLen() const noexcept
    {
        return 2 * _lenAndSelRangeCount.parts.selRangeCount;
    }

    static Size _selRangesLen(const VarTypeOpt& opt) noexcept
    {
        return 2 * opt.selectorRanges().ranges().size();
    }

private:
    /*
     * A single nucleotide containing both the total length and the
     * number of selector ranges.
     */
    union _tData {
        _tData() :
            nucleo {}
        {
        }

        PgmNucleo nucleo;

        struct {
            std::uint32_t len;
            std::uint32_t selRangeCount;
        } parts;
    };

    static_assert(sizeof(_tData) == sizeof(PgmNucleo),
                  "A `ReadVarInstrOpt::_tData` instance contains one nucleotide");

private:
    _tData _lenAndSelRangeCount;
};

using ReadVarWithUIntSelInstrOpt = ReadVarInstrOpt<VariantWithUnsignedIntegerSelectorType::Option::SelectorValue>;
using ReadVarWithSIntSelInstrOpt = ReadVarInstrOpt<VariantWithSignedIntegerSelectorType::Option::SelectorValue>;

static_assert(sizeof(ReadVarWithUIntSelInstrOpt) == sizeof(PgmNucleo),
              "A `ReadVarWithUIntSelInstrOpt` instance contains one nucleotide");
static_assert(alignof(ReadVarWithUIntSelInstrOpt) == alignof(PgmNucleo),
              "Alignment requirement of a `ReadVarWithUIntSelInstrOpt` instance matches alignment requirement of a `PgmNucleo` instance");

/*
 * "Read variant" instruction template: instructs the VM to read a
 * variant having an integer selector of type `SelT`.
 *
 * Such an instruction contains its total length, the number of options,
 * and then all the options.
 *
 * The big-endian memory layout of such an instruction is:
 *
 *                  ┏━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━┓
 *     Nucleo 0:    ┃ Opcode [7, 7] │ Align. req. [6, 4] │ Saved sel. pos. [3, 0] ┃
 *                  ┠───────────────┴────────────────────┴────────────────────────┨
 *     Nucleo 1:    ┃ Structure member type address                               ┃
 *                  ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 2:    ┃ Variant type address                                        ┃
 *                  ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 3:    ┃ Option count                                                ┃
 *                  ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 4:    ┃ Total length of options                                     ┃
 *                  ┠─────────────────────────────────────────────────────────────┨
 *     Nucleo 5...: ┃ Options...                                                  ┃
 *                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 *
 * The options are a sequence of what `ReadVarInstrOpt<SelT>` represents
 * (static + dynamic parts).
 *
 * Get the position of the saved selector with savedSelPos().
 *
 * Get the number of options with optCount().
 *
 * Get the option selected by some selector with optForSel().
 *
 * Get the length of the whole instruction with len().
 */
template <typename SelT, std::uint8_t OpcodeV, std::uint8_t EndReadVarOpcodeV>
class ReadVarInstr final :
    public ReadDataInstr
{
    friend class InstrBase;

private:
    // saved selector position byte range
    static constexpr _tByteRange _savedSelPosByteRange() noexcept
    {
        return {3, 0};
    }

public:
    using Sel = SelT;
    using Opt = ReadVarInstrOpt<SelT>;

private:
    /*
     * Builds a "read variant" instruction having the structure member
     * type `memberType`, the data type `dt`, and the saved selector
     * position `savedSelPos`.
     *
     * This constructor uses the number of options of `dt` to set its
     * own base.
     */
    explicit ReadVarInstr(const StructureMemberType * const memberType, const DataType& dt,
                          const Index savedSelPos, const Size totalOptLen) noexcept :
        ReadDataInstr {static_cast<Opcode>(OpcodeV), memberType, dt},
        _optCount {static_cast<std::uint64_t>(ReadVarInstr::_varTypeFromDt(dt).options().size())},
        _theTotalOptLen {static_cast<std::uint64_t>(totalOptLen)}
    {
        this->_writeToBase<_savedSelPosByteRange().upper,
                           _savedSelPosByteRange().lower>(savedSelPos);
    }

public:
    /*
     * Total length (number of nucleotides) of this instruction.
     */
    Size len() const noexcept
    {
        return this->staticLen() + _theTotalOptLen.u;
    }

    static constexpr Size staticLen() noexcept
    {
        return InstrBase::_staticLen<ReadVarInstr>();
    }

    Size totalOptLen() const noexcept
    {
        return _totalOptLen.u;
    }

    /*
     * Position of the saved selector.
     */
    Index savedSelPos() const noexcept
    {
        return this->_readFromBase<_savedSelPosByteRange().upper,
                                   _savedSelPosByteRange().lower>();
    }

    /*
     * Number of options.
     */
    Size optCount() const noexcept
    {
        return _optCount.u;
    }

    /*
     * Returns the option at the index `index`.
     *
     * ┌────────────────────────────────────────────────────────────┐
     * │ ATTENTION: This is inefficient because the dynamic option  │
     * │ part of the instruction is similar to a linked list.       │
     * │ Therefore only use this method to debug, not within the VM │
     * │ (use optForSel() to select an option with some             │
     * │ selector value).                                           │
     * └────────────────────────────────────────────────────────────┘
     */
    const Opt& operator[](const Index index) const noexcept
    {
        assert(index < this->optCount());

        // options immediately follow the static part
        auto at = this->asNucleo() + this->staticLen();

        // linear search
        Index curIndex = 0;

        while (curIndex < this->optCount()) {
            auto& opt = *reinterpret_cast<const Opt *>(at);

            if (curIndex == index) {
                return opt;
            }

            at += opt.len();
            ++curIndex;
        }

        std::abort();
    }

    /*
     * Returns a pair of the index of the option by the selector as well
     * as the selected option itself, or `boost::none` if none.
     */
    boost::optional<std::pair<Index, const Opt *>> optForSel(const SelT sel) const noexcept
    {
        // options immediately follow the static part
        const auto at = this->asNucleo() + this->staticLen();

        // linear search
        Index curIndex = 0;

        while (curIndex < this->optCount()) {
            auto& opt = *reinterpret_cast<const Opt *>(at);

            if (opt.isSel(sel)) {
                return std::make_pair(curIndex, &opt);
            }

            at += opt.len();
            ++curIndex;
        }

        // nothing found
        return boost::none;
    }

    /*
     * This function appends an "end read variant option" instruction to
     * each program of `optPgmNucleos`.
     */
    static void appendToPgmNucleos(PgmNucleos& nucleos,
                                   const StructureMemberType * const memberType,
                                   const DataType& dt, const Index savedSelPos,
                                   const std::vector<PgmNucleos>& optPgmNucleos)
    {
        auto& varType = ReadVarInstr::_varTypeFromDt(dt);

        assert(varType.options().size() == optPgmNucleos.size());

        // append static part
        InstrBase::_appendStaticToPgmNucleos<ReadVarInstr>(nucleos, memberType, dt, savedSelPos,
                                                           ReadVarInstr::_totalOptLen(varType,
                                                                                      optPgmNucleos));

        // append option programs
        for (Index optI = 0; optI < varType.options().size(); ++optI) {
            Opt::appendToPgmNucleos(nucleos, varType[optI], optPgmNucleos[optI]);
        }

        // append "end read" instruction
        InstrBase::appendToPgmNucleos(nucleos, static_cast<Opcode>(EndReadVarOpcodeV));
    }

private:
    static const VariantWithIntegerSelectorType<SelT>& _varTypeFromDt(const DataType& dt) noexcept
    {
        return static_cast<const VariantWithIntegerSelectorType<SelT>&>(dt);
    }

    static Size _totalOptLen(const VariantWithIntegerSelectorType<SelT>& varType,
                             const std::vector<PgmNucleos>& optPgmNucleos)
    {
        Size len = 0;

        for (Index i = 0; i < varType.options().size(); ++i) {
            /*
             * That `+ 1` is really nasty, but it's the "end read
             * variant option" instruction that we expect
             * ReadVarInstr::appendToPgmNucleos() to append (not part of
             * the provided program). Opt::_len() doesn't take it
             * into account.
             */
            len += Opt::_len(varType[i], optPgmNucleos[i].size() + 1);
        }

        return len;
    }

private:
    PgmNucleo _optCount;
    PgmNucleo _theTotalOptLen;
};

using ReadVarWithUIntSelInstr = ReadVarInstr<VariantWithUnsignedIntegerSelectorType::Option::SelectorValue,
                                             static_cast<std::uint8_t>(InstrBase::Opcode::ReadVarWithUIntSel),
                                             static_cast<std::uint8_t>(InstrBase::Opcode::EndReadVarWithUIntSel)>;

static_assert(InstrBase::baseIsBefore<ReadVarWithUIntSelInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadVarWithUIntSelInstr`");
static_assert(ReadVarWithUIntSelInstr::staticLen() == 5,
              "Length of static part of `ReadVarWithUIntSelInstr` is five nucleotides");

inline const ReadVarWithUIntSelInstr& InstrBase::asReadVarWithUIntSel() const noexcept
{
    assert(this->opcode() == Opcode::ReadVarWithUIntSel);
    return static_cast<const ReadVarWithUIntSelInstr&>(*this);
}

using ReadVarWithSIntSelInstr = ReadVarInstr<VariantWithSignedIntegerSelectorType::Option::SelectorValue,
                                             static_cast<std::uint8_t>(InstrBase::Opcode::ReadVarWithSIntSel),
                                             static_cast<std::uint8_t>(InstrBase::Opcode::EndReadVarWithSIntSel)>;

static_assert(InstrBase::baseIsBefore<ReadVarWithSIntSelInstr>(),
              "`InstrBase::_data` is at the beginning of `ReadVarWithSIntSelInstr`");
static_assert(ReadVarWithSIntSelInstr::staticLen() == 5,
              "Length of static part of `ReadVarWithSIntSelInstr` is five nucleotides");

inline const ReadVarWithSIntSelInstr& InstrBase::asReadVarWithSIntSel() const noexcept
{
    assert(this->opcode() == Opcode::ReadVarWithSIntSel);
    return static_cast<const ReadVarWithSIntSelInstr&>(*this);
}

/*
 * Partial program (read the specific context and payload scopes) of an
 * instance of a specific event record type.
 */
class ErPgm final
{
public:
    using UP = std::unique_ptr<const ErPgm>;

public:
    explicit ErPgm(const EventRecordType& ert, PgmNucleos pgm);

    const EventRecordType& ert() const noexcept
    {
        return *_ert;
    }

    PgmView pgm() const noexcept
    {
        return PgmView {_pgm};
    }

    Size pgmLen() const noexcept
    {
        return _pgm.size();
    }

private:
    const EventRecordType *_ert;
    PgmNucleos _pgm;
};

/*
 * Partial programs (read the packet context scope and read any event
 * record) for any packet of any instance of a specific data
 * stream type.
 */
class DsPktPgm final
{
public:
    using ErPgmMap = std::unordered_map<TypeId, ErPgm>;
    using ErPgmVec = std::vector<const ErPgm *>;

public:
    explicit DsPktPgm(const DataStreamType& dst, PgmNucleos pktPreamblePgm,
                      PgmNucleos erPreamblePgm, ErPgmMap erPgms);
    const ErPgm *operator[](TypeId id) const noexcept;
    const ErPgm& uniqueErPgm() const noexcept;

    template <typename FuncT>
    void forEachErPgm(FuncT&& func) const
    {
        for (auto& idErPgmPair : _erPgmsMap) {
            func(idErPgmPair.second);
        }
    }

    PgmView pktPreamblePgm() const noexcept
    {
        return PgmView {_pktPreamblePgm};
    }

    Size pktPreamblePgmLen() const noexcept
    {
        return _pktPreamblePgm.size();
    }

    PgmView erPreamblePgm() const noexcept
    {
        return PgmView {_erPreamblePgm};
    }

    Size erPreamblePgmLen() const noexcept
    {
        return _erPreamblePgm.size();
    }

    Size erPgmsCount() const noexcept
    {
        return _erPgmsMap.size() + _erPgmsVec.size();
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
    const DataStreamType *_dst;
    PgmNucleos _pktPreamblePgm;
    PgmNucleos _erPreamblePgm;
    unsigned int _erAlign = 1;

    /*
     * `_erPgmsMap` below owns all the event record programs.
     *
     * However, typically, event record type IDs are contiguous within a
     * given trace type; keeping them in a vector means a more efficient
     * lookup afterwards if this is possible. For outliers, we use the
     * (slower) map.
     *
     * `_erPgmsVec` contains pointers to objects which `_erPgmsMap`
     * owns. _erPgmsVec can contain both event record programs
     * and `nullptr`.
     */
    ErPgmVec _erPgmsVec;
    ErPgmMap _erPgmsMap;
};


/*
 * Programs to read any packet of an instance of a specific trace type.
 *
 * A `TraceType` object privately owns such an object. This means that
 * all the pointers to anything inside the owning `TraceType` object are
 * always safe to use.
 *
 * Any object which needs to access a `PktPgm` object must own its
 * owning `TraceType` object. For example (ownership tree):
 *
 *     User
 *       Element sequence iterator
 *         VM
 *           Trace type
 *             Packet program
 */
class PktPgm final
{
public:
    using DsPktPgms = std::unordered_map<TypeId, DsPktPgm>;

public:
    explicit PktPgm(const TraceType& traceType, PgmNucleos preamblePgm, DsPktPgms dsPktPgms,
                    Size savedValsCount);
    const DsPktPgm *operator[](TypeId id) const noexcept;
    const DsPktPgm& uniqueDsPktPgm() const noexcept;

    template <typename FuncT>
    void forEachDsPktPgm(FuncT&& func) const
    {
        for (auto& idDsPktPgmPair : _dsPktPgms) {
            func(idDsPktPgmPair.second);
        }
    }

    const TraceType& traceType() const noexcept
    {
        return *_traceType;
    }

    Size dsPktPgmsCount() const noexcept
    {
        return _dsPktPgms.size();
    }

    PgmView preamblePgm() const noexcept
    {
        return PgmView {_preamblePgm};
    }

    Size preamblePgmLen() const noexcept
    {
        return _preamblePgm.size();
    }

    Size savedValsCount() const noexcept
    {
        return _savedValsCount;
    }

private:
    const TraceType *_traceType;
    PgmNucleos _preamblePgm;
    DsPktPgms _dsPktPgms;
    Size _savedValsCount = 0;
};

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_PGM_HPP
