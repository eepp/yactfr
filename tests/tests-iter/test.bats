#!/usr/bin/env bats

# Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

tests_iter_path="$build_tests_path/tests-iter"

@test 'element sequence iterator: seek packet' {
  run "$tests_iter_path/test-iter-seek-packet"
  (($status == 0))
}

@test 'copy-construct element sequence iterator' {
  run "$tests_iter_path/test-iter-copy-ctor"
  (($status == 0))
}

@test 'copy-assign element sequence iterator' {
  run "$tests_iter_path/test-iter-copy-assign"
  (($status == 0))
}

@test 'move-construct element sequence iterator' {
  run "$tests_iter_path/test-iter-move-ctor"
  (($status == 0))
}

@test 'move-assign element sequence iterator' {
  run "$tests_iter_path/test-iter-move-assign"
  (($status == 0))
}

@test 'compare element sequence iterator' {
  run "$tests_iter_path/test-iter-cmp"
  (($status == 0))
}
