/*
 * Internal utilities.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <sstream>
#include <string.h>
#include <errno.h>

#include <yactfr/metadata/data-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/array-type.hpp>
#include <yactfr/metadata/sequence-type.hpp>
#include <yactfr/metadata/variant-type.hpp>
#include <yactfr/metadata/field-ref.hpp>
#include <yactfr/metadata/exceptions.hpp>

#include "utils.hpp"

namespace yactfr {
namespace utils {

std::string indent(const Size indent)
{
    std::string ind;

    ind.reserve(indent * 2);

    for (Index i = 0; i < indent; ++i) {
        ind.append("  ");
    }

    return ind;
}

const DataType *findType(const DataType *type,
                         std::vector<std::string>::const_iterator refAt,
                         std::vector<std::string>::const_iterator refEnd)
{
    if (!type) {
        return nullptr;
    }

    if (refAt == refEnd) {
        return type;
    }

    if (type->isStructType()) {
        auto fieldType = type->asStructType()->findType(*refAt);

        if (!fieldType) {
            return nullptr;
        }

        return findType(fieldType, refAt + 1, refEnd);
    } else if (type->isArrayType()) {
        return findType(&type->asArrayType()->elemType(), refAt, refEnd);
    } else if (type->isSequenceType()) {
        return findType(&type->asSequenceType()->elemType(), refAt, refEnd);
    } else if (type->isVariantType()) {
        auto fieldType = type->asVariantType()->findType(*refAt);

        if (!fieldType) {
            return nullptr;
        }

        return findType(fieldType, refAt + 1, refEnd);
    }

    return nullptr;
}

std::string strError()
{
        std::vector<char> buf;

        buf.reserve(1024);
        strerror_r(errno, buf.data(), buf.capacity());
        return buf.data();
}

void throwIfScopeTypeIsNotStruct(const DataType *type, const char *scopeName)
{
    if (!type) {
        return;
    }

    if (!type->isStructType()) {
        std::ostringstream ss;

        ss << scopeName << " type must be a structure type.";
        throw InvalidMetadata {ss.str()};
    }
}

} // namespace utils
} // namespace yactfr
