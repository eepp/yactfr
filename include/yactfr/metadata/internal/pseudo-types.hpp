/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_PSEUDO_TYPES_HPP
#define _YACTFR_METADATA_INTERNAL_PSEUDO_TYPES_HPP

#include <memory>
#include <vector>
#include <cstring>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/uuid/uuid.hpp>

#include "../../aliases.hpp"
#include "../data-loc.hpp"
#include "../enum-type.hpp"
#include "../trace-type.hpp"
#include "../aliases.hpp"

namespace yactfr {
namespace internal {

/*
 * All the "pseudo" stuff below exists because the yactfr metadata
 * objects are immutable and we need to modify them sometimes during the
 * parsing process, mostly because of data type aliases containing
 * relative data locations (they need to be converted to absolute data
 * locations because this is what the yactfr API expects).
 */

/*
 * A pseudo data location is the result of parsing a TSDL data location,
 * possibly not yet converted to an absolute data location (as yactfr
 * requires).
 *
 * If `isEnv` is true, then the parsed data location was
 * `env.SOMETHING`, where `SOMETHING` must be an existing environment
 * key (for static array types). The first element of `pathElems` is
 * `SOMETHING` in this case.
 *
 * If `isAbs` is false, then don't consider `scope`. Otherwise, `scope`
 * indicates the root scope, and `pathElems` contains everything else
 * (`stream.packet.context` and so forth are stripped).
 */
class PseudoDataLoc final
{
public:
    explicit PseudoDataLoc(bool isEnv, bool isAbs, Scope scope,
                           DataLocation::PathElements pathElems, TextLocation loc);

    PseudoDataLoc(const PseudoDataLoc&) = default;
    PseudoDataLoc(PseudoDataLoc&&) = default;
    PseudoDataLoc& operator=(const PseudoDataLoc&) = default;
    PseudoDataLoc& operator=(PseudoDataLoc&&) = default;

    bool isEnv() const noexcept
    {
        return _isEnv;
    }

    bool isAbs() const noexcept
    {
        return _isAbs;
    }

    Scope scope() const noexcept
    {
        return _scope;
    }

    const DataLocation::PathElements& pathElems() const noexcept
    {
        return _pathElems;
    }

    const TextLocation& loc() const noexcept
    {
        return _loc;
    }

private:
    bool _isEnv;
    bool _isAbs;
    Scope _scope;
    DataLocation::PathElements _pathElems;
    TextLocation _loc;
};

class PseudoDt;

/*
 * Set of pseudo data types.
 */
using PseudoDtSet = std::unordered_set<const PseudoDt *>;

/*
 * Base pseudo data type.
 */
class PseudoDt :
    boost::noncopyable
{
public:
    using UP = std::unique_ptr<PseudoDt>;

    enum class Kind
    {
        SCALAR_DT_WRAPPER,
        INT_TYPE_WRAPPER,
        STATIC_ARRAY,
        DYN_ARRAY,
        STRUCT,
        VAR,
    };

public:
    explicit PseudoDt(TextLocation loc);
    virtual ~PseudoDt();
    virtual Kind kind() const noexcept = 0;
    virtual bool isEmpty() const;
    PseudoDtSet findPseudoDtsByName(const std::string& name) const;

    /*
     * Fully clones this pseudo data type, meaning the returned object
     * is completely independent from this one.
     */
    virtual PseudoDt::UP clone() const = 0;

    const TextLocation& loc() const noexcept
    {
        return _loc;
    }

    void loc(TextLocation loc) noexcept
    {
        _loc = std::move(loc);
    }

protected:
    static void _findPseudoDtsByName(const PseudoDt& pseudoDt, const std::string& name,
                                     PseudoDtSet& pseudoDts);

    virtual void _findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const;

private:
    TextLocation _loc;
};

/*
 * This is a wrapper for any yactfr scalar type, except unsigned integer
 * and enumeration types.
 *
 * Scalar types are final and don't need to be modified during the
 * parsing process, so we can simply create them directly, wrap them
 * within instances of `PseudoScalarDtWrapper` so that they get the
 * common pseudo data type base, and move them later without unnecessary
 * allocations.
 */
class PseudoScalarDtWrapper :
    public PseudoDt
{
public:
    explicit PseudoScalarDtWrapper(DataType::UP dt, TextLocation loc = TextLocation {});

    PseudoDt::Kind kind() const noexcept override
    {
        return PseudoDt::Kind::SCALAR_DT_WRAPPER;
    }

    PseudoDt::UP clone() const override;

    const DataType& dt() const noexcept
    {
        return *_dt;
    }

private:
    DataType::UP _dt;
};

/*
 * This is a wrapper for yactfr integer and enumeration types.
 *
 * This is needed because:
 *
 * * During the decoding process, an unsigned integer type may be mapped
 *   to a clock type by name, and it's possible that we don't have this
 *   clock type yet (early data type aliases, for example).
 *
 * * An integer type may have an encoding: this is only needed to
 *   detect text array types; a yactfr integer type has no encoding.
 *
 * Keep an unmapped integer type here as well as the _name_ of the
 * mapped clock type, if any.
 */
class PseudoIntTypeWrapper final :
    public PseudoScalarDtWrapper
{
public:
    explicit PseudoIntTypeWrapper(DataType::UP dt, bool hasEncoding = false,
                                  boost::optional<std::string> mappedClkTypeName = boost::none,
                                  TextLocation loc = TextLocation {});

    PseudoDt::Kind kind() const noexcept override
    {
        return PseudoDt::Kind::INT_TYPE_WRAPPER;
    }

    PseudoDt::UP clone() const override;

    const IntegerType& intType() const noexcept
    {
        return static_cast<const IntegerType&>(this->dt());
    }

    bool hasEncoding() const noexcept
    {
        return _hasEncoding;
    }

    const boost::optional<std::string>& mappedClkTypeName() const noexcept
    {
        return _mappedClkTypeName;
    }

    void mappedClkTypeName(std::string name) noexcept
    {
        _mappedClkTypeName = std::move(name);
    }

private:
    bool _hasEncoding;
    boost::optional<std::string> _mappedClkTypeName;
};

/*
 * Pseudo array type (base class).
 */
struct PseudoArrayType :
    public PseudoDt
{
protected:
    explicit PseudoArrayType(PseudoDt::UP pseudoElemType, TextLocation loc = TextLocation {});

public:
    PseudoDt& pseudoElemType() noexcept
    {
        return *_pseudoElemType;
    }

    const PseudoDt& pseudoElemType() const noexcept
    {
        return *_pseudoElemType;
    }

private:
    void _findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const override;

private:
    PseudoDt::UP _pseudoElemType;
};

/*
 * Pseudo static array type.
 */
class PseudoStaticArrayType final :
    public PseudoArrayType
{
public:
    explicit PseudoStaticArrayType(Size len, PseudoDt::UP pseudoElemType,
                                   TextLocation loc = TextLocation {});

    PseudoDt::Kind kind() const noexcept override
    {
        return PseudoDt::Kind::STATIC_ARRAY;
    }

    PseudoDt::UP clone() const override;
    bool isEmpty() const override;

    Size len() const noexcept
    {
        return _len;
    }

private:
    Size _len;
};

/*
 * Pseudo dynamic array type.
 *
 * `pseudoLenLoc` may be a relative data location.
 */
class PseudoDynArrayType final :
    public PseudoArrayType
{
public:
    explicit PseudoDynArrayType(PseudoDataLoc pseudoLenLoc, PseudoDt::UP pseudoElemType,
                                TextLocation loc = TextLocation {});

    PseudoDt::Kind kind() const noexcept override
    {
        return PseudoDt::Kind::DYN_ARRAY;
    }

    PseudoDt::UP clone() const override;
    bool isEmpty() const override;

    const PseudoDataLoc& pseudoLenLoc() const noexcept
    {
        return _pseudoLenLoc;
    }

private:
    PseudoDataLoc _pseudoLenLoc;
};

/*
 * Pseudo named data type.
 */
class PseudoNamedDt final
{
public:
    using UP = std::unique_ptr<PseudoNamedDt>;

public:
    PseudoNamedDt() = default;
    explicit PseudoNamedDt(std::string name, PseudoDt::UP pseudoDt);

    const std::string& name() const noexcept
    {
        return _name;
    }

    const PseudoDt& pseudoDt() const noexcept
    {
        return *_pseudoDt;
    }

    PseudoDt& pseudoDt() noexcept
    {
        return *_pseudoDt;
    }

private:
    std::string _name;
    PseudoDt::UP _pseudoDt;
};

using PseudoNamedDts = std::vector<PseudoNamedDt::UP>;

/*
 * Pseudo structure type.
 */
class PseudoStructType final :
    public PseudoDt
{
public:
    explicit PseudoStructType(unsigned int minAlign, PseudoNamedDts&& pseudoMemberTypes,
                              TextLocation loc = TextLocation {});

    PseudoDt::Kind kind() const noexcept override
    {
        return PseudoDt::Kind::STRUCT;
    }

    PseudoDt::UP clone() const override;
    bool isEmpty() const override;

    /*
     * Returns the member class named `name`, or `nullptr` if not found.
     */
    const PseudoNamedDt *operator[](const std::string& name) const noexcept;

    unsigned int minAlign() const noexcept
    {
        return _minAlign;
    }

    const PseudoNamedDts& pseudoMemberTypes() const noexcept
    {
        return _pseudoMemberTypes;
    }

private:
    void _findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const override;

private:
    unsigned int _minAlign;
    PseudoNamedDts _pseudoMemberTypes;
};

/*
 * Pseudo variant type.
 *
 * `pseudoSelLoc` may be a relative data location.
 */
class PseudoVarType final :
    public PseudoDt
{
public:
    explicit PseudoVarType(boost::optional<PseudoDataLoc> pseudoSelLoc,
                           PseudoNamedDts&& pseudoOpts, TextLocation loc = TextLocation {});

    PseudoDt::Kind kind() const noexcept override
    {
        return PseudoDt::Kind::VAR;
    }

    PseudoDt::UP clone() const override;
    bool isEmpty() const override;

    const boost::optional<PseudoDataLoc>& pseudoSelLoc() const noexcept
    {
        return _pseudoSelLoc;
    }

    void pseudoSelLoc(PseudoDataLoc loc) noexcept
    {
        _pseudoSelLoc = std::move(loc);
    }

    const PseudoNamedDts& pseudoOpts() const noexcept
    {
        return _pseudoOpts;
    }

private:
    void _findPseudoDtsByName(const std::string& name, PseudoDtSet& pseudoDts) const override;

private:
    boost::optional<PseudoDataLoc> _pseudoSelLoc;
    PseudoNamedDts _pseudoOpts;
};

class PseudoValidatableType
{
protected:
    PseudoValidatableType() = default;

    /*
     * Validates that `pseudoDt`, named `name` (full name) in this
     * context, is a pseudo unsigned integer type (with a length
     * property of `*len` bits if available), throwing otherwise.
     */
    void _validateIsPseudoUIntType(const PseudoDt& pseudoDt, const std::string& name,
                                   const boost::optional<Size>& len = boost::none) const;

    /*
     * Validates that `pseudoDt`, the pseudo data type of a structure
     * member type named `name` in this context, is a pseudo unsigned
     * integer type (with a length property of `*len` bits if
     * available), throwing otherwise.
     */
    void _validateIsPseudoUIntTypeMember(const PseudoDt& pseudoDt,
                                         const std::string& memberTypeName,
                                         const boost::optional<Size>& len = boost::none) const;

    /*
     * Validates that the member type named `memberName` of the pseudo
     * structure type `parentPseudoDt` is a pseudo unsigned integer type
     * (with a length property of `*len` bits if available) if it
     * exists.
     */
    void _validateIsPseudoUIntTypeMemberIfExists(const PseudoDt& parentPseudoDt,
                                                 const std::string& memberTypeName,
                                                 const boost::optional<Size>& len = boost::none) const;

    /*
     * Throws a `MetadataParseError` instance, following `msg` and
     * `textLoc` to its constructor.
     *
     * This method exists so that `MetadataParseError` only declares
     * this class as a friend.
     */
    void _throwParseError(std::string msg, TextLocation textLoc = TextLocation {}) const;

    /*
     * Calls `exc._appendErrorMsg()`, following `msg` and `textLoc` to
     * it.
     *
     * This method exists so that `MetadataParseError` only declares
     * this class as a friend.
     */
    void _appendErrorMsgToParseError(MetadataParseError& exc, std::string msg,
                                     TextLocation textLoc = TextLocation {}) const;
};

class PseudoDst;

/*
 * Pseudo event record type: mutable event record type.
 */
class PseudoErt final :
    public PseudoValidatableType
{
public:
    explicit PseudoErt(TypeId id, boost::optional<std::string> name,
                       boost::optional<LogLevel> logLevel, boost::optional<std::string> emfUri,
                       PseudoDt::UP pseudoSpecCtxType, PseudoDt::UP pseudoPayloadType);

    PseudoErt(const PseudoErt&) = delete;
    PseudoErt(PseudoErt&&) = default;
    PseudoErt& operator=(const PseudoErt&) = delete;
    PseudoErt& operator=(PseudoErt&&) = default;

    /*
     * Validates this pseudo event record type, as belonging to
     * `pseudoDst`, throwing `MetadataParseError` on any error.
     */
    void validate(const PseudoDst& pseudoDst) const;

    TypeId id() const noexcept
    {
        return _id;
    }

    const boost::optional<std::string>& name() const noexcept
    {
        return _name;
    }

    const boost::optional<LogLevel>& logLevel() const noexcept
    {
        return _logLevel;
    }

    const boost::optional<std::string>& emfUri() const noexcept
    {
        return _emfUri;
    }

    const PseudoDt *pseudoSpecCtxType() const noexcept
    {
        return _pseudoSpecCtxType.get();
    }

    PseudoDt *pseudoSpecCtxType() noexcept
    {
        return _pseudoSpecCtxType.get();
    }

    const PseudoDt *pseudoPayloadType() const noexcept
    {
        return _pseudoPayloadType.get();
    }

    PseudoDt *pseudoPayloadType() noexcept
    {
        return _pseudoPayloadType.get();
    }

private:
    TypeId _id = 0;
    boost::optional<std::string> _name;
    boost::optional<LogLevel> _logLevel;
    boost::optional<std::string> _emfUri;
    PseudoDt::UP _pseudoSpecCtxType;
    PseudoDt::UP _pseudoPayloadType;
};

/*
 * Set of pseudo event record types.
 */
using PseudoErtSet = std::unordered_set<const PseudoErt *>;

/*
 * Pseudo data stream type: mutable data stream type.
 */
class PseudoDst final :
    public PseudoValidatableType
{
public:
    PseudoDst() = default;
    explicit PseudoDst(TypeId id, PseudoDt::UP pseudoPktCtxType, PseudoDt::UP pseudoErHeaderType,
                       PseudoDt::UP pseudoErCommonCtxType);

    PseudoDst(const PseudoDst&) = delete;
    PseudoDst(PseudoDst&&) = default;
    PseudoDst& operator=(const PseudoDst&) = delete;
    PseudoDst& operator=(PseudoDst&&) = default;

    /*
     * Validates this pseudo data stream type, as containing the pseudo
     * event record types `pseudoErts`, throwing `MetadataParseError` on
     * any error.
     */
    void validate(const PseudoErtSet& pseudoErts) const;

    TypeId id() const noexcept
    {
        return _id;
    }

    const PseudoDt *pseudoPktCtxType() const noexcept
    {
        return _pseudoPktCtxType.get();
    }

    PseudoDt *pseudoPktCtxType() noexcept
    {
        return _pseudoPktCtxType.get();
    }

    const PseudoDt *pseudoErHeaderType() const noexcept
    {
        return _pseudoErHeaderType.get();
    }

    PseudoDt *pseudoErHeaderType() noexcept
    {
        return _pseudoErHeaderType.get();
    }

    const PseudoDt *pseudoErCommonCtxType() const noexcept
    {
        return _pseudoErCommonCtxType.get();
    }

    PseudoDt *pseudoErCommonCtxType() noexcept
    {
        return _pseudoErCommonCtxType.get();
    }

private:
    TypeId _id = 0;
    PseudoDt::UP _pseudoPktCtxType;
    PseudoDt::UP _pseudoErHeaderType;
    PseudoDt::UP _pseudoErCommonCtxType;
};

/*
 * Orphan pseudo event record type entry.
 */
class PseudoOrphanErt final
{
public:
    explicit PseudoOrphanErt(PseudoErt pseudoErt, TextLocation loc);
    PseudoOrphanErt(const PseudoOrphanErt&) = delete;
    PseudoOrphanErt(PseudoOrphanErt&&) = default;
    PseudoOrphanErt& operator=(const PseudoOrphanErt&) = delete;
    PseudoOrphanErt& operator=(PseudoOrphanErt&&) = default;

    const PseudoErt& pseudoErt() const noexcept
    {
        return _pseudoErt;
    }

    const TextLocation& loc() const noexcept
    {
        return _loc;
    }

private:
    PseudoErt _pseudoErt;
    TextLocation _loc;
};

/*
 * Pseudo trace type: mutable trace type.
 */
class PseudoTraceType final :
    public PseudoValidatableType
{
public:
    using PseudoDsts = std::unordered_map<TypeId, std::unique_ptr<PseudoDst>>;
    using PseudoOrphanErts = std::unordered_map<TypeId, std::unordered_map<TypeId, PseudoOrphanErt>>;

public:
    explicit PseudoTraceType(unsigned int majorVersion, unsigned int minorVersion,
                             ByteOrder nativeBo, boost::optional<boost::uuids::uuid> uuid,
                             PseudoDt::UP pseudoPktHeaderType);

    /*
     * Validates this pseudo trace type, throwing `MetadataParseError`
     * on any error.
     */
    void validate() const;

    unsigned int majorVersion() const noexcept
    {
        return _majorVersion;
    }

    unsigned int minorVersion() const noexcept
    {
        return _majorVersion;
    }

    ByteOrder nativeBo() const noexcept
    {
        return _nativeBo;
    }

    const boost::optional<boost::uuids::uuid>& uuid() const noexcept
    {
        return _uuid;
    }

    const PseudoDt *pseudoPktHeaderType() const noexcept
    {
        return _pseudoPktHeaderType.get();
    }

    PseudoDt *pseudoPktHeaderType() noexcept
    {
        return _pseudoPktHeaderType.get();
    }

    const ClockTypeSet& clkTypes() const noexcept
    {
        return _clkTypes;
    }

    ClockTypeSet& clkTypes() noexcept
    {
        return _clkTypes;
    }

    const PseudoDsts& pseudoDsts() const noexcept
    {
        return _pseudoDsts;
    }

    PseudoDsts& pseudoDsts() noexcept
    {
        return _pseudoDsts;
    }

    const PseudoOrphanErts& pseudoOrphanErts() const noexcept
    {
        return _pseudoOrphanErts;
    }

    PseudoOrphanErts& pseudoOrphanErts() noexcept
    {
        return _pseudoOrphanErts;
    }

private:
    unsigned int _majorVersion;
    unsigned int _minorVersion;
    ByteOrder _nativeBo;
    boost::optional<boost::uuids::uuid> _uuid;
    PseudoDt::UP _pseudoPktHeaderType;
    ClockTypeSet _clkTypes;
    PseudoDsts _pseudoDsts;
    PseudoOrphanErts _pseudoOrphanErts;
};

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_PSEUDO_TYPES_HPP
