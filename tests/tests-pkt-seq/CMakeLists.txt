# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_executable (test-pkt-seq-begin EXCLUDE_FROM_ALL test-begin.cpp)
target_link_libraries (test-pkt-seq-begin yactfr)

add_executable (test-pkt-seq-end EXCLUDE_FROM_ALL test-end.cpp)
target_link_libraries (test-pkt-seq-end yactfr)

add_executable (test-pkt-seq-at EXCLUDE_FROM_ALL test-at.cpp)
target_link_libraries (test-pkt-seq-at yactfr)

include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
    ${Boost_INCLUDE_DIRS}
)

add_custom_target (
    tests-pkt-seq
    DEPENDS
        test-pkt-seq-begin
        test-pkt-seq-end
        test-pkt-seq-at
)
