import pytest
import functools


@pytest.fixture
def iter_pos_executor(executor):
    return functools.partial(executor, 'iter-pos')


def test_bool(iter_pos_executor):
    iter_pos_executor('bool')


def test_cmp(iter_pos_executor):
    iter_pos_executor('cmp')


def test_restore(iter_pos_executor):
    iter_pos_executor('restore')


def test_copy_assign(iter_pos_executor):
    iter_pos_executor('copy-assign')


def test_copy_ctor(iter_pos_executor):
    iter_pos_executor('copy-ctor')


def test_move_assign(iter_pos_executor):
    iter_pos_executor('move-assign')


def test_move_ctor(iter_pos_executor):
    iter_pos_executor('move-ctor')
