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
#include <yactfr/metadata/static-array-type.hpp>
#include <yactfr/metadata/static-text-array-type.hpp>
#include <yactfr/metadata/dyn-array-type.hpp>
#include <yactfr/metadata/dyn-text-array-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/metadata/metadata-parse-error.hpp>
#include <yactfr/internal/utils.hpp>

namespace yactfr {
namespace internal {

StructureType::UP dtFromPseudoRootDt(const PseudoDt& pseudoDt, const Scope scope,
                                     const PseudoTraceType& pseudoTraceType,
                                     const PseudoDst * const curPseudoDst,
                                     const PseudoErt * const curPseudoErt)
{
    return DtFromPseudoRootDtConverter {
        pseudoDt, scope, pseudoTraceType, curPseudoDst, curPseudoErt
    }.releaseDt();
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
     *    * The length integer types of dynamic array types.
     *    * The selector enumeration types of variant types.
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
     *    _findPseudoDts() uses the data above to make sure that it only
     *    finds the accessible data types depending on the context.
     */
    _dt = this->_structTypeFromPseudoDt(pseudoDt);
}

StructureType::UP DtFromPseudoRootDtConverter::_structTypeFromPseudoDt(const PseudoDt& pseudoDt)
{
    auto dt = this->_dtFromPseudoDt(pseudoDt);

    return StructureType::UP {static_cast<const StructureType *>(dt.release())};
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoDt(const PseudoDt& pseudoDt)
{
    switch (pseudoDt.kind()) {
    case PseudoDt::Kind::SCALAR_DT_WRAPPER:
        return this->_dtFromPseudoScalarDtWrapper(pseudoDt);

    case PseudoDt::Kind::INT_TYPE_WRAPPER:
        return this->_dtFromPseudoIntTypeWrapper(pseudoDt);

    case PseudoDt::Kind::STATIC_ARRAY:
        return this->_dtFromPseudoStaticArrayType(pseudoDt);

    case PseudoDt::Kind::DYN_ARRAY:
        return this->_dtFromPseudoDynArrayType(pseudoDt);

    case PseudoDt::Kind::STRUCT:
        return this->_dtFromPseudoStructType(pseudoDt);

    case PseudoDt::Kind::VAR:
        return this->_dtFromPseudoVarType(pseudoDt);

    default:
        std::abort();
    }
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoScalarDtWrapper(const PseudoDt& pseudoDt) const
{
    return static_cast<const PseudoScalarDtWrapper&>(pseudoDt).dt().clone();
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoIntTypeWrapper(const PseudoDt& pseudoDt) const
{
    auto& pseudoIntTypeWrapper = static_cast<const PseudoIntTypeWrapper&>(pseudoDt);
    auto& intType = pseudoIntTypeWrapper.intType();

    if (intType.isUnsignedIntegerType() && pseudoIntTypeWrapper.mappedClkTypeName()) {
        const ClockType *mappedClkType = nullptr;

        for (const auto& candClkType : _pseudoTraceType->clkTypes()) {
            if (*candClkType->name() == *pseudoIntTypeWrapper.mappedClkTypeName()) {
                mappedClkType = candClkType.get();
                break;
            }
        }

        if (!mappedClkType) {
            std::ostringstream ss;

            ss << "Unknown clock type `" << *pseudoIntTypeWrapper.mappedClkTypeName() << "`.";
            throw MetadataParseError {ss.str()};
        }

        if (intType.isUnsignedEnumerationType()) {
            auto& enumType = intType.asUnsignedEnumerationType();

            return std::make_unique<const UnsignedEnumerationType>(intType.alignment(),
                                                                   intType.length(),
                                                                   intType.byteOrder(),
                                                                   enumType.mappings(),
                                                                   intType.preferredDisplayBase(),
                                                                   mappedClkType);
        } else {
            return std::make_unique<const UnsignedIntegerType>(intType.alignment(), intType.length(),
                                                               intType.byteOrder(),
                                                               intType.preferredDisplayBase(),
                                                               mappedClkType);
        }
    } else {
        // no mapped clock type: return a simple clone
        return intType.clone();
    }
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoStaticArrayType(const PseudoDt& pseudoDt)
{
    auto& pseudoArrayType = static_cast<const PseudoStaticArrayType&>(pseudoDt);

    return this->_dtFromPseudoArrayType<StaticArrayType, StaticTextArrayType>(pseudoDt,
                                                                              pseudoArrayType.pseudoElemType(),
                                                                              pseudoArrayType.len());
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoDynArrayType(const PseudoDt& pseudoDt)
{
    auto& pseudoArrayType = static_cast<const PseudoDynArrayType&>(pseudoDt);
    const auto& lenLoc = _locMap[pseudoDt];

    try {
        const auto pseudoLenTypes = this->_findPseudoDts(lenLoc, pseudoDt.loc());

        assert(!pseudoLenTypes.empty());

        for (const auto pseudoLenType : pseudoLenTypes) {
            if (pseudoLenType->kind() != PseudoDt::Kind::INT_TYPE_WRAPPER) {
                throw MetadataParseError {
                    "Length type isn't an integer type.", pseudoLenType->loc()
                };
            }

            auto& pseudoIntLenType = static_cast<const PseudoIntTypeWrapper&>(*pseudoLenType);

            if (!pseudoIntLenType.intType().isUnsignedIntegerType()) {
                throw MetadataParseError {
                    "Length type isn't an unsigned integer type.", pseudoLenType->loc()
                };
            }
        }
    } catch (MetadataParseError& exc) {
        std::ostringstream ss;

        ss << "Invalid data location (`" <<
              this->_dataLocStr(lenLoc.scope(), lenLoc.begin(), lenLoc.end()) <<
              "`):";
        exc._appendErrorMsg(ss.str(), pseudoDt.loc());
        throw;
    }

    return this->_dtFromPseudoArrayType<DynamicArrayType,
                                        DynamicTextArrayType>(pseudoDt,
                                                              pseudoArrayType.pseudoElemType(),
                                                              lenLoc);
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoStructType(const PseudoDt& pseudoDt)
{
    StructureType::MemberTypes memberTypes;
    auto& pseudoStructType = static_cast<const PseudoStructType&>(pseudoDt);

    for (const auto& pseudoMemberType : pseudoStructType.pseudoMemberTypes()) {
        auto memberDt = this->_dtFromPseudoDt(pseudoMemberType->pseudoDt());

        memberTypes.push_back(std::make_unique<const StructureMemberType>(pseudoMemberType->name(),
                                                                          std::move(memberDt)));
    }

    return std::make_unique<const StructureType>(pseudoStructType.minAlign(),
                                                 std::move(memberTypes));
}

void DtFromPseudoRootDtConverter::_findPseudoDts(const PseudoDt& pseudoDt, const DataLocation& loc,
                                                 const DataLocation::PathElements::const_iterator locIt,
                                                 const TextLocation& srcLoc,
                                                 PseudoDtSet& pseudoDts) const
{
    switch (pseudoDt.kind()) {
    case PseudoDt::Kind::SCALAR_DT_WRAPPER:
    case PseudoDt::Kind::INT_TYPE_WRAPPER:
        if (locIt != loc.pathElements().end()) {
            std::ostringstream ss;

            ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "`: "
                  "nothing past scalar data type.";
            throw MetadataParseError {ss.str(), pseudoDt.loc()};
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
            throw MetadataParseError {ss.str(), pseudoDt.loc()};
        }

        this->_findPseudoDts(pseudoMemberType->pseudoDt(), loc, locIt + 1, srcLoc, pseudoDts);
        break;
    }

    case PseudoDt::Kind::STATIC_ARRAY:
    case PseudoDt::Kind::DYN_ARRAY:
    {
        if (_current.find(&pseudoDt) == _current.end()) {
            std::ostringstream ss;

            ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "`: "
                  "unreachable array element.";
            throw MetadataParseError {ss.str(), pseudoDt.loc()};
        }

        auto& pseudoArrayType = static_cast<const PseudoArrayType&>(pseudoDt);

        this->_findPseudoDts(pseudoArrayType.pseudoElemType(), loc, locIt, srcLoc, pseudoDts);
        break;
    }

    case PseudoDt::Kind::VAR:
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

    default:
        std::abort();
    }
}

PseudoDtSet DtFromPseudoRootDtConverter::_findPseudoDts(const DataLocation& loc,
                                                        const TextLocation& srcLoc) const
{
    if (static_cast<int>(loc.scope()) > static_cast<int>(_scope)) {
        std::ostringstream ss;

        ss << "`" << this->_dataLocStr(loc.scope(), loc.begin(), loc.end()) << "`: "
              "data would be unreachable.";
        throw MetadataParseError {ss.str(), srcLoc};
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
        throw MetadataParseError {ss.str(), srcLoc};
    }

    PseudoDtSet pseudoDts;

    this->_findPseudoDts(*pseudoDt, loc, loc.begin(), srcLoc, pseudoDts);
    return pseudoDts;
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoVarType(const PseudoDt& pseudoDt)
{
    auto& pseudoVarType = static_cast<const PseudoVarType&>(pseudoDt);
    const auto& selLoc = _locMap[pseudoDt];
    const PseudoIntTypeWrapper *pseudoIntSelType = nullptr;

    try {
        const auto pseudoSelTypes = this->_findPseudoDts(selLoc, pseudoDt.loc());

        assert(!pseudoSelTypes.empty());

        if (pseudoSelTypes.size() > 1) {
            std::ostringstream ss;

            ss << "Selector type of variant type (location: `" <<
                  this->_dataLocStr(selLoc.scope(), selLoc.begin(), selLoc.end()) <<
                  "`) targets more than one data type.";
            throw MetadataParseError {ss.str(), pseudoDt.loc()};
        }

        const auto& firstPseudoSelType = **pseudoSelTypes.begin();

        if (firstPseudoSelType.kind() != PseudoDt::Kind::INT_TYPE_WRAPPER) {
            throw MetadataParseError {
                "Selector type of variant type isn't an enumeration type.",
                firstPseudoSelType.loc()
            };
        }

        pseudoIntSelType = static_cast<const PseudoIntTypeWrapper *>(&firstPseudoSelType);

        if (!pseudoIntSelType->intType().isEnumerationType()) {
            throw MetadataParseError {
                "Selector type of variant type isn't an enumeration type.",
                firstPseudoSelType.loc()
            };
        }
    } catch (MetadataParseError& exc) {
        std::ostringstream ss;

        ss << "Invalid data location (`" <<
              this->_dataLocStr(selLoc.scope(), selLoc.begin(), selLoc.end()) <<
              "`):";
        exc._appendErrorMsg(ss.str(), pseudoDt.loc());
        throw;
    }

    assert(pseudoIntSelType);

    if (pseudoIntSelType->intType().isUnsignedIntegerType()) {
        return this->_dtFromPseudoVarType<VariantWithUnsignedSelectorType,
                                          UnsignedEnumerationType>(pseudoVarType, *pseudoIntSelType,
                                                                   selLoc);
    } else {
        return this->_dtFromPseudoVarType<VariantWithSignedSelectorType,
                                          SignedEnumerationType>(pseudoVarType, *pseudoIntSelType,
                                                                 selLoc);
    }
}

void DtFromPseudoRootDtConverter::_appendVarTypeInvalDataLocToMetadataParseErrorExc(const PseudoDt& pseudoDt,
                                                                                    const DataLocation& selLoc,
                                                                                    MetadataParseError& exc) const
{
    std::ostringstream ss;

    ss << "Invalid data location (`" <<
          this->_dataLocStr(selLoc.scope(), selLoc.begin(), selLoc.end()) << "`):";
    exc._appendErrorMsg(ss.str(), pseudoDt.loc());
}

} // namespace internal
} // namespace yactfr
