/*
 * Packet procedure builder.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_PROC_PACKET_PROC_BUILDER_HPP
#define _YACTFR_PROC_PACKET_PROC_BUILDER_HPP

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
 * This one builds a complete packet procedure out of a given trace
 * type. It does not set the trace type's packet procedure.
 */
class PacketProcBuilder final :
    private boost::noncopyable
{
    friend class InstrBuilderDataTypeVisitor;

public:
    explicit PacketProcBuilder(const TraceType& traceType);

    std::unique_ptr<PacketProc> takePacketProc()
    {
        return std::move(_packetProc);
    }

private:
    struct _SpecialFieldNames
    {
        const std::string *setCurrentId = nullptr;
        const std::string *setDataStreamId = nullptr;
        const std::string *setPacketSequenceNumber = nullptr;
        const std::string *setPacketTotalSize = nullptr;
        const std::string *setPacketContentSize = nullptr;
        const std::string *validateMagic = nullptr;
        const std::string *uuid = nullptr;
        const std::string *tsEnd = nullptr;
    };

private:
    void _buildPacketProc();
    void _buildBasePacketProc();
    void _subUuidInstr();
    void _insertSpecialInstrs();
    void _insertSpecialInstrsPacketProcPreambleProc();
    void _insertSpecialInstrsDstPacketProc(DataStreamTypePacketProc& dstPacketProc);
    void _insertInstrUpdateClockValue();
    void _setSavedValuePos();
    void _subInstrBeginReadVariantUnknownTag();
    void _insertEndInstrs();
    std::unique_ptr<DataStreamTypePacketProc> _buildDataStreamTypePacketProc(const DataStreamType& dst);
    std::unique_ptr<EventRecordTypeProc> _buildEventRecordTypeProc(const EventRecordType& ert);
    void _buildInstrReadScope(Scope scope, const DataType *ft,
                              Proc& baseProc);
    void _buildInstrRead(const std::string *fieldName,
                         const std::string *fieldDisplayName,
                         const DataType *ft,
                         Proc& baseProc);
    void _buildInstrReadSignedInt(const std::string *fieldName,
                                  const std::string *fieldDisplayName,
                                  const DataType *type,
                                  Proc& baseProc);
    void _buildInstrReadUnsignedInt(const std::string *fieldName,
                                    const std::string *fieldDisplayName,
                                    const DataType *type,
                                    Proc& baseProc);
    void _buildInstrReadFloat(const std::string *fieldName,
                              const std::string *fieldDisplayName,
                              const DataType *type,
                              Proc& baseProc);
    void _buildInstrReadSignedEnum(const std::string *fieldName,
                                   const std::string *fieldDisplayName,
                                   const DataType *type,
                                   Proc& baseProc);
    void _buildInstrReadUnsignedEnum(const std::string *fieldName,
                                     const std::string *fieldDisplayName,
                                     const DataType *type,
                                     Proc& baseProc);
    void _buildInstrReadString(const std::string *fieldName,
                               const std::string *fieldDisplayName,
                               const DataType *type,
                               Proc& baseProc);
    void _buildInstrReadStruct(const std::string *fieldName,
                               const std::string *fieldDisplayName,
                               const DataType *type,
                               Proc& baseProc);
    void _buildInstrReadStaticArray(const std::string *fieldName,
                                    const std::string *fieldDisplayName,
                                    const DataType *type,
                                    Proc& baseProc);
    void _buildInstrReadDynamicArray(const std::string *fieldName,
                                     const std::string *fieldDisplayName,
                                     const DataType *type,
                                     Proc& baseProc);
    void _buildInstrReadVariantUnknownTag(const std::string *fieldName,
                                          const std::string *fieldDisplayName,
                                          const DataType *type,
                                          Proc& baseProc);

private:
    const TraceType *_traceType = nullptr;
    std::unique_ptr<PacketProc> _packetProc;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_PROC_PACKET_PROC_BUILDER_HPP
