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
    fail-sl-array-beyond-content
    fail-sl-array-beyond-data
    fail-be-to-le-change-in-byte
    fail-dl-array-beyond-content
    fail-dl-array-beyond-data
    fail-dl-str-beyond-content
    fail-dl-str-beyond-data
    fail-fl-float-beyond-data
    fail-fl-int-beyond-content
    fail-fl-int-beyond-data
    fail-fl-int-one-bit-beyond-content
    fail-fl-int-one-bit-beyond-data
    fail-le-to-be-change-in-byte
    fail-pkt-content-len-gt-pkt-total-len-1
    fail-pkt-content-len-gt-pkt-total-len-2
    fail-pkt-content-len-too-small
    fail-pkt-total-len-not-multiple-eight
    fail-pkt-total-len-too-small
    fail-sl-str-beyond-content
    fail-sl-str-beyond-data
    fail-nt-str-beyond-content
    fail-nt-str-beyond-data
    fail-unknown-dst-id
    fail-unknown-ert-id
    fail-var-beyond-content
    fail-var-beyond-data
    fail-var-inval-sel
    pass-all-basic-features-be
    pass-all-basic-features-le
    pass-sl-array-empty-structs
    pass-sl-arrays
    pass-clk-vals
    pass-complex-sl-arrays
    pass-diff-magic
    pass-diff-uuid
    pass-dst
    pass-dl-array-empty-structs
    pass-dl-array-multi-len
    pass-dl-arrays
    pass-dl-strs
    pass-empty-data
    pass-er-header-id-nt-str
    pass-fl-floats
    pass-implicit-def-clk-ts-role
    pass-multiple-dst-id-fl-ints
    pass-multiple-ert-id-fl-ints
    pass-no-ers-no-dst-id-fl-ints
    pass-no-ers-with-dst-id-fl-ints
    pass-odd-fl-enums
    pass-odd-fl-ints
    pass-pkt-content-len-no-pkt-total-len
    pass-pkt-ctx-content-size-nt-str
    pass-pkt-ctx-pkt-size-nt-str
    pass-pkt-header-magic-nt-str
    pass-pkt-header-stream-id-nt-str
    pass-pkt-header-stream-instance-id-nt-str
    pass-pkt-header-uuid-sl-array-of-nt-strs
    pass-pkt-header-uuid-nt-str
    pass-pkt-disc-er-counter-snap
    pass-pkt-disc-er-counter-snap-alt
    pass-pkt-seq-num
    pass-pkt-seq-num-alt
    pass-pkt-total-len-no-pkt-content-len
    pass-sl-strs
    pass-std-fl-enums
    pass-std-fl-ints
    pass-nt-str-align
    pass-vars
)

add_custom_target (
    tests-iter-data-traces
    DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/fail-align-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-align-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-sl-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-sl-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-be-to-le-change-in-byte/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dl-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dl-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dl-str-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dl-str-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-fl-float-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-fl-int-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-fl-int-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-fl-int-one-bit-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-fl-int-one-bit-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-le-to-be-change-in-byte/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-content-len-gt-pkt-total-len-1/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-content-len-gt-pkt-total-len-2/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-content-len-too-small/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-total-len-not-multiple-eight/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-pkt-total-len-too-small/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-sl-str-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-sl-str-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-nt-str-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-nt-str-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-unknown-dst-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-unknown-ert-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-var-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-var-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-var-inval-sel/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-all-basic-features-be/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-all-basic-features-le/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-sl-array-empty-structs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-sl-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-clk-vals/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-complex-sl-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-diff-magic/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-diff-uuid/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dst/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dl-array-empty-structs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dl-array-multi-len/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dl-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dl-strs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-empty-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-er-header-id-nt-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-fl-floats/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-implicit-def-clk-ts-role/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-multiple-dst-id-fl-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-multiple-ert-id-fl-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-no-ers-no-dst-id-fl-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-no-ers-with-dst-id-fl-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-odd-fl-enums/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-odd-fl-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-content-len-no-pkt-total-len/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-ctx-content-size-nt-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-ctx-pkt-size-nt-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-magic-nt-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-stream-id-nt-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-stream-instance-id-nt-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-uuid-sl-array-of-nt-strs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-header-uuid-nt-str/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-disc-er-counter-snap/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-disc-er-counter-snap-alt/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-seq-num/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-seq-num-alt/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-pkt-total-len-no-pkt-content-len/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-sl-strs/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-std-fl-enums/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-std-fl-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-nt-str-align/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-vars/metadata"
    VERBATIM
)
