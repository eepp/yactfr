# SPDX-FileCopyrightText: 2018 Philippe Proulx <eepp.ca>
# SPDX-License-Identifier: MIT

add_executable (test-iter-seek-packet EXCLUDE_FROM_ALL test-seek-packet.cpp)
target_link_libraries (test-iter-seek-packet yactfr)

add_executable (test-iter-copy-ctor EXCLUDE_FROM_ALL test-copy-ctor.cpp)
target_link_libraries (test-iter-copy-ctor yactfr)

add_executable (test-iter-copy-assign EXCLUDE_FROM_ALL test-copy-assign.cpp)
target_link_libraries (test-iter-copy-assign yactfr)

add_executable (test-iter-move-ctor EXCLUDE_FROM_ALL test-move-ctor.cpp)
target_link_libraries (test-iter-move-ctor yactfr)

add_executable (test-iter-move-assign EXCLUDE_FROM_ALL test-move-assign.cpp)
target_link_libraries (test-iter-move-assign yactfr)

add_executable (test-iter-cmp EXCLUDE_FROM_ALL test-cmp.cpp)
target_link_libraries (test-iter-cmp yactfr)

include_directories (
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
)

add_custom_target (
    tests-iter
    DEPENDS
        test-iter-cmp
        test-iter-seek-packet
        test-iter-copy-ctor
        test-iter-copy-assign
        test-iter-move-ctor
        test-iter-move-assign
)
