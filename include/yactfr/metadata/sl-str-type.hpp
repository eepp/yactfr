/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_SL_STR_TYPE_HPP
#define _YACTFR_METADATA_SL_STR_TYPE_HPP

#include <memory>
#include <utility>

#include "non-nt-str-type.hpp"
#include "dt-visitor.hpp"
#include "../aliases.hpp"

namespace yactfr {

/*!
@brief
    Static-length string type.

@ingroup metadata_dt

A static-length string type describes data stream static-length strings.
*/
class StaticLengthStringType final :
    public NonNullTerminatedStringType
{
public:
    /// Unique pointer to constant static-length string type.
    using UP = std::unique_ptr<const StaticLengthStringType>;

public:
    /*!
    @brief
        Builds a static-length string type.

    @param[in] alignment
        Alignment of data stream static-length strings described by this
        type.
    @param[in] maximumLength
        Maximum length (UTF-8 bytes) of data stream static-length
        strings described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length strings described
        by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit StaticLengthStringType(unsigned int alignment, Size maximumLength,
                                    MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a static-length string type having a default alignment
        property (8).

    @param[in] maximumLength
        Maximum length (UTF-8 bytes) of data stream static-length
        strings described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream static-length strings described
        by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    */
    explicit StaticLengthStringType(Size maximumLength, MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Creates a constant static-length string type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the static-length string type
        constructor.

    @returns
        Created constant static-length string type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

    /// Maximum length (UTF-8 bytes) of data stream static-length
    /// strings described by this type.
    Size maximumLength() const noexcept
    {
        return _maxLen;
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    bool _isEqual(const DataType& other) const noexcept override;

private:
    const Size _maxLen;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_SL_STR_TYPE_HPP
