/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_TSDL_TSDL_ATTR_HPP
#define _YACTFR_INTERNAL_METADATA_TSDL_TSDL_ATTR_HPP

#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/utility.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/int-type-common.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/text-parse-error.hpp>

namespace yactfr {
namespace internal {

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
    enum class Kind {
        UNSET,
        STR,
        SINT,
        UINT,
        IDENT,
        CLK_NAME_VALUE,
    };

public:
    /*
     * Returns a display base from this attribute, throwing an error if
     * it cannot.
     */
    DisplayBase dispBase() const;

    /*
     * Ensures that the kind of this attribute is `expectedKind`,
     * throwing an error otherwise.
     */
    void checkKind(const Kind expectedKind) const;

    /*
     * Throws that this attribute is an unknown attribute.
     */
    void throwUnknown() const;

    /*
     * Throws that this attribute must be a boolean attribute.
     */
    void throwExpectingBool() const;

    /*
     * Returns an alignment from this attribute, throwing an error if
     * it's a wrong alignment or if the kind of this attribute isn't
     * expected.
     */
    unsigned int align() const;

    /*
     * Returns a byte order (or `boost::none` if native/default) from
     * this attribute, throwing an error if it cannot.
     */
    boost::optional<ByteOrder> bo() const;

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
    // kind of attribute
    Kind kind = Kind::UNSET;

    // name of attribute
    std::string name;

    // string value (for `STR`, `IDENT`, and `CLK_NAME_VALUE` kinds)
    std::string strVal;

    // unsigned integer value (for `UINT` kind)
    unsigned long long uintVal = 0;

    // signed integer value (for `SINT` kind)
    long long intVal = 0;

    // text location of the beginning of the parsed attribute name
    boost::optional<TextLocation> nameLoc;

    // text location of the beginning of the parsed attribute value
    boost::optional<TextLocation> valLoc;

    // true if this attribute can represent a boolean value
    bool hasEquivBool = false;

    // equivalent boolean value of attribute if `hasEquivBool` is true
    bool equivBool = false;

private:
    /*
     * String attribute to byte order (`boost::none` if native/default).
     *
     * Throws if the string is an unknown byte order.
     */
    boost::optional<ByteOrder> _toBo() const;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_TSDL_TSDL_ATTR_HPP
