/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>

namespace yactfr {

StaticTextArrayType::StaticTextArrayType(const unsigned int minAlign, const Size len) :
    StaticArrayType {
        _KIND_STATIC_TEXT_ARRAY, minAlign,
        std::make_unique<FixedLengthUnsignedIntegerType>(8, 8, ByteOrder::LITTLE), len, false
    }
{
}

} // namespace yactfr
