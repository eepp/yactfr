import pytest
import functools


@pytest.fixture
def iter_executor(executor):
    return functools.partial(executor, 'iter')


def test_cmp(iter_executor):
    iter_executor('cmp')


def test_copy_assign(iter_executor):
    iter_executor('copy-assign')


def test_copy_ctor(iter_executor):
    iter_executor('copy-ctor')


def test_move_assign(iter_executor):
    iter_executor('move-assign')


def test_move_ctor(iter_executor):
    iter_executor('move-ctor')


def test_seek_packet(iter_executor):
    iter_executor('seek-packet')
