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

#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/dyn-array-type.hpp>
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
     *    `SetExpectedPktContentLenInstr`, `SetPktMagicNumberInstr`,
     *    `UpdateDefClkValInstr`, and `SetPktEndDefClkValInstr` objects
     *    at the appropriate locations in the packet procedure.
     *
     * 4. Insert `SaveValInstr` objects where needed to accomodate
     *    subsequent "begin read dynamic array", "begin read
     *    dynamic-length string", and "begin read variant" instructions.
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

    void visit(BeginReadStructInstr& instr) override
    {
        this->_visit(instr);
    }

    void visit(BeginReadStaticArrayInstr& instr) override
    {
        if (_findWithTraceTypeUuidRole && instr.staticArrayType().hasTraceTypeUuidRole()) {
            _func(_curInstrLoc);
        }

        this->_visit(instr);
    }

    void visit(BeginReadStaticUuidArrayInstr& instr) override
    {
        this->visit(static_cast<BeginReadStaticArrayInstr&>(instr));
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

private:
    const boost::optional<UnsignedIntegerTypeRole> _uIntTypeRole;
    const bool _findWithTraceTypeUuidRole = false;
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

    InstrFinder {readScopeInstr.proc(), [&readArrayInstrIt](InstrLoc& instrLoc) {
        /*
         * Replace after this visitor finishes because it recurses into
         * this compound instruction afterwards so we cannot change it
         * in its back, effectively deleting the old shared pointer and
         * making a dangling pointer within the visitor.
         */
        readArrayInstrIt = instrLoc.it;
    }};

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
        assert((*instrLoc.it)->isReadFlUInt());

        const auto& readFixedLengthBitArrayInstr = static_cast<const ReadFlBitArrayInstr&>(**instrLoc.it);

        instrLoc.proc->insert(std::next(instrLoc.it),
                              std::make_shared<UpdateDefClkValInstr>(readFixedLengthBitArrayInstr.len()));
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
            readScopeInstr.proc(), UnsignedIntegerTypeRole::PACKET_ORIGIN_INDEX,
            [](auto& instrLoc) {
                instrLoc.proc->insert(std::next(instrLoc.it),
                                      std::make_shared<SetPktOriginIndexInstr>());
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

class FlIntTypeReadFlIntInstrMapCreator :
    public CallerInstrVisitor
{
public:
    using Func = std::function<void (InstrLoc&)>;

public:
    explicit FlIntTypeReadFlIntInstrMapCreator(Proc& proc, Func func) :
        _func {std::move(func)}
    {
        this->_visitProc(proc);
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

    void _visit(ReadFlIntInstr& instr)
    {
        _func(_curInstrLoc);
    }

private:
    const Func _func;
};

PktProcBuilder::_FlIntTypeReadFlIntInstrMap PktProcBuilder::_createFlIntTypeReadFlIntInstrMap() const
{
    _FlIntTypeReadFlIntInstrMap map;

    const auto insertFunc = [&map](InstrLoc& instrLoc) {
        auto& readDataInstr = static_cast<const ReadDataInstr&>(**instrLoc.it);

        map[&readDataInstr.dt()] = instrLoc;
    };

    FlIntTypeReadFlIntInstrMapCreator {_pktProc->preambleProc(), insertFunc};

    for (auto& dsPktProcPair : _pktProc->dsPktProcs()) {
        auto& dsPktProc = dsPktProcPair.second;

        FlIntTypeReadFlIntInstrMapCreator {dsPktProc->pktPreambleProc(), insertFunc};
        FlIntTypeReadFlIntInstrMapCreator {dsPktProc->erPreambleProc(), insertFunc};

        dsPktProcPair.second->forEachErProc([&insertFunc](ErProc& erProc) {
            FlIntTypeReadFlIntInstrMapCreator {erProc.proc(), insertFunc};
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

    void visit(BeginReadDlStrInstr& instr) override
    {
        instr.maxLenPos(_func(instr.dlStrType().maximumLengthTypes()));
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
     * We swipe the whole packet procedure tree to find the "begin read
     * dynamic array", "begin read dynamic-length string", and "begin
     * read variant" instructions, each of which having a data type
     * containing the lenght/selector types.
     *
     * For a given length/selector type, we can find the corresponding
     * "read fixed-length integer" instruction as data types are unique.
     *
     * We insert "save value" instructions at the appropriate locations
     * in the associated procedure and then return the saved value
     * position to the visitor so that it changes the requesting
     * instruction.
     */
    auto flIntTypeReadFlIntInstrMap = this->_createFlIntTypeReadFlIntInstrMap();
    Index nextPos = 0;

    const auto getPosFunc = [&flIntTypeReadFlIntInstrMap, &nextPos](const DataTypeSet& dts) {
        // saved value position to update
        const auto pos = nextPos;

        /*
         * For each data type of `dts`, insert a "save value"
         * instruction after its corresponding "read fixed-length
         * integer" instruction.
         */
        for (auto& dt : dts) {
            /*
             * Find corresponding "read fixed-length integer"
             * instruction location.
             */
            auto& instrLoc = flIntTypeReadFlIntInstrMap[dt];

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

    void visit(const SignedFixedLengthEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadFlSEnumInstr(_memberType, dt, *_baseProc);
    }

    void visit(const FixedLengthUnsignedEnumerationType& dt) override
    {
        _pktProcBuilder->_buildReadFlUEnumInstr(_memberType, dt, *_baseProc);
    }

    void visit(const NullTerminatedStringType& dt) override
    {
        _pktProcBuilder->_buildReadNtStrInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StructureType& dt) override
    {
        _pktProcBuilder->_buildReadStructInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StaticArrayType& dt) override
    {
        _pktProcBuilder->_buildReadStaticArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const StaticLengthStringType& dt) override
    {
        _pktProcBuilder->_buildReadSlStrInstr(_memberType, dt, *_baseProc);
    }

    void visit(const DynamicArrayType& dt) override
    {
        _pktProcBuilder->_buildReadDynArrayInstr(_memberType, dt, *_baseProc);
    }

    void visit(const DynamicLengthStringType& dt) override
    {
        _pktProcBuilder->_buildReadDlStrInstr(_memberType, dt, *_baseProc);
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
    assert(dt.isSignedFixedLengthEnumerationType());
    buildBasicReadInstr<ReadFlSEnumInstr>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadFlUEnumInstr(const StructureMemberType * const memberType,
                                            const DataType& dt, Proc& baseProc)
{
    assert(dt.isFixedLengthUnsignedEnumerationType());
    buildBasicReadInstr<ReadFlUEnumInstr>(memberType, dt, baseProc);
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
        this->_buildReadInstr(innerMemberType.get(), innerMemberType->type(), instr->proc());
    }

    auto endInstr = std::make_shared<EndReadDataInstr>(Instr::Kind::END_READ_STRUCT, memberType,
                                                       dt);

    instr->proc().pushBack(std::move(endInstr));
    baseProc.pushBack(std::move(instr));
}

void PktProcBuilder::_buildReadStaticArrayInstr(const StructureMemberType * const memberType,
                                                const DataType& dt, Proc& baseProc)
{
    assert(dt.isStaticArrayType());
    this->_buildReadInstrWithLen<BeginReadStaticArrayInstr,
                                 Instr::Kind::END_READ_STATIC_ARRAY>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadSlStrInstr(const StructureMemberType * const memberType,
                                                const DataType& dt, Proc& baseProc)
{
    assert(dt.isStaticLengthStringType());
    this->_buildReadInstrWithLen<BeginReadSlStrInstr,
                                 Instr::Kind::END_READ_SL_STR>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadDynArrayInstr(const StructureMemberType * const memberType,
                                             const DataType& dt, Proc& baseProc)
{
    assert(dt.isDynamicArrayType());
    this->_buildReadInstrWithLen<BeginReadDynArrayInstr,
                                 Instr::Kind::END_READ_DYN_ARRAY>(memberType, dt, baseProc);
}

void PktProcBuilder::_buildReadDlStrInstr(const StructureMemberType * const memberType,
                                          const DataType& dt, Proc& baseProc)
{
    assert(dt.isDynamicLengthStringType());
    this->_buildReadInstrWithLen<BeginReadDlStrInstr,
                                 Instr::Kind::END_READ_DL_STR>(memberType, dt, baseProc);
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
