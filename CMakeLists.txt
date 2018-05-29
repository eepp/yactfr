# Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)

# project and version
project (yactfr VERSION 0.1.0)

# packaging stuff
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_SOURCE_GENERATOR TBZ2)
set (CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION}")
set (CPACK_SOURCE_IGNORE_FILES "/build/;/.git/;.gitignore;~$;${CPACK_SOURCE_IGNORE_FILES}")
include (CPack)
add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

# configure compiler globally for C++14
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

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
