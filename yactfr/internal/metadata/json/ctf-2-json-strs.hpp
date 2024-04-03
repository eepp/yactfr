/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP
#define YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP

#include <cassert>
#include <unordered_map>
#include <memory>

#include "json-val.hpp"
#include "json-val-req.hpp"

namespace yactfr {
namespace internal {
namespace strs {

extern const char * const accuracy;
extern const char * const align;
extern const char * const appOctetStream;
extern const char * const attrs;
extern const char * const be;
extern const char * const bio;
extern const char * const bo;
extern const char * const cc;
extern const char * const cycles;
extern const char * const defCcId;
extern const char * const defClkTs;
extern const char * const descr;
extern const char * const discErCounterSnap;
extern const char * const dlArray;
extern const char * const dlBlob;
extern const char * const dlStr;
extern const char * const dsId;
extern const char * const dsc;
extern const char * const dscId;
extern const char * const encoding;
extern const char * const elemFc;
extern const char * const env;
extern const char * const erCommonCtx;
extern const char * const erCommonCtxFc;
extern const char * const erHeader;
extern const char * const erHeaderFc;
extern const char * const erPayload;
extern const char * const erSpecCtx;
extern const char * const erc;
extern const char * const ercId;
extern const char * const ext;
extern const char * const fc;
extern const char * const fcAlias;
extern const char * const flags;
extern const char * const flBitArray;
extern const char * const flBitMap;
extern const char * const flBool;
extern const char * const flFloat;
extern const char * const flSInt;
extern const char * const flUInt;
extern const char * const freq;
extern const char * const ftl;
extern const char * const id;
extern const char * const le;
extern const char * const len;
extern const char * const lenFieldLoc;
extern const char * const ltf;
extern const char * const mappings;
extern const char * const mediaType;
extern const char * const memberClss;
extern const char * const metadataStreamUuid;
extern const char * const minAlign;
extern const char * const name;
extern const char * const ns;
extern const char * const ntStr;
extern const char * const offsetFromOrig;
extern const char * const opt;
extern const char * const opts;
extern const char * const orig;
extern const char * const path;
extern const char * const payloadFc;
extern const char * const pktContentLen;
extern const char * const pktCtx;
extern const char * const pktCtxFc;
extern const char * const pktEndDefClkTs;
extern const char * const pktHeader;
extern const char * const pktHeaderFc;
extern const char * const pktMagicNumber;
extern const char * const pktSeqNum;
extern const char * const pktTotalLen;
extern const char * const pre;
extern const char * const prec;
extern const char * const prefDispBase;
extern const char * const roles;
extern const char * const secs;
extern const char * const selFieldLoc;
extern const char * const selFieldRanges;
extern const char * const slArray;
extern const char * const slBlob;
extern const char * const slStr;
extern const char * const specCtxFc;
extern const char * const structure;
extern const char * const tc;
extern const char * const type;
extern const char * const uid;
extern const char * const unixEpoch;
extern const char * const utf8;
extern const char * const utf16Be;
extern const char * const utf16Le;
extern const char * const utf32Be;
extern const char * const utf32Le;
extern const char * const uuid;
extern const char * const var;
extern const char * const version;
extern const char * const vlSInt;
extern const char * const vlUInt;

} // namespace strs
} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP
