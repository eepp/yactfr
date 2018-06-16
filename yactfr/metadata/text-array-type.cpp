/*
 * CTF text array type.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/text-array-type.hpp>
#include <yactfr/metadata/invalid-metadata.hpp>
#include <yactfr/metadata/int-type.hpp>

namespace yactfr {

TextArrayType::TextArrayType(const unsigned int align, const Encoding encoding,
                             const Size length) :
    ArrayType {
        _KIND_TEXT_ARRAY,
        align,
        std::make_unique<UnsignedIntType>(8, 8, ByteOrder::LITTLE,
                                          DisplayBase::HEXADECIMAL,
                                          encoding, boost::none),
        length
    }
{
    if (align < 8) {
        throw InvalidMetadata {
            "Text array type's alignment must be greater than or equal to 8."
        };
    }

    if (encoding == Encoding::NONE) {
        throw InvalidMetadata {
            "Text array type must have an encoding."
        };
    }
}

} // namespace yactfr
