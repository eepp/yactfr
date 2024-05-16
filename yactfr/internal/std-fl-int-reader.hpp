/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*
 * Those functions are ultrafast™ fixed-length integer reading routines
 * for 8-bit-aligned 8-bit, 16-bit, 32-bit, and 64-bit unsigned and
 * signed integers.
 *
 * The functions use boost::endian::endian_reverse() to swap the byte
 * order, which results in using the `bswap` instruction on x86-64 at
 * least.
 */

#ifndef YACTFR_INTERNAL_STD_FL_INT_READER_HPP
#define YACTFR_INTERNAL_STD_FL_INT_READER_HPP

#include <boost/endian/conversion.hpp>
#include <cstdint>
#include <type_traits>

namespace yactfr {
namespace internal {

template <typename ValT>
using GenReadFlIntRetT = typename std::conditional<std::is_signed<ValT>::value,
                                                   std::int64_t, std::uint64_t>::type;

template <typename ValT>
auto genReadFlIntLe(const std::uint8_t * const buf)
{
    ValT val;

    std::memcpy(&val, buf, sizeof val);
    boost::endian::little_to_native_inplace(val);
    return static_cast<GenReadFlIntRetT<ValT>>(val);
}

template <typename ValT>
auto genReadFlIntBe(const std::uint8_t * const buf)
{
    ValT val;

    std::memcpy(&val, buf, sizeof val);
    boost::endian::big_to_native_inplace(val);
    return static_cast<GenReadFlIntRetT<ValT>>(val);
}

inline auto readFlUInt8(const std::uint8_t * const buf)
{
    return static_cast<std::uint64_t>(buf[0]);
}

inline auto readFlSInt8(const std::uint8_t * const buf)
{
    return static_cast<std::int64_t>(static_cast<std::int8_t>(buf[0]));
}

inline auto readFlUIntLe16(const std::uint8_t * const buf)
{
    return genReadFlIntLe<std::uint16_t>(buf);
}

inline auto readFlUIntLe32(const std::uint8_t * const buf)
{
    return genReadFlIntLe<std::uint32_t>(buf);
}

inline auto readFlUIntLe64(const std::uint8_t * const buf)
{
    return genReadFlIntLe<std::uint64_t>(buf);
}

inline auto readFlSIntLe16(const std::uint8_t * const buf)
{
    return genReadFlIntLe<std::int16_t>(buf);
}

inline auto readFlSIntLe32(const std::uint8_t * const buf)
{
    return genReadFlIntLe<std::int32_t>(buf);
}

inline auto readFlSIntLe64(const std::uint8_t * const buf)
{
    return genReadFlIntLe<std::int64_t>(buf);
}

inline auto readFlUIntBe16(const std::uint8_t * const buf)
{
    return genReadFlIntBe<std::uint16_t>(buf);
}

inline auto readFlUIntBe32(const std::uint8_t * const buf)
{
    return genReadFlIntBe<std::uint32_t>(buf);
}

inline auto readFlUIntBe64(const std::uint8_t * const buf)
{
    return genReadFlIntBe<std::uint64_t>(buf);
}

inline auto readFlSIntBe16(const std::uint8_t * const buf)
{
    return genReadFlIntBe<std::int16_t>(buf);
}

inline auto readFlSIntBe32(const std::uint8_t * const buf)
{
    return genReadFlIntBe<std::int32_t>(buf);
}

inline auto readFlSIntBe64(const std::uint8_t * const buf)
{
    return genReadFlIntBe<std::int64_t>(buf);
}

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_STD_FL_INT_READER_HPP
