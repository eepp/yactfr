/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_PSEUDO_DT_UTILS_HPP
#define _YACTFR_METADATA_INTERNAL_PSEUDO_DT_UTILS_HPP

#include "pseudo-types.hpp"
#include "pseudo-dt-finder.hpp"

namespace yactfr {
namespace internal {

template <typename PseudoDtT, typename PredFuncT>
auto findPseudoDtsByName(PseudoDtT& basePseudoDt, const std::string& memberTypeName, PredFuncT&& predFunc)
{
    return findPseudoDts(basePseudoDt, [&memberTypeName, &predFunc](auto& pseudoDt,
                                                                    const auto name) {
        return name && memberTypeName == *name && std::forward<PredFuncT>(predFunc)(pseudoDt);
    });
}

template <typename PseudoDtT>
auto findPseudoDtsByName(PseudoDtT& basePseudoDt, const std::string& memberTypeName)
{
    return findPseudoDtsByName(basePseudoDt, memberTypeName, [](auto&) {
        return true;
    });
}

template <typename PseudoDtT, typename PredFuncT>
auto findPseudoUIntTypes(PseudoDtT& basePseudoDt, PredFuncT&& predFunc)
{
    return findPseudoDts(basePseudoDt, [&predFunc](auto& pseudoDt, const auto name) {
        return pseudoDt.isUInt() &&
            std::forward<PredFuncT>(predFunc)(pseudoDt, name);
    });
}

template <typename PseudoDtT>
auto findPseudoUIntTypesByName(PseudoDtT& basePseudoDt, const std::string& memberTypeName)
{
    return findPseudoUIntTypes(basePseudoDt, [&memberTypeName](auto&, const auto name) {
        return name && memberTypeName == *name;
    });
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_PSEUDO_DT_UTILS_HPP
