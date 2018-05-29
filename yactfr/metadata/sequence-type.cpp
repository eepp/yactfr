/*
 * CTF sequence type.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/sequence-type.hpp>

namespace yactfr {

SequenceType::SequenceType(const unsigned int minAlign, DataType::UP elemType,
                           const FieldRef& length) :
    SequenceType {_KIND_SEQUENCE, minAlign, std::move(elemType), length}
{
}

SequenceType::SequenceType(const int kind, const unsigned int minAlign,
                           DataType::UP elemType, const FieldRef& length) :
    ArraySequenceTypeBase {_KIND_SEQUENCE | kind, minAlign, std::move(elemType)},
    _length {length}
{
}

DataType::UP SequenceType::_clone() const
{
    return std::make_unique<SequenceType>(this->alignment(),
                                          this->elemType().clone(),
                                          this->length());
}

bool SequenceType::_compare(const DataType& otherType) const
{
    auto& seqType = static_cast<const SequenceType&>(otherType);

    return seqType.alignment() == this->alignment() &&
           seqType.elemType() == this->elemType() &&
           seqType.length() == this->length();
}

} // namespace yactfr
