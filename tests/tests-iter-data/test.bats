#!/usr/bin/env bats

# Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

iter_data_tester_bin="$testers_path/iter-data-tester"

test_iter_data() {
  local trace="$build_tests_path/tests-iter-data/$1"
  local expected_file="$trace/.expect"

  run "$iter_data_tester_bin" "$trace"
  (($status == 0))
  run diff -bB - "$expected_file" <<< "$output"
  (($status == 0))
}

#   __       _ _
#  / _| __ _(_) |
# | |_ / _` | | |
# |  _| (_| | | |
# |_|  \__,_|_|_|

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

@test '1-bit integer beyond data -> fail' {
  test_iter_data fail-int-one-bit-beyond-data
}

@test 'LE to BE byte order change within same byte -> fail' {
  test_iter_data fail-le-to-be-change-in-byte
}

@test 'packet content length > packet total length (1) -> fail' {
  test_iter_data fail-pkt-content-len-gt-pkt-total-len-1
}

@test 'packet content length > packet total length (2) -> fail' {
  test_iter_data fail-pkt-content-len-gt-pkt-total-len-2
}

@test 'packet content length too small -> fail' {
  test_iter_data fail-pkt-content-len-too-small
}

@test 'packet total length not a multiple of 8 -> fail' {
  test_iter_data fail-pkt-total-len-not-multiple-eight
}

@test 'packet total length too small -> fail' {
  test_iter_data fail-pkt-total-len-too-small
}

@test 'dynamic array beyond content -> fail' {
  test_iter_data fail-dyn-array-beyond-content
}

@test 'dynamic array beyond data -> fail' {
  test_iter_data fail-dyn-array-beyond-data
}

@test 'string beyond content -> fail' {
  test_iter_data fail-str-beyond-content
}

@test 'string beyond data -> fail' {
  test_iter_data fail-str-beyond-data
}

@test 'static text array beyond content -> fail' {
  test_iter_data fail-static-text-array-beyond-content
}

@test 'static text array beyond data -> fail' {
  test_iter_data fail-static-text-array-beyond-data
}

@test 'dynamic text array beyond content -> fail' {
  test_iter_data fail-dyn-text-array-beyond-content
}

@test 'dynamic text array beyond data -> fail' {
  test_iter_data fail-dyn-text-array-beyond-data
}

@test 'unknown data stream type ID -> fail' {
  test_iter_data fail-unknown-dst-id
}

@test 'unknown event record type ID -> fail' {
  test_iter_data fail-unknown-ert-id
}

@test 'variant beyond content -> fail' {
  test_iter_data fail-var-beyond-content
}

@test 'variant beyond data -> fail' {
  test_iter_data fail-var-beyond-data
}

@test 'invalid variant selector -> fail' {
  test_iter_data fail-var-inval-sel
}

#  _ __   __ _ ___ ___
# | '_ \ / _` / __/ __|
# | |_) | (_| \__ \__ \
# | .__/ \__,_|___/___/
# |_|

@test 'all basic features (BE) -> pass' {
  test_iter_data pass-all-basic-features-be
}

@test 'all basic features (LE) -> pass' {
  test_iter_data pass-all-basic-features-le
}

@test 'array of empty structures -> pass' {
  test_iter_data pass-array-empty-structs
}

@test 'various arrays -> pass' {
  test_iter_data pass-arrays
}

@test 'clock values -> pass' {
  test_iter_data pass-clk-vals
}

@test 'implicit default clock timestamp role -> pass' {
  test_iter_data pass-implicit-def-clk-ts-role
}

@test 'complex arrays -> pass' {
  test_iter_data pass-complex-arrays
}

@test 'data stream ID -> pass' {
  test_iter_data pass-dst
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

@test 'multiple `id` integers -> pass' {
  test_iter_data pass-multiple-ert-id-ints
}

@test 'multiple `stream_id` integers -> pass' {
  test_iter_data pass-multiple-dst-id-ints
}

@test 'no event records, no `stream_id` field -> pass' {
  test_iter_data pass-no-ers-no-dst-id-ints
}

@test 'no event records, with `stream_id` field -> pass' {
  test_iter_data pass-no-ers-with-dst-id
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

@test 'packet content length without packet total length -> pass' {
  test_iter_data pass-pkt-content-len-no-pkt-total-len
}

@test 'packet origin index -> pass' {
  test_iter_data pass-pkt-origin-index
}

@test 'packet total length without packet content length -> pass' {
  test_iter_data pass-pkt-total-len-no-pkt-content-len
}

@test 'dynamic array of empty structures -> pass' {
  test_iter_data pass-dyn-array-empty-structs
}

@test 'various dynamic arrays -> pass' {
  test_iter_data pass-dyn-arrays
}

@test 'dynamic array: multiple possible lengths -> pass' {
  test_iter_data pass-dyn-array-multi-len
}

@test 'string alignment -> pass' {
  test_iter_data pass-str-align
}

@test 'various static text arrays -> pass' {
  test_iter_data pass-static-text-arrays
}

@test 'various dynamic text arrays -> pass' {
  test_iter_data pass-dyn-text-arrays
}

@test 'various variants -> pass' {
  test_iter_data pass-vars
}

@test 'packet header: string named `magic` -> pass' {
  test_iter_data pass-vars pass-pkt-header-magic-str
}

@test 'packet header: string named `uuid` -> pass' {
  test_iter_data pass-vars pass-pkt-header-uuid-str
}

@test 'packet header: array of strings named `uuid` -> pass' {
  test_iter_data pass-vars pass-pkt-header-uuid-array-of-strs
}

@test 'packet header: string named `stream_id` -> pass' {
  test_iter_data pass-vars pass-pkt-header-stream-id-str
}

@test 'packet header: string named `stream_instance_id` -> pass' {
  test_iter_data pass-vars pass-pkt-header-stream-instance-id-str
}

@test 'packet context: string named `packet_size` -> pass' {
  test_iter_data pass-vars pass-pkt-ctx-pkt-size-str
}

@test 'packet context: string named `content_size` -> pass' {
  test_iter_data pass-vars pass-pkt-ctx-content-size-str
}

@test 'event record header: string named `id` -> pass' {
  test_iter_data pass-vars pass-er-header-id-str
}
