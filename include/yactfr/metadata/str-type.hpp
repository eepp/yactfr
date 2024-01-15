/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_STR_TYPE_HPP
#define _YACTFR_METADATA_STR_TYPE_HPP

#include "dt.hpp"
#include "scalar-dt.hpp"

namespace yactfr {

/*!
@brief
    String encoding.

@ingroup metadata_dt
*/
enum class StringEncoding
{
    /// UTF-8.
    UTF_8,

    /// UTF-16BE.
    UTF_16BE,

    /// UTF-16LE.
    UTF_16LE,

    /// UTF-32BE.
    UTF_32BE,

    /// UTF-32LE.
    UTF_32LE,
};

/*!
@brief
    Common interface of NullTerminatedStringType and
    NonNullTerminatedStringType.

@ingroup metadata_dt
*/
class StringType :
    public ScalarDataType
{
protected:
    explicit StringType(_Kind kind, unsigned int align, StringEncoding encoding,
                        MapItem::UP attrs);

public:
    /// Encoding of a string described by this type.
    StringEncoding encoding() const noexcept
    {
        return _encoding;
    }

protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    const StringEncoding _encoding;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_STR_TYPE_HPP
