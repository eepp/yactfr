/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_STR_TYPE_HPP
#define YACTFR_METADATA_STR_TYPE_HPP

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
    Utf8,

    /// UTF-16BE.
    Utf16Be,

    /// UTF-16LE.
    Utf16Le,

    /// UTF-32BE.
    Utf32Be,

    /// UTF-32LE.
    Utf32Le,
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
    explicit StringType(_tKind kind, unsigned int align, StringEncoding encoding,
                        MapItem::Up attrs);

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

#endif // YACTFR_METADATA_STR_TYPE_HPP
