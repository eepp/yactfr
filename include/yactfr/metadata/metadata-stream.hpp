/*
 * Metadata stream.
 *
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Metadata stream and related exception.

@ingroup metadata_stream
*/

#ifndef _YACTFR_METADATA_METADATA_STREAM_HPP
#define _YACTFR_METADATA_METADATA_STREAM_HPP

#include <cstdlib>
#include <string>
#include <boost/uuid/uuid.hpp>

#include <yactfr/aliases.hpp>

namespace yactfr {

/*!
@brief  Metadata stream.

@ingroup metadata_stream
*/
class MetadataStream
{
protected:
    explicit MetadataStream(std::string&& text);

public:
    virtual ~MetadataStream();

    /// Metadata text.
    const std::string& text() const noexcept
    {
        return _text;
    }

    /// \c true if the metadata text has a recognized signature,
    /// that is, <code>/* CTF 1.8</code>.
    bool hasSignature() const noexcept;

private:
    const std::string _text;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_METADATA_STREAM_HPP
