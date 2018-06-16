/*
 * CTF trace type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Classes related to trace types.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_TRACE_TYPE_HPP
#define _YACTFR_METADATA_TRACE_TYPE_HPP

// for std::unique_ptr, std::shared_ptr
#include <memory>

// for boost::uuids::uuid
#include <boost/uuid/uuid.hpp>

// for boost::optional
#include <boost/optional.hpp>

// for ClockType
#include "clock-type.hpp"

// for DataStreamType
#include "data-stream-type.hpp"

// for DataType
#include "data-type.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

struct ClockTypeNameCompare
{
    bool operator()(const std::unique_ptr<const ClockType>& a,
                    const std::unique_ptr<const ClockType>& b) const
    {
        return a->name() < b->name();
    }
};

struct DataStreamTypeIdCompare
{
    bool operator()(const std::unique_ptr<const DataStreamType>& a,
                    const std::unique_ptr<const DataStreamType>& b) const
    {
        return a->id() < b->id();
    }
};

} // namespace internal

class TraceTypeEnv;

/*!
@brief  Set of clock types with unique names.

@ingroup metadata
*/
using ClockTypeSet = std::set<std::unique_ptr<const ClockType>,
                              internal::ClockTypeNameCompare>;

/*!
@brief  Set of data stream types with unique IDs.

@ingroup metadata
*/
using DataStreamTypeSet = std::set<std::unique_ptr<const DataStreamType>,
                                   internal::DataStreamTypeIdCompare>;

/*!
@brief  Trace type.

@ingroup metadata

A trace type describes traces.
*/
class TraceType final :
    boost::noncopyable
{
    friend class internal::TraceTypeImpl;
    friend class PacketSequenceIterator;

public:
    /// Shared pointer to trace type.
    using SP = std::shared_ptr<const TraceType>;

public:
    /*!
    @brief  Builds a trace type.

    @param majorVersion         Major version (must be 1).
    @param minorVersion         Minor version (must be 8).
    @param uuid                 UUID of traces described by this trace type.
    @param packetHeaderType     Packet header type.
    @param env                  Trace type's environment.
    @param clockTypes           Trace type's clock types (moved to this
                                trace type).
    @param dataStreamTypes      Children data stream types (moved to
                                this trace type).

    @throws InvalidMetadata The trace class is invalid.
    */
    explicit TraceType(unsigned int majorVersion,
                       unsigned int minorVersion,
                       const boost::optional<boost::uuids::uuid>& uuid,
                       DataType::UP packetHeaderType,
                       std::unique_ptr<const TraceTypeEnv> env,
                       ClockTypeSet&& clockTypes,
                       DataStreamTypeSet&& dataStreamTypes);

    /*
     * Required because internal::TraceTypeImpl has no known size at
     * this point.
     */
    ~TraceType();

    /// Major version.
    unsigned int majorVersion() const noexcept;

    /// Minor version.
    unsigned int minorVersion() const noexcept;

    /// UUID.
    const boost::optional<boost::uuids::uuid>& uuid() const noexcept;

    /// Environment.
    const TraceTypeEnv& env() const noexcept;

    /*!
    Type of the header data of the packets contained in the data streams
    contained in the traces described by this trace type.

    \c nullptr if there's no packet header type.
    */
    const DataType* packetHeaderType() const noexcept;

    /// Contained set of clock types.
    const ClockTypeSet& clockTypes() const noexcept;

    /// Contained set of data stream types.
    const DataStreamTypeSet& dataStreamTypes() const noexcept;

    /*!
    @brief  Finds a data stream type by ID.

    @param id   ID of the data stream type to find.
    @returns    Data stream type with id \p ID or \c nullptr if not found.
    */
    const DataStreamType *operator[](TypeId id) const;

    /// Data stream type constant iterator set at the first data stream
    /// type of this trace type.
    DataStreamTypeSet::const_iterator begin() const noexcept;

    /// Data stream type constant iterator set \em after the last
    /// data stream type of this trace type.
    DataStreamTypeSet::const_iterator end() const noexcept;

    /*!
    @brief  Finds a clock type by name.

    @param name Name of the clock type to find.
    @returns    Clock type with name \p name or \c nullptr if not found.
    */
    const ClockType *findClockType(const std::string& name) const;

    /*!
    @brief  Finds a field using the absolute field reference \p ref
            and returns its data type.

    Only the Scope::PACKET_HEADER scope can be searched into.

    @param ref  Field reference of the field to find.
    @returns    Located field's data type, or \c nullptr if the field
                cannot be found.
    */
    const DataType *findDataType(const FieldRef& ref) const;

private:
    const std::unique_ptr<internal::TraceTypeImpl> _pimpl;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_TRACE_TYPE_HPP
