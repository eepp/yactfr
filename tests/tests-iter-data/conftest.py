# The MIT License (MIT)
#
# Copyright (c) 2015-2022 Philippe Proulx <pproulx@efficios.com>
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import os
import os.path
import pytest
import re
import subprocess
import tempfile
import pathlib


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
            raise RuntimeError('Missing `]` at the end.')

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
                raise RuntimeError('Missing bits before `]`.')

            index += 1
            return index, content
        else:
            index += 1

    if len(cur_byte) > 0:
        raise RuntimeError('Missing bits at the end.')


def _read_str_bytes(tbytes, index):
    content = bytearray()

    while True:
        if index == len(tbytes):
            raise RuntimeError('Missing `"` at the end.')

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
                raise RuntimeError('Missing nibble before `[`.')

            index += 1
            index, bytes = _read_bin_bytes(tbytes, index)
            content += bytes
        elif ch == '"':
            if last_nibble is not None:
                raise RuntimeError('Missing nibble before `"`.')

            index += 1
            index, bytes = _read_str_bytes(tbytes, index)
            content += bytes
        else:
            index += 1

    if last_nibble is not None:
        raise RuntimeError('Missing nibble at the end.')

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
    _create_data_stream(data_lines, out_dir_path)
    return '\n'.join(expect_lines)


class _StreamsItem(pytest.Item):
    def __init__(self, parent, path):
        super().__init__(parent=parent, name=os.path.splitext(os.path.basename(path))[0])
        self._path = path

    def runtest(self):
        # create a temporary directory to contain the trace
        trace_tmp_dir = tempfile.TemporaryDirectory(prefix='pytest-yactfr')

        # create the streams and get the expected lines
        expect = _create_streams(self._path, trace_tmp_dir.name)

        # run the tester, keeping the output
        tester_path = os.path.join(os.environ['YACTFR_BINARY_DIR'], 'tests', 'testers',
                                   'iter-data-tester')
        output = subprocess.check_output([tester_path, trace_tmp_dir.name], text=True)

        # compare to the expected lines
        assert(output.strip('\n') == expect.strip('\n'))

        # delete temporary directory
        trace_tmp_dir.cleanup()

    def repr_failure(self, excinfo, style=None):
        return f'`{self._path}` failed: {excinfo}.'

    def reportinfo(self):
        return self._path, None, self.name


class _StreamsFile(pytest.File):
    def collect(self):
        yield _StreamsItem.from_parent(self, path=self.path)


def pytest_collect_file(parent, path):
    ext = '.streams'

    if path.ext != ext:
        # not a streams file: don't collect
        return

    # create the file node
    return _StreamsFile.from_parent(parent, path=pathlib.Path(path))
