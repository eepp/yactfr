/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
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
