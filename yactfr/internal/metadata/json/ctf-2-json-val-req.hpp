/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_VAL_REQ_HPP
#define YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_VAL_REQ_HPP

#include <cassert>
#include <unordered_map>
#include <memory>

#include "json-val.hpp"
#include "json-val-req.hpp"

namespace yactfr {
namespace internal {

class JsonAnyFragValReqImpl;

/*
 * CTF 2 JSON (any) fragment value requirement.
 */
class JsonAnyFragValReq final :
    public JsonValReq
{
public:
    explicit JsonAnyFragValReq();

    /*
     * Required because `JsonAnyFragValReqImpl` has no known size at
     * this point.
     */
    ~JsonAnyFragValReq();

private:
    void _validate(const JsonVal& jsonVal) const override;

private:
    std::unique_ptr<const JsonAnyFragValReqImpl> _impl;
};

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_VAL_REQ_HPP
