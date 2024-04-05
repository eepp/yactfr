/*
 * Copyright (C) 2017-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>
#include <cassert>
#include <tuple>
#include <set>
#include <utility>

#include <yactfr/aliases.hpp>
#include <yactfr/metadata/aliases.hpp>
#include <yactfr/metadata/data-loc.hpp>
#include <yactfr/metadata/dl-array-type.hpp>
#include <yactfr/metadata/dl-str-type.hpp>
#include <yactfr/metadata/dst.hpp>
#include <yactfr/metadata/ert.hpp>
#include <yactfr/metadata/int-range.hpp>
#include <yactfr/metadata/sl-array-type.hpp>
#include <yactfr/metadata/sl-str-type.hpp>
#include <yactfr/metadata/struct-type.hpp>
#include <yactfr/metadata/trace-type.hpp>
#include <yactfr/metadata/var-type.hpp>
#include <yactfr/text-loc.hpp>
#include <yactfr/text-parse-error.hpp>

#include "pseudo-types.hpp"
#include "set-pseudo-dt-data-loc.hpp"
#include "../utils.hpp"

namespace yactfr {
namespace internal {
namespace {

void pseudoDataLocPathElemsToPathElems(const PseudoDataLoc::PathElems& pseudoDataLocPathElems,
                                       DataLocation::PathElements& pathElems)
{
    std::transform(pseudoDataLocPathElems.begin(), pseudoDataLocPathElems.end(),
                   std::back_inserter(pathElems),
                   [](const auto& pathElem) -> const std::string& {
        assert(pathElem.has_value());
        return *pathElem;
    });
}

} // namespace

/*
 * Setter of pseudo data type yactfr data locations.
 *
 * Helper class for setPseudoDtDataLoc().
 */
class DataLocSetter :
    boost::noncopyable
{
public:
    explicit DataLocSetter(PseudoDt& pseudoDt, const Scope scope) :
        _scope {scope}
    {
        this->_set(pseudoDt);
    }

private:
    /*
     * An entry of `_tMemberNames`.
     */
    using _tMemberNamesEntry = std::vector<const std::string *>;

    /*
     * A vector of `_tMemberNamesEntry`, used temporarily by _set() and
     * _dataLocFromPseudoDataLoc() to convert pseudo data locations to
     * yactfr data locations.
     */
    using _tMemberNames = std::vector<_tMemberNamesEntry>;

    // return type of _getPathElemsSuffixRel*()
    using _tGetPathElemsSuffixRelRet = std::pair<DataLocation::PathElements,
                                                 _tMemberNames::const_iterator>;

private:
    _tGetPathElemsSuffixRelRet _getPathElemsSuffixRel1(const PseudoDataLoc& pseudoDataLoc,
                                                       _tMemberNames::const_iterator searchEntryIt) const
    {
        assert(pseudoDataLoc.kind() == PseudoDataLoc::Kind::Rel1);

        DataLocation::PathElements pathElemsSuffix;

        // predicate for std::find_if() below
        const auto pred = call([&pseudoDataLoc] {
            // this is the name we're looking for (first)
            const auto& firstPathElem = *pseudoDataLoc.pathElems().front();

            return [&firstPathElem](const auto namePtr) {
                return firstPathElem == *namePtr;
            };
        });

        while (true) {
            if (std::find_if(searchEntryIt->begin(),
                             searchEntryIt->end(), pred) != searchEntryIt->end()) {
                pseudoDataLocPathElemsToPathElems(pseudoDataLoc.pathElems(), pathElemsSuffix);
                break;
            }

            /*
             * We can assert this because at this point the target
             * member name must exist. This is checked by
             * TsdlParser::_pseudoDataLocFromRelAllPathElems() when also
             * making sure that the target doesn't cross a data type
             * alias boundary.
             */
            assert(searchEntryIt != _memberNames.begin());
            --searchEntryIt;
        }

        return {pathElemsSuffix, searchEntryIt};
    }

    _tGetPathElemsSuffixRelRet _getPathElemsSuffixRel2(const PseudoDataLoc& pseudoDataLoc,
                                                       _tMemberNames::const_iterator searchEntryIt) const
    {
        assert(pseudoDataLoc.kind() == PseudoDataLoc::Kind::Rel2);

        // normalize the path (remove any unnecessary "parent" item)
        PseudoDataLoc::PathElems normPathElems;

        for (auto it = pseudoDataLoc.pathElems().begin();
                it != pseudoDataLoc.pathElems().end(); ++it) {
            if (*it) {
                // add member name
                normPathElems.push_back(*it);
            } else {
                // "parent"
                if (normPathElems.empty()) {
                    // empty path: add parent
                    normPathElems.push_back(boost::none);
                } else {
                    normPathElems.pop_back();
                }
            }
        }

        // now iterate the normalized path
        DataLocation::PathElements pathElemsSuffix;

        for (auto& pathElem : normPathElems) {
            if (pathElem) {
                // append as suffix
                pathElemsSuffix.push_back(*pathElem);
            } else {
                // go to parent, if any
                if (searchEntryIt == _memberNames.begin()) {
                    throwTextParseError("Cannot reach the parent of the root scope.",
                                        pseudoDataLoc.loc());
                }

                --searchEntryIt;
            }
        }

        return {pathElemsSuffix, searchEntryIt};
    }

    /*
     * Creates and returns a yactfr data location from the pseudo data
     * location `pseudoDataLoc` within the root scope `_scope`.
     */
    DataLocation _dataLocFromPseudoDataLoc(const PseudoDataLoc& pseudoDataLoc) const
    {
        /*
         * The `PseudoDataLoc::Kind::Env` is a temporary kind, which the
         * TSDL parser uses, leading to a `PseudoSlArrayType` instance
         * in TsdlParser::_parseArraySubscripts().
         *
         * Therefore it mustn't exist at this point.
         */
        assert(pseudoDataLoc.kind() != PseudoDataLoc::Kind::Env);

        if (pseudoDataLoc.kind() == PseudoDataLoc::Kind::Abs) {
            // already absolute
            DataLocation::PathElements pathElems;

            pseudoDataLocPathElemsToPathElems(pseudoDataLoc.pathElems(), pathElems);
            assert(pseudoDataLoc.scope());
            return DataLocation {*pseudoDataLoc.scope(), std::move(pathElems)};
        }

        /*
         * Relative location: start the search with the last entry of
         * `_memberNames`.
         */
        auto searchEntryIt = _memberNames.end() - 1;

        // relative data location path elements to append at the end
        DataLocation::PathElements pathElemsSuffix;

        if (pseudoDataLoc.kind() == PseudoDataLoc::Kind::Rel1) {
            std::tie(pathElemsSuffix, searchEntryIt) = this->_getPathElemsSuffixRel1(pseudoDataLoc,
                                                                                     searchEntryIt);
        } else {
            std::tie(pathElemsSuffix, searchEntryIt) = this->_getPathElemsSuffixRel2(pseudoDataLoc,
                                                                                     searchEntryIt);
        }

        /*
         * Now we go back from the first entry of `_memberNames` and
         * append the parent member names until we reach `searchEntryIt`
         * (excluding it).
         */
        DataLocation::PathElements pathElems;

        for (auto entryIt = _memberNames.begin(); entryIt != searchEntryIt; ++entryIt) {
            // last item of the entry is the parent name
            pathElems.push_back(*entryIt->back());
        }

        // append remaining suffix
        std::copy(pathElemsSuffix.begin(), pathElemsSuffix.end(), std::back_inserter(pathElems));
        return DataLocation {_scope, std::move(pathElems)};
    }

    /*
     * Sets the yactfr data locations of all the dynamic-length,
     * optional, and variant pseudo data types within `pseudoDt`.
     */
    void _set(PseudoDt& pseudoDt)
    {
        switch (pseudoDt.kind()) {
        case PseudoDt::Kind::SlArray:
        {
            this->_set(static_cast<PseudoSlArrayType&>(pseudoDt).pseudoElemType());
            break;
        }

        case PseudoDt::Kind::DlArray:
        {
            auto& pseudoArrayType = static_cast<PseudoDlArrayType&>(pseudoDt);

            pseudoArrayType.lenLoc(this->_dataLocFromPseudoDataLoc(pseudoArrayType.pseudoLenLoc()));
            this->_set(pseudoArrayType.pseudoElemType());
            break;
        }

        case PseudoDt::Kind::DlBlob:
        {
            auto& pseudoBlobType = static_cast<PseudoDlBlobType&>(pseudoDt);

            pseudoBlobType.lenLoc(this->_dataLocFromPseudoDataLoc(pseudoBlobType.pseudoLenLoc()));
            break;
        }

        case PseudoDt::Kind::Struct:
        {
            // new level
            _memberNames.push_back({});

            for (auto& pseudoMemberType : static_cast<PseudoStructType&>(pseudoDt).pseudoMemberTypes()) {
                /*
                 * Append this name before so that _createLocMap() can
                 * access the ancestor names.
                 */
                assert(pseudoMemberType->name());
                _memberNames.back().push_back(&(*pseudoMemberType->name()));
                this->_set(pseudoMemberType->pseudoDt());
            }

            _memberNames.pop_back();
            break;
        }

        case PseudoDt::Kind::Var:
        case PseudoDt::Kind::VarWithIntRanges:
        {
            auto& pseudoVarType = static_cast<PseudoVarType&>(pseudoDt);

            assert(pseudoVarType.pseudoSelLoc());
            pseudoVarType.selLoc(this->_dataLocFromPseudoDataLoc(*pseudoVarType.pseudoSelLoc()));

            for (auto& pseudoOpt : pseudoVarType.pseudoOpts()) {
                this->_set(pseudoOpt->pseudoDt());
            }

            break;
        }

        case PseudoDt::Kind::OptWithBoolSel:
        case PseudoDt::Kind::OptWithIntSel:
        {
            auto& pseudoOptType = static_cast<PseudoOptType&>(pseudoDt);

            pseudoOptType.selLoc(this->_dataLocFromPseudoDataLoc(pseudoOptType.pseudoSelLoc()));
            this->_set(pseudoOptType.pseudoDt());
            break;
        }

        default:
            break;
        }
    }

private:
    Scope _scope;
    _tMemberNames _memberNames;
};

void setPseudoDtDataLoc(PseudoDt& pseudoDt, const Scope scope)
{
    DataLocSetter setter {pseudoDt, scope};
}

} // namespace internal
} // namespace yactfr
