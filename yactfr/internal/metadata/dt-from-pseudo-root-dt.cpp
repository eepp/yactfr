/*
 * Copyright (C) 2017-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <boost/optional.hpp>
#include <boost/utility.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <yactfr/aliases.hpp>
#include <yactfr/internal/metadata/utils.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/metadata/data-loc.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/dl-blob-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/ert.hpp>
#include <yactfr/metadata/fl-enum-type.hpp>
#include <yactfr/metadata/int-range.hpp>
#include <yactfr/metadata/item.hpp>
#include <yactfr/metadata/opt-type.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/sl-blob-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/text-parse-error.hpp>

#include "dt-from-pseudo-root-dt.hpp"
#include "set-pseudo-dt-data-loc.hpp"
#include "set-pseudo-dt-pos-in-scope.hpp"
#include "pseudo-types.hpp"

namespace yactfr {
namespace internal {

/*
 * Converter of root pseudo data type to yactfr data type.
 */
class DtFromPseudoRootDtConverter :
    boost::noncopyable
{
    friend StructureType::UP dtFromPseudoRootDt(PseudoDt&, Scope, const PseudoTraceType&,
                                                const PseudoDst *, const PseudoErt *);

private:
    explicit DtFromPseudoRootDtConverter(PseudoDt& pseudoDt, Scope scope,
                                         const PseudoTraceType& pseudoTraceType,
                                         const PseudoDst *curPseudoDst,
                                         const PseudoErt *curPseudoErt);

    /*
     * Releases and returns the resulting yactfr data type.
     */
    StructureType::UP _releaseDt()
    {
        return std::move(_dt);
    }

    using _PseudoDtSels = std::pair<DataLocation, ConstPseudoDtSet>;

private:
    /*
     * Finds and returns all the pseudo data types from `loc` for the
     * source pseudo data type `pseudoSrcDt`.
     *
     * Doesn't add to the returned set any pseudo data type candidate
     * occurring after `pseudoSrcDt`.
     */
    ConstPseudoDtSet _findPseudoDts(const DataLocation& loc, const PseudoDt& pseudoSrcDt) const;

    /*
     * Recursive version of the other _findPseudoDts(), filling
     * `pseudoDts` as it goes.
     *
     * `locIt` is the current path element, within `loc`, to consider;
     * it can be `loc.end()` in which case some leaf/resolution is
     * expected.
     *
     * Returns `true` if `pseudoSrcDt` isn't reached yet (safe to
     * continue to find pseudo data types).
     */
    bool _findPseudoDts(const PseudoDt& pseudoDt, const DataLocation& loc,
                        DataLocation::PathElements::const_iterator locIt,
                        ConstPseudoDtSet& pseudoDts) const;

    /*
     * Converts the pseudo data type `pseudoDt` to a yactfr data type,
     * throwing if any error occurs.
     */
    DataType::UP _dtFromPseudoDt(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo structure type `pseudoDt` to a yactfr
     * structure type.
     */
    StructureType::UP _structTypeFromPseudoDt(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo scalar data type wrapper `pseudoDt` to a
     * yactfr data type.
     */
    DataType::UP _dtFromPseudoScalarDtWrapper(const PseudoDt& pseudoDt) const;

    /*
     * Converts the pseudo unsigned integer type wrapper `pseudoDt` to a
     * yactfr data type.
     */
    DataType::UP _dtFromPseudoFlUIntType(const PseudoDt& pseudoDt) const;

    /*
     * Converts the pseudo unsigned enumeration type wrapper `pseudoDt`
     * to a yactfr data type.
     */
    DataType::UP _dtFromPseudoFlUEnumType(const PseudoDt& pseudoDt) const;

    /*
     * Tries to convert the pseudo array type `pseudoArrayType` to a
     * yactfr non null-terminated string type having the type
     * `StrTypeT`.
     *
     * Returns a null pointer if `pseudoArrayType` doesn't match a non
     * null-terminated string type profile.
     */
    template <typename StrTypeT, typename PseudoArrayTypeT, typename LenT>
    DataType::UP _tryNonNtStrTypeFromPseudoArrayType(const PseudoArrayTypeT& pseudoArrayType,
                                                     const PseudoDt& pseudoElemType, LenT&& len);

    /*
     * Returns the validated length location of the pseudo
     * dynamic-length array or BLOB type `pseudoDt`.
     */
    template <typename PseudoDtT>
    const DataLocation& _getLenLoc(const PseudoDtT& pseudoDt) const;

    template <typename PseudoDtT, typename FuncT>
    DataType::UP _whileVisitingPseudoDt(const PseudoDtT& pseudoDt, FuncT&& func);

    /*
     * Converts the pseudo static-length array type `pseudoDt` to a
     * yactfr static-length array type.
     */
    DataType::UP _dtFromPseudoSlArrayType(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo dynamic-length array type `pseudoDt` to a
     * yactfr dynamic-length array type.
     */
    DataType::UP _dtFromPseudoDlArrayType(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo dynamic-length BLOB type `pseudoDt` to a
     * yactfr dynamic BLOB type.
     */
    DataType::UP _dtFromPseudoDlBlobType(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo structure type `pseudoDt` to a yactfr
     * structure type.
     */
    DataType::UP _dtFromPseudoStructType(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo variant type `pseudoDt` to a yactfr variant
     * type.
     */
    DataType::UP _dtFromPseudoVarType(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo variant (with integer ranges) type `pseudoDt`
     * to a yactfr variant type.
     */
    DataType::UP _dtFromPseudoVarWithIntRangesType(const PseudoDt& pseudoDt);

    /*
     * Returns the yactfr data location and all the pseudo selector
     * types of the pseudo data type `pseudoDt`.
     */
    template <typename PseudoDtT>
    _PseudoDtSels _pseudoDtSels(const PseudoDtT& pseudoDt) const;

    /*
     * Returns the yactfr data location and all the pseudo integer
     * selector types, validating them, of the pseudo data type
     * `pseudoDt` of which the name is `dtName` (either `variant` or
     * `optional`).
     */
    template <typename PseudoDtT>
    _PseudoDtSels _pseudoDtIntSels(const PseudoDtT& pseudoDt, const std::string& dtName) const;

    /*
     * Converts the pseudo variant type `pseudoVarType` to a yactfr
     * variant type of type `VarTypeT`, the type of the selector type
     * mappings `selTypeMappings` being `MappingsT`.
     */
    template <typename VarTypeT, typename MappingsT>
    DataType::UP _dtFromPseudoVarType(const PseudoVarType& pseudoVarType,
                                      const MappingsT& selTypeMappings, const DataLocation& selLoc);

    /*
     * Converts the pseudo variant (with integer ranges) type
     * `pseudoVarType` to a yactfr variant type of type `VarTypeT`, the
     * value type of the integer ranges of the options being
     * `IntRangeValueT`.
     */
    template <typename VarTypeT, typename IntRangeValueT>
    DataType::UP _dtFromPseudoVarWithIntRangesType(const PseudoVarWithIntRangesType& pseudoVarType,
                                                   DataLocation&& selLoc);

    /*
     * Converts the pseudo optional (with boolean selector) type
     * `pseudoDt` to a yactfr optional type.
     */
    DataType::UP _dtFromPseudoOptWithBoolSelType(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo optional (with integer selector) type
     * `pseudoDt` to a yactfr optional type.
     */
    DataType::UP _dtFromPseudoOptWithIntSelType(const PseudoDt& pseudoDt);

    [[ noreturn ]] void _throwInvalDataLoc(const std::string& initMsg, const TextLocation& initLoc,
                                           const DataLocation& dataLoc, const TextLocation& loc) const;

    template <typename ItT>
    static std::string _dataLocStr(Scope scope, ItT begin, ItT end);


    template <typename MappingsT>
    static bool _enumTypeMappingsOverlap(const MappingsT& mappings);

    static MapItem::UP _tryCloneAttrs(const MapItem *attrs);

private:
    // final yactfr data type
    StructureType::UP _dt;

    // current scope
    Scope _scope;

    // pseudo trace type
    const PseudoTraceType *_pseudoTraceType;

    // current pseudo data stream type, if any
    const PseudoDst *_pseudoDst;

    // current pseudo event record type, if any
    const PseudoErt *_pseudoErt;

    /*
     * Option/element indexes of currently visited pseudo
     * variant/optional, dynamic-length array/string/BLOB types (always
     * 0 for pseudo dynamic-length array/string/BLOB and pseudo optional
     * type).
     */
    std::unordered_map<const PseudoDt *, Index> _current;
};

template <typename ItT>
std::string DtFromPseudoRootDtConverter::_dataLocStr(const Scope scope, const ItT begin,
                                                     const ItT end)
{
    std::string str;

    switch (scope) {
    case Scope::PACKET_HEADER:
        str = "packet header";
        break;

    case Scope::PACKET_CONTEXT:
        str = "packet context";
        break;

    case Scope::EVENT_RECORD_HEADER:
        str = "event record header";
        break;

    case Scope::EVENT_RECORD_COMMON_CONTEXT:
        str = "event record common context";
        break;

    case Scope::EVENT_RECORD_SPECIFIC_CONTEXT:
        str = "event record specific context";
        break;

    case Scope::EVENT_RECORD_PAYLOAD:
        str = "event record payload";
        break;

    default:
        std::abort();
    }

    str += ": `";
    str += *begin;
    str += '`';

    for (auto it = begin + 1; it != end; ++it) {
        str += "/`";
        str += *it;
        str += '`';
    }

    return str;
}

template <typename StrTypeT, typename PseudoArrayTypeT, typename LenT>
DataType::UP DtFromPseudoRootDtConverter::_tryNonNtStrTypeFromPseudoArrayType(const PseudoArrayTypeT& pseudoArrayType,
                                                                              const PseudoDt& pseudoElemType,
                                                                              LenT&& len)
{
    if (pseudoElemType.isInt()) {
        boost::optional<StringEncoding> encoding;
        unsigned int align;
        unsigned int elemLen;

        if (pseudoElemType.isUInt()) {
            auto& pseudoIntElemType = static_cast<const PseudoFlUIntType&>(pseudoElemType);

            encoding = pseudoIntElemType.encoding();
            align = pseudoIntElemType.align();
            elemLen = pseudoIntElemType.len();
        } else {
            auto& pseudoScalarDtWrapper = static_cast<const PseudoScalarDtWrapper&>(pseudoElemType);
            auto& intType = pseudoScalarDtWrapper.dt().asFixedLengthSignedIntegerType();

            encoding = pseudoScalarDtWrapper.encoding();
            align = intType.alignment();
            elemLen = intType.length();
        }

        if (encoding && align == 8 && elemLen == 8) {
            return StrTypeT::create(8, std::forward<LenT>(len), *encoding,
                                    this->_tryCloneAttrs(pseudoArrayType.attrs()));
        }
    }

    return nullptr;
}

template <typename MappingsT>
bool DtFromPseudoRootDtConverter::_enumTypeMappingsOverlap(const MappingsT& mappings)
{
    for (auto it1 = mappings.begin(); it1 != mappings.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != mappings.end(); ++it2) {
            if (it1->second.intersects(it2->second)) {
                return true;
            }
        }
    }

    return false;
}

template <typename VarTypeT, typename MappingsT>
DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoVarType(const PseudoVarType& pseudoVarType,
                                                               const MappingsT& selTypeMappings,
                                                               const DataLocation& selLoc)
{
    // validate that the selector type has no overlapping mappings
    if (this->_enumTypeMappingsOverlap(selTypeMappings)) {
        this->_throwInvalDataLoc("Selector type of variant type contains overlapping mappings.",
                                 pseudoVarType.loc(), selLoc, pseudoVarType.loc());
    }

    typename VarTypeT::Options opts;

    for (auto i = 0U; i < pseudoVarType.pseudoOpts().size(); ++i) {
        // currently being visited
        _current[&pseudoVarType] = i;

        const auto& pseudoOpt = pseudoVarType.pseudoOpts()[i];
        auto optDt = this->_dtFromPseudoDt(pseudoOpt->pseudoDt());

        assert(pseudoOpt->name());

        const auto rangesIt = selTypeMappings.find(*pseudoOpt->name());

        // validate that the range set exists
        if (rangesIt == selTypeMappings.end()) {
            std::ostringstream ss;

            ss << "Selector type of variant type has no mapping named `" <<
                  *pseudoOpt->name() << "`.";
            this->_throwInvalDataLoc(ss.str(), pseudoVarType.loc(), selLoc, pseudoVarType.loc());
        }

        opts.push_back(VarTypeT::Option::create(*pseudoOpt->name(), std::move(optDt),
                                                rangesIt->second,
                                                this->_tryCloneAttrs(pseudoOpt->attrs())));
    }

    // not visited anymore
    _current.erase(&pseudoVarType);

    return VarTypeT::create(1, std::move(opts), selLoc,
                            this->_tryCloneAttrs(pseudoVarType.attrs()));
}

template <typename VarTypeT, typename IntRangeValueT>
DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoVarWithIntRangesType(const PseudoVarWithIntRangesType& pseudoVarType,
                                                                            DataLocation&& selLoc)
{
    typename VarTypeT::Options opts;

    for (auto i = 0U; i < pseudoVarType.pseudoOpts().size(); ++i) {
        // currently being visited
        _current[&pseudoVarType] = i;

        const auto& pseudoOpt = pseudoVarType.pseudoOpts()[i];
        auto optDt = this->_dtFromPseudoDt(pseudoOpt->pseudoDt());
        std::set<IntegerRange<IntRangeValueT>> ranges;

        for (auto& range : pseudoVarType.rangeSets()[i]) {
            ranges.insert(IntegerRange<IntRangeValueT> {
                static_cast<IntRangeValueT>(range.lower()),
                static_cast<IntRangeValueT>(range.upper())
            });
        }

        opts.push_back(VarTypeT::Option::create(pseudoOpt->name(), std::move(optDt),
                                                IntegerRangeSet<IntRangeValueT> {std::move(ranges)},
                                                this->_tryCloneAttrs(pseudoOpt->attrs())));
    }

    // not visited anymore
    _current.erase(&pseudoVarType);

    return VarTypeT::create(1, std::move(opts), std::move(selLoc),
                            this->_tryCloneAttrs(pseudoVarType.attrs()));
}

template <typename PseudoDtT, typename FuncT>
DataType::UP DtFromPseudoRootDtConverter::_whileVisitingPseudoDt(const PseudoDtT& pseudoCompoundDt,
                                                                 FuncT&& func)
{
    _current[&pseudoCompoundDt] = 0;

    auto pseudoDt = std::forward<FuncT>(func)(pseudoCompoundDt);

    _current.erase(&pseudoCompoundDt);
    return pseudoDt;
}

DtFromPseudoRootDtConverter::DtFromPseudoRootDtConverter(PseudoDt& pseudoDt,
                                                         const Scope scope,
                                                         const PseudoTraceType& pseudoTraceType,
                                                         const PseudoDst * const pseudoDst,
                                                         const PseudoErt * const pseudoErt) :
    _scope {scope},
    _pseudoTraceType {&pseudoTraceType},
    _pseudoDst {pseudoDst},
    _pseudoErt {pseudoErt}
{
    /*
     * Here's what happens here:
     *
     * 1. setPseudoDtDataLoc() sets the yactfr data location of each
     *    relevant pseudo data type from its pseudo data location.
     *
     *    After this step, we have all the yactfr (absolute) data
     *    locations we need, but there are no yactfr data types yet.
     *
     * 2. setPseudoDtPosInScope() sets the position, within their scope,
     *    of all the pseudo data types.
     *
     *    This makes the validation of pseudo length/selector types
     *    simpler.
     *
     * 3. _structTypeFromPseudoDt() recursively converts pseudo data
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
    setPseudoDtDataLoc(pseudoDt, scope);
    setPseudoDtPosInScope(pseudoDt);
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

    return FixedLengthUnsignedIntegerType::create(pseudoUIntType.align(), pseudoUIntType.len(),
                                                  pseudoUIntType.bo(),
                                                  pseudoUIntType.prefDispBase(),
                                                  tryCloneAttrs(pseudoUIntType.attrs()),
                                                  pseudoUIntType.roles());
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoFlUEnumType(const PseudoDt& pseudoDt) const
{
    auto& pseudoUEnumType = static_cast<const PseudoFlUEnumType&>(pseudoDt);

    return FixedLengthUnsignedEnumerationType::create(pseudoUEnumType.align(),
                                                      pseudoUEnumType.len(), pseudoUEnumType.bo(),
                                                      pseudoUEnumType.mappings(),
                                                      pseudoUEnumType.prefDispBase(),
                                                      tryCloneAttrs(pseudoUEnumType.attrs()),
                                                      pseudoUEnumType.roles());
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoSlArrayType(const PseudoDt& pseudoDt)
{
    auto& pseudoArrayType = static_cast<const PseudoSlArrayType&>(pseudoDt);
    auto arrayType = this->_tryNonNtStrTypeFromPseudoArrayType<StaticLengthStringType>(pseudoArrayType,
                                                                                       pseudoArrayType.pseudoElemType(),
                                                                                       pseudoArrayType.len());

    if (arrayType) {
        return arrayType;
    }

    auto elemDt = this->_whileVisitingPseudoDt(pseudoArrayType, [this](auto& pseudoArrayType) {
        return this->_dtFromPseudoDt(pseudoArrayType.pseudoElemType());
    });

    return StaticLengthArrayType::create(pseudoArrayType.minAlign(), std::move(elemDt),
                                         pseudoArrayType.len(),
                                         tryCloneAttrs(pseudoArrayType.attrs()),
                                         pseudoArrayType.hasMetadataStreamUuidRole());
}

template <typename PseudoDtT>
const DataLocation& DtFromPseudoRootDtConverter::_getLenLoc(const PseudoDtT& pseudoDt) const
{
    assert(pseudoDt.lenLoc());

    const auto pseudoLenTypes = this->_findPseudoDts(*pseudoDt.lenLoc(), pseudoDt);

    assert(!pseudoLenTypes.empty());

    for (const auto pseudoLenType : pseudoLenTypes) {
        if (!pseudoLenType->isUInt()) {
            this->_throwInvalDataLoc("Length type isn't an unsigned integer type.",
                                     pseudoLenType->loc(), *pseudoDt.lenLoc(), pseudoDt.loc());
        }
    }

    return *pseudoDt.lenLoc();
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoDlArrayType(const PseudoDt& pseudoDt)
{
    auto& pseudoArrayType = static_cast<const PseudoDlArrayType&>(pseudoDt);
    const auto& lenLoc = this->_getLenLoc(pseudoArrayType);
    auto strType = this->_tryNonNtStrTypeFromPseudoArrayType<DynamicLengthStringType>(pseudoArrayType,
                                                                                      pseudoArrayType.pseudoElemType(),
                                                                                      lenLoc);

    if (strType) {
        return strType;
    }

    auto elemDt = this->_whileVisitingPseudoDt(pseudoArrayType, [this](auto& pseudoArrayType) {
        return this->_dtFromPseudoDt(pseudoArrayType.pseudoElemType());
    });

    return DynamicLengthArrayType::create(pseudoArrayType.minAlign(), std::move(elemDt), lenLoc,
                                          tryCloneAttrs(pseudoArrayType.attrs()));
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoDlBlobType(const PseudoDt& pseudoDt)
{
    auto& pseudoBlobType = static_cast<const PseudoDlBlobType&>(pseudoDt);
    const auto& lenLoc = this->_getLenLoc(pseudoBlobType);

    if (pseudoBlobType.mediaType()) {
        return DynamicLengthBlobType::create(8, lenLoc, *pseudoBlobType.mediaType(),
                                             tryCloneAttrs(pseudoBlobType.attrs()));
    } else {
        return DynamicLengthBlobType::create(8, lenLoc,
                                             tryCloneAttrs(pseudoBlobType.attrs()));
    }
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoStructType(const PseudoDt& pseudoDt)
{
    StructureType::MemberTypes memberTypes;
    auto& pseudoStructType = static_cast<const PseudoStructType&>(pseudoDt);

    for (const auto& pseudoMemberType : pseudoStructType.pseudoMemberTypes()) {
        auto memberDt = this->_dtFromPseudoDt(pseudoMemberType->pseudoDt());

        memberTypes.push_back(StructureMemberType::create(*pseudoMemberType->name(),
                                                          std::move(memberDt),
                                                          tryCloneAttrs(pseudoMemberType->attrs())));
    }

    return StructureType::create(pseudoStructType.minAlign(), std::move(memberTypes),
                                 tryCloneAttrs(pseudoStructType.attrs()));
}

bool DtFromPseudoRootDtConverter::_findPseudoDts(const PseudoDt& pseudoDt, const DataLocation& loc,
                                                 const DataLocation::PathElements::const_iterator locIt,
                                                 ConstPseudoDtSet& pseudoDts) const
{
    switch (pseudoDt.kind()) {
    case PseudoDt::Kind::SCALAR_DT_WRAPPER:
    case PseudoDt::Kind::FL_UINT:
    case PseudoDt::Kind::FL_UENUM:
        if (locIt != loc.pathElements().end()) {
            std::ostringstream ss;

            ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "]: "
                  "nothing past scalar data type.";
            throwTextParseError(ss.str(), pseudoDt.loc());
        }

        pseudoDts.insert(&pseudoDt);
        return true;

    case PseudoDt::Kind::STRUCT:
    {
        if (locIt == loc.pathElements().end()) {
            std::ostringstream ss;

            ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), loc.end()) <<
                  "]: length/selector must not be a structure.";
            throwTextParseError(ss.str(), pseudoDt.loc());
        }

        auto& pseudoStructType = static_cast<const PseudoStructType&>(pseudoDt);

        for (auto& pseudoMemberType : pseudoStructType.pseudoMemberTypes()) {
            assert(pseudoMemberType->name());

            if (*pseudoMemberType->name() != *locIt) {
                continue;
            }

            return this->_findPseudoDts(pseudoMemberType->pseudoDt(), loc, locIt + 1, pseudoDts);
        }

        std::ostringstream ss;

        ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), locIt + 1) <<
              "]: cannot find `" << *locIt << "` (last element).";
        throwTextParseError(ss.str(), pseudoDt.loc());
    }

    case PseudoDt::Kind::SL_ARRAY:
    case PseudoDt::Kind::DL_ARRAY:
    {
        if (_current.find(&pseudoDt) == _current.end()) {
            std::ostringstream ss;

            ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "]: "
                  "unreachable array element.";
            throwTextParseError(ss.str(), pseudoDt.loc());
        }

        auto& pseudoArrayType = static_cast<const PseudoArrayType&>(pseudoDt);

        return this->_findPseudoDts(pseudoArrayType.pseudoElemType(), loc, locIt, pseudoDts);
    }

    case PseudoDt::Kind::VAR:
    case PseudoDt::Kind::VAR_WITH_INT_RANGES:
    {
        auto& pseudoVarType = static_cast<const PseudoVarType&>(pseudoDt);
        const auto it = _current.find(&pseudoDt);

        if (it == _current.end()) {
            // fan out (consider all options)
            for (auto& pseudoOpt : pseudoVarType.pseudoOpts()) {
                this->_findPseudoDts(pseudoOpt->pseudoDt(), loc, locIt, pseudoDts);
            }
        } else {
            // follow current option only
            return this->_findPseudoDts(pseudoVarType.pseudoOpts()[it->second]->pseudoDt(), loc,
                                        locIt, pseudoDts);
        }

        return true;
    }

    case PseudoDt::Kind::OPT_WITH_BOOL_SEL:
    case PseudoDt::Kind::OPT_WITH_INT_SEL:
    {
        if (_current.find(&pseudoDt) == _current.end()) {
            std::ostringstream ss;

            ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), locIt) << "]: "
                  "unreachable optional data.";
            throwTextParseError(ss.str(), pseudoDt.loc());
        }

        auto& pseudoOptType = static_cast<const PseudoOptType&>(pseudoDt);

        return this->_findPseudoDts(pseudoOptType.pseudoDt(), loc, locIt, pseudoDts);
    }

    default:
        std::abort();
    }
}

ConstPseudoDtSet DtFromPseudoRootDtConverter::_findPseudoDts(const DataLocation& loc,
                                                             const PseudoDt& pseudoSrcDt) const
{
    if (static_cast<int>(loc.scope()) > static_cast<int>(_scope)) {
        std::ostringstream ss;

        ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), loc.end()) << "]: "
              "data would be unreachable.";
        throwTextParseError(ss.str(), pseudoSrcDt.loc());
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

        ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), loc.end()) << "]: "
              "cannot find scope data type.";
        throwTextParseError(ss.str(), pseudoSrcDt.loc());
    }

    ConstPseudoDtSet pseudoDts;

    this->_findPseudoDts(*pseudoDt, loc, loc.begin(), pseudoDts);

    if (loc.scope() == _scope) {
        /*
         * Source and targets within the same scope: validate that all
         * the targets will be decoded before the source.
         */
        for (auto& pseudoDt : pseudoDts) {
            if (*pseudoDt->posInScope() > *pseudoSrcDt.posInScope()) {
                std::ostringstream ss;

                ss << "Data location [" << this->_dataLocStr(loc.scope(), loc.begin(), loc.end()) <<
                      "]: a length/selector wouldn't be decoded yet to decode the "
                      "datum which needs it.";
                throwTextParseError(ss.str(), pseudoSrcDt.loc());
            }
        }
    }

    return pseudoDts;
}

template <typename PseudoDtT>
DtFromPseudoRootDtConverter::_PseudoDtSels DtFromPseudoRootDtConverter::_pseudoDtSels(const PseudoDtT& pseudoDt) const
{
    assert(pseudoDt.selLoc());

    auto pseudoSelDts = this->_findPseudoDts(*pseudoDt.selLoc(), pseudoDt);

    assert(!pseudoSelDts.empty());
    return {*pseudoDt.selLoc(), std::move(pseudoSelDts)};
}

template <typename PseudoDtT>
DtFromPseudoRootDtConverter::_PseudoDtSels DtFromPseudoRootDtConverter::_pseudoDtIntSels(const PseudoDtT& pseudoDt,
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
    auto selLocPseudoDtsPair = this->_pseudoDtIntSels(pseudoVarType, "variant");
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
    const auto selLocPseudoDtsPair = this->_pseudoDtSels(pseudoVarType);
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
    auto selLocPseudoDtsPair = this->_pseudoDtSels(pseudoOptType);

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

    return OptionalWithBooleanSelectorType::create(1, std::move(containedDt),
                                                   std::move(selLocPseudoDtsPair.first),
                                                   tryCloneAttrs(pseudoOptType.attrs()));
}

static IntegerRangeSet<unsigned long long> uIntRangeSetFromUIntRangeSetWithoutPrecondsCheck(const IntegerRangeSet<unsigned long long, false>& ranges)
{
    using Ranges = IntegerRangeSet<unsigned long long>;

    std::set<Ranges::Range> newRanges;

    for (auto& range : ranges) {
        newRanges.insert(Ranges::Range {range.lower(), range.upper()});
    }

    return Ranges {std::move(newRanges)};
}

DataType::UP DtFromPseudoRootDtConverter::_dtFromPseudoOptWithIntSelType(const PseudoDt& pseudoDt)
{
    assert(_pseudoTraceType->majorVersion() == 2);

    auto& pseudoOptType = static_cast<const PseudoOptWithIntSelType&>(pseudoDt);
    auto selLocPseudoDtsPair = this->_pseudoDtIntSels(pseudoOptType, "optional");
    auto& selLoc = selLocPseudoDtsPair.first;
    const auto& pseudoSelDts = selLocPseudoDtsPair.second;

    auto containedDt = this->_whileVisitingPseudoDt(pseudoOptType, [this](auto& pseudoOptType) {
        return this->_dtFromPseudoDt(pseudoOptType.pseudoDt());
    });

    assert(!pseudoSelDts.empty());

    if ((*pseudoSelDts.begin())->isUInt()) {
        return OptionalWithUnsignedIntegerSelectorType::create(1, std::move(containedDt),
                                                               std::move(selLoc),
                                                               uIntRangeSetFromUIntRangeSetWithoutPrecondsCheck(pseudoOptType.selRanges()),
                                                               tryCloneAttrs(pseudoOptType.attrs()));
    } else {
        using SInt = long long;

        std::set<IntegerRange<SInt>> ranges;

        for (auto& range : pseudoOptType.selRanges()) {
            ranges.insert(IntegerRange<SInt> {
                static_cast<SInt>(range.lower()),
                static_cast<SInt>(range.upper())
            });
        }

        return OptionalWithSignedIntegerSelectorType::create(1, std::move(containedDt),
                                                             std::move(selLoc),
                                                             IntegerRangeSet<SInt> {std::move(ranges)},
                                                             tryCloneAttrs(pseudoOptType.attrs()));
    }

    return nullptr;
}

void DtFromPseudoRootDtConverter::_throwInvalDataLoc(const std::string& initMsg,
                                                     const TextLocation& initLoc,
                                                     const DataLocation& dataLoc,
                                                     const TextLocation& loc) const
{
    try {
        throwTextParseError(initMsg, initLoc);
    } catch (TextParseError& exc) {
        std::ostringstream ss;

        ss << "Invalid data location (" <<
              this->_dataLocStr(dataLoc.scope(), dataLoc.begin(), dataLoc.end()) << "):";
        appendMsgToTextParseError(exc, ss.str(), loc);
        throw;
    }
}

MapItem::UP DtFromPseudoRootDtConverter::_tryCloneAttrs(const MapItem * const attrs)
{
    return tryCloneAttrs(attrs);
}

StructureType::UP dtFromPseudoRootDt(PseudoDt& pseudoDt, const Scope scope,
                                     const PseudoTraceType& pseudoTraceType,
                                     const PseudoDst * const curPseudoDst,
                                     const PseudoErt * const curPseudoErt)
{
    return DtFromPseudoRootDtConverter {
        pseudoDt, scope, pseudoTraceType, curPseudoDst, curPseudoErt
    }._releaseDt();
}

} // namespace internal
} // namespace yactfr
