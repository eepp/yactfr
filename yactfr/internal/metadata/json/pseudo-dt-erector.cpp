/*
 * Copyright (C) 2022-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <sstream>

#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/fl-bit-map-type.hpp>
#include <yactfr/metadata/fl-bool-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/vl-int-type.hpp>
#include <yactfr/metadata/nt-str-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/dl-blob-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/opt-type.hpp>
#include <yactfr/text-parse-error.hpp>
#include <yactfr/metadata/aliases.hpp>

#include "json-val.hpp"
#include "pseudo-dt-erector.hpp"
#include "ctf-2-json-strs.hpp"
#include "ctf-2-json-utils.hpp"

namespace yactfr {
namespace internal {

template <typename DtT, typename... ArgTs>
PseudoDt::Up createPseudoScalarDtWrapper(const JsonVal& jsonVal, ArgTs&&... args)
{
    auto dt = std::make_unique<const DtT>(std::forward<ArgTs>(args)...);

    return std::make_unique<PseudoScalarDtWrapper>(std::move(dt), jsonVal.loc());
}

template <typename ValT, bool ValidatePrecondsV = true>
IntegerRangeSet<ValT, ValidatePrecondsV> intRangesFromArray(const JsonArrayVal& jsonArrayVal)
{
    using Ranges = IntegerRangeSet<ValT, ValidatePrecondsV>;

    std::set<typename Ranges::Range> ranges;

    for (auto& jsonRange : jsonArrayVal) {
        auto& jsonRangeArray = jsonRange->asArray();

        ranges.insert(typename Ranges::Range {
            rawIntValFromJsonIntVal<ValT>(jsonRangeArray[0]),
            rawIntValFromJsonIntVal<ValT>(jsonRangeArray[1])
        });
    }

    return Ranges {std::move(ranges)};
}

template <typename MappingsOrFlagsT>
MappingsOrFlagsT intTypeMappingsOrFlagsOfDt(const JsonObjVal& jsonDt, const char * const propName)
{
    using RangeValueT = typename MappingsOrFlagsT::mapped_type::Value;

    MappingsOrFlagsT mappingsOrFlags;
    const auto jsonMappingsOrFlags = jsonDt[propName];

    if (!jsonMappingsOrFlags) {
        return mappingsOrFlags;
    }

    for (auto& keyJsonIntRangesPair : jsonMappingsOrFlags->asObj()) {
        mappingsOrFlags.insert(std::make_pair(keyJsonIntRangesPair.first,
                                              intRangesFromArray<RangeValueT>(keyJsonIntRangesPair.second->asArray())));
    }

    return mappingsOrFlags;
}

template <typename IntTypeT>
typename IntTypeT::Mappings intTypeMappingsOfIntType(const JsonObjVal& jsonDt)
{
    return intTypeMappingsOrFlagsOfDt<typename IntTypeT::Mappings>(jsonDt, strs::mappings);
}

namespace {

UnsignedIntegerTypeRoleSet uIntTypeRolesOfUIntType(const JsonObjVal& jsonDt)
{
    UnsignedIntegerTypeRoleSet roles;
    const auto jsonRolesVal = jsonDt[strs::roles];

    if (!jsonRolesVal) {
        return roles;
    }

    for (auto& jsonRoleVal : jsonRolesVal->asArray()) {
        auto& roleName = *jsonRoleVal->asStr();

        if (roleName == strs::dscId) {
            roles.insert(UnsignedIntegerTypeRole::DataStreamTypeId);
        } else if (roleName == strs::dsId) {
            roles.insert(UnsignedIntegerTypeRole::DataStreamId);
        } else if (roleName == strs::pktMagicNumber) {
            roles.insert(UnsignedIntegerTypeRole::PacketMagicNumber);
        } else if (roleName == strs::defClkTs) {
            roles.insert(UnsignedIntegerTypeRole::DefaultClockTimestamp);
        } else if (roleName == strs::discErCounterSnap) {
            roles.insert(UnsignedIntegerTypeRole::DiscardedEventRecordCounterSnapshot);
        } else if (roleName == strs::pktContentLen) {
            roles.insert(UnsignedIntegerTypeRole::PacketContentLength);
        } else if (roleName == strs::pktTotalLen) {
            roles.insert(UnsignedIntegerTypeRole::PacketTotalLength);
        } else if (roleName == strs::pktEndDefClkTs) {
            roles.insert(UnsignedIntegerTypeRole::PacketEndDefaultClockTimestamp);
        } else if (roleName == strs::pktSeqNum) {
            roles.insert(UnsignedIntegerTypeRole::PacketSequenceNumber);
        } else {
            assert(roleName == strs::ercId);
            roles.insert(UnsignedIntegerTypeRole::EventRecordTypeId);
        }
    }

    return roles;
}

PseudoDt::Up pseudoDtFromFlUIntType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                    const unsigned int len, const ByteOrder bo, const BitOrder bio,
                                    const unsigned int align, const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = intTypeMappingsOfIntType<FixedLengthUnsignedIntegerType>(jsonDt);

    // roles
    auto roles = uIntTypeRolesOfUIntType(jsonDt);

    return createPseudoScalarDtWrapper<FixedLengthUnsignedIntegerType>(jsonDt, align, len, bo, bio,
                                                                       prefDispBase,
                                                                       std::move(mappings),
                                                                       std::move(attrs),
                                                                       std::move(roles));
}

PseudoDt::Up pseudoDtFromFlSIntType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                    const unsigned int len, const ByteOrder bo, const BitOrder bio,
                                    const unsigned int align, const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = intTypeMappingsOfIntType<FixedLengthSignedIntegerType>(jsonDt);

    return createPseudoScalarDtWrapper<FixedLengthSignedIntegerType>(jsonDt, align, len, bo, bio,
                                                                     prefDispBase,
                                                                     std::move(mappings),
                                                                     std::move(attrs));
}

PseudoDt::Up pseudoDtFromFlIntType(const JsonObjVal& jsonDt, const std::string& type,
                                   MapItem::Up attrs, const unsigned int len, const ByteOrder bo,
                                   const BitOrder bio, const unsigned int align)
{
    // preferred display base
    const auto prefDispBase = static_cast<DisplayBase>(jsonDt.getRawVal(strs::prefDispBase, 10ULL));

    if (type == strs::flUInt) {
        return pseudoDtFromFlUIntType(jsonDt, std::move(attrs), len, bo, bio, align, prefDispBase);
    } else {
        assert(type == strs::flSInt);
        return pseudoDtFromFlSIntType(jsonDt, std::move(attrs), len, bo, bio, align, prefDispBase);
    }
}

PseudoDt::Up pseudoDtFromFlBitMapType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                      const unsigned int len, const ByteOrder bo,
                                      const BitOrder bio, const unsigned int align)
{
    auto flags = intTypeMappingsOrFlagsOfDt<FixedLengthBitMapType::Flags>(jsonDt, strs::flags);

    return createPseudoScalarDtWrapper<FixedLengthBitMapType>(jsonDt, align, len, bo,
                                                              std::move(flags), bio,
                                                              std::move(attrs));
}

PseudoDt::Up pseudoDtFromFlBoolType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                    const unsigned int len, const ByteOrder bo, const BitOrder bio,
                                    const unsigned int align)
{
    return createPseudoScalarDtWrapper<FixedLengthBooleanType>(jsonDt, align, len, bo, bio,
                                                               std::move(attrs));
}

PseudoDt::Up pseudoDtFromFlFloatType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                     const unsigned int len, const ByteOrder bo,
                                     const BitOrder bio, const unsigned int align)
{
    return createPseudoScalarDtWrapper<FixedLengthFloatingPointNumberType>(jsonDt, align, len, bo,
                                                                           bio, std::move(attrs));
}

PseudoDt::Up pseudoDtFromFlBitArrayType(const JsonObjVal& jsonDt, const std::string& type,
                                        MapItem::Up attrs)
{
    // length
    const auto len = jsonDt.getRawUIntVal(strs::len);

    // byte order
    const auto bo = jsonDt.getRawStrVal(strs::bo) == strs::le ? ByteOrder::Little : ByteOrder::Big;

    // bit order
    const auto bio = [&jsonDt, &bo] {
        if (const auto jsonBo = jsonDt[strs::bio]) {
            return *jsonBo->asStr() == strs::ftl ? BitOrder::FirstToLast : BitOrder::LastToFirst;
        } else {
            if (bo == ByteOrder::Big) {
                return BitOrder::LastToFirst;
            } else {
                return BitOrder::FirstToLast;
            }
        }
    }();

    // alignment
    const auto align = jsonDt.getRawVal(strs::align, 1ULL);

    if (type == strs::flBitArray) {
        return createPseudoScalarDtWrapper<FixedLengthBitArrayType>(jsonDt, align, len, bo, bio,
                                                                    std::move(attrs));
    } else if (type == strs::flBitMap) {
        return pseudoDtFromFlBitMapType(jsonDt, std::move(attrs), len, bo, bio, align);
    } else if (type == strs::flBool) {
        return pseudoDtFromFlBoolType(jsonDt, std::move(attrs), len, bo, bio, align);
    } else if (type == strs::flUInt || type == strs::flSInt) {
        return pseudoDtFromFlIntType(jsonDt, type, std::move(attrs), len, bo, bio, align);
    } else {
        assert(type == strs::flFloat);
        return pseudoDtFromFlFloatType(jsonDt, std::move(attrs), len, bo, bio, align);
    }
}

PseudoDt::Up pseudoDtFromVlUIntType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                    const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = intTypeMappingsOfIntType<VariableLengthUnsignedIntegerType>(jsonDt);

    // roles
    auto roles = uIntTypeRolesOfUIntType(jsonDt);

    return createPseudoScalarDtWrapper<VariableLengthUnsignedIntegerType>(jsonDt, prefDispBase,
                                                                          std::move(mappings),
                                                                          std::move(attrs),
                                                                          std::move(roles));
}

PseudoDt::Up pseudoDtFromVlSIntType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                    const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = intTypeMappingsOfIntType<VariableLengthSignedIntegerType>(jsonDt);

    return createPseudoScalarDtWrapper<VariableLengthSignedIntegerType>(jsonDt, prefDispBase,
                                                                        std::move(mappings),
                                                                        std::move(attrs));
}

PseudoDt::Up pseudoDtFromVlIntType(const JsonObjVal& jsonDt, const std::string& type,
                                   MapItem::Up attrs)
{
    // preferred display base
    const auto prefDispBase = static_cast<DisplayBase>(jsonDt.getRawVal(strs::prefDispBase, 10ULL));

    if (type == strs::vlUInt) {
        return pseudoDtFromVlUIntType(jsonDt, std::move(attrs), prefDispBase);
    } else {
        assert(type == strs::vlSInt);
        return pseudoDtFromVlSIntType(jsonDt, std::move(attrs), prefDispBase);
    }
}

StringEncoding strEncodingOfStrType(const JsonObjVal& jsonDt) noexcept
{
    const auto jsonEncodingVal = jsonDt[strs::encoding];

    if (!jsonEncodingVal) {
        return StringEncoding::Utf8;
    }

    auto& jsonEncodingStrVal = *jsonEncodingVal->asStr();

    if (jsonEncodingStrVal == strs::utf8) {
        return StringEncoding::Utf8;
    } else if (jsonEncodingStrVal == strs::utf16Be) {
        return StringEncoding::Utf16Be;
    } else if (jsonEncodingStrVal == strs::utf16Le) {
        return StringEncoding::Utf16Le;
    } else if (jsonEncodingStrVal == strs::utf32Be) {
        return StringEncoding::Utf32Be;
    } else {
        assert(jsonEncodingStrVal == strs::utf32Le);
        return StringEncoding::Utf32Le;
    }
}

PseudoDt::Up pseudoDtFromNtStrType(const JsonObjVal& jsonDt, MapItem::Up attrs)
{
    return createPseudoScalarDtWrapper<NullTerminatedStringType>(jsonDt, strEncodingOfStrType(jsonDt),
                                                                 std::move(attrs));
}

PseudoDataLoc pseudoDataLocOfDynDt(const JsonObjVal& jsonDt, const std::string& propName)
{
    auto& jsonLocVal = jsonDt[propName]->asObj();
    boost::optional<Scope> scope;
    const auto jsonOrigVal = jsonLocVal[strs::orig];

    if (jsonOrigVal) {
        // absolute
        scope = [jsonOrigVal] {
            auto& scopeName = *jsonOrigVal->asStr();

            if (scopeName == strs::pktHeader) {
                return Scope::PacketHeader;
            } else if (scopeName == strs::pktCtx) {
                return Scope::PacketContext;
            } else if (scopeName == strs::erHeader) {
                return Scope::EventRecordHeader;
            } else if (scopeName == strs::erCommonCtx) {
                return Scope::EventRecordCommonContext;
            } else if (scopeName == strs::erSpecCtx) {
                return Scope::EventRecordSpecificContext;
            } else {
                assert(scopeName == strs::erPayload);
                return Scope::EventRecordPayload;
            }
        }();
    }

    auto& jsonPathVal = jsonLocVal[strs::path]->asArray();
    PseudoDataLoc::PathElems pathElems;

    std::transform(jsonPathVal.begin(), jsonPathVal.end(), std::back_inserter(pathElems),
                   [](const auto& jsonPathElem) -> boost::optional<std::string> {
        if (jsonPathElem->isNull()) {
            return boost::none;
        } else {
            return *jsonPathElem->asStr();
        }
    });

    return PseudoDataLoc {
        scope ? PseudoDataLoc::Kind::Abs : PseudoDataLoc::Kind::Rel2,
        scope, std::move(pathElems), jsonLocVal.loc()
    };
}

PseudoDt::Up pseudoDtFromDlStrType(const JsonObjVal& jsonDt, MapItem::Up attrs)
{
    /*
     * Returning a pseudo dynamic-length array type having a pseudo
     * fixed-length unsigned integer type with an encoding for a
     * dynamic-length string type to accomodate the common pseudo type
     * API which also serves the CTF 1.8 use case.
     *
     * dtFromPseudoRootDt() will convert this pseudo dynamic-length
     * array type to a `DynamicLengthStringType` instance.
     */
    auto pseudoElemType = std::make_unique<PseudoFlUIntType>(8, 8, ByteOrder::Big,
                                                             BitOrder::LastToFirst,
                                                             DisplayBase::Decimal,
                                                             FixedLengthUnsignedIntegerType::Mappings {},
                                                             strEncodingOfStrType(jsonDt));

    return std::make_unique<PseudoDlArrayType>(pseudoDataLocOfDynDt(jsonDt, strs::lenFieldLoc),
                                               std::move(pseudoElemType), std::move(attrs),
                                               jsonDt.loc());
}

PseudoDt::Up pseudoDtFromSlStrType(const JsonObjVal& jsonDt, MapItem::Up attrs)
{
    return createPseudoScalarDtWrapper<StaticLengthStringType>(jsonDt,
                                                               jsonDt.getRawUIntVal(strs::len),
                                                               strEncodingOfStrType(jsonDt),
                                                               std::move(attrs));
}

PseudoDt::Up pseudoDtFromNonNtStrType(const JsonObjVal& jsonDt, const std::string& type,
                                      MapItem::Up attrs)
{
    if (type == strs::slStr) {
        return pseudoDtFromSlStrType(jsonDt, std::move(attrs));
    } else {
        assert(type == strs::dlStr);
        return pseudoDtFromDlStrType(jsonDt, std::move(attrs));
    }
}

PseudoDt::Up pseudoDtFromDlBlobType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                    const char * const mediaType)
{
    return std::make_unique<PseudoDlBlobType>(pseudoDataLocOfDynDt(jsonDt, strs::lenFieldLoc),
                                              std::string {mediaType}, std::move(attrs),
                                              jsonDt.loc());
}

PseudoDt::Up pseudoDtFromSlBlobType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                    const char * const mediaType)
{
    // has metadata stream UUID role?
    bool hasMetadataStreamUuidRole = false;
    const auto jsonRolesVal = jsonDt[strs::roles];

    if (jsonRolesVal && jsonRolesVal->asArray().size() > 0) {
        hasMetadataStreamUuidRole = true;
    }

    return createPseudoScalarDtWrapper<StaticLengthBlobType>(jsonDt,
                                                             jsonDt.getRawUIntVal(strs::len),
                                                             mediaType, std::move(attrs),
                                                             hasMetadataStreamUuidRole);
}

PseudoDt::Up pseudoDtFromBlobType(const JsonObjVal& jsonDt, const std::string& type,
                                  MapItem::Up attrs)
{
    // media type
    const auto mediaType = jsonDt.getRawVal(strs::mediaType, strs::appOctetStream);

    if (type == strs::slBlob) {
        return pseudoDtFromSlBlobType(jsonDt, std::move(attrs), mediaType);
    } else {
        assert(type == strs::dlBlob);
        return pseudoDtFromDlBlobType(jsonDt, std::move(attrs), mediaType);
    }
}

} // namespace

PseudoDt::Up PseudoDtErector::_pseudoDtFromDlArrayType(const JsonObjVal& jsonDt,
                                                       MapItem::Up attrs,
                                                       const unsigned int minAlign)
{
    return std::make_unique<PseudoDlArrayType>(minAlign,
                                               pseudoDataLocOfDynDt(jsonDt, strs::lenFieldLoc),
                                               this->pseudoDtOfJsonObj(jsonDt, strs::elemFc),
                                               std::move(attrs), jsonDt.loc());
}

PseudoDt::Up PseudoDtErector::_pseudoDtFromSlArrayType(const JsonObjVal& jsonDt,
                                                       MapItem::Up attrs,
                                                       unsigned int minAlign)
{
    return std::make_unique<PseudoSlArrayType>(minAlign, jsonDt.getRawUIntVal(strs::len),
                                               this->pseudoDtOfJsonObj(jsonDt, strs::elemFc),
                                               std::move(attrs), jsonDt.loc());
}

PseudoDt::Up PseudoDtErector::_pseudoDtFromArrayType(const JsonObjVal& jsonDt,
                                                     const std::string& type,
                                                     MapItem::Up attrs)
{
    // minimum alignment
    const auto minAlign = jsonDt.getRawVal(strs::minAlign, 1ULL);

    try {
        if (type == strs::slArray) {
            return this->_pseudoDtFromSlArrayType(jsonDt, std::move(attrs), minAlign);
        } else {
            assert(type == strs::dlArray);
            return this->_pseudoDtFromDlArrayType(jsonDt, std::move(attrs), minAlign);
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In array type:", jsonDt.loc());
        throw;
    }
}

PseudoDt::Up PseudoDtErector::_pseudoDtFromStructType(const JsonObjVal& jsonDt,
                                                      MapItem::Up attrs)
{
    // member types
    PseudoNamedDts pseudoMemberTypes;
    const auto jsonMemberClss = jsonDt[strs::memberClss];

    if (jsonMemberClss) {
        for (auto& jsonMemberCls : jsonMemberClss->asArray()) {
            auto& jsonMemberClsObj = jsonMemberCls->asObj();
            auto& name = jsonMemberClsObj.getRawStrVal(strs::name);
            auto pseudoDt = [this, &name, &jsonMemberCls, &jsonMemberClsObj] {
                try {
                    return this->pseudoDtOfJsonObj(jsonMemberClsObj, strs::fc);
                } catch (TextParseError& exc) {
                    std::ostringstream ss;

                    ss << "In structure member type `" << name << "`:";
                    appendMsgToTextParseError(exc, ss.str(), jsonMemberCls->loc());
                    throw;
                }
            }();

            pseudoMemberTypes.push_back(std::make_unique<PseudoNamedDt>(std::move(name),
                                                                        std::move(pseudoDt),
                                                                        attrsOfObj(jsonMemberClsObj)));
        }
    }

    return std::make_unique<PseudoStructType>(jsonDt.getRawVal(strs::minAlign, 1ULL),
                                              std::move(pseudoMemberTypes), std::move(attrs),
                                              jsonDt.loc());
}

namespace {

PseudoDt::Up pseudoDtFromOptWithIntSelType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                           PseudoDataLoc&& pseudoSelLoc, PseudoDt::Up pseudoDt,
                                           const JsonArrayVal& jsonSelFieldRanges)
{
    return std::make_unique<PseudoOptWithIntSelType>(std::move(pseudoDt), std::move(pseudoSelLoc),
                                                     intRangesFromArray<unsigned long long, false>(jsonSelFieldRanges),
                                                     std::move(attrs), jsonDt.loc());
}

PseudoDt::Up pseudoDtFromOptWithBoolSelType(const JsonObjVal& jsonDt, MapItem::Up attrs,
                                            PseudoDataLoc&& pseudoSelLoc, PseudoDt::Up pseudoDt)
{
    return std::make_unique<PseudoOptWithBoolSelType>(std::move(pseudoDt), std::move(pseudoSelLoc),
                                                      std::move(attrs), jsonDt.loc());
}

} // namespace

PseudoDt::Up PseudoDtErector::_pseudoDtFromOptType(const JsonObjVal& jsonDt, MapItem::Up attrs)
{
    // selector location
    auto pseudoSelLoc = pseudoDataLocOfDynDt(jsonDt, strs::selFieldLoc);

    // data type
    auto pseudoDt = [this, &jsonDt] {
        try {
            return this->pseudoDtOfJsonObj(jsonDt, strs::fc);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "In optional type:", jsonDt.loc());
            throw;
        }
    }();

    // selector field ranges (presence indicates which kind of optional FC)
    const auto jsonSelFieldRanges = jsonDt[strs::selFieldRanges];

    if (jsonSelFieldRanges) {
        return pseudoDtFromOptWithIntSelType(jsonDt, std::move(attrs), std::move(pseudoSelLoc),
                                             std::move(pseudoDt), jsonSelFieldRanges->asArray());
    } else {
        return pseudoDtFromOptWithBoolSelType(jsonDt, std::move(attrs),
                                              std::move(pseudoSelLoc), std::move(pseudoDt));
    }
}

PseudoDt::Up PseudoDtErector::_pseudoDtFromVarType(const JsonObjVal& jsonDt, MapItem::Up attrs)
{
    // options and selector ranges
    PseudoNamedDts pseudoOpts;
    PseudoVarWithIntRangesType::RangeSets selRangeSets;

    for (auto& jsonOpt : jsonDt[strs::opts]->asArray()) {
        auto& jsonOptObj = jsonOpt->asObj();
        auto intRanges = intRangesFromArray<unsigned long long, false>(jsonOptObj[strs::selFieldRanges]->asArray());
        auto pseudoDt = [this, &pseudoOpts, &jsonOptObj] {
            try {
                return this->pseudoDtOfJsonObj(jsonOptObj, strs::fc);
            } catch (TextParseError& exc) {
                std::ostringstream ss;

                ss << "In variant type option #" << (pseudoOpts.size() + 1) << ":";
                appendMsgToTextParseError(exc, ss.str(), jsonOptObj.loc());
                throw;
            }
        }();

        selRangeSets.push_back(std::move(intRanges));
        pseudoOpts.push_back(std::make_unique<PseudoNamedDt>(optStrOfObj(jsonOptObj, strs::name),
                                                             std::move(pseudoDt),
                                                             attrsOfObj(jsonOptObj)));
    }

    return std::make_unique<PseudoVarWithIntRangesType>(pseudoDataLocOfDynDt(jsonDt,
                                                                             strs::selFieldLoc),
                                                        std::move(pseudoOpts),
                                                        std::move(selRangeSets),
                                                        std::move(attrs), jsonDt.loc());
}

PseudoDt::Up PseudoDtErector::pseudoDtOfJsonObj(const JsonObjVal& jsonObjVal,
                                                const std::string& propName)
{
    const auto jsonDtVal = jsonObjVal[propName];

    if (!jsonDtVal) {
        return nullptr;
    }

    if (jsonDtVal->isStr()) {
        // data type alias
        try {
            return this->_aliasedPseudoDt(*jsonDtVal->asStr(), jsonDtVal->loc());
        } catch (TextParseError& exc) {
            std::ostringstream ss;

            ss << "In object property `" << propName << "`:";
            appendMsgToTextParseError(exc, ss.str(), jsonDtVal->loc());
            throw;
        }
    }

    assert(jsonDtVal->isObj());

    auto& jsonDtObj = jsonDtVal->asObj();

    // get type
    auto& type = jsonDtObj.getRawStrVal(strs::type);

    // attributes
    auto attrs = attrsOfObj(jsonDtObj);

    // defer to specific method
    if (type == strs::flBitArray ||
            type == strs::flBitMap ||
            type == strs::flBool ||
            type == strs::flUInt || type == strs::flSInt ||
            type == strs::flFloat) {
        return pseudoDtFromFlBitArrayType(jsonDtObj, type, std::move(attrs));
    } else if (type == strs::vlUInt || type == strs::vlSInt) {
        return pseudoDtFromVlIntType(jsonDtObj, type, std::move(attrs));
    } else if (type == strs::ntStr) {
        return pseudoDtFromNtStrType(jsonDtObj, std::move(attrs));
    } else if (type == strs::slStr || type == strs::dlStr) {
        return pseudoDtFromNonNtStrType(jsonDtObj, type, std::move(attrs));
    } else if (type == strs::slBlob || type == strs::dlBlob) {
        return pseudoDtFromBlobType(jsonDtObj, type, std::move(attrs));
    } else if (type == strs::slArray || type == strs::dlArray) {
        return this->_pseudoDtFromArrayType(jsonDtObj, type, std::move(attrs));
    } else if (type == strs::structure) {
        return this->_pseudoDtFromStructType(jsonDtObj, std::move(attrs));
    } else if (type == strs::opt) {
        return this->_pseudoDtFromOptType(jsonDtObj, std::move(attrs));
    } else {
        assert(type == strs::var);
        return this->_pseudoDtFromVarType(jsonDtObj, std::move(attrs));
    }
}

PseudoDt::Up PseudoDtErector::_aliasedPseudoDt(const std::string& name,
                                               const TextLocation& textLoc)
{
    const auto it = _aliases.find(name);

    if (it == _aliases.end()) {
        std::ostringstream ss;

        ss << "Cannot find data type alias `" << name << "`.";

        throwTextParseError(ss.str(), textLoc);
    }

    return it->second->clone();
}

void PseudoDtErector::addAlias(const std::string& name, PseudoDt::Up pseudoDt,
                               const TextLocation& nameLoc)
{
    // check for duplicate
    {
        const auto it = _aliases.find(name);

        if (it != _aliases.end()) {
            std::ostringstream ss;

            ss << "Duplicate data type alias named `" << name << "`.";
            throwTextParseError(ss.str(), nameLoc);
        }
    }

    _aliases.emplace(name, std::move(pseudoDt));
}

} // namespace internal
} // namespace yactfr
