/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_DT_FROM_PSEUDO_ROOT_DT_HPP
#define YACTFR_INTERNAL_METADATA_DT_FROM_PSEUDO_ROOT_DT_HPP

#include <yactfr/metadata/struct-type.hpp>

#include "pseudo-types.hpp"

namespace yactfr {
namespace internal {

/*
 * Returns the root yactfr data type from the pseudo data type
 * `pseudoDt` having the scope `scope` within:
 *
 * * If not `nullptr`: the pseudo event record type `curPseudoErt`.
 * * If not `nullptr`: the pseudo data stream type `curPseudoDst`.
 * * The pseudo trace type `pseudoTraceType`.
 */
StructureType::Up dtFromPseudoRootDt(PseudoDt& pseudoDt, Scope scope,
                                     const PseudoTraceType& pseudoTraceType,
                                     const PseudoDst *curPseudoDst = nullptr,
                                     const PseudoErt *curPseudoErt = nullptr);

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_DT_FROM_PSEUDO_ROOT_DT_HPP
