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

@test 'static-length array beyond content -> fail' {
  test_iter_data fail-sl-array-beyond-content
}

@test 'static-length array beyond data -> fail' {
  test_iter_data fail-sl-array-beyond-data
}

@test 'BE to LE byte order change within same byte -> fail' {
  test_iter_data fail-be-to-le-change-in-byte
}

@test 'fixed-length floating point number beyond data -> fail' {
  test_iter_data fail-fl-float-beyond-data
}

@test 'fixed-length integer beyond content -> fail' {
  test_iter_data fail-fl-int-beyond-content
}

@test 'fixed-length integer beyond data -> fail' {
  test_iter_data fail-fl-int-beyond-data
}

@test '1-bit fixed-length integer beyond content -> fail' {
  test_iter_data fail-fl-int-one-bit-beyond-content
}

@test '1-bit fixed-length integer beyond data -> fail' {
  test_iter_data fail-fl-int-one-bit-beyond-data
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

@test 'dynamic-length array beyond content -> fail' {
  test_iter_data fail-dl-array-beyond-content
}

@test 'dynamic-length array beyond data -> fail' {
  test_iter_data fail-dl-array-beyond-data
}

@test 'null-terminated string beyond content -> fail' {
  test_iter_data fail-nt-str-beyond-content
}

@test 'null-terminated string beyond data -> fail' {
  test_iter_data fail-nt-str-beyond-data
}

@test 'static-length string beyond content -> fail' {
  test_iter_data fail-sl-str-beyond-content
}

@test 'static-length string beyond data -> fail' {
  test_iter_data fail-sl-str-beyond-data
}

@test 'dynamic-length string beyond content -> fail' {
  test_iter_data fail-dl-str-beyond-content
}

@test 'dynamic-length string beyond data -> fail' {
  test_iter_data fail-dl-str-beyond-data
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

@test 'static-length array of empty structures -> pass' {
  test_iter_data pass-sl-array-empty-structs
}

@test 'various static-length arrays -> pass' {
  test_iter_data pass-sl-arrays
}

@test 'clock values -> pass' {
  test_iter_data pass-clk-vals
}

@test 'implicit default clock timestamp role -> pass' {
  test_iter_data pass-implicit-def-clk-ts-role
}

@test 'complex static-length arrays -> pass' {
  test_iter_data pass-complex-sl-arrays
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

@test 'various fixed-length floating point numbers -> pass' {
  test_iter_data pass-fl-floats
}

@test 'multiple `id` fixed-length integers -> pass' {
  test_iter_data pass-multiple-ert-id-fl-ints
}

@test 'multiple `stream_id` fixed-length integers -> pass' {
  test_iter_data pass-multiple-dst-id-fl-ints
}

@test 'no event records, no `stream_id` fixed-length integers -> pass' {
  test_iter_data pass-no-ers-no-dst-id-fl-ints
}

@test 'no event records, with `stream_id` fixed-length integers -> pass' {
  test_iter_data pass-no-ers-with-dst-id-fl-ints
}

@test 'various odd fixed-length integers -> pass' {
  test_iter_data pass-odd-fl-ints
}

@test 'various odd fixed-length enumerations -> pass' {
  test_iter_data pass-odd-fl-enums
}

@test 'various standard fixed-length integers -> pass' {
  test_iter_data pass-std-fl-ints
}

@test 'various standard fixed-length enumerations -> pass' {
  test_iter_data pass-std-fl-enums
}

@test 'packet content length without packet total length -> pass' {
  test_iter_data pass-pkt-content-len-no-pkt-total-len
}

@test 'packet sequence number -> pass' {
  test_iter_data pass-pkt-seq-num
}

@test 'packet total length without packet content length -> pass' {
  test_iter_data pass-pkt-total-len-no-pkt-content-len
}

@test 'dynamic-length array of empty structures -> pass' {
  test_iter_data pass-dl-array-empty-structs
}

@test 'various dynamic-length arrays -> pass' {
  test_iter_data pass-dl-arrays
}

@test 'dynamic-length array: multiple possible lengths -> pass' {
  test_iter_data pass-dl-array-multi-len
}

@test 'null-terminated string alignment -> pass' {
  test_iter_data pass-nt-str-align
}

@test 'various static-length strings -> pass' {
  test_iter_data pass-sl-strs
}

@test 'various dynamic-length strings -> pass' {
  test_iter_data pass-dl-strs
}

@test 'various variants -> pass' {
  test_iter_data pass-vars
}

@test 'packet header: null-terminated string named `magic` -> pass' {
  test_iter_data pass-vars pass-pkt-header-magic-nt-str
}

@test 'packet header: null-terminated string named `uuid` -> pass' {
  test_iter_data pass-vars pass-pkt-header-uuid-nt-str
}

@test 'packet header: static-length array of null-terminated strings named `uuid` -> pass' {
  test_iter_data pass-vars pass-pkt-header-uuid-sl-array-of-nt-strs
}

@test 'packet header: null-terminated string named `stream_id` -> pass' {
  test_iter_data pass-vars pass-pkt-header-stream-id-nt-str
}

@test 'packet header: null-terminated string named `stream_instance_id` -> pass' {
  test_iter_data pass-vars pass-pkt-header-stream-instance-id-nt-str
}

@test 'packet context: null-terminated string named `packet_size` -> pass' {
  test_iter_data pass-vars pass-pkt-ctx-pkt-size-nt-str
}

@test 'packet context: null-terminated string named `content_size` -> pass' {
  test_iter_data pass-vars pass-pkt-ctx-content-size-nt-str
}

@test 'event record header: null-terminated string named `id` -> pass' {
  test_iter_data pass-vars pass-er-header-id-nt-str
}
