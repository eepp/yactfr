# Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

# check for Unix
if (NOT UNIX)
    message (FATAL_ERROR "yactfr library needs a Unix environment")
endif ()

# check for Boost
find_package (Boost 1.58 REQUIRED)

# yactfr library
add_library (
    yactfr SHARED
    metadata/array-sequence-type-base.cpp
    metadata/array-type.cpp
    metadata/bit-array-type.cpp
    metadata/clock-type.cpp
    metadata/compound-type.cpp
    metadata/data-stream-type.cpp
    metadata/data-type-visitor.cpp
    metadata/data-type.cpp
    metadata/event-record-type.cpp
    metadata/field-ref.cpp
    metadata/field-resolver.cpp
    metadata/field-resolver.hpp
    metadata/float-type.cpp
    metadata/int-type.cpp
    metadata/io.cpp
    metadata/metadata-parse-error.cpp
    metadata/metadata-stream.cpp
    metadata/metadata-text-location.cpp
    metadata/metadata.cpp
    metadata/named-data-type.cpp
    metadata/packetized-metadata-stream.cpp
    metadata/plain-text-metadata-stream.cpp
    metadata/scalar-type.cpp
    metadata/sequence-type.cpp
    metadata/string-type.cpp
    metadata/struct-type-field.cpp
    metadata/struct-type.cpp
    metadata/text-array-type.cpp
    metadata/text-sequence-type.cpp
    metadata/trace-type-env.cpp
    metadata/trace-type-impl.cpp
    metadata/trace-type.cpp
    metadata/tsdl-parser-base.cpp
    metadata/variant-type-option.cpp
    metadata/variant-type.cpp
    logging/zf_log.c
    data-block.cpp
    data-source-factory.cpp
    data-source.cpp
    decoding-errors.cpp
    element-visitor.cpp
    memory-mapped-file-view-factory-impl.cpp
    memory-mapped-file-view-factory.cpp
    packet-proc-builder.cpp
    packet-sequence-iterator.cpp
    packet-sequence.cpp
    proc.cpp
    utils.cpp
    vm.cpp
)
target_link_libraries (yactfr Boost::boost)
set_target_properties (
    yactfr
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_include_directories (yactfr PRIVATE "${CMAKE_SOURCE_DIR}/include")

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

# library install rules
install (
    TARGETS yactfr
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
