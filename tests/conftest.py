import pytest
import os
import os.path
import subprocess
import sys


def _exec(test_dir_suffix, test_bin_suffix):
    test_bin_path = os.path.join(os.environ['YACTFR_BINARY_DIR'], 'tests',
                                 f'tests-{test_dir_suffix}',
                                 f'test-{test_dir_suffix}-{test_bin_suffix}')
    assert(subprocess.call([test_bin_path]) == 0)


@pytest.fixture
def executor():
    return _exec


# hackish, but works very well to make some utils available anywhere
sys.path.append(os.path.join(os.path.dirname(__file__), 'common'))
