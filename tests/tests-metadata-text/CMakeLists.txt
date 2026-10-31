# Copyright (C) 2026 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_executable (test-metadata-text-num EXCLUDE_FROM_ALL test-num.cpp)
target_link_libraries (test-metadata-text-num yactfr)

add_custom_target (
    tests-metadata-text
    DEPENDS
        test-metadata-text-num
)
