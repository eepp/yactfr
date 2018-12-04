#!/usr/bin/env bash

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

build_dir="$1"

export bats_bin="$(pwd)/bats/bin/bats"
export build_tests_path="$build_dir/tests"
export testers_path="$build_tests_path/testers"

test_dirs=(
  tests-metadata-text
  tests-metadata-stream
  tests-iter-data
  tests-iter
  tests-iter-pos
  tests-elem-seq
)

"$bats_bin" ${test_dirs[*]}
