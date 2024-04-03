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

constexpr const char *accuracy = "accuracy";
constexpr const char *align = "alignment";
constexpr const char *appOctetStream = "application/octet-stream";
constexpr const char *attrs = "attributes";
constexpr const char *be = "big-endian";
constexpr const char *bio = "bit-order";
constexpr const char *bo = "byte-order";
constexpr const char *cc = "clock-class";
constexpr const char *cycles = "cycles";
constexpr const char *defCcId = "default-clock-class-id";
constexpr const char *defClkTs = "default-clock-timestamp";
constexpr const char *descr = "description";
constexpr const char *discErCounterSnap = "discarded-event-record-counter-snapshot";
constexpr const char *dlArray = "dynamic-length-array";
constexpr const char *dlBlob = "dynamic-length-blob";
constexpr const char *dlStr = "dynamic-length-string";
constexpr const char *dsId = "data-stream-id";
constexpr const char *dsc = "data-stream-class";
constexpr const char *dscId = "data-stream-class-id";
constexpr const char *encoding = "encoding";
constexpr const char *elemFc = "element-field-class";
constexpr const char *env = "environment";
constexpr const char *erCommonCtx = "event-record-common-context";
constexpr const char *erCommonCtxFc = "event-record-common-context-field-class";
constexpr const char *erHeader = "event-record-header";
constexpr const char *erHeaderFc = "event-record-header-field-class";
constexpr const char *erPayload = "event-record-payload";
constexpr const char *erSpecCtx = "event-record-specific-context";
constexpr const char *erc = "event-record-class";
constexpr const char *ercId = "event-record-class-id";
constexpr const char *ext = "extensions";
constexpr const char *fc = "field-class";
constexpr const char *fcAlias = "field-class-alias";
constexpr const char *flags = "flags";
constexpr const char *flBitArray = "fixed-length-bit-array";
constexpr const char *flBitMap = "fixed-length-bit-map";
constexpr const char *flBool = "fixed-length-boolean";
constexpr const char *flFloat = "fixed-length-floating-point-number";
constexpr const char *flSInt = "fixed-length-signed-integer";
constexpr const char *flUInt = "fixed-length-unsigned-integer";
constexpr const char *freq = "frequency";
constexpr const char *ftl = "first-to-last";
constexpr const char *id = "id";
constexpr const char *le = "little-endian";
constexpr const char *len = "length";
constexpr const char *lenFieldLoc = "length-field-location";
constexpr const char *ltf = "last-to-first";
constexpr const char *mappings = "mappings";
constexpr const char *mediaType = "media-type";
constexpr const char *memberClss = "member-classes";
constexpr const char *metadataStreamUuid = "metadata-stream-uuid";
constexpr const char *minAlign = "minimum-alignment";
constexpr const char *name = "name";
constexpr const char *ns = "namespace";
constexpr const char *ntStr = "null-terminated-string";
constexpr const char *offsetFromOrig = "offset-from-origin";
constexpr const char *opt = "optional";
constexpr const char *opts = "options";
constexpr const char *orig = "origin";
constexpr const char *path = "path";
constexpr const char *payloadFc = "payload-field-class";
constexpr const char *pktContentLen = "packet-content-length";
constexpr const char *pktCtx = "packet-context";
constexpr const char *pktCtxFc = "packet-context-field-class";
constexpr const char *pktEndDefClkTs = "packet-end-default-clock-timestamp";
constexpr const char *pktHeader = "packet-header";
constexpr const char *pktHeaderFc = "packet-header-field-class";
constexpr const char *pktMagicNumber = "packet-magic-number";
constexpr const char *pktSeqNum = "packet-sequence-number";
constexpr const char *pktTotalLen = "packet-total-length";
constexpr const char *pre = "preamble";
constexpr const char *prec = "precision";
constexpr const char *prefDispBase = "preferred-display-base";
constexpr const char *roles = "roles";
constexpr const char *secs = "seconds";
constexpr const char *selFieldLoc = "selector-field-location";
constexpr const char *selFieldRanges = "selector-field-ranges";
constexpr const char *slArray = "static-length-array";
constexpr const char *slBlob = "static-length-blob";
constexpr const char *slStr = "static-length-string";
constexpr const char *specCtxFc = "specific-context-field-class";
constexpr const char *structure = "structure";
constexpr const char *tc = "trace-class";
constexpr const char *type = "type";
constexpr const char *uid = "uid";
constexpr const char *unixEpoch = "unix-epoch";
constexpr const char *utf8 = "utf-8";
constexpr const char *utf16Be = "utf-16be";
constexpr const char *utf16Le = "utf-16le";
constexpr const char *utf32Be = "utf-32be";
constexpr const char *utf32Le = "utf-32le";
constexpr const char *uuid = "uuid";
constexpr const char *var = "variant";
constexpr const char *version = "version";
constexpr const char *vlSInt = "variable-length-signed-integer";
constexpr const char *vlUInt = "variable-length-unsigned-integer";

} // namespace strs
} // namespace internal
} // namespace yactfr
