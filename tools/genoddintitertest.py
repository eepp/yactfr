# Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

import random
from collections import namedtuple


def _value_to_bits(value, size):
    bits = format(abs(value), 'b')
    bits = '0' * (size - len(bits)) + bits

    if value < 0:
        comp_bits = ''

        for bit in bits:
            comp_bits += '1' if bit == '0' else '0'

        comp_value = int(comp_bits, 2)
        comp_value += 1
        bits = format(comp_value, 'b')

    assert(len(bits) == size)
    return bits


def _gen_bytes_le(at, size, value):
    bytes = []
    byte = '1' * at
    assert(len(byte) < 8)
    bits = _value_to_bits(value, size)

    for bit in reversed(bits):
        byte = bit + byte

        if len(byte) == 8:
            bytes.append(byte)
            byte = ''

    if len(byte) > 0:
        byte = '1' * (8 - len(byte)) + byte
        bytes.append(byte)

    return bytes


def _gen_bytes_be(at, size, value):
    bytes = []
    byte = '1' * at
    assert(len(byte) < 8)
    bits = _value_to_bits(value, size)

    for bit in bits:
        byte += bit

        if len(byte) == 8:
            bytes.append(byte)
            byte = ''

    if len(byte) > 0:
        byte += '1' * (8 - len(byte))
        bytes.append(byte)

    return bytes


def _gen_bytes(is_le, at, size, value):
    if is_le:
        bytes = _gen_bytes_le(at, size, value)
    else:
        bytes = _gen_bytes_be(at, size, value)

    return ' '.join(bytes)


def _gen_int_meta(at, size, is_le, is_signed):
    bo = 'byte_order = le;' if is_le else 'byte_order = be;'
    signed = 'signed = true;' if is_signed else 'signed = false;'
    line = 'struct { '

    if at > 0:
        line += f'integer {{ align = 1; size = {at}; {bo} {signed} }} pad; '

    line += f'integer {{ align = 1; size = {size}; {bo} {signed} }} int;'
    line += ' } align(8)'
    return line


def _get_value(size, is_signed):
    if is_signed:
        range_min = -(2**(size - 1))
        range_max = 2**(size - 1) - 1
    else:
        range_min = 0
        range_max = 2**size - 1

    return random.randint(range_min, range_max)


def _gen_meta(int_meta_lines):
    meta = '''trace {
    major = 1;
    minor = 8;
    byte_order = le; // not used here
};

event {
    name = test;
    fields := struct {
'''

    for line in int_meta_lines:
        meta += f'        {line}\n'

    meta += '''        struct {} align(8) pad;
    };
};'''
    return meta


def _gen_data(data_lines):
    data = '[\n'

    for line in data_lines:
        data += f'    {line}\n'

    data += ']'
    return data


def _gen_expect(expect_infos):
    expect = '''     0 PB
     0   PCB
     0     DST:0
     0     ERB
     0       ERT:0:test
     0       SCB:5
     0         STB
'''
    offset = 0

    for info in expect_infos:
        if info.is_signed:
            pref = 'I'
        else:
            pref = 'U'

        expect += f'{offset: >6}           STB:{info.name}\n'

        if info.at > 0:
            if info.is_signed:
                pad_value = -1
            else:
                pad_value = 2**info.at - 1

            expect += f'{offset: >6}             {pref}:pad:{pad_value}\n'
            offset += info.at

        expect += f'{offset: >6}             {pref}:int:{info.value}\n'
        offset += info.size
        expect += f'{offset: >6}           STE\n'
        offset = ((offset) + 7) & ~7

    expect += f'''{offset: >6}           STB:pad
{offset: >6}           STE
{offset: >6}         STE
{offset: >6}       SCE
{offset: >6}     ERE
{offset: >6}   PCE
{offset: >6} PE'''
    return expect


_ExpectInfo = namedtuple('_ExpectInfo', ['is_signed', 'size', 'at', 'name', 'value'])


def _gen():
    random.seed(23)
    int_meta_lines = []
    expect_infos = []
    data_lines = []

    for is_le in (True, False):
        bo = 'le' if is_le else 'be'

        for is_signed in (True, False):
            sign = 'i' if is_signed else 'u'

            for size in range(1, 65):
                for at in range(0, 8):
                    name = f'{sign}{bo}{size}at{at}'

                    # meta
                    int_meta_line = _gen_int_meta(at, size, is_le, is_signed)
                    int_meta_line += f' {name};'
                    int_meta_lines.append(int_meta_line)

                    # expect
                    value = _get_value(size, is_signed)
                    expect_infos.append(_ExpectInfo(is_signed, size, at, name,
                                                    value))

                    # data
                    data_lines.append(_gen_bytes(is_le, at, size, value))

    print(_gen_meta(int_meta_lines))
    print('----')
    print(_gen_data(data_lines))
    print('----')
    print(_gen_expect(expect_infos))


if __name__ == '__main__':
    _gen()
