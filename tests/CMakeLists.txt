# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_subdirectory (testers)
add_subdirectory (tests-iter-data)
add_subdirectory (tests-iter)
add_subdirectory (tests-iter-pos)
add_subdirectory (tests-pkt-seq)
add_custom_target (
    check
    COMMAND ./test.bash
    DEPENDS
        testers
        tests-iter-data-traces
        tests-iter
        tests-pkt-seq
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running tests"
    VERBATIM
)
