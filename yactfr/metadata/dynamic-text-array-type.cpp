/*
 * CTF dynamic text array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <boost/optional/optional.hpp>

#include <yactfr/metadata/dynamic-text-array-type.hpp>
#include <yactfr/metadata/invalid-metadata.hpp>
#include <yactfr/metadata/byte-order.hpp>
#include <yactfr/metadata/int-type.hpp>

namespace yactfr {

DynamicTextArrayType::DynamicTextArrayType(const unsigned int align,
                                           const Encoding encoding,
                                           const FieldRef& length) :
    DynamicArrayType {
        _KIND_DYNAMIC_TEXT_ARRAY, align,
        std::make_unique<UnsignedIntType>(8, 8, ByteOrder::LITTLE,
                                          DisplayBase::HEXADECIMAL,
                                          encoding, boost::none),
        length
    }
{
    if (align < 8) {
        throw InvalidMetadata {
            "Dynamic text array type's alignment must be greater than or equal to 8."
        };
    }

    if (encoding == Encoding::NONE) {
        throw InvalidMetadata {
            "Dynamic text array type must have an encoding."
        };
    }
}

} // namespace yactfr
