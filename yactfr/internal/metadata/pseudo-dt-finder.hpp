/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef YACTFR_INTERNAL_METADATA_PSEUDO_DT_FINDER_HPP
#define YACTFR_INTERNAL_METADATA_PSEUDO_DT_FINDER_HPP

#include <type_traits>
#include <unordered_set>
#include <utility>
#include <string>

#include "pseudo-types.hpp"
#include "pseudo-dt-visitor.hpp"

namespace yactfr {
namespace internal {

template <typename ParentVisitorT>
class PseudoDtFinder :
    public ParentVisitorT
{
private:
    using _tIsConst = std::is_same<ParentVisitorT, ConstPseudoDtVisitor>;

    template <typename PseudoDtT>
    using _tPseudoDt = std::conditional_t<_tIsConst::value, const PseudoDtT, PseudoDtT>;

public:
    using PredFunc = std::function<bool (const PseudoDt&, const std::string *)>;
    using Set = std::conditional_t<_tIsConst::value, ConstPseudoDtSet, PseudoDtSet>;

public:
    explicit PseudoDtFinder(PredFunc predFunc) :
        _predFunc {std::move(predFunc)}
    {
    }

    const Set& set() const noexcept
    {
        return _set;
    }

    void visit(_tPseudoDt<PseudoScalarDtWrapper>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);
    }

    void visit(_tPseudoDt<PseudoFlUIntType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);
    }

    void visit(_tPseudoDt<PseudoSlArrayType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(_tPseudoDt<PseudoDlArrayType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(_tPseudoDt<PseudoDlBlobType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);
    }

    void visit(_tPseudoDt<PseudoStructType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);

        for (const auto& pseudoMemberType : pseudoDt.pseudoMemberTypes()) {
            assert(pseudoMemberType->name());
            _curMemberTypeName = &(*pseudoMemberType->name());
            pseudoMemberType->pseudoDt().accept(*this);
        }
    }

    void visit(_tPseudoDt<PseudoVarType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);

        for (const auto& pseudoOpt : pseudoDt.pseudoOpts()) {
            _curMemberTypeName = nullptr;
            pseudoOpt->pseudoDt().accept(*this);
        }
    }

    void visit(_tPseudoDt<PseudoVarWithIntRangesType>& pseudoDt) override
    {
        this->visit(static_cast<_tPseudoDt<PseudoVarType>&>(pseudoDt));
    }

    void visit(_tPseudoDt<PseudoOptWithBoolSelType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(_tPseudoDt<PseudoOptWithIntSelType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

private:
    void _visit(_tPseudoDt<PseudoArrayType>& pseudoDt)
    {
        this->_tryAdd(pseudoDt);
        _curMemberTypeName = nullptr;
        pseudoDt.pseudoElemType().accept(*this);
    }

    void _visit(_tPseudoDt<PseudoOptType>& pseudoDt)
    {
        this->_tryAdd(pseudoDt);
        _curMemberTypeName = nullptr;
        pseudoDt.pseudoDt().accept(*this);
    }

    void _tryAdd(_tPseudoDt<PseudoDt>& pseudoDt)
    {
        if (_predFunc(pseudoDt, _curMemberTypeName)) {
            _set.insert(&pseudoDt);
        }
    }

private:
    const PredFunc _predFunc;
    const std::string *_curMemberTypeName = nullptr;
    Set _set;
};

template <typename VisitorT, typename PseudoDtT>
auto commonFindPseudoDts(PseudoDtT& pseudoDt, typename VisitorT::PredFunc predFunc)
{
    VisitorT visitor {std::move(predFunc)};

    pseudoDt.accept(visitor);
    return visitor.set();
}

inline auto findPseudoDts(PseudoDt& pseudoDt, PseudoDtFinder<PseudoDtVisitor>::PredFunc predFunc)
{
    return commonFindPseudoDts<PseudoDtFinder<PseudoDtVisitor>>(pseudoDt, std::move(predFunc));
}

inline auto findPseudoDts(const PseudoDt& pseudoDt,
                          PseudoDtFinder<ConstPseudoDtVisitor>::PredFunc predFunc)
{
    return commonFindPseudoDts<PseudoDtFinder<ConstPseudoDtVisitor>>(pseudoDt, std::move(predFunc));
}

} // namespace internal
} // namespace yactfr

#endif // YACTFR_INTERNAL_METADATA_PSEUDO_DT_FINDER_HPP
