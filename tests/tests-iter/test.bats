#!/usr/bin/env bats

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

tests_iter_path="$build_tests_path/tests-iter"

@test 'packet sequence iterator: seek packet' {
  run "$tests_iter_path/test-iter-seek-packet"
  [ $status -eq 0 ]
}

@test 'copy-construct packet sequence iterator' {
  run "$tests_iter_path/test-iter-copy-ctor"
  [ $status -eq 0 ]
}

@test 'copy-assign packet sequence iterator' {
  run "$tests_iter_path/test-iter-copy-assign"
  [ $status -eq 0 ]
}

@test 'move-construct packet sequence iterator' {
  run "$tests_iter_path/test-iter-move-ctor"
  [ $status -eq 0 ]
}

@test 'move-assign packet sequence iterator' {
  run "$tests_iter_path/test-iter-move-assign"
  [ $status -eq 0 ]
}

@test 'compare packet sequence iterator' {
  run "$tests_iter_path/test-iter-cmp"
  [ $status -eq 0 ]
}
