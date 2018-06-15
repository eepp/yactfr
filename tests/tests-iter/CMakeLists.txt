# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

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
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
)
