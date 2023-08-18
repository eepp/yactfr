/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DST_HPP
#define _YACTFR_METADATA_DST_HPP

#include <memory>
#include <utility>
#include <unordered_map>
#include <set>
#include <boost/noncopyable.hpp>

#include "dt.hpp"
#include "aliases.hpp"
#include "ert.hpp"
#include "struct-type.hpp"
#include "item.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

struct ErtIdComp final
{
    bool operator()(const std::unique_ptr<const EventRecordType>& a,
                    const std::unique_ptr<const EventRecordType>& b) const
    {
        return a->id() < b->id();
    }
};

} // namespace internal

class TraceType;
class StructureType;
class DataLocation;

/*!
@brief
    Set of event record types with unique IDs.

@ingroup metadata
*/
using EventRecordTypeSet = std::set<std::unique_ptr<const EventRecordType>, internal::ErtIdComp>;

/*!
@brief
    Data stream type.

@ingroup metadata

A data stream type describes data streams.
*/
class DataStreamType final :
    boost::noncopyable
{
    friend class internal::TraceTypeImpl;

public:
    /// Unique pointer to constant data stream type.
    using UP = std::unique_ptr<const DataStreamType>;

public:
    /*!
    @brief
        Builds a data stream type.

    @param[in] id
        Data stream type ID.
    @param[in] nameSpace
        Namespace of data streams described by this type.
    @param[in] name
        Name of data streams described by this type..
    @param[in] uid
        Unique ID of data streams described by this type..
    @param[in] eventRecordTypes
        Children event record types (moved to this type).
    @param[in] packetContextType
        Type of packet contexts of data streams described by this type,
        or \c nullptr if none.
    @param[in] eventRecordHeaderType
        Type of event record headers of data streams described by this
        type, or \c nullptr if none.
    @param[in] eventRecordCommonContextType
        Type of common event record context of data streams described by
        this type, or \c nullptr if none.
    @param[in] defaultClockType
        Type of the default clock of data streams described by this
        type, or \c nullptr if none.
    @param[in] userAttributes
        @parblock
        User attributes.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        @parblock
        If set, no data type in \p eventRecordCommonContextType,
        recursively, has a role (UnsignedIntegerTypeRole or "metadata
        stream UUID" role).

        If set, no data type in \p packetContextType, recursively, has a
        "metadata stream UUID" role.

        If set, no data type in \p eventRecordHeaderType, recursively,
        has a "metadata stream UUID" role.

        If set, any unsigned integer type within \p packetContextType,
        recursively, may only have the following roles:

        - UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH
        - UnsignedIntegerTypeRole::PACKET_CONTENT_LENGTH
        - UnsignedIntegerTypeRole::DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT
        - UnsignedIntegerTypeRole::PACKET_SEQUENCE_NUMBER
        - When \p defaultClockType is not \c nullptr:
          - UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP
          - UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP

        If set, any unsigned integer type within
        \p eventRecordHeaderType, recursively, may only have the
        following roles:

        - UnsignedIntegerTypeRole::EVENT_RECORD_TYPE_ID
        - When \p defaultClockType is not \c nullptr:
          UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP
        @endparblock
    */
    explicit DataStreamType(TypeId id, boost::optional<std::string> nameSpace,
                            boost::optional<std::string> name,
                            boost::optional<std::string> uid,
                            EventRecordTypeSet&& eventRecordTypes,
                            StructureType::UP packetContextType,
                            StructureType::UP eventRecordHeaderType,
                            StructureType::UP eventRecordCommonContextType,
                            const ClockType *defaultClockType = nullptr,
                            MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a data stream type without namespace, name, and unique ID
        properties.

    @param[in] id
        Data stream type ID.
    @param[in] eventRecordTypes
        Children event record types (moved to this type).
    @param[in] packetContextType
        Type of packet contexts of data streams described by this type,
        or \c nullptr if none.
    @param[in] eventRecordHeaderType
        Type of event record headers of data streams described by this
        type, or \c nullptr if none.
    @param[in] eventRecordCommonContextType
        Type of common event record context of data streams described by
        this type, or \c nullptr if none.
    @param[in] defaultClockType
        Type of the default clock of a data stream described by this
        type, or \c nullptr if none.
    @param[in] userAttributes
        @parblock
        User attributes.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        @parblock
        If set, no data type in \p eventRecordCommonContextType,
        recursively, has a role (UnsignedIntegerTypeRole or "metadata
        stream UUID" role).

        If set, no data type in \p packetContextType, recursively, has a
        "metadata stream UUID" role.

        If set, no data type in \p eventRecordHeaderType, recursively,
        has a "metadata stream UUID" role.

        If set, any unsigned integer type within \p packetContextType,
        recursively, may only have the following roles:

        - UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH
        - UnsignedIntegerTypeRole::PACKET_CONTENT_LENGTH
        - UnsignedIntegerTypeRole::DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT
        - UnsignedIntegerTypeRole::PACKET_SEQUENCE_NUMBER
        - When \p defaultClockType is not \c nullptr:
          - UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP
          - UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP

        If set, any unsigned integer type within
        \p eventRecordHeaderType, recursively, may only have the
        following roles:

        - UnsignedIntegerTypeRole::EVENT_RECORD_TYPE_ID
        - When \p defaultClockType is not \c nullptr:
          UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP
        @endparblock
    */
    explicit DataStreamType(TypeId id, EventRecordTypeSet&& eventRecordTypes,
                            StructureType::UP packetContextType,
                            StructureType::UP eventRecordHeaderType,
                            StructureType::UP eventRecordCommonContextType,
                            const ClockType *defaultClockType = nullptr,
                            MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a constant data stream type unique pointer, forwarding
        \p args to the constructor.

    @param[in] args
        Arguments to forward to the data stream type constructor.

    @returns
        Created constant data stream type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

    /*!
    @brief
        Numeric ID, unique amongst the IDs of all the data stream types
        which are part of the same \link TraceType trace type\endlink.
    */
    TypeId id() const noexcept
    {
        return _id;
    }

    /// Namespace of data streams described by this type.
    const boost::optional<std::string>& nameSpace() const noexcept
    {
        return _ns;
    }

    /// Name of data streams described by this type.
    const boost::optional<std::string>& name() const noexcept
    {
        return _name;
    }

    /// Unique ID of data streams described by this type.
    const boost::optional<std::string>& uid() const noexcept
    {
        return _uid;
    }

    /// Contained event record types.
    const EventRecordTypeSet& eventRecordTypes() const noexcept
    {
        return _erts;
    }

    /*!
    @brief
        Returns the event record type having the ID \p id,
        or \c nullptr if not found.

    @param[in] id
        ID of the event record type to find.

    @returns
        Event record type with ID \p id, or \c nullptr if not found.
    */
    const EventRecordType *operator[](TypeId id) const;

    /*!
    @brief
        Event record type constant iterator set at the first event
        record type of this type.
    */
    EventRecordTypeSet::const_iterator begin() const noexcept
    {
        return _erts.begin();
    }

    /*!
    @brief
        Event record type constant iterator set \em after the last event
        record type of this type.
    */
    EventRecordTypeSet::const_iterator end() const noexcept
    {
        return _erts.end();
    }

    /// Number of event record types this type has.
    Size size() const noexcept
    {
        return _erts.size();
    }

    /// Whether or not this type is empty (has no event record types).
    bool isEmpty() const noexcept
    {
        return _erts.empty();
    }

    /*!
    @brief
        Type of the context structure following the header structure of
        the packets of the data streams described by this type, or
        \c nullptr if there's no packet context type.
    */
    const StructureType *packetContextType() const noexcept
    {
        return _pktCtxType.get();
    }

    /*!
    @brief
        Type of the header structure of all the event records contained
        in the packets of the data streams described by this type, or
        \c nullptr if there's no event record header type.
    */
    const StructureType *eventRecordHeaderType() const noexcept
    {
        return _erHeaderType.get();
    }

    /*!
    @brief
        Type of the common context structure following the header
        structure of all the event records contained in the packets of
        the data streams described by this type, or
        \c nullptr if there's no event record common context type.
    */
    const StructureType *eventRecordCommonContextType() const noexcept
    {
        return _erCommonCtxType.get();
    }

    /*!
    @brief
        Type of the default clock of the data streams describe by this
        type.
    */
    const ClockType *defaultClockType() const noexcept
    {
        return _defClkType;
    }

    /*!
    @brief
        User attributes.

    If set, each key of the returned map item is a namespace.

    @note
        Even if the return value isn't \c nullptr, the returned map
        item may still be empty (which also means no user attributes).
    */
    const MapItem *userAttributes() const noexcept
    {
        return _userAttrs.get();
    }

    /*!
    @brief
        Parent trace type of this type, or \c nullptr if this type is
        not part of a trace type yet.
    */
    const TraceType *traceType() const noexcept
    {
        return _traceType;
    }

private:
    void _buildErtMap();
    bool _isDataTypeEmpty(const DataType *type) const;
    void _setTraceType(const TraceType& traceType) const;

private:
    const TypeId _id;
    const boost::optional<std::string> _ns;
    const boost::optional<std::string> _name;
    const boost::optional<std::string> _uid;
    const EventRecordTypeSet _erts;
    std::unordered_map<TypeId, const EventRecordType *> _idsToErts;
    StructureType::UP _pktCtxType;
    StructureType::UP _erHeaderType;
    StructureType::UP _erCommonCtxType;
    const ClockType * const _defClkType;
    const MapItem::UP _userAttrs;
    mutable const TraceType *_traceType = nullptr;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DST_HPP
