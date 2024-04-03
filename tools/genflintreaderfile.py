# Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

def _func_name(size, at, is_le, is_signed):
    bo = 'Le' if is_le else 'Be'
    sign = 'S' if is_signed else 'U'
    return f'readFl{sign}Int{bo}{size}At{at}'


def _ret_type(is_signed):
    return 'std::int64_t' if is_signed else 'std::uint64_t'


def _gen_algo_le(size, at, bytes):
    # collect all bytes as is except the first one, in reverse order
    for byte in reversed(range(1, bytes)):
        print(f'    res |= buf[{byte}];')

        if byte > 1:
            print('    res <<= 8;')

    # no need to shift with one byte: `res` is still 0
    if bytes > 1:
        # make place for the bits remaining in byte 0 (least significant bits)
        print(f'    res <<= {8 - at};')

    if at == 0:
        # avoid useless shift by 0
        print('    res |= buf[0];')
    else:
        print(f'    res |= (buf[0] >> {at});')


def _gen_algo_be(size, at, bytes):
    top = bytes - 1

    # collect all bytes as is except the last one
    for byte in range(top):
        print(f'    res |= buf[{byte}];')

        if byte < top - 1:
            print('    res <<= 8;')

    # this is the number of unused low bits in the last byte
    sr_len = (8 - size - at) % 8

    # no need to shift with one byte: `res` is still 0
    if bytes > 1:
        # make place for the bits remaining in the last byte
        print(f'    res <<= {8 - sr_len};')

    if sr_len == 0:
        # avoid useless shift by 0
        print(f'    res |= buf[{top}];')
    else:
        print(f'    res |= (buf[{top}] >> {sr_len});')


def _gen_algo(size, at, is_le, is_signed):
    init = f'{_ret_type(is_signed)} {_func_name(size, at, is_le, is_signed)}('
    print(init, end='')
    print('const std::uint8_t * const buf) {')
    print('    std::uint64_t res = 0;')
    print()

    # number of bytes on which our data spans
    bytes = (size + 7 + at) // 8

    if is_le:
        _gen_algo_le(size, at, bytes)
    else:
        _gen_algo_be(size, at, bytes)

    if size < 64:
        # apply a mask to clear garbage most significant bits
        mask_hex = format((1 << size) - 1, 'x')
        print(f'    res &= UINT64_C(0x{mask_hex});')

    if size < 64 and is_signed:
        # add condition to sign-extend if negative
        print()
        print(f'    if (res >> {size - 1}) {{')
        sign_ext_mask = '1' * (64 - size) + '0' * size
        sign_ext_mask_hex = format(int(sign_ext_mask, 2), 'x')
        print(f'        res |= UINT64_C(0x{sign_ext_mask_hex});')
        print('    }')
        print()

    if is_signed:
        ret = 'static_cast<std::int64_t>(res)'
    else:
        ret = 'res'

    print(f'    return {ret};')
    print('}')


def _gen_funcs(is_le, is_signed):
    for size in range(1, 65):
        for at in range(8):
            _gen_algo(size, at, is_le, is_signed)
            print()


def _gen_table(is_le, is_signed):
    bo = 'Le' if is_le else 'Be'
    sign = 'S' if is_signed else 'U'
    name = f'readFl{sign}Int{bo}Funcs'
    print(f'{_ret_type(is_signed)} (*{name}[])(const std::uint8_t *) = {{')

    for size in range(1, 65):
        for at in range(8):
            print(f'    {_func_name(size, at, is_le, is_signed)},')

    print('};')


def _gen_tables():
    _gen_table(False, False)
    print()
    _gen_table(False, True)
    print()
    _gen_table(True, False)
    print()
    _gen_table(True, True)
    print()


if __name__ == '__main__':
    print('''/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_FL_INT_READER_HPP
#define YACTFR_INTERNAL_FL_INT_READER_HPP

#include <cstdint>
#include <cassert>
#include <cstring>

namespace yactfr {
namespace internal {
namespace {
''')
    _gen_funcs(False, False)
    _gen_funcs(False, True)
    _gen_funcs(True, False)
    _gen_funcs(True, True)
    _gen_tables()
    print('''} // namespace
} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_FL_INT_READER_HPP''')
