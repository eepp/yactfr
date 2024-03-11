/*
 * Copyright (C) 2016-2025 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms of the
 * MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_PGM_IO_HPP
#define _YACTFR_INTERNAL_PGM_IO_HPP

#include <ostream>

#include "pgm.hpp"

namespace yactfr {
namespace internal {

std::ostream& operator<<(std::ostream& os, const PktPgm& pktPgm);

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_PGM_IO_HPP
