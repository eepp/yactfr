/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_FL_INT_TYPE_HPP
#define _YACTFR_METADATA_FL_INT_TYPE_HPP

#include <string>
#include <boost/optional.hpp>

#include "fl-bit-array-type.hpp"
#include "int-type-common.hpp"
#include "bo.hpp"
#include "dt.hpp"
#include "dt-visitor.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

} // namespace internal

/*!
@brief
    Abstract fixed-length integer type.

@ingroup metadata_dt

A fixed-length integer type describes data stream fixed-length integers.

Use the concrete FixedLengthSignedIntegerType and
FixedLengthUnsignedIntegerType depending on the signedness of the data
stream fixed-length integers to describe.
*/
class FixedLengthIntegerType :
    public FixedLengthBitArrayType,
    public IntegerTypeCommon
{
    friend class internal::TraceTypeImpl;

protected:
    explicit FixedLengthIntegerType(_Kind kind, unsigned int align, unsigned int len, ByteOrder bo,
                                    DisplayBase prefDispBase, MapItem::UP userAttrs);

public:
    /*!
    @brief
        Less-than operator.

    @attention
        This operator doesn't consider user attributes.

    @param[in] other
        Other fixed-length integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const FixedLengthIntegerType& other) const noexcept;

protected:
    bool _isEqual(const DataType& other) const noexcept override;
};

/*!
@brief
    Signed fixed-length integer type.

@ingroup metadata_dt

A signed fixed-length integer type describes data stream signed
integers.
*/
class FixedLengthSignedIntegerType :
    public FixedLengthIntegerType
{
protected:
    explicit FixedLengthSignedIntegerType(_Kind kind, unsigned int align, unsigned int len,
                                          ByteOrder bo, DisplayBase prefDispBase,
                                          MapItem::UP userAttrs);

public:
    /*!
    @brief
        Builds a fixed-length signed integer type.

    @param[in] alignment
        Alignment of data stream fixed-length signed integers described
        by this type.
    @param[in] length
        Length of data stream fixed-length signed integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length signed integers described
        by this type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length signed integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit FixedLengthSignedIntegerType(unsigned int alignment, unsigned int length,
                                          ByteOrder byteOrder,
                                          DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                          MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Builds a fixed-length signed integer type having a default
        alignment property (1).

    @param[in] length
        Length of data stream fixed-length signed integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length signed integers described
        by this type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length signed
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length signed integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock

    @pre
        \p length > 0.
    */
    explicit FixedLengthSignedIntegerType(unsigned int length, ByteOrder byteOrder,
                                          DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                          MapItem::UP userAttributes = nullptr);

    /*!
    @brief
        Less-than operator.

    @attention
        This operator doesn't consider user attributes.

    @param[in] other
        Other fixed-length signed integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const FixedLengthSignedIntegerType& other) const noexcept
    {
        return FixedLengthIntegerType::operator<(other);
    }

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length unsigned integer type.

@ingroup metadata_dt

An fixed-length unsigned integer type describes data stream fixed-length
unsigned integers.
*/
class FixedLengthUnsignedIntegerType :
    public FixedLengthIntegerType,
    public UnsignedIntegerTypeCommon
{
protected:
    explicit FixedLengthUnsignedIntegerType(_Kind kind, unsigned int align, unsigned int len,
                                            ByteOrder bo, DisplayBase prefDispBase,
                                            MapItem::UP userAttrs,
                                            UnsignedIntegerTypeRoleSet roles);

public:
    /*!
    @brief
        Builds a fixed-length unsigned integer type.

    @param[in] alignment
        Alignment of data stream fixed-length unsigned integers
        described by this type.
    @param[in] length
        Length of data stream fixed-length unsigned integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length unsigned integers
        described by this type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length unsigned integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of fixed-length unsigned integers described by this type.

    @pre
        \p alignment > 0.
    @pre
        \p alignment is a power of two.
    @pre
        \p length > 0.
    */
    explicit FixedLengthUnsignedIntegerType(unsigned int alignment, unsigned int length,
                                            ByteOrder byteOrder,
                                            DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                            MapItem::UP userAttributes = nullptr,
                                            UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Builds a fixed-length unsigned integer type having a default
        alignment property (1).

    @param[in] length
        Length of data stream fixed-length unsigned integers (bits)
        described by this type.
    @param[in] byteOrder
        Byte order of data stream fixed-length unsigned integers
        described by this type.
    @param[in] preferredDisplayBase
        Preferred display base of data stream fixed-length unsigned
        integers described by this type.
    @param[in] userAttributes
        @parblock
        User attributes of data stream fixed-length unsigned integers
        described by this type.

        If set, each key of \p *userAttributes is a namespace.
        @endparblock
    @param[in] roles
        Roles of fixed-length unsigned integers described by this type.

    @pre
        \p length > 0.
    */
    explicit FixedLengthUnsignedIntegerType(unsigned int length, ByteOrder byteOrder,
                                            DisplayBase preferredDisplayBase = DisplayBase::DECIMAL,
                                            MapItem::UP userAttributes = nullptr,
                                            UnsignedIntegerTypeRoleSet roles = {});

    /*!
    @brief
        Copy constructor.

    @param[in] other
        Fixed-length unsigned integer type to copy.
    */
    FixedLengthUnsignedIntegerType(const FixedLengthUnsignedIntegerType& other);

    /*!
    @brief
        Less-than operator.

    @param[in] other
        Other fixed-length unsigned integer type to compare to.

    @returns
        \c true if this type is less than \p other (respects total
        order).
    */
    bool operator<(const FixedLengthUnsignedIntegerType& other) const noexcept;

protected:
    bool _isEqual(const DataType& other) const noexcept override;

private:
    DataType::UP _clone() const override;

    void _accept(DataTypeVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

} // namespace yactfr

#endif // _YACTFR_METADATA_FL_INT_TYPE_HPP
