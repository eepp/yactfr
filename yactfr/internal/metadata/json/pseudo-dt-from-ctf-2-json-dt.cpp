/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/fl-bit-array-type.hpp>
#include <yactfr/metadata/fl-bool-type.hpp>
#include <yactfr/metadata/fl-int-type.hpp>
#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/metadata/fl-float-type.hpp>
#include <yactfr/metadata/vl-bit-array-type.hpp>
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
#include "pseudo-dt-from-ctf-2-json-dt.hpp"
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

template <typename ValT>
IntegerRangeSet<ValT> intRangesFromArray(const JsonArrayVal& jsonArrayVal)
{
    std::set<IntegerRange<ValT>> ranges;

    for (auto& jsonRange : jsonArrayVal) {
        auto& jsonRangeArray = jsonRange->asArray();

        ranges.insert(IntegerRange<ValT> {
            rawIntValFromJsonIntVal<ValT>(jsonRangeArray[0]),
            rawIntValFromJsonIntVal<ValT>(jsonRangeArray[1])
        });
    }

    return IntegerRangeSet<ValT> {std::move(ranges)};
}

template <typename EnumTypeT>
typename EnumTypeT::Mappings enumTypeMappingsOfEnumFc(const JsonObjVal& jsonFc)
{
    typename EnumTypeT::Mappings mappings;
    const auto jsonMappings = jsonFc[strs::MAPPINGS];

    if (!jsonMappings) {
        return mappings;
    }

    for (auto& keyJsonIntRangesPair : jsonMappings->asObj()) {
        mappings.insert(std::make_pair(keyJsonIntRangesPair.first,
                                       intRangesFromArray<typename EnumTypeT::Value>(keyJsonIntRangesPair.second->asArray())));
    }

    return mappings;
}

static PseudoDt::UP pseudoDtFromFlUEnumFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                          const unsigned int len, const ByteOrder bo,
                                          const unsigned int align, const DisplayBase prefDispBase,
                                          UnsignedIntegerTypeRoleSet&& roles)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumFc<FixedLengthUnsignedEnumerationType>(jsonFc);

    return createPseudoScalarDtWrapper<FixedLengthUnsignedEnumerationType>(jsonFc, align, len, bo,
                                                                           std::move(mappings),
                                                                           prefDispBase,
                                                                           std::move(userAttrs),
                                                                           std::move(roles));
}

static PseudoDt::UP pseudoDtFromFlSEnumFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                          const unsigned int len, const ByteOrder bo,
                                          const unsigned int align, const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumFc<FixedLengthSignedEnumerationType>(jsonFc);

    return createPseudoScalarDtWrapper<FixedLengthSignedEnumerationType>(jsonFc, align, len, bo,
                                                                         std::move(mappings),
                                                                         prefDispBase,
                                                                         std::move(userAttrs));
}

static UnsignedIntegerTypeRoleSet uIntTypeRolesOfUIntFc(const JsonObjVal& jsonFc)
{
    UnsignedIntegerTypeRoleSet roles;
    const auto jsonRolesVal = jsonFc[strs::ROLES];

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

static PseudoDt::UP pseudoDtFromFlUIntFc(const JsonObjVal& jsonFc, const std::string& type,
                                         MapItem::UP userAttrs, const unsigned int len,
                                         const ByteOrder bo, const unsigned int align,
                                         const DisplayBase prefDispBase)
{
    // roles
    auto roles = uIntTypeRolesOfUIntFc(jsonFc);

    if (type == strs::FL_UINT) {
        return createPseudoScalarDtWrapper<FixedLengthUnsignedIntegerType>(jsonFc, align, len, bo,
                                                                           prefDispBase,
                                                                           std::move(userAttrs),
                                                                           std::move(roles));
    } else {
        assert(type == strs::FL_UENUM);
        return pseudoDtFromFlUEnumFc(jsonFc, std::move(userAttrs), len, bo, align, prefDispBase,
                                     std::move(roles));
    }
}

static PseudoDt::UP pseudoDtFromFlSIntFc(const JsonObjVal& jsonFc, const std::string& type,
                                         MapItem::UP userAttrs, const unsigned int len,
                                         const ByteOrder bo, const unsigned int align,
                                         const DisplayBase prefDispBase)
{
    if (type == strs::FL_SINT) {
        return createPseudoScalarDtWrapper<FixedLengthSignedIntegerType>(jsonFc, align, len, bo,
                                                                         prefDispBase,
                                                                         std::move(userAttrs));
    } else {
        assert(type == strs::FL_SENUM);
        return pseudoDtFromFlSEnumFc(jsonFc, std::move(userAttrs), len, bo, align, prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromFlIntFc(const JsonObjVal& jsonFc, const std::string& type,
                                        MapItem::UP userAttrs, const unsigned int len,
                                        const ByteOrder bo, const unsigned int align)
{
    // preferred display base
    const auto prefDispBase = static_cast<DisplayBase>(jsonFc.getRawVal(strs::PREF_DISP_BASE,
                                                                        10ULL));

    if (type == strs::FL_UINT || type == strs::FL_UENUM) {
        return pseudoDtFromFlUIntFc(jsonFc, type, std::move(userAttrs), len, bo, align,
                                    prefDispBase);
    } else {
        assert(type == strs::FL_SINT || type == strs::FL_SENUM);
        return pseudoDtFromFlSIntFc(jsonFc, type, std::move(userAttrs), len, bo, align,
                                    prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromFlBoolFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                         const unsigned int len, const ByteOrder bo,
                                         const unsigned int align)
{
    return createPseudoScalarDtWrapper<FixedLengthBooleanType>(jsonFc, align, len, bo,
                                                               std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromFlFloatFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                          const unsigned int len, const ByteOrder bo,
                                          const unsigned int align)
{
    return createPseudoScalarDtWrapper<FixedLengthFloatingPointNumberType>(jsonFc, align, len, bo,
                                                                           std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromFlBitArrayFc(const JsonObjVal& jsonFc, const std::string& type,
                                             MapItem::UP userAttrs)
{
    // length
    const auto len = jsonFc.getRawUIntVal(strs::LEN);

    // byte order
    const auto bo = jsonFc.getRawStrVal(strs::BO) == strs::LE ? ByteOrder::LITTLE : ByteOrder::BIG;

    // alignment
    const auto align = jsonFc.getRawVal(strs::ALIGN, 1ULL);

    if (type == strs::FL_BIT_ARRAY) {
        return createPseudoScalarDtWrapper<FixedLengthBitArrayType>(jsonFc, align, len, bo,
                                                                    std::move(userAttrs));
    } else if (type == strs::FL_BOOL) {
        return pseudoDtFromFlBoolFc(jsonFc, std::move(userAttrs), len, bo, align);
    } else if (type == strs::FL_UINT || type == strs::FL_SINT ||
            type == strs::FL_UENUM || type == strs::FL_SENUM) {
        return pseudoDtFromFlIntFc(jsonFc, type, std::move(userAttrs), len, bo, align);
    } else {
        assert(type == strs::FL_FLOAT);
        return pseudoDtFromFlFloatFc(jsonFc, std::move(userAttrs), len, bo, align);
    }
}

static PseudoDt::UP pseudoDtFromVlUEnumFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                          const DisplayBase prefDispBase,
                                          UnsignedIntegerTypeRoleSet&& roles)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumFc<VariableLengthUnsignedEnumerationType>(jsonFc);

    return createPseudoScalarDtWrapper<VariableLengthUnsignedEnumerationType>(jsonFc,
                                                                              std::move(mappings),
                                                                              prefDispBase,
                                                                              std::move(userAttrs),
                                                                              std::move(roles));
}

static PseudoDt::UP pseudoDtFromVlSEnumFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                          const DisplayBase prefDispBase)
{
    // mappings
    auto mappings = enumTypeMappingsOfEnumFc<VariableLengthSignedEnumerationType>(jsonFc);

    return createPseudoScalarDtWrapper<VariableLengthSignedEnumerationType>(jsonFc,
                                                                            std::move(mappings),
                                                                            prefDispBase,
                                                                            std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromVlUIntFc(const JsonObjVal& jsonFc, const std::string& type,
                                         MapItem::UP userAttrs, const DisplayBase prefDispBase)
{
    // roles
    auto roles = uIntTypeRolesOfUIntFc(jsonFc);

    if (type == strs::VL_UINT) {
        return createPseudoScalarDtWrapper<VariableLengthUnsignedIntegerType>(jsonFc, prefDispBase,
                                                                              std::move(userAttrs));
    } else {
        assert(type == strs::VL_UENUM);
        return pseudoDtFromVlUEnumFc(jsonFc, std::move(userAttrs), prefDispBase, std::move(roles));
    }
}

static PseudoDt::UP pseudoDtFromVlSIntFc(const JsonObjVal& jsonFc, const std::string& type,
                                         MapItem::UP userAttrs, const DisplayBase prefDispBase)
{
    if (type == strs::VL_SINT) {
        return createPseudoScalarDtWrapper<VariableLengthSignedIntegerType>(jsonFc, prefDispBase,
                                                                            std::move(userAttrs));
    } else {
        assert(type == strs::VL_SENUM);
        return pseudoDtFromVlSEnumFc(jsonFc, std::move(userAttrs), prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromVlIntFc(const JsonObjVal& jsonFc, const std::string& type,
                                        MapItem::UP userAttrs)
{
    // preferred display base
    const auto prefDispBase = static_cast<DisplayBase>(jsonFc.getRawVal(strs::PREF_DISP_BASE, 10ULL));

    if (type == strs::VL_UINT || type == strs::VL_UENUM) {
        return pseudoDtFromVlUIntFc(jsonFc, type, std::move(userAttrs), prefDispBase);
    } else {
        assert(type == strs::VL_SINT || type == strs::VL_SENUM);
        return pseudoDtFromVlSIntFc(jsonFc, type, std::move(userAttrs), prefDispBase);
    }
}

static PseudoDt::UP pseudoDtFromVlBitArrayFc(const JsonObjVal& jsonFc, const std::string& type,
                                             MapItem::UP userAttrs)
{
    if (type == strs::VL_BIT_ARRAY) {
        return createPseudoScalarDtWrapper<VariableLengthBitArrayType>(jsonFc,
                                                                       std::move(userAttrs));
    } else {
        assert(type == strs::VL_UINT || type == strs::VL_SINT ||
               type == strs::VL_UENUM || type == strs::VL_SENUM);
        return pseudoDtFromVlIntFc(jsonFc, type, std::move(userAttrs));
    }
}

static PseudoDt::UP pseudoDtFromNtStrFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs)
{
    return createPseudoScalarDtWrapper<NullTerminatedStringType>(jsonFc, std::move(userAttrs));
}

static PseudoDataLoc pseudoDataLocOfDlFc(const JsonObjVal& jsonFc, const std::string& propName)
{
    auto& jsonLocVal = jsonFc[propName]->asArray();

    const auto scope = [&jsonLocVal] {
        auto& scopeName = *(*jsonLocVal.begin())->asStr();

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

    DataLocation::PathElements pathElems;

    for (auto it = jsonLocVal.begin() + 1; it != jsonLocVal.end(); ++it) {
        pathElems.push_back(*(*it)->asStr());
    }

    return PseudoDataLoc {false, true, scope, std::move(pathElems), jsonLocVal.loc()};
}

static PseudoDt::UP pseudoDtFromDlStrFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs)
{
    /*
     * Returning a pseudo dynamic array type having a pseudo
     * fixed-length unsigned integer type with an encoding for a
     * dynamic-length string type to accomodate the common pseudo type
     * API which also serves the CTF 1.8 use case.
     *
     * dtFromPseudoRootDt() will convert this pseudo dynamic array type
     * to a `DynamicLengthStringType` instance.
     */
    auto pseudoElemType = std::make_unique<PseudoFlUIntType>(8, 8, ByteOrder::BIG,
                                                             DisplayBase::DECIMAL, true);

    return std::make_unique<PseudoDlArrayType>(pseudoDataLocOfDlFc(jsonFc, strs::LEN_FIELD_LOC),
                                               std::move(pseudoElemType), std::move(userAttrs),
                                               jsonFc.loc());
}

static PseudoDt::UP pseudoDtFromSlStrFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs)
{
    return createPseudoScalarDtWrapper<StaticLengthStringType>(jsonFc,
                                                               jsonFc.getRawUIntVal(strs::LEN),
                                                               std::move(userAttrs));
}

static PseudoDt::UP pseudoDtFromNonNtStrFc(const JsonObjVal& jsonFc, const std::string& type,
                                           MapItem::UP userAttrs)
{
    if (type == strs::SL_STR) {
        return pseudoDtFromSlStrFc(jsonFc, std::move(userAttrs));
    } else {
        assert(type == strs::DL_STR);
        return pseudoDtFromDlStrFc(jsonFc, std::move(userAttrs));
    }
}

static PseudoDt::UP pseudoDtFromDlBlobFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                         const char * const mediaType)
{
    return std::make_unique<PseudoDlBlobType>(pseudoDataLocOfDlFc(jsonFc, strs::LEN_FIELD_LOC),
                                              std::string {mediaType}, std::move(userAttrs),
                                              jsonFc.loc());
}

static PseudoDt::UP pseudoDtFromSlBlobFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                         const char * const mediaType)
{
    // has trace type UUID role?
    bool hasTraceTypeUuidRole = false;
    const auto jsonRolesVal = jsonFc[strs::ROLES];

    if (jsonRolesVal && jsonRolesVal->asArray().size() > 0) {
        hasTraceTypeUuidRole = true;
    }

    return createPseudoScalarDtWrapper<StaticLengthBlobType>(jsonFc,
                                                             jsonFc.getRawUIntVal(strs::LEN),
                                                             mediaType, std::move(userAttrs),
                                                             hasTraceTypeUuidRole);
}

static PseudoDt::UP pseudoDtFromBlobFc(const JsonObjVal& jsonFc, const std::string& type,
                                       MapItem::UP userAttrs)
{
    // media type
    const auto mediaType = jsonFc.getRawVal(strs::MEDIA_TYPE, "application/octet-stream");

    if (type == strs::SL_BLOB) {
        return pseudoDtFromSlBlobFc(jsonFc, std::move(userAttrs), mediaType);
    } else {
        assert(type == strs::DL_BLOB);
        return pseudoDtFromDlBlobFc(jsonFc, std::move(userAttrs), mediaType);
    }
}

static PseudoDt::UP pseudoDtFromDlArrayFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                          const unsigned int minAlign)
{
    return std::make_unique<PseudoDlArrayType>(minAlign,
                                               pseudoDataLocOfDlFc(jsonFc, strs::LEN_FIELD_LOC),
                                               pseudoDtOfCtf2Obj(jsonFc, strs::ELEM_FC),
                                               std::move(userAttrs), jsonFc.loc());
}

static PseudoDt::UP pseudoDtFromSlArrayFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                          const unsigned int minAlign)
{
    return std::make_unique<PseudoSlArrayType>(minAlign, jsonFc.getRawUIntVal(strs::LEN),
                                               pseudoDtOfCtf2Obj(jsonFc, strs::ELEM_FC),
                                               std::move(userAttrs), jsonFc.loc());
}

static PseudoDt::UP pseudoDtFromArrayFc(const JsonObjVal& jsonFc, const std::string& type,
                                        MapItem::UP userAttrs)
{
    // minimum alignment
    const auto minAlign = jsonFc.getRawVal(strs::MIN_ALIGN, 1ULL);

    if (type == strs::SL_ARRAY) {
        return pseudoDtFromSlArrayFc(jsonFc, std::move(userAttrs), minAlign);
    } else {
        assert(type == strs::DL_ARRAY);
        return pseudoDtFromDlArrayFc(jsonFc, std::move(userAttrs), minAlign);
    }
}

static PseudoDt::UP pseudoDtFromStructFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs)
{
    // member types
    PseudoNamedDts pseudoMemberTypes;
    const auto jsonMemberClss = jsonFc[strs::MEMBER_CLSS];

    if (jsonMemberClss) {
        for (auto& jsonMemberCls : jsonMemberClss->asArray()) {
            auto& jsonMemberClsObj = jsonMemberCls->asObj();

            pseudoMemberTypes.push_back(std::make_unique<PseudoNamedDt>(jsonMemberClsObj.getRawStrVal(strs::NAME),
                                                                        pseudoDtOfCtf2Obj(jsonMemberClsObj, strs::FC),
                                                                        userAttrsOfObj(jsonMemberClsObj)));
        }
    }

    return std::make_unique<PseudoStructType>(jsonFc.getRawVal(strs::MIN_ALIGN, 1ULL),
                                              std::move(pseudoMemberTypes), std::move(userAttrs),
                                              jsonFc.loc());
}

static PseudoDt::UP pseudoDtFromOptWithIntSelFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                                PseudoDataLoc&& pseudoSelLoc,
                                                PseudoDt::UP pseudoDt,
                                                const JsonArrayVal& jsonSelFieldRanges)
{
    return std::make_unique<PseudoOptWithIntSelType>(std::move(pseudoDt), std::move(pseudoSelLoc),
                                                     intRangesFromArray<unsigned long long>(jsonSelFieldRanges),
                                                     std::move(userAttrs), jsonFc.loc());
}

static PseudoDt::UP pseudoDtFromOptWithBoolSelFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs,
                                                 PseudoDataLoc&& pseudoSelLoc,
                                                 PseudoDt::UP pseudoDt)
{
    return std::make_unique<PseudoOptWithBoolSelType>(std::move(pseudoDt), std::move(pseudoSelLoc),
                                                      std::move(userAttrs), jsonFc.loc());
}

static PseudoDt::UP pseudoDtFromOptFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs)
{
    // selector location
    auto pseudoSelLoc = pseudoDataLocOfDlFc(jsonFc, strs::SEL_FIELD_LOC);

    // data type
    auto pseudoDt = pseudoDtOfCtf2Obj(jsonFc, strs::FC);

    // selector field ranges (presence indicates which kind of optional FC)
    const auto jsonSelFieldRanges = jsonFc[strs::SEL_FIELD_RANGES];

    if (jsonSelFieldRanges) {
        return pseudoDtFromOptWithIntSelFc(jsonFc, std::move(userAttrs), std::move(pseudoSelLoc),
                                           std::move(pseudoDt), jsonSelFieldRanges->asArray());
    } else {
        return pseudoDtFromOptWithBoolSelFc(jsonFc, std::move(userAttrs), std::move(pseudoSelLoc),
                                            std::move(pseudoDt));
    }
}

static PseudoDt::UP pseudoDtFromVarFc(const JsonObjVal& jsonFc, MapItem::UP userAttrs)
{
    // options and selector ranges
    PseudoNamedDts pseudoOpts;
    PseudoVarWithIntRangesType::RangeSets selRangeSets;

    for (auto& jsonOpt : jsonFc[strs::OPTS]->asArray()) {
        auto& jsonOptObj = jsonOpt->asObj();
        auto intRanges = intRangesFromArray<unsigned long long>(jsonOptObj[strs::SEL_FIELD_RANGES]->asArray());

        selRangeSets.push_back(std::move(intRanges));
        pseudoOpts.push_back(std::make_unique<PseudoNamedDt>(optStrOfObj(jsonOptObj, strs::NAME),
                                                             pseudoDtOfCtf2Obj(jsonOptObj, strs::FC),
                                                             userAttrsOfObj(jsonOptObj)));
    }

    return std::make_unique<PseudoVarWithIntRangesType>(pseudoDataLocOfDlFc(jsonFc, strs::SEL_FIELD_LOC),
                                                        std::move(pseudoOpts),
                                                        std::move(selRangeSets),
                                                        std::move(userAttrs), jsonFc.loc());
}

PseudoDt::UP pseudoDtOfCtf2Obj(const JsonObjVal& jsonObjVal, const std::string& propName)
{
    const auto jsonFcVal = jsonObjVal[propName];

    if (!jsonFcVal) {
        return nullptr;
    }

    auto& jsonFcObj = jsonFcVal->asObj();

    // get type
    auto& type = jsonFcObj.getRawStrVal(strs::TYPE);

    // user attributes
    auto userAttrs = userAttrsOfObj(jsonFcObj);

    // defer to specific method
    if (type == strs::FL_BIT_ARRAY ||
            type == strs::FL_BOOL ||
            type == strs::FL_UINT || type == strs::FL_SINT ||
            type == strs::FL_UENUM || type == strs::FL_SENUM ||
            type == strs::FL_FLOAT) {
        return pseudoDtFromFlBitArrayFc(jsonFcObj, type, std::move(userAttrs));
    } else if (type == strs::VL_BIT_ARRAY ||
            type == strs::VL_UINT || type == strs::VL_SINT ||
            type == strs::VL_UENUM || type == strs::VL_SENUM) {
        return pseudoDtFromVlBitArrayFc(jsonFcObj, type, std::move(userAttrs));
    } else if (type == strs::NT_STR) {
        return pseudoDtFromNtStrFc(jsonFcObj, std::move(userAttrs));
    } else if (type == strs::SL_STR || type == strs::DL_STR) {
        return pseudoDtFromNonNtStrFc(jsonFcObj, type, std::move(userAttrs));
    } else if (type == strs::SL_BLOB || type == strs::DL_BLOB) {
        return pseudoDtFromBlobFc(jsonFcObj, type, std::move(userAttrs));
    } else if (type == strs::SL_ARRAY || type == strs::DL_ARRAY) {
        return pseudoDtFromArrayFc(jsonFcObj, type, std::move(userAttrs));
    } else if (type == strs::STRUCT) {
        return pseudoDtFromStructFc(jsonFcObj, std::move(userAttrs));
    } else if (type == strs::OPT) {
        return pseudoDtFromOptFc(jsonFcObj, std::move(userAttrs));
    } else {
        assert(type == strs::VAR);
        return pseudoDtFromVarFc(jsonFcObj, std::move(userAttrs));
    }
}

} // namespace internal
} // namespace yactfr
