/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_JSON_PSEUDO_DT_FROM_CTF_2_JSON_DT_HPP
#define _YACTFR_INTERNAL_METADATA_JSON_PSEUDO_DT_FROM_CTF_2_JSON_DT_HPP

#include "json-val.hpp"
#include "../pseudo-types.hpp"

namespace yactfr {
namespace internal {

PseudoDt::UP pseudoDtOfCtf2Obj(const JsonObjVal& jsonFc, const std::string& propName);

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_JSON_PSEUDO_DT_FROM_CTF_2_JSON_DT_HPP
