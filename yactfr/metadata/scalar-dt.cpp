/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/scalar-dt.hpp>

namespace yactfr {

ScalarDataType::ScalarDataType(const int kind, const unsigned int align) :
    DataType {_KIND_SCALAR | kind, align}
{
}

} // namespace yactfr
