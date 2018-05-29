/*
 * Standard integer reader.
 *
 * Those functions are ultrafast™ integer reading routines for 8-bit
 * aligned 8-bit, 16-bit, 32-bit, and 64-bit signed and unsigned
 * integers. Each readInt*() function is forced to be inlined. We use
 * boost::endian::endian_reverse() to swap the byte order, which results
 * in using the `bswap` instruction on x86-64 at least.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_STD_INT_READER_HPP
#define _YACTFR_STD_INT_READER_HPP

#include <boost/endian/conversion.hpp>
#include <cstdint>
#include <type_traits>

#include "utils.hpp"

namespace yactfr {
namespace internal {

template <typename ValT>
using GenReadIntRetT = typename std::conditional<std::is_signed<ValT>::value,
                                                 std::int64_t, std::uint64_t>::type;

template <typename ValT>
auto genReadIntLe(const std::uint8_t * const buf)
{
    ValT val;

    std::memcpy(&val, buf, sizeof(val));
    boost::endian::little_to_native_inplace(val);
    return static_cast<GenReadIntRetT<ValT>>(val);
}

template <typename ValT>
auto genReadIntBe(const std::uint8_t * const buf)
{
    ValT val;

    std::memcpy(&val, buf, sizeof(val));
    boost::endian::big_to_native_inplace(val);
    return static_cast<GenReadIntRetT<ValT>>(val);
}

static YACTFR_FORCE_INLINE auto readIntUnsigned8(const std::uint8_t * const buf)
{
    return static_cast<std::uint64_t>(buf[0]);
}

static YACTFR_FORCE_INLINE auto readIntSigned8(const std::uint8_t * const buf)
{
    return static_cast<std::int64_t>(static_cast<std::int8_t>(buf[0]));
}

static YACTFR_FORCE_INLINE auto readIntUnsignedLe16(const std::uint8_t * const buf)
{
    return genReadIntLe<std::uint16_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntUnsignedLe32(const std::uint8_t * const buf)
{
    return genReadIntLe<std::uint32_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntUnsignedLe64(const std::uint8_t * const buf)
{
    return genReadIntLe<std::uint64_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntSignedLe16(const std::uint8_t * const buf)
{
    return genReadIntLe<std::int16_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntSignedLe32(const std::uint8_t * const buf)
{
    return genReadIntLe<std::int32_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntSignedLe64(const std::uint8_t * const buf)
{
    return genReadIntLe<std::int64_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntUnsignedBe16(const std::uint8_t * const buf)
{
    return genReadIntBe<std::uint16_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntUnsignedBe32(const std::uint8_t * const buf)
{
    return genReadIntBe<std::uint32_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntUnsignedBe64(const std::uint8_t * const buf)
{
    return genReadIntBe<std::uint64_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntSignedBe16(const std::uint8_t * const buf)
{
    return genReadIntBe<std::int16_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntSignedBe32(const std::uint8_t * const buf)
{
    return genReadIntBe<std::int32_t>(buf);
}

static YACTFR_FORCE_INLINE auto readIntSignedBe64(const std::uint8_t * const buf)
{
    return genReadIntBe<std::int64_t>(buf);
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_STD_INT_READER_HPP
