#!/usr/bin/env bats

# The MIT License (MIT)
#
# Copyright (c) 2018 Philippe Proulx <eeppeliteloop@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

iter_data_tester_bin="$testers_path/iter-data-tester"

test_iter_data() {
  local trace="$build_tests_path/tests-iter-data/$1"
  local expected_file="$trace/.expect"

  run "$iter_data_tester_bin" "$trace"
  [ $status -eq 0 ]
  run diff -bB - "$expected_file" <<< "$output"
  [ $status -eq 0 ]
}

@test 'align beyond content -> fail' {
  test_iter_data fail-align-beyond-content
}

@test 'align beyond data -> fail' {
  test_iter_data fail-align-beyond-data
}

@test 'array beyond content -> fail' {
  test_iter_data fail-array-beyond-content
}

@test 'array beyond data -> fail' {
  test_iter_data fail-array-beyond-data
}

@test 'BE to LE byte order change within same byte -> fail' {
  test_iter_data fail-be-to-le-change-in-byte
}

@test 'floating point number beyond data -> fail' {
  test_iter_data fail-float-beyond-data
}

@test 'integer beyond content -> fail' {
  test_iter_data fail-int-beyond-content
}

@test 'integer beyond data -> fail' {
  test_iter_data fail-int-beyond-data
}

@test '1-bit integer beyond content -> fail' {
  test_iter_data fail-int-one-bit-beyond-content
}

@test '1-bit integer beyond content -> fail' {
  test_iter_data fail-int-one-bit-beyond-data
}

@test 'LE to BE byte order change within same byte -> fail' {
  test_iter_data fail-le-to-be-change-in-byte
}

@test 'packet content size > packet total size (1) -> fail' {
  test_iter_data fail-packet-content-size-gt-packet-total-size-1
}

@test 'packet content size > packet total size (2) -> fail' {
  test_iter_data fail-packet-content-size-gt-packet-total-size-2
}

@test 'packet content size too small -> fail' {
  test_iter_data fail-packet-content-size-too-small
}

@test 'packet total size not a multiple of 8 -> fail' {
  test_iter_data fail-packet-total-size-not-multiple-eight
}

@test 'packet total size too small -> fail' {
  test_iter_data fail-packet-total-size-too-small
}

@test 'dynamic array beyond content -> fail' {
  test_iter_data fail-dynamic-array-beyond-content
}

@test 'dynamic array beyond data -> fail' {
  test_iter_data fail-dynamic-array-beyond-data
}

@test 'string beyond content -> fail' {
  test_iter_data fail-string-beyond-content
}

@test 'string beyond data -> fail' {
  test_iter_data fail-string-beyond-data
}

@test 'array beyond content -> fail' {
  test_iter_data fail-text-array-beyond-content
}

@test 'text array beyond data -> fail' {
  test_iter_data fail-text-array-beyond-data
}

@test 'text dynamic array beyond content -> fail' {
  test_iter_data fail-text-dynamic-array-beyond-content
}

@test 'text dynamic array beyond data -> fail' {
  test_iter_data fail-text-dynamic-array-beyond-data
}

@test 'unknown data stream type ID -> fail' {
  test_iter_data fail-unknown-dst-id
}

@test 'unknown event record type ID -> fail' {
  test_iter_data fail-unknown-ert-id
}

@test 'variant beyond content -> fail' {
  test_iter_data fail-variant-beyond-content
}

@test 'variant beyond data -> fail' {
  test_iter_data fail-variant-beyond-data
}

@test 'unknown variant tag -> fail' {
  test_iter_data fail-variant-unknown-tag
}

@test 'all basic features (BE) -> pass' {
  test_iter_data pass-all-basic-features-be
}

@test 'all basic features (LE) -> pass' {
  test_iter_data pass-all-basic-features-le
}

@test 'array of empty structures -> pass' {
  test_iter_data pass-array-empty-struct
}

@test 'various arrays -> pass' {
  test_iter_data pass-arrays
}

@test 'clock values -> pass' {
  test_iter_data pass-clock-values
}

@test 'complex arrays -> pass' {
  test_iter_data pass-complex-arrays
}

@test 'data stream ID -> pass' {
  test_iter_data pass-data-stream-id
}

@test 'packet magic number mismatch -> pass' {
  test_iter_data pass-diff-magic
}

@test 'packet UUID mismatch -> pass' {
  test_iter_data pass-diff-uuid
}

@test 'empty data -> pass' {
  test_iter_data pass-empty-data
}

@test 'various floating point numbers -> pass' {
  test_iter_data pass-floats
}

@test 'multiple `id` fields -> pass' {
  test_iter_data pass-multiple-id
}

@test 'multiple `id` fields within array -> pass' {
  test_iter_data pass-multiple-id-in-array
}

@test 'multiple `stream_id` fields -> pass' {
  test_iter_data pass-multiple-stream-id
}

@test 'no events, no `stream_id` field -> pass' {
  test_iter_data pass-no-events-no-stream-id
}

@test 'no events with `stream_id` field -> pass' {
  test_iter_data pass-no-events-with-stream-id
}

@test 'various odd integers -> pass' {
  test_iter_data pass-odd-ints
}

@test 'various odd enumerations -> pass' {
  test_iter_data pass-odd-enums
}

@test 'various standard integers -> pass' {
  test_iter_data pass-std-ints
}

@test 'various standard enumerations -> pass' {
  test_iter_data pass-std-enums
}

@test 'packet content size without packet total size -> pass' {
  test_iter_data pass-packet-content-size-no-packet-total-size
}

@test 'packet origin index -> pass' {
  test_iter_data pass-packet-origin-index
}

@test 'packet total size without packet content size -> pass' {
  test_iter_data pass-packet-total-size-no-packet-content-size
}

@test 'dynamic array of empty structures -> pass' {
  test_iter_data pass-dynamic-array-empty-struct
}

@test 'various dynamic arrays -> pass' {
  test_iter_data pass-dynamic-arrays
}

@test 'string alignment -> pass' {
  test_iter_data pass-string-alignment
}

@test 'various text arrays -> pass' {
  test_iter_data pass-text-arrays
}

@test 'various text dynamic arrays -> pass' {
  test_iter_data pass-text-dynamic-arrays
}

@test 'various variants -> pass' {
  test_iter_data pass-variants
}
