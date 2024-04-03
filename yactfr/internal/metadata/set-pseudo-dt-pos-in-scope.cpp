/*
 * Copyright (C) 2017-2023 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <algorithm>

#include "pseudo-types.hpp"
#include "set-pseudo-dt-pos-in-scope.hpp"

namespace yactfr {
namespace internal {
namespace {

void setPseudoDtPosInScope(PseudoDt& pseudoDt, Index& nextPos)
{
    pseudoDt.posInScope(nextPos);
    ++nextPos;

    switch (pseudoDt.kind()) {
    case PseudoDt::Kind::SlArray:
    case PseudoDt::Kind::DlArray:
    {
        setPseudoDtPosInScope(static_cast<PseudoArrayType&>(pseudoDt).pseudoElemType(), nextPos);
        break;
    }

    case PseudoDt::Kind::Struct:
    {
        auto& pseudoStructType = static_cast<PseudoStructType&>(pseudoDt);

        for (auto& pseudoMemberType : pseudoStructType.pseudoMemberTypes()) {
            setPseudoDtPosInScope(pseudoMemberType->pseudoDt(), nextPos);
        }

        break;
    }

    case PseudoDt::Kind::Var:
    case PseudoDt::Kind::VarWithIntRanges:
    {
        auto& pseudoVarType = static_cast<PseudoVarType&>(pseudoDt);
        Index maxNextPos = 0;

        for (auto& pseudoOpt : pseudoVarType.pseudoOpts()) {
            Index optNextPos = nextPos;

            setPseudoDtPosInScope(pseudoOpt->pseudoDt(), optNextPos);
            maxNextPos = std::max(maxNextPos, optNextPos);
        }

        nextPos = maxNextPos + 1;
        break;
    }

    case PseudoDt::Kind::OptWithBoolSel:
    case PseudoDt::Kind::OptWithIntSel:
    {
        auto& pseudoOptType = static_cast<PseudoOptType&>(pseudoDt);

        setPseudoDtPosInScope(pseudoOptType.pseudoDt(), nextPos);
        break;
    }

    default:
        break;
    }
}

} // namespace

void setPseudoDtPosInScope(PseudoDt& pseudoDt)
{
    Index nextPos = 0;

    setPseudoDtPosInScope(pseudoDt, nextPos);
}

} // namespace internal
} // namespace yactfr
