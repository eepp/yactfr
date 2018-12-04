#!/usr/bin/env bats

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

tests_iter_pos_path="$build_tests_path/tests-iter-pos"

@test 'restore element sequence iterator position' {
  run "$tests_iter_pos_path/test-iter-pos-restore"
  [ $status -eq 0 ]
}

@test 'copy-construct element sequence iterator position' {
  run "$tests_iter_pos_path/test-iter-pos-copy-ctor"
  [ $status -eq 0 ]
}

@test 'copy-assign element sequence iterator position' {
  run "$tests_iter_pos_path/test-iter-pos-copy-assign"
  [ $status -eq 0 ]
}

@test 'move-construct element sequence iterator position' {
  run "$tests_iter_pos_path/test-iter-pos-move-ctor"
  [ $status -eq 0 ]
}

@test 'move-assign element sequence iterator position' {
  run "$tests_iter_pos_path/test-iter-pos-move-assign"
  [ $status -eq 0 ]
}

@test 'compare element sequence iterator position' {
  run "$tests_iter_pos_path/test-iter-pos-cmp"
  [ $status -eq 0 ]
}

@test 'boolean-cast element sequence iterator position' {
  run "$tests_iter_pos_path/test-iter-pos-bool"
  [ $status -eq 0 ]
}
