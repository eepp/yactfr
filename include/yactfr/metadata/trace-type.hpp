/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_TRACE_TYPE_HPP
#define _YACTFR_METADATA_TRACE_TYPE_HPP

#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/optional.hpp>

#include "clk-type.hpp"
#include "dst.hpp"
#include "dt.hpp"
#include "struct-type.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

struct ClkTypeNameComp final
{
    bool operator()(const std::unique_ptr<const ClockType>& a,
                    const std::unique_ptr<const ClockType>& b) const
    {
        return a->name() < b->name();
    }
};

struct DstIdComp final
{
    bool operator()(const std::unique_ptr<const DataStreamType>& a,
                    const std::unique_ptr<const DataStreamType>& b) const
    {
        return a->id() < b->id();
    }
};

} // namespace internal

/*!
@brief
    Set of clock types with unique names.

@ingroup metadata
*/
using ClockTypeSet = std::set<std::unique_ptr<const ClockType>, internal::ClkTypeNameComp>;

/*!
@brief
    Set of data stream types with unique IDs.

@ingroup metadata
*/
using DataStreamTypeSet = std::set<std::unique_ptr<const DataStreamType>, internal::DstIdComp>;

/*!
@brief
    Trace type.

@ingroup metadata

A trace type describes traces.
*/
class TraceType final :
    boost::noncopyable
{
    friend class internal::TraceTypeImpl;
    friend class ElementSequenceIterator;

public:
    /// Unique pointer to trace type.
    using UP = std::unique_ptr<const TraceType>;

public:
    /*!
    @brief
        Builds a trace type.

    @param[in] majorVersion
        Major version.
    @param[in] minorVersion
        Minor version.
    @param[in] uuid
        UUID of traces described by this trace type.
    @param[in] packetHeaderType
        Packet header type, or \c nullptr if none.
    @param[in] clockTypes
        Clock types of the trace type (moved).
    @param[in] dataStreamTypes
        Data stream types (moved).

    @pre
        \p majorVersion is 1.
    @pre
        \p minorVersion is 8.
    */
    explicit TraceType(unsigned int majorVersion, unsigned int minorVersion,
                       boost::optional<boost::uuids::uuid> uuid,
                       StructureType::UP packetHeaderType, ClockTypeSet&& clockTypes,
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

    /// Native byte order.
    ByteOrder nativeByteOrder() const noexcept;

    /// UUID.
    const boost::optional<boost::uuids::uuid>& uuid() const noexcept;

    /// Type of the header structure of all the packets of the trace
    /// described by this type, or \c nullptr if there's no packet
    /// header type.
    const StructureType *packetHeaderType() const noexcept;

    /// Contained clock types.
    const ClockTypeSet& clockTypes() const noexcept;

    /// Contained data stream types.
    const DataStreamTypeSet& dataStreamTypes() const noexcept;

    /*!
    @brief
        Returns the data stream type having the ID \p id,
        or \c nullptr if not found.

    @param[in] id
        ID of the data stream type to find.

    @returns
        Data stream type with ID \p id, or \c nullptr if not found.
    */
    const DataStreamType *operator[](TypeId id) const;

    /// Data stream type constant iterator set at the first data stream
    /// type of this type.
    DataStreamTypeSet::const_iterator begin() const noexcept;

    /// Data stream type constant iterator set \em after the last data
    /// stream type of this type.
    DataStreamTypeSet::const_iterator end() const noexcept;

private:
    const std::unique_ptr<internal::TraceTypeImpl> _pimpl;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_TRACE_TYPE_HPP
