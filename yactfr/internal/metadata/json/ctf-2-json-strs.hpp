/*
 * Copyright (C) 2022-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP
#define YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP

namespace yactfr::internal::strs {

inline constexpr auto accuracy = "accuracy";
inline constexpr auto align = "alignment";
inline constexpr auto appOctetStream = "application/octet-stream";
inline constexpr auto attrs = "attributes";
inline constexpr auto be = "big-endian";
inline constexpr auto bio = "bit-order";
inline constexpr auto bo = "byte-order";
inline constexpr auto cc = "clock-class";
inline constexpr auto cycles = "cycles";
inline constexpr auto defCcId = "default-clock-class-id";
inline constexpr auto defClkTs = "default-clock-timestamp";
inline constexpr auto descr = "description";
inline constexpr auto discErCounterSnap = "discarded-event-record-counter-snapshot";
inline constexpr auto dlArray = "dynamic-length-array";
inline constexpr auto dlBlob = "dynamic-length-blob";
inline constexpr auto dlStr = "dynamic-length-string";
inline constexpr auto dsId = "data-stream-id";
inline constexpr auto dsc = "data-stream-class";
inline constexpr auto dscId = "data-stream-class-id";
inline constexpr auto encoding = "encoding";
inline constexpr auto elemFc = "element-field-class";
inline constexpr auto env = "environment";
inline constexpr auto erCommonCtx = "event-record-common-context";
inline constexpr auto erCommonCtxFc = "event-record-common-context-field-class";
inline constexpr auto erHeader = "event-record-header";
inline constexpr auto erHeaderFc = "event-record-header-field-class";
inline constexpr auto erPayload = "event-record-payload";
inline constexpr auto erSpecCtx = "event-record-specific-context";
inline constexpr auto erc = "event-record-class";
inline constexpr auto ercId = "event-record-class-id";
inline constexpr auto ext = "extensions";
inline constexpr auto fc = "field-class";
inline constexpr auto fcAlias = "field-class-alias";
inline constexpr auto flags = "flags";
inline constexpr auto flBitArray = "fixed-length-bit-array";
inline constexpr auto flBitMap = "fixed-length-bit-map";
inline constexpr auto flBool = "fixed-length-boolean";
inline constexpr auto flFloat = "fixed-length-floating-point-number";
inline constexpr auto flSInt = "fixed-length-signed-integer";
inline constexpr auto flUInt = "fixed-length-unsigned-integer";
inline constexpr auto freq = "frequency";
inline constexpr auto ftl = "first-to-last";
inline constexpr auto id = "id";
inline constexpr auto le = "little-endian";
inline constexpr auto len = "length";
inline constexpr auto lenFieldLoc = "length-field-location";
inline constexpr auto ltf = "last-to-first";
inline constexpr auto mappings = "mappings";
inline constexpr auto mediaType = "media-type";
inline constexpr auto memberClss = "member-classes";
inline constexpr auto metadataStreamUuid = "metadata-stream-uuid";
inline constexpr auto minAlign = "minimum-alignment";
inline constexpr auto name = "name";
inline constexpr auto ns = "namespace";
inline constexpr auto ntStr = "null-terminated-string";
inline constexpr auto offsetFromOrig = "offset-from-origin";
inline constexpr auto opt = "optional";
inline constexpr auto opts = "options";
inline constexpr auto orig = "origin";
inline constexpr auto path = "path";
inline constexpr auto payloadFc = "payload-field-class";
inline constexpr auto pktContentLen = "packet-content-length";
inline constexpr auto pktCtx = "packet-context";
inline constexpr auto pktCtxFc = "packet-context-field-class";
inline constexpr auto pktEndDefClkTs = "packet-end-default-clock-timestamp";
inline constexpr auto pktHeader = "packet-header";
inline constexpr auto pktHeaderFc = "packet-header-field-class";
inline constexpr auto pktMagicNumber = "packet-magic-number";
inline constexpr auto pktSeqNum = "packet-sequence-number";
inline constexpr auto pktTotalLen = "packet-total-length";
inline constexpr auto pre = "preamble";
inline constexpr auto prec = "precision";
inline constexpr auto prefDispBase = "preferred-display-base";
inline constexpr auto roles = "roles";
inline constexpr auto secs = "seconds";
inline constexpr auto selFieldLoc = "selector-field-location";
inline constexpr auto selFieldRanges = "selector-field-ranges";
inline constexpr auto slArray = "static-length-array";
inline constexpr auto slBlob = "static-length-blob";
inline constexpr auto slStr = "static-length-string";
inline constexpr auto specCtxFc = "specific-context-field-class";
inline constexpr auto structure = "structure";
inline constexpr auto tc = "trace-class";
inline constexpr auto type = "type";
inline constexpr auto uid = "uid";
inline constexpr auto unixEpoch = "unix-epoch";
inline constexpr auto utf8 = "utf-8";
inline constexpr auto utf16Be = "utf-16be";
inline constexpr auto utf16Le = "utf-16le";
inline constexpr auto utf32Be = "utf-32be";
inline constexpr auto utf32Le = "utf-32le";
inline constexpr auto uuid = "uuid";
inline constexpr auto var = "variant";
inline constexpr auto version = "version";
inline constexpr auto vlSInt = "variable-length-signed-integer";
inline constexpr auto vlUInt = "variable-length-unsigned-integer";

} // namespace yactfr::internal::strs

#endif // YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP
