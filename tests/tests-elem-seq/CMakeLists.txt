# SPDX-FileCopyrightText: 2018 Philippe Proulx <eepp.ca>
# SPDX-License-Identifier: MIT

add_executable (test-elem-seq-begin EXCLUDE_FROM_ALL test-begin.cpp)
target_link_libraries (test-elem-seq-begin yactfr)

add_executable (test-elem-seq-end EXCLUDE_FROM_ALL test-end.cpp)
target_link_libraries (test-elem-seq-end yactfr)

add_executable (test-elem-seq-at EXCLUDE_FROM_ALL test-at.cpp)
target_link_libraries (test-elem-seq-at yactfr)

include_directories (
    "${CMAKE_CURRENT_SOURCE_DIR}/../common"
)

add_custom_target (
    tests-elem-seq
    DEPENDS
        test-elem-seq-begin
        test-elem-seq-end
        test-elem-seq-at
)
