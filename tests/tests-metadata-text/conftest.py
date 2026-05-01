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

import os
import os.path
import pytest
import subprocess
import tempfile
import yactfrutils
import moultipart


class _MetadataTextItem(pytest.Item):
    def __init__(self, parent, path):
        self._basename = os.path.basename(path)
        super().__init__(parent=parent, name=self._basename.replace('.', '-'))
        self._path = path

    def runtest(self):
        tester_path = os.path.join(os.environ['YACTFR_BINARY_DIR'], 'tests', 'testers',
                                   'metadata-text-tester')

        if self._basename.startswith('pass-'):
            output = subprocess.check_output([tester_path, self._path], text=True).strip('\n')

            if output != '':
                raise yactfrutils.UnexpectedOutput(output, '')

            return

        # expect-to-fail test item: create the real metadata stream file
        # and get the expected lines
        with tempfile.TemporaryDirectory(prefix='pytest-yactfr') as tmp_dir:
            with open(self._path) as f:
                parts = moultipart.parse(f)

            yactfrutils.create_text_file('metadata', parts[0].content, tmp_dir)
            metadata_stream_path = os.path.join(tmp_dir, 'metadata')
            output = subprocess.check_output([tester_path, metadata_stream_path],
                                             text=True).strip('\n')
            expect = parts[1].content.strip('\n')

            if output != expect:
                raise yactfrutils.UnexpectedOutput(output, expect)

    def repr_failure(self, excinfo, style=None):
        exc = excinfo.value

        if type(exc) is yactfrutils.UnexpectedOutput:
            msg = f'; got:\n\n{exc.output}\n\nExpecting:\n\n{exc.expected}'
        else:
            msg = f': {exc}'

        return f'`{self._path}` failed{msg}'

    def reportinfo(self):
        return self._path, None, self.name


class _MetadataTextFile(pytest.File):
    def collect(self):
        yield _MetadataTextItem.from_parent(self, path=self.path)


def pytest_collect_file(parent, file_path):
    if not file_path.name.startswith('pass-') and not file_path.name.startswith('fail-'):
        # not a metadata text file: don't collect
        return

    # create the file node
    return _MetadataTextFile.from_parent(parent, path=file_path)
