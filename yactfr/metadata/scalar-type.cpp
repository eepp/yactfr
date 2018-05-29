/*
 * CTF scalar type base.
 *
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/scalar-type.hpp>

namespace yactfr {

ScalarType::ScalarType(const int kind, const unsigned int align) :
    DataType {_KIND_SCALAR | kind, align}
{
}

} // namespace yactfr
