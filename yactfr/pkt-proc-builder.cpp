/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <functional>
#include <algorithm>
#include <boost/optional/optional.hpp>

#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/dyn-text-array-type.hpp>
#include <yactfr/metadata/dyn-array-type.hpp>

#include "pkt-proc-builder.hpp"

namespace yactfr {
namespace internal {

class CallerInstrVisitor :
    public InstrVisitor
{
protected:
    CallerInstrVisitor() = default;

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
     *    procedure, find a first-level `uuid` "read static array"
     *    instruction and replace it with a
     *    `BeginReadStaticUuidArrayInstr` object.
     *
     * 3. Insert `SetCurIdInstr`, `SetDstInstr`, `SetErtInstr`,
     *    `SetDsIdInstr`, `SetPktOriginIndexInstr`,
     *    `SetExpectedPktTotalLenInstr`,
     *    `SetExpectedPktContentLenInstr`, and `SetPktMagicNumberInstr`
     *    objects at the appropriate locations in the packet procedure.
     *
     * 4. Insert `UpdateClkValInstr` objects at appropriate locations.
     *
     * 5. Insert `SaveValInstr` objects where needed to accomodate
     *    subsequent "read dynamic array" and "begin read variant"
     *    instructions.
     *
     * 6. Insert "end procedure" instructions at the end of each
     *    top-level procedure.
     */
    this->_buildBasePktProc();
    this->_subUuidInstr();
    this->_insertSpecialInstrs();
    this->_insertUpdateClkValInstrs();
    this->_setSavedValPoss();
    this->_insertEndInstrs();
}

static bool instrIsSpecScope(const Instr& instr, const Scope scope) noexcept
{
    if (!instr.isBeginReadScope()) {
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
 * This procedure instruction visitor takes a procedure `proc`, finds
 * all the contained "read data" instructions of which the display name
 * is `dispName`, and calls `callback` with its location.
 *
 * The callback function also receives the level of the instruction,
 * where the instructions found directly in `proc` are at level 0.
 *
 * The iterator allows the callback to insert instructions after it.
 */
class MemberTypeFinderInstrVisitor :
    public CallerInstrVisitor
{
public:
    using Func = std::function<void (InstrLoc&, Index)>;

public:
    explicit MemberTypeFinderInstrVisitor(Proc& proc, std::string dispName, Func func) :
        _dispName {std::move(dispName)},
        _func {std::move(func)}
    {
        this->_visitProc(proc);
    }

    void visit(ReadSIntInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadUIntInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadFloatInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadSEnumInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadUEnumInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadStrInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStructInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticTextArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticUuidArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDynArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDynTextArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadVarUSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadVarSSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
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
        this->_visit(static_cast<ReadDataInstr&>(instr));
        this->_visitProc(instr.proc());
    }

    void _visit(ReadDataInstr& instr)
    {
        if (instr.memberType() && instr.memberType()->displayName() == _dispName) {
            _func(_curInstrLoc, _curLevel - 1);
        }
    }

private:
    const std::string _dispName;
    const Func _func;
};

void PktProcBuilder::_subUuidInstr()
{
    auto readScopeInstrIt = firstBeginReadScopeInstr(_pktProc->preambleProc(),
                                                     Scope::PACKET_HEADER);

    if (readScopeInstrIt == _pktProc->preambleProc().end()) {
        return;
    }

    auto& readScopeInstr = static_cast<BeginReadScopeInstr&>(**readScopeInstrIt);
    Proc::SharedIt readArrayInstrIt = readScopeInstr.proc().end();

    MemberTypeFinderInstrVisitor {
        readScopeInstr.proc(), "uuid",
        [&readArrayInstrIt](InstrLoc& instrLoc, const Index level) {
            if (level != 1) {
                return;
            }

            /*
             * Replace after this visitor finishes because it recurses
             * into this compound instruction afterwards so we cannot
             * change it in its back, effectively deleting the old
             * shared pointer and making a dangling pointer within the
             * visitor.
             */
            readArrayInstrIt = instrLoc.it;
        }
    };

    if (readArrayInstrIt != readScopeInstr.proc().end()) {
        auto& instrReadArray = static_cast<ReadDataInstr&>(**readArrayInstrIt);

        *readArrayInstrIt = std::make_shared<BeginReadStaticUuidArrayInstr>(instrReadArray.memberType(),
                                                                            instrReadArray.dt());

        auto& readArrayInstr = static_cast<BeginReadStaticArrayInstr&>(**readArrayInstrIt);

        this->_buildReadInstr(nullptr, readArrayInstr.staticArrayType().elementType(),
                              readArrayInstr.proc());
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

        MemberTypeFinderInstrVisitor {
            readScopeInstr.proc(), "magic",
            [](InstrLoc& instrLoc, const Index level) {
                if (level != 1) {
                    return;
                }

                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetPktMagicNumberInstr>());
            }
        };

        MemberTypeFinderInstrVisitor {
            readScopeInstr.proc(), "stream_id",
            [&hasDstId](InstrLoc& instrLoc, const Index level) {
                instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<SetCurIdInstr>());
                hasDstId = true;
            }
        };

        MemberTypeFinderInstrVisitor {
            readScopeInstr.proc(), "stream_instance_id",
            [](InstrLoc& instrLoc, const Index level) {
                if (level != 1) {
                    return;
                }

                instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<SetDsIdInstr>());
            }
        };
    }

    Proc::SharedIt insertPoint;

    if (readScopeInstrIt == _pktProc->preambleProc().end()) {
        insertPoint = _pktProc->preambleProc().end();
    } else {
        insertPoint = std::next(readScopeInstrIt);
    }

    if (hasDstId) {
        _pktProc->preambleProc().insert(insertPoint, std::make_shared<SetDstInstr>());
    } else {
        if (!_traceType->dataStreamTypes().empty()) {
            assert(_traceType->dataStreamTypes().size() == 1);

            const auto fixedId = (*_traceType->dataStreamTypes().begin())->id();

            _pktProc->preambleProc().insert(insertPoint, std::make_shared<SetDstInstr>(fixedId));
        }
    }
}

void PktProcBuilder::_insertSpecialDsPktProcInstrs(DsPktProc& dsPktProc)
{
    auto hasId = false;
    auto readScopeInstrIt = firstBeginReadScopeInstr(dsPktProc.pktPreambleProc(),
                                                     Scope::PACKET_CONTEXT);

    if (readScopeInstrIt != dsPktProc.pktPreambleProc().end()) {
        auto& readScopeInstr = static_cast<BeginReadScopeInstr&>(**readScopeInstrIt);

        MemberTypeFinderInstrVisitor {
            readScopeInstr.proc(), "packet_size",
            [](auto& instrLoc, const Index level) {
                if (level != 1) {
                    return;
                }

                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetExpectedPktTotalLenInstr>());
            }
        };

        MemberTypeFinderInstrVisitor {
            readScopeInstr.proc(), "content_size",
            [](auto& instrLoc, const Index level) {
                if (level != 1) {
                    return;
                }

                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetExpectedPktContentLenInstr>());
            }
        };

        MemberTypeFinderInstrVisitor {
            readScopeInstr.proc(), "packet_seq_num",
            [](auto& instrLoc, const Index level) {
                if (level != 1) {
                    return;
                }

                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetPktOriginIndexInstr>());
            }
        };
    }

    readScopeInstrIt = firstBeginReadScopeInstr(dsPktProc.erPreambleProc(),
                                                Scope::EVENT_RECORD_HEADER);

    if (readScopeInstrIt != dsPktProc.erPreambleProc().end()) {
        auto& readScopeInstr = static_cast<BeginReadScopeInstr&>(**readScopeInstrIt);

        MemberTypeFinderInstrVisitor {
            readScopeInstr.proc(), "id",
            [&hasId](auto& instrLoc, const Index level) {
                instrLoc.proc->insert(std::next(instrLoc.it), std::make_shared<SetCurIdInstr>());
                hasId = true;
            }
        };
    }

    Proc::SharedIt insertPoint;

    if (readScopeInstrIt == dsPktProc.erPreambleProc().end()) {
        insertPoint = dsPktProc.erPreambleProc().begin();
    } else {
        insertPoint = std::next(readScopeInstrIt);
    }

    if (hasId) {
        dsPktProc.erPreambleProc().insert(insertPoint, std::make_shared<SetErtInstr>());
    } else {
        if (!dsPktProc.dst().eventRecordTypes().empty()) {
            assert(dsPktProc.dst().eventRecordTypes().size() == 1);

            const auto fixedId = (*dsPktProc.dst().eventRecordTypes().begin())->id();

            dsPktProc.erPreambleProc().insert(insertPoint, std::make_shared<SetErtInstr>(fixedId));
        }
    }
}

/*
 * This procedure instruction visitor calls a callback function `func`
 * for each "read unsigned integer" instruction recursively found in
 * `proc` with an unsigned integer data type mapped to a clock type.
 *
 * The callback function receives the procedure instruction location and
 * the unsigned integer type (containing the mapped clock type pointer)
 * so that it can insert an "update clock value" instruction with the
 * appropriate clock type index and size.
 */
class UpdateClkValInserterInstrVisitor :
    public CallerInstrVisitor
{
public:
    using Func = std::function<void (Scope scope, InstrLoc& instrLoc, const UnsignedIntegerType&)>;

public:
    explicit UpdateClkValInserterInstrVisitor(Proc& proc, Func func) :
        _func {std::move(func)}
    {
        this->_visitProc(proc);
    }

    void visit(ReadUIntInstr& instr) override
    {
        if (instr.uIntType().mappedClockType()) {
            _func(_curScope, _curInstrLoc, instr.uIntType());
        }
    }

    void visit(ReadUEnumInstr& instr) override
    {
        this->visit(static_cast<ReadUIntInstr&>(instr));
    }

    void visit(BeginReadStructInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticTextArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticUuidArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDynArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDynTextArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadVarUSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadVarSSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadScopeInstr& instr) override
    {
        this->_curScope = instr.scope();
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
    const Func _func;
    Scope _curScope;
};

void PktProcBuilder::_insertUpdateClkValInstrs()
{
    const auto insertUpdateClkValInstr = [this](const Scope scope, InstrLoc& instrLoc,
                                                const UnsignedIntegerType& intType) {
        const Index clkTypeIndex = _pktProc->clkTypeIndex(*intType.mappedClockType());
        auto& instrRead = static_cast<const ReadDataInstr&>(**instrLoc.it);
        Instr::SP instrToInsert;

        if (scope == Scope::PACKET_CONTEXT && instrRead.memberType() &&
                instrRead.memberType()->displayName() == "timestamp_end") {
            instrToInsert = std::make_shared<SetPktEndClkValInstr>(*intType.mappedClockType(),
                                                                   clkTypeIndex);
        } else {
            instrToInsert = std::make_shared<UpdateClkValInstr>(*intType.mappedClockType(),
                                                                clkTypeIndex, intType.length());
        }

        instrLoc.proc->insert(std::next(instrLoc.it), std::move(instrToInsert));
    };

    UpdateClkValInserterInstrVisitor {_pktProc->preambleProc(), insertUpdateClkValInstr};

    for (auto& dsPktProcPair : _pktProc->dsPktProcs()) {
        UpdateClkValInserterInstrVisitor {
            dsPktProcPair.second->pktPreambleProc(), insertUpdateClkValInstr
        };

        UpdateClkValInserterInstrVisitor {
            dsPktProcPair.second->erPreambleProc(), insertUpdateClkValInstr
        };

        dsPktProcPair.second->forEachErProc([&insertUpdateClkValInstr](ErProc& erProc) {
            UpdateClkValInserterInstrVisitor {erProc.proc(), insertUpdateClkValInstr};
        });
    }
}

class IntTypeReadIntInstrMapCreator :
    public CallerInstrVisitor
{
public:
    using Func = std::function<void (InstrLoc&)>;

public:
    explicit IntTypeReadIntInstrMapCreator(Proc& proc, Func func) :
        _func {std::move(func)}
    {
        this->_visitProc(proc);
    }

    void visit(ReadSIntInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadUIntInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadSEnumInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(ReadUEnumInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStructInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDynArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadVarUSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadVarSSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
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

    void _visit(ReadIntInstr& instr)
    {
        _func(_curInstrLoc);
    }

private:
    const Func _func;
};

PktProcBuilder::_IntTypeReadIntInstrMap PktProcBuilder::_createIntTypeReadIntInstrMap() const
{
    _IntTypeReadIntInstrMap map;

    const auto insertFunc = [&map](InstrLoc& instrLoc) {
        auto& readDataInstr = static_cast<const ReadDataInstr&>(**instrLoc.it);

        map[&readDataInstr.dt()] = instrLoc;
    };

    IntTypeReadIntInstrMapCreator {_pktProc->preambleProc(), insertFunc};

    for (auto& dsPktProcPair : _pktProc->dsPktProcs()) {
        auto& dsPktProc = dsPktProcPair.second;

        IntTypeReadIntInstrMapCreator {dsPktProc->pktPreambleProc(), insertFunc};
        IntTypeReadIntInstrMapCreator {dsPktProc->erPreambleProc(), insertFunc};

        dsPktProcPair.second->forEachErProc([&insertFunc](ErProc& erProc) {
            IntTypeReadIntInstrMapCreator {erProc.proc(), insertFunc};
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

    void visit(BeginReadStaticArrayInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadDynArrayInstr& instr) override
    {
        instr.lenPos(_func(instr.dynArrayType().lengthTypes()));
        this->_visit(instr);
    }

    void visit(BeginReadDynTextArrayInstr& instr) override
    {
        instr.lenPos(_func(instr.dynArrayType().lengthTypes()));
    }

    void visit(BeginReadVarUSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
    }

    void visit(BeginReadVarSSelInstr& instr) override
    {
        this->_visitBeginReadVarInstr(instr);
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

private:
    const GetPosFunc _func;
};

void PktProcBuilder::_setSavedValPoss()
{
    /*
     * Here's the idea.
     *
     * We swipe the whole packet procedure tree to find the "read
     * dynamic array" and "begin read variant" instructions, each of
     * which having a data type containing the lenght/selector types.
     *
     * For a given length/selector type, we can find the corresponding
     * "read integer" instruction as data types are unique.
     *
     * We insert "save value" instructions at the appropriate locations
     * in the associated procedure and then return the saved value
     * position to the visitor so that it changes the requesting
     * instruction.
     */
    auto intTypeReadIntInstrMap = this->_createIntTypeReadIntInstrMap();
    Index nextPos = 0;

    const auto getPosFunc = [&intTypeReadIntInstrMap, &nextPos](const DataTypeSet& dts) {
        // saved value position to update
        const auto pos = nextPos;

        /*
         * For each data type of `dts`, insert a "save value"
         * instruction after its corresponding "read integer"
         * instruction.
         */
        for (auto& dt : dts) {
            // find corresponding "read integer" instruction location
            auto& instrLoc = intTypeReadIntInstrMap[dt];

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

    void visit(const SignedIntegerType& dt) override
    {
        _pktProcBuilder->_buildReadSIntInstr(_memberType, dt, *_baseProc);
    }

    void visit(const UnsignedIntegerType& dt) override
    {
        _pktProcBuilder->_buildReadUIntInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FloatingPointNumberType& dt) override
    {
        _pktProcBuilder->_buildReadFloatInstr(_memberType, dt, *_baseProc);
    }

    void visit(const SignedEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadSEnumInstr(_memberType, dt, *_baseProc);
    }

    void visit(const UnsignedEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadUEnumInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StringType& dt) override
    {
        _pktProcBuilder->_buildReadStrInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StructureType& dt) override
    {
        _pktProcBuilder->_buildReadStructInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StaticArrayType& dt) override
    {
        _pktProcBuilder->_buildReadStaticArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StaticTextArrayType& dt) override
    {
        this->visit(static_cast<const StaticArrayType&>(dt));
    }

    void visit(const DynamicArrayType& dt) override
    {
        _pktProcBuilder->_buildReadDynArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const DynamicTextArrayType& dt) override
    {
        this->visit(static_cast<const DynamicArrayType&>(dt));
    }

    void visit(const VariantWithUnsignedSelectorType& dt) override
    {
        _pktProcBuilder->_buildReadVarUSelInstr(_memberType, dt, *_baseProc);
    }

    void visit(const VariantWithSignedSelectorType& dt) override
    {
        _pktProcBuilder->_buildReadVarSSelInstr(_memberType, dt, *_baseProc);
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

void PktProcBuilder::_buildReadSIntInstr(const StructureMemberType * const memberType,
                                         const DataType& dt, Proc& baseProc)
{
    assert(dt.isSignedIntegerType());
    buildBasicReadInstr<ReadSIntInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadUIntInstr(const StructureMemberType * const memberType,
                                         const DataType& dt, Proc& baseProc)
{
    assert(dt.isUnsignedIntegerType());
    buildBasicReadInstr<ReadUIntInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFloatInstr(const StructureMemberType * const memberType,
                                         const DataType& dt, Proc& baseProc)
{
    assert(dt.isFloatingPointNumberType());
    buildBasicReadInstr<ReadFloatInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadSEnumInstr(const StructureMemberType * const memberType,
                                          const DataType& dt, Proc& baseProc)
{
    assert(dt.isSignedEnumerationType());
    buildBasicReadInstr<ReadSEnumInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadUEnumInstr(const StructureMemberType * const memberType,
                                          const DataType& dt, Proc& baseProc)
{
    assert(dt.isUnsignedEnumerationType());
    buildBasicReadInstr<ReadUEnumInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadStrInstr(const StructureMemberType * const memberType,
                                        const DataType& dt, Proc& baseProc)
{
    assert(dt.isStringType());
    buildBasicReadInstr<ReadStrInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadStructInstr(const StructureMemberType * const memberType,
                                           const DataType& dt, Proc& baseProc)
{
    assert(dt.isStructureType());

    auto instr = std::make_shared<BeginReadStructInstr>(memberType, dt);

    for (const auto& innerMemberType : dt.asStructureType().memberTypes()) {
        this->_buildReadInstr(innerMemberType.get(), innerMemberType->type(), instr->proc());
    }

    auto endInstr = std::make_shared<EndReadCompoundInstr>(Instr::Kind::END_READ_STRUCT,
                                                           memberType, dt);

    instr->proc().pushBack(std::move(endInstr));
    baseProc.pushBack(std::move(instr));
}

void PktProcBuilder::_buildReadStaticArrayInstr(const StructureMemberType * const memberType,
                                                const DataType& dt, Proc& baseProc)
{
    assert(dt.isStaticArrayType());
    this->_buildReadArrayInstr<BeginReadStaticArrayInstr,
                               BeginReadStaticTextArrayInstr>(memberType, dt, baseProc,
                                                              Instr::Kind::END_READ_STATIC_ARRAY,
                                                              Instr::Kind::END_READ_STATIC_TEXT_ARRAY);
}

void PktProcBuilder::_buildReadDynArrayInstr(const StructureMemberType * const memberType,
                                             const DataType& dt, Proc& baseProc)
{
    assert(dt.isDynamicArrayType());
    this->_buildReadArrayInstr<BeginReadDynArrayInstr,
                               BeginReadDynTextArrayInstr>(memberType, dt, baseProc,
                                                           Instr::Kind::END_READ_DYN_ARRAY,
                                                           Instr::Kind::END_READ_DYN_TEXT_ARRAY);
}

void PktProcBuilder::_buildReadVarUSelInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    this->_buildReadVarInstr<BeginReadVarUSelInstr>(memberType,
                                                    dt.asVariantWithUnsignedSelectorType(),
                                                    baseProc);
}

void PktProcBuilder::_buildReadVarSSelInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    this->_buildReadVarInstr<BeginReadVarSSelInstr>(memberType,
                                                    dt.asVariantWithSignedSelectorType(), baseProc);
}

} // namespace internal
} // namespace yactfr
