# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_executable (test-begin EXCLUDE_FROM_ALL test-begin.cpp)
target_link_libraries (test-begin yactfr)

add_executable (test-end EXCLUDE_FROM_ALL test-end.cpp)
target_link_libraries (test-end yactfr)

add_executable (test-at EXCLUDE_FROM_ALL test-at.cpp)
target_link_libraries (test-at yactfr)

include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
)
