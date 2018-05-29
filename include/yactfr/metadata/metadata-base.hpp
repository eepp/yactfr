/*
 * CTF metadata base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_METADATA_BASE_HPP
#define _YACTFR_METADATA_METADATA_BASE_HPP

namespace yactfr {

// Completely useless for the moment, should probably not exist
class MetadataBase
{
public:
    virtual ~MetadataBase() = 0;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_METADATA_BASE_HPP
