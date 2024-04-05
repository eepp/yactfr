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
        for (auto& pseudoMemberType : static_cast<PseudoStructType&>(pseudoDt).pseudoMemberTypes()) {
            setPseudoDtPosInScope(pseudoMemberType->pseudoDt(), nextPos);
        }

        break;
    }

    case PseudoDt::Kind::Var:
    case PseudoDt::Kind::VarWithIntRanges:
    {
        Index maxNextPos = 0;

        for (auto& pseudoOpt : static_cast<PseudoVarType&>(pseudoDt).pseudoOpts()) {
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
        setPseudoDtPosInScope(static_cast<PseudoOptType&>(pseudoDt).pseudoDt(), nextPos);
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
