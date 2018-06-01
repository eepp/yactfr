/*
 * CTF data type base.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Data type.

@ingroup metadata_dt
*/

#ifndef _YACTFR_METADATA_DATA_TYPE_HPP
#define _YACTFR_METADATA_DATA_TYPE_HPP

#include <stdexcept>
#include <memory>
#include <boost/noncopyable.hpp>

#include "metadata-base.hpp"
#include "scope.hpp"
#include "fwd.hpp"

namespace yactfr {

/*!
@brief  Data type.

@ingroup metadata_dt
*/
class DataType :
    public MetadataBase,
    boost::noncopyable
{
public:
    /// Unique pointer to constant data type.
    using UP = std::unique_ptr<const DataType>;

protected:
    // data type's kind
    enum _Kind
    {
        _KIND_SIGNED_ENUM =       1 << 0,
        _KIND_UNSIGNED_ENUM =     1 << 1,
        _KIND_SIGNED_INT =        1 << 2,
        _KIND_UNSIGNED_INT =      1 << 3,
        _KIND_INT =               1 << 4,
        _KIND_ENUM =              1 << 5,
        _KIND_BIT_ARRAY =         1 << 6,
        _KIND_FLOAT =             1 << 7,
        _KIND_STRING =            1 << 8,
        _KIND_SCALAR =            1 << 9,
        _KIND_STRUCT =            1 << 10,
        _KIND_TEXT_ARRAY =        1 << 11,
        _KIND_ARRAY =             1 << 12,
        _KIND_TEXT_SEQUENCE =     1 << 13,
        _KIND_SEQUENCE =          1 << 14,
        _KIND_VARIANT =           1 << 15,
        _KIND_COMPOUND =          1 << 16,
    };

protected:
    explicit DataType(int kind, unsigned int alignment);
    explicit DataType(_Kind kind, unsigned int alignment);

public:
    /// Alignment of data stream bits described by this data type.
    unsigned int alignment() const noexcept
    {
        return _align;
    }

    /// \c true if this data type is a bit array type.
    bool isBitArrayType() const noexcept
    {
        return this->_isKind(_KIND_BIT_ARRAY);
    }

    /// \c true if this data type is an integer type.
    bool isIntType() const noexcept
    {
        return this->_isKind(_KIND_INT);
    }

    /// \c true if this data type is a signed integer type.
    bool isSignedIntType() const noexcept
    {
        return this->_isKind(_KIND_SIGNED_INT);
    }

    /// \c true if this data type is an unsigned integer type.
    bool isUnsignedIntType() const noexcept
    {
        return this->_isKind(_KIND_UNSIGNED_INT);
    }

    /// \c true if this data type is a floating point number type.
    bool isFloatType() const noexcept
    {
        return this->_isKind(_KIND_FLOAT);
    }

    /// \c true if this data type is an enumeration type.
    bool isEnumType() const noexcept
    {
        return this->_isKind(_KIND_ENUM);
    }

    /// \c true if this data type is a signed enumeration type.
    bool isSignedEnumType() const noexcept
    {
        return this->_isKind(_KIND_SIGNED_ENUM);
    }

    /// \c true if this data type is an unsigned enumeration type.
    bool isUnsignedEnumType() const noexcept
    {
        return this->_isKind(_KIND_UNSIGNED_ENUM);
    }

    /// \c true if this data type is a string type.
    bool isStringType() const noexcept
    {
        return this->_isKind(_KIND_STRING);
    }

    /// \c true if this data type is an array type.
    bool isArrayType() const noexcept
    {
        return this->_isKind(_KIND_ARRAY);
    }

    /// \c true if this data type is a text array type.
    bool isTextArrayType() const noexcept
    {
        return this->_isKind(_KIND_TEXT_ARRAY);
    }

    /// \c true if this data type is a sequence type.
    bool isSequenceType() const noexcept
    {
        return this->_isKind(_KIND_SEQUENCE);
    }

    /// \c true if this data type is a text sequence type.
    bool isTextSequenceType() const noexcept
    {
        return this->_isKind(_KIND_TEXT_SEQUENCE);
    }

    /// \c true if this data type is a structure type.
    bool isStructType() const noexcept
    {
        return this->_isKind(_KIND_STRUCT);
    }

    /// \c true if this data type is a variant type.
    bool isVariantType() const noexcept
    {
        return this->_isKind(_KIND_VARIANT);
    }

    /// \c true if this data type is a compound type.
    bool isCompoundType() const noexcept
    {
        return this->_isKind(_KIND_COMPOUND);
    }

    /*!
    @brief  This data type as a bit array type.

    @warning    You must make sure that this data type is indeed a
                bit array type before using the returned pointer.
    */
    const BitArrayType *asBitArrayType() const;

    /*!
    @brief  This data type as an integer type.

    @warning    You must make sure that this data type is indeed an
                integer type before using the returned
                pointer.
    */
    const IntType *asIntType() const;

    /*!
    @brief  This data type as a signed integer type.

    @warning    You must make sure that this data type is indeed a
                signed integer type before using the returned
                pointer.
    */
    const SignedIntType *asSignedIntType() const;

    /*!
    @brief  This data type as a unsigned integer type.

    @warning    You must make sure that this data type is indeed an
                unsigned integer type before using the returned
                pointer.
    */
    const UnsignedIntType *asUnsignedIntType() const;

    /*!
    @brief  This data type as a floating point number type.

    @warning    You must make sure that this data type is indeed a
                floating point number type before using the
                returned pointer.
    */
    const FloatType *asFloatType() const;

    /*!
    @brief  This data type as a signed enum type.

    @warning    You must make sure that this data type is indeed a
                signed enum type before using the returned
                pointer.
    */
    const SignedEnumType *asSignedEnumType() const;

    /*!
    @brief  This data type as an unsigned enum type.

    @warning    You must make sure that this data type is indeed an
                unsigned enum type before using the returned
                pointer.
    */
    const UnsignedEnumType *asUnsignedEnumType() const;

    /*!
    @brief  This data type as a string type.

    @warning    You must make sure that this data type is indeed a
                string type before using the returned pointer.
    */
    const StringType *asStringType() const;

    /*!
    @brief  This data type as a array type.

    @warning    You must make sure that this data type is indeed a
                array type before using the returned pointer.
    */
    const ArrayType *asArrayType() const;

    /*!
    @brief  This data type as a text array type.

    @warning    You must make sure that this data type is indeed a
                text array type before using the returned pointer.
    */
    const ArrayType *asTextArrayType() const;

    /*!
    @brief  This data type as a sequence type.

    @warning    You must make sure that this data type is indeed a
                sequence type before using the returned pointer.
    */
    const SequenceType *asSequenceType() const;

    /*!
    @brief  This data type as a text sequence type.

    @warning    You must make sure that this data type is indeed a
                text sequence type before using the returned pointer.
    */
    const TextSequenceType *asTextSequenceType() const;

    /*!
    @brief  This data type as a struct type.

    @warning    You must make sure that this data type is indeed a
                struct type before using the returned pointer.
    */
    const StructType *asStructType() const;

    /*!
    @brief  This data type as a variant type.

    @warning    You must make sure that this data type is indeed a
                variant type before using the returned pointer.
    */
    const VariantType *asVariantType() const;

    /*!
    @brief  Equality operator.

    @param otherType    Other type to compare with.
    @returns            \c true if \p otherType is equal to this data type.
    */
    bool operator==(const DataType& otherType) const;

    /*!
    @brief  Non-equality operator.

    @param otherType    Other type to compare with.
    @returns            \c true if \p otherType is not equal to this data type.
    */
    bool operator!=(const DataType& otherType) const;

    /// New clone (deep copy) of this data type.
    DataType::UP clone() const;

    /*!
    @brief  Accepts \p visitor as a visitor of this data type.

    @param visitor  Data type visitor to accept.
    */
    void accept(DataTypeVisitor& visitor) const;

protected:
    virtual DataType::UP _clone() const = 0;
    virtual void _accept(DataTypeVisitor& visitor) const = 0;
    virtual bool _compare(const DataType& otherType) const = 0;
    void _setAlign(unsigned int align);

private:
    bool _isKind(const _Kind kind) const noexcept
    {
        return _kind & kind;
    }

private:
    const _Kind _kind;
    unsigned int _align;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DATA_TYPE_HPP
