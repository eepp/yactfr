/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_TSDL_TSDL_ATTR_HPP
#define YACTFR_INTERNAL_METADATA_TSDL_TSDL_ATTR_HPP

#include <cassert>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/int-type-common.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/text-parse-error.hpp>

namespace yactfr::internal {

/*
 * A TSDL attribute, the result of parsing something like this:
 *
 *     size = 32;
 *
 *     byte_order = be;
 *
 *     map = clock.monotonic.value;
 *
 *     custom_stuff = "hello there";
 */
class TsdlAttr final
{
public:
    // identifier value
    struct Ident final
    {
        std::string name;
    };

    // `clock.NAME.value` value
    struct ClkNameVal final
    {
        // `NAME` part
        std::string clkName;
    };

    /*
     * Value of a TSDL attribute, one of:
     *
     * `std::monostate`::
     *     Unset.
     *
     * `std::string`::
     *     Literal string.
     *
     * `Ident`::
     *     Identifier.
     *
     * `ClkNameVal`::
     *     `clock.NAME.value`.
     *
     * `unsigned long long`::
     *     Constant unsigned integer.
     *
     * `long long`::
     *     Constant signed integer.
     */
    using Val = std::variant<std::monostate, std::string, Ident, ClkNameVal,
                             unsigned long long, long long>;

public:
    /*
     * Returns the literal string value of this attribute, throwing an
     * error if it's not a literal string.
     */
    const std::string& strVal() const;

    /*
     * Returns the identifier value of this attribute, throwing an error
     * if it's not an identifier.
     */
    const std::string& identVal() const;

    /*
     * Returns the literal string or identifier value of this attribute,
     * throwing an error if it's neither.
     */
    const std::string& strOrIdentVal() const;

    /*
     * Returns the clock type name of the `clock.NAME.value` value of
     * this attribute, throwing an error if it's not such a value.
     */
    const std::string& clkNameVal() const;

    /*
     * Returns the constant unsigned integer value of this attribute,
     * throwing an error if it's not a constant unsigned integer.
     */
    unsigned long long uintVal() const;

    /*
     * Returns a display base from this attribute, throwing an error if
     * it cannot.
     */
    DisplayBase dispBase() const;

    /*
     * Throws that this attribute is an unknown attribute.
     */
    void throwUnknown() const;

    /*
     * Returns an alignment from this attribute, throwing an error if
     * it's a wrong alignment or if the value type of this attribute
     * isn't expected.
     */
    unsigned int align() const;

    /*
     * Returns a byte order (or `std::nullopt` if native/default) from
     * this attribute, throwing an error if it cannot.
     */
    std::optional<ByteOrder> bo() const;

    /*
     * Returns whether or not this attribute value is an encoding,
     * throwing an error if it cannot.
     */
    bool hasEncoding() const;

    /*
     * Returns the equivalent boolean value of this attribute, throwing
     * an error if it cannot.
     */
    bool boolEquiv() const;

    /*
     * Text location of the name part of this attribute.
     */
    TextLocation nameTextLoc() const noexcept
    {
        assert(nameLoc);
        return *nameLoc;
    }

    /*
     * Text location of the value part of this attribute.
     */
    TextLocation valTextLoc() const noexcept
    {
        assert(valLoc);
        return *valLoc;
    }

public:
    // name of attribute
    std::string name;

    // value of attribute
    Val val;

    // text location of the beginning of the parsed attribute name
    std::optional<TextLocation> nameLoc;

    // text location of the beginning of the parsed attribute value
    std::optional<TextLocation> valLoc;

private:
    /*
     * Returns the value of this attribute as `ValT`, throwing an error
     * mentioning `expectedDescr` if it's not a `ValT` value.
     */
    template <typename ValT>
    const ValT& _expectVal(std::string_view expectedDescr) const;

    /*
     * Throws that this attribute expects `expectedDescr`.
     */
    [[ noreturn ]] void _throwExpecting(std::string_view expectedDescr) const;
};

} // namespace yactfr::internal

#endif // YACTFR_INTERNAL_METADATA_TSDL_TSDL_ATTR_HPP
