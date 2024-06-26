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
    internal/metadata/dt-from-pseudo-root-dt.cpp
    internal/metadata/item.cpp
    internal/metadata/json/ctf-2-json-seq-parser.cpp
    internal/metadata/json/ctf-2-json-strs.cpp
    internal/metadata/json/ctf-2-json-utils.cpp
    internal/metadata/json/ctf-2-json-val-req.cpp
    internal/metadata/json/item-from-json-val.cpp
    internal/metadata/json/json-val-from-text.cpp
    internal/metadata/json/json-val-req.cpp
    internal/metadata/json/json-val.cpp
    internal/metadata/json/pseudo-dt-erector.cpp
    internal/metadata/pseudo-types.cpp
    internal/metadata/set-pseudo-dt-data-loc.cpp
    internal/metadata/set-pseudo-dt-pos-in-scope.cpp
    internal/metadata/str-scanner.cpp
    internal/metadata/trace-type-from-pseudo-trace-type.cpp
    internal/metadata/trace-type-impl.cpp
    internal/metadata/tsdl/tsdl-attr.cpp
    internal/metadata/tsdl/tsdl-parser.cpp
    internal/mmap-file-view-factory-impl.cpp
    internal/pkt-proc-builder.cpp
    internal/proc.cpp
    internal/utils.cpp
    internal/vm.cpp
    metadata/array-type.cpp
    metadata/blob-type.cpp
    metadata/clk-type.cpp
    metadata/compound-dt.cpp
    metadata/data-loc.cpp
    metadata/dl-array-type.cpp
    metadata/dl-blob-type.cpp
    metadata/dl-str-type.cpp
    metadata/dst.cpp
    metadata/dt.cpp
    metadata/ert.cpp
    metadata/fl-bit-array-type.cpp
    metadata/fl-bit-map-type.cpp
    metadata/fl-bool-type.cpp
    metadata/fl-float-type.cpp
    metadata/fl-int-type.cpp
    metadata/from-metadata-text.cpp
    metadata/int-type-common.cpp
    metadata/metadata-stream.cpp
    metadata/metadata.cpp
    metadata/non-nt-str-type.cpp
    metadata/nt-str-type.cpp
    metadata/opt-type.cpp
    metadata/packetized-metadata-stream.cpp
    metadata/plain-text-metadata-stream.cpp
    metadata/scalar-dt.cpp
    metadata/sl-array-type.cpp
    metadata/sl-blob-type.cpp
    metadata/sl-str-type.cpp
    metadata/str-type.cpp
    metadata/struct-member-type.cpp
    metadata/struct-type.cpp
    metadata/trace-env.cpp
    metadata/trace-type.cpp
    metadata/var-type.cpp
    metadata/vl-int-type.cpp
    mmap-file-view-factory.cpp
    text-loc.cpp
    text-parse-error.cpp
)
set_target_properties (
    yactfr
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_include_directories (
    yactfr PRIVATE
    .
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)
target_compile_definitions(
    yactfr PRIVATE
    -DWISE_ENUM_OPTIONAL_TYPE=boost::optional
)

# include-what-you-use
option (
    OPT_ENABLE_IWYU
    "Enable include-what-you-use"
    OFF
)

if (OPT_ENABLE_IWYU)
    find_program (IWYU_PATH NAMES include-what-you-use iwyu REQUIRED)
    set_property (TARGET yactfr PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})
endif ()

# library installation rules
install (
    TARGETS yactfr
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
