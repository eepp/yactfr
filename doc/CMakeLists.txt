# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

# generate API documentation with Doxygen
find_package (Doxygen)

if (NOT DOXYGEN_FOUND)
    message (FATAL_ERROR "You need Doxygen to build the API documentation")
endif ()

message (STATUS "API documentation will be built")
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/doc/api)

if (GIT_COMMIT_HASH)
    set (YACTFR_DOC_VERSION "${PROJECT_VERSION} (${YACTFR_GIT_COMMIT_HASH})")
else ()
    set (YACTFR_DOC_VERSION "${PROJECT_VERSION}")
endif ()

configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/api/Doxyfile.in
    ${CMAKE_BINARY_DIR}/doc/api/Doxyfile
    @ONLY
)
set (YACTFR_DOC_WORKDIR "${CMAKE_BINARY_DIR}/doc/api")
set (YACTFR_DOC_CMD "${DOXYGEN_EXECUTABLE}" Doxyfile)
set (YACTFR_DOC_INDEX_HTML "${CMAKE_BINARY_DIR}/doc/api/output/html/index.html")
file (
    GLOB_RECURSE YACTFR_DOC_DEPS
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_SOURCE_DIR}/doc/api/*.dox"
)
add_custom_command (
    OUTPUT "${YACTFR_DOC_INDEX_HTML}"
    COMMAND ${YACTFR_DOC_CMD}
    DEPENDS ${YACTFR_DOC_DEPS}
    WORKING_DIRECTORY "${YACTFR_DOC_WORKDIR}"
    COMMENT "Building API documentation with Doxygen"
    VERBATIM
)
add_custom_target (
    doc ALL DEPENDS "${YACTFR_DOC_INDEX_HTML}"
)
add_custom_target (
    force-doc
    COMMAND ${YACTFR_DOC_CMD}
    WORKING_DIRECTORY "${YACTFR_DOC_WORKDIR}"
    VERBATIM
)
