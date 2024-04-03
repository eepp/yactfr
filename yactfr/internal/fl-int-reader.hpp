/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_FL_INT_READER_HPP
#define _YACTFR_INTERNAL_FL_INT_READER_HPP

#include <cstdint>
#include <cassert>
#include <cstring>

namespace yactfr {
namespace internal {
namespace {

std::uint64_t readFlUIntBe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntBe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntBe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntBe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntBe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntBe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntBe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntBe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntBe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 1;
    res |= (buf[1] >> 7);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntBe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 2;
    res |= (buf[1] >> 6);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntBe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 3;
    res |= (buf[1] >> 5);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntBe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 4;
    res |= (buf[1] >> 4);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntBe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 5;
    res |= (buf[1] >> 3);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntBe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 6;
    res |= (buf[1] >> 2);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntBe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 7;
    res |= (buf[1] >> 1);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntBe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntBe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[2] >> 7);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntBe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[2] >> 6);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntBe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntBe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntBe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntBe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntBe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntBe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntBe18At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[2] >> 5);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntBe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntBe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntBe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntBe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntBe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntBe19At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe19At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[2] >> 4);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntBe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntBe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntBe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntBe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntBe20At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe20At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe20At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[2] >> 3);
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntBe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntBe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntBe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntBe21At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe21At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe21At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe21At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[2] >> 2);
    res &= UINT64_C(0x3fffff);
    return res;
}

std::uint64_t readFlUIntBe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x3fffff);
    return res;
}

std::uint64_t readFlUIntBe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x3fffff);
    return res;
}

std::uint64_t readFlUIntBe22At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe22At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe22At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe22At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe22At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[2] >> 1);
    res &= UINT64_C(0x7fffff);
    return res;
}

std::uint64_t readFlUIntBe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0x7fffff);
    return res;
}

std::uint64_t readFlUIntBe23At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe23At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe23At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe23At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe23At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe23At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[2];
    res &= UINT64_C(0xffffff);
    return res;
}

std::uint64_t readFlUIntBe24At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe24At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe24At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe24At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe24At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe24At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe24At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe25At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe26At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe27At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe28At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe29At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe30At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe31At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe32At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe34At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe34At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe34At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe34At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe34At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe34At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe35At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe35At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe35At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe35At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe35At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe36At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe36At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe36At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe36At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe37At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe37At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe37At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe38At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe38At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe39At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntBe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::uint64_t readFlUIntBe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntBe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe2At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe3At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe3At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe4At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe4At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe4At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe5At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe5At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe5At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe5At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe6At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe6At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe6At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe6At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe6At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe7At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe7At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe7At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe7At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe7At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe7At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntBe8At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe8At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe8At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe8At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe8At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe8At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe8At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe9At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe10At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe11At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe12At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe13At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe14At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe15At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe16At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe17At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe18At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe19At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe20At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe21At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe22At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe23At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe24At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe25At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe26At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe27At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe28At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe29At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe30At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe31At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe32At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe33At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe34At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe34At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe34At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe34At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe34At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe34At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe34At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe34At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe35At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe35At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe35At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe35At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe35At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe35At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe35At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe35At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe36At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe36At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe36At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe36At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe36At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe36At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe36At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe36At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe37At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe37At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe37At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe37At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe37At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe37At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe37At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe37At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe38At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe38At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe38At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe38At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe38At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe38At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe38At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe38At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe39At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntBe39At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe39At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe39At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe39At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe39At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe39At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe39At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe40At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe41At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe42At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe42At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe42At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe42At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe42At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe42At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe42At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe42At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe43At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe43At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe43At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe43At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe43At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe43At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe43At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe43At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe44At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe44At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe44At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe44At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe44At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe44At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe44At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe44At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe45At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe45At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe45At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe45At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe45At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe45At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe45At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe45At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe46At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe46At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe46At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe46At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe46At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe46At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe46At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe46At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe47At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

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

std::int64_t readFlSIntBe47At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe47At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe47At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe47At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe47At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe47At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe47At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe48At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe49At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe50At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe50At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe50At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe50At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe50At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe50At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe50At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe50At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe51At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe51At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe51At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe51At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe51At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe51At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe51At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe51At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe52At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe52At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe52At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe52At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe52At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe52At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe52At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe52At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe53At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe53At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe53At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe53At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe53At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe53At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe53At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe53At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe54At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe54At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe54At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe54At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe54At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe54At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe54At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe54At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe55At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
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

std::int64_t readFlSIntBe55At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe55At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe55At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe55At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe55At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe55At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe55At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe56At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe57At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe58At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe59At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe60At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe61At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe62At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe63At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::int64_t readFlSIntBe64At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
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

std::uint64_t readFlUIntLe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);
    return res;
}

std::uint64_t readFlUIntLe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe2At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3);
    return res;
}

std::uint64_t readFlUIntLe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe3At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe3At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7);
    return res;
}

std::uint64_t readFlUIntLe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe4At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe4At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe4At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xf);
    return res;
}

std::uint64_t readFlUIntLe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe5At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe5At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe5At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe5At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1f);
    return res;
}

std::uint64_t readFlUIntLe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe6At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe6At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe6At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe6At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe6At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3f);
    return res;
}

std::uint64_t readFlUIntLe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe7At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe7At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe7At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe7At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe7At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe7At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7f);
    return res;
}

std::uint64_t readFlUIntLe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe8At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe8At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe8At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe8At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe8At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe8At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe8At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xff);
    return res;
}

std::uint64_t readFlUIntLe9At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe9At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe9At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe9At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe9At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe9At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe9At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe9At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ff);
    return res;
}

std::uint64_t readFlUIntLe10At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe10At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe10At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe10At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe10At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe10At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe10At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe10At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3ff);
    return res;
}

std::uint64_t readFlUIntLe11At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe11At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe11At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe11At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe11At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe11At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe11At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe11At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7ff);
    return res;
}

std::uint64_t readFlUIntLe12At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe12At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe12At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe12At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe12At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe12At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe12At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe12At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xfff);
    return res;
}

std::uint64_t readFlUIntLe13At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe13At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe13At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe13At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe13At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe13At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe13At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe13At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1fff);
    return res;
}

std::uint64_t readFlUIntLe14At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe14At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe14At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe14At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe14At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe14At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe14At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe14At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x3fff);
    return res;
}

std::uint64_t readFlUIntLe15At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe15At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe15At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe15At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe15At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe15At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe15At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe15At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x7fff);
    return res;
}

std::uint64_t readFlUIntLe16At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe16At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe16At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe16At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe16At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe16At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe16At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe16At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0xffff);
    return res;
}

std::uint64_t readFlUIntLe17At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe17At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe17At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe17At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe17At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe17At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe17At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe17At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 1;
    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1ffff);
    return res;
}

std::uint64_t readFlUIntLe18At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntLe18At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntLe18At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntLe18At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntLe18At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntLe18At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntLe18At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 2;
    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3ffff);
    return res;
}

std::uint64_t readFlUIntLe18At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe19At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntLe19At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntLe19At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntLe19At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntLe19At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntLe19At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 3;
    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7ffff);
    return res;
}

std::uint64_t readFlUIntLe19At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe19At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe20At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntLe20At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntLe20At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntLe20At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntLe20At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 4;
    res |= (buf[0] >> 4);
    res &= UINT64_C(0xfffff);
    return res;
}

std::uint64_t readFlUIntLe20At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe20At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe20At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe21At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntLe21At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntLe21At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntLe21At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 5;
    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1fffff);
    return res;
}

std::uint64_t readFlUIntLe21At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe21At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe21At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe21At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe22At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x3fffff);
    return res;
}

std::uint64_t readFlUIntLe22At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3fffff);
    return res;
}

std::uint64_t readFlUIntLe22At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 6;
    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3fffff);
    return res;
}

std::uint64_t readFlUIntLe22At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe22At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe22At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe22At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe22At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe23At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0x7fffff);
    return res;
}

std::uint64_t readFlUIntLe23At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 7;
    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7fffff);
    return res;
}

std::uint64_t readFlUIntLe23At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe23At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe23At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe23At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe23At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe23At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe24At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[2];
    res <<= 8;
    res |= buf[1];
    res <<= 8;
    res |= buf[0];
    res &= UINT64_C(0xffffff);
    return res;
}

std::uint64_t readFlUIntLe24At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe24At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe24At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe24At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe24At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe24At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe24At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe25At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe26At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe27At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe28At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe29At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe30At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe31At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe32At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe33At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe34At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe35At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe36At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe37At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe38At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe39At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe40At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe41At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe42At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe43At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe44At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe45At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe46At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe47At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe48At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe49At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe50At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe51At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe52At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe53At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe54At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe55At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe56At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe57At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe58At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe59At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe60At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe61At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe62At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe63At7(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At0(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At1(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At2(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At3(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At4(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At5(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At6(const std::uint8_t * const buf) {
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

std::uint64_t readFlUIntLe64At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe1At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe1At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe1At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe1At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe1At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe1At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe1At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe1At7(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 7);
    res &= UINT64_C(0x1);

    if (res >> 0) {
        res |= UINT64_C(0xfffffffffffffffe);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At6(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 6);
    res &= UINT64_C(0x3);

    if (res >> 1) {
        res |= UINT64_C(0xfffffffffffffffc);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe2At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe3At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe3At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe3At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe3At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe3At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe3At5(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 5);
    res &= UINT64_C(0x7);

    if (res >> 2) {
        res |= UINT64_C(0xfffffffffffffff8);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe3At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe3At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe4At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe4At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe4At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe4At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe4At4(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 4);
    res &= UINT64_C(0xf);

    if (res >> 3) {
        res |= UINT64_C(0xfffffffffffffff0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe4At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe4At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe4At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe5At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe5At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe5At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe5At3(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 3);
    res &= UINT64_C(0x1f);

    if (res >> 4) {
        res |= UINT64_C(0xffffffffffffffe0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe5At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe5At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe5At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe5At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe6At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe6At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe6At2(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 2);
    res &= UINT64_C(0x3f);

    if (res >> 5) {
        res |= UINT64_C(0xffffffffffffffc0);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe6At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe6At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe6At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe6At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe6At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe7At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe7At1(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= (buf[0] >> 1);
    res &= UINT64_C(0x7f);

    if (res >> 6) {
        res |= UINT64_C(0xffffffffffffff80);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe7At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe7At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe7At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe7At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe7At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe7At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe8At0(const std::uint8_t * const buf) {
    std::uint64_t res = 0;

    res |= buf[0];
    res &= UINT64_C(0xff);

    if (res >> 7) {
        res |= UINT64_C(0xffffffffffffff00);
    }

    return static_cast<std::int64_t>(res);
}

std::int64_t readFlSIntLe8At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe8At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe8At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe8At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe8At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe8At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe8At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe9At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe10At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe11At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe12At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe13At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe14At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe15At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe16At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe17At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe18At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe19At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe20At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe21At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe22At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe23At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe24At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe25At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe26At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe27At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe28At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe29At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe30At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe31At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe32At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe33At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe34At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe35At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe36At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe37At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe38At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe39At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe40At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe41At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe42At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe43At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe44At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe45At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe46At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe47At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe48At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe49At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe50At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe51At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe52At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe53At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe54At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe55At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe56At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe57At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe58At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe59At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe60At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe61At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe62At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe63At7(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At0(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At1(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At2(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At3(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At4(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At5(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At6(const std::uint8_t * const buf) {
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

std::int64_t readFlSIntLe64At7(const std::uint8_t * const buf) {
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

std::uint64_t (*readFlUIntBeFuncs[])(const std::uint8_t *) = {
    readFlUIntBe1At0,
    readFlUIntBe1At1,
    readFlUIntBe1At2,
    readFlUIntBe1At3,
    readFlUIntBe1At4,
    readFlUIntBe1At5,
    readFlUIntBe1At6,
    readFlUIntBe1At7,
    readFlUIntBe2At0,
    readFlUIntBe2At1,
    readFlUIntBe2At2,
    readFlUIntBe2At3,
    readFlUIntBe2At4,
    readFlUIntBe2At5,
    readFlUIntBe2At6,
    readFlUIntBe2At7,
    readFlUIntBe3At0,
    readFlUIntBe3At1,
    readFlUIntBe3At2,
    readFlUIntBe3At3,
    readFlUIntBe3At4,
    readFlUIntBe3At5,
    readFlUIntBe3At6,
    readFlUIntBe3At7,
    readFlUIntBe4At0,
    readFlUIntBe4At1,
    readFlUIntBe4At2,
    readFlUIntBe4At3,
    readFlUIntBe4At4,
    readFlUIntBe4At5,
    readFlUIntBe4At6,
    readFlUIntBe4At7,
    readFlUIntBe5At0,
    readFlUIntBe5At1,
    readFlUIntBe5At2,
    readFlUIntBe5At3,
    readFlUIntBe5At4,
    readFlUIntBe5At5,
    readFlUIntBe5At6,
    readFlUIntBe5At7,
    readFlUIntBe6At0,
    readFlUIntBe6At1,
    readFlUIntBe6At2,
    readFlUIntBe6At3,
    readFlUIntBe6At4,
    readFlUIntBe6At5,
    readFlUIntBe6At6,
    readFlUIntBe6At7,
    readFlUIntBe7At0,
    readFlUIntBe7At1,
    readFlUIntBe7At2,
    readFlUIntBe7At3,
    readFlUIntBe7At4,
    readFlUIntBe7At5,
    readFlUIntBe7At6,
    readFlUIntBe7At7,
    readFlUIntBe8At0,
    readFlUIntBe8At1,
    readFlUIntBe8At2,
    readFlUIntBe8At3,
    readFlUIntBe8At4,
    readFlUIntBe8At5,
    readFlUIntBe8At6,
    readFlUIntBe8At7,
    readFlUIntBe9At0,
    readFlUIntBe9At1,
    readFlUIntBe9At2,
    readFlUIntBe9At3,
    readFlUIntBe9At4,
    readFlUIntBe9At5,
    readFlUIntBe9At6,
    readFlUIntBe9At7,
    readFlUIntBe10At0,
    readFlUIntBe10At1,
    readFlUIntBe10At2,
    readFlUIntBe10At3,
    readFlUIntBe10At4,
    readFlUIntBe10At5,
    readFlUIntBe10At6,
    readFlUIntBe10At7,
    readFlUIntBe11At0,
    readFlUIntBe11At1,
    readFlUIntBe11At2,
    readFlUIntBe11At3,
    readFlUIntBe11At4,
    readFlUIntBe11At5,
    readFlUIntBe11At6,
    readFlUIntBe11At7,
    readFlUIntBe12At0,
    readFlUIntBe12At1,
    readFlUIntBe12At2,
    readFlUIntBe12At3,
    readFlUIntBe12At4,
    readFlUIntBe12At5,
    readFlUIntBe12At6,
    readFlUIntBe12At7,
    readFlUIntBe13At0,
    readFlUIntBe13At1,
    readFlUIntBe13At2,
    readFlUIntBe13At3,
    readFlUIntBe13At4,
    readFlUIntBe13At5,
    readFlUIntBe13At6,
    readFlUIntBe13At7,
    readFlUIntBe14At0,
    readFlUIntBe14At1,
    readFlUIntBe14At2,
    readFlUIntBe14At3,
    readFlUIntBe14At4,
    readFlUIntBe14At5,
    readFlUIntBe14At6,
    readFlUIntBe14At7,
    readFlUIntBe15At0,
    readFlUIntBe15At1,
    readFlUIntBe15At2,
    readFlUIntBe15At3,
    readFlUIntBe15At4,
    readFlUIntBe15At5,
    readFlUIntBe15At6,
    readFlUIntBe15At7,
    readFlUIntBe16At0,
    readFlUIntBe16At1,
    readFlUIntBe16At2,
    readFlUIntBe16At3,
    readFlUIntBe16At4,
    readFlUIntBe16At5,
    readFlUIntBe16At6,
    readFlUIntBe16At7,
    readFlUIntBe17At0,
    readFlUIntBe17At1,
    readFlUIntBe17At2,
    readFlUIntBe17At3,
    readFlUIntBe17At4,
    readFlUIntBe17At5,
    readFlUIntBe17At6,
    readFlUIntBe17At7,
    readFlUIntBe18At0,
    readFlUIntBe18At1,
    readFlUIntBe18At2,
    readFlUIntBe18At3,
    readFlUIntBe18At4,
    readFlUIntBe18At5,
    readFlUIntBe18At6,
    readFlUIntBe18At7,
    readFlUIntBe19At0,
    readFlUIntBe19At1,
    readFlUIntBe19At2,
    readFlUIntBe19At3,
    readFlUIntBe19At4,
    readFlUIntBe19At5,
    readFlUIntBe19At6,
    readFlUIntBe19At7,
    readFlUIntBe20At0,
    readFlUIntBe20At1,
    readFlUIntBe20At2,
    readFlUIntBe20At3,
    readFlUIntBe20At4,
    readFlUIntBe20At5,
    readFlUIntBe20At6,
    readFlUIntBe20At7,
    readFlUIntBe21At0,
    readFlUIntBe21At1,
    readFlUIntBe21At2,
    readFlUIntBe21At3,
    readFlUIntBe21At4,
    readFlUIntBe21At5,
    readFlUIntBe21At6,
    readFlUIntBe21At7,
    readFlUIntBe22At0,
    readFlUIntBe22At1,
    readFlUIntBe22At2,
    readFlUIntBe22At3,
    readFlUIntBe22At4,
    readFlUIntBe22At5,
    readFlUIntBe22At6,
    readFlUIntBe22At7,
    readFlUIntBe23At0,
    readFlUIntBe23At1,
    readFlUIntBe23At2,
    readFlUIntBe23At3,
    readFlUIntBe23At4,
    readFlUIntBe23At5,
    readFlUIntBe23At6,
    readFlUIntBe23At7,
    readFlUIntBe24At0,
    readFlUIntBe24At1,
    readFlUIntBe24At2,
    readFlUIntBe24At3,
    readFlUIntBe24At4,
    readFlUIntBe24At5,
    readFlUIntBe24At6,
    readFlUIntBe24At7,
    readFlUIntBe25At0,
    readFlUIntBe25At1,
    readFlUIntBe25At2,
    readFlUIntBe25At3,
    readFlUIntBe25At4,
    readFlUIntBe25At5,
    readFlUIntBe25At6,
    readFlUIntBe25At7,
    readFlUIntBe26At0,
    readFlUIntBe26At1,
    readFlUIntBe26At2,
    readFlUIntBe26At3,
    readFlUIntBe26At4,
    readFlUIntBe26At5,
    readFlUIntBe26At6,
    readFlUIntBe26At7,
    readFlUIntBe27At0,
    readFlUIntBe27At1,
    readFlUIntBe27At2,
    readFlUIntBe27At3,
    readFlUIntBe27At4,
    readFlUIntBe27At5,
    readFlUIntBe27At6,
    readFlUIntBe27At7,
    readFlUIntBe28At0,
    readFlUIntBe28At1,
    readFlUIntBe28At2,
    readFlUIntBe28At3,
    readFlUIntBe28At4,
    readFlUIntBe28At5,
    readFlUIntBe28At6,
    readFlUIntBe28At7,
    readFlUIntBe29At0,
    readFlUIntBe29At1,
    readFlUIntBe29At2,
    readFlUIntBe29At3,
    readFlUIntBe29At4,
    readFlUIntBe29At5,
    readFlUIntBe29At6,
    readFlUIntBe29At7,
    readFlUIntBe30At0,
    readFlUIntBe30At1,
    readFlUIntBe30At2,
    readFlUIntBe30At3,
    readFlUIntBe30At4,
    readFlUIntBe30At5,
    readFlUIntBe30At6,
    readFlUIntBe30At7,
    readFlUIntBe31At0,
    readFlUIntBe31At1,
    readFlUIntBe31At2,
    readFlUIntBe31At3,
    readFlUIntBe31At4,
    readFlUIntBe31At5,
    readFlUIntBe31At6,
    readFlUIntBe31At7,
    readFlUIntBe32At0,
    readFlUIntBe32At1,
    readFlUIntBe32At2,
    readFlUIntBe32At3,
    readFlUIntBe32At4,
    readFlUIntBe32At5,
    readFlUIntBe32At6,
    readFlUIntBe32At7,
    readFlUIntBe33At0,
    readFlUIntBe33At1,
    readFlUIntBe33At2,
    readFlUIntBe33At3,
    readFlUIntBe33At4,
    readFlUIntBe33At5,
    readFlUIntBe33At6,
    readFlUIntBe33At7,
    readFlUIntBe34At0,
    readFlUIntBe34At1,
    readFlUIntBe34At2,
    readFlUIntBe34At3,
    readFlUIntBe34At4,
    readFlUIntBe34At5,
    readFlUIntBe34At6,
    readFlUIntBe34At7,
    readFlUIntBe35At0,
    readFlUIntBe35At1,
    readFlUIntBe35At2,
    readFlUIntBe35At3,
    readFlUIntBe35At4,
    readFlUIntBe35At5,
    readFlUIntBe35At6,
    readFlUIntBe35At7,
    readFlUIntBe36At0,
    readFlUIntBe36At1,
    readFlUIntBe36At2,
    readFlUIntBe36At3,
    readFlUIntBe36At4,
    readFlUIntBe36At5,
    readFlUIntBe36At6,
    readFlUIntBe36At7,
    readFlUIntBe37At0,
    readFlUIntBe37At1,
    readFlUIntBe37At2,
    readFlUIntBe37At3,
    readFlUIntBe37At4,
    readFlUIntBe37At5,
    readFlUIntBe37At6,
    readFlUIntBe37At7,
    readFlUIntBe38At0,
    readFlUIntBe38At1,
    readFlUIntBe38At2,
    readFlUIntBe38At3,
    readFlUIntBe38At4,
    readFlUIntBe38At5,
    readFlUIntBe38At6,
    readFlUIntBe38At7,
    readFlUIntBe39At0,
    readFlUIntBe39At1,
    readFlUIntBe39At2,
    readFlUIntBe39At3,
    readFlUIntBe39At4,
    readFlUIntBe39At5,
    readFlUIntBe39At6,
    readFlUIntBe39At7,
    readFlUIntBe40At0,
    readFlUIntBe40At1,
    readFlUIntBe40At2,
    readFlUIntBe40At3,
    readFlUIntBe40At4,
    readFlUIntBe40At5,
    readFlUIntBe40At6,
    readFlUIntBe40At7,
    readFlUIntBe41At0,
    readFlUIntBe41At1,
    readFlUIntBe41At2,
    readFlUIntBe41At3,
    readFlUIntBe41At4,
    readFlUIntBe41At5,
    readFlUIntBe41At6,
    readFlUIntBe41At7,
    readFlUIntBe42At0,
    readFlUIntBe42At1,
    readFlUIntBe42At2,
    readFlUIntBe42At3,
    readFlUIntBe42At4,
    readFlUIntBe42At5,
    readFlUIntBe42At6,
    readFlUIntBe42At7,
    readFlUIntBe43At0,
    readFlUIntBe43At1,
    readFlUIntBe43At2,
    readFlUIntBe43At3,
    readFlUIntBe43At4,
    readFlUIntBe43At5,
    readFlUIntBe43At6,
    readFlUIntBe43At7,
    readFlUIntBe44At0,
    readFlUIntBe44At1,
    readFlUIntBe44At2,
    readFlUIntBe44At3,
    readFlUIntBe44At4,
    readFlUIntBe44At5,
    readFlUIntBe44At6,
    readFlUIntBe44At7,
    readFlUIntBe45At0,
    readFlUIntBe45At1,
    readFlUIntBe45At2,
    readFlUIntBe45At3,
    readFlUIntBe45At4,
    readFlUIntBe45At5,
    readFlUIntBe45At6,
    readFlUIntBe45At7,
    readFlUIntBe46At0,
    readFlUIntBe46At1,
    readFlUIntBe46At2,
    readFlUIntBe46At3,
    readFlUIntBe46At4,
    readFlUIntBe46At5,
    readFlUIntBe46At6,
    readFlUIntBe46At7,
    readFlUIntBe47At0,
    readFlUIntBe47At1,
    readFlUIntBe47At2,
    readFlUIntBe47At3,
    readFlUIntBe47At4,
    readFlUIntBe47At5,
    readFlUIntBe47At6,
    readFlUIntBe47At7,
    readFlUIntBe48At0,
    readFlUIntBe48At1,
    readFlUIntBe48At2,
    readFlUIntBe48At3,
    readFlUIntBe48At4,
    readFlUIntBe48At5,
    readFlUIntBe48At6,
    readFlUIntBe48At7,
    readFlUIntBe49At0,
    readFlUIntBe49At1,
    readFlUIntBe49At2,
    readFlUIntBe49At3,
    readFlUIntBe49At4,
    readFlUIntBe49At5,
    readFlUIntBe49At6,
    readFlUIntBe49At7,
    readFlUIntBe50At0,
    readFlUIntBe50At1,
    readFlUIntBe50At2,
    readFlUIntBe50At3,
    readFlUIntBe50At4,
    readFlUIntBe50At5,
    readFlUIntBe50At6,
    readFlUIntBe50At7,
    readFlUIntBe51At0,
    readFlUIntBe51At1,
    readFlUIntBe51At2,
    readFlUIntBe51At3,
    readFlUIntBe51At4,
    readFlUIntBe51At5,
    readFlUIntBe51At6,
    readFlUIntBe51At7,
    readFlUIntBe52At0,
    readFlUIntBe52At1,
    readFlUIntBe52At2,
    readFlUIntBe52At3,
    readFlUIntBe52At4,
    readFlUIntBe52At5,
    readFlUIntBe52At6,
    readFlUIntBe52At7,
    readFlUIntBe53At0,
    readFlUIntBe53At1,
    readFlUIntBe53At2,
    readFlUIntBe53At3,
    readFlUIntBe53At4,
    readFlUIntBe53At5,
    readFlUIntBe53At6,
    readFlUIntBe53At7,
    readFlUIntBe54At0,
    readFlUIntBe54At1,
    readFlUIntBe54At2,
    readFlUIntBe54At3,
    readFlUIntBe54At4,
    readFlUIntBe54At5,
    readFlUIntBe54At6,
    readFlUIntBe54At7,
    readFlUIntBe55At0,
    readFlUIntBe55At1,
    readFlUIntBe55At2,
    readFlUIntBe55At3,
    readFlUIntBe55At4,
    readFlUIntBe55At5,
    readFlUIntBe55At6,
    readFlUIntBe55At7,
    readFlUIntBe56At0,
    readFlUIntBe56At1,
    readFlUIntBe56At2,
    readFlUIntBe56At3,
    readFlUIntBe56At4,
    readFlUIntBe56At5,
    readFlUIntBe56At6,
    readFlUIntBe56At7,
    readFlUIntBe57At0,
    readFlUIntBe57At1,
    readFlUIntBe57At2,
    readFlUIntBe57At3,
    readFlUIntBe57At4,
    readFlUIntBe57At5,
    readFlUIntBe57At6,
    readFlUIntBe57At7,
    readFlUIntBe58At0,
    readFlUIntBe58At1,
    readFlUIntBe58At2,
    readFlUIntBe58At3,
    readFlUIntBe58At4,
    readFlUIntBe58At5,
    readFlUIntBe58At6,
    readFlUIntBe58At7,
    readFlUIntBe59At0,
    readFlUIntBe59At1,
    readFlUIntBe59At2,
    readFlUIntBe59At3,
    readFlUIntBe59At4,
    readFlUIntBe59At5,
    readFlUIntBe59At6,
    readFlUIntBe59At7,
    readFlUIntBe60At0,
    readFlUIntBe60At1,
    readFlUIntBe60At2,
    readFlUIntBe60At3,
    readFlUIntBe60At4,
    readFlUIntBe60At5,
    readFlUIntBe60At6,
    readFlUIntBe60At7,
    readFlUIntBe61At0,
    readFlUIntBe61At1,
    readFlUIntBe61At2,
    readFlUIntBe61At3,
    readFlUIntBe61At4,
    readFlUIntBe61At5,
    readFlUIntBe61At6,
    readFlUIntBe61At7,
    readFlUIntBe62At0,
    readFlUIntBe62At1,
    readFlUIntBe62At2,
    readFlUIntBe62At3,
    readFlUIntBe62At4,
    readFlUIntBe62At5,
    readFlUIntBe62At6,
    readFlUIntBe62At7,
    readFlUIntBe63At0,
    readFlUIntBe63At1,
    readFlUIntBe63At2,
    readFlUIntBe63At3,
    readFlUIntBe63At4,
    readFlUIntBe63At5,
    readFlUIntBe63At6,
    readFlUIntBe63At7,
    readFlUIntBe64At0,
    readFlUIntBe64At1,
    readFlUIntBe64At2,
    readFlUIntBe64At3,
    readFlUIntBe64At4,
    readFlUIntBe64At5,
    readFlUIntBe64At6,
    readFlUIntBe64At7,
};

std::int64_t (*readFlSIntBeFuncs[])(const std::uint8_t *) = {
    readFlSIntBe1At0,
    readFlSIntBe1At1,
    readFlSIntBe1At2,
    readFlSIntBe1At3,
    readFlSIntBe1At4,
    readFlSIntBe1At5,
    readFlSIntBe1At6,
    readFlSIntBe1At7,
    readFlSIntBe2At0,
    readFlSIntBe2At1,
    readFlSIntBe2At2,
    readFlSIntBe2At3,
    readFlSIntBe2At4,
    readFlSIntBe2At5,
    readFlSIntBe2At6,
    readFlSIntBe2At7,
    readFlSIntBe3At0,
    readFlSIntBe3At1,
    readFlSIntBe3At2,
    readFlSIntBe3At3,
    readFlSIntBe3At4,
    readFlSIntBe3At5,
    readFlSIntBe3At6,
    readFlSIntBe3At7,
    readFlSIntBe4At0,
    readFlSIntBe4At1,
    readFlSIntBe4At2,
    readFlSIntBe4At3,
    readFlSIntBe4At4,
    readFlSIntBe4At5,
    readFlSIntBe4At6,
    readFlSIntBe4At7,
    readFlSIntBe5At0,
    readFlSIntBe5At1,
    readFlSIntBe5At2,
    readFlSIntBe5At3,
    readFlSIntBe5At4,
    readFlSIntBe5At5,
    readFlSIntBe5At6,
    readFlSIntBe5At7,
    readFlSIntBe6At0,
    readFlSIntBe6At1,
    readFlSIntBe6At2,
    readFlSIntBe6At3,
    readFlSIntBe6At4,
    readFlSIntBe6At5,
    readFlSIntBe6At6,
    readFlSIntBe6At7,
    readFlSIntBe7At0,
    readFlSIntBe7At1,
    readFlSIntBe7At2,
    readFlSIntBe7At3,
    readFlSIntBe7At4,
    readFlSIntBe7At5,
    readFlSIntBe7At6,
    readFlSIntBe7At7,
    readFlSIntBe8At0,
    readFlSIntBe8At1,
    readFlSIntBe8At2,
    readFlSIntBe8At3,
    readFlSIntBe8At4,
    readFlSIntBe8At5,
    readFlSIntBe8At6,
    readFlSIntBe8At7,
    readFlSIntBe9At0,
    readFlSIntBe9At1,
    readFlSIntBe9At2,
    readFlSIntBe9At3,
    readFlSIntBe9At4,
    readFlSIntBe9At5,
    readFlSIntBe9At6,
    readFlSIntBe9At7,
    readFlSIntBe10At0,
    readFlSIntBe10At1,
    readFlSIntBe10At2,
    readFlSIntBe10At3,
    readFlSIntBe10At4,
    readFlSIntBe10At5,
    readFlSIntBe10At6,
    readFlSIntBe10At7,
    readFlSIntBe11At0,
    readFlSIntBe11At1,
    readFlSIntBe11At2,
    readFlSIntBe11At3,
    readFlSIntBe11At4,
    readFlSIntBe11At5,
    readFlSIntBe11At6,
    readFlSIntBe11At7,
    readFlSIntBe12At0,
    readFlSIntBe12At1,
    readFlSIntBe12At2,
    readFlSIntBe12At3,
    readFlSIntBe12At4,
    readFlSIntBe12At5,
    readFlSIntBe12At6,
    readFlSIntBe12At7,
    readFlSIntBe13At0,
    readFlSIntBe13At1,
    readFlSIntBe13At2,
    readFlSIntBe13At3,
    readFlSIntBe13At4,
    readFlSIntBe13At5,
    readFlSIntBe13At6,
    readFlSIntBe13At7,
    readFlSIntBe14At0,
    readFlSIntBe14At1,
    readFlSIntBe14At2,
    readFlSIntBe14At3,
    readFlSIntBe14At4,
    readFlSIntBe14At5,
    readFlSIntBe14At6,
    readFlSIntBe14At7,
    readFlSIntBe15At0,
    readFlSIntBe15At1,
    readFlSIntBe15At2,
    readFlSIntBe15At3,
    readFlSIntBe15At4,
    readFlSIntBe15At5,
    readFlSIntBe15At6,
    readFlSIntBe15At7,
    readFlSIntBe16At0,
    readFlSIntBe16At1,
    readFlSIntBe16At2,
    readFlSIntBe16At3,
    readFlSIntBe16At4,
    readFlSIntBe16At5,
    readFlSIntBe16At6,
    readFlSIntBe16At7,
    readFlSIntBe17At0,
    readFlSIntBe17At1,
    readFlSIntBe17At2,
    readFlSIntBe17At3,
    readFlSIntBe17At4,
    readFlSIntBe17At5,
    readFlSIntBe17At6,
    readFlSIntBe17At7,
    readFlSIntBe18At0,
    readFlSIntBe18At1,
    readFlSIntBe18At2,
    readFlSIntBe18At3,
    readFlSIntBe18At4,
    readFlSIntBe18At5,
    readFlSIntBe18At6,
    readFlSIntBe18At7,
    readFlSIntBe19At0,
    readFlSIntBe19At1,
    readFlSIntBe19At2,
    readFlSIntBe19At3,
    readFlSIntBe19At4,
    readFlSIntBe19At5,
    readFlSIntBe19At6,
    readFlSIntBe19At7,
    readFlSIntBe20At0,
    readFlSIntBe20At1,
    readFlSIntBe20At2,
    readFlSIntBe20At3,
    readFlSIntBe20At4,
    readFlSIntBe20At5,
    readFlSIntBe20At6,
    readFlSIntBe20At7,
    readFlSIntBe21At0,
    readFlSIntBe21At1,
    readFlSIntBe21At2,
    readFlSIntBe21At3,
    readFlSIntBe21At4,
    readFlSIntBe21At5,
    readFlSIntBe21At6,
    readFlSIntBe21At7,
    readFlSIntBe22At0,
    readFlSIntBe22At1,
    readFlSIntBe22At2,
    readFlSIntBe22At3,
    readFlSIntBe22At4,
    readFlSIntBe22At5,
    readFlSIntBe22At6,
    readFlSIntBe22At7,
    readFlSIntBe23At0,
    readFlSIntBe23At1,
    readFlSIntBe23At2,
    readFlSIntBe23At3,
    readFlSIntBe23At4,
    readFlSIntBe23At5,
    readFlSIntBe23At6,
    readFlSIntBe23At7,
    readFlSIntBe24At0,
    readFlSIntBe24At1,
    readFlSIntBe24At2,
    readFlSIntBe24At3,
    readFlSIntBe24At4,
    readFlSIntBe24At5,
    readFlSIntBe24At6,
    readFlSIntBe24At7,
    readFlSIntBe25At0,
    readFlSIntBe25At1,
    readFlSIntBe25At2,
    readFlSIntBe25At3,
    readFlSIntBe25At4,
    readFlSIntBe25At5,
    readFlSIntBe25At6,
    readFlSIntBe25At7,
    readFlSIntBe26At0,
    readFlSIntBe26At1,
    readFlSIntBe26At2,
    readFlSIntBe26At3,
    readFlSIntBe26At4,
    readFlSIntBe26At5,
    readFlSIntBe26At6,
    readFlSIntBe26At7,
    readFlSIntBe27At0,
    readFlSIntBe27At1,
    readFlSIntBe27At2,
    readFlSIntBe27At3,
    readFlSIntBe27At4,
    readFlSIntBe27At5,
    readFlSIntBe27At6,
    readFlSIntBe27At7,
    readFlSIntBe28At0,
    readFlSIntBe28At1,
    readFlSIntBe28At2,
    readFlSIntBe28At3,
    readFlSIntBe28At4,
    readFlSIntBe28At5,
    readFlSIntBe28At6,
    readFlSIntBe28At7,
    readFlSIntBe29At0,
    readFlSIntBe29At1,
    readFlSIntBe29At2,
    readFlSIntBe29At3,
    readFlSIntBe29At4,
    readFlSIntBe29At5,
    readFlSIntBe29At6,
    readFlSIntBe29At7,
    readFlSIntBe30At0,
    readFlSIntBe30At1,
    readFlSIntBe30At2,
    readFlSIntBe30At3,
    readFlSIntBe30At4,
    readFlSIntBe30At5,
    readFlSIntBe30At6,
    readFlSIntBe30At7,
    readFlSIntBe31At0,
    readFlSIntBe31At1,
    readFlSIntBe31At2,
    readFlSIntBe31At3,
    readFlSIntBe31At4,
    readFlSIntBe31At5,
    readFlSIntBe31At6,
    readFlSIntBe31At7,
    readFlSIntBe32At0,
    readFlSIntBe32At1,
    readFlSIntBe32At2,
    readFlSIntBe32At3,
    readFlSIntBe32At4,
    readFlSIntBe32At5,
    readFlSIntBe32At6,
    readFlSIntBe32At7,
    readFlSIntBe33At0,
    readFlSIntBe33At1,
    readFlSIntBe33At2,
    readFlSIntBe33At3,
    readFlSIntBe33At4,
    readFlSIntBe33At5,
    readFlSIntBe33At6,
    readFlSIntBe33At7,
    readFlSIntBe34At0,
    readFlSIntBe34At1,
    readFlSIntBe34At2,
    readFlSIntBe34At3,
    readFlSIntBe34At4,
    readFlSIntBe34At5,
    readFlSIntBe34At6,
    readFlSIntBe34At7,
    readFlSIntBe35At0,
    readFlSIntBe35At1,
    readFlSIntBe35At2,
    readFlSIntBe35At3,
    readFlSIntBe35At4,
    readFlSIntBe35At5,
    readFlSIntBe35At6,
    readFlSIntBe35At7,
    readFlSIntBe36At0,
    readFlSIntBe36At1,
    readFlSIntBe36At2,
    readFlSIntBe36At3,
    readFlSIntBe36At4,
    readFlSIntBe36At5,
    readFlSIntBe36At6,
    readFlSIntBe36At7,
    readFlSIntBe37At0,
    readFlSIntBe37At1,
    readFlSIntBe37At2,
    readFlSIntBe37At3,
    readFlSIntBe37At4,
    readFlSIntBe37At5,
    readFlSIntBe37At6,
    readFlSIntBe37At7,
    readFlSIntBe38At0,
    readFlSIntBe38At1,
    readFlSIntBe38At2,
    readFlSIntBe38At3,
    readFlSIntBe38At4,
    readFlSIntBe38At5,
    readFlSIntBe38At6,
    readFlSIntBe38At7,
    readFlSIntBe39At0,
    readFlSIntBe39At1,
    readFlSIntBe39At2,
    readFlSIntBe39At3,
    readFlSIntBe39At4,
    readFlSIntBe39At5,
    readFlSIntBe39At6,
    readFlSIntBe39At7,
    readFlSIntBe40At0,
    readFlSIntBe40At1,
    readFlSIntBe40At2,
    readFlSIntBe40At3,
    readFlSIntBe40At4,
    readFlSIntBe40At5,
    readFlSIntBe40At6,
    readFlSIntBe40At7,
    readFlSIntBe41At0,
    readFlSIntBe41At1,
    readFlSIntBe41At2,
    readFlSIntBe41At3,
    readFlSIntBe41At4,
    readFlSIntBe41At5,
    readFlSIntBe41At6,
    readFlSIntBe41At7,
    readFlSIntBe42At0,
    readFlSIntBe42At1,
    readFlSIntBe42At2,
    readFlSIntBe42At3,
    readFlSIntBe42At4,
    readFlSIntBe42At5,
    readFlSIntBe42At6,
    readFlSIntBe42At7,
    readFlSIntBe43At0,
    readFlSIntBe43At1,
    readFlSIntBe43At2,
    readFlSIntBe43At3,
    readFlSIntBe43At4,
    readFlSIntBe43At5,
    readFlSIntBe43At6,
    readFlSIntBe43At7,
    readFlSIntBe44At0,
    readFlSIntBe44At1,
    readFlSIntBe44At2,
    readFlSIntBe44At3,
    readFlSIntBe44At4,
    readFlSIntBe44At5,
    readFlSIntBe44At6,
    readFlSIntBe44At7,
    readFlSIntBe45At0,
    readFlSIntBe45At1,
    readFlSIntBe45At2,
    readFlSIntBe45At3,
    readFlSIntBe45At4,
    readFlSIntBe45At5,
    readFlSIntBe45At6,
    readFlSIntBe45At7,
    readFlSIntBe46At0,
    readFlSIntBe46At1,
    readFlSIntBe46At2,
    readFlSIntBe46At3,
    readFlSIntBe46At4,
    readFlSIntBe46At5,
    readFlSIntBe46At6,
    readFlSIntBe46At7,
    readFlSIntBe47At0,
    readFlSIntBe47At1,
    readFlSIntBe47At2,
    readFlSIntBe47At3,
    readFlSIntBe47At4,
    readFlSIntBe47At5,
    readFlSIntBe47At6,
    readFlSIntBe47At7,
    readFlSIntBe48At0,
    readFlSIntBe48At1,
    readFlSIntBe48At2,
    readFlSIntBe48At3,
    readFlSIntBe48At4,
    readFlSIntBe48At5,
    readFlSIntBe48At6,
    readFlSIntBe48At7,
    readFlSIntBe49At0,
    readFlSIntBe49At1,
    readFlSIntBe49At2,
    readFlSIntBe49At3,
    readFlSIntBe49At4,
    readFlSIntBe49At5,
    readFlSIntBe49At6,
    readFlSIntBe49At7,
    readFlSIntBe50At0,
    readFlSIntBe50At1,
    readFlSIntBe50At2,
    readFlSIntBe50At3,
    readFlSIntBe50At4,
    readFlSIntBe50At5,
    readFlSIntBe50At6,
    readFlSIntBe50At7,
    readFlSIntBe51At0,
    readFlSIntBe51At1,
    readFlSIntBe51At2,
    readFlSIntBe51At3,
    readFlSIntBe51At4,
    readFlSIntBe51At5,
    readFlSIntBe51At6,
    readFlSIntBe51At7,
    readFlSIntBe52At0,
    readFlSIntBe52At1,
    readFlSIntBe52At2,
    readFlSIntBe52At3,
    readFlSIntBe52At4,
    readFlSIntBe52At5,
    readFlSIntBe52At6,
    readFlSIntBe52At7,
    readFlSIntBe53At0,
    readFlSIntBe53At1,
    readFlSIntBe53At2,
    readFlSIntBe53At3,
    readFlSIntBe53At4,
    readFlSIntBe53At5,
    readFlSIntBe53At6,
    readFlSIntBe53At7,
    readFlSIntBe54At0,
    readFlSIntBe54At1,
    readFlSIntBe54At2,
    readFlSIntBe54At3,
    readFlSIntBe54At4,
    readFlSIntBe54At5,
    readFlSIntBe54At6,
    readFlSIntBe54At7,
    readFlSIntBe55At0,
    readFlSIntBe55At1,
    readFlSIntBe55At2,
    readFlSIntBe55At3,
    readFlSIntBe55At4,
    readFlSIntBe55At5,
    readFlSIntBe55At6,
    readFlSIntBe55At7,
    readFlSIntBe56At0,
    readFlSIntBe56At1,
    readFlSIntBe56At2,
    readFlSIntBe56At3,
    readFlSIntBe56At4,
    readFlSIntBe56At5,
    readFlSIntBe56At6,
    readFlSIntBe56At7,
    readFlSIntBe57At0,
    readFlSIntBe57At1,
    readFlSIntBe57At2,
    readFlSIntBe57At3,
    readFlSIntBe57At4,
    readFlSIntBe57At5,
    readFlSIntBe57At6,
    readFlSIntBe57At7,
    readFlSIntBe58At0,
    readFlSIntBe58At1,
    readFlSIntBe58At2,
    readFlSIntBe58At3,
    readFlSIntBe58At4,
    readFlSIntBe58At5,
    readFlSIntBe58At6,
    readFlSIntBe58At7,
    readFlSIntBe59At0,
    readFlSIntBe59At1,
    readFlSIntBe59At2,
    readFlSIntBe59At3,
    readFlSIntBe59At4,
    readFlSIntBe59At5,
    readFlSIntBe59At6,
    readFlSIntBe59At7,
    readFlSIntBe60At0,
    readFlSIntBe60At1,
    readFlSIntBe60At2,
    readFlSIntBe60At3,
    readFlSIntBe60At4,
    readFlSIntBe60At5,
    readFlSIntBe60At6,
    readFlSIntBe60At7,
    readFlSIntBe61At0,
    readFlSIntBe61At1,
    readFlSIntBe61At2,
    readFlSIntBe61At3,
    readFlSIntBe61At4,
    readFlSIntBe61At5,
    readFlSIntBe61At6,
    readFlSIntBe61At7,
    readFlSIntBe62At0,
    readFlSIntBe62At1,
    readFlSIntBe62At2,
    readFlSIntBe62At3,
    readFlSIntBe62At4,
    readFlSIntBe62At5,
    readFlSIntBe62At6,
    readFlSIntBe62At7,
    readFlSIntBe63At0,
    readFlSIntBe63At1,
    readFlSIntBe63At2,
    readFlSIntBe63At3,
    readFlSIntBe63At4,
    readFlSIntBe63At5,
    readFlSIntBe63At6,
    readFlSIntBe63At7,
    readFlSIntBe64At0,
    readFlSIntBe64At1,
    readFlSIntBe64At2,
    readFlSIntBe64At3,
    readFlSIntBe64At4,
    readFlSIntBe64At5,
    readFlSIntBe64At6,
    readFlSIntBe64At7,
};

std::uint64_t (*readFlUIntLeFuncs[])(const std::uint8_t *) = {
    readFlUIntLe1At0,
    readFlUIntLe1At1,
    readFlUIntLe1At2,
    readFlUIntLe1At3,
    readFlUIntLe1At4,
    readFlUIntLe1At5,
    readFlUIntLe1At6,
    readFlUIntLe1At7,
    readFlUIntLe2At0,
    readFlUIntLe2At1,
    readFlUIntLe2At2,
    readFlUIntLe2At3,
    readFlUIntLe2At4,
    readFlUIntLe2At5,
    readFlUIntLe2At6,
    readFlUIntLe2At7,
    readFlUIntLe3At0,
    readFlUIntLe3At1,
    readFlUIntLe3At2,
    readFlUIntLe3At3,
    readFlUIntLe3At4,
    readFlUIntLe3At5,
    readFlUIntLe3At6,
    readFlUIntLe3At7,
    readFlUIntLe4At0,
    readFlUIntLe4At1,
    readFlUIntLe4At2,
    readFlUIntLe4At3,
    readFlUIntLe4At4,
    readFlUIntLe4At5,
    readFlUIntLe4At6,
    readFlUIntLe4At7,
    readFlUIntLe5At0,
    readFlUIntLe5At1,
    readFlUIntLe5At2,
    readFlUIntLe5At3,
    readFlUIntLe5At4,
    readFlUIntLe5At5,
    readFlUIntLe5At6,
    readFlUIntLe5At7,
    readFlUIntLe6At0,
    readFlUIntLe6At1,
    readFlUIntLe6At2,
    readFlUIntLe6At3,
    readFlUIntLe6At4,
    readFlUIntLe6At5,
    readFlUIntLe6At6,
    readFlUIntLe6At7,
    readFlUIntLe7At0,
    readFlUIntLe7At1,
    readFlUIntLe7At2,
    readFlUIntLe7At3,
    readFlUIntLe7At4,
    readFlUIntLe7At5,
    readFlUIntLe7At6,
    readFlUIntLe7At7,
    readFlUIntLe8At0,
    readFlUIntLe8At1,
    readFlUIntLe8At2,
    readFlUIntLe8At3,
    readFlUIntLe8At4,
    readFlUIntLe8At5,
    readFlUIntLe8At6,
    readFlUIntLe8At7,
    readFlUIntLe9At0,
    readFlUIntLe9At1,
    readFlUIntLe9At2,
    readFlUIntLe9At3,
    readFlUIntLe9At4,
    readFlUIntLe9At5,
    readFlUIntLe9At6,
    readFlUIntLe9At7,
    readFlUIntLe10At0,
    readFlUIntLe10At1,
    readFlUIntLe10At2,
    readFlUIntLe10At3,
    readFlUIntLe10At4,
    readFlUIntLe10At5,
    readFlUIntLe10At6,
    readFlUIntLe10At7,
    readFlUIntLe11At0,
    readFlUIntLe11At1,
    readFlUIntLe11At2,
    readFlUIntLe11At3,
    readFlUIntLe11At4,
    readFlUIntLe11At5,
    readFlUIntLe11At6,
    readFlUIntLe11At7,
    readFlUIntLe12At0,
    readFlUIntLe12At1,
    readFlUIntLe12At2,
    readFlUIntLe12At3,
    readFlUIntLe12At4,
    readFlUIntLe12At5,
    readFlUIntLe12At6,
    readFlUIntLe12At7,
    readFlUIntLe13At0,
    readFlUIntLe13At1,
    readFlUIntLe13At2,
    readFlUIntLe13At3,
    readFlUIntLe13At4,
    readFlUIntLe13At5,
    readFlUIntLe13At6,
    readFlUIntLe13At7,
    readFlUIntLe14At0,
    readFlUIntLe14At1,
    readFlUIntLe14At2,
    readFlUIntLe14At3,
    readFlUIntLe14At4,
    readFlUIntLe14At5,
    readFlUIntLe14At6,
    readFlUIntLe14At7,
    readFlUIntLe15At0,
    readFlUIntLe15At1,
    readFlUIntLe15At2,
    readFlUIntLe15At3,
    readFlUIntLe15At4,
    readFlUIntLe15At5,
    readFlUIntLe15At6,
    readFlUIntLe15At7,
    readFlUIntLe16At0,
    readFlUIntLe16At1,
    readFlUIntLe16At2,
    readFlUIntLe16At3,
    readFlUIntLe16At4,
    readFlUIntLe16At5,
    readFlUIntLe16At6,
    readFlUIntLe16At7,
    readFlUIntLe17At0,
    readFlUIntLe17At1,
    readFlUIntLe17At2,
    readFlUIntLe17At3,
    readFlUIntLe17At4,
    readFlUIntLe17At5,
    readFlUIntLe17At6,
    readFlUIntLe17At7,
    readFlUIntLe18At0,
    readFlUIntLe18At1,
    readFlUIntLe18At2,
    readFlUIntLe18At3,
    readFlUIntLe18At4,
    readFlUIntLe18At5,
    readFlUIntLe18At6,
    readFlUIntLe18At7,
    readFlUIntLe19At0,
    readFlUIntLe19At1,
    readFlUIntLe19At2,
    readFlUIntLe19At3,
    readFlUIntLe19At4,
    readFlUIntLe19At5,
    readFlUIntLe19At6,
    readFlUIntLe19At7,
    readFlUIntLe20At0,
    readFlUIntLe20At1,
    readFlUIntLe20At2,
    readFlUIntLe20At3,
    readFlUIntLe20At4,
    readFlUIntLe20At5,
    readFlUIntLe20At6,
    readFlUIntLe20At7,
    readFlUIntLe21At0,
    readFlUIntLe21At1,
    readFlUIntLe21At2,
    readFlUIntLe21At3,
    readFlUIntLe21At4,
    readFlUIntLe21At5,
    readFlUIntLe21At6,
    readFlUIntLe21At7,
    readFlUIntLe22At0,
    readFlUIntLe22At1,
    readFlUIntLe22At2,
    readFlUIntLe22At3,
    readFlUIntLe22At4,
    readFlUIntLe22At5,
    readFlUIntLe22At6,
    readFlUIntLe22At7,
    readFlUIntLe23At0,
    readFlUIntLe23At1,
    readFlUIntLe23At2,
    readFlUIntLe23At3,
    readFlUIntLe23At4,
    readFlUIntLe23At5,
    readFlUIntLe23At6,
    readFlUIntLe23At7,
    readFlUIntLe24At0,
    readFlUIntLe24At1,
    readFlUIntLe24At2,
    readFlUIntLe24At3,
    readFlUIntLe24At4,
    readFlUIntLe24At5,
    readFlUIntLe24At6,
    readFlUIntLe24At7,
    readFlUIntLe25At0,
    readFlUIntLe25At1,
    readFlUIntLe25At2,
    readFlUIntLe25At3,
    readFlUIntLe25At4,
    readFlUIntLe25At5,
    readFlUIntLe25At6,
    readFlUIntLe25At7,
    readFlUIntLe26At0,
    readFlUIntLe26At1,
    readFlUIntLe26At2,
    readFlUIntLe26At3,
    readFlUIntLe26At4,
    readFlUIntLe26At5,
    readFlUIntLe26At6,
    readFlUIntLe26At7,
    readFlUIntLe27At0,
    readFlUIntLe27At1,
    readFlUIntLe27At2,
    readFlUIntLe27At3,
    readFlUIntLe27At4,
    readFlUIntLe27At5,
    readFlUIntLe27At6,
    readFlUIntLe27At7,
    readFlUIntLe28At0,
    readFlUIntLe28At1,
    readFlUIntLe28At2,
    readFlUIntLe28At3,
    readFlUIntLe28At4,
    readFlUIntLe28At5,
    readFlUIntLe28At6,
    readFlUIntLe28At7,
    readFlUIntLe29At0,
    readFlUIntLe29At1,
    readFlUIntLe29At2,
    readFlUIntLe29At3,
    readFlUIntLe29At4,
    readFlUIntLe29At5,
    readFlUIntLe29At6,
    readFlUIntLe29At7,
    readFlUIntLe30At0,
    readFlUIntLe30At1,
    readFlUIntLe30At2,
    readFlUIntLe30At3,
    readFlUIntLe30At4,
    readFlUIntLe30At5,
    readFlUIntLe30At6,
    readFlUIntLe30At7,
    readFlUIntLe31At0,
    readFlUIntLe31At1,
    readFlUIntLe31At2,
    readFlUIntLe31At3,
    readFlUIntLe31At4,
    readFlUIntLe31At5,
    readFlUIntLe31At6,
    readFlUIntLe31At7,
    readFlUIntLe32At0,
    readFlUIntLe32At1,
    readFlUIntLe32At2,
    readFlUIntLe32At3,
    readFlUIntLe32At4,
    readFlUIntLe32At5,
    readFlUIntLe32At6,
    readFlUIntLe32At7,
    readFlUIntLe33At0,
    readFlUIntLe33At1,
    readFlUIntLe33At2,
    readFlUIntLe33At3,
    readFlUIntLe33At4,
    readFlUIntLe33At5,
    readFlUIntLe33At6,
    readFlUIntLe33At7,
    readFlUIntLe34At0,
    readFlUIntLe34At1,
    readFlUIntLe34At2,
    readFlUIntLe34At3,
    readFlUIntLe34At4,
    readFlUIntLe34At5,
    readFlUIntLe34At6,
    readFlUIntLe34At7,
    readFlUIntLe35At0,
    readFlUIntLe35At1,
    readFlUIntLe35At2,
    readFlUIntLe35At3,
    readFlUIntLe35At4,
    readFlUIntLe35At5,
    readFlUIntLe35At6,
    readFlUIntLe35At7,
    readFlUIntLe36At0,
    readFlUIntLe36At1,
    readFlUIntLe36At2,
    readFlUIntLe36At3,
    readFlUIntLe36At4,
    readFlUIntLe36At5,
    readFlUIntLe36At6,
    readFlUIntLe36At7,
    readFlUIntLe37At0,
    readFlUIntLe37At1,
    readFlUIntLe37At2,
    readFlUIntLe37At3,
    readFlUIntLe37At4,
    readFlUIntLe37At5,
    readFlUIntLe37At6,
    readFlUIntLe37At7,
    readFlUIntLe38At0,
    readFlUIntLe38At1,
    readFlUIntLe38At2,
    readFlUIntLe38At3,
    readFlUIntLe38At4,
    readFlUIntLe38At5,
    readFlUIntLe38At6,
    readFlUIntLe38At7,
    readFlUIntLe39At0,
    readFlUIntLe39At1,
    readFlUIntLe39At2,
    readFlUIntLe39At3,
    readFlUIntLe39At4,
    readFlUIntLe39At5,
    readFlUIntLe39At6,
    readFlUIntLe39At7,
    readFlUIntLe40At0,
    readFlUIntLe40At1,
    readFlUIntLe40At2,
    readFlUIntLe40At3,
    readFlUIntLe40At4,
    readFlUIntLe40At5,
    readFlUIntLe40At6,
    readFlUIntLe40At7,
    readFlUIntLe41At0,
    readFlUIntLe41At1,
    readFlUIntLe41At2,
    readFlUIntLe41At3,
    readFlUIntLe41At4,
    readFlUIntLe41At5,
    readFlUIntLe41At6,
    readFlUIntLe41At7,
    readFlUIntLe42At0,
    readFlUIntLe42At1,
    readFlUIntLe42At2,
    readFlUIntLe42At3,
    readFlUIntLe42At4,
    readFlUIntLe42At5,
    readFlUIntLe42At6,
    readFlUIntLe42At7,
    readFlUIntLe43At0,
    readFlUIntLe43At1,
    readFlUIntLe43At2,
    readFlUIntLe43At3,
    readFlUIntLe43At4,
    readFlUIntLe43At5,
    readFlUIntLe43At6,
    readFlUIntLe43At7,
    readFlUIntLe44At0,
    readFlUIntLe44At1,
    readFlUIntLe44At2,
    readFlUIntLe44At3,
    readFlUIntLe44At4,
    readFlUIntLe44At5,
    readFlUIntLe44At6,
    readFlUIntLe44At7,
    readFlUIntLe45At0,
    readFlUIntLe45At1,
    readFlUIntLe45At2,
    readFlUIntLe45At3,
    readFlUIntLe45At4,
    readFlUIntLe45At5,
    readFlUIntLe45At6,
    readFlUIntLe45At7,
    readFlUIntLe46At0,
    readFlUIntLe46At1,
    readFlUIntLe46At2,
    readFlUIntLe46At3,
    readFlUIntLe46At4,
    readFlUIntLe46At5,
    readFlUIntLe46At6,
    readFlUIntLe46At7,
    readFlUIntLe47At0,
    readFlUIntLe47At1,
    readFlUIntLe47At2,
    readFlUIntLe47At3,
    readFlUIntLe47At4,
    readFlUIntLe47At5,
    readFlUIntLe47At6,
    readFlUIntLe47At7,
    readFlUIntLe48At0,
    readFlUIntLe48At1,
    readFlUIntLe48At2,
    readFlUIntLe48At3,
    readFlUIntLe48At4,
    readFlUIntLe48At5,
    readFlUIntLe48At6,
    readFlUIntLe48At7,
    readFlUIntLe49At0,
    readFlUIntLe49At1,
    readFlUIntLe49At2,
    readFlUIntLe49At3,
    readFlUIntLe49At4,
    readFlUIntLe49At5,
    readFlUIntLe49At6,
    readFlUIntLe49At7,
    readFlUIntLe50At0,
    readFlUIntLe50At1,
    readFlUIntLe50At2,
    readFlUIntLe50At3,
    readFlUIntLe50At4,
    readFlUIntLe50At5,
    readFlUIntLe50At6,
    readFlUIntLe50At7,
    readFlUIntLe51At0,
    readFlUIntLe51At1,
    readFlUIntLe51At2,
    readFlUIntLe51At3,
    readFlUIntLe51At4,
    readFlUIntLe51At5,
    readFlUIntLe51At6,
    readFlUIntLe51At7,
    readFlUIntLe52At0,
    readFlUIntLe52At1,
    readFlUIntLe52At2,
    readFlUIntLe52At3,
    readFlUIntLe52At4,
    readFlUIntLe52At5,
    readFlUIntLe52At6,
    readFlUIntLe52At7,
    readFlUIntLe53At0,
    readFlUIntLe53At1,
    readFlUIntLe53At2,
    readFlUIntLe53At3,
    readFlUIntLe53At4,
    readFlUIntLe53At5,
    readFlUIntLe53At6,
    readFlUIntLe53At7,
    readFlUIntLe54At0,
    readFlUIntLe54At1,
    readFlUIntLe54At2,
    readFlUIntLe54At3,
    readFlUIntLe54At4,
    readFlUIntLe54At5,
    readFlUIntLe54At6,
    readFlUIntLe54At7,
    readFlUIntLe55At0,
    readFlUIntLe55At1,
    readFlUIntLe55At2,
    readFlUIntLe55At3,
    readFlUIntLe55At4,
    readFlUIntLe55At5,
    readFlUIntLe55At6,
    readFlUIntLe55At7,
    readFlUIntLe56At0,
    readFlUIntLe56At1,
    readFlUIntLe56At2,
    readFlUIntLe56At3,
    readFlUIntLe56At4,
    readFlUIntLe56At5,
    readFlUIntLe56At6,
    readFlUIntLe56At7,
    readFlUIntLe57At0,
    readFlUIntLe57At1,
    readFlUIntLe57At2,
    readFlUIntLe57At3,
    readFlUIntLe57At4,
    readFlUIntLe57At5,
    readFlUIntLe57At6,
    readFlUIntLe57At7,
    readFlUIntLe58At0,
    readFlUIntLe58At1,
    readFlUIntLe58At2,
    readFlUIntLe58At3,
    readFlUIntLe58At4,
    readFlUIntLe58At5,
    readFlUIntLe58At6,
    readFlUIntLe58At7,
    readFlUIntLe59At0,
    readFlUIntLe59At1,
    readFlUIntLe59At2,
    readFlUIntLe59At3,
    readFlUIntLe59At4,
    readFlUIntLe59At5,
    readFlUIntLe59At6,
    readFlUIntLe59At7,
    readFlUIntLe60At0,
    readFlUIntLe60At1,
    readFlUIntLe60At2,
    readFlUIntLe60At3,
    readFlUIntLe60At4,
    readFlUIntLe60At5,
    readFlUIntLe60At6,
    readFlUIntLe60At7,
    readFlUIntLe61At0,
    readFlUIntLe61At1,
    readFlUIntLe61At2,
    readFlUIntLe61At3,
    readFlUIntLe61At4,
    readFlUIntLe61At5,
    readFlUIntLe61At6,
    readFlUIntLe61At7,
    readFlUIntLe62At0,
    readFlUIntLe62At1,
    readFlUIntLe62At2,
    readFlUIntLe62At3,
    readFlUIntLe62At4,
    readFlUIntLe62At5,
    readFlUIntLe62At6,
    readFlUIntLe62At7,
    readFlUIntLe63At0,
    readFlUIntLe63At1,
    readFlUIntLe63At2,
    readFlUIntLe63At3,
    readFlUIntLe63At4,
    readFlUIntLe63At5,
    readFlUIntLe63At6,
    readFlUIntLe63At7,
    readFlUIntLe64At0,
    readFlUIntLe64At1,
    readFlUIntLe64At2,
    readFlUIntLe64At3,
    readFlUIntLe64At4,
    readFlUIntLe64At5,
    readFlUIntLe64At6,
    readFlUIntLe64At7,
};

std::int64_t (*readFlSIntLeFuncs[])(const std::uint8_t *) = {
    readFlSIntLe1At0,
    readFlSIntLe1At1,
    readFlSIntLe1At2,
    readFlSIntLe1At3,
    readFlSIntLe1At4,
    readFlSIntLe1At5,
    readFlSIntLe1At6,
    readFlSIntLe1At7,
    readFlSIntLe2At0,
    readFlSIntLe2At1,
    readFlSIntLe2At2,
    readFlSIntLe2At3,
    readFlSIntLe2At4,
    readFlSIntLe2At5,
    readFlSIntLe2At6,
    readFlSIntLe2At7,
    readFlSIntLe3At0,
    readFlSIntLe3At1,
    readFlSIntLe3At2,
    readFlSIntLe3At3,
    readFlSIntLe3At4,
    readFlSIntLe3At5,
    readFlSIntLe3At6,
    readFlSIntLe3At7,
    readFlSIntLe4At0,
    readFlSIntLe4At1,
    readFlSIntLe4At2,
    readFlSIntLe4At3,
    readFlSIntLe4At4,
    readFlSIntLe4At5,
    readFlSIntLe4At6,
    readFlSIntLe4At7,
    readFlSIntLe5At0,
    readFlSIntLe5At1,
    readFlSIntLe5At2,
    readFlSIntLe5At3,
    readFlSIntLe5At4,
    readFlSIntLe5At5,
    readFlSIntLe5At6,
    readFlSIntLe5At7,
    readFlSIntLe6At0,
    readFlSIntLe6At1,
    readFlSIntLe6At2,
    readFlSIntLe6At3,
    readFlSIntLe6At4,
    readFlSIntLe6At5,
    readFlSIntLe6At6,
    readFlSIntLe6At7,
    readFlSIntLe7At0,
    readFlSIntLe7At1,
    readFlSIntLe7At2,
    readFlSIntLe7At3,
    readFlSIntLe7At4,
    readFlSIntLe7At5,
    readFlSIntLe7At6,
    readFlSIntLe7At7,
    readFlSIntLe8At0,
    readFlSIntLe8At1,
    readFlSIntLe8At2,
    readFlSIntLe8At3,
    readFlSIntLe8At4,
    readFlSIntLe8At5,
    readFlSIntLe8At6,
    readFlSIntLe8At7,
    readFlSIntLe9At0,
    readFlSIntLe9At1,
    readFlSIntLe9At2,
    readFlSIntLe9At3,
    readFlSIntLe9At4,
    readFlSIntLe9At5,
    readFlSIntLe9At6,
    readFlSIntLe9At7,
    readFlSIntLe10At0,
    readFlSIntLe10At1,
    readFlSIntLe10At2,
    readFlSIntLe10At3,
    readFlSIntLe10At4,
    readFlSIntLe10At5,
    readFlSIntLe10At6,
    readFlSIntLe10At7,
    readFlSIntLe11At0,
    readFlSIntLe11At1,
    readFlSIntLe11At2,
    readFlSIntLe11At3,
    readFlSIntLe11At4,
    readFlSIntLe11At5,
    readFlSIntLe11At6,
    readFlSIntLe11At7,
    readFlSIntLe12At0,
    readFlSIntLe12At1,
    readFlSIntLe12At2,
    readFlSIntLe12At3,
    readFlSIntLe12At4,
    readFlSIntLe12At5,
    readFlSIntLe12At6,
    readFlSIntLe12At7,
    readFlSIntLe13At0,
    readFlSIntLe13At1,
    readFlSIntLe13At2,
    readFlSIntLe13At3,
    readFlSIntLe13At4,
    readFlSIntLe13At5,
    readFlSIntLe13At6,
    readFlSIntLe13At7,
    readFlSIntLe14At0,
    readFlSIntLe14At1,
    readFlSIntLe14At2,
    readFlSIntLe14At3,
    readFlSIntLe14At4,
    readFlSIntLe14At5,
    readFlSIntLe14At6,
    readFlSIntLe14At7,
    readFlSIntLe15At0,
    readFlSIntLe15At1,
    readFlSIntLe15At2,
    readFlSIntLe15At3,
    readFlSIntLe15At4,
    readFlSIntLe15At5,
    readFlSIntLe15At6,
    readFlSIntLe15At7,
    readFlSIntLe16At0,
    readFlSIntLe16At1,
    readFlSIntLe16At2,
    readFlSIntLe16At3,
    readFlSIntLe16At4,
    readFlSIntLe16At5,
    readFlSIntLe16At6,
    readFlSIntLe16At7,
    readFlSIntLe17At0,
    readFlSIntLe17At1,
    readFlSIntLe17At2,
    readFlSIntLe17At3,
    readFlSIntLe17At4,
    readFlSIntLe17At5,
    readFlSIntLe17At6,
    readFlSIntLe17At7,
    readFlSIntLe18At0,
    readFlSIntLe18At1,
    readFlSIntLe18At2,
    readFlSIntLe18At3,
    readFlSIntLe18At4,
    readFlSIntLe18At5,
    readFlSIntLe18At6,
    readFlSIntLe18At7,
    readFlSIntLe19At0,
    readFlSIntLe19At1,
    readFlSIntLe19At2,
    readFlSIntLe19At3,
    readFlSIntLe19At4,
    readFlSIntLe19At5,
    readFlSIntLe19At6,
    readFlSIntLe19At7,
    readFlSIntLe20At0,
    readFlSIntLe20At1,
    readFlSIntLe20At2,
    readFlSIntLe20At3,
    readFlSIntLe20At4,
    readFlSIntLe20At5,
    readFlSIntLe20At6,
    readFlSIntLe20At7,
    readFlSIntLe21At0,
    readFlSIntLe21At1,
    readFlSIntLe21At2,
    readFlSIntLe21At3,
    readFlSIntLe21At4,
    readFlSIntLe21At5,
    readFlSIntLe21At6,
    readFlSIntLe21At7,
    readFlSIntLe22At0,
    readFlSIntLe22At1,
    readFlSIntLe22At2,
    readFlSIntLe22At3,
    readFlSIntLe22At4,
    readFlSIntLe22At5,
    readFlSIntLe22At6,
    readFlSIntLe22At7,
    readFlSIntLe23At0,
    readFlSIntLe23At1,
    readFlSIntLe23At2,
    readFlSIntLe23At3,
    readFlSIntLe23At4,
    readFlSIntLe23At5,
    readFlSIntLe23At6,
    readFlSIntLe23At7,
    readFlSIntLe24At0,
    readFlSIntLe24At1,
    readFlSIntLe24At2,
    readFlSIntLe24At3,
    readFlSIntLe24At4,
    readFlSIntLe24At5,
    readFlSIntLe24At6,
    readFlSIntLe24At7,
    readFlSIntLe25At0,
    readFlSIntLe25At1,
    readFlSIntLe25At2,
    readFlSIntLe25At3,
    readFlSIntLe25At4,
    readFlSIntLe25At5,
    readFlSIntLe25At6,
    readFlSIntLe25At7,
    readFlSIntLe26At0,
    readFlSIntLe26At1,
    readFlSIntLe26At2,
    readFlSIntLe26At3,
    readFlSIntLe26At4,
    readFlSIntLe26At5,
    readFlSIntLe26At6,
    readFlSIntLe26At7,
    readFlSIntLe27At0,
    readFlSIntLe27At1,
    readFlSIntLe27At2,
    readFlSIntLe27At3,
    readFlSIntLe27At4,
    readFlSIntLe27At5,
    readFlSIntLe27At6,
    readFlSIntLe27At7,
    readFlSIntLe28At0,
    readFlSIntLe28At1,
    readFlSIntLe28At2,
    readFlSIntLe28At3,
    readFlSIntLe28At4,
    readFlSIntLe28At5,
    readFlSIntLe28At6,
    readFlSIntLe28At7,
    readFlSIntLe29At0,
    readFlSIntLe29At1,
    readFlSIntLe29At2,
    readFlSIntLe29At3,
    readFlSIntLe29At4,
    readFlSIntLe29At5,
    readFlSIntLe29At6,
    readFlSIntLe29At7,
    readFlSIntLe30At0,
    readFlSIntLe30At1,
    readFlSIntLe30At2,
    readFlSIntLe30At3,
    readFlSIntLe30At4,
    readFlSIntLe30At5,
    readFlSIntLe30At6,
    readFlSIntLe30At7,
    readFlSIntLe31At0,
    readFlSIntLe31At1,
    readFlSIntLe31At2,
    readFlSIntLe31At3,
    readFlSIntLe31At4,
    readFlSIntLe31At5,
    readFlSIntLe31At6,
    readFlSIntLe31At7,
    readFlSIntLe32At0,
    readFlSIntLe32At1,
    readFlSIntLe32At2,
    readFlSIntLe32At3,
    readFlSIntLe32At4,
    readFlSIntLe32At5,
    readFlSIntLe32At6,
    readFlSIntLe32At7,
    readFlSIntLe33At0,
    readFlSIntLe33At1,
    readFlSIntLe33At2,
    readFlSIntLe33At3,
    readFlSIntLe33At4,
    readFlSIntLe33At5,
    readFlSIntLe33At6,
    readFlSIntLe33At7,
    readFlSIntLe34At0,
    readFlSIntLe34At1,
    readFlSIntLe34At2,
    readFlSIntLe34At3,
    readFlSIntLe34At4,
    readFlSIntLe34At5,
    readFlSIntLe34At6,
    readFlSIntLe34At7,
    readFlSIntLe35At0,
    readFlSIntLe35At1,
    readFlSIntLe35At2,
    readFlSIntLe35At3,
    readFlSIntLe35At4,
    readFlSIntLe35At5,
    readFlSIntLe35At6,
    readFlSIntLe35At7,
    readFlSIntLe36At0,
    readFlSIntLe36At1,
    readFlSIntLe36At2,
    readFlSIntLe36At3,
    readFlSIntLe36At4,
    readFlSIntLe36At5,
    readFlSIntLe36At6,
    readFlSIntLe36At7,
    readFlSIntLe37At0,
    readFlSIntLe37At1,
    readFlSIntLe37At2,
    readFlSIntLe37At3,
    readFlSIntLe37At4,
    readFlSIntLe37At5,
    readFlSIntLe37At6,
    readFlSIntLe37At7,
    readFlSIntLe38At0,
    readFlSIntLe38At1,
    readFlSIntLe38At2,
    readFlSIntLe38At3,
    readFlSIntLe38At4,
    readFlSIntLe38At5,
    readFlSIntLe38At6,
    readFlSIntLe38At7,
    readFlSIntLe39At0,
    readFlSIntLe39At1,
    readFlSIntLe39At2,
    readFlSIntLe39At3,
    readFlSIntLe39At4,
    readFlSIntLe39At5,
    readFlSIntLe39At6,
    readFlSIntLe39At7,
    readFlSIntLe40At0,
    readFlSIntLe40At1,
    readFlSIntLe40At2,
    readFlSIntLe40At3,
    readFlSIntLe40At4,
    readFlSIntLe40At5,
    readFlSIntLe40At6,
    readFlSIntLe40At7,
    readFlSIntLe41At0,
    readFlSIntLe41At1,
    readFlSIntLe41At2,
    readFlSIntLe41At3,
    readFlSIntLe41At4,
    readFlSIntLe41At5,
    readFlSIntLe41At6,
    readFlSIntLe41At7,
    readFlSIntLe42At0,
    readFlSIntLe42At1,
    readFlSIntLe42At2,
    readFlSIntLe42At3,
    readFlSIntLe42At4,
    readFlSIntLe42At5,
    readFlSIntLe42At6,
    readFlSIntLe42At7,
    readFlSIntLe43At0,
    readFlSIntLe43At1,
    readFlSIntLe43At2,
    readFlSIntLe43At3,
    readFlSIntLe43At4,
    readFlSIntLe43At5,
    readFlSIntLe43At6,
    readFlSIntLe43At7,
    readFlSIntLe44At0,
    readFlSIntLe44At1,
    readFlSIntLe44At2,
    readFlSIntLe44At3,
    readFlSIntLe44At4,
    readFlSIntLe44At5,
    readFlSIntLe44At6,
    readFlSIntLe44At7,
    readFlSIntLe45At0,
    readFlSIntLe45At1,
    readFlSIntLe45At2,
    readFlSIntLe45At3,
    readFlSIntLe45At4,
    readFlSIntLe45At5,
    readFlSIntLe45At6,
    readFlSIntLe45At7,
    readFlSIntLe46At0,
    readFlSIntLe46At1,
    readFlSIntLe46At2,
    readFlSIntLe46At3,
    readFlSIntLe46At4,
    readFlSIntLe46At5,
    readFlSIntLe46At6,
    readFlSIntLe46At7,
    readFlSIntLe47At0,
    readFlSIntLe47At1,
    readFlSIntLe47At2,
    readFlSIntLe47At3,
    readFlSIntLe47At4,
    readFlSIntLe47At5,
    readFlSIntLe47At6,
    readFlSIntLe47At7,
    readFlSIntLe48At0,
    readFlSIntLe48At1,
    readFlSIntLe48At2,
    readFlSIntLe48At3,
    readFlSIntLe48At4,
    readFlSIntLe48At5,
    readFlSIntLe48At6,
    readFlSIntLe48At7,
    readFlSIntLe49At0,
    readFlSIntLe49At1,
    readFlSIntLe49At2,
    readFlSIntLe49At3,
    readFlSIntLe49At4,
    readFlSIntLe49At5,
    readFlSIntLe49At6,
    readFlSIntLe49At7,
    readFlSIntLe50At0,
    readFlSIntLe50At1,
    readFlSIntLe50At2,
    readFlSIntLe50At3,
    readFlSIntLe50At4,
    readFlSIntLe50At5,
    readFlSIntLe50At6,
    readFlSIntLe50At7,
    readFlSIntLe51At0,
    readFlSIntLe51At1,
    readFlSIntLe51At2,
    readFlSIntLe51At3,
    readFlSIntLe51At4,
    readFlSIntLe51At5,
    readFlSIntLe51At6,
    readFlSIntLe51At7,
    readFlSIntLe52At0,
    readFlSIntLe52At1,
    readFlSIntLe52At2,
    readFlSIntLe52At3,
    readFlSIntLe52At4,
    readFlSIntLe52At5,
    readFlSIntLe52At6,
    readFlSIntLe52At7,
    readFlSIntLe53At0,
    readFlSIntLe53At1,
    readFlSIntLe53At2,
    readFlSIntLe53At3,
    readFlSIntLe53At4,
    readFlSIntLe53At5,
    readFlSIntLe53At6,
    readFlSIntLe53At7,
    readFlSIntLe54At0,
    readFlSIntLe54At1,
    readFlSIntLe54At2,
    readFlSIntLe54At3,
    readFlSIntLe54At4,
    readFlSIntLe54At5,
    readFlSIntLe54At6,
    readFlSIntLe54At7,
    readFlSIntLe55At0,
    readFlSIntLe55At1,
    readFlSIntLe55At2,
    readFlSIntLe55At3,
    readFlSIntLe55At4,
    readFlSIntLe55At5,
    readFlSIntLe55At6,
    readFlSIntLe55At7,
    readFlSIntLe56At0,
    readFlSIntLe56At1,
    readFlSIntLe56At2,
    readFlSIntLe56At3,
    readFlSIntLe56At4,
    readFlSIntLe56At5,
    readFlSIntLe56At6,
    readFlSIntLe56At7,
    readFlSIntLe57At0,
    readFlSIntLe57At1,
    readFlSIntLe57At2,
    readFlSIntLe57At3,
    readFlSIntLe57At4,
    readFlSIntLe57At5,
    readFlSIntLe57At6,
    readFlSIntLe57At7,
    readFlSIntLe58At0,
    readFlSIntLe58At1,
    readFlSIntLe58At2,
    readFlSIntLe58At3,
    readFlSIntLe58At4,
    readFlSIntLe58At5,
    readFlSIntLe58At6,
    readFlSIntLe58At7,
    readFlSIntLe59At0,
    readFlSIntLe59At1,
    readFlSIntLe59At2,
    readFlSIntLe59At3,
    readFlSIntLe59At4,
    readFlSIntLe59At5,
    readFlSIntLe59At6,
    readFlSIntLe59At7,
    readFlSIntLe60At0,
    readFlSIntLe60At1,
    readFlSIntLe60At2,
    readFlSIntLe60At3,
    readFlSIntLe60At4,
    readFlSIntLe60At5,
    readFlSIntLe60At6,
    readFlSIntLe60At7,
    readFlSIntLe61At0,
    readFlSIntLe61At1,
    readFlSIntLe61At2,
    readFlSIntLe61At3,
    readFlSIntLe61At4,
    readFlSIntLe61At5,
    readFlSIntLe61At6,
    readFlSIntLe61At7,
    readFlSIntLe62At0,
    readFlSIntLe62At1,
    readFlSIntLe62At2,
    readFlSIntLe62At3,
    readFlSIntLe62At4,
    readFlSIntLe62At5,
    readFlSIntLe62At6,
    readFlSIntLe62At7,
    readFlSIntLe63At0,
    readFlSIntLe63At1,
    readFlSIntLe63At2,
    readFlSIntLe63At3,
    readFlSIntLe63At4,
    readFlSIntLe63At5,
    readFlSIntLe63At6,
    readFlSIntLe63At7,
    readFlSIntLe64At0,
    readFlSIntLe64At1,
    readFlSIntLe64At2,
    readFlSIntLe64At3,
    readFlSIntLe64At4,
    readFlSIntLe64At5,
    readFlSIntLe64At6,
    readFlSIntLe64At7,
};

} // namespace
} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_FL_INT_READER_HPP
