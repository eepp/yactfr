/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP
#define _YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP

#include <cassert>
#include <unordered_map>
#include <memory>

#include "json-val.hpp"
#include "json-val-req.hpp"

namespace yactfr {
namespace internal {
namespace strs {

static constexpr auto ACCURACY = "accuracy";
static constexpr auto ALIGN = "alignment";
static constexpr auto APP_OCTET_STREAM = "application/octet-stream";
static constexpr auto ATTRS = "attributes";
static constexpr auto BE = "big-endian";
static constexpr auto BO = "byte-order";
static constexpr auto CC = "clock-class";
static constexpr auto CYCLES = "cycles";
static constexpr auto DEF_CC_ID = "default-clock-class-id";
static constexpr auto DEF_CLK_TS = "default-clock-timestamp";
static constexpr auto DESCR = "description";
static constexpr auto DISC_ER_COUNTER_SNAP = "discarded-event-record-counter-snapshot";
static constexpr auto DL_ARRAY = "dynamic-length-array";
static constexpr auto DL_BLOB = "dynamic-length-blob";
static constexpr auto DL_STR = "dynamic-length-string";
static constexpr auto DS_ID = "data-stream-id";
static constexpr auto DSC = "data-stream-class";
static constexpr auto DSC_ID = "data-stream-class-id";
static constexpr auto ENCODING = "encoding";
static constexpr auto ELEM_FC = "element-field-class";
static constexpr auto ENV = "environment";
static constexpr auto ER_COMMON_CTX = "event-record-common-context";
static constexpr auto ER_COMMON_CTX_FC = "event-record-common-context-field-class";
static constexpr auto ER_HEADER = "event-record-header";
static constexpr auto ER_HEADER_FC = "event-record-header-field-class";
static constexpr auto ER_PAYLOAD = "event-record-payload";
static constexpr auto ER_SPEC_CTX = "event-record-specific-context";
static constexpr auto ERC = "event-record-class";
static constexpr auto ERC_ID = "event-record-class-id";
static constexpr auto EXT = "extensions";
static constexpr auto FC = "field-class";
static constexpr auto FC_ALIAS = "field-class-alias";
static constexpr auto FL_BIT_ARRAY = "fixed-length-bit-array";
static constexpr auto FL_BOOL = "fixed-length-boolean";
static constexpr auto FL_FLOAT = "fixed-length-floating-point-number";
static constexpr auto FL_SINT = "fixed-length-signed-integer";
static constexpr auto FL_UINT = "fixed-length-unsigned-integer";
static constexpr auto FREQ = "frequency";
static constexpr auto ID = "id";
static constexpr auto LE = "little-endian";
static constexpr auto LEN = "length";
static constexpr auto LEN_FIELD_LOC = "length-field-location";
static constexpr auto MAPPINGS = "mappings";
static constexpr auto MEDIA_TYPE = "media-type";
static constexpr auto MEMBER_CLSS = "member-classes";
static constexpr auto METADATA_STREAM_UUID = "metadata-stream-uuid";
static constexpr auto MIN_ALIGN = "minimum-alignment";
static constexpr auto NAME = "name";
static constexpr auto NS = "namespace";
static constexpr auto NT_STR = "null-terminated-string";
static constexpr auto OFFSET_FROM_ORIG = "offset-from-origin";
static constexpr auto OPT = "optional";
static constexpr auto OPTS = "options";
static constexpr auto ORIG = "origin";
static constexpr auto PATH = "path";
static constexpr auto PAYLOAD_FC = "payload-field-class";
static constexpr auto PKT_CONTENT_LEN = "packet-content-length";
static constexpr auto PKT_CTX = "packet-context";
static constexpr auto PKT_CTX_FC = "packet-context-field-class";
static constexpr auto PKT_END_DEF_CLK_TS = "packet-end-default-clock-timestamp";
static constexpr auto PKT_HEADER = "packet-header";
static constexpr auto PKT_HEADER_FC = "packet-header-field-class";
static constexpr auto PKT_MAGIC_NUMBER = "packet-magic-number";
static constexpr auto PKT_SEQ_NUM = "packet-sequence-number";
static constexpr auto PKT_TOTAL_LEN = "packet-total-length";
static constexpr auto PRE = "preamble";
static constexpr auto PREC = "precision";
static constexpr auto PREF_DISP_BASE = "preferred-display-base";
static constexpr auto ROLES = "roles";
static constexpr auto SECS = "seconds";
static constexpr auto SEL_FIELD_LOC = "selector-field-location";
static constexpr auto SEL_FIELD_RANGES = "selector-field-ranges";
static constexpr auto SL_ARRAY = "static-length-array";
static constexpr auto SL_BLOB = "static-length-blob";
static constexpr auto SL_STR = "static-length-string";
static constexpr auto SPEC_CTX_FC = "specific-context-field-class";
static constexpr auto STRUCT = "structure";
static constexpr auto TC = "trace-class";
static constexpr auto TYPE = "type";
static constexpr auto UID = "uid";
static constexpr auto UNIX_EPOCH = "unix-epoch";
static constexpr auto UTF_8 = "utf-8";
static constexpr auto UTF_16BE = "utf-16be";
static constexpr auto UTF_16LE = "utf-16le";
static constexpr auto UTF_32BE = "utf-32be";
static constexpr auto UTF_32LE = "utf-32le";
static constexpr auto UUID = "uuid";
static constexpr auto VAR = "variant";
static constexpr auto VERSION = "version";
static constexpr auto VL_SINT = "variable-length-signed-integer";
static constexpr auto VL_UINT = "variable-length-unsigned-integer";

} // namespace strs
} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP
