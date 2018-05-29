/*
 * Generic integer reader, works whatever the executing architecture's
 * byte order is.
 *
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INT_READER_HPP
#define _YACTFR_INT_READER_HPP

#include <cstdint>
#include <cassert>
#include <cstring>

namespace yactfr {
namespace internal {

static std::uint64_t readIntUnsignedBe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe26At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe27At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe28At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe29At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe30At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe31At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe32At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 5;
    res |= (buf[8] >> 3);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 5;
    res |= (buf[8] >> 3);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 6;
    res |= (buf[8] >> 2);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedBe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    return res;
}

static std::uint64_t readIntUnsignedBe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    return res;
}

static std::uint64_t readIntUnsignedBe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    return res;
}

static std::uint64_t readIntUnsignedBe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    return res;
}

static std::uint64_t readIntUnsignedBe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    return res;
}

static std::uint64_t readIntUnsignedBe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 5;
    res |= (buf[8] >> 3);
    return res;
}

static std::uint64_t readIntUnsignedBe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 6;
    res |= (buf[8] >> 2);
    return res;
}

static std::uint64_t readIntUnsignedBe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 7;
    res |= (buf[8] >> 1);
    return res;
}

static std::int64_t readIntSignedBe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe26At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe27At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe28At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe29At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe30At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe31At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe32At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 1;
    res |= (buf[4] >> 7);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 2;
    res |= (buf[4] >> 6);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 3;
    res |= (buf[4] >> 5);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 4;
    res |= (buf[4] >> 4);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 5;
    res |= (buf[4] >> 3);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 6;
    res |= (buf[4] >> 2);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 7;
    res |= (buf[4] >> 1);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 1;
    res |= (buf[5] >> 7);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 2;
    res |= (buf[5] >> 6);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 3;
    res |= (buf[5] >> 5);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 4;
    res |= (buf[5] >> 4);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 5;
    res |= (buf[5] >> 3);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 6;
    res |= (buf[5] >> 2);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 7;
    res |= (buf[5] >> 1);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 1;
    res |= (buf[6] >> 7);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 2;
    res |= (buf[6] >> 6);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 3;
    res |= (buf[6] >> 5);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 4;
    res |= (buf[6] >> 4);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 5;
    res |= (buf[6] >> 3);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 6;
    res |= (buf[6] >> 2);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 7;
    res |= (buf[6] >> 1);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 1;
    res |= (buf[7] >> 7);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 2;
    res |= (buf[7] >> 6);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 3;
    res |= (buf[7] >> 5);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 4;
    res |= (buf[7] >> 4);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 5;
    res |= (buf[7] >> 3);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 6;
    res |= (buf[7] >> 2);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 5;
    res |= (buf[8] >> 3);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 7;
    res |= (buf[7] >> 1);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 5;
    res |= (buf[8] >> 3);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 6;
    res |= (buf[8] >> 2);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 1;
    res |= (buf[8] >> 7);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 2;
    res |= (buf[8] >> 6);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 3;
    res |= (buf[8] >> 5);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 4;
    res |= (buf[8] >> 4);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 5;
    res |= (buf[8] >> 3);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 6;
    res |= (buf[8] >> 2);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedBe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[7];
    res <<= 7;
    res |= (buf[8] >> 1);
    return static_cast<std::int64_t>(res);
}

static std::uint64_t readIntUnsignedLe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= 0x1ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe26At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe27At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe28At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe29At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe30At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe31At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe32At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffffffffULL;
    return res;
}

static std::uint64_t readIntUnsignedLe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    return res;
}

static std::uint64_t readIntUnsignedLe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    return res;
}

static std::uint64_t readIntUnsignedLe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    return res;
}

static std::uint64_t readIntUnsignedLe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    return res;
}

static std::uint64_t readIntUnsignedLe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    return res;
}

static std::uint64_t readIntUnsignedLe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    return res;
}

static std::uint64_t readIntUnsignedLe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    return res;
}

static std::uint64_t readIntUnsignedLe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    return res;
}

static std::int64_t readIntSignedLe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= 0x1ULL;

    if (res >> 0) {
        res |= 0xfffffffffffffffeULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ULL;

    if (res >> 1) {
        res |= 0xfffffffffffffffcULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ULL;

    if (res >> 2) {
        res |= 0xfffffffffffffff8ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfULL;

    if (res >> 3) {
        res |= 0xfffffffffffffff0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fULL;

    if (res >> 4) {
        res |= 0xffffffffffffffe0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fULL;

    if (res >> 5) {
        res |= 0xffffffffffffffc0ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fULL;

    if (res >> 6) {
        res |= 0xffffffffffffff80ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffULL;

    if (res >> 7) {
        res |= 0xffffffffffffff00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffULL;

    if (res >> 8) {
        res |= 0xfffffffffffffe00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffULL;

    if (res >> 9) {
        res |= 0xfffffffffffffc00ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffULL;

    if (res >> 10) {
        res |= 0xfffffffffffff800ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffULL;

    if (res >> 11) {
        res |= 0xfffffffffffff000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffULL;

    if (res >> 12) {
        res |= 0xffffffffffffe000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffULL;

    if (res >> 13) {
        res |= 0xffffffffffffc000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffULL;

    if (res >> 14) {
        res |= 0xffffffffffff8000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffULL;

    if (res >> 15) {
        res |= 0xffffffffffff0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffULL;

    if (res >> 16) {
        res |= 0xfffffffffffe0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffULL;

    if (res >> 17) {
        res |= 0xfffffffffffc0000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffULL;

    if (res >> 18) {
        res |= 0xfffffffffff80000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffULL;

    if (res >> 19) {
        res |= 0xfffffffffff00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffULL;

    if (res >> 20) {
        res |= 0xffffffffffe00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffULL;

    if (res >> 21) {
        res |= 0xffffffffffc00000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffULL;

    if (res >> 22) {
        res |= 0xffffffffff800000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffULL;

    if (res >> 23) {
        res |= 0xffffffffff000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffULL;

    if (res >> 24) {
        res |= 0xfffffffffe000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe26At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffULL;

    if (res >> 25) {
        res |= 0xfffffffffc000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe27At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffULL;

    if (res >> 26) {
        res |= 0xfffffffff8000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe28At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffULL;

    if (res >> 27) {
        res |= 0xfffffffff0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe29At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffULL;

    if (res >> 28) {
        res |= 0xffffffffe0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe30At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffULL;

    if (res >> 29) {
        res |= 0xffffffffc0000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe31At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffULL;

    if (res >> 30) {
        res |= 0xffffffff80000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe32At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffULL;

    if (res >> 31) {
        res |= 0xffffffff00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffULL;

    if (res >> 32) {
        res |= 0xfffffffe00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffULL;

    if (res >> 33) {
        res |= 0xfffffffc00000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffULL;

    if (res >> 34) {
        res |= 0xfffffff800000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffULL;

    if (res >> 35) {
        res |= 0xfffffff000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffULL;

    if (res >> 36) {
        res |= 0xffffffe000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffULL;

    if (res >> 37) {
        res |= 0xffffffc000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffULL;

    if (res >> 38) {
        res |= 0xffffff8000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffffULL;

    if (res >> 39) {
        res |= 0xffffff0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffffULL;

    if (res >> 40) {
        res |= 0xfffffe0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffffULL;

    if (res >> 41) {
        res |= 0xfffffc0000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffffULL;

    if (res >> 42) {
        res |= 0xfffff80000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffffULL;

    if (res >> 43) {
        res |= 0xfffff00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffffULL;

    if (res >> 44) {
        res |= 0xffffe00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffffULL;

    if (res >> 45) {
        res |= 0xffffc00000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffffULL;

    if (res >> 46) {
        res |= 0xffff800000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffffffULL;

    if (res >> 47) {
        res |= 0xffff000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffffffULL;

    if (res >> 48) {
        res |= 0xfffe000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffffffULL;

    if (res >> 49) {
        res |= 0xfffc000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffffffULL;

    if (res >> 50) {
        res |= 0xfff8000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffffffULL;

    if (res >> 51) {
        res |= 0xfff0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffffffULL;

    if (res >> 52) {
        res |= 0xffe0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffffffULL;

    if (res >> 53) {
        res |= 0xffc0000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffffffULL;

    if (res >> 54) {
        res |= 0xff80000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xffffffffffffffULL;

    if (res >> 55) {
        res |= 0xff00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1ffffffffffffffULL;

    if (res >> 56) {
        res |= 0xfe00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3ffffffffffffffULL;

    if (res >> 57) {
        res |= 0xfc00000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7ffffffffffffffULL;

    if (res >> 58) {
        res |= 0xf800000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0xfffffffffffffffULL;

    if (res >> 59) {
        res |= 0xf000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x1fffffffffffffffULL;

    if (res >> 60) {
        res |= 0xe000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x3fffffffffffffffULL;

    if (res >> 61) {
        res |= 0xc000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= 0x7fffffffffffffffULL;

    if (res >> 62) {
        res |= 0x8000000000000000ULL;
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    return static_cast<std::int64_t>(res);
}

static std::int64_t readIntSignedLe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[8];
    res <<= 8;
    res |= buf[7];
    res <<= 8;
    res |= buf[6];
    res <<= 8;
    res |= buf[5];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    return static_cast<std::int64_t>(res);
}

static std::uint64_t (*readIntBeUnsignedFuncs[])(const std::uint8_t *) = {
    readIntUnsignedBe1At0,
    readIntUnsignedBe1At1,
    readIntUnsignedBe1At2,
    readIntUnsignedBe1At3,
    readIntUnsignedBe1At4,
    readIntUnsignedBe1At5,
    readIntUnsignedBe1At6,
    readIntUnsignedBe1At7,
    readIntUnsignedBe2At0,
    readIntUnsignedBe2At1,
    readIntUnsignedBe2At2,
    readIntUnsignedBe2At3,
    readIntUnsignedBe2At4,
    readIntUnsignedBe2At5,
    readIntUnsignedBe2At6,
    readIntUnsignedBe2At7,
    readIntUnsignedBe3At0,
    readIntUnsignedBe3At1,
    readIntUnsignedBe3At2,
    readIntUnsignedBe3At3,
    readIntUnsignedBe3At4,
    readIntUnsignedBe3At5,
    readIntUnsignedBe3At6,
    readIntUnsignedBe3At7,
    readIntUnsignedBe4At0,
    readIntUnsignedBe4At1,
    readIntUnsignedBe4At2,
    readIntUnsignedBe4At3,
    readIntUnsignedBe4At4,
    readIntUnsignedBe4At5,
    readIntUnsignedBe4At6,
    readIntUnsignedBe4At7,
    readIntUnsignedBe5At0,
    readIntUnsignedBe5At1,
    readIntUnsignedBe5At2,
    readIntUnsignedBe5At3,
    readIntUnsignedBe5At4,
    readIntUnsignedBe5At5,
    readIntUnsignedBe5At6,
    readIntUnsignedBe5At7,
    readIntUnsignedBe6At0,
    readIntUnsignedBe6At1,
    readIntUnsignedBe6At2,
    readIntUnsignedBe6At3,
    readIntUnsignedBe6At4,
    readIntUnsignedBe6At5,
    readIntUnsignedBe6At6,
    readIntUnsignedBe6At7,
    readIntUnsignedBe7At0,
    readIntUnsignedBe7At1,
    readIntUnsignedBe7At2,
    readIntUnsignedBe7At3,
    readIntUnsignedBe7At4,
    readIntUnsignedBe7At5,
    readIntUnsignedBe7At6,
    readIntUnsignedBe7At7,
    readIntUnsignedBe8At0,
    readIntUnsignedBe8At1,
    readIntUnsignedBe8At2,
    readIntUnsignedBe8At3,
    readIntUnsignedBe8At4,
    readIntUnsignedBe8At5,
    readIntUnsignedBe8At6,
    readIntUnsignedBe8At7,
    readIntUnsignedBe9At0,
    readIntUnsignedBe9At1,
    readIntUnsignedBe9At2,
    readIntUnsignedBe9At3,
    readIntUnsignedBe9At4,
    readIntUnsignedBe9At5,
    readIntUnsignedBe9At6,
    readIntUnsignedBe9At7,
    readIntUnsignedBe10At0,
    readIntUnsignedBe10At1,
    readIntUnsignedBe10At2,
    readIntUnsignedBe10At3,
    readIntUnsignedBe10At4,
    readIntUnsignedBe10At5,
    readIntUnsignedBe10At6,
    readIntUnsignedBe10At7,
    readIntUnsignedBe11At0,
    readIntUnsignedBe11At1,
    readIntUnsignedBe11At2,
    readIntUnsignedBe11At3,
    readIntUnsignedBe11At4,
    readIntUnsignedBe11At5,
    readIntUnsignedBe11At6,
    readIntUnsignedBe11At7,
    readIntUnsignedBe12At0,
    readIntUnsignedBe12At1,
    readIntUnsignedBe12At2,
    readIntUnsignedBe12At3,
    readIntUnsignedBe12At4,
    readIntUnsignedBe12At5,
    readIntUnsignedBe12At6,
    readIntUnsignedBe12At7,
    readIntUnsignedBe13At0,
    readIntUnsignedBe13At1,
    readIntUnsignedBe13At2,
    readIntUnsignedBe13At3,
    readIntUnsignedBe13At4,
    readIntUnsignedBe13At5,
    readIntUnsignedBe13At6,
    readIntUnsignedBe13At7,
    readIntUnsignedBe14At0,
    readIntUnsignedBe14At1,
    readIntUnsignedBe14At2,
    readIntUnsignedBe14At3,
    readIntUnsignedBe14At4,
    readIntUnsignedBe14At5,
    readIntUnsignedBe14At6,
    readIntUnsignedBe14At7,
    readIntUnsignedBe15At0,
    readIntUnsignedBe15At1,
    readIntUnsignedBe15At2,
    readIntUnsignedBe15At3,
    readIntUnsignedBe15At4,
    readIntUnsignedBe15At5,
    readIntUnsignedBe15At6,
    readIntUnsignedBe15At7,
    readIntUnsignedBe16At0,
    readIntUnsignedBe16At1,
    readIntUnsignedBe16At2,
    readIntUnsignedBe16At3,
    readIntUnsignedBe16At4,
    readIntUnsignedBe16At5,
    readIntUnsignedBe16At6,
    readIntUnsignedBe16At7,
    readIntUnsignedBe17At0,
    readIntUnsignedBe17At1,
    readIntUnsignedBe17At2,
    readIntUnsignedBe17At3,
    readIntUnsignedBe17At4,
    readIntUnsignedBe17At5,
    readIntUnsignedBe17At6,
    readIntUnsignedBe17At7,
    readIntUnsignedBe18At0,
    readIntUnsignedBe18At1,
    readIntUnsignedBe18At2,
    readIntUnsignedBe18At3,
    readIntUnsignedBe18At4,
    readIntUnsignedBe18At5,
    readIntUnsignedBe18At6,
    readIntUnsignedBe18At7,
    readIntUnsignedBe19At0,
    readIntUnsignedBe19At1,
    readIntUnsignedBe19At2,
    readIntUnsignedBe19At3,
    readIntUnsignedBe19At4,
    readIntUnsignedBe19At5,
    readIntUnsignedBe19At6,
    readIntUnsignedBe19At7,
    readIntUnsignedBe20At0,
    readIntUnsignedBe20At1,
    readIntUnsignedBe20At2,
    readIntUnsignedBe20At3,
    readIntUnsignedBe20At4,
    readIntUnsignedBe20At5,
    readIntUnsignedBe20At6,
    readIntUnsignedBe20At7,
    readIntUnsignedBe21At0,
    readIntUnsignedBe21At1,
    readIntUnsignedBe21At2,
    readIntUnsignedBe21At3,
    readIntUnsignedBe21At4,
    readIntUnsignedBe21At5,
    readIntUnsignedBe21At6,
    readIntUnsignedBe21At7,
    readIntUnsignedBe22At0,
    readIntUnsignedBe22At1,
    readIntUnsignedBe22At2,
    readIntUnsignedBe22At3,
    readIntUnsignedBe22At4,
    readIntUnsignedBe22At5,
    readIntUnsignedBe22At6,
    readIntUnsignedBe22At7,
    readIntUnsignedBe23At0,
    readIntUnsignedBe23At1,
    readIntUnsignedBe23At2,
    readIntUnsignedBe23At3,
    readIntUnsignedBe23At4,
    readIntUnsignedBe23At5,
    readIntUnsignedBe23At6,
    readIntUnsignedBe23At7,
    readIntUnsignedBe24At0,
    readIntUnsignedBe24At1,
    readIntUnsignedBe24At2,
    readIntUnsignedBe24At3,
    readIntUnsignedBe24At4,
    readIntUnsignedBe24At5,
    readIntUnsignedBe24At6,
    readIntUnsignedBe24At7,
    readIntUnsignedBe25At0,
    readIntUnsignedBe25At1,
    readIntUnsignedBe25At2,
    readIntUnsignedBe25At3,
    readIntUnsignedBe25At4,
    readIntUnsignedBe25At5,
    readIntUnsignedBe25At6,
    readIntUnsignedBe25At7,
    readIntUnsignedBe26At0,
    readIntUnsignedBe26At1,
    readIntUnsignedBe26At2,
    readIntUnsignedBe26At3,
    readIntUnsignedBe26At4,
    readIntUnsignedBe26At5,
    readIntUnsignedBe26At6,
    readIntUnsignedBe26At7,
    readIntUnsignedBe27At0,
    readIntUnsignedBe27At1,
    readIntUnsignedBe27At2,
    readIntUnsignedBe27At3,
    readIntUnsignedBe27At4,
    readIntUnsignedBe27At5,
    readIntUnsignedBe27At6,
    readIntUnsignedBe27At7,
    readIntUnsignedBe28At0,
    readIntUnsignedBe28At1,
    readIntUnsignedBe28At2,
    readIntUnsignedBe28At3,
    readIntUnsignedBe28At4,
    readIntUnsignedBe28At5,
    readIntUnsignedBe28At6,
    readIntUnsignedBe28At7,
    readIntUnsignedBe29At0,
    readIntUnsignedBe29At1,
    readIntUnsignedBe29At2,
    readIntUnsignedBe29At3,
    readIntUnsignedBe29At4,
    readIntUnsignedBe29At5,
    readIntUnsignedBe29At6,
    readIntUnsignedBe29At7,
    readIntUnsignedBe30At0,
    readIntUnsignedBe30At1,
    readIntUnsignedBe30At2,
    readIntUnsignedBe30At3,
    readIntUnsignedBe30At4,
    readIntUnsignedBe30At5,
    readIntUnsignedBe30At6,
    readIntUnsignedBe30At7,
    readIntUnsignedBe31At0,
    readIntUnsignedBe31At1,
    readIntUnsignedBe31At2,
    readIntUnsignedBe31At3,
    readIntUnsignedBe31At4,
    readIntUnsignedBe31At5,
    readIntUnsignedBe31At6,
    readIntUnsignedBe31At7,
    readIntUnsignedBe32At0,
    readIntUnsignedBe32At1,
    readIntUnsignedBe32At2,
    readIntUnsignedBe32At3,
    readIntUnsignedBe32At4,
    readIntUnsignedBe32At5,
    readIntUnsignedBe32At6,
    readIntUnsignedBe32At7,
    readIntUnsignedBe33At0,
    readIntUnsignedBe33At1,
    readIntUnsignedBe33At2,
    readIntUnsignedBe33At3,
    readIntUnsignedBe33At4,
    readIntUnsignedBe33At5,
    readIntUnsignedBe33At6,
    readIntUnsignedBe33At7,
    readIntUnsignedBe34At0,
    readIntUnsignedBe34At1,
    readIntUnsignedBe34At2,
    readIntUnsignedBe34At3,
    readIntUnsignedBe34At4,
    readIntUnsignedBe34At5,
    readIntUnsignedBe34At6,
    readIntUnsignedBe34At7,
    readIntUnsignedBe35At0,
    readIntUnsignedBe35At1,
    readIntUnsignedBe35At2,
    readIntUnsignedBe35At3,
    readIntUnsignedBe35At4,
    readIntUnsignedBe35At5,
    readIntUnsignedBe35At6,
    readIntUnsignedBe35At7,
    readIntUnsignedBe36At0,
    readIntUnsignedBe36At1,
    readIntUnsignedBe36At2,
    readIntUnsignedBe36At3,
    readIntUnsignedBe36At4,
    readIntUnsignedBe36At5,
    readIntUnsignedBe36At6,
    readIntUnsignedBe36At7,
    readIntUnsignedBe37At0,
    readIntUnsignedBe37At1,
    readIntUnsignedBe37At2,
    readIntUnsignedBe37At3,
    readIntUnsignedBe37At4,
    readIntUnsignedBe37At5,
    readIntUnsignedBe37At6,
    readIntUnsignedBe37At7,
    readIntUnsignedBe38At0,
    readIntUnsignedBe38At1,
    readIntUnsignedBe38At2,
    readIntUnsignedBe38At3,
    readIntUnsignedBe38At4,
    readIntUnsignedBe38At5,
    readIntUnsignedBe38At6,
    readIntUnsignedBe38At7,
    readIntUnsignedBe39At0,
    readIntUnsignedBe39At1,
    readIntUnsignedBe39At2,
    readIntUnsignedBe39At3,
    readIntUnsignedBe39At4,
    readIntUnsignedBe39At5,
    readIntUnsignedBe39At6,
    readIntUnsignedBe39At7,
    readIntUnsignedBe40At0,
    readIntUnsignedBe40At1,
    readIntUnsignedBe40At2,
    readIntUnsignedBe40At3,
    readIntUnsignedBe40At4,
    readIntUnsignedBe40At5,
    readIntUnsignedBe40At6,
    readIntUnsignedBe40At7,
    readIntUnsignedBe41At0,
    readIntUnsignedBe41At1,
    readIntUnsignedBe41At2,
    readIntUnsignedBe41At3,
    readIntUnsignedBe41At4,
    readIntUnsignedBe41At5,
    readIntUnsignedBe41At6,
    readIntUnsignedBe41At7,
    readIntUnsignedBe42At0,
    readIntUnsignedBe42At1,
    readIntUnsignedBe42At2,
    readIntUnsignedBe42At3,
    readIntUnsignedBe42At4,
    readIntUnsignedBe42At5,
    readIntUnsignedBe42At6,
    readIntUnsignedBe42At7,
    readIntUnsignedBe43At0,
    readIntUnsignedBe43At1,
    readIntUnsignedBe43At2,
    readIntUnsignedBe43At3,
    readIntUnsignedBe43At4,
    readIntUnsignedBe43At5,
    readIntUnsignedBe43At6,
    readIntUnsignedBe43At7,
    readIntUnsignedBe44At0,
    readIntUnsignedBe44At1,
    readIntUnsignedBe44At2,
    readIntUnsignedBe44At3,
    readIntUnsignedBe44At4,
    readIntUnsignedBe44At5,
    readIntUnsignedBe44At6,
    readIntUnsignedBe44At7,
    readIntUnsignedBe45At0,
    readIntUnsignedBe45At1,
    readIntUnsignedBe45At2,
    readIntUnsignedBe45At3,
    readIntUnsignedBe45At4,
    readIntUnsignedBe45At5,
    readIntUnsignedBe45At6,
    readIntUnsignedBe45At7,
    readIntUnsignedBe46At0,
    readIntUnsignedBe46At1,
    readIntUnsignedBe46At2,
    readIntUnsignedBe46At3,
    readIntUnsignedBe46At4,
    readIntUnsignedBe46At5,
    readIntUnsignedBe46At6,
    readIntUnsignedBe46At7,
    readIntUnsignedBe47At0,
    readIntUnsignedBe47At1,
    readIntUnsignedBe47At2,
    readIntUnsignedBe47At3,
    readIntUnsignedBe47At4,
    readIntUnsignedBe47At5,
    readIntUnsignedBe47At6,
    readIntUnsignedBe47At7,
    readIntUnsignedBe48At0,
    readIntUnsignedBe48At1,
    readIntUnsignedBe48At2,
    readIntUnsignedBe48At3,
    readIntUnsignedBe48At4,
    readIntUnsignedBe48At5,
    readIntUnsignedBe48At6,
    readIntUnsignedBe48At7,
    readIntUnsignedBe49At0,
    readIntUnsignedBe49At1,
    readIntUnsignedBe49At2,
    readIntUnsignedBe49At3,
    readIntUnsignedBe49At4,
    readIntUnsignedBe49At5,
    readIntUnsignedBe49At6,
    readIntUnsignedBe49At7,
    readIntUnsignedBe50At0,
    readIntUnsignedBe50At1,
    readIntUnsignedBe50At2,
    readIntUnsignedBe50At3,
    readIntUnsignedBe50At4,
    readIntUnsignedBe50At5,
    readIntUnsignedBe50At6,
    readIntUnsignedBe50At7,
    readIntUnsignedBe51At0,
    readIntUnsignedBe51At1,
    readIntUnsignedBe51At2,
    readIntUnsignedBe51At3,
    readIntUnsignedBe51At4,
    readIntUnsignedBe51At5,
    readIntUnsignedBe51At6,
    readIntUnsignedBe51At7,
    readIntUnsignedBe52At0,
    readIntUnsignedBe52At1,
    readIntUnsignedBe52At2,
    readIntUnsignedBe52At3,
    readIntUnsignedBe52At4,
    readIntUnsignedBe52At5,
    readIntUnsignedBe52At6,
    readIntUnsignedBe52At7,
    readIntUnsignedBe53At0,
    readIntUnsignedBe53At1,
    readIntUnsignedBe53At2,
    readIntUnsignedBe53At3,
    readIntUnsignedBe53At4,
    readIntUnsignedBe53At5,
    readIntUnsignedBe53At6,
    readIntUnsignedBe53At7,
    readIntUnsignedBe54At0,
    readIntUnsignedBe54At1,
    readIntUnsignedBe54At2,
    readIntUnsignedBe54At3,
    readIntUnsignedBe54At4,
    readIntUnsignedBe54At5,
    readIntUnsignedBe54At6,
    readIntUnsignedBe54At7,
    readIntUnsignedBe55At0,
    readIntUnsignedBe55At1,
    readIntUnsignedBe55At2,
    readIntUnsignedBe55At3,
    readIntUnsignedBe55At4,
    readIntUnsignedBe55At5,
    readIntUnsignedBe55At6,
    readIntUnsignedBe55At7,
    readIntUnsignedBe56At0,
    readIntUnsignedBe56At1,
    readIntUnsignedBe56At2,
    readIntUnsignedBe56At3,
    readIntUnsignedBe56At4,
    readIntUnsignedBe56At5,
    readIntUnsignedBe56At6,
    readIntUnsignedBe56At7,
    readIntUnsignedBe57At0,
    readIntUnsignedBe57At1,
    readIntUnsignedBe57At2,
    readIntUnsignedBe57At3,
    readIntUnsignedBe57At4,
    readIntUnsignedBe57At5,
    readIntUnsignedBe57At6,
    readIntUnsignedBe57At7,
    readIntUnsignedBe58At0,
    readIntUnsignedBe58At1,
    readIntUnsignedBe58At2,
    readIntUnsignedBe58At3,
    readIntUnsignedBe58At4,
    readIntUnsignedBe58At5,
    readIntUnsignedBe58At6,
    readIntUnsignedBe58At7,
    readIntUnsignedBe59At0,
    readIntUnsignedBe59At1,
    readIntUnsignedBe59At2,
    readIntUnsignedBe59At3,
    readIntUnsignedBe59At4,
    readIntUnsignedBe59At5,
    readIntUnsignedBe59At6,
    readIntUnsignedBe59At7,
    readIntUnsignedBe60At0,
    readIntUnsignedBe60At1,
    readIntUnsignedBe60At2,
    readIntUnsignedBe60At3,
    readIntUnsignedBe60At4,
    readIntUnsignedBe60At5,
    readIntUnsignedBe60At6,
    readIntUnsignedBe60At7,
    readIntUnsignedBe61At0,
    readIntUnsignedBe61At1,
    readIntUnsignedBe61At2,
    readIntUnsignedBe61At3,
    readIntUnsignedBe61At4,
    readIntUnsignedBe61At5,
    readIntUnsignedBe61At6,
    readIntUnsignedBe61At7,
    readIntUnsignedBe62At0,
    readIntUnsignedBe62At1,
    readIntUnsignedBe62At2,
    readIntUnsignedBe62At3,
    readIntUnsignedBe62At4,
    readIntUnsignedBe62At5,
    readIntUnsignedBe62At6,
    readIntUnsignedBe62At7,
    readIntUnsignedBe63At0,
    readIntUnsignedBe63At1,
    readIntUnsignedBe63At2,
    readIntUnsignedBe63At3,
    readIntUnsignedBe63At4,
    readIntUnsignedBe63At5,
    readIntUnsignedBe63At6,
    readIntUnsignedBe63At7,
    readIntUnsignedBe64At0,
    readIntUnsignedBe64At1,
    readIntUnsignedBe64At2,
    readIntUnsignedBe64At3,
    readIntUnsignedBe64At4,
    readIntUnsignedBe64At5,
    readIntUnsignedBe64At6,
    readIntUnsignedBe64At7,
};

static std::int64_t (*readIntBeSignedFuncs[])(const std::uint8_t *) = {
    readIntSignedBe1At0,
    readIntSignedBe1At1,
    readIntSignedBe1At2,
    readIntSignedBe1At3,
    readIntSignedBe1At4,
    readIntSignedBe1At5,
    readIntSignedBe1At6,
    readIntSignedBe1At7,
    readIntSignedBe2At0,
    readIntSignedBe2At1,
    readIntSignedBe2At2,
    readIntSignedBe2At3,
    readIntSignedBe2At4,
    readIntSignedBe2At5,
    readIntSignedBe2At6,
    readIntSignedBe2At7,
    readIntSignedBe3At0,
    readIntSignedBe3At1,
    readIntSignedBe3At2,
    readIntSignedBe3At3,
    readIntSignedBe3At4,
    readIntSignedBe3At5,
    readIntSignedBe3At6,
    readIntSignedBe3At7,
    readIntSignedBe4At0,
    readIntSignedBe4At1,
    readIntSignedBe4At2,
    readIntSignedBe4At3,
    readIntSignedBe4At4,
    readIntSignedBe4At5,
    readIntSignedBe4At6,
    readIntSignedBe4At7,
    readIntSignedBe5At0,
    readIntSignedBe5At1,
    readIntSignedBe5At2,
    readIntSignedBe5At3,
    readIntSignedBe5At4,
    readIntSignedBe5At5,
    readIntSignedBe5At6,
    readIntSignedBe5At7,
    readIntSignedBe6At0,
    readIntSignedBe6At1,
    readIntSignedBe6At2,
    readIntSignedBe6At3,
    readIntSignedBe6At4,
    readIntSignedBe6At5,
    readIntSignedBe6At6,
    readIntSignedBe6At7,
    readIntSignedBe7At0,
    readIntSignedBe7At1,
    readIntSignedBe7At2,
    readIntSignedBe7At3,
    readIntSignedBe7At4,
    readIntSignedBe7At5,
    readIntSignedBe7At6,
    readIntSignedBe7At7,
    readIntSignedBe8At0,
    readIntSignedBe8At1,
    readIntSignedBe8At2,
    readIntSignedBe8At3,
    readIntSignedBe8At4,
    readIntSignedBe8At5,
    readIntSignedBe8At6,
    readIntSignedBe8At7,
    readIntSignedBe9At0,
    readIntSignedBe9At1,
    readIntSignedBe9At2,
    readIntSignedBe9At3,
    readIntSignedBe9At4,
    readIntSignedBe9At5,
    readIntSignedBe9At6,
    readIntSignedBe9At7,
    readIntSignedBe10At0,
    readIntSignedBe10At1,
    readIntSignedBe10At2,
    readIntSignedBe10At3,
    readIntSignedBe10At4,
    readIntSignedBe10At5,
    readIntSignedBe10At6,
    readIntSignedBe10At7,
    readIntSignedBe11At0,
    readIntSignedBe11At1,
    readIntSignedBe11At2,
    readIntSignedBe11At3,
    readIntSignedBe11At4,
    readIntSignedBe11At5,
    readIntSignedBe11At6,
    readIntSignedBe11At7,
    readIntSignedBe12At0,
    readIntSignedBe12At1,
    readIntSignedBe12At2,
    readIntSignedBe12At3,
    readIntSignedBe12At4,
    readIntSignedBe12At5,
    readIntSignedBe12At6,
    readIntSignedBe12At7,
    readIntSignedBe13At0,
    readIntSignedBe13At1,
    readIntSignedBe13At2,
    readIntSignedBe13At3,
    readIntSignedBe13At4,
    readIntSignedBe13At5,
    readIntSignedBe13At6,
    readIntSignedBe13At7,
    readIntSignedBe14At0,
    readIntSignedBe14At1,
    readIntSignedBe14At2,
    readIntSignedBe14At3,
    readIntSignedBe14At4,
    readIntSignedBe14At5,
    readIntSignedBe14At6,
    readIntSignedBe14At7,
    readIntSignedBe15At0,
    readIntSignedBe15At1,
    readIntSignedBe15At2,
    readIntSignedBe15At3,
    readIntSignedBe15At4,
    readIntSignedBe15At5,
    readIntSignedBe15At6,
    readIntSignedBe15At7,
    readIntSignedBe16At0,
    readIntSignedBe16At1,
    readIntSignedBe16At2,
    readIntSignedBe16At3,
    readIntSignedBe16At4,
    readIntSignedBe16At5,
    readIntSignedBe16At6,
    readIntSignedBe16At7,
    readIntSignedBe17At0,
    readIntSignedBe17At1,
    readIntSignedBe17At2,
    readIntSignedBe17At3,
    readIntSignedBe17At4,
    readIntSignedBe17At5,
    readIntSignedBe17At6,
    readIntSignedBe17At7,
    readIntSignedBe18At0,
    readIntSignedBe18At1,
    readIntSignedBe18At2,
    readIntSignedBe18At3,
    readIntSignedBe18At4,
    readIntSignedBe18At5,
    readIntSignedBe18At6,
    readIntSignedBe18At7,
    readIntSignedBe19At0,
    readIntSignedBe19At1,
    readIntSignedBe19At2,
    readIntSignedBe19At3,
    readIntSignedBe19At4,
    readIntSignedBe19At5,
    readIntSignedBe19At6,
    readIntSignedBe19At7,
    readIntSignedBe20At0,
    readIntSignedBe20At1,
    readIntSignedBe20At2,
    readIntSignedBe20At3,
    readIntSignedBe20At4,
    readIntSignedBe20At5,
    readIntSignedBe20At6,
    readIntSignedBe20At7,
    readIntSignedBe21At0,
    readIntSignedBe21At1,
    readIntSignedBe21At2,
    readIntSignedBe21At3,
    readIntSignedBe21At4,
    readIntSignedBe21At5,
    readIntSignedBe21At6,
    readIntSignedBe21At7,
    readIntSignedBe22At0,
    readIntSignedBe22At1,
    readIntSignedBe22At2,
    readIntSignedBe22At3,
    readIntSignedBe22At4,
    readIntSignedBe22At5,
    readIntSignedBe22At6,
    readIntSignedBe22At7,
    readIntSignedBe23At0,
    readIntSignedBe23At1,
    readIntSignedBe23At2,
    readIntSignedBe23At3,
    readIntSignedBe23At4,
    readIntSignedBe23At5,
    readIntSignedBe23At6,
    readIntSignedBe23At7,
    readIntSignedBe24At0,
    readIntSignedBe24At1,
    readIntSignedBe24At2,
    readIntSignedBe24At3,
    readIntSignedBe24At4,
    readIntSignedBe24At5,
    readIntSignedBe24At6,
    readIntSignedBe24At7,
    readIntSignedBe25At0,
    readIntSignedBe25At1,
    readIntSignedBe25At2,
    readIntSignedBe25At3,
    readIntSignedBe25At4,
    readIntSignedBe25At5,
    readIntSignedBe25At6,
    readIntSignedBe25At7,
    readIntSignedBe26At0,
    readIntSignedBe26At1,
    readIntSignedBe26At2,
    readIntSignedBe26At3,
    readIntSignedBe26At4,
    readIntSignedBe26At5,
    readIntSignedBe26At6,
    readIntSignedBe26At7,
    readIntSignedBe27At0,
    readIntSignedBe27At1,
    readIntSignedBe27At2,
    readIntSignedBe27At3,
    readIntSignedBe27At4,
    readIntSignedBe27At5,
    readIntSignedBe27At6,
    readIntSignedBe27At7,
    readIntSignedBe28At0,
    readIntSignedBe28At1,
    readIntSignedBe28At2,
    readIntSignedBe28At3,
    readIntSignedBe28At4,
    readIntSignedBe28At5,
    readIntSignedBe28At6,
    readIntSignedBe28At7,
    readIntSignedBe29At0,
    readIntSignedBe29At1,
    readIntSignedBe29At2,
    readIntSignedBe29At3,
    readIntSignedBe29At4,
    readIntSignedBe29At5,
    readIntSignedBe29At6,
    readIntSignedBe29At7,
    readIntSignedBe30At0,
    readIntSignedBe30At1,
    readIntSignedBe30At2,
    readIntSignedBe30At3,
    readIntSignedBe30At4,
    readIntSignedBe30At5,
    readIntSignedBe30At6,
    readIntSignedBe30At7,
    readIntSignedBe31At0,
    readIntSignedBe31At1,
    readIntSignedBe31At2,
    readIntSignedBe31At3,
    readIntSignedBe31At4,
    readIntSignedBe31At5,
    readIntSignedBe31At6,
    readIntSignedBe31At7,
    readIntSignedBe32At0,
    readIntSignedBe32At1,
    readIntSignedBe32At2,
    readIntSignedBe32At3,
    readIntSignedBe32At4,
    readIntSignedBe32At5,
    readIntSignedBe32At6,
    readIntSignedBe32At7,
    readIntSignedBe33At0,
    readIntSignedBe33At1,
    readIntSignedBe33At2,
    readIntSignedBe33At3,
    readIntSignedBe33At4,
    readIntSignedBe33At5,
    readIntSignedBe33At6,
    readIntSignedBe33At7,
    readIntSignedBe34At0,
    readIntSignedBe34At1,
    readIntSignedBe34At2,
    readIntSignedBe34At3,
    readIntSignedBe34At4,
    readIntSignedBe34At5,
    readIntSignedBe34At6,
    readIntSignedBe34At7,
    readIntSignedBe35At0,
    readIntSignedBe35At1,
    readIntSignedBe35At2,
    readIntSignedBe35At3,
    readIntSignedBe35At4,
    readIntSignedBe35At5,
    readIntSignedBe35At6,
    readIntSignedBe35At7,
    readIntSignedBe36At0,
    readIntSignedBe36At1,
    readIntSignedBe36At2,
    readIntSignedBe36At3,
    readIntSignedBe36At4,
    readIntSignedBe36At5,
    readIntSignedBe36At6,
    readIntSignedBe36At7,
    readIntSignedBe37At0,
    readIntSignedBe37At1,
    readIntSignedBe37At2,
    readIntSignedBe37At3,
    readIntSignedBe37At4,
    readIntSignedBe37At5,
    readIntSignedBe37At6,
    readIntSignedBe37At7,
    readIntSignedBe38At0,
    readIntSignedBe38At1,
    readIntSignedBe38At2,
    readIntSignedBe38At3,
    readIntSignedBe38At4,
    readIntSignedBe38At5,
    readIntSignedBe38At6,
    readIntSignedBe38At7,
    readIntSignedBe39At0,
    readIntSignedBe39At1,
    readIntSignedBe39At2,
    readIntSignedBe39At3,
    readIntSignedBe39At4,
    readIntSignedBe39At5,
    readIntSignedBe39At6,
    readIntSignedBe39At7,
    readIntSignedBe40At0,
    readIntSignedBe40At1,
    readIntSignedBe40At2,
    readIntSignedBe40At3,
    readIntSignedBe40At4,
    readIntSignedBe40At5,
    readIntSignedBe40At6,
    readIntSignedBe40At7,
    readIntSignedBe41At0,
    readIntSignedBe41At1,
    readIntSignedBe41At2,
    readIntSignedBe41At3,
    readIntSignedBe41At4,
    readIntSignedBe41At5,
    readIntSignedBe41At6,
    readIntSignedBe41At7,
    readIntSignedBe42At0,
    readIntSignedBe42At1,
    readIntSignedBe42At2,
    readIntSignedBe42At3,
    readIntSignedBe42At4,
    readIntSignedBe42At5,
    readIntSignedBe42At6,
    readIntSignedBe42At7,
    readIntSignedBe43At0,
    readIntSignedBe43At1,
    readIntSignedBe43At2,
    readIntSignedBe43At3,
    readIntSignedBe43At4,
    readIntSignedBe43At5,
    readIntSignedBe43At6,
    readIntSignedBe43At7,
    readIntSignedBe44At0,
    readIntSignedBe44At1,
    readIntSignedBe44At2,
    readIntSignedBe44At3,
    readIntSignedBe44At4,
    readIntSignedBe44At5,
    readIntSignedBe44At6,
    readIntSignedBe44At7,
    readIntSignedBe45At0,
    readIntSignedBe45At1,
    readIntSignedBe45At2,
    readIntSignedBe45At3,
    readIntSignedBe45At4,
    readIntSignedBe45At5,
    readIntSignedBe45At6,
    readIntSignedBe45At7,
    readIntSignedBe46At0,
    readIntSignedBe46At1,
    readIntSignedBe46At2,
    readIntSignedBe46At3,
    readIntSignedBe46At4,
    readIntSignedBe46At5,
    readIntSignedBe46At6,
    readIntSignedBe46At7,
    readIntSignedBe47At0,
    readIntSignedBe47At1,
    readIntSignedBe47At2,
    readIntSignedBe47At3,
    readIntSignedBe47At4,
    readIntSignedBe47At5,
    readIntSignedBe47At6,
    readIntSignedBe47At7,
    readIntSignedBe48At0,
    readIntSignedBe48At1,
    readIntSignedBe48At2,
    readIntSignedBe48At3,
    readIntSignedBe48At4,
    readIntSignedBe48At5,
    readIntSignedBe48At6,
    readIntSignedBe48At7,
    readIntSignedBe49At0,
    readIntSignedBe49At1,
    readIntSignedBe49At2,
    readIntSignedBe49At3,
    readIntSignedBe49At4,
    readIntSignedBe49At5,
    readIntSignedBe49At6,
    readIntSignedBe49At7,
    readIntSignedBe50At0,
    readIntSignedBe50At1,
    readIntSignedBe50At2,
    readIntSignedBe50At3,
    readIntSignedBe50At4,
    readIntSignedBe50At5,
    readIntSignedBe50At6,
    readIntSignedBe50At7,
    readIntSignedBe51At0,
    readIntSignedBe51At1,
    readIntSignedBe51At2,
    readIntSignedBe51At3,
    readIntSignedBe51At4,
    readIntSignedBe51At5,
    readIntSignedBe51At6,
    readIntSignedBe51At7,
    readIntSignedBe52At0,
    readIntSignedBe52At1,
    readIntSignedBe52At2,
    readIntSignedBe52At3,
    readIntSignedBe52At4,
    readIntSignedBe52At5,
    readIntSignedBe52At6,
    readIntSignedBe52At7,
    readIntSignedBe53At0,
    readIntSignedBe53At1,
    readIntSignedBe53At2,
    readIntSignedBe53At3,
    readIntSignedBe53At4,
    readIntSignedBe53At5,
    readIntSignedBe53At6,
    readIntSignedBe53At7,
    readIntSignedBe54At0,
    readIntSignedBe54At1,
    readIntSignedBe54At2,
    readIntSignedBe54At3,
    readIntSignedBe54At4,
    readIntSignedBe54At5,
    readIntSignedBe54At6,
    readIntSignedBe54At7,
    readIntSignedBe55At0,
    readIntSignedBe55At1,
    readIntSignedBe55At2,
    readIntSignedBe55At3,
    readIntSignedBe55At4,
    readIntSignedBe55At5,
    readIntSignedBe55At6,
    readIntSignedBe55At7,
    readIntSignedBe56At0,
    readIntSignedBe56At1,
    readIntSignedBe56At2,
    readIntSignedBe56At3,
    readIntSignedBe56At4,
    readIntSignedBe56At5,
    readIntSignedBe56At6,
    readIntSignedBe56At7,
    readIntSignedBe57At0,
    readIntSignedBe57At1,
    readIntSignedBe57At2,
    readIntSignedBe57At3,
    readIntSignedBe57At4,
    readIntSignedBe57At5,
    readIntSignedBe57At6,
    readIntSignedBe57At7,
    readIntSignedBe58At0,
    readIntSignedBe58At1,
    readIntSignedBe58At2,
    readIntSignedBe58At3,
    readIntSignedBe58At4,
    readIntSignedBe58At5,
    readIntSignedBe58At6,
    readIntSignedBe58At7,
    readIntSignedBe59At0,
    readIntSignedBe59At1,
    readIntSignedBe59At2,
    readIntSignedBe59At3,
    readIntSignedBe59At4,
    readIntSignedBe59At5,
    readIntSignedBe59At6,
    readIntSignedBe59At7,
    readIntSignedBe60At0,
    readIntSignedBe60At1,
    readIntSignedBe60At2,
    readIntSignedBe60At3,
    readIntSignedBe60At4,
    readIntSignedBe60At5,
    readIntSignedBe60At6,
    readIntSignedBe60At7,
    readIntSignedBe61At0,
    readIntSignedBe61At1,
    readIntSignedBe61At2,
    readIntSignedBe61At3,
    readIntSignedBe61At4,
    readIntSignedBe61At5,
    readIntSignedBe61At6,
    readIntSignedBe61At7,
    readIntSignedBe62At0,
    readIntSignedBe62At1,
    readIntSignedBe62At2,
    readIntSignedBe62At3,
    readIntSignedBe62At4,
    readIntSignedBe62At5,
    readIntSignedBe62At6,
    readIntSignedBe62At7,
    readIntSignedBe63At0,
    readIntSignedBe63At1,
    readIntSignedBe63At2,
    readIntSignedBe63At3,
    readIntSignedBe63At4,
    readIntSignedBe63At5,
    readIntSignedBe63At6,
    readIntSignedBe63At7,
    readIntSignedBe64At0,
    readIntSignedBe64At1,
    readIntSignedBe64At2,
    readIntSignedBe64At3,
    readIntSignedBe64At4,
    readIntSignedBe64At5,
    readIntSignedBe64At6,
    readIntSignedBe64At7,
};

static std::uint64_t (*readIntLeUnsignedFuncs[])(const std::uint8_t *) = {
    readIntUnsignedLe1At0,
    readIntUnsignedLe1At1,
    readIntUnsignedLe1At2,
    readIntUnsignedLe1At3,
    readIntUnsignedLe1At4,
    readIntUnsignedLe1At5,
    readIntUnsignedLe1At6,
    readIntUnsignedLe1At7,
    readIntUnsignedLe2At0,
    readIntUnsignedLe2At1,
    readIntUnsignedLe2At2,
    readIntUnsignedLe2At3,
    readIntUnsignedLe2At4,
    readIntUnsignedLe2At5,
    readIntUnsignedLe2At6,
    readIntUnsignedLe2At7,
    readIntUnsignedLe3At0,
    readIntUnsignedLe3At1,
    readIntUnsignedLe3At2,
    readIntUnsignedLe3At3,
    readIntUnsignedLe3At4,
    readIntUnsignedLe3At5,
    readIntUnsignedLe3At6,
    readIntUnsignedLe3At7,
    readIntUnsignedLe4At0,
    readIntUnsignedLe4At1,
    readIntUnsignedLe4At2,
    readIntUnsignedLe4At3,
    readIntUnsignedLe4At4,
    readIntUnsignedLe4At5,
    readIntUnsignedLe4At6,
    readIntUnsignedLe4At7,
    readIntUnsignedLe5At0,
    readIntUnsignedLe5At1,
    readIntUnsignedLe5At2,
    readIntUnsignedLe5At3,
    readIntUnsignedLe5At4,
    readIntUnsignedLe5At5,
    readIntUnsignedLe5At6,
    readIntUnsignedLe5At7,
    readIntUnsignedLe6At0,
    readIntUnsignedLe6At1,
    readIntUnsignedLe6At2,
    readIntUnsignedLe6At3,
    readIntUnsignedLe6At4,
    readIntUnsignedLe6At5,
    readIntUnsignedLe6At6,
    readIntUnsignedLe6At7,
    readIntUnsignedLe7At0,
    readIntUnsignedLe7At1,
    readIntUnsignedLe7At2,
    readIntUnsignedLe7At3,
    readIntUnsignedLe7At4,
    readIntUnsignedLe7At5,
    readIntUnsignedLe7At6,
    readIntUnsignedLe7At7,
    readIntUnsignedLe8At0,
    readIntUnsignedLe8At1,
    readIntUnsignedLe8At2,
    readIntUnsignedLe8At3,
    readIntUnsignedLe8At4,
    readIntUnsignedLe8At5,
    readIntUnsignedLe8At6,
    readIntUnsignedLe8At7,
    readIntUnsignedLe9At0,
    readIntUnsignedLe9At1,
    readIntUnsignedLe9At2,
    readIntUnsignedLe9At3,
    readIntUnsignedLe9At4,
    readIntUnsignedLe9At5,
    readIntUnsignedLe9At6,
    readIntUnsignedLe9At7,
    readIntUnsignedLe10At0,
    readIntUnsignedLe10At1,
    readIntUnsignedLe10At2,
    readIntUnsignedLe10At3,
    readIntUnsignedLe10At4,
    readIntUnsignedLe10At5,
    readIntUnsignedLe10At6,
    readIntUnsignedLe10At7,
    readIntUnsignedLe11At0,
    readIntUnsignedLe11At1,
    readIntUnsignedLe11At2,
    readIntUnsignedLe11At3,
    readIntUnsignedLe11At4,
    readIntUnsignedLe11At5,
    readIntUnsignedLe11At6,
    readIntUnsignedLe11At7,
    readIntUnsignedLe12At0,
    readIntUnsignedLe12At1,
    readIntUnsignedLe12At2,
    readIntUnsignedLe12At3,
    readIntUnsignedLe12At4,
    readIntUnsignedLe12At5,
    readIntUnsignedLe12At6,
    readIntUnsignedLe12At7,
    readIntUnsignedLe13At0,
    readIntUnsignedLe13At1,
    readIntUnsignedLe13At2,
    readIntUnsignedLe13At3,
    readIntUnsignedLe13At4,
    readIntUnsignedLe13At5,
    readIntUnsignedLe13At6,
    readIntUnsignedLe13At7,
    readIntUnsignedLe14At0,
    readIntUnsignedLe14At1,
    readIntUnsignedLe14At2,
    readIntUnsignedLe14At3,
    readIntUnsignedLe14At4,
    readIntUnsignedLe14At5,
    readIntUnsignedLe14At6,
    readIntUnsignedLe14At7,
    readIntUnsignedLe15At0,
    readIntUnsignedLe15At1,
    readIntUnsignedLe15At2,
    readIntUnsignedLe15At3,
    readIntUnsignedLe15At4,
    readIntUnsignedLe15At5,
    readIntUnsignedLe15At6,
    readIntUnsignedLe15At7,
    readIntUnsignedLe16At0,
    readIntUnsignedLe16At1,
    readIntUnsignedLe16At2,
    readIntUnsignedLe16At3,
    readIntUnsignedLe16At4,
    readIntUnsignedLe16At5,
    readIntUnsignedLe16At6,
    readIntUnsignedLe16At7,
    readIntUnsignedLe17At0,
    readIntUnsignedLe17At1,
    readIntUnsignedLe17At2,
    readIntUnsignedLe17At3,
    readIntUnsignedLe17At4,
    readIntUnsignedLe17At5,
    readIntUnsignedLe17At6,
    readIntUnsignedLe17At7,
    readIntUnsignedLe18At0,
    readIntUnsignedLe18At1,
    readIntUnsignedLe18At2,
    readIntUnsignedLe18At3,
    readIntUnsignedLe18At4,
    readIntUnsignedLe18At5,
    readIntUnsignedLe18At6,
    readIntUnsignedLe18At7,
    readIntUnsignedLe19At0,
    readIntUnsignedLe19At1,
    readIntUnsignedLe19At2,
    readIntUnsignedLe19At3,
    readIntUnsignedLe19At4,
    readIntUnsignedLe19At5,
    readIntUnsignedLe19At6,
    readIntUnsignedLe19At7,
    readIntUnsignedLe20At0,
    readIntUnsignedLe20At1,
    readIntUnsignedLe20At2,
    readIntUnsignedLe20At3,
    readIntUnsignedLe20At4,
    readIntUnsignedLe20At5,
    readIntUnsignedLe20At6,
    readIntUnsignedLe20At7,
    readIntUnsignedLe21At0,
    readIntUnsignedLe21At1,
    readIntUnsignedLe21At2,
    readIntUnsignedLe21At3,
    readIntUnsignedLe21At4,
    readIntUnsignedLe21At5,
    readIntUnsignedLe21At6,
    readIntUnsignedLe21At7,
    readIntUnsignedLe22At0,
    readIntUnsignedLe22At1,
    readIntUnsignedLe22At2,
    readIntUnsignedLe22At3,
    readIntUnsignedLe22At4,
    readIntUnsignedLe22At5,
    readIntUnsignedLe22At6,
    readIntUnsignedLe22At7,
    readIntUnsignedLe23At0,
    readIntUnsignedLe23At1,
    readIntUnsignedLe23At2,
    readIntUnsignedLe23At3,
    readIntUnsignedLe23At4,
    readIntUnsignedLe23At5,
    readIntUnsignedLe23At6,
    readIntUnsignedLe23At7,
    readIntUnsignedLe24At0,
    readIntUnsignedLe24At1,
    readIntUnsignedLe24At2,
    readIntUnsignedLe24At3,
    readIntUnsignedLe24At4,
    readIntUnsignedLe24At5,
    readIntUnsignedLe24At6,
    readIntUnsignedLe24At7,
    readIntUnsignedLe25At0,
    readIntUnsignedLe25At1,
    readIntUnsignedLe25At2,
    readIntUnsignedLe25At3,
    readIntUnsignedLe25At4,
    readIntUnsignedLe25At5,
    readIntUnsignedLe25At6,
    readIntUnsignedLe25At7,
    readIntUnsignedLe26At0,
    readIntUnsignedLe26At1,
    readIntUnsignedLe26At2,
    readIntUnsignedLe26At3,
    readIntUnsignedLe26At4,
    readIntUnsignedLe26At5,
    readIntUnsignedLe26At6,
    readIntUnsignedLe26At7,
    readIntUnsignedLe27At0,
    readIntUnsignedLe27At1,
    readIntUnsignedLe27At2,
    readIntUnsignedLe27At3,
    readIntUnsignedLe27At4,
    readIntUnsignedLe27At5,
    readIntUnsignedLe27At6,
    readIntUnsignedLe27At7,
    readIntUnsignedLe28At0,
    readIntUnsignedLe28At1,
    readIntUnsignedLe28At2,
    readIntUnsignedLe28At3,
    readIntUnsignedLe28At4,
    readIntUnsignedLe28At5,
    readIntUnsignedLe28At6,
    readIntUnsignedLe28At7,
    readIntUnsignedLe29At0,
    readIntUnsignedLe29At1,
    readIntUnsignedLe29At2,
    readIntUnsignedLe29At3,
    readIntUnsignedLe29At4,
    readIntUnsignedLe29At5,
    readIntUnsignedLe29At6,
    readIntUnsignedLe29At7,
    readIntUnsignedLe30At0,
    readIntUnsignedLe30At1,
    readIntUnsignedLe30At2,
    readIntUnsignedLe30At3,
    readIntUnsignedLe30At4,
    readIntUnsignedLe30At5,
    readIntUnsignedLe30At6,
    readIntUnsignedLe30At7,
    readIntUnsignedLe31At0,
    readIntUnsignedLe31At1,
    readIntUnsignedLe31At2,
    readIntUnsignedLe31At3,
    readIntUnsignedLe31At4,
    readIntUnsignedLe31At5,
    readIntUnsignedLe31At6,
    readIntUnsignedLe31At7,
    readIntUnsignedLe32At0,
    readIntUnsignedLe32At1,
    readIntUnsignedLe32At2,
    readIntUnsignedLe32At3,
    readIntUnsignedLe32At4,
    readIntUnsignedLe32At5,
    readIntUnsignedLe32At6,
    readIntUnsignedLe32At7,
    readIntUnsignedLe33At0,
    readIntUnsignedLe33At1,
    readIntUnsignedLe33At2,
    readIntUnsignedLe33At3,
    readIntUnsignedLe33At4,
    readIntUnsignedLe33At5,
    readIntUnsignedLe33At6,
    readIntUnsignedLe33At7,
    readIntUnsignedLe34At0,
    readIntUnsignedLe34At1,
    readIntUnsignedLe34At2,
    readIntUnsignedLe34At3,
    readIntUnsignedLe34At4,
    readIntUnsignedLe34At5,
    readIntUnsignedLe34At6,
    readIntUnsignedLe34At7,
    readIntUnsignedLe35At0,
    readIntUnsignedLe35At1,
    readIntUnsignedLe35At2,
    readIntUnsignedLe35At3,
    readIntUnsignedLe35At4,
    readIntUnsignedLe35At5,
    readIntUnsignedLe35At6,
    readIntUnsignedLe35At7,
    readIntUnsignedLe36At0,
    readIntUnsignedLe36At1,
    readIntUnsignedLe36At2,
    readIntUnsignedLe36At3,
    readIntUnsignedLe36At4,
    readIntUnsignedLe36At5,
    readIntUnsignedLe36At6,
    readIntUnsignedLe36At7,
    readIntUnsignedLe37At0,
    readIntUnsignedLe37At1,
    readIntUnsignedLe37At2,
    readIntUnsignedLe37At3,
    readIntUnsignedLe37At4,
    readIntUnsignedLe37At5,
    readIntUnsignedLe37At6,
    readIntUnsignedLe37At7,
    readIntUnsignedLe38At0,
    readIntUnsignedLe38At1,
    readIntUnsignedLe38At2,
    readIntUnsignedLe38At3,
    readIntUnsignedLe38At4,
    readIntUnsignedLe38At5,
    readIntUnsignedLe38At6,
    readIntUnsignedLe38At7,
    readIntUnsignedLe39At0,
    readIntUnsignedLe39At1,
    readIntUnsignedLe39At2,
    readIntUnsignedLe39At3,
    readIntUnsignedLe39At4,
    readIntUnsignedLe39At5,
    readIntUnsignedLe39At6,
    readIntUnsignedLe39At7,
    readIntUnsignedLe40At0,
    readIntUnsignedLe40At1,
    readIntUnsignedLe40At2,
    readIntUnsignedLe40At3,
    readIntUnsignedLe40At4,
    readIntUnsignedLe40At5,
    readIntUnsignedLe40At6,
    readIntUnsignedLe40At7,
    readIntUnsignedLe41At0,
    readIntUnsignedLe41At1,
    readIntUnsignedLe41At2,
    readIntUnsignedLe41At3,
    readIntUnsignedLe41At4,
    readIntUnsignedLe41At5,
    readIntUnsignedLe41At6,
    readIntUnsignedLe41At7,
    readIntUnsignedLe42At0,
    readIntUnsignedLe42At1,
    readIntUnsignedLe42At2,
    readIntUnsignedLe42At3,
    readIntUnsignedLe42At4,
    readIntUnsignedLe42At5,
    readIntUnsignedLe42At6,
    readIntUnsignedLe42At7,
    readIntUnsignedLe43At0,
    readIntUnsignedLe43At1,
    readIntUnsignedLe43At2,
    readIntUnsignedLe43At3,
    readIntUnsignedLe43At4,
    readIntUnsignedLe43At5,
    readIntUnsignedLe43At6,
    readIntUnsignedLe43At7,
    readIntUnsignedLe44At0,
    readIntUnsignedLe44At1,
    readIntUnsignedLe44At2,
    readIntUnsignedLe44At3,
    readIntUnsignedLe44At4,
    readIntUnsignedLe44At5,
    readIntUnsignedLe44At6,
    readIntUnsignedLe44At7,
    readIntUnsignedLe45At0,
    readIntUnsignedLe45At1,
    readIntUnsignedLe45At2,
    readIntUnsignedLe45At3,
    readIntUnsignedLe45At4,
    readIntUnsignedLe45At5,
    readIntUnsignedLe45At6,
    readIntUnsignedLe45At7,
    readIntUnsignedLe46At0,
    readIntUnsignedLe46At1,
    readIntUnsignedLe46At2,
    readIntUnsignedLe46At3,
    readIntUnsignedLe46At4,
    readIntUnsignedLe46At5,
    readIntUnsignedLe46At6,
    readIntUnsignedLe46At7,
    readIntUnsignedLe47At0,
    readIntUnsignedLe47At1,
    readIntUnsignedLe47At2,
    readIntUnsignedLe47At3,
    readIntUnsignedLe47At4,
    readIntUnsignedLe47At5,
    readIntUnsignedLe47At6,
    readIntUnsignedLe47At7,
    readIntUnsignedLe48At0,
    readIntUnsignedLe48At1,
    readIntUnsignedLe48At2,
    readIntUnsignedLe48At3,
    readIntUnsignedLe48At4,
    readIntUnsignedLe48At5,
    readIntUnsignedLe48At6,
    readIntUnsignedLe48At7,
    readIntUnsignedLe49At0,
    readIntUnsignedLe49At1,
    readIntUnsignedLe49At2,
    readIntUnsignedLe49At3,
    readIntUnsignedLe49At4,
    readIntUnsignedLe49At5,
    readIntUnsignedLe49At6,
    readIntUnsignedLe49At7,
    readIntUnsignedLe50At0,
    readIntUnsignedLe50At1,
    readIntUnsignedLe50At2,
    readIntUnsignedLe50At3,
    readIntUnsignedLe50At4,
    readIntUnsignedLe50At5,
    readIntUnsignedLe50At6,
    readIntUnsignedLe50At7,
    readIntUnsignedLe51At0,
    readIntUnsignedLe51At1,
    readIntUnsignedLe51At2,
    readIntUnsignedLe51At3,
    readIntUnsignedLe51At4,
    readIntUnsignedLe51At5,
    readIntUnsignedLe51At6,
    readIntUnsignedLe51At7,
    readIntUnsignedLe52At0,
    readIntUnsignedLe52At1,
    readIntUnsignedLe52At2,
    readIntUnsignedLe52At3,
    readIntUnsignedLe52At4,
    readIntUnsignedLe52At5,
    readIntUnsignedLe52At6,
    readIntUnsignedLe52At7,
    readIntUnsignedLe53At0,
    readIntUnsignedLe53At1,
    readIntUnsignedLe53At2,
    readIntUnsignedLe53At3,
    readIntUnsignedLe53At4,
    readIntUnsignedLe53At5,
    readIntUnsignedLe53At6,
    readIntUnsignedLe53At7,
    readIntUnsignedLe54At0,
    readIntUnsignedLe54At1,
    readIntUnsignedLe54At2,
    readIntUnsignedLe54At3,
    readIntUnsignedLe54At4,
    readIntUnsignedLe54At5,
    readIntUnsignedLe54At6,
    readIntUnsignedLe54At7,
    readIntUnsignedLe55At0,
    readIntUnsignedLe55At1,
    readIntUnsignedLe55At2,
    readIntUnsignedLe55At3,
    readIntUnsignedLe55At4,
    readIntUnsignedLe55At5,
    readIntUnsignedLe55At6,
    readIntUnsignedLe55At7,
    readIntUnsignedLe56At0,
    readIntUnsignedLe56At1,
    readIntUnsignedLe56At2,
    readIntUnsignedLe56At3,
    readIntUnsignedLe56At4,
    readIntUnsignedLe56At5,
    readIntUnsignedLe56At6,
    readIntUnsignedLe56At7,
    readIntUnsignedLe57At0,
    readIntUnsignedLe57At1,
    readIntUnsignedLe57At2,
    readIntUnsignedLe57At3,
    readIntUnsignedLe57At4,
    readIntUnsignedLe57At5,
    readIntUnsignedLe57At6,
    readIntUnsignedLe57At7,
    readIntUnsignedLe58At0,
    readIntUnsignedLe58At1,
    readIntUnsignedLe58At2,
    readIntUnsignedLe58At3,
    readIntUnsignedLe58At4,
    readIntUnsignedLe58At5,
    readIntUnsignedLe58At6,
    readIntUnsignedLe58At7,
    readIntUnsignedLe59At0,
    readIntUnsignedLe59At1,
    readIntUnsignedLe59At2,
    readIntUnsignedLe59At3,
    readIntUnsignedLe59At4,
    readIntUnsignedLe59At5,
    readIntUnsignedLe59At6,
    readIntUnsignedLe59At7,
    readIntUnsignedLe60At0,
    readIntUnsignedLe60At1,
    readIntUnsignedLe60At2,
    readIntUnsignedLe60At3,
    readIntUnsignedLe60At4,
    readIntUnsignedLe60At5,
    readIntUnsignedLe60At6,
    readIntUnsignedLe60At7,
    readIntUnsignedLe61At0,
    readIntUnsignedLe61At1,
    readIntUnsignedLe61At2,
    readIntUnsignedLe61At3,
    readIntUnsignedLe61At4,
    readIntUnsignedLe61At5,
    readIntUnsignedLe61At6,
    readIntUnsignedLe61At7,
    readIntUnsignedLe62At0,
    readIntUnsignedLe62At1,
    readIntUnsignedLe62At2,
    readIntUnsignedLe62At3,
    readIntUnsignedLe62At4,
    readIntUnsignedLe62At5,
    readIntUnsignedLe62At6,
    readIntUnsignedLe62At7,
    readIntUnsignedLe63At0,
    readIntUnsignedLe63At1,
    readIntUnsignedLe63At2,
    readIntUnsignedLe63At3,
    readIntUnsignedLe63At4,
    readIntUnsignedLe63At5,
    readIntUnsignedLe63At6,
    readIntUnsignedLe63At7,
    readIntUnsignedLe64At0,
    readIntUnsignedLe64At1,
    readIntUnsignedLe64At2,
    readIntUnsignedLe64At3,
    readIntUnsignedLe64At4,
    readIntUnsignedLe64At5,
    readIntUnsignedLe64At6,
    readIntUnsignedLe64At7,
};

static std::int64_t (*readIntLeSignedFuncs[])(const std::uint8_t *) = {
    readIntSignedLe1At0,
    readIntSignedLe1At1,
    readIntSignedLe1At2,
    readIntSignedLe1At3,
    readIntSignedLe1At4,
    readIntSignedLe1At5,
    readIntSignedLe1At6,
    readIntSignedLe1At7,
    readIntSignedLe2At0,
    readIntSignedLe2At1,
    readIntSignedLe2At2,
    readIntSignedLe2At3,
    readIntSignedLe2At4,
    readIntSignedLe2At5,
    readIntSignedLe2At6,
    readIntSignedLe2At7,
    readIntSignedLe3At0,
    readIntSignedLe3At1,
    readIntSignedLe3At2,
    readIntSignedLe3At3,
    readIntSignedLe3At4,
    readIntSignedLe3At5,
    readIntSignedLe3At6,
    readIntSignedLe3At7,
    readIntSignedLe4At0,
    readIntSignedLe4At1,
    readIntSignedLe4At2,
    readIntSignedLe4At3,
    readIntSignedLe4At4,
    readIntSignedLe4At5,
    readIntSignedLe4At6,
    readIntSignedLe4At7,
    readIntSignedLe5At0,
    readIntSignedLe5At1,
    readIntSignedLe5At2,
    readIntSignedLe5At3,
    readIntSignedLe5At4,
    readIntSignedLe5At5,
    readIntSignedLe5At6,
    readIntSignedLe5At7,
    readIntSignedLe6At0,
    readIntSignedLe6At1,
    readIntSignedLe6At2,
    readIntSignedLe6At3,
    readIntSignedLe6At4,
    readIntSignedLe6At5,
    readIntSignedLe6At6,
    readIntSignedLe6At7,
    readIntSignedLe7At0,
    readIntSignedLe7At1,
    readIntSignedLe7At2,
    readIntSignedLe7At3,
    readIntSignedLe7At4,
    readIntSignedLe7At5,
    readIntSignedLe7At6,
    readIntSignedLe7At7,
    readIntSignedLe8At0,
    readIntSignedLe8At1,
    readIntSignedLe8At2,
    readIntSignedLe8At3,
    readIntSignedLe8At4,
    readIntSignedLe8At5,
    readIntSignedLe8At6,
    readIntSignedLe8At7,
    readIntSignedLe9At0,
    readIntSignedLe9At1,
    readIntSignedLe9At2,
    readIntSignedLe9At3,
    readIntSignedLe9At4,
    readIntSignedLe9At5,
    readIntSignedLe9At6,
    readIntSignedLe9At7,
    readIntSignedLe10At0,
    readIntSignedLe10At1,
    readIntSignedLe10At2,
    readIntSignedLe10At3,
    readIntSignedLe10At4,
    readIntSignedLe10At5,
    readIntSignedLe10At6,
    readIntSignedLe10At7,
    readIntSignedLe11At0,
    readIntSignedLe11At1,
    readIntSignedLe11At2,
    readIntSignedLe11At3,
    readIntSignedLe11At4,
    readIntSignedLe11At5,
    readIntSignedLe11At6,
    readIntSignedLe11At7,
    readIntSignedLe12At0,
    readIntSignedLe12At1,
    readIntSignedLe12At2,
    readIntSignedLe12At3,
    readIntSignedLe12At4,
    readIntSignedLe12At5,
    readIntSignedLe12At6,
    readIntSignedLe12At7,
    readIntSignedLe13At0,
    readIntSignedLe13At1,
    readIntSignedLe13At2,
    readIntSignedLe13At3,
    readIntSignedLe13At4,
    readIntSignedLe13At5,
    readIntSignedLe13At6,
    readIntSignedLe13At7,
    readIntSignedLe14At0,
    readIntSignedLe14At1,
    readIntSignedLe14At2,
    readIntSignedLe14At3,
    readIntSignedLe14At4,
    readIntSignedLe14At5,
    readIntSignedLe14At6,
    readIntSignedLe14At7,
    readIntSignedLe15At0,
    readIntSignedLe15At1,
    readIntSignedLe15At2,
    readIntSignedLe15At3,
    readIntSignedLe15At4,
    readIntSignedLe15At5,
    readIntSignedLe15At6,
    readIntSignedLe15At7,
    readIntSignedLe16At0,
    readIntSignedLe16At1,
    readIntSignedLe16At2,
    readIntSignedLe16At3,
    readIntSignedLe16At4,
    readIntSignedLe16At5,
    readIntSignedLe16At6,
    readIntSignedLe16At7,
    readIntSignedLe17At0,
    readIntSignedLe17At1,
    readIntSignedLe17At2,
    readIntSignedLe17At3,
    readIntSignedLe17At4,
    readIntSignedLe17At5,
    readIntSignedLe17At6,
    readIntSignedLe17At7,
    readIntSignedLe18At0,
    readIntSignedLe18At1,
    readIntSignedLe18At2,
    readIntSignedLe18At3,
    readIntSignedLe18At4,
    readIntSignedLe18At5,
    readIntSignedLe18At6,
    readIntSignedLe18At7,
    readIntSignedLe19At0,
    readIntSignedLe19At1,
    readIntSignedLe19At2,
    readIntSignedLe19At3,
    readIntSignedLe19At4,
    readIntSignedLe19At5,
    readIntSignedLe19At6,
    readIntSignedLe19At7,
    readIntSignedLe20At0,
    readIntSignedLe20At1,
    readIntSignedLe20At2,
    readIntSignedLe20At3,
    readIntSignedLe20At4,
    readIntSignedLe20At5,
    readIntSignedLe20At6,
    readIntSignedLe20At7,
    readIntSignedLe21At0,
    readIntSignedLe21At1,
    readIntSignedLe21At2,
    readIntSignedLe21At3,
    readIntSignedLe21At4,
    readIntSignedLe21At5,
    readIntSignedLe21At6,
    readIntSignedLe21At7,
    readIntSignedLe22At0,
    readIntSignedLe22At1,
    readIntSignedLe22At2,
    readIntSignedLe22At3,
    readIntSignedLe22At4,
    readIntSignedLe22At5,
    readIntSignedLe22At6,
    readIntSignedLe22At7,
    readIntSignedLe23At0,
    readIntSignedLe23At1,
    readIntSignedLe23At2,
    readIntSignedLe23At3,
    readIntSignedLe23At4,
    readIntSignedLe23At5,
    readIntSignedLe23At6,
    readIntSignedLe23At7,
    readIntSignedLe24At0,
    readIntSignedLe24At1,
    readIntSignedLe24At2,
    readIntSignedLe24At3,
    readIntSignedLe24At4,
    readIntSignedLe24At5,
    readIntSignedLe24At6,
    readIntSignedLe24At7,
    readIntSignedLe25At0,
    readIntSignedLe25At1,
    readIntSignedLe25At2,
    readIntSignedLe25At3,
    readIntSignedLe25At4,
    readIntSignedLe25At5,
    readIntSignedLe25At6,
    readIntSignedLe25At7,
    readIntSignedLe26At0,
    readIntSignedLe26At1,
    readIntSignedLe26At2,
    readIntSignedLe26At3,
    readIntSignedLe26At4,
    readIntSignedLe26At5,
    readIntSignedLe26At6,
    readIntSignedLe26At7,
    readIntSignedLe27At0,
    readIntSignedLe27At1,
    readIntSignedLe27At2,
    readIntSignedLe27At3,
    readIntSignedLe27At4,
    readIntSignedLe27At5,
    readIntSignedLe27At6,
    readIntSignedLe27At7,
    readIntSignedLe28At0,
    readIntSignedLe28At1,
    readIntSignedLe28At2,
    readIntSignedLe28At3,
    readIntSignedLe28At4,
    readIntSignedLe28At5,
    readIntSignedLe28At6,
    readIntSignedLe28At7,
    readIntSignedLe29At0,
    readIntSignedLe29At1,
    readIntSignedLe29At2,
    readIntSignedLe29At3,
    readIntSignedLe29At4,
    readIntSignedLe29At5,
    readIntSignedLe29At6,
    readIntSignedLe29At7,
    readIntSignedLe30At0,
    readIntSignedLe30At1,
    readIntSignedLe30At2,
    readIntSignedLe30At3,
    readIntSignedLe30At4,
    readIntSignedLe30At5,
    readIntSignedLe30At6,
    readIntSignedLe30At7,
    readIntSignedLe31At0,
    readIntSignedLe31At1,
    readIntSignedLe31At2,
    readIntSignedLe31At3,
    readIntSignedLe31At4,
    readIntSignedLe31At5,
    readIntSignedLe31At6,
    readIntSignedLe31At7,
    readIntSignedLe32At0,
    readIntSignedLe32At1,
    readIntSignedLe32At2,
    readIntSignedLe32At3,
    readIntSignedLe32At4,
    readIntSignedLe32At5,
    readIntSignedLe32At6,
    readIntSignedLe32At7,
    readIntSignedLe33At0,
    readIntSignedLe33At1,
    readIntSignedLe33At2,
    readIntSignedLe33At3,
    readIntSignedLe33At4,
    readIntSignedLe33At5,
    readIntSignedLe33At6,
    readIntSignedLe33At7,
    readIntSignedLe34At0,
    readIntSignedLe34At1,
    readIntSignedLe34At2,
    readIntSignedLe34At3,
    readIntSignedLe34At4,
    readIntSignedLe34At5,
    readIntSignedLe34At6,
    readIntSignedLe34At7,
    readIntSignedLe35At0,
    readIntSignedLe35At1,
    readIntSignedLe35At2,
    readIntSignedLe35At3,
    readIntSignedLe35At4,
    readIntSignedLe35At5,
    readIntSignedLe35At6,
    readIntSignedLe35At7,
    readIntSignedLe36At0,
    readIntSignedLe36At1,
    readIntSignedLe36At2,
    readIntSignedLe36At3,
    readIntSignedLe36At4,
    readIntSignedLe36At5,
    readIntSignedLe36At6,
    readIntSignedLe36At7,
    readIntSignedLe37At0,
    readIntSignedLe37At1,
    readIntSignedLe37At2,
    readIntSignedLe37At3,
    readIntSignedLe37At4,
    readIntSignedLe37At5,
    readIntSignedLe37At6,
    readIntSignedLe37At7,
    readIntSignedLe38At0,
    readIntSignedLe38At1,
    readIntSignedLe38At2,
    readIntSignedLe38At3,
    readIntSignedLe38At4,
    readIntSignedLe38At5,
    readIntSignedLe38At6,
    readIntSignedLe38At7,
    readIntSignedLe39At0,
    readIntSignedLe39At1,
    readIntSignedLe39At2,
    readIntSignedLe39At3,
    readIntSignedLe39At4,
    readIntSignedLe39At5,
    readIntSignedLe39At6,
    readIntSignedLe39At7,
    readIntSignedLe40At0,
    readIntSignedLe40At1,
    readIntSignedLe40At2,
    readIntSignedLe40At3,
    readIntSignedLe40At4,
    readIntSignedLe40At5,
    readIntSignedLe40At6,
    readIntSignedLe40At7,
    readIntSignedLe41At0,
    readIntSignedLe41At1,
    readIntSignedLe41At2,
    readIntSignedLe41At3,
    readIntSignedLe41At4,
    readIntSignedLe41At5,
    readIntSignedLe41At6,
    readIntSignedLe41At7,
    readIntSignedLe42At0,
    readIntSignedLe42At1,
    readIntSignedLe42At2,
    readIntSignedLe42At3,
    readIntSignedLe42At4,
    readIntSignedLe42At5,
    readIntSignedLe42At6,
    readIntSignedLe42At7,
    readIntSignedLe43At0,
    readIntSignedLe43At1,
    readIntSignedLe43At2,
    readIntSignedLe43At3,
    readIntSignedLe43At4,
    readIntSignedLe43At5,
    readIntSignedLe43At6,
    readIntSignedLe43At7,
    readIntSignedLe44At0,
    readIntSignedLe44At1,
    readIntSignedLe44At2,
    readIntSignedLe44At3,
    readIntSignedLe44At4,
    readIntSignedLe44At5,
    readIntSignedLe44At6,
    readIntSignedLe44At7,
    readIntSignedLe45At0,
    readIntSignedLe45At1,
    readIntSignedLe45At2,
    readIntSignedLe45At3,
    readIntSignedLe45At4,
    readIntSignedLe45At5,
    readIntSignedLe45At6,
    readIntSignedLe45At7,
    readIntSignedLe46At0,
    readIntSignedLe46At1,
    readIntSignedLe46At2,
    readIntSignedLe46At3,
    readIntSignedLe46At4,
    readIntSignedLe46At5,
    readIntSignedLe46At6,
    readIntSignedLe46At7,
    readIntSignedLe47At0,
    readIntSignedLe47At1,
    readIntSignedLe47At2,
    readIntSignedLe47At3,
    readIntSignedLe47At4,
    readIntSignedLe47At5,
    readIntSignedLe47At6,
    readIntSignedLe47At7,
    readIntSignedLe48At0,
    readIntSignedLe48At1,
    readIntSignedLe48At2,
    readIntSignedLe48At3,
    readIntSignedLe48At4,
    readIntSignedLe48At5,
    readIntSignedLe48At6,
    readIntSignedLe48At7,
    readIntSignedLe49At0,
    readIntSignedLe49At1,
    readIntSignedLe49At2,
    readIntSignedLe49At3,
    readIntSignedLe49At4,
    readIntSignedLe49At5,
    readIntSignedLe49At6,
    readIntSignedLe49At7,
    readIntSignedLe50At0,
    readIntSignedLe50At1,
    readIntSignedLe50At2,
    readIntSignedLe50At3,
    readIntSignedLe50At4,
    readIntSignedLe50At5,
    readIntSignedLe50At6,
    readIntSignedLe50At7,
    readIntSignedLe51At0,
    readIntSignedLe51At1,
    readIntSignedLe51At2,
    readIntSignedLe51At3,
    readIntSignedLe51At4,
    readIntSignedLe51At5,
    readIntSignedLe51At6,
    readIntSignedLe51At7,
    readIntSignedLe52At0,
    readIntSignedLe52At1,
    readIntSignedLe52At2,
    readIntSignedLe52At3,
    readIntSignedLe52At4,
    readIntSignedLe52At5,
    readIntSignedLe52At6,
    readIntSignedLe52At7,
    readIntSignedLe53At0,
    readIntSignedLe53At1,
    readIntSignedLe53At2,
    readIntSignedLe53At3,
    readIntSignedLe53At4,
    readIntSignedLe53At5,
    readIntSignedLe53At6,
    readIntSignedLe53At7,
    readIntSignedLe54At0,
    readIntSignedLe54At1,
    readIntSignedLe54At2,
    readIntSignedLe54At3,
    readIntSignedLe54At4,
    readIntSignedLe54At5,
    readIntSignedLe54At6,
    readIntSignedLe54At7,
    readIntSignedLe55At0,
    readIntSignedLe55At1,
    readIntSignedLe55At2,
    readIntSignedLe55At3,
    readIntSignedLe55At4,
    readIntSignedLe55At5,
    readIntSignedLe55At6,
    readIntSignedLe55At7,
    readIntSignedLe56At0,
    readIntSignedLe56At1,
    readIntSignedLe56At2,
    readIntSignedLe56At3,
    readIntSignedLe56At4,
    readIntSignedLe56At5,
    readIntSignedLe56At6,
    readIntSignedLe56At7,
    readIntSignedLe57At0,
    readIntSignedLe57At1,
    readIntSignedLe57At2,
    readIntSignedLe57At3,
    readIntSignedLe57At4,
    readIntSignedLe57At5,
    readIntSignedLe57At6,
    readIntSignedLe57At7,
    readIntSignedLe58At0,
    readIntSignedLe58At1,
    readIntSignedLe58At2,
    readIntSignedLe58At3,
    readIntSignedLe58At4,
    readIntSignedLe58At5,
    readIntSignedLe58At6,
    readIntSignedLe58At7,
    readIntSignedLe59At0,
    readIntSignedLe59At1,
    readIntSignedLe59At2,
    readIntSignedLe59At3,
    readIntSignedLe59At4,
    readIntSignedLe59At5,
    readIntSignedLe59At6,
    readIntSignedLe59At7,
    readIntSignedLe60At0,
    readIntSignedLe60At1,
    readIntSignedLe60At2,
    readIntSignedLe60At3,
    readIntSignedLe60At4,
    readIntSignedLe60At5,
    readIntSignedLe60At6,
    readIntSignedLe60At7,
    readIntSignedLe61At0,
    readIntSignedLe61At1,
    readIntSignedLe61At2,
    readIntSignedLe61At3,
    readIntSignedLe61At4,
    readIntSignedLe61At5,
    readIntSignedLe61At6,
    readIntSignedLe61At7,
    readIntSignedLe62At0,
    readIntSignedLe62At1,
    readIntSignedLe62At2,
    readIntSignedLe62At3,
    readIntSignedLe62At4,
    readIntSignedLe62At5,
    readIntSignedLe62At6,
    readIntSignedLe62At7,
    readIntSignedLe63At0,
    readIntSignedLe63At1,
    readIntSignedLe63At2,
    readIntSignedLe63At3,
    readIntSignedLe63At4,
    readIntSignedLe63At5,
    readIntSignedLe63At6,
    readIntSignedLe63At7,
    readIntSignedLe64At0,
    readIntSignedLe64At1,
    readIntSignedLe64At2,
    readIntSignedLe64At3,
    readIntSignedLe64At4,
    readIntSignedLe64At5,
    readIntSignedLe64At6,
    readIntSignedLe64At7,
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INT_READER_HPP
