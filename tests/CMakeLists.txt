# Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_subdirectory (testers)
add_subdirectory (tests-iter)
add_subdirectory (tests-iter-pos)
add_subdirectory (tests-elem-seq)
add_custom_target (
    tests
    DEPENDS
        testers
        tests-iter
        tests-iter-pos
        tests-elem-seq
    VERBATIM
)
add_custom_target (
    check
    COMMAND
        ${CMAKE_COMMAND} -E env
            "YACTFR_BINARY_DIR=${CMAKE_BINARY_DIR}"
            py.test -v
    DEPENDS
        tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running tests"
    VERBATIM
)
