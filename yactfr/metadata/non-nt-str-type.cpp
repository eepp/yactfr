/*
 * SPDX-FileCopyrightText: 2022 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/non-nt-str-type.hpp>

namespace yactfr {

NonNullTerminatedStringType::NonNullTerminatedStringType(const _tKind kind,
                                                         const unsigned int align,
                                                         const StringEncoding encoding,
                                                         MapItem::Up attrs) :
    StringType {kind, align, encoding, std::move(attrs)}
{
}

} // namespace yactfr
