/*
 * SPDX-FileCopyrightText: 2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#ifndef YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_VAL_REQ_HPP
#define YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_VAL_REQ_HPP

#include <memory>

#include "json-val.hpp"
#include "json-val-req.hpp"

namespace yactfr::internal {

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

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_METADATA_JSON_CTF_2_JSON_VAL_REQ_HPP
