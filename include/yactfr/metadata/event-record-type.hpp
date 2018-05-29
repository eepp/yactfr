/*
 * CTF event record type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Event record type.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_EVENT_RECORD_TYPE_HPP
#define _YACTFR_METADATA_EVENT_RECORD_TYPE_HPP

#include <memory>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include "metadata-base.hpp"
#include "fwd.hpp"

namespace yactfr {

namespace internal {

class TraceTypeImpl;

}

class DataStreamType;

/*!
@brief  Event record type.

@ingroup metadata

An event record type describes data stream event records.
*/
class EventRecordType final :
    public MetadataBase,
    boost::noncopyable
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief  Builds an event record type.

    @param name                 Name.
    @param id                   ID.
    @param logLevel             Log level.
    @param modelEmfUri          EMF URI.
    @param secondContextType    Second context's type.
    @param payloadType          Payload's type.
    */
    explicit EventRecordType(TypeId id,
                             const boost::optional<std::string>& name,
                             const boost::optional<LogLevel>& logLevel,
                             const boost::optional<std::string>& modelEmfUri,
                             std::unique_ptr<const DataType> secondContextType,
                             std::unique_ptr<const DataType> payloadType);

    /*!
    @brief  Numeric ID.

    This ID is unique amongst the IDs of all the event record types
    which are children of the same DataStreamType.
    */
    TypeId id() const noexcept
    {
        return _id;
    }

    /*!
    @brief  Name.
    */
    const boost::optional<std::string>& name() const noexcept
    {
        return _name;
    }

    /// Positive log level.
    const boost::optional<LogLevel>& logLevel() const noexcept
    {
        return _logLevel;
    }

    /// EMF URI.
    const boost::optional<std::string>& modelEmfUri() const noexcept
    {
        return _modelEmfUri;
    }

    /*!
    @brief  Type of the second context data of the data stream event
            records described by this event record type.

    \c nullptr if there's no event record second context type.
    */
    const DataType* secondContextType() const noexcept
    {
        return _secondContextType.get();
    }

    /*!
    @brief  Type of the payload data of the data stream event records
            described by this event record type.

    \c nullptr if there's no event record payload type.
    */
    const DataType* payloadType() const noexcept
    {
        return _payloadType.get();
    }

    /*!
    @brief  Parent data stream type of this event record type.

    \c nullptr if this event record type is not part of a trace type's
    hierarchy yet.
    */
    const DataStreamType *dataStreamType() const noexcept
    {
        return _dataStreamType;
    }

    /*!
    @brief  Finds a field using the absolute field reference \p ref
            and returns its data type.

    The following scopes can be searched into:

    -# Scope::EVENT_RECORD_PAYLOAD
    -# Scope::EVENT_RECORD_SECOND_CONTEXT
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
    void _setDataStreamType(const DataStreamType *dataStreamType) const;

private:
    const TypeId _id;
    const boost::optional<std::string> _name;
    const boost::optional<LogLevel> _logLevel;
    const boost::optional<std::string> _modelEmfUri;
    std::unique_ptr<const DataType> _secondContextType;
    std::unique_ptr<const DataType> _payloadType;
    mutable const DataStreamType *_dataStreamType = nullptr;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_EVENT_RECORD_TYPE_HPP
