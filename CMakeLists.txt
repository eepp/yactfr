# Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

cmake_minimum_required (VERSION 3.10.0 FATAL_ERROR)

# project and version
project (yactfr VERSION 0.2.0)

# add target for root documents
add_custom_target (
	rootdocs COMMAND
	asciidoctor ${CMAKE_SOURCE_DIR}/README.adoc ${CMAKE_SOURCE_DIR}/HOWITWORKS.adoc
        -a source-highlighter=coderay -D ${CMAKE_BINARY_DIR}
)

# require C++14
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# current Git hash
if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
    execute_process (
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE YACTFR_GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

# check for Boost (common to the library and to tests)
find_package (Boost 1.58 REQUIRED)

# yacftr library
add_subdirectory (include)
add_subdirectory (yactfr)

# tests
add_subdirectory (tests)

# API docs
option (
    OPT_BUILD_DOC
    "Build and install the HTML API documentation (requires Doxygen)"
    OFF
)

if (OPT_BUILD_DOC)
    add_subdirectory (doc)
endif ()
