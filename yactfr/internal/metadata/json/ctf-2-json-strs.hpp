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

extern const char * const ACCURACY;
extern const char * const ALIGN;
extern const char * const APP_OCTET_STREAM;
extern const char * const ATTRS;
extern const char * const BE;
extern const char * const BIO;
extern const char * const BO;
extern const char * const CC;
extern const char * const CYCLES;
extern const char * const DEF_CC_ID;
extern const char * const DEF_CLK_TS;
extern const char * const DESCR;
extern const char * const DISC_ER_COUNTER_SNAP;
extern const char * const DL_ARRAY;
extern const char * const DL_BLOB;
extern const char * const DL_STR;
extern const char * const DS_ID;
extern const char * const DSC;
extern const char * const DSC_ID;
extern const char * const ENCODING;
extern const char * const ELEM_FC;
extern const char * const ENV;
extern const char * const ER_COMMON_CTX;
extern const char * const ER_COMMON_CTX_FC;
extern const char * const ER_HEADER;
extern const char * const ER_HEADER_FC;
extern const char * const ER_PAYLOAD;
extern const char * const ER_SPEC_CTX;
extern const char * const ERC;
extern const char * const ERC_ID;
extern const char * const EXT;
extern const char * const FC;
extern const char * const FC_ALIAS;
extern const char * const FLAGS;
extern const char * const FL_BIT_ARRAY;
extern const char * const FL_BIT_MAP;
extern const char * const FL_BOOL;
extern const char * const FL_FLOAT;
extern const char * const FL_SINT;
extern const char * const FL_UINT;
extern const char * const FREQ;
extern const char * const FTL;
extern const char * const ID;
extern const char * const LE;
extern const char * const LEN;
extern const char * const LEN_FIELD_LOC;
extern const char * const LTF;
extern const char * const MAPPINGS;
extern const char * const MEDIA_TYPE;
extern const char * const MEMBER_CLSS;
extern const char * const METADATA_STREAM_UUID;
extern const char * const MIN_ALIGN;
extern const char * const NAME;
extern const char * const NS;
extern const char * const NT_STR;
extern const char * const OFFSET_FROM_ORIG;
extern const char * const OPT;
extern const char * const OPTS;
extern const char * const ORIG;
extern const char * const PATH;
extern const char * const PAYLOAD_FC;
extern const char * const PKT_CONTENT_LEN;
extern const char * const PKT_CTX;
extern const char * const PKT_CTX_FC;
extern const char * const PKT_END_DEF_CLK_TS;
extern const char * const PKT_HEADER;
extern const char * const PKT_HEADER_FC;
extern const char * const PKT_MAGIC_NUMBER;
extern const char * const PKT_SEQ_NUM;
extern const char * const PKT_TOTAL_LEN;
extern const char * const PRE;
extern const char * const PREC;
extern const char * const PREF_DISP_BASE;
extern const char * const ROLES;
extern const char * const SECS;
extern const char * const SEL_FIELD_LOC;
extern const char * const SEL_FIELD_RANGES;
extern const char * const SL_ARRAY;
extern const char * const SL_BLOB;
extern const char * const SL_STR;
extern const char * const SPEC_CTX_FC;
extern const char * const STRUCT;
extern const char * const TC;
extern const char * const TYPE;
extern const char * const UID;
extern const char * const UNIX_EPOCH;
extern const char * const UTF_8;
extern const char * const UTF_16BE;
extern const char * const UTF_16LE;
extern const char * const UTF_32BE;
extern const char * const UTF_32LE;
extern const char * const UUID;
extern const char * const VAR;
extern const char * const VERSION;
extern const char * const VL_SINT;
extern const char * const VL_UINT;

} // namespace strs
} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_STRS_HPP
