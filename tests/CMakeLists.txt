# SPDX-FileCopyrightText: 2018-2022 Philippe Proulx <eepp.ca>
# SPDX-License-Identifier: MIT

add_subdirectory (testers)
add_subdirectory (tests-iter)
add_subdirectory (tests-iter-pos)
add_subdirectory (tests-elem-seq)
add_subdirectory (tests-metadata-stream)
add_subdirectory (tests-metadata-text)
add_custom_target (
    tests
    DEPENDS
        testers
        tests-iter
        tests-iter-pos
        tests-elem-seq
        tests-metadata-stream
        tests-metadata-text
    VERBATIM
)
add_custom_target (
    check
    COMMAND
        ${CMAKE_COMMAND} -E env
            "YACTFR_BINARY_DIR=${PROJECT_BINARY_DIR}"
            py.test -v
    DEPENDS
        tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running tests"
    VERBATIM
)
