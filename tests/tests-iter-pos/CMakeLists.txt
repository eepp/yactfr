# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_executable (test-iter-pos-copy-ctor test-copy-ctor.cpp)
target_link_libraries (test-iter-pos-copy-ctor yactfr)

add_executable (test-iter-pos-copy-assign test-copy-assign.cpp)
target_link_libraries (test-iter-pos-copy-assign yactfr)

add_executable (test-iter-pos-move-ctor test-move-ctor.cpp)
target_link_libraries (test-iter-pos-move-ctor yactfr)

add_executable (test-iter-pos-move-assign test-move-assign.cpp)
target_link_libraries (test-iter-pos-move-assign yactfr)

add_executable (test-iter-pos-cmp test-cmp.cpp)
target_link_libraries (test-iter-pos-cmp yactfr)

add_executable (test-iter-pos-restore test-restore.cpp)
target_link_libraries (test-iter-pos-restore yactfr)

add_executable (test-iter-pos-bool test-bool.cpp)
target_link_libraries (test-iter-pos-bool yactfr)

include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
)
