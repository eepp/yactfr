/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <iterator>
#include <cassert>
#include <tuple>
#include <set>
#include <sstream>

#include <yactfr/text-loc.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/text-parse-error.hpp>

#include "pseudo-types.hpp"
#include "pseudo-dt-visitor.hpp"
#include "pseudo-dt-utils.hpp"
#include "utils.hpp"

namespace yactfr {
namespace internal {

PseudoDataLoc::PseudoDataLoc(const bool isEnv, const bool isAbs, const Scope scope,
                             DataLocation::PathElements pathElems, TextLocation loc) :
    _isEnv {isEnv},
    _isAbs {isAbs},
    _scope {scope},
    _pathElems {std::move(pathElems)},
    _loc {std::move(loc)}
{
}

PseudoDt::PseudoDt(MapItem::UP userAttrs, TextLocation loc) :
    _userAttrs {std::move(userAttrs)},
    _loc {std::move(loc)}
{
}

bool PseudoDt::isEmpty() const
{
    return false;
}

bool PseudoDt::isInt() const noexcept
{
    return false;
}

bool PseudoDt::isUInt() const noexcept
{
    return false;
}

bool PseudoDt::isFlUInt() const noexcept
{
    return false;
}

PseudoScalarDtWrapper::PseudoScalarDtWrapper(DataType::UP dt, MapItem::UP userAttrs,
                                             TextLocation loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _dt {std::move(dt)}
{
}

PseudoScalarDtWrapper::PseudoScalarDtWrapper(DataType::UP dt, const bool hasEncoding,
                                             MapItem::UP userAttrs, TextLocation loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _dt {std::move(dt)},
    _hasEncoding {hasEncoding}
{
}

PseudoDt::UP PseudoScalarDtWrapper::clone() const
{
    return std::make_unique<PseudoScalarDtWrapper>(_dt->clone(),
                                                   tryCloneUserAttrs(this->userAttrs()),
                                                   this->loc());
}

bool PseudoScalarDtWrapper::isEmpty() const
{
    return _dt->isStaticLengthBlobType() && _dt->asStaticLengthBlobType().length() == 0;
}

void PseudoScalarDtWrapper::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoScalarDtWrapper::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

bool PseudoScalarDtWrapper::isInt() const noexcept
{
    return _dt->isFixedLengthIntegerType();
}

bool PseudoScalarDtWrapper::isUInt() const noexcept
{
    return _dt->isUnsignedIntegerType();
}

PseudoFlUIntType::PseudoFlUIntType(const unsigned int align, const unsigned int len,
                                   const ByteOrder bo, const DisplayBase prefDispBase,
                                   const bool hasEncoding,
                                   boost::optional<std::string> mappedClkTypeName,
                                   MapItem::UP userAttrs, TextLocation loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _align {align},
    _len {len},
    _bo {bo},
    _prefDispBase {prefDispBase},
    _hasEncoding {hasEncoding},
    _mappedClkTypeName {std::move(mappedClkTypeName)}
{
}

PseudoDt::UP PseudoFlUIntType::clone() const
{
    return std::make_unique<PseudoFlUIntType>(_align, _len, _bo, _prefDispBase, _hasEncoding,
                                              _mappedClkTypeName,
                                              tryCloneUserAttrs(this->userAttrs()), this->loc());
}

void PseudoFlUIntType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoFlUIntType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

bool PseudoFlUIntType::isInt() const noexcept
{
    return true;
}

bool PseudoFlUIntType::isUInt() const noexcept
{
    return true;
}

bool PseudoFlUIntType::isFlUInt() const noexcept
{
    return true;
}

PseudoFlUEnumType::PseudoFlUEnumType(const unsigned int align, const unsigned int len,
                                     const ByteOrder bo, const DisplayBase prefDispBase,
                                     FixedLengthUnsignedEnumerationType::Mappings mappings,
                                     const bool hasEncoding,
                                     boost::optional<std::string> mappedClkTypeName,
                                     MapItem::UP userAttrs, TextLocation loc) :
    PseudoFlUIntType {
        align, len, bo, prefDispBase, hasEncoding,
        std::move(mappedClkTypeName), std::move(userAttrs), std::move(loc)
    },
    _mappings {std::move(mappings)}
{
}

PseudoDt::UP PseudoFlUEnumType::clone() const
{
    return std::make_unique<PseudoFlUEnumType>(this->align(), this->len(), this->bo(),
                                               this->prefDispBase(), _mappings,
                                               this->hasEncoding(), this->mappedClkTypeName(),
                                               tryCloneUserAttrs(this->userAttrs()), this->loc());
}

void PseudoFlUEnumType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoFlUEnumType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoSlType::PseudoSlType(const Size len) :
    _len {len}
{
}

PseudoDlType::PseudoDlType(PseudoDataLoc pseudoLenLoc) :
    _pseudoLenLoc {std::move(pseudoLenLoc)}
{
}

PseudoArrayType::PseudoArrayType(PseudoDt::UP pseudoElemType, MapItem::UP userAttrs,
                                 TextLocation loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _pseudoElemType {std::move(pseudoElemType)}
{
}

PseudoSlArrayType::PseudoSlArrayType(const Size len, PseudoDt::UP pseudoElemType,
                                     MapItem::UP userAttrs, TextLocation loc) :
    PseudoArrayType {std::move(pseudoElemType), std::move(userAttrs), std::move(loc)},
    PseudoSlType {len}
{
}

PseudoDt::UP PseudoSlArrayType::clone() const
{
    return std::make_unique<PseudoSlArrayType>(_len, this->pseudoElemType().clone(),
                                               tryCloneUserAttrs(this->userAttrs()), this->loc());
}

bool PseudoSlArrayType::isEmpty() const
{
    if (_len == 0) {
        return true;
    }

    return this->pseudoElemType().isEmpty();
}

void PseudoSlArrayType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoSlArrayType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoDlArrayType::PseudoDlArrayType(PseudoDataLoc pseudoLenLoc, PseudoDt::UP pseudoElemType,
                                     MapItem::UP userAttrs, TextLocation loc) :
    PseudoArrayType {std::move(pseudoElemType), std::move(userAttrs), std::move(loc)},
    PseudoDlType {std::move(pseudoLenLoc)}
{
}

PseudoDt::UP PseudoDlArrayType::clone() const
{
    return std::make_unique<PseudoDlArrayType>(_pseudoLenLoc, this->pseudoElemType().clone(),
                                               tryCloneUserAttrs(this->userAttrs()), this->loc());
}

bool PseudoDlArrayType::isEmpty() const
{
    return this->pseudoElemType().isEmpty();
}

void PseudoDlArrayType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoDlArrayType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoBlobType::PseudoBlobType(boost::optional<std::string> mediaType, MapItem::UP userAttrs,
                               TextLocation loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _mediaType {std::move(mediaType)}
{
}

PseudoDlBlobType::PseudoDlBlobType(PseudoDataLoc pseudoLenLoc,
                                   boost::optional<std::string> mediaType, MapItem::UP userAttrs,
                                   TextLocation loc) :
    PseudoBlobType {std::move(mediaType), std::move(userAttrs), std::move(loc)},
    PseudoDlType {std::move(pseudoLenLoc)}
{
}

PseudoDt::UP PseudoDlBlobType::clone() const
{
    return std::make_unique<PseudoDlBlobType>(_pseudoLenLoc, this->mediaType(),
                                              tryCloneUserAttrs(this->userAttrs()), this->loc());
}

void PseudoDlBlobType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoDlBlobType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoNamedDt::PseudoNamedDt(std::string name, PseudoDt::UP pseudoDt, MapItem::UP userAttrs) :
    _name {std::move(name)},
    _pseudoDt {std::move(pseudoDt)},
    _userAttrs {std::move(userAttrs)}
{
}

PseudoStructType::PseudoStructType(const unsigned int minAlign, PseudoNamedDts&& pseudoMemberTypes,
                                   MapItem::UP userAttrs, TextLocation loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _minAlign {minAlign},
    _pseudoMemberTypes {std::move(pseudoMemberTypes)}
{
}

PseudoDt::UP PseudoStructType::clone() const
{
    PseudoNamedDts newPseudoMembers;

    for (const auto& pseudoMemberType : _pseudoMemberTypes) {
        auto newPseudoMemberType = std::make_unique<PseudoNamedDt>(pseudoMemberType->name(),
                                                                   pseudoMemberType->pseudoDt().clone(),
                                                                   tryCloneUserAttrs(pseudoMemberType->userAttrs()));

        newPseudoMembers.push_back(std::move(newPseudoMemberType));
    }

    return std::make_unique<PseudoStructType>(_minAlign, std::move(newPseudoMembers),
                                              tryCloneUserAttrs(this->userAttrs()), this->loc());
}

bool PseudoStructType::isEmpty() const
{
    if (_pseudoMemberTypes.empty()) {
        return true;
    }

    auto isEmpty = true;

    for (auto& pseudoMemberType : _pseudoMemberTypes) {
        isEmpty = isEmpty && pseudoMemberType->pseudoDt().isEmpty();
    }

    return isEmpty;
}

void PseudoStructType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoStructType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

const PseudoNamedDt *PseudoStructType::operator[](const std::string& name) const noexcept
{
    const auto it = std::find_if(_pseudoMemberTypes.begin(), _pseudoMemberTypes.end(),
                                 [&name](const auto& pseudoMember) {
        return pseudoMember->name() == name;
    });

    if (it == _pseudoMemberTypes.end()) {
        return nullptr;
    }

    return it->get();
}

PseudoVarType::PseudoVarType(boost::optional<PseudoDataLoc> pseudoSelLoc,
                             PseudoNamedDts&& pseudoOpts, MapItem::UP userAttrs, TextLocation loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _pseudoSelLoc {std::move(pseudoSelLoc)},
    _pseudoOpts {std::move(pseudoOpts)}
{
}

PseudoNamedDts PseudoVarType::_clonePseudoOpts() const
{
    PseudoNamedDts newPseudoOpts;

    for (const auto& pseudoOpt : _pseudoOpts) {
        auto newPseudoOpt = std::make_unique<PseudoNamedDt>(pseudoOpt->name(),
                                                            pseudoOpt->pseudoDt().clone(),
                                                            tryCloneUserAttrs(pseudoOpt->userAttrs()));

        newPseudoOpts.push_back(std::move(newPseudoOpt));
    }

    return newPseudoOpts;
}

PseudoDt::UP PseudoVarType::clone() const
{
   return std::make_unique<PseudoVarType>(_pseudoSelLoc, this->_clonePseudoOpts(),
                                          tryCloneUserAttrs(this->userAttrs()), this->loc());
}

bool PseudoVarType::isEmpty() const
{
    auto isEmpty = true;

    for (auto& pseudoOpt : _pseudoOpts) {
        isEmpty = isEmpty && pseudoOpt->pseudoDt().isEmpty();
    }

    return isEmpty;
}

void PseudoVarType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoVarType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoVarWithIntRangesType::PseudoVarWithIntRangesType(boost::optional<PseudoDataLoc> pseudoSelLoc,
                                                       PseudoNamedDts&& pseudoOpts,
                                                       RangeSets&& rangeSets,
                                                       MapItem::UP userAttrs, TextLocation loc) :
    PseudoVarType {
        std::move(pseudoSelLoc), std::move(pseudoOpts), std::move(userAttrs), std::move(loc)
    },
    _rangeSets {std::move(rangeSets)}
{
    assert(this->pseudoOpts().size() == _rangeSets.size());
}

PseudoDt::UP PseudoVarWithIntRangesType::clone() const
{
    return std::make_unique<PseudoVarWithIntRangesType>(this->pseudoSelLoc(),
                                                        this->_clonePseudoOpts(),
                                                        RangeSets {_rangeSets},
                                                        tryCloneUserAttrs(this->userAttrs()),
                                                        this->loc());
}

void PseudoVarWithIntRangesType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoVarWithIntRangesType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoOptType::PseudoOptType(PseudoDt::UP pseudoDt, PseudoDataLoc&& pseudoSelLoc,
                             MapItem::UP userAttrs, TextLocation&& loc) :
    PseudoDt {std::move(userAttrs), std::move(loc)},
    _pseudoDt {std::move(pseudoDt)},
    _pseudoSelLoc {std::move(pseudoSelLoc)}
{
}

bool PseudoOptType::isEmpty() const
{
    return _pseudoDt->isEmpty();
}

PseudoOptWithBoolSelType::PseudoOptWithBoolSelType(PseudoDt::UP pseudoDt,
                                                   PseudoDataLoc pseudoSelLoc,
                                                   MapItem::UP userAttrs, TextLocation loc) :
    PseudoOptType {
        std::move(pseudoDt), std::move(pseudoSelLoc),
        std::move(userAttrs), std::move(loc)
    }
{
}

PseudoDt::UP PseudoOptWithBoolSelType::clone() const
{
    return std::make_unique<PseudoOptWithBoolSelType>(this->pseudoDt().clone(),
                                                      this->pseudoSelLoc(),
                                                      tryCloneUserAttrs(this->userAttrs()),
                                                      this->loc());
}

void PseudoOptWithBoolSelType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoOptWithBoolSelType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoOptWithIntSelType::PseudoOptWithIntSelType(PseudoDt::UP pseudoDt, PseudoDataLoc pseudoSelLoc,
                                                 RangeSet&& selRanges, MapItem::UP userAttrs,
                                                 TextLocation loc) :
    PseudoOptType {
        std::move(pseudoDt), std::move(pseudoSelLoc),
        std::move(userAttrs), std::move(loc)
    },
    _selRanges {std::move(selRanges)}
{
}

PseudoDt::UP PseudoOptWithIntSelType::clone() const
{
    return std::make_unique<PseudoOptWithIntSelType>(this->pseudoDt().clone(),
                                                     this->pseudoSelLoc(), RangeSet {_selRanges},
                                                     tryCloneUserAttrs(this->userAttrs()),
                                                     this->loc());
}

void PseudoOptWithIntSelType::accept(PseudoDtVisitor& visitor)
{
    visitor.visit(*this);
}

void PseudoOptWithIntSelType::accept(ConstPseudoDtVisitor& visitor) const
{
    visitor.visit(*this);
}

PseudoErt::PseudoErt(const TypeId id, boost::optional<std::string> ns,
                     boost::optional<std::string> name, boost::optional<LogLevel> logLevel,
                     boost::optional<std::string> emfUri, PseudoDt::UP pseudoSpecCtxType,
                     PseudoDt::UP pseudoPayloadType, MapItem::UP userAttrs) :
    _id {id},
    _ns {std::move(ns)},
    _name {std::move(name)},
    _logLevel {std::move(logLevel)},
    _emfUri {std::move(emfUri)},
    _pseudoSpecCtxType {std::move(pseudoSpecCtxType)},
    _pseudoPayloadType {std::move(pseudoPayloadType)},
    _userAttrs {std::move(userAttrs)}
{
}

void PseudoErt::_validateNotEmpty(const PseudoDst& pseudoDst) const
{
    /*
     * Make sure that we can't guarantee that an instance of this event
     * record type is empty.
     */
    if (_pseudoPayloadType && !_pseudoPayloadType->isEmpty()) {
        return;
    }

    if (_pseudoSpecCtxType && !_pseudoSpecCtxType->isEmpty()) {
        return;
    }

    if (pseudoDst.pseudoErCommonCtxType() && !pseudoDst.pseudoErCommonCtxType()->isEmpty()) {
        return;
    }

    if (pseudoDst.pseudoErHeaderType() && !pseudoDst.pseudoErHeaderType()->isEmpty()) {
        return;
    }

    std::ostringstream ss;

    ss << "Any event record would be empty (no data).";
    throwTextParseError(ss.str());
}

static auto validateNoMappedClkTypeName(const PseudoDt& basePseudoDt)
{
    const auto pseudoDts = findPseudoUIntTypes(basePseudoDt, [](auto& pseudoIntType, auto) {
        if (!pseudoIntType.isFlUInt()) {
            return false;
        }

        return static_cast<const PseudoFlUIntType&>(pseudoIntType).mappedClkTypeName().has_value();
    });

    if (!pseudoDts.empty()) {
        throwTextParseError("At least one fixed-length unsigned integer type "
                            "is mapped to a clock type; "
                            "this isn't not supported within this scope.",
                            basePseudoDt.loc());
    }
}

void PseudoErt::_validateNoMappedClkTypeName(const PseudoDst& pseudoDst) const
{
    if (_pseudoSpecCtxType) {
        try {
            validateNoMappedClkTypeName(*_pseudoSpecCtxType);
        } catch (TextParseError& exc) {
            std::ostringstream ss;

            appendMsgToTextParseError(exc, "In the specific context type:",
                                      _pseudoSpecCtxType->loc());
            throw;
        }
    }

    if (_pseudoPayloadType) {
        try {
            validateNoMappedClkTypeName(*_pseudoPayloadType);
        } catch (TextParseError& exc) {
            std::ostringstream ss;

            appendMsgToTextParseError(exc, "In the payload type:", _pseudoPayloadType->loc());
            throw;
        }
    }
}

template <typename PseudoTypeT>
static std::string pseudoTypeIdenStr(const PseudoTypeT& pseudoDst)
{
    std::ostringstream ss;

    ss << pseudoDst.id();

    if (pseudoDst.name() || pseudoDst.ns()) {
        ss << '(';

        if (pseudoDst.name()) {
            ss << "named `" << *pseudoDst.name() << '`';

            if (pseudoDst.ns()) {
                ss << ' ';
            }
        }

        if (pseudoDst.ns()) {
            ss << "within namespace `" << *pseudoDst.ns() << '`';
        }

        ss << ')';
    }

    return ss.str();
}

void PseudoErt::validate(const PseudoDst& pseudoDst) const
{
    try {
        this->_validateNotEmpty(pseudoDst);
        this->_validateNoMappedClkTypeName(pseudoDst);
    } catch (TextParseError& exc) {
        std::ostringstream ss;

        ss << "In the event record type " << pseudoTypeIdenStr(*this) <<
              " of data stream type " << pseudoTypeIdenStr(pseudoDst) << ":";
        appendMsgToTextParseError(exc, ss.str());
        throw;
    }
}

PseudoOrphanErt::PseudoOrphanErt(PseudoErt pseudoErt, TextLocation loc) :
    _pseudoErt {std::move(pseudoErt)},
    _loc {std::move(loc)}
{
}

PseudoDst::PseudoDst(const TypeId id, boost::optional<std::string> ns,
                     boost::optional<std::string> name, PseudoDt::UP pseudoPktCtxType,
                     PseudoDt::UP pseudoErHeaderType, PseudoDt::UP pseudoErCommonCtxType,
                     const ClockType * const defClkType, MapItem::UP userAttrs) :
    _id {id},
    _ns {std::move(ns)},
    _name {std::move(name)},
    _pseudoPktCtxType {std::move(pseudoPktCtxType)},
    _pseudoErHeaderType {std::move(pseudoErHeaderType)},
    _pseudoErCommonCtxType {std::move(pseudoErCommonCtxType)},
    _defClkType {defClkType},
    _userAttrs {std::move(userAttrs)}
{
}

static auto findPseudoSlArrayTypesWithTraceTypeUuidRole(const PseudoDt& basePseudoDt)
{
    return findPseudoDts(basePseudoDt, [](auto& pseudoDt, auto) {
        return pseudoDt.kind() == PseudoDt::Kind::SL_ARRAY &&
            static_cast<const PseudoSlArrayType&>(pseudoDt).hasTraceTypeUuidRole();
    });
}

static auto findPseudoUIntTypesByRole(const PseudoDt& basePseudoDt,
                                      const UnsignedIntegerTypeRole role)
{
    return findPseudoUIntTypes(basePseudoDt, [role](auto& pseudoIntType, auto) {
        if (pseudoIntType.isFlUInt()) {
            return static_cast<const PseudoFlUIntType&>(pseudoIntType).hasRole(role);
        } else {
            assert(pseudoIntType.kind() == PseudoDt::Kind::SCALAR_DT_WRAPPER);

            auto& pseudoVlIntType = static_cast<const PseudoScalarDtWrapper&>(pseudoIntType);

            return pseudoVlIntType.dt().asVariableLengthUnsignedIntegerType().hasRole(role);
        }
    });
}

void PseudoDst::_validateErHeaderType(const PseudoErtSet& pseudoErts) const
{
    if (_pseudoErHeaderType) {
        try {
            /*
             * Validate pseudo unsigned integer types with an "event
             * record type ID" role.
             */
            const auto idPseudoDts = findPseudoUIntTypesByRole(*_pseudoErHeaderType,
                                                               UnsignedIntegerTypeRole::EVENT_RECORD_TYPE_ID);

            /*
             * Without any pseudo unsigned integer type with an "event
             * record type ID" role, there may be only one (implicit)
             * event record type.
             */
            if (idPseudoDts.empty() && pseudoErts.size() > 1) {
                throwTextParseError("No structure member type with the "
                                    "\"event record type ID\" role, "
                                    "but the data stream type contains "
                                    "more than one event record type.",
                                    _pseudoErHeaderType->loc());
            }
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "In the event record header type:",
                                      _pseudoErHeaderType->loc());
            throw;
        }
    }
}

void PseudoDst::_validateNoMappedClkTypeName() const
{
    if (_pseudoErCommonCtxType) {
        try {
            validateNoMappedClkTypeName(*_pseudoErCommonCtxType);
        } catch (TextParseError& exc) {
            std::ostringstream ss;

            appendMsgToTextParseError(exc, "In the event record common context type:",
                                      _pseudoErCommonCtxType->loc());
            throw;
        }
    }
}

void PseudoDst::validate(const PseudoErtSet& pseudoErts) const
{
    try {
        this->_validateErHeaderType(pseudoErts);
        this->_validateNoMappedClkTypeName();
    } catch (TextParseError& exc) {
        std::ostringstream ss;

        ss << "In data stream type " << pseudoTypeIdenStr(*this) << ':';
        appendMsgToTextParseError(exc, ss.str());
        throw;
    }
}

PseudoTraceType::PseudoTraceType(const unsigned int majorVersion, const unsigned int minorVersion,
                                 const ByteOrder nativeBo,
                                 boost::optional<boost::uuids::uuid> uuid,
                                 PseudoDt::UP pseudoPktHeaderType, MapItem::UP userAttrs) :
    _majorVersion {majorVersion},
    _minorVersion {minorVersion},
    _nativeBo {nativeBo},
    _uuid {std::move(uuid)},
    _pseudoPktHeaderType {std::move(pseudoPktHeaderType)},
    _userAttrs {std::move(userAttrs)}
{
}

void PseudoTraceType::validate() const
{
    // validate that all orphan ERTs match the real ERTs
    for (const auto& dstIdPseudoOrphanErtsPair : _pseudoOrphanErts) {
        if (_pseudoDsts.find(dstIdPseudoOrphanErtsPair.first) == _pseudoDsts.end()) {
            std::ostringstream ss;

            ss << "Event record type needs a data stream type " <<
                  "(with ID " << dstIdPseudoOrphanErtsPair.first << ") which doesn't exist.";
            assert(!dstIdPseudoOrphanErtsPair.second.empty());

            const auto& firstPseudoErt = dstIdPseudoOrphanErtsPair.second.begin()->second;

            throwTextParseError(ss.str(), firstPseudoErt.loc());
        }
    }

    // validate packet header type
    if (_pseudoPktHeaderType) {
        try {
            /*
             * Validate pseudo static-length array types with the "trace
             * type UUID" role.
             */
            const auto pseudoUuidDts = findPseudoSlArrayTypesWithTraceTypeUuidRole(*_pseudoPktHeaderType);

            for (auto& pseudoUuidDt : pseudoUuidDts) {
                auto& pseudoUuidArrayType = static_cast<const PseudoSlArrayType&>(*pseudoUuidDt);

                try {
                    if (pseudoUuidArrayType.len() != 16) {
                        throwTextParseError("Expecting a 16-element static-length array type.",
                                            pseudoUuidDt->loc());
                    }

                    if (!pseudoUuidArrayType.pseudoElemType().isFlUInt()) {
                        throwTextParseError("Expecting a fixed-length integer type.",
                                            pseudoUuidArrayType.pseudoElemType().loc());
                    }

                    auto& pseudoUIntType = static_cast<const PseudoFlUIntType&>(pseudoUuidArrayType.pseudoElemType());

                    if (pseudoUIntType.len() != 8) {
                        throwTextParseError("Expecting a fixed-length unsigned integer type "
                                            "with a length of 8 bits.",
                                            pseudoUIntType.loc());
                    }
                } catch (TextParseError& exc) {
                    appendMsgToTextParseError(exc,
                                              "Static-length array type with a \"trace type UUID\" role:",
                                              pseudoUuidDt->loc());
                    throw;
                }
            }

            /*
             * Validate pseudo unsigned integer types with the "packet
             * magic number" role.
             */
            const auto pseudoMagicDts = findPseudoUIntTypesByRole(*_pseudoPktHeaderType,
                                                                    UnsignedIntegerTypeRole::PACKET_MAGIC_NUMBER);

            if (pseudoMagicDts.size() == 1) {
                auto& firstPseudoDt = **pseudoMagicDts.begin();

                if (!firstPseudoDt.isFlUInt()) {
                    throwTextParseError("Unsigned integer type with the "
                                        "\"packet magic number\" role must be a "
                                        "fixed-length integer type.",
                                        firstPseudoDt.loc());
                }

                auto& pseudoMagicDt = static_cast<const PseudoFlUIntType&>(firstPseudoDt);
                auto& pseudoPktHeaderType = static_cast<const PseudoStructType&>(*_pseudoPktHeaderType);

                if (&pseudoPktHeaderType.pseudoMemberTypes()[0]->pseudoDt() != &pseudoMagicDt) {
                    throwTextParseError("Fixed-length unsigned integer type with the "
                                        "\"packet magic number\" role must be within the "
                                        "first member type of the packet header structure type.",
                                        pseudoMagicDt.loc());
                }

                if (pseudoMagicDt.len() != 32) {
                    throwTextParseError("Fixed-length unsigned integer type with the "
                                        "\"packet magic number\" role must have a length of "
                                        "32 bits.",
                                        pseudoMagicDt.loc());
                }
            } else if (pseudoMagicDts.size() > 1) {
                throwTextParseError("More than one fixed-length unsigned integer type with the "
                                    "\"packet magic number\" role found.",
                                    _pseudoPktHeaderType->loc());
            }

            /*
             * Without any pseudo unsigned integer type with a "data
             * stream type ID" role, there may be only one (implicit)
             * data stream type.
             */
            if (_pseudoDsts.size() > 1 &&
                    findPseudoUIntTypesByRole(*_pseudoPktHeaderType,
                                              UnsignedIntegerTypeRole::DATA_STREAM_TYPE_ID).empty()) {
                throwTextParseError("No structure member type with the "
                                    "\"data stream type ID\" role, "
                                    "but the trace type contains "
                                    "more than one data stream type.",
                                    _pseudoPktHeaderType->loc());
            }

            // no mapped clock type within the packet header type
            validateNoMappedClkTypeName(*_pseudoPktHeaderType);
        } catch (TextParseError& exc) {
            appendMsgToTextParseError(exc, "In the packet header type:",
                                      _pseudoPktHeaderType->loc());
            throw;
        }
    }
}

} // namespace internal
} // namespace yactfr
