# Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

# check for Unix
if (NOT UNIX)
    message (FATAL_ERROR "The yactfr library needs a Unix environment")
endif ()

# yactfr shared library
add_library (
    yactfr SHARED
    data-blk.cpp
    data-src-factory.cpp
    data-src.cpp
    decoding-errors.cpp
    elem-seq-it.cpp
    elem-seq.cpp
    elem-visitor.cpp
    item.cpp
    logging/zf_log.c
    metadata/array-type.cpp
    metadata/blob-type.cpp
    metadata/clk-type.cpp
    metadata/compound-dt.cpp
    metadata/data-loc-map.cpp
    metadata/data-loc.cpp
    metadata/dst.cpp
    metadata/dt-from-pseudo-root-dt.cpp
    metadata/dt.cpp
    metadata/dl-array-type.cpp
    metadata/dl-blob-type.cpp
    metadata/dl-str-type.cpp
    metadata/ert.cpp
    metadata/fl-bit-array-type.cpp
    metadata/fl-bool-type.cpp
    metadata/fl-enum-type.cpp
    metadata/fl-float-type.cpp
    metadata/fl-int-type.cpp
    metadata/int-type-common.cpp
    metadata/metadata-stream.cpp
    metadata/metadata.cpp
    metadata/non-nt-str-type.cpp
    metadata/nt-str-type.cpp
    metadata/opt-type.cpp
    metadata/packetized-metadata-stream.cpp
    metadata/plain-text-metadata-stream.cpp
    metadata/pseudo-types.cpp
    metadata/scalar-dt.cpp
    metadata/sl-array-type.cpp
    metadata/sl-blob-type.cpp
    metadata/sl-str-type.cpp
    metadata/struct-member-type.cpp
    metadata/struct-type.cpp
    metadata/trace-type-from-pseudo-trace-type.cpp
    metadata/trace-type-impl.cpp
    metadata/trace-type.cpp
    metadata/tsdl-attr.cpp
    metadata/tsdl-parser-base.cpp
    metadata/utils.cpp
    metadata/var-type.cpp
    metadata/vl-bit-array-type.cpp
    metadata/vl-enum-type.cpp
    metadata/vl-int-type.cpp
    mmap-file-view-factory-impl.cpp
    mmap-file-view-factory.cpp
    pkt-proc-builder.cpp
    proc.cpp
    text-loc.cpp
    text-parse-error.cpp
    trace-env.cpp
    utils.cpp
    vm.cpp
)
set_target_properties (
    yactfr
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_include_directories (
    yactfr PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

# configure logging
option (
    OPT_ENABLE_LOGGING
    "Enable logging (when in debug mode)"
    OFF
)
target_compile_definitions (
    yactfr PRIVATE
    -DZF_LOG_DEF_SRCLOC=ZF_LOG_SRCLOC_NONE
)

if (OPT_ENABLE_LOGGING)
    message (STATUS "Enabling logging")
    target_compile_definitions (
        yactfr PRIVATE
        -DZF_LOG_LEVEL=ZF_LOG_DEBUG
    )
else ()
    target_compile_definitions (
        yactfr PRIVATE
        -DZF_LOG_LEVEL=ZF_LOG_NONE
    )
endif ()

# library installation rules
install (
    TARGETS yactfr
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
