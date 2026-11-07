# SPDX-FileCopyrightText: 2026 Philippe Proulx <eepp.ca>
# SPDX-License-Identifier: MIT

add_executable (test-metadata-stream-io-error EXCLUDE_FROM_ALL test-io-error.cpp)
target_link_libraries (test-metadata-stream-io-error yactfr)

add_custom_target (
    tests-metadata-stream
    DEPENDS
        test-metadata-stream-io-error
)
