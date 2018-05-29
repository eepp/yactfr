/*
 * CTF compound type base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/compound-type.hpp>

namespace yactfr {

CompoundType::CompoundType(const int kind, const unsigned int align) :
    DataType {_KIND_COMPOUND | kind, align}
{
}

} // namespace yactfr
