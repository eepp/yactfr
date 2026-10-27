/*
 * Copyright (C) 2022-2026 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_FL_INT_READER_HPP
#define YACTFR_INTERNAL_FL_INT_READER_HPP

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <utility>

#include <yactfr/metadata/bo.hpp>

#include "utils.hpp"

namespace yactfr::internal {

/*
 * Returns the bytes from `buf[FirstIndexV]` to `buf[LastIndexV]`, the
 * byte at `FirstIndexV` being the least significant one.
 *
 * This is a single expression instead of a loop so that the compiler
 * may merge the byte loads into wider loads (it doesn't when it fully
 * unrolls an equivalent loop).
 */
template <unsigned int FirstIndexV, unsigned int LastIndexV>
YACTFR_INTERNAL_HIDDEN
std::uint64_t gatherFlIntBytes(const std::uint8_t * const buf) noexcept
{
    if constexpr (FirstIndexV == LastIndexV) {
        return buf[FirstIndexV];
    } else {
        constexpr auto nextIndex = FirstIndexV < LastIndexV ? FirstIndexV + 1 : FirstIndexV - 1;

        return (gatherFlIntBytes<nextIndex, LastIndexV>(buf) << 8) | buf[FirstIndexV];
    }
}

/*
 * Reads a `LenV`-bit fixed-length integer having the byte order `BoV`
 * and starting at the bit `AtV` of `buf[0]`.
 *
 * `RetT` is either `std::uint64_t` or `std::int64_t` (sign extension).
 *
 * All the byte indexes, shift amounts, and masks are known at
 * build time.
 */
template <typename RetT, unsigned int LenV, unsigned int AtV, ByteOrder BoV>
YACTFR_INTERNAL_HIDDEN
RetT readFlInt(const std::uint8_t * const buf) noexcept
{
    static_assert(LenV >= 1 && LenV <= 64, "`LenV` is a valid length.");
    static_assert(AtV < 8, "`AtV` is a valid bit position.");

    // number of bytes on which the data spans
    constexpr auto lenBytes = (LenV + 7 + AtV) / 8;

    std::uint64_t res = 0;

    if constexpr (BoV == ByteOrder::Little) {
        /*
         * Gather all the bytes except the first one, the last one being
         * the most significant, and then make place for the remaining
         * bits of the first byte (least significant bits).
         */
        if constexpr (lenBytes > 1) {
            res = gatherFlIntBytes<1, lenBytes - 1>(buf);
            res <<= 8 - AtV;
        }

        res |= buf[0] >> AtV;
    } else {
        constexpr auto lastIndex = lenBytes - 1;

        // number of unused low bits in the last byte
        constexpr auto lastByteShift = (8 - (LenV + AtV) % 8) % 8;

        /*
         * Gather all the bytes except the last one, the first one being
         * the most significant, and then make place for the remaining
         * bits of the last byte (least significant bits).
         */
        if constexpr (lenBytes > 1) {
            res = gatherFlIntBytes<lastIndex - 1, 0>(buf);
            res <<= 8 - lastByteShift;
        }

        res |= buf[lastIndex] >> lastByteShift;
    }

    if constexpr (LenV < 64) {
        // clear garbage most significant bits
        constexpr auto mask = (UINT64_C(1) << LenV) - 1;

        res &= mask;

        if constexpr (std::is_signed_v<RetT>) {
            if (res >> (LenV - 1)) {
                // sign-extend negative value
                res |= ~mask;
            }
        }
    }

    return static_cast<RetT>(res);
}

template <typename RetT, ByteOrder BoV, typename IndexSeqT>
struct YACTFR_INTERNAL_HIDDEN FlIntReadFuncsImpl;

template <typename RetT, ByteOrder BoV, std::size_t... IndexesV>
struct YACTFR_INTERNAL_HIDDEN FlIntReadFuncsImpl<RetT, BoV, std::index_sequence<IndexesV...>> final
{
    static constexpr RetT (*funcs[])(const std::uint8_t *) = {
        &readFlInt<RetT, IndexesV / 8 + 1, IndexesV % 8, BoV>...
    };
};

/*
 * `FlIntReadFuncs<RetT, BoV>::funcs` is a table of functions which read
 * a fixed-length integer having the byte order `BoV`.
 *
 * The table index is `(len - 1) * 8 + at`, where `len` is the length of
 * the integer (1 to 64) and `at` is its bit position within the first
 * byte of data (0 to 7).
 */
template <typename RetT, ByteOrder BoV>
using FlIntReadFuncs = FlIntReadFuncsImpl<RetT, BoV, std::make_index_sequence<64 * 8>>;

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_FL_INT_READER_HPP
