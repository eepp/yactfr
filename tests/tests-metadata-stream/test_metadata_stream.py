import os
import pytest
import subprocess


_TESTER_PATH = os.path.join(os.environ['YACTFR_BINARY_DIR'], 'tests', 'testers', 'metadata-stream-tester')


def _metadata_stream_path(name):
    return os.path.join(os.path.dirname(__file__), name)


def _exec_fail(name, offset):
    assert(subprocess.call([_TESTER_PATH, '0', _metadata_stream_path(f'fail-{name}'), str(offset)]) == 2)


def _exec_pass(name, expected):
    output = subprocess.check_output([_TESTER_PATH, '0', _metadata_stream_path(f'pass-{name}')],
                                     text=True)
    assert(output.strip() == expected.strip())


@pytest.fixture
def pass_executor():
    return _exec_pass


@pytest.fixture
def fail_executor():
    return _exec_fail


def test_fail_ends_magic(fail_executor):
    fail_executor('ends-magic', 90112)


def test_fail_ends_uuid(fail_executor):
    fail_executor('ends-uuid', 90116)


def test_fail_ends_checksum(fail_executor):
    fail_executor('ends-checksum', 90132)


def test_fail_ends_pkt_content_size(fail_executor):
    fail_executor('ends-pkt-content-size', 90136)


def test_fail_ends_pkt_total_size(fail_executor):
    fail_executor('ends-pkt-total-size', 90140)


def test_fail_ends_compression_scheme(fail_executor):
    fail_executor('ends-compression-scheme', 90144)


def test_fail_ends_encryption_scheme(fail_executor):
    fail_executor('ends-encryption-scheme', 90145)


def test_fail_ends_checksum_scheme(fail_executor):
    fail_executor('ends-checksum-scheme', 90146)


def test_fail_ends_major_version(fail_executor):
    fail_executor('ends-major-version', 90147)


def test_fail_ends_minor_version(fail_executor):
    fail_executor('ends-minor-version', 90148)


def test_fail_ends_content(fail_executor):
    fail_executor('ends-content', 90149)


def test_fail_ends_padding(fail_executor):
    fail_executor('ends-padding', 90511)


def test_fail_ends_one_header(fail_executor):
    fail_executor('ends-one-header', 37)


def test_fail_empty(fail_executor):
    fail_executor('empty', 0)


def test_fail_pkt_total_size_not_multiple_8(fail_executor):
    fail_executor('pkt-total-size-not-multiple-8', 0)


def test_fail_pkt_content_size_not_multiple_8(fail_executor):
    fail_executor('pkt-content-size-not-multiple-8', 0)


def test_fail_pkt_content_size_lt_header_size(fail_executor):
    fail_executor('pkt-content-size-lt-header-size', 0)


def test_fail_pkt_content_size_gt_pkt_size(fail_executor):
    fail_executor('pkt-content-size-gt-pkt-size', 0)


def test_fail_wrong_major(fail_executor):
    fail_executor('wrong-major', 0)


def test_fail_wrong_minor(fail_executor):
    fail_executor('wrong-minor', 0)


def test_fail_unsupported_compression_scheme(fail_executor):
    fail_executor('unsupported-compression-scheme', 0)


def test_fail_unsupported_encryption_scheme(fail_executor):
    fail_executor('unsupported-encryption-scheme', 0)


def test_fail_unsupported_checksum_scheme(fail_executor):
    fail_executor('unsupported-checksum-scheme', 0)


def test_fail_uuid_mismatch(fail_executor):
    fail_executor('uuid-mismatch', 4096)


def test_pass_23_pkts(pass_executor):
  pass_executor('23-pkts', 'text-size=11633,has-ctf-1-signature=0,pkt-count=23,major-version=1,minor-version=8,bo=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d')


def test_pass_empty_pkt(pass_executor):
  pass_executor('empty-pkt', 'text-size=1084,has-ctf-1-signature=0,pkt-count=2,major-version=1,minor-version=8,bo=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d')


def test_pass_with_signature(pass_executor):
  pass_executor('with-signature', 'text-size=1084,has-ctf-1-signature=1,pkt-count=1,major-version=1,minor-version=8,bo=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d')


def test_pass_with_signature_be(pass_executor):
  pass_executor('with-signature-be', 'text-size=1084,has-ctf-1-signature=1,pkt-count=1,major-version=1,minor-version=8,bo=be,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d')


def test_pass_text(pass_executor):
  pass_executor('text', 'text-size=378,has-ctf-1-signature=1')


def test_pass_text_no_sig(pass_executor):
  pass_executor('text-no-sig', 'text-size=363,has-ctf-1-signature=0')
