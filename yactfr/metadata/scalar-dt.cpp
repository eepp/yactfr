/*
 * Copyright (C) 2017-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/scalar-dt.hpp>

namespace yactfr {

ScalarDataType::ScalarDataType(const _Kind kind, const unsigned int align, MapItem::UP userAttrs) :
    DataType {kind, align, std::move(userAttrs)}
{
}

} // namespace yactfr
