/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>
#include <tuple>
#include <set>

#include <yactfr/text-loc.hpp>
#include <yactfr/metadata/internal/dt-from-pseudo-root-dt.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/dl-blob-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/opt-type.hpp>
#include <yactfr/metadata/metadata-parse-error.hpp>
#include <yactfr/internal/utils.hpp>

#include "utils.hpp"

namespace yactfr {
namespace internal {

StructureType::UP dtFromPseudoRootDt(const PseudoDt& pseudoDt, const Scope scope,
                                     const PseudoTraceType& pseudoTraceType,
                                     const PseudoDst * const curPseudoDst,
                                     const PseudoErt * const curPseudoErt)
{
    return DtFromPseudoRootDtConverter {
        pseudoDt, scope, pseudoTraceType, curPseudoDst, curPseudoErt
    }._releaseDt();
}

DtFromPseudoRootDtConverter::DtFromPseudoRootDtConverter(const PseudoDt& pseudoDt,
                                                         const Scope scope,
                                                         const PseudoTraceType& pseudoTraceType,
                                                         const PseudoDst * const pseudoDst,
                                                         const PseudoErt * const pseudoErt) :
    _scope {scope},
    _pseudoTraceType {&pseudoTraceType},
    _pseudoDst {pseudoDst},
    _pseudoErt {pseudoErt},
    _locMap {pseudoDt, scope}
{

    /*
     * Here's what happens here:
     *
     * 1. Building `_locMap` above maps each relevant pseudo data type
     *    to its yactfr data location from its pseudo data location.
     *
     *    After this step, we have all the yactfr (absolute) data
     *    locations we need, but there are no yactfr data types yet.
     *
     * 2. _structTypeFromPseudoDt() recursively converts pseudo data
     *    types to yactfr data types.
     *
     *    During this process, we need to find and validate:
     *
     *    * The length integer types of dynamic-length array, string,
     *      and BLOB types.
     *
     *    * The selector type of variant and optional types.
     *
     *    To do so:
     *
     *    a) When visiting the data types of the options of a variant
     *       type VT, we make `_current` contain the current option
     *       index for VT.
     *
     *    b) When visiting the element type of an array type AT, we make
     *       `_current` contain that AT is currently being visited.
     *
     *    c) When visiting the pseudo data type of an optional type OT,
     *       we make `_current` contain that OT is currently being
     *       visited.
     *
     *    _findPseudoDts() uses the data above to make sure that it only
     *    finds the accessible data types depending on the context.
     */
    _dt = this->_structTypeFromPseudoDt(pseudoDt);
}

StructureType::UP DtFromPseudoRootDtConverter::_structTypeFromPseudoDt(const PseudoDt& pseudoDt)
{
    return StructureType::UP {static_cast<const StructureType *>(this->_dtFromPseudoDt(pseudoDt).release())};
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoDt(const PseudoDt& pseudoDt)
{
    switch (pseudoDt.kind()) {
    case PseudoDt::Kind::SCALAR_DT_WRAPPER:
        return this->_dtFromPseudoScalarDtWrapper(pseudoDt);

    case PseudoDt::Kind::FL_UINT:
        return this->_dtFromPseudoFlUIntType(pseudoDt);

    case PseudoDt::Kind::FL_UENUM:
        return this->_dtFromPseudoFlUEnumType(pseudoDt);

    case PseudoDt::Kind::SL_ARRAY:
        return this->_dtFromPseudoSlArrayType(pseudoDt);

    case PseudoDt::Kind::DL_ARRAY:
        return this->_dtFromPseudoDlArrayType(pseudoDt);

    case PseudoDt::Kind::DL_BLOB:
        return this->_dtFromPseudoDlBlobType(pseudoDt);

    case PseudoDt::Kind::STRUCT:
        return this->_dtFromPseudoStructType(pseudoDt);

    case PseudoDt::Kind::VAR:
        return this->_dtFromPseudoVarType(pseudoDt);

    case PseudoDt::Kind::VAR_WITH_INT_RANGES:
        return this->_dtFromPseudoVarWithIntRangesType(pseudoDt);

    case PseudoDt::Kind::OPT_WITH_BOOL_SEL:
        return this->_dtFromPseudoOptWithBoolSelType(pseudoDt);

    case PseudoDt::Kind::OPT_WITH_INT_SEL:
        return this->_dtFromPseudoOptWithIntSelType(pseudoDt);

    default:
        std::abort();
    }
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoScalarDtWrapper(const PseudoDt& pseudoDt) const
{
    return static_cast<const PseudoScalarDtWrapper&>(pseudoDt).dt().clone();
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoFlUIntType(const PseudoDt& pseudoDt) const
{
    auto& pseudoUIntType = static_cast<const PseudoFlUIntType&>(pseudoDt);

    return std::make_unique<const FixedLengthUnsignedIntegerType>(pseudoUIntType.align(),
                                                                  pseudoUIntType.len(),
                                                                  pseudoUIntType.bo(),
                                                                  pseudoUIntType.prefDispBase(),
                                                                  tryCloneUserAttrs(pseudoUIntType.userAttrs()),
                                                                  pseudoUIntType.roles());
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoFlUEnumType(const PseudoDt& pseudoDt) const
{
    auto& pseudoUEnumType = static_cast<const PseudoFlUEnumType&>(pseudoDt);

    return std::make_unique<const FixedLengthUnsignedEnumerationType>(pseudoUEnumType.align(),
                                                                      pseudoUEnumType.len(),
                                                                      pseudoUEnumType.bo(),
                                                                      pseudoUEnumType.mappings(),
                                                                      pseudoUEnumType.prefDispBase(),
                                                                      tryCloneUserAttrs(pseudoUEnumType.userAttrs()),
                                                                      pseudoUEnumType.roles());
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoSlArrayType(const PseudoDt& pseudoDt)
{
    auto& pseudoArrayType = static_cast<const PseudoSlArrayType&>(pseudoDt);
    auto arrayType = this->_tryNonNtStrTypeFromPseudoArrayType<StaticLengthStringType>(pseudoDt,
                                                                                   pseudoArrayType.pseudoElemType(),
                                                                                   pseudoArrayType.len());

    if (arrayType) {
        return arrayType;
    }

    auto elemDt = this->_whileVisitingPseudoDt(pseudoArrayType, [this](auto& pseudoArrayType) {
        return this->_dtFromPseudoDt(pseudoArrayType.pseudoElemType());
    });

    // not visited anymore
    _current.erase(&pseudoArrayType);

    return std::make_unique<const StaticLengthArrayType>(1, std::move(elemDt),
                                                         pseudoArrayType.len(),
                                                         tryCloneUserAttrs(pseudoArrayType.userAttrs()),
                                                         pseudoArrayType.hasTraceTypeUuidRole());
}

const DataLocation& DtFromPseudoRootDtConverter::_getLenLoc(const PseudoDt& pseudoDt) const
{
    const auto& lenLoc = _locMap[pseudoDt];
    const auto pseudoLenTypes = this->_findPseudoDts(lenLoc, pseudoDt.loc());

    assert(!pseudoLenTypes.empty());

    for (const auto pseudoLenType : pseudoLenTypes) {
        if (!pseudoLenType->isUInt()) {
            this->_throwInvalDataLoc("Length type isn't an unsigned integer type.",
                                     pseudoLenType->loc(), lenLoc, pseudoDt.loc());
        }
    }

    return lenLoc;
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoDlArrayType(const PseudoDt& pseudoDt)
{
    const auto& lenLoc = this->_getLenLoc(pseudoDt);
    auto& pseudoArrayType = static_cast<const PseudoDlArrayType&>(pseudoDt);
    auto strType = this->_tryNonNtStrTypeFromPseudoArrayType<DynamicLengthStringType>(pseudoDt,
                                                                                      pseudoArrayType.pseudoElemType(),
                                                                                      lenLoc);

    if (strType) {
        return strType;
    }

    auto elemDt = this->_whileVisitingPseudoDt(pseudoArrayType, [this](auto& pseudoArrayType) {
        return this->_dtFromPseudoDt(pseudoArrayType.pseudoElemType());
    });

    return std::make_unique<const DynamicLengthArrayType>(1, std::move(elemDt), lenLoc,
                                                          tryCloneUserAttrs(pseudoArrayType.userAttrs()));
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoDlBlobType(const PseudoDt& pseudoDt)
{
    const auto& lenLoc = this->_getLenLoc(pseudoDt);
    auto& pseudoBlobType = static_cast<const PseudoDlBlobType&>(pseudoDt);

    if (pseudoBlobType.mediaType()) {
        return std::make_unique<const DynamicLengthBlobType>(1, lenLoc,
                                                             *pseudoBlobType.mediaType(),
                                                             tryCloneUserAttrs(pseudoBlobType.userAttrs()));
    } else {
        return std::make_unique<const DynamicLengthBlobType>(1, lenLoc,
                                                             tryCloneUserAttrs(pseudoBlobType.userAttrs()));
    }
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoStructType(const PseudoDt& pseudoDt)
{
    StructureType::MemberTypes memberTypes;
    auto& pseudoStructType = static_cast<const PseudoStructType&>(pseudoDt);

    for (const auto& pseudoMemberType : pseudoStructType.pseudoMemberTypes()) {
        auto memberDt = this->_dtFromPseudoDt(pseudoMemberType->pseudoDt());

        memberTypes.push_back(std::make_unique<const StructureMemberType>(pseudoMemberType->name(),
                                                                          std::move(memberDt),
                                                                          tryCloneUserAttrs(pseudoMemberType->userAttrs())));
    }

    return std::make_unique<const StructureType>(pseudoStructType.minAlign(),
                                                 std::move(memberTypes),
                                                 tryCloneUserAttrs(pseudoStructType.userAttrs()));
}

void DtFromPseudoRootDtConverter::_findPseudoDts(const PseudoDt& pseudoDt, const DataLocation& loc,
                                                 const DataLocation::PathElements::const_iterator locIt,
                                                 const TextLocation& srcLoc,
                                                 ConstPseudoDtSet& pseudoDts) const
{
    switch (pseudoDt.kind()) {
    case PseudoDt::Kind::SCALAR_DT_WRAPPER:
    case PseudoDt::Kind::FL_UINT:
    case PseudoDt::Kind::FL_UENUM:
        if (locIt != loc.pathElements().end()) {
            std::ostringstream ss;

            ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "`: "
                  "nothing past scalar data type.";
            throwMetadataParseError(ss.str(), pseudoDt.loc());
        }

        pseudoDts.insert(&pseudoDt);
        break;

    case PseudoDt::Kind::STRUCT:
    {
        const auto pseudoMemberType = static_cast<const PseudoStructType&>(pseudoDt)[*locIt];

        if (!pseudoMemberType) {
            std::ostringstream ss;

            ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), locIt + 1) << "`: "
                  "cannot find `" << *locIt << "` (last element).";
            throwMetadataParseError(ss.str(), pseudoDt.loc());
        }

        this->_findPseudoDts(pseudoMemberType->pseudoDt(), loc, locIt + 1, srcLoc, pseudoDts);
        break;
    }

    case PseudoDt::Kind::SL_ARRAY:
    case PseudoDt::Kind::DL_ARRAY:
    {
        if (_current.find(&pseudoDt) == _current.end()) {
            std::ostringstream ss;

            ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "`: "
                  "unreachable array element.";
            throwMetadataParseError(ss.str(), pseudoDt.loc());
        }

        auto& pseudoArrayType = static_cast<const PseudoArrayType&>(pseudoDt);

        this->_findPseudoDts(pseudoArrayType.pseudoElemType(), loc, locIt, srcLoc, pseudoDts);
        break;
    }

    case PseudoDt::Kind::VAR:
    case PseudoDt::Kind::VAR_WITH_INT_RANGES:
    {
        auto& pseudoVarType = static_cast<const PseudoVarType&>(pseudoDt);
        const auto it = _current.find(&pseudoDt);

        if (it == _current.end()) {
            // fan out (consider all options)
            for (auto& pseudoOpt : pseudoVarType.pseudoOpts()) {
                this->_findPseudoDts(pseudoOpt->pseudoDt(), loc, locIt, srcLoc, pseudoDts);
            }
        } else {
            // follow current option only
            this->_findPseudoDts(pseudoVarType.pseudoOpts()[it->second]->pseudoDt(), loc, locIt,
                                 srcLoc, pseudoDts);
        }

        break;
    }

    case PseudoDt::Kind::OPT_WITH_BOOL_SEL:
    case PseudoDt::Kind::OPT_WITH_INT_SEL:
    {
        if (_current.find(&pseudoDt) == _current.end()) {
            std::ostringstream ss;

            ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "`: "
                  "unreachable optional data.";
            throwMetadataParseError(ss.str(), pseudoDt.loc());
        }

        auto& pseudoOptType = static_cast<const PseudoOptType&>(pseudoDt);

        this->_findPseudoDts(pseudoOptType.pseudoDt(), loc, locIt, srcLoc, pseudoDts);
        break;
    }

    default:
        std::abort();
    }
}

ConstPseudoDtSet DtFromPseudoRootDtConverter::_findPseudoDts(const DataLocation& loc,
                                                             const TextLocation& srcLoc) const
{
    if (static_cast<int>(loc.scope()) > static_cast<int>(_scope)) {
        std::ostringstream ss;

        ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), loc.end()) << "`: "
              "data would be unreachable.";
        throwMetadataParseError(ss.str(), srcLoc);
    }

    const PseudoDt *pseudoDt = nullptr;

    switch (loc.scope()) {
    case Scope::PACKET_HEADER:
        pseudoDt = _pseudoTraceType->pseudoPktHeaderType();
        break;

    case Scope::PACKET_CONTEXT:
        pseudoDt = _pseudoDst->pseudoPktCtxType();
        break;

    case Scope::EVENT_RECORD_HEADER:
        pseudoDt = _pseudoDst->pseudoErHeaderType();
        break;

    case Scope::EVENT_RECORD_COMMON_CONTEXT:
        pseudoDt = _pseudoDst->pseudoErCommonCtxType();
        break;

    case Scope::EVENT_RECORD_SPECIFIC_CONTEXT:
        pseudoDt = _pseudoErt->pseudoSpecCtxType();
        break;

    case Scope::EVENT_RECORD_PAYLOAD:
        pseudoDt = _pseudoErt->pseudoPayloadType();
        break;

    default:
        std::abort();
    }

    if (!pseudoDt) {
        std::ostringstream ss;

        ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), loc.end()) << "`: "
              "cannot find scope data type.";
        throwMetadataParseError(ss.str(), srcLoc);
    }

    ConstPseudoDtSet pseudoDts;

    this->_findPseudoDts(*pseudoDt, loc, loc.begin(), srcLoc, pseudoDts);
    return pseudoDts;
}

DtFromPseudoRootDtConverter::_PseudoDtSels DtFromPseudoRootDtConverter::_pseudoDtSels(const PseudoDt& pseudoDt) const
{
    const auto& selLoc = _locMap[pseudoDt];
    auto pseudoSelDts = this->_findPseudoDts(selLoc, pseudoDt.loc());

    assert(!pseudoSelDts.empty());
    return {selLoc, std::move(pseudoSelDts)};
}

DtFromPseudoRootDtConverter::_PseudoDtSels DtFromPseudoRootDtConverter::_pseudoDtIntSels(const PseudoDt& pseudoDt,
                                                                                         const std::string& dtName) const
{
    auto pseudoDtSels = this->_pseudoDtSels(pseudoDt);

    // validate selector types
    Size unsignedIntSelTypeCount = 0;

    for (const auto pseudoSelDt : pseudoDtSels.second) {
        if (!pseudoSelDt->isInt()) {
            std::ostringstream ss;

            ss << "Selector type of " << dtName << " type isn't an integer type.";
            this->_throwInvalDataLoc(ss.str(), pseudoSelDt->loc(), pseudoDtSels.first,
                                     pseudoDt.loc());
        }

        if (pseudoSelDt->isUInt()) {
            ++unsignedIntSelTypeCount;
        }
    }

    if (unsignedIntSelTypeCount > 0 && unsignedIntSelTypeCount < pseudoDtSels.second.size()) {
        std::ostringstream ss;

        ss << "All selector types of " << dtName << " type don't have the same signedness.";
        this->_throwInvalDataLoc(ss.str(), pseudoDt.loc(), pseudoDtSels.first, pseudoDt.loc());
    }

    return pseudoDtSels;
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoVarWithIntRangesType(const PseudoDt& pseudoDt)
{
    assert(_pseudoTraceType->majorVersion() == 2);

    auto& pseudoVarType = static_cast<const PseudoVarWithIntRangesType&>(pseudoDt);
    auto selLocPseudoDtsPair = this->_pseudoDtIntSels(pseudoDt, "variant");
    auto& selLoc = selLocPseudoDtsPair.first;
    const auto& pseudoSelDts = selLocPseudoDtsPair.second;

    assert(!pseudoSelDts.empty());

    if ((*pseudoSelDts.begin())->isUInt()) {
        return this->_dtFromPseudoVarWithIntRangesType<VariantWithUnsignedIntegerSelectorType,
                                                       unsigned long long>(pseudoVarType,
                                                                           std::move(selLoc));
    } else {
        return this->_dtFromPseudoVarWithIntRangesType<VariantWithSignedIntegerSelectorType,
                                                       long long>(pseudoVarType, std::move(selLoc));
    }

    return nullptr;
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoVarType(const PseudoDt& pseudoDt)
{
    assert(_pseudoTraceType->majorVersion() == 1);

    auto& pseudoVarType = static_cast<const PseudoVarType&>(pseudoDt);
    const auto selLocPseudoDtsPair = this->_pseudoDtSels(pseudoDt);
    auto& selLoc = selLocPseudoDtsPair.first;
    auto& pseudoSelDts = selLocPseudoDtsPair.second;
    const PseudoDt *pseudoSelDt = nullptr;
    bool selIsFlUEnumType;

    // validate selector type
    {
        if (pseudoSelDts.size() > 1) {
            this->_throwInvalDataLoc("Selector type of variant type targets more than one data type.",
                                     pseudoVarType.loc(), selLoc, pseudoVarType.loc());
        }

        pseudoSelDt = *pseudoSelDts.begin();

        if (!pseudoSelDt->isInt()) {
            this->_throwInvalDataLoc("Selector type of variant type isn't an integer type.",
                                     pseudoSelDt->loc(), selLoc, pseudoDt.loc());
        }

        bool isFlEnumType;

        if (pseudoSelDt->kind() == PseudoDt::Kind::SCALAR_DT_WRAPPER) {
            auto& pseudoScalarDtWrapper = static_cast<const PseudoScalarDtWrapper&>(*pseudoSelDt);

            isFlEnumType = pseudoScalarDtWrapper.dt().isFixedLengthEnumerationType();
            selIsFlUEnumType = pseudoScalarDtWrapper.dt().isFixedLengthUnsignedEnumerationType();
        } else {
            isFlEnumType = pseudoSelDt->kind() == PseudoDt::Kind::FL_UENUM;
            selIsFlUEnumType = true;
        }

        if (!isFlEnumType) {
            this->_throwInvalDataLoc("Selector type of variant type isn't an enumeration type.",
                                     pseudoSelDt->loc(), selLoc, pseudoDt.loc());
        }

    }

    assert(pseudoSelDt);

    if (selIsFlUEnumType) {
        auto& pseudoUEnumSelType = static_cast<const PseudoFlUEnumType&>(*pseudoSelDt);

        return this->_dtFromPseudoVarType<VariantWithUnsignedIntegerSelectorType>(pseudoVarType,
                                                                                  pseudoUEnumSelType.mappings(),
                                                                                  selLoc);
    } else {
        auto& pseudoScalarDtWrapper = static_cast<const PseudoScalarDtWrapper&>(*pseudoSelDt);
        auto& mappings = pseudoScalarDtWrapper.dt().asFixedLengthSignedEnumerationType().mappings();

        return this->_dtFromPseudoVarType<VariantWithSignedIntegerSelectorType>(pseudoVarType,
                                                                                mappings, selLoc);
    }
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoOptWithBoolSelType(const PseudoDt& pseudoDt)
{
    assert(_pseudoTraceType->majorVersion() == 2);

    auto& pseudoOptType = static_cast<const PseudoOptType&>(pseudoDt);
    auto selLocPseudoDtsPair = this->_pseudoDtSels(pseudoDt);

    for (const auto pseudoSelDt : selLocPseudoDtsPair.second) {
        if (pseudoSelDt->kind() != PseudoDt::Kind::SCALAR_DT_WRAPPER ||
                !static_cast<const PseudoScalarDtWrapper&>(*pseudoSelDt).dt().isFixedLengthBooleanType()) {
            this->_throwInvalDataLoc("Selector type of optional type isn't a boolean type.",
                                     pseudoSelDt->loc(), selLocPseudoDtsPair.first, pseudoDt.loc());
        }
    }

    auto containedDt = this->_whileVisitingPseudoDt(pseudoOptType, [this](auto& pseudoOptType) {
        return this->_dtFromPseudoDt(pseudoOptType.pseudoDt());
    });

    return std::make_unique<const OptionalWithBooleanSelectorType>(1, std::move(containedDt),
                                                                   std::move(selLocPseudoDtsPair.first),
                                                                   tryCloneUserAttrs(pseudoDt.userAttrs()));
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoOptWithIntSelType(const PseudoDt& pseudoDt)
{
    assert(_pseudoTraceType->majorVersion() == 2);

    auto& pseudoOptType = static_cast<const PseudoOptWithIntSelType&>(pseudoDt);
    auto selLocPseudoDtsPair = this->_pseudoDtIntSels(pseudoDt, "optional");
    auto& selLoc = selLocPseudoDtsPair.first;
    const auto& pseudoSelDts = selLocPseudoDtsPair.second;

    auto containedDt = this->_whileVisitingPseudoDt(pseudoOptType, [this](auto& pseudoOptType) {
        return this->_dtFromPseudoDt(pseudoOptType.pseudoDt());
    });

    assert(!pseudoSelDts.empty());

    if ((*pseudoSelDts.begin())->isUInt()) {
        return std::make_unique<OptionalWithUnsignedIntegerSelectorType>(1, std::move(containedDt),
                                                                         std::move(selLoc),
                                                                         pseudoOptType.selRanges(),
                                                                         tryCloneUserAttrs(pseudoDt.userAttrs()));
    } else {
        using SInt = long long;

        std::set<IntegerRange<SInt>> ranges;

        for (auto& range : pseudoOptType.selRanges()) {
            ranges.insert(IntegerRange<SInt> {
                static_cast<SInt>(range.lower()),
                static_cast<SInt>(range.upper())
            });
        }

        return std::make_unique<OptionalWithSignedIntegerSelectorType>(1, std::move(containedDt),
                                                                       std::move(selLoc),
                                                                       IntegerRangeSet<SInt> {std::move(ranges)},
                                                                       tryCloneUserAttrs(pseudoDt.userAttrs()));
    }

    return nullptr;
}

void DtFromPseudoRootDtConverter::_throwInvalDataLoc(const std::string& initMsg,
                                                     const TextLocation& initLoc,
                                                     const DataLocation& dataLoc,
                                                     const TextLocation& loc) const
{
    try {
        throwMetadataParseError(initMsg, initLoc);
    } catch (MetadataParseError& exc) {
        std::ostringstream ss;

        ss << "Invalid data location (`" <<
              this->_dataLocStr(dataLoc.scope(), dataLoc.begin(), dataLoc.end()) << "`):";
        appendMsgToMetadataParseError(exc, ss.str(), loc);
        throw;
    }
}

MapItem::UP DtFromPseudoRootDtConverter::_tryCloneUserAttrs(const MapItem * const userAttrs)
{
    return tryCloneUserAttrs(userAttrs);
}

} // namespace internal
} // namespace yactfr
