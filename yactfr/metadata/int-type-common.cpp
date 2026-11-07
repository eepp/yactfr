/*
 * SPDX-FileCopyrightText: 2022-2024 Philippe Proulx <eepp.ca>
 * SPDX-License-Identifier: MIT
 */

#include <yactfr/metadata/int-type-common.hpp>

namespace yactfr {

UnsignedIntegerTypeCommon::UnsignedIntegerTypeCommon(UnsignedIntegerTypeRoleSet&& roles) :
    _roles {std::move(roles)}
{
}

bool UnsignedIntegerTypeCommon::_isEqual(const UnsignedIntegerTypeCommon& other) const noexcept
{
    return _roles == other._roles;
}

} // namespace yactfr
