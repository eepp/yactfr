/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_PKT_PROC_BUILDER_HPP
#define _YACTFR_PKT_PROC_BUILDER_HPP

#include <cstdlib>
#include <cassert>
#include <memory>
#include <functional>
#include <vector>
#include <boost/noncopyable.hpp>

#include <yactfr/metadata/trace-type.hpp>

#include "proc.hpp"

namespace yactfr {
namespace internal {

/*
 * Packet procedure builder.
 *
 * Builds a complete packet procedure from a given trace type.
 *
 * A packet procedure builder does NOT set the packet procedure of the
 * trace type.
 */
class PktProcBuilder final :
    private boost::noncopyable
{
    friend class BuilderDtInstrVisitor;

public:
    /*
     * Builds a packet procedure from the trace type `traceType`.
     *
     * Call releasePktProc() to steal the resulting packet procedure.
     */
    explicit PktProcBuilder(const TraceType& traceType);

    std::unique_ptr<PktProc> releasePktProc()
    {
        return std::move(_pktProc);
    }

private:
    using _FlIntTypeReadFlIntInstrMap = std::unordered_map<const DataType *, InstrLoc>;

private:
    void _buildPktProc();
    void _buildBasePktProc();
    void _subUuidInstr();
    void _insertSpecialInstrs();
    void _insertSpecialPktProcPreambleProcInstrs();
    void _insertSpecialDsPktProcInstrs(DsPktProc& dsPktProc);
    void _insertUpdateDefClkValInstrs();
    _FlIntTypeReadFlIntInstrMap _createFlIntTypeReadFlIntInstrMap() const;
    void _setSavedValPoss();
    void _insertEndInstrs();
    std::unique_ptr<DsPktProc> _buildDsPktProc(const DataStreamType& dst);
    std::unique_ptr<ErProc> _buildErProc(const EventRecordType& ert);
    void _buildReadScopeInstr(Scope scope, const DataType *dt, Proc& baseProc);
    void _buildReadInstr(const StructureMemberType *memberType, const DataType& dt, Proc& baseProc);

    void _buildReadFlBitArrayInstr(const StructureMemberType *memberType, const DataType& dt,
                                   Proc& baseProc);

    void _buildReadFlBoolInstr(const StructureMemberType *memberType, const DataType& dt,
                               Proc& baseProc);

    void _buildReadFlSIntInstr(const StructureMemberType *memberType, const DataType& dt,
                               Proc& baseProc);

    void _buildReadFlUIntInstr(const StructureMemberType *memberType, const DataType& dt,
                               Proc& baseProc);

    void _buildReadFlFloatInstr(const StructureMemberType *memberType, const DataType& dt,
                                Proc& baseProc);

    void _buildReadFlSEnumInstr(const StructureMemberType *memberType, const DataType& dt,
                                Proc& baseProc);

    void _buildReadFlUEnumInstr(const StructureMemberType *memberType, const DataType& dt,
                                Proc& baseProc);

    void _buildReadNtStrInstr(const StructureMemberType *memberType, const DataType& dt,
                              Proc& baseProc);

    void _buildReadStructInstr(const StructureMemberType *memberType, const DataType& dt,
                               Proc& baseProc);

    void _buildReadSlArrayInstr(const StructureMemberType *memberType, const DataType& dt,
                                Proc& baseProc);

    void _buildReadDlArrayInstr(const StructureMemberType *memberType, const DataType& dt,
                                Proc& baseProc);

    void _buildReadSlStrInstr(const StructureMemberType *memberType, const DataType& dt,
                              Proc& baseProc);

    void _buildReadDlStrInstr(const StructureMemberType *memberType, const DataType& dt,
                              Proc& baseProc);

    void _buildReadSlBlobInstr(const StructureMemberType *memberType, const DataType& dt,
                               Proc& baseProc);

    void _buildReadDlBlobInstr(const StructureMemberType *memberType, const DataType& dt,
                               Proc& baseProc);

    template <typename BeginReadVarInstrT, typename VarTypeT>
    void _buildReadVarInstr(const StructureMemberType *memberType, const VarTypeT& varType,
                            Proc& baseProc);

    void _buildReadVarUSelInstr(const StructureMemberType *memberType, const DataType& dt,
                                Proc& baseProc);

    void _buildReadVarSSelInstr(const StructureMemberType *memberType, const DataType& dt,
                                Proc& baseProc);

    template <typename InstrT>
    void _commonSpecBuildReadArrayInstrWithLen(InstrT& instr, const DataType& dt)
    {
        this->_buildReadInstr(nullptr, dt.asArrayType().elementType(), instr.proc());
    }

    void _specBuildReadDataInstrWithLen(Instr& instr, const DataType& dt)
    {
    }

    void _specBuildReadDataInstrWithLen(BeginReadSlArrayInstr& instr, const DataType& dt)
    {
        this->_commonSpecBuildReadArrayInstrWithLen(instr, dt);
    }

    void _specBuildReadDataInstrWithLen(BeginReadDlArrayInstr& instr, const DataType& dt)
    {
        this->_commonSpecBuildReadArrayInstrWithLen(instr, dt);
    }

    template <typename InstrT, Instr::Kind KindV>
    void _buildReadInstrWithLen(const StructureMemberType * const memberType, const DataType& dt,
                                Proc& baseProc)
    {
        auto instr = std::make_shared<InstrT>(memberType, dt);

        this->_specBuildReadDataInstrWithLen(*instr, dt);
        baseProc.pushBack(std::move(instr));
        baseProc.pushBack(std::make_shared<EndReadDataInstr>(KindV, memberType, dt));
    }

private:
    const TraceType *_traceType = nullptr;
    std::unique_ptr<PktProc> _pktProc;
};

template <typename BeginReadVarInstrT, typename VarTypeT>
void PktProcBuilder::_buildReadVarInstr(const StructureMemberType * const memberType,
                                        const VarTypeT& varType, Proc& baseProc)
{
    auto instr = std::make_shared<BeginReadVarInstrT>(memberType, varType);

    for (auto i = 0U; i < varType.size(); ++i) {
        auto& optProc = instr->opts()[i].proc();

        this->_buildReadInstr(nullptr, varType[i].type(), optProc);

        /*
         * The VM can push the procedure of each option as the current
         * one, so each one ends with an "end read variant" instruction
         * to be consistent with other begin/end instruction pairs.
         */
        auto endInstr = std::make_shared<EndReadDataInstr>(Instr::Kind::END_READ_VAR, memberType,
                                                           varType);

        optProc.pushBack(std::move(endInstr));
    }

    baseProc.pushBack(std::move(instr));
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_PKT_PROC_BUILDER_HPP
