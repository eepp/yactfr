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
configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/api/Doxyfile.in
    ${CMAKE_BINARY_DIR}/doc/api/Doxyfile
    @ONLY
)
set (DOC_WORKDIR "${CMAKE_BINARY_DIR}/doc/api")
set (DOC_CMD "${DOXYGEN_EXECUTABLE}" Doxyfile)
add_custom_command (
    OUTPUT "${CMAKE_BINARY_DIR}/doc/api/output/html/index.html"
    COMMAND ${DOC_CMD}
    WORKING_DIRECTORY "${DOC_WORKDIR}"
    COMMENT "Building API documentation with Doxygen"
    VERBATIM
)
add_custom_target (
    doc ALL DEPENDS "${CMAKE_BINARY_DIR}/doc/api/output/html/index.html"
)
add_custom_target (
    force-doc
    COMMAND ${DOC_CMD}
    WORKING_DIRECTORY "${DOC_WORKDIR}"
    VERBATIM
)
