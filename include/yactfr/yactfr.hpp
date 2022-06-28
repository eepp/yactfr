/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief
    Master header.
*/

#ifndef _YACTFR_YACTFR_HPP
#define _YACTFR_YACTFR_HPP

#include "aliases.hpp"
#include "data-blk.hpp"
#include "data-src-factory.hpp"
#include "data-src.hpp"
#include "decoding-errors.hpp"
#include "elem-seq-it-pos.hpp"
#include "elem-seq-it.hpp"
#include "elem-seq.hpp"
#include "elem-visitor.hpp"
#include "elem.hpp"
#include "from-metadata-text.hpp"
#include "io-error.hpp"
#include "metadata/aliases.hpp"
#include "metadata/array-type.hpp"
#include "metadata/blob-type.hpp"
#include "metadata/bo.hpp"
#include "metadata/clk-offset.hpp"
#include "metadata/clk-type.hpp"
#include "metadata/clk-value-interval.hpp"
#include "metadata/compound-dt.hpp"
#include "metadata/data-loc.hpp"
#include "metadata/dl-array-type.hpp"
#include "metadata/dl-blob-type.hpp"
#include "metadata/dl-str-type.hpp"
#include "metadata/dst.hpp"
#include "metadata/dt-visitor.hpp"
#include "metadata/dt.hpp"
#include "metadata/enum-type.hpp"
#include "metadata/ert.hpp"
#include "metadata/fl-bit-array-type.hpp"
#include "metadata/fl-enum-type.hpp"
#include "metadata/fl-float-type.hpp"
#include "metadata/fl-int-type.hpp"
#include "metadata/fwd.hpp"
#include "metadata/int-range-set.hpp"
#include "metadata/int-range.hpp"
#include "metadata/int-type-common.hpp"
#include "metadata/invalid-metadata-stream.hpp"
#include "metadata/metadata-stream.hpp"
#include "metadata/non-nt-str-type.hpp"
#include "metadata/nt-str-type.hpp"
#include "metadata/packetized-metadata-stream.hpp"
#include "metadata/plain-text-metadata-stream.hpp"
#include "metadata/scalar-dt.hpp"
#include "metadata/scope.hpp"
#include "metadata/sl-array-type.hpp"
#include "metadata/sl-blob-type.hpp"
#include "metadata/sl-str-type.hpp"
#include "metadata/struct-member-type.hpp"
#include "metadata/struct-type.hpp"
#include "metadata/trace-type.hpp"
#include "metadata/var-type-opt.hpp"
#include "metadata/var-type.hpp"
#include "metadata/vl-enum-type.hpp"
#include "metadata/vl-int-type.hpp"
#include "mmap-file-view-factory.hpp"
#include "text-parse-error.hpp"
#include "trace-env-stream-decoder.hpp"
#include "trace-env.hpp"

#endif // _YACTFR_YACTFR_HPP
