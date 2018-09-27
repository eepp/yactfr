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
    fail-float-beyond-data
    fail-int-beyond-content
    fail-int-beyond-data
    fail-int-one-bit-beyond-content
    fail-int-one-bit-beyond-data
    fail-le-to-be-change-in-byte
    fail-packet-content-size-gt-packet-total-size-1
    fail-packet-content-size-gt-packet-total-size-2
    fail-packet-content-size-too-small
    fail-packet-total-size-not-multiple-eight
    fail-packet-total-size-too-small
    fail-dynamic-array-beyond-content
    fail-dynamic-array-beyond-data
    fail-string-beyond-content
    fail-string-beyond-data
    fail-text-array-beyond-content
    fail-text-array-beyond-data
    fail-text-dynamic-array-beyond-content
    fail-text-dynamic-array-beyond-data
    fail-unknown-dst-id
    fail-unknown-ert-id
    fail-variant-beyond-content
    fail-variant-beyond-data
    fail-variant-unknown-tag
    pass-all-basic-features-be
    pass-all-basic-features-le
    pass-array-empty-struct
    pass-arrays
    pass-clock-values
    pass-complex-arrays
    pass-data-stream-id
    pass-diff-magic
    pass-diff-uuid
    pass-empty-data
    pass-floats
    pass-multiple-id
    pass-multiple-id-in-array
    pass-multiple-stream-id
    pass-no-events-no-stream-id
    pass-no-events-with-stream-id
    pass-odd-enums
    pass-odd-ints
    pass-packet-content-size-no-packet-total-size
    pass-packet-origin-index
    pass-packet-total-size-no-packet-content-size
    pass-dynamic-array-empty-struct
    pass-dynamic-arrays
    pass-std-enums
    pass-std-ints
    pass-string-alignment
    pass-text-arrays
    pass-text-dynamic-arrays
    pass-variants
)

add_custom_target (
    tests-iter-data-traces
    DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/fail-align-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-align-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-be-to-le-change-in-byte/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-float-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-one-bit-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-int-one-bit-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-le-to-be-change-in-byte/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-packet-content-size-gt-packet-total-size-1/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-packet-content-size-gt-packet-total-size-2/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-packet-content-size-too-small/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-packet-total-size-not-multiple-eight/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-packet-total-size-too-small/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dynamic-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-dynamic-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-string-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-string-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-text-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-text-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-text-dynamic-array-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-text-dynamic-array-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-unknown-dst-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-unknown-ert-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-variant-beyond-content/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-variant-beyond-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/fail-variant-unknown-tag/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-all-basic-features-be/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-all-basic-features-le/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-array-empty-struct/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-clock-values/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-complex-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-data-stream-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-diff-magic/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-diff-uuid/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-empty-data/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-floats/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-multiple-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-multiple-id-in-array/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-multiple-stream-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-no-events-no-stream-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-no-events-with-stream-id/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-odd-enums/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-odd-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-packet-content-size-no-packet-total-size/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-packet-origin-index/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-packet-total-size-no-packet-content-size/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dynamic-array-empty-struct/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-dynamic-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-std-enums/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-std-ints/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-string-alignment/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-text-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-text-dynamic-arrays/metadata"
        "${CMAKE_CURRENT_BINARY_DIR}/pass-variants/metadata"
    VERBATIM
)
