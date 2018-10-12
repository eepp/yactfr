/*
 * Packet procedure builder.
 *
 * This builder uses a bunch of specialized procedure instruction
 * visitors which call it back. This is somewhat cleaner than having
 * our own recursive visitor implementation.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <functional>
#include <algorithm>
#include <boost/optional/optional.hpp>

#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/dynamic-text-array-type.hpp>
#include <yactfr/metadata/dynamic-array-type.hpp>

#include "packet-proc-builder.hpp"

namespace yactfr {
namespace internal {

/*
 * This data type visitor calls packet procedure builder's methods
 * depending on the visited object to build individual "read data"
 * procedure instructions.
 */
class InstrBuilderDataTypeVisitor :
    public DataTypeVisitor
{
public:
    explicit InstrBuilderDataTypeVisitor(PacketProcBuilder& packetProcBuilder,
                                         const std::string *fieldName,
                                         const std::string *fieldDisplayName,
                                         Proc& baseProc) :
        _packetProcBuilder {&packetProcBuilder},
        _fieldName {fieldName},
        _fieldDisplayName {fieldDisplayName},
        _baseProc {&baseProc}
    {
    }

    void visit(const SignedIntType& type) override
    {
        _packetProcBuilder->_buildInstrReadSignedInt(_fieldName,
                                                     _fieldDisplayName,
                                                     &type,
                                                     *_baseProc);
    }

    void visit(const UnsignedIntType& type) override
    {
        _packetProcBuilder->_buildInstrReadUnsignedInt(_fieldName,
                                                       _fieldDisplayName,
                                                       &type,
                                                       *_baseProc);
    }

    void visit(const FloatType& type) override
    {
        _packetProcBuilder->_buildInstrReadFloat(_fieldName,
                                                 _fieldDisplayName,
                                                 &type,
                                                 *_baseProc);
    }

    void visit(const SignedEnumType& type) override
    {
        _packetProcBuilder->_buildInstrReadSignedEnum(_fieldName,
                                                      _fieldDisplayName,
                                                      &type,
                                                      *_baseProc);
    }

    void visit(const UnsignedEnumType& type) override
    {
        _packetProcBuilder->_buildInstrReadUnsignedEnum(_fieldName,
                                                        _fieldDisplayName,
                                                        &type,
                                                        *_baseProc);
    }

    void visit(const StringType& type) override
    {
        _packetProcBuilder->_buildInstrReadString(_fieldName,
                                                  _fieldDisplayName,
                                                  &type,
                                                  *_baseProc);
    }

    void visit(const StructType& type) override
    {
        _packetProcBuilder->_buildInstrReadStruct(_fieldName,
                                                  _fieldDisplayName,
                                                  &type,
                                                  *_baseProc);
    }

    void visit(const StaticArrayType& type) override
    {
        _packetProcBuilder->_buildInstrReadStaticArray(_fieldName,
                                                       _fieldDisplayName,
                                                       &type,
                                                       *_baseProc);
    }

    void visit(const StaticTextArrayType& type) override
    {
        this->visit(static_cast<const StaticArrayType&>(type));
    }

    void visit(const DynamicArrayType& type) override
    {
        _packetProcBuilder->_buildInstrReadDynamicArray(_fieldName,
                                                        _fieldDisplayName,
                                                        &type,
                                                        *_baseProc);
    }

    void visit(const DynamicTextArrayType& type) override
    {
        this->visit(static_cast<const DynamicArrayType&>(type));
    }

    void visit(const VariantType& type) override
    {
        _packetProcBuilder->_buildInstrReadVariantUnknownTag(_fieldName,
                                                             _fieldDisplayName,
                                                             &type,
                                                             *_baseProc);
    }

private:
    PacketProcBuilder *_packetProcBuilder;
    const std::string *_fieldName;
    const std::string *_fieldDisplayName;
    Proc *_baseProc;
};

class InstrCallerVisitor :
    public InstrVisitor
{
protected:
    void _visitProc(Proc& proc)
    {
        // save current procedure to restore it later
        const auto oldProc = _curProc;
        const auto oldIter = _curIter;

        ++_curLevel;

        for (auto it = std::begin(proc); it != std::end(proc); ++it) {
            _curIter = it;

           auto& instrSp = *it;

            /*
             * Set current procedure for each iteration because it can
             * change during instrSp->accept().
             */
            _curProc = &proc;
            instrSp->accept(*this);
        }

        // restore stuff
        --_curLevel;
        _curProc = oldProc;
        _curIter = oldIter;
    }

protected:
    Proc *_curProc = nullptr;
    Proc::SharedIterator _curIter;
    Index _curLevel = 0;
};

/*
 * This procedure instruction visitor takes a procedure `proc`,
 * finds all the contained "read data" instructions of which the
 * display name is `fieldName`, and calls `callback` with the procedure
 * in which the instruction was found and its position as an iterator.
 * The callback also receives the level of the instruction, where the
 * instructions found directly in `proc` are at level 0.
 *
 * The iterator allows the callback to insert instructions after it.
 */
class InstrFieldFinderVisitor :
    public InstrCallerVisitor
{
public:
    using Callback = std::function<void (Proc&, Proc::SharedIterator, Index)>;

public:
    explicit InstrFieldFinderVisitor(Proc& proc,
                                     const std::string& fieldName,
                                     Callback callback) :
        _fieldName {&fieldName},
        _callback {callback}
    {
        this->_visitProc(proc);
    }

    void visit(InstrReadSignedInt& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadUnsignedInt& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadFloat& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadSignedEnum& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadUnsignedEnum& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadString& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStruct& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticTextArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticUuidArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicTextArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadVariantUnknownTag& instr) override
    {
        for (auto& optionPair : instr.options()) {
            this->_visitProc(optionPair.second);
        }
    }

    void visit(InstrBeginReadScope& instr) override
    {
        this->_visitProc(instr.proc());
    }

private:
    void _visit(InstrBeginReadCompound& instr)
    {
        this->_visit(static_cast<InstrReadData&>(instr));
        this->_visitProc(instr.proc());
    }

    void _visit(InstrReadData& instr)
    {
        if (instr.fieldDisplayName() &&
                *instr.fieldDisplayName() == *_fieldName) {
            _callback(*_curProc, _curIter, _curLevel - 1);
        }
    }

private:
    const std::string *_fieldName;
    Callback _callback;
};

/*
 * This procedure instruction visitor calls a callback function
 * `callback` for each "read int" instruction recursively found in
 * `proc` with an int data type mapped to a clock type by name.
 *
 * The callback receives the containing procedure, the instruction's
 * iterator, and the integer type (containing the mapped clock type's
 * name) so that it can insert an "update clock value" instruction with
 * the appropriate clock type index and size.
 */
class UpdateClockValueInserterInstrVisitor :
    public InstrCallerVisitor
{
public:
    using Callback = std::function<void (Scope scope, Proc&,
                                         Proc::SharedIterator,
                                         const IntType&)>;

public:
    explicit UpdateClockValueInserterInstrVisitor(Proc& proc,
                                                  Callback callback) :
        _callback {callback}
    {
        this->_visitProc(proc);
    }

    void visit(InstrReadSignedInt& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadUnsignedInt& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadSignedEnum& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrReadUnsignedEnum& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStruct& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticTextArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticUuidArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicTextArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadVariantUnknownTag& instr) override
    {
        for (auto& optionPair : instr.options()) {
            this->_visitProc(optionPair.second);
        }
    }

    void visit(InstrBeginReadScope& instr) override
    {
        this->_curScope = instr.scope();
        this->_visitProc(instr.proc());
    }

private:
    void _visit(InstrBeginReadCompound& instr)
    {
        this->_visitProc(instr.proc());
    }

    void _visit(InstrReadIntBase& instr)
    {
        if (instr.intType().mappedClockTypeName()) {
            _callback(_curScope, *_curProc, _curIter, instr.intType());
        }
    }

private:
    Callback _callback;
    Scope _curScope;
};

class InstrSaveValueInserterVisitor :
    public InstrCallerVisitor
{
public:
    using GetPos = std::function<Index (const FieldRef&)>;

public:
    explicit InstrSaveValueInserterVisitor(Proc& proc, const Scope scope,
                                           GetPos callback) :
        _scope {scope},
        _callback {callback}
    {
        this->_visitProc(proc);
    }

    void visit(InstrBeginReadStruct& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticTextArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticUuidArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicArray& instr) override
    {
        auto pos = this->_getPos(instr.dynamicArrayType().length());

        if (pos) {
            instr.lengthPos(*pos);
        }

        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicTextArray& instr) override
    {
        this->visit(static_cast<InstrBeginReadDynamicArray&>(instr));
    }

    void visit(InstrBeginReadVariantUnknownTag& instr) override
    {
        auto pos = this->_getPos(instr.variantType().tag());

        if (pos) {
            instr.tagPos(*pos);
        }

        for (auto& optionPair : instr.options()) {
            this->_visitProc(optionPair.second);
        }
    }

    void visit(InstrBeginReadScope& instr) override
    {
        this->_visitProc(instr.proc());
    }

private:
    void _visit(InstrBeginReadCompound& instr)
    {
        this->_visitProc(instr.proc());
    }

    boost::optional<GetPos::result_type> _getPos(const FieldRef& fieldRef)
    {
        if (fieldRef.scope() != _scope) {
            return boost::none;
        }

        return _callback(fieldRef);
    }

private:
    const Scope _scope;
    GetPos _callback;
};

/*
 * This visitor visits "read unknown variant" instructions in postorder
 * to replace nested instructions before their potentially container
 * instruction ("read unknown variant" instructions which contain "read
 * unknown variant" instructions).
 */
class InstrVariantUnknownTagReplacerVisitor :
    public InstrCallerVisitor
{
public:
    using Callback = std::function<void (Proc::SharedIterator)>;

public:
    explicit InstrVariantUnknownTagReplacerVisitor(Proc& proc,
                                                   Callback callback) :
        _callback {callback}
    {
        this->_visitProc(proc);
    }

    void visit(InstrBeginReadStruct& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticTextArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadStaticUuidArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadDynamicTextArray& instr) override
    {
        this->_visit(instr);
    }

    void visit(InstrBeginReadVariantUnknownTag& instr) override
    {
        for (auto& optionPair : instr.options()) {
            /*
             * If this option's procedure contains a "read unknown
             * variant" instruction itself, it is replaced during this
             * visit so that, after this loop, we are sure that the
             * option procedures do not contain any "read unknown
             * variant" instruction.
             */
            this->_visitProc(optionPair.second);
        }

        // replace this instruction
        _callback(_curIter);
    }

    void visit(InstrBeginReadScope& instr) override
    {
        this->_visitProc(instr.proc());
    }

private:
    void _visit(InstrBeginReadCompound& instr)
    {
        this->_visitProc(instr.proc());
    }

private:
    Callback _callback;
};

PacketProcBuilder::PacketProcBuilder(const TraceType& traceType) :
    _traceType {&traceType}
{
    this->_buildPacketProc();
    _packetProc->buildRawProcFromShared();

    for (auto& idDstPacketProcPair : _packetProc->dataStreamTypePacketProcs()) {
        idDstPacketProcPair.second->setEventRecordAlignment();
    }
}

void PacketProcBuilder::_buildPacketProc()
{
    /*
     * The builder has multiple phases:
     *
     * 1. Translate from metadata objects to procedure objects without
     *    any special rule. After this phase, the "read variant"
     *    instructions are only InstrBeginReadVariantUnknownTag objects.
     *
     * 2. In the trace's preamble procedure's InstrBeginReadScope object,
     *    find a first-level `uuid` "read array" instruction and replace
     *    it with a InstrBeginReadStaticUuidArray object.
     *
     * 3. Insert InstrSetCurrentId, InstrSetDataStreamType,
     *    InstrSetEventRecordType, InstrSetDataStreamId,
     *    InstrSetPacketSequenceNumber, InstrSetPacketTotalSize,
     *    InstrSetPacketContentSize, and InstrValidateMagic
     *    objects at the appropriate locations in the packet procedure.
     *
     * 4. Insert InstrUpdateClockValue objects at appropriate
     *    locations.
     *
     * 5. Insert InstrSaveValue objects where needed to accomodate
     *    following "read dynamic array/variant" instructions.
     *
     * 6. Replace InstrBeginReadVariantUnknownTag objects with
     *    InstrBeginReadVariantSignedTag or
     *    InstrBeginReadVariantUnsignedTag objects depending on the
     *    tag's signedness.
     *
     * 7. Insert "end procedure" instructions at the end of each
     *    top-level procedure.
     */
    this->_buildBasePacketProc();
    this->_subUuidInstr();
    this->_insertSpecialInstrs();
    this->_insertInstrUpdateClockValue();
    this->_setSavedValuePos();
    this->_subInstrBeginReadVariantUnknownTag();
    this->_insertEndInstrs();
}

static bool instrIsSpecificScope(const Instr& instr, const Scope scope)
{
    if (!instr.isBeginReadScope()) {
        return false;
    }

    auto& instrReadScope = static_cast<const InstrBeginReadScope&>(instr);

    return instrReadScope.scope() == scope;
}

static Proc::SharedIterator firstInstrBeginReadScope(Proc& proc, const Scope scope)
{
    for (auto it = std::begin(proc); it != std::end(proc); ++it) {
        auto& instr = *it;

        if (instrIsSpecificScope(*instr, scope)) {
            return it;
        }
    }

    return std::end(proc);
}

void PacketProcBuilder::_subUuidInstr()
{
    auto instrReadScopeIt = firstInstrBeginReadScope(_packetProc->preambleProc(),
                                                     Scope::PACKET_HEADER);

    if (instrReadScopeIt != std::end(_packetProc->preambleProc())) {
        auto& instrReadScope = static_cast<InstrBeginReadScope&>(**instrReadScopeIt);
        Proc::SharedIterator instrReadArrayIt;
        InstrReadData *instrReadArray = nullptr;

        InstrFieldFinderVisitor {
            instrReadScope.proc(), "uuid",
            [&instrReadArrayIt, &instrReadArray](Proc& proc,
                                                 Proc::SharedIterator it,
                                                 Index level) {
                if (level != 1) {
                    return;
                }

                /*
                 * Replace after this visitor finishes because it
                 * recurses into this compound instruction afterwards so
                 * we cannot change it in its back, effectively deleting
                 * the old shared pointer and making a dangling pointer
                 * within the visitor.
                 */
                instrReadArray = static_cast<InstrReadData *>(it->get());
                instrReadArrayIt = it;
            }
        };

        if (instrReadArray) {
            *instrReadArrayIt = std::make_shared<InstrBeginReadStaticUuidArray>(instrReadArray->fieldName(),
                                                                                instrReadArray->fieldDisplayName(),
                                                                                instrReadArray->type());

            auto& instrReadUuidArray = static_cast<InstrBeginReadStaticArray&>(**instrReadArrayIt);

            this->_buildInstrRead(instrReadUuidArray.fieldName(),
                                  instrReadUuidArray.fieldDisplayName(),
                                  &instrReadUuidArray.staticArrayType().elemType(),
                                  instrReadUuidArray.proc());
        }
    }
}

void PacketProcBuilder::_insertSpecialInstrs()
{
    this->_insertSpecialInstrsPacketProcPreambleProc();

    for (auto& idDstPacketProcPair : _packetProc->dataStreamTypePacketProcs()) {
        this->_insertSpecialInstrsDstPacketProc(*idDstPacketProcPair.second);
    }
}

void PacketProcBuilder::_insertSpecialInstrsPacketProcPreambleProc()
{
    bool hasStreamId = false;
    auto instrReadScopeIt = firstInstrBeginReadScope(_packetProc->preambleProc(),
                                                     Scope::PACKET_HEADER);
    InstrBeginReadScope *instrReadScope = nullptr;

    if (instrReadScopeIt != std::end(_packetProc->preambleProc())) {
        instrReadScope = static_cast<InstrBeginReadScope *>(instrReadScopeIt->get());

        InstrFieldFinderVisitor {
            instrReadScope->proc(), "magic",
            [](Proc& proc, Proc::SharedIterator it, Index level) {
                if (level != 1) {
                    return;
                }

                auto instr = std::make_shared<InstrSetPacketMagicNumber>();

                proc.insert(std::next(it), std::move(instr));
            }
        };

        InstrFieldFinderVisitor {
            instrReadScope->proc(), "stream_id",
            [&hasStreamId](Proc& proc, Proc::SharedIterator it, Index level) {
                auto instr = std::make_shared<InstrSetCurrentId>();

                proc.insert(std::next(it), std::move(instr));
                hasStreamId = true;
            }
        };

        InstrFieldFinderVisitor {
            instrReadScope->proc(), "stream_instance_id",
            [](Proc& proc, Proc::SharedIterator it, Index level) {
                if (level != 1) {
                    return;
                }

                auto instr = std::make_shared<InstrSetDataStreamId>();

                proc.insert(std::next(it), std::move(instr));
            }
        };
    }

    Proc::SharedIterator insertPoint;

    if (instrReadScopeIt == std::end(_packetProc->preambleProc())) {
        insertPoint = std::end(_packetProc->preambleProc());
    } else {
        insertPoint = std::next(instrReadScopeIt);
    }

    if (hasStreamId) {
        auto instrSetDst = std::make_shared<InstrSetDataStreamType>(boost::none);

        _packetProc->preambleProc().insert(insertPoint, std::move(instrSetDst));
    } else {
        if (!_traceType->dataStreamTypes().empty()) {
            assert(_traceType->dataStreamTypes().size() == 1);

            auto fixedId = (*std::begin(_traceType->dataStreamTypes()))->id();
            auto instrSetDst = std::make_shared<InstrSetDataStreamType>(fixedId);

            _packetProc->preambleProc().insert(insertPoint, std::move(instrSetDst));
        }
    }
}

void PacketProcBuilder::_insertSpecialInstrsDstPacketProc(DataStreamTypePacketProc& dstPacketProc)
{
    bool hasId = false;
    auto instrReadScopeIt = firstInstrBeginReadScope(dstPacketProc.packetPreambleProc(),
                                                     Scope::PACKET_CONTEXT);
    InstrBeginReadScope *instrReadScope = nullptr;

    if (instrReadScopeIt != std::end(dstPacketProc.packetPreambleProc())) {
        instrReadScope = static_cast<InstrBeginReadScope *>(instrReadScopeIt->get());

        InstrFieldFinderVisitor {
            instrReadScope->proc(), "packet_size",
            [](Proc& proc, Proc::SharedIterator it, Index level) {
                if (level != 1) {
                    return;
                }

                auto instr = std::make_shared<InstrSetPacketTotalSize>();

                proc.insert(std::next(it), std::move(instr));
            }
        };

        InstrFieldFinderVisitor {
            instrReadScope->proc(), "content_size",
            [](Proc& proc, Proc::SharedIterator it, Index level) {
                if (level != 1) {
                    return;
                }

                auto instr = std::make_shared<InstrSetPacketContentSize>();

                proc.insert(std::next(it), std::move(instr));
            }
        };

        InstrFieldFinderVisitor {
            instrReadScope->proc(), "packet_seq_num",
            [](Proc& proc, Proc::SharedIterator it, Index level) {
                if (level != 1) {
                    return;
                }

                auto instr = std::make_shared<InstrSetPacketOriginIndex>();

                proc.insert(std::next(it), std::move(instr));
            }
        };
    }

    instrReadScopeIt = firstInstrBeginReadScope(dstPacketProc.eventRecordPreambleProc(),
                                                Scope::EVENT_RECORD_HEADER);
    instrReadScope = nullptr;


    if (instrReadScopeIt != std::end(dstPacketProc.eventRecordPreambleProc())) {
        instrReadScope = static_cast<InstrBeginReadScope *>(instrReadScopeIt->get());

        InstrFieldFinderVisitor {
            instrReadScope->proc(), "id",
            [&hasId](Proc& proc, Proc::SharedIterator it, Index level) {
                auto instr = std::make_shared<InstrSetCurrentId>();

                proc.insert(std::next(it), std::move(instr));
                hasId = true;
            }
        };
    }

    Proc::SharedIterator insertPoint;

    if (instrReadScopeIt == std::end(dstPacketProc.eventRecordPreambleProc())) {
        insertPoint = std::begin(dstPacketProc.eventRecordPreambleProc());
    } else {
        insertPoint = std::next(instrReadScopeIt);
    }

    if (hasId) {
        auto instrSetErt = std::make_shared<InstrSetEventRecordType>(boost::none);

        dstPacketProc.eventRecordPreambleProc().insert(insertPoint,
                                                       std::move(instrSetErt));
    } else {
        auto& dst = dstPacketProc.dataStreamType();

        if (!dst.eventRecordTypes().empty()) {
            assert(dst.eventRecordTypes().size() == 1);

            auto fixedId = (*std::begin(dst.eventRecordTypes()))->id();
            auto instrSetErt = std::make_shared<InstrSetEventRecordType>(fixedId);

            dstPacketProc.eventRecordPreambleProc().insert(insertPoint,
                                                           std::move(instrSetErt));
        }
    }
}

void PacketProcBuilder::_insertInstrUpdateClockValue()
{
    auto updateClockValueFn = [this](Scope scope, Proc& proc, Proc::SharedIterator it,
                                     const IntType& intType) {
        const Index ccIndex = _packetProc->clockTypeIndex(*intType.mappedClockTypeName());
        auto& clockType = *_traceType->findClockType(*intType.mappedClockTypeName());
        auto& instrRead = static_cast<const InstrReadData&>(**it);
        Instr::SP instrToInsert;

        if (scope == Scope::PACKET_CONTEXT &&
                instrRead.fieldDisplayName() &&
                *instrRead.fieldDisplayName() == "timestamp_end") {
            instrToInsert = std::make_shared<InstrSetPacketEndClockValue>(clockType,
                                                                          ccIndex);
        } else {
            instrToInsert = std::make_shared<InstrUpdateClockValue>(clockType, ccIndex,
                                                                    intType.size());
        }

        proc.insert(std::next(it), std::move(instrToInsert));
    };

    UpdateClockValueInserterInstrVisitor {
        _packetProc->preambleProc(), updateClockValueFn
    };

    for (auto& dstPacketProcPair : _packetProc->dataStreamTypePacketProcs()) {
        UpdateClockValueInserterInstrVisitor {
            dstPacketProcPair.second->packetPreambleProc(), updateClockValueFn
        };

        UpdateClockValueInserterInstrVisitor {
            dstPacketProcPair.second->eventRecordPreambleProc(), updateClockValueFn
        };

        dstPacketProcPair.second->forEachEventRecordTypeProc([&updateClockValueFn](EventRecordTypeProc& ertProc) {
            UpdateClockValueInserterInstrVisitor {
                ertProc.proc(), updateClockValueFn
            };
        });
    }
}

void PacketProcBuilder::_setSavedValuePos()
{
    /*
     * Here's the idea. We swipe the whole packet procedure tree to find
     * the "read dynamic array/variant" instructions which have a data
     * type which refers to a specific scope for the length/tag. We
     * insert "save value" instructions at the appropriate locations in
     * the scope's associated procedure and return the saved value
     * position to the visitor so that it changes the requesting
     * instruction.
     *
     * After each swipe, we keep the current "next" position so as to
     * restart at that location for the swipes targeting the same
     * following scope.
     *
     * For example, if the Scope::PACKET_HEADER swipe finishes with a
     * current saved value position vector of size 7, then we know that,
     * FOR EACH data stream type packet procedure to swipe, the
     * positions for the saved values of the Scope::PACKET_CONTEXT scope
     * can start at index 7. And by this I mean all the saved values of
     * all the Scope::PACKET_CONTEXT scopes can start at index 7.
     *
     * This trick saves space because we know that it will never happen
     * that we read two different packet contexts within the same
     * packet, or two payloads within the same event record, for
     * example. Thus we don't need to allocate two distinct saved values
     * for two different event payloads: they can overwrite each other's
     * saved values.
     */
    DataStreamTypePacketProc *curDstPacketProc = nullptr;
    EventRecordTypeProc *curErtProc = nullptr;
    Index nextPos = 0;
    Index maxPos = 0;

    auto getPosFunc = [&curDstPacketProc, &curErtProc, &nextPos,
                       &maxPos, this](const FieldRef& fieldRef) {
        /*
         * Our job here is to find a position at which to save the value
         * located at `fieldRef`.
         *
         * Our first task is to reach the equivalent "read int"
         * instruction.
         *
         * Then, from this instruction, we check if there's any
         * following "save value" instruction until the next "read data"
         * instruction. If there is, that's the position to return.
         * Otherwise, we allocate a new saved value (use, then increment
         * `nextPos`), and we insert a "save value" instruction after
         * the "read int" instruction we found.
         */
        InstrLocation loc;

        switch (fieldRef.scope()) {
        case Scope::PACKET_HEADER:
            loc = _packetProc->findInstr(fieldRef);
            break;

        case Scope::PACKET_CONTEXT:
        case Scope::EVENT_RECORD_HEADER:
        case Scope::EVENT_RECORD_FIRST_CONTEXT:
            assert(curDstPacketProc);
            loc = curDstPacketProc->findInstr(fieldRef);
            break;

        case Scope::EVENT_RECORD_SECOND_CONTEXT:
        case Scope::EVENT_RECORD_PAYLOAD:
            assert(curErtProc);
            loc = curErtProc->findInstr(fieldRef);
        }

        assert(loc.proc);

        boost::optional<Index> pos;

        for (auto it = std::next(loc.it); it != std::end(*loc.proc); ++it) {
            auto& instr = **it;

            if (instr.kind() == Instr::Kind::SAVE_VALUE) {
                auto& instrSaveValue = static_cast<InstrSaveValue&>(instr);

                pos = instrSaveValue.pos();
                break;
            }

            if (instr.isReadData()) {
                break;
            }
        }

        if (!pos) {
            // allocate new saved value
            pos = nextPos;
            ++nextPos;
            maxPos = std::max(maxPos, nextPos);

            // insert "save value" instruction after the "read data" instruction
            auto instr = std::make_shared<InstrSaveValue>(*pos);

            loc.proc->insert(std::next(loc.it), std::move(instr));
        }

        assert(pos);
        return *pos;
    };

    // packet header
    InstrSaveValueInserterVisitor {_packetProc->preambleProc(),
                                   Scope::PACKET_HEADER, getPosFunc};

    for (auto& dstPacketProcPair : _packetProc->dataStreamTypePacketProcs()) {
        auto& dstPacketProc = dstPacketProcPair.second;

        InstrSaveValueInserterVisitor {dstPacketProc->packetPreambleProc(),
                                       Scope::PACKET_HEADER, getPosFunc};
        InstrSaveValueInserterVisitor {dstPacketProc->eventRecordPreambleProc(),
                                       Scope::PACKET_HEADER, getPosFunc};

        dstPacketProcPair.second->forEachEventRecordTypeProc([&getPosFunc](EventRecordTypeProc& ertProc) {
            InstrSaveValueInserterVisitor {ertProc.proc(),
                                           Scope::PACKET_HEADER, getPosFunc};
        });
    }

    const auto packetContextNextPos = nextPos;

    for (auto& dstPacketProcPair : _packetProc->dataStreamTypePacketProcs()) {
        auto& dstPacketProc = dstPacketProcPair.second;

        curDstPacketProc = dstPacketProc.get();

        // packet context
        nextPos = packetContextNextPos;
        InstrSaveValueInserterVisitor {dstPacketProc->packetPreambleProc(),
                                       Scope::PACKET_CONTEXT, getPosFunc};
        InstrSaveValueInserterVisitor {dstPacketProc->eventRecordPreambleProc(),
                                       Scope::PACKET_CONTEXT, getPosFunc};

        dstPacketProc->forEachEventRecordTypeProc([&getPosFunc](EventRecordTypeProc& ertProc) {
            InstrSaveValueInserterVisitor {ertProc.proc(),
                                           Scope::PACKET_CONTEXT,
                                           getPosFunc};
        });

        // event record header
        InstrSaveValueInserterVisitor {dstPacketProc->eventRecordPreambleProc(),
                                       Scope::EVENT_RECORD_HEADER,
                                       getPosFunc};

        dstPacketProc->forEachEventRecordTypeProc([&getPosFunc](EventRecordTypeProc& ertProc) {
            InstrSaveValueInserterVisitor {ertProc.proc(),
                                           Scope::EVENT_RECORD_HEADER,
                                           getPosFunc};
        });

        // event record first context
        InstrSaveValueInserterVisitor {dstPacketProc->eventRecordPreambleProc(),
                                       Scope::EVENT_RECORD_FIRST_CONTEXT,
                                       getPosFunc};

        dstPacketProc->forEachEventRecordTypeProc([&getPosFunc](EventRecordTypeProc& ertProc) {
            InstrSaveValueInserterVisitor {ertProc.proc(),
                                           Scope::EVENT_RECORD_FIRST_CONTEXT,
                                           getPosFunc};
        });

        const auto eventRecordSecondContextNextPos = nextPos;

        dstPacketProc->forEachEventRecordTypeProc([&getPosFunc, &curErtProc,
                                                   &nextPos,
                                                   &eventRecordSecondContextNextPos](EventRecordTypeProc& ertProc) {
            curErtProc = &ertProc;

            // event record second context
            nextPos = eventRecordSecondContextNextPos;
            InstrSaveValueInserterVisitor {ertProc.proc(),
                                           Scope::EVENT_RECORD_SECOND_CONTEXT,
                                           getPosFunc};

            // event record payload
            InstrSaveValueInserterVisitor {ertProc.proc(),
                                           Scope::EVENT_RECORD_PAYLOAD,
                                           getPosFunc};
        });
    }

    _packetProc->savedValuesCount(maxPos);
}

void PacketProcBuilder::_subInstrBeginReadVariantUnknownTag()
{
    DataStreamTypePacketProc *curDstPacketProc = nullptr;
    EventRecordTypeProc *curErtProc = nullptr;

    auto callback = [&curDstPacketProc, &curErtProc, this](Proc::SharedIterator it) {
        /*
         * In this callback we need to find the variant type's tag type
         * in order to replace it with the appropriate
         * InstrReadVariantXTag and to populate its range
         * procedures. `curScope` indicates where to search.
         */
        assert((*it)->kind() == Instr::Kind::BEGIN_READ_VARIANT_UNKNOWN_TAG);

        auto& instrReadUnkVariant = static_cast<InstrBeginReadVariantUnknownTag&>(**it);
        const DataType *tagType = nullptr;
        auto& tag = instrReadUnkVariant.variantType().tag();

        switch (tag.scope()) {
        case Scope::PACKET_HEADER:
            tagType = _traceType->findDataType(tag);
            break;

        case Scope::PACKET_CONTEXT:
        case Scope::EVENT_RECORD_HEADER:
        case Scope::EVENT_RECORD_FIRST_CONTEXT:
            assert(curDstPacketProc);
            tagType = curDstPacketProc->dataStreamType().findDataType(tag);
            break;

        case Scope::EVENT_RECORD_SECOND_CONTEXT:
        case Scope::EVENT_RECORD_PAYLOAD:
            assert(curErtProc);
            tagType = curErtProc->eventRecordType().findDataType(tag);
            break;
        }

        assert(tagType);

        // create concrete "read variant" instruction
        Instr::SP instrReadVariant;

        if (tagType->isSignedEnumType()) {
            instrReadVariant = std::make_shared<InstrBeginReadVariantSignedTag>(instrReadUnkVariant,
                                                                                *tagType->asSignedEnumType());
        } else if (tagType->isUnsignedEnumType()) {
            instrReadVariant = std::make_shared<InstrBeginReadVariantUnsignedTag>(instrReadUnkVariant,
                                                                                *tagType->asUnsignedEnumType());
        } else {
            abort();
        }

        // replace instruction
        *it = std::move(instrReadVariant);
    };

    InstrVariantUnknownTagReplacerVisitor {
        _packetProc->preambleProc(), callback
    };

    for (auto& dstPacketProcPair : _packetProc->dataStreamTypePacketProcs()) {
        auto& dstPacketProc = dstPacketProcPair.second;

        curDstPacketProc = dstPacketProc.get();

        InstrVariantUnknownTagReplacerVisitor {
            dstPacketProc->packetPreambleProc(), callback
        };
        InstrVariantUnknownTagReplacerVisitor {
            dstPacketProc->eventRecordPreambleProc(), callback
        };

        dstPacketProc->forEachEventRecordTypeProc([&callback, &curErtProc](EventRecordTypeProc& ertProc) {
            curErtProc = &ertProc;

            InstrVariantUnknownTagReplacerVisitor {ertProc.proc(), callback};
        });
    }
}

template <typename InstrT>
void insertEndInstr(Proc& proc)
{
    proc.pushBack(std::make_shared<InstrT>());
}

void PacketProcBuilder::_insertEndInstrs()
{
    insertEndInstr<InstrEndPacketPreambleProc>(_packetProc->preambleProc());

    for (auto& dstPacketProcPair : _packetProc->dataStreamTypePacketProcs()) {
        auto& dstPacketProc = dstPacketProcPair.second;

        insertEndInstr<InstrEndDstPacketPreambleProc>(dstPacketProc->packetPreambleProc());
        insertEndInstr<InstrEndDstErtPreambleProc>(dstPacketProc->eventRecordPreambleProc());
        dstPacketProc->forEachEventRecordTypeProc([](EventRecordTypeProc& ertProc) {
            insertEndInstr<InstrEndErtProc>(ertProc.proc());
        });
    }
}

void PacketProcBuilder::_buildBasePacketProc()
{
    _packetProc = std::make_unique<PacketProc>(*_traceType);

    this->_buildInstrReadScope(Scope::PACKET_HEADER,
                               _traceType->packetHeaderType(),
                               _packetProc->preambleProc());

    for (auto& dstUp : _traceType->dataStreamTypes()) {
        auto dstPacketProc = this->_buildDataStreamTypePacketProc(*dstUp);

        assert(dstPacketProc);
        _packetProc->dataStreamTypePacketProcs()[dstUp->id()] = std::move(dstPacketProc);
    }
}

std::unique_ptr<DataStreamTypePacketProc> PacketProcBuilder::_buildDataStreamTypePacketProc(const DataStreamType& dataStreamType)
{
    auto dstPacketProc = std::make_unique<DataStreamTypePacketProc>(dataStreamType);
    this->_buildInstrReadScope(Scope::PACKET_CONTEXT,
                               dataStreamType.packetContextType(),
                               dstPacketProc->packetPreambleProc());
    this->_buildInstrReadScope(Scope::EVENT_RECORD_HEADER,
                               dataStreamType.eventRecordHeaderType(),
                               dstPacketProc->eventRecordPreambleProc());
    this->_buildInstrReadScope(Scope::EVENT_RECORD_FIRST_CONTEXT,
                               dataStreamType.eventRecordFirstContextType(),
                               dstPacketProc->eventRecordPreambleProc());

    for (auto& ertUp : dataStreamType.eventRecordTypes()) {
        auto ertProc = this->_buildEventRecordTypeProc(*ertUp);

        assert(ertProc);
        dstPacketProc->addEventRecordTypeProc(std::move(ertProc));
    }

    return dstPacketProc;
}

std::unique_ptr<EventRecordTypeProc> PacketProcBuilder::_buildEventRecordTypeProc(const EventRecordType& eventRecordType)
{
    auto ertProc = std::make_unique<EventRecordTypeProc>(eventRecordType);
    this->_buildInstrReadScope(Scope::EVENT_RECORD_SECOND_CONTEXT,
                               eventRecordType.secondContextType(),
                               ertProc->proc());
    this->_buildInstrReadScope(Scope::EVENT_RECORD_PAYLOAD,
                               eventRecordType.payloadType(),
                               ertProc->proc());
    return ertProc;
}

void PacketProcBuilder::_buildInstrReadScope(const Scope scope,
                                             const DataType *ft, Proc& baseProc)
{
    if (!ft) {
        return;
    }

    auto instrReadScope = std::make_shared<InstrBeginReadScope>(scope,
                                                                ft->alignment());

    this->_buildInstrRead(nullptr, nullptr, ft, instrReadScope->proc());
    instrReadScope->proc().pushBack(std::make_shared<InstrEndReadScope>(scope));
    baseProc.pushBack(std::move(instrReadScope));
}

void PacketProcBuilder::_buildInstrRead(const std::string *fieldName,
                                        const std::string *fieldDisplayName,
                                        const DataType *ft, Proc& baseProc)
{
    InstrBuilderDataTypeVisitor visitor {
        *this, fieldName, fieldDisplayName, baseProc
    };

    assert(ft);
    ft->accept(visitor);
}

template <typename InstrReadT>
void buildBasicInstrRead(const std::string *fieldName,
                         const std::string *fieldDisplayName,
                         const DataType *type, Proc& baseProc)
{
    auto instr = std::make_shared<InstrReadT>(fieldName,
                                              fieldDisplayName, type);

    baseProc.pushBack(std::move(instr));
}

void PacketProcBuilder::_buildInstrReadSignedInt(const std::string *fieldName,
                                                 const std::string *fieldDisplayName,
                                                 const DataType *type,
                                                 Proc& baseProc)
{
    assert(type->isSignedIntType());
    buildBasicInstrRead<InstrReadSignedInt>(fieldName, fieldDisplayName, type, baseProc);
}

void PacketProcBuilder::_buildInstrReadUnsignedInt(const std::string *fieldName,
                                                   const std::string *fieldDisplayName,
                                                   const DataType *type,
                                                   Proc& baseProc)
{
    assert(type->isUnsignedIntType());
    buildBasicInstrRead<InstrReadUnsignedInt>(fieldName, fieldDisplayName, type, baseProc);
}

void PacketProcBuilder::_buildInstrReadFloat(const std::string *fieldName,
                                             const std::string *fieldDisplayName,
                                             const DataType *type,
                                             Proc& baseProc)
{
    assert(type->isFloatType());
    buildBasicInstrRead<InstrReadFloat>(fieldName, fieldDisplayName, type, baseProc);
}

void PacketProcBuilder::_buildInstrReadSignedEnum(const std::string *fieldName,
                                                  const std::string *fieldDisplayName,
                                                  const DataType *type,
                                                  Proc& baseProc)
{
    assert(type->isSignedEnumType());
    buildBasicInstrRead<InstrReadSignedEnum>(fieldName, fieldDisplayName, type, baseProc);
}

void PacketProcBuilder::_buildInstrReadUnsignedEnum(const std::string *fieldName,
                                                    const std::string *fieldDisplayName,
                                                    const DataType *type,
                                                    Proc& baseProc)
{
    assert(type->isUnsignedEnumType());
    buildBasicInstrRead<InstrReadUnsignedEnum>(fieldName, fieldDisplayName, type, baseProc);
}

void PacketProcBuilder::_buildInstrReadString(const std::string *fieldName,
                                              const std::string *fieldDisplayName,
                                              const DataType *type,
                                              Proc& baseProc)
{
    assert(type->isStringType());
    buildBasicInstrRead<InstrReadString>(fieldName, fieldDisplayName, type, baseProc);
}

void PacketProcBuilder::_buildInstrReadStruct(const std::string *fieldName,
                                              const std::string *fieldDisplayName,
                                              const DataType *type,
                                              Proc& baseProc)
{
    assert(type->isStructType());

    auto instr = std::make_shared<InstrBeginReadStruct>(fieldName, fieldDisplayName, type);

    for (const auto& field : type->asStructType()->fields()) {
        this->_buildInstrRead(&field->name(), &field->displayName(),
                              &field->type(), instr->proc());
    }

    auto endInstr = std::make_shared<InstrEndReadCompound>(Instr::Kind::END_READ_STRUCT,
                                                           fieldName,
                                                           fieldDisplayName,
                                                           type);

    instr->proc().pushBack(std::move(endInstr));
    baseProc.pushBack(std::move(instr));
}

void PacketProcBuilder::_buildInstrReadStaticArray(const std::string *fieldName,
                                                   const std::string *fieldDisplayName,
                                                   const DataType *type,
                                                   Proc& baseProc)
{
    assert(type->isArrayType());

    std::shared_ptr<InstrBeginReadStaticArray> instr;
    Instr::Kind endKind;

    if (type->isStaticTextArrayType()) {
        instr = std::make_shared<InstrBeginReadStaticTextArray>(fieldName, fieldDisplayName, type);
        endKind = Instr::Kind::END_READ_STATIC_TEXT_ARRAY;
    } else {
        instr = std::make_shared<InstrBeginReadStaticArray>(fieldName,
                                                      fieldDisplayName, type);
        this->_buildInstrRead(fieldName, fieldDisplayName,
                              &type->asArrayType()->elemType(),
                              instr->proc());
        endKind = Instr::Kind::END_READ_STATIC_ARRAY;
    }

    baseProc.pushBack(std::move(instr));

    auto endInstr = std::make_shared<InstrEndReadCompound>(endKind,
                                                           fieldName,
                                                           fieldDisplayName,
                                                           type);

    baseProc.pushBack(std::move(endInstr));
}

void PacketProcBuilder::_buildInstrReadDynamicArray(const std::string *fieldName,
                                                    const std::string *fieldDisplayName,
                                                    const DataType *type,
                                                    Proc& baseProc)
{
    assert(type->isDynamicArrayType());

    std::shared_ptr<InstrBeginReadDynamicArray> instr;
    Instr::Kind endKind;

    if (type->isDynamicTextArrayType()) {
        instr = std::make_shared<InstrBeginReadDynamicTextArray>(fieldName,
                                                             fieldDisplayName,
                                                             type);
        endKind = Instr::Kind::END_READ_DYNAMIC_TEXT_ARRAY;
    } else {
        instr = std::make_shared<InstrBeginReadDynamicArray>(fieldName,
                                                         fieldDisplayName,
                                                         type);
        endKind = Instr::Kind::END_READ_DYNAMIC_ARRAY;
        this->_buildInstrRead(fieldName, fieldDisplayName,
                              &type->asDynamicArrayType()->elemType(),
                              instr->proc());
    }

    baseProc.pushBack(std::move(instr));

    auto endInstr = std::make_shared<InstrEndReadCompound>(endKind,
                                                           fieldName,
                                                           fieldDisplayName,
                                                           type);

    baseProc.pushBack(std::move(endInstr));
}

void PacketProcBuilder::_buildInstrReadVariantUnknownTag(const std::string *fieldName,
                                                         const std::string *fieldDisplayName,
                                                         const DataType *type,
                                                         Proc& baseProc)
{
    assert(type->isVariantType());

    auto instr = std::make_shared<InstrBeginReadVariantUnknownTag>(fieldName,
                                                                   fieldDisplayName,
                                                                   type);

    for (const auto& option : type->asVariantType()->options()) {
        auto& optionProc = instr->options()[option->name()];
        this->_buildInstrRead(&option->name(), &option->displayName(),
                              &option->type(), optionProc);

        /*
         * Each option's procedure can be pushed by the VM as the
         * current one, so each one ends with an "end read variant"
         * instruction to be consistent with other begin/end instruction
         * pairs.
         */
        auto endInstr = std::make_shared<InstrEndReadCompound>(Instr::Kind::END_READ_VARIANT,
                                                               fieldName,
                                                               fieldDisplayName,
                                                               type);
        optionProc.pushBack(std::move(endInstr));
    }

    baseProc.pushBack(std::move(instr));
}

} // namespace internal
} // namespace yactfr
