/*
 * CTF array/sequence type base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <yactfr/metadata/exceptions.hpp>
#include <yactfr/metadata/array-sequence-type-base.hpp>

namespace yactfr {

ArraySequenceTypeBase::ArraySequenceTypeBase(const int kind,
                                             const unsigned int minAlign,
                                             DataType::UP elemType) :
    CompoundType {kind, std::max(minAlign, elemType->alignment())},
    _elemType {std::move(elemType)}
{
    if (!_elemType) {
        throw InvalidMetadata {
            "Array or sequence type's element type is null."
        };
    }
}

} // namespace yactfr
