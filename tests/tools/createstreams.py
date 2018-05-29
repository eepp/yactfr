# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

import os.path
import re
import sys


def _error(msg):
    print('Error: ' + msg, file=sys.stderr)
    sys.exit(1)


def _split(path):
    with open(path) as f:
        lines = f.read().splitlines()

    split_indexes = []

    for index, line in enumerate(lines):
        if line.strip() == '----':
            split_indexes.append(index)

    metadata_lines = lines[0:split_indexes[0]]
    data_lines = lines[split_indexes[0] + 1:split_indexes[1]]
    expect_lines = lines[split_indexes[1] + 1:]
    return metadata_lines, data_lines, expect_lines


def _create_file_from_lines(filename, lines, out_dir_path):
    with open(os.path.join(out_dir_path, filename), 'w') as f:
        f.write('\n'.join(lines))


def _read_bin_bytes(tbytes, index):
    content = bytearray()
    cur_byte = []

    while True:
        if index == len(tbytes):
            _error('Missing `]` at the end.')

        ch = tbytes[index]

        if ch in '01':
            cur_byte.append(ch)

            if len(cur_byte) == 8:
                cur_byte_str = ''.join(cur_byte)
                byte = int(cur_byte_str, 2)
                content.append(byte)
                cur_byte = []

            index += 1
        elif ch == ']':
            if len(cur_byte) > 0:
                _error('Missing bits before `]`.')

            index += 1
            return index, content
        else:
            index += 1

    if len(cur_byte) > 0:
        _error('Missing bits at the end.')


def _read_str_bytes(tbytes, index):
    content = bytearray()

    while True:
        if index == len(tbytes):
            _error('Missing `"` at the end.')

        ch = tbytes[index]

        if ch == '"':
            index += 1
            return index, content
        else:
            content.append(ord(ch))
            index += 1


def _create_data_stream(lines, out_dir_path):
    content = bytearray()
    tbytes = ''.join(lines)
    last_nibble = None
    index = 0

    while True:
        if index == len(tbytes):
            break

        ch = tbytes[index]

        if ch in '0123456789abcdef':
            if last_nibble is None:
                last_nibble = ch
            else:
                byte = last_nibble + ch
                content.append(int(byte, 16))
                last_nibble = None

            index += 1
        elif ch == '[':
            if last_nibble is not None:
                _error('Missing nibble before `[`.')

            index += 1
            index, bytes = _read_bin_bytes(tbytes, index)
            content += bytes
        elif ch == '"':
            if last_nibble is not None:
                _error('Missing nibble before `"`.')

            index += 1
            index, bytes = _read_str_bytes(tbytes, index)
            content += bytes
        else:
            index += 1

    if last_nibble is not None:
        _error('Missing nibble at the end.')

    with open(os.path.join(out_dir_path, 'stream'), 'wb') as f:
        f.write(content)


def _create_streams(descr_path, out_dir_path):
    metadata_lines, data_lines, expect_lines = _split(descr_path)
    metadata_lines.insert(0, '''/* CTF 1.8 */

typealias integer { size = 8; } := u8;
typealias integer { size = 16; } := u16;
typealias integer { size = 32; } := u32;
typealias integer { size = 64; } := u64;
typealias integer { size = 8; byte_order = le; } := u8le;
typealias integer { size = 16; byte_order = le; } := u16le;
typealias integer { size = 32; byte_order = le; } := u32le;
typealias integer { size = 64; byte_order = le; } := u64le;
typealias integer { size = 8; byte_order = be; } := u8be;
typealias integer { size = 16; byte_order = be; } := u16be;
typealias integer { size = 32; byte_order = be; } := u32be;
typealias integer { size = 64; byte_order = be; } := u64be;
typealias integer { signed = true; size = 8; } := i8;
typealias integer { signed = true; size = 16; } := i16;
typealias integer { signed = true; size = 32; } := i32;
typealias integer { signed = true; size = 64; } := i64;
typealias integer { signed = true; size = 8; byte_order = le; } := i8le;
typealias integer { signed = true; size = 16; byte_order = le; } := i16le;
typealias integer { signed = true; size = 32; byte_order = le; } := i32le;
typealias integer { signed = true; size = 64; byte_order = le; } := i64le;
typealias integer { signed = true; size = 8; byte_order = be; } := i8be;
typealias integer { signed = true; size = 16; byte_order = be; } := i16be;
typealias integer { signed = true; size = 32; byte_order = be; } := i32be;
typealias integer { signed = true; size = 64; byte_order = be; } := i64be;
''')
    _create_file_from_lines('metadata', metadata_lines, out_dir_path)
    _create_file_from_lines('.expect', expect_lines, out_dir_path)
    _create_data_stream(data_lines, out_dir_path)


if __name__ == '__main__':
    _create_streams(sys.argv[1], sys.argv[2])
