/*
 * Copyright (C) 2016-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_ELEM_HPP
#define _YACTFR_ELEM_HPP

#include <cstdint>
#include <string>
#include <algorithm>
#include <boost/uuid/uuid.hpp>
#include <boost/optional/optional.hpp>

#ifdef __cpp_lib_string_view
#include <string_view>
#endif

#include "metadata/fwd.hpp"
#include "metadata/dt.hpp"
#include "metadata/fl-bit-array-type.hpp"
#include "metadata/fl-bool-type.hpp"
#include "metadata/fl-float-type.hpp"
#include "metadata/fl-int-type.hpp"
#include "metadata/fl-enum-type.hpp"
#include "metadata/vl-int-type.hpp"
#include "metadata/vl-enum-type.hpp"
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
    enum _Kind
    {
        _KIND_END                               = 1 << 0,
        _KIND_BEG                               = 1 << 1,
        _KIND_PKT                               = 1 << 2,
        _KIND_SCOPE                             = 1 << 3,
        _KIND_PKT_CONTENT                       = 1 << 4,
        _KIND_ER                                = 1 << 5,
        _KIND_PKT_MAGIC_NUMBER                  = 1 << 6,
        _KIND_METADATA_STREAM_UUID              = 1 << 7,
        _KIND_DS                                = 1 << 8,
        _KIND_INFO                              = 1 << 9,
        _KIND_DEF_CLK_VAL                       = 1 << 10,
        _KIND_FL_BIT_ARRAY                      = 1 << 11,
        _KIND_BOOL_DATA                         = 1 << 12,
        _KIND_INT_DATA                          = 1 << 13,
        _KIND_SIGNED                            = 1 << 14,
        _KIND_UNSIGNED                          = 1 << 15,
        _KIND_FLOAT_DATA                        = 1 << 16,
        _KIND_ENUM_DATA                         = _KIND_INT_DATA | (1 << 17),
        _KIND_VL_INT                            = _KIND_INT_DATA | (1 << 18),
        _KIND_NT_STR                            = 1 << 19,
        _KIND_SUBSTR                            = 1 << 20,
        _KIND_BLOB_SECTION                      = 1 << 21,
        _KIND_STRUCT                            = 1 << 22,
        _KIND_SL_DATA                           = 1 << 23,
        _KIND_DL_DATA                           = 1 << 24,
        _KIND_ARRAY                             = 1 << 25,
        _KIND_NON_NT_STR                        = 1 << 26,
        _KIND_BLOB                              = 1 << 27,
        _KIND_VAR                               = 1 << 28,
        _KIND_INT_SEL                           = 1 << 29,
        _KIND_BOOL_SEL                          = 1 << 30,
        _KIND_OPT                               = 1 << 31,
    };

    using _U = unsigned long long;

public:
    /// %Kind of element.
    enum class Kind : _U
    {
        /// PacketBeginningElement
        PACKET_BEGINNING                                    = static_cast<_U>(_KIND_PKT | _KIND_BEG),

        /// PacketEndElement
        PACKET_END                                          = static_cast<_U>(_KIND_PKT | _KIND_END),

        /// ScopeBeginningElement
        SCOPE_BEGINNING                                     = static_cast<_U>(_KIND_SCOPE | _KIND_BEG),

        /// ScopeEndElement
        SCOPE_END                                           = static_cast<_U>(_KIND_SCOPE | _KIND_END),

        /// PacketContentBeginningElement
        PACKET_CONTENT_BEGINNING                            = static_cast<_U>(_KIND_PKT_CONTENT | _KIND_BEG),

        /// PacketContentEndElement
        PACKET_CONTENT_END                                  = static_cast<_U>(_KIND_PKT_CONTENT | _KIND_END),

        /// EventRecordBeginningElement
        EVENT_RECORD_BEGINNING                              = static_cast<_U>(_KIND_ER | _KIND_BEG),

        /// EventRecordEndElement
        EVENT_RECORD_END                                    = static_cast<_U>(_KIND_ER | _KIND_END),

        /// PacketMagicNumberElement
        PACKET_MAGIC_NUMBER                                 = static_cast<_U>(_KIND_PKT_MAGIC_NUMBER),

        /// MetadataStreamUuidElement
        METADATA_STREAM_UUID                                = static_cast<_U>(_KIND_METADATA_STREAM_UUID),

        /// DataStreamInfoElement
        DATA_STREAM_INFO                                    = static_cast<_U>(_KIND_DS | _KIND_INFO),

        /// DefaultClockValueElement
        DEFAULT_CLOCK_VALUE                                 = static_cast<_U>(_KIND_DEF_CLK_VAL),

        /// PacketInfoElement
        PACKET_INFO                                         = static_cast<_U>(_KIND_PKT | _KIND_INFO),

        /// EventRecordInfoElement
        EVENT_RECORD_INFO                                   = static_cast<_U>(_KIND_ER | _KIND_INFO),

        /// FixedLengthBitArrayElement
        FIXED_LENGTH_BIT_ARRAY                              = static_cast<_U>(_KIND_FL_BIT_ARRAY),

        /// FixedLengthBooleanElement
        FIXED_LENGTH_BOOLEAN                                = static_cast<_U>(_KIND_FL_BIT_ARRAY | _KIND_BOOL_DATA),

        /// FixedLengthSignedIntegerElement
        FIXED_LENGTH_SIGNED_INTEGER                         = static_cast<_U>(_KIND_FL_BIT_ARRAY | _KIND_INT_DATA | _KIND_SIGNED),

        /// FixedLengthUnsignedIntegerElement
        FIXED_LENGTH_UNSIGNED_INTEGER                       = static_cast<_U>(_KIND_FL_BIT_ARRAY | _KIND_INT_DATA | _KIND_UNSIGNED),

        /// FixedLengthFloatingPointNumberElement
        FIXED_LENGTH_FLOATING_POINT_NUMBER                  = static_cast<_U>(_KIND_FL_BIT_ARRAY | _KIND_FLOAT_DATA),

        /// FixedLengthSignedEnumerationElement
        FIXED_LENGTH_SIGNED_ENUMERATION                     = static_cast<_U>(_KIND_FL_BIT_ARRAY | _KIND_ENUM_DATA | _KIND_SIGNED),

        /// FixedLengthUnsignedEnumerationElement
        FIXED_LENGTH_UNSIGNED_ENUMERATION                   = static_cast<_U>(_KIND_FL_BIT_ARRAY | _KIND_ENUM_DATA | _KIND_UNSIGNED),

        /// VariableLengthSignedIntegerElement
        VARIABLE_LENGTH_SIGNED_INTEGER                      = static_cast<_U>(_KIND_VL_INT | _KIND_SIGNED),

        /// VariableLengthUnsignedIntegerElement
        VARIABLE_LENGTH_UNSIGNED_INTEGER                    = static_cast<_U>(_KIND_VL_INT | _KIND_UNSIGNED),

        /// VariableLengthSignedEnumerationElement
        VARIABLE_LENGTH_SIGNED_ENUMERATION                  = static_cast<_U>(_KIND_VL_INT | _KIND_ENUM_DATA | _KIND_SIGNED),

        /// VariableLengthUnsignedEnumerationElement
        VARIABLE_LENGTH_UNSIGNED_ENUMERATION                = static_cast<_U>(_KIND_VL_INT | _KIND_ENUM_DATA | _KIND_UNSIGNED),

        /// NullTerminatedStringBeginningElement
        NULL_TERMINATED_STRING_BEGINNING                    = static_cast<_U>(_KIND_NT_STR | _KIND_BEG),

        /// NullTerminatedStringEndElement
        NULL_TERMINATED_STRING_END                          = static_cast<_U>(_KIND_NT_STR | _KIND_END),

        /// SubstringElement
        SUBSTRING                                           = static_cast<_U>(_KIND_SUBSTR),

        /// BlobSectionElement
        BLOB_SECTION                                        = static_cast<_U>(_KIND_BLOB_SECTION),

        /// StructureBeginningElement
        STRUCTURE_BEGINNING                                 = static_cast<_U>(_KIND_STRUCT | _KIND_BEG),

        /// StructureEndElement
        STRUCTURE_END                                       = static_cast<_U>(_KIND_STRUCT | _KIND_END),

        /// StaticLengthArrayBeginningElement
        STATIC_LENGTH_ARRAY_BEGINNING                       = static_cast<_U>(_KIND_SL_DATA | _KIND_ARRAY | _KIND_BEG),

        /// StaticLengthArrayEndElement
        STATIC_LENGTH_ARRAY_END                             = static_cast<_U>(_KIND_SL_DATA | _KIND_ARRAY | _KIND_END),

        /// DynamicLengthArrayBeginningElement
        DYNAMIC_LENGTH_ARRAY_BEGINNING                      = static_cast<_U>(_KIND_DL_DATA | _KIND_ARRAY | _KIND_BEG),

        /// DynamicLengthArrayEndElement
        DYNAMIC_LENGTH_ARRAY_END                            = static_cast<_U>(_KIND_DL_DATA | _KIND_ARRAY | _KIND_END),

        /// StaticLengthBlobBeginningElement
        STATIC_LENGTH_BLOB_BEGINNING                        = static_cast<_U>(_KIND_SL_DATA | _KIND_BLOB | _KIND_BEG),

        /// StaticLengthBlobEndElement
        STATIC_LENGTH_BLOB_END                              = static_cast<_U>(_KIND_SL_DATA | _KIND_BLOB | _KIND_END),

        /// DynamicLengthBlobBeginningElement
        DYNAMIC_LENGTH_BLOB_BEGINNING                       = static_cast<_U>(_KIND_DL_DATA | _KIND_BLOB | _KIND_BEG),

        /// DynamicLengthBlobEndElement
        DYNAMIC_LENGTH_BLOB_END                             = static_cast<_U>(_KIND_DL_DATA | _KIND_BLOB | _KIND_END),

        /// StaticLengthStringBeginningElement
        STATIC_LENGTH_STRING_BEGINNING                      = static_cast<_U>(_KIND_SL_DATA | _KIND_NON_NT_STR | _KIND_BEG),

        /// StaticLengthStringEndElement
        STATIC_LENGTH_STRING_END                            = static_cast<_U>(_KIND_SL_DATA | _KIND_NON_NT_STR | _KIND_END),

        /// DynamicLengthStringBeginningElement
        DYNAMIC_LENGTH_STRING_BEGINNING                     = static_cast<_U>(_KIND_DL_DATA | _KIND_NON_NT_STR | _KIND_BEG),

        /// DynamicLengthStringEndElement
        DYNAMIC_LENGTH_STRING_END                           = static_cast<_U>(_KIND_DL_DATA | _KIND_NON_NT_STR | _KIND_END),

        /// VariantWithSignedIntegerSelectorBeginningElement
        VARIANT_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING      = static_cast<_U>(_KIND_VAR | _KIND_SIGNED | _KIND_BEG),

        /// VariantWithSignedIntegerSelectorEndElement
        VARIANT_WITH_SIGNED_INTEGER_SELECTOR_END            = static_cast<_U>(_KIND_VAR | _KIND_SIGNED | _KIND_END),

        /// VariantWithUnsignedIntegerSelectorBeginningElement
        VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING    = static_cast<_U>(_KIND_VAR | _KIND_UNSIGNED | _KIND_BEG),

        /// VariantWithUnsignedIntegerSelectorEndElement
        VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_END          = static_cast<_U>(_KIND_VAR | _KIND_UNSIGNED | _KIND_END),

        /// OptionalWithBooleanSelectorBeginningElement
        OPTIONAL_WITH_BOOLEAN_SELECTOR_BEGINNING            = static_cast<_U>(_KIND_OPT | _KIND_BOOL_SEL | _KIND_BEG),

        /// OptionalWithBooleanSelectorEndElement
        OPTIONAL_WITH_BOOLEAN_SELECTOR_END                  = static_cast<_U>(_KIND_OPT | _KIND_BOOL_SEL | _KIND_END),

        /// OptionalWithSignedIntegerSelectorBeginningElement
        OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING     = static_cast<_U>(_KIND_OPT | _KIND_SIGNED | _KIND_BEG),

        /// OptionalWithSignedIntegerSelectorEndElement
        OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_END           = static_cast<_U>(_KIND_OPT | _KIND_SIGNED | _KIND_END),

        /// OptionalWithUnsignedIntegerSelectorBeginningElement
        OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING   = static_cast<_U>(_KIND_OPT | _KIND_UNSIGNED | _KIND_BEG),

        /// OptionalWithUnsignedIntegerSelectorEndElement
        OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_END         = static_cast<_U>(_KIND_OPT | _KIND_UNSIGNED | _KIND_END),
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
        return this->_isKind(_KIND_BEG);
    }

    /// \c true if this element is an end element.
    bool isEndElement() const noexcept
    {
        return this->_isKind(_KIND_END);
    }

    /// \c true if this element is a packet beginning/end element.
    bool isPacketElement() const noexcept
    {
        return this->_isKind(_KIND_PKT);
    }

    /// \c true if this element is a packet beginning element.
    bool isPacketBeginningElement() const noexcept
    {
        return _kind == Kind::PACKET_BEGINNING;
    }

    /// \c true if this element is a packet end element.
    bool isPacketEndElement() const noexcept
    {
        return _kind == Kind::PACKET_END;
    }

    /// \c true if this element is a scope beginning/end element.
    bool isScopeElement() const noexcept
    {
        return this->_isKind(_KIND_SCOPE);
    }

    /// \c true if this element is a scope beginning element.
    bool isScopeBeginningElement() const noexcept
    {
        return _kind == Kind::SCOPE_BEGINNING;
    }

    /// \c true if this element is a scope end element.
    bool isScopeEndElement() const noexcept
    {
        return _kind == Kind::SCOPE_END;
    }

    /// \c true if this element is a packet content beginning/end element.
    bool isPacketContentElement() const noexcept
    {
        return this->_isKind(_KIND_PKT_CONTENT);
    }

    /// \c true if this element is a packet content beginning element.
    bool isPacketContentBeginningElement() const noexcept
    {
        return _kind == Kind::PACKET_CONTENT_BEGINNING;
    }

    /// \c true if this element is a packet content end element.
    bool isPacketContentEndElement() const noexcept
    {
        return _kind == Kind::PACKET_CONTENT_END;
    }

    /// \c true if this element is an event record beginning/end element.
    bool isEventRecordElement() const noexcept
    {
        return this->_isKind(_KIND_ER);
    }

    /// \c true if this element is an event record beginning element.
    bool isEventRecordBeginningElement() const noexcept
    {
        return _kind == Kind::EVENT_RECORD_BEGINNING;
    }

    /// \c true if this element is an event record end element.
    bool isEventRecordEndElement() const noexcept
    {
        return _kind == Kind::EVENT_RECORD_END;
    }

    /// \c true if this element is a packet magic number element.
    bool isPacketMagicNumberElement() const noexcept
    {
        return _kind == Kind::PACKET_MAGIC_NUMBER;
    }

    /// \c true if this element is a metadata stream UUID element.
    bool isMetadataStreamUuidElement() const noexcept
    {
        return _kind == Kind::METADATA_STREAM_UUID;
    }

    /// \c true if this element is a data stream info element.
    bool isDataStreamInfoElement() const noexcept
    {
        return _kind == Kind::DATA_STREAM_INFO;
    }

    /// \c true if this element is a default clock value element.
    bool isDefaultClockValueElement() const noexcept
    {
        return _kind == Kind::DEFAULT_CLOCK_VALUE;
    }

    /// \c true if this element is an info element.
    bool isInfoElement() const noexcept
    {
        return this->_isKind(_KIND_INFO);
    }

    /// \c true if this element is a packet info element.
    bool isPacketInfoElement() const noexcept
    {
        return _kind == Kind::PACKET_INFO;
    }

    /// \c true if this element is an event record info element.
    bool isEventRecordInfoElement() const noexcept
    {
        return _kind == Kind::EVENT_RECORD_INFO;
    }

    /// \c true if this element is a fixed-length bit array element.
    bool isFixedLengthBitArrayElement() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY);
    }

    /// \c true if this element is a fixed-length boolean element.
    bool isFixedLengthBooleanElement() const noexcept
    {
        return _kind == Kind::FIXED_LENGTH_BOOLEAN;
    }

    /// \c true if this element is an integer element.
    bool isIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_INT_DATA);
    }

    /// \c true if this element is a fixed-length integer element.
    bool isFixedLengthIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY | _KIND_INT_DATA);
    }

    /// \c true if this element is a signed integer element.
    bool isSignedIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_INT_DATA | _KIND_SIGNED);
    }

    /// \c true if this element is an unsigned integer element.
    bool isUnsignedIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_INT_DATA | _KIND_UNSIGNED);
    }

    /// \c true if this element is a fixed-length signed integer element.
    bool isFixedLengthSignedIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY | _KIND_INT_DATA | _KIND_SIGNED);
    }

    /// \c true if this element is a fixed-length unsigned integer element.
    bool isFixedLengthUnsignedIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY | _KIND_INT_DATA | _KIND_UNSIGNED);
    }

    /// \c true if this element is a fixed-length floating-point number element.
    bool isFixedLengthFloatingPointNumberElement() const noexcept
    {
        return _kind == Kind::FIXED_LENGTH_FLOATING_POINT_NUMBER;
    }

    /// \c true if this element is an enumeration element.
    bool isEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_ENUM_DATA);
    }

    /// \c true if this element is a fixed-length enumeration element.
    bool isFixedLengthEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY | _KIND_ENUM_DATA);
    }

    /// \c true if this element is a signed enumeration element.
    bool isSignedEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_ENUM_DATA | _KIND_SIGNED);
    }

    /// \c true if this element is an unsigned enumeration element.
    bool isUnsignedEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_ENUM_DATA | _KIND_UNSIGNED);
    }

    /// \c true if this element is a fixed-length signed enumeration element.
    bool isFixedLengthSignedEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY | _KIND_ENUM_DATA | _KIND_SIGNED);
    }

    /// \c true if this element is a fixed-length unsigned enumeration element.
    bool isFixedLengthUnsignedEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_FL_BIT_ARRAY | _KIND_ENUM_DATA | _KIND_UNSIGNED);
    }

    /// \c true if this element is a variable-length integer element.
    bool isVariableLengthIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_VL_INT);
    }

    /// \c true if this element is a variable-length signed integer element.
    bool isVariableLengthSignedIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_VL_INT | _KIND_SIGNED);
    }

    /// \c true if this element is a variable-length unsigned integer element.
    bool isVariableLengthUnsignedIntegerElement() const noexcept
    {
        return this->_isKind(_KIND_VL_INT | _KIND_UNSIGNED);
    }

    /// \c true if this element is a variable-length enumeration element.
    bool isVariableLengthEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_VL_INT | _KIND_ENUM_DATA);
    }

    /// \c true if this element is a variable-length signed enumeration element.
    bool isVariableLengthSignedEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_VL_INT | _KIND_ENUM_DATA | _KIND_SIGNED);
    }

    /// \c true if this element is a variable-length unsigned enumeration element.
    bool isVariableLengthUnsignedEnumerationElement() const noexcept
    {
        return this->_isKind(_KIND_VL_INT | _KIND_ENUM_DATA | _KIND_UNSIGNED);
    }

    /// \c true if this element is a null-terminated string beginning/end element.
    bool isNullTerminatedStringElement() const noexcept
    {
        return this->_isKind(_KIND_NT_STR);
    }

    /// \c true if this element is a null-terminated string beginning element.
    bool isNullTerminatedStringBeginningElement() const noexcept
    {
        return _kind == Kind::NULL_TERMINATED_STRING_BEGINNING;
    }

    /// \c true if this element is a null-terminated string end element.
    bool isNullTerminatedStringEndElement() const noexcept
    {
        return _kind == Kind::NULL_TERMINATED_STRING_END;
    }

    /// \c true if this element is a substring element.
    bool isSubstringElement() const noexcept
    {
        return _kind == Kind::SUBSTRING;
    }

    /// \c true if this element is a BLOB section element.
    bool isBlobSectionElement() const noexcept
    {
        return _kind == Kind::BLOB_SECTION;
    }

    /// \c true if this element is a structure beginning/end element.
    bool isStructureElement() const noexcept
    {
        return this->_isKind(_KIND_STRUCT);
    }

    /// \c true if this element is a structure beginning element.
    bool isStructureBeginningElement() const noexcept
    {
        return _kind == Kind::STRUCTURE_BEGINNING;
    }

    /// \c true if this element is a structure end element.
    bool isStructureEndElement() const noexcept
    {
        return _kind == Kind::STRUCTURE_END;
    }

    /// \c true if this element is an array beginning/end element.
    bool isArrayElement() const noexcept
    {
        return this->_isKind(_KIND_ARRAY);
    }

    /// \c true if this element is a static-length array beginning/end element.
    bool isStaticLengthArrayElement() const noexcept
    {
        return this->_isKind(_KIND_SL_DATA | _KIND_ARRAY);
    }

    /// \c true if this element is a static-length array beginning element.
    bool isStaticLengthArrayBeginningElement() const noexcept
    {
        return _kind == Kind::STATIC_LENGTH_ARRAY_BEGINNING;
    }

    /// \c true if this element is a static-length array end element.
    bool isStaticLengthArrayEndElement() const noexcept
    {
        return _kind == Kind::STATIC_LENGTH_ARRAY_END;
    }

    /// \c true if this element is a dynamic-length array beginning/end element.
    bool isDynamicLengthArrayElement() const noexcept
    {
        return this->_isKind(_KIND_DL_DATA | _KIND_ARRAY);
    }

    /// \c true if this element is a dynamic-length array beginning element.
    bool isDynamicLengthArrayBeginningElement() const noexcept
    {
        return _kind == Kind::DYNAMIC_LENGTH_ARRAY_BEGINNING;
    }

    /// \c true if this element is a dynamic-length array end element.
    bool isDynamicLengthArrayEndElement() const noexcept
    {
        return _kind == Kind::DYNAMIC_LENGTH_ARRAY_END;
    }

    /// \c true if this element is a BLOB beginning/end element.
    bool isBlobElement() const noexcept
    {
        return this->_isKind(_KIND_BLOB);
    }

    /// \c true if this element is a static-length BLOB beginning/end element.
    bool isStaticLengthBlobElement() const noexcept
    {
        return this->_isKind(_KIND_SL_DATA | _KIND_BLOB);
    }

    /// \c true if this element is a static-length BLOB beginning element.
    bool isStaticLengthBlobBeginningElement() const noexcept
    {
        return _kind == Kind::STATIC_LENGTH_BLOB_BEGINNING;
    }

    /// \c true if this element is a static-length BLOB end element.
    bool isStaticLengthBlobEndElement() const noexcept
    {
        return _kind == Kind::STATIC_LENGTH_BLOB_END;
    }

    /// \c true if this element is a dynamic-length BLOB beginning/end element.
    bool isDynamicLengthBlobElement() const noexcept
    {
        return this->_isKind(_KIND_DL_DATA | _KIND_BLOB);
    }

    /// \c true if this element is a dynamic-length BLOB beginning element.
    bool isDynamicLengthBlobBeginningElement() const noexcept
    {
        return _kind == Kind::DYNAMIC_LENGTH_BLOB_BEGINNING;
    }

    /// \c true if this element is a dynamic-length BLOB end element.
    bool isDynamicLengthBlobEndElement() const noexcept
    {
        return _kind == Kind::DYNAMIC_LENGTH_BLOB_END;
    }

    /// \c true if this element is a non-null-terminated string beginning/end element.
    bool isNonNullTerminatedStringElement() const noexcept
    {
        return this->_isKind(_KIND_NON_NT_STR);
    }

    /// \c true if this element is a static-length string beginning/end element.
    bool isStaticLengthStringElement() const noexcept
    {
        return this->_isKind(_KIND_SL_DATA | _KIND_NON_NT_STR);
    }

    /// \c true if this element is a static-length string beginning element.
    bool isStaticLengthStringBeginningElement() const noexcept
    {
        return _kind == Kind::STATIC_LENGTH_STRING_BEGINNING;
    }

    /// \c true if this element is a static-length string end element.
    bool isStaticLengthStringEndElement() const noexcept
    {
        return _kind == Kind::STATIC_LENGTH_STRING_END;
    }

    /// \c true if this element is a dynamic-length string beginning/end element.
    bool isDynamicLengthStringElement() const noexcept
    {
        return this->_isKind(_KIND_DL_DATA | _KIND_NON_NT_STR);
    }

    /// \c true if this element is a dynamic-length string beginning element.
    bool isDynamicLengthStringBeginningElement() const noexcept
    {
        return _kind == Kind::DYNAMIC_LENGTH_STRING_BEGINNING;
    }

    /// \c true if this element is a dynamic-length string end element.
    bool isDynamicLengthStringEndElement() const noexcept
    {
        return _kind == Kind::DYNAMIC_LENGTH_STRING_END;
    }

    /// \c true if this element is a variant beginning/end element.
    bool isVariantElement() const noexcept
    {
        return this->_isKind(_KIND_VAR);
    }

    /// \c true if this element is a variant beginning element.
    bool isVariantBeginningElement() const noexcept
    {
        return this->_isKind(_KIND_VAR | _KIND_BEG);
    }

    /// \c true if this element is a variant end element.
    bool isVariantEndElement() const noexcept
    {
        return this->_isKind(_KIND_VAR | _KIND_END);
    }

    /// \c true if this element is a variant with a signed integer selector beginning/end element.
    bool isVariantWithSignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_KIND_VAR | _KIND_SIGNED);
    }

    /// \c true if this element is a variant with a signed integer selector beginning element.
    bool isVariantWithSignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::VARIANT_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING;
    }

    /// \c true if this element is a variant with a signed integer selector end element.
    bool isVariantWithSignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::VARIANT_WITH_SIGNED_INTEGER_SELECTOR_END;
    }

    /// \c true if this element is a variant with an unsigned integer selector beginning/end element.
    bool isVariantWithUnsignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_KIND_VAR | _KIND_UNSIGNED);
    }

    /// \c true if this element is a variant with an unsigned integer selector beginning element.
    bool isVariantWithUnsignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING;
    }

    /// \c true if this element is a variant with an unsigned integer selector end element.
    bool isVariantWithUnsignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_END;
    }

    /// \c true if this element is an optional beginning/end element.
    bool isOptionalElement() const noexcept
    {
        return this->_isKind(_KIND_OPT);
    }

    /// \c true if this element is an optional beginning element.
    bool isOptionalBeginningElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_BEG);
    }

    /// \c true if this element is an optional end element.
    bool isOptionalEndElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_END);
    }

    /// \c true if this element is an optional with a boolean selector beginning/end element.
    bool isOptionalWithBooleanSelectorElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_BOOL_SEL);
    }

    /// \c true if this element is an optional with a boolean selector beginning element.
    bool isOptionalWithBooleanSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::OPTIONAL_WITH_BOOLEAN_SELECTOR_BEGINNING;
    }

    /// \c true if this element is an optional with a boolean selector end element.
    bool isOptionalWithBooleanSelectorEndElement() const noexcept
    {
        return _kind == Kind::OPTIONAL_WITH_BOOLEAN_SELECTOR_END;
    }

    /// \c true if this element is an optional with an integer selector beginning/end element.
    bool isOptionalWithIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_SIGNED | _KIND_UNSIGNED);
    }

    /// \c true if this element is an optional with an integer selector beginning element.
    bool isOptionalWithIntegerSelectorBeginningElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_SIGNED | _KIND_UNSIGNED | _KIND_BEG);
    }

    /// \c true if this element is an optional with an integer selector end element.
    bool isOptionalWithIntegerSelectorEndElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_SIGNED | _KIND_UNSIGNED | _KIND_END);
    }

    /// \c true if this element is an optional with a signed integer selector beginning/end element.
    bool isOptionalWithSignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_SIGNED);
    }

    /// \c true if this element is an optional with a signed integer selector beginning element.
    bool isOptionalWithSignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING;
    }

    /// \c true if this element is an optional with a signed integer selector end element.
    bool isOptionalWithSignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_END;
    }

    /// \c true if this element is an optional with an unsigned integer selector beginning/end element.
    bool isOptionalWithUnsignedIntegerSelectorElement() const noexcept
    {
        return this->_isKind(_KIND_OPT | _KIND_UNSIGNED);
    }

    /// \c true if this element is an optional with an unsigned integer selector beginning element.
    bool isOptionalWithUnsignedIntegerSelectorBeginningElement() const noexcept
    {
        return _kind == Kind::OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING;
    }

    /// \c true if this element is an optional with an unsigned integer selector end element.
    bool isOptionalWithUnsignedIntegerSelectorEndElement() const noexcept
    {
        return _kind == Kind::OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_END;
    }

    /*!
    @brief
        Returns this element as a BLOB element.

    @pre
        This type is a BLOB element.
    */
    const BlobSectionElement& asBlobSectionElement() const noexcept;

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
        Returns this element as a fixed-length signed enumeration
        element.

    @pre
        This type is a fixed-length signed enumeration element.
    */
    const FixedLengthSignedEnumerationElement& asFixedLengthSignedEnumerationElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length signed integer element.

    @pre
        This type is a fixed-length signed integer element.
    */
    const FixedLengthSignedIntegerElement& asFixedLengthSignedIntegerElement() const noexcept;

    /*!
    @brief
        Returns this element as a fixed-length unsigned enumeration
        element.

    @pre
        This type is a fixed-length unsigned enumeration element.
    */
    const FixedLengthUnsignedEnumerationElement& asFixedLengthUnsignedEnumerationElement() const noexcept;

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
        Returns this element as a substring element.

    @pre
        This type is a substring element.
    */
    const SubstringElement& asSubstringElement() const noexcept;

    /*!
    @brief
        Returns this element as a metadata stream UUID element.

    @pre
        This type is a metadata stream UUID element.
    */
    const MetadataStreamUuidElement& asMetadataStreamUuidElement() const noexcept;

    /*!
    @brief
        Returns this element as a variable-length signed enumeration
        element.

    @pre
        This type is a variable-length signed enumeration element.
    */
    const VariableLengthSignedEnumerationElement& asVariableLengthSignedEnumerationElement() const noexcept;

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
        Returns this element as a variable-length unsigned enumeration
        element.

    @pre
        This type is a variable-length unsigned enumeration element.
    */
    const VariableLengthUnsignedEnumerationElement& asVariableLengthUnsignedEnumerationElement() const noexcept;

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
        BeginningElement {Kind::PACKET_BEGINNING}
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
        EndElement {Kind::PACKET_END}
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
        BeginningElement {Kind::SCOPE_BEGINNING}
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
        EndElement {Kind::SCOPE_END}
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
        BeginningElement {Kind::EVENT_RECORD_BEGINNING}
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
        EndElement {Kind::EVENT_RECORD_END}
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
        BeginningElement {Kind::PACKET_CONTENT_BEGINNING}
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
        EndElement {Kind::PACKET_CONTENT_END}
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
        Element {Kind::PACKET_MAGIC_NUMBER}
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
        Element {Kind::METADATA_STREAM_UUID}
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
        Element {Kind::DATA_STREAM_INFO}
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
        Element {Kind::DEFAULT_CLOCK_VALUE}
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
        Element {Kind::PACKET_INFO}
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
        Element {Kind::EVENT_RECORD_INFO}
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
    explicit NumberElement(const Kind kind) :
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
        FixedLengthBitArrayElement {Kind::FIXED_LENGTH_BIT_ARRAY}
    {
    }

public:
    /// Fixed-length bit array type.
    const FixedLengthBitArrayType& type() const noexcept
    {
        return this->dataType().asFixedLengthBitArrayType();
    }

    /// Value as an unsigned integer.
    unsigned long long unsignedIntegerValue() const noexcept
    {
        return _theVal.u;
    }

    /*!
    @brief
        Returns the value of the bit at the index \p index, where
        0 is the index of the least significant bit.

    @param[in] index
        Index of the bit to return.

    @returns
        Bit at the index \p index.

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
        FixedLengthBitArrayElement {Kind::FIXED_LENGTH_BOOLEAN}
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
    Fixed-length signed integer element.

@ingroup elems
*/
class FixedLengthSignedIntegerElement :
    public FixedLengthBitArrayElement
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
        FixedLengthSignedIntegerElement {Kind::FIXED_LENGTH_SIGNED_INTEGER}
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
class FixedLengthUnsignedIntegerElement :
    public FixedLengthBitArrayElement
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
        FixedLengthUnsignedIntegerElement {Kind::FIXED_LENGTH_UNSIGNED_INTEGER}
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
    Fixed-length signed enumeration element.

@ingroup elems
*/
class FixedLengthSignedEnumerationElement final :
    public FixedLengthSignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthSignedEnumerationElement() :
        FixedLengthSignedIntegerElement {Kind::FIXED_LENGTH_SIGNED_ENUMERATION}
    {
    }

public:
    /// Fixed-length signed enumeration type.
    const FixedLengthSignedEnumerationType& type() const noexcept
    {
        return this->dataType().asFixedLengthSignedEnumerationType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Fixed-length unsigned enumeration element.

@ingroup elems
*/
class FixedLengthUnsignedEnumerationElement final :
    public FixedLengthUnsignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit FixedLengthUnsignedEnumerationElement() :
        FixedLengthUnsignedIntegerElement {Kind::FIXED_LENGTH_UNSIGNED_ENUMERATION}
    {
    }

public:
    /// Fixed-length unsigned enumeration type.
    const FixedLengthUnsignedEnumerationType& type() const noexcept
    {
        return this->dataType().asFixedLengthUnsignedEnumerationType();
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
        FixedLengthBitArrayElement {Kind::FIXED_LENGTH_FLOATING_POINT_NUMBER}
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
    /// Variable-length integer type.
    const VariableLengthIntegerType& type() const noexcept
    {
        return this->dataType().asVariableLengthIntegerType();
    }

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
class VariableLengthSignedIntegerElement :
    public VariableLengthIntegerElement
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
        VariableLengthSignedIntegerElement {Kind::VARIABLE_LENGTH_SIGNED_INTEGER}
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
class VariableLengthUnsignedIntegerElement :
    public VariableLengthIntegerElement
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
        VariableLengthUnsignedIntegerElement {Kind::VARIABLE_LENGTH_UNSIGNED_INTEGER}
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
    Variable-length signed enumeration element.

@ingroup elems
*/
class VariableLengthSignedEnumerationElement final :
    public VariableLengthSignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariableLengthSignedEnumerationElement() :
        VariableLengthSignedIntegerElement {Kind::VARIABLE_LENGTH_SIGNED_ENUMERATION}
    {
    }

public:
    /// Variable-length signed enumeration type.
    const VariableLengthSignedEnumerationType& type() const noexcept
    {
        return this->dataType().asVariableLengthSignedEnumerationType();
    }

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

/*!
@brief
    Variable-length unsigned enumeration element.

@ingroup elems
*/
class VariableLengthUnsignedEnumerationElement final :
    public VariableLengthUnsignedIntegerElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit VariableLengthUnsignedEnumerationElement() :
        VariableLengthUnsignedIntegerElement {Kind::VARIABLE_LENGTH_UNSIGNED_ENUMERATION}
    {
    }

public:
    /// Variable-length unsigned enumeration type.
    const VariableLengthUnsignedEnumerationType& type() const noexcept
    {
        return this->dataType().asVariableLengthUnsignedEnumerationType();
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

The next SubstringElement elements before the next
NullTerminatedStringEndElement are consecutive substrings of this
beginning null-terminated string.

@sa SubstringElement
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
        BeginningElement {Kind::NULL_TERMINATED_STRING_BEGINNING}
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
        EndElement {Kind::NULL_TERMINATED_STRING_END}
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
    Substring element.

@ingroup elems

This element can occur:

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
</dl>

begin() points to the first byte of the substring and end() points to
the byte \em after the last byte of the substring. Use size() to compute
the size of the substring \em data in bytes.

The whole substring may contain <em>zero or more</em> null bytes. If
there's a null byte between begin() and end(), the substring finishes at
this point, but for static-length and dynamic-length strings, there may
be other non-null bytes before end() which are still part of the data
stream. Knowing this:

- Use stringEnd() to get the end of the null-terminated substring
  (the first null byte or end() if none).

- Use stringSize() to get the size of the null-terminated substring.

- Use string() to get a string containing the text data of
  the null-terminate substring.

- If available, use stringView() to get a string view containing the
  text data of the null-terminated substring.
*/
class SubstringElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit SubstringElement() :
        Element {Kind::SUBSTRING}
    {
    }

public:
    /*!
    @brief
        Beginning of the data of this substring (\em not necessarily
        null-terminated).
    */
    const char *begin() const noexcept
    {
        return _begin;
    }

    /*!
    @brief
        End of the data of this substring (points to the byte \em after
        the last byte of the substring).

    Use stringEnd() to get the end of the null-terminated substring.
    */
    const char *end() const noexcept
    {
        return _end;
    }

    /*!
    @brief
        End of this null-terminated substring (points to either the
        first null byte, or is end() if none).
    */
    const char *stringEnd() const noexcept
    {
        return std::find(_begin, _end, '\0');
    }

    /*!
    @brief
        Size of this substring (bytes), including null characters and
        characters after that, if any.

    Use stringSize() to get the size of this null-terminated string,
    excluding any terminating null character.
    */
    Size size() const noexcept
    {
        return _end - _begin;
    }

    /*!
    @brief
        Size of this null-terminated substring (bytes), excluding any
        terminating null character.
    */
    Size stringSize() const noexcept
    {
        return this->stringEnd() - _begin;
    }

    /*!
    @brief
        String containing the text data (between begin() and
        stringEnd()) of this substring.
    */
    std::string string() const
    {
        return {_begin, this->stringEnd()};
    }

#ifdef __cpp_lib_string_view
    /*!
    @brief
        String view wrapping the text data (between begin() and
        stringEnd()) of this substring.
    */
    std::string_view stringView() const
    {
        return {_begin, this->stringSize()};
    }
#endif

    void accept(ElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

private:
    const char *_begin = nullptr;
    const char *_end = nullptr;
};

/*!
@brief
    BLOB section element.

@ingroup elems

This element can occur:

<dl>
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

begin() points to the first byte of the BLOB section and end() points to
the byte \em after the last byte of the BLOB section. Use size() to
compute the size of the BLOB section.
*/
class BlobSectionElement final :
    public Element
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit BlobSectionElement() :
        Element {Kind::BLOB_SECTION}
    {
    }

public:
    /// Beginning of the data of this BLOB section.
    const std::uint8_t *begin() const noexcept
    {
        return _begin;
    }

    /// End of the data of this BLOB section.
    const std::uint8_t *end() const noexcept
    {
        return _end;
    }

    /// Size (bytes) of this BLOB section.
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
        ArrayBeginningElement {Kind::STATIC_LENGTH_ARRAY_BEGINNING}
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
        ArrayEndElement {Kind::STATIC_LENGTH_ARRAY_END}
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
        ArrayBeginningElement {Kind::DYNAMIC_LENGTH_ARRAY_BEGINNING}
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
        ArrayEndElement {Kind::DYNAMIC_LENGTH_ARRAY_END}
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

The next SubstringElement elements before the next
StaticLengthStringEndElement are consecutive substrings of this
beginning static-length string.

@sa SubstringElement
@sa StaticLengthStringEndElement
*/
class StaticLengthStringBeginningElement final :
    public NonNullTerminatedStringBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthStringBeginningElement() :
        NonNullTerminatedStringBeginningElement {Kind::STATIC_LENGTH_STRING_BEGINNING}
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

@sa SubstringElement
@sa StaticLengthStringBeginningElement
*/
class StaticLengthStringEndElement final :
    public NonNullTerminatedStringEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthStringEndElement() :
        NonNullTerminatedStringEndElement {Kind::STATIC_LENGTH_STRING_END}
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

The next SubstringElement elements before the next
DynamicLengthStringEndElement are consecutive substrings of this
beginning dynamic-length string.

@sa SubstringElement
@sa DynamicLengthStringEndElement
*/
class DynamicLengthStringBeginningElement final :
    public NonNullTerminatedStringBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthStringBeginningElement() :
        NonNullTerminatedStringBeginningElement {Kind::DYNAMIC_LENGTH_STRING_BEGINNING}
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

@sa SubstringElement
@sa DynamicLengthStringBeginningElement
*/
class DynamicLengthStringEndElement final :
    public NonNullTerminatedStringEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthStringEndElement() :
        NonNullTerminatedStringEndElement {Kind::DYNAMIC_LENGTH_STRING_END}
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

The next BlobSectionElement elements before the next
StaticLengthBlobEndElement are consecutive BLOB sections of this
beginning static-length BLOB.

@sa BlobSectionElement
@sa StaticLengthBlobEndElement
*/
class StaticLengthBlobBeginningElement final :
    public BlobBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthBlobBeginningElement() :
        BlobBeginningElement {Kind::STATIC_LENGTH_BLOB_BEGINNING}
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

@sa BlobSectionElement
@sa StaticLengthBlobEndElement
*/
class StaticLengthBlobEndElement final :
    public BlobEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit StaticLengthBlobEndElement() :
        BlobEndElement {Kind::STATIC_LENGTH_BLOB_END}
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

The next BlobSectionElement elements before the next
DynamicLengthBlobEndElement are consecutive BLOB sections of this
beginning dynamic-length BLOB.

@sa BlobSectionElement
@sa DynamicLengthBlobEndElement
*/
class DynamicLengthBlobBeginningElement final :
    public BlobBeginningElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthBlobBeginningElement() :
        BlobBeginningElement {Kind::DYNAMIC_LENGTH_BLOB_BEGINNING}
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

@sa BlobSectionElement
@sa DynamicLengthBlobEndElement
*/
class DynamicLengthBlobEndElement final :
    public BlobEndElement
{
    friend class internal::Vm;
    friend class internal::VmPos;

private:
    explicit DynamicLengthBlobEndElement() :
        BlobEndElement {Kind::DYNAMIC_LENGTH_BLOB_END}
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
        BeginningElement {Kind::STRUCTURE_BEGINNING}
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
        EndElement {Kind::STRUCTURE_END}
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
                                                      Element::Kind::VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING>
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
                                                Element::Kind::VARIANT_WITH_UNSIGNED_INTEGER_SELECTOR_END>
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
                                                      Element::Kind::VARIANT_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING>
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
                                                Element::Kind::VARIANT_WITH_SIGNED_INTEGER_SELECTOR_END>
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
        OptionalBeginningElement {Element::Kind::OPTIONAL_WITH_BOOLEAN_SELECTOR_BEGINNING}
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
        OptionalEndElement {Element::Kind::OPTIONAL_WITH_BOOLEAN_SELECTOR_END}
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
                                                       Element::Kind::OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_BEGINNING>
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
                                                 Element::Kind::OPTIONAL_WITH_UNSIGNED_INTEGER_SELECTOR_END>
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
                                                       Element::Kind::OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_BEGINNING>
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
                                                 Element::Kind::OPTIONAL_WITH_SIGNED_INTEGER_SELECTOR_END>
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

inline const BlobSectionElement& Element::asBlobSectionElement() const noexcept
{
    return static_cast<const BlobSectionElement&>(*this);
}

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

inline const FixedLengthBooleanElement& Element::asFixedLengthBooleanElement() const noexcept
{
    return static_cast<const FixedLengthBooleanElement&>(*this);
}

inline const FixedLengthFloatingPointNumberElement& Element::asFixedLengthFloatingPointNumberElement() const noexcept
{
    return static_cast<const FixedLengthFloatingPointNumberElement&>(*this);
}

inline const FixedLengthSignedEnumerationElement& Element::asFixedLengthSignedEnumerationElement() const noexcept
{
    return static_cast<const FixedLengthSignedEnumerationElement&>(*this);
}

inline const FixedLengthSignedIntegerElement& Element::asFixedLengthSignedIntegerElement() const noexcept
{
    return static_cast<const FixedLengthSignedIntegerElement&>(*this);
}

inline const FixedLengthUnsignedEnumerationElement& Element::asFixedLengthUnsignedEnumerationElement() const noexcept
{
    return static_cast<const FixedLengthUnsignedEnumerationElement&>(*this);
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

inline const SubstringElement& Element::asSubstringElement() const noexcept
{
    return static_cast<const SubstringElement&>(*this);
}

inline const MetadataStreamUuidElement& Element::asMetadataStreamUuidElement() const noexcept
{
    return static_cast<const MetadataStreamUuidElement&>(*this);
}

inline const VariableLengthSignedEnumerationElement& Element::asVariableLengthSignedEnumerationElement() const noexcept
{
    return static_cast<const VariableLengthSignedEnumerationElement&>(*this);
}

inline const VariableLengthSignedIntegerElement& Element::asVariableLengthSignedIntegerElement() const noexcept
{
    return static_cast<const VariableLengthSignedIntegerElement&>(*this);
}

inline const VariableLengthUnsignedEnumerationElement& Element::asVariableLengthUnsignedEnumerationElement() const noexcept
{
    return static_cast<const VariableLengthUnsignedEnumerationElement&>(*this);
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

#endif // _YACTFR_ELEM_HPP
