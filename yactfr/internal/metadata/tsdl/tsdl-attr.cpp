/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cctype>
#include <sstream>
#include <limits>

#include <yactfr/text-parse-error.hpp>

#include "tsdl-attr.hpp"
#include "../../utils.hpp"

namespace yactfr::internal {

void TsdlAttr::_throwExpecting(const std::string_view expectedDescr) const
{
    std::ostringstream ss;

    ss << "Attribute `" << name << "`: expecting " << expectedDescr << ".";
    throwTextParseError(ss.str(), this->valTextLoc());
}

template <typename ValT>
const ValT& TsdlAttr::_expectVal(const std::string_view expectedDescr) const
{
    if (const auto typedVal = std::get_if<ValT>(&val)) {
        return *typedVal;
    }

    this->_throwExpecting(expectedDescr);
}

const std::string& TsdlAttr::strVal() const
{
    return this->_expectVal<std::string>("literal string");
}

const std::string& TsdlAttr::identVal() const
{
    return this->_expectVal<Ident>("identifier").name;
}

const std::string& TsdlAttr::strOrIdentVal() const
{
    if (const auto ident = std::get_if<Ident>(&val)) {
        return ident->name;
    } else if (const auto str = std::get_if<std::string>(&val)) {
        return *str;
    }

    this->_throwExpecting("identifier or literal string");
}

const std::string& TsdlAttr::clkNameVal() const
{
    return this->_expectVal<ClkNameVal>("`clock.NAME.value`").clkName;
}

unsigned long long TsdlAttr::uintVal() const
{
    return this->_expectVal<unsigned long long>("constant unsigned integer");
}

long long TsdlAttr::sIntVal() const
{
    if (const auto sIntVal = std::get_if<long long>(&val)) {
        return *sIntVal;
    }

    const auto uIntVal = std::get_if<unsigned long long>(&val);

    if (!uIntVal) {
        this->_throwExpecting("constant signed integer");
    }

    if (*uIntVal > static_cast<unsigned long long>(std::numeric_limits<long long>::max())) {
        std::ostringstream ss;

        ss << "Attribute `" << name << "`: value is too large: " << *uIntVal << ".";
        throwTextParseError(ss.str(), this->valTextLoc());
    }

    return static_cast<long long>(*uIntVal);
}

DisplayBase TsdlAttr::dispBase() const
{
    if (const auto uintVal = std::get_if<unsigned long long>(&val)) {
        if (*uintVal != 2 && *uintVal != 8 && *uintVal != 10 && *uintVal != 16) {
            std::ostringstream ss;

            ss << "Invalid `base` attribute: " << *uintVal << ".";
            throwTextParseError(ss.str(), this->valTextLoc());
        }

        return static_cast<DisplayBase>(*uintVal);
    }

    const auto ident = std::get_if<Ident>(&val);

    if (!ident) {
        this->_throwExpecting("constant unsigned integer or identifier");
    }

    const auto& str = ident->name;

    if (str == "decimal" || str == "dec" || str == "d" || str == "i" || str == "u") {
        return DisplayBase::Decimal;
    } else if (str == "hexadecimal" || str == "hex" || str == "x" || str == "X" || str == "p") {
        return DisplayBase::Hexadecimal;
    } else if (str == "octal" || str == "oct" || str == "o") {
        return DisplayBase::Octal;
    } else if (str == "binary" || str == "bin" || str == "b") {
        return DisplayBase::Binary;
    }

    std::ostringstream ss;

    ss << "Invalid `base` attribute: `" << str << "`.";
    throwTextParseError(ss.str(), this->valTextLoc());
}

void TsdlAttr::throwUnknown() const
{
    std::ostringstream ss;

    ss << "Unknown attribute `" << name << "`.";
    throwTextParseError(ss.str(), this->nameTextLoc());
}

unsigned int tsdlAlign(const unsigned long long val, const std::string_view descr,
                       const TextLocation& loc)
{
    assert(!descr.empty());

    if (!isPowOfTwo(val)) {
        std::ostringstream ss;

        ss << "Invalid " << descr << " (must be a power of two): " << val << ".";
        throwTextParseError(ss.str(), loc);
    }

    if (val > std::numeric_limits<unsigned int>::max()) {
        std::ostringstream ss;

        ss << static_cast<char>(std::toupper(static_cast<unsigned char>(descr.front()))) <<
              descr.substr(1) << " is too large (unsupported): " << val << ".";
        throwTextParseError(ss.str(), loc);
    }

    return static_cast<unsigned int>(val);
}

unsigned int TsdlAttr::align() const
{
    return tsdlAlign(this->uintVal(), "`align` attribute", this->valTextLoc());
}

std::optional<ByteOrder> TsdlAttr::bo() const
{
    const auto& ident = this->identVal();

    if (ident == "be" || ident == "network") {
        return ByteOrder::Big;
    } else if (ident == "le") {
        return ByteOrder::Little;
    } else if (ident == "native") {
        return std::nullopt;
    }

    std::ostringstream ss;

    ss << "Invalid byte order `" << ident << "`.";
    throwTextParseError(ss.str(), this->valTextLoc());
}

bool TsdlAttr::hasEncoding() const
{
    const auto& ident = this->identVal();

    if (ident == "NONE" || ident == "none") {
        return false;
    } else if (ident == "UTF8" || ident == "utf8" || ident == "ASCII" || ident == "ascii") {
        return true;
    }

    std::ostringstream ss;

    ss << "Invalid encoding `" << ident << "`.";
    throwTextParseError(ss.str(), this->valTextLoc());
}

bool TsdlAttr::boolEquiv() const
{
    if (const auto uintVal = std::get_if<unsigned long long>(&val)) {
        if (*uintVal == 1) {
            return true;
        } else if (*uintVal == 0) {
            return false;
        }
    } else if (const auto ident = std::get_if<Ident>(&val)) {
        if (ident->name == "true" || ident->name == "TRUE") {
            return true;
        } else if (ident->name == "false" || ident->name == "FALSE") {
            return false;
        }
    }

    std::ostringstream ss;

    ss << "Expecting `0`, `false`, `FALSE`, `1`, `true`, or `TRUE` for `" <<
          name << "` attribute.";
    throwTextParseError(ss.str(), this->valTextLoc());
}

} // namespace yactfr::internal
