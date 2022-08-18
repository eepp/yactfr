import os
import os.path
import json
import pytest
import pathlib
import subprocess
import tempfile


def _join_lines(lines):
    return '\n'.join(lines)


def metadata_lines(lines):
    if lines[0].strip().startswith('['):
        # CTF 2: convert to JSON text sequence
        frags = json.loads(_join_lines(lines))
        json_seq_lines = []

        for frag in frags:
            json_seq_lines.append('\x1e' + json.dumps(frag))

        lines = json_seq_lines
    else:
        # CTF 1: add preamble
        lines.insert(0, '''/* CTF 1.8 */

typealias integer { size = 8; } := u8;
typealias integer { size = 16; } := u16;
typealias integer { size = 32; } := u32;
typealias integer { size = 64; } := u64;
typealias integer { size = 8; byte_order = le; } := u8le;
typealias integer { size = 16; byte_order = le; } := u16le;
typealias integer { size = 32; byte_order = le; } := u32le;
typealias integer { size = 64; byte_order = le; } := u64le;
typealias integer { size = 8; byte_order = be; } := u8be;
typealias integer { size = 16; byte_order = be; } := u16be;
typealias integer { size = 32; byte_order = be; } := u32be;
typealias integer { size = 64; byte_order = be; } := u64be;
typealias integer { signed = true; size = 8; } := i8;
typealias integer { signed = true; size = 16; } := i16;
typealias integer { signed = true; size = 32; } := i32;
typealias integer { signed = true; size = 64; } := i64;
typealias integer { signed = true; size = 8; byte_order = le; } := i8le;
typealias integer { signed = true; size = 16; byte_order = le; } := i16le;
typealias integer { signed = true; size = 32; byte_order = le; } := i32le;
typealias integer { signed = true; size = 64; byte_order = le; } := i64le;
typealias integer { signed = true; size = 8; byte_order = be; } := i8be;
typealias integer { signed = true; size = 16; byte_order = be; } := i16be;
typealias integer { signed = true; size = 32; byte_order = be; } := i32be;
typealias integer { signed = true; size = 64; byte_order = be; } := i64be;
''')

    return lines


def split_text_blocks(path):
    with open(path) as f:
        lines = f.read().split('\n')

    sep_indexes = []

    for line_index, line in enumerate(lines):
        if line.strip() == '----':
            sep_indexes.append(line_index)

    if len(sep_indexes) == 0:
        # no separator: single block
        return [lines]

    # start with first block
    blocks = [lines[0:sep_indexes[0]]]

    # append middle blocks
    if len(sep_indexes) >= 2:
        for i in range(0, len(sep_indexes) - 1):
            blocks.append(lines[sep_indexes[i] + 1:sep_indexes[i + 1]])

    # append last block
    blocks.append(lines[sep_indexes[-1] + 1:])
    return blocks


def _split(path):
    blocks = split_text_blocks(path)
    return metadata_lines(blocks[0]), blocks[1], blocks[2]


def create_file_from_lines(filename, lines, out_dir_path):
    with open(os.path.join(out_dir_path, filename), 'w') as f:
        f.write(_join_lines(lines))
        f.write('\n')


def _read_bin_bytes(tbytes, index):
    content = bytearray()
    cur_byte = []

    while True:
        if index == len(tbytes):
            raise RuntimeError('Missing `]` at the end.')

        ch = tbytes[index]

        if ch in '01':
            cur_byte.append(ch)

            if len(cur_byte) == 8:
                cur_byte_str = ''.join(cur_byte)
                byte = int(cur_byte_str, 2)
                content.append(byte)
                cur_byte = []

            index += 1
        elif ch == ']':
            if len(cur_byte) > 0:
                raise RuntimeError('Missing bits before `]`.')

            index += 1
            return index, content
        else:
            index += 1

    if len(cur_byte) > 0:
        raise RuntimeError('Missing bits at the end.')


def _read_str_bytes(tbytes, index):
    content = bytearray()

    while True:
        if index == len(tbytes):
            raise RuntimeError('Missing `"` at the end.')

        ch = tbytes[index]

        if ch == '"':
            index += 1
            return index, content
        else:
            content.append(ord(ch))
            index += 1


def _create_data_stream(lines, out_dir_path):
    content = bytearray()
    tbytes = ''.join(lines)
    last_nibble = None
    index = 0

    while True:
        if index == len(tbytes):
            break

        ch = tbytes[index]

        if ch in '0123456789abcdef':
            if last_nibble is None:
                last_nibble = ch
            else:
                byte = last_nibble + ch
                content.append(int(byte, 16))
                last_nibble = None

            index += 1
        elif ch == '[':
            if last_nibble is not None:
                raise RuntimeError('Missing nibble before `[`.')

            index += 1
            index, bytes = _read_bin_bytes(tbytes, index)
            content += bytes
        elif ch == '"':
            if last_nibble is not None:
                raise RuntimeError('Missing nibble before `"`.')

            index += 1
            index, bytes = _read_str_bytes(tbytes, index)
            content += bytes
        else:
            index += 1

    if last_nibble is not None:
        raise RuntimeError('Missing nibble at the end.')

    with open(os.path.join(out_dir_path, 'stream'), 'wb') as f:
        f.write(content)


def _create_streams(descr_path, out_dir_path):
    metadata_lines, data_lines, expect_lines = _split(descr_path)
    create_file_from_lines('metadata', metadata_lines, out_dir_path)
    _create_data_stream(data_lines, out_dir_path)
    return '\n'.join(expect_lines)


class UnexpectedOutput(RuntimeError):
    def __init__(self, output, expected):
        self._output = output
        self._expected = expected

    @property
    def output(self):
        return self._output

    @property
    def expected(self):
        return self._expected


class _StreamsItem(pytest.Item):
    def __init__(self, parent, path, tester_path):
        name = name=os.path.splitext(os.path.basename(path))[0].replace('.', '-')
        super().__init__(parent=parent, name=name)
        self._path = path
        self._tester_path = tester_path

    def runtest(self):
        # create a temporary directory to contain the trace
        trace_tmp_dir = tempfile.TemporaryDirectory(prefix='pytest-yactfr')

        # create the streams and get the expected lines
        expect = _create_streams(self._path, trace_tmp_dir.name)

        # run the tester, keeping the output
        output = subprocess.check_output([self._tester_path, trace_tmp_dir.name], text=True)

        # compare to the expected lines
        output = output.strip('\n')
        expect = expect.strip('\n')

        if output != expect:
            raise UnexpectedOutput(output, expect)

        # delete temporary directory
        trace_tmp_dir.cleanup()

    def repr_failure(self, excinfo, style=None):
        exc = excinfo.value

        if type(exc) is UnexpectedOutput:
            msg = f'; got:\n\n{exc.output}\n\nExpecting:\n\n{exc.expected}'
        else:
            msg = f': {exc}'

        return f'`{self._path}` failed{msg}'

    def reportinfo(self):
        return self._path, None, self.name


class _StreamsFile(pytest.File):
    def __init__(self, parent, path, tester_path, **kwargs):
        super().__init__(parent=parent, path=path, **kwargs)
        self._tester_path = tester_path

    def collect(self):
        yield _StreamsItem.from_parent(self, path=self.path, tester_path=self._tester_path)


def collect_streams_file(parent, path, tester_path):
    if path.ext != '.streams':
        # not a streams file: don't collect
        return

    # create the file node
    return _StreamsFile.from_parent(parent, path=pathlib.Path(path), tester_path=tester_path)
