/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief
    Master header, without the metadata text parser.
*/

#ifndef _YACTFR_YACTFR_WITHOUT_METADATA_TEXT_PARSER_HPP
#define _YACTFR_YACTFR_WITHOUT_METADATA_TEXT_PARSER_HPP

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
#include "io-error.hpp"
#include "metadata/aliases.hpp"
#include "metadata/array-type.hpp"
#include "metadata/bit-array-type.hpp"
#include "metadata/bo.hpp"
#include "metadata/clk-offset.hpp"
#include "metadata/clk-type.hpp"
#include "metadata/clk-value-interval.hpp"
#include "metadata/compound-dt.hpp"
#include "metadata/data-loc.hpp"
#include "metadata/dst.hpp"
#include "metadata/dt-visitor.hpp"
#include "metadata/dt.hpp"
#include "metadata/dyn-array-type.hpp"
#include "metadata/dyn-text-array-type.hpp"
#include "metadata/enum-type.hpp"
#include "metadata/ert.hpp"
#include "metadata/float-type.hpp"
#include "metadata/fwd.hpp"
#include "metadata/int-range-set.hpp"
#include "metadata/int-range.hpp"
#include "metadata/int-type.hpp"
#include "metadata/invalid-metadata-stream.hpp"
#include "metadata/metadata-parse-error.hpp"
#include "metadata/metadata-stream.hpp"
#include "metadata/packetized-metadata-stream.hpp"
#include "metadata/plain-text-metadata-stream.hpp"
#include "metadata/scalar-dt.hpp"
#include "metadata/scope.hpp"
#include "metadata/static-array-type.hpp"
#include "metadata/static-text-array-type.hpp"
#include "metadata/str-type.hpp"
#include "metadata/struct-member-type.hpp"
#include "metadata/struct-type.hpp"
#include "metadata/trace-type.hpp"
#include "metadata/var-type-opt.hpp"
#include "metadata/var-type.hpp"
#include "mmap-file-view-factory.hpp"
#include "trace-env.hpp"
#include "trace.hpp"

#endif // _YACTFR_YACTFR_WITHOUT_METADATA_TEXT_PARSER_HPP
