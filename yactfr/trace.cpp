/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <string>

#include <yactfr/trace.hpp>

namespace yactfr {

Trace::Trace(TraceType::UP type, TraceEnvironment&& environment) :
    _type {std::move(type)},
    _env {std::move(environment)}
{
}

} // namespace yactfr
