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
#include <sstream>

#include <yactfr/text-loc.hpp>
#include <yactfr/metadata/internal/pseudo-types.hpp>
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

PseudoDataLoc::PseudoDataLoc(const bool isEnv, const bool isAbs, const Scope scope,
                             DataLocation::PathElements pathElems, TextLocation loc) :
    _isEnv {isEnv},
    _isAbs {isAbs},
    _scope {scope},
    _pathElems {std::move(pathElems)},
    _loc {std::move(loc)}
{
}

PseudoDt::PseudoDt(TextLocation loc) :
    _loc {std::move(loc)}
{
}

PseudoDt::~PseudoDt()
{
}

bool PseudoDt::isEmpty() const
{
    return false;
}

PseudoDtSet PseudoDt::findPseudoDtsByName(const std::string& name) const
{
    PseudoDtSet pseudoDts;

    this->_findPseudoDtsByName(name, pseudoDts);
    return pseudoDts;
}

void PseudoDt::_findPseudoDtsByName(const PseudoDt& pseudoDt, const std::string& name,
                                    PseudoDtSet& pseudoDts)
{
    pseudoDt._findPseudoDtsByName(name, pseudoDts);
}

void PseudoDt::_findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const
{
}

PseudoScalarDtWrapper::PseudoScalarDtWrapper(DataType::UP dt, TextLocation loc) :
    PseudoDt {std::move(loc)},
    _dt {std::move(dt)}
{
}

PseudoDt::UP PseudoScalarDtWrapper::clone() const
{
    return std::make_unique<PseudoScalarDtWrapper>(_dt->clone(), this->loc());
}

PseudoIntTypeWrapper::PseudoIntTypeWrapper(DataType::UP dt, const bool hasEncoding,
                                           boost::optional<std::string> mappedClkTypeName,
                                           TextLocation loc) :
    PseudoScalarDtWrapper {std::move(dt), std::move(loc)},
    _hasEncoding {hasEncoding},
    _mappedClkTypeName {std::move(mappedClkTypeName)}
{
}

PseudoDt::UP PseudoIntTypeWrapper::clone() const
{
    return std::make_unique<PseudoIntTypeWrapper>(this->dt().clone(), _hasEncoding,
                                                  _mappedClkTypeName, this->loc());
}

PseudoArrayType::PseudoArrayType(PseudoDt::UP pseudoElemType, TextLocation loc) :
    PseudoDt {std::move(loc)},
    _pseudoElemType {std::move(pseudoElemType)}
{
}

void PseudoArrayType::_findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const
{
    PseudoDt::_findPseudoDtsByName(*_pseudoElemType, name, pseudoDts);
}

PseudoStaticArrayType::PseudoStaticArrayType(const Size len, PseudoDt::UP pseudoElemType,
                                             TextLocation loc) :
    PseudoArrayType {std::move(pseudoElemType), std::move(loc)},
    _len {len}
{
}

PseudoDt::UP PseudoStaticArrayType::clone() const
{
    return std::make_unique<PseudoStaticArrayType>(_len, this->pseudoElemType().clone(),
                                                   this->loc());
}

bool PseudoStaticArrayType::isEmpty() const
{
    if (_len == 0) {
        return true;
    }

    return this->pseudoElemType().isEmpty();
}

PseudoDynArrayType::PseudoDynArrayType(PseudoDataLoc pseudoLenLoc, PseudoDt::UP pseudoElemType,
                                       TextLocation loc) :
    PseudoArrayType {std::move(pseudoElemType), std::move(loc)},
    _pseudoLenLoc {std::move(pseudoLenLoc)}
{
}

PseudoDt::UP PseudoDynArrayType::clone() const
{
    return std::make_unique<PseudoDynArrayType>(_pseudoLenLoc, this->pseudoElemType().clone(),
                                                this->loc());
}

bool PseudoDynArrayType::isEmpty() const
{
    return this->pseudoElemType().isEmpty();
}

PseudoNamedDt::PseudoNamedDt(std::string name, PseudoDt::UP pseudoDt) :
    _name {std::move(name)},
    _pseudoDt {std::move(pseudoDt)}
{
}

PseudoStructType::PseudoStructType(const unsigned int minAlign, PseudoNamedDts&& pseudoMemberTypes,
                                   TextLocation loc) :
    PseudoDt {std::move(loc)},
    _minAlign {minAlign},
    _pseudoMemberTypes {std::move(pseudoMemberTypes)}
{
}

PseudoDt::UP PseudoStructType::clone() const
{
    PseudoNamedDts newPseudoMembers;

    for (const auto& pseudoMemberType : _pseudoMemberTypes) {
        auto newPseudoMemberType = std::make_unique<PseudoNamedDt>(pseudoMemberType->name(),
                                                                   pseudoMemberType->pseudoDt().clone());

        newPseudoMembers.push_back(std::move(newPseudoMemberType));
    }

    return std::make_unique<PseudoStructType>(_minAlign, std::move(newPseudoMembers), this->loc());
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

void PseudoStructType::_findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const
{
    for (auto& pseudoMemberType : _pseudoMemberTypes) {
        if (pseudoMemberType->name() == name) {
            pseudoDts.insert(&pseudoMemberType->pseudoDt());
        }

        PseudoDt::_findPseudoDtsByName(pseudoMemberType->pseudoDt(), name, pseudoDts);
    }
}

PseudoVarType::PseudoVarType(boost::optional<PseudoDataLoc> pseudoSelLoc, PseudoNamedDts&& pseudoOpts,
                             TextLocation loc) :
    PseudoDt {std::move(loc)},
    _pseudoSelLoc {std::move(pseudoSelLoc)},
    _pseudoOpts {std::move(pseudoOpts)}
{
}

PseudoDt::UP PseudoVarType::clone() const
{
    PseudoNamedDts newPseudoOpts;

    for (const auto& pseudoOpt : _pseudoOpts) {
        auto newPseudoOpt = std::make_unique<PseudoNamedDt>(pseudoOpt->name(),
                                                            pseudoOpt->pseudoDt().clone());

        newPseudoOpts.push_back(std::move(newPseudoOpt));
    }

    return std::make_unique<PseudoVarType>(_pseudoSelLoc, std::move(newPseudoOpts), this->loc());
}

bool PseudoVarType::isEmpty() const
{
    auto isEmpty = true;

    for (auto& pseudoOpt : _pseudoOpts) {
        isEmpty = isEmpty && pseudoOpt->pseudoDt().isEmpty();
    }

    return isEmpty;
}

void PseudoVarType::_findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const
{
    for (auto& pseudoOpt : _pseudoOpts) {
        PseudoDt::_findPseudoDtsByName(pseudoOpt->pseudoDt(), name, pseudoDts);
    }
}

void PseudoValidatableType::_validateIsPseudoUIntType(const PseudoDt& pseudoDt,
                                                      const std::string& name,
                                                      const boost::optional<Size>& len) const
{
    if (pseudoDt.kind() != PseudoDt::Kind::INT_TYPE_WRAPPER) {
        std::ostringstream ss;

        ss << "Expecting `" << name << "` to be an integer type.";
        this->_throwParseError(ss.str(), pseudoDt.loc());
    }

    auto& pseudoIntType = static_cast<const PseudoIntTypeWrapper&>(pseudoDt);

    if (!pseudoIntType.intType().isUnsignedIntegerType()) {
        std::ostringstream ss;

        ss << "Expecting `" << name << "` to be an unsigned integer type.";
        this->_throwParseError(ss.str(), pseudoDt.loc());
    }

    if (len && pseudoIntType.intType().length() != *len) {
        std::ostringstream ss;

        ss << "Expecting `" << name << "` to be a " << *len << "-bit "
              "unsigned integer type.";
        this->_throwParseError(ss.str(), pseudoDt.loc());
    }
}

void PseudoValidatableType::_validateIsPseudoUIntTypeMember(const PseudoDt& pseudoDt,
                                                            const std::string& memberTypeName,
                                                            const boost::optional<Size>& len) const
{
    std::ostringstream ss;

    ss << "structure member type `" << memberTypeName << "`";
    this->_validateIsPseudoUIntType(pseudoDt, ss.str(), len);
}

void PseudoValidatableType::_validateIsPseudoUIntTypeMemberIfExists(const PseudoDt& parentPseudoDt,
                                                                    const std::string& memberTypeName,
                                                                    const boost::optional<Size>& len) const
{
    assert(parentPseudoDt.kind() == PseudoDt::Kind::STRUCT);

    auto& pseudoStructType = static_cast<const PseudoStructType&>(parentPseudoDt);
    auto pseudoMemberType = pseudoStructType[memberTypeName];

    if (!pseudoMemberType) {
        return;
    }

    this->_validateIsPseudoUIntTypeMember(pseudoMemberType->pseudoDt(), memberTypeName, len);
}

void PseudoValidatableType::_throwParseError(std::string msg, TextLocation textLoc) const
{
    throw MetadataParseError {std::move(msg), std::move(textLoc)};
}

void PseudoValidatableType::_appendErrorMsgToParseError(MetadataParseError& exc, std::string msg,
                                                        TextLocation textLoc) const
{
    exc._appendErrorMsg(std::move(msg), std::move(textLoc));
}

PseudoErt::PseudoErt(const TypeId id, boost::optional<std::string> name,
                     boost::optional<LogLevel> logLevel, boost::optional<std::string> emfUri,
                     PseudoDt::UP pseudoSpecCtxType, PseudoDt::UP pseudoPayloadType) :
    _id {id},
    _name {std::move(name)},
    _logLevel {std::move(logLevel)},
    _emfUri {std::move(emfUri)},
    _pseudoSpecCtxType {std::move(pseudoSpecCtxType)},
    _pseudoPayloadType {std::move(pseudoPayloadType)}
{
}

void PseudoErt::validate(const PseudoDst& pseudoDst) const
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

    ss << "Any event record with type ID " << _id << " within a data stream with "
          "type ID " << _id << " would be empty (no data).";
    this->_throwParseError(ss.str());
}

PseudoOrphanErt::PseudoOrphanErt(PseudoErt pseudoErt, TextLocation loc) :
    _pseudoErt {std::move(pseudoErt)},
    _loc {std::move(loc)}
{
}

PseudoDst::PseudoDst(const TypeId id, PseudoDt::UP pseudoPktCtxType,
                     PseudoDt::UP pseudoErHeaderType, PseudoDt::UP pseudoErCommonCtxType) :
    _id {id},
    _pseudoPktCtxType {std::move(pseudoPktCtxType)},
    _pseudoErHeaderType {std::move(pseudoErHeaderType)},
    _pseudoErCommonCtxType {std::move(pseudoErCommonCtxType)}
{
}

void PseudoDst::validate(const PseudoErtSet& pseudoErts) const
{
    // validate packet context type
    if (_pseudoPktCtxType) {
        try {
            // validate data types
            this->_validateIsPseudoUIntTypeMemberIfExists(*_pseudoPktCtxType, "packet_size");
            this->_validateIsPseudoUIntTypeMemberIfExists(*_pseudoPktCtxType, "content_size");
            this->_validateIsPseudoUIntTypeMemberIfExists(*_pseudoPktCtxType, "events_discarded");
        } catch (MetadataParseError& exc) {
            std::ostringstream ss;

            ss << "In the packet context type of data stream type " << _id << ":";
            this->_appendErrorMsgToParseError(exc, ss.str(), _pseudoPktCtxType->loc());
            throw;
        }
    }

    // validate event record header type
    if (_pseudoErHeaderType) {
        try {
            // validate `id` data types
            const auto idPseudoDts = _pseudoErHeaderType->findPseudoDtsByName("id");

            for (const auto pseudoDt : idPseudoDts) {
                this->_validateIsPseudoUIntType(*pseudoDt, "id");
            }

            /*
             * Without any `id` member, there may be only one (implicit)
             * event record type.
             */
            if (idPseudoDts.empty() && pseudoErts.size() > 1) {
                this->_throwParseError("No structure member type named `id`, "
                                       "but the data stream type contains "
                                       "more than one event record type.",
                                       _pseudoErHeaderType->loc());
            }
        } catch (MetadataParseError& exc) {
            std::ostringstream ss;

            ss << "In the event record header type of data stream type " << _id << ":";
            this->_appendErrorMsgToParseError(exc, ss.str(), _pseudoErHeaderType->loc());
            throw;
        }
    }
}

PseudoTraceType::PseudoTraceType(const unsigned int majorVersion, const unsigned int minorVersion,
                                 const ByteOrder nativeBo, boost::optional<boost::uuids::uuid> uuid,
                                 PseudoDt::UP pseudoPktHeaderType) :
    _majorVersion {majorVersion},
    _minorVersion {minorVersion},
    _nativeBo {nativeBo},
    _uuid {std::move(uuid)},
    _pseudoPktHeaderType {std::move(pseudoPktHeaderType)}
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

            this->_throwParseError(ss.str(), firstPseudoErt.loc());
        }
    }

    // validate packet header type
    if (_pseudoPktHeaderType) {
        try {
            // validate data types
            this->_validateIsPseudoUIntTypeMemberIfExists(*_pseudoPktHeaderType, "magic", 32);
            this->_validateIsPseudoUIntTypeMemberIfExists(*_pseudoPktHeaderType, "stream_id");
            this->_validateIsPseudoUIntTypeMemberIfExists(*_pseudoPktHeaderType,
                                                          "stream_instance_id");

            const auto uuidDts = _pseudoPktHeaderType->findPseudoDtsByName("uuid");

            if (uuidDts.size() == 1) {
                auto& uuidDt = **uuidDts.begin();

                if (uuidDt.kind() != PseudoDt::Kind::STATIC_ARRAY) {
                    std::ostringstream ss;

                    ss << "`uuid` member type: expecting a static array type.";
                    this->_throwParseError(ss.str(), uuidDt.loc());
                }

                auto& uuidArrayType = static_cast<const PseudoStaticArrayType&>(uuidDt);

                if (uuidArrayType.len() != 16) {
                    this->_throwParseError("`uuid` member type: expecting a 16-element static array type.",
                                           uuidDt.loc());
                }

                this->_validateIsPseudoUIntTypeMember(uuidArrayType.pseudoElemType(),
                                                      "element type of `uuid` member type", 8);
            } else if (uuidDts.size() > 1) {
                std::ostringstream ss;

                ss << "Packet header type contains more than one (" << uuidDts.size() << ") type "
                      "named `uuid`.";
                this->_throwParseError(ss.str(), _pseudoPktHeaderType->loc());
            }

            // validate that the `magic` member type is the first, if any
            auto& pseudoPktHeaderType = static_cast<const PseudoStructType&>(*_pseudoPktHeaderType);

            for (auto i = 0U; i < pseudoPktHeaderType.pseudoMemberTypes().size(); ++i) {
                const auto& pseudoMemberType = pseudoPktHeaderType.pseudoMemberTypes()[i];

                if (pseudoMemberType->name() == "magic" && i != 0) {
                    this->_throwParseError("`magic` member type must be the first.",
                                           pseudoMemberType->pseudoDt().loc());
                }
            }

            /*
             * Without a `stream_id` member, there may be only one
             * (implicit) data stream type.
             */
            if (_pseudoDsts.size() > 1 && !pseudoPktHeaderType["stream_id"]) {
                this->_throwParseError("No structure member type named `stream_id`, but "
                                       "the trace type contains more than one data stream type.",
                                       pseudoPktHeaderType.loc());
            }
        } catch (MetadataParseError& exc) {
            this->_appendErrorMsgToParseError(exc, "In the packet header type:",
                                              _pseudoPktHeaderType->loc());
            throw;
        }
    }
}

} // namespace internal
} // namespace yactfr
