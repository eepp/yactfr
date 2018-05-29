/*
 * CTF encoding.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Encoding.

@ingroup metadata
*/

#ifndef _YACTFR_METADATA_ENCODING_HPP
#define _YACTFR_METADATA_ENCODING_HPP

namespace yactfr {

/*!
@brief  Character encoding.

@ingroup metadata_dt
*/
enum class Encoding
{
    /// No character encoding.
    NONE,

    /// <a href="https://en.wikipedia.org/wiki/UTF-8">UTF-8</a>.
    UTF8,
};

} // namespace yactfr

#endif // _YACTFR_METADATA_ENCODING_HPP
