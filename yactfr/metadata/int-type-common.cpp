/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/int-type-common.hpp>

namespace yactfr {

IntegerTypeCommon::IntegerTypeCommon(const DisplayBase prefDispBase) :
    _prefDispBase {prefDispBase}
{
}

bool IntegerTypeCommon::_isEqual(const IntegerTypeCommon& other) const noexcept
{
    return _prefDispBase == other._prefDispBase;
}

UnsignedIntegerTypeCommon::UnsignedIntegerTypeCommon(UnsignedIntegerTypeRoleSet&& roles) :
    _roles {std::move(roles)}
{
}

bool UnsignedIntegerTypeCommon::_isEqual(const UnsignedIntegerTypeCommon& other) const noexcept
{
    return _roles == other._roles;
}

} // namespace yactfr
