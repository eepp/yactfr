#!/usr/bin/env bats

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

tests_elem_seq_path="$build_tests_path/tests-elem-seq"

@test 'begin()' {
  run "$tests_elem_seq_path/test-elem-seq-begin"
  (($status == 0))
}

@test 'end()' {
  run "$tests_elem_seq_path/test-elem-seq-end"
  (($status == 0))
}

@test 'at()' {
  run "$tests_elem_seq_path/test-elem-seq-at"
  (($status == 0))
}
