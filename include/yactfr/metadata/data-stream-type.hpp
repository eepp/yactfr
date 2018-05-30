/*
 * CTF data stream type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Classes and aliases related to data stream types.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_DATA_STREAM_TYPE_HPP
#define _YACTFR_METADATA_DATA_STREAM_TYPE_HPP

#include <memory>
#include <unordered_map>
#include <set>
#include <sstream>
#include <boost/noncopyable.hpp>

#include "metadata-base.hpp"
#include "data-type.hpp"
#include "aliases.hpp"
#include "event-record-type.hpp"
#include "struct-type.hpp"

namespace yactfr {

namespace internal {
class TraceTypeImpl;

struct EventRecordTypeIdCompare
{
    bool operator()(const std::unique_ptr<const EventRecordType>& a,
                    const std::unique_ptr<const EventRecordType>& b) const
    {
        return a->id() < b->id();
    }
};
}

class TraceType;

/*!
@brief  Set of event record types with unique IDs.

@ingroup metadata
*/
using EventRecordTypeSet = std::set<std::unique_ptr<const EventRecordType>,
                                    internal::EventRecordTypeIdCompare>;

/*!
@brief  Data stream type.

@ingroup metadata

A data stream type describes data streams.
*/
class DataStreamType final :
    public MetadataBase,
    boost::noncopyable
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief  Builds a data stream type.

    @param id                           Data stream type ID.
    @param eventRecordTypes             Children event record types (moved
                                        to this data stream type).
    @param packetContextType            Packet context type.
    @param eventRecordHeaderType        Event record header type.
    @param eventRecordFirstContextType  Event record first context type.

    @throws InvalidMetadata The data stream type is invalid.
    */
    explicit DataStreamType(TypeId id,
                            EventRecordTypeSet&& eventRecordTypes,
                            DataType::UP packetContextType,
                            DataType::UP eventRecordHeaderType,
                            DataType::UP eventRecordFirstContextType);

    /// ID of this data stream type.
    TypeId id() const noexcept
    {
        return _id;
    }

    /// Contained set of event record types.
    const EventRecordTypeSet& eventRecordTypes() const noexcept
    {
        return _eventRecordTypes;
    }

    /*!
    @brief  Finds an event record type by ID.

    @param id   ID of the event record type to find.
    @returns    Event record type with id \p ID or \c nullptr if not found.
    */
    const EventRecordType *operator[](TypeId id) const;

    /// Event record type iterator set at the first event record type
    /// of this data stream type.
    EventRecordTypeSet::const_iterator begin() const noexcept
    {
        return std::begin(_eventRecordTypes);
    }

    /// Event record type iterator set \em after the last
    /// event record type of this data stream type.
    EventRecordTypeSet::const_iterator end() const noexcept
    {
        return std::end(_eventRecordTypes);
    }

    /*!
    Type of the context data following the header data of the packets
    contained in the data streams described by this data stream type.

    \c nullptr if there's no packet context type.
    */
    const DataType* packetContextType() const noexcept
    {
        return _packetContextType.get();
    }

    /*!
    @brief  Type of the header data of all the event records contained
            in the packets contained in the data streams described by
            this data stream type.

    \c nullptr if there's no event record header type.
    */
    const DataType* eventRecordHeaderType() const noexcept
    {
        return _eventRecordHeaderType.get();
    }

    /*!
    @brief  Type of the first context data following the header data of
            all the event records contained in the packets contained in
            the data streams described by this data stream type.

    \c nullptr if there's no event record first context type.
    */
    const DataType* eventRecordFirstContextType() const noexcept
    {
        return _eventRecordFirstContextType.get();
    }

    /*!
    @brief  Parent trace type of this data stream type.

    \c nullptr if this data stream type is not part of a trace type's
    hierarchy yet.
    */
    const TraceType *traceType() const noexcept
    {
        return _traceType;
    }

    /*!
    @brief  Finds a field using the absolute field reference \p ref
            and returns its data type.

    The following scopes can be searched into:

    -# Scope::EVENT_RECORD_FIRST_CONTEXT
    -# Scope::EVENT_RECORD_HEADER
    -# Scope::PACKET_CONTEXT
    -# Scope::PACKET_HEADER

    @param ref  Field reference of the field to find.
    @returns    Located field's data type, or \c nullptr if the field
                cannot be found.
    */
    const DataType *findDataType(const FieldRef& ref) const;

private:
    void _buildErtMap();
    void _validate() const;
    void _validateEventRecordType(const EventRecordType& eventRecordType) const;
    bool _isTypeEmpty(const DataType* type) const;
    void _setTraceType(const TraceType *traceType) const;

private:
    const TypeId _id;
    const EventRecordTypeSet _eventRecordTypes;
    std::unordered_map<TypeId, const EventRecordType *> _idsToEventRecordTypes;
    DataType::UP _packetContextType;
    DataType::UP _eventRecordHeaderType;
    DataType::UP _eventRecordFirstContextType;
    mutable const TraceType *_traceType = nullptr;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DATA_STREAM_TYPE_HPP
