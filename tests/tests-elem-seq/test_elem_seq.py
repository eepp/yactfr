# SPDX-FileCopyrightText: 2022 Philippe Proulx <pproulx@efficios.com>
# SPDX-License-Identifier: MIT

import pytest
import functools


@pytest.fixture
def elem_seq_executor(executor):
    return functools.partial(executor, 'elem-seq')


def test_at(elem_seq_executor):
    elem_seq_executor('at')


def test_begin(elem_seq_executor):
    elem_seq_executor('begin')


def test_end(elem_seq_executor):
    elem_seq_executor('end')
