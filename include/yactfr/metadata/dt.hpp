/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DT_HPP
#define _YACTFR_METADATA_DT_HPP

#include <memory>
#include <unordered_set>
#include <boost/noncopyable.hpp>

#include "fwd.hpp"

namespace yactfr {

class DataTypeVisitor;

/*!
@brief
    Data type.

@ingroup metadata_dt

A data type is the type of a data stream datum.
*/
class DataType :
    boost::noncopyable
{
public:
    /// Unique pointer to constant data type.
    using UP = std::unique_ptr<const DataType>;

protected:
    // kind of data type
    enum _Kind
    {
        _KIND_FL_BIT_ARRAY          = 1 << 1,
        _KIND_FL_BOOL               = 1 << 2,
        _KIND_FL_INT                = 1 << 3,
        _KIND_FL_SINT               = 1 << 4,
        _KIND_FL_UINT               = 1 << 5,
        _KIND_FL_ENUM               = 1 << 6,
        _KIND_FL_SENUM              = 1 << 7,
        _KIND_FL_UENUM              = 1 << 8,
        _KIND_FL_FLOAT              = 1 << 9,
        _KIND_NT_STR                = 1 << 10,
        _KIND_SCALAR                = 1 << 11,
        _KIND_STRUCT                = 1 << 12,
        _KIND_ARRAY                 = 1 << 13,
        _KIND_SL_ARRAY              = 1 << 14,
        _KIND_DL_ARRAY              = 1 << 15,
        _KIND_NON_NT_STRING         = 1 << 16,
        _KIND_SL_STR                = 1 << 17,
        _KIND_DL_STR                = 1 << 18,
        _KIND_BLOB                  = 1 << 19,
        _KIND_SL_BLOB               = 1 << 20,
        _KIND_DL_BLOB               = 1 << 21,
        _KIND_VAR                   = 1 << 22,
        _KIND_VAR_USEL              = 1 << 23,
        _KIND_VAR_SSEL              = 1 << 24,
        _KIND_COMPOUND              = 1 << 25,
    };

protected:
    explicit DataType(int kind, unsigned int alignment);
    explicit DataType(_Kind kind, unsigned int alignment);

public:
    virtual ~DataType() = default;

    /// Alignment of the first data stream bit described by this type.
    unsigned int alignment() const noexcept
    {
        return _align;
    }

    /// \c true if this type is a fixed-length bit array type.
    bool isFixedLengthBitArrayType() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY);
    }

    /// \c true if this type is a fixed-length boolean type.
    bool isFixedLengthBooleanType() const noexcept
    {
        return this->_isKind(_KIND_FL_BOOL);
    }

    /// \c true if this type is a fixed-length integer type.
    bool isFixedLengthIntegerType() const noexcept
    {
        return this->_isKind(_KIND_FL_INT);
    }

    /// \c true if this type is a fixed-length signed integer type.
    bool isFixedLengthSignedIntegerType() const noexcept
    {
        return this->_isKind(_KIND_FL_SINT);
    }

    /// \c true if this type is a fixed-length unsigned integer type.
    bool isFixedLengthUnsignedIntegerType() const noexcept
    {
        return this->_isKind(_KIND_FL_UINT);
    }

    /// \c true if this type is a fixed-length floating point number type.
    bool isFixedLengthFloatingPointNumberType() const noexcept
    {
        return this->_isKind(_KIND_FL_FLOAT);
    }

    /// \c true if this type is a fixed-length enumeration type.
    bool isFixedLengthEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_FL_ENUM);
    }

    /// \c true if this type is a fixed-length signed enumeration type.
    bool isSignedFixedLengthEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_FL_SENUM);
    }

    /// \c true if this type is a fixed-length unsigned enumeration type.
    bool isFixedLengthUnsignedEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_FL_UENUM);
    }

    /// \c true if this type is a null-terminated string type.
    bool isNullTerminatedStringType() const noexcept
    {
        return this->_isKind(_KIND_NT_STR);
    }

    /// \c true if this type is an array type.
    bool isArrayType() const noexcept
    {
        return this->_isKind(_KIND_ARRAY);
    }

    /// \c true if this type is a static-length array type.
    bool isStaticLengthArrayType() const noexcept
    {
        return this->_isKind(_KIND_SL_ARRAY);
    }

    /// \c true if this type is a dynamic-length array type.
    bool isDynamicLengthArrayType() const noexcept
    {
        return this->_isKind(_KIND_DL_ARRAY);
    }

    /// \c true if this type is a string type which is not a
    /// null-terminated string type.
    bool isNonNullTerminatedStringType() const noexcept
    {
        return this->_isKind(_KIND_NON_NT_STRING);
    }

    /// \c true if this type is a static-length string type.
    bool isStaticLengthStringType() const noexcept
    {
        return this->_isKind(_KIND_SL_STR);
    }

    /// \c true if this type is a dynamic-length string type.
    bool isDynamicLengthStringType() const noexcept
    {
        return this->_isKind(_KIND_DL_STR);
    }

    /// \c true if this type is a BLOB type.
    bool isBlobType() const noexcept
    {
        return this->_isKind(_KIND_BLOB);
    }

    /// \c true if this type is a static-length BLOB type.
    bool isStaticLengthBlobType() const noexcept
    {
        return this->_isKind(_KIND_SL_BLOB);
    }

    /// \c true if this type is a dynamic-length BLOB type.
    bool isDynamicLengthBlobType() const noexcept
    {
        return this->_isKind(_KIND_DL_BLOB);
    }

    /// \c true if this type is a structure type.
    bool isStructureType() const noexcept
    {
        return this->_isKind(_KIND_STRUCT);
    }

    /// \c true if this type is a variant type.
    bool isVariantType() const noexcept
    {
        return this->_isKind(_KIND_VAR);
    }

    /// \c true if this type is the type of data stream variants with an
    /// unsigned selector.
    bool isVariantWithUnsignedSelectorType() const noexcept
    {
        return this->_isKind(_KIND_VAR_USEL);
    }

    /// \c true if this type is the type of data stream variants with a
    /// signed selector.
    bool isVariantWithSignedSelectorType() const noexcept
    {
        return this->_isKind(_KIND_VAR_SSEL);
    }

    /// \c true if this type is a compound type (contains another data
    /// type).
    bool isCompoundDataType() const noexcept
    {
        return this->_isKind(_KIND_COMPOUND);
    }

    /*!
    @brief
        Returns this type as a fixed-length bit array type.

    @pre
        This type is a fixed-length bit array type.
    */
    const FixedLengthBitArrayType& asFixedLengthBitArrayType() const noexcept;

    /*!
    @brief
        Returns this type as a fixed-length boolean type.

    @pre
        This type is a fixed-length boolean type.
    */
    const FixedLengthBooleanType& asFixedLengthBooleanType() const noexcept;

    /*!
    @brief
        This type as a fixed-length integer type.

    @pre
        This type is a fixed-length integer type.
    */
    const FixedLengthIntegerType& asFixedLengthIntegerType() const noexcept;

    /*!
    @brief
        This type as a fixed-length signed integer type.

    @pre
        This type is a fixed-length signed integer type.
    */
    const FixedLengthSignedIntegerType& asFixedLengthSignedIntegerType() const noexcept;

    /*!
    @brief
        This type as a fixed-length unsigned integer type.

    @pre
        This type is a fixed-length unsigned integer type.
    */
    const FixedLengthUnsignedIntegerType& asFixedLengthUnsignedIntegerType() const noexcept;

    /*!
    @brief
        This type as a fixed-length floating point number type.

    @pre
        This type is a fixed-length floating point number type.
    */
    const FixedLengthFloatingPointNumberType& asFixedLengthFloatingPointNumberType() const noexcept;

    /*!
    @brief
        This type as a fixed-length signed enumeration type.

    @pre
        This type is a fixed-length signed enumeration type.
    */
    const SignedFixedLengthEnumerationType& asFixedLengthSignedEnumerationType() const noexcept;

    /*!
    @brief
        This type as a fixed-length unsigned enumeration type.

    @pre
        This type is a fixed-length unsigned enumeration type.
    */
    const FixedLengthUnsignedEnumerationType& asFixedLengthUnsignedEnumerationType() const noexcept;

    /*!
    @brief
        This type as a null-terminated string type.

    @pre
        This type is a null-terminated string type.
    */
    const NullTerminatedStringType& asNullTerminatedStringType() const noexcept;

    /*!
    @brief
        This type as an array type.

    @pre
        This type is an array type.
    */
    const ArrayType& asArrayType() const noexcept;

    /*!
    @brief
        This type as a static-length array type.

    @pre
        This type is a static-length array type.
    */
    const StaticLengthArrayType& asStaticLengthArrayType() const noexcept;

    /*!
    @brief
        This type as a dynamic-length array type.

    @pre
        This type is a dynamic-length array type.
    */
    const DynamicLengthArrayType& asDynamicLengthArrayType() const noexcept;

    /*!
    @brief
        This type as a non null-terminated string type.

    @pre
        This type is a non null-terminated string type.
    */
    const NonNullTerminatedStringType& asNonNullTerminatedStringType() const noexcept;

    /*!
    @brief
        This type as a static-length string type.

    @pre
        This type is a static-length string type.
    */
    const StaticLengthStringType& asStaticLengthStringType() const noexcept;

    /*!
    @brief
        This type as a dynamic-length string type.

    @pre
        This type is a dynamic-length string type.
    */
    const DynamicLengthStringType& asDynamicLengthStringType() const noexcept;

    /*!
    @brief
        This type as a BLOB type.

    @pre
        This type is a BLOB type.
    */
    const BlobType& asBlobType() const noexcept;

    /*!
    @brief
        This type as a static-length BLOB type.

    @pre
        This type is a static-length BLOB type.
    */
    const StaticLengthBlobType& asStaticLengthBlobType() const noexcept;

    /*!
    @brief
        This type as a dynamic-length BLOB type.

    @pre
        This type is a dynamic-length BLOB type.
    */
    const DynamicLengthBlobType& asDynamicLengthBlobType() const noexcept;

    /*!
    @brief
        This type as a structure type.

    @pre
        This type is a structure type.
    */
    const StructureType& asStructureType() const noexcept;

    /*!
    @brief
        This type as the type of data stream variants with an
        unsigned selector.

    @pre
        This type is the type of data stream variants with an unsigned
        selector.
    */
    const VariantWithUnsignedSelectorType& asVariantWithUnsignedSelectorType() const noexcept;

    /*!
    @brief
        This type as the type of data stream variants with a signed
        selector.

    @pre
        This type is the type of data stream variants with a signed
        selector.
    */
    const VariantWithSignedSelectorType& asVariantWithSignedSelectorType() const noexcept;

    /*!
    @brief
        Equality operator.

    @param[in] other
        Other type to compare to.

    @returns
        \c true if \p other is equal to this type.
    */
    bool operator==(const DataType& other) const noexcept;

    /*!
    @brief
        Non-equality operator.

    @param[in] other
        Other type to compare to.

    @returns
        \c true if \p other is not equal to this type.
    */
    bool operator!=(const DataType& other) const noexcept;

    /*!
    @brief
        Clones this type and returns it.

    @returns
        Clone of this type.
    */
    DataType::UP clone() const;

    /*!
    @brief
        Accepts \p visitor to visit this type.

    @param[in] visitor
        Data type visitor to accept.
    */
    void accept(DataTypeVisitor& visitor) const;

protected:
    virtual DataType::UP _clone() const = 0;
    virtual void _accept(DataTypeVisitor& visitor) const = 0;
    virtual bool _compare(const DataType& other) const noexcept = 0;

    _Kind _kind() const noexcept
    {
        return _theKind;
    }

private:
    bool _isKind(const _Kind kind) const noexcept
    {
        return _theKind & kind;
    }

private:
    const _Kind _theKind;
    unsigned int _align;
};

/*!
@brief
    Data type set.

@ingroup metadata_dt
*/
using DataTypeSet = std::unordered_set<const DataType *>;

} // namespace yactfr

#endif // _YACTFR_METADATA_DT_HPP
