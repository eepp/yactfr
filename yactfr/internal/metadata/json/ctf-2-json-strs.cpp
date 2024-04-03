/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "ctf-2-json-strs.hpp"

namespace yactfr {
namespace internal {
namespace strs {

constexpr const char *ACCURACY = "accuracy";
constexpr const char *ALIGN = "alignment";
constexpr const char *APP_OCTET_STREAM = "application/octet-stream";
constexpr const char *ATTRS = "attributes";
constexpr const char *BE = "big-endian";
constexpr const char *BIO = "bit-order";
constexpr const char *BO = "byte-order";
constexpr const char *CC = "clock-class";
constexpr const char *CYCLES = "cycles";
constexpr const char *DEF_CC_ID = "default-clock-class-id";
constexpr const char *DEF_CLK_TS = "default-clock-timestamp";
constexpr const char *DESCR = "description";
constexpr const char *DISC_ER_COUNTER_SNAP = "discarded-event-record-counter-snapshot";
constexpr const char *DL_ARRAY = "dynamic-length-array";
constexpr const char *DL_BLOB = "dynamic-length-blob";
constexpr const char *DL_STR = "dynamic-length-string";
constexpr const char *DS_ID = "data-stream-id";
constexpr const char *DSC = "data-stream-class";
constexpr const char *DSC_ID = "data-stream-class-id";
constexpr const char *ENCODING = "encoding";
constexpr const char *ELEM_FC = "element-field-class";
constexpr const char *ENV = "environment";
constexpr const char *ER_COMMON_CTX = "event-record-common-context";
constexpr const char *ER_COMMON_CTX_FC = "event-record-common-context-field-class";
constexpr const char *ER_HEADER = "event-record-header";
constexpr const char *ER_HEADER_FC = "event-record-header-field-class";
constexpr const char *ER_PAYLOAD = "event-record-payload";
constexpr const char *ER_SPEC_CTX = "event-record-specific-context";
constexpr const char *ERC = "event-record-class";
constexpr const char *ERC_ID = "event-record-class-id";
constexpr const char *EXT = "extensions";
constexpr const char *FC = "field-class";
constexpr const char *FC_ALIAS = "field-class-alias";
constexpr const char *FLAGS = "flags";
constexpr const char *FL_BIT_ARRAY = "fixed-length-bit-array";
constexpr const char *FL_BIT_MAP = "fixed-length-bit-map";
constexpr const char *FL_BOOL = "fixed-length-boolean";
constexpr const char *FL_FLOAT = "fixed-length-floating-point-number";
constexpr const char *FL_SINT = "fixed-length-signed-integer";
constexpr const char *FL_UINT = "fixed-length-unsigned-integer";
constexpr const char *FREQ = "frequency";
constexpr const char *FTL = "first-to-last";
constexpr const char *ID = "id";
constexpr const char *LE = "little-endian";
constexpr const char *LEN = "length";
constexpr const char *LEN_FIELD_LOC = "length-field-location";
constexpr const char *LTF = "last-to-first";
constexpr const char *MAPPINGS = "mappings";
constexpr const char *MEDIA_TYPE = "media-type";
constexpr const char *MEMBER_CLSS = "member-classes";
constexpr const char *METADATA_STREAM_UUID = "metadata-stream-uuid";
constexpr const char *MIN_ALIGN = "minimum-alignment";
constexpr const char *NAME = "name";
constexpr const char *NS = "namespace";
constexpr const char *NT_STR = "null-terminated-string";
constexpr const char *OFFSET_FROM_ORIG = "offset-from-origin";
constexpr const char *OPT = "optional";
constexpr const char *OPTS = "options";
constexpr const char *ORIG = "origin";
constexpr const char *PATH = "path";
constexpr const char *PAYLOAD_FC = "payload-field-class";
constexpr const char *PKT_CONTENT_LEN = "packet-content-length";
constexpr const char *PKT_CTX = "packet-context";
constexpr const char *PKT_CTX_FC = "packet-context-field-class";
constexpr const char *PKT_END_DEF_CLK_TS = "packet-end-default-clock-timestamp";
constexpr const char *PKT_HEADER = "packet-header";
constexpr const char *PKT_HEADER_FC = "packet-header-field-class";
constexpr const char *PKT_MAGIC_NUMBER = "packet-magic-number";
constexpr const char *PKT_SEQ_NUM = "packet-sequence-number";
constexpr const char *PKT_TOTAL_LEN = "packet-total-length";
constexpr const char *PRE = "preamble";
constexpr const char *PREC = "precision";
constexpr const char *PREF_DISP_BASE = "preferred-display-base";
constexpr const char *ROLES = "roles";
constexpr const char *SECS = "seconds";
constexpr const char *SEL_FIELD_LOC = "selector-field-location";
constexpr const char *SEL_FIELD_RANGES = "selector-field-ranges";
constexpr const char *SL_ARRAY = "static-length-array";
constexpr const char *SL_BLOB = "static-length-blob";
constexpr const char *SL_STR = "static-length-string";
constexpr const char *SPEC_CTX_FC = "specific-context-field-class";
constexpr const char *STRUCT = "structure";
constexpr const char *TC = "trace-class";
constexpr const char *TYPE = "type";
constexpr const char *UID = "uid";
constexpr const char *UNIX_EPOCH = "unix-epoch";
constexpr const char *UTF_8 = "utf-8";
constexpr const char *UTF_16BE = "utf-16be";
constexpr const char *UTF_16LE = "utf-16le";
constexpr const char *UTF_32BE = "utf-32be";
constexpr const char *UTF_32LE = "utf-32le";
constexpr const char *UUID = "uuid";
constexpr const char *VAR = "variant";
constexpr const char *VERSION = "version";
constexpr const char *VL_SINT = "variable-length-signed-integer";
constexpr const char *VL_UINT = "variable-length-unsigned-integer";

} // namespace strs
} // namespace internal
} // namespace yactfr
