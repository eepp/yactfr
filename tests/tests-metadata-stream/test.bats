#!/usr/bin/env bats

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

assert_file_exists() {
  local file="$1"

  if [ ! -f "$file" ]; then
    echo "FATAL: file \`$1\` does not exist" 1>&2
    false
    return
  fi
}

metadata_stream_tester_bin="$testers_path/metadata-stream-tester"

test_metadata_fail() {
  local file="fail-$1"
  local offset="$2"

  assert_file_exists "$file"
  run "$metadata_stream_tester_bin" 0 "$file" "$offset"
  [ $status -eq 2 ]
  run bash -c "$metadata_stream_tester_bin 1 '' "$offset" < $file"
  [ $status -eq 2 ]
}

test_metadata_pass() {
  local file="pass-$1"
  local expected="$2"

  assert_file_exists "$file"
  run "$metadata_stream_tester_bin" 0 "$file"
  [ $status -eq 0 ]
  [ "${lines[0]}" = "$expected" ]
  run bash -c "$metadata_stream_tester_bin 1 '' < $file"
  [ $status -eq 0 ]
  [ "${lines[0]}" = "$expected" ]
}

@test 'good stream with 23 packets' {
  test_metadata_pass 23-packets 'text-size=11633,has-signature=0,packet-count=23,major-version=1,minor-version=8,byte-order=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good stream with an empty packet' {
  test_metadata_pass empty-packet 'text-size=1084,has-signature=0,packet-count=2,major-version=1,minor-version=8,byte-order=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good stream with signature' {
  test_metadata_pass with-signature 'text-size=1084,has-signature=1,packet-count=1,major-version=1,minor-version=8,byte-order=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good stream with signature (big endian)' {
  test_metadata_pass with-signature-be 'text-size=1084,has-signature=1,packet-count=1,major-version=1,minor-version=8,byte-order=be,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good plain text stream' {
  test_metadata_pass text 'text-size=378,has-signature=1'
}

@test 'good plain text stream without signature' {
  test_metadata_pass text-no-sig 'text-size=363,has-signature=0'
}

@test 'ends prematurely: middle of magic' {
  test_metadata_fail ends-magic 90112
}

@test 'ends prematurely: middle of UUID' {
  test_metadata_fail ends-uuid 90116
}

@test 'ends prematurely: middle of checksum' {
  test_metadata_fail ends-checksum 90132
}

@test 'ends prematurely: middle of content size' {
  test_metadata_fail ends-content-size 90136
}

@test 'ends prematurely: middle of packet size' {
  test_metadata_fail ends-packet-size 90140
}

@test 'ends prematurely: before compression scheme' {
  test_metadata_fail ends-compression-scheme 90144
}

@test 'ends prematurely: before encryption scheme' {
  test_metadata_fail ends-encryption-scheme 90145
}

@test 'ends prematurely: before checksum scheme' {
  test_metadata_fail ends-checksum-scheme 90146
}

@test 'ends prematurely: before major version' {
  test_metadata_fail ends-major-version 90147
}

@test 'ends prematurely: before minor version' {
  test_metadata_fail ends-minor-version 90148
}

@test 'ends prematurely: middle of content' {
  test_metadata_fail ends-content 90149
}

@test 'ends prematurely: middle of padding' {
  test_metadata_fail ends-padding 90511
}

@test 'ends prematurely: one packet header' {
  test_metadata_fail ends-one-header 37
}

@test 'ends prematurely: empty file' {
  test_metadata_fail empty 0
}

@test 'packet size is not a multiple of 8' {
  test_metadata_fail packet-size-not-multiple-8 0
}

@test 'content size is not a multiple of 8' {
  test_metadata_fail content-size-not-multiple-8 0
}

@test 'content size < header size' {
  test_metadata_fail content-size-lt-header-size 0
}

@test 'content size > packet size' {
  test_metadata_fail content-size-gt-packet-size 0
}

@test 'wrong major number' {
  test_metadata_fail wrong-major 0
}

@test 'wrong minor number' {
  test_metadata_fail wrong-minor 0
}

@test 'unsupported compression scheme' {
  test_metadata_fail unsupported-compression-scheme 0
}

@test 'unsupported encryption scheme' {
  test_metadata_fail unsupported-encryption-scheme 0
}

@test 'unsupported checksum scheme' {
  test_metadata_fail unsupported-checksum-scheme 0
}

@test 'UUID mismatch' {
  test_metadata_fail uuid-mismatch 4096
}
