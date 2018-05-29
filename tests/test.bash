#!/usr/bin/env bash

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

test_dirs=(
  tests-metadata-text
  tests-metadata-stream
  tests-iter-data
  tests-iter
  tests-iter-pos
  tests-pkt-seq
)

export bats_bin="$(pwd)/bats/bin/bats"
export build_tests_path="$(pwd)/../build/tests"
export testers_path="$build_tests_path/testers"

rc=0

for d in ${test_dirs[@]}; do
  pushd $d > /dev/null
  "$bats_bin" $@ .
  bats_rc=$?

  if [ $bats_rc -ne 0 ]; then
    # latch error, but continue other tests
    rc=1
  fi

  popd > /dev/null
done

exit $rc
