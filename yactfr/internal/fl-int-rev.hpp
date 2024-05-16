/*
 * Copyright (C) 2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_FL_INT_REV_HPP
#define YACTFR_INTERNAL_FL_INT_REV_HPP

#include <cstdint>

#include <yactfr/aliases.hpp>

namespace yactfr {
namespace internal {

/*
 * Does... something.
 *
 * And then returns the result.
 *
 * See
 * <https://matthewarcus.wordpress.com/2012/11/18/reversing-a-64-bit-word/>.
 */
template <typename T, T MaskV, Size ShiftV>
T swapBits(const T p) noexcept
{
    const auto q = ((p >> ShiftV) ^ p) & MaskV;

    return p ^ q ^ (q << ShiftV);
}

/*
 * Based on Knuth's.
 *
 * For example, given an unsigned `val` with the value 0b111011010 and
 * `len` set to 9, the returned value is 0b010110111.
 *
 * Given a _signed_ `val` with the value 0b01011 and `len` set to 5, the
 * returned value is
 * 0b1111111111111111111111111111111111111111111111111111111111111010
 * (sign extended).
 */
template <typename ValT>
ValT revFlIntBits(const ValT val, const Size len)
{
    static_assert(sizeof(val) == 8, "`val` is a 64-bit integer");

    static constexpr std::uint64_t m0 = 0x5555555555555555LLU;
    static constexpr std::uint64_t m1 = 0x0300c0303030c303LLU;
    static constexpr std::uint64_t m2 = 0x00c0300c03f0003fLLU;
    static constexpr std::uint64_t m3 = 0x00000ffc00003fffLLU;

    // work with the unsigned version to perform the reversal
    auto uVal = static_cast<std::uint64_t>(val);

    uVal = ((uVal >> 1) & m0) | (uVal & m0) << 1;
    uVal = swapBits<std::uint64_t, m1, 4>(uVal);
    uVal = swapBits<std::uint64_t, m2, 8>(uVal);
    uVal = swapBits<std::uint64_t, m3, 20>(uVal);
    uVal = (uVal >> 34) | (uVal << 30);

    /*
     * Sign-extends when `ValT` is signed because in that case the sign
     * bit (LSB of `val`) is at position 63 before this shift.
     */
    return static_cast<ValT>(uVal) >> (64 - len);
}

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_FL_INT_REV_HPP
