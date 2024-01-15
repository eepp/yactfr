/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_NT_STR_TYPE_HPP
#define _YACTFR_METADATA_NT_STR_TYPE_HPP

#include <memory>
#include <utility>

#include "dt.hpp"
#include "str-type.hpp"
#include "dt-visitor.hpp"

namespace yactfr {

/*!
@brief
    Null-terminated string type.

@ingroup metadata_dt

A null-terminated string type describes data stream null-terminated
strings.
*/
class NullTerminatedStringType final :
    public StringType
{
public:
    /// Unique pointer to constant null-terminated string type.
    using UP = std::unique_ptr<const NullTerminatedStringType>;

public:
    /*!
    @brief
        Builds a null-terminated string type.

    @param[in] alignment
        Alignment of data stream null-terminated strings described by
        this type.
    @param[in] encoding
        Encoding of data stream null-terminated strings described by
        this type.
    @param[in] attributes
        @parblock
        Attributes of data stream null-terminated strings described
        by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock

    @pre
        \p alignment ≥ 8.
    @pre
        \p alignment is a power of two.
    */
    explicit NullTerminatedStringType(unsigned int alignment,
                                      StringEncoding encoding = StringEncoding::UTF_8,
                                      MapItem::UP attributes = nullptr);

    /*!
    @brief
        Builds a null-terminated string type having a default alignment
        property (8).

    @param[in] encoding
        Encoding of data stream null-terminated strings described by
        this type.
    @param[in] attributes
        @parblock
        Attributes of data stream null-terminated strings described
        by this type.

        If set, each key of \p *attributes is a namespace.
        @endparblock
    */
    explicit NullTerminatedStringType(StringEncoding encoding = StringEncoding::UTF_8,
                                      MapItem::UP attributes = nullptr);

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Null-terminated string type to copy.
    */
    NullTerminatedStringType(const NullTerminatedStringType& other);

    /*!
    @brief
        Creates a constant null-terminated string type unique pointer,
        forwarding \p args to the constructor.

    @param[in] args
        Arguments to forward to the null-terminated string type
        constructor.

    @returns
        Created constant null-terminated string type unique pointer.

    @pre
        See the preconditions of the constructor.
    */
    template <typename... ArgTs>
    static UP create(ArgTs&&... args)
    {
        return std::make_unique<UP::element_type>(std::forward<ArgTs>(args)...);
    }

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other null-terminated string type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const NullTerminatedStringType& other) const noexcept
    {
        return this->alignment() < other.alignment();
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

};

} // namespace yactfr

#endif // _YACTFR_METADATA_NT_STR_TYPE_HPP
