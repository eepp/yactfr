/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/non-nt-str-type.hpp>

namespace yactfr {

NonNullTerminatedStringType::NonNullTerminatedStringType(const _Kind kind,
                                                         const unsigned int align,
                                                         const StringEncoding encoding,
                                                         MapItem::UP userAttrs) :
    StringType {kind, align, encoding, std::move(userAttrs)}
{
}

} // namespace yactfr
