# SPDX-FileCopyrightText: 2026 Philippe Proulx <eepp.ca>
# SPDX-License-Identifier: MIT

add_executable (test-metadata-text-num EXCLUDE_FROM_ALL test-num.cpp)
target_link_libraries (test-metadata-text-num yactfr)

add_custom_target (
    tests-metadata-text
    DEPENDS
        test-metadata-text-num
)
