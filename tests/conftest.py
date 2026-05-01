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

import pytest
import os
import subprocess
import sys
import pathlib


def _exec(test_dir_suffix, test_bin_suffix):
    test_bin_path = (pathlib.Path(os.environ['YACTFR_BINARY_DIR']) / 'tests' /
                     f'tests-{test_dir_suffix}' /
                     f'test-{test_dir_suffix}-{test_bin_suffix}')
    assert subprocess.call([test_bin_path]) == 0


@pytest.fixture
def executor():
    return _exec


# hackish, but works very well to make some utils available anywhere
sys.path.append(str(pathlib.Path(__file__).parent / 'common'))
