/*
 * Common utilities.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_UTILS_HPP
#define _YACTFR_UTILS_HPP

#include <string>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/data-type.hpp>
#include <yactfr/metadata/field-ref.hpp>
#include <yactfr/internal/utils.hpp>

#ifdef __MSVC__
# define YACTFR_FORCE_INLINE    __forceinline
#elif defined(__GNUC__)
# define YACTFR_FORCE_INLINE    __attribute__((always_inline)) inline
#else
# define YACTFR_FORCE_INLINE
#endif

#ifdef __GNUC__
# define YACTFR_LIKELY(_cond)   (__builtin_expect(_cond, 1))
# define YACTFR_UNLIKELY(_cond) (__builtin_expect(_cond, 0))
#else
# define YACTFR_LIKELY(_cond)
# define YACTFR_UNLIKELY(_cond)
#endif

namespace yactfr {
namespace utils {

std::string indent(const Size indent);

const DataType *findType(const DataType *type,
                         std::vector<std::string>::const_iterator refAt,
                         std::vector<std::string>::const_iterator refEnd);

std::string strError();

void throwIfScopeTypeIsNotStruct(const DataType *type, const char *scopeName);

} // namespace utils
} // namespace yactfr

#endif // _YACTFR_UTILS_HPP
