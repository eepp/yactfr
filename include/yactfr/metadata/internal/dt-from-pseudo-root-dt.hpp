/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_INTERNAL_DT_FROM_PSEUDO_ROOT_DT_CONVERTER_HPP
#define _YACTFR_METADATA_INTERNAL_DT_FROM_PSEUDO_ROOT_DT_CONVERTER_HPP

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

#include "../../aliases.hpp"
#include "../../trace-env.hpp"
#include "../trace-type.hpp"
#include "../data-loc.hpp"
#include "../dst.hpp"
#include "../ert.hpp"
#include "../fl-enum-type.hpp"
#include "../int-range.hpp"
#include "../aliases.hpp"
#include "../metadata-parse-error.hpp"
#include "pseudo-types.hpp"
#include "data-loc-map.hpp"

namespace yactfr {
namespace internal {

StructureType::UP dtFromPseudoRootDt(const PseudoDt& pseudoDt, Scope scope,
                                     const PseudoTraceType& pseudoTraceType,
                                     const PseudoDst *curPseudoDst = nullptr,
                                     const PseudoErt *curPseudoErt = nullptr);

/*
 * Converter of root pseudo data type to yactfr data type.
 */
class DtFromPseudoRootDtConverter :
    boost::noncopyable
{
    friend StructureType::UP dtFromPseudoRootDt(const PseudoDt&, Scope, const PseudoTraceType&,
                                                const PseudoDst *, const PseudoErt *);

private:
    explicit DtFromPseudoRootDtConverter(const PseudoDt& pseudoDt, Scope scope,
                                         const PseudoTraceType& pseudoTraceType,
                                         const PseudoDst *curPseudoDst,
                                         const PseudoErt *curPseudoErt);

    /*
     * Releases and returns the resulting yactfr data type.
     */
    StructureType::UP releaseDt()
    {
        return std::move(_dt);
    }

private:
    /*
     * Finds and returns all the pseudo data types from `loc`.
     */
    ConstPseudoDtSet _findPseudoDts(const DataLocation& loc, const TextLocation& srcLoc) const;

    /*
     * Recursive version of the other _findPseudoDts(), filling
     * `pseudoDts` as it goes.
     *
     * `locIt` is the current path element, within `loc`, to consider;
     * it can be `loc.end()` in which case some leaf/resolution is
     * expected.
     */
    void _findPseudoDts(const PseudoDt& pseudoDt, const DataLocation& loc,
                        DataLocation::PathElements::const_iterator locIt,
                        const TextLocation& srcLoc, ConstPseudoDtSet& pseudoDts) const;

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
    template <typename StrTypeT, typename LenT>
    DataType::UP _tryNonNtStrTypeFromPseudoArrayType(const PseudoDt& pseudoArrayType,
                                                     const PseudoDt& pseudoElemType, LenT&& len);

    /*
     * Converts the pseudo static array type `pseudoDt` to a yactfr
     * static array type.
     */
    DataType::UP _dtFromPseudoStaticArrayType(const PseudoDt& pseudoDt);

    /*
     * Converts the pseudo dynamic array type `pseudoDt` to a yactfr
     * dynamic array type.
     */
    DataType::UP _dtFromPseudoDynArrayType(const PseudoDt& pseudoDt);

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
     * Converts the pseudo variant type `pseudoVarType` to a yactfr
     * variant type of type `VarTypeT`, the type of the selector being
     * `pseudoSelType` of yactfr type `SelTypeT`.
     */
    template <typename VarTypeT, typename MappingsT>
    DataType::UP _dtFromPseudoVarType(const PseudoVarType& pseudoVarType,
                                      const MappingsT& selTypeMappings, const DataLocation& selLoc);

    [[ noreturn ]] void _throwVarTypeInvalDataLoc(const std::string& initMsg,
                                                  const PseudoDt& pseudoDt,
                                                  const DataLocation& selLoc) const;

    template <typename ItT>
    static std::string _dataLocStr(Scope scope, ItT begin, ItT end);


    template <typename MappingsT>
    static bool _enumTypeMappingsOverlap(const MappingsT& mappings);

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

    // data locations
    DataLocMap _locMap;

    /*
     * Option/element indexes of currently visited pseudo variant and
     * dynamic array types (always 0 for a pseudo dynamic array type).
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
        str = "packet.header";
        break;

    case Scope::PACKET_CONTEXT:
        str = "packet.context";
        break;

    case Scope::EVENT_RECORD_HEADER:
        str = "stream.event.header";
        break;

    case Scope::EVENT_RECORD_COMMON_CONTEXT:
        str = "stream.event.context";
        break;

    case Scope::EVENT_RECORD_SPECIFIC_CONTEXT:
        str = "event.context";
        break;

    case Scope::EVENT_RECORD_PAYLOAD:
        str = "event.fields";
        break;

    default:
        std::abort();
    }

    for (auto it = begin; it != end; ++it) {
        str += '.';
        str += *it;
    }

    return str;
}

template <typename StrTypeT, typename LenT>
DataType::UP DtFromPseudoRootDtConverter::_tryNonNtStrTypeFromPseudoArrayType(const PseudoDt& pseudoArrayType,
                                                                              const PseudoDt& pseudoElemType,
                                                                              LenT&& len)
{
    if (pseudoElemType.isInt()) {
        bool hasEncoding;
        unsigned int align;
        unsigned int elemLen;

        if (pseudoElemType.isUInt()) {
            auto& pseudoIntElemType = static_cast<const PseudoFlUIntType&>(pseudoElemType);

            hasEncoding = pseudoIntElemType.hasEncoding();
            align = pseudoIntElemType.align();
            elemLen = pseudoIntElemType.len();
        } else {
            auto& pseudoScalarDtWrapper = static_cast<const PseudoScalarDtWrapper&>(pseudoElemType);
            auto& intType = pseudoScalarDtWrapper.dt().asFixedLengthSignedIntegerType();

            hasEncoding = pseudoScalarDtWrapper.hasEncoding();
            align = intType.alignment();
            elemLen = intType.length();
        }

        if (hasEncoding && align == 8 && elemLen == 8) {
            return std::make_unique<const StrTypeT>(8, std::forward<LenT>(len));
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
        this->_throwVarTypeInvalDataLoc("Selector type of variant type contains overlapping mappings.",
                                        pseudoVarType, selLoc);
    }

    typename VarTypeT::Options opts;

    for (auto i = 0U; i < pseudoVarType.pseudoOpts().size(); ++i) {
        // currently being visited
        _current[&pseudoVarType] = i;

        const auto& pseudoOpt = pseudoVarType.pseudoOpts()[i];
        auto optDt = this->_dtFromPseudoDt(pseudoOpt->pseudoDt());
        const auto rangesIt = selTypeMappings.find(pseudoOpt->name());

        // validate that the range set exists
        if (rangesIt == selTypeMappings.end()) {
            std::ostringstream ss;

            ss << "Selector type of variant type has no mapping named `" <<
                  pseudoOpt->name() << "`.";
            this->_throwVarTypeInvalDataLoc(ss.str(), pseudoVarType, selLoc);
        }

        opts.push_back(std::make_unique<const typename VarTypeT::Option>(pseudoOpt->name(),
                                                                         std::move(optDt), rangesIt->second));
    }

    // not visited anymore
    _current.erase(&pseudoVarType);

    return std::make_unique<const VarTypeT>(1, std::move(opts), selLoc);
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_METADATA_INTERNAL_DT_FROM_PSEUDO_ROOT_DT_CONVERTER_HPP
