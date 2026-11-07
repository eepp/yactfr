# SPDX-FileCopyrightText: 2015-2026 Philippe Proulx <pproulx@efficios.com>
# SPDX-License-Identifier: MIT

import pytest
import os
import subprocess
import pathlib


def _exec(test_dir_suffix, test_bin_suffix):
    test_bin_path = (pathlib.Path(os.environ['YACTFR_BINARY_DIR']) / 'tests' /
                     f'tests-{test_dir_suffix}' /
                     f'test-{test_dir_suffix}-{test_bin_suffix}')
    assert subprocess.call([test_bin_path]) == 0


@pytest.fixture
def executor():
    return _exec


def pytest_configure(config):
    if not os.environ.get('YACTFR_BINARY_DIR'):
        pytest.exit('`YACTFR_BINARY_DIR` environment variable must be set to the build directory',
                    returncode=pytest.ExitCode.USAGE_ERROR)
