# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_executable (test-iter-seek-packet test-seek-packet.cpp)
target_link_libraries (test-iter-seek-packet yactfr)

add_executable (test-iter-copy-ctor test-copy-ctor.cpp)
target_link_libraries (test-iter-copy-ctor yactfr)

add_executable (test-iter-copy-assign test-copy-assign.cpp)
target_link_libraries (test-iter-copy-assign yactfr)

add_executable (test-iter-move-ctor test-move-ctor.cpp)
target_link_libraries (test-iter-move-ctor yactfr)

add_executable (test-iter-move-assign test-move-assign.cpp)
target_link_libraries (test-iter-move-assign yactfr)

add_executable (test-iter-cmp test-cmp.cpp)
target_link_libraries (test-iter-cmp yactfr)

include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
)
