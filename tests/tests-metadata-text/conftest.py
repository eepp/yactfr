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
import subprocess
import pathlib
import tempfile
import yactfrutils


class _MetadataTextItem(pytest.Item):
    def __init__(self, parent, path):
        self._basename = os.path.basename(path)
        super().__init__(parent=parent, name=self._basename.replace('.', '-'))
        self._path = path

    def runtest(self):
        tmp_dir = None
        metadata_stream_path = self._path

        # if this is an expect-to-fail test item, then create the real
        # metadata stream file and get the expected lines
        expect_to_pass = self._basename.startswith('pass-')

        if not expect_to_pass:
            # create a temporary directory to contain the metadata stream file
            tmp_dir = tempfile.TemporaryDirectory(prefix='pytest-yactfr')

            # get the metadata stream file and expected output lines
            blocks = yactfrutils.split_text_blocks(self._path)

            # create the metadata stream file
            yactfrutils.create_file_from_lines('metadata', blocks[0], tmp_dir.name)
            metadata_stream_path = os.path.join(tmp_dir.name, 'metadata')

        # run the tester, keeping the output on success
        tester_path = os.path.join(os.environ['YACTFR_BINARY_DIR'], 'tests', 'testers',
                                   'metadata-text-tester')
        output = subprocess.check_output([tester_path, metadata_stream_path], text=True)

        # compare to the expected lines
        output = output.strip('\n')

        if expect_to_pass:
            expect = ''
        else:
            expect = '\n'.join(blocks[1]).strip('\n')

        if output != expect:
            raise yactfrutils.UnexpectedOutput(output, expect)

        # delete temporary directory, if any
        if tmp_dir is not None:
            #tmp_dir.cleanup()
            pass

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


def pytest_collect_file(parent, path):
    basename = os.path.basename(path)

    if not basename.startswith('pass-') and not basename.startswith('fail-'):
        # not a metadata text file: don't collect
        return

    # create the file node
    return _MetadataTextFile.from_parent(parent, path=pathlib.Path(path))
