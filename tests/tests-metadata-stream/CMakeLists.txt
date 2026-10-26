# Copyright (C) 2026 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

add_executable (test-metadata-stream-io-error EXCLUDE_FROM_ALL test-io-error.cpp)
target_link_libraries (test-metadata-stream-io-error yactfr)

include_directories (
    "${CMAKE_SOURCE_DIR}/include"
    ${Boost_INCLUDE_DIRS}
)

add_custom_target (
    tests-metadata-stream
    DEPENDS
        test-metadata-stream-io-error
)
