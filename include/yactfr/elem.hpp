/*
 * Copyright (C) 2016-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_ELEM_HPP
#define YACTFR_ELEM_HPP

#include <cstdint>
#include <string>
#include <unordered_set>
#include <boost/uuid/uuid.hpp>
#include <boost/optional/optional.hpp>

#include "metadata/fwd.hpp"
#include "metadata/dt.hpp"
#include "metadata/fl-bit-array-type.hpp"
#include "metadata/fl-bit-map-type.hpp"
#include "metadata/fl-bool-type.hpp"
#include "metadata/fl-float-type.hpp"
#include "metadata/fl-int-type.hpp"
#include "metadata/vl-int-type.hpp"
#include "metadata/sl-array-type.hpp"
#include "metadata/dl-array-type.hpp"
#include "metadata/sl-str-type.hpp"
#include "metadata/dl-str-type.hpp"
#include "metadata/sl-blob-type.hpp"
#include "metadata/dl-blob-type.hpp"
#include "metadata/var-type.hpp"
#include "metadata/opt-type.hpp"
#include "elem-visitor.hpp"
#include "aliases.hpp"

namespace yactfr {
namespace internal {

class Vm;
class VmPos;

} // namespace internal

/*!
@defgroup elems Elements
@brief
    Elements.
@ingroup element_seq
*/

/*!
@brief
    Value of an
    \link ElementSequenceIterator element sequence iterator\endlink.

@ingroup elems
*/
class Element
{
private:
    enum _tKind
    {
        _kindEnd                = 1 << 0,
        _kindBeg                = 1 << 1,
        _kindPkt                = 1 << 2,
        _kindScope              = 1 << 3,
        _kindPktContent         = 1 << 4,
        _kindEr                 = 1 << 5,
        _kindPktMagicNumber     = 1 << 6,
        _kindMetadataStreamUuid = 1 << 7,
        _kindDs                 = 1 << 8,
        _kindINFO               = 1 << 9,
        _kindDefClkVal          = 1 << 10,
        _kindFlBitArray         = 1 << 11,
        _kindBitMapData         = 1 << 12,
        _kindBoolData           = 1 << 13,
        _kindIntData            = 1 << 14,
        _kindSigned             = 1 << 15,
        _kindUnsigned           = 1 << 16,
        _kindFloatData          = 1 << 17,
        _kindVlInt              = _kindIntData | (1 << 19),
        _kindNtStr              = 1 << 20,
        _kindRawData            = 1 << 21,
        _kindStruct             = 1 << 22,
        _kindSlData             = 1 << 23,
        _kindDlData             = 1 << 24,
        _kindArray              = 1 << 25,
        _kindNonNtStr           = 1 << 26,
        _kindBlob               = 1 << 27,
        _kindVar                = 1 << 28,
        _kindIntSel             = 1 << 29,
        _kindBoolSel            = 1 << 30,
        _kindOpt                = 1 << 31,
    };

    using _tU = unsigned long long;

public:
    /// %Kind of element.
    enum class Kind : _tU
    {
        /// PacketBeginningElement
        PacketBeginning                             = static_cast<_tU>(_kindPkt | _kindBeg),

        /// PacketEndElement
        PacketEnd                                   = static_cast<_tU>(_kindPkt | _kindEnd),

        /// ScopeBeginningElement
        ScopeBeginning                              = static_cast<_tU>(_kindScope | _kindBeg),

        /// ScopeEndElement
        ScopeEnd                                    = static_cast<_tU>(_kindScope | _kindEnd),

        /// PacketContentBeginningElement
        PacketContentBeginning                      = static_cast<_tU>(_kindPktContent | _kindBeg),

        /// PacketContentEndElement
        PacketContentEnd                            = static_cast<_tU>(_kindPktContent | _kindEnd),

        /// EventRecordBeginningElement
        EventRecordBeginning                        = static_cast<_tU>(_kindEr | _kindBeg),

        /// EventRecordEndElement
        EventRecordEnd                              = static_cast<_tU>(_kindEr | _kindEnd),

        /// PacketMagicNumberElement
        PacketMagicNumber                           = static_cast<_tU>(_kindPktMagicNumber),

        /// MetadataStreamUuidElement
        MetadataStreamUuid                          = static_cast<_tU>(_kindMetadataStreamUuid),

        /// DataStreamInfoElement
        DataStreamInfo                              = static_cast<_tU>(_kindDs | _kindINFO),

        /// DefaultClockValueElement
        DefaultClockValue                           = static_cast<_tU>(_kindDefClkVal),

        /// PacketInfoElement
        PacketInfo                                  = static_cast<_tU>(_kindPkt | _kindINFO),

        /// EventRecordInfoElement
        EventRecordInfo                             = static_cast<_tU>(_kindEr | _kindINFO),

        /// FixedLengthBitArrayElement
        FixedLengthBitArray                         = static_cast<_tU>(_kindFlBitArray),

        /// FixedLengthBitMapElement
        FixedLengthBitMap                           = static_cast<_tU>(_kindFlBitArray | _kindBitMapData),

        /// FixedLengthBooleanElement
        FixedLengthBoolean                          = static_cast<_tU>(_kindFlBitArray | _kindBoolData),

        /// FixedLengthSignedIntegerElement
        FixedLengthSignedInteger                    = static_cast<_tU>(_kindFlBitArray | _kindIntData | _kindSigned),

        /// FixedLengthUnsignedIntegerElement
        FixedLengthUnsignedInteger                  = static_cast<_tU>(_kindFlBitArray | _kindIntData | _kindUnsigned),

        /// FixedLengthFloatingPointNumberElement
        FixedLengthFloatingPointNumber              = static_cast<_tU>(_kindFlBitArray | _kindFloatData),

        /// VariableLengthSignedIntegerElement
        VariableLengthSignedInteger                 = static_cast<_tU>(_kindVlInt | _kindSigned),

        /// VariableLengthUnsignedIntegerElement
        VariableLengthUnsignedInteger               = static_cast<_tU>(_kindVlInt | _kindUnsigned),

        /// NullTerminatedStringBeginningElement
        NullTerminatedStringBeginning               = static_cast<_tU>(_kindNtStr | _kindBeg),

        /// NullTerminatedStringEndElement
        NullTerminatedStringEnd                     = static_cast<_tU>(_kindNtStr | _kindEnd),

        /// RawDataElement
        RawData                                     = static_cast<_tU>(_kindRawData),

        /// StructureBeginningElement
        StructureBeginning                          = static_cast<_tU>(_kindStruct | _kindBeg),

        /// StructureEndElement
        StructureEnd                                = static_cast<_tU>(_kindStruct | _kindEnd),

        /// StaticLengthArrayBeginningElement
        StaticLengthArrayBeginning                  = static_cast<_tU>(_kindSlData | _kindArray | _kindBeg),

        /// StaticLengthArrayEndElement
        StaticLengthArrayEnd                        = static_cast<_tU>(_kindSlData | _kindArray | _kindEnd),

        /// DynamicLengthArrayBeginningElement
        DynamicLengthArrayBeginning                 = static_cast<_tU>(_kindDlData | _kindArray | _kindBeg),

        /// DynamicLengthArrayEndElement
        DynamicLengthArrayEnd                       = static_cast<_tU>(_kindDlData | _kindArray | _kindEnd),

        /// StaticLengthBlobBeginningElement
        StaticLengthBlobBeginning                   = static_cast<_tU>(_kindSlData | _kindBlob | _kindBeg),

        /// StaticLengthBlobEndElement
        StaticLengthBlobEnd                         = static_cast<_tU>(_kindSlData | _kindBlob | _kindEnd),

        /// DynamicLengthBlobBeginningElement
        DynamicLengthBlobBeginning                  = static_cast<_tU>(_kindDlData | _kindBlob | _kindBeg),

        /// DynamicLengthBlobEndElement
        DynamicLengthBlobEnd                        = static_cast<_tU>(_kindDlData | _kindBlob | _kindEnd),

        /// StaticLengthStringBeginningElement
        StaticLengthStringBeginning                 = static_cast<_tU>(_kindSlData | _kindNonNtStr | _kindBeg),

        /// StaticLengthStringEndElement
        StaticLengthStringEnd                       = static_cast<_tU>(_kindSlData | _kindNonNtStr | _kindEnd),

        /// DynamicLengthStringBeginningElement
        DynamicLengthStringBeginning                = static_cast<_tU>(_kindDlData | _kindNonNtStr | _kindBeg),

        /// DynamicLengthStringEndElement
        DynamicLengthStringEnd                      = static_cast<_tU>(_kindDlData | _kindNonNtStr | _kindEnd),

        /// VariantWithSignedIntegerSelectorBeginningElement
        VariantWithSignedIntegerSelectorBeginning   = static_cast<_tU>(_kindVar | _kindSigned | _kindBeg),

        /// VariantWithSignedIntegerSelectorEndElement
        VariantWithSignedIntegerSelectorEnd         = static_cast<_tU>(_kindVar | _kindSigned | _kindEnd),

        /// VariantWithUnsignedIntegerSelectorBeginningElement
        VariantWithUnsignedIntegerSelectorBeginning = static_cast<_tU>(_kindVar | _kindUnsigned | _kindBeg),

        /// VariantWithUnsignedIntegerSelectorEndElement
        VariantWithUnsignedIntegerSelectorEnd       = static_cast<_tU>(_kindVar | _kindUnsigned | _kindEnd),

        /// OptionalWithBooleanSelectorBeginningElement
        OptionalWithBooleanSelectorBeginning        = static_cast<_tU>(_kindOpt | _kindBoolSel | _kindBeg),

        /// OptionalWithBooleanSelectorEndElement
        OptionalWithBooleanSelectorEnd              = static_cast<_tU>(_kindOpt | _kindBoolSel | _kindEnd),

        /// OptionalWithSignedIntegerSelectorBeginningElement
        OptionalWithSignedIntegerSelectorBeginning  = static_cast<_tU>(_kindOpt | _kindIntSel | _kindSigned | _kindBeg),

        /// OptionalWithSignedIntegerSelectorEndElement
        OptionalWithSignedIntegerSelectorEnd        = static_cast<_tU>(_kindOpt | _kindIntSel | _kindSigned | _kindEnd),

        /// OptionalWithUnsignedIntegerSelectorBeginningElement
        OptionalWithUnsignedIntegerSelectorBeginning= static_cast<_tU>(_kindOpt | _kindIntSel | _kindUnsigned | _kindBeg),

        /// OptionalWithUnsignedIntegerSelectorEndElement
        OptionalWithUnsignedIntegerSelectorEnd      = static_cast<_tU>(_kindOpt | _kindIntSel | _kindUnsigned | _kindEnd),
    };

protected:
    explicit Element(const Kind kind) :
        _kind {kind}
    {
    }

public:
    /*!
    @brief
        %Kind of this element.

    You can also use accept() with an \link ElementVisitor element
    visitor\endlink to get access to the concrete element.

    @returns
        %Kind of this element.
    */
    Kind kind() const noexcept
    {
        return _kind;
    }

    /*!
    @brief
        Accepts \p visitor to visit this element.

    @param[in] visitor
        Visitor to accept.
    */
    virtual void accept(ElementVisitor& visitor) const = 0;

    /// \c true if this element is a beginning element.
    bool isBeginningElement() const noexcept
    {
        return this->_isKind(_kindBeg);
    }

    /// \c true if this element is an end element.
    bool isEndElement() const noexcept
    {
        return this->_isKind(_kindEnd);
    }

    /// \c true if this element is a packet beginning/end element.
    bool isPacketElement() const noexcept
    {
        return this->_isKind(_kindPkt);
    }

    /// \c true if this element is a packet beginning element.
    bool isPacketBeginningElement() const noexcept
    {
        return _kind == Kind::PacketBeginning;
    }

    /// \c true if this element is a packet end element.
    bool isPacketEndElement() const noexcept
    {
        return _kind == Kind::PacketEnd;
    }

    /// \c true if this element is a scope beginning/end element.
    bool isScopeElement() const noexcept
    {
        return this->_isKind(_kindScope);
    }

    /// \c true if this element is a scope beginning element.
    bool isScopeBeginningElement() const noexcept
    {
        return _kind == Kind::ScopeBeginning;
    }

    /// \c true if this element is a scope end element.
    bool isScopeEndElement() const noexcept
    {
        return _kind == Kind::ScopeEnd;
    }

    /// \c true if this element is a packet content beginning/end element.
    bool isPacketContentElement() const noexcept
    {
        return this->_isKind(_kindPktContent);
    }

    /// \c true if this element is a packet content beginning element.
    bool isPacketContentBeginningElement() const noexcept
    {
        return _kind == Kind::PacketContentBeginning;
    }

    /// \c true if this element is a packet content end element.
    bool isPacketContentEndElement() const noexcept
    {
        return _kind == Kind::PacketContentEnd;
    }

    /// \c true if this element is an event record beginning/end element.
    bool isEventRecordElement() const noexcept
    {
        return this->_isKind(_kindEr);
    }

    /// \c true if this element is an event record beginning element.
    bool isEventRecordBeginningElement() const noexcept
    {
        return _kind == Kind::EventRecordBeginning;
    }

    /// \c true if this element is an event record end element.
    bool isEventRecordEndElement() const noexcept
    {
        return _kind == Kind::EventRecordEnd;
    }

    /// \c true if this element is a packet magic number element.
    bool isPacketMagicNumberElement() const noexcept
    {
        return _kind == Kind::PacketMagicNumber;
    }

    /// \c true if this element is a metadata stream UUID element.
    bool isMetadataStreamUuidElement() const noexcept
    {
        return _kind == Kind::MetadataStreamUuid;
    }

    /// \c true if this element is a data stream info element.
    bool isDataStreamInfoElement() const noexcept
    {
        return _kind == Kind::DataStreamInfo;
    }

    /// \c true if this element is a default clock value element.
    bool isDefaultClockValueElement() const noexcept
    {
        return _kind == Kind::DefaultClockValue;
    }

    /// \c true if this element is an info element.
    bool isInfoElement() const noexcept
    {
        return this->_isKind(_kindINFO);
    }

    /// \c true if this element is a packet info element.
    bool isPacketInfoElement() const noexcept
    {
        return _kind == Kind::PacketInfo;
    }

    /// \c true if this element is an event record info element.
    bool isEventRecordInfoElement() const noexcept
    {
        return _kind == Kind::EventRecordInfo;
    }

    /// \c true if this element is a fixed-length bit array element.
    bool isFixedLengthBitArrayElement() const noexcept
    {
        return this->_isKind(_kindFlBitArray);
    }

    /// \c true if this element is a fixed-length bit map element.
    bool isFixedLengthBitMapElement() const noexcept
    {
        return _kind == Kind::FixedLengthBitMap;
    }

    /// \c true if this element is a fixed-length boolean element.
    bool isFixedLengthBooleanElement() const noexcept
    {
        return _kind == Kind::FixedLengthBoolean;
    }

    /// \c true if this element is an integer element.
    bool isIntegerElement() const noexcept
    {
        return this->_isKind(_kindIntData);
    }

    /// \c true if this element is a fixed-length integer element.
    bool isFixedLengthIntegerElement() const noexcept
    {
        return this->_isKind(_kindFlBitArray | _kindIntData);
    }

    /// \c true if this element is a signed integer element.
    bool isSignedIntegerElement() const noexcept
    {
        return this->_isKind(_kindIntData | _kindSigned);
    }

    /// \c true if this element is an unsigned integer element.
    bool isUnsignedIntegerElement() const noexcept
    {
        return this->_isKind(_kindIntData | _kindUnsigned);
    }

    /// \c true if this element is a fixed-length signed integer element.
    bool isFixedLengthSignedIntegerElement() const noexcept
    {
        return this->_isKind(_kindFlBitArray | _kindIntData | _kindSigned);
    }

    /// \c true if this element is a fixed-length unsigned integer element.
    bool isFixedLengthUnsignedIntegerElement() const noexcept
    {
        return this->_isKind(_kindFlBitArray | _kindIntData | _kindUnsigned);
    }

    /// \c true if this element is a fixed-length floating-point number element.
    bool isFixedLengthFloatingPointNumberElement() const noexcept
    {
        return _kind == Kind::FixedLengthFloatingPointNumber;
    }

    /// \c true if this element is a variable-length integer element.
    bool isVariableLengthIntegerElement() const noexcept
    {
        return this->_isKind(_kindVlInt);
    }

    /// \c true if this element is a variable-length signed integer element.
    bool isVariableLengthSignedIntegerElement() const noexcept
    {
        return this->_isKind(_kindVlInt | _kindSigned);
    }

    /// \c true if this element is a variable-length unsigned integer element.
    bool isVariableLengthUnsignedIntegerElement() const noexcept
    {
        return this->_isKind(_kindVlInt | _kindUnsigned);
    }

    /// \c true if this element is a null-terminated string beginning/end element.
    bool isNullTerminatedStringElement() const noexcept
    {
        return this->_isKind(_kindNtStr);
    }

    /// \c true if this element is a null-terminated string beginning element.
    bool isNullTerminatedStringBeginningElement() const noexcept
    {
        return _kind == Kind::NullTerminatedStringBeginning;
    }

    /// \c true if this element is a null-terminated string end element.
    bool isNullTerminatedStringEndElement() const noexcept
    {
        return _kind == Kind::NullTerminatedStringEnd;
    }

    /// \c true if this element is a raw data element.
    bool isRawDataElement() const noexcept
    {
        return _kind == Kind::RawData;
    }

    /// \c true if this element is a structure beginning/end element.
    bool isStructureElement() const noexcept
    {
        return this->_isKind(_kindStruct);
    }

    /// \c true if this element is a structure beginning element.
    bool isStructureBeginningElement() const noexcept
    {
        return _kind == Kind::StructureBeginning;
    }

    /// \c true if this element is a structure end element.
    bool isStructureEndElement() const noexcept
    {
        return _kind == Kind::StructureEnd;
    }

    /// \c true if this element is an array beginning/end element.
    bool isArrayElement() const noexcept
    {
        return this->_isKind(_kindArray);
    }

    /// \c true if this element is a static-length array beginning/end element.
    bool isStaticLengthArrayElement() const noexcept
    {
        return this->_isKind(_kindSlData | _kindArray);
    }

    /// \c true if this element is a static-length array beginning element.
    bool isStaticLengthArrayBeginningElement() const noexcept
    {
        return _kind == Kind::StaticLengthArrayBeginning;
    }

    /// \c true if this element is a static-length array end element.
    bool isStaticLengthArrayEndElement() const noexcept
    {
        return _kind == Kind::StaticLengthArrayEnd;
    }

    /// \c true if this element is a dynamic-length array beginning/end element.
    bool isDynamicLengthArrayElement() const noexcept
    {
        return this->_isKind(_kindDlData | _kindArray);
    }

    /// \c true if this element is a dynamic-length array beginning element.
    bool isDynamicLengthArrayBeginningElement() const noexcept
    {
        return _kind == Kind::DynamicLengthArrayBeginning;
    }

    /// \c true if this element is a dynamic-length array end element.
    bool isDynamicLengthArrayEndElement() const noexcept
    {
        return _kind == Kind::DynamicLengthArrayEnd;
    }

    /// \c true if this element is a BLOB beginning/end element.
    bool isBlobElement() const noexcept
    {
        return this->_isKind(_kindBlob);
    }

    /// \c true if this element is a static-length BLOB beginning/end element.
    bool isStaticLengthBlobElement() const noexcept
    {
        return this->_isKind(_kindSlData | _kindBlob);
    }

    /// \c true if this element is a static-length BLOB beginning element.
    bool isStaticLengthBlobBeginningElement() const noexcept
    {
        return _kind == Kind::StaticLengthBlobBeginning;
    }

    /// \c true if this element is a static-length BLOB end element.
    bool isStaticLengthBlobEndElement() const noexcept
    {
        return _kind == Kind::StaticLengthBlobEnd;
    }

    /// \c true if this element is a dynamic-length BLOB beginning/end element.
    bool isDynamicLengthBlobElement() const noexcept
    {
        return this->_isKind(_kindDlData | _kindBlob);
    }

    /// \c true if this element is a dynamic-length BLOB beginning element.
    bool isDynamicLengthBlobBeginningElement() const noexcept
    {
        return _kind == Kind::DynamicLengthBlobBeginning;
    }

    /// \c true if this element is a dynamic-length BLOB end element.
    bool isDynamicLengthBlobEndElement() const noexcept
    {
        return _kind == Kind::DynamicLengthBlobEnd;
    }

    /// \c true if this element is a non-null-terminated string beginning/end element.
    bool isNonNullTerminatedStringElement() const noexcept
    {
        return this->_isKind(_kindNonNtStr);
    }

    /// \c true if this element is a static-length string beginning/end element.
    bool isStaticLengthStringElement() const noexcept
    {
        return this->_isKind(_kindSlData | _kindNonNtStr);
    }

    /// \c true if this element is a static-length string beginning element.
    bool isStaticLengthStringBeginningElement() const noexcept
    {
        return _kind == Kind::StaticLengthStringBeginning;
    }

    /// \c true if this element is a static-length string end element.
    bool isStaticLengthStringEndElement() const noexcept
    {
        return _kind == Kind::StaticLengthStringEnd;
    }

    /// \c true if this element is a dynamic-length string beginning/end element.
    bool isDynamicLengthStringElement() const noexcept
    {
        return this->_isKind(_kindDlData | _kindNonNtStr);
    }

    /// \c true if this element is a dynamic-length string beginning element.
    bool isDynamicLengthStringBeginningElement() const noexcept
    {
        return _kind == Kind::DynamicLengthStringBeginning;
    }

    /// \c true if this element is a dynamic-length string end element.
    bool isDynamicLengthStringEndElement() const noexcept
    {
        return _kind == Kind::DynamicLengthStringEnd;
    }

    /// \c true if this element is a variant beginning/end element.
    bool isVariantElement() const noexcept
    {
        return this->_isKind(_kindVar);
    }

    /// \c true if this element is a variant beginning element.
    bool isVariantBeginningElement() const noexcept
    {
        return this->_isKind(_kindVar | _kindBeg);
    }

    /// \c true if this element is a variant end element.
    bool isVariantEndElement() const noexcept
    {
        return this->_isKind(_kindVar | _kindEnd);
    }

    /// \c true if this element is a variant with a signed integer selector beginning/end element.
    bool isVariantWithSignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_kindVar | _kindSigned);
    }

    /// \c true if this element is a variant with a signed integer selector beginning element.
    bool isVariantWithSignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::VariantWithSignedIntegerSelectorBeginning;
    }

    /// \c true if this element is a variant with a signed integer selector end element.
    bool isVariantWithSignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::VariantWithSignedIntegerSelectorEnd;
    }

    /// \c true if this element is a variant with an unsigned integer selector beginning/end element.
    bool isVariantWithUnsignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_kindVar | _kindUnsigned);
    }

    /// \c true if this element is a variant with an unsigned integer selector beginning element.
    bool isVariantWithUnsignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::VariantWithUnsignedIntegerSelectorBeginning;
    }

    /// \c true if this element is a variant with an unsigned integer selector end element.
    bool isVariantWithUnsignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::VariantWithUnsignedIntegerSelectorEnd;
    }

    /// \c true if this element is an optional beginning/end element.
    bool isOptionalElement() const noexcept
    {
        return this->_isKind(_kindOpt);
    }

    /// \c true if this element is an optional beginning element.
    bool isOptionalBeginningElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindBeg);
    }

    /// \c true if this element is an optional end element.
    bool isOptionalEndElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindEnd);
    }

    /// \c true if this element is an optional with a boolean selector beginning/end element.
    bool isOptionalWithBooleanSelectorElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindBoolSel);
    }

    /// \c true if this element is an optional with a boolean selector beginning element.
    bool isOptionalWithBooleanSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::OptionalWithBooleanSelectorBeginning;
    }

    /// \c true if this element is an optional with a boolean selector end element.
    bool isOptionalWithBooleanSelectorEndElement() const noexcept
    {
        return _kind == Kind::OptionalWithBooleanSelectorEnd;
    }

    /// \c true if this element is an optional with an integer selector beginning/end element.
    bool isOptionalWithIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindSigned | _kindUnsigned);
    }

    /// \c true if this element is an optional with an integer selector beginning element.
    bool isOptionalWithIntegerSelectorBeginningElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindSigned | _kindUnsigned | _kindBeg);
    }

    /// \c true if this element is an optional with an integer selector end element.
    bool isOptionalWithIntegerSelectorEndElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindSigned | _kindUnsigned | _kindEnd);
    }

    /// \c true if this element is an optional with a signed integer selector beginning/end element.
    bool isOptionalWithSignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindSigned);
    }

    /// \c true if this element is an optional with a signed integer selector beginning element.
    bool isOptionalWithSignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::OptionalWithSignedIntegerSelectorBeginning;
    }

    /// \c true if this element is an optional with a signed integer selector end element.
    bool isOptionalWithSignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::OptionalWithSignedIntegerSelectorEnd;
    }

    /// \c true if this element is an optional with an unsigned integer selector beginning/end element.
    bool isOptionalWithUnsignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_kindOpt | _kindUnsigned);
    }

    /// \c true if this element is an optional with an unsigned integer selector beginning element.
    bool isOptionalWithUnsignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::OptionalWithUnsignedIntegerSelectorBeginning;
    }

    /// \c true if this element is an optional with an unsigned integer selector end element.
    bool isOptionalWithUnsignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::OptionalWithUnsignedIntegerSelectorEnd;
    }

    /*!
    @brief
        Returns this element as a data stream info element.

    @pre
        This type is a data stream info element.
    */
    const DataStreamInfoElement& asDataStreamInfoElement() const noexcept;

    /*!
    @brief
        Returns this element as a default clock value element.

    @pre
        This type is a default clock value element.
    */
    const DefaultClockValueElement& asDefaultClockValueElement() const noexcept;

    /*!
    @brief
        Returns this element as a dynamic-length array beginning
        element.

    @pre
        This type is a dynamic-length array beginning element.
    */
    const DynamicLengthArrayBeginningElement& asDynamicLengthArrayBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a dynamic-length array end element.

    @pre
        This type is a dynamic-length array end element.
    */
    const DynamicLengthArrayEndElement& asDynamicLengthArrayEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a dynamic-length BLOB beginning element.

    @pre
        This type is a dynamic-length BLOB beginning element.
    */
    const DynamicLengthBlobBeginningElement& asDynamicLengthBlobBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a dynamic-length BLOB end element.

    @pre
        This type is a dynamic-length BLOB end element.
    */
    const DynamicLengthBlobEndElement& asDynamicLengthBlobEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a dynamic-length string beginning
        element.

    @pre
        This type is a dynamic-length string beginning element.
    */
    const DynamicLengthStringBeginningElement& asDynamicLengthStringBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a dynamic-length string end element.

    @pre
        This type is a dynamic-length string end element.
    */
    const DynamicLengthStringEndElement& asDynamicLengthStringEndElement() const noexcept;

    /*!
    @brief
        Returns this element as an event record beginning element.

    @pre
        This type is an event record beginning element.
    */
    const EventRecordBeginningElement& asEventRecordBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as an event record end element.

    @pre
        This type is an event record end element.
    */
    const EventRecordEndElement& asEventRecordEndElement() const noexcept;

    /*!
    @brief
        Returns this element as an event record info element.

    @pre
        This type is an event record info element.
    */
    const EventRecordInfoElement& asEventRecordInfoElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length bit array element.

    @pre
        This type is a fixed-length bit array element.
    */
    const FixedLengthBitArrayElement& asFixedLengthBitArrayElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length bit map element.

    @pre
        This type is a fixed-length bit map element.
    */
    const FixedLengthBitMapElement& asFixedLengthBitMapElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length boolean element.

    @pre
        This type is a fixed-length boolean element.
    */
    const FixedLengthBooleanElement& asFixedLengthBooleanElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length floating-point number
        element.

    @pre
        This type is a fixed-length floating-point number element.
    */
    const FixedLengthFloatingPointNumberElement& asFixedLengthFloatingPointNumberElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length signed integer element.

    @pre
        This type is a fixed-length signed integer element.
    */
    const FixedLengthSignedIntegerElement& asFixedLengthSignedIntegerElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length unsigned integer element.

    @pre
        This type is a fixed-length unsigned integer element.
    */
    const FixedLengthUnsignedIntegerElement& asFixedLengthUnsignedIntegerElement() const noexcept;

    /*!
    @brief
        Returns this element as a null-terminated string beginning
        element.

    @pre
        This type is a null-terminated string beginning element.
    */
    const NullTerminatedStringBeginningElement& asNullTerminatedStringBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a null-terminated string end element.

    @pre
        This type is a null-terminated string end element.
    */
    const NullTerminatedStringEndElement& asNullTerminatedStringEndElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional beginning element.

    @pre
        This type is an optional beginning element.
    */
    const OptionalBeginningElement& asOptionalBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional end element.

    @pre
        This type is an optional end element.
    */
    const OptionalEndElement& asOptionalEndElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional with a boolean selector
        beginning element.

    @pre
        This type is an optional with a boolean selector beginning
        element.
    */
    const OptionalWithBooleanSelectorBeginningElement& asOptionalWithBooleanSelectorBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional with a boolean selector end
        element.

    @pre
        This type is an optional with a boolean selector end element.
    */
    const OptionalWithBooleanSelectorEndElement& asOptionalWithBooleanSelectorEndElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional with a signed integer
        selector beginning element.

    @pre
        This type is an optional with a signed integer selector
        beginning element.
    */
    const OptionalWithSignedIntegerSelectorBeginningElement& asOptionalWithSignedIntegerSelectorBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional with a signed integer
        selector end element.

    @pre
        This type is an optional with a signed integer selector end
        element.
    */
    const OptionalWithSignedIntegerSelectorEndElement& asOptionalWithSignedIntegerSelectorEndElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional with an unsigned integer
        selector beginning element.

    @pre
        This type is an optional with an unsigned integer selector
        beginning element.
    */
    const OptionalWithUnsignedIntegerSelectorBeginningElement& asOptionalWithUnsignedIntegerSelectorBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as an optional with an unsigned integer
        selector end element.

    @pre
        This type is an optional with an unsigned integer selector end
        element.
    */
    const OptionalWithUnsignedIntegerSelectorEndElement& asOptionalWithUnsignedIntegerSelectorEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a packet beginning element.

    @pre
        This type is a packet beginning element.
    */
    const PacketBeginningElement& asPacketBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a packet content beginning element.

    @pre
        This type is a packet content beginning element.
    */
    const PacketContentBeginningElement& asPacketContentBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a packet content end element.

    @pre
        This type is a packet content end element.
    */
    const PacketContentEndElement& asPacketContentEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a packet end element.

    @pre
        This type is a packet end element.
    */
    const PacketEndElement& asPacketEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a packet info element.

    @pre
        This type is a packet info element.
    */
    const PacketInfoElement& asPacketInfoElement() const noexcept;

    /*!
    @brief
        Returns this element as a packet magic number element.

    @pre
        This type is a packet magic number element.
    */
    const PacketMagicNumberElement& asPacketMagicNumberElement() const noexcept;

    /*!
    @brief
        Returns this element as a scope beginning element.

    @pre
        This type is a scope beginning element.
    */
    const ScopeBeginningElement& asScopeBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a scope end element.

    @pre
        This type is a scope end element.
    */
    const ScopeEndElement& asScopeEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a static-length array beginning element.

    @pre
        This type is a static-length array beginning element.
    */
    const StaticLengthArrayBeginningElement& asStaticLengthArrayBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a static-length array end element.

    @pre
        This type is a static-length array end element.
    */
    const StaticLengthArrayEndElement& asStaticLengthArrayEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a static-length BLOB beginning element.

    @pre
        This type is a static-length BLOB beginning element.
    */
    const StaticLengthBlobBeginningElement& asStaticLengthBlobBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a static-length BLOB end element.

    @pre
        This type is a static-length BLOB end element.
    */
    const StaticLengthBlobEndElement& asStaticLengthBlobEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a static-length string beginning
        element.

    @pre
        This type is a static-length string beginning element.
    */
    const StaticLengthStringBeginningElement& asStaticLengthStringBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a static-length string end element.

    @pre
        This type is a static-length string end element.
    */
    const StaticLengthStringEndElement& asStaticLengthStringEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a structure beginning element.

    @pre
        This type is a structure beginning element.
    */
    const StructureBeginningElement& asStructureBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a structure end element.

    @pre
        This type is a structure end element.
    */
    const StructureEndElement& asStructureEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a raw data element.

    @pre
        This type is a raw data element.
    */
    const RawDataElement& asRawDataElement() const noexcept;

    /*!
    @brief
        Returns this element as a metadata stream UUID element.

    @pre
        This type is a metadata stream UUID element.
    */
    const MetadataStreamUuidElement& asMetadataStreamUuidElement() const noexcept;

    /*!
    @brief
        Returns this element as a variable-length signed integer
        element.

    @pre
        This type is a variable-length signed integer element.
    */
    const VariableLengthSignedIntegerElement& asVariableLengthSignedIntegerElement() const noexcept;

    /*!
    @brief
        Returns this element as a variable-length unsigned integer
        element.

    @pre
        This type is a variable-length unsigned integer element.
    */
    const VariableLengthUnsignedIntegerElement& asVariableLengthUnsignedIntegerElement() const noexcept;

    /*!
    @brief
        Returns this element as a variant beginning element.

    @pre
        This type is a variant beginning element.
    */
    const VariantBeginningElement& asVariantBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a variant end element.

    @pre
        This type is a variant end element.
    */
    const VariantEndElement& asVariantEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a variant with a signed integer selector
        beginning element.

    @pre
        This type is a variant with a signed integer selector beginning
        element.
    */
    const VariantWithSignedIntegerSelectorBeginningElement& asVariantWithSignedIntegerSelectorBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a variant with a signed integer selector
        end element.

    @pre
        This type is a variant with a signed integer selector end
        element.
    */
    const VariantWithSignedIntegerSelectorEndElement& asVariantWithSignedIntegerSelectorEndElement() const noexcept;

    /*!
    @brief
        Returns this element as a variant with an unsigned integer
        selector beginning element.

    @pre
        This type is a variant with an unsigned integer selector
        beginning element.
    */
    const VariantWithUnsignedIntegerSelectorBeginningElement& asVariantWithUnsignedIntegerSelectorBeginningElement() const noexcept;

    /*!
    @brief
        Returns this element as a variant with an unsigned integer
        selector end element.

    @pre
        This type is a variant with an unsigned integer selector end
        element.
    */
    const VariantWithUnsignedIntegerSelectorEndElement& asVariantWithUnsignedIntegerSelectorEndElement() const noexcept;

private:
    bool _isKind(const unsigned long long kind) const noexcept
    {
        return (static_cast<unsigned long long>(_kind) & kind) == kind;
    }

private:
    Kind _kind;
};

/*!
@brief
    Beginning base element.

@ingroup elems

@sa EndElement
*/
class BeginningElement :
    public Element
{
protected:
    explicit BeginningElement(const Kind kind) :
        Element {kind}
    {
    }
};

/*!
@brief
    End element.

@ingroup elems

@sa BeginningElement
*/
class EndElement :
    public Element
{
protected:
    explicit EndElement(const Kind kind) :
        Element {kind}
    {
    }
};

/*!
@brief
    Packet beginning element.

@ingroup elems

@sa PacketEndElement
*/
class PacketBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketBeginningElement() :
        BeginningElement {Kind::PacketBeginning}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Packet end element.

@ingroup elems

@sa PacketBeginningElement
*/
class PacketEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketEndElement() :
        EndElement {Kind::PacketEnd}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Scope element.

@ingroup elems

@sa ScopeBeginningElement
@sa ScopeEndElement
*/
class ScopeElement
{
protected:
    explicit ScopeElement() = default;

public:
    /// Scope.
    Scope scope() const noexcept
    {
        return _scope;
    }

protected:
    Scope _scope;
};

/*!
@brief
    Scope beginning element.

@ingroup elems

@sa ScopeEndElement
*/
class ScopeBeginningElement final :
    public BeginningElement,
    public ScopeElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit ScopeBeginningElement() :
        BeginningElement {Kind::ScopeBeginning}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Scope end element.

@ingroup elems

@sa ScopeBeginningElement
*/
class ScopeEndElement final :
    public EndElement,
    public ScopeElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit ScopeEndElement() :
        EndElement {Kind::ScopeEnd}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Event record beginning element.

@ingroup elems

@sa EventRecordEndElement
*/
class EventRecordBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit EventRecordBeginningElement() :
        BeginningElement {Kind::EventRecordBeginning}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Event record end element.

@ingroup elems

@sa EventRecordBeginningElement
*/
class EventRecordEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit EventRecordEndElement() :
        EndElement {Kind::EventRecordEnd}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Packet content beginning element.

@ingroup elems

This element indicates the beginning of the \em content of the current
packet.

All the elements between this one and the following
PacketContentEndElement within a given element sequence are part of the
packet content, which does \em not include the optional padding bits
before the end of the packet (indicated by the next PacketEndElement).

@sa PacketContentEndElement
*/
class PacketContentBeginningElement final :
    public BeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketContentBeginningElement() :
        BeginningElement {Kind::PacketContentBeginning}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Packet content end element.

@ingroup elems

This element indicates the end of the \em content of the current packet.

@sa PacketContentBeginningElement
*/
class PacketContentEndElement final :
    public EndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketContentEndElement() :
        EndElement {Kind::PacketContentEnd}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Packet magic number element.

@ingroup elems

This element contains the magic number of the decoded packet as well as
the expected magic number (always 0xc1fc1fc1).

Call isValid() to get whether or not the decoded magic number is valid
as per the specification.
*/
class PacketMagicNumberElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketMagicNumberElement() :
        Element {Kind::PacketMagicNumber}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /// \c true if the decoded magic number is valid.
    bool isValid() const noexcept
    {
        return _val == this->expectedValue();
    }

    /// Decoded magic number value.
    unsigned long long value() const noexcept
    {
        return _val;
    }

    /// Expected magic number value.
    static constexpr unsigned long long expectedValue() noexcept
    {
        return 0xc1fc1fc1;
    }

private:
    unsigned long long _val = 0;
};

/*!
@brief
    Metadata stream UUID element.

@ingroup elems

This element contains the decoded metadata stream UUID.
*/
class MetadataStreamUuidElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit MetadataStreamUuidElement() : //-V730
        Element {Kind::MetadataStreamUuid}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /// Decoded UUID.
    const boost::uuids::uuid& uuid() const noexcept
    {
        return _uuid;
    }

private:
    boost::uuids::uuid _uuid;
};

/*!
@brief
    Data stream information element.

@ingroup elems

This element contains information about the current data stream, as
found in the header of the current packet.
*/
class DataStreamInfoElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DataStreamInfoElement() :
        Element {Kind::DataStreamInfo}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /*!
    @brief
        Type of the data stream of the current packet, or \c nullptr if
        the trace type has no data stream types.
    */
    const DataStreamType *type() const noexcept
    {
        return _dst;
    }

    /*!
    @brief
        ID of the data stream of the current packet.

    @note
        Not to be confused with the \em type ID of the data stream of
        the current packet: use type() and then DataStreamType::id().
    */
    const boost::optional<unsigned long long>& id() const noexcept
    {
        return _id;
    }

private:
    void _reset() noexcept
    {
        _dst = nullptr;
        _id = boost::none;
    }

private:
    const DataStreamType *_dst = nullptr;
    boost::optional<unsigned long long> _id;
};

/*!
@brief
    Default clock value element.

@ingroup elems

This element provides the value of the default clock of the data stream
of the current packet.
*/
class DefaultClockValueElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DefaultClockValueElement() :
        Element {Kind::DefaultClockValue}
    {
    }

public:
    /// Value of the clock (cycles).
    Cycles cycles() const noexcept
    {
        return _cycles;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    Cycles _cycles = 0;
};

/*!
@brief
    Packet information element.

@ingroup elems

This element contains information about the current packet, as found in
its context.

As per the CTF rules:

- <strong>If expectedTotalLength() and expectedContentLength() are both
  not set</strong>: the total and content lengths of this packet are the
  length of the current data stream (this packet is the only one within
  its data stream).

- <strong>If expectedTotalLength() is set, but expectedContentLength()
  isn't</strong>: the expected content length of this packet is its
  expected total length (value of expectedTotalLength()).

- <strong>If expectedContentLength() is set, but expectedTotalLength()
  isn't</strong>: the expected total length of this packet is its
  expected content length (value of expectedContentLength()).
*/
class PacketInfoElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit PacketInfoElement() :
        Element {Kind::PacketInfo}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /*!
    @brief
        Numeric sequence number of the current packet
        within its <em>data stream</em> (\em not within its element
        sequence).
    */
    const boost::optional<Index>& sequenceNumber() const noexcept
    {
        return _seqNum;
    }

    /*!
    @brief
        Count of total discarded event records at the end of the current
        packet since the beginning of its <em>data stream</em> (\em not
        its element sequence).
    */
    const boost::optional<Size>& discardedEventRecordCounterSnapshot() const noexcept
    {
        return _discErCounterSnap;
    }

    /*!
    @brief
        Expected total length, in bits, of the current packet.

    This length \em includes the packet padding bits before the end of
    the packet, if any.
    */
    const boost::optional<Size>& expectedTotalLength() const noexcept
    {
        return _expectedTotalLen;
    }

    /*!
    @brief
        Expected content length, in bits, of the current packet.

    This length \em excludes the packet padding bits before the end of
    the packet, if any: the total length of the packet minus its content
    length provides its padding length.
    */
    const boost::optional<Size>& expectedContentLength() const noexcept
    {
        return _expectedContentLen;
    }

    /*!
    @brief
        Value of the default clock of the data stream of the current
        packet at its end.

    During the packet decoding process, this default clock value is
    known \em before decoding the event records.

    @sa DefaultClockValueElement
    */
    const boost::optional<Cycles>& endDefaultClockValue() const noexcept
    {
        return _endDefClkVal;
    }

private:
    void _reset() noexcept
    {
        _seqNum = boost::none;
        _discErCounterSnap = boost::none;
        _expectedTotalLen = boost::none;
        _expectedContentLen = boost::none;
        _endDefClkVal = boost::none;
    }

private:
    boost::optional<Index> _seqNum;
    boost::optional<Size> _discErCounterSnap;
    boost::optional<Size> _expectedTotalLen;
    boost::optional<Size> _expectedContentLen;
    boost::optional<Cycles> _endDefClkVal;
};

/*!
@brief
    Event record information element.

@ingroup elems

This element contains information about the current event record, as
found in its header.
*/
class EventRecordInfoElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit EventRecordInfoElement() :
        Element {Kind::EventRecordInfo}
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /*!
    @brief
        Type of the current event record, or \c nullptr if the data
        stream type has no event record types.
    */
    const EventRecordType *type() const noexcept
    {
        return _ert;
    }

private:
    void _reset() noexcept
    {
        _ert = nullptr;
    }

private:
    const EventRecordType *_ert = nullptr;
};

/*!
@brief
    Data base element.

@ingroup elems
*/
class DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit DataElement() = default;

public:
    /*!
    @brief
        Type of the immediate structure member containing this element,
        or \c nullptr if none (scope).
    */
    const StructureMemberType *structureMemberType() const noexcept
    {
        return _structMemberType;
    }

    /// Data type.
    const DataType& dataType() const noexcept
    {
        return *_dt;
    }

private:
    const StructureMemberType *_structMemberType;
    const DataType *_dt;
};

/*
 * Number element mixin.
 */
class NumberElement :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

public:
    explicit NumberElement(const Kind kind) : //-V730
        Element {kind}
    {
    }

private:
    void _val(const std::uint64_t val) noexcept
    {
        _theVal.u = val;
    }

    void _val(const std::int64_t val) noexcept
    {
        _theVal.i = val;
    }

    void _val(const double val) noexcept
    {
        _theVal.d = val;
    }

protected:
    union {
        unsigned long long u;
        long long i;
        double d;
    } _theVal;
};

/*!
@brief
    Fixed-length bit array element.

@ingroup elems
*/
class FixedLengthBitArrayElement :
    public NumberElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthBitArrayElement(const Kind kind) : //-V730
        NumberElement {kind}
    {
    }

private:
    explicit FixedLengthBitArrayElement() :
        FixedLengthBitArrayElement {Kind::FixedLengthBitArray}
    {
    }

public:
    /// Fixed-length bit array type.
    const FixedLengthBitArrayType& type() const noexcept
    {
        return this->dataType().asFixedLengthBitArrayType();
    }

    /*!
    @brief
        Whole array value as an unsigned integer.

    The LSB of the returned integral value is the value of the first
    element (bit) of the array.
    */
    unsigned long long unsignedIntegerValue() const noexcept
    {
        return _theVal.u;
    }

    /*!
    @brief
        Returns the value of the element (bit) at the index \p index.

    @param[in] index
        Index of the element (bit) to return.

    @returns
        Element (bit)it at the index \p index.

    @pre
        \p index < <code>type().length()</code>
    */
    bool operator[](const Index index) const noexcept
    {
        assert(index < this->type().length());
        return static_cast<bool>((_theVal.u >> index) & 1);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length bit map element.

@ingroup elems
*/
class FixedLengthBitMapElement final :
    public FixedLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthBitMapElement() :
        FixedLengthBitArrayElement {Kind::FixedLengthBitMap}
    {
    }

public:
    /// Fixed-length bit map type.
    const FixedLengthBitMapType& type() const noexcept
    {
        return this->dataType().asFixedLengthBitMapType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    /*!
    @brief
        Adds to \p names the names of the active flags for the active
        bits of this element.

    @param[out] names
        @parblock
        Set of the names of active flags for this element.

        The pointed strings remain valid as long as what type() returns
        exists.
        @endparblock
    */
    void activeFlagNames(std::unordered_set<const std::string *>& names) const
    {
        this->type().activeFlagNamesForUnsignedIntegerValue(this->unsignedIntegerValue(), names);
    }
};

/*!
@brief
    Fixed-length boolean element.

@ingroup elems
*/
class FixedLengthBooleanElement final :
    public FixedLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthBooleanElement() :
        FixedLengthBitArrayElement {Kind::FixedLengthBoolean}
    {
    }

public:
    /// Fixed-length boolean type.
    const FixedLengthBooleanType& type() const noexcept
    {
        return this->dataType().asFixedLengthBooleanType();
    }

    /// Boolean value.
    bool value() const noexcept
    {
        return static_cast<bool>(_theVal.u);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Common integer element (mixin).

@ingroup elems
*/
template <typename ElemT>
class IntegerElement
{
protected:
    IntegerElement() = default;

public:
    /*!
    @brief
        Adds to \p names the names of the mappings for value of this
        element.

    @param[out] names
        @parblock
        Set of the names of mappings for the value of this element.

        The pointed strings remain valid as long as the integer type of
        this element exists.
        @endparblock
    */
    void mappingNames(std::unordered_set<const std::string *>& names) const
    {
        auto& elem = static_cast<const ElemT&>(*this);

        elem.type().mappingNamesForValue(elem.value(), names);
    }
};

/*!
@brief
    Fixed-length signed integer element.

@ingroup elems
*/
class FixedLengthSignedIntegerElement final :
    public FixedLengthBitArrayElement,
    public IntegerElement<FixedLengthSignedIntegerElement>
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthSignedIntegerElement(const Kind kind) :
        FixedLengthBitArrayElement {kind}
    {
    }

private:
    explicit FixedLengthSignedIntegerElement() :
        FixedLengthSignedIntegerElement {Kind::FixedLengthSignedInteger}
    {
    }

public:
    /// Fixed-length signed integer type.
    const FixedLengthSignedIntegerType& type() const noexcept
    {
        return this->dataType().asFixedLengthSignedIntegerType();
    }

    /// Integral value.
    long long value() const noexcept
    {
        return static_cast<long long>(_theVal.i);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length unsigned integer element.

@ingroup elems
*/
class FixedLengthUnsignedIntegerElement final :
    public FixedLengthBitArrayElement,
    public IntegerElement<FixedLengthUnsignedIntegerElement>
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit FixedLengthUnsignedIntegerElement(const Kind kind) :
        FixedLengthBitArrayElement {kind}
    {
    }

private:
    explicit FixedLengthUnsignedIntegerElement() :
        FixedLengthUnsignedIntegerElement {Kind::FixedLengthUnsignedInteger}
    {
    }

public:
    /// Fixed-length unsigned integer type.
    const FixedLengthUnsignedIntegerType& type() const noexcept
    {
        return this->dataType().asFixedLengthUnsignedIntegerType();
    }

    /// Integral value.
    unsigned long long value() const noexcept
    {
        return static_cast<unsigned long long>(_theVal.u);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length floating point number element.

@ingroup elems
*/
class FixedLengthFloatingPointNumberElement final :
    public FixedLengthBitArrayElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthFloatingPointNumberElement() :
        FixedLengthBitArrayElement {Kind::FixedLengthFloatingPointNumber}
    {
    }

public:
    /// Fixed-length floating point number type.
    const FixedLengthFloatingPointNumberType& type() const noexcept
    {
        return this->dataType().asFixedLengthFloatingPointNumberType();
    }

    /// Real value.
    double value() const noexcept
    {
        return _theVal.d;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variable-length integer element.

@ingroup elems
*/
class VariableLengthIntegerElement :
    public NumberElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariableLengthIntegerElement(const Kind kind) :
        NumberElement {kind}
    {
    }

public:
    /*!
    @brief
        Bit-array length (bits).

    This is the length of the decoded integer itself (excluding
    continuation bits), not of the data stream variable-length integer
    datum (use dataLength()).
    */
    Size length() const noexcept
    {
        return _len;
    }

    /*!
    @brief
        Data length (bits).

    This is the length of the data stream variable-length integer datum
    (including continuation bits), not of the decoded integer (use
    length()).
    */
    Size dataLength() const noexcept
    {
        return ((_len + 6) / 7) * 8;
    }

private:
    Size _len = 0;
};

/*!
@brief
    Variable-length signed integer element.

@ingroup elems
*/
class VariableLengthSignedIntegerElement final :
    public VariableLengthIntegerElement,
    public IntegerElement<VariableLengthSignedIntegerElement>
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariableLengthSignedIntegerElement(const Kind kind) :
        VariableLengthIntegerElement {kind}
    {
    }

private:
    explicit VariableLengthSignedIntegerElement() :
        VariableLengthSignedIntegerElement {Kind::VariableLengthSignedInteger}
    {
    }

public:
    /// Variable-length signed integer type.
    const VariableLengthSignedIntegerType& type() const noexcept
    {
        return this->dataType().asVariableLengthSignedIntegerType();
    }

    /// Integral value.
    long long value() const noexcept
    {
        return static_cast<long long>(_theVal.i);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variable-length unsigned integer element.

@ingroup elems
*/
class VariableLengthUnsignedIntegerElement final :
    public VariableLengthIntegerElement,
    public IntegerElement<VariableLengthUnsignedIntegerElement>
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariableLengthUnsignedIntegerElement(const Kind kind) :
        VariableLengthIntegerElement {kind}
    {
    }

private:
    explicit VariableLengthUnsignedIntegerElement() :
        VariableLengthUnsignedIntegerElement {Kind::VariableLengthUnsignedInteger}
    {
    }

public:
    /// Variable-length unsigned integer type.
    const VariableLengthUnsignedIntegerType& type() const noexcept
    {
        return this->dataType().asVariableLengthUnsignedIntegerType();
    }

    /// Integral value.
    unsigned long long value() const noexcept
    {
        return static_cast<unsigned long long>(_theVal.u);
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Null-terminated string beginning element.

@ingroup elems

This element indicates the beginning of a data stream null-terminated
string.

The next RawDataElement elements before the next
NullTerminatedStringEndElement are consecutive parts of this beginning
null-terminated string.

@sa RawDataElement
@sa NullTerminatedStringEndElement
*/
class NullTerminatedStringBeginningElement final :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit NullTerminatedStringBeginningElement() :
        BeginningElement {Kind::NullTerminatedStringBeginning}
    {
    }

public:
    /// Null-terminated string type.
    const NullTerminatedStringType& type() const noexcept
    {
        return this->dataType().asNullTerminatedStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Null-terminated string end element.

@ingroup elems

This element indicates the end of a data stream null-terminated string.

@sa NullTerminatedStringBeginningElement
*/
class NullTerminatedStringEndElement final :
    public EndElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit NullTerminatedStringEndElement() :
        EndElement {Kind::NullTerminatedStringEnd}
    {
    }

public:
    /// Null-terminated string type.
    const NullTerminatedStringType& type() const noexcept
    {
        return this->dataType().asNullTerminatedStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Raw data element.

@ingroup elems

This element can occur zero or more times:

<dl>
  <dt>Data stream null-terminated string</dt>
  <dd>
    Between NullTerminatedStringBeginningElement and
    NullTerminatedStringEndElement elements.
  </dd>

  <dt>Data stream static-length string</dt>
  <dd>
    Between StaticLengthStringBeginningElement and
    StaticLengthStringEndElement elements.
  </dd>

  <dt>Data stream dynamic-length string</dt>
  <dd>
    Between DynamicLengthStringBeginningElement and
    DynamicLengthStringEndElement elements.
  </dd>

  <dt>Data stream static-length BLOB</dt>
  <dd>
    Between StaticLengthBlobBeginningElement and
    StaticLengthBlobEndElement elements.
  </dd>

  <dt>Data stream dynamic-length BLOB</dt>
  <dd>
    Between DynamicLengthBlobBeginningElement and
    DynamicLengthBlobEndElement elements.
  </dd>
</dl>

begin() points to the first byte of the raw data and end() points to
the byte \em after the last byte of the raw data. Use size() to compute
the size of the raw data \em in bytes.

The pointed raw data is actually part of a \link DataBlock data
block\endlink which the \link DataSource data source\endlink provided
(zero copy).

The concatenated data of all the raw data elements between a pair of
string/BLOB beginning and end elements forms:

<dl>
  <dt>For a string</dt>
  <dd>
    The actual encoded string.

    @note
        yactfr doesn't perform any string conversion: use the
        StringType::encoding() method of the string type of the last
        string beginning element to get the encoding of the concatenated
        encoded string parts.

    Considering the concatenated data \em D of all the raw data elements
    between a pair of string beginning and string end elements, \em D
    may contain an encoded U+0000 (null) codepoint. In that case, the
    actual encoded string finishes at this point, and excludes said
    encoded U+0000 codepoint. For static-length and dynamic-length
    strings, \em D may contain more garbage bytes after an encoded
    U+0000 codepoint. Such data is still part of the data stream, but
    not part of the encoded string.

    For example, consider the following bytes of <em>D</em> representing
    a CTF 23-byte static-length UTF-16LE string:

    @code
    68 00 65 00 6c 00 6c 00 6f 00 20 00 77 00 6f 00
    72 00 6c 00 64 00 20 00 3c d8 3b df 00 00 dd ff
    44 52 00 00 bd cc 4e
    @endcode

    The encoded string is "hello world 🌻" (everything before the first
    encoded U+0000 codepoint, which is two zero bytes in UTF-16) while
    the bytes

    @code
    00 00 dd ff 44 52 00 00 bd cc 4e
    @endcode

    are garbage bytes.
  </dd>

  <dt>For a BLOB</dt>
  <dd>
    The whole BLOB data.
  </dd>
</dl>
*/
class RawDataElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit RawDataElement() :
        Element {Kind::RawData}
    {
    }

public:
    /// Beginning of the data of this element.
    const std::uint8_t *begin() const noexcept
    {
        return _begin;
    }

    /*!
    @brief
        End of the data of this element (points to the byte \em after
        the last byte of the raw data).
    */
    const std::uint8_t *end() const noexcept
    {
        return _end;
    }

    /// Size of this raw data (bytes).
    Size size() const noexcept
    {
        return _end - _begin;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const std::uint8_t *_begin = nullptr;
    const std::uint8_t *_end = nullptr;
};

/*!
@brief
    Array beginning base element.

@ingroup elems

@sa ArrayEndElement
*/
class ArrayBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    ArrayBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Array type.
    const ArrayType& type() const noexcept
    {
        return this->dataType().asArrayType();
    }

    /// Array length.
    Size length() const noexcept
    {
        return _len;
    }

protected:
    Size _len = 0;
};

/*!
@brief
    Array end base element.

@ingroup elems

@sa ArrayBeginningElement
*/
class ArrayEndElement :
    public EndElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    ArrayEndElement(const Kind kind) :
        EndElement {kind}
    {
    }

public:
    /// Array type.
    const ArrayType& type() const noexcept
    {
        return this->dataType().asArrayType();
    }
};

/*!
@brief
    Static-length array beginning element.

@ingroup elems

This element indicates the beginning of a data stream static-length
array.

The next elements until the next StaticLengthArrayEndElement at the same
level are all part of this static-length array.

@sa StaticLengthArrayEndElement
*/
class StaticLengthArrayBeginningElement final :
    public ArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthArrayBeginningElement() :
        ArrayBeginningElement {Kind::StaticLengthArrayBeginning}
    {
    }

public:
    /// Static-length array type.
    const StaticLengthArrayType& type() const noexcept
    {
        return this->dataType().asStaticLengthArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Static-length array end element.

@ingroup elems

This element indicates the end of a data stream static-length array.

@sa StaticLengthArrayBeginningElement
*/
class StaticLengthArrayEndElement final :
    public ArrayEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthArrayEndElement() :
        ArrayEndElement {Kind::StaticLengthArrayEnd}
    {
    }

public:
    /// Static-length array type.
    const StaticLengthArrayType& type() const noexcept
    {
        return this->dataType().asStaticLengthArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length array beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic-length
array.

The next elements until the next DynamicLengthArrayEndElement at the
same level are all part of this dynamic-length array.

@sa DynamicLengthArrayEndElement
*/
class DynamicLengthArrayBeginningElement final :
    public ArrayBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthArrayBeginningElement() :
        ArrayBeginningElement {Kind::DynamicLengthArrayBeginning}
    {
    }

public:
    /// Dynamic-length array type.
    const DynamicLengthArrayType& type() const noexcept
    {
        return this->dataType().asDynamicLengthArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length array end element.

@ingroup elems

This element indicates the end of a data stream dynamic-length array.

@sa DynamicLengthArrayBeginningElement
*/
class DynamicLengthArrayEndElement final :
    public ArrayEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthArrayEndElement() :
        ArrayEndElement {Kind::DynamicLengthArrayEnd}
    {
    }

public:
    /// Dynamic-length array type.
    const DynamicLengthArrayType& type() const noexcept
    {
        return this->dataType().asDynamicLengthArrayType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Non null-terminated string beginning base element.

@ingroup elems

@sa NonNullTerminatedStringEndElement
*/
class NonNullTerminatedStringBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    NonNullTerminatedStringBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Non null-terminated string type.
    const NonNullTerminatedStringType& type() const noexcept
    {
        return this->dataType().asNonNullTerminatedStringType();
    }

    /// Maximum length (bytes).
    Size maximumLength() const noexcept
    {
        return _maxLen;
    }

protected:
    Size _maxLen = 0;
};

/*!
@brief
    Non null-terminated string end base element.

@ingroup elems

@sa NonNullTerminatedStringBeginningElement
*/
class NonNullTerminatedStringEndElement :
    public EndElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    NonNullTerminatedStringEndElement(const Kind kind) :
        EndElement {kind}
    {
    }

public:
    /// Non null-terminated string type.
    const NonNullTerminatedStringType& type() const noexcept
    {
        return this->dataType().asNonNullTerminatedStringType();
    }
};

/*!
@brief
    Static-length string beginning element.

@ingroup elems

This element indicates the beginning of a data stream static-length
string.

The next RawDataElement elements before the next
StaticLengthStringEndElement are consecutive parts of this
beginning static-length string.

@sa RawDataElement
@sa StaticLengthStringEndElement
*/
class StaticLengthStringBeginningElement final :
    public NonNullTerminatedStringBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthStringBeginningElement() :
        NonNullTerminatedStringBeginningElement {Kind::StaticLengthStringBeginning}
    {
    }

public:
    /// Static-length string type.
    const StaticLengthStringType& type() const noexcept
    {
        return this->dataType().asStaticLengthStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Static-length string end element.

@ingroup elems

This element indicates the end of a data stream static-length string.

@sa RawDataElement
@sa StaticLengthStringBeginningElement
*/
class StaticLengthStringEndElement final :
    public NonNullTerminatedStringEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthStringEndElement() :
        NonNullTerminatedStringEndElement {Kind::StaticLengthStringEnd}
    {
    }

public:
    /// Static-length string type.
    const StaticLengthStringType& type() const noexcept
    {
        return this->dataType().asStaticLengthStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length string beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic-length
string.

The next RawDataElement elements before the next
DynamicLengthStringEndElement are consecutive parts of this
beginning dynamic-length string.

@sa RawDataElement
@sa DynamicLengthStringEndElement
*/
class DynamicLengthStringBeginningElement final :
    public NonNullTerminatedStringBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthStringBeginningElement() :
        NonNullTerminatedStringBeginningElement {Kind::DynamicLengthStringBeginning}
    {
    }

public:
    /// Dynamic-length string type.
    const DynamicLengthStringType& type() const noexcept
    {
        return this->dataType().asDynamicLengthStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length string end element.

@ingroup elems

This element indicates the end of a data stream dynamic-length string.

@sa RawDataElement
@sa DynamicLengthStringBeginningElement
*/
class DynamicLengthStringEndElement final :
    public NonNullTerminatedStringEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthStringEndElement() :
        NonNullTerminatedStringEndElement {Kind::DynamicLengthStringEnd}
    {
    }

public:
    /// Dynamic-length string type.
    const DynamicLengthStringType& type() const noexcept
    {
        return this->dataType().asDynamicLengthStringType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    BLOB beginning base element.

@ingroup elems

@sa BlobEndElement
*/
class BlobBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    BlobBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// BLOB type.
    const BlobType& type() const noexcept
    {
        return this->dataType().asBlobType();
    }

    /// BLOB length (bytes).
    Size length() const noexcept
    {
        return _len;
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

protected:
    Size _len = 0;
};

/*!
@brief
    BLOB end base element.

@ingroup elems

@sa BlobBeginningElement
*/
class BlobEndElement :
    public EndElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    BlobEndElement(const Kind kind) :
        EndElement {kind}
    {
    }

public:
    /// BLOB type.
    const BlobType& type() const noexcept
    {
        return this->dataType().asBlobType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Static-length BLOB beginning element.

@ingroup elems

This element indicates the beginning of a data stream static-length
BLOB.

The next RawDataElement elements before the next
StaticLengthBlobEndElement are consecutive parts of this
beginning static-length BLOB.

@sa RawDataElement
@sa StaticLengthBlobEndElement
*/
class StaticLengthBlobBeginningElement final :
    public BlobBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthBlobBeginningElement() :
        BlobBeginningElement {Kind::StaticLengthBlobBeginning}
    {
    }

public:
    /// Static-length BLOB type.
    const StaticLengthBlobType& type() const noexcept
    {
        return this->dataType().asStaticLengthBlobType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Static-length BLOB end element.

@ingroup elems

This element indicates the end of a data stream static-length BLOB.

@sa RawDataElement
@sa StaticLengthBlobEndElement
*/
class StaticLengthBlobEndElement final :
    public BlobEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthBlobEndElement() :
        BlobEndElement {Kind::StaticLengthBlobEnd}
    {
    }

public:
    /// Static-length BLOB type.
    const StaticLengthBlobType& type() const noexcept
    {
        return this->dataType().asStaticLengthBlobType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length BLOB beginning element.

@ingroup elems

This element indicates the beginning of a data stream dynamic-length
BLOB.

The next RawDataElement elements before the next
DynamicLengthBlobEndElement are consecutive parts of this
beginning dynamic-length BLOB.

@sa RawDataElement
@sa DynamicLengthBlobEndElement
*/
class DynamicLengthBlobBeginningElement final :
    public BlobBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthBlobBeginningElement() :
        BlobBeginningElement {Kind::DynamicLengthBlobBeginning}
    {
    }

public:
    /// Dynamic-length BLOB type.
    const DynamicLengthBlobType& type() const noexcept
    {
        return this->dataType().asDynamicLengthBlobType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Dynamic-length BLOB end element.

@ingroup elems

This element indicates the end of a data stream dynamic-length BLOB.

@sa RawDataElement
@sa DynamicLengthBlobEndElement
*/
class DynamicLengthBlobEndElement final :
    public BlobEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthBlobEndElement() :
        BlobEndElement {Kind::DynamicLengthBlobEnd}
    {
    }

public:
    /// Dynamic-length BLOB type.
    const DynamicLengthBlobType& type() const noexcept
    {
        return this->dataType().asDynamicLengthBlobType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Structure beginning element.

@ingroup elems

This element indicates the beginning of a data stream structure.

The next elements until the next StructureEndElement at the same level
are all part of this structure.

@sa StructureEndElement
*/
class StructureBeginningElement final :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StructureBeginningElement() :
        BeginningElement {Kind::StructureBeginning}
    {
    }

public:
    /// Structure type.
    const StructureType& type() const noexcept
    {
        return this->dataType().asStructureType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Structure end element.

@ingroup elems

This element indicates the end of a data stream structure.

@sa StructureBeginningElement
*/
class StructureEndElement final :
    public EndElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StructureEndElement() :
        EndElement {Kind::StructureEnd}
    {
    }

public:
    /// Structure type.
    const StructureType& type() const noexcept
    {
        return this->dataType().asStructureType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Common variant beginning element.

@ingroup elems

@sa VariantWithUnsignedIntegerSelectorEndElement
@sa VariantWithSignedIntegerSelectorEndElement
@sa VariantEndElement
*/
class VariantBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    VariantBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Variant type.
    const VariantType& type() const noexcept
    {
        return this->dataType().asVariantType();
    }
};

/*!
@brief
    Common variant end element.

@ingroup elems

@sa VariantWithUnsignedIntegerSelectorBeginningElement
@sa VariantWithSignedIntegerSelectorBeginningElement
@sa VariantBeginningElement
*/
class VariantEndElement :
    public EndElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    VariantEndElement(const Kind kind) :
        EndElement {kind}
    {
    }
};

/*!
@brief
    Variant with integer selector beginning base element.

@ingroup elems

@sa VariantWithUnsignedIntegerSelectorEndElement
@sa VariantWithSignedIntegerSelectorEndElement
*/
template <typename VariantTypeT, typename SelectorValueT, Element::Kind KindV>
class VariantWithIntegerSelectorBeginningElement :
    public VariantBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariantWithIntegerSelectorBeginningElement() :
        VariantBeginningElement {KindV}
    {
    }

public:
    /// Variant type.
    const VariantTypeT& type() const noexcept
    {
        return static_cast<const VariantTypeT&>(this->dataType());
    }

    /// Value of the variant selector.
    SelectorValueT selectorValue() const noexcept
    {
        return _selVal;
    }

    /// Selected option of the variant type.
    const typename VariantTypeT::Option& typeOption() const noexcept
    {
        return *_opt;
    }

private:
    SelectorValueT _selVal = 0;
    const typename VariantTypeT::Option *_opt = nullptr;
};

/*!
@brief
    Variant with integer selector end base element.

@ingroup elems

@sa VariantWithUnsignedIntegerSelectorBeginningElement
@sa VariantWithSignedIntegerSelectorBeginningElement
*/
template <typename VariantTypeT, Element::Kind KindV>
class VariantWithIntegerSelectorEndElement :
    public VariantEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit VariantWithIntegerSelectorEndElement() :
        VariantEndElement {KindV}
    {
    }

public:
    /// Variant type.
    const VariantTypeT& type() const noexcept
    {
        return static_cast<const VariantTypeT&>(this->dataType());
    }
};

/*!
@brief
    Variant with unsigned integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream variant with an
unsigned integer selector.

The next element is the selected element of this variant. Expect an
VariantWithUnsignedIntegerSelectorEndElement after this next element at
the same level.

@sa VariantWithUnsignedIntegerSelectorEndElement
*/
class VariantWithUnsignedIntegerSelectorBeginningElement final :
    public VariantWithIntegerSelectorBeginningElement<VariantWithUnsignedIntegerSelectorType, unsigned long long,
                                                      Element::Kind::VariantWithUnsignedIntegerSelectorBeginning>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithUnsignedIntegerSelectorBeginningElement() = default;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variant with unsigned integer selector end element.

@ingroup elems

This element indicates the end of a data stream variant with an unsigned
integer selector.

@sa VariantWithUnsignedIntegerSelectorBeginningElement
*/
class VariantWithUnsignedIntegerSelectorEndElement final :
    public VariantWithIntegerSelectorEndElement<VariantWithUnsignedIntegerSelectorType,
                                                Element::Kind::VariantWithUnsignedIntegerSelectorEnd>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithUnsignedIntegerSelectorEndElement() = default;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variant with signed integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream variant with a
signed integer selector.

The next element is the selected element of this variant. Expect an
VariantWithSignedIntegerSelectorEndElement after this next element at
the same level.

@sa VariantWithSignedIntegerSelectorEndElement
*/
class VariantWithSignedIntegerSelectorBeginningElement final :
    public VariantWithIntegerSelectorBeginningElement<VariantWithSignedIntegerSelectorType, long long,
                                                      Element::Kind::VariantWithSignedIntegerSelectorBeginning>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithSignedIntegerSelectorBeginningElement() = default;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variant with signed integer selector end element.

@ingroup elems

This element indicates the end of a data stream variant with a signed
integer selector.

@sa VariantWithSignedIntegerSelectorBeginningElement
*/
class VariantWithSignedIntegerSelectorEndElement final :
    public VariantWithIntegerSelectorEndElement<VariantWithSignedIntegerSelectorType,
                                                Element::Kind::VariantWithSignedIntegerSelectorEnd>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariantWithSignedIntegerSelectorEndElement() = default;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Common optional beginning element.

@ingroup elems

@sa OptionalWithBooleanSelectorBeginningElement
@sa OptionalWithUnsignedIntegerSelectorBeginningElement
@sa OptionalWithSignedIntegerSelectorBeginningElement
@sa OptionalEndElement
*/
class OptionalBeginningElement :
    public BeginningElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    OptionalBeginningElement(const Kind kind) :
        BeginningElement {kind}
    {
    }

public:
    /// Optional type.
    const OptionalType& type() const noexcept
    {
        return this->dataType().asOptionalType();
    }

    /// Whether or not this optional is enabled (contains data).
    bool isEnabled() const noexcept
    {
        return _isEnabled;
    }

private:
    bool _isEnabled = false;
};

/*!
@brief
    Common optional end element.

@ingroup elems

@sa OptionalWithBooleanSelectorEndElement
@sa OptionalWithUnsignedIntegerSelectorEndElement
@sa OptionalWithSignedIntegerSelectorEndElement
@sa OptionalBeginningElement
*/
class OptionalEndElement :
    public EndElement,
    public DataElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    OptionalEndElement(const Kind kind) :
        EndElement {kind}
    {
    }

public:
    /// Optional type.
    const OptionalType& type() const noexcept
    {
        return this->dataType().asOptionalType();
    }
};

/*!
@brief
    Optional with boolean selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream optional with a
boolean selector.

The next element, if the isEnabled() returns \c true, is the contained
element of this optional. Expect an
OptionalWithBooleanSelectorEndElement after this at the same level.

@sa OptionalWithBooleanSelectorEndElement
*/
class OptionalWithBooleanSelectorBeginningElement final :
    public OptionalBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithBooleanSelectorBeginningElement() :
        OptionalBeginningElement {Element::Kind::OptionalWithBooleanSelectorBeginning}
    {
    }

public:
    /// Optional type.
    const OptionalWithBooleanSelectorType& type() const noexcept
    {
        return this->dataType().asOptionalWithBooleanSelectorType();
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Optional with boolean selector end element.

@ingroup elems

This element indicates the end of a data stream optional with a boolean
selector.

@sa OptionalWithBooleanSelectorBeginningElement
*/
class OptionalWithBooleanSelectorEndElement final :
    public OptionalEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithBooleanSelectorEndElement() :
        OptionalEndElement {Element::Kind::OptionalWithBooleanSelectorEnd}
    {
    }

public:
    /// Optional type.
    const OptionalWithBooleanSelectorType& type() const noexcept
    {
        return this->dataType().asOptionalWithBooleanSelectorType();
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Optional with integer selector beginning base element.

@ingroup elems

@sa OptionalWithUnsignedIntegerSelectorBeginningElement
@sa OptionalWithSignedIntegerSelectorBeginningElement
@sa OptionalWithIntegerSelectorEndElement
*/
template <typename OptionalTypeT, typename SelectorValueT, Element::Kind KindV>
class OptionalWithIntegerSelectorBeginningElement :
    public OptionalBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit OptionalWithIntegerSelectorBeginningElement() :
        OptionalBeginningElement {KindV}
    {
    }

public:
    /// Optional type.
    const OptionalTypeT& type() const noexcept
    {
        return static_cast<const OptionalTypeT&>(this->dataType());
    }

    /// Value of the optional selector.
    SelectorValueT selectorValue() const noexcept
    {
        return _selVal;
    }

private:
    SelectorValueT _selVal = 0;
};

/*!
@brief
    Optional with integer selector end base element.

@ingroup elems

@sa OptionalWithUnsignedIntegerSelectorEndElement
@sa OptionalWithSignedIntegerSelectorEndElement
@sa OptionalWithIntegerSelectorBeginningElement
*/
template <typename OptionalTypeT, Element::Kind KindV>
class OptionalWithIntegerSelectorEndElement :
    public OptionalEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

protected:
    explicit OptionalWithIntegerSelectorEndElement() :
        OptionalEndElement {KindV}
    {
    }

public:
    /// Optional type.
    const OptionalTypeT& type() const noexcept
    {
        return static_cast<const OptionalTypeT&>(this->dataType());
    }
};

/*!
@brief
    Optional with unsigned integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream optional with an
unsigned integer selector.

The next element, if the isEnabled() returns \c true, is the contained
element of this optional. Expect an
OptionalWithUnsignedIntegerSelectorEndElement after this at the same
level.

@sa OptionalWithUnsignedIntegerSelectorEndElement
*/
class OptionalWithUnsignedIntegerSelectorBeginningElement final :
    public OptionalWithIntegerSelectorBeginningElement<OptionalWithUnsignedIntegerSelectorType, unsigned long long,
                                                       Element::Kind::OptionalWithUnsignedIntegerSelectorBeginning>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithUnsignedIntegerSelectorBeginningElement() = default;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Optional with unsigned integer selector end element.

@ingroup elems

This element indicates the end of a data stream optional with an
unsigned integer selector.

@sa OptionalWithUnsignedIntegerSelectorBeginningElement
*/
class OptionalWithUnsignedIntegerSelectorEndElement final :
    public OptionalWithIntegerSelectorEndElement<OptionalWithUnsignedIntegerSelectorType,
                                                 Element::Kind::OptionalWithUnsignedIntegerSelectorEnd>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithUnsignedIntegerSelectorEndElement() = default;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Optional with signed integer selector beginning element.

@ingroup elems

This element indicates the beginning of a data stream optional with a
signed integer selector.

The next element, if the isEnabled() returns \c true, is the contained
element of this optional. Expect an
OptionalWithSignedIntegerSelectorEndElement after this at the same
level.

@sa OptionalWithSignedIntegerSelectorEndElement
*/
class OptionalWithSignedIntegerSelectorBeginningElement final :
    public OptionalWithIntegerSelectorBeginningElement<OptionalWithSignedIntegerSelectorType, long long,
                                                       Element::Kind::OptionalWithSignedIntegerSelectorBeginning>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithSignedIntegerSelectorBeginningElement()
    {
    }

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Optional with signed integer selector end element.

@ingroup elems

This element indicates the end of a data stream optional with a signed
integer selector.

@sa OptionalWithSignedIntegerSelectorBeginningElement
*/
class OptionalWithSignedIntegerSelectorEndElement final :
    public OptionalWithIntegerSelectorEndElement<OptionalWithSignedIntegerSelectorType,
                                                 Element::Kind::OptionalWithSignedIntegerSelectorEnd>
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit OptionalWithSignedIntegerSelectorEndElement() = default;

public:
    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

inline const DataStreamInfoElement& Element::asDataStreamInfoElement() const noexcept
{
    return static_cast<const DataStreamInfoElement&>(*this);
}

inline const DefaultClockValueElement& Element::asDefaultClockValueElement() const noexcept
{
    return static_cast<const DefaultClockValueElement&>(*this);
}

inline const DynamicLengthArrayBeginningElement& Element::asDynamicLengthArrayBeginningElement() const noexcept
{
    return static_cast<const DynamicLengthArrayBeginningElement&>(*this);
}

inline const DynamicLengthArrayEndElement& Element::asDynamicLengthArrayEndElement() const noexcept
{
    return static_cast<const DynamicLengthArrayEndElement&>(*this);
}

inline const DynamicLengthBlobBeginningElement& Element::asDynamicLengthBlobBeginningElement() const noexcept
{
    return static_cast<const DynamicLengthBlobBeginningElement&>(*this);
}

inline const DynamicLengthBlobEndElement& Element::asDynamicLengthBlobEndElement() const noexcept
{
    return static_cast<const DynamicLengthBlobEndElement&>(*this);
}

inline const DynamicLengthStringBeginningElement& Element::asDynamicLengthStringBeginningElement() const noexcept
{
    return static_cast<const DynamicLengthStringBeginningElement&>(*this);
}

inline const DynamicLengthStringEndElement& Element::asDynamicLengthStringEndElement() const noexcept
{
    return static_cast<const DynamicLengthStringEndElement&>(*this);
}

inline const EventRecordBeginningElement& Element::asEventRecordBeginningElement() const noexcept
{
    return static_cast<const EventRecordBeginningElement&>(*this);
}

inline const EventRecordEndElement& Element::asEventRecordEndElement() const noexcept
{
    return static_cast<const EventRecordEndElement&>(*this);
}

inline const EventRecordInfoElement& Element::asEventRecordInfoElement() const noexcept
{
    return static_cast<const EventRecordInfoElement&>(*this);
}

inline const FixedLengthBitArrayElement& Element::asFixedLengthBitArrayElement() const noexcept
{
    return static_cast<const FixedLengthBitArrayElement&>(*this);
}

inline const FixedLengthBitMapElement& Element::asFixedLengthBitMapElement() const noexcept
{
    return static_cast<const FixedLengthBitMapElement&>(*this);
}

inline const FixedLengthBooleanElement& Element::asFixedLengthBooleanElement() const noexcept
{
    return static_cast<const FixedLengthBooleanElement&>(*this);
}

inline const FixedLengthFloatingPointNumberElement& Element::asFixedLengthFloatingPointNumberElement() const noexcept
{
    return static_cast<const FixedLengthFloatingPointNumberElement&>(*this);
}

inline const FixedLengthSignedIntegerElement& Element::asFixedLengthSignedIntegerElement() const noexcept
{
    return static_cast<const FixedLengthSignedIntegerElement&>(*this);
}

inline const FixedLengthUnsignedIntegerElement& Element::asFixedLengthUnsignedIntegerElement() const noexcept
{
    return static_cast<const FixedLengthUnsignedIntegerElement&>(*this);
}

inline const NullTerminatedStringBeginningElement& Element::asNullTerminatedStringBeginningElement() const noexcept
{
    return static_cast<const NullTerminatedStringBeginningElement&>(*this);
}

inline const NullTerminatedStringEndElement& Element::asNullTerminatedStringEndElement() const noexcept
{
    return static_cast<const NullTerminatedStringEndElement&>(*this);
}

inline const OptionalBeginningElement& Element::asOptionalBeginningElement() const noexcept
{
    return static_cast<const OptionalBeginningElement&>(*this);
}

inline const OptionalEndElement& Element::asOptionalEndElement() const noexcept
{
    return static_cast<const OptionalEndElement&>(*this);
}

inline const OptionalWithBooleanSelectorBeginningElement& Element::asOptionalWithBooleanSelectorBeginningElement() const noexcept
{
    return static_cast<const OptionalWithBooleanSelectorBeginningElement&>(*this);
}

inline const OptionalWithBooleanSelectorEndElement& Element::asOptionalWithBooleanSelectorEndElement() const noexcept
{
    return static_cast<const OptionalWithBooleanSelectorEndElement&>(*this);
}

inline const OptionalWithSignedIntegerSelectorBeginningElement& Element::asOptionalWithSignedIntegerSelectorBeginningElement() const noexcept
{
    return static_cast<const OptionalWithSignedIntegerSelectorBeginningElement&>(*this);
}

inline const OptionalWithSignedIntegerSelectorEndElement& Element::asOptionalWithSignedIntegerSelectorEndElement() const noexcept
{
    return static_cast<const OptionalWithSignedIntegerSelectorEndElement&>(*this);
}

inline const OptionalWithUnsignedIntegerSelectorBeginningElement& Element::asOptionalWithUnsignedIntegerSelectorBeginningElement() const noexcept
{
    return static_cast<const OptionalWithUnsignedIntegerSelectorBeginningElement&>(*this);
}

inline const OptionalWithUnsignedIntegerSelectorEndElement& Element::asOptionalWithUnsignedIntegerSelectorEndElement() const noexcept
{
    return static_cast<const OptionalWithUnsignedIntegerSelectorEndElement&>(*this);
}

inline const PacketBeginningElement& Element::asPacketBeginningElement() const noexcept
{
    return static_cast<const PacketBeginningElement&>(*this);
}

inline const PacketContentBeginningElement& Element::asPacketContentBeginningElement() const noexcept
{
    return static_cast<const PacketContentBeginningElement&>(*this);
}

inline const PacketContentEndElement& Element::asPacketContentEndElement() const noexcept
{
    return static_cast<const PacketContentEndElement&>(*this);
}

inline const PacketEndElement& Element::asPacketEndElement() const noexcept
{
    return static_cast<const PacketEndElement&>(*this);
}

inline const PacketInfoElement& Element::asPacketInfoElement() const noexcept
{
    return static_cast<const PacketInfoElement&>(*this);
}

inline const PacketMagicNumberElement& Element::asPacketMagicNumberElement() const noexcept
{
    return static_cast<const PacketMagicNumberElement&>(*this);
}

inline const ScopeBeginningElement& Element::asScopeBeginningElement() const noexcept
{
    return static_cast<const ScopeBeginningElement&>(*this);
}

inline const ScopeEndElement& Element::asScopeEndElement() const noexcept
{
    return static_cast<const ScopeEndElement&>(*this);
}

inline const StaticLengthArrayBeginningElement& Element::asStaticLengthArrayBeginningElement() const noexcept
{
    return static_cast<const StaticLengthArrayBeginningElement&>(*this);
}

inline const StaticLengthArrayEndElement& Element::asStaticLengthArrayEndElement() const noexcept
{
    return static_cast<const StaticLengthArrayEndElement&>(*this);
}

inline const StaticLengthBlobBeginningElement& Element::asStaticLengthBlobBeginningElement() const noexcept
{
    return static_cast<const StaticLengthBlobBeginningElement&>(*this);
}

inline const StaticLengthBlobEndElement& Element::asStaticLengthBlobEndElement() const noexcept
{
    return static_cast<const StaticLengthBlobEndElement&>(*this);
}

inline const StaticLengthStringBeginningElement& Element::asStaticLengthStringBeginningElement() const noexcept
{
    return static_cast<const StaticLengthStringBeginningElement&>(*this);
}

inline const StaticLengthStringEndElement& Element::asStaticLengthStringEndElement() const noexcept
{
    return static_cast<const StaticLengthStringEndElement&>(*this);
}

inline const StructureBeginningElement& Element::asStructureBeginningElement() const noexcept
{
    return static_cast<const StructureBeginningElement&>(*this);
}

inline const StructureEndElement& Element::asStructureEndElement() const noexcept
{
    return static_cast<const StructureEndElement&>(*this);
}

inline const RawDataElement& Element::asRawDataElement() const noexcept
{
    return static_cast<const RawDataElement&>(*this);
}

inline const MetadataStreamUuidElement& Element::asMetadataStreamUuidElement() const noexcept
{
    return static_cast<const MetadataStreamUuidElement&>(*this);
}

inline const VariableLengthSignedIntegerElement& Element::asVariableLengthSignedIntegerElement() const noexcept
{
    return static_cast<const VariableLengthSignedIntegerElement&>(*this);
}

inline const VariableLengthUnsignedIntegerElement& Element::asVariableLengthUnsignedIntegerElement() const noexcept
{
    return static_cast<const VariableLengthUnsignedIntegerElement&>(*this);
}

inline const VariantBeginningElement& Element::asVariantBeginningElement() const noexcept
{
    return static_cast<const VariantBeginningElement&>(*this);
}

inline const VariantEndElement& Element::asVariantEndElement() const noexcept
{
    return static_cast<const VariantEndElement&>(*this);
}

inline const VariantWithSignedIntegerSelectorBeginningElement& Element::asVariantWithSignedIntegerSelectorBeginningElement() const noexcept
{
    return static_cast<const VariantWithSignedIntegerSelectorBeginningElement&>(*this);
}

inline const VariantWithSignedIntegerSelectorEndElement& Element::asVariantWithSignedIntegerSelectorEndElement() const noexcept
{
    return static_cast<const VariantWithSignedIntegerSelectorEndElement&>(*this);
}

inline const VariantWithUnsignedIntegerSelectorBeginningElement& Element::asVariantWithUnsignedIntegerSelectorBeginningElement() const noexcept
{
    return static_cast<const VariantWithUnsignedIntegerSelectorBeginningElement&>(*this);
}

inline const VariantWithUnsignedIntegerSelectorEndElement& Element::asVariantWithUnsignedIntegerSelectorEndElement() const noexcept
{
    return static_cast<const VariantWithUnsignedIntegerSelectorEndElement&>(*this);
}

} // namespace yactfr

#endif // YACTFR_ELEM_HPP
