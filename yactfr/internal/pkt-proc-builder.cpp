/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <functional>
#include <algorithm>
#include <type_traits>
#include <boost/optional/optional.hpp>

#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/vl-int-type.hpp>
#include <yactfr/metadata/vl-enum-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>

#include "pkt-proc-builder.hpp"

namespace yactfr {
namespace internal {

class CallerInstrVisitor :
    public InstrVisitor
{
protected:
    explicit CallerInstrVisitor() = default;

    void _visitProc(Proc& proc)
    {
        // save current procedure to restore it later
        const auto oldInstrLoc = _curInstrLoc;

        ++_curLevel;

        for (auto it = proc.begin(); it != proc.end(); ++it) {
            /*
             * Set current procedure instruction location for each
             * iteration because it can change during an Instr::accept()
             * call.
             */
            _curInstrLoc.proc = &proc.sharedProc();
            _curInstrLoc.it = it;

            // accept this visitor
            (*it)->accept(*this);
        }

        // restore stuff
        --_curLevel;

        _curInstrLoc = oldInstrLoc;
    }

protected:
    InstrLoc _curInstrLoc;
    Index _curLevel = 0;
};

static bool isReadVlUInt(const Instr& instr) noexcept
{
    return instr.kind() == Instr::Kind::READ_VL_UINT ||
           instr.kind() == Instr::Kind::READ_VL_UENUM;
}

static bool isReadVlSInt(const Instr& instr) noexcept
{
    return instr.kind() == Instr::Kind::READ_VL_SINT ||
           instr.kind() == Instr::Kind::READ_VL_SENUM;
}

static bool isReadVlInt(const Instr& instr) noexcept
{
    return isReadVlUInt(instr) || isReadVlSInt(instr);
}

static bool isReadFlUInt(const Instr& instr) noexcept
{
    switch (instr.kind()) {
    case Instr::Kind::READ_FL_UENUM_A16_BE:
    case Instr::Kind::READ_FL_UENUM_A16_LE:
    case Instr::Kind::READ_FL_UENUM_A32_BE:
    case Instr::Kind::READ_FL_UENUM_A32_LE:
    case Instr::Kind::READ_FL_UENUM_A64_BE:
    case Instr::Kind::READ_FL_UENUM_A64_LE:
    case Instr::Kind::READ_FL_UENUM_A8:
    case Instr::Kind::READ_FL_UENUM_BE:
    case Instr::Kind::READ_FL_UENUM_LE:
    case Instr::Kind::READ_FL_UINT_A16_BE:
    case Instr::Kind::READ_FL_UINT_A16_LE:
    case Instr::Kind::READ_FL_UINT_A32_BE:
    case Instr::Kind::READ_FL_UINT_A32_LE:
    case Instr::Kind::READ_FL_UINT_A64_BE:
    case Instr::Kind::READ_FL_UINT_A64_LE:
    case Instr::Kind::READ_FL_UINT_A8:
    case Instr::Kind::READ_FL_UINT_BE:
    case Instr::Kind::READ_FL_UINT_LE:
        return true;

    default:
        return false;
    }
}

#ifndef NDEBUG
static bool isReadUInt(const Instr& instr) noexcept
{
    return isReadFlUInt(instr) || isReadVlUInt(instr);
}
#endif // NDEBUG

PktProcBuilder::PktProcBuilder(const TraceType& traceType) :
    _traceType {&traceType}
{
    this->_buildPktProc();
    _pktProc->buildRawProcFromShared();

    for (auto& idDsPktProcPair : _pktProc->dsPktProcs()) {
        idDsPktProcPair.second->setErAlign();
    }
}

void PktProcBuilder::_buildPktProc()
{
    /*
     * The builder has multiple phases:
     *
     * 1. Translate from metadata objects to procedure objects without
     *    any special rule.
     *
     * 2. In the `BeginReadScopeInstr` instruction of the trace preamble
     *    procedure, find "begin read static-length array" and "begin
     *    read static-length BLOB" instructions and replace them with
     *    `BeginReadSlUuidArrayInstr` and `BeginReadSlUuidBlobInstr`
     *    object.
     *
     * 3. Insert `SetCurIdInstr`, `SetDstInstr`, `SetErtInstr`,
     *    `SetDsIdInstr`, `SetPktSeqNumInstr`,
     *    `SetExpectedPktTotalLenInstr`,
     *    `SetExpectedPktContentLenInstr`, `SetPktMagicNumberInstr`,
     *    `UpdateDefClkValInstr`, `UpdateDefClkValFlInstr`, and
     *    `SetPktEndDefClkValInstr` objects at the appropriate locations
     *    in the packet procedure.
     *
     * 4. Insert `SaveValInstr` objects where needed to accomodate
     *    subsequent "begin read dynamic-length array", "begin read
     *    dynamic-length string", "begin read dynamic-length BLOB",
     *    "begin read variant", and "begin read optional" instructions.
     *
     * 5. Insert "end procedure" instructions at the end of each
     *    top-level procedure.
     */
    this->_buildBasePktProc();
    this->_subUuidInstr();
    this->_insertSpecialInstrs();
    this->_setSavedValPoss();
    this->_insertEndInstrs();
}

static bool instrIsSpecScope(const Instr& instr, const Scope scope) noexcept
{
    if (instr.kind() != Instr::Kind::BEGIN_READ_SCOPE) {
        return false;
    }

    return static_cast<const BeginReadScopeInstr&>(instr).scope() == scope;
}

static Proc::SharedIt firstBeginReadScopeInstr(Proc& proc, const Scope scope) noexcept
{
    for (auto it = proc.begin(); it != proc.end(); ++it) {
        auto& instr = *it;

        if (instrIsSpecScope(*instr, scope)) {
            return it;
        }
    }

    return proc.end();
}

/*
 * This procedure instruction visitor takes a procedure, finds all the
 * contained "read data" instructions with a given role, and calls a
 * function with their locations.
 *
 * The iterator allows the callback to insert instructions after it.
 */
class InstrFinder :
    public CallerInstrVisitor
{
public:
    using Func = std::function<void (InstrLoc&)>;

public:
    explicit InstrFinder(Proc& proc, const UnsignedIntegerTypeRole role, Func func) :
        _uIntTypeRole {role},
        _func {std::move(func)}
    {
        this->_visitProc(proc);
    }

    explicit InstrFinder(Proc& proc, Func func) :
        _findWithTraceTypeUuidRole {true},
        _func {std::move(func)}
    {
        this->_visitProc(proc);
    }

    void visit(ReadFlUIntInstr& instr) override
    {
        if (_uIntTypeRole && instr.uIntType().hasRole(*_uIntTypeRole)) {
            _func(_curInstrLoc);
        }
    }

    void visit(ReadFlUEnumInstr& instr) override
    {
        this->visit(static_cast<ReadFlUIntInstr&>(instr));
    }

    void visit(ReadVlBitArrayInstr& instr) override
    {
        if (_uIntTypeRole && isReadVlUInt(instr) &&
                instr.vlBitArrayType().asVariableLengthUnsignedIntegerType().hasRole(*_uIntTypeRole)) {
            _func(_curInstrLoc);
        }
    }

    void visit(BeginReadStructInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadSlArrayInstr& instr) override
    {
        if (_findWithTraceTypeUuidRole && instr.slArrayType().hasTraceTypeUuidRole()) {
            _func(_curInstrLoc);
        }

        this->_visit(instr);
    }

    void visit(BeginReadSlBlobInstr& instr) override
    {
        if (_findWithTraceTypeUuidRole && instr.slBlobType().hasTraceTypeUuidRole()) {
            _func(_curInstrLoc);
        }
    }

    void visit(BeginReadSlUuidArrayInstr& instr) override
    {
        this->visit(static_cast<BeginReadSlArrayInstr&>(instr));
    }

    void visit(BeginReadDlArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadVarUIntSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadVarSIntSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadOptBoolSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadOptUIntSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadOptSIntSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadScopeInstr& instr) override
    {
        this->_visitProc(instr.proc());
    }

private:
    template <typename BeginReadVarInstrT>
    void _visitBeginReadVarInstr(BeginReadVarInstrT& instr)
    {
        for (auto& opt : instr.opts()) {
            this->_visitProc(opt.proc());
        }
    }

    void _visit(BeginReadCompoundInstr& instr)
    {
        this->_visitProc(instr.proc());
    }

private:
    const boost::optional<UnsignedIntegerTypeRole> _uIntTypeRole;
    const bool _findWithTraceTypeUuidRole = false;
    const Func _func;
};

void PktProcBuilder::_subUuidInstr()
{
    const auto readScopeInstrIt = firstBeginReadScopeInstr(_pktProc->preambleProc(),
                                                           Scope::PACKET_HEADER);

    if (readScopeInstrIt == _pktProc->preambleProc().end()) {
        return;
    }

    auto& readScopeInstr = static_cast<BeginReadScopeInstr&>(**readScopeInstrIt);
    std::vector<InstrLoc> instrLocs;

    InstrFinder {readScopeInstr.proc(), [&instrLocs](InstrLoc& instrLoc) {
        /*
         * Replace after this visitor finishes because it recurses into
         * "begin reading static-length array" instructions afterwards
         * so we cannot change it in its back, effectively deleting the
         * old shared pointer and making a dangling pointer within the
         * visitor.
         */
        instrLocs.push_back(instrLoc);
    }};

    for (auto& instrLoc : instrLocs) {
        const auto& origInstr = static_cast<const ReadDataInstr&>(**instrLoc.it);

        if (origInstr.kind() == Instr::Kind::BEGIN_READ_SL_ARRAY) {
            auto& origBeginReadArrayInstr = static_cast<const BeginReadSlArrayInstr&>(**instrLoc.it);

            // replace instruction
            *instrLoc.it = std::make_shared<BeginReadSlUuidArrayInstr>(origBeginReadArrayInstr.memberType(),
                                                                       origBeginReadArrayInstr.dt());

            auto& beginReadUuidArrayInstr = static_cast<BeginReadSlArrayInstr&>(**instrLoc.it);

            // rebuild subprocedure
            this->_buildReadInstr(nullptr, beginReadUuidArrayInstr.slArrayType().elementType(),
                                  beginReadUuidArrayInstr.proc());
        } else {
            assert(origInstr.kind() == Instr::Kind::BEGIN_READ_SL_BLOB);

            // replace instruction
            *instrLoc.it = std::make_shared<BeginReadSlUuidBlobInstr>(origInstr.memberType(),
                                                                      origInstr.dt());
        }
    }
}

void PktProcBuilder::_insertSpecialInstrs()
{
    this->_insertSpecialPktProcPreambleProcInstrs();

    for (auto& idDsPktProcPair : _pktProc->dsPktProcs()) {
        this->_insertSpecialDsPktProcInstrs(*idDsPktProcPair.second);
    }
}

void PktProcBuilder::_insertSpecialPktProcPreambleProcInstrs()
{
    auto hasDstId = false;
    auto readScopeInstrIt = firstBeginReadScopeInstr(_pktProc->preambleProc(),
                                                     Scope::PACKET_HEADER);

    if (readScopeInstrIt != _pktProc->preambleProc().end()) {
        auto& readScopeInstr = static_cast<BeginReadScopeInstr&>(**readScopeInstrIt);

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::PACKET_MAGIC_NUMBER,
            [](InstrLoc& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetPktMagicNumberInstr>());
            }
        };

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::DATA_STREAM_TYPE_ID,
            [&hasDstId](InstrLoc& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<SetCurIdInstr>());
                hasDstId = true;
            }
        };

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::DATA_STREAM_ID,
            [](InstrLoc& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<SetDsIdInstr>());
            }
        };
    }

    if (hasDstId) {
        _pktProc->preambleProc().insert(_pktProc->preambleProc().end(),
                                        std::make_shared<SetDstInstr>());
    } else {
        if (!_traceType->dataStreamTypes().empty()) {
            assert(_traceType->dataStreamTypes().size() == 1);

            const auto fixedId = (*_traceType->dataStreamTypes().begin())->id();

            _pktProc->preambleProc().insert(_pktProc->preambleProc().end(),
                                            std::make_shared<SetDstInstr>(fixedId));
        }
    }

    _pktProc->preambleProc().insert(_pktProc->preambleProc().end(),
                                    std::make_shared<SetDsInfoInstr>());
}

void PktProcBuilder::_insertSpecialDsPktProcInstrs(DsPktProc& dsPktProc)
{
    auto hasErtIdRole = false;
    auto readScopeInstrIt = firstBeginReadScopeInstr(dsPktProc.pktPreambleProc(),
                                                     Scope::PACKET_CONTEXT);

    const auto insertUpdateDefClkValInstr = [&dsPktProc](auto& instrLoc) {
        assert(dsPktProc.dst().defaultClockType());

        const auto& readUIntInstr = **instrLoc.it;

        assert(isReadUInt(readUIntInstr));

        if (isReadFlUInt(readUIntInstr)) {
            const auto& readFlBitArrayInstr = static_cast<const ReadFlBitArrayInstr&>(readUIntInstr);

            instrLoc.proc->insert(std::next(instrLoc.it),
                                  std::make_shared<UpdateDefClkValFlInstr>(readFlBitArrayInstr.len()));
        } else {
            assert(isReadVlUInt(readUIntInstr));
            instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<UpdateDefClkValInstr>());
        }
    };

    if (readScopeInstrIt != dsPktProc.pktPreambleProc().end()) {
        auto& readScopeInstr = static_cast<BeginReadScopeInstr&>(**readScopeInstrIt);

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH,
            [](auto& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetExpectedPktTotalLenInstr>());
            }
        };

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::PACKET_CONTENT_LENGTH,
            [](auto& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetExpectedPktContentLenInstr>());
            }
        };

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::PACKET_SEQUENCE_NUMBER,
            [](auto& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetPktSeqNumInstr>());
            }
        };

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT,
            [](auto& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetPktDiscErCounterSnapInstr>());
            }
        };

        InstrFinder {
            readScopeInstr.proc(),
            UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP,
            insertUpdateDefClkValInstr
        };

        InstrFinder {
            readScopeInstr.proc(),
            UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP,
            [&dsPktProc](auto& instrLoc) {
                assert(dsPktProc.dst().defaultClockType());
                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetPktEndDefClkValInstr>());
            }
        };
    }

    dsPktProc.pktPreambleProc().insert(dsPktProc.pktPreambleProc().end(),
                                       std::make_shared<SetPktInfoInstr>());
    readScopeInstrIt = firstBeginReadScopeInstr(dsPktProc.erPreambleProc(),
                                                Scope::EVENT_RECORD_HEADER);

    if (readScopeInstrIt != dsPktProc.erPreambleProc().end()) {
        auto& readScopeInstr = static_cast<BeginReadScopeInstr&>(**readScopeInstrIt);

        InstrFinder {
            readScopeInstr.proc(), UnsignedIntegerTypeRole::EVENT_RECORD_TYPE_ID,
            [&hasErtIdRole](auto& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<SetCurIdInstr>());
                hasErtIdRole = true;
            }
        };

        InstrFinder {
            readScopeInstr.proc(),
            UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP,
            insertUpdateDefClkValInstr
        };
    }

    auto insertPoint = readScopeInstrIt == dsPktProc.erPreambleProc().end() ?
                       dsPktProc.erPreambleProc().begin() : std::next(readScopeInstrIt);

    if (hasErtIdRole) {
        insertPoint = std::next(dsPktProc.erPreambleProc().insert(insertPoint,
                                                                  std::make_shared<SetErtInstr>()));
    } else {
        if (!dsPktProc.dst().eventRecordTypes().empty()) {
            assert(dsPktProc.dst().eventRecordTypes().size() == 1);

            const auto fixedId = (*dsPktProc.dst().eventRecordTypes().begin())->id();

            insertPoint = std::next(dsPktProc.erPreambleProc().insert(insertPoint,
                                                                      std::make_shared<SetErtInstr>(fixedId)));
        }
    }

    dsPktProc.erPreambleProc().insert(insertPoint, std::make_shared<SetErInfoInstr>());
}

class DtReadLenSelInstrMapCreator :
    public CallerInstrVisitor
{
public:
    using Func = std::function<void (InstrLoc&)>;

public:
    explicit DtReadLenSelInstrMapCreator(Proc& proc, Func func) :
        _func {std::move(func)}
    {
        this->_visitProc(proc);
    }

    void visit(ReadFlBoolInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadFlSIntInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadFlUIntInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadFlSEnumInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadFlUEnumInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadVlBitArrayInstr& instr) override
    {
        if (isReadVlInt(instr)) {
            this->_visit(instr);
        }
    }

    void visit(BeginReadStructInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadSlArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDlArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadVarUIntSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadVarSIntSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadOptBoolSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadOptUIntSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadOptSIntSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadScopeInstr& instr) override
    {
        this->_visitProc(instr.proc());
    }

private:
    template <typename BeginReadVarInstrT>
    void _visitBeginReadVarInstr(BeginReadVarInstrT& instr)
    {
        for (auto& opt : instr.opts()) {
            this->_visitProc(opt.proc());
        }
    }

    void _visit(BeginReadCompoundInstr& instr)
    {
        this->_visitProc(instr.proc());
    }

    void _visit(ReadDataInstr&)
    {
        _func(_curInstrLoc);
    }

private:
    const Func _func;
};

PktProcBuilder::_DtReadLenSelInstrMap PktProcBuilder::_createDtReadLenSelInstrMap() const
{
    _DtReadLenSelInstrMap map;

    const auto insertFunc = [&map](InstrLoc& instrLoc) {
        auto& readDataInstr = static_cast<const ReadDataInstr&>(**instrLoc.it);

        map[&readDataInstr.dt()] = instrLoc;
    };

    DtReadLenSelInstrMapCreator {_pktProc->preambleProc(), insertFunc};

    for (auto& dsPktProcPair : _pktProc->dsPktProcs()) {
        auto& dsPktProc = dsPktProcPair.second;

        DtReadLenSelInstrMapCreator {dsPktProc->pktPreambleProc(), insertFunc};
        DtReadLenSelInstrMapCreator {dsPktProc->erPreambleProc(), insertFunc};

        dsPktProcPair.second->forEachErProc([&insertFunc](ErProc& erProc) {
            DtReadLenSelInstrMapCreator {erProc.proc(), insertFunc};
        });
    }

    return map;
}

class SaveValInstrInserterVisitor :
    public CallerInstrVisitor
{
public:
    using GetPosFunc = std::function<Index (const DataTypeSet&)>;

public:
    explicit SaveValInstrInserterVisitor(Proc& proc, GetPosFunc func) :
        _func {std::move(func)}
    {
        this->_visitProc(proc);
    }

    void visit(BeginReadStructInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadSlArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDlArrayInstr& instr) override
    {
        instr.lenPos(_func(instr.dlArrayType().lengthTypes()));
        this->_visit(instr);
    }

    void visit(BeginReadDlStrInstr& instr) override
    {
        instr.maxLenPos(_func(instr.dlStrType().maximumLengthTypes()));
    }

    void visit(BeginReadDlBlobInstr& instr) override
    {
        instr.lenPos(_func(instr.dlBlobType().lengthTypes()));
    }

    void visit(BeginReadVarUIntSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadVarSIntSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadOptBoolSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadOptUIntSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadOptSIntSelInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadScopeInstr& instr) override
    {
        this->_visitProc(instr.proc());
    }

private:
    template <typename BeginReadVarInstrT>
    void _visitBeginReadVarInstr(BeginReadVarInstrT& instr)
    {
        instr.selPos(_func(instr.varType().selectorTypes()));

        for (auto& opt : instr.opts()) {
            this->_visitProc(opt.proc());
        }
    }

    void _visit(BeginReadCompoundInstr& instr)
    {
        this->_visitProc(instr.proc());
    }

    void _visit(BeginReadOptInstr& instr)
    {
        instr.selPos(_func(instr.optType().selectorTypes()));
        this->_visit(static_cast<BeginReadCompoundInstr&>(instr));
    }

private:
    const GetPosFunc _func;
};

void PktProcBuilder::_setSavedValPoss()
{
    /*
     * Here's the idea.
     *
     * We swipe the whole packet procedure tree to find the "begin read
     * dynamic-length array", "begin read dynamic-length string", "begin
     * read dynamic-length BLOB", "begin read variant" instructions, and
     * "begin read optional" each of which having a data type containing
     * the length/selector types.
     *
     * For a given length/selector type, we can find the corresponding
     * "read boolean" or "read integer" instruction as data types are
     * unique.
     *
     * We insert "save value" instructions at the appropriate locations
     * in the associated procedure and then return the saved value
     * position to the visitor so that it changes the requesting
     * instruction.
     */
    auto dtReadLenSelInstrMap = this->_createDtReadLenSelInstrMap();
    Index nextPos = 0;

    const auto getPosFunc = [&dtReadLenSelInstrMap, &nextPos](const DataTypeSet& dts) {
        // saved value position to update
        const auto pos = nextPos;

        /*
         * For each data type of `dts`, insert a "save value"
         * instruction after its corresponding "read boolean" or "read
         * integer" instruction.
         */
        for (auto& dt : dts) {
            /*
             * Find corresponding "read boolean" or "read integer"
             * instruction location.
             */
            auto& instrLoc = dtReadLenSelInstrMap[dt];

            // insert "save value" instruction just after
            instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<SaveValInstr>(pos));
        }

        // this saved value position is now used
        ++nextPos;

        return pos;
    };

    SaveValInstrInserterVisitor {_pktProc->preambleProc(), getPosFunc};

    for (auto& dsPktProcPair : _pktProc->dsPktProcs()) {
        auto& dsPktProc = dsPktProcPair.second;

        SaveValInstrInserterVisitor {dsPktProc->pktPreambleProc(), getPosFunc};
        SaveValInstrInserterVisitor {dsPktProc->erPreambleProc(), getPosFunc};

        dsPktProcPair.second->forEachErProc([&getPosFunc](ErProc& erProc) {
            SaveValInstrInserterVisitor {erProc.proc(), getPosFunc};
        });
    }

    _pktProc->savedValsCount(nextPos);
}

template <typename InstrT>
void insertEndInstr(Proc& proc)
{
    proc.pushBack(std::make_shared<InstrT>());
}

void PktProcBuilder::_insertEndInstrs()
{
    insertEndInstr<EndPktPreambleProcInstr>(_pktProc->preambleProc());

    for (auto& dsPktProcPair : _pktProc->dsPktProcs()) {
        auto& dsPktProc = dsPktProcPair.second;

        insertEndInstr<EndDsPktPreambleProcInstr>(dsPktProc->pktPreambleProc());
        insertEndInstr<EndDsErPreambleProcInstr>(dsPktProc->erPreambleProc());

        dsPktProc->forEachErProc([](ErProc& erProc) {
            insertEndInstr<EndErProcInstr>(erProc.proc());
        });
    }
}

void PktProcBuilder::_buildBasePktProc()
{
    _pktProc = std::make_unique<PktProc>(*_traceType);

    this->_buildReadScopeInstr(Scope::PACKET_HEADER, _traceType->packetHeaderType(),
                               _pktProc->preambleProc());

    for (auto& dst : _traceType->dataStreamTypes()) {
        auto dsPktProc = this->_buildDsPktProc(*dst);

        assert(dsPktProc);
        _pktProc->dsPktProcs()[dst->id()] = std::move(dsPktProc);
    }
}

std::unique_ptr<DsPktProc> PktProcBuilder::_buildDsPktProc(const DataStreamType& dst)
{
    auto dsPktProc = std::make_unique<DsPktProc>(dst);

    this->_buildReadScopeInstr(Scope::PACKET_CONTEXT, dst.packetContextType(),
                               dsPktProc->pktPreambleProc());
    this->_buildReadScopeInstr(Scope::EVENT_RECORD_HEADER, dst.eventRecordHeaderType(),
                               dsPktProc->erPreambleProc());
    this->_buildReadScopeInstr(Scope::EVENT_RECORD_COMMON_CONTEXT,
                               dst.eventRecordCommonContextType(), dsPktProc->erPreambleProc());

    for (auto& ert : dst.eventRecordTypes()) {
        auto erProc = this->_buildErProc(*ert);

        assert(erProc);
        dsPktProc->addErProc(std::move(erProc));
    }

    return dsPktProc;
}

std::unique_ptr<ErProc> PktProcBuilder::_buildErProc(const EventRecordType& ert)
{
    auto erProc = std::make_unique<ErProc>(ert);

    this->_buildReadScopeInstr(Scope::EVENT_RECORD_SPECIFIC_CONTEXT, ert.specificContextType(),
                               erProc->proc());
    this->_buildReadScopeInstr(Scope::EVENT_RECORD_PAYLOAD, ert.payloadType(), erProc->proc());
    return erProc;
}

void PktProcBuilder::_buildReadScopeInstr(const Scope scope, const DataType * const dt,
                                          Proc& baseProc)
{
    if (!dt) {
        return;
    }

    auto readScopeInstr = std::make_shared<BeginReadScopeInstr>(scope, dt->alignment());

    this->_buildReadInstr(nullptr, *dt, readScopeInstr->proc());
    readScopeInstr->proc().pushBack(std::make_shared<EndReadScopeInstr>(scope));
    baseProc.pushBack(std::move(readScopeInstr));
}

/*
 * This data type visitor calls _buildRead*Instr() methods of an
 * attached packet procedure builder depending on the visited data type
 * to build individual "read data" procedure instructions.
 */
class BuilderDtInstrVisitor :
    public DataTypeVisitor
{
public:
    explicit BuilderDtInstrVisitor(PktProcBuilder& pktProcBuilder,
                                   const StructureMemberType * const memberType, Proc& baseProc) :
        _pktProcBuilder {&pktProcBuilder},
        _memberType {memberType},
        _baseProc {&baseProc}
    {
    }

    void visit(const FixedLengthBitArrayType& dt) override
    {
        _pktProcBuilder->_buildReadFlBitArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FixedLengthBooleanType& dt) override
    {
        _pktProcBuilder->_buildReadFlBoolInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FixedLengthSignedIntegerType& dt) override
    {
        _pktProcBuilder->_buildReadFlSIntInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FixedLengthUnsignedIntegerType& dt) override
    {
        _pktProcBuilder->_buildReadFlUIntInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FixedLengthFloatingPointNumberType& dt) override
    {
        _pktProcBuilder->_buildReadFlFloatInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FixedLengthSignedEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadFlSEnumInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FixedLengthUnsignedEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadFlUEnumInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariableLengthBitArrayType& dt) override
    {
        _pktProcBuilder->_buildReadVlBitArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariableLengthSignedIntegerType& dt) override
    {
        _pktProcBuilder->_buildReadVlBitArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariableLengthUnsignedIntegerType& dt) override
    {
        _pktProcBuilder->_buildReadVlBitArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariableLengthSignedEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadVlBitArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariableLengthUnsignedEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadVlBitArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const NullTerminatedStringType& dt) override
    {
        _pktProcBuilder->_buildReadNtStrInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StructureType& dt) override
    {
        _pktProcBuilder->_buildReadStructInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StaticLengthArrayType& dt) override
    {
        _pktProcBuilder->_buildReadSlArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const DynamicLengthArrayType& dt) override
    {
        _pktProcBuilder->_buildReadDlArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StaticLengthStringType& dt) override
    {
        _pktProcBuilder->_buildReadSlStrInstr(_memberType, dt, *_baseProc);
    }

    void visit(const DynamicLengthStringType& dt) override
    {
        _pktProcBuilder->_buildReadDlStrInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StaticLengthBlobType& dt) override
    {
        _pktProcBuilder->_buildReadSlBlobInstr(_memberType, dt, *_baseProc);
    }

    void visit(const DynamicLengthBlobType& dt) override
    {
        _pktProcBuilder->_buildReadDlBlobInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariantWithUnsignedIntegerSelectorType& dt) override
    {
        _pktProcBuilder->_buildReadVarUIntSelInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariantWithSignedIntegerSelectorType& dt) override
    {
        _pktProcBuilder->_buildReadVarSIntSelInstr(_memberType, dt, *_baseProc);
    }

    void visit(const OptionalWithBooleanSelectorType& dt) override
    {
        _pktProcBuilder->_buildReadOptBoolSelInstr(_memberType, dt, *_baseProc);
    }

    void visit(const OptionalWithUnsignedIntegerSelectorType& dt) override
    {
        _pktProcBuilder->_buildReadOptUIntSelInstr(_memberType, dt, *_baseProc);
    }

    void visit(const OptionalWithSignedIntegerSelectorType& dt) override
    {
        _pktProcBuilder->_buildReadOptSIntSelInstr(_memberType, dt, *_baseProc);
    }

private:
    PktProcBuilder * const _pktProcBuilder;
    const StructureMemberType * const _memberType;
    Proc * const _baseProc;
};

void PktProcBuilder::_buildReadInstr(const StructureMemberType * const memberType,
                                     const DataType& dt, Proc& baseProc)
{
    BuilderDtInstrVisitor visitor {*this, memberType, baseProc};

    dt.accept(visitor);
}

template <typename ReadInstrT>
static void buildBasicReadInstr(const StructureMemberType * const memberType, const DataType& dt,
                                Proc& baseProc)
{
    baseProc.pushBack(std::make_shared<ReadInstrT>(memberType, dt));
}

void PktProcBuilder::_buildReadFlBitArrayInstr(const StructureMemberType * const memberType,
                                               const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthBitArrayType());
    buildBasicReadInstr<ReadFlBitArrayInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFlBoolInstr(const StructureMemberType * const memberType,
                                           const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthBooleanType());
    buildBasicReadInstr<ReadFlBoolInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFlSIntInstr(const StructureMemberType * const memberType,
                                           const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthSignedIntegerType());
    buildBasicReadInstr<ReadFlSIntInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFlUIntInstr(const StructureMemberType * const memberType,
                                           const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthUnsignedIntegerType());
    buildBasicReadInstr<ReadFlUIntInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFlFloatInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthFloatingPointNumberType());
    buildBasicReadInstr<ReadFlFloatInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFlSEnumInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthSignedEnumerationType());
    buildBasicReadInstr<ReadFlSEnumInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFlUEnumInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthUnsignedEnumerationType());
    buildBasicReadInstr<ReadFlUEnumInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadVlBitArrayInstr(const StructureMemberType * const memberType,
                                               const DataType& dt, Proc& baseProc)
{
    assert(dt.isVariableLengthBitArrayType());
    buildBasicReadInstr<ReadVlBitArrayInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadNtStrInstr(const StructureMemberType * const memberType,
                                          const DataType& dt, Proc& baseProc)
{
    assert(dt.isNullTerminatedStringType());
    buildBasicReadInstr<ReadNtStrInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadStructInstr(const StructureMemberType * const memberType,
                                           const DataType& dt, Proc& baseProc)
{
    assert(dt.isStructureType());

    auto instr = std::make_shared<BeginReadStructInstr>(memberType, dt);

    for (const auto& innerMemberType : dt.asStructureType().memberTypes()) {
        this->_buildReadInstr(innerMemberType.get(), innerMemberType->dataType(), instr->proc());
    }

    auto endInstr = std::make_shared<EndReadDataInstr>(Instr::Kind::END_READ_STRUCT, memberType,
                                                       dt);

    instr->proc().pushBack(std::move(endInstr));
    baseProc.pushBack(std::move(instr));
}

void PktProcBuilder::_buildReadSlArrayInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    assert(dt.isStaticLengthArrayType());
    this->_buildReadInstrWithLen<BeginReadSlArrayInstr,
                                 Instr::Kind::END_READ_SL_ARRAY>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadSlStrInstr(const StructureMemberType * const memberType,
                                          const DataType& dt, Proc& baseProc)
{
    assert(dt.isStaticLengthStringType());
    this->_buildReadInstrWithLen<BeginReadSlStrInstr,
                                 Instr::Kind::END_READ_SL_STR>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadDlArrayInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    assert(dt.isDynamicLengthArrayType());
    this->_buildReadInstrWithLen<BeginReadDlArrayInstr,
                                 Instr::Kind::END_READ_DL_ARRAY>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadDlStrInstr(const StructureMemberType * const memberType,
                                          const DataType& dt, Proc& baseProc)
{
    assert(dt.isDynamicLengthStringType());
    this->_buildReadInstrWithLen<BeginReadDlStrInstr,
                                 Instr::Kind::END_READ_DL_STR>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadSlBlobInstr(const StructureMemberType * const memberType,
                                           const DataType& dt, Proc& baseProc)
{
    assert(dt.isStaticLengthBlobType());
    this->_buildReadInstrWithLen<BeginReadSlBlobInstr,
                                 Instr::Kind::END_READ_SL_BLOB>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadDlBlobInstr(const StructureMemberType * const memberType,
                                           const DataType& dt, Proc& baseProc)
{
    assert(dt.isDynamicLengthBlobType());
    this->_buildReadInstrWithLen<BeginReadDlBlobInstr,
                                 Instr::Kind::END_READ_DL_BLOB>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadVarUIntSelInstr(const StructureMemberType * const memberType,
                                               const DataType& dt, Proc& baseProc)
{
    this->_buildReadVarInstr<BeginReadVarUIntSelInstr>(memberType,
                                                       dt.asVariantWithUnsignedIntegerSelectorType(),
                                                       baseProc,
                                                       Instr::Kind::END_READ_VAR_UINT_SEL);
}

void PktProcBuilder::_buildReadVarSIntSelInstr(const StructureMemberType * const memberType,
                                               const DataType& dt, Proc& baseProc)
{
    this->_buildReadVarInstr<BeginReadVarSIntSelInstr>(memberType,
                                                       dt.asVariantWithSignedIntegerSelectorType(),
                                                       baseProc,
                                                       Instr::Kind::END_READ_VAR_SINT_SEL);
}

void PktProcBuilder::_buildReadOptBoolSelInstr(const StructureMemberType * const memberType,
                                               const DataType& dt, Proc& baseProc)
{
    auto instr = std::make_shared<BeginReadOptBoolSelInstr>(memberType, dt);

    this->_buildReadInstr(nullptr, dt.asOptionalType().dataType(), instr->proc());
    instr->proc().pushBack(std::make_shared<EndReadDataInstr>(Instr::Kind::END_READ_OPT_BOOL_SEL,
                                                              memberType, dt));
    baseProc.pushBack(std::move(instr));
}

void PktProcBuilder::_buildReadOptUIntSelInstr(const StructureMemberType * const memberType,
                                               const DataType& dt, Proc& baseProc)
{
    this->_buildReadOptIntSelInstr<BeginReadOptUIntSelInstr>(memberType,
                                                             dt.asOptionalWithUnsignedIntegerSelectorType(),
                                                             baseProc,
                                                             Instr::Kind::END_READ_OPT_UINT_SEL);
}

void PktProcBuilder::_buildReadOptSIntSelInstr(const StructureMemberType * const memberType,
                                               const DataType& dt, Proc& baseProc)
{
    this->_buildReadOptIntSelInstr<BeginReadOptSIntSelInstr>(memberType,
                                                             dt.asOptionalWithSignedIntegerSelectorType(),
                                                             baseProc,
                                                             Instr::Kind::END_READ_OPT_SINT_SEL);
}

} // namespace internal
} // namespace yactfr
