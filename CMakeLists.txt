# Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

cmake_minimum_required (VERSION 3.11.0 FATAL_ERROR)

# project and version
project (yactfr VERSION 0.2.0)

# whether or not yactfr is the top-level project (not a subproject
# added with add_subdirectory() or FetchContent)
if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set (YACTFR_IS_TOP_LEVEL ON)
else ()
    set (YACTFR_IS_TOP_LEVEL OFF)
endif ()

# options
#
# As a subproject, the defaults build a static library to embed into
# the parent project, without tests and installation rules.
option (
    YACTFR_BUILD_SHARED
    "Build yactfr as a shared library instead of a static one"
    ${YACTFR_IS_TOP_LEVEL}
)
option (
    YACTFR_INSTALL
    "Generate the yactfr installation rules"
    ${YACTFR_IS_TOP_LEVEL}
)
option (
    YACTFR_BUILD_TESTS
    "Add the yactfr test targets (excluded from `all`)"
    ${YACTFR_IS_TOP_LEVEL}
)
option (
    OPT_BUILD_DOC
    "Build and install the HTML API documentation (requires Doxygen)"
    OFF
)

# add target for root documents
if (YACTFR_IS_TOP_LEVEL)
    add_custom_target (
        rootdocs COMMAND
        asciidoctor ${PROJECT_SOURCE_DIR}/README.adoc ${PROJECT_SOURCE_DIR}/HOWITWORKS.adoc
            -a source-highlighter=coderay -D ${PROJECT_BINARY_DIR}
    )
endif ()

# require C++17
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# current Git hash
if (EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process (
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE YACTFR_GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

# check for Boost (common to the library and to tests)
find_package (Boost 1.58 REQUIRED)

# standard installation directories
include (GNUInstallDirs)

# yacftr library
add_subdirectory (include)
add_subdirectory (yactfr)

# tests
if (YACTFR_BUILD_TESTS)
    add_subdirectory (tests)
endif ()

# API docs
if (OPT_BUILD_DOC)
    add_subdirectory (doc)
endif ()

# CMake package for find_package()
if (YACTFR_INSTALL)
    include (CMakePackageConfigHelpers)
    set (YACTFR_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/yactfr")
    install (
        EXPORT yactfr-targets
        NAMESPACE yactfr::
        DESTINATION "${YACTFR_CMAKE_INSTALL_DIR}"
    )
    configure_package_config_file (
        cmake/yactfr-config.cmake.in
        "${PROJECT_BINARY_DIR}/yactfr-config.cmake"
        INSTALL_DESTINATION "${YACTFR_CMAKE_INSTALL_DIR}"
    )

    # yactfr 0.x: minor versions may break the API
    write_basic_package_version_file (
        "${PROJECT_BINARY_DIR}/yactfr-config-version.cmake"
        COMPATIBILITY SameMinorVersion
    )
    install (
        FILES
            "${PROJECT_BINARY_DIR}/yactfr-config.cmake"
            "${PROJECT_BINARY_DIR}/yactfr-config-version.cmake"
        DESTINATION "${YACTFR_CMAKE_INSTALL_DIR}"
    )
endif ()
