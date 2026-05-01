# The MIT License (MIT)
#
# Copyright (c) 2015-2026 Philippe Proulx <pproulx@efficios.com>
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

import json
import pytest
import subprocess
import tempfile
import sys
import moultipart
import normand
import difflib
import pathlib
from dataclasses import dataclass


def _metadata(orig_metadata):
    if orig_metadata.strip().startswith('['):
        # CTF 2: convert to JSON text sequence
        frags = json.loads(orig_metadata)
        return '\n'.join('\x1e' + json.dumps(frag, ensure_ascii=False) for frag in frags)
    else:
        # CTF 1: add preamble
        return '''/* CTF 1.8 */

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
''' + orig_metadata


def create_text_file(filename, contents, out_dir_path):
    (pathlib.Path(out_dir_path) / filename).write_text(contents)


def _create_streams(descr_path, out_dir_path):
    with open(descr_path) as f:
        metadata_part, data_part, expect_part = moultipart.parse(f)

    create_text_file('metadata', _metadata(metadata_part.content), out_dir_path)
    (pathlib.Path(out_dir_path) / 'stream').write_bytes(normand.parse(data_part.content).data)
    return expect_part.content


@dataclass(frozen=True)
class UnexpectedOutput(Exception):
    output: str
    expected: str


class _StreamsItem(pytest.Item):
    def __init__(self, parent, path, tester_path):
        super().__init__(parent=parent, name=pathlib.Path(path).stem.replace('.', '-'))
        self._path = path
        self._tester_path = tester_path

    def runtest(self):
        # create a temporary directory to contain the trace
        with tempfile.TemporaryDirectory(prefix='pytest-yactfr') as trace_tmp_dir:
            # create the streams and get the expected lines
            expect = _create_streams(self._path, trace_tmp_dir).strip('\n') + '\n'

            # run the tester and compare to the expected lines
            output = subprocess.run([self._tester_path, trace_tmp_dir],
                                    capture_output=True, text=True,
                                    check=True).stdout.strip('\n') + '\n'

            if output != expect:
                raise UnexpectedOutput(output, expect)

    def repr_failure(self, excinfo, style=None):
        exc = excinfo.value

        if isinstance(exc, UnexpectedOutput):
            msg = f'; got:\n\n{exc.output}\n\n'
            msg += f'Expecting:\n\n{exc.expected}\n\n'
            msg += 'Diff:\n\n'
            msg += ''.join(difflib.unified_diff(exc.output.splitlines(keepends=True),
                                                exc.expected.splitlines(keepends=True),
                                                fromfile='got', tofile='expected'))
        else:
            msg = f': {exc}'

        return f'`{self._path}` failed{msg}'

    def reportinfo(self):
        return self._path, None, self.name


class _StreamsFile(pytest.File):
    def __init__(self, parent, path, tester_path, **kwargs):
        super().__init__(parent=parent, path=path, **kwargs)
        self._tester_path = tester_path

    def collect(self):
        yield _StreamsItem.from_parent(self, path=self.path, tester_path=self._tester_path)


def collect_streams_file(parent, file_path, tester_path):
    if file_path.suffix != '.streams':
        # not a streams file: don't collect
        return

    # create the file node
    return _StreamsFile.from_parent(parent, path=file_path, tester_path=tester_path)


if __name__ == '__main__':
    _create_streams(sys.argv[1], sys.argv[2])
