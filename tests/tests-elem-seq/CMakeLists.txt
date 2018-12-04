# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_executable (test-elem-seq-begin EXCLUDE_FROM_ALL test-begin.cpp)
target_link_libraries (test-elem-seq-begin yactfr)

add_executable (test-elem-seq-end EXCLUDE_FROM_ALL test-end.cpp)
target_link_libraries (test-elem-seq-end yactfr)

add_executable (test-elem-seq-at EXCLUDE_FROM_ALL test-at.cpp)
target_link_libraries (test-elem-seq-at yactfr)

include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
    ${Boost_INCLUDE_DIRS}
)

add_custom_target (
    tests-elem-seq
    DEPENDS
        test-elem-seq-begin
        test-elem-seq-end
        test-elem-seq-at
)
