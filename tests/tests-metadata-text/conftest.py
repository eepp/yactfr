# SPDX-FileCopyrightText: 2015-2026 Philippe Proulx <pproulx@efficios.com>
# SPDX-License-Identifier: MIT

import os
import pytest
import subprocess
import tempfile
import yactfrutils
import moultipart
import pathlib


class _MetadataTextItem(pytest.Item):
    def __init__(self, parent, path):
        super().__init__(parent=parent, name=pathlib.Path(path).name.replace('.', '-'))
        self._path = path

    def runtest(self):
        tester_path = pathlib.Path(os.environ['YACTFR_BINARY_DIR']) / 'tests/testers/metadata-text-tester'

        if pathlib.Path(self._path).name.startswith('pass-'):
            output = subprocess.run([tester_path, self._path],
                                    capture_output=True, text=True,
                                    check=True).stdout.strip('\n')

            if output != '':
                raise yactfrutils.UnexpectedOutput(output, '')

            return

        # expect-to-fail test item: create the real metadata stream file
        # and get the expected lines
        with tempfile.TemporaryDirectory(prefix='pytest-yactfr') as tmp_dir:
            with open(self._path) as f:
                parts = moultipart.parse(f)

            metadata = parts[0].content

            # For CTF 2 (metadata stream starts with a record
            # separator), strip the trailing new line added by
            # `moultipart`: this lets a metadata stream consist of only
            # record separators without trailing characters that the
            # parser would treat as part of a fragment.
            if metadata.startswith('\x1e'):
                metadata = metadata.rstrip('\n')

            yactfrutils.create_text_file('metadata', metadata, tmp_dir)
            output = subprocess.run([tester_path, pathlib.Path(tmp_dir) / 'metadata'],
                                    capture_output=True, text=True,
                                    check=True).stdout.strip('\n')
            expect = parts[1].content.strip('\n')

            if output != expect:
                raise yactfrutils.UnexpectedOutput(output, expect)

    def repr_failure(self, excinfo, style=None):
        exc = excinfo.value

        if isinstance(exc, yactfrutils.UnexpectedOutput):
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
