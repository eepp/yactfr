/*
 * Copyright (C) 2026 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_FL_FLOAT_VAL_HPP
#define YACTFR_INTERNAL_FL_FLOAT_VAL_HPP

#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

#include <yactfr/aliases.hpp>

namespace yactfr {
namespace internal {

/*
 * Returns the value of the native floating point number having the
 * bits `bits`.
 *
 * `FloatT` is `float` (IEEE 754 binary32) or `double` (IEEE 754
 * binary64).
 */
template <typename FloatT>
FloatT nativeFlFloatValFromBits(const std::uint64_t bits) noexcept
{
    using UIntT = std::conditional_t<sizeof(FloatT) == sizeof(std::uint32_t),
                                     std::uint32_t, std::uint64_t>;

    static_assert(std::is_same<FloatT, float>::value || std::is_same<FloatT, double>::value,
                  "`FloatT` is `float` or `double`.");
    static_assert(std::numeric_limits<FloatT>::is_iec559,
                  "`FloatT` is an IEEE 754 floating point number type.");
    static_assert(std::numeric_limits<FloatT>::radix == 2,
                  "`FloatT` is a binary floating point number type.");
    static_assert(std::numeric_limits<FloatT>::digits == (sizeof(FloatT) == 4 ? 24 : 53),
                  "`FloatT` has the significand length of IEEE 754 binary32/binary64.");
    static_assert(std::numeric_limits<FloatT>::max_exponent == (sizeof(FloatT) == 4 ? 128 : 1024),
                  "`FloatT` has the exponent range of IEEE 754 binary32/binary64.");
    static_assert(sizeof(FloatT) == sizeof(UIntT),
                  "Floating point number and integer sizes match.");

    const auto uIntBits = static_cast<UIntT>(bits);
    FloatT val;

    std::memcpy(&val, &uIntBits, sizeof(val));
    return val;
}

/*
 * Returns the value of the IEEE 754 binary16 floating point number
 * having the bits `bits` (16 LSBs) as a `double`.
 *
 * C++17 has no native binary16 type, so this function builds the
 * equivalent IEEE 754 binary64 number, which can represent any binary16
 * value exactly.
 */
inline double binary16FlFloatValFromBits(const std::uint64_t bits) noexcept
{
    const auto sign = (bits >> 15) & 1;
    const auto exp = (bits >> 10) & 0x1f;
    const auto mant = bits & 0x3ff;

    if (exp == 0) {
        // zero or subnormal: value is `mant` × 2^-24 (exact)
        const auto val = static_cast<double>(mant) * 0x1p-24;

        return sign ? -val : val;
    }

    /*
     * Normal number, infinity, or NaN: rebias the exponent (keep the
     * maximum exponent for infinity and NaN) and move the significand
     * bits to the most significant positions of the binary64
     * significand (also keeps the NaN payload and quiet bit).
     */
    const auto exp64 = exp == 0x1f ? std::uint64_t {0x7ff} : exp - 15 + 1023;

    return nativeFlFloatValFromBits<double>((sign << 63) | (exp64 << 52) | (mant << 42));
}

/*
 * Returns the value of the IEEE 754 fixed-length floating point number
 * having the length `LenBitsV` (16, 32, or 64) and the bits `bits` as
 * a `double`.
 */
template <Size LenBitsV>
double flFloatValFromBits(const std::uint64_t bits) noexcept
{
    static_assert(LenBitsV == 16 || LenBitsV == 32 || LenBitsV == 64,
                  "`LenBitsV` is 16, 32, or 64.");

    // `double` (element value) can represent any `float` value exactly
    static_assert(std::numeric_limits<double>::digits >= std::numeric_limits<float>::digits &&
                  std::numeric_limits<double>::max_exponent >=
                  std::numeric_limits<float>::max_exponent &&
                  std::numeric_limits<double>::min_exponent <=
                  std::numeric_limits<float>::min_exponent,
                  "`double` can represent any `float` value exactly.");

    if constexpr (LenBitsV == 16) {
        return binary16FlFloatValFromBits(bits);
    } else if constexpr (LenBitsV == 32) {
        return nativeFlFloatValFromBits<float>(bits);
    } else {
        return nativeFlFloatValFromBits<double>(bits);
    }
}

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_FL_FLOAT_VAL_HPP
