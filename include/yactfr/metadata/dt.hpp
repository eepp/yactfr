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
#include "item.hpp"

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
        _KIND_SCALAR                = 1 << 1,
        _KIND_BIT_ARRAY             = (1 << 2) | _KIND_SCALAR,
        _KIND_S                     = (1 << 3) | _KIND_SCALAR,
        _KIND_U                     = (1 << 4) | _KIND_SCALAR,
        _KIND_FL                    = (1 << 5) | _KIND_SCALAR,
        _KIND_INT                   = (1 << 6) | _KIND_BIT_ARRAY,
        _KIND_UINT                  = _KIND_U | _KIND_INT,
        _KIND_SINT                  = _KIND_S | _KIND_INT,
        _KIND_ENUM                  = (1 << 7) | _KIND_INT,
        _KIND_UENUM                 = _KIND_U | _KIND_ENUM,
        _KIND_SENUM                 = _KIND_S | _KIND_ENUM,
        _KIND_FL_BIT_ARRAY          = _KIND_FL | _KIND_BIT_ARRAY,
        _KIND_FL_BOOL               = (1 << 8) | _KIND_FL_BIT_ARRAY,
        _KIND_FL_INT                = _KIND_FL | _KIND_INT,
        _KIND_FL_SINT               = _KIND_FL | _KIND_SINT,
        _KIND_FL_UINT               = _KIND_FL | _KIND_UINT,
        _KIND_FL_ENUM               = _KIND_FL | _KIND_ENUM,
        _KIND_FL_SENUM              = _KIND_FL | _KIND_SENUM,
        _KIND_FL_UENUM              = _KIND_FL | _KIND_UENUM,
        _KIND_FL_FLOAT              = (1 << 9) | _KIND_FL_BIT_ARRAY,
        _KIND_VL                    = (1 << 10) | _KIND_SCALAR,
        _KIND_VL_BIT_ARRAY          = _KIND_VL | _KIND_BIT_ARRAY,
        _KIND_VL_INT                = _KIND_VL | _KIND_INT,
        _KIND_VL_SINT               = _KIND_VL | _KIND_SINT,
        _KIND_VL_UINT               = _KIND_VL | _KIND_UINT,
        _KIND_VL_ENUM               = _KIND_VL | _KIND_ENUM,
        _KIND_VL_SENUM              = _KIND_VL | _KIND_SENUM,
        _KIND_VL_UENUM              = _KIND_VL | _KIND_SENUM,
        _KIND_NT_STR                = (1 << 11) | _KIND_SCALAR,
        _KIND_COMPOUND              = 1 << 12,
        _KIND_STRUCT                = (1 << 13) | _KIND_COMPOUND,
        _KIND_ARRAY                 = (1 << 14) | _KIND_COMPOUND,
        _KIND_SL                    = 1 << 15,
        _KIND_DL                    = 1 << 16,
        _KIND_SL_ARRAY              = _KIND_SL | _KIND_ARRAY,
        _KIND_DL_ARRAY              = _KIND_DL | _KIND_ARRAY,
        _KIND_NON_NT_STR            = (1 << 17) | _KIND_SCALAR,
        _KIND_SL_STR                = _KIND_SL | _KIND_NON_NT_STR,
        _KIND_DL_STR                = _KIND_DL | _KIND_NON_NT_STR,
        _KIND_BLOB                  = (1 << 18) | _KIND_SCALAR,
        _KIND_SL_BLOB               = _KIND_SL | _KIND_BLOB,
        _KIND_DL_BLOB               = _KIND_DL | _KIND_BLOB,
        _KIND_VAR                   = (1 << 19) | _KIND_COMPOUND,
        _KIND_UINT_SEL              = 1 << 20,
        _KIND_SINT_SEL              = 1 << 21,
        _KIND_BOOL_SEL              = 1 << 22,
        _KIND_VAR_UINT_SEL          = _KIND_VAR | _KIND_UINT_SEL,
        _KIND_VAR_SINT_SEL          = _KIND_VAR | _KIND_SINT_SEL,
        _KIND_OPT                   = (1 << 23) | _KIND_COMPOUND,
        _KIND_OPT_UINT_SEL          = _KIND_OPT | _KIND_UINT_SEL,
        _KIND_OPT_SINT_SEL          = _KIND_OPT | _KIND_SINT_SEL,
        _KIND_OPT_INT_SEL           = _KIND_OPT_UINT_SEL | _KIND_OPT_SINT_SEL,
        _KIND_OPT_BOOL_SEL          = _KIND_OPT | _KIND_BOOL_SEL,
    };

protected:
    explicit DataType(_Kind kind, unsigned int align, MapItem::UP userAttrs);

public:
    virtual ~DataType() = default;

    /// Alignment of the first data stream bit described by this type.
    unsigned int alignment() const noexcept
    {
        return _align;
    }

    /*!
    @brief
        User attributes.

    If set, each key of the returned map item is a namespace.

    @note
        Even if the return value isn't \c nullptr, the returned map
        item may still be empty (which also means no user attributes).
    */
    const MapItem *userAttributes() const noexcept
    {
        return _userAttrs.get();
    }

    /// \c true if this type is a bit array type.
    bool isBitArrayType() const noexcept
    {
        return this->_isKind(_KIND_BIT_ARRAY);
    }

    /// \c true if this type is an integer type.
    bool isIntegerType() const noexcept
    {
        return this->_isKind(_KIND_INT);
    }

    /// \c true if this type is a signed integer type.
    bool isSignedIntegerType() const noexcept
    {
        return this->_isKind(_KIND_SINT);
    }

    /// \c true if this type is an unsigned integer type.
    bool isUnsignedIntegerType() const noexcept
    {
        return this->_isKind(_KIND_UINT);
    }

    /// \c true if this type is an enumeration type.
    bool isEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_ENUM);
    }

    /// \c true if this type is a signed enumeration type.
    bool isSignedEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_SENUM);
    }

    /// \c true if this type is an unsigned enumeration type.
    bool isUnsignedEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_UENUM);
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

    /// \c true if this type is a fixed-length floating point number
    /// type.
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
    bool isFixedLengthSignedEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_FL_SENUM);
    }

    /// \c true if this type is a fixed-length unsigned enumeration
    /// type.
    bool isFixedLengthUnsignedEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_FL_UENUM);
    }

    /// \c true if this type is a variable-length bit array type.
    bool isVariableLengthBitArrayType() const noexcept
    {
        return this->_isKind(_KIND_VL_BIT_ARRAY);
    }

    /// \c true if this type is a variable-length integer type.
    bool isVariableLengthIntegerType() const noexcept
    {
        return this->_isKind(_KIND_VL_INT);
    }

    /// \c true if this type is a variable-length signed integer type.
    bool isVariableLengthSignedIntegerType() const noexcept
    {
        return this->_isKind(_KIND_VL_SINT);
    }

    /// \c true if this type is a variable-length unsigned integer type.
    bool isVariableLengthUnsignedIntegerType() const noexcept
    {
        return this->_isKind(_KIND_VL_UINT);
    }

    /// \c true if this type is a variable-length enumeration type.
    bool isVariableLengthEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_VL_ENUM);
    }

    /// \c true if this type is a variable-length signed enumeration
    /// type.
    bool isVariableLengthSignedEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_VL_SENUM);
    }

    /// \c true if this type is a variable-length unsigned enumeration
    /// type.
    bool isVariableLengthUnsignedEnumerationType() const noexcept
    {
        return this->_isKind(_KIND_VL_UENUM);
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
        return this->_isKind(_KIND_NON_NT_STR);
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
    /// unsigned integer selector.
    bool isVariantWithUnsignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_KIND_VAR_UINT_SEL);
    }

    /// \c true if this type is the type of data stream variants with a
    /// signed integer selector.
    bool isVariantWithSignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_KIND_VAR_SINT_SEL);
    }

    /// \c true if this type is a optional type.
    bool isOptionalType() const noexcept
    {
        return this->_isKind(_KIND_OPT);
    }

    /// \c true if this type is the type of data stream optionals with
    /// a boolean selector.
    bool isOptionalWithBooleanSelectorType() const noexcept
    {
        return this->_isKind(_KIND_OPT_BOOL_SEL);
    }

    /// \c true if this type is the type of data stream optionals with
    /// an integer selector.
    bool isOptionalWithIntegerSelectorType() const noexcept
    {
        return this->_isKind(_KIND_OPT_INT_SEL);
    }

    /// \c true if this type is the type of data stream optionals with
    /// an unsigned integer selector.
    bool isOptionalWithUnsignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_KIND_OPT_UINT_SEL);
    }

    /// \c true if this type is the type of data stream optionals with a
    /// signed integer selector.
    bool isOptionalWithSignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_KIND_OPT_SINT_SEL);
    }

    /// \c true if this type is a scalar type (doesn't contains another
    /// data type).
    bool isScalarDataType() const noexcept
    {
        return this->_isKind(_KIND_SCALAR);
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
        Returns this type as a fixed-length integer type.

    @pre
        This type is a fixed-length integer type.
    */
    const FixedLengthIntegerType& asFixedLengthIntegerType() const noexcept;

    /*!
    @brief
        Returns this type as a fixed-length signed integer type.

    @pre
        This type is a fixed-length signed integer type.
    */
    const FixedLengthSignedIntegerType& asFixedLengthSignedIntegerType() const noexcept;

    /*!
    @brief
        Returns this type as a fixed-length unsigned integer type.

    @pre
        This type is a fixed-length unsigned integer type.
    */
    const FixedLengthUnsignedIntegerType& asFixedLengthUnsignedIntegerType() const noexcept;

    /*!
    @brief
        Returns this type as a fixed-length floating point number type.

    @pre
        This type is a fixed-length floating point number type.
    */
    const FixedLengthFloatingPointNumberType& asFixedLengthFloatingPointNumberType() const noexcept;

    /*!
    @brief
        Returns this type as a fixed-length signed enumeration type.

    @pre
        This type is a fixed-length signed enumeration type.
    */
    const FixedLengthSignedEnumerationType& asFixedLengthSignedEnumerationType() const noexcept;

    /*!
    @brief
        Returns this type as a fixed-length unsigned enumeration type.

    @pre
        This type is a fixed-length unsigned enumeration type.
    */
    const FixedLengthUnsignedEnumerationType& asFixedLengthUnsignedEnumerationType() const noexcept;

    /*!
    @brief
        Returns this type as a variable-length bit array type.

    @pre
        This type is a variable-length bit array type.
    */
    const VariableLengthBitArrayType& asVariableLengthBitArrayType() const noexcept;

    /*!
    @brief
        Returns this type as a variable-length integer type.

    @pre
        This type is a variable-length integer type.
    */
    const VariableLengthIntegerType& asVariableLengthIntegerType() const noexcept;

    /*!
    @brief
        Returns this type as a variable-length signed integer type.

    @pre
        This type is a variable-length signed integer type.
    */
    const VariableLengthSignedIntegerType& asVariableLengthSignedIntegerType() const noexcept;

    /*!
    @brief
        Returns this type as a variable-length unsigned integer type.

    @pre
        This type is a variable-length unsigned integer type.
    */
    const VariableLengthUnsignedIntegerType& asVariableLengthUnsignedIntegerType() const noexcept;

    /*!
    @brief
        Returns this type as a variable-length signed enumeration type.

    @pre
        This type is a variable-length signed enumeration type.
    */
    const VariableLengthSignedEnumerationType& asVariableLengthSignedEnumerationType() const noexcept;

    /*!
    @brief
        Returns this type as a variable-length unsigned enumeration
        type.

    @pre
        This type is a variable-length unsigned enumeration type.
    */
    const VariableLengthUnsignedEnumerationType& asVariableLengthUnsignedEnumerationType() const noexcept;

    /*!
    @brief
        Returns this type as a null-terminated string type.

    @pre
        This type is a null-terminated string type.
    */
    const NullTerminatedStringType& asNullTerminatedStringType() const noexcept;

    /*!
    @brief
        Returns this type as an array type.

    @pre
        This type is an array type.
    */
    const ArrayType& asArrayType() const noexcept;

    /*!
    @brief
        Returns this type as a static-length array type.

    @pre
        This type is a static-length array type.
    */
    const StaticLengthArrayType& asStaticLengthArrayType() const noexcept;

    /*!
    @brief
        Returns this type as a dynamic-length array type.

    @pre
        This type is a dynamic-length array type.
    */
    const DynamicLengthArrayType& asDynamicLengthArrayType() const noexcept;

    /*!
    @brief
        Returns this type as a non null-terminated string type.

    @pre
        This type is a non null-terminated string type.
    */
    const NonNullTerminatedStringType& asNonNullTerminatedStringType() const noexcept;

    /*!
    @brief
        Returns this type as a static-length string type.

    @pre
        This type is a static-length string type.
    */
    const StaticLengthStringType& asStaticLengthStringType() const noexcept;

    /*!
    @brief
        Returns this type as a dynamic-length string type.

    @pre
        This type is a dynamic-length string type.
    */
    const DynamicLengthStringType& asDynamicLengthStringType() const noexcept;

    /*!
    @brief
        Returns this type as a BLOB type.

    @pre
        This type is a BLOB type.
    */
    const BlobType& asBlobType() const noexcept;

    /*!
    @brief
        Returns this type as a static-length BLOB type.

    @pre
        This type is a static-length BLOB type.
    */
    const StaticLengthBlobType& asStaticLengthBlobType() const noexcept;

    /*!
    @brief
        Returns this type as a dynamic-length BLOB type.

    @pre
        This type is a dynamic-length BLOB type.
    */
    const DynamicLengthBlobType& asDynamicLengthBlobType() const noexcept;

    /*!
    @brief
        Returns this type as a structure type.

    @pre
        This type is a structure type.
    */
    const StructureType& asStructureType() const noexcept;

    /*!
    @brief
        Returns this type as the type of data stream variants with an
        unsigned integer selector.

    @pre
        This type is the type of data stream variants with an unsigned
        integer selector.
    */
    const VariantWithUnsignedIntegerSelectorType& asVariantWithUnsignedIntegerSelectorType() const noexcept;

    /*!
    @brief
        Returns this type as the type of data stream variants with a
        signed integer selector.

    @pre
        This type is the type of data stream variants with a signed
        integer selector.
    */
    const VariantWithSignedIntegerSelectorType& asVariantWithSignedIntegerSelectorType() const noexcept;

    /*!
    @brief
        Returns this type as an optional type.

    @pre
        This type is an optional type.
    */
    const OptionalType& asOptionalType() const noexcept;

    /*!
    @brief
        Returns this type as the type of data stream optionals with a
        boolean selector.

    @pre
        This type is the type of data stream optionals with a boolean
        selector.
    */
    const OptionalWithBooleanSelectorType& asOptionalWithBooleanSelectorType() const noexcept;

    /*!
    @brief
        Returns this type as the type of data stream optionals with an
        integer unsigned selector.

    @pre
        This type is the type of data stream optionals with an unsigned
        integer selector.
    */
    const OptionalWithUnsignedIntegerSelectorType& asOptionalWithUnsignedIntegerSelectorType() const noexcept;

    /*!
    @brief
        Returns this type as the type of data stream optionals with a
        signed integer selector.

    @pre
        This type is the type of data stream optionals with a signed
        integer selector.
    */
    const OptionalWithSignedIntegerSelectorType& asOptionalWithSignedIntegerSelectorType() const noexcept;

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
        Creates and returns a clone (deep copy) of this type.

    @returns
        Clone (deep copy) of this type.
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
    virtual bool _isEqual(const DataType& other) const noexcept = 0;

    _Kind _kind() const noexcept
    {
        return _theKind;
    }

private:
    bool _isKind(const _Kind kind) const noexcept
    {
        return (_theKind & kind) == kind;
    }

private:
    const _Kind _theKind;
    unsigned int _align;
    const MapItem::UP _userAttrs;
};

/*!
@brief
    Data type set.

@ingroup metadata_dt
*/
using DataTypeSet = std::unordered_set<const DataType *>;

} // namespace yactfr

#endif // _YACTFR_METADATA_DT_HPP
