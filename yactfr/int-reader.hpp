/*
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

static std::uint64_t readUIntBe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntBe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntBe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntBe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntBe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntBe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntBe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntBe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntBe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntBe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntBe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntBe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntBe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntBe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntBe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntBe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntBe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntBe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntBe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntBe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntBe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntBe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntBe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntBe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntBe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntBe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe26At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntBe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe27At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe27At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntBe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe28At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe28At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe28At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntBe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe29At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe29At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe29At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe29At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntBe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe30At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe30At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe30At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe30At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe30At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntBe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe31At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe31At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe31At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe31At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe31At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe31At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntBe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe32At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe32At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe32At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe32At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe32At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe32At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe32At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntBe33At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe33At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe33At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe33At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe33At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe33At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe33At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntBe36At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe36At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe36At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe36At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntBe37At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe37At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe37At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntBe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntBe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntBe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntBe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntBe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntBe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntBe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntBe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntBe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 1;
    res |= (buf[3] >> 7);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 2;
    res |= (buf[3] >> 6);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe26At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 3;
    res |= (buf[3] >> 5);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe27At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 4;
    res |= (buf[3] >> 4);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe28At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 5;
    res |= (buf[3] >> 3);
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe29At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 6;
    res |= (buf[3] >> 2);
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe30At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 7;
    res |= (buf[3] >> 1);
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe31At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe32At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[3];
    res <<= 8;
    res |= buf[4];
    res <<= 8;
    res |= buf[5];
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntBe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::int64_t readSIntBe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

static std::uint64_t readUIntLe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);
    return res;
}

static std::uint64_t readUIntLe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3);
    return res;
}

static std::uint64_t readUIntLe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7);
    return res;
}

static std::uint64_t readUIntLe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xf);
    return res;
}

static std::uint64_t readUIntLe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1f);
    return res;
}

static std::uint64_t readUIntLe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3f);
    return res;
}

static std::uint64_t readUIntLe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7f);
    return res;
}

static std::uint64_t readUIntLe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xff);
    return res;
}

static std::uint64_t readUIntLe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ff);
    return res;
}

static std::uint64_t readUIntLe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3ff);
    return res;
}

static std::uint64_t readUIntLe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7ff);
    return res;
}

static std::uint64_t readUIntLe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xfff);
    return res;
}

static std::uint64_t readUIntLe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1fff);
    return res;
}

static std::uint64_t readUIntLe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3fff);
    return res;
}

static std::uint64_t readUIntLe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7fff);
    return res;
}

static std::uint64_t readUIntLe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xffff);
    return res;
}

static std::uint64_t readUIntLe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ffff);
    return res;
}

static std::uint64_t readUIntLe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3ffff);
    return res;
}

static std::uint64_t readUIntLe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7ffff);
    return res;
}

static std::uint64_t readUIntLe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xfffff);
    return res;
}

static std::uint64_t readUIntLe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1fffff);
    return res;
}

static std::uint64_t readUIntLe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3fffff);
    return res;
}

static std::uint64_t readUIntLe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7fffff);
    return res;
}

static std::uint64_t readUIntLe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xffffff);
    return res;
}

static std::uint64_t readUIntLe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ffffff);
    return res;
}

static std::uint64_t readUIntLe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe26At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffff);
    return res;
}

static std::uint64_t readUIntLe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe27At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe27At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);
    return res;
}

static std::uint64_t readUIntLe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe28At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe28At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe28At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);
    return res;
}

static std::uint64_t readUIntLe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe29At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe29At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe29At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe29At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);
    return res;
}

static std::uint64_t readUIntLe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe30At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe30At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe30At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe30At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe30At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);
    return res;
}

static std::uint64_t readUIntLe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe31At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe31At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe31At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe31At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe31At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe31At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);
    return res;
}

static std::uint64_t readUIntLe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe32At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe32At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe32At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe32At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe32At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe32At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe32At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);
    return res;
}

static std::uint64_t readUIntLe33At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe33At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe33At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe33At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe33At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe33At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe33At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe33At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe34At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe35At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);
    return res;
}

static std::uint64_t readUIntLe36At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe36At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe36At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe36At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe36At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe36At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe36At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe36At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);
    return res;
}

static std::uint64_t readUIntLe37At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe37At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe37At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe37At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe37At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe37At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe37At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe37At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe38At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe39At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);
    return res;
}

static std::uint64_t readUIntLe40At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe40At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe40At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe40At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe40At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe40At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe40At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe40At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe41At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe42At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe43At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe44At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe45At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe46At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe47At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe48At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe49At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe50At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe51At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe52At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe53At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe54At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe55At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe56At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe57At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe58At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe59At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe60At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe61At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe62At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe63At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);
    return res;
}

static std::uint64_t readUIntLe64At0(const std::uint8_t * const buf) {
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

static std::uint64_t readUIntLe64At1(const std::uint8_t * const buf) {
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

static std::uint64_t readUIntLe64At2(const std::uint8_t * const buf) {
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

static std::uint64_t readUIntLe64At3(const std::uint8_t * const buf) {
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

static std::uint64_t readUIntLe64At4(const std::uint8_t * const buf) {
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

static std::uint64_t readUIntLe64At5(const std::uint8_t * const buf) {
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

static std::uint64_t readUIntLe64At6(const std::uint8_t * const buf) {
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

static std::uint64_t readUIntLe64At7(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ff);

    if (res >> 8) {
        res |= UINT64_C(0xfffffffffffffe00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3ff);

    if (res >> 9) {
        res |= UINT64_C(0xfffffffffffffc00);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7ff);

    if (res >> 10) {
        res |= UINT64_C(0xfffffffffffff800);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xfff);

    if (res >> 11) {
        res |= UINT64_C(0xfffffffffffff000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1fff);

    if (res >> 12) {
        res |= UINT64_C(0xffffffffffffe000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3fff);

    if (res >> 13) {
        res |= UINT64_C(0xffffffffffffc000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7fff);

    if (res >> 14) {
        res |= UINT64_C(0xffffffffffff8000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xffff);

    if (res >> 15) {
        res |= UINT64_C(0xffffffffffff0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ffff);

    if (res >> 16) {
        res |= UINT64_C(0xfffffffffffe0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe18At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3ffff);

    if (res >> 17) {
        res |= UINT64_C(0xfffffffffffc0000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe19At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7ffff);

    if (res >> 18) {
        res |= UINT64_C(0xfffffffffff80000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe20At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xfffff);

    if (res >> 19) {
        res |= UINT64_C(0xfffffffffff00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe21At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1fffff);

    if (res >> 20) {
        res |= UINT64_C(0xffffffffffe00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe22At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3fffff);

    if (res >> 21) {
        res |= UINT64_C(0xffffffffffc00000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe23At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7fffff);

    if (res >> 22) {
        res |= UINT64_C(0xffffffffff800000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe24At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xffffff);

    if (res >> 23) {
        res |= UINT64_C(0xffffffffff000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe25At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ffffff);

    if (res >> 24) {
        res |= UINT64_C(0xfffffffffe000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe26At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffff);

    if (res >> 25) {
        res |= UINT64_C(0xfffffffffc000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe27At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffff);

    if (res >> 26) {
        res |= UINT64_C(0xfffffffff8000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe28At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffff);

    if (res >> 27) {
        res |= UINT64_C(0xfffffffff0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe29At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffff);

    if (res >> 28) {
        res |= UINT64_C(0xffffffffe0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe30At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffff);

    if (res >> 29) {
        res |= UINT64_C(0xffffffffc0000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe31At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffff);

    if (res >> 30) {
        res |= UINT64_C(0xffffffff80000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[3];
    res <<= 8;
    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe32At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffff);

    if (res >> 31) {
        res |= UINT64_C(0xffffffff00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe33At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffff);

    if (res >> 32) {
        res |= UINT64_C(0xfffffffe00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe34At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffff);

    if (res >> 33) {
        res |= UINT64_C(0xfffffffc00000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe35At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffff);

    if (res >> 34) {
        res |= UINT64_C(0xfffffff800000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe36At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffff);

    if (res >> 35) {
        res |= UINT64_C(0xfffffff000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe37At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffff);

    if (res >> 36) {
        res |= UINT64_C(0xffffffe000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe38At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffff);

    if (res >> 37) {
        res |= UINT64_C(0xffffffc000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe39At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffff);

    if (res >> 38) {
        res |= UINT64_C(0xffffff8000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe40At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffff);

    if (res >> 39) {
        res |= UINT64_C(0xffffff0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe41At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffff);

    if (res >> 40) {
        res |= UINT64_C(0xfffffe0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe42At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffff);

    if (res >> 41) {
        res |= UINT64_C(0xfffffc0000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe43At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffff);

    if (res >> 42) {
        res |= UINT64_C(0xfffff80000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe44At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffff);

    if (res >> 43) {
        res |= UINT64_C(0xfffff00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe45At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffff);

    if (res >> 44) {
        res |= UINT64_C(0xffffe00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe46At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffff);

    if (res >> 45) {
        res |= UINT64_C(0xffffc00000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe47At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffff);

    if (res >> 46) {
        res |= UINT64_C(0xffff800000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe48At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffff);

    if (res >> 47) {
        res |= UINT64_C(0xffff000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe49At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffff);

    if (res >> 48) {
        res |= UINT64_C(0xfffe000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe50At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffff);

    if (res >> 49) {
        res |= UINT64_C(0xfffc000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe51At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffff);

    if (res >> 50) {
        res |= UINT64_C(0xfff8000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe52At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffff);

    if (res >> 51) {
        res |= UINT64_C(0xfff0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe53At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffff);

    if (res >> 52) {
        res |= UINT64_C(0xffe0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe54At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffff);

    if (res >> 53) {
        res |= UINT64_C(0xffc0000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe55At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffff);

    if (res >> 54) {
        res |= UINT64_C(0xff80000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe56At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xffffffffffffff);

    if (res >> 55) {
        res |= UINT64_C(0xff00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe57At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1ffffffffffffff);

    if (res >> 56) {
        res |= UINT64_C(0xfe00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe58At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3ffffffffffffff);

    if (res >> 57) {
        res |= UINT64_C(0xfc00000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe59At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7ffffffffffffff);

    if (res >> 58) {
        res |= UINT64_C(0xf800000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe60At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0xfffffffffffffff);

    if (res >> 59) {
        res |= UINT64_C(0xf000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe61At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x1fffffffffffffff);

    if (res >> 60) {
        res |= UINT64_C(0xe000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe62At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x3fffffffffffffff);

    if (res >> 61) {
        res |= UINT64_C(0xc000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At0(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At1(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At2(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At3(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At4(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At5(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At6(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe63At7(const std::uint8_t * const buf) {
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
    res &= UINT64_C(0x7fffffffffffffff);

    if (res >> 62) {
        res |= UINT64_C(0x8000000000000000);
    }

    return static_cast<std::int64_t>(res);
}

static std::int64_t readSIntLe64At0(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe64At1(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe64At2(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe64At3(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe64At4(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe64At5(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe64At6(const std::uint8_t * const buf) {
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

static std::int64_t readSIntLe64At7(const std::uint8_t * const buf) {
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

static std::uint64_t (*readUIntBeFuncs[])(const std::uint8_t *) = {
    readUIntBe1At0,
    readUIntBe1At1,
    readUIntBe1At2,
    readUIntBe1At3,
    readUIntBe1At4,
    readUIntBe1At5,
    readUIntBe1At6,
    readUIntBe1At7,
    readUIntBe2At0,
    readUIntBe2At1,
    readUIntBe2At2,
    readUIntBe2At3,
    readUIntBe2At4,
    readUIntBe2At5,
    readUIntBe2At6,
    readUIntBe2At7,
    readUIntBe3At0,
    readUIntBe3At1,
    readUIntBe3At2,
    readUIntBe3At3,
    readUIntBe3At4,
    readUIntBe3At5,
    readUIntBe3At6,
    readUIntBe3At7,
    readUIntBe4At0,
    readUIntBe4At1,
    readUIntBe4At2,
    readUIntBe4At3,
    readUIntBe4At4,
    readUIntBe4At5,
    readUIntBe4At6,
    readUIntBe4At7,
    readUIntBe5At0,
    readUIntBe5At1,
    readUIntBe5At2,
    readUIntBe5At3,
    readUIntBe5At4,
    readUIntBe5At5,
    readUIntBe5At6,
    readUIntBe5At7,
    readUIntBe6At0,
    readUIntBe6At1,
    readUIntBe6At2,
    readUIntBe6At3,
    readUIntBe6At4,
    readUIntBe6At5,
    readUIntBe6At6,
    readUIntBe6At7,
    readUIntBe7At0,
    readUIntBe7At1,
    readUIntBe7At2,
    readUIntBe7At3,
    readUIntBe7At4,
    readUIntBe7At5,
    readUIntBe7At6,
    readUIntBe7At7,
    readUIntBe8At0,
    readUIntBe8At1,
    readUIntBe8At2,
    readUIntBe8At3,
    readUIntBe8At4,
    readUIntBe8At5,
    readUIntBe8At6,
    readUIntBe8At7,
    readUIntBe9At0,
    readUIntBe9At1,
    readUIntBe9At2,
    readUIntBe9At3,
    readUIntBe9At4,
    readUIntBe9At5,
    readUIntBe9At6,
    readUIntBe9At7,
    readUIntBe10At0,
    readUIntBe10At1,
    readUIntBe10At2,
    readUIntBe10At3,
    readUIntBe10At4,
    readUIntBe10At5,
    readUIntBe10At6,
    readUIntBe10At7,
    readUIntBe11At0,
    readUIntBe11At1,
    readUIntBe11At2,
    readUIntBe11At3,
    readUIntBe11At4,
    readUIntBe11At5,
    readUIntBe11At6,
    readUIntBe11At7,
    readUIntBe12At0,
    readUIntBe12At1,
    readUIntBe12At2,
    readUIntBe12At3,
    readUIntBe12At4,
    readUIntBe12At5,
    readUIntBe12At6,
    readUIntBe12At7,
    readUIntBe13At0,
    readUIntBe13At1,
    readUIntBe13At2,
    readUIntBe13At3,
    readUIntBe13At4,
    readUIntBe13At5,
    readUIntBe13At6,
    readUIntBe13At7,
    readUIntBe14At0,
    readUIntBe14At1,
    readUIntBe14At2,
    readUIntBe14At3,
    readUIntBe14At4,
    readUIntBe14At5,
    readUIntBe14At6,
    readUIntBe14At7,
    readUIntBe15At0,
    readUIntBe15At1,
    readUIntBe15At2,
    readUIntBe15At3,
    readUIntBe15At4,
    readUIntBe15At5,
    readUIntBe15At6,
    readUIntBe15At7,
    readUIntBe16At0,
    readUIntBe16At1,
    readUIntBe16At2,
    readUIntBe16At3,
    readUIntBe16At4,
    readUIntBe16At5,
    readUIntBe16At6,
    readUIntBe16At7,
    readUIntBe17At0,
    readUIntBe17At1,
    readUIntBe17At2,
    readUIntBe17At3,
    readUIntBe17At4,
    readUIntBe17At5,
    readUIntBe17At6,
    readUIntBe17At7,
    readUIntBe18At0,
    readUIntBe18At1,
    readUIntBe18At2,
    readUIntBe18At3,
    readUIntBe18At4,
    readUIntBe18At5,
    readUIntBe18At6,
    readUIntBe18At7,
    readUIntBe19At0,
    readUIntBe19At1,
    readUIntBe19At2,
    readUIntBe19At3,
    readUIntBe19At4,
    readUIntBe19At5,
    readUIntBe19At6,
    readUIntBe19At7,
    readUIntBe20At0,
    readUIntBe20At1,
    readUIntBe20At2,
    readUIntBe20At3,
    readUIntBe20At4,
    readUIntBe20At5,
    readUIntBe20At6,
    readUIntBe20At7,
    readUIntBe21At0,
    readUIntBe21At1,
    readUIntBe21At2,
    readUIntBe21At3,
    readUIntBe21At4,
    readUIntBe21At5,
    readUIntBe21At6,
    readUIntBe21At7,
    readUIntBe22At0,
    readUIntBe22At1,
    readUIntBe22At2,
    readUIntBe22At3,
    readUIntBe22At4,
    readUIntBe22At5,
    readUIntBe22At6,
    readUIntBe22At7,
    readUIntBe23At0,
    readUIntBe23At1,
    readUIntBe23At2,
    readUIntBe23At3,
    readUIntBe23At4,
    readUIntBe23At5,
    readUIntBe23At6,
    readUIntBe23At7,
    readUIntBe24At0,
    readUIntBe24At1,
    readUIntBe24At2,
    readUIntBe24At3,
    readUIntBe24At4,
    readUIntBe24At5,
    readUIntBe24At6,
    readUIntBe24At7,
    readUIntBe25At0,
    readUIntBe25At1,
    readUIntBe25At2,
    readUIntBe25At3,
    readUIntBe25At4,
    readUIntBe25At5,
    readUIntBe25At6,
    readUIntBe25At7,
    readUIntBe26At0,
    readUIntBe26At1,
    readUIntBe26At2,
    readUIntBe26At3,
    readUIntBe26At4,
    readUIntBe26At5,
    readUIntBe26At6,
    readUIntBe26At7,
    readUIntBe27At0,
    readUIntBe27At1,
    readUIntBe27At2,
    readUIntBe27At3,
    readUIntBe27At4,
    readUIntBe27At5,
    readUIntBe27At6,
    readUIntBe27At7,
    readUIntBe28At0,
    readUIntBe28At1,
    readUIntBe28At2,
    readUIntBe28At3,
    readUIntBe28At4,
    readUIntBe28At5,
    readUIntBe28At6,
    readUIntBe28At7,
    readUIntBe29At0,
    readUIntBe29At1,
    readUIntBe29At2,
    readUIntBe29At3,
    readUIntBe29At4,
    readUIntBe29At5,
    readUIntBe29At6,
    readUIntBe29At7,
    readUIntBe30At0,
    readUIntBe30At1,
    readUIntBe30At2,
    readUIntBe30At3,
    readUIntBe30At4,
    readUIntBe30At5,
    readUIntBe30At6,
    readUIntBe30At7,
    readUIntBe31At0,
    readUIntBe31At1,
    readUIntBe31At2,
    readUIntBe31At3,
    readUIntBe31At4,
    readUIntBe31At5,
    readUIntBe31At6,
    readUIntBe31At7,
    readUIntBe32At0,
    readUIntBe32At1,
    readUIntBe32At2,
    readUIntBe32At3,
    readUIntBe32At4,
    readUIntBe32At5,
    readUIntBe32At6,
    readUIntBe32At7,
    readUIntBe33At0,
    readUIntBe33At1,
    readUIntBe33At2,
    readUIntBe33At3,
    readUIntBe33At4,
    readUIntBe33At5,
    readUIntBe33At6,
    readUIntBe33At7,
    readUIntBe34At0,
    readUIntBe34At1,
    readUIntBe34At2,
    readUIntBe34At3,
    readUIntBe34At4,
    readUIntBe34At5,
    readUIntBe34At6,
    readUIntBe34At7,
    readUIntBe35At0,
    readUIntBe35At1,
    readUIntBe35At2,
    readUIntBe35At3,
    readUIntBe35At4,
    readUIntBe35At5,
    readUIntBe35At6,
    readUIntBe35At7,
    readUIntBe36At0,
    readUIntBe36At1,
    readUIntBe36At2,
    readUIntBe36At3,
    readUIntBe36At4,
    readUIntBe36At5,
    readUIntBe36At6,
    readUIntBe36At7,
    readUIntBe37At0,
    readUIntBe37At1,
    readUIntBe37At2,
    readUIntBe37At3,
    readUIntBe37At4,
    readUIntBe37At5,
    readUIntBe37At6,
    readUIntBe37At7,
    readUIntBe38At0,
    readUIntBe38At1,
    readUIntBe38At2,
    readUIntBe38At3,
    readUIntBe38At4,
    readUIntBe38At5,
    readUIntBe38At6,
    readUIntBe38At7,
    readUIntBe39At0,
    readUIntBe39At1,
    readUIntBe39At2,
    readUIntBe39At3,
    readUIntBe39At4,
    readUIntBe39At5,
    readUIntBe39At6,
    readUIntBe39At7,
    readUIntBe40At0,
    readUIntBe40At1,
    readUIntBe40At2,
    readUIntBe40At3,
    readUIntBe40At4,
    readUIntBe40At5,
    readUIntBe40At6,
    readUIntBe40At7,
    readUIntBe41At0,
    readUIntBe41At1,
    readUIntBe41At2,
    readUIntBe41At3,
    readUIntBe41At4,
    readUIntBe41At5,
    readUIntBe41At6,
    readUIntBe41At7,
    readUIntBe42At0,
    readUIntBe42At1,
    readUIntBe42At2,
    readUIntBe42At3,
    readUIntBe42At4,
    readUIntBe42At5,
    readUIntBe42At6,
    readUIntBe42At7,
    readUIntBe43At0,
    readUIntBe43At1,
    readUIntBe43At2,
    readUIntBe43At3,
    readUIntBe43At4,
    readUIntBe43At5,
    readUIntBe43At6,
    readUIntBe43At7,
    readUIntBe44At0,
    readUIntBe44At1,
    readUIntBe44At2,
    readUIntBe44At3,
    readUIntBe44At4,
    readUIntBe44At5,
    readUIntBe44At6,
    readUIntBe44At7,
    readUIntBe45At0,
    readUIntBe45At1,
    readUIntBe45At2,
    readUIntBe45At3,
    readUIntBe45At4,
    readUIntBe45At5,
    readUIntBe45At6,
    readUIntBe45At7,
    readUIntBe46At0,
    readUIntBe46At1,
    readUIntBe46At2,
    readUIntBe46At3,
    readUIntBe46At4,
    readUIntBe46At5,
    readUIntBe46At6,
    readUIntBe46At7,
    readUIntBe47At0,
    readUIntBe47At1,
    readUIntBe47At2,
    readUIntBe47At3,
    readUIntBe47At4,
    readUIntBe47At5,
    readUIntBe47At6,
    readUIntBe47At7,
    readUIntBe48At0,
    readUIntBe48At1,
    readUIntBe48At2,
    readUIntBe48At3,
    readUIntBe48At4,
    readUIntBe48At5,
    readUIntBe48At6,
    readUIntBe48At7,
    readUIntBe49At0,
    readUIntBe49At1,
    readUIntBe49At2,
    readUIntBe49At3,
    readUIntBe49At4,
    readUIntBe49At5,
    readUIntBe49At6,
    readUIntBe49At7,
    readUIntBe50At0,
    readUIntBe50At1,
    readUIntBe50At2,
    readUIntBe50At3,
    readUIntBe50At4,
    readUIntBe50At5,
    readUIntBe50At6,
    readUIntBe50At7,
    readUIntBe51At0,
    readUIntBe51At1,
    readUIntBe51At2,
    readUIntBe51At3,
    readUIntBe51At4,
    readUIntBe51At5,
    readUIntBe51At6,
    readUIntBe51At7,
    readUIntBe52At0,
    readUIntBe52At1,
    readUIntBe52At2,
    readUIntBe52At3,
    readUIntBe52At4,
    readUIntBe52At5,
    readUIntBe52At6,
    readUIntBe52At7,
    readUIntBe53At0,
    readUIntBe53At1,
    readUIntBe53At2,
    readUIntBe53At3,
    readUIntBe53At4,
    readUIntBe53At5,
    readUIntBe53At6,
    readUIntBe53At7,
    readUIntBe54At0,
    readUIntBe54At1,
    readUIntBe54At2,
    readUIntBe54At3,
    readUIntBe54At4,
    readUIntBe54At5,
    readUIntBe54At6,
    readUIntBe54At7,
    readUIntBe55At0,
    readUIntBe55At1,
    readUIntBe55At2,
    readUIntBe55At3,
    readUIntBe55At4,
    readUIntBe55At5,
    readUIntBe55At6,
    readUIntBe55At7,
    readUIntBe56At0,
    readUIntBe56At1,
    readUIntBe56At2,
    readUIntBe56At3,
    readUIntBe56At4,
    readUIntBe56At5,
    readUIntBe56At6,
    readUIntBe56At7,
    readUIntBe57At0,
    readUIntBe57At1,
    readUIntBe57At2,
    readUIntBe57At3,
    readUIntBe57At4,
    readUIntBe57At5,
    readUIntBe57At6,
    readUIntBe57At7,
    readUIntBe58At0,
    readUIntBe58At1,
    readUIntBe58At2,
    readUIntBe58At3,
    readUIntBe58At4,
    readUIntBe58At5,
    readUIntBe58At6,
    readUIntBe58At7,
    readUIntBe59At0,
    readUIntBe59At1,
    readUIntBe59At2,
    readUIntBe59At3,
    readUIntBe59At4,
    readUIntBe59At5,
    readUIntBe59At6,
    readUIntBe59At7,
    readUIntBe60At0,
    readUIntBe60At1,
    readUIntBe60At2,
    readUIntBe60At3,
    readUIntBe60At4,
    readUIntBe60At5,
    readUIntBe60At6,
    readUIntBe60At7,
    readUIntBe61At0,
    readUIntBe61At1,
    readUIntBe61At2,
    readUIntBe61At3,
    readUIntBe61At4,
    readUIntBe61At5,
    readUIntBe61At6,
    readUIntBe61At7,
    readUIntBe62At0,
    readUIntBe62At1,
    readUIntBe62At2,
    readUIntBe62At3,
    readUIntBe62At4,
    readUIntBe62At5,
    readUIntBe62At6,
    readUIntBe62At7,
    readUIntBe63At0,
    readUIntBe63At1,
    readUIntBe63At2,
    readUIntBe63At3,
    readUIntBe63At4,
    readUIntBe63At5,
    readUIntBe63At6,
    readUIntBe63At7,
    readUIntBe64At0,
    readUIntBe64At1,
    readUIntBe64At2,
    readUIntBe64At3,
    readUIntBe64At4,
    readUIntBe64At5,
    readUIntBe64At6,
    readUIntBe64At7,
};

static std::int64_t (*readSIntBeFuncs[])(const std::uint8_t *) = {
    readSIntBe1At0,
    readSIntBe1At1,
    readSIntBe1At2,
    readSIntBe1At3,
    readSIntBe1At4,
    readSIntBe1At5,
    readSIntBe1At6,
    readSIntBe1At7,
    readSIntBe2At0,
    readSIntBe2At1,
    readSIntBe2At2,
    readSIntBe2At3,
    readSIntBe2At4,
    readSIntBe2At5,
    readSIntBe2At6,
    readSIntBe2At7,
    readSIntBe3At0,
    readSIntBe3At1,
    readSIntBe3At2,
    readSIntBe3At3,
    readSIntBe3At4,
    readSIntBe3At5,
    readSIntBe3At6,
    readSIntBe3At7,
    readSIntBe4At0,
    readSIntBe4At1,
    readSIntBe4At2,
    readSIntBe4At3,
    readSIntBe4At4,
    readSIntBe4At5,
    readSIntBe4At6,
    readSIntBe4At7,
    readSIntBe5At0,
    readSIntBe5At1,
    readSIntBe5At2,
    readSIntBe5At3,
    readSIntBe5At4,
    readSIntBe5At5,
    readSIntBe5At6,
    readSIntBe5At7,
    readSIntBe6At0,
    readSIntBe6At1,
    readSIntBe6At2,
    readSIntBe6At3,
    readSIntBe6At4,
    readSIntBe6At5,
    readSIntBe6At6,
    readSIntBe6At7,
    readSIntBe7At0,
    readSIntBe7At1,
    readSIntBe7At2,
    readSIntBe7At3,
    readSIntBe7At4,
    readSIntBe7At5,
    readSIntBe7At6,
    readSIntBe7At7,
    readSIntBe8At0,
    readSIntBe8At1,
    readSIntBe8At2,
    readSIntBe8At3,
    readSIntBe8At4,
    readSIntBe8At5,
    readSIntBe8At6,
    readSIntBe8At7,
    readSIntBe9At0,
    readSIntBe9At1,
    readSIntBe9At2,
    readSIntBe9At3,
    readSIntBe9At4,
    readSIntBe9At5,
    readSIntBe9At6,
    readSIntBe9At7,
    readSIntBe10At0,
    readSIntBe10At1,
    readSIntBe10At2,
    readSIntBe10At3,
    readSIntBe10At4,
    readSIntBe10At5,
    readSIntBe10At6,
    readSIntBe10At7,
    readSIntBe11At0,
    readSIntBe11At1,
    readSIntBe11At2,
    readSIntBe11At3,
    readSIntBe11At4,
    readSIntBe11At5,
    readSIntBe11At6,
    readSIntBe11At7,
    readSIntBe12At0,
    readSIntBe12At1,
    readSIntBe12At2,
    readSIntBe12At3,
    readSIntBe12At4,
    readSIntBe12At5,
    readSIntBe12At6,
    readSIntBe12At7,
    readSIntBe13At0,
    readSIntBe13At1,
    readSIntBe13At2,
    readSIntBe13At3,
    readSIntBe13At4,
    readSIntBe13At5,
    readSIntBe13At6,
    readSIntBe13At7,
    readSIntBe14At0,
    readSIntBe14At1,
    readSIntBe14At2,
    readSIntBe14At3,
    readSIntBe14At4,
    readSIntBe14At5,
    readSIntBe14At6,
    readSIntBe14At7,
    readSIntBe15At0,
    readSIntBe15At1,
    readSIntBe15At2,
    readSIntBe15At3,
    readSIntBe15At4,
    readSIntBe15At5,
    readSIntBe15At6,
    readSIntBe15At7,
    readSIntBe16At0,
    readSIntBe16At1,
    readSIntBe16At2,
    readSIntBe16At3,
    readSIntBe16At4,
    readSIntBe16At5,
    readSIntBe16At6,
    readSIntBe16At7,
    readSIntBe17At0,
    readSIntBe17At1,
    readSIntBe17At2,
    readSIntBe17At3,
    readSIntBe17At4,
    readSIntBe17At5,
    readSIntBe17At6,
    readSIntBe17At7,
    readSIntBe18At0,
    readSIntBe18At1,
    readSIntBe18At2,
    readSIntBe18At3,
    readSIntBe18At4,
    readSIntBe18At5,
    readSIntBe18At6,
    readSIntBe18At7,
    readSIntBe19At0,
    readSIntBe19At1,
    readSIntBe19At2,
    readSIntBe19At3,
    readSIntBe19At4,
    readSIntBe19At5,
    readSIntBe19At6,
    readSIntBe19At7,
    readSIntBe20At0,
    readSIntBe20At1,
    readSIntBe20At2,
    readSIntBe20At3,
    readSIntBe20At4,
    readSIntBe20At5,
    readSIntBe20At6,
    readSIntBe20At7,
    readSIntBe21At0,
    readSIntBe21At1,
    readSIntBe21At2,
    readSIntBe21At3,
    readSIntBe21At4,
    readSIntBe21At5,
    readSIntBe21At6,
    readSIntBe21At7,
    readSIntBe22At0,
    readSIntBe22At1,
    readSIntBe22At2,
    readSIntBe22At3,
    readSIntBe22At4,
    readSIntBe22At5,
    readSIntBe22At6,
    readSIntBe22At7,
    readSIntBe23At0,
    readSIntBe23At1,
    readSIntBe23At2,
    readSIntBe23At3,
    readSIntBe23At4,
    readSIntBe23At5,
    readSIntBe23At6,
    readSIntBe23At7,
    readSIntBe24At0,
    readSIntBe24At1,
    readSIntBe24At2,
    readSIntBe24At3,
    readSIntBe24At4,
    readSIntBe24At5,
    readSIntBe24At6,
    readSIntBe24At7,
    readSIntBe25At0,
    readSIntBe25At1,
    readSIntBe25At2,
    readSIntBe25At3,
    readSIntBe25At4,
    readSIntBe25At5,
    readSIntBe25At6,
    readSIntBe25At7,
    readSIntBe26At0,
    readSIntBe26At1,
    readSIntBe26At2,
    readSIntBe26At3,
    readSIntBe26At4,
    readSIntBe26At5,
    readSIntBe26At6,
    readSIntBe26At7,
    readSIntBe27At0,
    readSIntBe27At1,
    readSIntBe27At2,
    readSIntBe27At3,
    readSIntBe27At4,
    readSIntBe27At5,
    readSIntBe27At6,
    readSIntBe27At7,
    readSIntBe28At0,
    readSIntBe28At1,
    readSIntBe28At2,
    readSIntBe28At3,
    readSIntBe28At4,
    readSIntBe28At5,
    readSIntBe28At6,
    readSIntBe28At7,
    readSIntBe29At0,
    readSIntBe29At1,
    readSIntBe29At2,
    readSIntBe29At3,
    readSIntBe29At4,
    readSIntBe29At5,
    readSIntBe29At6,
    readSIntBe29At7,
    readSIntBe30At0,
    readSIntBe30At1,
    readSIntBe30At2,
    readSIntBe30At3,
    readSIntBe30At4,
    readSIntBe30At5,
    readSIntBe30At6,
    readSIntBe30At7,
    readSIntBe31At0,
    readSIntBe31At1,
    readSIntBe31At2,
    readSIntBe31At3,
    readSIntBe31At4,
    readSIntBe31At5,
    readSIntBe31At6,
    readSIntBe31At7,
    readSIntBe32At0,
    readSIntBe32At1,
    readSIntBe32At2,
    readSIntBe32At3,
    readSIntBe32At4,
    readSIntBe32At5,
    readSIntBe32At6,
    readSIntBe32At7,
    readSIntBe33At0,
    readSIntBe33At1,
    readSIntBe33At2,
    readSIntBe33At3,
    readSIntBe33At4,
    readSIntBe33At5,
    readSIntBe33At6,
    readSIntBe33At7,
    readSIntBe34At0,
    readSIntBe34At1,
    readSIntBe34At2,
    readSIntBe34At3,
    readSIntBe34At4,
    readSIntBe34At5,
    readSIntBe34At6,
    readSIntBe34At7,
    readSIntBe35At0,
    readSIntBe35At1,
    readSIntBe35At2,
    readSIntBe35At3,
    readSIntBe35At4,
    readSIntBe35At5,
    readSIntBe35At6,
    readSIntBe35At7,
    readSIntBe36At0,
    readSIntBe36At1,
    readSIntBe36At2,
    readSIntBe36At3,
    readSIntBe36At4,
    readSIntBe36At5,
    readSIntBe36At6,
    readSIntBe36At7,
    readSIntBe37At0,
    readSIntBe37At1,
    readSIntBe37At2,
    readSIntBe37At3,
    readSIntBe37At4,
    readSIntBe37At5,
    readSIntBe37At6,
    readSIntBe37At7,
    readSIntBe38At0,
    readSIntBe38At1,
    readSIntBe38At2,
    readSIntBe38At3,
    readSIntBe38At4,
    readSIntBe38At5,
    readSIntBe38At6,
    readSIntBe38At7,
    readSIntBe39At0,
    readSIntBe39At1,
    readSIntBe39At2,
    readSIntBe39At3,
    readSIntBe39At4,
    readSIntBe39At5,
    readSIntBe39At6,
    readSIntBe39At7,
    readSIntBe40At0,
    readSIntBe40At1,
    readSIntBe40At2,
    readSIntBe40At3,
    readSIntBe40At4,
    readSIntBe40At5,
    readSIntBe40At6,
    readSIntBe40At7,
    readSIntBe41At0,
    readSIntBe41At1,
    readSIntBe41At2,
    readSIntBe41At3,
    readSIntBe41At4,
    readSIntBe41At5,
    readSIntBe41At6,
    readSIntBe41At7,
    readSIntBe42At0,
    readSIntBe42At1,
    readSIntBe42At2,
    readSIntBe42At3,
    readSIntBe42At4,
    readSIntBe42At5,
    readSIntBe42At6,
    readSIntBe42At7,
    readSIntBe43At0,
    readSIntBe43At1,
    readSIntBe43At2,
    readSIntBe43At3,
    readSIntBe43At4,
    readSIntBe43At5,
    readSIntBe43At6,
    readSIntBe43At7,
    readSIntBe44At0,
    readSIntBe44At1,
    readSIntBe44At2,
    readSIntBe44At3,
    readSIntBe44At4,
    readSIntBe44At5,
    readSIntBe44At6,
    readSIntBe44At7,
    readSIntBe45At0,
    readSIntBe45At1,
    readSIntBe45At2,
    readSIntBe45At3,
    readSIntBe45At4,
    readSIntBe45At5,
    readSIntBe45At6,
    readSIntBe45At7,
    readSIntBe46At0,
    readSIntBe46At1,
    readSIntBe46At2,
    readSIntBe46At3,
    readSIntBe46At4,
    readSIntBe46At5,
    readSIntBe46At6,
    readSIntBe46At7,
    readSIntBe47At0,
    readSIntBe47At1,
    readSIntBe47At2,
    readSIntBe47At3,
    readSIntBe47At4,
    readSIntBe47At5,
    readSIntBe47At6,
    readSIntBe47At7,
    readSIntBe48At0,
    readSIntBe48At1,
    readSIntBe48At2,
    readSIntBe48At3,
    readSIntBe48At4,
    readSIntBe48At5,
    readSIntBe48At6,
    readSIntBe48At7,
    readSIntBe49At0,
    readSIntBe49At1,
    readSIntBe49At2,
    readSIntBe49At3,
    readSIntBe49At4,
    readSIntBe49At5,
    readSIntBe49At6,
    readSIntBe49At7,
    readSIntBe50At0,
    readSIntBe50At1,
    readSIntBe50At2,
    readSIntBe50At3,
    readSIntBe50At4,
    readSIntBe50At5,
    readSIntBe50At6,
    readSIntBe50At7,
    readSIntBe51At0,
    readSIntBe51At1,
    readSIntBe51At2,
    readSIntBe51At3,
    readSIntBe51At4,
    readSIntBe51At5,
    readSIntBe51At6,
    readSIntBe51At7,
    readSIntBe52At0,
    readSIntBe52At1,
    readSIntBe52At2,
    readSIntBe52At3,
    readSIntBe52At4,
    readSIntBe52At5,
    readSIntBe52At6,
    readSIntBe52At7,
    readSIntBe53At0,
    readSIntBe53At1,
    readSIntBe53At2,
    readSIntBe53At3,
    readSIntBe53At4,
    readSIntBe53At5,
    readSIntBe53At6,
    readSIntBe53At7,
    readSIntBe54At0,
    readSIntBe54At1,
    readSIntBe54At2,
    readSIntBe54At3,
    readSIntBe54At4,
    readSIntBe54At5,
    readSIntBe54At6,
    readSIntBe54At7,
    readSIntBe55At0,
    readSIntBe55At1,
    readSIntBe55At2,
    readSIntBe55At3,
    readSIntBe55At4,
    readSIntBe55At5,
    readSIntBe55At6,
    readSIntBe55At7,
    readSIntBe56At0,
    readSIntBe56At1,
    readSIntBe56At2,
    readSIntBe56At3,
    readSIntBe56At4,
    readSIntBe56At5,
    readSIntBe56At6,
    readSIntBe56At7,
    readSIntBe57At0,
    readSIntBe57At1,
    readSIntBe57At2,
    readSIntBe57At3,
    readSIntBe57At4,
    readSIntBe57At5,
    readSIntBe57At6,
    readSIntBe57At7,
    readSIntBe58At0,
    readSIntBe58At1,
    readSIntBe58At2,
    readSIntBe58At3,
    readSIntBe58At4,
    readSIntBe58At5,
    readSIntBe58At6,
    readSIntBe58At7,
    readSIntBe59At0,
    readSIntBe59At1,
    readSIntBe59At2,
    readSIntBe59At3,
    readSIntBe59At4,
    readSIntBe59At5,
    readSIntBe59At6,
    readSIntBe59At7,
    readSIntBe60At0,
    readSIntBe60At1,
    readSIntBe60At2,
    readSIntBe60At3,
    readSIntBe60At4,
    readSIntBe60At5,
    readSIntBe60At6,
    readSIntBe60At7,
    readSIntBe61At0,
    readSIntBe61At1,
    readSIntBe61At2,
    readSIntBe61At3,
    readSIntBe61At4,
    readSIntBe61At5,
    readSIntBe61At6,
    readSIntBe61At7,
    readSIntBe62At0,
    readSIntBe62At1,
    readSIntBe62At2,
    readSIntBe62At3,
    readSIntBe62At4,
    readSIntBe62At5,
    readSIntBe62At6,
    readSIntBe62At7,
    readSIntBe63At0,
    readSIntBe63At1,
    readSIntBe63At2,
    readSIntBe63At3,
    readSIntBe63At4,
    readSIntBe63At5,
    readSIntBe63At6,
    readSIntBe63At7,
    readSIntBe64At0,
    readSIntBe64At1,
    readSIntBe64At2,
    readSIntBe64At3,
    readSIntBe64At4,
    readSIntBe64At5,
    readSIntBe64At6,
    readSIntBe64At7,
};

static std::uint64_t (*readUIntLeFuncs[])(const std::uint8_t *) = {
    readUIntLe1At0,
    readUIntLe1At1,
    readUIntLe1At2,
    readUIntLe1At3,
    readUIntLe1At4,
    readUIntLe1At5,
    readUIntLe1At6,
    readUIntLe1At7,
    readUIntLe2At0,
    readUIntLe2At1,
    readUIntLe2At2,
    readUIntLe2At3,
    readUIntLe2At4,
    readUIntLe2At5,
    readUIntLe2At6,
    readUIntLe2At7,
    readUIntLe3At0,
    readUIntLe3At1,
    readUIntLe3At2,
    readUIntLe3At3,
    readUIntLe3At4,
    readUIntLe3At5,
    readUIntLe3At6,
    readUIntLe3At7,
    readUIntLe4At0,
    readUIntLe4At1,
    readUIntLe4At2,
    readUIntLe4At3,
    readUIntLe4At4,
    readUIntLe4At5,
    readUIntLe4At6,
    readUIntLe4At7,
    readUIntLe5At0,
    readUIntLe5At1,
    readUIntLe5At2,
    readUIntLe5At3,
    readUIntLe5At4,
    readUIntLe5At5,
    readUIntLe5At6,
    readUIntLe5At7,
    readUIntLe6At0,
    readUIntLe6At1,
    readUIntLe6At2,
    readUIntLe6At3,
    readUIntLe6At4,
    readUIntLe6At5,
    readUIntLe6At6,
    readUIntLe6At7,
    readUIntLe7At0,
    readUIntLe7At1,
    readUIntLe7At2,
    readUIntLe7At3,
    readUIntLe7At4,
    readUIntLe7At5,
    readUIntLe7At6,
    readUIntLe7At7,
    readUIntLe8At0,
    readUIntLe8At1,
    readUIntLe8At2,
    readUIntLe8At3,
    readUIntLe8At4,
    readUIntLe8At5,
    readUIntLe8At6,
    readUIntLe8At7,
    readUIntLe9At0,
    readUIntLe9At1,
    readUIntLe9At2,
    readUIntLe9At3,
    readUIntLe9At4,
    readUIntLe9At5,
    readUIntLe9At6,
    readUIntLe9At7,
    readUIntLe10At0,
    readUIntLe10At1,
    readUIntLe10At2,
    readUIntLe10At3,
    readUIntLe10At4,
    readUIntLe10At5,
    readUIntLe10At6,
    readUIntLe10At7,
    readUIntLe11At0,
    readUIntLe11At1,
    readUIntLe11At2,
    readUIntLe11At3,
    readUIntLe11At4,
    readUIntLe11At5,
    readUIntLe11At6,
    readUIntLe11At7,
    readUIntLe12At0,
    readUIntLe12At1,
    readUIntLe12At2,
    readUIntLe12At3,
    readUIntLe12At4,
    readUIntLe12At5,
    readUIntLe12At6,
    readUIntLe12At7,
    readUIntLe13At0,
    readUIntLe13At1,
    readUIntLe13At2,
    readUIntLe13At3,
    readUIntLe13At4,
    readUIntLe13At5,
    readUIntLe13At6,
    readUIntLe13At7,
    readUIntLe14At0,
    readUIntLe14At1,
    readUIntLe14At2,
    readUIntLe14At3,
    readUIntLe14At4,
    readUIntLe14At5,
    readUIntLe14At6,
    readUIntLe14At7,
    readUIntLe15At0,
    readUIntLe15At1,
    readUIntLe15At2,
    readUIntLe15At3,
    readUIntLe15At4,
    readUIntLe15At5,
    readUIntLe15At6,
    readUIntLe15At7,
    readUIntLe16At0,
    readUIntLe16At1,
    readUIntLe16At2,
    readUIntLe16At3,
    readUIntLe16At4,
    readUIntLe16At5,
    readUIntLe16At6,
    readUIntLe16At7,
    readUIntLe17At0,
    readUIntLe17At1,
    readUIntLe17At2,
    readUIntLe17At3,
    readUIntLe17At4,
    readUIntLe17At5,
    readUIntLe17At6,
    readUIntLe17At7,
    readUIntLe18At0,
    readUIntLe18At1,
    readUIntLe18At2,
    readUIntLe18At3,
    readUIntLe18At4,
    readUIntLe18At5,
    readUIntLe18At6,
    readUIntLe18At7,
    readUIntLe19At0,
    readUIntLe19At1,
    readUIntLe19At2,
    readUIntLe19At3,
    readUIntLe19At4,
    readUIntLe19At5,
    readUIntLe19At6,
    readUIntLe19At7,
    readUIntLe20At0,
    readUIntLe20At1,
    readUIntLe20At2,
    readUIntLe20At3,
    readUIntLe20At4,
    readUIntLe20At5,
    readUIntLe20At6,
    readUIntLe20At7,
    readUIntLe21At0,
    readUIntLe21At1,
    readUIntLe21At2,
    readUIntLe21At3,
    readUIntLe21At4,
    readUIntLe21At5,
    readUIntLe21At6,
    readUIntLe21At7,
    readUIntLe22At0,
    readUIntLe22At1,
    readUIntLe22At2,
    readUIntLe22At3,
    readUIntLe22At4,
    readUIntLe22At5,
    readUIntLe22At6,
    readUIntLe22At7,
    readUIntLe23At0,
    readUIntLe23At1,
    readUIntLe23At2,
    readUIntLe23At3,
    readUIntLe23At4,
    readUIntLe23At5,
    readUIntLe23At6,
    readUIntLe23At7,
    readUIntLe24At0,
    readUIntLe24At1,
    readUIntLe24At2,
    readUIntLe24At3,
    readUIntLe24At4,
    readUIntLe24At5,
    readUIntLe24At6,
    readUIntLe24At7,
    readUIntLe25At0,
    readUIntLe25At1,
    readUIntLe25At2,
    readUIntLe25At3,
    readUIntLe25At4,
    readUIntLe25At5,
    readUIntLe25At6,
    readUIntLe25At7,
    readUIntLe26At0,
    readUIntLe26At1,
    readUIntLe26At2,
    readUIntLe26At3,
    readUIntLe26At4,
    readUIntLe26At5,
    readUIntLe26At6,
    readUIntLe26At7,
    readUIntLe27At0,
    readUIntLe27At1,
    readUIntLe27At2,
    readUIntLe27At3,
    readUIntLe27At4,
    readUIntLe27At5,
    readUIntLe27At6,
    readUIntLe27At7,
    readUIntLe28At0,
    readUIntLe28At1,
    readUIntLe28At2,
    readUIntLe28At3,
    readUIntLe28At4,
    readUIntLe28At5,
    readUIntLe28At6,
    readUIntLe28At7,
    readUIntLe29At0,
    readUIntLe29At1,
    readUIntLe29At2,
    readUIntLe29At3,
    readUIntLe29At4,
    readUIntLe29At5,
    readUIntLe29At6,
    readUIntLe29At7,
    readUIntLe30At0,
    readUIntLe30At1,
    readUIntLe30At2,
    readUIntLe30At3,
    readUIntLe30At4,
    readUIntLe30At5,
    readUIntLe30At6,
    readUIntLe30At7,
    readUIntLe31At0,
    readUIntLe31At1,
    readUIntLe31At2,
    readUIntLe31At3,
    readUIntLe31At4,
    readUIntLe31At5,
    readUIntLe31At6,
    readUIntLe31At7,
    readUIntLe32At0,
    readUIntLe32At1,
    readUIntLe32At2,
    readUIntLe32At3,
    readUIntLe32At4,
    readUIntLe32At5,
    readUIntLe32At6,
    readUIntLe32At7,
    readUIntLe33At0,
    readUIntLe33At1,
    readUIntLe33At2,
    readUIntLe33At3,
    readUIntLe33At4,
    readUIntLe33At5,
    readUIntLe33At6,
    readUIntLe33At7,
    readUIntLe34At0,
    readUIntLe34At1,
    readUIntLe34At2,
    readUIntLe34At3,
    readUIntLe34At4,
    readUIntLe34At5,
    readUIntLe34At6,
    readUIntLe34At7,
    readUIntLe35At0,
    readUIntLe35At1,
    readUIntLe35At2,
    readUIntLe35At3,
    readUIntLe35At4,
    readUIntLe35At5,
    readUIntLe35At6,
    readUIntLe35At7,
    readUIntLe36At0,
    readUIntLe36At1,
    readUIntLe36At2,
    readUIntLe36At3,
    readUIntLe36At4,
    readUIntLe36At5,
    readUIntLe36At6,
    readUIntLe36At7,
    readUIntLe37At0,
    readUIntLe37At1,
    readUIntLe37At2,
    readUIntLe37At3,
    readUIntLe37At4,
    readUIntLe37At5,
    readUIntLe37At6,
    readUIntLe37At7,
    readUIntLe38At0,
    readUIntLe38At1,
    readUIntLe38At2,
    readUIntLe38At3,
    readUIntLe38At4,
    readUIntLe38At5,
    readUIntLe38At6,
    readUIntLe38At7,
    readUIntLe39At0,
    readUIntLe39At1,
    readUIntLe39At2,
    readUIntLe39At3,
    readUIntLe39At4,
    readUIntLe39At5,
    readUIntLe39At6,
    readUIntLe39At7,
    readUIntLe40At0,
    readUIntLe40At1,
    readUIntLe40At2,
    readUIntLe40At3,
    readUIntLe40At4,
    readUIntLe40At5,
    readUIntLe40At6,
    readUIntLe40At7,
    readUIntLe41At0,
    readUIntLe41At1,
    readUIntLe41At2,
    readUIntLe41At3,
    readUIntLe41At4,
    readUIntLe41At5,
    readUIntLe41At6,
    readUIntLe41At7,
    readUIntLe42At0,
    readUIntLe42At1,
    readUIntLe42At2,
    readUIntLe42At3,
    readUIntLe42At4,
    readUIntLe42At5,
    readUIntLe42At6,
    readUIntLe42At7,
    readUIntLe43At0,
    readUIntLe43At1,
    readUIntLe43At2,
    readUIntLe43At3,
    readUIntLe43At4,
    readUIntLe43At5,
    readUIntLe43At6,
    readUIntLe43At7,
    readUIntLe44At0,
    readUIntLe44At1,
    readUIntLe44At2,
    readUIntLe44At3,
    readUIntLe44At4,
    readUIntLe44At5,
    readUIntLe44At6,
    readUIntLe44At7,
    readUIntLe45At0,
    readUIntLe45At1,
    readUIntLe45At2,
    readUIntLe45At3,
    readUIntLe45At4,
    readUIntLe45At5,
    readUIntLe45At6,
    readUIntLe45At7,
    readUIntLe46At0,
    readUIntLe46At1,
    readUIntLe46At2,
    readUIntLe46At3,
    readUIntLe46At4,
    readUIntLe46At5,
    readUIntLe46At6,
    readUIntLe46At7,
    readUIntLe47At0,
    readUIntLe47At1,
    readUIntLe47At2,
    readUIntLe47At3,
    readUIntLe47At4,
    readUIntLe47At5,
    readUIntLe47At6,
    readUIntLe47At7,
    readUIntLe48At0,
    readUIntLe48At1,
    readUIntLe48At2,
    readUIntLe48At3,
    readUIntLe48At4,
    readUIntLe48At5,
    readUIntLe48At6,
    readUIntLe48At7,
    readUIntLe49At0,
    readUIntLe49At1,
    readUIntLe49At2,
    readUIntLe49At3,
    readUIntLe49At4,
    readUIntLe49At5,
    readUIntLe49At6,
    readUIntLe49At7,
    readUIntLe50At0,
    readUIntLe50At1,
    readUIntLe50At2,
    readUIntLe50At3,
    readUIntLe50At4,
    readUIntLe50At5,
    readUIntLe50At6,
    readUIntLe50At7,
    readUIntLe51At0,
    readUIntLe51At1,
    readUIntLe51At2,
    readUIntLe51At3,
    readUIntLe51At4,
    readUIntLe51At5,
    readUIntLe51At6,
    readUIntLe51At7,
    readUIntLe52At0,
    readUIntLe52At1,
    readUIntLe52At2,
    readUIntLe52At3,
    readUIntLe52At4,
    readUIntLe52At5,
    readUIntLe52At6,
    readUIntLe52At7,
    readUIntLe53At0,
    readUIntLe53At1,
    readUIntLe53At2,
    readUIntLe53At3,
    readUIntLe53At4,
    readUIntLe53At5,
    readUIntLe53At6,
    readUIntLe53At7,
    readUIntLe54At0,
    readUIntLe54At1,
    readUIntLe54At2,
    readUIntLe54At3,
    readUIntLe54At4,
    readUIntLe54At5,
    readUIntLe54At6,
    readUIntLe54At7,
    readUIntLe55At0,
    readUIntLe55At1,
    readUIntLe55At2,
    readUIntLe55At3,
    readUIntLe55At4,
    readUIntLe55At5,
    readUIntLe55At6,
    readUIntLe55At7,
    readUIntLe56At0,
    readUIntLe56At1,
    readUIntLe56At2,
    readUIntLe56At3,
    readUIntLe56At4,
    readUIntLe56At5,
    readUIntLe56At6,
    readUIntLe56At7,
    readUIntLe57At0,
    readUIntLe57At1,
    readUIntLe57At2,
    readUIntLe57At3,
    readUIntLe57At4,
    readUIntLe57At5,
    readUIntLe57At6,
    readUIntLe57At7,
    readUIntLe58At0,
    readUIntLe58At1,
    readUIntLe58At2,
    readUIntLe58At3,
    readUIntLe58At4,
    readUIntLe58At5,
    readUIntLe58At6,
    readUIntLe58At7,
    readUIntLe59At0,
    readUIntLe59At1,
    readUIntLe59At2,
    readUIntLe59At3,
    readUIntLe59At4,
    readUIntLe59At5,
    readUIntLe59At6,
    readUIntLe59At7,
    readUIntLe60At0,
    readUIntLe60At1,
    readUIntLe60At2,
    readUIntLe60At3,
    readUIntLe60At4,
    readUIntLe60At5,
    readUIntLe60At6,
    readUIntLe60At7,
    readUIntLe61At0,
    readUIntLe61At1,
    readUIntLe61At2,
    readUIntLe61At3,
    readUIntLe61At4,
    readUIntLe61At5,
    readUIntLe61At6,
    readUIntLe61At7,
    readUIntLe62At0,
    readUIntLe62At1,
    readUIntLe62At2,
    readUIntLe62At3,
    readUIntLe62At4,
    readUIntLe62At5,
    readUIntLe62At6,
    readUIntLe62At7,
    readUIntLe63At0,
    readUIntLe63At1,
    readUIntLe63At2,
    readUIntLe63At3,
    readUIntLe63At4,
    readUIntLe63At5,
    readUIntLe63At6,
    readUIntLe63At7,
    readUIntLe64At0,
    readUIntLe64At1,
    readUIntLe64At2,
    readUIntLe64At3,
    readUIntLe64At4,
    readUIntLe64At5,
    readUIntLe64At6,
    readUIntLe64At7,
};

static std::int64_t (*readSIntLeFuncs[])(const std::uint8_t *) = {
    readSIntLe1At0,
    readSIntLe1At1,
    readSIntLe1At2,
    readSIntLe1At3,
    readSIntLe1At4,
    readSIntLe1At5,
    readSIntLe1At6,
    readSIntLe1At7,
    readSIntLe2At0,
    readSIntLe2At1,
    readSIntLe2At2,
    readSIntLe2At3,
    readSIntLe2At4,
    readSIntLe2At5,
    readSIntLe2At6,
    readSIntLe2At7,
    readSIntLe3At0,
    readSIntLe3At1,
    readSIntLe3At2,
    readSIntLe3At3,
    readSIntLe3At4,
    readSIntLe3At5,
    readSIntLe3At6,
    readSIntLe3At7,
    readSIntLe4At0,
    readSIntLe4At1,
    readSIntLe4At2,
    readSIntLe4At3,
    readSIntLe4At4,
    readSIntLe4At5,
    readSIntLe4At6,
    readSIntLe4At7,
    readSIntLe5At0,
    readSIntLe5At1,
    readSIntLe5At2,
    readSIntLe5At3,
    readSIntLe5At4,
    readSIntLe5At5,
    readSIntLe5At6,
    readSIntLe5At7,
    readSIntLe6At0,
    readSIntLe6At1,
    readSIntLe6At2,
    readSIntLe6At3,
    readSIntLe6At4,
    readSIntLe6At5,
    readSIntLe6At6,
    readSIntLe6At7,
    readSIntLe7At0,
    readSIntLe7At1,
    readSIntLe7At2,
    readSIntLe7At3,
    readSIntLe7At4,
    readSIntLe7At5,
    readSIntLe7At6,
    readSIntLe7At7,
    readSIntLe8At0,
    readSIntLe8At1,
    readSIntLe8At2,
    readSIntLe8At3,
    readSIntLe8At4,
    readSIntLe8At5,
    readSIntLe8At6,
    readSIntLe8At7,
    readSIntLe9At0,
    readSIntLe9At1,
    readSIntLe9At2,
    readSIntLe9At3,
    readSIntLe9At4,
    readSIntLe9At5,
    readSIntLe9At6,
    readSIntLe9At7,
    readSIntLe10At0,
    readSIntLe10At1,
    readSIntLe10At2,
    readSIntLe10At3,
    readSIntLe10At4,
    readSIntLe10At5,
    readSIntLe10At6,
    readSIntLe10At7,
    readSIntLe11At0,
    readSIntLe11At1,
    readSIntLe11At2,
    readSIntLe11At3,
    readSIntLe11At4,
    readSIntLe11At5,
    readSIntLe11At6,
    readSIntLe11At7,
    readSIntLe12At0,
    readSIntLe12At1,
    readSIntLe12At2,
    readSIntLe12At3,
    readSIntLe12At4,
    readSIntLe12At5,
    readSIntLe12At6,
    readSIntLe12At7,
    readSIntLe13At0,
    readSIntLe13At1,
    readSIntLe13At2,
    readSIntLe13At3,
    readSIntLe13At4,
    readSIntLe13At5,
    readSIntLe13At6,
    readSIntLe13At7,
    readSIntLe14At0,
    readSIntLe14At1,
    readSIntLe14At2,
    readSIntLe14At3,
    readSIntLe14At4,
    readSIntLe14At5,
    readSIntLe14At6,
    readSIntLe14At7,
    readSIntLe15At0,
    readSIntLe15At1,
    readSIntLe15At2,
    readSIntLe15At3,
    readSIntLe15At4,
    readSIntLe15At5,
    readSIntLe15At6,
    readSIntLe15At7,
    readSIntLe16At0,
    readSIntLe16At1,
    readSIntLe16At2,
    readSIntLe16At3,
    readSIntLe16At4,
    readSIntLe16At5,
    readSIntLe16At6,
    readSIntLe16At7,
    readSIntLe17At0,
    readSIntLe17At1,
    readSIntLe17At2,
    readSIntLe17At3,
    readSIntLe17At4,
    readSIntLe17At5,
    readSIntLe17At6,
    readSIntLe17At7,
    readSIntLe18At0,
    readSIntLe18At1,
    readSIntLe18At2,
    readSIntLe18At3,
    readSIntLe18At4,
    readSIntLe18At5,
    readSIntLe18At6,
    readSIntLe18At7,
    readSIntLe19At0,
    readSIntLe19At1,
    readSIntLe19At2,
    readSIntLe19At3,
    readSIntLe19At4,
    readSIntLe19At5,
    readSIntLe19At6,
    readSIntLe19At7,
    readSIntLe20At0,
    readSIntLe20At1,
    readSIntLe20At2,
    readSIntLe20At3,
    readSIntLe20At4,
    readSIntLe20At5,
    readSIntLe20At6,
    readSIntLe20At7,
    readSIntLe21At0,
    readSIntLe21At1,
    readSIntLe21At2,
    readSIntLe21At3,
    readSIntLe21At4,
    readSIntLe21At5,
    readSIntLe21At6,
    readSIntLe21At7,
    readSIntLe22At0,
    readSIntLe22At1,
    readSIntLe22At2,
    readSIntLe22At3,
    readSIntLe22At4,
    readSIntLe22At5,
    readSIntLe22At6,
    readSIntLe22At7,
    readSIntLe23At0,
    readSIntLe23At1,
    readSIntLe23At2,
    readSIntLe23At3,
    readSIntLe23At4,
    readSIntLe23At5,
    readSIntLe23At6,
    readSIntLe23At7,
    readSIntLe24At0,
    readSIntLe24At1,
    readSIntLe24At2,
    readSIntLe24At3,
    readSIntLe24At4,
    readSIntLe24At5,
    readSIntLe24At6,
    readSIntLe24At7,
    readSIntLe25At0,
    readSIntLe25At1,
    readSIntLe25At2,
    readSIntLe25At3,
    readSIntLe25At4,
    readSIntLe25At5,
    readSIntLe25At6,
    readSIntLe25At7,
    readSIntLe26At0,
    readSIntLe26At1,
    readSIntLe26At2,
    readSIntLe26At3,
    readSIntLe26At4,
    readSIntLe26At5,
    readSIntLe26At6,
    readSIntLe26At7,
    readSIntLe27At0,
    readSIntLe27At1,
    readSIntLe27At2,
    readSIntLe27At3,
    readSIntLe27At4,
    readSIntLe27At5,
    readSIntLe27At6,
    readSIntLe27At7,
    readSIntLe28At0,
    readSIntLe28At1,
    readSIntLe28At2,
    readSIntLe28At3,
    readSIntLe28At4,
    readSIntLe28At5,
    readSIntLe28At6,
    readSIntLe28At7,
    readSIntLe29At0,
    readSIntLe29At1,
    readSIntLe29At2,
    readSIntLe29At3,
    readSIntLe29At4,
    readSIntLe29At5,
    readSIntLe29At6,
    readSIntLe29At7,
    readSIntLe30At0,
    readSIntLe30At1,
    readSIntLe30At2,
    readSIntLe30At3,
    readSIntLe30At4,
    readSIntLe30At5,
    readSIntLe30At6,
    readSIntLe30At7,
    readSIntLe31At0,
    readSIntLe31At1,
    readSIntLe31At2,
    readSIntLe31At3,
    readSIntLe31At4,
    readSIntLe31At5,
    readSIntLe31At6,
    readSIntLe31At7,
    readSIntLe32At0,
    readSIntLe32At1,
    readSIntLe32At2,
    readSIntLe32At3,
    readSIntLe32At4,
    readSIntLe32At5,
    readSIntLe32At6,
    readSIntLe32At7,
    readSIntLe33At0,
    readSIntLe33At1,
    readSIntLe33At2,
    readSIntLe33At3,
    readSIntLe33At4,
    readSIntLe33At5,
    readSIntLe33At6,
    readSIntLe33At7,
    readSIntLe34At0,
    readSIntLe34At1,
    readSIntLe34At2,
    readSIntLe34At3,
    readSIntLe34At4,
    readSIntLe34At5,
    readSIntLe34At6,
    readSIntLe34At7,
    readSIntLe35At0,
    readSIntLe35At1,
    readSIntLe35At2,
    readSIntLe35At3,
    readSIntLe35At4,
    readSIntLe35At5,
    readSIntLe35At6,
    readSIntLe35At7,
    readSIntLe36At0,
    readSIntLe36At1,
    readSIntLe36At2,
    readSIntLe36At3,
    readSIntLe36At4,
    readSIntLe36At5,
    readSIntLe36At6,
    readSIntLe36At7,
    readSIntLe37At0,
    readSIntLe37At1,
    readSIntLe37At2,
    readSIntLe37At3,
    readSIntLe37At4,
    readSIntLe37At5,
    readSIntLe37At6,
    readSIntLe37At7,
    readSIntLe38At0,
    readSIntLe38At1,
    readSIntLe38At2,
    readSIntLe38At3,
    readSIntLe38At4,
    readSIntLe38At5,
    readSIntLe38At6,
    readSIntLe38At7,
    readSIntLe39At0,
    readSIntLe39At1,
    readSIntLe39At2,
    readSIntLe39At3,
    readSIntLe39At4,
    readSIntLe39At5,
    readSIntLe39At6,
    readSIntLe39At7,
    readSIntLe40At0,
    readSIntLe40At1,
    readSIntLe40At2,
    readSIntLe40At3,
    readSIntLe40At4,
    readSIntLe40At5,
    readSIntLe40At6,
    readSIntLe40At7,
    readSIntLe41At0,
    readSIntLe41At1,
    readSIntLe41At2,
    readSIntLe41At3,
    readSIntLe41At4,
    readSIntLe41At5,
    readSIntLe41At6,
    readSIntLe41At7,
    readSIntLe42At0,
    readSIntLe42At1,
    readSIntLe42At2,
    readSIntLe42At3,
    readSIntLe42At4,
    readSIntLe42At5,
    readSIntLe42At6,
    readSIntLe42At7,
    readSIntLe43At0,
    readSIntLe43At1,
    readSIntLe43At2,
    readSIntLe43At3,
    readSIntLe43At4,
    readSIntLe43At5,
    readSIntLe43At6,
    readSIntLe43At7,
    readSIntLe44At0,
    readSIntLe44At1,
    readSIntLe44At2,
    readSIntLe44At3,
    readSIntLe44At4,
    readSIntLe44At5,
    readSIntLe44At6,
    readSIntLe44At7,
    readSIntLe45At0,
    readSIntLe45At1,
    readSIntLe45At2,
    readSIntLe45At3,
    readSIntLe45At4,
    readSIntLe45At5,
    readSIntLe45At6,
    readSIntLe45At7,
    readSIntLe46At0,
    readSIntLe46At1,
    readSIntLe46At2,
    readSIntLe46At3,
    readSIntLe46At4,
    readSIntLe46At5,
    readSIntLe46At6,
    readSIntLe46At7,
    readSIntLe47At0,
    readSIntLe47At1,
    readSIntLe47At2,
    readSIntLe47At3,
    readSIntLe47At4,
    readSIntLe47At5,
    readSIntLe47At6,
    readSIntLe47At7,
    readSIntLe48At0,
    readSIntLe48At1,
    readSIntLe48At2,
    readSIntLe48At3,
    readSIntLe48At4,
    readSIntLe48At5,
    readSIntLe48At6,
    readSIntLe48At7,
    readSIntLe49At0,
    readSIntLe49At1,
    readSIntLe49At2,
    readSIntLe49At3,
    readSIntLe49At4,
    readSIntLe49At5,
    readSIntLe49At6,
    readSIntLe49At7,
    readSIntLe50At0,
    readSIntLe50At1,
    readSIntLe50At2,
    readSIntLe50At3,
    readSIntLe50At4,
    readSIntLe50At5,
    readSIntLe50At6,
    readSIntLe50At7,
    readSIntLe51At0,
    readSIntLe51At1,
    readSIntLe51At2,
    readSIntLe51At3,
    readSIntLe51At4,
    readSIntLe51At5,
    readSIntLe51At6,
    readSIntLe51At7,
    readSIntLe52At0,
    readSIntLe52At1,
    readSIntLe52At2,
    readSIntLe52At3,
    readSIntLe52At4,
    readSIntLe52At5,
    readSIntLe52At6,
    readSIntLe52At7,
    readSIntLe53At0,
    readSIntLe53At1,
    readSIntLe53At2,
    readSIntLe53At3,
    readSIntLe53At4,
    readSIntLe53At5,
    readSIntLe53At6,
    readSIntLe53At7,
    readSIntLe54At0,
    readSIntLe54At1,
    readSIntLe54At2,
    readSIntLe54At3,
    readSIntLe54At4,
    readSIntLe54At5,
    readSIntLe54At6,
    readSIntLe54At7,
    readSIntLe55At0,
    readSIntLe55At1,
    readSIntLe55At2,
    readSIntLe55At3,
    readSIntLe55At4,
    readSIntLe55At5,
    readSIntLe55At6,
    readSIntLe55At7,
    readSIntLe56At0,
    readSIntLe56At1,
    readSIntLe56At2,
    readSIntLe56At3,
    readSIntLe56At4,
    readSIntLe56At5,
    readSIntLe56At6,
    readSIntLe56At7,
    readSIntLe57At0,
    readSIntLe57At1,
    readSIntLe57At2,
    readSIntLe57At3,
    readSIntLe57At4,
    readSIntLe57At5,
    readSIntLe57At6,
    readSIntLe57At7,
    readSIntLe58At0,
    readSIntLe58At1,
    readSIntLe58At2,
    readSIntLe58At3,
    readSIntLe58At4,
    readSIntLe58At5,
    readSIntLe58At6,
    readSIntLe58At7,
    readSIntLe59At0,
    readSIntLe59At1,
    readSIntLe59At2,
    readSIntLe59At3,
    readSIntLe59At4,
    readSIntLe59At5,
    readSIntLe59At6,
    readSIntLe59At7,
    readSIntLe60At0,
    readSIntLe60At1,
    readSIntLe60At2,
    readSIntLe60At3,
    readSIntLe60At4,
    readSIntLe60At5,
    readSIntLe60At6,
    readSIntLe60At7,
    readSIntLe61At0,
    readSIntLe61At1,
    readSIntLe61At2,
    readSIntLe61At3,
    readSIntLe61At4,
    readSIntLe61At5,
    readSIntLe61At6,
    readSIntLe61At7,
    readSIntLe62At0,
    readSIntLe62At1,
    readSIntLe62At2,
    readSIntLe62At3,
    readSIntLe62At4,
    readSIntLe62At5,
    readSIntLe62At6,
    readSIntLe62At7,
    readSIntLe63At0,
    readSIntLe63At1,
    readSIntLe63At2,
    readSIntLe63At3,
    readSIntLe63At4,
    readSIntLe63At5,
    readSIntLe63At6,
    readSIntLe63At7,
    readSIntLe64At0,
    readSIntLe64At1,
    readSIntLe64At2,
    readSIntLe64At3,
    readSIntLe64At4,
    readSIntLe64At5,
    readSIntLe64At6,
    readSIntLe64At7,
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INT_READER_HPP
