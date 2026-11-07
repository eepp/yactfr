/*
 * SPDX-FileCopyrightText: 2017-2018 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/scalar-dt.hpp>

namespace yactfr {

ScalarDataType::ScalarDataType(const _tKind kind, const unsigned int align, MapItem::Up attrs) :
    DataType {kind, align, std::move(attrs)}
{
}

} // namespace yactfr
