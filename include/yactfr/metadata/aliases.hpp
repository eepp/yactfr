/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_ALIASES_HPP
#define _YACTFR_METADATA_ALIASES_HPP

namespace yactfr {

/*!
@brief
    ID of a DataStreamType or EventRecordType.

@ingroup metadata
*/
using TypeId = unsigned long long;

/*!
@brief
    Numeric log level.

@ingroup metadata
*/
using LogLevel = long long;

/*!
@brief
    Clock cycles.

@ingroup metadata
*/
using Cycles = unsigned long long;

} // namespace yactfr

#endif // _YACTFR_METADATA_ALIASES_HPP
