# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

function (yactfr_create_streams NAME)
    set (BUILD-NAME-PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${NAME}")
    set (INPUT-PATH "${CMAKE_CURRENT_SOURCE_DIR}/${NAME}.streams")
    add_custom_command (
        OUTPUT "${BUILD-NAME-PREFIX}/metadata"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${BUILD-NAME-PREFIX}"
        COMMAND python3 "${CMAKE_SOURCE_DIR}/tests/tools/createstreams.py" "${INPUT-PATH}" "${BUILD-NAME-PREFIX}"
        VERBATIM
    )
endfunction ()

function (yactfr_create_all_streams)
    foreach (ARG IN LISTS ARGN)
        yactfr_create_streams ("${ARG}")
    endforeach ()
endfunction ()

yactfr_create_all_streams (
    fail-align-beyond-content
    fail-align-beyond-data
    fail-array-beyond-content
    fail-array-beyond-data
    fail-be-to-le-change-in-byte
    fail-dyn-array-beyond-content
    fail-dyn-array-beyond-data
    fail-dyn-text-array-beyond-content
    fail-dyn-text-array-beyond-data
    fail-float-beyond-data
    fail-int-beyond-content
    fail-int-beyond-data
    fail-int-one-bit-beyond-content
    fail-int-one-bit-beyond-data
    fail-le-to-be-change-in-byte
    fail-pkt-content-len-gt-pkt-total-len-1
    fail-pkt-content-len-gt-pkt-total-len-2
    fail-pkt-content-len-too-small
    fail-pkt-total-len-not-multiple-eight
    fail-pkt-total-len-too-small
    fail-static-text-array-beyond-content
    fail-static-text-array-beyond-data
    fail-str-beyond-content
    fail-str-beyond-data
    fail-unknown-dst-id
    fail-unknown-ert-id
    fail-var-beyond-content
    fail-var-beyond-data
    fail-var-inval-sel
    pass-all-basic-features-be
    pass-all-basic-features-le
    pass-array-empty-structs
    pass-arrays
    pass-clk-vals
    pass-complex-arrays
    pass-diff-magic
    pass-diff-uuid
    pass-dst
    pass-dyn-array-empty-structs
    pass-dyn-array-multi-len
    pass-dyn-arrays
    pass-dyn-text-arrays
    pass-empty-data
    pass-er-header-id-str
    pass-floats
    pass-implicit-def-clk-ts-role
    pass-multiple-dst-id-ints
    pass-multiple-ert-id-ints
    pass-no-ers-no-dst-id-ints
    pass-no-ers-with-dst-id
    pass-odd-enums
    pass-odd-ints
    pass-pkt-content-len-no-pkt-total-len
    pass-pkt-ctx-content-size-str
    pass-pkt-ctx-pkt-size-str
    pass-pkt-header-magic-str
    pass-pkt-header-stream-id-str
    pass-pkt-header-stream-instance-id-str
    pass-pkt-header-uuid-array-of-strs
    pass-pkt-header-uuid-str
    pass-pkt-origin-index
    pass-pkt-total-len-no-pkt-content-len
    pass-static-text-arrays
    pass-std-enums
    pass-std-ints
    pass-str-align
    pass-vars
)

add_custom_target (
    tests-iter-data-traces
    DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/fail-align-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-align-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-be-to-le-change-in-byte/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dyn-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dyn-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dyn-text-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dyn-text-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-float-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-one-bit-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-one-bit-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-le-to-be-change-in-byte/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-content-len-gt-pkt-total-len-1/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-content-len-gt-pkt-total-len-2/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-content-len-too-small/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-total-len-not-multiple-eight/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-total-len-too-small/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-static-text-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-static-text-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-str-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-str-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-unknown-dst-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-unknown-ert-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-var-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-var-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-var-inval-sel/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-all-basic-features-be/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-all-basic-features-le/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-array-empty-structs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-clk-vals/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-complex-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-diff-magic/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-diff-uuid/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dst/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dyn-array-empty-structs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dyn-array-multi-len/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dyn-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dyn-text-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-empty-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-er-header-id-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-floats/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-implicit-def-clk-ts-role/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-multiple-dst-id-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-multiple-ert-id-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-no-ers-no-dst-id-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-no-ers-with-dst-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-odd-enums/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-odd-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-content-len-no-pkt-total-len/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-ctx-content-size-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-ctx-pkt-size-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-magic-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-stream-id-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-stream-instance-id-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-uuid-array-of-strs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-uuid-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-origin-index/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-total-len-no-pkt-content-len/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-static-text-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-std-enums/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-std-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-str-align/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-vars/metadata"
    VERBATIM
)
