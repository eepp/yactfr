#!/usr/bin/env bats

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

tests_pkt_seq_path="$build_tests_path/tests-pkt-seq"

@test 'begin' {
  run "$tests_pkt_seq_path/test-begin"
  [ $status -eq 0 ]
}

@test 'end' {
  run "$tests_pkt_seq_path/test-end"
  [ $status -eq 0 ]
}

@test 'at' {
  run "$tests_pkt_seq_path/test-at"
  [ $status -eq 0 ]
}
