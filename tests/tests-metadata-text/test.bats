#!/usr/bin/env bats

# Copyright (C) 2018 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

metadata_text_tester_bin="$testers_path/metadata-text-tester"

assert_file_exists() {
  local file="$1"

  if [ ! -f "$file" ]; then
    echo "FATAL: file \`$1\` does not exist" 1>&2
    false
    return
  fi
}

test_metadata_fail() {
  local file="fail-$1"

  assert_file_exists "$file"
  run "$metadata_text_tester_bin" "$file"
  [ $status -eq 2 ]
}

test_metadata_pass() {
  local file="pass-$1"

  assert_file_exists "$file"
  run "$metadata_text_tester_bin" "$file"
  [ $status -eq 0 ]
}

@test 'metadata: empty -> fail' {
  test_metadata_fail metadata-empty
}

@test 'trace: no major attribute -> fail' {
  test_metadata_fail trace-no-major
}

@test 'trace: no minor attribute -> fail' {
  test_metadata_fail trace-no-minor
}

@test 'trace: wrong major attribute -> fail' {
  test_metadata_fail trace-wrong-major
}

@test 'trace: wrong minor attribute -> fail' {
  test_metadata_fail trace-wrong-minor
}

@test 'trace: no byte order attribute -> fail' {
  test_metadata_fail trace-no-byte-order
}

@test 'trace: wrong byte order attribute -> fail' {
  test_metadata_fail trace-wrong-byte-order
}

@test 'trace: wrong UUID attribute (1) -> fail' {
  test_metadata_fail trace-wrong-uuid-1
}

@test 'trace: wrong UUID attribute (2) -> fail' {
  test_metadata_fail trace-wrong-uuid-2
}

@test 'trace: wrong UUID attribute (3) -> fail' {
  test_metadata_fail trace-wrong-uuid-3
}

@test 'trace: wrong UUID attribute (4) -> fail' {
  test_metadata_fail trace-wrong-uuid-4
}

@test 'trace: unknown attribute -> fail' {
  test_metadata_fail trace-unknown-attr
}

@test 'trace: duplicate attribute -> fail' {
  test_metadata_fail trace-dup-attr
}

@test 'trace: duplicate PH -> fail' {
  test_metadata_fail trace-dup-ph
}

@test 'trace: no block -> fail' {
  test_metadata_fail trace-no
}

@test 'trace: duplicate block -> fail' {
  test_metadata_fail trace-dup
}

@test 'trace PH: invalid magic field (1) -> fail' {
  test_metadata_fail trace-ph-inval-magic-1
}

@test 'trace PH: invalid magic field (2) -> fail' {
  test_metadata_fail trace-ph-inval-magic-2
}

@test 'trace PH: invalid magic field (3) -> fail' {
  test_metadata_fail trace-ph-inval-magic-3
}

@test 'trace PH: invalid magic field (4) -> fail' {
  test_metadata_fail trace-ph-inval-magic-4
}

@test 'trace PH: invalid UUID field (1) -> fail' {
  test_metadata_fail trace-ph-inval-uuid-1
}

@test 'trace PH: invalid UUID field (2) -> fail' {
  test_metadata_fail trace-ph-inval-uuid-2
}

@test 'trace PH: invalid UUID field (3) -> fail' {
  test_metadata_fail trace-ph-inval-uuid-3
}

@test 'trace PH: invalid UUID field (4) -> fail' {
  test_metadata_fail trace-ph-inval-uuid-4
}

@test 'trace PH: invalid stream ID field (1) -> fail' {
  test_metadata_fail trace-ph-inval-stream-id-1
}

@test 'trace PH: invalid stream ID field (2) -> fail' {
  test_metadata_fail trace-ph-inval-stream-id-2
}

@test 'trace PH: invalid stream instance ID field (1) -> fail' {
  test_metadata_fail trace-ph-inval-stream-instance-id-1
}

@test 'trace PH: invalid stream instance ID field (2) -> fail' {
  test_metadata_fail trace-ph-inval-stream-instance-id-2
}

@test 'trace PH: missing stream ID field -> fail' {
  test_metadata_fail trace-ph-need-stream-id
}

@test 'env: out of range (negative) -> fail' {
  test_metadata_fail env-out-of-range-neg
}

@test 'env: out of range (positive) -> fail' {
  test_metadata_fail env-out-of-range-pos
}

@test 'env: duplicate entry -> fail' {
  test_metadata_fail env-dup-entry
}

@test 'env: duplicate block -> fail' {
  test_metadata_fail env-dup
}

@test 'env: wrong entry -> fail' {
  test_metadata_fail env-wrong-entry
}

@test 'clock: duplicate with same name -> fail' {
  test_metadata_fail clock-dup
}

@test 'clock: duplicate attribute -> fail' {
  test_metadata_fail clock-dup-attr
}

@test 'clock: missing name -> fail' {
  test_metadata_fail clock-no-name
}

@test 'clock: unknown attribute -> fail' {
  test_metadata_fail clock-unknown-attr
}

@test 'clock: wrong description attribute (1) -> fail' {
  test_metadata_fail clock-wrong-description-1
}

@test 'clock: wrong description attribute (2) -> fail' {
  test_metadata_fail clock-wrong-description-2
}

@test 'clock: wrong frequency attribute (1) -> fail' {
  test_metadata_fail clock-wrong-freq-1
}

@test 'clock: wrong frequency attribute (2) -> fail' {
  test_metadata_fail clock-wrong-freq-2
}

@test 'clock: wrong frequency attribute (3) -> fail' {
  test_metadata_fail clock-wrong-freq-3
}

@test 'clock: wrong name attribute -> fail' {
  test_metadata_fail clock-wrong-name
}

@test 'clock: wrong offset (cycles) attribute (1) -> fail' {
  test_metadata_fail clock-wrong-offset-1
}

@test 'clock: wrong offset (cycles) attribute (2) -> fail' {
  test_metadata_fail clock-wrong-offset-2
}

@test 'clock: wrong offset (seconds) attribute -> fail' {
  test_metadata_fail clock-wrong-offset-s
}

@test 'clock: wrong precision attribute (1) -> fail' {
  test_metadata_fail clock-wrong-precision-1
}

@test 'clock: wrong precision attribute (2) -> fail' {
  test_metadata_fail clock-wrong-precision-2
}

@test 'clock: wrong UUID attribute (1) -> fail' {
  test_metadata_fail clock-wrong-uuid-1
}

@test 'clock: wrong UUID attribute (2) -> fail' {
  test_metadata_fail clock-wrong-uuid-2
}

@test 'clock: wrong UUID attribute (3) -> fail' {
  test_metadata_fail clock-wrong-uuid-3
}

@test 'clock: wrong UUID attribute (4) -> fail' {
  test_metadata_fail clock-wrong-uuid-4
}

@test 'clock: wrong absolute attribute (1) -> fail' {
  test_metadata_fail clock-wrong-absolute-1
}

@test 'clock: wrong absolute attribute (2) -> fail' {
  test_metadata_fail clock-wrong-absolute-2
}

@test 'stream: missing ID attribute -> fail' {
  test_metadata_fail stream-need-id
}

@test 'stream: unknown attribute -> fail' {
  test_metadata_fail stream-unknown-attr
}

@test 'stream: duplicate attribute -> fail' {
  test_metadata_fail stream-dup-attr
}

@test 'stream: wrong ID attribute -> fail' {
  test_metadata_fail stream-wrong-id
}

@test 'stream: duplicate with same ID attribute -> fail' {
  test_metadata_fail stream-dup
}

@test 'stream: duplicate PC -> fail' {
  test_metadata_fail stream-dup-pc
}

@test 'stream: duplicate EH -> fail' {
  test_metadata_fail stream-dup-eh
}

@test 'stream: duplicate EC -> fail' {
  test_metadata_fail stream-dup-ec
}

@test 'stream PC: invalid packet size field (1) -> fail' {
  test_metadata_fail stream-pc-inval-packet-size-1
}

@test 'stream PC: invalid packet size field (2) -> fail' {
  test_metadata_fail stream-pc-inval-packet-size-2
}

@test 'stream PC: invalid content size field (1) -> fail' {
  test_metadata_fail stream-pc-inval-content-size-1
}

@test 'stream PC: invalid content size field (2) -> fail' {
  test_metadata_fail stream-pc-inval-content-size-2
}

@test 'stream EH: invalid ID field (1) -> fail' {
  test_metadata_fail stream-eh-inval-id-1
}

@test 'stream EH: invalid ID field (2) -> fail' {
  test_metadata_fail stream-eh-inval-id-2
}

@test 'event: unknown attribute -> fail' {
  test_metadata_fail event-unknown-attr
}

@test 'event: duplicate attribute -> fail' {
  test_metadata_fail event-dup-attr
}

@test 'event: missing stream ID attribute -> fail' {
  test_metadata_fail event-need-stream-id
}

@test 'event: missing ID attribute -> fail' {
  test_metadata_fail event-need-id
}

@test 'event: wrong ID attribute -> fail' {
  test_metadata_fail event-wrong-id
}

@test 'event: wrong stream ID attribute -> fail' {
  test_metadata_fail event-wrong-stream-id
}

@test 'event: wrong name attribute -> fail' {
  test_metadata_fail event-wrong-name
}

@test 'event: wrong log level attribute -> fail' {
  test_metadata_fail event-wrong-loglevel
}

@test 'event: wrong model EMF URI attribute -> fail' {
  test_metadata_fail event-wrong-model-emf-uri
}

@test 'event: duplicate with same ID attribute -> fail' {
  test_metadata_fail event-dup
}

@test 'event: empty (1) -> fail' {
  test_metadata_fail event-empty-1
}

@test 'event: empty (2) -> fail' {
  test_metadata_fail event-empty-2
}

@test 'event: empty (3) -> fail' {
  test_metadata_fail event-empty-3
}

@test 'event: empty (4) -> fail' {
  test_metadata_fail event-empty-4
}

@test 'event: empty (5) -> fail' {
  test_metadata_fail event-empty-5
}

@test 'event: duplicate C -> fail' {
  test_metadata_fail event-dup-c
}

@test 'event: duplicate F -> fail' {
  test_metadata_fail event-dup-f
}

@test 'event: log level is out of range -> fail' {
  test_metadata_fail event-loglevel-out-of-range
}

@test 'type alias: duplicate with same name -> fail' {
  test_metadata_fail typealias-dup
}

@test 'type alias: sequence type length outside type alias -> fail' {
  test_metadata_fail typealias-seq-len-outside
}

@test 'invalid syntax: no `;` after trace block -> fail' {
  test_metadata_fail syntax-trace-no-semi
}

@test 'invalid syntax: no `;` after stream block -> fail' {
  test_metadata_fail syntax-stream-no-semi
}

@test 'invalid syntax: no `;` after event block -> fail' {
  test_metadata_fail syntax-event-no-semi
}

@test 'invalid syntax: open quoted literal string -> fail' {
  test_metadata_fail syntax-open-quoted-literal
}

@test 'invalid syntax: no `;` after clock block -> fail' {
  test_metadata_fail syntax-clock-no-semi
}

@test 'invalid syntax: no `;` after env block -> fail' {
  test_metadata_fail syntax-env-no-semi
}

@test 'invalid syntax: no `;` after type alias block -> fail' {
  test_metadata_fail syntax-typealias-no-semi
}

@test 'invalid syntax: no `=` after attribute name -> fail' {
  test_metadata_fail syntax-attr-no-equal
}

@test 'invalid syntax: no value after attribute equal -> fail' {
  test_metadata_fail syntax-attr-no-value
}

@test 'invalid syntax: no `;` after attribute value -> fail' {
  test_metadata_fail syntax-attr-no-semi
}

@test 'invalid syntax: no attribute name -> fail' {
  test_metadata_fail syntax-attr-no-name
}

@test 'invalid syntax: invalid attribute value -> fail' {
  test_metadata_fail syntax-attr-inval-value
}

@test 'invalid syntax: no `:=` in type alias -> fail' {
  test_metadata_fail syntax-typealias-no-assign
}

@test 'invalid syntax: no name in type alias -> fail' {
  test_metadata_fail syntax-typealias-no-name
}

@test 'invalid syntax: wrong name in type alias -> fail' {
  test_metadata_fail syntax-typealias-wrong-name
}

@test 'invalid syntax: no type in type alias -> fail' {
  test_metadata_fail syntax-typealias-no-type
}

@test 'invalid syntax: unexpected end of file -> fail' {
  test_metadata_fail syntax-eof
}

@test 'invalid syntax: expecting field or type alias (in struct) -> fail' {
  test_metadata_fail syntax-struct-field
}

@test 'invalid syntax: expecting option or type alias (in variant) -> fail' {
  test_metadata_fail syntax-variant-option
}

@test 'invalid syntax: reserved word in typealias name (1) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-1
}

@test 'invalid syntax: reserved word in typealias name (2) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-2
}

@test 'invalid syntax: reserved word in typealias name (3) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-3
}

@test 'invalid syntax: reserved word in typealias name (4) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-4
}

@test 'invalid syntax: reserved word in typealias name (5) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-5
}

@test 'invalid syntax: reserved word in typealias name (6) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-6
}

@test 'invalid syntax: reserved word in typealias name (7) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-7
}

@test 'invalid syntax: reserved word in typealias name (8) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-8
}

@test 'invalid syntax: reserved word in typealias name (9) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-9
}

@test 'invalid syntax: reserved word in typealias name (10) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-10
}

@test 'invalid syntax: reserved word in typealias name (11) -> fail' {
  test_metadata_fail syntax-typealias-reserved-name-11
}

@test 'integer: negative alignment attribute -> fail' {
  test_metadata_fail integer-align-neg
}

@test 'integer: non-power-of-two alignment attribute -> fail' {
  test_metadata_fail integer-align-non-pow2
}

@test 'integer: zero alignment attribute -> fail' {
  test_metadata_fail integer-align-zero
}

@test 'integer: duplicate attribute -> fail' {
  test_metadata_fail integer-dup-attr
}

@test 'integer: unknown mapped clock -> fail' {
  test_metadata_fail integer-map-unknown-clock
}

@test 'integer: missing size attribute -> fail' {
  test_metadata_fail integer-no-size
}

@test 'integer: negative size attribute -> fail' {
  test_metadata_fail integer-size-neg
}

@test 'integer: zero size attribute -> fail' {
  test_metadata_fail integer-size-zero
}

@test 'integer: size is too large -> fail' {
  test_metadata_fail integer-size-too-large
}

@test 'integer: unknown attribute -> fail' {
  test_metadata_fail integer-unknown-attr
}

@test 'integer: wrong base attribute (1) -> fail' {
  test_metadata_fail integer-wrong-base-1
}

@test 'integer: wrong base attribute (2) -> fail' {
  test_metadata_fail integer-wrong-base-2
}

@test 'integer: wrong base attribute (3) -> fail' {
  test_metadata_fail integer-wrong-base-3
}

@test 'integer: wrong byte order attribute (1) -> fail' {
  test_metadata_fail integer-wrong-byte-order-1
}

@test 'integer: wrong byte order attribute (2) -> fail' {
  test_metadata_fail integer-wrong-byte-order-2
}

@test 'integer: wrong encoding attribute (1) -> fail' {
  test_metadata_fail integer-wrong-encoding-1
}

@test 'integer: wrong encoding attribute (2) -> fail' {
  test_metadata_fail integer-wrong-encoding-2
}

@test 'integer: wrong map attribute (1) -> fail' {
  test_metadata_fail integer-wrong-map-1
}

@test 'integer: wrong map attribute (2) -> fail' {
  test_metadata_fail integer-wrong-map-2
}

@test 'integer: wrong signed attribute (1) -> fail' {
  test_metadata_fail integer-wrong-signed-1
}

@test 'integer: wrong signed attribute (2) -> fail' {
  test_metadata_fail integer-wrong-signed-2
}

@test 'integer: wrong signed attribute (3) -> fail' {
  test_metadata_fail integer-wrong-signed-3
}

@test 'integer: wrong size attribute -> fail' {
  test_metadata_fail integer-wrong-size
}

@test 'floating: duplicate attribute -> fail' {
  test_metadata_fail float-dup-attr
}

@test 'floating: missing exponent size attribute -> fail' {
  test_metadata_fail float-no-exp-dig
}

@test 'floating: missing mantissa size attribute -> fail' {
  test_metadata_fail float-no-mang-dig
}

@test 'floating: unknown attribute -> fail' {
  test_metadata_fail float-unknown-attr
}

@test 'floating: wrong exponent size attribute (1) -> fail' {
  test_metadata_fail float-wrong-exp-dig-1
}

@test 'floating: wrong exponent size attribute (2) -> fail' {
  test_metadata_fail float-wrong-exp-dig-2
}

@test 'floating: wrong mantissa size attribute (1) -> fail' {
  test_metadata_fail float-wrong-mant-dig-1
}

@test 'floating: wrong mantissa size attribute (2) -> fail' {
  test_metadata_fail float-wrong-mant-dig-2
}

@test 'string: duplicate attribute -> fail' {
  test_metadata_fail string-dup-attr
}

@test 'string: unknown attribute -> fail' {
  test_metadata_fail string-unknown-attr
}

@test 'string: wrong encoding attribute -> fail' {
  test_metadata_fail string-wrong-encoding-attr
}

@test 'struct: negative alignment -> fail' {
  test_metadata_fail struct-align-neg
}

@test 'struct: non-power-of-two alignment -> fail' {
  test_metadata_fail struct-align-non-pow2
}

@test 'struct: zero alignment -> fail' {
  test_metadata_fail struct-align-zero
}

@test 'struct: duplicate field -> fail' {
  test_metadata_fail struct-dup-field
}

@test 'struct: duplicate type alias -> fail' {
  test_metadata_fail struct-dup-typealias
}

@test 'struct: field uses type alias defined after it -> fail' {
  test_metadata_fail struct-field-typealias-after-field
}

@test 'struct: field uses unknown type alias -> fail' {
  test_metadata_fail struct-field-unknown-typealias
}

@test "enum: inversed member's lower and upper -> fail" {
  test_metadata_fail enum-inversed-lower-upper
}

@test 'enum: integer is too small (1) -> fail' {
  test_metadata_fail enum-int-too-small-1
}

@test 'enum: integer is too small (2) -> fail' {
  test_metadata_fail enum-int-too-small-2
}

@test 'enum: `int` type alias not defined but needed -> fail' {
  test_metadata_fail enum-need-int-typealias
}

@test 'enum: integer type alias is not an int -> fail' {
  test_metadata_fail enum-wrong-int-typealias
}

@test 'enum: member is out of range (1) -> fail' {
  test_metadata_fail enum-out-of-range-1
}

@test 'enum: member is out of range (2) -> fail' {
  test_metadata_fail enum-out-of-range-2
}

@test 'enum: member is out of range (3) -> fail' {
  test_metadata_fail enum-out-of-range-3
}

@test 'enum: member is out of range (4) -> fail' {
  test_metadata_fail enum-out-of-range-4
}

@test 'enum: member is out of range (5) -> fail' {
  test_metadata_fail enum-out-of-range-5
}

@test 'enum: unknown integer type alias -> fail' {
  test_metadata_fail enum-unknown-int
}

@test 'enum: wrong integer -> fail' {
  test_metadata_fail enum-wrong-int
}

@test 'variant: empty body (no options) -> fail' {
  test_metadata_fail variant-empty
}

@test 'variant: empty tag (1) -> fail' {
  test_metadata_fail variant-empty-tag-1
}

@test 'variant: empty tag (2) -> fail' {
  test_metadata_fail variant-empty-tag-2
}

@test 'variant: tag is not an enum -> fail' {
  test_metadata_fail variant-tag-not-enum
}

@test 'variant: tag member is not a option -> fail' {
  test_metadata_fail variant-unhandled-tag-option
}

@test 'variant: unknown tag (1) -> fail' {
  test_metadata_fail variant-unknown-tag-1
}

@test 'variant: unknown tag (2) -> fail' {
  test_metadata_fail variant-unknown-tag-2
}

@test 'variant: unknown tag (3) -> fail' {
  test_metadata_fail variant-unknown-tag-3
}

@test 'variant: unknown tag (4) -> fail' {
  test_metadata_fail variant-unknown-tag-4
}

@test 'variant: unknown tag (5) -> fail' {
  test_metadata_fail variant-unknown-tag-5
}

@test 'variant: unknown tag (6) -> fail' {
  test_metadata_fail variant-unknown-tag-6
}

@test 'variant: unknown tag (7) -> fail' {
  test_metadata_fail variant-unknown-tag-7
}

@test 'variant: unknown tag (8) -> fail' {
  test_metadata_fail variant-unknown-tag-8
}

@test 'variant: unknown tag (9) -> fail' {
  test_metadata_fail variant-unknown-tag-9
}

@test 'variant: untagged field (1) -> fail' {
  test_metadata_fail variant-untagged-field-1
}

@test 'variant: untagged field (2) -> fail' {
  test_metadata_fail variant-untagged-field-2
}

@test 'variant: wrong tag -> fail' {
  test_metadata_fail variant-wrong-tag
}

@test 'variant: named variant with relative tag -> fail' {
  test_metadata_fail variant-named-rel-tag
}

@test 'array: empty length -> fail' {
  test_metadata_fail array-length-empty
}

@test 'array: length is negative -> fail' {
  test_metadata_fail array-length-neg
}

@test 'array: wrong length -> fail' {
  test_metadata_fail array-wrong-length
}

@test 'array: negative length through environment reference -> fail' {
  test_metadata_fail array-env-length-neg
}

@test 'array: environment reference with missing environment -> fail' {
  test_metadata_fail array-env-no-env
}

@test 'array: environment reference without a key -> fail' {
  test_metadata_fail array-env-no-key
}

@test 'array: environment reference with missing environment entry -> fail' {
  test_metadata_fail array-env-ref-missing
}

@test 'array: environment reference is too long -> fail' {
  test_metadata_fail array-env-ref-too-long
}

@test 'array: environment reference is a string -> fail' {
  test_metadata_fail array-env-string-key
}

@test 'sequence: unknown length -> fail' {
  test_metadata_fail seq-unknown-length
}

@test 'CTF test suite: array-redefinition -> fail' {
  test_metadata_fail ctf-testsuite-array-redefinition
}

@test 'CTF test suite: array-size-identifier -> fail' {
  test_metadata_fail ctf-testsuite-array-size-identifier
}

@test 'CTF test suite: array-size-keyword -> fail' {
  test_metadata_fail ctf-testsuite-array-size-keyword
}

@test 'CTF test suite: array-size-negative -> fail' {
  test_metadata_fail ctf-testsuite-array-size-negative
}

@test 'CTF test suite: array-size-not-present -> fail' {
  test_metadata_fail ctf-testsuite-array-size-not-present
}

@test 'CTF test suite: array-size-string -> fail' {
  test_metadata_fail ctf-testsuite-array-size-string
}

@test 'CTF test suite: array-size-type -> fail' {
  test_metadata_fail ctf-testsuite-array-size-type
}

@test 'CTF test suite: array-size-type-field -> fail' {
  test_metadata_fail ctf-testsuite-array-size-type-field
}

@test 'CTF test suite: enum-empty -> fail' {
  test_metadata_fail ctf-testsuite-enum-empty
}

@test 'CTF test suite: enum-field-value-out-of-range -> fail' {
  test_metadata_fail ctf-testsuite-enum-field-value-out-of-range
}

@test 'CTF test suite: enum-type-implicit-but-undefined-int-type -> fail' {
  test_metadata_fail ctf-testsuite-enum-type-implicit-but-undefined-int-type
}

@test 'CTF test suite: enum-type-negative-out-of-range -> fail' {
  test_metadata_fail ctf-testsuite-enum-type-negative-out-of-range
}

@test 'CTF test suite: enum-type-value-out-of-range -> fail' {
  test_metadata_fail ctf-testsuite-enum-type-value-out-of-range
}

@test 'CTF test suite: enum-untyped-missing-int -> fail' {
  test_metadata_fail ctf-testsuite-enum-untyped-missing-int
}

@test 'CTF test suite: enum-untyped-string -> fail' {
  test_metadata_fail ctf-testsuite-enum-untyped-string
}

@test 'CTF test suite: enum-values-floating -> fail' {
  test_metadata_fail ctf-testsuite-enum-values-floating
}

@test 'CTF test suite: enum-values-token -> fail' {
  test_metadata_fail ctf-testsuite-enum-values-token
}

@test 'CTF test suite: enum-values-too-small -> fail' {
  test_metadata_fail ctf-testsuite-enum-values-too-small
}

@test 'CTF test suite: event-id-string -> fail' {
  test_metadata_fail ctf-testsuite-event-id-string
}

@test 'CTF test suite: event-id-struct -> fail' {
  test_metadata_fail ctf-testsuite-event-id-struct
}

@test 'CTF test suite: integer-0-bit-size -> fail' {
  test_metadata_fail ctf-testsuite-integer-0-bit-size
}

@test 'CTF test suite: integer-align-as-string -> fail' {
  test_metadata_fail ctf-testsuite-integer-align-as-string
}

@test 'CTF test suite: integer-align-negative -> fail' {
  test_metadata_fail ctf-testsuite-integer-align-negative
}

@test 'CTF test suite: integer-align-non-power-2 -> fail' {
  test_metadata_fail ctf-testsuite-integer-align-non-power-2
}

@test 'CTF test suite: integer-base-as-string -> fail' {
  test_metadata_fail ctf-testsuite-integer-base-as-string
}

@test 'CTF test suite: integer-base-invalid -> fail' {
  test_metadata_fail ctf-testsuite-integer-base-invalid
}

@test 'CTF test suite: integer-byte-order-invalid -> fail' {
  test_metadata_fail ctf-testsuite-integer-byte-order-invalid
}

@test 'CTF test suite: integer-encoding-as-string -> fail' {
  test_metadata_fail ctf-testsuite-integer-encoding-as-string
}

@test 'CTF test suite: integer-encoding-invalid -> fail' {
  test_metadata_fail ctf-testsuite-integer-encoding-invalid
}

@test 'CTF test suite: integer-negative-bit-size -> fail' {
  test_metadata_fail ctf-testsuite-integer-negative-bit-size
}

@test 'CTF test suite: integer-range -> fail' {
  test_metadata_fail ctf-testsuite-integer-range
}

@test 'CTF test suite: integer-signed-as-string -> fail' {
  test_metadata_fail ctf-testsuite-integer-signed-as-string
}

@test 'CTF test suite: integer-signed-invalid -> fail' {
  test_metadata_fail ctf-testsuite-integer-signed-invalid
}

@test 'CTF test suite: integer-size-as-string -> fail' {
  test_metadata_fail ctf-testsuite-integer-size-as-string
}

@test 'CTF test suite: integer-size-missing -> fail' {
  test_metadata_fail ctf-testsuite-integer-size-missing
}

@test 'CTF test suite: integer-size-negative -> fail' {
  test_metadata_fail ctf-testsuite-integer-size-negative
}

@test 'CTF test suite: lexer-literal-guid-corrupted -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-guid-corrupted
}

@test 'CTF test suite: lexer-literal-guid-too-big -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-guid-too-big
}

@test 'CTF test suite: lexer-literal-guid-too-small -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-guid-too-small
}

@test 'CTF test suite: lexer-literal-int-incomplete -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-int-incomplete
}

@test 'CTF test suite: lexer-unterminated-bracket -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-bracket
}

@test 'CTF test suite: lexer-unterminated-declaration -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-declaration
}

@test 'CTF test suite: lexer-unterminated-expression -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-expression
}

@test 'CTF test suite: lexer-unterminated-string -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-string
}

@test 'CTF test suite: metadata-empty-after-header -> fail' {
  test_metadata_fail ctf-testsuite-metadata-empty-after-header
}

@test 'CTF test suite: metadata-with-null-char -> fail' {
  test_metadata_fail ctf-testsuite-metadata-with-null-char
}

@test 'CTF test suite: repeated-event-id-in-same-stream -> fail' {
  test_metadata_fail ctf-testsuite-repeated-event-id-in-same-stream
}

@test 'CTF test suite: string-concat -> fail' {
  test_metadata_fail ctf-testsuite-string-concat
}

@test 'CTF test suite: struct-align-enum -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-enum
}

@test 'CTF test suite: struct-align-huge -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-huge
}

@test 'CTF test suite: struct-align-negative -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-negative
}

@test 'CTF test suite: struct-align-string -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-string
}

@test 'CTF test suite: struct-align-zero -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-zero
}

@test 'CTF test suite: struct-duplicate-field-name -> fail' {
  test_metadata_fail ctf-testsuite-struct-duplicate-field-name
}

@test 'CTF test suite: struct-duplicate-struct-name -> fail' {
  test_metadata_fail ctf-testsuite-struct-duplicate-struct-name
}

@test 'CTF test suite: struct-inner-struct-undefined -> fail' {
  test_metadata_fail ctf-testsuite-struct-inner-struct-undefined
}

@test 'CTF test suite: struct-int-type-undefined -> fail' {
  test_metadata_fail ctf-testsuite-struct-int-type-undefined
}

@test 'CTF test suite: struct-recursive -> fail' {
  test_metadata_fail ctf-testsuite-struct-recursive
}

@test 'CTF test suite: typealias-duplicate-name -> fail' {
  test_metadata_fail ctf-testsuite-typealias-duplicate-name
}

@test 'CTF test suite: typealias-invalid-type-kind -> fail' {
  test_metadata_fail ctf-testsuite-typealias-invalid-type-kind
}

@test 'CTF test suite: typealias-reserved-keyword -> fail' {
  test_metadata_fail ctf-testsuite-typealias-reserved-keyword
}

@test 'CTF test suite: typedef-redefinition -> fail' {
  test_metadata_fail ctf-testsuite-typedef-redefinition
}

@test 'CTF test suite: variant-missing-tag -> fail' {
  test_metadata_fail ctf-testsuite-variant-missing-tag
}

@test 'CTF test suite: variant-string-fields -> fail' {
  test_metadata_fail ctf-testsuite-variant-string-fields
}

@test 'CTF test suite: variant-tag-integer -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-integer
}

@test 'CTF test suite: variant-tag-string -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-string
}

@test 'CTF test suite: variant-tag-type-floating -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-type-floating
}

@test 'CTF test suite: variant-tag-type-string -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-type-string
}


@test 'LTTng-modules 2.7.0 (1300+ event record classes) -> pass' {
  test_metadata_pass lttng-modules-2.7.0
}

@test 'LTTng-modules 2.9.2 (1300+ event record classes) -> pass' {
  test_metadata_pass lttng-modules-2.9.2
}

@test 'int: full type -> pass' {
  test_metadata_pass int-full
}

@test 'float: full type -> pass' {
  test_metadata_pass float-full
}

@test 'string: full type -> pass' {
  test_metadata_pass string-full
}

@test 'enum max. value (unsigned 64-bit, decimal) -> pass' {
  test_metadata_pass enum-ranges-u64-dec
}

@test 'enum max. value (unsigned 64-bit, hexadecimal) -> pass' {
  test_metadata_pass enum-ranges-u64-hex
}

@test 'enum max. value (unsigned 64-bit, octal) -> pass' {
  test_metadata_pass enum-ranges-u64-oct
}

@test 'enum max. value (unsigned 64-bit, binary) -> pass' {
  test_metadata_pass enum-ranges-u64-bin
}

@test 'enum max. value (signed 64-bit, decimal) -> pass' {
  test_metadata_pass enum-ranges-s64-dec
}

@test 'enum max. value (signed 64-bit, hexadecimal) -> pass' {
  test_metadata_pass enum-ranges-s64-hex
}

@test 'enum max. value (signed 64-bit, octal) -> pass' {
  test_metadata_pass enum-ranges-s64-oct
}

@test 'enum max. value (signed 64-bit, binary) -> pass' {
  test_metadata_pass enum-ranges-s64-bin
}

@test 'enum: named alias -> pass' {
  test_metadata_pass enum-alias
}

@test 'sequence: valid length (1) -> pass' {
  test_metadata_pass seq-length-1
}

@test 'sequence: valid length (2) -> pass' {
  test_metadata_pass seq-length-2
}

@test 'sequence: valid length (3) -> pass' {
  test_metadata_pass seq-length-3
}

@test 'sequence: valid length (4) -> pass' {
  test_metadata_pass seq-length-4
}

@test 'sequence: valid length (5) -> pass' {
  test_metadata_pass seq-length-5
}

@test 'sequence: valid length (6) -> pass' {
  test_metadata_pass seq-length-6
}

@test 'sequence: valid length (7) -> pass' {
  test_metadata_pass seq-length-7
}

@test 'sequence: valid length (8) -> pass' {
  test_metadata_pass seq-length-8
}

@test 'sequence: valid length (9) -> pass' {
  test_metadata_pass seq-length-9
}

@test 'sequence: valid length (10) -> pass' {
  test_metadata_pass seq-length-10
}

@test 'array: environment reference for length -> pass' {
  test_metadata_pass array-env
}

@test 'struct: named alias -> pass' {
  test_metadata_pass struct-alias
}

@test 'env: full block -> pass' {
  test_metadata_pass env-full
}

@test 'clock: full block -> pass' {
  test_metadata_pass clock-full
}

@test 'clock: negative offset (seconds) attribute -> pass' {
  test_metadata_pass clock-neg-offset-s
}

@test 'event: log levels -> pass' {
  test_metadata_pass event-with-loglevel
}

@test 'event: model.emf.uri -> pass' {
  test_metadata_pass event-with-model-emf-uri
}

@test 'callsite: full block -> pass' {
  test_metadata_pass callsite-full
}

@test 'syntax: escape sequences in literal string -> pass' {
  test_metadata_pass syntax-literal-string-escape-chars
}

@test 'syntax: extra semicolons -> pass' {
  test_metadata_pass syntax-extra-semicolons
}

@test 'type aliases everywhere -> pass' {
  test_metadata_pass typealiases-everywhere
}

@test 'type aliases with cross-reference -> pass' {
  test_metadata_pass typealiases-xref
}

@test 'typedefs everywhere -> pass' {
  test_metadata_pass typedefs-everywhere
}

@test 'CTF test suite: array-basic-1dim -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-1dim
}

@test 'CTF test suite: array-basic-2dim -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-2dim
}

@test 'CTF test suite: array-basic-2dim-2typedef -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-2dim-2typedef
}

@test 'CTF test suite: array-basic-2dim-typedef -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-2dim-typedef
}

@test 'CTF test suite: array-of-enum -> pass' {
  test_metadata_pass ctf-testsuite-array-of-enum
}

@test 'CTF test suite: array-of-struct -> pass' {
  test_metadata_pass ctf-testsuite-array-of-struct
}

@test 'CTF test suite: enum-nameless -> pass' {
  test_metadata_pass ctf-testsuite-enum-nameless
}

@test 'CTF test suite: enum-token-kind -> pass' {
  test_metadata_pass ctf-testsuite-enum-token-kind
}

@test 'CTF test suite: enum-untyped-int -> pass' {
  test_metadata_pass ctf-testsuite-enum-untyped-int
}

@test 'CTF test suite: enum-values-signed-big -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-signed-big
}

@test 'CTF test suite: enum-values-signed-small -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-signed-small
}

@test 'CTF test suite: enum-values-signed-value -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-signed-value
}

@test 'CTF test suite: enum-values-unsigned-big -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-unsigned-big
}

@test 'CTF test suite: event-id-integer -> pass' {
  test_metadata_pass ctf-testsuite-event-id-integer
}

@test 'CTF test suite: integer-1-bit-size -> pass' {
  test_metadata_pass ctf-testsuite-integer-1-bit-size
}

@test 'CTF test suite: literal-integers -> pass' {
  test_metadata_pass ctf-testsuite-literal-integers
}

@test 'CTF test suite: metadata-big-endian -> pass' {
  test_metadata_pass ctf-testsuite-metadata-big-endian
}

@test 'CTF test suite: metadata-minimal-accepted -> pass' {
  test_metadata_pass ctf-testsuite-metadata-minimal-accepted
}

@test 'CTF test suite: name-escaping-clashes -> pass' {
  test_metadata_pass ctf-testsuite-name-escaping-clashes
}

@test 'CTF test suite: name-escaping-empty -> pass' {
  test_metadata_pass ctf-testsuite-name-escaping-empty
}

@test 'CTF test suite: repeated-event-id-in-2-streams -> pass' {
  test_metadata_pass ctf-testsuite-repeated-event-id-in-2-streams
}

@test 'CTF test suite: sequence-basic-1dim -> pass' {
  test_metadata_pass ctf-testsuite-sequence-basic-1dim
}

@test 'CTF test suite: sequence-basic-2dim -> pass' {
  test_metadata_pass ctf-testsuite-sequence-basic-2dim
}

@test 'CTF test suite: sequence-scoped-length -> pass' {
  test_metadata_pass ctf-testsuite-sequence-scoped-length
}

@test 'CTF test suite: stream-undefined-id -> pass' {
  test_metadata_pass ctf-testsuite-stream-undefined-id
}

@test 'CTF test suite: struct-align-larger -> pass' {
  test_metadata_pass ctf-testsuite-struct-align-larger
}

@test 'CTF test suite: struct-align-smaller -> pass' {
  test_metadata_pass ctf-testsuite-struct-align-smaller
}

@test 'CTF test suite: struct-align-valid -> pass' {
  test_metadata_pass ctf-testsuite-struct-align-valid
}

@test 'CTF test suite: struct-inner-struct -> pass' {
  test_metadata_pass ctf-testsuite-struct-inner-struct
}

@test 'CTF test suite: struct-unamed-struct-as-field -> pass' {
  test_metadata_pass ctf-testsuite-struct-unamed-struct-as-field
}

@test 'CTF test suite: struct-underscores-in-fields -> pass' {
  test_metadata_pass ctf-testsuite-struct-underscores-in-fields
}

@test 'CTF test suite: typealias-reserved-keyword -> pass' {
  test_metadata_pass ctf-testsuite-typealias-reserved-keyword
}

@test 'CTF test suite: typealias-simple -> pass' {
  test_metadata_pass ctf-testsuite-typealias-simple
}

@test 'CTF test suite: typedef-simple -> pass' {
  test_metadata_pass ctf-testsuite-typedef-simple
}

@test 'CTF test suite: unknown-env -> pass' {
  test_metadata_pass ctf-testsuite-unknown-env
}

@test 'CTF test suite: variant-integers -> pass' {
  test_metadata_pass ctf-testsuite-variant-integers
}

@test 'CTF test suite: variant-integers-unnamed -> pass' {
  test_metadata_pass ctf-testsuite-variant-integers-unnamed
}

@test 'CTF test suite: variant-missing-selector -> pass' {
  test_metadata_pass ctf-testsuite-variant-missing-selector
}

@test 'CTF test suite: variant-scope-tag -> pass' {
  test_metadata_pass ctf-testsuite-variant-scope-tag
}

@test 'CTF test suite: variant-structs -> pass' {
  test_metadata_pass ctf-testsuite-variant-structs
}

@test 'CTF test suite: variant-two-levels -> pass' {
  test_metadata_pass ctf-testsuite-variant-two-levels
}

@test 'CTF test suite: variant-two-levels-redefinition -> pass' {
  test_metadata_pass ctf-testsuite-variant-two-levels-redefinition
}
