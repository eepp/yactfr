# SPDX-FileCopyrightText: 2015-2026 Philippe Proulx <pproulx@efficios.com>
# SPDX-License-Identifier: MIT

import os
import yactfrutils
import pathlib


def pytest_collect_file(parent, file_path):
    tester_path = pathlib.Path(os.environ['YACTFR_BINARY_DIR']) / 'tests/testers/iter-data-tester'
    return yactfrutils.collect_streams_file(parent, file_path, tester_path)
