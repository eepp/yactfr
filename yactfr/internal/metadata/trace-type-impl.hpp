/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_TRACE_TYPE_IMPL_HPP
#define _YACTFR_INTERNAL_METADATA_TRACE_TYPE_IMPL_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <functional>

#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/aliases.hpp>
#include <yactfr/metadata/item.hpp>

#include "../proc.hpp"
#include "../utils.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl final
{
public:
    explicit TraceTypeImpl(unsigned int majorVersion, unsigned int minorVersion,
                           boost::optional<boost::uuids::uuid> uuid,
                           StructureType::UP pktHeaderType, ClockTypeSet&& clkTypes,
                           DataStreamTypeSet&& dsts, MapItem::UP userAttrs,
                           const TraceType& traceType);

    unsigned int majorVersion() const noexcept
    {
        return _majorVersion;
    }

    unsigned int minorVersion() const noexcept
    {
        return _minorVersion;
    }

    const boost::optional<boost::uuids::uuid>& uuid() const noexcept
    {
        return _uuid;
    }

    const StructureType *pktHeaderType() const noexcept
    {
        return _pktHeaderType.get();
    }

    const ClockTypeSet& clkTypes() const noexcept
    {
        return _clkTypes;
    }

    const DataStreamTypeSet& dsts() const noexcept
    {
        return _dsts;
    }

    const MapItem *userAttrs() const noexcept
    {
        return _userAttrs.get();
    }

    const DataStreamType *findDst(TypeId id) const noexcept;

    /*
     * It is safe to keep a pointer to the returned object as long as
     * this trace type lives.
     */
    const PktProc& pktProc() const;

    static DataTypeSet& dlArrayTypeLenTypes(const DynamicLengthArrayType& dt) noexcept
    {
        return dt._lenTypes();
    }

    static DataTypeSet& dlBlobTypeLenTypes(const DynamicLengthBlobType& dt) noexcept
    {
        return dt._lenTypes();
    }

    static DataTypeSet& dlStrTypeMaxLenTypes(const DynamicLengthStringType& dt) noexcept
    {
        return dt._maxLenTypes();
    }

    template <typename DtT>
    static DataTypeSet& varOptTypeSelTypes(const DtT& dt) noexcept
    {
        return dt._selTypes();
    }

    template <typename ObjT>
    static void setDispName(const ObjT& obj, const std::string& name, const bool removeUnderscore)
    {
        if (removeUnderscore && name.c_str()[0] == '_') {
            obj._dispName = name.substr(1);
        } else {
            obj._dispName = name;
        }
    }

private:
    struct _StackFrame final
    {
        const DataType *parentType;
        Index curChildIndex;
    };

private:
    void _buildDstMap();
    void _createParentLinks(const TraceType& traceType) const;
    void _setTypeDeps() const;
    void _setDispNames() const;

private:
    const unsigned int _majorVersion;
    const unsigned int _minorVersion;
    const boost::optional<boost::uuids::uuid> _uuid;
    const StructureType::UP _pktHeaderType;
    const ClockTypeSet _clkTypes;
    const DataStreamTypeSet _dsts;
    std::unordered_map<TypeId, const DataStreamType *> _idsToDsts;
    const MapItem::UP _userAttrs;
    const TraceType *_traceType;

    // packet procedure cache; created the first time we need it
    mutable std::unique_ptr<const PktProc> _pktProc;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_TRACE_TYPE_IMPL_HPP
