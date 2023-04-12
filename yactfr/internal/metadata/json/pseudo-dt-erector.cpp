/*
 * Copyright (C) 2022-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>
#include <sstream>

#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/fl-bool-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/vl-int-type.hpp>
#include <yactfr/metadata/vl-enum-type.hpp>
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
PseudoDt::UP createPseudoScalarDtWrapper(const JsonVal& jsonVal, ArgTs&&... args)
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

template <typename EnumTypeT>
typename EnumTypeT::Mappings enumTypeMappingsOfEnumType(const JsonObjVal& jsonDt)
{
    typename EnumTypeT::Mappings mappings;
    const auto jsonMappings = jsonDt[strs::MAPPINGS];

    if (!jsonMappings) {
        return mappings;
    }

    for (auto& keyJsonIntRangesPair : jsonMappings->asObj()) {
        mappings.insert(std::make_pair(keyJsonIntRangesPair.first,
                                       intRangesFromArray<typename EnumTypeT::Value>(keyJsonIntRangesPair.second->asArray())));
    }

    return mappings;
}

static PseudoDt::UP pseudoDtFromFlUEnumType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                            const unsigned int len, const ByteOrder bo,
                                            const unsigned int align,
                                            const DisplayBase prefDispBase,
                                            UnsignedIntegerTypeRoleSet&& roles)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumType<FixedLengthUnsignedEnumerationType>(jsonDt);

    return createPseudoScalarDtWrapper<FixedLengthUnsignedEnumerationType>(jsonDt, align, len, bo,
                                                                           std::move(mappings),
                                                                           prefDispBase,
                                                                           std::move(userAttrs),
                                                                           std::move(roles));
}

static PseudoDt::UP pseudoDtFromFlSEnumType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                            const unsigned int len, const ByteOrder bo,
                                            const unsigned int align,
                                            const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumType<FixedLengthSignedEnumerationType>(jsonDt);

    return createPseudoScalarDtWrapper<FixedLengthSignedEnumerationType>(jsonDt, align, len, bo,
                                                                         std::move(mappings),
                                                                         prefDispBase,
                                                                         std::move(userAttrs));
}

static UnsignedIntegerTypeRoleSet uIntTypeRolesOfUIntType(const JsonObjVal& jsonDt)
{
    UnsignedIntegerTypeRoleSet roles;
    const auto jsonRolesVal = jsonDt[strs::ROLES];

    if (!jsonRolesVal) {
        return roles;
    }

    for (auto& jsonRoleVal : jsonRolesVal->asArray()) {
        auto& roleName = *jsonRoleVal->asStr();

        if (roleName == strs::DSC_ID) {
            roles.insert(UnsignedIntegerTypeRole::DATA_STREAM_TYPE_ID);
        } else if (roleName == strs::DS_ID) {
            roles.insert(UnsignedIntegerTypeRole::DATA_STREAM_ID);
        } else if (roleName == strs::PKT_MAGIC_NUMBER) {
            roles.insert(UnsignedIntegerTypeRole::PACKET_MAGIC_NUMBER);
        } else if (roleName == strs::DEF_CLK_TS) {
            roles.insert(UnsignedIntegerTypeRole::DEFAULT_CLOCK_TIMESTAMP);
        } else if (roleName == strs::DISC_ER_COUNTER_SNAP) {
            roles.insert(UnsignedIntegerTypeRole::DISCARDED_EVENT_RECORD_COUNTER_SNAPSHOT);
        } else if (roleName == strs::PKT_CONTENT_LEN) {
            roles.insert(UnsignedIntegerTypeRole::PACKET_CONTENT_LENGTH);
        } else if (roleName == strs::PKT_TOTAL_LEN) {
            roles.insert(UnsignedIntegerTypeRole::PACKET_TOTAL_LENGTH);
        } else if (roleName == strs::PKT_END_DEF_CLK_TS) {
            roles.insert(UnsignedIntegerTypeRole::PACKET_END_DEFAULT_CLOCK_TIMESTAMP);
        } else if (roleName == strs::PKT_SEQ_NUM) {
            roles.insert(UnsignedIntegerTypeRole::PACKET_SEQUENCE_NUMBER);
        } else {
            assert(roleName == strs::ERC_ID);
            roles.insert(UnsignedIntegerTypeRole::EVENT_RECORD_TYPE_ID);
        }
    }

    return roles;
}

static PseudoDt::UP pseudoDtFromFlUIntType(const JsonObjVal& jsonDt, const std::string& type,
                                           MapItem::UP userAttrs, const unsigned int len,
                                           const ByteOrder bo, const unsigned int align,
                                           const DisplayBase prefDispBase)
{
    // roles
    auto roles = uIntTypeRolesOfUIntType(jsonDt);

    if (type == strs::FL_UINT) {
        return createPseudoScalarDtWrapper<FixedLengthUnsignedIntegerType>(jsonDt, align, len, bo,
                                                                           prefDispBase,
                                                                           std::move(userAttrs),
                                                                           std::move(roles));
    } else {
        assert(type == strs::FL_UENUM);
        return pseudoDtFromFlUEnumType(jsonDt, std::move(userAttrs), len, bo, align, prefDispBase,
                                       std::move(roles));
    }
}

static PseudoDt::UP pseudoDtFromFlSIntType(const JsonObjVal& jsonDt, const std::string& type,
                                           MapItem::UP userAttrs, const unsigned int len,
                                           const ByteOrder bo, const unsigned int align,
                                           const DisplayBase prefDispBase)
{
    if (type == strs::FL_SINT) {
        return createPseudoScalarDtWrapper<FixedLengthSignedIntegerType>(jsonDt, align, len, bo,
                                                                         prefDispBase,
                                                                         std::move(userAttrs));
    } else {
        assert(type == strs::FL_SENUM);
        return pseudoDtFromFlSEnumType(jsonDt, std::move(userAttrs), len, bo, align, prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromFlIntType(const JsonObjVal& jsonDt, const std::string& type,
                                          MapItem::UP userAttrs, const unsigned int len,
                                          const ByteOrder bo, const unsigned int align)
{
    // preferred display base
    const auto prefDispBase = static_cast<DisplayBase>(jsonDt.getRawVal(strs::PREF_DISP_BASE,
                                                                        10ULL));

    if (type == strs::FL_UINT || type == strs::FL_UENUM) {
        return pseudoDtFromFlUIntType(jsonDt, type, std::move(userAttrs), len, bo, align,
                                      prefDispBase);
    } else {
        assert(type == strs::FL_SINT || type == strs::FL_SENUM);
        return pseudoDtFromFlSIntType(jsonDt, type, std::move(userAttrs), len, bo, align,
                                      prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromFlBoolType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                           const unsigned int len, const ByteOrder bo,
                                           const unsigned int align)
{
    return createPseudoScalarDtWrapper<FixedLengthBooleanType>(jsonDt, align, len, bo,
                                                               std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromFlFloatType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                            const unsigned int len, const ByteOrder bo,
                                            const unsigned int align)
{
    return createPseudoScalarDtWrapper<FixedLengthFloatingPointNumberType>(jsonDt, align, len, bo,
                                                                           std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromFlBitArrayType(const JsonObjVal& jsonDt, const std::string& type,
                                               MapItem::UP userAttrs)
{
    // length
    const auto len = jsonDt.getRawUIntVal(strs::LEN);

    // byte order
    const auto bo = jsonDt.getRawStrVal(strs::BO) == strs::LE ? ByteOrder::LITTLE : ByteOrder::BIG;

    // alignment
    const auto align = jsonDt.getRawVal(strs::ALIGN, 1ULL);

    if (type == strs::FL_BIT_ARRAY) {
        return createPseudoScalarDtWrapper<FixedLengthBitArrayType>(jsonDt, align, len, bo,
                                                                    std::move(userAttrs));
    } else if (type == strs::FL_BOOL) {
        return pseudoDtFromFlBoolType(jsonDt, std::move(userAttrs), len, bo, align);
    } else if (type == strs::FL_UINT || type == strs::FL_SINT ||
            type == strs::FL_UENUM || type == strs::FL_SENUM) {
        return pseudoDtFromFlIntType(jsonDt, type, std::move(userAttrs), len, bo, align);
    } else {
        assert(type == strs::FL_FLOAT);
        return pseudoDtFromFlFloatType(jsonDt, std::move(userAttrs), len, bo, align);
    }
}

static PseudoDt::UP pseudoDtFromVlUEnumType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                            const DisplayBase prefDispBase,
                                            UnsignedIntegerTypeRoleSet&& roles)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumType<VariableLengthUnsignedEnumerationType>(jsonDt);

    return createPseudoScalarDtWrapper<VariableLengthUnsignedEnumerationType>(jsonDt,
                                                                              std::move(mappings),
                                                                              prefDispBase,
                                                                              std::move(userAttrs),
                                                                              std::move(roles));
}

static PseudoDt::UP pseudoDtFromVlSEnumType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                            const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumType<VariableLengthSignedEnumerationType>(jsonDt);

    return createPseudoScalarDtWrapper<VariableLengthSignedEnumerationType>(jsonDt,
                                                                            std::move(mappings),
                                                                            prefDispBase,
                                                                            std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromVlUIntType(const JsonObjVal& jsonDt, const std::string& type,
                                           MapItem::UP userAttrs, const DisplayBase prefDispBase)
{
    // roles
    auto roles = uIntTypeRolesOfUIntType(jsonDt);

    if (type == strs::VL_UINT) {
        return createPseudoScalarDtWrapper<VariableLengthUnsignedIntegerType>(jsonDt, prefDispBase,
                                                                              std::move(userAttrs));
    } else {
        assert(type == strs::VL_UENUM);
        return pseudoDtFromVlUEnumType(jsonDt, std::move(userAttrs), prefDispBase,
                                       std::move(roles));
    }
}

static PseudoDt::UP pseudoDtFromVlSIntType(const JsonObjVal& jsonDt, const std::string& type,
                                           MapItem::UP userAttrs, const DisplayBase prefDispBase)
{
    if (type == strs::VL_SINT) {
        return createPseudoScalarDtWrapper<VariableLengthSignedIntegerType>(jsonDt, prefDispBase,
                                                                            std::move(userAttrs));
    } else {
        assert(type == strs::VL_SENUM);
        return pseudoDtFromVlSEnumType(jsonDt, std::move(userAttrs), prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromVlIntType(const JsonObjVal& jsonDt, const std::string& type,
                                          MapItem::UP userAttrs)
{
    // preferred display base
    const auto prefDispBase = static_cast<DisplayBase>(jsonDt.getRawVal(strs::PREF_DISP_BASE, 10ULL));

    if (type == strs::VL_UINT || type == strs::VL_UENUM) {
        return pseudoDtFromVlUIntType(jsonDt, type, std::move(userAttrs), prefDispBase);
    } else {
        assert(type == strs::VL_SINT || type == strs::VL_SENUM);
        return pseudoDtFromVlSIntType(jsonDt, type, std::move(userAttrs), prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromNtStrType(const JsonObjVal& jsonDt, MapItem::UP userAttrs)
{
    return createPseudoScalarDtWrapper<NullTerminatedStringType>(jsonDt, std::move(userAttrs));
}

static PseudoDataLoc pseudoDataLocOfDynDt(const JsonObjVal& jsonDt, const std::string& propName)
{
    auto& jsonLocVal = jsonDt[propName]->asObj();
    boost::optional<Scope> scope;
    const auto jsonOrigVal = jsonLocVal[strs::ORIG];

    if (jsonOrigVal) {
        // absolute
        scope = [jsonOrigVal] {
            auto& scopeName = *jsonOrigVal->asStr();

            if (scopeName == strs::PKT_HEADER) {
                return Scope::PACKET_HEADER;
            } else if (scopeName == strs::PKT_CTX) {
                return Scope::PACKET_CONTEXT;
            } else if (scopeName == strs::ER_HEADER) {
                return Scope::EVENT_RECORD_HEADER;
            } else if (scopeName == strs::ER_COMMON_CTX) {
                return Scope::EVENT_RECORD_COMMON_CONTEXT;
            } else if (scopeName == strs::ER_SPEC_CTX) {
                return Scope::EVENT_RECORD_SPECIFIC_CONTEXT;
            } else {
                assert(scopeName == strs::ER_PAYLOAD);
                return Scope::EVENT_RECORD_PAYLOAD;
            }
        }();
    }

    auto& jsonPathVal = jsonLocVal[strs::PATH]->asArray();
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
        scope ? PseudoDataLoc::Kind::ABS : PseudoDataLoc::Kind::REL_2,
        scope, std::move(pathElems), jsonLocVal.loc()
    };
}

static PseudoDt::UP pseudoDtFromDlStrType(const JsonObjVal& jsonDt, MapItem::UP userAttrs)
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
    auto pseudoElemType = std::make_unique<PseudoFlUIntType>(8, 8, ByteOrder::BIG,
                                                             DisplayBase::DECIMAL, true);

    return std::make_unique<PseudoDlArrayType>(pseudoDataLocOfDynDt(jsonDt, strs::LEN_FIELD_LOC),
                                               std::move(pseudoElemType), std::move(userAttrs),
                                               jsonDt.loc());
}

static PseudoDt::UP pseudoDtFromSlStrType(const JsonObjVal& jsonDt, MapItem::UP userAttrs)
{
    return createPseudoScalarDtWrapper<StaticLengthStringType>(jsonDt,
                                                               jsonDt.getRawUIntVal(strs::LEN),
                                                               std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromNonNtStrType(const JsonObjVal& jsonDt, const std::string& type,
                                             MapItem::UP userAttrs)
{
    if (type == strs::SL_STR) {
        return pseudoDtFromSlStrType(jsonDt, std::move(userAttrs));
    } else {
        assert(type == strs::DL_STR);
        return pseudoDtFromDlStrType(jsonDt, std::move(userAttrs));
    }
}

static PseudoDt::UP pseudoDtFromDlBlobType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                           const char * const mediaType)
{
    return std::make_unique<PseudoDlBlobType>(pseudoDataLocOfDynDt(jsonDt, strs::LEN_FIELD_LOC),
                                              std::string {mediaType}, std::move(userAttrs),
                                              jsonDt.loc());
}

static PseudoDt::UP pseudoDtFromSlBlobType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                           const char * const mediaType)
{
    // has metadata stream UUID role?
    bool hasMetadataStreamUuidRole = false;
    const auto jsonRolesVal = jsonDt[strs::ROLES];

    if (jsonRolesVal && jsonRolesVal->asArray().size() > 0) {
        hasMetadataStreamUuidRole = true;
    }

    return createPseudoScalarDtWrapper<StaticLengthBlobType>(jsonDt,
                                                             jsonDt.getRawUIntVal(strs::LEN),
                                                             mediaType, std::move(userAttrs),
                                                             hasMetadataStreamUuidRole);
}

static PseudoDt::UP pseudoDtFromBlobType(const JsonObjVal& jsonDt, const std::string& type,
                                         MapItem::UP userAttrs)
{
    // media type
    const auto mediaType = jsonDt.getRawVal(strs::MEDIA_TYPE, strs::APP_OCTET_STREAM);

    if (type == strs::SL_BLOB) {
        return pseudoDtFromSlBlobType(jsonDt, std::move(userAttrs), mediaType);
    } else {
        assert(type == strs::DL_BLOB);
        return pseudoDtFromDlBlobType(jsonDt, std::move(userAttrs), mediaType);
    }
}

PseudoDt::UP PseudoDtErector::_pseudoDtFromDlArrayType(const JsonObjVal& jsonDt,
                                                       MapItem::UP userAttrs,
                                                       const unsigned int minAlign)
{
    return std::make_unique<PseudoDlArrayType>(minAlign,
                                               pseudoDataLocOfDynDt(jsonDt, strs::LEN_FIELD_LOC),
                                               this->pseudoDtOfJsonObj(jsonDt, strs::ELEM_FC),
                                               std::move(userAttrs), jsonDt.loc());
}

PseudoDt::UP PseudoDtErector::_pseudoDtFromSlArrayType(const JsonObjVal& jsonDt,
                                                       MapItem::UP userAttrs,
                                                       unsigned int minAlign)
{
    return std::make_unique<PseudoSlArrayType>(minAlign, jsonDt.getRawUIntVal(strs::LEN),
                                               this->pseudoDtOfJsonObj(jsonDt, strs::ELEM_FC),
                                               std::move(userAttrs), jsonDt.loc());
}

PseudoDt::UP PseudoDtErector::_pseudoDtFromArrayType(const JsonObjVal& jsonDt,
                                                     const std::string& type,
                                                     MapItem::UP userAttrs)
{
    // minimum alignment
    const auto minAlign = jsonDt.getRawVal(strs::MIN_ALIGN, 1ULL);

    try {
        if (type == strs::SL_ARRAY) {
            return this->_pseudoDtFromSlArrayType(jsonDt, std::move(userAttrs), minAlign);
        } else {
            assert(type == strs::DL_ARRAY);
            return this->_pseudoDtFromDlArrayType(jsonDt, std::move(userAttrs), minAlign);
        }
    } catch (TextParseError& exc) {
        appendMsgToTextParseError(exc, "In array type:", jsonDt.loc());
        throw;
    }
}

PseudoDt::UP PseudoDtErector::_pseudoDtFromStructType(const JsonObjVal& jsonDt,
                                                      MapItem::UP userAttrs)
{
    // member types
    PseudoNamedDts pseudoMemberTypes;
    const auto jsonMemberClss = jsonDt[strs::MEMBER_CLSS];

    if (jsonMemberClss) {
        for (auto& jsonMemberCls : jsonMemberClss->asArray()) {
            auto& jsonMemberClsObj = jsonMemberCls->asObj();
            auto& name = jsonMemberClsObj.getRawStrVal(strs::NAME);
            auto pseudoDt = [this, &name, &jsonMemberCls, &jsonMemberClsObj] {
                try {
                    return this->pseudoDtOfJsonObj(jsonMemberClsObj, strs::FC);
                } catch (TextParseError& exc) {
                    std::ostringstream ss;

                    ss << "In structure member type `" << name << "`:";
                    appendMsgToTextParseError(exc, ss.str(), jsonMemberCls->loc());
                    throw;
                }
            }();

            pseudoMemberTypes.push_back(std::make_unique<PseudoNamedDt>(std::move(name),
                                                                        std::move(pseudoDt),
                                                                        userAttrsOfObj(jsonMemberClsObj)));
        }
    }

    return std::make_unique<PseudoStructType>(jsonDt.getRawVal(strs::MIN_ALIGN, 1ULL),
                                              std::move(pseudoMemberTypes), std::move(userAttrs),
                                              jsonDt.loc());
}

static PseudoDt::UP pseudoDtFromOptWithIntSelType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                                  PseudoDataLoc&& pseudoSelLoc,
                                                  PseudoDt::UP pseudoDt,
                                                  const JsonArrayVal& jsonSelFieldRanges)
{
    return std::make_unique<PseudoOptWithIntSelType>(std::move(pseudoDt), std::move(pseudoSelLoc),
                                                     intRangesFromArray<unsigned long long, false>(jsonSelFieldRanges),
                                                     std::move(userAttrs), jsonDt.loc());
}

static PseudoDt::UP pseudoDtFromOptWithBoolSelType(const JsonObjVal& jsonDt, MapItem::UP userAttrs,
                                                   PseudoDataLoc&& pseudoSelLoc,
                                                   PseudoDt::UP pseudoDt)
{
    return std::make_unique<PseudoOptWithBoolSelType>(std::move(pseudoDt), std::move(pseudoSelLoc),
                                                      std::move(userAttrs), jsonDt.loc());
}

PseudoDt::UP PseudoDtErector::_pseudoDtFromOptType(const JsonObjVal& jsonDt, MapItem::UP userAttrs)
{
    // selector location
    auto pseudoSelLoc = pseudoDataLocOfDynDt(jsonDt, strs::SEL_FIELD_LOC);

    // data type
    auto pseudoDt = [this, &jsonDt] {
        try {
            return this->pseudoDtOfJsonObj(jsonDt, strs::FC);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "In optional type:", jsonDt.loc());
            throw;
        }
    }();

    // selector field ranges (presence indicates which kind of optional FC)
    const auto jsonSelFieldRanges = jsonDt[strs::SEL_FIELD_RANGES];

    if (jsonSelFieldRanges) {
        return pseudoDtFromOptWithIntSelType(jsonDt, std::move(userAttrs), std::move(pseudoSelLoc),
                                             std::move(pseudoDt), jsonSelFieldRanges->asArray());
    } else {
        return pseudoDtFromOptWithBoolSelType(jsonDt, std::move(userAttrs),
                                              std::move(pseudoSelLoc), std::move(pseudoDt));
    }
}

PseudoDt::UP PseudoDtErector::_pseudoDtFromVarType(const JsonObjVal& jsonDt, MapItem::UP userAttrs)
{
    // options and selector ranges
    PseudoNamedDts pseudoOpts;
    PseudoVarWithIntRangesType::RangeSets selRangeSets;

    for (auto& jsonOpt : jsonDt[strs::OPTS]->asArray()) {
        auto& jsonOptObj = jsonOpt->asObj();
        auto intRanges = intRangesFromArray<unsigned long long, false>(jsonOptObj[strs::SEL_FIELD_RANGES]->asArray());
        auto pseudoDt = [this, &pseudoOpts, &jsonOptObj] {
            try {
                return this->pseudoDtOfJsonObj(jsonOptObj, strs::FC);
            } catch (TextParseError& exc) {
                std::ostringstream ss;

                ss << "In variant type option #" << (pseudoOpts.size() + 1) << ":";
                appendMsgToTextParseError(exc, ss.str(), jsonOptObj.loc());
                throw;
            }
        }();

        selRangeSets.push_back(std::move(intRanges));
        pseudoOpts.push_back(std::make_unique<PseudoNamedDt>(optStrOfObj(jsonOptObj, strs::NAME),
                                                             std::move(pseudoDt),
                                                             userAttrsOfObj(jsonOptObj)));
    }

    return std::make_unique<PseudoVarWithIntRangesType>(pseudoDataLocOfDynDt(jsonDt,
                                                                             strs::SEL_FIELD_LOC),
                                                        std::move(pseudoOpts),
                                                        std::move(selRangeSets),
                                                        std::move(userAttrs), jsonDt.loc());
}

PseudoDt::UP PseudoDtErector::pseudoDtOfJsonObj(const JsonObjVal& jsonObjVal,
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
    auto& type = jsonDtObj.getRawStrVal(strs::TYPE);

    // user attributes
    auto userAttrs = userAttrsOfObj(jsonDtObj);

    // defer to specific method
    if (type == strs::FL_BIT_ARRAY ||
            type == strs::FL_BOOL ||
            type == strs::FL_UINT || type == strs::FL_SINT ||
            type == strs::FL_UENUM || type == strs::FL_SENUM ||
            type == strs::FL_FLOAT) {
        return pseudoDtFromFlBitArrayType(jsonDtObj, type, std::move(userAttrs));
    } else if (type == strs::VL_UINT || type == strs::VL_SINT ||
            type == strs::VL_UENUM || type == strs::VL_SENUM) {
        return pseudoDtFromVlIntType(jsonDtObj, type, std::move(userAttrs));
    } else if (type == strs::NT_STR) {
        return pseudoDtFromNtStrType(jsonDtObj, std::move(userAttrs));
    } else if (type == strs::SL_STR || type == strs::DL_STR) {
        return pseudoDtFromNonNtStrType(jsonDtObj, type, std::move(userAttrs));
    } else if (type == strs::SL_BLOB || type == strs::DL_BLOB) {
        return pseudoDtFromBlobType(jsonDtObj, type, std::move(userAttrs));
    } else if (type == strs::SL_ARRAY || type == strs::DL_ARRAY) {
        return this->_pseudoDtFromArrayType(jsonDtObj, type, std::move(userAttrs));
    } else if (type == strs::STRUCT) {
        return this->_pseudoDtFromStructType(jsonDtObj, std::move(userAttrs));
    } else if (type == strs::OPT) {
        return this->_pseudoDtFromOptType(jsonDtObj, std::move(userAttrs));
    } else {
        assert(type == strs::VAR);
        return this->_pseudoDtFromVarType(jsonDtObj, std::move(userAttrs));
    }
}

PseudoDt::UP PseudoDtErector::_aliasedPseudoDt(const std::string& name,
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

void PseudoDtErector::addAlias(const std::string& name, PseudoDt::UP pseudoDt,
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
