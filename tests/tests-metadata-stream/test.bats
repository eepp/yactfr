#!/usr/bin/env bats

# Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

assert_file_exists() {
  local file="$1"

  if [[ ! -f "$BATS_TEST_DIRNAME/$file" ]]; then
    echo "FATAL: file \`$1\` does not exist" 1>&2
    return 1
  fi
}

metadata_stream_tester_bin="$testers_path/metadata-stream-tester"

test_metadata_fail() {
  local file="fail-$1"
  local abs_file="$BATS_TEST_DIRNAME/$file"
  local offset=$2

  assert_file_exists "$file"
  run "$metadata_stream_tester_bin" 0 "$abs_file" "$offset"
  (($status == 2))
  run bash -c "$metadata_stream_tester_bin 1 '' "$offset" < $abs_file"
  (($status == 2))
}

test_metadata_pass() {
  local file="pass-$1"
  local abs_file="$BATS_TEST_DIRNAME/$file"
  local expected=$2

  assert_file_exists "$file"
  run "$metadata_stream_tester_bin" 0 "$abs_file"
  (($status == 0))
  [[ "${lines[0]}" = "$expected" ]]
  run bash -c "$metadata_stream_tester_bin 1 '' < $abs_file"
  (($status == 0))
  [[ "${lines[0]}" = "$expected" ]]
}

#   __       _ _
#  / _| __ _(_) |
# | |_ / _` | | |
# |  _| (_| | | |
# |_|  \__,_|_|_|

@test 'ends prematurely: middle of magic datum' {
  test_metadata_fail ends-magic 90112
}

@test 'ends prematurely: middle of UUID datum' {
  test_metadata_fail ends-uuid 90116
}

@test 'ends prematurely: middle of checksum datum' {
  test_metadata_fail ends-checksum 90132
}

@test 'ends prematurely: middle of packet content length datum' {
  test_metadata_fail ends-pkt-content-size 90136
}

@test 'ends prematurely: middle of packet total size datum' {
  test_metadata_fail ends-pkt-total-size 90140
}

@test 'ends prematurely: before compression scheme datum' {
  test_metadata_fail ends-compression-scheme 90144
}

@test 'ends prematurely: before encryption scheme datum' {
  test_metadata_fail ends-encryption-scheme 90145
}

@test 'ends prematurely: before checksum scheme datum' {
  test_metadata_fail ends-checksum-scheme 90146
}

@test 'ends prematurely: before major version datum' {
  test_metadata_fail ends-major-version 90147
}

@test 'ends prematurely: before minor version datum' {
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

@test 'packet total size is not a multiple of 8' {
  test_metadata_fail pkt-total-size-not-multiple-8 0
}

@test 'packet content length is not a multiple of 8' {
  test_metadata_fail pkt-content-size-not-multiple-8 0
}

@test 'packet content length < packet header size' {
  test_metadata_fail pkt-content-size-lt-header-size 0
}

@test 'packet content length > packet total size' {
  test_metadata_fail pkt-content-size-gt-pkt-size 0
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

#  _ __   __ _ ___ ___
# | '_ \ / _` / __/ __|
# | |_) | (_| \__ \__ \
# | .__/ \__,_|___/___/
# |_|

@test 'good stream with 23 packets' {
  test_metadata_pass 23-pkts 'text-size=11633,has-signature=0,pkt-count=23,major-version=1,minor-version=8,bo=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good stream with an empty packet' {
  test_metadata_pass empty-pkt 'text-size=1084,has-signature=0,pkt-count=2,major-version=1,minor-version=8,bo=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good stream with signature' {
  test_metadata_pass with-signature 'text-size=1084,has-signature=1,pkt-count=1,major-version=1,minor-version=8,bo=le,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good stream with signature (big-endian)' {
  test_metadata_pass with-signature-be 'text-size=1084,has-signature=1,pkt-count=1,major-version=1,minor-version=8,bo=be,uuid=a560bbc4-7f93-b346-a980-3959745a0f5d'
}

@test 'good plain text stream' {
  test_metadata_pass text 'text-size=378,has-signature=1'
}

@test 'good plain text stream without signature' {
  test_metadata_pass text-no-sig 'text-size=363,has-signature=0'
}

