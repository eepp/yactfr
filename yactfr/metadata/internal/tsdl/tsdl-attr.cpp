/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>
#include <tuple>
#include <set>

#include <yactfr/text-loc.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/text-parse-error.hpp>

#include "tsdl-attr.hpp"
#include "../../../internal/utils.hpp"

namespace yactfr {
namespace internal {

boost::optional<ByteOrder> TsdlAttr::_toBo() const
{
    if (strVal == "be" || strVal == "network") {
        return ByteOrder::BIG;
    } else if (strVal == "le") {
        return ByteOrder::LITTLE;
    } else if (strVal == "native") {
        return boost::none;
    }

    std::ostringstream ss;

    ss << "Invalid byte order `" << strVal << "`.";
    throwTextParseError(ss.str(), this->valTextLoc());
}

DisplayBase TsdlAttr::dispBase() const
{
    boost::optional<DisplayBase> dispBase;

    if (kind != Kind::UINT && kind != Kind::IDENT) {
        std::ostringstream ss;

        ss << "Attribute `" << name <<
              "`: expecting constant unsigned integer or identifier.";
        throwTextParseError(ss.str(), this->valTextLoc());
    }

    if (kind == Kind::UINT) {
        if (uintVal != 2 && uintVal != 8 && uintVal != 10 && uintVal != 16) {
            std::ostringstream ss;

            ss << "Invalid `base` attribute: " << uintVal << ".";
            throwTextParseError(ss.str(), this->valTextLoc());
        }

        dispBase = static_cast<DisplayBase>(uintVal);
    }

    if (strVal == "decimal" || strVal == "dec" || strVal == "d" || strVal == "i" || strVal == "u") {
        dispBase = DisplayBase::DECIMAL;
    } else if (strVal == "hexadecimal" || strVal == "hex" ||
            strVal == "x" || strVal == "X" || strVal == "p") {
        dispBase = DisplayBase::HEXADECIMAL;
    } else if (strVal == "octal" || strVal == "oct" || strVal == "o") {
        dispBase = DisplayBase::OCTAL;
    } else if (strVal == "binary" || strVal == "bin" || strVal == "b") {
        dispBase = DisplayBase::BINARY;
    }

    if (!dispBase) {
        std::ostringstream ss;

        ss << "Invalid `base` attribute: `" << strVal << "`.";
        throwTextParseError(ss.str(), this->valTextLoc());
    }

    return *dispBase;
}

void TsdlAttr::checkKind(const Kind expectedKind) const
{
    if (kind != expectedKind) {
        std::ostringstream ss;

        ss << "Attribute `" << name << "`: expecting ";

        switch (expectedKind) {
        case Kind::STR:
            ss << "literal string";
            break;

        case Kind::UINT:
            ss << "constant unsigned integer.";
            break;

        case Kind::SINT:
            ss << "constant signed integer.";
            break;

        case Kind::IDENT:
            ss << "identifier.";
            break;

        case Kind::CLK_NAME_VALUE:
            ss << "`clock.NAME.value`.";
            break;

        default:
            std::abort();
        }

        throwTextParseError(ss.str(), this->valTextLoc());
    }
}

void TsdlAttr::throwUnknown() const
{
    std::ostringstream ss;

    ss << "Unknown attribute `" << name << "`.";
    throwTextParseError(ss.str(), this->nameTextLoc());
}

unsigned int TsdlAttr::align() const
{
    this->checkKind(Kind::UINT);

    if (!isPowOfTwo(uintVal)) {
        std::ostringstream ss;

        ss << "Invalid `align` attribute (must be a power of two): " << uintVal << ".";
        throwTextParseError(ss.str(), this->valTextLoc());
    }

    return uintVal;
}

boost::optional<ByteOrder> TsdlAttr::bo() const
{
    this->checkKind(Kind::IDENT);
    return this->_toBo();
}

bool TsdlAttr::hasEncoding() const
{
    this->checkKind(Kind::IDENT);

    if (strVal == "NONE" || strVal == "none") {
        return false;
    } else if (strVal == "UTF8" || strVal == "utf8" || strVal == "ASCII" || strVal == "ascii") {
        return true;
    }

    std::ostringstream ss;

    ss << "Invalid encoding `" << strVal << "`.";
    throwTextParseError(ss.str(), this->valTextLoc());
}

bool TsdlAttr::boolEquiv() const
{
    switch (kind) {
    case Kind::UINT:
        if (uintVal == 1) {
            return true;
        } else if (uintVal == 0) {
            return false;
        }
        break;

    case Kind::IDENT:
        if (strVal == "true" || strVal == "TRUE") {
            return true;
        } else if (strVal == "false" || strVal == "FALSE") {
            return false;
        }

    default:
        break;
    }

    std::ostringstream ss;

    ss << "Expecting `0`, `false`, `FALSE`, `1`, `true`, or `TRUE` for `" <<
          name << "` attribute.";
    throwTextParseError(ss.str(), this->valTextLoc());
}

} // namespace internal
} // namespace yactfr
