#!/usr/bin/env bats

# Copyright (C) 2018-2022 Philippe Proulx <eepp.ca>
#
# This software may be modified and distributed under the terms
# of the MIT license. See the LICENSE file for details.

assert_file_exists() {
  local file=$1

  if [[ ! -f "$BATS_TEST_DIRNAME/$file" ]]; then
    echo "FATAL: file \`$1\` does not exist" 1>&2
    return 1
  fi
}

metadata_text_tester_bin="$testers_path/metadata-text-tester"

test_metadata_fail() {
  local file="fail-$1"

  assert_file_exists "$file"
  run "$metadata_text_tester_bin" "$BATS_TEST_DIRNAME/$file"
  (($status == 2))
}

test_metadata_pass() {
  local file="pass-$1"

  assert_file_exists "$file"
  run "$metadata_text_tester_bin" "$BATS_TEST_DIRNAME/$file"
  (($status == 0))
}

#   __       _ _
#  / _| __ _(_) |
# | |_ / _` | | |
# |  _| (_| | | |
# |_|  \__,_|_|_|

@test 'metadata: empty -> fail' {
  test_metadata_fail metadata-empty
}

@test 'trace type: missing `major` attribute -> fail' {
  test_metadata_fail trace-type-missing-major-attr
}

@test 'trace type: missing `minor` attribute -> fail' {
  test_metadata_fail trace-type-missing-minor-attr
}

@test 'trace type: wrong `major` attribute -> fail' {
  test_metadata_fail trace-type-wrong-major-attr
}

@test 'trace type: wrong `minor` attribute -> fail' {
  test_metadata_fail trace-type-wrong-minor-attr
}

@test 'trace type: missing `byte_order` attribute -> fail' {
  test_metadata_fail trace-type-missing-bo-attr
}

@test 'trace type: wrong `byte_order` attribute -> fail' {
  test_metadata_fail trace-type-wrong-bo-attr
}

@test 'trace type: wrong `uuid` attribute (1) -> fail' {
  test_metadata_fail trace-type-wrong-uuid-attr-1
}

@test 'trace type: wrong `uuid` attribute (2) -> fail' {
  test_metadata_fail trace-type-wrong-uuid-attr-2
}

@test 'trace type: wrong `uuid` attribute (3) -> fail' {
  test_metadata_fail trace-type-wrong-uuid-attr-3
}

@test 'trace type: wrong `uuid` attribute (4) -> fail' {
  test_metadata_fail trace-type-wrong-uuid-attr-4
}

@test 'trace type: unknown attribute -> fail' {
  test_metadata_fail trace-type-unknown-attr
}

@test 'trace type: duplicate attribute -> fail' {
  test_metadata_fail trace-type-dup-attr
}

@test 'trace type: duplicate PH type -> fail' {
  test_metadata_fail trace-type-dup-ph-type
}

@test 'trace type: missing -> fail' {
  test_metadata_fail trace-type-missing
}

@test 'trace type: duplicate block -> fail' {
  test_metadata_fail trace-type-dup
}

@test 'trace type: PH type: invalid `magic` member (1) -> fail' {
  test_metadata_fail trace-type-ph-type-inval-magic-member-1
}

@test 'trace type: PH type: invalid `magic` member (2) -> fail' {
  test_metadata_fail trace-type-ph-type-inval-magic-member-2
}

@test 'trace type: PH type: missing `stream_id` member -> fail' {
  test_metadata_fail trace-type-ph-type-missing-stream-id-member
}

@test '`env` block: out of range (negative) -> fail' {
  test_metadata_fail env-out-of-range-neg
}

@test '`env` block: out of range (positive) -> fail' {
  test_metadata_fail env-out-of-range-pos
}

@test '`env` block: duplicate entry -> fail' {
  test_metadata_fail env-dup-entry
}

@test '`env` block: duplicate block -> fail' {
  test_metadata_fail env-dup
}

@test '`env` block: wrong entry -> fail' {
  test_metadata_fail env-wrong-entry
}

@test 'clock type: duplicate with same `name` attribute -> fail' {
  test_metadata_fail clk-type-dup
}

@test 'clock type: duplicate attribute -> fail' {
  test_metadata_fail clk-type-dup-attr
}

@test 'clock type: missing `name` attribute -> fail' {
  test_metadata_fail clk-type-missing-name-attr
}

@test 'clock type: unknown attribute -> fail' {
  test_metadata_fail clk-type-unknown-attr
}

@test 'clock type: wrong `description` attribute (1) -> fail' {
  test_metadata_fail clk-type-wrong-descr-attr-1
}

@test 'clock type: wrong `description` attribute (2) -> fail' {
  test_metadata_fail clk-type-wrong-descr-attr-2
}

@test 'clock type: wrong `frequency` attribute (1) -> fail' {
  test_metadata_fail clk-type-wrong-freq-attr-1
}

@test 'clock type: wrong `frequency` attribute (2) -> fail' {
  test_metadata_fail clk-type-wrong-freq-attr-2
}

@test 'clock type: wrong `frequency` attribute (3) -> fail' {
  test_metadata_fail clk-type-wrong-freq-attr-3
}

@test 'clock type: wrong `name` attribute -> fail' {
  test_metadata_fail clk-type-wrong-name-attr
}

@test 'clock type: wrong `offset` attribute (1) -> fail' {
  test_metadata_fail clk-type-wrong-offset-attr-1
}

@test 'clock type: wrong `offset` attribute (2) -> fail' {
  test_metadata_fail clk-type-wrong-offset-attr-2
}

@test 'clock type: wrong `offset_s` attribute -> fail' {
  test_metadata_fail clk-type-wrong-offset-s-attr
}

@test 'clock type: wrong `precision` attribute (1) -> fail' {
  test_metadata_fail clk-type-wrong-precision-attr-1
}

@test 'clock type: wrong `precision` attribute (2) -> fail' {
  test_metadata_fail clk-type-wrong-precision-attr-2
}

@test 'clock type: wrong `uuid` attribute (1) -> fail' {
  test_metadata_fail clk-type-wrong-uuid-attr-1
}

@test 'clock type: wrong `uuid` attribute (2) -> fail' {
  test_metadata_fail clk-type-wrong-uuid-attr-2
}

@test 'clock type: wrong `uuid` attribute (3) -> fail' {
  test_metadata_fail clk-type-wrong-uuid-attr-3
}

@test 'clock type: wrong `uuid` attribute (4) -> fail' {
  test_metadata_fail clk-type-wrong-uuid-attr-4
}

@test 'clock type: wrong `absolute` attribute (1) -> fail' {
  test_metadata_fail clk-type-wrong-absolute-attr-1
}

@test 'clock type: wrong `absolute` attribute (2) -> fail' {
  test_metadata_fail clk-type-wrong-absolute-attr-2
}

@test 'data stream type: missing `id` attribute -> fail' {
  test_metadata_fail dst-missing-id-attr
}

@test 'data stream type: unknown attribute -> fail' {
  test_metadata_fail dst-unknown-attr
}

@test 'data stream type: duplicate attribute -> fail' {
  test_metadata_fail dst-dup-attr
}

@test 'data stream type: wrong `id` attribute -> fail' {
  test_metadata_fail dst-wrong-id-attr
}

@test 'data stream type: duplicate with same `id` attribute -> fail' {
  test_metadata_fail dst-dup
}

@test 'data stream type: duplicate PC type -> fail' {
  test_metadata_fail dst-dup-pc-type
}

@test 'data stream type: duplicate ERH type -> fail' {
  test_metadata_fail dst-dup-erh-type
}

@test 'data stream type: duplicate ERCC type -> fail' {
  test_metadata_fail dst-dup-ercc-type
}

@test 'event record type: unknown attribute -> fail' {
  test_metadata_fail ert-unknown-attr
}

@test 'event record type: duplicate attribute -> fail' {
  test_metadata_fail ert-dup-attr
}

@test 'event record type: missing stream ID attribute -> fail' {
  test_metadata_fail ert-missing-stream-id-attr
}

@test 'event record type: missing `id` attribute -> fail' {
  test_metadata_fail ert-missing-id-attr
}

@test 'event record type: wrong `id` attribute -> fail' {
  test_metadata_fail ert-wrong-id-attr
}

@test 'event record type: wrong `stream_id` attribute -> fail' {
  test_metadata_fail ert-wrong-stream-id-attr
}

@test 'event record type: wrong `name` attribute -> fail' {
  test_metadata_fail ert-wrong-name-attr
}

@test 'event record type: wrong `loglevel` attribute -> fail' {
  test_metadata_fail ert-wrong-log-level-attr
}

@test 'event record type: wrong `model.emf.uri` attribute -> fail' {
  test_metadata_fail ert-wrong-model-emf-uri-attr
}

@test 'event record type: duplicate with same `id` attribute -> fail' {
  test_metadata_fail ert-dup
}

@test 'event record type: duplicate with same `id` attribute, one after DST block -> fail' {
  test_metadata_fail ert-dup-after-dst
}

@test 'event record type: empty (1) -> fail' {
  test_metadata_fail ert-empty-1
}

@test 'event record type: empty (2) -> fail' {
  test_metadata_fail ert-empty-2
}

@test 'event record type: empty (3) -> fail' {
  test_metadata_fail ert-empty-3
}

@test 'event record type: empty (4) -> fail' {
  test_metadata_fail ert-empty-4
}

@test 'event record type: empty (5) -> fail' {
  test_metadata_fail ert-empty-5
}

@test 'event record type: duplicate specific context type -> fail' {
  test_metadata_fail ert-dup-sc-type
}

@test 'event record type: duplicate payload type -> fail' {
  test_metadata_fail ert-dup-p-type
}

@test 'event record type: `loglevel` attribute is out of range -> fail' {
  test_metadata_fail ert-log-level-attr-out-of-range
}

@test 'data type alias: duplicate with same name -> fail' {
  test_metadata_fail dt-alias-dup
}

@test 'data type alias: length type of dynamic-length array type outside alias scope -> fail' {
  test_metadata_fail dt-alias-dl-array-type-len-type-outside
}

@test 'data type alias: length type of dynamic-length string type outside alias scope -> fail' {
  test_metadata_fail dt-alias-dl-str-type-len-type-outside
}

@test 'syntax: missing `;` after `trace` block -> fail' {
  test_metadata_fail syntax-trace-block-missing-semi
}

@test 'syntax: missing `;` after `stream` block -> fail' {
  test_metadata_fail syntax-stream-block-missing-semi
}

@test 'syntax: missing `;` after `event` block -> fail' {
  test_metadata_fail syntax-event-block-missing-semi
}

@test 'syntax: missing `;` after `clock` block -> fail' {
  test_metadata_fail syntax-clock-block-missing-semi
}

@test 'syntax: missing `;` after `env` block -> fail' {
  test_metadata_fail syntax-env-block-missing-semi
}

@test 'syntax: missing `;` after data type alias block -> fail' {
  test_metadata_fail syntax-dt-alias-block-missing-semi
}

@test 'syntax: open quoted literal string -> fail' {
  test_metadata_fail syntax-open-quoted-literal
}

@test 'syntax: attribute: missing `=` after name -> fail' {
  test_metadata_fail syntax-attr-missing-equal
}

@test 'syntax: attribute: missing value after `=` -> fail' {
  test_metadata_fail syntax-attr-missing-val
}

@test 'syntax: attribute: missing `;` after value -> fail' {
  test_metadata_fail syntax-attr-missing-semi
}

@test 'syntax: attribute: missing name -> fail' {
  test_metadata_fail syntax-attr-missing-name
}

@test 'syntax: attribute: invalid value -> fail' {
  test_metadata_fail syntax-attr-inval-val
}

@test 'syntax: data type alias: missing `:=` -> fail' {
  test_metadata_fail syntax-dt-alias-block-missing-assign
}

@test 'syntax: data type alias: missing name -> fail' {
  test_metadata_fail syntax-dt-alias-block-missing-name
}

@test 'syntax: data type alias: wrong name -> fail' {
  test_metadata_fail syntax-dt-alias-block-wrong-name
}

@test 'syntax: data type alias: missing data type -> fail' {
  test_metadata_fail syntax-dt-alias-block-missing-dt
}

@test 'syntax: unexpected end of file -> fail' {
  test_metadata_fail syntax-eof
}

@test 'syntax: structure type: expecting member type or data type alias -> fail' {
  test_metadata_fail syntax-struct-type-member-type
}

@test 'syntax: variant type: expecting option or data type alias -> fail' {
  test_metadata_fail syntax-var-type-opt
}

@test 'syntax: data type alias: reserved word name (1) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-1
}

@test 'syntax: data type alias: reserved word name (2) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-2
}

@test 'syntax: data type alias: reserved word name (3) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-3
}

@test 'syntax: data type alias: reserved word name (4) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-4
}

@test 'syntax: data type alias: reserved word name (5) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-5
}

@test 'syntax: data type alias: reserved word name (6) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-6
}

@test 'syntax: data type alias: reserved word name (7) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-7
}

@test 'syntax: data type alias: reserved word name (8) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-8
}

@test 'syntax: data type alias: reserved word name (9) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-9
}

@test 'syntax: data type alias: reserved word name (10) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-10
}

@test 'syntax: data type alias: reserved word name (11) -> fail' {
  test_metadata_fail syntax-dt-alias-block-reserved-name-11
}

@test 'fixed-length integer type: negative `align` attribute -> fail' {
  test_metadata_fail fl-int-type-align-attr-neg
}

@test 'fixed-length integer type: non-power-of-two `align` attribute -> fail' {
  test_metadata_fail fl-int-type-align-attr-non-pow2
}

@test 'fixed-length integer type: zero `align` attribute -> fail' {
  test_metadata_fail fl-int-type-align-attr-zero
}

@test 'fixed-length integer type: duplicate attribute -> fail' {
  test_metadata_fail fl-int-type-dup-attr
}

@test 'fixed-length integer type: unknown mapped clock type name (`map` attribute) -> fail' {
  test_metadata_fail fl-int-type-map-attr-unknown-clk-type-name
}

@test 'fixed-length integer type: missing `size` attribute -> fail' {
  test_metadata_fail fl-int-type-missing-size-attr
}

@test 'fixed-length integer type: negative `size` attribute -> fail' {
  test_metadata_fail fl-int-type-size-attr-neg
}

@test 'fixed-length integer type: zero `size` attribute -> fail' {
  test_metadata_fail fl-int-type-size-attr-zero
}

@test 'fixed-length integer type: `size` attribute is too large -> fail' {
  test_metadata_fail fl-int-type-size-attr-too-large
}

@test 'fixed-length integer type: unknown attribute -> fail' {
  test_metadata_fail fl-int-type-unknown-attr
}

@test 'fixed-length integer type: wrong `base` attribute (1) -> fail' {
  test_metadata_fail fl-int-type-wrong-base-attr-1
}

@test 'fixed-length integer type: wrong `base` attribute (2) -> fail' {
  test_metadata_fail fl-int-type-wrong-base-attr-2
}

@test 'fixed-length integer type: wrong `base` attribute (3) -> fail' {
  test_metadata_fail fl-int-type-wrong-base-attr-3
}

@test 'fixed-length integer type: wrong `byte_order` attribute (1) -> fail' {
  test_metadata_fail fl-int-type-wrong-bo-attr-1
}

@test 'fixed-length integer type: wrong `byte_order` attribute (2) -> fail' {
  test_metadata_fail fl-int-type-wrong-bo-attr-2
}

@test 'fixed-length integer type: wrong `encoding` attribute (1) -> fail' {
  test_metadata_fail fl-int-type-wrong-encoding-attr-1
}

@test 'fixed-length integer type: wrong `encoding` attribute (2) -> fail' {
  test_metadata_fail fl-int-type-wrong-encoding-attr-2
}

@test 'fixed-length integer type: wrong `map` attribute (1) -> fail' {
  test_metadata_fail fl-int-type-wrong-map-attr-1
}

@test 'fixed-length integer type: wrong `map` attribute (2) -> fail' {
  test_metadata_fail fl-int-type-wrong-map-attr-2
}

@test 'fixed-length integer type: wrong `signed` attribute (1) -> fail' {
  test_metadata_fail fl-int-type-wrong-signed-attr-1
}

@test 'fixed-length integer type: wrong `signed` attribute (2) -> fail' {
  test_metadata_fail fl-int-type-wrong-signed-attr-2
}

@test 'fixed-length integer type: wrong `signed` attribute (3) -> fail' {
  test_metadata_fail fl-int-type-wrong-signed-attr-3
}

@test 'fixed-length integer type: wrong `size` attribute -> fail' {
  test_metadata_fail fl-int-type-wrong-size-attr
}

@test 'fixed-length floating point number type: duplicate attribute -> fail' {
  test_metadata_fail fl-float-type-dup-attr
}

@test 'fixed-length floating point number type: missing `exp_dig` attribute -> fail' {
  test_metadata_fail fl-float-type-missing-exp-dig-attr
}

@test 'fixed-length floating point number type: missing `mant_dig` attribute -> fail' {
  test_metadata_fail fl-float-type-missing-mant-dig-attr
}

@test 'fixed-length floating point number type: unknown attribute -> fail' {
  test_metadata_fail fl-float-type-unknown-attr
}

@test 'fixed-length floating point number type: wrong `exp_dig` attribute (1) -> fail' {
  test_metadata_fail fl-float-type-wrong-exp-dig-attr-1
}

@test 'fixed-length floating point number type: wrong `exp_dig` attribute (2) -> fail' {
  test_metadata_fail fl-float-type-wrong-exp-dig-attr-2
}

@test 'fixed-length floating point number type: wrong `mant_dig` attribute (1) -> fail' {
  test_metadata_fail fl-float-type-wrong-mant-dig-attr-1
}

@test 'fixed-length floating point number type: wrong `mant_dig` attribute (2) -> fail' {
  test_metadata_fail fl-float-type-wrong-mant-dig-attr-2
}

@test 'null-terminated string type: duplicate attribute -> fail' {
  test_metadata_fail nt-str-type-dup-attr
}

@test 'null-terminated string type: unknown attribute -> fail' {
  test_metadata_fail nt-str-type-unknown-attr
}

@test 'null-terminated string type: wrong `encoding` attribute -> fail' {
  test_metadata_fail nt-str-type-wrong-encoding-attr
}

@test 'structure type: negative minimum alignment -> fail' {
  test_metadata_fail struct-type-min-align-neg
}

@test 'structure type: non-power-of-two minimum alignment -> fail' {
  test_metadata_fail struct-type-min-align-non-pow2
}

@test 'structure type: zero alignment -> fail' {
  test_metadata_fail struct-type-min-align-zero
}

@test 'structure type: duplicate member type -> fail' {
  test_metadata_fail struct-type-dup-member-type
}

@test 'structure type: duplicate data type alias -> fail' {
  test_metadata_fail struct-type-dup-dt-alias
}

@test 'structure type: member type uses data type alias defined after it -> fail' {
  test_metadata_fail struct-type-member-type-dt-alias-after
}

@test 'structure type: member type uses unknown data type alias -> fail' {
  test_metadata_fail struct-type-member-type-unknown-dt-alias
}

@test 'fixed-length enumeration type: inversed lower and upper enumerator value -> fail' {
  test_metadata_fail fl-enum-type-inversed-lower-upper-vals
}

@test 'fixed-length enumeration type: length is too small (1) -> fail' {
  test_metadata_fail fl-enum-type-len-too-small-1
}

@test 'fixed-length enumeration type: length is too small (2) -> fail' {
  test_metadata_fail fl-enum-type-len-too-small-2
}

@test 'fixed-length enumeration type: missing `int` data type alias -> fail' {
  test_metadata_fail fl-enum-type-missing-int-dt-alias
}

@test 'fixed-length enumeration type: integer type alias is not an integer type -> fail' {
  test_metadata_fail fl-enum-type-wrong-int-dt-alias
}

@test 'fixed-length enumeration type: enumerator value is out of range (1) -> fail' {
  test_metadata_fail fl-enum-type-val-out-of-range-1
}

@test 'fixed-length enumeration type: enumerator value is out of range (2) -> fail' {
  test_metadata_fail fl-enum-type-val-out-of-range-2
}

@test 'fixed-length enumeration type: enumerator value is out of range (3) -> fail' {
  test_metadata_fail fl-enum-type-val-out-of-range-3
}

@test 'fixed-length enumeration type: enumerator value is out of range (4) -> fail' {
  test_metadata_fail fl-enum-type-val-out-of-range-4
}

@test 'fixed-length enumeration type: enumerator value is out of range (5) -> fail' {
  test_metadata_fail fl-enum-type-val-out-of-range-5
}

@test 'fixed-length enumeration type: unknown integer type alias -> fail' {
  test_metadata_fail fl-enum-type-unknown-int-dt-alias
}

@test 'fixed-length enumeration type: wrong integer type -> fail' {
  test_metadata_fail fl-enum-type-wrong-fl-int-type
}

@test 'variant type: empty body (no options) -> fail' {
  test_metadata_fail var-type-empty
}

@test 'variant type: duplicate option -> fail' {
  test_metadata_fail var-type-dup-opt
}

@test 'variant type: empty selector location (1) -> fail' {
  test_metadata_fail var-type-empty-sel-loc-1
}

@test 'variant type: empty selector location (2) -> fail' {
  test_metadata_fail var-type-empty-sel-loc-2
}

@test 'variant type: selector type is not an enumeration type -> fail' {
  test_metadata_fail var-type-sel-type-not-fl-enum-type
}

@test 'variant type: invalid selector location (1) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-1
}

@test 'variant type: invalid selector location (2) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-2
}

@test 'variant type: invalid selector location (3) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-3
}

@test 'variant type: invalid selector location (4) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-4
}

@test 'variant type: invalid selector location (5) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-5
}

@test 'variant type: invalid selector location (6) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-6
}

@test 'variant type: invalid selector location (7) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-7
}

@test 'variant type: invalid selector location (8) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-8
}

@test 'variant type: invalid selector location (9) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-9
}

@test 'variant type: invalid selector location (10) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-10
}

@test 'variant type: invalid selector location (11) -> fail' {
  test_metadata_fail var-type-inval-sel-loc-11
}

@test 'variant type: missing selector location (as member type) (1) -> fail' {
  test_metadata_fail var-type-missing-sel-loc-1
}

@test 'variant type: missing selector location (as member type) (2) -> fail' {
  test_metadata_fail var-type-missing-sel-loc-2
}

@test 'variant type: wrong selector location -> fail' {
  test_metadata_fail var-type-wrong-sel-loc
}

@test 'variant type: named variant type with relative selector location -> fail' {
  test_metadata_fail var-type-named-rel-sel-loc
}

@test 'static-length array type: empty length -> fail' {
  test_metadata_fail sl-array-type-len-empty
}

@test 'static-length array type: length is negative -> fail' {
  test_metadata_fail sl-array-type-len-neg
}

@test 'static-length array type: wrong length -> fail' {
  test_metadata_fail sl-array-type-wrong-len
}

@test 'static-length array type: negative length through `env` reference -> fail' {
  test_metadata_fail sl-array-type-env-ref-len-neg
}

@test 'static-length array type: `env` reference with missing `env` block -> fail' {
  test_metadata_fail sl-array-type-env-ref-missing-env-block
}

@test 'static-length array type: missing `env` reference key -> fail' {
  test_metadata_fail sl-array-type-env-ref-missing-key
}

@test 'static-length array type: missing `env` reference entry -> fail' {
  test_metadata_fail sl-array-type-env-ref-missing
}

@test 'static-length array type: `env` reference is too long -> fail' {
  test_metadata_fail sl-array-type-env-ref-too-long
}

@test 'static-length array type: `env` reference is a string -> fail' {
  test_metadata_fail sl-array-type-env-ref-str-val
}

@test 'static-length string type: empty length -> fail' {
  test_metadata_fail sl-str-type-len-empty
}

@test 'static-length string type: length is negative -> fail' {
  test_metadata_fail sl-str-type-len-neg
}

@test 'static-length string type: wrong length -> fail' {
  test_metadata_fail sl-str-type-wrong-len
}

@test 'static-length string type: negative length through `env` reference -> fail' {
  test_metadata_fail sl-str-type-env-ref-len-neg
}

@test 'static-length string type: `env` reference with missing `env` block -> fail' {
  test_metadata_fail sl-str-type-env-ref-missing-env-block
}

@test 'static-length string type: missing `env` reference key -> fail' {
  test_metadata_fail sl-str-type-env-ref-missing-key
}

@test 'static-length string type: missing `env` reference entry -> fail' {
  test_metadata_fail sl-str-type-env-ref-missing
}

@test 'static-length string type: `env` reference is too long -> fail' {
  test_metadata_fail sl-str-type-env-ref-too-long
}

@test 'static-length string type: `env` reference is a string -> fail' {
  test_metadata_fail sl-str-type-env-ref-str-val
}

@test 'dynamic-length array type: invalid length location (1) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-1
}

@test 'dynamic-length array type: invalid length location (2) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-2
}

@test 'dynamic-length array type: invalid length location (3) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-3
}

@test 'dynamic-length array type: invalid length location (4) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-4
}

@test 'dynamic-length array type: invalid length location (5) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-5
}

@test 'dynamic-length array type: invalid length location (6) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-6
}

@test 'dynamic-length array type: invalid length location (7) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-7
}

@test 'dynamic-length array type: invalid length location (8) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-8
}

@test 'dynamic-length array type: invalid length location (9) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-9
}

@test 'dynamic-length array type: invalid length location (10) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-10
}

@test 'dynamic-length array type: invalid length location (11) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-11
}

@test 'dynamic-length array type: invalid length location (12) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-12
}

@test 'dynamic-length array type: invalid length location (13) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-13
}

@test 'dynamic-length array type: invalid length location (14) -> fail' {
  test_metadata_fail dl-array-type-inval-len-loc-14
}

@test 'dynamic-length string type: invalid length location (1) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-1
}

@test 'dynamic-length string type: invalid length location (2) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-2
}

@test 'dynamic-length string type: invalid length location (3) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-3
}

@test 'dynamic-length string type: invalid length location (4) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-4
}

@test 'dynamic-length string type: invalid length location (5) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-5
}

@test 'dynamic-length string type: invalid length location (6) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-6
}

@test 'dynamic-length string type: invalid length location (7) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-7
}

@test 'dynamic-length string type: invalid length location (8) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-8
}

@test 'dynamic-length string type: invalid length location (9) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-9
}

@test 'dynamic-length string type: invalid length location (10) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-10
}

@test 'dynamic-length string type: invalid length location (11) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-11
}

@test 'dynamic-length string type: invalid length location (12) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-12
}

@test 'dynamic-length string type: invalid length location (13) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-13
}

@test 'dynamic-length string type: invalid length location (14) -> fail' {
  test_metadata_fail dl-str-type-inval-len-loc-14
}

@test 'CTF test suite: `array-redefinition` -> fail' {
  test_metadata_fail ctf-testsuite-array-redefinition
}

@test 'CTF test suite: `array-size-identifier` -> fail' {
  test_metadata_fail ctf-testsuite-array-size-identifier
}

@test 'CTF test suite: `array-size-keyword` -> fail' {
  test_metadata_fail ctf-testsuite-array-size-keyword
}

@test 'CTF test suite: `array-size-negative` -> fail' {
  test_metadata_fail ctf-testsuite-array-size-negative
}

@test 'CTF test suite: `array-size-not-present` -> fail' {
  test_metadata_fail ctf-testsuite-array-size-not-present
}

@test 'CTF test suite: `array-size-string` -> fail' {
  test_metadata_fail ctf-testsuite-array-size-string
}

@test 'CTF test suite: `array-size-type` -> fail' {
  test_metadata_fail ctf-testsuite-array-size-type
}

@test 'CTF test suite: `array-size-type-field` -> fail' {
  test_metadata_fail ctf-testsuite-array-size-type-field
}

@test 'CTF test suite: `enum-empty` -> fail' {
  test_metadata_fail ctf-testsuite-enum-empty
}

@test 'CTF test suite: `enum-field-value-out-of-range` -> fail' {
  test_metadata_fail ctf-testsuite-enum-field-value-out-of-range
}

@test 'CTF test suite: `enum-type-implicit-but-undefined-int-type` -> fail' {
  test_metadata_fail ctf-testsuite-enum-type-implicit-but-undefined-int-type
}

@test 'CTF test suite: `enum-type-negative-out-of-range` -> fail' {
  test_metadata_fail ctf-testsuite-enum-type-negative-out-of-range
}

@test 'CTF test suite: `enum-type-value-out-of-range` -> fail' {
  test_metadata_fail ctf-testsuite-enum-type-value-out-of-range
}

@test 'CTF test suite: `enum-untyped-missing-int` -> fail' {
  test_metadata_fail ctf-testsuite-enum-untyped-missing-int
}

@test 'CTF test suite: `enum-untyped-string` -> fail' {
  test_metadata_fail ctf-testsuite-enum-untyped-string
}

@test 'CTF test suite: `enum-values-floating` -> fail' {
  test_metadata_fail ctf-testsuite-enum-values-floating
}

@test 'CTF test suite: `enum-values-token` -> fail' {
  test_metadata_fail ctf-testsuite-enum-values-token
}

@test 'CTF test suite: `enum-values-too-small` -> fail' {
  test_metadata_fail ctf-testsuite-enum-values-too-small
}

@test 'CTF test suite: `event-id-string` -> fail' {
  test_metadata_fail ctf-testsuite-event-id-string
}

@test 'CTF test suite: `event-id-struct` -> fail' {
  test_metadata_fail ctf-testsuite-event-id-struct
}

@test 'CTF test suite: `integer-0-bit-size` -> fail' {
  test_metadata_fail ctf-testsuite-integer-0-bit-size
}

@test 'CTF test suite: `integer-align-as-string` -> fail' {
  test_metadata_fail ctf-testsuite-integer-align-as-string
}

@test 'CTF test suite: `integer-align-negative` -> fail' {
  test_metadata_fail ctf-testsuite-integer-align-negative
}

@test 'CTF test suite: `integer-align-non-power-2` -> fail' {
  test_metadata_fail ctf-testsuite-integer-align-non-power-2
}

@test 'CTF test suite: `integer-base-as-string` -> fail' {
  test_metadata_fail ctf-testsuite-integer-base-as-string
}

@test 'CTF test suite: `integer-base-invalid` -> fail' {
  test_metadata_fail ctf-testsuite-integer-base-invalid
}

@test 'CTF test suite: `integer-byte-order-invalid` -> fail' {
  test_metadata_fail ctf-testsuite-integer-byte-order-invalid
}

@test 'CTF test suite: `integer-encoding-as-string` -> fail' {
  test_metadata_fail ctf-testsuite-integer-encoding-as-string
}

@test 'CTF test suite: `integer-encoding-invalid` -> fail' {
  test_metadata_fail ctf-testsuite-integer-encoding-invalid
}

@test 'CTF test suite: `integer-negative-bit-size` -> fail' {
  test_metadata_fail ctf-testsuite-integer-negative-bit-size
}

@test 'CTF test suite: `integer-range` -> fail' {
  test_metadata_fail ctf-testsuite-integer-range
}

@test 'CTF test suite: `integer-signed-as-string` -> fail' {
  test_metadata_fail ctf-testsuite-integer-signed-as-string
}

@test 'CTF test suite: `integer-signed-invalid` -> fail' {
  test_metadata_fail ctf-testsuite-integer-signed-invalid
}

@test 'CTF test suite: `integer-size-as-string` -> fail' {
  test_metadata_fail ctf-testsuite-integer-size-as-string
}

@test 'CTF test suite: `integer-size-missing` -> fail' {
  test_metadata_fail ctf-testsuite-integer-size-missing
}

@test 'CTF test suite: `integer-size-negative` -> fail' {
  test_metadata_fail ctf-testsuite-integer-size-negative
}

@test 'CTF test suite: `lexer-literal-guid-corrupted` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-guid-corrupted
}

@test 'CTF test suite: `lexer-literal-guid-too-big` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-guid-too-big
}

@test 'CTF test suite: `lexer-literal-guid-too-small` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-guid-too-small
}

@test 'CTF test suite: `lexer-literal-int-incomplete` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-literal-int-incomplete
}

@test 'CTF test suite: `lexer-unterminated-bracket` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-bracket
}

@test 'CTF test suite: `lexer-unterminated-declaration` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-declaration
}

@test 'CTF test suite: `lexer-unterminated-expression` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-expression
}

@test 'CTF test suite: `lexer-unterminated-string` -> fail' {
  test_metadata_fail ctf-testsuite-lexer-unterminated-string
}

@test 'CTF test suite: `metadata-empty-after-header` -> fail' {
  test_metadata_fail ctf-testsuite-metadata-empty-after-header
}

@test 'CTF test suite: `metadata-with-null-char` -> fail' {
  test_metadata_fail ctf-testsuite-metadata-with-null-char
}

@test 'CTF test suite: `repeated-event-id-in-same-stream` -> fail' {
  test_metadata_fail ctf-testsuite-repeated-event-id-in-same-stream
}

@test 'CTF test suite: `string-concat` -> fail' {
  test_metadata_fail ctf-testsuite-string-concat
}

@test 'CTF test suite: `struct-align-enum` -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-enum
}

@test 'CTF test suite: `struct-align-huge` -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-huge
}

@test 'CTF test suite: `struct-align-negative` -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-negative
}

@test 'CTF test suite: `struct-align-string` -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-string
}

@test 'CTF test suite: `struct-align-zero` -> fail' {
  test_metadata_fail ctf-testsuite-struct-align-zero
}

@test 'CTF test suite: `struct-duplicate-field-name` -> fail' {
  test_metadata_fail ctf-testsuite-struct-duplicate-field-name
}

@test 'CTF test suite: `struct-duplicate-struct-name` -> fail' {
  test_metadata_fail ctf-testsuite-struct-duplicate-struct-name
}

@test 'CTF test suite: `struct-inner-struct-undefined` -> fail' {
  test_metadata_fail ctf-testsuite-struct-inner-struct-undefined
}

@test 'CTF test suite: `struct-fl-int-type-undefined` -> fail' {
  test_metadata_fail ctf-testsuite-struct-int-type-undefined
}

@test 'CTF test suite: `struct-recursive` -> fail' {
  test_metadata_fail ctf-testsuite-struct-recursive
}

@test 'CTF test suite: `typealias-duplicate-name` -> fail' {
  test_metadata_fail ctf-testsuite-typealias-duplicate-name
}

@test 'CTF test suite: `typealias-invalid-type-kind` -> fail' {
  test_metadata_fail ctf-testsuite-typealias-invalid-type-kind
}

@test 'CTF test suite: `typealias-reserved-keyword` -> fail' {
  test_metadata_fail ctf-testsuite-typealias-reserved-keyword
}

@test 'CTF test suite: `typedef-redefinition` -> fail' {
  test_metadata_fail ctf-testsuite-typedef-redefinition
}

@test 'CTF test suite: `variant-missing-tag` -> fail' {
  test_metadata_fail ctf-testsuite-variant-missing-tag
}

@test 'CTF test suite: `variant-string-fields` -> fail' {
  test_metadata_fail ctf-testsuite-variant-string-fields
}

@test 'CTF test suite: `variant-tag-integer` -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-integer
}

@test 'CTF test suite: `variant-tag-string` -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-string
}

@test 'CTF test suite: `variant-tag-type-floating` -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-type-floating
}

@test 'CTF test suite: `variant-tag-type-string` -> fail' {
  test_metadata_fail ctf-testsuite-variant-tag-type-string
}

#  _ __   __ _ ___ ___
# | '_ \ / _` / __/ __|
# | |_) | (_| \__ \__ \
# | .__/ \__,_|___/___/
# |_|

@test 'LTTng-modules 2.7.0 (1300+ event record classes) -> pass' {
  test_metadata_pass lttng-modules-2.7.0
}

@test 'LTTng-modules 2.9.2 (1300+ event record classes) -> pass' {
  test_metadata_pass lttng-modules-2.9.2
}

@test 'LTTng-UST 2.11.0-rc1-40-gf82f93a1 (with DST blocks after ERT blocks) -> pass' {
  test_metadata_pass lttng-ust-2.11.0-rc1-40-gf82f93a1-dst-after-ert
}

@test 'fixed-length integer type: full -> pass' {
  test_metadata_pass fl-int-type-full
}

@test 'fixed-length integer type: signed with encoding -> pass' {
  test_metadata_pass fl-int-type-signed-encoding
}

@test 'fixed-length floating point number type: full -> pass' {
  test_metadata_pass fl-float-type-full
}

@test 'null-terminated string type: full -> pass' {
  test_metadata_pass nt-str-type-full
}

@test 'fixed-length enumeration type: maximum value (unsigned 64-bit, decimal) -> pass' {
  test_metadata_pass fl-enum-type-ranges-u64-dec
}

@test 'fixed-length enumeration type: maximum value (unsigned 64-bit, hexadecimal) -> pass' {
  test_metadata_pass fl-enum-type-ranges-u64-hex
}

@test 'fixed-length enumeration type: maximum value (unsigned 64-bit, octal) -> pass' {
  test_metadata_pass fl-enum-type-ranges-u64-oct
}

@test 'fixed-length enumeration type: maximum value (unsigned 64-bit, binary) -> pass' {
  test_metadata_pass fl-enum-type-ranges-u64-bin
}

@test 'fixed-length enumeration type: maximum value (signed 64-bit, decimal) -> pass' {
  test_metadata_pass fl-enum-type-ranges-s64-dec
}

@test 'fixed-length enumeration type: maximum value (signed 64-bit, hexadecimal) -> pass' {
  test_metadata_pass fl-enum-type-ranges-s64-hex
}

@test 'fixed-length enumeration type: maximum value (signed 64-bit, octal) -> pass' {
  test_metadata_pass fl-enum-type-ranges-s64-oct
}

@test 'fixed-length enumeration type: maximum value (signed 64-bit, binary) -> pass' {
  test_metadata_pass fl-enum-type-ranges-s64-bin
}

@test 'fixed-length enumeration type: named alias -> pass' {
  test_metadata_pass fl-enum-type-alias
}

@test 'dynamic-length array type: valid length location (1) -> pass' {
  test_metadata_pass dl-array-type-len-loc-1
}

@test 'dynamic-length array type: valid length location (2) -> pass' {
  test_metadata_pass dl-array-type-len-loc-2
}

@test 'dynamic-length array type: valid length location (3) -> pass' {
  test_metadata_pass dl-array-type-len-loc-3
}

@test 'dynamic-length array type: valid length location (4) -> pass' {
  test_metadata_pass dl-array-type-len-loc-4
}

@test 'dynamic-length array type: valid length location (5) -> pass' {
  test_metadata_pass dl-array-type-len-loc-5
}

@test 'dynamic-length array type: valid length location (6) -> pass' {
  test_metadata_pass dl-array-type-len-loc-6
}

@test 'dynamic-length array type: valid length location (7) -> pass' {
  test_metadata_pass dl-array-type-len-loc-7
}

@test 'dynamic-length array type: valid length location (8) -> pass' {
  test_metadata_pass dl-array-type-len-loc-8
}

@test 'dynamic-length array type: valid length location (9) -> pass' {
  test_metadata_pass dl-array-type-len-loc-9
}

@test 'dynamic-length array type: valid length location (10) -> pass' {
  test_metadata_pass dl-array-type-len-loc-10
}

@test 'dynamic-length array type: valid length location: multiple length types (1) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-1
}

@test 'dynamic-length array type: valid length location: multiple length types (2) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-2
}

@test 'dynamic-length array type: valid length location: multiple length types (3) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-3
}

@test 'dynamic-length array type: valid length location: multiple length types (4) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-4
}

@test 'dynamic-length array type: valid length location: multiple length types (5) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-5
}

@test 'dynamic-length array type: valid length location: multiple length types (6) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-6
}

@test 'dynamic-length array type: valid length location: multiple length types (7) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-7
}

@test 'dynamic-length array type: valid length location: multiple length types (8) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-8
}

@test 'dynamic-length array type: valid length location: multiple length types (9) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-9
}

@test 'dynamic-length array type: valid length location: multiple length types (10) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-10
}

@test 'dynamic-length array type: valid length location: multiple length types (11) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-11
}

@test 'dynamic-length array type: valid length location: multiple length types (12) -> pass' {
  test_metadata_pass dl-array-type-len-loc-multi-12
}

@test 'dynamic-length string type: valid length location (1) -> pass' {
  test_metadata_pass dl-str-type-len-loc-1
}

@test 'dynamic-length string type: valid length location (2) -> pass' {
  test_metadata_pass dl-str-type-len-loc-2
}

@test 'dynamic-length string type: valid length location (3) -> pass' {
  test_metadata_pass dl-str-type-len-loc-3
}

@test 'dynamic-length string type: valid length location (4) -> pass' {
  test_metadata_pass dl-str-type-len-loc-4
}

@test 'dynamic-length string type: valid length location (5) -> pass' {
  test_metadata_pass dl-str-type-len-loc-5
}

@test 'dynamic-length string type: valid length location (6) -> pass' {
  test_metadata_pass dl-str-type-len-loc-6
}

@test 'dynamic-length string type: valid length location (7) -> pass' {
  test_metadata_pass dl-str-type-len-loc-7
}

@test 'dynamic-length string type: valid length location (8) -> pass' {
  test_metadata_pass dl-str-type-len-loc-8
}

@test 'dynamic-length string type: valid length location (9) -> pass' {
  test_metadata_pass dl-str-type-len-loc-9
}

@test 'dynamic-length string type: valid length location (10) -> pass' {
  test_metadata_pass dl-str-type-len-loc-10
}

@test 'dynamic-length string type: valid length location: multiple length types (1) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-1
}

@test 'dynamic-length string type: valid length location: multiple length types (2) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-2
}

@test 'dynamic-length string type: valid length location: multiple length types (3) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-3
}

@test 'dynamic-length string type: valid length location: multiple length types (4) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-4
}

@test 'dynamic-length string type: valid length location: multiple length types (5) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-5
}

@test 'dynamic-length string type: valid length location: multiple length types (6) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-6
}

@test 'dynamic-length string type: valid length location: multiple length types (7) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-7
}

@test 'dynamic-length string type: valid length location: multiple length types (8) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-8
}

@test 'dynamic-length string type: valid length location: multiple length types (9) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-9
}

@test 'dynamic-length string type: valid length location: multiple length types (10) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-10
}

@test 'dynamic-length string type: valid length location: multiple length types (11) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-11
}

@test 'dynamic-length string type: valid length location: multiple length types (12) -> pass' {
  test_metadata_pass dl-str-type-len-loc-multi-12
}

@test 'static-length array type: `env` reference for length -> pass' {
  test_metadata_pass sl-array-type-len-env-ref
}

@test 'static-length array type: signed element type -> pass' {
  test_metadata_pass sl-str-signed-elem-type
}

@test 'static-length string type: `env` reference for length -> pass' {
  test_metadata_pass sl-str-type-len-env-ref
}

@test 'structure type: named alias -> pass' {
  test_metadata_pass struct-type-alias
}

@test 'variant type: named variant type with absolute selector location -> pass' {
  test_metadata_pass var-type-named-abs-sel-loc
}

@test '`env` block: full -> pass' {
  test_metadata_pass env-full
}

@test 'clock type: full -> pass' {
  test_metadata_pass clk-type-full
}

@test 'clock type: negative `offset_s` attribute -> pass' {
  test_metadata_pass clk-type-neg-offset-s-attr
}

@test 'clock type: no `uuid` attribute -> pass' {
  test_metadata_pass clk-type-no-uuid-attr
}

@test 'event record type: with log levels -> pass' {
  test_metadata_pass ert-with-log-level-attr
}

@test 'event record type: with `model.emf.uri` attribute -> pass' {
  test_metadata_pass ert-with-model-emf-uri-attr
}

@test 'data stream type: DST block with `id` attribute after ERT block -> pass' {
  test_metadata_pass dst-with-id-attr-after-ert
}

@test 'data stream type: PC type: string type for `packet_size` member -> pass' {
  test_metadata_pass dst-pc-type-packet-size-member-1
}

@test 'data stream type: PC type: signed integer type for `packet_size` member -> pass' {
  test_metadata_pass dst-pc-type-packet-size-member-2
}

@test 'data stream type: PC type: string type for `content_size` member -> pass' {
  test_metadata_pass dst-pc-type-content-size-member-1
}

@test 'data stream type: PC type: signed integer type for `content_size` member -> pass' {
  test_metadata_pass dst-pc-type-content-size-member-2
}

@test 'data stream type: ERH type: string type for `id` member -> pass' {
  test_metadata_pass dst-erh-type-id-member-1
}

@test 'data stream type: ERH type: signed integer type for `id` member -> pass' {
  test_metadata_pass dst-erh-type-id-member-2
}

@test '`callsite` block: full -> pass' {
  test_metadata_pass callsite-full
}

@test 'syntax: escape characters in literal string -> pass' {
  test_metadata_pass syntax-literal-escape-chars
}

@test 'syntax: extra semicolons -> pass' {
  test_metadata_pass syntax-extra-semicolons
}

@test 'data type aliases everywhere -> pass' {
  test_metadata_pass dt-aliases-everywhere
}

@test 'data type aliases with cross-reference -> pass' {
  test_metadata_pass dt-aliases-xref
}

@test 'type definitions everywhere -> pass' {
  test_metadata_pass type-defs-everywhere
}

@test 'trace type: no `uuid` attribute -> pass' {
  test_metadata_pass trace-type-no-uuid-attr
}

@test 'trace type: PH type: string type for `magic` member -> pass' {
  test_metadata_pass trace-type-ph-type-magic-member-1
}

@test 'trace type: PH type: signed integer type for `magic` member -> pass' {
  test_metadata_pass trace-type-ph-type-magic-member-2
}

@test 'trace type: PH type: string type for `stream_id` member -> pass' {
  test_metadata_pass trace-type-ph-type-stream-id-member-1
}

@test 'trace type: PH type: signed integer type for `stream_id` member -> pass' {
  test_metadata_pass trace-type-ph-type-stream-id-member-2
}

@test 'trace type: PH type: string type for `stream_instance_id` member -> pass' {
  test_metadata_pass trace-type-ph-type-stream-instance-id-member-1
}

@test 'trace type: PH type: signed integer type for `stream_instance_id` member -> pass' {
  test_metadata_pass trace-type-ph-type-stream-instance-id-member-2
}

@test 'trace type: PH type: string type for `uuid` member -> pass' {
  test_metadata_pass trace-type-ph-type-uuid-member-1
}

@test 'trace type: PH type: static-length array of strings type for `uuid` member -> pass' {
  test_metadata_pass trace-type-ph-type-uuid-member-2
}

@test 'trace type: PH type: static-length array of 15 bytes type for `uuid` member -> pass' {
  test_metadata_pass trace-type-ph-type-uuid-member-3
}

@test 'trace type: PH type: static-length array of 16 16-bit integers type for `uuid` member -> pass' {
  test_metadata_pass trace-type-ph-type-uuid-member-4
}

@test 'trace type: PH type: static-length array of 16-bit-aligned integers type for `uuid` member -> pass' {
  test_metadata_pass trace-type-ph-type-uuid-member-5
}

@test 'trace type: PH type: dynamic-length array type for `uuid` member -> pass' {
  test_metadata_pass trace-type-ph-type-uuid-member-6
}

@test 'CTF test suite: `array-basic-1dim` -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-1dim
}

@test 'CTF test suite: `array-basic-2dim` -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-2dim
}

@test 'CTF test suite: `array-basic-2dim-2typedef` -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-2dim-2typedef
}

@test 'CTF test suite: `array-basic-2dim-typedef` -> pass' {
  test_metadata_pass ctf-testsuite-array-basic-2dim-typedef
}

@test 'CTF test suite: `array-of-enum` -> pass' {
  test_metadata_pass ctf-testsuite-array-of-enum
}

@test 'CTF test suite: `array-of-struct` -> pass' {
  test_metadata_pass ctf-testsuite-array-of-struct
}

@test 'CTF test suite: `enum-nameless` -> pass' {
  test_metadata_pass ctf-testsuite-enum-nameless
}

@test 'CTF test suite: `enum-token-kind` -> pass' {
  test_metadata_pass ctf-testsuite-enum-token-kind
}

@test 'CTF test suite: `enum-untyped-int` -> pass' {
  test_metadata_pass ctf-testsuite-enum-untyped-int
}

@test 'CTF test suite: `enum-values-signed-big` -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-signed-big
}

@test 'CTF test suite: `enum-values-signed-small` -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-signed-small
}

@test 'CTF test suite: `enum-values-signed-value` -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-signed-value
}

@test 'CTF test suite: `enum-values-unsigned-big` -> pass' {
  test_metadata_pass ctf-testsuite-enum-values-unsigned-big
}

@test 'CTF test suite: `event-id-integer` -> pass' {
  test_metadata_pass ctf-testsuite-event-id-integer
}

@test 'CTF test suite: `integer-1-bit-size` -> pass' {
  test_metadata_pass ctf-testsuite-integer-1-bit-size
}

@test 'CTF test suite: `literal-integers` -> pass' {
  test_metadata_pass ctf-testsuite-literal-integers
}

@test 'CTF test suite: `metadata-big-endian` -> pass' {
  test_metadata_pass ctf-testsuite-metadata-big-endian
}

@test 'CTF test suite: `metadata-minimal-accepted` -> pass' {
  test_metadata_pass ctf-testsuite-metadata-minimal-accepted
}

@test 'CTF test suite: `name-escaping-clashes` -> pass' {
  test_metadata_pass ctf-testsuite-name-escaping-clashes
}

@test 'CTF test suite: `name-escaping-empty` -> pass' {
  test_metadata_pass ctf-testsuite-name-escaping-empty
}

@test 'CTF test suite: `repeated-event-id-in-2-streams` -> pass' {
  test_metadata_pass ctf-testsuite-repeated-event-id-in-2-streams
}

@test 'CTF test suite: `dynamic-array-basic-1dim` -> pass' {
  test_metadata_pass ctf-testsuite-dynamic-array-basic-1dim
}

@test 'CTF test suite: `dynamic-array-basic-2dim` -> pass' {
  test_metadata_pass ctf-testsuite-dynamic-array-basic-2dim
}

@test 'CTF test suite: `dynamic-array-scoped-length` -> pass' {
  test_metadata_pass ctf-testsuite-dynamic-array-scoped-length
}

@test 'CTF test suite: `stream-undefined-id` -> pass' {
  test_metadata_pass ctf-testsuite-stream-undefined-id
}

@test 'CTF test suite: `struct-align-larger` -> pass' {
  test_metadata_pass ctf-testsuite-struct-align-larger
}

@test 'CTF test suite: `struct-align-smaller` -> pass' {
  test_metadata_pass ctf-testsuite-struct-align-smaller
}

@test 'CTF test suite: `struct-align-valid` -> pass' {
  test_metadata_pass ctf-testsuite-struct-align-valid
}

@test 'CTF test suite: `struct-inner-struct` -> pass' {
  test_metadata_pass ctf-testsuite-struct-inner-struct
}

@test 'CTF test suite: `struct-unamed-struct-as-field` -> pass' {
  test_metadata_pass ctf-testsuite-struct-unamed-struct-as-field
}

@test 'CTF test suite: `struct-underscores-in-fields` -> pass' {
  test_metadata_pass ctf-testsuite-struct-underscores-in-fields
}

@test 'CTF test suite: `typealias-reserved-keyword` -> pass' {
  test_metadata_pass ctf-testsuite-typealias-reserved-keyword
}

@test 'CTF test suite: `typealias-simple` -> pass' {
  test_metadata_pass ctf-testsuite-typealias-simple
}

@test 'CTF test suite: `typedef-simple` -> pass' {
  test_metadata_pass ctf-testsuite-typedef-simple
}

@test 'CTF test suite: `unknown-env` -> pass' {
  test_metadata_pass ctf-testsuite-unknown-env
}

@test 'CTF test suite: `variant-integers` -> pass' {
  test_metadata_pass ctf-testsuite-variant-integers
}

@test 'CTF test suite: `variant-integers-unnamed` -> pass' {
  test_metadata_pass ctf-testsuite-variant-integers-unnamed
}

@test 'CTF test suite: `variant-missing-selector` -> pass' {
  test_metadata_pass ctf-testsuite-variant-missing-selector
}

@test 'CTF test suite: `variant-scope-tag` -> pass' {
  test_metadata_pass ctf-testsuite-variant-scope-tag
}

@test 'CTF test suite: `variant-structs` -> pass' {
  test_metadata_pass ctf-testsuite-variant-structs
}

@test 'CTF test suite: `variant-two-levels` -> pass' {
  test_metadata_pass ctf-testsuite-variant-two-levels
}

@test 'CTF test suite: `variant-two-levels-redefinition` -> pass' {
  test_metadata_pass ctf-testsuite-variant-two-levels-redefinition
}
