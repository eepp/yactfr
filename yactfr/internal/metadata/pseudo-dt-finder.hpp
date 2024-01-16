/*
 * Copyright (C) 2015-2024 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_INTERNAL_METADATA_PSEUDO_DT_FINDER_HPP
#define _YACTFR_INTERNAL_METADATA_PSEUDO_DT_FINDER_HPP

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
    using _IsConst = std::is_same<ParentVisitorT, ConstPseudoDtVisitor>;

    template <typename PseudoDtT>
    using _PseudoDt = std::conditional_t<_IsConst::value, const PseudoDtT, PseudoDtT>;

public:
    using PredFunc = std::function<bool (const PseudoDt&, const std::string *)>;
    using Set = std::conditional_t<_IsConst::value, ConstPseudoDtSet, PseudoDtSet>;

public:
    explicit PseudoDtFinder(PredFunc predFunc) :
        _predFunc {std::move(predFunc)}
    {
    }

    const Set& set() const noexcept
    {
        return _set;
    }

    void visit(_PseudoDt<PseudoScalarDtWrapper>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);
    }

    void visit(_PseudoDt<PseudoFlUIntType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);
    }

    void visit(_PseudoDt<PseudoSlArrayType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(_PseudoDt<PseudoDlArrayType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(_PseudoDt<PseudoDlBlobType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);
    }

    void visit(_PseudoDt<PseudoStructType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);

        for (const auto& pseudoMemberType : pseudoDt.pseudoMemberTypes()) {
            assert(pseudoMemberType->name());
            _curMemberTypeName = &(*pseudoMemberType->name());
            pseudoMemberType->pseudoDt().accept(*this);
        }
    }

    void visit(_PseudoDt<PseudoVarType>& pseudoDt) override
    {
        this->_tryAdd(pseudoDt);

        for (const auto& pseudoOpt : pseudoDt.pseudoOpts()) {
            _curMemberTypeName = nullptr;
            pseudoOpt->pseudoDt().accept(*this);
        }
    }

    void visit(_PseudoDt<PseudoVarWithIntRangesType>& pseudoDt) override
    {
        this->visit(static_cast<_PseudoDt<PseudoVarType>&>(pseudoDt));
    }

    void visit(_PseudoDt<PseudoOptWithBoolSelType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

    void visit(_PseudoDt<PseudoOptWithIntSelType>& pseudoDt) override
    {
        this->_visit(pseudoDt);
    }

private:
    void _visit(_PseudoDt<PseudoArrayType>& pseudoDt)
    {
        this->_tryAdd(pseudoDt);
        _curMemberTypeName = nullptr;
        pseudoDt.pseudoElemType().accept(*this);
    }

    void _visit(_PseudoDt<PseudoOptType>& pseudoDt)
    {
        this->_tryAdd(pseudoDt);
        _curMemberTypeName = nullptr;
        pseudoDt.pseudoDt().accept(*this);
    }

    void _tryAdd(_PseudoDt<PseudoDt>& pseudoDt)
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

static inline auto findPseudoDts(PseudoDt& pseudoDt,
                                 PseudoDtFinder<PseudoDtVisitor>::PredFunc predFunc)
{
    return commonFindPseudoDts<PseudoDtFinder<PseudoDtVisitor>>(pseudoDt, std::move(predFunc));
}

static inline auto findPseudoDts(const PseudoDt& pseudoDt,
                                 PseudoDtFinder<ConstPseudoDtVisitor>::PredFunc predFunc)
{
    return commonFindPseudoDts<PseudoDtFinder<ConstPseudoDtVisitor>>(pseudoDt, std::move(predFunc));
}

} // namespace internal
} // namespace yactfr

#endif // _YACTFR_INTERNAL_METADATA_PSEUDO_DT_FINDER_HPP
