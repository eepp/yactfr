/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_METADATA_DT_HPP
#define YACTFR_METADATA_DT_HPP

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
    using Up = std::unique_ptr<const DataType>;

protected:
    // kind of data type
    enum _tKind
    {
        _kindScalar     = 1 << 1,
        _kindBitArray   = (1 << 2) | _kindScalar,
        _kindS          = (1 << 3) | _kindScalar,
        _kindU          = (1 << 4) | _kindScalar,
        _kindFl         = (1 << 5) | _kindScalar,
        _kindInt        = (1 << 6) | _kindBitArray,
        _kindUInt       = _kindU | _kindInt,
        _kindSInt       = _kindS | _kindInt,
        _kindFlBitArray = _kindFl | _kindBitArray,
        _kindFlBitMap   = (1 << 7) | _kindFlBitArray,
        _kindFlBool     = (1 << 8) | _kindFlBitArray,
        _kindFlInt      = _kindFlBitArray | _kindInt,
        _kindFlSInt     = _kindFlInt | _kindSInt,
        _kindFlUInt     = _kindFlInt | _kindUInt,
        _kindFlFloat    = (1 << 9) | _kindFlBitArray,
        _kindVl         = (1 << 10) | _kindScalar,
        _kindVlBitArray = _kindVl | _kindBitArray,
        _kindVlInt      = _kindVlBitArray | _kindInt,
        _kindVlSInt     = _kindVlInt | _kindSInt,
        _kindVlUInt     = _kindVlInt | _kindUInt,
        _kindStr        = (1 << 11) | _kindScalar,
        _kindNtStr      = (1 << 12) | _kindStr,
        _kindCompound   = 1 << 13,
        _kindStruct     = (1 << 14) | _kindCompound,
        _kindArray      = (1 << 15) | _kindCompound,
        _kindSl         = 1 << 16,
        _kindDl         = 1 << 17,
        _kindSlArray    = _kindSl | _kindArray,
        _kindDlArray    = _kindDl | _kindArray,
        _kindNonNtStr   = (1 << 18) | _kindStr,
        _kindSlStr      = _kindSl | _kindNonNtStr,
        _kindDlStr      = _kindDl | _kindNonNtStr,
        _kindBlob       = (1 << 19) | _kindScalar,
        _kindSlBlob     = _kindSl | _kindBlob,
        _kindDlBlob     = _kindDl | _kindBlob,
        _kindVar        = (1 << 20) | _kindCompound,
        _kindUIntSel    = 1 << 21,
        _kindSIntSel    = 1 << 22,
        _kindBoolSel    = 1 << 23,
        _kindVarUIntSel = _kindVar | _kindUIntSel,
        _kindVarSIntSel = _kindVar | _kindSIntSel,
        _kindOpt        = (1 << 24) | _kindCompound,
        _kindOptUIntSel = _kindOpt | _kindUIntSel,
        _kindOptSIntSel = _kindOpt | _kindSIntSel,
        _kindOptIntSel  = _kindOptUIntSel | _kindOptSIntSel,
        _kindOptBoolSel = _kindOpt | _kindBoolSel,
    };

protected:
    explicit DataType(_tKind kind, unsigned int align, MapItem::Up attrs);

public:
    virtual ~DataType() = default;

    /// Alignment of the first data stream bit described by this type.
    unsigned int alignment() const noexcept
    {
        return _align;
    }

    /*!
    @brief
        Attributes.

    If set, each key of the returned map item is a namespace.

    @note
        Even if the return value isn't \c nullptr, the returned map
        item may still be empty (which also means no attributes).
    */
    const MapItem *attributes() const noexcept
    {
        return _attrs.get();
    }

    /// \c true if this type is a bit array type.
    bool isBitArrayType() const noexcept
    {
        return this->_isKind(_kindBitArray);
    }

    /// \c true if this type is an integer type.
    bool isIntegerType() const noexcept
    {
        return this->_isKind(_kindInt);
    }

    /// \c true if this type is a signed integer type.
    bool isSignedIntegerType() const noexcept
    {
        return this->_isKind(_kindSInt);
    }

    /// \c true if this type is an unsigned integer type.
    bool isUnsignedIntegerType() const noexcept
    {
        return this->_isKind(_kindUInt);
    }

    /// \c true if this type is a fixed-length bit array type.
    bool isFixedLengthBitArrayType() const noexcept
    {
        return this->_isKind(_kindFlBitArray);
    }

    /// \c true if this type is a fixed-length bit map type.
    bool isFixedLengthBitMapType() const noexcept
    {
        return this->_isKind(_kindFlBitMap);
    }

    /// \c true if this type is a fixed-length boolean type.
    bool isFixedLengthBooleanType() const noexcept
    {
        return this->_isKind(_kindFlBool);
    }

    /// \c true if this type is a fixed-length integer type.
    bool isFixedLengthIntegerType() const noexcept
    {
        return this->_isKind(_kindFlInt);
    }

    /// \c true if this type is a fixed-length signed integer type.
    bool isFixedLengthSignedIntegerType() const noexcept
    {
        return this->_isKind(_kindFlSInt);
    }

    /// \c true if this type is a fixed-length unsigned integer type.
    bool isFixedLengthUnsignedIntegerType() const noexcept
    {
        return this->_isKind(_kindFlUInt);
    }

    /*!
    @brief
        \c true if this type is a fixed-length floating point number
        type.
    */
    bool isFixedLengthFloatingPointNumberType() const noexcept
    {
        return this->_isKind(_kindFlFloat);
    }

    /// \c true if this type is a variable-length integer type.
    bool isVariableLengthIntegerType() const noexcept
    {
        return this->_isKind(_kindVlInt);
    }

    /// \c true if this type is a variable-length signed integer type.
    bool isVariableLengthSignedIntegerType() const noexcept
    {
        return this->_isKind(_kindVlSInt);
    }

    /// \c true if this type is a variable-length unsigned integer type.
    bool isVariableLengthUnsignedIntegerType() const noexcept
    {
        return this->_isKind(_kindVlUInt);
    }

    /// \c true if this type is a string type.
    bool isStringType() const noexcept
    {
        return this->_isKind(_kindStr);
    }

    /// \c true if this type is a null-terminated string type.
    bool isNullTerminatedStringType() const noexcept
    {
        return this->_isKind(_kindNtStr);
    }

    /// \c true if this type is an array type.
    bool isArrayType() const noexcept
    {
        return this->_isKind(_kindArray);
    }

    /// \c true if this type is a static-length array type.
    bool isStaticLengthArrayType() const noexcept
    {
        return this->_isKind(_kindSlArray);
    }

    /// \c true if this type is a dynamic-length array type.
    bool isDynamicLengthArrayType() const noexcept
    {
        return this->_isKind(_kindDlArray);
    }

    /*!
    @brief
        \c true if this type is a string type which is not a
        null-terminated string type.
    */
    bool isNonNullTerminatedStringType() const noexcept
    {
        return this->_isKind(_kindNonNtStr);
    }

    /// \c true if this type is a static-length string type.
    bool isStaticLengthStringType() const noexcept
    {
        return this->_isKind(_kindSlStr);
    }

    /// \c true if this type is a dynamic-length string type.
    bool isDynamicLengthStringType() const noexcept
    {
        return this->_isKind(_kindDlStr);
    }

    /// \c true if this type is a BLOB type.
    bool isBlobType() const noexcept
    {
        return this->_isKind(_kindBlob);
    }

    /// \c true if this type is a static-length BLOB type.
    bool isStaticLengthBlobType() const noexcept
    {
        return this->_isKind(_kindSlBlob);
    }

    /// \c true if this type is a dynamic-length BLOB type.
    bool isDynamicLengthBlobType() const noexcept
    {
        return this->_isKind(_kindDlBlob);
    }

    /// \c true if this type is a structure type.
    bool isStructureType() const noexcept
    {
        return this->_isKind(_kindStruct);
    }

    /// \c true if this type is a variant type.
    bool isVariantType() const noexcept
    {
        return this->_isKind(_kindVar);
    }

    /*!
    @brief
        \c true if this type is the type of data stream variants with an
        unsigned integer selector.
    */
    bool isVariantWithUnsignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_kindVarUIntSel);
    }

    /*!
    @brief
        \c true if this type is the type of data stream variants with a
        signed integer selector.
    */
    bool isVariantWithSignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_kindVarSIntSel);
    }

    /// \c true if this type is a optional type.
    bool isOptionalType() const noexcept
    {
        return this->_isKind(_kindOpt);
    }

    /*!
    @brief
        \c true if this type is the type of data stream optionals with
        a boolean selector.
    */
    bool isOptionalWithBooleanSelectorType() const noexcept
    {
        return this->_isKind(_kindOptBoolSel);
    }

    /*!
    @brief
        \c true if this type is the type of data stream optionals with
        an integer selector.
    */
    bool isOptionalWithIntegerSelectorType() const noexcept
    {
        return this->_isKind(_kindOptIntSel);
    }

    /*!
    @brief
        \c true if this type is the type of data stream optionals with
        an unsigned integer selector.
    */
    bool isOptionalWithUnsignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_kindOptUIntSel);
    }

    /*!
    @brief
        \c true if this type is the type of data stream optionals with a
        signed integer selector.
    */
    bool isOptionalWithSignedIntegerSelectorType() const noexcept
    {
        return this->_isKind(_kindOptSIntSel);
    }

    /*!
    @brief
        \c true if this type is a scalar type (doesn't contains another
        data type).
    */
    bool isScalarDataType() const noexcept
    {
        return this->_isKind(_kindScalar);
    }

    /*!
    @brief
        \c true if this type is a compound type (contains another data
        type).
    */
    bool isCompoundDataType() const noexcept
    {
        return this->_isKind(_kindCompound);
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
        Returns this type as a fixed-length bit map type.

    @pre
        This type is a fixed-length bit map type.
    */
    const FixedLengthBitMapType& asFixedLengthBitMapType() const noexcept;

    /*!
    @brief
        Returns this type as a fixed-length boolean type.

    @pre
        This type is a fixed-length boolean type.
    */
    const FixedLengthBooleanType& asFixedLengthBooleanType() const noexcept;

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
        Returns this type as a string type.

    @pre
        This type is a string type.
    */
    const StringType& asStringType() const noexcept;

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
        Returns this type as a variant type.

    @pre
        This type is a variant type.
    */
    const VariantType& asVariantType() const noexcept;

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
    DataType::Up clone() const;

    /*!
    @brief
        Accepts \p visitor to visit this type.

    @param[in] visitor
        Data type visitor to accept.
    */
    void accept(DataTypeVisitor& visitor) const;

protected:
    virtual DataType::Up _clone() const = 0;
    virtual void _accept(DataTypeVisitor& visitor) const = 0;
    virtual bool _isEqual(const DataType& other) const noexcept = 0;

    _tKind _kind() const noexcept
    {
        return _theKind;
    }

private:
    bool _isKind(const _tKind kind) const noexcept
    {
        return (_theKind & kind) == kind;
    }

private:
    const _tKind _theKind;
    unsigned int _align;
    const MapItem::Up _attrs;
};

/*!
@brief
    Data type set.

@ingroup metadata_dt
*/
using DataTypeSet = std::unordered_set<const DataType *>;

} // namespace yactfr

#endif // YACTFR_METADATA_DT_HPP
