/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TRACE_HPP
#define _YACTFR_TRACE_HPP

#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/optional.hpp>

#include "metadata/trace-type.hpp"
#include "trace-env.hpp"

namespace yactfr {

/*!
@brief
    Trace.

@ingroup trace

A trace has a \link TraceType type\endlink and an
\link TraceEnvironment environment\endlink.

This is the return type of traceFromMetadataText(); it's not meant to
contain data streams (see ElementSequence for this).
*/
class Trace final :
    boost::noncopyable
{
public:
    /// Unique pointer to constant trace.
    using UP = std::unique_ptr<const Trace>;

public:
    /*!
    @brief
        Builds a trace.

    @param[in] type
        Type of trace.
    @param[in] environment
        Environment of trace (moved).
    */
    explicit Trace(TraceType::UP type, TraceEnvironment&& environment);

    /// Type.
    const TraceType& type() const noexcept
    {
        return *_type;
    }

    /// Environment.
    const TraceEnvironment& environment() const noexcept
    {
        return _env;
    }

private:
    TraceType::UP _type;
    TraceEnvironment _env;
};

} // namespace yactfr

#endif // _YACTFR_TRACE_HPP
