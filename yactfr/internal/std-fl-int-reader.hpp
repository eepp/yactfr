/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*
 * readStdFlInt() is an ultrafast™ fixed-length integer reading
 * routine for 8-bit-aligned 8-bit, 16-bit, 32-bit, and 64-bit unsigned
 * and signed integers.
 *
 * It uses boost::endian::endian_reverse() to swap the byte order, which
 * results in using the `bswap` instruction on x86-64 at least.
 */

#ifndef YACTFR_INTERNAL_STD_FL_INT_READER_HPP
#define YACTFR_INTERNAL_STD_FL_INT_READER_HPP

#include <boost/endian/conversion.hpp>
#include <cstdint>
#include <type_traits>

#include <yactfr/metadata/bo.hpp>

namespace yactfr {
namespace internal {

template <typename ValT>
using GenReadFlIntRetT = typename std::conditional<std::is_signed<ValT>::value,
                                                   std::int64_t,
                                                   std::uint64_t>::type;

/*
 * Reads a fixed-length integer having the native type `ValT` and the
 * byte order `BoV` from `buf`.
 *
 * `BoV` doesn't matter when `ValT` is a single byte.
 */
template <typename ValT, ByteOrder BoV>
auto readStdFlInt(const std::uint8_t * const buf)
{
    ValT val;

    std::memcpy(&val, buf, sizeof val);

    if constexpr (sizeof val > 1) {
        if constexpr (BoV == ByteOrder::Little) {
            boost::endian::little_to_native_inplace(val);
        } else {
            boost::endian::big_to_native_inplace(val);
        }
    }

    return static_cast<GenReadFlIntRetT<ValT>>(val);
}

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_STD_FL_INT_READER_HPP
