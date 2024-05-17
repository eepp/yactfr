/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_SEQ_PARSER_HPP
#define YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_SEQ_PARSER_HPP

#include <cassert>
#include <array>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/ert.hpp>
#include <yactfr/text-parse-error.hpp>
#include <yactfr/metadata/aliases.hpp>

#include "ctf-2-json-val-req.hpp"
#include "ctf-2-json-utils.hpp"
#include "json-val.hpp"
#include "pseudo-dt-erector.hpp"
#include "../pseudo-types.hpp"

namespace yactfr {
namespace internal {

/*
 * CTF 2 JSON text sequence metadata stream parser.
 *
 * This parser parses a CTF 2 (JSON text sequence) metadata string and
 * then contains a corresponding trace type object.
 */
class Ctf2JsonSeqParser final
{
public:
    /*
     * Builds a JSON text sequence metadata stream parser, wrapping a
     * string between `begin` (included) and `end` (excluded), and
     * parses it.
     *
     * You can release the resulting trace type from this parser
     * with releaseTraceType().
     *
     * Throws `TextParseError` when there was a parsing error.
     */
    explicit Ctf2JsonSeqParser(const char *begin, const char *end);

    /*
     * Releases and returns the parsed trace type.
     */
    TraceType::Up releaseTraceType()
    {
        return std::move(_traceType);
    }

    /*
     * Returns the UUID of the metadata stream.
     */
    const boost::optional<boost::uuids::uuid>& metadataStreamUuid() const noexcept
    {
        return _metadataStreamUuid;
    }

private:
    /*
     * Creates the yactfr trace type from the pseudo trace type.
     */
    void _createTraceType();

    /*
     * Parses the whole metadata string, creating the resulting trace
     * type and trace environment on success, throwing
     * `TextParseError` otherwise.
     */
    void _parseMetadata();

    /*
     * Parses the JSON fragment between `begin` (included) and `end`
     * (excluded), updating the internal state on success, or throwing
     * `TextParseError` on failure.
     */
    void _parseFrag(const char *begin, const char *end, Index fragIndex);

    /*
     * Handles the JSON fragment `jsonFrag`, updating the internal state
     * on success, or throwing `TextParseError` on failure.
     */
    void _handleFrag(const JsonVal& jsonFrag, Index fragIndex);

    /*
     * Handles the JSON trace type fragment `jsonFrag`, updating the
     * internal state on success, or throwing `TextParseError`
     * on failure.
     */
    void _handleTraceTypeFrag(const JsonObjVal& jsonFrag);

    /*
     * Handles the JSON data type alias fragment `jsonFrag`, updating
     * the internal state on success, or throwing `TextParseError`
     * on failure.
     */
    void _handleDtAliasFrag(const JsonObjVal& jsonFrag);

    /*
     * Handles the JSON clock type fragment `jsonFrag`, updating the
     * internal state on success, or throwing `TextParseError`
     * on failure.
     */
    void _handleClkTypeFrag(const JsonObjVal& jsonFrag);

    /*
     * Handles the JSON data stream type fragment `jsonFrag`, updating
     * the internal state on success, or throwing `TextParseError`
     * on failure.
     */
    void _handleDstFrag(const JsonObjVal& jsonFrag);

    /*
     * Handles the JSON event record type fragment `jsonFrag`, updating
     * the internal state on success, or throwing `TextParseError`
     * on failure.
     */
    void _handleErtFrag(const JsonObjVal& jsonFrag);

    /*
     * Ensures that `_pseudoTraceType` is initialized.
     */
    void _ensureExistingPseudoTraceType();

    /*
     * Calls `_pseudoDtErector.pseudoDtOfJsonObj()`, also validating
     * that the returned value is a pseudo structure type.
     */
    PseudoDt::Up _pseudoScopeDtOfJsonObj(const JsonObjVal& jsonObjVal, const std::string& propName);

    /*
     * Returns the default clock type for the JSON data stream type
     * fragment `jsonFrag`, or `nullptr` if none.
     *
     * Throws if it can't find the clock type.
     */
    const ClockType *_defClkTypeOfDstFrag(const JsonObjVal& jsonFrag);

private:
    // beginning and end metadata string pointers
    const char *_begin;
    const char *_end;

    // fragment requirement
    JsonAnyFragValReq _fragValReq;

    // pseudo data type erector
    PseudoDtErector _pseudoDtErector;

    // default clock offset JSON value
    JsonObjVal::Up _defClkOffsetVal;

    // final trace type
    TraceType::Up _traceType;

    // metadata stream UUID
    boost::optional<boost::uuids::uuid> _metadataStreamUuid;

    // current pseudo trace type
    boost::optional<PseudoTraceType> _pseudoTraceType;
};

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_SEQ_PARSER_HPP
