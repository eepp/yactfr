/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/dyn-text-array-type.hpp>
#include <yactfr/metadata/bo.hpp>
#include <yactfr/metadata/int-type.hpp>

namespace yactfr {

DynamicTextArrayType::DynamicTextArrayType(const unsigned int minAlign,
                                           DataLocation lenLoc) :
    DynamicArrayType {
        _KIND_DYN_TEXT_ARRAY, minAlign,
        std::make_unique<UnsignedIntegerType>(8, 8, ByteOrder::LITTLE),
        std::move(lenLoc)
    }
{
}

} // namespace yactfr
