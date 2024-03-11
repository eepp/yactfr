/*
 * Copyright (C) 2016-2025 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_BUILD_PKT_PGM_HPP
#define YACTFR_INTERNAL_BUILD_PKT_PGM_HPP

#include <yactfr/metadata/trace-type.hpp>

#include "pgm.hpp"

namespace yactfr {
namespace internal {

PktPgm buildPktPgm(const TraceType& traceType);

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_BUILD_PKT_PGM_HPP
